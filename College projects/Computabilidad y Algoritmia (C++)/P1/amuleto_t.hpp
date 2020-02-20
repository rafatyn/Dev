#pragma once

#include "mazmorra_t.hpp"

using namespace std;

class amuleto_t{
  
  private:
  
    int x_;
    int y_;
    bool pillado_;
    
  public:
  
    amuleto_t(void);
    void modificar(int x, int y, bool pillado);
    ~amuleto_t(void);
    int get_x(void);
    void set_x(int x);
    int get_y(void);
    void set_y(int y);
    bool& get_set_pillado(void);
    bool get_pillado(void);
    void set_pillado(bool pillado);
    void mostrar(char* map_, int m, mazmorra_t* mazmorra, int n_mazmorras);
    
};