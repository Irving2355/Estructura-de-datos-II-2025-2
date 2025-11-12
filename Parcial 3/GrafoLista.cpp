#include <bits/stdc++.h>
using namespace std;

class GrafoLista{
    //matriz booleana
    vector<vector<size_t>> adj;

    bool esDirigido;

public:
    GrafoLista(size_t n, bool dirigido = true)
        : adj(n), esDirigido(dirigido){}
    
    size_t numVertices() const {return adj.size();}

    //agregar arista u -> v
    void agregarArista(size_t u, size_t v){
        //validaciones basicas evitar accesos invalidos
        if(u >= numVertices() || v >= numVertices()){
            return;
        }
        adj[u].push_back(v);
        if(!esDirigido) adj[v].push_back(u);
    }

    void eliminarArista(size_t u, size_t v){
        if(u >= numVertices() || v >= numVertices()){
            return;
        }
        auto &lu = adj[u];
        // 2,4,5,6,5 u=5
        // remove 2,4,6,?,?
        //erase 2,4,6
        lu.erase(remove(lu.begin(), lu.end(), v),lu.end()); 

        if(!esDirigido){
            auto &lv = adj[v];
            lv.erase(remove(lv.begin(),lv.end(),u),lv.end());
        }
    }

    bool existeArista(size_t u, size_t v){
        if(u >= numVertices() || v >= numVertices()){
            return false;
        }
        const auto &lu = adj[u];
        return find(lu.begin(),lu.end(),v) != lu.end();
    }

    void imprimir() const{
        cout << "Lista de adyacencia ("
             << (esDirigido? "dirigido" : "no dirigido")
             << ")\n";
        for(size_t i = 0; i< numVertices(); ++i){
            cout << i << ": [";
            for(size_t v : adj[i]) cout << v << " ";
            cout << "]"<< endl;
        }
    }

    //recorrido BFS desde una fuente
    vector<size_t> BFS(size_t s) const{
        vector<size_t> orden;
        if(s >= numVertices()) return orden;
        vector<bool> vis(numVertices(), false);
        queue<size_t> q;
        vis[s] = true; q.push(s);
        while(!q.empty()){
            size_t u = q.front(); q.pop();
            orden.push_back(u);
            for(size_t v : adj[u]){
                if(!vis[v]){ 
                    vis[v]= true;
                    q.push(v);
                }
            }
        }
        return orden;
    }

};

int main(){
    GrafoLista G(4, true);
    G.agregarArista(0,1);
    G.agregarArista(0,2);
    G.agregarArista(1,3);
    G.agregarArista(2,3);

    G.imprimir();

    auto orden = G.BFS(0);
    cout << "BFS desde 0: ";
    for(auto x: orden) cout << x << " ";
    cout << endl;
    return 0;
}