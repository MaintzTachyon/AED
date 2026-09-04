#include <iostream>
#include <string>

template<typename T>
class doublelinkedlist{
    struct Node{
        T data;
        Node* next;
        Node* prev;

        Node(const T& val, Node* p, Node* n) : data (val), next(n), prev(p) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;
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
                    delete curr;
                }
                curr = curr->next;
        }

        void deleteFirst(){
            if (head == nullptr) return;
            Node* temp = head;
            unlink(temp);
            delete temp;
        }

        void deleteLast(){
            if (tail == nullptr)return;
            Node* temp = tail;
            unlink(temp);
            delete temp;
        }

        void print(std::ostream& out)const{
            Node* curr = head;
            bool first = true;
            while(curr != nullptr){
                if (!first) out << " ";
                out << curr->data;
                first = false;
                curr = curr->next;
            }
            out << '\n';
        }

        ~doublelinkedlist(){
            Node* curr = head;
            while(curr != nullptr){
                Node* next = curr->next;
                delete curr;
                curr = next;
            }
        }  
    private:
        void unlink(Node* node){
            if (node->prev != nullptr) node->prev->next = node->next;
            else head = node->next;

            if (node->next != nullptr) node->next->prev = node->prev;
            else tail = node->prev;
        }

};


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

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
    
    list.print(std::cout);

    return 0;
}