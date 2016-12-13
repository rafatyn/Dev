#include "state_t.hpp"

state_t::state_t(void):
  transiciones_(),
  aceptacion_(0),
  id(0)
  {}

state_t::state_t(const state_t &cp):                       
  transiciones_(cp.get_transiciones()),
  aceptacion_(cp.aceptacion()),
  id(cp.get_id())
  {}

state_t& state_t::operator=(const state_t &x)
{
  this->transiciones_ = x.get_transiciones();
  this->aceptacion_ = x.aceptacion();
  this-> id=x.get_id();
   return (*this);
}

set<transition_state_t> state_t::get_transiciones(void) const
{
  return(transiciones_);
}

state_t::state_t(set<transition_state_t> transiciones, bool aceptacion, int id):
  transiciones_(transiciones),
  aceptacion_(aceptacion),
  id(id)
  {}

state_t::~state_t(void)
{}

bool state_t::aceptacion(void) const
{
  return(aceptacion_);
}

bool state_t::estado_muerte(void) const
{
  if(aceptacion_)
    return(0);
  for(set <transition_state_t>::iterator i=transiciones_.begin(); i!=transiciones_.end(); i++)
    if((*i).get_next_state()!=get_id())
      return(0);
  return(1);
}

bool state_t::reconocido(char x) const
{
  for(set <transition_state_t>::iterator i=transiciones_.begin(); i!=transiciones_.end(); i++)
    if((*i).reconocido(x))
      return(1);
  return(0);
}

void state_t::mostrar(void) const
{
  cout<<"Estado: "<<get_id()<<" Aceptacion: "<<aceptacion_<<" Numero transiciones: "<<transiciones_.size();
  for(set <transition_state_t>::iterator i=transiciones_.begin(); i!=transiciones_.end(); i++)
    (*i).mostrar();
}

int state_t::estado_siguiente(char x) const
{
  for(set <transition_state_t>::iterator i=transiciones_.begin(); i!=transiciones_.end(); i++)
    if((*i).reconocido(x))
      return((*i).get_next_state());
  cout<<"Estado siguiente no reconocido"<<endl;
}

int state_t::get_id(void) const
{
  return(id);
} 

int state_t::operator==(const int x) const
{
   if( this->get_id() != x) return 0;
   return 1;
}

ostream& operator<<(ostream &output, const state_t &x)
{
  output<<x.get_id()<<" "<<x.aceptacion()<<" "<<x.get_transiciones().size();
  for(set <transition_state_t>::iterator i=x.get_transiciones().begin(); i!=x.get_transiciones().end(); i++)
    output<<(*i);
  return(output);
}

int state_t::operator<(const state_t &x) const
{
  if(this->get_id() < x.get_id())
    return(1);
  return(0);
}