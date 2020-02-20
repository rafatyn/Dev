#pragma once

#include "mazmorra_t.hpp"
#include "pasillo_t.hpp"
#include "amuleto_t.hpp"

using namespace std;

class jugador_t{
  
  private:
  
    int x_;
    int y_;
    int vidas_;
    bool amuleto_;
    int sx_;
    int sy_;
    
  public:
  
    jugador_t(void);
    jugador_t(int x, int y, int vidas, bool amuleto);
    ~jugador_t(void);
    bool ganar(void);
    bool perder(void);
    int& get_set_vidas(void);    
    int get_sx(void);
    void set_sx(int sx);
    int get_sy(void);
    void set_sy(int sy);
    int get_x(void);
    void set_x(int x);
    int get_y(void);
    void set_y(int y);
    int get_vidas(void);
    void set_vidas(int vidas);
    bool get_amuleto(void);
    void modificar(int x, int y, int vidas, bool amuleto, int sx, int sy);
    void mover(mazmorra_t* mazmorra, int n_mazmorras, pasillo_t* pasillo, int n_pasillos_, int xa, int ya, bool& pillado);
    int pos(int i, int j, int m);
    void pintar(char* map_, int m,mazmorra_t* mazmorra,int n_mazmorras);
      
};