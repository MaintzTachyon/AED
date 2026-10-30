#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::vector<int>>adj(n+1);
    for (int i = 0; i < m ; i++){
        int a,b;
        std::cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    std::vector<bool> validator(n+1, false);

    while(q--){
        int u,v;
        std::cin >> u >> v;

        for (int x: adj[u]){
            validator[x] = true;
        }

        int commonfriends = 0;

        for (int x :adj[v]){
            if (validator[x]){
                commonfriends++;
            }
        }

        for(int x: adj[u]){
            validator[x] = false;
        }

        std::cout << commonfriends << "\n";
    }

    return 0;
}