#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

class HashTable{
    std::vector<std::vector<int>> table;

    int bucket;
    int Nelements;

    int hashFunction(const int& k){
        if (bucket == 0) throw std::invalid_argument("The number of buckets must be greater than 0");
        int index = k % bucket;
        return index < 0 ? index + bucket : index;
    }


    public:

    HashTable(int n){
        if (bucket == 0) throw std::invalid_argument("The number of buckets must be greater than 0");
        bucket = n;
        table = std::vector<std::vector<int>>(n);
        Nelements = 0;
    }

    void insert(const int& key){
        int index = hashFunction(key);

        if(std::find(table[index].begin(), table[index].end(),key) == table[index].end()){
            table[index].insert(table[index].begin(), key);
            Nelements++;
        }
    }

    void removekey(const int& key){
        int index = hashFunction(key);

        auto it = std::find(table[index].begin(), table[index].end(),key);

        if (it != table[index].end()){
            table[index].erase(it);
            Nelements--;
            std::cout << "Key eliminated\n";
            return;
        }

        std::cout << "Key doesn't exist to be eliminated\n";
    }
    

    void findKey(const int& key){
        int index = hashFunction(key);

        auto it = std::find(table[index].begin(), table[index].end(),key);

        if (it != table[index].end()){
            std::cout << "Found\n";
            return;
        }

        std::cout << "Not Found\n";
    }

    ~HashTable() = default;
    
};