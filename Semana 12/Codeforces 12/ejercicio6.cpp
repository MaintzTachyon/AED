#include <iostream>
#include <vector>

int solve(std::vector<std::vector<int>>& v, int& c, int n, int m){
    if (c == 0){
        return 0;
    }
    
    int nlamps = n*m;
    int minp = nlamps + 1;

    for (int combinations = 0; combinations <(1 << nlamps);combinations++ ){
        std::vector<std::vector<int>>copy = v;
        int pnow = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){

                int index = i * m + j;

                if ((combinations & (1 << index))!= 0){
                    pnow++;
                    copy[i][j] = 1 - copy[i][j];

                    if (i > 0){
                        copy[i - 1][j] = 1 - copy[i - 1][j];
                    }
                    if (i + 1 < n){
                        copy[i + 1][j] = 1 - copy[i + 1][j];
                    }
                    if (j > 0){
                        copy[i][j - 1] = 1 - copy[i][j - 1];
                    }
                    if (j + 1 < m){
                        copy[i][j + 1] = 1 - copy[i][j + 1];
                    }
                }
            }
        }

        bool apagadas = true;

        for (int i = 0 ; i < n; i++){
            for (int j = 0; j < m; j++){
                if (copy[i][j] == 1){
                    apagadas = false;
                }
            }
        }
        if (apagadas && pnow < minp){
            minp = pnow;
        }
    }


    if (minp == nlamps + 1){
        return -1;
    }
    return minp;
}


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n,m;

    std::cin>> n >> m;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(m,0));

    char val;
    int count = 0;
    for(int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            std::cin>> val;
            if (val == '1'){
                matrix[i][j] = 1;
                count ++;
            }
        }
    }

    std::cout << solve(matrix, count, n,m);
    return 0;
}