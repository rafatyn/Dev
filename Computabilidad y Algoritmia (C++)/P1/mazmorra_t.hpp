#pragma once

#include <iostream>
#include "monstruo_t.hpp"

using namespace std;

class mazmorra_t {
  
  private:
  
    int xsup_;
    int ysup_;
    int xinf_;
    int yinf_;
    bool visible_;
    int xp1_;
    int yp1_;
    int xp2_;
    int yp2_;
    monstruo_t* monstruo_;
    int n_monstruos_;
    
  public:
  
    mazmorra_t(void);
    ~mazmorra_t(void);
    void set_mazmorra(int xsup, int ysup, int xinf, int yinf, bool visible, int xp1, int yp1, int xp2, int yp2, int n_monstruos);
    void set_nmonstruos(int x);
    int get_nmonstruos(void);
    void redimensionar_monstruos(void);
    void modificar_monstruo(int n, int x, int y);
    void mover_monstruos(int& vidas, int x, int y);    
    void pintar_mazmorra(char* map_, int m);
    bool dentro(int x, int y);
    void destruye_monstruos(void);
    void crea_monstruos(void);
    monstruo_t* get_monstruos(void);
    bool monstruo(int x, int y);
    bool pertenece(int x, int y);
    int pos(int i, int j, int m);
    void calcular_x(int x1, int x2, int x3);
    void calcular_y(int x1, int x2, int x3);
    int get_xsup(void);
    void set_xsup(int xsup);
    int get_ysup(void);
    void set_ysup(int ysup);
    int get_xinf(void);
    void set_xinf(int xinf);
    int get_yinf(void);
    void set_yinf(int yinf);
    bool get_visible(void);
    void set_visible(bool visible);
    int get_xp1(void);
    void set_xp1(int xp1);
    int get_yp1(void);
    void set_yp1(int yp1);
    int get_xp2(void);
    void set_xp2(int xp2);
    int get_yp2(void);
    void set_yp2(int yp2);
    
};