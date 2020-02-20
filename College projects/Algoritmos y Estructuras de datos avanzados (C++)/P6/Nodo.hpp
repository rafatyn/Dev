#ifndef NOD_H
#define NOD_H

#include <cstdio>
#include "DNI.hpp"

using namespace std;

template<class T>
class nodo {
            
    public:
        
        nodo(T dat, T cl, nodo<T> *iz_=NULL, nodo<T> *de_=NULL):
            dato(dat),
            clave(cl),
            iz(iz_),
            de(de_)
            {}
        
        T dato;
        T clave;
        nodo<T> *iz;
        nodo<T> *de;
        
        bool write(int n)
        {
            bool i=true,d=true;
            if(n==0){
                cout << "[" << dato << "]";
            }else{
                if(iz!=NULL){
                    i=iz->write(n-1);
                }else{
                    for(int j=0; j<pow(2,n-1); j++){
                        cout << "[.]";
                    }
                    i=false;
                }
                
                if(de!=NULL){
                    d=de->write(n-1);
                }else{
                    for(int j=0; j<pow(2,n-1); j++){
                        cout << "[.]";
                    }
                    d=false;
                }
            }
            if(!i&&!d){
                return false;    
            }
            return true;
        }
};

#endif //NOD_H