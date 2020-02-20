#ifndef FEC_H
#define FEC_H

#include "FExploracion.hpp"
#include <iostream>
#include <cmath>

using namespace std;

template<class T>
class FEcuad: public explr<T> {

    public:
    
        FEcuad(void);
        ~FEcuad(void);
        int g(T x, int intento);
};

template<class T>
FEcuad<T>::FEcuad(void){}

template<class T>
FEcuad<T>::~FEcuad(void){}

template<class T>
int FEcuad<T>::g(T x, int intento)
{
    if(this->t==1){
        return (this->distm->h(x)+pow(intento,2));
    }else if(this->t==2){
        return (this->dista->h(x)+pow(intento,2));
    }
}

#endif //FEC_H