#include <iostream>

template<typename T>
class doublelinkedlist{
    struct Node{
        T data;
        Node* next;
        Node* prev;
        Node(const T& val, Node* n, Node* p): data(val), next(n), prev(p){}
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    public:

    doublelinkedlist():head(nullptr), tail(nullptr){}

    void push_front(const T& val){
        Node* nNode = new Node(val, head, nullptr);
        head = nNode;
    }

    void pop_front(){
        if (head == nullptr)return;
        Node* curr = head;
        head = head->next;
        delete curr;
    }

    void push_back(const T& val){
        Node* nNode = new Node(val, nullptr, tail);
        tail->next = nNode;
        tail = nNode;
    }

    void pop_back(){
        if (head == nullptr)return;
        if (head->next == nullptr)

        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    }

    bool search(const T& val){

    }
};