#include <iostream>
#include <string>
#include <vector>
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

    public:

    Stack() = default;

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& val){
        top = new Node(val, top);
    }

    void pop(){
        if (top == nullptr)return;
        
        Node*temp = top;
        top = top->next;
        delete temp;
    }

    bool isEmpty() const{
        return top == nullptr;
    }

    const T& peek()const{
        if(top == nullptr) throw std::runtime_error("Stack is empty");

        return top->data;
    }

    bool validation(const std::vector<T>& reff){
        Stack<T> pila;

        for (std::size_t i = 0; i < reff.size(); ++i){
            T symbol = reff[i];

            if (symbol == '(' || symbol == '[' || symbol == '{'){
                pila.push(symbol);
            }
            else if(symbol == ')' || symbol == ']' || symbol== '}'){
                if(pila.isEmpty())return false;

                T open = pila.peek();

                bool validPair = 
                (open == '(' && symbol == ')')||
                (open == '[' && symbol == ']')||
                (open == '{' && symbol == '}');

                if (!validPair){
                    return false;
                }
                pila.pop();
            }
        }

        return pila.isEmpty();
    }

    ~Stack(){
        while(top != nullptr){
            pop();
        }
    }
};


int main(){
    int n;
    std::cin>> n;
    
    Stack<char> val;

    for (int i = 0; i < n; i++){
        std::string text;
        std::cin >> text;

        std::vector<char> symbols(text.begin(), text.end());

        if (val.validation(symbols)){
            std::cout << "YES" << '\n';
        }else{
            std::cout << "NO" << '\n';
        }
    }
}
