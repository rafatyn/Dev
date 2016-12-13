#include "Pila.hpp"

pila::pila(void):
    lista()
    {}
    
pila::~pila(void){}

void pila::push(dato x)
{
    lista.insertini(new nodo(x));
}

dato pila::pop(void)
{
    if(!empty()){
        nodo* aux = lista.extractini();
        return aux->getval();
    }else{
        cout << "La pila esta vacia" << endl;
    }
}  

bool pila::empty(void)
{
    return lista.empty();
}

ostream& pila::write(ostream& os) const
{
    lista.write(os);
}