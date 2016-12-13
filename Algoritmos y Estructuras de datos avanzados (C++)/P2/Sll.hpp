#include <cstdio>
#include "Nodo.hpp"

using namespace std;

template<class dato>
class sll {
    
    private:
        
        nodo<dato>* ini;
        
    public:
    
        sll(void);
        ~sll(void);
        void insertini(nodo<dato>* x);
        nodo<dato>* extractini(void);
        nodo<dato>* extractfin(void);
        nodo<dato>* getini(void);
        bool empty(void);
        ostream& write(ostream& os) const;
    
};

template<class dato>
sll<dato>::sll(void):
    ini(NULL)
    {}
    
template<class dato>
sll<dato>::~sll(void)
{
    while(ini!=NULL){            
        nodo<dato>* aux=ini;
        ini = ini->getsig();
        delete aux;
    }
}

template<class dato>
void sll<dato>::insertini(nodo<dato>* x)
{
    x->setsig(ini);
    ini = x;
}

template<class dato>
nodo<dato>* sll<dato>::extractini(void)
{
    nodo<dato>* aux = ini;
    if(aux!=NULL){
        ini = aux->getsig();
        aux->setsig(NULL);
    }else{
        ini = NULL;
    }  
    
    return aux;
}

template<class dato>
nodo<dato>* sll<dato>::extractfin(void)
{
    nodo<dato>* aux = ini;
    if(aux!=NULL){
        nodo<dato>* aux2 = ini->getsig();
        if(aux2!=NULL){
            while(aux2->getsig()!=NULL){
                aux = aux->getsig();
                aux2 = aux2->getsig();
            }
            aux->setsig(NULL);
            
            return aux2;
        }
    }
    ini = NULL;
    
    return aux;
}

template<class dato>
nodo<dato>* sll<dato>::getini(void)
{
    return ini;
}

template<class dato>
bool sll<dato>::empty(void)
{
    if(ini==NULL){
        return 1;
    }
    return 0;
}

template<class dato>
ostream& sll<dato>::write(ostream& os) const
{
    nodo<dato>* aux = ini;
    while(aux!=NULL){
        aux->write(os);
        aux = aux->getsig();
    }
    os << endl;
}