#include "estado.hpp"

estado::estado(void):
transiciones(),
aceptacion(0),
id(-1)
{}

estado::estado(const estado &x)
{
    transiciones = x.get_transiciones();
    aceptacion = x.get_aceptacion();
    id = x.get_id();
}

estado::estado(set <transicion> transiciones_, bool aceptacion_, int id_)
{
    transiciones=transiciones_;
    aceptacion=aceptacion_;
    id=id_;
}

estado::~estado(void)
{}

bool estado::existe(char x) const
{
    for(set <transicion>::iterator i=transiciones.begin(); i!=transiciones.end(); i++){
        if((*i).existe(x)){
            return true;
        }
    }
    return false;
}

void estado::mostrar(void) const
{
    cout << "Estado: " << get_id() << " " << "Aceptacion: " << aceptacion << " " << "Numero transiciones: " << transiciones.size() << " ";
    for(set <transicion>::iterator i=transiciones.begin(); i!=transiciones.end(); i++){
        (*i).mostrar();
    }
}


bool estado::get_aceptacion(void) const
{
    return aceptacion;
}

int estado::estado_siguiente(char x) const
{
    for(set <transicion>::iterator i=transiciones.begin(); i!=transiciones.end(); i++){
        if((*i).existe(x)){
            return (*i).get_sig_estado();
        }
    }
    cout<<"Estado siguiente no reconocido"<<endl;
}

bool estado::estado_muerte(void) const
{
    int x=0;
    
    for(set <transicion>::iterator i=transiciones.begin(); i!=transiciones.end(); i++){
        if((*i).get_sig_estado()!=id){
            x++;
        }
    }
    if(x!=0||aceptacion==true){
        return false;
    }else{
        return true;
    }
}

int estado::get_id(void) const
{
    return id;
}

set <transicion> estado::get_transiciones(void) const
{
    return transiciones;
}

estado& estado::operator=(const estado &x)
{
    this->transiciones = x.get_transiciones();
    this->aceptacion = x.get_aceptacion();
    this->id = x.get_id();
    return(*this);
}

int estado::operator<(const estado &x) const
{
    if(id<x.get_id()){
        return 1;
    }else{
        return 0;
    }
}

ostream& operator<<(ostream &output, const estado &x)
{
    output << x.get_id() << " " << x.get_aceptacion() << " " << x.get_transiciones().size();
    for(set <transicion>::iterator i=x.get_transiciones().begin(); i!=x.get_transiciones().end(); i++){
        output << (*i);
    }
    return output;
}

bool estado::operator==(const estado &x) const
{
    
    if(this->id!=x.get_id())
        return 0;
    if(this->aceptacion!=x.get_aceptacion())
        return 0;
    if(!equal(transiciones.begin(),transiciones.end(),x.get_transiciones().begin()))
        return 0;
    return 1;
}
    