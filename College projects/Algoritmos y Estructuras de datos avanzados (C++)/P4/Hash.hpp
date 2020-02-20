#include "Celda.hpp"
#include "FDaleatoria.hpp"
#include "FDmodulo.hpp"
#include "FElineal.hpp"
#include "FEcuadratica.hpp"
#include "FEdispdoble.hpp"
#include "FEredispersion.hpp"

using namespace std;

template<class T>
class hash {
    
    private:
        
        celda<T>* nCeldas;
        distr<T>* dist;
        explr<T>* expr;
        int n;
    
    public:
    
        hash(void);
        hash(int n, int m, int d, int e);
        ~hash(void);
        bool buscar(T x, int &pos, int &max, int &min, float &med);
        bool insertar(T x, int &max, int &min, float &med);
        void write(ostream& os);
        
};

template<class T>
hash<T>::hash(void):
nCeldas(NULL),
dist(NULL),
expr(NULL),
n(0)
{}

template<class T>
hash<T>::hash(int n_, int m, int d, int e)
{
    try {
        
        n=n_;
        nCeldas = new celda<T> [n_];
        for(int i=0; i<n_; i++){
            celda<T> aux(m);
            nCeldas[i] = aux;
        }
            
        switch(d){
            case 1:
                dist = new FDmod<T>;
            break;
            case 2:
                dist = new FDrand<T>;
            break;
            default:
                cout << "La función de dispersión indicada no existe";
            break;
        }
        dist->setn(n_);
    
        switch(e){
            case 1:
                expr = new FElin<T>;
            break;
            case 2:
                expr = new FEcuad<T>;
            break;
            case 3:
                expr = new FEdd<T>;
            break;
            case 4:
                expr = new FErd<T>;
            break;
            default:
                cout << "La función de exploración indicada no existe";
            break;
        }
        expr->setn(n_);
        expr->sett(d);
    }
    catch(bad_alloc &b){
        
        cerr << "Error creando la tabla hash " << b.what() << endl;
        
        throw b;
    }
}

template<class T>
hash<T>::~hash(void)
{
    if(nCeldas!=NULL){
        //delete nCeldas;
        nCeldas = NULL;
    }
    delete dist;
    delete expr;
}

template<class T>
bool hash<T>::buscar(T x, int &pos, int &max, int &min, float &med)
{
    int p = dist->h(x);
    int z = p;
    int ia = 0;
    for(int t=1; t<=n; t++){
        int i=0;
        bool b = nCeldas[z].buscar(x,pos,i);
        if(!b&&nCeldas[z].full()){
            z = expr->g(x,t)%n;
            
            if(i<min) min=i;
            if(t==1) min=i;
            if(i>max) max=i;
            ia += i;
            med = ia/t;
            
        }else if(!b&&!nCeldas[z].full()){
            
            if(i<min) min=i;
            if(t==1) min=i;
            if(i>max) max=i;
            ia += i;
            med = ia/t;
            
            return false;
        }else if(b){
            
            if(i<min) min=i;
            if(t==1) min=i;
            if(i>max) max=i;
            ia += i;
            med = ia/t;
            
            pos = (pos*n)+z+1;
            return true;
        }
    }
    return false;
}

template<class T>
bool hash<T>::insertar(T x, int &max, int &min, float &med)
{
    int bas=0;
    bool c = buscar(x,bas,max,min,med);
    if(!c){
        int p = dist->h(x);
        int z = p;
        for(int t=1; t<=n; t++){
            bool b = nCeldas[z].insertar(x);
            if(b){
                return true;
            }else{
                z = expr->g(x,t)%n;
            }
        }
        return false;
    }
    return true;
}

template<class T>
void hash<T>::write(ostream& os)
{
    for(int i=0; i<n; i++){
        os << "Columna " << i << ": ";
        nCeldas[i].write(os);
    }
    os << endl;
}