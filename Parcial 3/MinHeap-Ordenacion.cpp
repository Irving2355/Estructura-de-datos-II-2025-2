#include <iostream>

using namespace std;

class MinHeap{
    int data[50];
    int size;

    void siftDown(int i){
        //cout << "siftDown desde i= "<<i<<endl;
        while (true)
        {
            int left = 2*i +1;
            int right = 2*i +2;
            int smallest = i;

            if(left < size && data[left] < data[smallest]){
                //cout << " hijo izq menor: data["<<left<<"]="<<data[left]<<endl;
                smallest = left; 
            }

            if(right < size && data[right] < data[smallest]){ 
                //cout << " hijo der menor: data["<<right<<"]="<<data[right]<<endl; 
                smallest = right; 
            }

            if(smallest == i){
               // cout << "Propiedad cumplida\n";
                break;
            }
            //cout << " swap("<<data[i]<<","<<data[smallest]<<")\n";
            swap(data[i],data[smallest]);
            i=smallest;
        }
    }

public:
    MinHeap() : size(0) {}

    void insert(int v){
        data[size] = v;
        int i = size;

        //Reordenar hacia arriba 
        while(i > 0 && data[i] < data[(i-1)/2]){
            swap(data[i],data[(i-1)/2]);
            i = (i-1)/2;
        }
        ++size;
    }

    int extactMin(){
        if(size == 0) {cout << "Heap vacio\n"; return -1;}
        int minVal = data[0];
        siftDown(0);
        return minVal;
    }

    void print(){
        for(int i=0; i<size; ++i) cout << data[i] << " ";
        cout << endl;
    }

};

int main(){
    MinHeap h;
    int values[] = {10,4,15,20,0,8};
    for(int v: values) h.insert(v);
    h.print();

    cout << "\n\nminimo " << h.extactMin() << endl;
    h.print();
    return 0;
}