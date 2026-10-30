#include <iostream>
#include <deque>
#include <limits>
#include <vector>


int minroad(const std::vector<std::vector<int>>& matrix, int startX, int startY,int endX, int endY) {
    const int n = static_cast<int>(matrix.size());
    const int m = static_cast<int>(matrix[0].size());
    const int infinity = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> walls(n, std::vector<int>(m, infinity));
    std::deque<std::pair<int, int>> coords;

    walls[startX][startY] = matrix[startX][startY] == -2 ? 1 : 0;
    coords.push_front({startX, startY});

    int dx[] = {-1,1,0,0};
    int dy[] = {0,0,-1,1};

    while(!coords.empty()){
        auto [currX, currY] = coords.front();
        coords.pop_front();

        for(int i = 0; i < 4; i++){
            int nextX = currX + dx[i];
            int nextY = currY + dy[i];

            if(nextX < 0 || nextX >= n || nextY < 0 || nextY >= m){
                continue;
            }

            const int cost = matrix[nextX][nextY] == -2 ? 1 : 0;
            const int newWalls = walls[currX][currY] + cost;

            if(newWalls >= walls[nextX][nextY]){
                continue;
            }

            walls[nextX][nextY] = newWalls;
            if(cost == 0){
                coords.push_front({nextX, nextY});
            }else{
                coords.push_back({nextX, nextY});
            }
        }
    }

    return walls[endX][endY] == infinity ? -1 : walls[endX][endY];
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n,m;
    
    std::cin >> n >> m;

    std::vector<std::vector<int>> matrix(n,std::vector<int>(m,-1));

    int startX = 0, startY = 0, endX = n - 1, endY = m - 1;
    char c;
    for(int i = 0; i < n; i++){
        for (int j = 0; j < m ;j++){
            std::cin >> c;
            if(c == '#'){
                matrix[i][j] = -2;
            }
        }
    }

    std::cout << minroad(matrix, startX, startY, endX, endY) << '\n';

    return 0;
}