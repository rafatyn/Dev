#include "tm.hpp"

tuma::tuma(void):
estados(),
estado_inicial(),
alfabeto(),
cintaa()
{}

tuma::~tuma(void)
{}

bool tuma::leer_tape(char* fichero)
{
    return cintaa.leer_tape(fichero);
}    
    
bool tuma::leer_fichero(char* fichero)
{
    ifstream textfile;
    textfile.open(fichero);
    if (textfile.is_open()==true){
        if(estados.empty()==false){
  		    estados.erase(estados.begin(),estados.end());
        }
        vector <set <transicion> > vt;
        int auxint;
        bool auxbool;
        char auxchar;
        textfile >> (int &) auxint;
        int n_e = auxint;
        textfile >> (int &) auxint;
        int estado_inicial_ = auxint;
        textfile >> (int &) auxint;
        int eacep = auxint;
        textfile >> (int &) auxint;
        int n_t = auxint;
        set <transicion> tr;
        int rec=0;
        int rec1=0;
        for(int m=0; m<n_e; m++){
            vt.push_back(tr);
        }
        for(int i=0; i<n_t; i++){
            rec=rec1;
            textfile >> (int &) auxint;
            int id = auxint;
            textfile >> (char &) auxchar;
            char le = auxchar;
            textfile >> (char &) auxchar;
            char es = auxchar;
            textfile >> (char &) auxchar;
            int mov;
            rec1=id;
            if(rec!=rec1){
                vt[rec]=tr;
                tr.erase(tr.begin(),tr.end());
            }
            switch (auxchar){
                case 'L':
                    mov=-1;
                    break;
                case 'R':
                    mov=1;
                    break;
                case 'S':
                    mov=0;
                    break;
            }
            textfile >> (int &) auxint;
            int se = auxint;
            transicion tmp(le,es,mov,se);
            tr.insert(tmp);
        }
        vt[rec1]=tr;
        for(int j=0; j<vt.size(); j++){
            if(j==eacep){
                estado tmp2(vt[j],1,j);
                estados.insert(tmp2);
            }else{
                estado tmp2(vt[j],0,j);
                estados.insert(tmp2);
            }
        }
        if(estado_inicial_==eacep){
            estado ei(vt[estado_inicial_],1,estado_inicial_);
            estado_inicial = ei;    
        }else{
            estado ei(vt[estado_inicial_],0,estado_inicial_);
            estado_inicial = ei;    
        }                
        textfile.close();
    }else{
      cout<<"Error en la apertura del fichero."<<endl;
      return 0;
    }
    return 1;
}

bool tuma::alfabeto_existe(char x)
{
    for(set <char>::iterator i=alfabeto.begin(); i!=alfabeto.end(); i++){
        if((*i)==x){
            return 1;
        }
    }
    return 0;
}

ostream& operator<<(ostream &output, const tuma &x)
{
    output << x.get_n_estados() << endl << x.get_inicial().get_id() << endl;
    for(set <estado>::iterator i=x.get_estados().begin(); i!=x.get_estados().end(); i++){
      output << (*i) <<endl;
    }
    return output;
}

set <estado> tuma::get_estados(void) const
{
    return estados;
}

int tuma::get_n_estados(void) const
{
    return estados.size();
}

void tuma::mostrar(void)
{
    cout << endl << "Estados: " << estados.size() << endl;
    cout << "Estado incial: " << estado_inicial.get_id() << " " << endl;
    for(set <estado>::iterator i=estados.begin(); i!=estados.end(); i++){
        if((*i).get_aceptacion()){
            cout << "Estado de aceptación: " << (*i).get_id() << " ";
        }
    }
    cout << endl;
    int n=0;
    for(set <estado>::iterator i=estados.begin(); i!=estados.end(); i++){
        set <transicion> nn=(*i).get_transiciones();
        for(set <transicion>::iterator j=nn.begin(); j!=nn.end(); j++){
            n++;
        }
    }
    cout << "Numero de transiciones: " << n << endl;
    for(set <estado>::iterator i=estados.begin(); i!=estados.end(); i++){
      (*i).mostrar();
    }
}

estado tuma::get_inicial(void) const
{
    return estado_inicial;
}

int tuma::get_id_inicial(void) const
{
    return estado_inicial.get_id();
}

void tuma::analizar_cadena(void)
{
    vector <char> tape = cintaa.get_c();
    int c=1;
    estado aux = estado_inicial;
    int x=0;
    do{
        if(aux.existe(tape[c])){
            for(int i=0; i<c; i++){
                cout << tape[i];
            }
            cout << " q" << aux.get_id() << " ";
            for(int i=c; i<tape.size(); i++){
                cout << tape[i];
            }
            cout << endl;
            transicion tmp = aux.get_transicion(tape[c]);
            aux=get_estado(tmp.get_sig_estado());
            tape[c]=tmp.get_escribe();
            c+=tmp.get_movimiento();
        }else{
            x++;
        }
    }while(!aux.get_aceptacion()&&x!=1);
    if(aux.get_aceptacion()){
        cout << "Cadena ACEPTADA";
    }else{
        cout << "Cadena NO ACEPTADA";
    }       
    cout << endl;
}

estado tuma::get_estado(int x)
{
    if(x<estados.size()){
        for(set<estado>::iterator i=estados.begin(); i!=estados.end(); i++){
            if((*i).get_id()==x){
                return (*i);
            }
        }
    }  
    cout << "Estado no encontrado" << endl;
}

void tuma::mostrar_estados_muerte(void)
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