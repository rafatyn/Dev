#ifndef FDM_H
#define FDM_H

#include "FDistribucion.hpp"
#include <iostream>

using namespace std;

template<class T>
class FDmod: public distr<T> {

    public:
    
        FDmod(void);
        ~FDmod(void);
        int h(T x) const;
};

template<class T>
FDmod<T>::FDmod(void){}

template<class T>
FDmod<T>::~FDmod(void){}

template<class T>
int FDmod<T>::h(T x) const
{
    return (x % this->n);
}

#endif //FDM_H