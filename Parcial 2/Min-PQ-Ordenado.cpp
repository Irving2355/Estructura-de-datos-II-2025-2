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

    //findMin el minimo logico esta en head
    Item2 findMin() const {
        if(isEmpty()) return Item2{-1,0};
        return a[head];
    }

    Item2 extraxtMin(){
        if(isEmpty()) return Item2{-1,0};
        Item2 ans = a[head++];
        //si head crecio mucho compactar
        if(head > 256 && head > (n/2)){
            const_cast<OrderMinPQ*>(this)->compact();
        }
        return ans;
    }

    void print()const{
        cout << "[";
        for(int i=head; i<n; ++i){
            cout << "(" << a[i].id << "," << a[i].key << ")";
            if(i+1<n) cout << ", ";
        }
        cout << "]\n";
    }
};

int main(){
    OrderMinPQ pq;
    pq.insert(1,5);
    pq.insert(4,2);
    pq.insert(3,9);
    pq.insert(2,2);
    pq.insert(5,7);

    cout << "tras inserciones: "; pq.print();

    Item2 m = pq.findMin();
    cout << "findMin -> (id= " << m.id << ", key= " << m.key <<")\n";

    Item2 e = pq.extraxtMin();
    cout << "extractMin -> (id= " << e.id << ", key= " << e.key <<")\n";

    cout << "estado final: "; pq.print();

    return 0;
}