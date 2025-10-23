#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 20; //tamaño del heap

class MinHeap{
    int data[MAX];
    int size;

    //corrige hacia arriba
    void siftUp(int i){
        /*Mientras no estemos en la raiz y el hijo sea menor
        que su padre*/
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if(data[i] >= data[parent]) break; //propiedad cumplida
            swap(data[i], data[parent]);
            i = parent; //seguimos subiendo
        }
    }

    void siftDown(int i){
        while (true)
        {
            int left = 2*i + 1;
            int right = 2*i + 2;
            int smallest = i;

            if(left < size && data[left] < data[smallest])
                smallest = left;
            if(right < size && data[right] < data[smallest])
                smallest = right;
            
            if(smallest == i) break;

            swap(data[i],data[smallest]);
            i=smallest;
        }
        
    }

public:
    MinHeap() : size(0){}
    
    //insertar al final sin asegurar la proridad
    void insertRaw(int value){
        if(size == MAX){
            cout << "Heap lleno\n";
            return;
        }
        data[size] = value;
        siftUp(size);
        size++;
    }

    void printArray() const{
        cout << "Heap (en arreglo)";
        for(int i=0; i<size; ++i){
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main(){
    MinHeap h;
    h.insertRaw(20);
    h.insertRaw(15);
    h.insertRaw(30);
    h.insertRaw(10);
    h.insertRaw(5);
    h.printArray(); //el menor queda en la raiz
    return 0;
}
