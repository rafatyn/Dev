#include <cstdio>
#include <iostream>
#include "DNI.hpp"

using namespace std;

template<class T>
class celda {
    
    private:
    
        T* nBloques;
        int m;
        
    public:
    
        celda(void);
        celda(int n);
        ~celda(void);
        bool buscar(T x, int &pos, int &cont);
        bool insertar(T x);
        bool full(void);
        void write(ostream& os);
        
};

template<class T>
celda<T>::celda(void):
    nBloques(NULL),
    m(0)
    {}
    
template<class T>
celda<T>::celda(int n):
    nBloques(NULL),
    m(n)
    {    
        try {
            nBloques = new T [n];
            for(int i=0; i<n; i++){
                nBloques[i] = 0;
            }
        }
        catch(bad_alloc &b){
            
            cerr << "Error creando las celdas " << b.what() << endl;
            
            throw b;
        }
    }
    
template<class T>
celda<T>::~celda(void)
{
    if(nBloques!=NULL){
        //delete nBloques;
        nBloques=NULL;
    }
}

template<class T>
bool celda<T>::buscar(T x, int &pos, int &cont)
{
    for(int i=0; i<m; i++){
        cont++;
        if(nBloques[i]==x){
            pos = i;
            return true;
        }
        if(nBloques[i]==0){
            return false;
        }
    }
    return false;
}

template<class T>
bool celda<T>::insertar(T x)
{
    for(int i=0; i<m; i++){
        if(nBloques[i]==0){
            nBloques[i] = x;
            return true;
        }
    }
    return false;
}

template<class T>
bool celda<T>::full(void)
{
    for(int i=0; i<m; i++){
        if(nBloques[i]==0){
            return false;
        }
    }
    return true;
}

template<class T>
void celda<T>::write(ostream& os)
{
    for(int i=0; i<m; i++){
        os << nBloques[i] << " ";
    }
    os << "   ";
}