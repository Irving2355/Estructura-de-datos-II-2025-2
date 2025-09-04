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

    
};

int main(){
    return 0;
}