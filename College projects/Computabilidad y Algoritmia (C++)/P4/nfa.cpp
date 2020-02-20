#include "nfa.hpp"

nfa::nfa(void):
estados(),
estado_inicial()
{}

nfa::~nfa(void)
{}

bool nfa::leer_fichero(void)
{
    char fichero[80];
    cout << "Introduzca el nombre del fichero a leer: ";
    cin >> fichero;
    ifstream textfile;
    textfile.open(fichero);
    if (textfile.is_open()==true){
      if(estados.empty()==false){
  		  estados.erase(estados.begin(),estados.end());
      }
      int n_e;
      int auxint;
      bool auxbool;
      char auxchar;
      int id;
      textfile >> (int &) auxint;
      n_e = auxint;
      textfile >> (int &) auxint;
      int estado_inicial_ = auxint;
      for(int i=0; i<n_e; i++){
        int sz;
        textfile >> (int &) id;
        textfile >> (bool &) auxbool >> (int &) auxint;
        sz = auxint;
        set <transicion> transiciones;
        for(int j=0; j<sz; j++){
          textfile >> (char &) auxchar >> (int &) auxint;
          transicion tmp(auxchar,auxint);
          transiciones.insert(tmp);
        }
        estado tmp(transiciones,auxbool,id);
        estados.insert(tmp);
        if(id==estado_inicial_){
          estado_inicial = get_estado(id);
        }
      }
      textfile.close();
    }else{
      cout<<"Error en la apertura del fichero."<<endl;
      return 0;
    }
    return 1;
}

ostream& operator<<(ostream &output, const nfa &x)
{
    output << "Numero de estados: "<< x.get_n_estados() << "Estado inicial: "<< x.get_inicial().get_id() << endl;
    for(set <estado>::iterator i=x.get_estados().begin(); i!=x.get_estados().end(); i++){
      output << (*i) <<endl;
    }
    return output;
}

set <estado> nfa::get_estados(void) const
{
    return estados;
}

int nfa::get_n_estados(void) const
{
    return estados.size();
}

void nfa::mostrar(void)
{
    cout << endl << "Estados: " << estados.size() << endl;
    cout << "Estado incial: " << estado_inicial.get_id() << " " << endl;
    for(set <estado>::iterator i=estados.begin(); i!=estados.end(); i++){
      (*i).mostrar();
      cout << endl;
    }
}

estado nfa::get_inicial(void) const
{
    return estado_inicial;
}

void nfa::analizar_cadena(void)
{
    char cadena[85];
    cout << endl << "Introduzca la cadena que desea analizar: ";
    cin >> cadena;
    cout << endl << "Cadena de entrada: " << cadena << endl;
    estado aux = estado_inicial;  
    int x=0;
    bool baux=0;
    stringbuf buffer;
    ostream os (&buffer);
    analizar_cadena_recursivo(x,cadena,-1,buffer,os,estado_inicial,baux);
    cout << endl << "Desición final: " << endl << "Cadena de entrada: ";
    if(baux==true){
        cout << "ACEPTADA";
    }else{
        cout << "NO ACEPTADA";
    }
    cout << endl;
}

void nfa::analizar_cadena_recursivo(int &n, char cadena [], int i, const stringbuf &buffer, const ostream &os, estado estado_, bool &baux)
{
    if(cadena[i+1]!='\0'){
        set <int> transiciones = estado_.get_epsilon_clausura();
        if(transiciones.size()!=0){
            for(set <int>::iterator x=transiciones.begin(); x!=transiciones.end(); x++){
                stringbuf buffer2;
                ostream os2(&buffer2);            
                os2 << left << buffer.str() << left << setw(17) << setfill(' ') << estado_.get_id() << setw(11) << setfill(' ') << "~" << (*x) << endl;
                analizar_cadena_recursivo(n, cadena, i, buffer2, os2, get_estado((*x)), baux);
            }
        }
        if(transiciones.empty()==false){
    		  transiciones.erase(transiciones.begin(), transiciones.end());
        }
        transiciones = estado_.get_conjunto_transiciones(cadena[i+1]);
        if(transiciones.size()==0){
            n++;
            cout << endl << "Camino " << n << ":" << endl;
            cout << "Estado actual    Entrada    Siguiente estado" << endl;
            cout << left << buffer.str();
            cout << left << setw(17) << setfill(' ') << estado_.get_id() << setw(11) << setfill(' ') << cadena[i+1] << estados.size() << endl;
            for(int j=i+2; cadena[j]!='\0'; j++){
                cout << left << setw(17) << setfill(' ') << estados.size() << setw(11) << setfill(' ') << cadena[j] << estados.size() << endl;
            }
            cout << "Cadena de entrada ";
            cout << "NO ACEPTADA" << endl;
        }else{
            for(set <int>::iterator x=transiciones.begin(); x!=transiciones.end(); x++){
                stringbuf buffer2;
                ostream os2(&buffer2);
                os2 << left << buffer.str() << left << setw(17) << setfill(' ') << estado_.get_id() << setw(11) << setfill(' ') << cadena[i+1] << (*x) << endl;
                analizar_cadena_recursivo(n, cadena, i+1, buffer2, os2, get_estado((*x)), baux);
            }
        }
    }else{
        set <int> e_transiciones = estado_.get_epsilon_clausura();
        if(e_transiciones.size()!=0){
            for(set <int>::iterator x=e_transiciones.begin(); x!=e_transiciones.end(); x++){
                stringbuf buffer2;
                ostream os2(&buffer2);
                os2 << left << buffer.str() << left << setw(17) << setfill(' ') << estado_.get_id() << setw(11) << setfill(' ') << "~" << (*x) << endl;
                analizar_cadena_recursivo(n, cadena, i, buffer2, os2, get_estado((*x)), baux);
            }
        }
        n++;
        cout << "Camino " << n << ":" << endl;
        cout << "Estado actual    Entrada    Siguiente estado" << endl;
        cout << left << buffer.str() << endl;
        cout << "Cadena de entrada ";
        if(estado_.get_aceptacion()){
            cout<<"ACEPTADA"<<endl;
            baux = 1;
        }else{
            cout<<"NO ACEPTADA"<<endl;
        }
    }
}
    

estado nfa::get_estado(int x)
{
    if(x<estados.size()){
        for(set<estado>::iterator i=estados.begin(); i!=estados.end(); i++){
            if((*i).get_id()==x){
                return (*i);
            }
        }
    }  
    cout << "Estado no encontrado." << endl;
}

void nfa::mostrar_estados_muerte(void)
{
    int x=0;
    for(set <estado>::iterator i=estados.begin(); i!=estados.end(); i++){
        if((*i).estado_muerte()==true){
            cout << endl << "El estado q" << (*i).get_id() << " es un estado de muerte";
            x++;
        }
    }
    if(x==0){
        cout << endl << "No hay estados de muerte";
    }
    cout << endl;
}