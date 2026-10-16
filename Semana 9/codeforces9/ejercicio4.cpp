#include <iostream>
#include <algorithm>

class AVL{
    struct Node{
        int data;
        int height;
        Node* left;
        Node* right;

        Node(int value){
            data = value;
            height = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root = nullptr;

    int height(Node* node){
        if (node == nullptr) return 0;
        return node->height; 
    }

    int getBalance(Node* node){
        if (node == nullptr) return 0;

        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node){
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    Node* rotateLeft(Node* x){
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);
        
        return y;
    }

    Node* rotateRight(Node* y){
        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    Node* rebalance(Node* node){
        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1){
            if (getBalance(node->left) < 0){
                node->left = rotateLeft(node->left);
            }

            return rotateRight(node);
        }

        if (balance < -1){
            if (getBalance(node->right) > 0){
                node->right = rotateRight(node->right);
            }

            return rotateLeft(node);
        }
        
        return node;
    }

    Node* insert(Node* node, int value){
        if (node == nullptr) return new Node(value);

        if (value < node->data) node->left = insert(node->left, value);
        else if (value > node->data) node->right = insert(node->right, value);
        else return node;

        return rebalance(node);
    }

    bool search(Node* node, int value){
        if (node == nullptr) return false;

        if (node->data == value)return true;
        
        if (value < node->data) return search(node->left, value);

        return search(node->right, value);
    }

    Node* minNode(Node* node){
        while(node->left != nullptr){
            node = node->left;
        }

        return node;
    }

    Node* remove(Node* node, int value){
        if(node == nullptr) return nullptr;

        if (value < node->data){
            node->left = remove(node->left, value);
        }
        else if(value > node->data){
            node->right = remove(node->right, value);
        }
        else{
           if (node->left == nullptr || node->right == nullptr){
            Node* child = node->left != nullptr ? node->left: node->right;
            delete node;
            return child;
           } 

           Node* succesor = minNode(node->right);

           node->data = succesor->data;

           node->right = remove(node->right, succesor->data);
        }

        return rebalance(node);
    }

    void Preorder(Node* root){
        if(root == nullptr)return;

        std::cout << root->data << " ";

        Preorder(root->left);
        Preorder(root->right);

    }

    void Inorder(Node* root){
        if(root == nullptr)return;

        Inorder(root->left);
        std::cout << root->data << " ";
        Inorder(root->right);
    }

    void Postorder(Node* root){
        if(root == nullptr)return;

        Postorder(root->left);
        Postorder(root->right);
        std::cout << root->data << " ";
    }

    void clear(Node* node){
        if (node == nullptr) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

    public:
    AVL() = default;

    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

     ~AVL() {
        clear(root);
    }

    void insertV(int value) {
        root = insert(root, value);
    }

    void remove(int value) {
        root = remove(root, value);
    }

    bool search(int value) {
        return search(root, value);
    }

    void inOrder() {
        Inorder(root);
        std::cout << "\n";
    }

    void preOrder() {
        Preorder(root);
        std::cout << "\n";
    }

    void postOrder() {
        Postorder(root);
        std::cout << "\n";
    }

    int getHeight() {
        return height(root);
    }

    int getRoot(){
        return root->data;
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Nnodes;

    std::cin >> Nnodes;


    AVL tree;

    for(int i = 0; i < Nnodes; i++){
        int value;

        std::cin >> value;

        tree.insertV(value);

        std::cout << tree.getHeight() - 1 << " " << tree.getRoot() << "\n";
    }
    

    return 0;
}