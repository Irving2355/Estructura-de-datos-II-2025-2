#include <iostream>
#include <vector>
#include <queue>
#include <string> 
#include <algorithm> // funcion max

using namespace std;

struct Nodo {
    int key; // dato almacenado
    int h; //altura de nodo
    Nodo* izq;
    Nodo* der;
};

class AVL{
public:
    AVL() : raiz(nullptr), verbose(true) {}

    void setVerbose(bool v){ verbose = v;}

    void insertar(int k){
        raiz = insertarRec(raiz,k);
        imprimirBonito();
    }

    void imprimirBonito(){
        auto box = render(raiz);
        for(const auto& line : box.lines) cout << line << '\n';
    }

private:

    struct box
    {
        vector<string> lines; // subarbol
        int width = 0;
        int height = 0;
        int rootMid = 0;
    };
    
    Nodo* raiz;
    bool verbose;

    static box render(Nodo* n){
        if(!n){
            box b;
            b.lines = {" "};
            b.width = 1;
            b.height = 1;
            b.rootMid = 0;
            return b;
        }
        if(!n->izq && !n->der) renderLeaf(n);
        box left = render(n->izq);
        box right = render(n->der);
        return glue(n->izq? &left: nullptr, label(n), n->der? &right: nullptr );

    }

};

int main(){
    return 0;
}