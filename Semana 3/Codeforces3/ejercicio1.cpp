#include <iostream>
#include <unordered_map>
#include <list>

template<typename T>
class doublelinkedlist{
    struct Node{
        T* data;
        Node * next = nullptr;
        Node * prev = nullptr;

        Node(const T& value): data(new T(value)){}
        ~Node(){delete data;}
    };
    Node * head = nullptr;
    Node * tail = nullptr;
    std::unordered_map<T, Node*> list;

    public:

    Node* insert (const T& value){
        Node* nhead = new Node(value);
        nhead->prev = nullptr;
        nhead->next = head;

        if(head!=nullptr){
            head->prev = nhead;
        }else{
            tail = nhead;
        }
        
        head = nhead;

        index[value].push_back(nhead);

        return head;
    }
/*
    bool deletex(T& x){
        Node* curr = head;
        while (curr != nullptr){
            if(*(curr->data) == x){
                if (curr->prev != nullptr){
                    curr->prev->next = curr->next;
                }else{
                    head = curr->next;
                }

                if (curr->next != nullptr){
                    curr->next->prev = curr->prev;
                }else{
                    tail = curr->prev;
                }
                delete curr;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

*/

    bool deletex(const T& x){
        auto it = list.find(x);
        if (it == list.end() || it->second.empty())return false;

        Node* curr = it->second.front();
        it->second.pop_front();
        if(it->second.empty())index.erase(it);

        if (curr->prev != nullptr){
            curr->prev->next = curr->next;
        }else{
            head = curr->next;
        }
        
        if (curr->head != nullptr){
            curr->next->prev = curr->prev;
        }else{
            tail = curr->prev;
        }
        delete curr;
        return true;

    }
/*
    Node* deleteFirst(){
        Node* temp = head;
        if(head == nullptr){
            return nullptr;
        }else if(head->next == nullptr){
            delete head;

            head = nullptr;
            tail = nullptr;

            return nullptr;
        }else{
            head = temp->next;
            head->prev = nullptr;
            delete temp;
        }
        return head;
    }

    Node* deleteLast(){
        Node* temp = tail;
        if(tail == nullptr){
            return nullptr;
        }else if(tail->prev == nullptr){
            delete tail;
            head = nullptr;
            tail = nullptr;
        }else{
            tail = temp->prev;
            tail->next = nullptr;
            delete temp;
        }
        return tail;
    }

    void print(){
        Node* curr = head;
        while(curr != nullptr){
            std::cout << *(curr->data);
            if (curr->next != nullptr){
                std::cout << " ";
            }
            curr = curr->next;
        }
        std::cout << std::endl;
    }
};
*/
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