#pragma once

#include <cstdio>
#include "Nodo.hpp"

using namespace std;

class sll {
    
    private:
        
        nodo* ini;
        
    public:
    
        sll(void);
        ~sll(void);
        void insertini(nodo* x);
        nodo* extractini(void);
        nodo* extractfin(void);
        nodo* getini(void);
        bool empty(void);
        ostream& write(ostream& os) const;
    
};