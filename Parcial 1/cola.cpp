#include <iostream>

using namespace std;

class Cola{
    public:
        int datos[5];
        int frente,fin;

        Cola(){frente = 0; fin = -1;}

        bool isEmpty(){return frente >= fin;}
        bool isFull(){return fin == 4;}

        void enqueue(int v){
            if(isFull()){
                cout << "Cola llena" <<endl;
            }else{
                datos[++fin] = v;
            }
        }

        void dequeue(){
            if(isEmpty()){
                cout << "Cola vacia" <<endl;
            }else{
                ++frente;
            }
        } 

        int front(){
            if(isEmpty()){
                cout << "Cola vacia" << endl;
                return -1;
            }
            return datos[frente];
        }

        int size(){
            if(isEmpty()){
                cout << "Cola vacia" << endl;
                return -1;
            }
            return fin - frente + 1;
        }

        void clear(){
            frente = 0;
            fin = -1;
        }

        void mostrar(){
            if(isEmpty()){
                cout << "Cola vacia" << endl;
            }
            for(int i=frente; i<= fin; ++i){
                cout << datos[i] << " ";
            }
        }
};

int main(){
    Cola cola;
    cola.enqueue(1);
    cola.enqueue(2);
    cola.dequeue();
    int x = cola.size();
    cout << x << endl;
    cola.mostrar();
    return 0;
}