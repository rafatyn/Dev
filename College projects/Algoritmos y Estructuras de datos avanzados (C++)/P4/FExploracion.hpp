#ifndef FE_H
#define FE_H

#include <iostream>
#include <cstdlib>
#include "FDaleatoria.hpp"
#include "FDmodulo.hpp"
#include "DNI.hpp"

using namespace std;

template<class T>
class explr {
    
    protected:
    
        short unsigned int t;
        distr<T>* distm;
        distr<T>* dista;
        
    public:
    
        explr(void);    
        ~explr(void);
        void setn(int n_=100);
        void sett(int t_=1);
        virtual int g(T x, int intento) = 0;
        
};

template<class T>
explr<T>::explr(void)
{
    try {
        distm = new FDmod<T>;
        dista = new FDrand<T>;
    }
    catch(bad_alloc &b){
        
        cerr << "Error en las funciones de dispersion de la exploracion  " << b.what() << endl;
        
        throw b;
    }
}

template<class T>
explr<T>::~explr(void)
{
    delete distm;
    delete dista;
}

template<class T>
void explr<T>::setn(int n_)
{
    distm->setn(n_);
    dista->setn(n_);
}

template<class T>
void explr<T>::sett(int t_)
{
    t = t_;
}
#endif //FE_H