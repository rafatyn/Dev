#include "Pila.hpp"
#include "Cola.hpp"
#include "Vector.hpp"
#include "Numeros.hpp"
#include "Real.hpp"
#include "Entero.hpp"
#include "Rad.hpp"
#include "Complex.hpp"
#include "Calculadora.hpp"
#include <cstring>
#include <cstdlib> 
#include <sstream>

int comprobar(char* cadena)
{
    try {
        int t=0;
        
        if(cadena[0]=='"'){
            t=10;
        }else{
            if(cadena[0]=='('){
                t=20;
            }else{
                for(int i=0; i<strlen(cadena); i++){
                    if(cadena[i]=='.'){
                        t=5;
                    }
                }
            }
        }
        
        return t;
    }
    catch (exception& e)
    {
        cerr << "Excepción comp: " << e.what() << endl;
        
        throw e;
    }
}

int main(void){
    
    try {
        int op;
        string axx;
        cout << "En que tipo de estructura desea almacenar los datos?" << endl << "1.Pila" << endl << "2.Cola" << endl << "3.Vector" << endl << "4.Lista" << endl << "Opcion: ";
        getline(cin,axx);
        op=atoi(axx.c_str());
        
        string aux;
        cout << endl << "Introduzca la ecuación a realizar: ";
        getline(cin,aux);
    
        char *ent = new char[aux.length() + 1];
        strcpy(ent, aux.c_str());
        char *pch = strtok(ent," ");
        char *pp;
        char *pp2;
        int i=1;
        
        pila<numero*> st;
        cola<numero*> co;
        vector<numero*> vc(aux.length()-aux.length()/2);
        sll<numero*> sl;
        calc<numero*> cl;
        numero* aux1=NULL;
        numero* aux2=NULL;
        
        switch(op){
            case 1:
                while(pch!=NULL){
                    switch(*pch){
                        case '+':
                            aux1 = st.pop();
                            aux2 = st.pop();
                            aux2 = cl.suma(aux1, aux2);
                            st.push(aux2);
                        break;
                        case '-':
                            aux1 = st.pop();
                            aux2 = st.pop();
                            aux2 = cl.resta(aux2, aux1);
                            st.push(aux2);
                        break;
                        case '*':
                            aux1 = st.pop();
                            aux2 = st.pop();
                            aux2 = cl.mult(aux1, aux2);
                            st.push(aux2);
                        break;
                        case '/':
                            aux1 = st.pop();
                            aux2 = st.pop();
                            aux2 = cl.divi(aux2, aux1);
                            st.push(aux2);
                        break;
                        default:
                            int x = comprobar(pch);
                            switch(x){
                                case 0:
                                    st.push(new entero(atoi(pch)));                                
                                break;
                                case 5:
                                    st.push(new real(atof(pch)));
                                break;
                                case 10:
                                    pp = new char[strlen(pch) - 1];
                                    for(int i=1; i<strlen(pch); i++){
                                        pp[i-1]=pch[i];
                                    }
                                    pch = strtok(NULL," ");
                                    pch = strtok(NULL," ");
                                    pp2 = new char[strlen(pch) - 1];
                                    strncpy (pp2, pch, strlen(pch) - 2);
                                    st.push(new complex(atoi(pp),atoi(pp2)));
                                break;
                                case 20:
                                    pp = new char[strlen(pch) - 1];
                                    for(int i=1; i<strlen(pch); i++){
                                        pp[i-1]=pch[i];
                                    }
                                    pch = strtok(NULL," ");
                                    pch = strtok(NULL," ");
                                    pp2 = new char[strlen(pch) - 1];
                                    strncpy (pp2, pch, strlen(pch) - 1);
                                    st.push(new rad(atoi(pp),atoi(pp2)));
                                break;
                                default:
                                    cout << "No se reconoce el numero introducido" << endl;
                            }  
                        break;
                    }
                    pch = strtok(NULL," ");
                }
                cout << "Resultado: ";
                st.write(cout);
            break;
            case 2:
                while(pch!=NULL){
                    switch(*pch){
                        case '+':
                            aux1 = co.pop();
                            aux2 = co.pop();
                            aux2 = cl.suma(aux1, aux2);
                            co.push(aux2);
                        break;
                        case '-':
                            aux1 = co.pop();
                            aux2 = co.pop();
                            aux2 = cl.resta(aux1, aux2);
                            co.push(aux2);
                        break;
                        case '*':
                            aux1 = co.pop();
                            aux2 = co.pop();
                            aux2 = cl.mult(aux1, aux2);
                            co.push(aux2);
                        break;
                        case '/':
                            aux1 = co.pop();
                            aux2 = co.pop();
                            aux2 = cl.divi(aux1, aux2);
                            co.push(aux2);
                        break;
                        default:
                            int x = comprobar(pch);
                            switch(x){
                                case 0:
                                    co.push(new entero(atoi(pch)));                                
                                break;
                                case 5:
                                    co.push(new real(atof(pch)));
                                break;
                                case 10:
                                    pp = new char[strlen(pch) - 1];
                                    for(int i=1; i<strlen(pch); i++){
                                        pp[i-1]=pch[i];
                                    }
                                    pch = strtok(NULL," ");
                                    pch = strtok(NULL," ");
                                    pp2 = new char[strlen(pch) - 1];
                                    strncpy (pp2, pch, strlen(pch) - 2);
                                    co.push(new complex(atoi(pp),atoi(pp2)));
                                break;
                                case 20:
                                    pp = new char[strlen(pch) - 1];
                                    for(int i=1; i<strlen(pch); i++){
                                        pp[i-1]=pch[i];
                                    }
                                    pch = strtok(NULL," ");
                                    pch = strtok(NULL," ");
                                    pp2 = new char[strlen(pch) - 1];
                                    strncpy (pp2, pch, strlen(pch) - 1);
                                    co.push(new rad(atoi(pp),atoi(pp2)));
                                break;
                                default:
                                    cout << "No se reconoce el numero introducido" << endl;
                            }   
                        break;
                    }
                    pch = strtok(NULL," ");
                }
                cout << "Resultado: ";
                co.write(cout);
            break;
            case 3:
                while(pch!=NULL){
                    switch(*pch){
                        case '+':
                            i--;
                            aux1 = vc.getdato(i);
                            vc.setdato(NULL,i);
                            i--;
                            aux2 = vc.getdato(i);
                            vc.setdato(NULL,i);
                            aux2 = cl.suma(aux1, aux2);
                            vc.setdato(aux2, i);
                            i++;
                        break;
                        case '-':
                            i--;
                            aux1 = vc.getdato(i);
                            vc.setdato(NULL,i);
                            i--;
                            aux2 = vc.getdato(i);
                            vc.setdato(NULL,i);
                            aux2 = cl.resta(aux2, aux1);
                            vc.setdato(aux2, i);
                            i++;
                        break;
                        case '*':
                            i--;
                            aux1 = vc.getdato(i);
                            vc.setdato(NULL,i);
                            i--;
                            aux2 = vc.getdato(i);
                            vc.setdato(NULL,i);
                            aux2 = cl.mult(aux1, aux2);
                            vc.setdato(aux2, i);
                            i++;
                        break;
                        case '/':
                            i--;
                            aux1 = vc.getdato(i);
                            vc.setdato(NULL,i);
                            i--;
                            aux2 = vc.getdato(i);
                            vc.setdato(NULL,i);
                            aux2 = cl.divi(aux2, aux1);
                            vc.setdato(aux2, i);
                            i++;
                        break;
                        default:
                            entero et;
                            complex c;
                            rad d;
                            real r;
                            int x = comprobar(pch);
                            switch(x){
                                case 0:
                                    vc.setdato(new entero(atoi(pch)),i);
                                break;
                                case 5:
                                    vc.setdato(new real(atof(pch)),i);
                                break;
                                case 10:
                                    pp = new char[strlen(pch) - 1];
                                    for(int x=1; x<strlen(pch); x++){
                                        pp[x-1]=pch[x];
                                    }
                                    pch = strtok(NULL," ");
                                    pch = strtok(NULL," ");
                                    pp2 = new char[strlen(pch) - 1];
                                    strncpy (pp2, pch, strlen(pch) - 2);
                                    vc.setdato(new complex(atoi(pp),atoi(pp2)),i);
                                break;
                                case 20:
                                    pp = new char[strlen(pch) - 1];
                                    for(int x=1; x<strlen(pch); x++){
                                        pp[x-1]=pch[x];
                                    }
                                    pch = strtok(NULL," ");
                                    pch = strtok(NULL," ");
                                    pp2 = new char[strlen(pch) - 1];
                                    strncpy (pp2, pch, strlen(pch) - 1);
                                    vc.setdato(new rad(atoi(pp),atoi(pp2)),i);
                                break;
                                default:
                                    cout << "No se reconoce el numero introducido" << endl;
                            }
                            i++;  
                        break;
                    }
                    pch = strtok(NULL," ");
                }
                cout << "Resultado: ";
                vc.write(cout, i-1);
            break;
            case 4:
                while(pch!=NULL){
                    switch(*pch){
                        case '+':
                            aux1 = sl.extractini()->getval();
                            aux2 = sl.extractini()->getval();
                            aux2 = cl.suma(aux1, aux2);
                            sl.insertini(new nodo<numero*>(aux2));
                        break;
                        case '-':
                            aux1 = sl.extractini()->getval();
                            aux2 = sl.extractini()->getval();
                            aux2 = cl.resta(aux2, aux1);
                            sl.insertini(new nodo<numero*>(aux2));
                        break;
                        case '*':
                            aux1 = sl.extractini()->getval();
                            aux2 = sl.extractini()->getval();
                            aux2 = cl.mult(aux1, aux2);
                            sl.insertini(new nodo<numero*>(aux2));
                        break;
                        case '/':
                            aux1 = sl.extractini()->getval();
                            aux2 = sl.extractini()->getval();
                            aux2 = cl.divi(aux2, aux1);
                            sl.insertini(new nodo<numero*>(aux2));
                        break;
                        default:
                            entero et;
                            complex c;
                            rad d;
                            real r;
                            int x = comprobar(pch);
                            switch(x){
                                case 0:
                                    sl.insertini(new nodo<numero*>(new entero(atoi(pch))));
                                break;
                                case 5:
                                    sl.insertini(new nodo<numero*>(new real(atof(pch))));
                                break;
                                case 10:
                                    pp = new char[strlen(pch) - 1];
                                    for(int i=1; i<strlen(pch); i++){
                                        pp[i-1]=pch[i];
                                    }
                                    pch = strtok(NULL," ");
                                    pch = strtok(NULL," ");
                                    pp2 = new char[strlen(pch) - 1];
                                    strncpy (pp2, pch, strlen(pch) - 2);
                                    sl.insertini(new nodo<numero*>(new complex(atoi(pp),atoi(pp2))));
                                break;
                                case 20:
                                    pp = new char[strlen(pch) - 1];
                                    for(int i=1; i<strlen(pch); i++){
                                        pp[i-1]=pch[i];
                                    }
                                    pch = strtok(NULL," ");
                                    pch = strtok(NULL," ");
                                    pp2 = new char[strlen(pch) - 1];
                                    strncpy (pp2, pch, strlen(pch) - 1);
                                    sl.insertini(new nodo<numero*>(new rad(atoi(pp),atoi(pp2))));
                                break;
                                default:
                                    cout << "No se reconoce el numero introducido" << endl;
                            }  
                        break;
                    }
                    pch = strtok(NULL," ");
                }
                cout << "Resultado: ";
                sl.write(cout);
            break;
        }
    }
    catch (int& e)
    {
        cerr << "Error" << endl;
        
        throw 10;
    }
    catch (exception& e)
    {
        cerr << "Excepción: " << e.what() << endl;
        
        throw e;
    }
}