#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

template<typename T>

class Grafo{
    bool dirigido;
    std::unordered_map<T, std::unordered_set<T>>lista_adyacencia;
    public:
    Grafo(bool d):dirigido(d) {}

    void insertar(const T& origen,const T& destino){

        lista_adyacencia[origen];
        lista_adyacencia[destino];

        lista_adyacencia[origen].insert(destino);

        if(!dirigido){
            lista_adyacencia[destino].insert(origen);
        }
    }

    bool eliminar(const T& origen, const T& destino){
        auto origenE = lista_adyacencia.find(origen);

        if (origenE == lista_adyacencia.end()){
            return false;
        }

        std::size_t conexionesEliminadas = origenE->second.erase(destino);

        if (conexionesEliminadas == 0){
            return false;
        }

        if (!dirigido){
            auto destinoEncontrado = lista_adyacencia.find(destino);

            if (destinoEncontrado != lista_adyacencia.end()){
                destinoEncontrado->second.erase(origen);
            }
        }
        return true;
         
    }

};