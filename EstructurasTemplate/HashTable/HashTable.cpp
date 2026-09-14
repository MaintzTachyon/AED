#include "../linkedlists/Linkedlist.cpp"

template<typename T>
class HashTable{
    struct Hash{
        linked_list<linked_list<T>> table;
        int bucket;
        int elements;
    };

    public:

    Hashtable() = default;

    void insert(const T& index, const T& value){
        
        
    }

    T Hashfunction(int i){
        return (i % bucket);
    }
};