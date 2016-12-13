#include "Entero.hpp"

entero::entero(void):
ent(0)
{}


entero::entero(int e):
ent(e)
{}

entero::entero(const entero &e):
ent(e.gete())
{}

entero::~entero(void){}


entero& entero::operator=(const entero y)
{
    this->ent=y.gete();

    return *this;
}


entero entero::operator+(const entero y)
{
    entero tmp(this->gete()+y.gete());

    return tmp;
}


entero entero::operator-(const entero y)
{
    entero tmp;
    tmp.sete(this->gete()-y.gete());

    return tmp;
}


entero entero::operator*(const entero y)
{
    entero tmp;
    tmp.sete(this->gete()*y.gete());

    return tmp;
}


entero entero::operator/(const entero y)
{
    try {
            
        entero tmp;
        
        if(y.gete()==0){
            throw 10;
        }
        
        tmp.sete(this->gete()/y.gete());
    
        return tmp;
    }
    catch (int &e)
    {
        cerr << "Se esta realizando una división entre cero" << endl;
        
        throw 10;
    }
}

const entero entero::toEntero(void) const
{
    return *this;
}


const rad entero::toRacional(void) const
{
    rad tmp(this->gete(), 1);

    return tmp;
}

 
const real entero::toReal(void) const
{
    try {
        double aux = (double) this->gete();
        real tmp(aux);
    
        return tmp;
    }
    catch (exception& e)
    {
        cerr << "Excepción haciendo conversion: " << e.what() << endl;
        
        throw e;
    }
}

 
const complex entero::toComplejo(void) const
{
    complex tmp(this->gete(), 0);

    return tmp;
}

 
ostream& entero::toStream(ostream& os) const
{
    os << this->gete() << " ";

    return os;
}


istream& entero::fromStream(istream& is)
{
    int aux;

    is >> aux;
    this->sete(aux);

    return is;
}
