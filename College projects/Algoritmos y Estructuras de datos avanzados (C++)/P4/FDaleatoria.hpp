#ifndef FDA_H
#define FDA_H

#include <iostream>
#include <cstdlib>
#include "FDistribucion.hpp"

using namespace std;

template<class T>
class FDrand : public distr<T> {
    
    public:
    
        FDrand(void);
        ~FDrand(void);
        int h(T x) const;
        
};

template<class T>
FDrand<T>::FDrand(void){}

template<class T>
FDrand<T>::~FDrand(void){}

template<class T>
int FDrand<T>::h(T x) const
{
    srand(x);
    return (rand() % this->n);
}

#endif //FDA_H