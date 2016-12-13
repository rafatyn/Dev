#include "Real.hpp"

real::real(void):
re(0)
{}


real::real(double r):
re(r)
{}

real::real(const real &r):
re(r.getr())
{}

real::~real(void){}


real& real::operator=(const real y)
{
    this->re=y.getr();

    return *this;
}


real real::operator+(const real y)
{
    real tmp;
    tmp.setr(this->getr()+y.getr());

    return tmp;
}


real real::operator-(const real y)
{
    real tmp;
    tmp.setr(this->getr()-y.getr());

    return tmp;
}


real real::operator*(const real y)
{
    real tmp;
    tmp.setr(this->getr()*y.getr());

    return tmp;
}


real real::operator/(const real y)
{
    try {
        
        if(this->getr()==0){
            throw 10;
        }
        real tmp;
        tmp.setr(this->getr()/y.getr());
    
        return tmp;
    }
    catch (int &e)
    {
        cerr << "Se esta realizando una división entre cero" << endl;
        
        throw 10;
    }
}

const entero real::toEntero(void) const
{
    try {
        int aux = (int) this->getr();
        entero tmp(aux);
    
        return tmp;
    }
    catch (exception& e)
    {
        cerr << "Excepción haciendo conversion: " << e.what() << endl;
        
        throw e;
    }
}


const rad real::toRacional(void) const
{
    try {
        rad tmp((int)this->getr(), 1);
    
        return tmp;
    }
    catch (exception& e)
    {
        cerr << "Excepción haciendo conversion: " << e.what() << endl;
        
        throw e;
    }
}

 
const real real::toReal(void) const
{
    return *this;
}

 
const complex real::toComplejo(void) const
{
    try {
        complex tmp((int)this->getr(), 0);
    
        return tmp;
    }
    catch (exception& e)
    {
        cerr << "Excepción haciendo conversion: " << e.what() << endl;
        
        throw e;
    }
}

 
ostream& real::toStream(ostream& os) const
{
    os << this->getr() << " ";

    return os;
}


istream& real::fromStream(istream& is)
{
    double aux;

    is >> aux;
    this->setr(aux);

    return is;
}
