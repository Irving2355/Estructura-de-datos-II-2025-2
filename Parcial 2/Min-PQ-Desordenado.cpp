#include <iostream>
using namespace std;

/*Representar un elemento en la cola de prioridad
id: para identificar 
key: la prioridad (menor = m surgente)*/

struct Item{
    int id;
    int key;
};

class UnorderMinPQ{
    //capacidad fija
    static const int CAP = 1024;

    //arreglo fisico donde almacenamos los elementos fila india
    Item a[CAP];

    //n: numero de elementos validos actualmente
    int n;

public:
    UnorderMinPQ(): n(0){}

    //consultas basicas de estado
    bool isEmpty() const { return n == 0;}
    bool isFull() const { return n == CAP;}
    int size() const { return n;}

    //INSERT(O(1)):
    /*colcoar el nuevo elemento al final sin ordenar*/
    bool insert(int id, int key){
        if(isFull()) return false;
        a[n++] = {id, key};
        return true;
    }

    /*findMinIdex O(n):
    recorrer todo el arreglo para ubicar el menor*/
    int findMinIndex() const{
        if(isEmpty()) return -1;
        int imin = 0;
        for(int i = 1; i<n; ++i){
            if(a[i].key < a[imin].key){
                imin = i;
            }
        }
        return imin; // retornamos position
    }

    //findMin elemento minimo sin sacarlo
    Item findMin() const{
        int i = findMinIndex();
        return (i >= 0) ? a[i] : Item{-1,0};
    }

    //extractMin
    Item extractMin(){
        int i = findMinIndex();
        if(i < 0) return Item{-1,0};
        Item ans = a[i];

        a[i] = a[n-1]; //compactamos rellenando el hueco
        --n; // decimos que hay un elemento menos
        return ans;
    }


};

int main(){
    return 0;
}