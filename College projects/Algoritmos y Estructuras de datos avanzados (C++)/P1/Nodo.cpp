#include "Nodo.hpp"

nodo::nodo(void):
    x(0),
    siguiente(NULL)
    {}
    
nodo::nodo(dato x_):
    x(x_),
    siguiente(NULL)
    {}
    
nodo::~nodo(void)
{
    /*
    if(siguiente!=NULL){
        delete siguiente;
        siguiente = NULL;
    }*/
}

nodo* nodo::getsig(void)
{
    return siguiente;
}

void nodo::setsig(nodo* x_)
{
    siguiente = x_;
}

dato nodo::getval(void)
{
    return x;
}

ostream& nodo::write(ostream& os) const
{
    os << x << " ";
}