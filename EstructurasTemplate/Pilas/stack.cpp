#include <iostream>
#include <stdexcept>
#include <cstddef>

template<typename T>
class Stack{
    struct Node{
        T data;
        Node* next = nullptr;
        Node(const T& d, Node* n = nullptr): data(d), next(n){}
    };
    Node* top = nullptr;
    std::size_t count = 0;

    public:

    Stack() = default;

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& val){
        top = new Node(val, top);
        ++count;
    }

    void pop(){
        if (top == nullptr)return;
        
        Node*temp = top;
        top = top->next;
        delete temp;
        --count;
    }

    const T& peek()const{
        if(topp == nullptr) throw std::runtime_error("Stack is empty");

        return top->value;
    }


    std::size_t size(){
        return count;
    }

    bool isEmpty(){
        return top == nullptr;
    }

    ~Stack(){
        while(top != nullptr){
            pop();
        }
    }
};