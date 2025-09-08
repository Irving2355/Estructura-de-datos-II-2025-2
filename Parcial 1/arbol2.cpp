#include <iostream>
#include <string>

using namespace std;

class NodoFS{
private:
    static const int K = 6;
    string nombre;
    bool esDirectorio;
    size_t tam;
    NodoFS* hijos[K];
    int nHijos;

    NodoFS(const string& n,bool dir, size_t t)
        : nombre(n), esDirectorio(dir), tam(t), nHijos(0){
            for(int i=0; i<K; ++i) hijos[i] = nullptr;
        }

public:
    //cosntructores estaticos
    static NodoFS* directorio(const string& n){
        return new NodoFS(n,true,0);
    }

    static NodoFS* archivos(const string& n,size_t bytes){
        return new NodoFS(n,false,bytes);
    }

    NodoFS(const NodoFS&) = delete;
    NodoFS& operator=(const NodoFS&) = delete;

    //destructor
    ~NodoFS(){
        for(int i=0; i<nHijos; ++i) delete hijos[i];
    }

    //agregar hijos si es directorio
    bool agregar(NodoFS* h){
        if(!esDirectorio || nHijos>=K) return false;
        hijos[nHijos++] = h;
        return true;
    }

    //calcular tamaño total acumulado
    size_t tamanoTotal() const{
        if(!esDirectorio) return tam;
        size_t total = 0;
        for(int i=0; i<nHijos; ++i){
            total += hijos[i]->tamanoTotal();
        }
        return total;
    }

    //listar rutas absolutas
    void listarRutas(const string& prefijo = "") const{
        string ruta = prefijo + "/" + nombre;
        if(!esDirectorio){
            cout << ruta << " (" << tam << ") bytes\n";
            return;
        }
        for(int i=0; i<nHijos; ++i){
            hijos[i]->listarRutas();
        }
    }

    //imprimir el arbol en postorden
    void imprimirPostorden(int nivel = 0)const{
        //primero recorrer hijos
        for(int i=0; i<nHijos; ++i){
            hijos[i]->imprimirPostorden(nivel + 1);
        }

        //luego visitar el nodo actual
        cout << string(nivel * 2, ' ') << "- " << nombre;
        if(!esDirectorio) cout << " (" << tam << ") bytes";
        cout << "\n";
    }
};

int main(){
    NodoFS* root = NodoFS::directorio("C:");
    NodoFS* home = NodoFS::directorio("home");
    NodoFS* user = NodoFS::directorio("user");
    NodoFS* docs = NodoFS::directorio("docs");
    NodoFS* img = NodoFS::directorio("img");

    NodoFS* tareaPdf = NodoFS::archivos("tarea.pdf", 12000);
    NodoFS* notasTxt = NodoFS::archivos("notas.txt", 1000);
    NodoFS* fotoPng = NodoFS::archivos("foto.png", 4500000);

    NodoFS* etc = NodoFS::directorio("etc");
    NodoFS* conf = NodoFS::archivos("config,sys", 2000);

    root->agregar(home);
    root->agregar(etc);

    home->agregar(user);
    user->agregar(docs);
    user->agregar(img);

    cout << "Postorden\n";
    root->imprimirPostorden();
    return 0;
}