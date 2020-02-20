#include "Cola.hpp"

cola::cola(void):
    lista()
    {}
    
cola::~cola(void){}

void cola::push(dato x)
{
    lista.insertini(new nodo(x));
}

dato cola::pop(void)
{
    if(!empty()){
        nodo* aux = lista.extractfin();
        return aux->getval();
    }else{
        cout << endl << "La cola esta vacia" << endl;
    }
}

bool cola::empty(void)
{
    return lista.empty();
}

ostream& cola::write(ostream& os) const
{
    lista.write(os);
}