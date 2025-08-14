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
};

int main(){
    return 0;
}