#include <iostream>
#include <map>
#include <algorithm>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n,m;

    std::cin >> n >> m;
    std::map<int, int> followers;
    std::map<std::pair<int,int>, int> pairs;
    
    for (int value = 1; value <= n; value++) {
        followers[value] = 0;
    }

    for (int i = 0; i < m; i++){
        
        int c1, c2;

        std::cin >> c1 >> c2;
        followers[c2]++;
        if(c1 > c2)std::swap(c1,c2);

        pairs[{c1,c2}] ++;
    }

    int mostFollowed = 0;
    int maxFollowers = -1;
    for (const auto& [value, count] : followers) {
        if (count > maxFollowers) {
            mostFollowed = value;
            maxFollowers = count;
        }
    }

    int numberOfPairs = 0;
    for (const auto& [pair, count] : pairs) {
        if (count == 2) {
            numberOfPairs++;
        }
    }

    std::cout << numberOfPairs << ' '<< mostFollowed << ' '<< maxFollowers;

    return 0;
}