#include <iostream>

template<typename T>
class BST{
    struct node{
        T value;
        node* left;
        node* right;

        node(T val){
            value = val:
            left = right = nullptr;
        }
    };

    
    public:

    node* insert(node* root, const T& key){
        if (root == nullptr){return new Node(key);}

        if (key = root->value){return root;}

        if (key < root->value){root->left = insert(root->left, key);
        }else{root->right = insert(root->right, key);}

    }


    node* search(const T& val, node* root){
        if (root == nullptr)return nullptr;

        if (root->value < val)return search(val, root->right);
        if (root->value > val)return search(val, root->left);

        return root;
    }

    void Preorder(node* root){
        if(root == nullptr)return;

        std::cout << root->value << " ";

        Preorder(root->left);
        Preorder(root->right);

    }

    void Inorder(node* root){
        if(root == nullptr)return;

        Inorder(root->left);
        std::cout << root->value << " ";
        Inorder(root->right);
    }

    void Postorder(node* root){
        if(root == nullptr)return;

        Postorder(root->left);
        Postorder(root->right);
        std::cout << root->value << " ";
    }
};


