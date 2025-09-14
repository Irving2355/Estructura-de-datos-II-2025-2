#include <iostream>
#include <string>

using namespace std;

class Auto{
    public: 
        string marca;
        int anio;

        //constructor
        Auto(string m, int a){
            marca = m;
            anio = a;
        }

        //metodos
        void mostrarInfo(){
            cout << "Marca: " << marca << " anio: " << anio <<endl;
        }
};

int main(){
    Auto miAuto("Toyota",1999);
    miAuto.mostrarInfo();
    return 0;
}