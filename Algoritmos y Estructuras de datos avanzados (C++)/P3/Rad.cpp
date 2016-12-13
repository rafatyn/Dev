#include "Rad.hpp"

rad::rad(void):
num(0),
dem(1)
{}


rad::rad(int n, int d):
num(n),
dem(d)
{}

rad::rad(const rad &d):
num(d.getn()),
dem(d.getd())
{}

rad::~rad(void){}


rad& rad::operator=(const rad y)
{
    this->num=y.getn();
    this->dem=y.getd();

    return *this;
}


rad rad::operator+(const rad y)
{
    rad tmp;
    tmp.setd(this->dem*y.getd());
    tmp.setn((y.getd()*this->num)+(this->dem*y.getn()));

    return tmp;
}


rad rad::operator-(const rad y)
{
    rad tmp;
    tmp.setd(this->dem*y.getd());
    tmp.setn((y.getd()*this->num)-(this->dem*y.getn()));

    return tmp;
}


rad rad::operator*(const rad y)
{
    rad tmp;
    tmp.setd(this->dem*y.getd());
    tmp.setn(this->num*y.getn());

    return tmp;
}


rad rad::operator/(const rad y)
{
    rad tmp;
    tmp.setd(this->dem*y.getn());
    tmp.setn(this->num*y.getd());

    return tmp;
}


const entero rad::toEntero(void) const
{
    try {
        
        if(this->getd()==0){
            throw 10;
        }
        
        int aux = (int) this->getn()/this->getd();
        entero tmp(aux);
    
        return tmp;
    }
    catch (int &e)
    {
        cerr << "Se esta realizando una división entre cero" << endl;
        
        throw 10;
    }
    catch (exception& e)
    {
        cerr << "Excepción haciendo conversion: " << e.what() << endl;
        
        throw e;
    }
}


const rad rad::toRacional(void) const
{
    return *this;
}

 
const real rad::toReal(void) const
{
    try {
        
        if(this->getd()==0){
            throw 10;
        }    
        
        double aux = (double) this->getn()/this->getd();
        real tmp(aux);
    
        return tmp;
    }
    catch (int &e)
    {
        cerr << "Se esta realizando una división entre cero" << endl;
        
        throw 10;
    }
    catch (exception& e)
    {
        cerr << "Excepción haciendo conversion: " << e.what() << endl;
        
        throw e;
    }
}

 
const complex rad::toComplejo(void) const
{
    try {
        
        if(this->getd()==0){
            throw 10;
        }
        complex tmp(this->getn()/this->getd(), 0);
    
        return tmp;
    }
    catch (int &e)
    {
        cerr << "Se esta realizando una división entre cero" << endl;
        
        throw 10;
    }
}

 
ostream& rad::toStream(ostream& os) const
{
    os << this->getn() << "/" << this->getd() << " ";

    return os;
}


istream& rad::fromStream(istream& is)
{
    int aux1, aux2;

    is >> aux1 >> aux2;
    this->setn(aux1);
    this->setd(aux2);

    return is;
}
