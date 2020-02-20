#pragma once

#include <cstdio>

using namespace std;

class pasillo_t{
  
  private:
  
    int* x_;
    int* y_;
    int n_puntos_;
    bool visible_;
    
  public:
  
    pasillo_t(void);
    ~pasillo_t(void);
    void redimensionar(void);
    bool coincide(int x, int y);
    void set_x(int x, int i);
    void set_y(int y, int i);
    int get_x(int i);
    int get_y(int i);
    void destruye_pasillo(void);
    void crear_pasillo(void);
    void set_visible(bool visible);
    bool get_visible(void);
    int pos(int i, int j, int m);
    int get_npuntos(void);
    void set_npuntos(int n_puntos);
    void pintar_pasillo(char* map_, int m); 
    
};