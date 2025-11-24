#include <bits/stdc++.h>

using namespace std;

struct DFSTools
{
    const vector<vector<int>>& adj;
    bool dirigido;
    vector<int> color;
    vector<int> tin, tout, parent;
    int timer = 0;
    bool hayCiclo = false;

    DFSTools(const vector<vector<int>>& g, bool dir)
        : adj(g), dirigido(dir), color(g.size(),-1),
        parent(g.size(),-1), tin(g.size(),-1),
        tout(g.size(),-1) {}
    
    void dfs_visit(int u){
        color[u] = 1;     //gris 
        tin[u] = timer++; //tiempo de entrada

        for(int v: adj[u]){
            if(color[v] == 0){
                parent[v] = u;
                dfs_visit(v);
            }else if(color[v] == 1){
                if(dirigido || v != parent[u]) 
                    hayCiclo = true;
            }
        }

        tout[u] = timer++; //tiempo de salida
        color[u] = 2; //negro
    }

    void run_all(){
        for(size_t u=0; u<adj.size(); ++u)
            if(color[u] == 0) dfs_visit((int)u);
    }
    
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, d; //n vertices, m aristas, d dirigido

    cin >> n >> m >> d;
    vector<vector<int>> adj(n);

    auto addEdge = [&](int u, int v){
        adj[u].push_back(v);
        if(!d) adj[v].push_back(u);
    };

    for(int i=0;i<m;++i){
        int u,v;
        cin>>u>>v;
        addEdge(u,v);
    }

    DFSTools dfs(adj, d==1);
    dfs.run_all();

    cout << "tin: "; for(int x:dfs.tin) cout << x << " ";
    cout << endl;

    cout << "tout: "; for(int x:dfs.tout) cout << x << " ";
    cout << endl;

    cout << "Ciclo? " << (dfs.hayCiclo?"si":"no") << "\n";

    return 0;
}

/*Version mas sencilla 

#include <bits/stdc++.h>
using namespace std;

class GrafoLista{
    vector<vector<size_t>> adj;
    bool esDirigido;

public:
    GrafoLista(size_t n, bool dirigido = true)
        : adj(n), esDirigido(dirigido) {}

    size_t numVertices() const { return adj.size(); }

    // Agregar arista u -> v
    void agregarArista(size_t u, size_t v) {
        if (u >= numVertices() || v >= numVertices()) return;
        adj[u].push_back(v);
        if (!esDirigido) adj[v].push_back(u);
    }

    void imprimir() const {
        cout << "Lista de adyacencia ("
             << (esDirigido ? "dirigido" : "no dirigido")
             << ")\n";
        for (size_t i = 0; i < numVertices(); ++i) {
            cout << i << ": [";
            for (size_t v : adj[i]) cout << v << " ";
            cout << "]\n";
        }
    }

    // **** DFS sencillo *****

    void dfsRec(size_t u,
                vector<bool>& visitado,
                vector<bool>& enRecursion,
                vector<size_t>& orden,
                bool& hayCiclo,
                size_t padre)
    {
        visitado[u] = true;
        enRecursion[u] = true;   // "gris"
        orden.push_back(u);

        for (size_t v : adj[u]) {
            if (!visitado[v]) {
                dfsRec(v, visitado, enRecursion, orden, hayCiclo, u);
            } else {
                // Si ya estaba en la pila de recursion,
                // encontramos un ciclo.
                if (enRecursion[v]) {
                    // En no dirigido ignoramos la arista al padre
                    if (esDirigido || v != padre) {
                        hayCiclo = true;
                    }
                }
            }
        }

        enRecursion[u] = false;  // salir del "gris"
    }

    // Recorre todo el grafo con DFS (por si es no conexo)
    vector<size_t> DFS(bool& hayCiclo) {
        vector<size_t> orden;
        size_t n = numVertices();

        vector<bool> visitado(n, false);
        vector<bool> enRecursion(n, false);
        hayCiclo = false;

        for (size_t u = 0; u < n; ++u) {
            if (!visitado[u]) {
                dfsRec(u, visitado, enRecursion, orden, hayCiclo, (size_t)-1);
            }
        }
        return orden;
    }
};

int main() {
    // Ejemplo pequeño
    GrafoLista G(4, true); // dirigido
    G.agregarArista(0, 1);
    G.agregarArista(0, 2);
    G.agregarArista(1, 3);
    G.agregarArista(2, 3);

    G.imprimir();

    bool hayCiclo = false;
    auto orden = G.DFS(hayCiclo);

    cout << "DFS (orden de visita): ";
    for (auto x : orden) cout << x << " ";
    cout << "\n";

    cout << "Hay ciclo? " << (hayCiclo ? "si" : "no") << "\n";

    return 0;
}
*/