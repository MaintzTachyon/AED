#include <iostream>
#include <vector> 
#include <queue>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n,m,k;
    std::cin>> n >> m >> k;

    std::vector<int> dist(n+1,-1);

    std::queue<int> q;


    for(int i = 0; i < k; i++){
        int hospital;
        std::cin >> hospital;
        dist[hospital] = 0;
        q.push(hospital);

    }

    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 0 ; i < m; i++){
        int u, v;

        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    while(!q.empty()){
        int curr = q.front(); q.pop();

        for (int v : adj[curr]){
            if (dist[v] == -1){
                dist[v] = dist[curr] + 1;
                q.push(v);
            }
        }

    }

    for (int i = 1; i <= n; i++){
        std::cout << dist[i] << (i == n ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}