#include <iostream>
#include <utility>
#include <string>

template<typename T>
class Queue{
    struct Node{
        T data;
        Node* next= nullptr;
        Node* prev = nullptr;
        Node(const T& val, Node* n = nullptr, Node* p = nullptr) : data(val), next(n), prev(p){}
    };
    Node* top = nullptr;
    Node* tail = nullptr;
    bool reversed = false;
    public:

    Queue():top(nullptr), tail(nullptr){}
    Queue(const Queue& other): top (nullptr), tail(nullptr){
        Node* curr = other.reversed ? other.tail : other.top;

        while (curr != nullptr){
            push_back(curr->data);
            curr = other.reversed ? curr->prev : curr->next;
        }
    }


    Queue& operator=(const Queue& other){
        if (this == &other){
            return *this;
        }

        Queue copy(other);

        std::swap(top, copy.top);
        std::swap(tail, copy.tail);
        std::swap(reversed, copy.reversed);

        return *this;
    }

    void push_back(const T& val){
        Node* nNode = new Node(val, nullptr);
        if(top == nullptr){
            top = nNode;
            tail = nNode;
            return;
        }
        if (!reversed) {
            nNode->prev = tail;
            tail->next = nNode;
            tail = nNode;
        } else {
            nNode->next = top;
            top->prev = nNode;
            top = nNode;
        }
    }

    void toFront(const T& val){
        Node* nNode = new Node(val, nullptr);
        if(top == nullptr){
            top = nNode;
            tail = nNode;
            return;
        }
        if (!reversed) {
            nNode->next = top;
            top->prev = nNode;
            top = nNode;
        } else {
            nNode->prev = tail;
            tail->next = nNode;
            tail = nNode;
        }
    }

    void front(){
        if (top == nullptr) {
            std::cout << "No job for Ada?" << '\n';
            return;
        }
        if (!reversed) {
            Node* temp = top;
            std::cout << temp->data << '\n';
            top = top->next;
            if (top == nullptr) tail = nullptr;
            else top->prev = nullptr;
            delete temp;
        } else {
            Node* temp = tail;
            std::cout << temp->data << '\n';
            tail = tail->prev;
            if (tail == nullptr) top = nullptr;
            else tail->next = nullptr;
            delete temp;
        }
    }

    void back(){
        if (top == nullptr) {
            std::cout << "No job for Ada?" << '\n';
            return;
        }
        if (!reversed) {
            Node* curr = tail;
            std::cout << curr->data << '\n';
            tail = tail->prev;
            if (tail == nullptr) top = nullptr;
            else tail->next = nullptr;
            delete curr;
        } else {
            Node* curr = top;
            std::cout << curr->data << '\n';
            top = top->next;
            if (top == nullptr) tail = nullptr;
            else top->prev = nullptr;
            delete curr;
        }
        
    }

    void reverse(){
        reversed = !reversed;
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

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Queue<int> queue;
    int iter = 0;
    std::cin>>iter;
    
    for (int i = 0;i<iter;i++){
        std::string command;
        std::cin>> command;

        if (command == "toFront") {
            int value;
            std::cin >> value;
            queue.toFront(value);
        } else if (command == "push_back") {
            int value;
            std::cin >> value;
            queue.push_back(value);
        } else if (command == "front") {
            queue.front();
        } else if (command == "back") {
            queue.back();
        } else if (command == "reverse") {
            queue.reverse();
        }

    }
    return 0;
}