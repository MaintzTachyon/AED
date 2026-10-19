#include <iostream>
#include <algorithm>

using namespace std;

int v[10000];

void backtraking(int rest, int max, int size){
    if (rest == 0){
        for (int i = 0; i< size; i++){
            if (i > 0)cout << " ";
            cout << v[i];
        }
        cout << "\n";
        return;
    }

    for (int i = min(rest,max); i >= 1; i--){
        v[size] = i;
        backtraking(rest - i, i ,size + 1);
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    cin >> n;

    backtraking(n,n,0);
}