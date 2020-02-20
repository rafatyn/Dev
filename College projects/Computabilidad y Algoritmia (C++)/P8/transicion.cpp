#include "transicion.hpp"

transicion::transicion(void):
entrada(0),
escribe(0),
movimiento(0),
sig_estado(0)
{}

transicion::transicion(const transicion &x)
{
    entrada = x.get_entrada();
    escribe = x.get_escribe();
    movimiento = x.get_movimiento();
    sig_estado = x.get_sig_estado();
}

transicion::transicion(char entrada_, char escribe_, short int movimiento_, int sig_estado_):
entrada(entrada_),
escribe(escribe_),
movimiento(movimiento_),
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

char transicion::get_escribe(void) const
{
    return escribe;
}

short int transicion::get_movimiento(void) const
{
    return movimiento;
}

int transicion::get_sig_estado(void) const
{
    return sig_estado;
}

void transicion::mostrar(void) const
{
    cout << "Entrada: " << entrada << " Escribe: " << escribe << " Movimiento: ";
    char mov;
    switch (movimiento){
        case -1:
            mov='L';
            break;
        case 1:
            mov='R';
            break;
        case 0:
            mov='S';
            break;
    }        
    cout << mov <<" Siguiente estado: " << sig_estado << " ";
}

transicion& transicion::operator =(const transicion &x)
{
    this->entrada = x.get_entrada();
    this->escribe = x.get_escribe();
    this->movimiento = x.get_movimiento();
    this->sig_estado = x.get_sig_estado();
    return(*this);
}

ostream& operator<<(ostream &output, const transicion &x)
{
    output << " " << x.get_entrada() << " " << x.get_escribe() << " " << x.get_movimiento() << " " << x.get_sig_estado();
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
      return 0;
    }    
    if(this->get_sig_estado()!=x.get_sig_estado()){
        return 0;
    }
    if(this->get_escribe()!=x.get_escribe()){
        return 0;
    }
    if(this->get_movimiento()!=x.get_movimiento()){
        return 0;
    }
    return 1;
}