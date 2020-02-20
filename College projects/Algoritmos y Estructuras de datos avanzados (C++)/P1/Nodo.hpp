#pragma once

#include <cstdio>
#include <iostream>

typedef char dato;

using namespace std;

class nodo {
    
    private:
    
        dato x;
        nodo* siguiente;
        
    public:
    
        nodo(void);
        nodo(dato x_);
        ~nodo(void);
        nodo* getsig(void);
        void setsig(nodo* x_);
        dato getval(void);
        ostream& write(ostream& os) const;
        
};