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

    void eliminarArista(size_t u, size_t v){
        if(u >= numVertices() || v >= numVertices()){
            return;
        }
        A[u][v] = false;
        if(!esDirigido) A[v][u] = false;
    }

    bool existeArista(size_t u, size_t v){
        if(u >= numVertices() || v >= numVertices()){
            return false;
        }
        return A[u][v];
    }

    void imprimir() const{
        cout << "Matriz de adyacencia ("
             << (esDirigido? "dirigido" : "no dirigido")
             << ")\n";
        for(size_t i = 0; i< numVertices(); ++i){
            for(size_t j = 0; j< numVertices(); ++j){
                cout << (A[i][j]? 1 : 0) << " ";
            }
            cout << endl;
        }
    }
};

int main(){
    GrafoMatriz G(4, true);
    G.agregarArista(0,1);
    G.agregarArista(0,2);
    G.agregarArista(1,3);
    G.agregarArista(2,3);

    G.imprimir();

    cout << "Existe 0->2 ? " << (G.existeArista(0,2)? "si":"no");
    return 0;
}