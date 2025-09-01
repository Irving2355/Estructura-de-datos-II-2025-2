#include <iostream>
#include <string>

using namespace std;

class Empleado{
private:
    static const int K = 5;
    string nombre;
    Empleado* hijos[K]; //arreglo de punteros a hijos
    int nHijos; //numero actual de hijos
public:
    //constructor
    explicit Empleado (const string& n): nombre(n), nHijos(0){
        for(int i=0; i<K; ++i) hijos[i] = nullptr;
    }

    //Evitamos copias
    Empleado(const Empleado&) = delete;
    Empleado& operator=(const Empleado&) = delete;

    //destructor recursivo
    ~Empleado(){
        for(int i=0; i<K; ++i)delete hijos[i];
    }

    //agregar subordinados si hay lugar
    bool agregarSubordinado(Empleado* e){
        if(nHijos >= K) return false;
        hijos[nHijos++] = e;
        return true;
    }

    //recorrido en preorden jefe -> hijos
    void imprimirPreorden(int nivel = 0)const{
        cout << "Impresion en preorden del arbol" << endl;
        cout << string(nivel * 2, ' ') << "- " << nombre << endl;
        for(int i=0; i<nHijos; ++i){
            hijos[i]->imprimirPreorden(nivel + 1);
        }
    }
};

int main(){

    return 0;
}