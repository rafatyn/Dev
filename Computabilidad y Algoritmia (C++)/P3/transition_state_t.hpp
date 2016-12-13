#pragma once

#include <iostream>
#include <vector>

using namespace std;

class transition_state_t{
  private:
    char entrada;
    int sig_estado;
  
  public:
    transition_state_t(void);
    transition_state_t(const transition_state_t &cp);
    transition_state_t(char entrada_, int sig_estado_);
    ~transition_state_t(void);
    bool reconocido(char x) const;
    char get_char(void) const;   
    int get_next_state(void) const;
    void mostrar(void) const;    
    transition_state_t& operator=(const transition_state_t &x);
    int operator<(const transition_state_t &x) const;
  
  private:
    friend ostream &operator<<(ostream &, const transition_state_t &);
};

