#include <iostream>
#include <initializer_list>
#include <utility>
#include <string>

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

        //valida si existe el valor a buscar
        bool search(const T& val){
            Node* curr = head;

            while(curr != nullptr){
                if (curr->data == val)return true;
                curr = curr->next;
            }
            return false;
        }

        //muestra el valor a buscar en caso que exista
        T* find(const T& val){
            Node* curr = head;

            while (curr != nullptr){
                if(curr->data == val){
                    return &curr->data;
                }
                curr = curr->next;
            }
            return nullptr;
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

            while(curr != nullptr && !(curr->data == x)){
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

            while (curr != nullptr && !(curr->data == ref)){
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


template<typename T>
class Diccionary{
    struct Entry{
        int key;
        T value;

        bool operator==(const Entry& other)const{
            return key == other.key;
        }
    };

    linked_list<Entry>* table;
    int bucketcount;
    int Nelements;

    int hashFunction(const int& key) const{
        int index = key % bucketcount;
        return index < 0 ? index + bucketcount : index;
    }

public:

    explicit Diccionary(int buckets = 20): 
        table(new linked_list<Entry>[buckets > 0 ? buckets : 1]),
        bucketcount(buckets > 0 ? buckets : 1),
        Nelements(0){}

    Diccionary(const Diccionary& other)
        : table(new linked_list<Entry>[other.bucketcount]),
          bucketcount(other.bucketcount),
          Nelements(other.Nelements) {
        for (int i = 0; i < bucketcount; ++i)
            table[i] = other.table[i];
    }

    Diccionary& operator=(const Diccionary& other){
        if (this == &other)
            return *this;

        linked_list<Entry>* newTable = new linked_list<Entry>[other.bucketcount];

        for (int i = 0; i < other.bucketcount; ++i){
            newTable[i] = other.table[i];
        }

        delete[] table;
        table = newTable;
        bucketcount = other.bucketcount;
        Nelements = other.Nelements;

        return *this;
    }

    void insert(const int& key, const T& val){
        int index = hashFunction(key);

        Entry e{key, val};

        Entry* entry = table[index].find(e);
        if(entry != nullptr){
            entry->value = val;
            return;
        }

        table[index].push_front(e);
        ++Nelements;
    }

    T* searchVal(const int& key){
        int index = hashFunction(key);

        Entry search{key,T{}};
        Entry* entry = table[index].find(search);

        if(entry!= nullptr){
            return &entry->value;
        }

        return nullptr;
    }

    bool deleteVal(const int& key){ 
        int index = hashFunction(key);
        Entry entryremove{key, T{}};
        if(table[index].removeX(entryremove)){ 
            --Nelements;
            return true; 
        } 
        return false; 
    }

    ~Diccionary(){
        delete[] table;
    }
};



int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nops;
    std::cin >> nops;
    Diccionary<int> diccionary(nops > 0 ? 2 * nops + 1 : 1);

    for (int i = 0; i < nops;++i){
        std::string op;
        std::cin>> op;
        int key;
        if (op == "INSERTAR"){
            int val;
            std::cin>> key;
            std::cin>> val;
            diccionary.insert(key,val);
        }else if(op == "BUSCAR"){
            std::cin>>key;
            int * result = diccionary.searchVal(key);

            if (result != nullptr){
                std::cout << *result << '\n';
            }else{
                std::cout << "NO EXISTE\n";
            }
        }else if(op == "ELIMINAR"){
            std::cin>>key;
            diccionary.deleteVal(key);
        }
    }


    return 0;
}
