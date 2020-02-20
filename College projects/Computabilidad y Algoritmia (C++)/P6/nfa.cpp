#include "nfa.hpp"


NFA_t::NFA_t(void):
  estados_(),
  estado_inicial_(-1),
  alfabeto_()
  {}


NFA_t::NFA_t(set<state_t> estados, int estado_inicial, set<char> alfabeto):
  estados_(estados),
  estado_inicial_(estado_inicial),
  alfabeto_(alfabeto)
  {}

NFA_t::~NFA_t(void)
{}

int NFA_t::get_estado_inicial(void) const 
{
  
  return(estado_inicial_);
}

set<char> NFA_t::get_alfabeto(void) const 
{
  
  return(alfabeto_);
}

bool NFA_t::encontrado_alfabeto(char x) 
{
  
  if(x=='~')
    return(1);
  for(set<char>::iterator i=alfabeto_.begin(); i!=alfabeto_.end(); i++)
    if((*i)==x)
      return(1);
  return(0);
}
 
set<state_t> NFA_t::get_estados(void) const 
{
  
  return(estados_);
}

bool NFA_t::leer_fichero(char* fichero) 
{
  
  NFA_t nfa=(*this);
  ifstream textfile;
  textfile.open(fichero);
  if(textfile.is_open()) {
    
    if(!estados_.empty())
		  estados_.erase(estados_.begin(),estados_.end());
		if(!alfabeto_.empty())
		  alfabeto_.erase(alfabeto_.begin(),alfabeto_.end());
		  
    int n_estados_;
    int auxi;
    bool aux;
    char auxc;
    int id;
    textfile>>(int &) n_estados_;
    textfile>>(int &) estado_inicial_;
    for(int i=0; i<n_estados_; i++)
    {
      int sz;
      textfile>>(int &) id;
      textfile>>(bool &) aux>>(int &) sz;
      set<transition_state_t> transiciones;
      for(int j=0; j<sz; j++)
      {
        textfile>>(char &) auxc>>(int &) auxi;
        if(!encontrado_alfabeto(auxc))
          alfabeto_.insert(auxc);
        transition_state_t dummy(auxc,auxi);
        transiciones.insert(dummy);
      }
      state_t tmp(transiciones,aux,id);
      estados_.insert(tmp);
    }
    textfile.close();
  } else {
    
    cerr<<"Error de apertura ."<<endl;
    (*this)=nfa;
    return(0);
  }
  return(1);
}

void NFA_t::mostrar_estados_muerte(void)
{
  for(set<state_t>::iterator i=estados_.begin(); i!=estados_.end(); i++)
    if((*i).estado_muerte())
      cout<<"q"<<(*i).get_id()<<" es un estado de muerte."<<endl;
  cout<<"q"<<estados_.size()<<" es un estado de muerte."<<endl;
}

ostream& NFA_t::mostrar(ostream& os) const 
{
  
  os<<estados_.size()<<endl;
  os<<estado_inicial_<<endl;
  for(set<state_t>::iterator i=estados_.begin(); i!=estados_.end(); i++)
    (*i).mostrar(os)<<endl;
  return(os);
}

bool NFA_t::analizar_cadena(char* cadena) 
{
  set<state_t> tmp;
  tmp.insert(get_state(estado_inicial_));
  tmp=e_clausura(tmp);
  for(int b=0; cadena[b]!='\0'; b++)
    tmp=e_clausura(move(tmp, cadena[b]));
  for(set<state_t>::iterator x=tmp.begin(); x!=tmp.end(); x++)
    if((*x).aceptacion())
      return(1);
  return(0);
}


NFA_t& NFA_t::operator=(const NFA_t &x) 
{
  
  this->estados_=x.get_estados();
  this->estado_inicial_=x.get_estado_inicial();
  return(*this);
}

state_t NFA_t::get_state(const int x) const 
{
  
  for(set<state_t>::iterator i=estados_.begin(); i!=estados_.end(); i++)
   if((*i).get_id()==x)
     return(*i);
  cerr<<"Estado no encontrado."<<endl;
}

DFA_t NFA_t::convert2DFA(void) 
{
  
  int cont=0;
  vector<set<state_t> > estadosDFA;
  vector<set<transition_state_t> > tranDFA;
  {
    {
      set<state_t> tmp;
      tmp.insert(get_state(estado_inicial_));
      estadosDFA.push_back(e_clausura(tmp));
    }
    {
      set<transition_state_t> tmp;
      tranDFA.push_back(tmp);
    }
    
    for(int T=0; T<estadosDFA.size(); T++) {
      
      int cont=0;
      {
        for(set<char>::iterator i=alfabeto_.begin(); i!=alfabeto_.end(); i++)
        {
          set<state_t> H=e_clausura(move(estadosDFA[T], (*i)));
          bool baux=0;
          for(int j=0; j<estadosDFA.size()&&!baux; j++)
            if((estadosDFA[j].size()==H.size())&&equal(estadosDFA[j].begin(), estadosDFA[j].end(), H.begin()))
              baux=1;
          if(!baux) {
            
            if(H.size()) {  
              estadosDFA.push_back(H);
              {
                set<transition_state_t> dummy;
                tranDFA.push_back(dummy);
              }
            }
          }
          baux=0;
          for(int j=0; j<estadosDFA.size()&&!baux; j++) {        
            
            if(estadosDFA[j].size()==H.size()&&equal(estadosDFA[j].begin(), estadosDFA[j].end(), H.begin()))
            {
              baux=1;
              transition_state_t tmp((*i), j);
              tranDFA[T].insert(tmp);
            }
          }
        }
      }
    }
  }
  
  set<state_t> estadosDFA_final;
  for(int i=0; i<estadosDFA.size(); i++) {
    
    bool aceptacion=0;
    for(set<state_t>::iterator j=estadosDFA[i].begin(); j!=estadosDFA[i].end()&&!aceptacion; j++)
      if((*j).aceptacion())
        aceptacion=1;
    if(tranDFA[i].size())
    {
      state_t tmp(tranDFA[i], aceptacion, i);
      estadosDFA_final.insert(tmp);
      
    } else {
      set<transition_state_t> dummy;
      state_t tmp(dummy, aceptacion, i);
      estadosDFA_final.insert(tmp);
    }
  }
  DFA_t DFA(estadosDFA_final, 0, alfabeto_);
  return(DFA);
}


set<state_t> NFA_t::e_clausura(const set<state_t> &conjunto) 
{
  
  set<state_t> e_c, e_c_copia;
  
  for(set<state_t>::iterator i=conjunto.begin(); i!=conjunto.end(); i++) {
    
      set<state_t> tmp;
      set<int> aux=(*i).get_epsilon_clausura();
      
      for(set<int>::iterator j=aux.begin(); j!=aux.end(); j++)
        tmp.insert(get_state((*j)));
      set_union(e_c.begin(), e_c.end(), tmp.begin(), tmp.end(), inserter(e_c, e_c.begin()));
  }
  
  do {
    e_c_copia=e_c;
    for(set<state_t>::iterator i=e_c_copia.begin(); i!=e_c_copia.end(); i++) {
      set<state_t> tmp;
      set<int> aux=(*i).get_epsilon_clausura();
      for(set<int>::iterator j=aux.begin(); j!=aux.end(); j++)
        tmp.insert(get_state((*j)));
      set_union(e_c.begin(), e_c.end(), tmp.begin(), tmp.end(), inserter(e_c, e_c.begin()));
    }
  }
  
  while(e_c.size()!=e_c_copia.size());
  set_union(e_c.begin(), e_c.end(), conjunto.begin(), conjunto.end(), inserter(e_c, e_c.begin()));
  return(e_c);
}



set<state_t> NFA_t::move(const set<state_t> &T, char a) 
{
  
  set<state_t> mov;
  for(set<state_t>::iterator i=T.begin(); i!=T.end(); i++) {
    
    if((*i).reconocido(a)) {
      
      set<int> tmp=(*i).get_conjunto_transiciones(a);
      
      for(set<int>::iterator j=tmp.begin(); j!=tmp.end(); j++)
        mov.insert(get_state((*j)));
    }
  }
  return(mov);
}

ostream& operator<<(ostream &output, const NFA_t &x)
{
  return(x.mostrar(output));
}