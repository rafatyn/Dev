#include "dfa.hpp"

DFA_t::DFA_t(void):
  estados_(),
  estado_inicial_(-1),
  alfabeto_()
  {}



DFA_t::DFA_t(set<state_t> estados, int estado_inicial, set<char> alfabeto):
  estados_(estados),
  estado_inicial_(estado_inicial),
  alfabeto_(alfabeto)
  {}



DFA_t::~DFA_t(void)
{}



int DFA_t::get_estado_inicial(void) const 
{
  
  return(estado_inicial_);
}



set<state_t> DFA_t::get_estados(void) const 
{
  
  return(estados_);
}


ostream& DFA_t::mostrar(ostream& os) const 
{
  
  os<<estados_.size()<<endl;
  os<<estado_inicial_<<endl;
  for(set<state_t>::iterator i=estados_.begin(); i!=estados_.end(); i++)
    (*i).mostrar(os)<<endl;
  return(os);
}


void DFA_t::mostrar_estados_muerte(void) 
{
  
  for(set<state_t>::iterator i=estados_.begin(); i!=estados_.end(); i++)
    if((*i).estado_muerte())
      cout<<"q"<<(*i).get_id()<<" es un estado de muerte."<<endl;
  cout<<"q"<<estados_.size()<<" es un estado de muerte."<<endl;
}


bool DFA_t::analizar_cadena(char* cadena) 
{
  state_t aux;
  bool reconocido=1;
  if(cadena[0]!='~'){
  aux=get_state(estado_inicial_);
  
  for(int i=0; cadena[i]!='\0'&&reconocido ; i++)
    if(reconocido=aux.reconocido(cadena[i]))
        aux=get_state(aux.estado_siguiente(cadena[i]));
  }else{
    aux=get_state(estado_inicial_);
  }
  return(aux.aceptacion()&&reconocido);
}



bool DFA_t::leer_fichero(char* fichero)
{
  
  DFA_t dfa=(*this);
  ifstream textfile;
  textfile.open(fichero);
  if (textfile.is_open()) {
    
    if(!estados_.empty())
		  estados_.erase(estados_.begin(),estados_.end());
		if(!alfabeto_.empty())
		  alfabeto_.erase(alfabeto_.begin(),alfabeto_.end());
		  
    int n_estados_;
    int auxi;
    bool aux;
    char auxc;
    int id;
    
    textfile>>(int &) auxi;
    n_estados_=auxi;
    textfile>>(int &) estado_inicial_;
    for(int i=0; i<n_estados_; i++) {
      
      int sz;
      textfile>>(int &) id;
      textfile>>(bool &) aux>>(int &) auxi;
      sz=auxi;
      set<transition_state_t> transiciones;
      
      for(int j=0; j<sz; j++) {
        textfile>>(char &) auxc>>(int &) auxi;
        if(!encontrado_alfabeto(auxc))
          alfabeto_.insert(auxc);
        transition_state_t dummy(auxc,auxi);
        transiciones.insert(dummy);
      }
      
      state_t tmp(transiciones,aux,id);
      estados_.insert(tmp);
      if(tmp.error())  {
        cerr<<"Error en las transiciones."<<endl;
        (*this)=dfa;
        return(0);
      }
    }
    textfile.close();
    
  } else  {
    
    cerr<<"Error de apertura"<<endl;
    (*this)=dfa;
    return(0);
  }
  return(1);
}



bool DFA_t::encontrado_alfabeto(char x) 
{
  
  for(set<char>::iterator i=alfabeto_.begin(); i!=alfabeto_.end(); i++)
    if((*i)==x)
      return(1);
  return(0);
}



DFA_t& DFA_t::operator=(const DFA_t &x) 
{
  
  this->estados_=x.get_estados();
  this->estado_inicial_=x.get_estado_inicial();
  this->alfabeto_=x.get_alfabeto();
  return(*this);
}



set<char> DFA_t::get_alfabeto(void) const 
{
  
  return(alfabeto_);
}



ostream& operator<<(ostream &os, const DFA_t &x) 
{
  
  return(x.mostrar(os));
}



state_t DFA_t::get_state(int x) 
{
  
  if(x<estados_.size())
    for(set<state_t>::iterator i=estados_.begin(); i!=estados_.end(); i++)
      if((*i).get_id()==x)
        return(*i);
        
  cerr<<"Estado no encontrado."<<endl;
}



