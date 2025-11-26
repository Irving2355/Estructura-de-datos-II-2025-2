#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

struct Libro{
    string isbn;
    string titulo;
    string autor;
    string area;
    string ubicacion;

    Libro(const string& i = "",
         const string& t = "",
         const string& a = "",
         const string& ar = "",
         const string& u = "")
        : isbn(i), titulo(t), autor(a), area(ar),ubicacion(u){}
};

class HashLibros{
private:
    vector<list<Libro>> tabla;
    size_t capacidad;

    //convierte isbn en un indice
    //isbn 2347895 o 23445F34A
    size_t hashISBN(const string& isbn) const{
        unsigned long h = 0;
        for(char c : isbn){
            h = h * 131 + (unsigned)c;
        }
        return h % capacidad;
    }

public:
    HashLibros(size_t cap = 101)
        : tabla(cap), capacidad(cap){}
    
    void insertar(const Libro& libro){
        size_t idx = hashISBN(libro.isbn);
        for(auto& lb : tabla[idx]){
            if(lb.isbn == libro.isbn){
                lb = libro; //actualiza 
                return;
            }
        }
        tabla[idx].push_back(libro);
    }

    Libro* buscar(const string& isbn){
        size_t idx = hashISBN(isbn);
        for(auto& lb: tabla[idx]){
            if(lb.isbn == isbn){
                return &lb;
            }
        }
        return nullptr;
    }

    bool eliminar(const string& isbn){
        size_t idx = hashISBN(isbn);
        for(auto it = tabla[idx].begin(); it != tabla[idx].end(); ++it){
            if(it->isbn == isbn){
                tabla[idx].erase(it);
                return true;
            }
        }
        return false;
    }

    size_t totalLibros()const{
        size_t total = 0;
        for(const auto& bucket : tabla){
            total += bucket.size();
        }
        return total;
    }

    size_t contarPorArea(const string& area) const{
        size_t total = 0;
        for(const auto& bucket : tabla){
            for(const auto& lb : bucket){
                if(lb.area == area){
                    total++;
                }
            }
        }
        return total;
    }

    void imprimirDebug() const{
        for(size_t i=0; i < capacidad; ++i){
            cout << "Bucket " << i << ": ";
            for(const auto& lb : tabla[i]){
                cout << "[ " << lb.isbn << " | " << lb.titulo << lb.area << " | " << lb.autor << " ]";     
            }
            cout << "\n";
        }
    }
};

int main(){
    HashLibros catalogo(11);

    catalogo.insertar(Libro("978-0101", "Don quijote","Cervantes","Clasico","España"));

    catalogo.insertar(Libro("978-0102", "Prisionero","Cervantes","Clasico","España"));

    catalogo.insertar(Libro("978-0103", "Lorax","Cervantes","Clasico","España"));

    catalogo.imprimirDebug();

    cout << "\n\ntotal" << catalogo.totalLibros() << "\n";

    catalogo.eliminar("978-0103");

    cout << endl;
    catalogo.imprimirDebug();
    return 0;
}