#ifndef FD_H
#define FD_H

#include <iostream>
#include <cstdlib>
#include "DNI.hpp"

using namespace std;

template<class T>
class distr {
    
    protected:
    
        int n;
        
    public:
    
        void setn(int n_=10);
        virtual int h(T x) const = 0;
        
};

template<class T>
void distr<T>::setn(int n_)
{
    n = n_;
}

#endif //FD_H