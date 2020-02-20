#include <cstdio>
#include <iostream>

using namespace std;

template<class T>
class complex {
    
    private: 
    
        T real;
        T imaginario;
    
    public:
    
        complex(void);
        complex(T r, T i);
        ~complex(void);
        T getr(void) {return real;}
        T geti(void) {return imaginario;}
        T getr(void) const {return real;}
        T geti(void) const {return imaginario;}
        void setr(T r) {real = r;}
        void seti(T i) {imaginario = i;}
        complex& operator=(const complex<T> y);
        complex operator+(const complex<T> y);
        complex operator-(const complex<T> y);
        complex operator*(const complex<T> y);
        complex operator/(const complex<T> y);
};

template<class T>
complex<T>::complex(void):
real(0),
imaginario(0)
{}

template<class T>
complex<T>::complex(T r, T i):
real(r),
imaginario(i)
{}

template<class T>
complex<T>::~complex(void){}
    
template<class T>
complex<T>& complex<T>::operator=(const complex<T> y)
{
    this->real=y.getr();
    this->imaginario=y.geti();
    
    return *this;
}

template<class T>
complex<T> complex<T>::operator+(const complex<T> y)
{
    complex<T> tmp;
    tmp.setr(this->getr()+y.getr());
    tmp.seti(this->geti()+y.geti());
    
    return tmp;
}

template<class T>
complex<T> complex<T>::operator-(const complex<T> y)
{
    complex<T> tmp;
    tmp.setr(this->getr()-y.getr());
    tmp.seti(this->geti()-y.geti());
    
    return tmp;
}

template<class T>
complex<T> complex<T>::operator*(const complex<T> y)
{
    complex<T> tmp;
    tmp.setr((this->getr()*y.getr())-(this->geti()*y.geti()));  
    tmp.seti((this->getr()*y.geti())+(this->geti()*y.getr()));   
    
    return tmp;
}

template<class T>
complex<T> complex<T>::operator/(const complex<T> y)
{
    complex<T> tmp;
    tmp.setr(((this->getr()*y.getr())+(this->geti()*y.geti()))/((y.getr()*y.getr())+(y.geti()*y.geti())));  
    tmp.seti(((this->geti()*y.getr())-(this->getr()*y.geti()))/((y.getr()*y.getr())+(y.geti()*y.geti()))); 
    
    return tmp;
}

template<class T>
ostream& operator<<(ostream& os, const complex<T>& y)
{
    os << y.getr() << " + " << y.geti() << "i";
    
    return os;
}