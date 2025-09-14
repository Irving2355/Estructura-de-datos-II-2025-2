#include <iostream>
#include <cstdint>

using namespace std;

float sqrt(float n){
    //casos base
    if(n<0.0f) return -1;
    if(n==0) return 0.0f;
    //intervalo
    /*
    si n>=1 la raiz esta entre [0,n]
    si 0 < n < 1 la raiz esta entre [0,1]
     */
    float lo = 0.0f;
    float hi = (n >= 1.0f) ? n : 1.0f;

    // 1e-7 error de calculo
    //Cada iteracion reduce  a la mitad el intervalo
    for(int i=0; i<100; ++i){
        float mid = lo + (hi - lo) * 0.5f;
        float sq = mid * mid;

        if(sq <= n){
            lo = mid;
        }else{
            hi = mid;
        }
    }

    return (lo + hi) * 0.5f;
}

int main(){
    float n,r;
    cout << "Dame un numero para la raiz: ";
    cin >> n;

    r = sqrt(n);
    cout << "Respuesta aprox: " << r;
    return 0;
}