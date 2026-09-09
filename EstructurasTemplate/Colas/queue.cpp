#include <iostream>
#include <optional>
#include <utility>

template<typename T>
class Queue{
    struct Node{
        T data;
        Node* next= nullptr;

        Node(const T& val, Node* n = nullptr) : data(val), next(n){}
    };
    Node* top = nullptr;
    Node* tail = nullptr;
    public:

    Queue():top(nullptr), tail(nullptr){}
    Queue(const Queue& other): top (nullptr){
        Node* curr = other.top;

        while (curr != nullptr){
            push(curr->data);
            curr = curr->next;
        }
    }


    Queue& operator=(const Queue& other){
        if (this == &other){
            return *this;
        }

        Queue copy(other);

        std::swap(top, copy.top);
        std::swap(tail, copy.tail);

        return *this;
    }

    void push(const T& val){
        Node* nNode = new Node(val, nullptr);
        if(top == nullptr){
            top = nNode;
            tail = nNode;
            return;
        }
        tail->next = nNode;
        tail = nNode;
    }

    void pop(){
        if (top == nullptr) return;
        if (top->next == nullptr){
            delete top;
            top = nullptr;
            tail = nullptr;
            return;
        }
        Node*temp = top;
        top = top->next;
        delete temp;
    }

    std::optional<T> front()const{
        if (top == nullptr){
            return std::nullopt;
        }
        return top->data;
    }

    std::optional<T> back() const{
        if (tail == nullptr){
            return std::nullopt;
        }
        return tail->data;
    }

    bool empty()const{
        if(top != nullptr) return false;
        else return true;
    }

    ~Queue(){
        Node* curr = top;
        while(top != nullptr){
            top = top->next;
            delete curr;
            curr = top;
        }
        top = nullptr;
        tail = nullptr;
    }
};