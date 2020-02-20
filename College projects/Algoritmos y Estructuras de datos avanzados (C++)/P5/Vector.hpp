#ifndef VEC_H
#define VEC_H

#include <cstdio>
#include "DNI.hpp"

using namespace std;

template<class T>
class vector {
    
    private:
    
        T* v;
        int n;
    
    public:
    
    vector(void);
    vector(int n_);
    ~vector(void);
    int getn(void) {return n;}
    T getd(int i) {return v[i];}
    void setd(T x, int i) {v[i] = x;}
    void write(ostream& os);
    void write(ostream& os, int i);
    void write(ostream& os, int i, int j);
    void writeu(ostream& os, int ini, int fin);
    void write(ostream& os, int i, int j, T p, int ini, int fin);
        
};

template<class T>
vector<T>::vector(void):
    v(NULL),
    n(0)
    {}
    
template<class T>
vector<T>::vector(int n_):
    n(n_),
    v(NULL)
    {
        v = new T [n_];
    }

template<class T>
vector<T>::~vector(void)
{
    //delete v;
    v = NULL;
}

template<class T>
void vector<T>::write(ostream& os)
{
    for(int i=0; i<n; i++){
        os << normal << v[i] << "  ";
    }
}

template<class T>
void vector<T>::write(ostream& os, int i, int j)
{
    for(int k=0; k<i; k++){
        os << normal << v[k] << "  ";
    }
    os << redb << v[i] << "  ";
    for(int k=i+1; k<j; k++){
        os << normal << v[k] << "  ";
    }
    os << redb << v[j] << "  ";
    for(int k=j+1; k<n; k++){
        os << normal << v[k] << "  ";
    }
    os << normal;
}

template<class T>
void vector<T>::write(ostream& os, int i)
{
    int k;
    for(k=0; k<i; k++){
        os << redb << v[k] << "  ";
    }
    if(k<n){
        os << yellowb << v[k] << "  " << normal;
        for(k=i+1; k<n; k++){
            os << v[k] << "  ";
        }
    }
    os << normal;
    
}

template<class T>
void vector<T>::writeu(ostream& os, int ini, int fin)
{
    int cent = (ini+fin)/2;
    for(int i=ini; i<=cent; i++){
        os << greenb << v[i] << "  ";
    }
    for(int j=cent+1; j<=fin; j++){
        os << cyanb << v[j] << "  ";
    }
    os << normal;    
}

template<class T>
void vector<T>::write(ostream& os, int i, int j, T p, int ini, int fin)
{
    int k=0;
    int x=0;
    fin++;
    for(x=0; x<n&&v[x]!=p; x++){}
        
    if(i<j){
        if(i<x){
            for(k=ini; k<i; k++){
                os << normal << v[k] << "  ";
            }
            os << redb << v[i] << "  ";
            if(x<=j){
                for(k=i+1; k<x; k++){
                    os << normal << v[k] << "  ";
                }
                if(j!=x) os << yellowb << v[x] << "  ";
                else os << greenb << v[x] << "  ";
                for(k=k+1; k<j; k++){
                    os << normal << v[k] << "  ";
                }
                if(j!=x) os << redb << v[j] << "  ";
                for(k=j+1; k<fin; k++){
                    os << normal << v[k] << "  ";
                }
            }else if(j<x){
                for(k=i+1; k<j; k++){
                    os << normal << v[k] << "  ";
                }
                os << redb << v[j] << "  ";
                for(k=j+1; k<x; k++){
                    os << normal << v[k] << "  ";
                }
                os << yellowb << v[x] << "  ";
                for(k=x+1; k<fin; k++){
                    os << normal << v[k] << "  ";
                }
            }            
        }else if(i>x){
            for(k=ini; k<x; k++){
                os << normal << v[k] << "  ";
            }
            os << yellowb << v[x] << "  ";
            for(k=x+1; k<i; k++){
                os << normal << v[k] << "  ";
            }
            os << redb << v[i] << "  ";
            for(k=i+1; k<j; k++){
                os << normal << v[k] << "  ";
            }
            os << redb << v[j] << "  ";
            for(k=j+1; k<fin; k++){
                os << normal << v[k] << "  ";
            }
        }else if(i==x){
            for(k=ini; k<x; k++){
                os << normal << v[k] << "  ";
            }
            os << greenb << v[x] << "  ";
            for(k=i+1; k<j; k++){
                os << normal << v[k] << "  ";
            }
            os << redb << v[j] << "  ";
            for(k=j+1; k<fin; k++){
                os << normal << v[k] << "  ";
            }
        }
    }else if(j<i){
        if(j<x){
            for(k=ini; k<j; k++){
                os << normal << v[k] << "  ";
            }
            os << redb << v[j] << "  ";
            if(i<x){
                for(k=j+1; k<i; k++){
                    os << normal << v[k] << "  ";
                }
                os << redb << v[i] << "  ";
                for(k=i+1; k<x; k++){
                    os << normal << v[k] << "  ";
                }
                os << yellowb << v[x] << "  ";
                for(k=x+1; k<fin; k++){
                    os << normal << v[k] << "  ";
                }                
            }else if(i>x){
                for(k=j+1; k<x; k++){
                    os << normal << v[k] << "  ";
                }
                os << yellowb << v[x] << "  ";
                for(k=x+1; k<i; k++){
                    os << normal << v[k] << "  ";
                }
                os << redb << v[i] << "  ";
                for(k=i+1; k<fin; k++){
                    os << normal << v[k] << "  ";
                }
            }else if(i==x){
                for(k=j+1; k<x; k++){
                    os << normal << v[k] << "  ";
                }
                os << greenb << v[x] << "  ";
                for(k=i+1; k<fin; k++){
                    os << normal << v[k] << "  ";
                }
            }
        }else if(j>x){
            for(k=ini; k<x; k++){
                os << normal << v[k] << "  ";
            }
            os << yellowb << v[x] << "  ";
            for(k=x+1; k<j; k++){
                os << normal << v[k] << "  ";
            }
            os << redb << v[j] << "  ";
            for(k=j+1; k<i; k++){
                os << normal << v[k] << "  ";
            }
            os << redb << v[i] << "  ";
            for(k=i+1; k<fin; k++){
                os << normal << v[k] << "  ";
            }
        }else if(j==x){
            for(k=0; k<x; k++){
                os << normal << v[k] << "  ";
            }
            os << greenb << v[x] << "  ";
            for(k=j+1; k<i; k++){
                os << normal << v[k] << "  ";
            }
            os << redb << v[i] << "  ";
            for(k=i+1; k<fin; k++){
                os << normal << v[k] << "  ";
            }
        }
    }else if(i==j){
        if(i<x){
            for(k=ini; k<j; k++){
                os << normal << v[k] << "  ";
            }
            os << cyanb << v[j] << "  ";
            for(k=j+1; k<x; k++){
                os << normal << v[k] << "  ";
            }
            os << yellowb << v[x] << "  ";
            for(k=x+1; k<fin; k++){
                os << normal << v[k] << "  ";
            }
        }else if(i>x){
            for(k=ini; k<x; k++){
                os << normal << v[k] << "  ";
            }
            os << yellowb << v[x] << "  ";
            for(k=x+1; k<j; k++){
                os << normal << v[k] << "  ";
            }
            os << cyanb << v[j] << "  ";
            for(k=j+1; k<fin; k++){
                os << normal << v[k] << "  ";
            }
        }else if(i==x){
            for(k=ini; k<x; k++){
                os << normal << v[k] << "  ";
            }
            os << magentab << v[x] << "  ";
            for(k=x+1; k<fin; k++){
                os << normal << v[k] << "  ";
            }
        }
    }    
    os << normal;
}

#endif // VEC_H