#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 20; // tamaño de heap

class MinHeap{
    int data[MAX];
    int size;

    void siftUp(int i){
        cout << "siftUp desde i= " << i << endl;
        while (i > 0)
        {
            int parent = (i - 1)/ 2;
            cout << " comparar data["<<i<<"]"<<data[i];
            cout << "con padre data["<<parent<<"]"<<data[parent];
            if(data[i] >= data[parent]){
                cout << "propiedad cumplida\n";
                break; //propiedad cumplida
            }
            cout << " swap("<<data[i]<<","<<data[parent]<<")\n";
            swap(data[i],data[parent]);
            i = parent;
        }
    }

    void siftDown(int i){
        cout << "siftDown desde i= "<<i<<endl;
        while (true)
        {
            int left = 2*i +1;
            int right = 2*i +2;
            int smallest = i;

            if(left < size && data[left] < data[smallest]){
                cout << " hijo izq menor: data["<<left<<"]="<<data[left]<<endl;
                smallest = left; 
            }

            if(right < size && data[right] < data[smallest]){ 
                cout << " hijo der menor: data["<<right<<"]="<<data[right]<<endl; 
                smallest = right; 
            }

            if(smallest == i){
                cout << "Propiedad cumplida\n";
                break;
            }
            cout << " swap("<<data[i]<<","<<data[smallest]<<")\n";
            swap(data[i],data[smallest]);
            i=smallest;
        }
    }

public:
    MinHeap() : size(0){}

    void insertRaw(int value){
        if(size == MAX){
            cout << "Heap lleno\n";
            return;
        }
        data[size] = value;
        siftUp(size);
        size++;
        printArray();
    }

    void printArray() const{
        cout << "Heap arreglo \n";
        for(int i=0; i<size; ++i){
            cout << data[i] << " ";
        }
        cout << endl;
    }

    bool extractMin(int& out){
        if(size == 0){
            cout << "extractMin heap vacio\n";
            return false;
        }
        out = data[0];
        cout << "min= " << out << endl;
        data[0] = data[--size];
        if(size > 0) siftDown(0);
        printArray();
        return true;
    }
};


int main(){
    MinHeap h;

    h.insertRaw(20);
    h.insertRaw(15);
    h.insertRaw(30);
    h.insertRaw(10);
    h.insertRaw(5);

    h.printArray();

    int x;
    //if(!(cin>x)) break;
    cout << "dame x";
    cin >> x;
    h.insertRaw(x);

    int v;
    h.extractMin(v);

    cout << "\n menor v=" << v << endl;

    return 0;
}