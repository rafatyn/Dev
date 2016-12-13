#ifndef VEC_H
#define VEC_H

#include <iostream>

using namespace std;

template<class dato>
class vector {
    
    private: 
    
        int sz;
        dato* pepe;
    
    public:
    
        vector(void);
        vector(int sz_);
        vector(vector<dato>& x);
        ~vector(void);
        dato getdato(int pos);
        void setdato(dato data, int pos);
        int getsz(void);
        ostream& write(ostream& os, int i) const;
        
};

#endif //VEC_H
    
template<class dato>
vector<dato>::vector(void):
    sz(0),
    pepe(NULL)
    {}

template<class dato>
vector<dato>::vector(int sz_):
    sz(sz_),
    pepe(NULL)
    {
        try {
            pepe = new dato [sz_];
            for(int i=0; i<sz_; i++){
                pepe[i]=0;
            }
        }
        catch(bad_alloc &e)
        {            
            cerr << "Error reservando memoria para el vector" << endl;
            
            throw e;
        }
        catch (exception& e)
        {
            cerr << "Excepción construyendo el vector: " << e.what() << endl;
            
            throw e;
        }
    }
    
template<class dato>
vector<dato>::vector(vector& x)
{
    try {
        sz = x.getsz();
        pepe = new dato [sz];
        for(int i=0; i<sz; i++){
            pepe[i]=x.getdato(i);
        }
    }
    catch(bad_alloc &e)
    {        
        cerr << "Error reservando memoria para el vector" << endl;
        
        throw e;
    }
    catch (exception& e)
    {
        cerr << "Excepción construyendo el vector: " << e.what() << endl;
        
        throw e;
    }
}

template<class dato>
vector<dato>::~vector(void)
{
    if(pepe!=NULL){
        delete [] pepe;
        pepe = NULL;
    }
}

template<class dato>
dato vector<dato>::getdato(int pos)
{
    try {
        if((pos-1)<0){
            cout << "Esta intentado acceder a una posicion menor que cero";
        }else{
            if((pos-1)>sz){
                cout << "La posicion a la que accede no existe";
            }else{
                return pepe[pos-1];
            }
        }
    }
    catch (exception& e)
    {
        cerr << "Excepción entrando en el vector: " << e.what() << endl;
        
        throw e;
    }
}

template<class dato>
void vector<dato>::setdato(dato data, int pos)
{
    try {
        if((pos-1)<0){
            cout << "Esta intentado acceder a una posicion menor que cero";
        }else{
            if((pos-1)>sz){
                cout << "La posicion a la que accede no existe";
            }else{
                pepe[pos-1]=data;
            }  
        }
    }
    catch (exception& e)
    {
        cerr << "Excepción entrando en el vector: " << e.what() << endl;
        
        throw e;
    }
}

template<class dato>
int vector<dato>::getsz(void)
{
    return sz;
}

template<class dato>
ostream& vector<dato>::write(ostream& os, int i_) const
{
    try {
        for(int i=0; i<i_; i++){
            os << pepe[i] << " ";
        }
        os << endl;
    }
    catch (exception& e)
    {
        cerr << "Excepción escribiendo en el os: " << e.what() << endl;
        
        throw e;
    }
}