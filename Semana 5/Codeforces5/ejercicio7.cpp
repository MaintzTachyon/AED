#include <iostream>
#include <cstddef>
#include <stdexcept>

template<typename T>
class Stack{
    struct Node{
        T data;
        T Max_val;
        Node* next = nullptr;

        Node(const T& d, const T& m, Node* n = nullptr)
            : data(d), Max_val(m), next(n) {}
    };
    Node* top = nullptr;
    std::size_t count = 0;

    public:

    Stack() = default;

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& val){
        T currentMax = (top == nullptr || val > top->Max_val)? val: top->Max_val;

        top = new Node(val, currentMax, top);
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

    void MaxVal()const{
        if (top != nullptr) {
            std::cout << top->Max_val << '\n';
        }
    }

    ~Stack(){
        while(top != nullptr){
            pop();
        }
    }
};


int main(){
    int iter;
    Stack<int> a;
    std:: cin >> iter;


    for(int i = 0; i< iter ; i++){
        int val, op;
        std::cin >> op;
        if(op == 1){
            std::cin >> val;
            a.push(val);
        }else if(op == 2){
            a.pop();
        }else if (op == 3){
            a.MaxVal();
        }
    }

}