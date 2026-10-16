#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class treebuilder {
    struct Node{
        T data;
        int height;
        Node* left;
        Node* right;

        Node(const T& value)
            : data(value), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    bool validateBST(Node* node, const T* lower, const T* upper){
        if (node == nullptr) {
            return true;
        }

        if (lower != nullptr && !(*lower < node->data)) {
            return false;
        }

        if (upper != nullptr && !(node->data < *upper)) {
            return false;
        }

        return validateBST(node->left, lower, &node->data) &&
               validateBST(node->right, &node->data, upper);
    }

    int validateAVL(Node* node){
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = validateAVL(node->left);
        int rightHeight = validateAVL(node->right);

        if (leftHeight == -1 || rightHeight == -1 ||
            std::abs(leftHeight - rightHeight) > 1) {
            return -1;
        }

        return 1 + std::max(leftHeight, rightHeight);
    }

    public:
    void build(int Nnodes){
        std::vector<Node*> nodes(Nnodes + 1, nullptr);
        std::vector<int> leftchild(Nnodes + 1);
        std::vector<int> rightchild(Nnodes + 1);
        std::vector<bool>hasParent(Nnodes + 1, false);

        for(int i = 1; i<= Nnodes; i++){
            T value;
            int leftIndex;
            int rightIndex;

            std::cin >> value >> leftIndex >> rightIndex;

            nodes[i] = new Node(value);
            leftchild[i] = leftIndex;
            rightchild[i] = rightIndex;

            if (leftIndex != 0) {
                hasParent[leftIndex] = true;
            }

            if (rightIndex != 0) {
                hasParent[rightIndex] = true;
            }
        }

        for (int i = 1; i <= Nnodes; i++) {
            if (leftchild[i] != 0) {
                nodes[i]->left = nodes[leftchild[i]];
            }

            if (rightchild[i] != 0) {
                nodes[i]->right = nodes[rightchild[i]];
            }
        }

        for (int i = 1; i <= Nnodes; i++) {
            if (!hasParent[i]) {
                root = nodes[i];
                break;
            }
        }
    }

    bool isBST(){
        return validateBST(root, nullptr, nullptr);
    }

    bool isAVL(){
        return isBST() && validateAVL(root) != -1;
    }
};



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int numberOfTrees;
    std::cin >> numberOfTrees;

    for (int i = 0; i < numberOfTrees; i++) {
        int numberOfNodes;
        std::cin >> numberOfNodes;

        treebuilder<int> tree;
        tree.build(numberOfNodes);

        if (tree.isAVL()) {
            std::cout << "AVL\n";
        } else if (tree.isBST()) {
            std::cout << "BST\n";
        } else {
            std::cout << "NINGUNO\n";
        }
    }
    return 0;
}