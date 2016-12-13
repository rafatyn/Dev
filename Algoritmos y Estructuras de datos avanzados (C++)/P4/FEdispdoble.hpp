#ifndef FEDD_H
#define FEDD_H

#include "FExploracion.hpp"
#include <iostream>

using namespace std;

template<class T>
class FEdd: public explr<T> {

    public:
    
        FEdd(void);
        ~FEdd(void);
        int g(T x, int intento);
};

template<class T>
FEdd<T>::FEdd(void){}

template<class T>
FEdd<T>::~FEdd(void){}

template<class T>
int FEdd<T>::g(T x, int intento)
{
    if(this->t==1){
        return ((this->distm->h(x))+(intento*(this->dista->h(x))));
    }else if(this->t==2){
        return ((this->dista->h(x))+(intento*(this->distm->h(x))));
    }
}

#endif //FEDD_H