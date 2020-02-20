#pragma once

#include <cstdio>
#include <cstdlib>

using namespace std;

class monstruo_t{
  
  private:
  
    int x_;
    int y_;
    int vidas_;
    
  public:
  
    monstruo_t(void);
    monstruo_t(int x, int y, int vidas);
    ~monstruo_t(void);
    int pos(int i, int j, int m);
    void pintar_monstruo(char* map_, int m);
    bool coincide(int x, int y);
    void situar_y(int yi, int ys);
    void situar_x(int xi, int xs);
    bool adyacente(int x, int y);
    void modificar(int x, int y);
    int get_x(void);
    void set_x(int x);
    int get_y(void);
    void set_y(int y);
    int get_vidas(void);
    void set_vidas(int vidas);
    
};