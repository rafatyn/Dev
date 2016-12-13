#ifndef DNI_H
#define DNI_H

#include <iostream>
#include <exception>
#include <new>
#include "concolor.h"

using namespace std;

class dni {
    
    private:
    
        unsigned long int x;
        
    public:
        
        static int comp;
        dni(void);
        dni(long int n);
        ~dni(void);
        long int getx(void) const {return x;}
        int operator%(const int y);
        bool operator<(const dni y);
        bool operator>(const dni y);
        bool operator==(const dni y);
        operator int(void) {return ((int) this->x);}
        void operator <<(ostream& os);
        
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

bool dni::operator<(const dni y)
{
    comp++;
    if(this->x < y.getx()){
        return true;
    }else{
        return false;
    }
}

bool dni::operator>(const dni y)
{
    comp++;
    if(this->x > y.getx()){
        return true;
    }else{
        return false;
    }
}

bool dni::operator==(const dni y)
{
    comp++;
    if(this->x == y.getx()){
        return true;
    }else{
        return false;
    }
}

void dni::operator<<(ostream& os)
{
    os << x;
}

#endif //DNI_H