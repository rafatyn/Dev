#include "tm.hpp"
#include <fstream>

int main (int argc, char *argv[])
{
    char* fichero= new char[0];
    tuma TM;
    if(argc==1){
      cout<<"Introduzca el nombre del fichero que contiene la TM: ";
      cin>>fichero;
    }else{
      fichero=argv[1];
    }
    while(!TM.leer_fichero(fichero)){
      cout<<"Error al abrir la tm, introduzca uno válido: ";
      cin>>fichero;
    }
    if(argc<3){
      cout<<"Introduzca el nombre del fichero que contiene la cinta: ";
      cin>>fichero;
    }else{
      fichero=argv[2];
    }
    while(!TM.leer_tape(fichero)){
      cout<<"Error al abrir la tape, introduzca una válida: ";
      cin>>fichero;
    }
    TM.mostrar();
    cout << endl << "Analizar cadena: " << endl;
    TM.analizar_cadena();  
}