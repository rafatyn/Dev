#include <cstdio>
#include <iostream>

using namespace std;

template<class T>
class rad {
    
    private: 
    
        T num;
        T dem;
    
    public:
    
        rad(void);
        rad(T n, T d);
        ~rad(void);
        T getn(void) {return num;}
        T getd(void) {return dem;}
        T getn(void) const {return num;}
        T getd(void) const {return dem;}
        void setn(T n) {num = n;}
        void setd(T d) {dem = d;}
        rad& operator=(const rad<T> y);
        rad operator+(const rad<T> y);
        rad operator-(const rad<T> y);
        rad operator*(const rad<T> y);
        rad operator/(const rad<T> y);
};

template<class T>
rad<T>::rad(void):
num(0),
dem(0)
{}

template<class T>
rad<T>::rad(T n, T d):
num(n),
dem(d)
{}

template<class T>
rad<T>::~rad(void){}
    
template<class T>
rad<T>& rad<T>::operator=(const rad<T> y)
{
    this->num=y.getn();
    this->dem=y.getd();
    
    return *this;
}

template<class T>
rad<T> rad<T>::operator+(const rad<T> y)
{
    rad<T> tmp;
    tmp.setd(this->dem*y.getd());
    tmp.setn((y.getd()*this->num)+(this->dem*y.getn()));
    
    return tmp;
}

template<class T>
rad<T> rad<T>::operator-(const rad<T> y)
{
    rad<T> tmp;
    tmp.setd(this->dem*y.getd());
    tmp.setn((y.getd()*this->num)-(this->dem*y.getn()));
    
    return tmp;
}

template<class T>
rad<T> rad<T>::operator*(const rad<T> y)
{
    rad<T> tmp;
    tmp.setd(this->dem*y.getd());
    tmp.setn(this->num*y.getn());   
    
    return tmp;
}

template<class T>
rad<T> rad<T>::operator/(const rad<T> y)
{
    rad<T> tmp;
    tmp.setd(this->dem*y.getn());
    tmp.setn(this->num*y.getd());   
    
    return tmp;
}

template<class T>
ostream& operator<<(ostream& os, const rad<T>& y)
{
    if(y.getd()!=0){
        os << y.getn() << "/" << y.getd();
    }else{
        os << "Infinito";
    }
    return os;
}
