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

    //contar total de empleados en el subarbol
    int contarEmpleados()const{
        int total = 1;
        for(int i=0; i<nHijos; ++i){
            total += hijos[i]->contarEmpleados();
        }
        return total;
    }

    //calcular la altura
    int altura()const{
        int hmax = -1;
        for(int i=0; i<nHijos; ++i){
            hmax = max(hmax,hijos[i]->altura());
        }
        return hmax + 1;
    }

    //calcular el grado maximo en todo el subarbol
    int gradoMaximo()const{
        int g = nHijos;
        for(int i=0; i<nHijos; ++i){
            g = max(g, hijos[i]->gradoMaximo());
        }
        return g;
    }
};

int main(){
    Empleado* CEO = new Empleado("CEO");
    Empleado* CTO = new Empleado("CTO");
    Empleado* CFO = new Empleado("CFO");
    Empleado* COO = new Empleado("COO");

    CEO->agregarSubordinado(CTO);
    CEO->agregarSubordinado(CFO);
    CEO->agregarSubordinado(COO);

    Empleado* DevLead = new Empleado("Lider Dev");
    CTO->agregarSubordinado(DevLead);
    DevLead->agregarSubordinado(new Empleado("Dev1"));
    DevLead->agregarSubordinado(new Empleado("Dev2"));

    CFO->agregarSubordinado(new Empleado("Finanzas1"));

    COO->agregarSubordinado(new Empleado("Ops1"));
    COO->agregarSubordinado(new Empleado("Ops2"));

    //Resultados
    cout << "***** Preorden *****"<<endl;
    CEO->imprimirPreorden();

    cout << "\nTotal empleados: " << CEO->contarEmpleados() << endl;

    cout << "\nAltura: " << CEO->altura() << endl;

    cout << "\nGrado maximo: " << CEO->gradoMaximo() << endl;

    delete CEO; //libera todo

    return 0;
}