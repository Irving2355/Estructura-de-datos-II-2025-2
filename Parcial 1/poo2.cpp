#include <iostream>
#include <string>

using namespace std;

class Alumno{
    public: 
        string nombre;
        int edad;

        Alumno(string n,int e){
            nombre = n;
            edad = e;
        }

        void mostrar(){
            cout << "Nombre " << nombre << endl;
            cout << "Edad " << edad << endl;
        }
};

int main(){
    //Alumno al("Victor", 19);
    //Alumno al2("Edgar", 26);

    Alumno al3;
    al3.nombre="Juan";
    al3.edad=19;

    al3.mostrar();

    //al.mostrar();
    //al2.mostrar();
    return 0;
}