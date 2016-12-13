#ifndef FEL_H
#define FEL_H

#include "FExploracion.hpp"
#include <iostream>

using namespace std;

template<class T>
class FElin: public explr<T> {

    public:
    
        FElin(void);
        ~FElin(void);
        int g(T x, int intento);
};

template<class T>
FElin<T>::FElin(void){}

template<class T>
FElin<T>::~FElin(void){}

template<class T>
int FElin<T>::g(T x, int intento)
{
    if(this->t==1){
        return (this->distm->h(x)+intento);
    }else if(this->t==2){
        return (this->dista->h(x)+intento);
    }        
}

#endif //FEL_H