/*si las claves son enteras en [0,k] con k pequeño
mantenenos un arreglo de colas un bucket por clave
osea "si conozco el rango de prioridades puedo ir 
directo al bucket minimo" */
#include <iostream>
using namespace std;

//cola circular simple para cada bucket
struct Queue
{
    static const int CAP = 256; //capacidad de bucket
    int id[CAP]; //simetria con el key
    int key[CAP]; //key es el bucket en un rango 
    int head = 0, tail = 0, cnt = 0;

    bool empty() const { return cnt == 0;}
    bool full() const {return cnt == CAP;}
    int size() const { return cnt;}

    //push encola al final tail
    bool push(int _id, int _key){
        if(full()) return false;
        id[tail] = _id;
        key[tail] = _key;
        tail = (tail + 1) % CAP;
        ++cnt;
        return true;
    }

    //pop saca del frente head
    bool pop(int& _id, int& _key){
        if(empty()) return false;
        _id = id[head];
        _key = key[head];
        head = (head + 1) % CAP;
        --cnt;
        return true;
    }

    //front lee el frente sin extraer
    bool front(int& _id, int& _key)const{
        if(empty()) return false;
        _id = id[head];
        _key = key[head];
        return true;
    }

    void dump() const{
        cout << "[";
        for(int i=0; i<cnt; ++i){
            int pos = (head + i) % CAP; //posicion real del i-mismo
            cout << id[pos];
            if(i + 1 < cnt) cout << ",";
        }
        cout << "]";
    }

    /*findIdOffset busca id y devuelve su offset logico (o ... cnt-1) contando desde head
    sirve para ubicar rapidamente en elemnto dentro del bucket*/
    int findIdOffset(int targetId) const{
        for(int i=0; i<cnt; ++i){
            int pos = (head + i) % CAP;
            if(id[pos] == targetId) return i;
        }
        return -1; // no se encontro
    }

    /*ereaseOffset elimina el elemento ubicado en el offset*/
    bool ereaseOffset(int off, int& outId, int& outKey){
        if(off < 0 || off >= cnt) return false;
        int newCnt = 0;
        bool removed = false;

        /*Recoremos toda la cola desde head copiando a la
        nueva ubicacion logica excepto el elemento a borrar*/
        for(int i=0; i<cnt; ++i){
            int pos = (head + i) % CAP;
            if(i == off){
                //guardamos el que borramos para devolver
                outId = id[pos];
                outKey = key[pos];
                removed = true;
            }else{
                //compactar logicamente 
                id[(head + newCnt) % CAP] = id[pos];
                key[(head + newCnt) % CAP] = key[pos];
                ++newCnt;
            }
        }

        tail = (head + newCnt) % CAP;
        cnt = newCnt;
        return removed;
    }

    bool enqueueBack(int _id, int _key){ return push(_id,_key);}
};

class BucketMinPQ{
    static const int K = 100;
    static const int BK = K + 1;
    Queue B[BK];
    int minPtr = BK;
    int total = 0; 

    void advanceMinPtr(){
        while(minPtr < BK && B[minPtr].empty()) ++minPtr;
    }

public:
    bool isEmpty() const{return total == 0;}

    //insert amortizado coloca  id,key en el bucket de su key
    bool insert(int id, int key){
        if(key < 0 || key > K) return false;
        bool ok = B[key].push(id,key);
        if(!ok) return false;
        ++total;
        if(minPtr >= BK || key < minPtr) minPtr = key;
        return true;
    }

    bool extactMin(int& id, int& key){
        if(isEmpty()) return false;
        if(minPtr >= BK) advanceMinPtr();
        if(minPtr >= BK) return false;

        if(B[minPtr].empty()){
            advanceMinPtr();
            if(minPtr >= BK) return false;
        }

        bool ok = B[minPtr].pop(id,key);
        if(!ok) return false;
        --total;

        if(B[minPtr].empty()){
            ++minPtr;
            advanceMinPtr();
        }

        return true;
    }

    void printState() const{
        cout << "PQ(total= " << total << ", minPtr= ";
        if(minPtr >= BK) cout << "N/A"; else cout << minPtr;
        cout << " )\n"; 
        for(int k=0; k<BK; ++k){
            if(!B[k].empty()){
                cout << " k= "<<k<< " ";
                B[k].dump();
                cout << "\n";
            }
        }
    }

    void clear(){
        for(int k=0; k<BK; ++k){
            B[k] = Queue{};
        }
        minPtr = BK;
        total = 0;
    }

    /*peekMin inspecciona el minimo sin extraer*/
    bool peekMin(int& id, int& key){
        if(isEmpty()) return false;
        if(minPtr >= BK) advanceMinPtr();
        if(minPtr >= BK) return false;

        if(B[minPtr].empty()){
            advanceMinPtr();
            if(minPtr >= BK) return false;
        }

        return B[minPtr].front(id,key);
    }

    bool decreaseKeyById(int targetId ,int newKey){
        if(newKey < 0 || newKey > K) return false;

        int foundBucket = -1, off = -1;
        for(int k=0; k<BK; ++k){
            off = B[k].findIdOffset(targetId);

            if(off >= 0) {foundBucket = k; break;}
        }
        if(foundBucket < 0) return false;

        int oldId, oldKey;
        if(!B[foundBucket].ereaseOffset(off,oldId,oldKey)) return false;

        if(newKey > oldKey){
            B[foundBucket].enqueueBack(oldId,oldKey);
            return false;
        }

        if(!B[newKey].enqueueBack(oldId,newKey)){
            B[foundBucket].enqueueBack(oldId,oldKey);
            return false;
        }

        if(minPtr >= BK || newKey < minPtr) minPtr = newKey;
        return true;
    }
};


int main(){
    BucketMinPQ pq;

    pq.insert(10,8);
    pq.insert(11,1);
    pq.insert(12,13);
    pq.insert(13,1);
    pq.insert(14,0);
    pq.insert(15,5);
    pq.insert(16,9);
    pq.insert(17,2);
    pq.insert(99,99);
    pq.insert(34,99);
    cout << "Estado inicial \n";
    pq.printState();

    int id,key;
    if(pq.peekMin(id,key)){
        cout << "peekMin-> (id= " << id << " ,key= " << key <<")\n";
    }

    //tres extraciones
    for(int t=1; t<=3; ++t){
        bool ok = pq.extactMin(id,key);
        cout << t << " extactMin-> (id= " << (ok? to_string(id): "N/A") << " ,key= " << (ok? to_string(key): "N/A") <<")\n";

        cout << "Estado iterado "<< t << "\n";
        pq.printState();
        cout << endl;
    }

    cout << "\n decreaseKey (16,1) == \n";
    pq.decreaseKeyById(16,1);
    pq.printState();
    
    return 0;
}