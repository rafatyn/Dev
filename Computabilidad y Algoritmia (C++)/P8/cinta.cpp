#include "cinta.hpp"

cinta::cinta(void):
cadena()
{}

cinta::~cinta(void)
{}

vector <char> cinta::get_c(void)
{
    return cadena;
}

bool cinta::leer_tape(char* fichero)
{
    ifstream textfile;
    textfile.open(fichero);
    if(textfile.is_open()==true){
        if(cadena.empty()==false){
  		    cadena.erase(cadena.begin(),cadena.end());
        }
        cadena.push_back('$');
        char* auxchar=new char[0];
        textfile >> (char* &) auxchar;
        for(int i=0; auxchar[i]!='\0'; i++){
            cadena.push_back(auxchar[i]);
        }
        cadena.push_back('$');
    }else{
      cout<<"Error en la apertura del fichero."<<endl;
      return 0;
    }
    return 1;
}

void cinta::set_m(char c)
{
    cadena.push_back(c);
    cadena.push_back('$');
}

void cinta::set_me(char c)
{
    vector <char> cadena1 = cadena;
    cadena.erase(cadena.begin(),cadena.end());
    cadena.push_back('$');
    cadena.push_back(c);
    for(int i=0; i<cadena1.size(); i++)
    {
        cadena.push_back(cadena1[i]);
    }
        
}