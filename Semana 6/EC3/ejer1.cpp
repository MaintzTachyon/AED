#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>

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

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nV;
    std::cin >> nV;

    HashTable table(nV);

    for(int i = 0; i < nV; i++){
        int val;
        std::cin >> val;
        table.insert(val);
    }

    int Ncommands;
    std::cin>>Ncommands;

    for(int i = 0; i < Ncommands; i++){
        std::string command;
        int val;
        std::cin >> command;
        std::cin >> val;
        if(command == "Insert"){
            table.insert(val);
        }else if(command == "Remove"){
            table.removekey(val);
        }else if(command == "Search"){
            table.findKey(val);
        }
    }
    

    return 0;
}