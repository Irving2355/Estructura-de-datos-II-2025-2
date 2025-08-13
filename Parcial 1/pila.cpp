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
};

int main(){

    return 0;
}