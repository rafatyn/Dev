#include "Complex.hpp"

complex::complex(void):
rel(0),
imaginario(0)
{}


complex::complex(int r, int i):
rel(r),
imaginario(i)
{}

complex::complex(const complex &c):
rel(c.getr()),
imaginario(c.geti())
{}

complex::~complex(void){}


complex& complex::operator=(const complex y)
{
    this->rel=y.getr();
    this->imaginario=y.geti();

    return *this;
}


complex complex::operator+(const complex y)
{
    complex tmp;
    tmp.setr(this->getr()+y.getr());
    tmp.seti(this->geti()+y.geti());

    return tmp;
}


complex complex::operator-(const complex y)
{
    complex tmp;
    tmp.setr(this->getr()-y.getr());
    tmp.seti(this->geti()-y.geti());

    return tmp;
}


complex complex::operator*(const complex y)
{
    complex tmp;
    tmp.setr((this->getr()*y.getr())-(this->geti()*y.geti()));
    tmp.seti((this->getr()*y.geti())+(this->geti()*y.getr()));

    return tmp;
}


complex complex::operator/(const complex y)
{
    try {
        complex tmp;
        
        if(((y.getr()*y.getr())+(y.geti()*y.geti()))==0){
            throw 10;
        }
        
        tmp.setr(((this->getr()*y.getr())+(this->geti()*y.geti()))/((y.getr()*y.getr())+(y.geti()*y.geti())));
        tmp.seti(((this->geti()*y.getr())-(this->getr()*y.geti()))/((y.getr()*y.getr())+(y.geti()*y.geti())));
            
        return tmp;
    }
    catch (int &e)
    {
        cerr << "Se esta realizando una división entre cero" << endl;
        
        throw 10;
    }
}


const entero complex::toEntero(void) const
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


const rad complex::toRacional(void) const
{
    rad tmp(this->getr(), 1);

    return tmp;
}

 
const real complex::toReal(void) const
{
    try {
        double aux = (double) this->getr();
        real tmp(aux);
    
        return tmp;
    }
    catch (exception& e)
    {
        cerr << "Excepción haciendo conversion: " << e.what() << endl;
        
        throw e;
    }
}

 
const complex complex::toComplejo(void) const
{
    return *this;
}

 
ostream& complex::toStream(ostream& os) const
{
    os << this->getr() << " + " << this->geti() << "i ";

    return os;
}


istream& complex::fromStream(istream& is)
{
    int aux1, aux2;

    is >> aux1 >> aux2;
    this->setr(aux1);
    this->seti(aux2);

    return is;
}
