#include <iostream>
#include <string>

template<typename T>
class doublelinkedlist{
    struct Node{
        T data;
        Node* next;
        Node* prev;

        Node(const T& val, Node* p, Node* n) : data (val), next(n), prev(p) {}
    }
    Node * head;
    Node * tail;
    public:
        void insert(const T& val){
            Node* newNode = new Node(val, nullptr, head);
            if (head != nullptr){
                head->prev = newNode;
            }else{
                tail = newNode;
            }
            head = newNode;
        }

        void deletex(const T& val){
            if (head == nullptr)return;
            Node* curr = head;
            while(curr!= nullptr){
                if (curr->data == val){}
                    unlink(curr);
                }
            }
        }
}

int main(){
    int n;
    std::cin >> n;

    doublelinkedlist<int> list;

    for (int i = 0; i<n ; i++){
        std::string operation;
        std::cin >> operation;
        if (operation == "insert"){
            int x;
            std::cin >> x;
            list.insert(x);
        } else if(operation == "delete"){
            int x;
            std::cin >> x;
            list.deletex(x);
        }else if(operation == "deleteFirst"){
            list.deleteFirst();
        } else if(operation == "deleteLast"){
            list.deleteLast();
        }
    }
    list.print();

    return 0;
}