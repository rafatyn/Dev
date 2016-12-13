#include "pasillo_t.hpp"

pasillo_t::pasillo_t(void):

    x_(NULL),
    y_(NULL),
    n_puntos_(0),
    visible_(0)
    {}

pasillo_t::~pasillo_t(void)
{
    destruye_pasillo();
}

void pasillo_t::redimensionar(void)
{
    destruye_pasillo();
    crear_pasillo();
}

void pasillo_t::destruye_pasillo(void)
{
    if(x_!=NULL)
    {
      delete [] x_;
      x_=NULL;
    }
    if(y_!=NULL)
    {
      delete [] y_;
      y_=NULL;
    }
}

bool pasillo_t::coincide(int x, int y)
{
  bool aux=0;
  for(int i=1; (i<n_puntos_)&&(aux == false); i++){
    if(x_[i-1]==x_[i]){
      if(y_[i-1]<y_[i]){
        aux = ((x ==x_[i])&&(y>= y_[i-1])&&(y<= y_[i]));
      }else{
        aux = ((x== x_[i])&&(y>= y_[i])&&(y<= y_[i-1]));
      }
    }else{
      if(x_[i-1]<x_[i]){
        aux = ((y== y_[i])&&(x>= x_[i-1])&&(x<= x_[i]));
      }else{
        aux = ((y== y_[i])&&(x>= x_[i])&&(x<= x_[i-1]));
      }
    }
  }
  return aux;
}

void pasillo_t::crear_pasillo(void)
{
    x_= new int [n_puntos_];
    y_= new int [n_puntos_];
    for(int i=0; i<n_puntos_; i++){
      x_[i]=-1;
      y_[i]=-1;
    }
}

int pasillo_t::get_x(int i)
{
    return x_[i];
}

int pasillo_t::get_y(int i)
{
    return y_[i];
}

void pasillo_t::set_x(int x, int i)
{
    x_[i]= x;
}

void pasillo_t::set_y(int y, int i)
{
    y_[i]= y;
}

void pasillo_t::set_visible(bool visible)
{
    visible_= visible;
}

bool pasillo_t::get_visible(void)
{
    return visible_;
}

int pasillo_t::pos(int i, int j, int m)
{
    return (i*m+j);
}

int pasillo_t::get_npuntos(void)
{
    return n_puntos_;
}

void pasillo_t::set_npuntos(int n_puntos)
{
    n_puntos_= n_puntos;
}

void pasillo_t::pintar_pasillo(char* map_, int m)
{
  if(visible_ == true){
    for(int i=1; i<n_puntos_; i++){
      if(x_[i-1]==x_[i]){
        if(y_[i-1]<y_[i]){
          for(int j=y_[i-1]; j<=y_[i]; j++){
            map_[pos(x_[i],j,m)] = '#';
          }
        }else{
          for(int j=y_[i]; j<=y_[i-1]; j++){
            map_[pos(x_[i],j,m)] = '#';
          }
        }
      }else{
        if(x_[i-1]<x_[i]){
          for(int j=x_[i-1]; j<=x_[i]; j++){
            map_[pos(j,y_[i],m)] = '#';
          }
        }else{
          for(int j=x_[i]; j<=x_[i-1]; j++){
            map_[pos(j,y_[i],m)] = '#';
          }
        }
      }
    }
  }
}