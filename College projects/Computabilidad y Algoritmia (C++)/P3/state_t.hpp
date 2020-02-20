#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <sstream>

using namespace std;

#include "transition_state_t.hpp"

class state_t{
  private:
    set <transition_state_t> transiciones_;
    bool aceptacion_;
    int id;
  
  public:
    state_t(void);
    state_t(const state_t &);    
    state_t(set<transition_state_t> transiciones, bool aceptacion, int id_);    
    ~state_t(void);
    bool reconocido(char x) const; 
    void mostrar(void) const;  
    bool error(void) const;    
    int operator==(const int x) const;
    int estado_siguiente(char x) const;    
    set <transition_state_t> get_transiciones(void) const;    
    state_t& operator=(const state_t &x);
    int operator<(const state_t &x) const; 
    bool aceptacion(void) const;    
    bool estado_muerte(void) const;
    int get_id(void) const;
    
  private:
    friend ostream &operator<<(ostream &, const state_t &);
};
  
  