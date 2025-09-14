#include <iostream>

using namespace std;

class Nodo{
    public:
        int dato;
        Nodo* sig;
        Nodo(int v){
            dato = v;
            sig = nullptr;
        }
};

class Lista{
    public:
        Nodo* cabeza;
        Lista(){
            cabeza = nullptr;
        }

        void insertarInico(int v){
            Nodo* nuevo = new Nodo(v);
            nuevo->sig = cabeza;
            cabeza = nuevo;
        }

        void eliminarInicio(){
            if(!cabeza) return;
            Nodo* tmp = cabeza;
            cabeza = cabeza->sig;
            delete tmp;
        }

        bool buscar(int v){
            Nodo* aux = cabeza;
            while (aux)
            {
                if(aux->dato == v){
                    return true;
                }
                aux = aux->sig; // aux++;
            }
            return false;
        }

        void mostrar(){
            Nodo* aux = cabeza;
            while (aux)
            {
                cout << aux->dato << " -> ";
                aux = aux->sig; // aux++;
            }
            cout << " NULL" << endl;
        }
};

int main(){
    Lista lista;
    lista.insertarInico(1);
    lista.insertarInico(2);
    lista.insertarInico(3);
    lista.mostrar();
    lista.eliminarInicio();
    lista.mostrar();
    bool buscar = lista.buscar(1);
    if(buscar){
        cout << "\nsi esta";
    }else{
        cout << "\nno esta";
    }
    return 0;
}