#include <iostream>
#include <initializer_list>
#include <utility>

template<typename T>
class linked_list{
    struct Node{
        T data; 
        Node* next;
        Node(const T& val, Node* n) : data(val), next(n) {}
    };
    Node* head = nullptr;
    
    public:

        linked_list() : head(nullptr){}
        linked_list(const linked_list& other) : head(nullptr){
            Node* curr = other.head;

            while(curr!= nullptr){
                push_back(curr->data);
                curr = curr->next;
            }
        }

        linked_list(std::initializer_list<T> init): head(nullptr){
            for(const T& val : init){
                push_back(val);
            }
        }

        linked_list& operator=(const linked_list& other){
            if(this == &other){
                return *this;
            }

            linked_list copy(other);
            std::swap(head, copy.head);
            return *this;
        }

        void push_front(const T& val){
            Node * nNode = new Node(val, head);
            head = nNode;
        }

        void pop_front(){
            if (head == nullptr)return;
            Node * curr = head;
            head = head->next;
            delete curr;
        }

        void push_back(const T& val){
            Node * nNode = new Node(val, nullptr);
            
            if (head == nullptr){
                head = nNode;
                return;
            }

            Node * curr = head;

            while(curr->next != nullptr){
                curr = curr->next;
            }

            curr->next = nNode;
        }

        void pop_back(){

            if (head == nullptr)return;

            if (head->next == nullptr){
                delete head;
                head = nullptr;
                return;
            }

            Node * curr = head;

            while (curr->next->next != nullptr){
                curr = curr->next;

            }

            delete curr->next;
            curr->next = nullptr;
        }

        bool search(const T& val){
            Node* curr = head;

            while(curr != nullptr){
                if (curr->data == val)return true;
                curr = curr->next;
            }
            return false;
        }

        bool removeX(const T& x){
            if (head == nullptr)return false;


            if (head->data == x){
                Node* temp = head;
                head = head-> next;
                delete temp;
                return true;
            }

            Node* prev = head;
            Node* curr = head->next;

            while(curr != nullptr && curr->data != x){
                prev = curr;
                curr = curr->next;
            }
            if (curr == nullptr){
                return false;
            }
            
            prev->next = curr->next;
            delete curr;
            
            return true;
        }

        void reverse(){
            Node* curr = head;
            Node* prev = nullptr;

            while (curr!= nullptr){
                Node* next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            head = prev;
        }

        bool insertX(const T& ref, const T& x){
            
            Node* curr = head;

            while (curr != nullptr && curr->data != ref){
                curr = curr->next;
            }

            if (curr == nullptr) return false;

            Node* nNode = new Node(x, curr->next);
            curr->next = nNode;

            return true;
        }

        static linked_list join(const linked_list& list1, const linked_list& list2){
            linked_list newlist;
            Node* curr1 = list1.head;
            Node* curr2 = list2.head;

            while (curr1 != nullptr && curr2 != nullptr ){
                if (curr1->data <= curr2->data){
                    newlist.push_back(curr1->data);
                    curr1 = curr1->next;
                }else{
                    newlist.push_back(curr2->data);
                    curr2 = curr2->next;
                }
            }
            while (curr1 != nullptr){
                newlist.push_back(curr1->data);
                curr1 = curr1->next;
            }

            while (curr2 != nullptr){
                newlist.push_back(curr2->data);
                curr2 = curr2->next;
            }

            return newlist;
        }

        virtual ~linked_list(){
            while (head != nullptr){
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

};