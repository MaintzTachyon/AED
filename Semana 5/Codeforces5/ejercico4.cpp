#include <cstddef>
#include <stdexcept>

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
        if(top == nullptr) throw std::runtime_error("Stack is empty");

        return top->data;
    }


    std::size_t size()const{
        return count;
    }

    bool isEmpty()const{
        return top == nullptr;
    }

    ~Stack(){
        while(top != nullptr){
            pop();
        }
    }
};