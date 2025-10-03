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
    
    bool buscar(int v)const{return buscarRec(raiz, v);}
    void eliminar(int v){raiz = eliminarRec(raiz, v);}

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

    static bool buscarRec(Nodo* nodo, int v){
        if(nodo == nullptr) return false;
        if(v == nodo->dato) return true;
        if(v < nodo->dato) return buscarRec(nodo->izq,v);
        else return buscarRec(nodo->der,v);
    }

    static Nodo* minNodo(Nodo* nodo){
        while (nodo && nodo->izq)
        {
            nodo = nodo->izq;
        }
        return nodo;
    }

    static Nodo* eliminarRec(Nodo* nodo,int v){
        if(nodo == nullptr) return nullptr;

        if(v < nodo->dato){
            nodo->izq = eliminarRec(nodo->izq,v);
        }else if(v > nodo->dato){
            nodo->der = eliminarRec(nodo->der,v);
        }else{
            // 3 casos
            //caso 1 sin hijos
            if(nodo->izq == nullptr && nodo->der == nullptr){
                delete nodo;
                return nullptr;
            }
            //caso 2 un hijo
            else if(nodo->izq == nullptr){
                Nodo* tmp = nodo->der;
                delete nodo;
                return tmp;
            }
            else if(nodo->der == nullptr){
                Nodo* tmp = nodo->izq;
                delete nodo;
                return tmp;
            }
            //caso 3 tiene 2 hijos
            else{
                Nodo* sucesor = minNodo(nodo->der);
                nodo->dato = sucesor->dato;
                nodo->der = eliminarRec(nodo->der,sucesor->dato);
            }
        }
    }
};



int main(){
    ABB t;
    int datos[] = {45,20,60,10,30,50,70,25};
    for(int v : datos) t.insertar(v);

    cout << "Inorden: "; t.inorden();
    cout << "Preorden: "; t.preorden();
    cout << "Postorden: "; t.postorden();

    cout << "Buscar 30: " << (t.buscar(30)? "SI" : "NO") << endl;

    t.eliminar(10);
    cout << "Inorden: "; t.inorden();

    return 0;
}