#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>
#include <chrono>   // para medir tiempo

using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void mostrarVector(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main() {
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

    bubbleSort(vec);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    // acaba el cronometro

    cout << "\nVector ordenado con Bubble Sort:\n";
    mostrarVector(vec);

    cout << "\nTiempo de ejecucion: " << duration.count() << " ms\n";

    return 0;
}