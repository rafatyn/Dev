#ifndef DNI_H
#define DNI_H

#include <iostream>
#include <exception>
#include <new>

using namespace std;

class dni {
    
    private:
    
        unsigned long int x;
        
    public:
    
        dni(void);
        dni(long int n);
        ~dni(void);
        int operator%(const int y);
        operator int(void) {return ((int) this->x);}
        
};

dni::dni(void):
x(0)
{}

dni::dni(long int n):
x(n)
{}

dni::~dni(void){}

int dni::operator%(const int y)
{
    return (this->x%y);
}

#endif //DNI_H