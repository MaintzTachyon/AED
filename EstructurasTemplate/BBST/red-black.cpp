#include <iostream>
#include <string>

using namespace std;

enum Color {red, black};

struct Node{
    int data;
    Color color;
    Node* left; 
    Node* right;
    Node* parent;

    Node(int value): 
    data(value), color(red), left(nullptr),
    right(nullptr), parent(nullptr)  {}

};

class RedBlackTree{
    Node* root;
    Node* nil;

    void rotateLeft(Node* x){
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nil)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nil)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;

        if (y->right != nil)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nil)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node* z) {
        while (z->parent->color == red) {
            if (z->parent == z->parent->parent->left) {
                Node* uncle = z->parent->parent->right;

                if (uncle->color == red) {
                    z->parent->color = black;
                    uncle->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }

                    z->parent->color = black;
                    z->parent->parent->color = red;
                    rotateRight(z->parent->parent);
                }
            } else {
                Node* uncle = z->parent->parent->left;

                if (uncle->color == red) {
                    z->parent->color = black;
                    uncle->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }

                    z->parent->color = black;
                    z->parent->parent->color = red;
                    rotateLeft(z->parent->parent);
                }
            }
        }

        root->color = black;
    }

    Node* findNode(int data) const {
        Node* current = root;

        while (current != nil) {
            if (data == current->data)
                return current;

            if (data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        return nil;
    }

    Node* minimum(Node* node) const {
        while (node->left != nil)
            node = node->left;

        return node;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nil)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }

    void fixDelete(Node* x) {
        while (x != root && x->color == black) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;

                if (w->color == red) {
                    w->color = black;
                    x->parent->color = red;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }

                if (w->left->color == black &&
                    w->right->color == black) {
                    if (w != nil)
                        w->color = red;
                    x = x->parent;
                } else {
                    if (w->right->color == black) {
                        w->left->color = black;
                        w->color = red;
                        rotateRight(w);
                        w = x->parent->right;
                    }

                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    rotateLeft(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;

                if (w->color == red) {
                    w->color = black;
                    x->parent->color = red;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == black &&
                    w->left->color == black) {
                    if (w != nil)
                        w->color = red;
                    x = x->parent;
                } else {
                    if (w->left->color == black) {
                        w->right->color = black;
                        w->color = red;
                        rotateLeft(w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }

        x->color = black;
    }

    void inorderHelper(Node* node) const {
        if (node == nil)
            return;

        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

    void printHelper(Node* node, string indent,
                     bool last) const {
        if (node == nil)
            return;

        cout << indent;

        if (last) {
            cout << "R----";
            indent += "     ";
        } else {
            cout << "L----";
            indent += "|    ";
        }

        cout << node->data
             << (node->color == red ? "(R)" : "(B)")
             << '\n';

        printHelper(node->left, indent, false);
        printHelper(node->right, indent, true);
    }

    void clear(Node* node) {
        if (node == nil)
            return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    RedBlackTree() {
        nil = new Node(0);
        nil->color = black;
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;

        root = nil;
    }

    ~RedBlackTree() {
        clear(root);
        delete nil;
    }

    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;

    void insert(int data) {
        Node* parent = nil;
        Node* current = root;

        while (current != nil) {
            parent = current;

            if (data == current->data)
                return;

            if (data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        Node* z = new Node(data);
        z->parent = parent;
        z->left = nil;
        z->right = nil;

        if (parent == nil)
            root = z;
        else if (data < parent->data)
            parent->left = z;
        else
            parent->right = z;

        fixInsert(z);
    }

    bool search(int data) const {
        return findNode(data) != nil;
    }

    void remove(int data) {
        Node* z = findNode(data);

        if (z == nil)
            return;

        Node* y = z;
        Node* x;
        Color originalColor = y->color;

        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            originalColor = y->color;
            x = y->right;

            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (originalColor == black)
            fixDelete(x);

        nil->parent = nil;
    }

    void inorder() const {
        inorderHelper(root);
        cout << '\n';
    }

    void printTree() const {
        if (root == nil) {
            cout << "Empty\n";
            return;
        }

        printHelper(root, "", true);
    }


};