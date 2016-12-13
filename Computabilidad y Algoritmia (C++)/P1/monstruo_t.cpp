#include "monstruo_t.hpp"

monstruo_t::monstruo_t(void):
    x_(0),
    y_(0)
    {}

monstruo_t::monstruo_t(int x, int y, int vidas):
    x_(x),
    y_(y)
    {}

bool monstruo_t::adyacente(int x, int y)
{
    if(((x==x_-1)&&(y_==y))||((x==x_+1)&&(y_==y))||((x==x_)&&(y_-1==y))||((x==x_)&&(y_+1==y))){
      return true;
    }else{
      return false;
    }
  }

void monstruo_t::situar_x(int xi, int xs)
{
    x_= rand () % (xi-xs) + xs;
}

void monstruo_t::situar_y(int yi, int ys)
{
    y_= rand () % (yi-ys) + ys;
}

bool monstruo_t::coincide(int x, int y)
{
    if((x_== x)&&(y_== y)){
      return true;
    }else{
      return false;
    }
}

int monstruo_t::pos(int i, int j, int m)
{
    return (i*m+j);
}

void monstruo_t::pintar_monstruo(char* map_, int m)
{
    map_[pos(x_,y_,m)] = 'O';
}

void monstruo_t::modificar(int x, int y)
{
    x_= x;
    y_= y;
}

monstruo_t::~monstruo_t(void)
{}

int monstruo_t::get_x(void)
{
    return x_;
}

void monstruo_t::set_x(int x)
{
    x_= x;
}

int monstruo_t::get_y(void)
{
    return y_;
}
void monstruo_t::set_y(int y)
{
    y_= y;
}