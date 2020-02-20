#include "Vector.hpp"

vector::vector(void):
    sz(0),
    pepe(NULL)
    {}

vector::vector(int sz_):
    sz(sz_),
    pepe(NULL)
    {
        pepe = new dato [sz_];
        for(int i=0; i<sz; i++){
            pepe[i]='0';
        }
    }
    
vector::vector(vector& x)
{
    sz = x.getsz();
    pepe = new dato [sz];
    for(int i=0; i<sz; i++){
        pepe[i]=x.getdato(i);
    }
}

vector::~vector(void)
{
    if(pepe!=NULL){
        delete [] pepe;
        pepe = NULL;
    }
}

dato vector::getdato(int pos)
{
    return pepe[pos-1];
}

void vector::setdato(dato data, int pos)
{
    pepe[pos-1]=data;
}

int vector::getsz(void)
{
    return sz;
}

ostream& vector::write(ostream& os) const
{
    for(int i=0; i<sz; i++){
        os << pepe[i] << " ";
    }
    os << endl;
}
    
    