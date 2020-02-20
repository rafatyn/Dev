#ifndef CAL_H
#define CAL_H

#include <cstdio>
#include <typeinfo>
#include <exception>
#include <iostream>
#include <new>
#include "Numeros.hpp"
#include "Real.hpp"
#include "Entero.hpp"
#include "Rad.hpp"
#include "Complex.hpp"

using namespace std;

template<class T>
class calc {
    public:
        T suma(T x, T y);
        T resta(T x, T y);
        T mult(T x, T y);
        T divi(T x, T y);
        int comprobar(T x);
};

template<class T>
int calc<T>::comprobar(T x){
    
    try {
        int f=0;
        if(typeid(*x).name()==typeid(entero).name()){
            f=1;
        }else{
            if(typeid(*x).name()==typeid(rad).name()){
                f=2;
            }else{
                if(typeid(*x).name()==typeid(real).name()){
                    f=3;
                }else{
                    if(typeid(*x).name()==typeid(complex).name()){
                        f=4;
                    }
                }
            }
        }
        return f;
    }
    catch (bad_typeid& bt)
    {
        cerr << "Typeid erroneo: " << bt.what() << endl;
        
        throw 10;
    }
    catch (exception& e)
    {
        cerr << "Excepción comprueba: " << e.what() << endl;
        
        throw e;
    }
}
 
    
template<class T>
T calc<T>::suma(T x, T y){
    
    try {
        int fx=comprobar(x);
        int fy=comprobar(y);
        
        if(fx==0||fy==0){
            throw 10;
        }
                
        if(fx!=fy){
            if(fx>fy){
                switch(fx){
                    case 2:
                        return(suma(x,new rad(y->toRacional())));
                    break;
                    case 3:
                        return(suma(x,new real(y->toReal())));
                    break;
                    case 4:
                        return(suma(x,new complex(y->toComplejo())));
                    break;
                }
            }else{
                switch(fy){
                    case 2:
                        return(suma(new rad(x->toRacional()),y));
                    break;
                    case 3:
                        return(suma(new real(x->toReal()),y));
                    break;
                    case 4:
                        return(suma(new complex(x->toComplejo()),y));
                    break;
                }    
            }
        }else{
            complex c,c2;
            rad d,d2;
            real r,r2;
            entero e,e2;
            switch(fx){
                case 1:
                    e = x->toEntero();
                    e2 = y->toEntero();
                    return(new entero(e+e2));
                break;
                case 2:
                    d = x->toRacional();
                    d2 = y->toRacional();
                    return(new rad(d+d2));
                break;
                case 3:
                    r = x->toReal();
                    r2 = y->toReal();
                    return(new real(r+r2));
                break;
                case 4:
                    c = x->toComplejo();
                    c2 = y->toComplejo();
                    return(new complex(c+c2));
                break;
            }
        }
    }
    catch (int& n)
    {
        cerr << "Error comprobando tipo de dato" << endl;
        
        throw 10;
    }
    catch (exception& e)
    {
        cerr << "Excepción calcula: " << e.what() << endl;
        
        throw e;
    }
}

template<class T>
T calc<T>::resta(T x, T y){
    
        try {
        int fx=comprobar(x);
        int fy=comprobar(y);
        
        if(fx==0||fy==0){
            throw 10;
        }
                
        if(fx!=fy){
            if(fx>fy){
                switch(fx){
                    case 2:
                        return(resta(x,new rad(y->toRacional())));
                    break;
                    case 3:
                        return(resta(x,new real(y->toReal())));
                    break;
                    case 4:
                        return(resta(x,new complex(y->toComplejo())));
                    break;
                }
            }else{
                switch(fy){
                    case 2:
                        return(resta(new rad(x->toRacional()),y));
                    break;
                    case 3:
                        return(resta(new real(x->toReal()),y));
                    break;
                    case 4:
                        return(resta(new complex(x->toComplejo()),y));
                    break;
                }    
            }
        }else{
            complex c,c2;
            rad d,d2;
            real r,r2;
            entero e,e2;
            switch(fx){
                case 1:
                    e = x->toEntero();
                    e2 = y->toEntero();
                    return(new entero(e-e2));
                break;
                case 2:
                    d = x->toRacional();
                    d2 = y->toRacional();
                    return(new rad(d-d2));
                break;
                case 3:
                    r = x->toReal();
                    r2 = y->toReal();
                    return(new real(r-r2));
                break;
                case 4:
                    c = x->toComplejo();
                    c2 = y->toComplejo();
                    return(new complex(c-c2));
                break;
            }
        }
    }
    catch (int& n)
    {
        cerr << "Error comprobando tipo de dato" << endl;
        
        throw 10;
    }
    catch (exception& e)
    {
        cerr << "Excepción calcula: " << e.what() << endl;
        
        throw e;
    }
}

template<class T>
T calc<T>::mult(T x, T y){
    
    try {
        int fx=comprobar(x);
        int fy=comprobar(y);
        
        if(fx==0||fy==0){
            throw 10;
        }
                
        if(fx!=fy){
            if(fx>fy){
                switch(fx){
                    case 2:
                        return(mult(x,new rad(y->toRacional())));
                    break;
                    case 3:
                        return(mult(x,new real(y->toReal())));
                    break;
                    case 4:
                        return(mult(x,new complex(y->toComplejo())));
                    break;
                }
            }else{
                switch(fy){
                    case 2:
                        return(mult(new rad(x->toRacional()),y));
                    break;
                    case 3:
                        return(mult(new real(x->toReal()),y));
                    break;
                    case 4:
                        return(mult(new complex(x->toComplejo()),y));
                    break;
                }    
            }
        }else{
            complex c,c2;
            rad d,d2;
            real r,r2;
            entero e,e2;
            switch(fx){
                case 1:
                    e = x->toEntero();
                    e2 = y->toEntero();
                    return(new entero(e*e2));
                break;
                case 2:
                    d = x->toRacional();
                    d2 = y->toRacional();
                    return(new rad(d*d2));
                break;
                case 3:
                    r = x->toReal();
                    r2 = y->toReal();
                    return(new real(r*r2));
                break;
                case 4:
                    c = x->toComplejo();
                    c2 = y->toComplejo();
                    return(new complex(c*c2));
                break;
            }
        }
    }
    catch (int& n)
    {
        cerr << "Error comprobando tipo de dato" << endl;
        
        throw 10;
    }
    catch (exception& e)
    {
        cerr << "Excepción calcula: " << e.what() << endl;
        
        throw e;
    }
}

template<class T>
T calc<T>::divi(T x, T y){
    
    try {
        int fx=comprobar(x);
        int fy=comprobar(y);
        
        if(fx==0||fy==0){
            throw 10;
        }
                
        if(fx!=fy){
            if(fx>fy){
                switch(fx){
                    case 2:
                        return(divi(x,new rad(y->toRacional())));
                    break;
                    case 3:
                        return(divi(x,new real(y->toReal())));
                    break;
                    case 4:
                        return(divi(x,new complex(y->toComplejo())));
                    break;
                }
            }else{
                switch(fy){
                    case 2:
                        return(divi(new rad(x->toRacional()),y));
                    break;
                    case 3:
                        return(divi(new real(x->toReal()),y));
                    break;
                    case 4:
                        return(divi(new complex(x->toComplejo()),y));
                    break;
                }    
            }
        }else{
            complex c,c2;
            rad d,d2;
            real r,r2;
            entero e,e2;
            switch(fx){
                case 1:
                    e = x->toEntero();
                    e2 = y->toEntero();
                    return(new entero(e/e2));
                break;
                case 2:
                    d = x->toRacional();
                    d2 = y->toRacional();
                    return(new rad(d/d2));
                break;
                case 3:
                    r = x->toReal();
                    r2 = y->toReal();
                    return(new real(r/r2));
                break;
                case 4:
                    c = x->toComplejo();
                    c2 = y->toComplejo();
                    return(new complex(c/c2));
                break;
            }
        }
    }
    catch (int& e)
    {
        cerr << "Error comprobando tipo de dato" << endl;
        
        throw 10;
    }
    catch (exception& e)
    {
        cerr << "Excepción calcula: " << e.what() << endl;
        
        throw e;
    }
}

#endif //CAL_H