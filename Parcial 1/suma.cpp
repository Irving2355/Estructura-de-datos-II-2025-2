#include <iostream>
#include <cstdint>

using namespace std;

long long fastPow(long long a, long long n){
    if(n == 0) return 1;
    if(n == 1) return a;
    if((n % 2) == 0){
        long long t = fastPow(a, n/2);
        return t * t;
    }else{
        return a * fastPow(a,n-1);
    }
}

int main(){
    cout << fastPow(2,4) << endl;
    cout << fastPow(2,3) << endl;
    return 0;
}