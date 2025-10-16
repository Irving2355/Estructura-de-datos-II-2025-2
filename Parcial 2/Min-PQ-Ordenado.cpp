#include <iostream>
using namespace std;

struct Item2 {int id; int key;};

class OrderMinPQ{
    //capacidad fija
    static const int CAP = 1024;

    //arreglo fisico donde almacenamos los elementos fila india
    Item2 a[CAP];

    //n: numero de elementos validos actualmente
    int n;

    //head: inicio logico 
    int head;

public:
    OrderMinPQ() : n(0), head(0) {}

    //consultas basicas de estado
    bool isEmpty() const { return head >= n;}
    bool isFull() const { return n >= CAP;}
    int size() const { return n-head;}

    void compact(){
        int sz = size();
        for(int i=0; i<sz; i++) a[i]=a[head+i];
        head = 0; n = sz;
    }

    /*insert 
    si hace falta compactar para tener espacio al frente
    desplazar a la derecha hasta ubicar "key"
    insertar en la posicion adecuada*/
    bool insert(int id, int key){
        if(isFull()) return false;
        if(head > 0 && n == CAP) compact(); //por si hay huecos
        
        //si hay espcaio frontal sin usar y se aproxima a CAP
        if(head > 0 && (n-head)>CAP/2 && n>CAP-8) compact();

        //insercion ordenada derecha a izquierda
        int i = n-1;
        while (i >= head && a[i].key > key){
            a[i+1] = a[i];
            --i;
        }

        a[i+1] = {id,key};
        ++n;
        return true;
    }

};

int main(){
    return 0;
}