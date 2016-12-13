#include "dfa.hpp"
#include <fstream>

int main (int argc, char *argv[])
{
    char* fichero= new char[0];
    if(argc!=2){
        cout << "Introduzca el nombre del fichero: ";
        cin >> fichero;
        cin.clear();
    }else{
        fichero=argv[1];
    }
    dfa DFA;
    while(!DFA.leer_fichero(fichero)){
        cout << "Error al abrir fichero, el nombre no es valido, introduzca otro: ";
        cin >> fichero;
        cin.clear();
    }
    int opcion;
    do{
      cout<<endl;
      cout<<"1. Leer fichero."<<endl;
      cout<<"2. Mostrar DFA."<<endl;
      cout<<"3. Mostrar estados de muerte."<<endl;
      cout<<"4. Analizar cadena."<<endl;
      cout<<"5. Minimizar DFA."<<endl;
      cout<<"6. Exportar a fichero."<<endl;
      cout<<"0. Salir."<<endl;
      cout<<"Introduzca una opción: ";
      cin >> opcion;
      
      switch(opcion){
          case 2:
            DFA.mostrar();
            break;
          case 3:
            DFA.mostrar_estados_muerte();
            break;
          case 4:
            DFA.analizar_cadena();
            break;
          case 1: 
            DFA.destruir();
            cout << "Introduzca el nombre del fichero a leer: ";
            cin >> fichero;
            cin.clear();
            if(DFA.leer_fichero(fichero)){
                cout<<"El fichero se ha cargado"<<endl;
            }else{
                cout<<"Error al cargar el fichero"<<endl;
            }
            break;
          case 5:
            {
            dfa DFA2 = DFA.minimizar();
            DFA2.mostrar();
            int op;
            do{
            cout<<endl;
            cout<<"¿Que desea hacer?"<<endl;
            cout<<"1. Guardarlo en un fichero"<<endl;
            cout<<"2. Cargarlo como DFA actual"<<endl;
            cout<<"0. Salir"<<endl;
            cout<<"Introduzca una opcion: ";
            cin>>op;
            switch(op){
                case 1:
                  {
                      DFA2.crear_fichero();
                  }
                break;
                case 2:
                    DFA.copiar(DFA2);
                break;
                case 0:
                break;
            }
            }while(op!=0);
            }
            break;            
          case 6:
            {
                DFA.crear_fichero();
            }
            break;
          case 0:
            break;
          default:
            cout<<"Opción no encontrada."<<endl;
            break;
      }
    }while(opcion!=0);
}