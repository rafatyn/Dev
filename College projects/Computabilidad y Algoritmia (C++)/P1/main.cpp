#include "tablero_t.hpp"

#include <cstdio>

using namespace std;

int main (void)
{
  
  srand(time(NULL));

  char opcion;
  cout << "¿Desea generar un mapa aletorio?(Si no se generara pr fichero) y/n : ";
  cin.get(opcion);

  tablero_t mapa;
  
  if(opcion =='y'){
    
    mapa.generar_aleatorio();
    mapa.crear_fichero();
    
  }else{

    if(opcion =='n'){

      mapa.cargar();
    }
  }
  
  mapa.mostrar();
  mapa.partida();
}