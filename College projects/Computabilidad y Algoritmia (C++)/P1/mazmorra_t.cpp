#include "mazmorra_t.hpp"

mazmorra_t::mazmorra_t(void):

    xsup_(0),
    ysup_(0),
    xinf_(0),
    yinf_(0),
    visible_(0),
    xp1_(0),
    yp1_(0),
    xp2_(0),
    yp2_(0),
    monstruo_(),
    n_monstruos_(0)
    {}

void mazmorra_t::modificar_monstruo(int n, int x, int y)
{
    monstruo_[n].modificar(x,y);
}
void mazmorra_t::redimensionar_monstruos(void)
{
    destruye_monstruos();
    monstruo_= new monstruo_t [n_monstruos_];
}

void mazmorra_t::set_mazmorra(int xsup, int ysup, int xinf, int yinf, bool visible, int xp1, int yp1, int xp2, int yp2, int n_monstruos)
{
    xsup_= xsup;
    ysup_= ysup;
    xinf_= xinf;
    yinf_= yinf;
    visible_= visible;
    xp1_= xp1;
    yp1_= yp1;
    xp2_= xp2;
    yp2_= yp2;
    n_monstruos_= n_monstruos;
}

void mazmorra_t::mover_monstruos(int& vidas, int x, int y)
{
  bool aux;
  for(int i=0; i<n_monstruos_; i++){
    
    do{
      aux = false;
      
      switch(rand()%4){
        case 0:
        
        // Mover hacia la derecha, x++
        
          if(dentro(monstruo_[i].get_x()+1,monstruo_[i].get_y()) == true){
            for(int j=0; (j<i)&&(aux == false); j++){
              if((monstruo_[i].get_x()+1 == monstruo_[j].get_x())&&(monstruo_[i].get_y() == monstruo_[j].get_y())){
                aux = true;
              }
            }
            for(int j=i+1; (j<n_monstruos_)&&(aux == false); j++){
              if((monstruo_[i].get_x()+1 == monstruo_[j].get_x())&&(monstruo_[i].get_y() == monstruo_[j].get_y())){
                aux = true;
              }
            }
            if(aux == false){
              if((monstruo_[i].get_x()+1 == x)&&(monstruo_[i].get_y() == y)){
                aux = true;
                vidas--;
              }else{
                aux = true;
                monstruo_[i].set_x(monstruo_[i].get_x()+1);
              } 
            }
          }
          break;
        
        case 1:
        
        // Mover hacia la izquierda, x--
        
          if(dentro(monstruo_[i].get_x()-1,monstruo_[i].get_y()) == true){
            for(int j=0; (j<i)&&(aux == false); j++){
              if((monstruo_[i].get_x()-1 == monstruo_[j].get_x())&&(monstruo_[i].get_y() == monstruo_[j].get_y())){
                aux = true;
              }
            }
            for(int j=i+1; (j<n_monstruos_)&&(aux == false); j++){
              if((monstruo_[i].get_x()-1 == monstruo_[j].get_x())&&(monstruo_[i].get_y() == monstruo_[j].get_y())){
                aux = true;
              }
            }
            if(aux == false){
              if((monstruo_[i].get_x()-1 == x)&&(monstruo_[i].get_y() == y)){
                aux = true;
                vidas--;
            }else{
                aux = true;
                monstruo_[i].set_x(monstruo_[i].get_x()-1);
              } 
            }
          }
          break;
          
        case 2:
        
        // Mover hacia abajo, y++
        
          if(dentro(monstruo_[i].get_x(),monstruo_[i].get_y()+1))
          {
            for(int j=0; (j<i)&&(aux ==false); j++){
              if((monstruo_[i].get_x() == monstruo_[j].get_x())&&(monstruo_[i].get_y()+1 == monstruo_[j].get_y())){
                aux = true;
              }
            }
            for(int j=i+1; (j<n_monstruos_)&&(aux == false); j++){
              if((monstruo_[i].get_x() == monstruo_[j].get_x())&&(monstruo_[i].get_y()+1 == monstruo_[j].get_y())){
                aux = true;
              }
            }
            if(aux == false){
              if((monstruo_[i].get_x()+1 == x)&&(monstruo_[i].get_y()+1 == y)){
                aux = true;
                vidas--;
              }else{
                aux = true;
                monstruo_[i].set_y(monstruo_[i].get_y()+1);
              } 
            }
          }
          break;
          
        case 3:
        
        // Mover hacia rriba, y--
        
          if(dentro(monstruo_[i].get_x(),monstruo_[i].get_y()-1) == true){
            for(int j=0; (j<i)&&(aux == false); j++){
              if((monstruo_[i].get_x() == monstruo_[j].get_x())&&(monstruo_[i].get_y()-1 == monstruo_[j].get_y())){
                aux = true;
              }
            }
            for(int j=i+1; (j<n_monstruos_)&&(aux == false); j++){
              if((monstruo_[i].get_x() == monstruo_[j].get_x())&&(monstruo_[i].get_y()-1 == monstruo_[j].get_y())){
                aux = true;
              }
            }
            if(aux == false){
              if((monstruo_[i].get_x()-1 ==x )&&(monstruo_[i].get_y()-1 == y)){
                aux = true;
                vidas--;
              }else{
                aux = true;
                monstruo_[i].set_y(monstruo_[i].get_y()-1);
              } 
            } 
          }
          break;
          
        default: 
          
          break;
      }
    }while(aux == false);
    
    if(monstruo_[i].adyacente(x,y) == true){
      vidas--;
    }
  }
}

bool mazmorra_t::dentro(int x, int y)
{
    return ((x>xsup_)&&(x<xinf_)&&(y>ysup_)&&(y<yinf_));
}

monstruo_t* mazmorra_t::get_monstruos(void)
{
    return monstruo_;
}

bool mazmorra_t::monstruo(int x, int y)
{
    bool aux = false;
    for(int i=0; (i<n_monstruos_)&&(aux == false); i++){
      aux = monstruo_[i].coincide(x,y);
    }
    return aux;
}

void mazmorra_t::set_nmonstruos(int x)
{
    n_monstruos_ = x;
}

bool mazmorra_t::pertenece(int x, int y)
{
    return((x>=xsup_)&&(x<=xinf_)&&(y>=ysup_)&&(y<=yinf_));
}

int mazmorra_t::get_nmonstruos(void)
{
    return n_monstruos_;
}

void mazmorra_t::destruye_monstruos(void)
{
    if(monstruo_!=NULL)
    {
      delete [] monstruo_;
      monstruo_=NULL;
    }
}

void mazmorra_t::crea_monstruos(void)
{
  redimensionar_monstruos();
  bool aux;
  int cont;
  
  for(int i=0; (i<n_monstruos_)&&(cont!=10); i++)
  {
    monstruo_[i].situar_x(xinf_-1,xsup_+1);
    monstruo_[i].situar_y(yinf_-1,ysup_+1);
    cont=0;
    for(int j=i-1; (j>=0)&&(cont!=10); j=j-!aux){
      aux = monstruo_[j].coincide(monstruo_[i].get_x(),monstruo_[i].get_y());
      if(aux == true){
        monstruo_[i].situar_x(xinf_-1,xsup_+1);
        monstruo_[i].situar_y(yinf_-1,ysup_+1);
        cont++;
      }else{
        cont=0;
      }
    }
  }
  if(cont==10){
    cout << "Eror, cerrando programa." << endl;
    exit(0);
  }
}

mazmorra_t::~mazmorra_t(void)
{
    destruye_monstruos();
}

int mazmorra_t::pos(int i, int j, int m)
{
    return (i*m+j);
}

void mazmorra_t::calcular_x(int x1, int x2, int x3)
{
  do{
    xsup_= rand () % x1 + x2;
    xinf_= rand () % x1+x3+xsup_;
  }while(xinf_-xsup_<4);
}

void mazmorra_t::calcular_y(int x1, int x2, int x3)
{
  do{
    ysup_= rand () % x1 + x2;
    yinf_= rand () % x1+x3+ysup_;
  }while(yinf_-ysup_<4);
}

void mazmorra_t::pintar_mazmorra(char* map_, int m)
{
  if(visible_ == true){
    int xaux;
    int yaux;
    yaux = get_ysup();
    for(xaux = get_xsup(); xaux<=get_xinf(); xaux++){
      map_[pos(xaux,yaux,m)] = '*';
    }
    yaux++;    
    
    for(yaux; yaux<=get_yinf()-1; yaux++){
      xaux = get_xsup();
      map_[pos(xaux,yaux,m)] = '*';
      for(xaux=xaux+1; xaux<=get_xinf()-1; xaux++){
        map_[pos(xaux,yaux,m)] = '.';
      }
      map_[pos(xaux,yaux,m)] = '*';
    }
    
    for(xaux = get_xsup(); xaux<=get_xinf(); xaux++){
      map_[pos(xaux,yaux,m)] = '*';
    }
    map_[pos(get_xp1(),get_yp1(),m)] = '+';
    map_[pos(get_xp2(),get_yp2(),m)] = '+';
    for(int i=0; i<n_monstruos_; i++){
      monstruo_[i].pintar_monstruo(map_,m);
    }
  }
}

int mazmorra_t::get_xsup(void)
{
    return xsup_;
}

void mazmorra_t::set_xsup(int xsup)
{
    xsup_= xsup;
}

int mazmorra_t::get_ysup(void)
{
    return ysup_;
}

void mazmorra_t::set_ysup(int ysup)
{
    ysup_= ysup;
}

int mazmorra_t::get_xinf(void)
{
    return xinf_;
}

void mazmorra_t::set_xinf(int xinf)
{
    xinf_= xinf;
}

int mazmorra_t::get_yinf(void)
{
    return yinf_;
}

void mazmorra_t::set_yinf(int yinf)
{
    yinf_= yinf;
}

bool mazmorra_t::get_visible(void)
{
    return visible_;
}

void mazmorra_t::set_visible(bool visible)
{
    visible_= visible;
}

int mazmorra_t::get_xp1(void)
{
    return xp1_;
}

void mazmorra_t::set_xp1(int xp1)
{
    xp1_= xp1;
}

int mazmorra_t::get_yp1(void)
{
    return yp1_;
}

void mazmorra_t::set_yp1(int yp1)
{
    yp1_= yp1;
}

int mazmorra_t::get_xp2(void)
{
    return xp2_;
}


void mazmorra_t::set_xp2(int xp2)
{
    xp2_= xp2;
}

int mazmorra_t::get_yp2(void)
{
    return yp2_;
}

void mazmorra_t::set_yp2(int yp2)
{
    yp2_= yp2;
}
