#include <bits/stdc++.h>

using namespace std;

class GrafoPonderado{
    /*adj guarda todas las aristas en pares
    (v,w) v nodo vecino
    w peso/costo de arista u -> v*/
    vector<vector<pair<size_t,int>>> adj;
    bool esDirigido;
public:

    GrafoPonderado(size_t n, bool dirigido = true)
        : adj(n), esDirigido(dirigido){}
    
    size_t numVertices() const {return adj.size();}

    void agregarArista(size_t u, size_t v, int w){
        //validaciones basicas evitar accesos invalidos
        if(u >= numVertices() || v >= numVertices()){
            return;
        }

        adj[u].push_back({v,w});
        if(!esDirigido){
            adj[v].push_back({u,w});
        }
    }

    void imprimir() const {
        cout << "Grafo ponderado ("
             << (esDirigido? "dirigido" : "no dirigido")
             << ")\n";
        for(size_t i = 0; i< numVertices(); ++i){
            cout << i << ": ";
            for(auto [v,w] : adj[i]){
                cout << "(" << v << ", w= " << w << ")";
            }
            cout << endl;
        }
    }

    void dijkstra(size_t s,
                  vector<int>& dist,
                  vector<int>& parent)
    {
        const int INF = 1e9;
        size_t n = numVertices();
        dist.assign(n,INF);
        parent.assign(n,-1);

        if(s >= n) return;

        dist[s] = 0;

        using P = pair<int,size_t>; //(int,size_t)
        priority_queue<P,vector<P>,greater<P>> pq;

        pq.push({0,s});

        while(!pq.empty()){
            auto [du,u] = pq.top();
            pq.pop();

            if(du != dist[u]) continue;

            for(auto [v,w]: adj[u]){
                if(dist[u] + w < dist[v]){
                    dist[v] = dist[u] + w;
                    parent[v] = (int)u;
                    pq.push({dist[v],v});
                }
            }
        }
    }
};

int main(){
    GrafoPonderado G(4,true);

    G.agregarArista(0,1,2);
    G.agregarArista(0,2,5);
    G.agregarArista(1,2,1);
    G.agregarArista(1,3,3);
    G.agregarArista(2,3,2);

    G.imprimir();

    size_t fuente = 0;
    vector<int> dist, parent;

    G.dijkstra(fuente,dist,parent);

    cout << "\nDistancia minima desde " << fuente << ":\n";
    for(size_t u = 0; u<G.numVertices(); ++u){
        if(dist[u] == 1e9)
            cout << u << ": Inf\n";
        else  
            cout << u << ": " <<dist[u] <<"\n";
    }

    //desde una fuente a un destino
    size_t destino = 3;
    if(destino >= G.numVertices() || dist[destino] == 1e9){
        cout << "\nNo hay camino\n";
    }else{
        vector<size_t> camino;
        
        for(int x=(int)destino; x!= -1; x=parent[x]){
            camino.push_back((size_t)x);
        }
        
        reverse(camino.begin(),camino.end());
        
        cout << "\nCamino minimo " << fuente << " -> " << destino
        << ": ";

        for(size_t i=0; i<camino.size(); ++i){
            cout << camino[i];
            if(i + 1 < camino.size()) cout << " -> ";
        }
        cout <<"\nCosto total: " << dist[destino] << "\n";
        
    }
    return 0;
}