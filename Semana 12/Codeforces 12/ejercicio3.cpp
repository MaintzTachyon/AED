#include <iostream>
#include <vector>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    constexpr long long MOD = 1'000'000'007;

    int n, m;

    std::cin >> n >> m;

    std::vector<std::vector<int>> no(n + 1);

    for(int i = 1; i <= m; i++){
        int u, v;

        std::cin >> u >> v;

        no[u].push_back(v);
        no[v].push_back(u);
    }

    std::vector<int> teams(n + 1, 0);
    long long ways = 1;
    bool validator = true;

    for (int i = 1; i <= n; i++){
        if (teams[i] != 0) continue;

        ways = (ways * 2) % MOD;
        
        teams[i] = 1; 
        
        std::vector<int> q;
        q.push_back(i);
        std::size_t next = 0;

        while(next < q.size() && validator){
            int curr = q[next++];

            int currteam = teams[curr];
            int opositeteam = (currteam == 1) ? 2 : 1;

            for (int n : no[curr]){
                if(teams[n] == 0){
                    teams[n] = opositeteam;
                    q.push_back(n);
                }else if(teams[n] == currteam){
                    validator = false;
                    break;
                }
            }
        }
        if(!validator) break;
    }
    if(validator){
        std::cout << "SI " << ways << '\n';
    }else{
        std::cout << "NO\n";
    }

    return 0;
}