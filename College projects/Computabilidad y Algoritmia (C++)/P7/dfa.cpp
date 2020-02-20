#include "dfa.hpp"

dfa::dfa(void):
estados(),
estado_inicial(),
alfabeto(),
gram()
{}

dfa::~dfa(void)
{}

void dfa::destruir(void)
{
    set <estado> cvacio;
    estado evacio;
    set <char> avacio;
    estados=cvacio;
    estado_inicial=evacio;
    alfabeto=avacio;
}

void dfa::crear_dfa(set <estado> estados_,estado estado_inicial_,set <char> alfabeto_)
{
    estados=estados_;
    estado_inicial=estado_inicial_;
    alfabeto=alfabeto_;
}

bool dfa::leer_fichero(char fichero[])
{
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
                if(alfabeto_existe(auxchar)==false){
                    alfabeto.insert(auxchar);
                }
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

bool dfa::alfabeto_existe(char x)
{
    for(set <char>::iterator i=alfabeto.begin(); i!=alfabeto.end(); i++){
        if((*i)==x){
            return 1;
        }
    }
    return 0;
}

ostream& operator<<(ostream &output, const dfa &x)
{
    output << x.get_n_estados() << endl << x.get_inicial().get_id() << endl;
    for(set <estado>::iterator i=x.get_estados().begin(); i!=x.get_estados().end(); i++){
      output << (*i) <<endl;
    }
    return output;
}

set <estado> dfa::get_estados(void) const
{
    return estados;
}

int dfa::get_n_estados(void) const
{
    return estados.size();
}

void dfa::mostrar(void)
{
    cout << endl << "Estados: " << estados.size() << endl;
    cout << "Estado incial: " << estado_inicial.get_id() << " " << endl;
    for(set <estado>::iterator i=estados.begin(); i!=estados.end(); i++){
      (*i).mostrar();
      cout << endl;
    }
}

estado dfa::get_inicial(void) const
{
    return estado_inicial;
}

int dfa::get_id_inicial(void) const
{
    return estado_inicial.get_id();
}

void dfa::analizar_cadena(void)
{
    char cadena[85];
    cout << endl << "Introduzca la cadena que desea analizar: ";
    cin >> cadena;
    cout << endl << "Cadena de entrada: " << cadena << endl;
    cout << "Estado actual    Entrada    Siguiente estado" << endl;
    estado aux = estado_inicial;
    bool reconocido = 1;
    for(int i=0; cadena[i]!='\0'&&reconocido ; i++){
        cout << left;
        cout << setw(17) << setfill(' ') << aux.get_id();
        cout << setw(11) << setfill(' ') << cadena[i];
        if(reconocido=aux.existe(cadena[i])){
            aux = get_estado(aux.estado_siguiente(cadena[i]));
            cout << aux.get_id();
        }else{
            cout << "X";
        }
        cout << endl;
    }
    cout << "Cadena de entrada ";
    if(aux.get_aceptacion()==true&&reconocido){
        cout << "ACEPTADA";
    }else{
        cout << "NO ACEPTADA";
    }
    cout << endl;
}

bool dfa::analizar_cadena_sin(char* cadena) 
{
    estado aux=estado_inicial;
    bool reconocido=1;
    if(cadena[0]!='~'){  
        for(int i=0; cadena[i]!='\0'&&reconocido; i++){
            if(reconocido=aux.existe(cadena[i])){
                aux=get_estado(aux.estado_siguiente(cadena[i]));
            }
        }
    }
    return(aux.get_aceptacion()&&reconocido);
}
    

estado dfa::get_estado(int x)
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

void dfa::mostrar_estados_muerte(void)
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

void dfa::print(set <set <estado> > Cjto)
{
    cout << "{";
    int m=0;
    int x=Cjto.size();
    for(set <set <estado> >::iterator i=Cjto.begin(); i!=Cjto.end(); i++){
        print((*i));
        m++;
	    if(m!=x){
	        cout << ",";
	    }
    }
    cout << "}";
}

void dfa::print(set <estado> Cjto)
{
    cout<<"{";
    int m=0;
    int x=Cjto.size();
	for(set<estado>::iterator i = Cjto.begin(); i != Cjto.end(); i++){
	    cout << (*i).get_id(); 
	    m++;
	    if(m!=x){
	        cout << ", ";
	    }
	}
	cout<<"}";
}

bool dfa::alldim1(set <set <estado> > conjunto)
{
    for(set <set <estado> >::iterator i=conjunto.begin(); i!=conjunto.end(); i++){
        if((*i).size()>1){
            return 0;
        }
    }
    return 1;
}

dfa dfa::minimizar(void)
{
    set <set <estado> > conjuntoviejo;
    set <set <estado> > conjuntonuevo;
    set <estado> acep;
    set <estado> noacep;
    
    for(set <estado>::iterator i=estados.begin(); i!=estados.end(); i++){
        if((*i).get_aceptacion()==true){
            acep.insert((*i));
        }else{
            noacep.insert((*i));
        }
    }
    
    conjuntonuevo.insert(acep);
    conjuntonuevo.insert(noacep);
    
    cout << endl << "Particion inicial: ";
    print(conjuntonuevo);
    cout << endl << endl << endl;
    int x=1;
    
    do{
        
        conjuntoviejo = conjuntonuevo;       
        conjuntonuevo = nueva_particion(conjuntoviejo);
        cout << "P" << x << "= ";
        print(conjuntonuevo);
        cout << endl << endl;
        x++;
        
    }while(!(equal(conjuntoviejo.begin(),conjuntoviejo.end(),conjuntonuevo.begin()))&&!(alldim1(conjuntonuevo)));
    
    cout << endl << "Particion final: ";
    print(conjuntoviejo);
    cout << endl << endl;
    cout << "El DFA minimo tiene " << conjuntoviejo.size() << " estados" << endl;
    
    dfa nv = crear_nueva_dfa(conjuntonuevo);
    return nv;
}

set <set <estado> > dfa::nueva_particion(set <set <estado> > conjuntoviejo)
{
    set <set <estado> > conjuntonuevo;
    set <set <estado> > tmp;
    for(set <set <estado> >::iterator i=conjuntoviejo.begin(); i!=conjuntoviejo.end(); i++){
        tmp.insert((*i));
        if((*i).size()>1){
            tmp = descomponer((*i),conjuntoviejo);
        }
        set_union(conjuntonuevo.begin(),conjuntonuevo.end(),tmp.begin(),tmp.end(), inserter(conjuntonuevo, conjuntonuevo.begin()));
    }
    return conjuntonuevo;
}

set <set <estado> > dfa::descomponer(set <estado> conjuntoestados, set <set <estado> > conjuntoviejo)
{
    set <set <estado> > tmp; 
    tmp.insert(conjuntoestados);
    set <set <estado> > pmt;
    bool mejora=0;
    for(set <char>::iterator i=alfabeto.begin(); i!=alfabeto.end(); i++){
        set <set <estado> > tmp2;
        tmp2 = partir(conjuntoestados,(*i),conjuntoviejo);
        if(tmp2!=tmp&&!mejora){
            set_union(pmt.begin(),pmt.end(),tmp2.begin(),tmp2.end(),inserter(pmt,pmt.begin()));            
            mejora=1;
        }
        cout << "Con el simbolo '" << (*i) << "': " << endl;
        print(tmp2);
        cout << endl << endl;
    }
    if(pmt.size()!=0){
        tmp=pmt;
    }
    return tmp;
}

bool dfa::contenido(set <estado> cactual, int x)
{
    for(set <estado>::iterator i=cactual.begin(); i!=cactual.end(); i++){
        if((*i).get_id()==x){
            cout << "Si" << (*i).get_id() << endl;
            return 1;
        }else{
            cout << "No" << x << endl;
        }
    }
    return 0;
}

set <set <estado> > dfa::partir(set <estado> conjuntoactual, char x, set <set <estado> > conjuntoviejo)
{
    set <set <estado> > xd;
    for(set <set <estado> >::iterator i=conjuntoviejo.begin(); i!=conjuntoviejo.end(); i++){       
        set <estado> tmp2;
        print((*i));
        cout <<endl;
        for(set <estado>::iterator j=conjuntoactual.begin(); j!=conjuntoactual.end(); j++){   
            if((*j).existe(x)){
                if(contenido((*i),(*j).estado_siguiente(x))){
                    tmp2.insert((*j)); 
                }
            }
        }
        if(tmp2.size()!=0){
            xd.insert(tmp2);
        }
    }
    return xd;
}

int dfa::donde(set <set <estado> > conjuntototal, int x)
{
    int id=0;
    for(set <set <estado> >::iterator i=conjuntototal.begin(); i!=conjuntototal.end(); i++){
        for(set <estado>::iterator j=(*i).begin(); j!=(*i).end(); j++){
            if((*j).get_id()==x){
                return id;
            }
        }
        id++;
    }
}           
        
dfa dfa::crear_nueva_dfa(set <set <estado> > conjuntofinal)
{
    set <estado> tmp;
    int id=0;
      
    for(set <set <estado> >::iterator i=conjuntofinal.begin(); i!=conjuntofinal.end();i++) {
        set <estado>::iterator j=(*i).begin();
        bool aceptacion;
        aceptacion = (*j).get_aceptacion();
        set <transicion> f1;
        for(set <char>::iterator k=alfabeto.begin(); k!=alfabeto.end(); k++){
            if((*j).existe((*k))){
                transicion f2((*k),donde(conjuntofinal,(*j).estado_siguiente((*k))));
                f1.insert(f2);
            }
        }
        estado e1(f1,aceptacion,id);
        tmp.insert(e1);
        id++;    
    }
  
    dfa nv;
    nv.crear_dfa(tmp,get_estado(donde(conjuntofinal,get_id_inicial())),alfabeto);
    return nv;
}

set <char> dfa::get_alfabeto(void) const
{
    return alfabeto;
}
    
void dfa::copiar(dfa &x)
{
    estados=x.get_estados();
    estado_inicial=x.get_inicial();
    alfabeto=x.get_alfabeto();
}

void dfa::crear_fichero(char* nombre)
{
    ofstream fichero;
    fichero.open(nombre);
    fichero << get_n_estados() << "\n";
    fichero << get_inicial().get_id();
    for(set <estado>::iterator i=estados.begin(); i!=estados.end(); i++){
        fichero << "\n" << (*i).get_id() << " " << (*i).get_aceptacion() << " " << (*i).get_transiciones().size();
        for(set <transicion>::iterator j=(*i).get_transiciones().begin(); j!=(*i).get_transiciones().end(); j++){
            fichero << " " << (*j).get_entrada() << " " << (*j).get_sig_estado();
        }
    }
    fichero.close();
}
    
void dfa::convert2gr(char* fichero)
{
    set <transicion> S = estado_inicial.get_transiciones();
    if(estado_inicial.get_aceptacion()){
        transicion tmp('~',-5);
        S.insert(tmp);
    }
    vector <set <transicion> > cnt; 
    for(set <estado>::iterator j=estados.begin(); j!=estados.end(); j++){
        set <transicion> nt = (*j).get_transiciones();
        if((*j).get_aceptacion()){
            transicion tmp('~',-5);
            nt.insert(tmp);
        }
        cnt.push_back(nt);
    }    
    gram.crear_gr(cnt,S,alfabeto);
    gram.exporta(fichero);
}
