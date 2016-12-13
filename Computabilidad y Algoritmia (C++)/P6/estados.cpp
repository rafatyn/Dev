#include "estados.hpp"

state_t::state_t(void):
  transiciones_(),
  aceptacion_(0),
  ID_(-1)
  {}



state_t::state_t(const state_t &cp):                     
  transiciones_(cp.get_transiciones()),
  aceptacion_(cp.aceptacion()),
  ID_(cp.get_id())
  {}



state_t::~state_t(void)
{}



state_t::state_t(set<transition_state_t> transiciones, bool aceptacion, int id):
  transiciones_(transiciones),
  aceptacion_(aceptacion),
  ID_(id)
  {}


bool state_t::reconocido(char x) const {
  
  for(set <transition_state_t>::iterator i=transiciones_.begin(); i!=transiciones_.end(); i++)
    if((*i).reconocido(x))
      return(1);
  return(0);
}


int state_t::estado_siguiente(char x) const {
  
  for(set <transition_state_t>::iterator i=transiciones_.begin(); i!=transiciones_.end(); i++)
    if((*i).reconocido(x))
      return((*i).get_next_state());
  cerr<<"Estado siguiente no encontrado."<<endl;
  return(-1);
}


int state_t::get_id(void) const {
  
  return(ID_);
} 


set<int> state_t::get_conjunto_transiciones(char x) const {
  
  set<int> aux;
  for(set<transition_state_t>::iterator i=transiciones_.begin(); i!=transiciones_.end(); i++)
    if((*i).reconocido(x))
      aux.insert((*i).get_next_state());
  return(aux);
}


set<int> state_t::get_epsilon_clausura(void) const {
  
  set<int> aux;
  for(set<transition_state_t>::iterator i=transiciones_.begin(); i!=transiciones_.end(); i++)
    if((*i).reconocido('~'))
      aux.insert((*i).get_next_state());
  return(aux);
}


set<transition_state_t> state_t::get_transiciones(void) const {
  
  return(transiciones_);
}


state_t& state_t::operator=(const state_t &x) {
  
  this->transiciones_=x.get_transiciones();
  this->aceptacion_=x.aceptacion();
  this-> ID_=x.get_id();
   return (*this);
}


bool state_t::operator<(const state_t &x) const
{
  if(this->get_id() < x.get_id())
    return(1);
    
  return(0);
}


bool state_t::aceptacion(void) const {
  return(aceptacion_);
}


bool state_t::estado_muerte(void) const {
  
  if(aceptacion_)
    return(0);
  for(set <transition_state_t>::iterator i=transiciones_.begin(); i!=transiciones_.end(); i++)
    if((*i).get_next_state()!=get_id())
      return(0);
  return(1);
}


bool state_t::error(void) const {
  
  for(set <transition_state_t>::iterator i=transiciones_.begin();i!=transiciones_.end(); i++) {
    
    set <transition_state_t>::iterator j=i;
    j++;
    for(j; j!=transiciones_.end(); j++)
      if((*j).reconocido((*i).get_char()))
        return(1);
  }
  return(0);
}


ostream& state_t::mostrar(ostream& os) const {
  
  os<<get_id()<<" "<<aceptacion_<<" "<<transiciones_.size();
  for(set <transition_state_t>::iterator i=transiciones_.begin(); i!=transiciones_.end(); i++)
    (*i).mostrar(os);
  return(os);
}


bool state_t::operator==(const state_t &x) const {
  
  return(this->ID_==x.get_id());
}


ostream& operator<<(ostream &output, const state_t &x) {
  return(x.mostrar(output));
}
