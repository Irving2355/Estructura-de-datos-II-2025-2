#include <bits/stdc++.h>

using namespace std;

class GrafoMatriz{
    //matriz booleana
    vector<vector<bool>> A;
    bool esDirigido;
public:
    GrafoMatriz(size_t n, bool dirigido = true)
        : A(n,vector<bool>(n,false)), esDirigido(dirigido){}

    size_t numVertices() const {return A.size();}

    //agregar arista u -> v
    void agregarArista(size_t u, size_t v){
        //validaciones basicas evitar accesos invalidos
        if(u >= numVertices() || v >= numVertices()){
            return;
        }
        A[u][v] = true;
        if(!esDirigido) A[v][u] = true;
    }
};

int main(){
    return 0;
}