#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <chrono>   // para medir tiempo

/*
auto x = 10;        // x es int
auto y = 3.14;      // y es double
auto z = "Hola";    // z es const char*
auto x;             //Error: no hay valor para deducir tipo
Una vez deducido el tipo es fijo
*/

using namespace std;
using namespace std::chrono;

void siftDown(vector<int>& arr, int n, int i){
    while (true)
    {
        int lergest = i , left = 2*i+1 , right = 2*i+2;
        if(left < n && arr[left] < arr[lergest]){
            lergest = left; 
        }
        if(right < n && arr[right] < arr[lergest]){ 
            lergest = right; 
        }
        if(lergest == i){
            break;
        }
        swap(arr[i],arr[lergest]);
        i=lergest;
    }
}

void heapSort(vector<int>& arr, int n){
    //construir max-heap
    for(int i = n/2 -1; i >=0; --i) siftDown(arr,n,i);
    //extraer maximos al final
    for(int i=n-1; i >=1; --i){
        swap(arr[0],arr[i]);
        siftDown(arr,i,0);
    }
}

void mostrarVector(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main(){
    int n = 1000;
    vector<int> vec(n);
    srand(time(0));

    // Llenar vector con numeros aleatorios
    for (int i = 0; i < n; i++) {
        vec[i] = rand() % 100 + 1;
    }

    cout << "\nVector original:\n";
    mostrarVector(vec);

    // inica el cronometro
    auto start = high_resolution_clock::now();

    heapSort(vec,n);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    // acaba el cronometro

    cout << "\nVector ordenado con Bubble Sort:\n";
    mostrarVector(vec);

    cout << "\nTiempo de ejecucion: " << duration.count() << " ms\n";

    return 0;
}