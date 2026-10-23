#include <iostream>
#include <map>
#include <algorithm>

int main(){

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n,m,q;

    std::cin >> n >> m >> q;

    std::map<std::pair<int,int>, int> cables;

    for (int i = 0; i < m ; i++){
        int mi, mi2;
        std::cin >> mi >> mi2;

        if (mi > mi2) std::swap(mi,mi2);

        cables[{mi, mi2}]++;
    }

    for (int i = 0; i < q; i++){
        int qi, qi2;
        std::cin >> qi >> qi2;

        if (qi > qi2) std::swap(qi,qi2);
        auto it = cables.find({qi,qi2});
        if (it != cables.end()){
            std::cout << it->second << "\n";
        }else {
            std::cout << 0 << "\n";
        }
    }
    return 0;
}