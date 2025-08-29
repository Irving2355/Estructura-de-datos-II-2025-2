#include <iostream>

using namespace std;

int x=0;

void hanoi(int n,char A,char B,char C){
    if(n == 0) return;
    cout << "Valor n antes de" << n <<endl;
    hanoi(n-1,A,C,B);
    x++;
    cout <<"Torre a: " <<A << " Torre b: " << B <<" Torre c: "<< C <<" Valor n: "<< n << endl;
    hanoi(n-1,B,A,C);
    cout << "Valor n despues de" << n <<endl;
    //cout << B << "->" << C << endl;
}

int main(){
    hanoi(5,'A','B','C');
    cout << x;
    return 0;
}