#include "nfa.hpp"

int main (int argc, char *argv[]) {
  
  char* fichero= new char[0];
  NFA_t NFA;
  DFA_t DFA;
  if(argc==1) {
    
    cout<<"Introduzca el nombre del fichero que contiene el NFA: ";
    cin>>fichero;
  }
  else
    fichero=argv[1];
  while(!NFA.leer_fichero(fichero)) {
    
    cout<<"Error de apertura " << "Introduzca el nombre del fichero que contiene el NFA: ";
    cin>>fichero;
  }
  DFA=NFA.convert2DFA();
  
  if(argc<3) {
    
    cout<<"Introduzca el nombre del fichero donde desea almacenar el DFA resultante: ";
    cin>>fichero;
  }
  else
    fichero=argv[2];
  {
    ofstream textfile;
    textfile.open(fichero);
    textfile<<DFA;
    textfile.close();
  }
  
  if(argc>3)
    fichero=argv[3];
  else {
    cout<<"Introduzca el nombre del fichero que contiene las cadenas que desea analizar: ";
    cin>>fichero;
  }
  {
    ifstream textfile;
    textfile.open(fichero);
    while(!textfile.is_open()) {
      
      cout<<"Error al abrir fichero, introduzca uno válido: ";
      cin>>fichero;
      textfile.open(fichero);
    }
    
    cout<<"Cadena      NFA          DFA"<<endl;
    cout<<"------------------------------------"<<endl;
    char* cadena= new char[0];
    int n_cadenas;
    textfile>>(int &) n_cadenas;
    for(int i=0; i<n_cadenas; i++) {
      
      textfile>>(char* &) cadena;
      cout<<left<<setw(12)<<setfill(' ')<<cadena<<setw(13)<<setfill(' ')<<(NFA.analizar_cadena(cadena) ? "Aceptada" : "No aceptada")<<(DFA.analizar_cadena(cadena) ? "Aceptada" : "No aceptada")<<endl;
    }
    textfile.close();
  }
}
