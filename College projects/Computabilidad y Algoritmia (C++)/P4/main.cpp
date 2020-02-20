#include "nfa.hpp"

int main (void)
{
    nfa NFA;
    while(!NFA.leer_fichero());
    int opcion;
    do{
      cout<<endl;
      cout<<"1. Leer fichero."<<endl;
      cout<<"2. Mostrar NFA."<<endl;
      cout<<"3. Mostrar estados de muerte."<<endl;
      cout<<"4. Analizar cadena."<<endl;
      cout<<"5. Salir."<<endl;
      cout<<"Introduzca una opción: ";
      cin >> opcion;
      
      switch(opcion){
          case 2:
            NFA.mostrar();
            break;
          case 3:
            NFA.mostrar_estados_muerte();
            break;
          case 4:
            NFA.analizar_cadena();
            break;
          case 1:
            NFA.leer_fichero();
            break;
          case 5:
            break;
          default:
            cout<<"Opción no encontrada."<<endl;
            break;
      }
    }while(opcion!=5);
}