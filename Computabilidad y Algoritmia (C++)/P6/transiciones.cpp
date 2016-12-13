#include "transiciones.hpp"


transition_state_t::transition_state_t(void):
  caracter_(0),
  next_state_(-1)
  {}


transition_state_t::transition_state_t(const transition_state_t &cp):
  caracter_(cp.get_char()),
  next_state_(cp.get_next_state())
  {}


transition_state_t::transition_state_t(char caracter, int next_state):
  caracter_(caracter),
  next_state_(next_state)
  {}


transition_state_t::~transition_state_t(void)
{}



char transition_state_t::get_char(void) const {
  
  return(caracter_);
}


bool transition_state_t::reconocido(char x) const {
  
  return(caracter_==x);
}


int transition_state_t::get_next_state(void) const {
  
  return(next_state_);
}


ostream& transition_state_t::mostrar(ostream& os) const {
  
  os<<" "<<caracter_<<" "<<next_state_;
  return(os);
}


transition_state_t& transition_state_t::operator=(const transition_state_t &x) {
  
  this->caracter_= x.get_char();
  this->next_state_=x.get_next_state();
  return(*this);
}


bool transition_state_t::operator<(const transition_state_t &x) const {
  
  if(this->get_char()==x.get_char()&&this->get_next_state()<x.get_next_state())
    return(1);
  if(this->get_char()<x.get_char())
    return(1);
  return 0;
}


bool transition_state_t::operator==(const transition_state_t &x) const {
  
  if(this->get_char()!=x.get_char())
    return(0);
    
  if(this->get_next_state()!=x.get_next_state())
    return(0);
  return(1);
}


ostream& operator<<(ostream &output, const transition_state_t &x) {
  return(x.mostrar(output));
}    