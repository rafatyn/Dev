#include "amuleto_t.hpp"

amuleto_t::amuleto_t(void):
 
  x_(0),
  y_(0),
  pillado_(false)
 
  {}

void amuleto_t::modificar(int x, int y, bool pillado)
{
    x_ = x;
    y_ = y;
    pillado_ = pillado;
}

amuleto_t::~amuleto_t(void)
{}

int amuleto_t::get_x(void)
{
    return x_;
}

void amuleto_t::set_x(int x)
{
    x_ = x;
}

int amuleto_t::get_y(void)
{
    return y_;
}

void amuleto_t::set_y(int y)
{
    y_ = y;
}

bool& amuleto_t::get_set_pillado(void)
{
    return pillado_;
}

bool amuleto_t::get_pillado(void)
{
    return pillado_;
}

void amuleto_t::set_pillado(bool pillado)
{
    pillado_ = pillado;
}

void amuleto_t::mostrar(char* map_, int m, mazmorra_t* mazmorra, int n_mazmorras)
{
  
  bool dentro = false;
  
  if(pillado_ == false){
    
    for(int i=0; (i<n_mazmorras)&&(dentro == false); i++){
      
      if(mazmorra[i].dentro(x_,y_) == true){
        
        dentro = true;
        
        if((mazmorra[i].monstruo(x_,y_) == false)&&(mazmorra[i].get_visible() == true))
          map_[x_*m+y_] = '&';
      }
    }
  }
}