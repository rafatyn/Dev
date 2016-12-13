#ifndef NOD_H
#define NOD_H

#include <cstdio>
#include <iostream>
#include "Calculadora.hpp"

using namespace std;

template<class dato>
class nodo {
    
    private:
    
        dato x;
        nodo<dato>* siguiente;
        
    public:
    
        nodo(void);
        nodo(dato x_);
        ~nodo(void);
        nodo<dato>* getsig(void);
        void setsig(nodo<dato>* x_);
        dato getval(void);
        ostream& write(ostream& os) const;
        
};

template<class dato>
nodo<dato>::nodo(void):
    x(0),
    siguiente(NULL)
    {}
    
template<class dato>
nodo<dato>::nodo(dato x_):
    x(x_),
    siguiente(NULL)
    {}
    
template<class dato>
nodo<dato>::~nodo(void)
{
    if(siguiente!=NULL){
        delete siguiente;
        siguiente = NULL;
    }
}

template<class dato>
nodo<dato>* nodo<dato>::getsig(void)
{
    return siguiente;
}

template<class dato>
void nodo<dato>::setsig(nodo<dato>* x_)
{
    siguiente = x_;
}

template<class dato>
dato nodo<dato>::getval(void)
{
    return x;
}

template<class dato>
ostream& nodo<dato>::write(ostream& os) const
{
    os << x << " ";
    
    return os;
}

#endif //NOD_H
