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

    static int altura(Nodo* n){ return n? n->h : 0;}

    static int balance(Nodo* n){
        return n? altura(n->izq) - altura(n->der) : 0;
    }

    static void actualizarAltura(Nodo* n){
        if(!n) return;
        n->h = 1 + max(altura(n->izq), altura(n->der));
    }

    static string label(Nodo* n){
        if(!n) return string(); //""
        return "[" + to_string(n->key) + "]";
    }

    static box renderLeaf(Nodo* n){
        box b;
        b.lines = {label(n)};
        b.width = (int)b.lines[0].size();
        b.height = 1;
        b.rootMid = b.width / 2;
        return b;
    }

    static box glue(const box* L, const string& root,const box* R ){
        const int gapMin = 2;
        const int lw = L ? L->width : 0;
        const int rw = R ? R->width : 0;
        const int lh = L ? L->height : 0;
        const int rh = R ? R->height : 0;

        int rootW = (int)root.size();
        int gap = max(gapMin, rootW);
        int width = lw + gap + rw;

        //etiqueta de la raiz centrada
        string top(width, ' ');
        int topPos = lw + gap/2 - rootW/2;
        topPos = max(0,min(width - rootW,topPos));
        top.replace(topPos,rootW,root);

        //conectores hacia L y R 
        string connectors(width, ' ');
        if (L) connectors[L->rootMid] = '/';
        if (R) connectors[lw+gap+R->rootMid] = '\\';

        //Cuerpo coser verticalmente L y R
        int h = max(lh,rh);
        vector<string> body;
        body.reserve(h);

        for(int i=0; i<h; ++i){
            string leftPart = (L && i < L->height)? L->lines[i]: string(lw, ' ');
            string rightPart = (R && i < R->height)? R->lines[i]: string(rw, ' ');
            body.emplace_back(leftPart + string(gap, ' ') + rightPart);
        }

        box b;
        b.lines.reserve(2 + h);
        b.lines.push_back(top);
        b.lines.push_back(connectors);

        for(auto& row: body) b.lines.push_back(std::move(row));

        b.width = width;
        b.height = (int)b.lines.size();
        b.rootMid = topPos + rootW/2;
        
        return b;
    }

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

    Nodo* insertarRec(Nodo* n,int k){
        if(!n) return new Nodo(k);
        
        if(k < n->key) n->izq = insertarRec(n->izq,k);
        else if(k > n->key) n->der = insertarRec(n->der,k);
        else return n;

        actualizarAltura(n);
    }

};

int main(){
    return 0;
}