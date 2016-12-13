#include "tablero_t.hpp"

void tablero_t::redimensiona_pasillos(void)
{
    destruye_pasillos();
    pasillo_= new pasillo_t [n_pasillos_];
}
void tablero_t::destruye_pasillos(void)
{
    if(pasillo_!=NULL){
      for(int i=0; i<n_pasillos_; i++){
        pasillo_[i].destruye_pasillo();
      }
      delete [] pasillo_;
    }
}

void tablero_t::generar_aleatorio(void)
{
    redimensiona(50,100);
    destruye_mazmorra();
    destruye_pasillos();
    n_mazmorras_= 3;
    n_pasillos_= 3;
    crea_mazmorras();
    situar_amuleto();
    situa_personaje();
    crea_pasillos();
}

void tablero_t::redimensionar_mazmorras(void)
{
    destruye_mazmorra();
    mazmorra_= new mazmorra_t [n_mazmorras_];
}

void tablero_t::crear_fichero(void)
{
    ofstream fichero;
    fichero.open("fichero");
    fichero << n_ << " " << m_ << "\n";
    fichero << n_mazmorras_ << "\n";
    for(int i=0; i<n_mazmorras_; i++){
      
      fichero << mazmorra_[i].get_xsup() << " ";
      fichero << mazmorra_[i].get_ysup() << " ";
      fichero << mazmorra_[i].get_xinf() << " ";
      fichero << mazmorra_[i].get_yinf() << " ";
      fichero << mazmorra_[i].get_visible() << " ";
      fichero << mazmorra_[i].get_xp1() << " ";
      fichero << mazmorra_[i].get_yp1() << " ";
      fichero << mazmorra_[i].get_xp2() << " ";
      fichero << mazmorra_[i].get_yp2() << " ";
      fichero << mazmorra_[i].get_nmonstruos() << "\n";
      monstruo_t* monstruo_ = mazmorra_[i].get_monstruos();
      
      for(int j=0; j<mazmorra_[i].get_nmonstruos(); j++){
        
        fichero << monstruo_[j].get_x() << " ";
        fichero << monstruo_[j].get_y() << "\n";
      }
    }
    fichero << n_pasillos_ << "\n";
    for(int i=0; i<n_pasillos_; i++){
      
      fichero << pasillo_[i].get_npuntos() << " ";
      fichero << pasillo_[i].get_visible() << "\n";
      for(int j=0; j<pasillo_[i].get_npuntos(); j++){
        
        fichero << pasillo_[i].get_x(j) << " ";
        fichero << pasillo_[i].get_y(j) << "\n";
      }
    }
    fichero << amuleto_.get_x() << " ";
    fichero << amuleto_.get_y() << " ";
    fichero << amuleto_.get_pillado() << "\n";
    fichero << jugador_.get_x() << " ";
    fichero << jugador_.get_y() << " ";
    fichero << jugador_.get_vidas() << " ";
    fichero << jugador_.get_amuleto() << " ";
    fichero << jugador_.get_sx() << " ";
    fichero << jugador_.get_sy() << "\n";
    fichero.close();
}

void tablero_t::cargar(void)
{
    char fichero[85];
    cout << "Introduzca el nombre del fichero que desea cargar: ";
    cin >> fichero;
    ifstream textfile;
  	textfile.open(fichero);
    if (textfile.is_open())
    {
      int aux1, aux2, aux3, aux4, aux5, aux6, aux7, aux8, aux9;
      bool baux;
      textfile >> (int &) aux1 >> (int &) aux2;
      redimensiona(aux1,aux2);
      textfile >> (int &) aux1;
      n_mazmorras_ = aux1;
      redimensionar_mazmorras();
      for(int i=0; i<n_mazmorras_; i++){
        
        textfile >> (int &) aux1 >> (int &) aux2 >> (int &) aux3 >> (int &) aux4 >> (bool &) baux >> (int &) aux5 >> (int &) aux6 >> (int &) aux7 >> (int &) aux8 >> (int &) aux9;
        mazmorra_[i].set_mazmorra(aux1, aux2, aux3, aux4, baux, aux5, aux6, aux7, aux8, aux9);
        mazmorra_[i].redimensionar_monstruos();
        for(int j=0; j<mazmorra_[i].get_nmonstruos(); j++){
          textfile >> (int &) aux1 >> (int &) aux2;
          mazmorra_[i].modificar_monstruo(j,aux1,aux2);
        }
      }
      textfile >> (int &) aux1;
      n_pasillos_ = aux1;
      redimensiona_pasillos();
      for(int i=0; i<n_pasillos_; i++){
        textfile >> (int &) aux1 >> (bool &) baux;
        pasillo_[i].set_npuntos(aux1);
        pasillo_[i].set_visible(baux);
        pasillo_[i].redimensionar();
        for(int j=0; j<pasillo_[i].get_npuntos(); j++){
          textfile >> (int &) aux1 >> (int &) aux2;
          pasillo_[i].set_x(aux1,j);
          pasillo_[i].set_y(aux2,j);
        }
      }
      textfile >> (int &) aux1 >> (int &) aux2 >> (bool &) baux;
      amuleto_.modificar(aux1,aux2,baux);
      textfile >> (int &) aux1 >> (int &) aux2 >> (int &) aux3 >> (bool &) baux >> (int &) aux4 >> (int &) aux5;
      jugador_.modificar(aux1,aux2,aux3,baux,aux4,aux5);
        
      textfile.close();
    }
    else
      cout << "Error en la apertura del fichero." << endl;  
}

void tablero_t::pintar_amuleto(void)
{
  amuleto_.mostrar(map_,m_,mazmorra_,n_mazmorras_);
}

void tablero_t::situar_amuleto(void)
{
  amuleto_.set_x(rand () % (mazmorra_[2].get_xinf()-mazmorra_[2].get_xsup()-1) + mazmorra_[2].get_xsup()+1);
  amuleto_.set_y(rand () % (mazmorra_[2].get_yinf()-mazmorra_[2].get_ysup()-1) + mazmorra_[2].get_ysup()+1);
}

void tablero_t::partida(void)
{
  
    while(game_over() == false)
    {
      jugador_.mover(mazmorra_,n_mazmorras_,pasillo_,n_pasillos_, amuleto_.get_x(), amuleto_.get_y(), amuleto_.get_set_pillado());
      for(int i=0; i<n_mazmorras_; i++){
        mazmorra_[i].mover_monstruos(jugador_.get_set_vidas(), jugador_.get_x(), jugador_.get_y());
      }
      mostrar();
    }
}   

bool tablero_t::game_over(void)
{
    if(jugador_.ganar() == true){
      cout << endl << "¡¡You win!!" << endl;
    }else{
      if(jugador_.perder() == true){
        cout << endl << "You Loose" << endl;
      }
    }
    return(jugador_.ganar()||jugador_.perder());    
}

void tablero_t::pintar_personaje(void)
{
    jugador_.pintar(map_,m_,mazmorra_,n_mazmorras_);  
}

void tablero_t::situa_personaje(void)
{
    int rx;
    int ry;
    bool aux;
    
    do{
      rx = rand () % (mazmorra_[0].get_xinf()-mazmorra_[0].get_xsup()-1) + mazmorra_[0].get_xsup()+1;
      ry = rand () % (mazmorra_[0].get_yinf()-mazmorra_[0].get_ysup()-1) + mazmorra_[0].get_ysup()+1;
      aux = mazmorra_[0].monstruo(rx,ry);
    }while(aux == true);
      
    jugador_.modificar(rx, ry, 5, 0, rx, ry);
}

void tablero_t::crea_pasillos(void)
{
    int xaux;
    int yaux;
    int raux;
    int cont;
    pasillo_= new pasillo_t [n_pasillos_];
    bool error;
    
    do{
      error = 0;
      xaux = mazmorra_[0].get_xp2()+1;
      yaux = mazmorra_[0].get_yp2();
      raux = rand () % (mazmorra_[2].get_xp1()-mazmorra_[0].get_xp2()-1) + mazmorra_[0].get_xp2()+1;
     
      cont=1;
      for(xaux; (xaux<raux)&&(error == false); xaux++){
        if(mazmorra_[1].pertenece(xaux,yaux) == true){
          error = true;
        }else{
          cont++;
        }
      }
      if(mazmorra_[0].get_yp2()<mazmorra_[2].get_yp1()){
        for(yaux; (yaux<mazmorra_[2].get_yp1())&&(error == false); yaux++){
          if(mazmorra_[1].pertenece(xaux,yaux)){
            error = true;
          }else{
            cont++;
          }
        }
      }else{
        for(yaux; (yaux>mazmorra_[2].get_yp1())&&(error == false); yaux--){
          if(mazmorra_[1].pertenece(xaux,yaux)){
            error = true;
          }else{
            cont++;
          }
        }
      }
      for(xaux; (xaux<=mazmorra_[2].get_xp1())&&(error = false); xaux++){
        if(mazmorra_[1].pertenece(xaux,yaux)){
            error = true;
        }else{
          cont++;
        }
      }
    }while(error == true);
    
    pasillo_[0].set_npuntos(4);
    pasillo_[0].crear_pasillo();
    cont = 0;
    xaux= mazmorra_[0].get_xp2();
    yaux= mazmorra_[0].get_yp2();
    pasillo_[0].set_x(mazmorra_[0].get_xp2(),0);
    pasillo_[0].set_y(mazmorra_[0].get_yp2(),0);
    pasillo_[0].set_x(raux,1);
    pasillo_[0].set_y(mazmorra_[0].get_yp2(),1);
    pasillo_[0].set_x(raux,2);
    pasillo_[0].set_y(mazmorra_[2].get_yp1(),2);
    pasillo_[0].set_x(mazmorra_[2].get_xp1(),3);
    pasillo_[0].set_y(mazmorra_[2].get_yp1(),3);
    
    pasillo_[1].set_npuntos(4);
    pasillo_[1].crear_pasillo();
    pasillo_[1].set_x(mazmorra_[0].get_xp1(),0);
    pasillo_[1].set_y(mazmorra_[0].get_yp1(),0);
    raux= rand () % (mazmorra_[1].get_yp1()-mazmorra_[0].get_yp1()) + mazmorra_[0].get_yp1()-1;
    pasillo_[1].set_x(mazmorra_[0].get_xp1(),1);
    pasillo_[1].set_y(raux,1);
    pasillo_[1].set_x(mazmorra_[1].get_xp1(),2);
    pasillo_[1].set_y(raux,2);
    pasillo_[1].set_x(mazmorra_[1].get_xp1(),3);
    pasillo_[1].set_y(mazmorra_[1].get_yp1(),3);
  
    pasillo_[2].set_npuntos(5);
    pasillo_[2].crear_pasillo();
    pasillo_[2].set_x(mazmorra_[2].get_xp2(),0);
    pasillo_[2].set_y(mazmorra_[2].get_yp2(),0);
    raux=rand () % 2+2;
    pasillo_[2].set_x(mazmorra_[2].get_xp2(),1);
    pasillo_[2].set_y(raux+mazmorra_[2].get_yp2(),1); 
    raux=rand () % (mazmorra_[2].get_xsup()-mazmorra_[1].get_xp2()-1) + mazmorra_[1].get_xp2();
    pasillo_[2].set_x(raux,2);
    pasillo_[2].set_y(pasillo_[2].get_y(1),2); 
    pasillo_[2].set_x(pasillo_[2].get_x(2),3);
    pasillo_[2].set_y(mazmorra_[1].get_yp2(),3);
    pasillo_[2].set_x(mazmorra_[1].get_xp2(),4);
    pasillo_[2].set_y(mazmorra_[1].get_yp2(),4);
}

void tablero_t::pintar_mazmorras(void)
{
    for(int i=0; i<n_mazmorras_; i++){
      mazmorra_[i].pintar_mazmorra(map_,m_);
    }
}
void tablero_t::pintar_pasillos(void)
{
    for(int i=0; i<n_pasillos_; i++){
      pasillo_[i].pintar_pasillo(map_,m_);
    }
}

void tablero_t::crea_mazmorras(void)
{ 
    destruye_mazmorra();
    mazmorra_= new mazmorra_t [n_mazmorras_];
    mazmorra_[0].calcular_x(n_/5,0,0);
    mazmorra_[0].calcular_y(m_/5,0,0); 
    mazmorra_[0].set_xp1(rand () % (mazmorra_[0].get_xinf()-mazmorra_[0].get_xsup()-2) + mazmorra_[0].get_xsup()+1);
    mazmorra_[0].set_yp1(mazmorra_[0].get_yinf());
    mazmorra_[0].set_xp2(mazmorra_[0].get_xinf());
    mazmorra_[0].set_yp2(rand () % (mazmorra_[0].get_yinf()-mazmorra_[0].get_ysup()-2) + mazmorra_[0].get_ysup()+1);
    mazmorra_[0].set_visible(1);
    
    mazmorra_[1].calcular_x(n_/5,0,0);
    mazmorra_[1].calcular_y(m_/5,m_/2,0);
    mazmorra_[1].set_xp1(rand () % (mazmorra_[1].get_xinf()-mazmorra_[1].get_xsup()-2)+ mazmorra_[1].get_xsup()+1);
    mazmorra_[1].set_yp1(mazmorra_[1].get_ysup());
    mazmorra_[1].set_xp2(mazmorra_[1].get_xinf());
    mazmorra_[1].set_yp2(rand () % (mazmorra_[1].get_yinf()-mazmorra_[1].get_ysup()-2) + mazmorra_[1].get_ysup()+1);
  
    mazmorra_[2].calcular_x(n_/5,n_/2,0);
    mazmorra_[2].calcular_y(m_/2,0,-4);
    mazmorra_[2].set_xp1(mazmorra_[2].get_xsup());
    mazmorra_[2].set_yp1(rand () % (mazmorra_[2].get_yinf()-mazmorra_[2].get_ysup()-2) + mazmorra_[2].get_ysup()+1);
    mazmorra_[2].set_xp2(rand () % (mazmorra_[2].get_xinf()-mazmorra_[2].get_xsup()-2) + mazmorra_[2].get_xsup()+1);
    mazmorra_[2].set_yp2(mazmorra_[2].get_yinf());
    for(int i=0; i<n_mazmorras_; i++){
      mazmorra_[i].set_nmonstruos(3);
      mazmorra_[i].crea_monstruos();
    }
}

void tablero_t::destruye_mazmorra(void)
{
    if(mazmorra_!=NULL)
    {
      for(int i=0; i<n_mazmorras_; i++)
        mazmorra_[i].destruye_monstruos();
      delete [] mazmorra_;
      mazmorra_=NULL;
    }
}

tablero_t::tablero_t(void):

    n_(0),
    m_(0),
    map_(NULL),
    mazmorra_(),
    n_mazmorras_(0),
    pasillo_(),
    n_pasillos_(0),
    jugador_(),
    amuleto_()
    {}
  
tablero_t::~tablero_t(void)
{
    destruye();
    destruye_mazmorra();
    destruye_pasillos();
}

void tablero_t::crea(void)
{
    map_= new char [n_*m_];
    limpiar();
}

void tablero_t::limpiar(void)
{
    for(int i=0; i<n_; i++){
      for(int j=0; j<m_; j++){
        set(i,j,' ');
      }
    }
}

void tablero_t::destruye(void)
{
    if(map_!=NULL)
    {
      delete [] map_;
      map_= NULL;
    }
    n_= 0;
    m_= 0;
}

void tablero_t::redimensiona(int n, int m)
{
    destruye();
    n_= n;
    m_= m;
    crea();
}

int tablero_t::pos(int i, int j)
{
    if((i>n_)||(j>m_)){
      cout << endl << "overflow" << endl;
    }
    return (i*m_+j);
}

char tablero_t::get(int i, int j)
{
    return map_[pos(i,j)];
}

void tablero_t::set(int i, int j, char x)
{
    map_[pos(i,j)] = x;
}

int tablero_t::get_n(void)
{
    return n_;
}

int tablero_t::get_m(void)
{
    return m_;
}

void tablero_t::mostrar(void)
{
    system("clear");
    limpiar();
    pintar_pasillos();
    pintar_mazmorras();
    pintar_personaje();
    pintar_amuleto();
    for(int i=0; i<n_; i++){
      for(int j=0; j<m_; j++){
        cout << get(i,j);
      }
      cout<<endl;
    }
    cout << endl << "----------------------------------------------------------------------------" << endl;
    cout << "Vidas restantes: ";
    for(int i=0; i<jugador_.get_vidas(); i++){
      cout << "♥";
    }
    cout << endl << "Direccion: ";
}