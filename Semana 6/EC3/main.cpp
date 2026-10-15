#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>

//repo utilizado: https://github.com/MaintzTachyon/AED.git

class HashTable{
    std::vector<std::vector<std::pair<int,int>>> table;

    int bucket;
    int Nelements;

    int hashFunction(const int& k){
        if (bucket == 0) throw std::invalid_argument("The number of buckets must be greater than 0");
        int index = k % bucket;
        return index < 0 ? index + bucket : index;
    }


public:

    HashTable(int n): bucket(n), Nelements(0), table(n){
        if (n <= 0) throw std::invalid_argument("The number of buckets must be greater than 0");
    }

    void insert(const int& key) {
        int index = hashFunction(key);

        for (auto& element : table[index]) {
            if (element.first == key) {
                element.second++;
                return;
            }
        }
        table[index].push_back({key,1});
    }

    void frequencycount(const int& key){
        int index = hashFunction(key);

        for (const auto& element: table[index]){
            if (element.first == key && element.second > 1){
                std::cout << element.first << " ";
                return;
            }

        }
        return;
    }


    ~HashTable() = default;

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    HashTable hashTable(n);
    std::map<int, int> values;

    for (int i = 0; i < n; i++) {
        int key;
        std::cin >> key;
        hashTable.insert(key);
        values[key]++;
    }

    for (const auto& value : values) {
       hashTable.frequencycount(value.first);
    }


}