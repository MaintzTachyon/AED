#include <iostream>

void height(const long long& n){
    if (n == 0) {
        std::cout << "0 0\n";
        return;
    }

    long long minH = 0;
    long long a = 1;

    while (a * 2 <= n) {
        a *= 2;
        minH++;
    }

    a = 0;
    long long b = 1;
    long long maxH = 0;
    long long next = 0;

    while (1 + a + b <= n) {
        next = 1 + a + b;

        maxH++;
        a = b;
        b = next;
    }

    std::cout << minH << " " << maxH << '\n';
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++){
        long long Nnodes;

        std::cin >> Nnodes;

        height(Nnodes);
    }

    return 0;
}