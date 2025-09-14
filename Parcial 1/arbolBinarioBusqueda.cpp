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
private:
    Nodo* raiz;
    
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