#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <set>
#include <iomanip>
#include "state_t.hpp"

using namespace std;


class DFA{
  private:
    set <state_t> estados;
    state_t estado_inicial;
  
  public:
    DFA(void);
    ~DFA(void);    
    int get_n_estados(void) const; 
    state_t get_inicial(void) const;    
    set<state_t> get_estados(void) const;
    void mostrar_estados_muerte(void);
    bool leer_fichero(void);
    void mostrar(void);
    void analizar_cadena(void);
    state_t get_state(int x);
  
  private:
    friend ostream &operator<<(ostream &, const DFA &);
};