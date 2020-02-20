#include "jugador_t.hpp"

jugador_t::jugador_t(void):
  
    x_(0),
    y_(0),
    vidas_(5),
    amuleto_(0),
    sx_(0),
    sy_(0)
    {}

jugador_t::jugador_t(int x, int y, int vidas, bool amuleto):
    
    x_(x),
    y_(y),
    vidas_(vidas),
    amuleto_(amuleto)
    {}

jugador_t::~jugador_t(void)
{}

bool jugador_t::ganar(void)
{
    if((x_== sx_)&&(y_== sy_)&&(amuleto_== true)){
      return true;
    }else{
      return false;
    }
}

bool jugador_t::perder(void)
{
    if(vidas_< 0){
      return true;
    }else{
      return false;
    }
}

int& jugador_t::get_set_vidas(void)
{
    return vidas_;
}

int jugador_t::get_sx(void)
{
    return sx_;
}

void jugador_t::set_sx(int sx)
{
    sx_= sx;
}

int jugador_t::get_sy(void)
{
    return sy_;
}

void jugador_t::set_sy(int sy)
{
    sy_= sy;
}

int jugador_t::get_x(void)
{
  return x_;
}

void jugador_t::set_x(int x)
{
  x_= x;
}

int jugador_t::get_y(void)
{
  return y_;
}

void jugador_t::set_y(int y)
{
  y_= y;
}

int jugador_t::get_vidas(void)
{
  return vidas_;
}

void jugador_t::set_vidas(int vidas)
{
  vidas_= vidas;
}
bool jugador_t::get_amuleto(void)
{
  return amuleto_;
}

void jugador_t::mover(mazmorra_t* mazmorra, int n_mazmorras, pasillo_t* pasillo, int n_pasillos_, int xa, int ya, bool& pillado)
{
  bool aux=0;
  bool coincide;
  char opcion;
  
  cin.get(opcion);
  cin.get();
  
  do{
    switch(opcion){
      
      case 'j':
        for(int i=0; (i<n_mazmorras)&&(coincide == false); i++){
          if(mazmorra[i].dentro(x_,y_-1) == true){
            
            coincide = true;
            monstruo_t* monstruo = mazmorra[i].get_monstruos();
            
            for(int j=0; (j<mazmorra[i].get_nmonstruos())&&(aux == false); j++){
              if(monstruo[j].coincide(x_,y_-1) == true){
                aux = true;
              }
            }
            if(aux == false){
              
              y_--;
              if((xa == x_)&&(ya == y_)){
                
                pillado = true;
                amuleto_= true;
              }
            }
          }else{
            if(mazmorra[i].pertenece(x_,y_-1) == true){
              mazmorra[i].set_visible(true);
            }
          }
        }
        if(coincide == false){
          for(int i=0; (i<n_pasillos_)&&(coincide == false); i++){
            if(pasillo[i].coincide(x_,y_-1) == true){
              coincide = true;
              
              if(pasillo[i].get_visible() == false){
                pasillo[i].set_visible(true);
              }
              y_--;
            }
          }
        }
        aux = true;
        
        break;
        
      case 'l':
        for(int i=0; (i<n_mazmorras)&&(coincide == false); i++){
          if(mazmorra[i].dentro(x_,y_+1) == true){
            coincide = true;
            monstruo_t* monstruo = mazmorra[i].get_monstruos();
            for(int j=0; (j<mazmorra[i].get_nmonstruos())&&(aux == false); j++){
              if(monstruo[j].coincide(x_,y_+1) == true){
                aux = true;
              }
            }
            if(aux == false){
              aux = true;
              y_++;
              if((xa == x_)&&(ya == y_)){ 
                
                pillado = true;
                amuleto_= true;
              }
            }
          }else{
            if(mazmorra[i].pertenece(x_,y_+1) == true){
              mazmorra[i].set_visible(true);
            }
          }
        }
        if(coincide == false)
        {
          for(int i=0; (i<n_pasillos_)&&(coincide == false); i++){
            if(pasillo[i].coincide(x_,y_+1) == true){
              coincide = true;
              if(pasillo[i].get_visible() == false){
                pasillo[i].set_visible(true);
              }
              y_++;
            }
          }
        }
        aux = true;
        break;
        
      case 'k':
        for(int i=0; (i<n_mazmorras)&&(coincide == false); i++){
          if(mazmorra[i].dentro(x_+1,y_) == true){
            coincide = true;
            monstruo_t* monstruo = mazmorra[i].get_monstruos();
            for(int j=0; (j<mazmorra[i].get_nmonstruos())&&(aux == false); j++){
              if(monstruo[j].coincide(x_+1,y_) == true){
                aux = true;
              }
            }
            if(aux == false)
            {
              aux = true;
              x_++;
              if((xa == x_)&&(ya == y_)){ 
                
                pillado = true;
                amuleto_= true;
              }
            }
          }else{
            if(mazmorra[i].pertenece(x_+1,y_) == true){
              mazmorra[i].set_visible(true);
            }
          }
        }
        if(coincide == false){
          for(int i=0; (i<n_pasillos_)&&(coincide == false); i++){
            if(pasillo[i].coincide(x_+1,y_) == true){
              coincide = true;
              if(pasillo[i].get_visible() == false){
                pasillo[i].set_visible(true);
              }
              x_++;
            }
          }
        } 
        aux = true;
        break;
        
      case 'i':
        for(int i=0; (i<n_mazmorras)&&(coincide == false); i++){ 
          if(mazmorra[i].dentro(x_-1,y_) == true){
            coincide = true;
            monstruo_t* monstruo = mazmorra[i].get_monstruos();
            for(int j=0; (j<mazmorra[i].get_nmonstruos())&&(aux == false); j++){
              if(monstruo[j].coincide(x_-1,y_) == true){
                aux = true;
              }
            }
            if(aux == false){
              aux = true;
              x_--;
              if((xa == x_)&&(ya == y_)){
                
                pillado = true;
                amuleto_= true;
              }
            }
          }else{
            if(mazmorra[i].pertenece(x_-1,y_) == true){
              mazmorra[i].set_visible(true);
            }
          }
        }
        if(coincide == false){
          for(int i=0; (i<n_pasillos_)&&(coincide == false); i++){
            if(pasillo[i].coincide(x_-1,y_) == true){
              coincide = true;
              if(pasillo[i].get_visible() == false){
                pasillo[i].set_visible(true);
              }
              x_--;
            }
          }
        }
        aux = true;
        break;
        
      default:
        
        cout << "Movimiento incorrecto, por favor intruduzca una de estas opciones: j = izquierda, i = arriba, l = derecha, k = abajo." << endl;
        cin.get(opcion);
        cin.get();
        break;
    }
  }while(aux == false);
}

int jugador_t::pos(int i, int j, int m)
{
    return (i*m+j);
}

void jugador_t::pintar(char* map_, int m, mazmorra_t* mazmorra, int n_mazmorras)
{
    bool ocupado;
    bool dentro = false;
    map_[pos(x_,y_,m)] = '@';
    for(int i=0; (i<n_mazmorras)&&(dentro == false); i++){
      dentro = mazmorra[i].dentro(sx_,sy_);
      if(dentro == true){
        ocupado = mazmorra[i].monstruo(sx_,sy_);
      }
    }
    if((ocupado == false)&&((sx_ != x_)||(sy_ != y_))){
      map_[pos(sx_,sy_,m)] = 'x';
    }
}

void jugador_t::modificar(int x, int y, int vidas, bool amuleto, int sx, int sy)
{
    x_= x;
    y_= y;
    vidas_= vidas;
    amuleto_= amuleto;
    sx_= sx;
    sy_= sy;
}
