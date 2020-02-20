#pragma once

#include <iostream>

typedef char dato;

using namespace std;

class vector {
    
    private: 
    
        int sz;
        dato* pepe;
    
    public:
    
        vector(void);
        vector(int sz_);
        vector(vector& x);
        ~vector(void);
        dato getdato(int pos);
        void setdato(dato data, int pos);
        int getsz(void);
        ostream& write(ostream& os) const;
        
};
    
    