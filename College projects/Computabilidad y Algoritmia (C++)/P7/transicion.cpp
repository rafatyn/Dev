#include "transicion.hpp"

transicion::transicion(void):
entrada(0),
sig_estado(0)
{}

transicion::transicion(const transicion &x)
{
    entrada = x.get_entrada();
    sig_estado = x.get_sig_estado();
}

transicion::transicion(char entrada_, int sig_estado_):
entrada(entrada_),
sig_estado(sig_estado_)
{}

transicion::~transicion(void)
{}

bool transicion::existe(char x) const
{
    if(x==entrada){
        return true;
    }else{
        return false;
    }
}

char transicion::get_entrada(void) const
{
    return entrada;
}

int transicion::get_sig_estado(void) const
{
    return sig_estado;
}

void transicion::mostrar(void) const
{
    cout << "Entrada: " << entrada << " " << "Siguiente estado: " << sig_estado << " ";
}

transicion& transicion::operator =(const transicion &x)
{
    this->entrada = x.get_entrada();
    this->sig_estado = x.get_sig_estado();
    return(*this);
}

ostream& operator<<(ostream &output, const transicion &x)
{
    output << " " << x.get_entrada() << " " << x.get_sig_estado();
    return output;
}

int transicion::operator<(const transicion &x) const
{
    if((entrada == x.get_entrada()&&sig_estado < x.get_sig_estado())||(entrada < x.get_entrada())){
        return 1;
    }else{
        return 0;
    }
}

bool transicion::operator==(const transicion &x) const
{
    if(this->get_entrada()!=x.get_entrada()){
      return(0);
    }    
    if(this->get_sig_estado()!=x.get_sig_estado()){
        return(0);
    }
    return(1);
}