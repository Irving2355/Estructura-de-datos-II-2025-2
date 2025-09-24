#include <iostream>

using namespace std;

struct Nodo{
    int dato;
    Nodo* izq;
    Nodo* der;
    explicit Nodo(int v): dato(v),izq(nullptr),der(nullptr){}
};

class ABB{
public:
    ABB() : raiz(nullptr){}
    ~ABB() {liberar(raiz);}

    void insertar(int v){ raiz = insertarRec(raiz, v);}

    void preorden() const{preordenRec(raiz); cout<<"\n";}
    void postorden() const{postordenRec(raiz); cout<<"\n";}
    void inorden() const{inordenRec(raiz); cout<<"\n";}

    void limpiar(){ liberar(raiz); raiz = nullptr;}
private:
    Nodo* raiz;

    static Nodo* insertarRec(Nodo* nodo, int v){
        if(nodo == nullptr) return new Nodo(v);
        if(v < nodo->dato) nodo->izq = insertarRec(nodo->izq,v);
        else nodo->der = insertarRec(nodo->der,v);
    }

    static void preordenRec(Nodo* nodo){
        if(!nodo) return;
        cout << nodo->dato << ' '; // raiz
        preordenRec(nodo->izq);  //izq
        preordenRec(nodo->der); //der
    }

    static void postordenRec(Nodo* nodo){
        if(!nodo) return;
        preordenRec(nodo->izq);  //izq
        preordenRec(nodo->der); //der
        cout << nodo->dato << ' '; // raiz
    }

    static void inordenRec(Nodo* nodo){
        if(!nodo) return;
        preordenRec(nodo->izq);  //izq
        cout << nodo->dato << ' '; // raiz
        preordenRec(nodo->der); //der
    }
    
    static void liberar(Nodo* nodo){
        if(!nodo) return;
        liberar(nodo->izq);
        liberar(nodo->der);
        delete nodo;
    }
};



int main(){
    return 0;
}