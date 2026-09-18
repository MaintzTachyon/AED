#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

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

    HashTable(int n):bucket(n), Nelements(0), table(n){
        if (n <= 0) {
            throw std::invalid_argument("The number of buckets must be greater than 0");
        }
    }

    void insert(const int& key){
        int index = hashFunction(key);

        for (auto& element: table[index]){
            if (element.first == key){
                element.second++;
                return;
            }
        }

        table[index].push_back({key,1});
        Nelements++;
    }

    void removekey(const int& key){
        int index = hashFunction(key);

        for (auto it = table[index].begin(); it != table[index].end(); it++){
            if(it->first == key){
                table[index].erase(it);
                Nelements--;
                std::cout << "Key eliminated\n";
                return;
            }
        }

        std::cout << "Key doesn't exist to be eliminated\n";
    }
    

    void findKey(const int& key){
        int index = hashFunction(key);

        for (const auto& element : table[index]){
            if (element.first == key){
                std::cout << "Element found\n";
                return;
            }
        }

        std::cout << "Not Found\n";
    }


    void frequencycount(const int& key){
        int index = hashFunction(key);

        for (const auto& element: table[index]){
            if (element.first == key){
                std::cout << element.second << '\n';
                return;
            }

        }

        std::cout << "0\n";
        
    }

    ~HashTable() = default;
    
};


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n , q;

    std::cin >> n;
    std::cin >> q;

    HashTable table(n);

    for (int i = 0; i < n; i++){
        int val;
        std::cin >> val;
        table.insert(val);
    }

    for (int i = 0 ; i < q; i++){
        int valS;
        std::cin >> valS;
        table.frequencycount(valS);
    }

    return 0;
}