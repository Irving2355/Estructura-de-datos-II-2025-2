#include <iostream>

using namespace std;

int binSearch(const int a[],int lo, int hi, int x){
    if(lo > hi) return -1; //caso base
    int mid = lo + (hi - lo)/2;
    if(a[mid] == x) return mid; //caso base
    if(x < a[mid]) return binSearch(a,lo,mid-1,x);//actualizar alto
    else return binSearch(a,mid + 1, hi, x);
}

int main(){
    const int n = 10;
    int a[n] = {-5,-2,0,1,3,5,7,9,12,15};
    cout << binSearch(a,0,n-1,-5) << endl;
    cout << binSearch(a,0,n-1,7) << endl;
    cout << binSearch(a,0,n-1,16) << endl;
    return 0;
}