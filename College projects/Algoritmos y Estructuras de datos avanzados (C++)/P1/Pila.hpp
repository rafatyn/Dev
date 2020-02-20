#include <cstdio>
#include "Sll.hpp"

using namespace std;

class pila {
    
    private:
    
        sll lista;
        
    public:
    
        pila(void);
        ~pila(void);
        void push(dato x);
        dato pop(void);
        bool empty(void);
        ostream& write(ostream& os) const;
        
};