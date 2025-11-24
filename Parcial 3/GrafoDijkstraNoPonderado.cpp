#include <bits/stdc++.h>

using namespace std;

/*Grafo no ponderado*/

class GrafoLista{
    vector<vector<size_t>> adj; //lista de adyacencia
    bool esDirigido;

public:
    GrafoLista(size_t n,bool dirigido = false)
        : adj(n), esDirigido(dirigido){}
    
    size_t numVertices() const {return adj.size();}

    void agregarArista(size_t u, size_t v){
        //validaciones basicas evitar accesos invalidos
        if(u >= numVertices() || v >= numVertices()){
            return;
        }
        adj[u].push_back(v);
        if(!esDirigido) adj[v].push_back(u);
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

    void dijkstra(size_t s,
                 vector<int>& dist,
                 vector<int>& parent) const
    {
        size_t n = numVertices();
        const int INF = 1e9; //numero grande como infinito

        //iniciamos distancias y padres
        dist.assign(n,INF); //al inicio nadie es alcanzado
        parent.assign(n,-1); //-1 sin padre

        if(s >= n) return; //si la fuente es invalida

        dist[s] = 0; //distancia de fuente a s es igual

        //priority queue de pares (distancia,nodo)
        using P = pair<int,size_t>;
        //usamos el greater para que sea min-heap
        priority_queue<P,vector<P>,greater<P>> pq;

        pq.push({0,s}); //insertamos fuente con distancia 0

        while (!pq.empty())
        {
            auto [du, u] = pq.top();
            pq.pop();

            if(du != dist[u]) continue;

            for(size_t v : adj[u]){
                if(dist[u] + 1 < dist[v]){
                    dist[v] = dist[u] + 1; //nueva mejor distancia

                    parent[v] = (int)u; //el mejor camino

                    pq.push({dist[v],v});
                    //metemos la nueva distancia a la cola
                }
            }
        }
    }

};

int main(){
    GrafoLista G(5,false);
    G.agregarArista(0,1);
    G.agregarArista(1,2);
    G.agregarArista(0,3);
    G.agregarArista(1,4);
    G.agregarArista(3,4);

    G.imprimir();

    size_t fuente = 0; //vertice desde el cual calculamos distnacias
    vector<int> dist, parent;

    G.dijkstra(fuente,dist,parent);

    cout << "\nDistancia minima desde " << fuente << ":\n";
    for(size_t u = 0; u<G.numVertices(); ++u){
        if(dist[u] == 1e9)
            cout << u << ": Inf\n";
        else  
            cout << u << ": " <<dist[u] <<"\n";
    }

    return 0;
}