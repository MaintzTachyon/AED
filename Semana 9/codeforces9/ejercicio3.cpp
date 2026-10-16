#include <iostream>
#include <vector>
#include <string>

void crearVector(std::vector<int>& n, const int& i){
    n[0] = 0;
    for(int j = 1; j < i +1; j++){
        n[j] = j;
    }
}

void rotacionIzquierda(
    std::vector<std::pair<int,int>>& n,
    std::vector<int>& parent,
    int& root,
    const int& op){
    
    // El hijo derecho de op subirá y será la nueva raíz del subárbol que estamos rotando.
    int child = n[op].second;

    // Guardamos el padre original de op.
    int parentOp = parent[op];

    // Este subárbol se moverá al hijo derecho de op. 
    int mid = n[child].first;

    // El subárbol intermedio pasa a ser hijo derecho de op.
    n[op].second = mid;
    
    // Si mid existe, su nuevo padre ahora es op.
    if (mid != 0){
        parent[mid] = op;
    }
    // op pasa a ser hijo izquierdo de child.   
    n[child].first = op;
    // Actualizamos los padres de op y child.
    parent[op] = child;
    parent[child] = parentOp;

    // Si op era la raíz, child se convierte en la nueva raíz.
    if (parentOp == 0){
        root = child;
    }// Si op era hijo izquierdo de su padre,child ocupa ahora esa posición.
    else if(n[parentOp].first == op){
        n[parentOp].first = child;
    }// Si op era hijo derecho, child ocupa esa posición.
    else {
        n[parentOp].second = child;
    }

}   

void rotacionDerecha(
    std::vector<std::pair<int, int>>& n,
    std::vector<int>& parent,
    int& root,
    const int& op
) {
    // El hijo izquierdo de op subirá.
    int child = n[op].first;

    // Guardamos el padre original de op.
    int parentOp = parent[op];

    // Este subárbol se moverá al hijo izquierdo de op.
    int mid = n[child].second;

    // El subárbol intermedio pasa a ser hijo izquierdo de op.
    n[op].first = mid;

    // Actualizamos el padre de mid.
    if (mid != 0) {
        parent[mid] = op;
    }

    // op pasa a ser hijo derecho de child.
    n[child].second = op;

    // Actualizamos los padres.
    parent[op] = child;
    parent[child] = parentOp;

    // Si op era la raíz, child se convierte en la nueva raíz.
    if (parentOp == 0) {
        root = child;
    }
    // Si op era hijo izquierdo, child ocupa esa posición.
    else if (n[parentOp].first == op) {
        n[parentOp].first = child;
    }
    // Si op era hijo derecho, child ocupa esa posición.
    else {
        n[parentOp].second = child;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int Nnodos, ops;

    std::cin >> Nnodos;
    std::cin >> ops;

    std::vector<int> vecnodo(Nnodos + 1);
    std::vector<std::pair<int,int>> childs(Nnodos + 1);
    std::vector<int> parent(Nnodos + 1, 0);
    
    int root = 1;
    childs[0] = {0,0};
    crearVector(vecnodo, Nnodos);

    for (int i = 1; i < Nnodos + 1; i++){
        int L, R;

        std::cin >> L;
        std::cin >> R;
        
        childs[i] = {L,R};

        if(L != 0){
            parent[L] = i;
        }

        if (R != 0){
            parent[R] = i;
        }
    }

    for (int i = 0; i < ops; i++){
        std::string Rop;
        int op;

        std::cin >> Rop;
        std::cin >> op;

        if (Rop == "I"){
            rotacionIzquierda(childs, parent,root, op);
        }
        if (Rop == "D"){
            rotacionDerecha(childs, parent,root, op);
        }
    }
}