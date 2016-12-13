#include "Sll.hpp"

sll::sll(void):
    ini(NULL)
    {}
    
sll::~sll(void)
{
    while(ini!=NULL){            
        nodo* aux=ini;
        ini = ini->getsig();
        delete aux;
    }
}

void sll::insertini(nodo* x)
{
    x->setsig(ini);
    ini = x;
}

nodo* sll::extractini(void)
{
    nodo* aux = ini;
    if(aux!=NULL){
        ini = aux->getsig();
        aux->setsig(NULL);
    }else{
        ini = NULL;
    }  
    
    return aux;
}

nodo* sll::extractfin(void)
{
    nodo* aux = ini;
    if(aux!=NULL){
        nodo* aux2 = ini->getsig();
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

nodo* sll::getini(void)
{
    return ini;
}

bool sll::empty(void)
{
    if(ini==NULL){
        return 1;
    }
    return 0;
}

ostream& sll::write(ostream& os) const
{
    nodo* aux = ini;
    while(aux!=NULL){
        aux->write(os);
        aux = aux->getsig();
    }
    os << endl;
}