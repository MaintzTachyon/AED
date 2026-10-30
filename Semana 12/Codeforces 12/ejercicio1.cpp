#include <iostream>
#include <vector>
#include <queue>


int minroad(std::vector<std::vector<int>>& v, int startX, int startY,int endX, int endY, int m, int n){
    std::queue<std::pair<int,int>> coords;
    coords.push({startX,startY});

    int dx[] = {-1,1,0,0};
    int dy[] = {0,0,-1,1};

    while(!coords.empty()){
        auto [currX, currY] = coords.front();
        coords.pop();

        for(int i = 0; i < 4; i++){
            int nextX = currX + dx[i];
            int nextY = currY + dy[i];

            if(nextX < 0 || nextX >= n || nextY < 0 || nextY >= m){
                continue;
            }

            if(nextX == endX && nextY == endY){
                return v[currX][currY] + 1;
            }

            if(v[nextX][nextY] != -1){
                continue;
            }

            v[nextX][nextY] = v[currX][currY] + 1;
            coords.push({nextX, nextY});
        }
    }

    return -1;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n,m;
    
    std::cin >> n >> m;

    std::vector<std::vector<int>> matrix(n,std::vector<int>(m,-1));

    int startX, startY, endX, endY;
    char c;
    for(int i = 0; i < n; i++){
        for (int j = 0; j < m ;j++){
            std::cin >> c;
            if(c == 'S'){
                matrix[i][j] = 0;
                startX = i;
                startY = j;
            }else if(c == '#'){
                matrix[i][j] = -2;
            }else if(c == 'E'){
                endX = i;
                endY = j;
            }
        }
    }

    std::cout << minroad(matrix, startX, startY, endX, endY, m, n) << '\n';

    return 0;
}