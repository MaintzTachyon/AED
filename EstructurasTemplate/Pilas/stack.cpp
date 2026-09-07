#include <iostream>

template<typename T>
class Stack{
    struct Node{
        T data;
        Node* next = nullptr;

        Node(const T& d, Node* n = nullptr): data(d), next(n){}
    };
    Node* top = nullptr;
    public:

    void push(const T& val){
        Node* newNode = new Node();
        newNode->data = val;
        newNode->next = top;
        top = newNode;
    }

    void pop(){
        Node*temp = top;
        top = top->next;
        delete temp;
    }
};