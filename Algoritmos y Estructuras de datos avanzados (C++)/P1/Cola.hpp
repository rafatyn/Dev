#pragma once

#include <cstdio>
#include "Sll.hpp"

using namespace std;

class cola {
    
    private:
        
        sll lista;
        
    public:
    
        cola(void);
        ~cola(void);
        void push(dato x);
        dato pop(void);
        bool empty(void);
        ostream& write(ostream& os) const;

};