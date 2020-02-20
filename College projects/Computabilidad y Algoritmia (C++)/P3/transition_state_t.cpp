#include "transition_state_t.hpp"

transition_state_t::transition_state_t(void):
  entrada(0),
  sig_estado(0)
  {}

transition_state_t::transition_state_t(char entrada_, int sig_estado_):
  entrada(entrada_),
  sig_estado(sig_estado_)
  {}

transition_state_t::transition_state_t(const transition_state_t &cp)
{
  this->entrada = cp.get_char();
  this->sig_estado = cp.get_next_state();
}

char transition_state_t::get_char(void) const
{
  return entrada;
}

transition_state_t::~transition_state_t(void)
{}

bool transition_state_t::reconocido(char x) const
{
  return (entrada==x);
}

int transition_state_t::get_next_state(void) const
{
  return sig_estado;
}

void transition_state_t::mostrar(void) const
{
  cout << " Entrada: " << entrada << " Siguiente estado: " << sig_estado;
}

transition_state_t& transition_state_t::operator=(const transition_state_t &x)
{
  this->entrada = x.get_char();
  this->sig_estado =x.get_next_state();
  return(*this);
}

ostream& operator<<(ostream &output, const transition_state_t &x)
{
  output << " " << x.get_char() << " " << x.get_next_state();
  return(output);
}

int transition_state_t::operator<(const transition_state_t &x) const
{
  if(this->get_char() < x.get_char())
    return(1);
  if(this->get_char() > x.get_char())
    return(0);
  return(0);
}
    
    
    