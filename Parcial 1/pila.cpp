#include <iostream>

using namespace std;

class Pila{
    public:
        int datos[5];
        int tope;

        Pila(){tope = -1; }

        bool isEmpty(){return tope == -1;}
        bool isFull(){return tope == 4; }

        void push(int v){
            if(isFull()) 
                cout << "Pila llena" << endl;
            else 
                datos[++tope] = v;
        }

        void pop(){
            if(isEmpty())
                cout << "pila vacia" << endl;
            else
                tope--;
        }

        void mostrar(){
            for(int i=tope; i>=0; --i){
                cout << datos[i] << " ";
            }
        }
};

int main(){
    Pila pila;

    pila.push(1);
    pila.push(2);
    pila.push(3);
    pila.push(4);
    pila.push(5);
    pila.mostrar();
    pila.pop();
    cout << endl;
    pila.mostrar();
    pila.push(6);
    pila.push(7);
    cout << endl;
    pila.mostrar();

    return 0;
}