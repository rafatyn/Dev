#ifndef NUM_H
#define NUM_H

#include <cstdio>
#include <iostream>

using namespace std;

class entero;
class rad;
class complex;
class real;

class numero {

  public:

    virtual const entero toEntero(void) const = 0;
    virtual const rad toRacional(void) const = 0; 
    virtual const real toReal(void) const = 0; 
    virtual const complex toComplejo(void) const = 0; 
    virtual ostream& toStream(ostream& os) const = 0;
    virtual istream& fromStream(istream& is) = 0;
    friend ostream& operator<<(ostream& os, const numero* x) {x->toStream(os); return os;}
};

#endif //NUM_H