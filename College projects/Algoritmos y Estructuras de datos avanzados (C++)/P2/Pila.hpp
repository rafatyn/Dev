#include <cstdio>
#include "Sll.hpp"

using namespace std;

template<class dato>
class pila {
    
    private:
    
        sll<dato> lista;
        
    public:
    
        pila(void);
        ~pila(void);
        void push(dato x);
        dato pop(void);
        bool empty(void);
        ostream& write(ostream& os) const;
        
};

template<class dato>
pila<dato>::pila(void):
    lista()
    {}
    
template<class dato>    
pila<dato>::~pila(void){}

template<class dato>
void pila<dato>::push(dato x)
{
    lista.insertini(new nodo<dato>(x));
}

template<class dato>
dato pila<dato>::pop(void)
{
    if(!empty()){
        nodo<dato>* aux = lista.extractini();
        return aux->getval();
    }else{
        cout << "La pila esta vacia" << endl;
    }
}  

template<class dato>
bool pila<dato>::empty(void)
{
    return lista.empty();
}

template<class dato>
ostream& pila<dato>::write(ostream& os) const
{
    lista.write(os);
}