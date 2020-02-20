#ifndef COL_H
#define COL_H

#include <cstdio>
#include "Sll.hpp"

using namespace std;

template<class dato>
class cola {
    
    private:
        
        sll<dato> lista;
        
    public:
    
        cola(void);
        ~cola(void);
        void push(dato x);
        dato pop(void);
        bool empty(void);
        ostream& write(ostream& os) const;

};

template<class dato>
cola<dato>::cola(void):
    lista()
    {}
    
template<class dato>
cola<dato>::~cola(void){}

template<class dato>
void cola<dato>::push(dato x)
{
    try {
        lista.insertini(new nodo<dato>(x));
    }
    catch(bad_alloc &e)
    {
        cerr << "Error reservando memoria para el nodo a introducir" << endl;
        
        throw e;
    }
    catch (exception& e)
    {
        cerr << "Excepción insertando por el principio: " << e.what() << endl;
        
        throw e;
    }
}

template<class dato>
dato cola<dato>::pop(void)
{
    try {
        if(!empty()){
            nodo<dato>* aux = lista.extractfin();
            return aux->getval();
        }else{
            cout << endl << "La cola esta vacia" << endl;
        }
    }
    catch (exception& e)
    {
        cerr << "Excepción extrayendo el principio: " << e.what() << endl;
        
        throw e;
    }
}

template<class dato>
bool cola<dato>::empty(void)
{
    return lista.empty();
}

template<class dato>
ostream& cola<dato>::write(ostream& os) const
{
    lista.write(os);
}

#endif //COL_H