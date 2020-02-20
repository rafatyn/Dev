#ifndef FERD_H
#define FERD_H

#include "FExploracion.hpp"
#include <iostream>

using namespace std;

template<class T>
class FErd: public explr<T> {

    public:
    
        FErd(void);
        ~FErd(void);
        int g(T x, int intento);
};

template<class T>
FErd<T>::FErd(void){}

template<class T>
FErd<T>::~FErd(void){}

template<class T>
int FErd<T>::g(T x, int intento)
{
    srand(x);
    int r;
    for(int i=0; i<intento; i++){
         r = rand();
    }
    if(this->t==1){
        return (this->distm->h(x)+r);       
    }else if(this->t==2){
        return (this->dista->h(x)+r);
    }
}

#endif //FERD_H