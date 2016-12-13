#include "DFA.hpp"

DFA::DFA(void):
  estados(),
  estado_inicial()
  {}

DFA::~DFA(void)
{}

bool DFA::leer_fichero(void)
{
  char fichero[80];
  cout<<"Introduzca el nombre del fichero a leer: ";
  cin>>fichero;
  ifstream textfile;
  textfile.open(fichero);
  if (textfile.is_open())
  {
    if(!estados.empty())
		  estados.erase(estados.begin(),estados.end());
    int n_estados_;
    int auxint;
    bool auxbool;
    char auxchar;
    int useless;
    textfile>>(int &) auxint;
    n_estados_=auxint;
    textfile>>(int &) auxint;
    int estado_inicial_=auxint;
    for(int i=0; i<n_estados_; i++){
      int sz;
      textfile>>(int &) useless;
      textfile>>(bool &) auxbool>>(int &) auxint;
      sz=auxint;
      set<transition_state_t> transiciones;
      for(int j=0; j<sz; j++){
        textfile>>(char &) auxchar>>(int &) auxint;
        transition_state_t ts(auxchar,auxint);
        transiciones.insert(ts);
      }
      state_t tmp(transiciones,auxbool,useless);
      estados.insert(tmp);
      if(useless==estado_inicial_){
        estado_inicial=get_state(useless);
      }
    }
    textfile.close();
  }else{
    cout<<"Error en la apertura del fichero."<<endl;
    return(0);
  }
  return(1);
}

ostream& operator<<(ostream &output, const DFA &x)
{
  output<<"\n"<<x.get_n_estados()<<"\n"<<x.get_inicial().get_id()<<"\n";
  for(set<state_t>::iterator i=x.get_estados().begin(); i!=x.get_estados().end(); i++)
    output<<(*i)<<"\n";
  return(output);
}

set<state_t> DFA::get_estados(void) const
{
  return(estados);
}

int DFA::get_n_estados(void) const
{
  return(estados.size());
}

void DFA::mostrar(void)
{
  cout<<endl<<"Estados: "<<estados.size()<<endl;
  cout<<"Estado incial: "<<estado_inicial.get_id()<<endl;
  for(set<state_t>::iterator i=estados.begin(); i!=estados.end(); i++){
    (*i).mostrar();
    cout<<endl;
  }
}

state_t DFA::get_inicial(void) const
{
  return(estado_inicial);
}

void DFA::analizar_cadena(void)
{
  char cadena[85];
  cout<<endl<<"Introduzca la cadena que desea analizar: ";
  cin>>cadena;
  cout<<endl<<"Cadena de entrada: "<<cadena<<endl;
  cout<<"Estado actual    Entrada    Siguiente estado"<<endl;
  state_t aux=estado_inicial;
  bool reconocido=1;
  for(int i=0; cadena[i]!='\0'&&reconocido ; i++){
    cout<<left;
    cout << setw(17) << setfill(' ') << aux.get_id();
    cout << setw(11) << setfill(' ') <<  cadena[i];
    if(reconocido=aux.reconocido(cadena[i])){
        aux=get_state(aux.estado_siguiente(cadena[i]));
        cout << aux.get_id();
    }else{
      cout << "X";
    }
    cout<<endl;
  }
  cout<<"Cadena de entrada ";
  if(aux.aceptacion()&&reconocido)
    cout<<"ACEPTADA";
  else
    cout<<"NO ACEPTADA";
  cout<<endl;
}

state_t DFA::get_state(int x)
{
  if(x<estados.size())
    for(set<state_t>::iterator i=estados.begin(); i!=estados.end(); i++)
      if((*i).get_id()==x)
        return(*i);
  
  cout<<"Estado no encontrado."<<endl;
}

void DFA::mostrar_estados_muerte(void)
{
  int x=0;
  for(set<state_t>::iterator i=estados.begin(); i!=estados.end(); i++)
    if((*i).estado_muerte()){
      cout<<endl<<"El estado q"<<(*i).get_id()<<" es un estado de muerte";
      x++;
    }
    
  if(x==0)
    cout<<endl<<"No hay estados de muerte";
  cout<<endl;
}
    
