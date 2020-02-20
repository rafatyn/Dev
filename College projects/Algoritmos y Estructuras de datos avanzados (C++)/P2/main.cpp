#include "Pila.hpp"
#include <cstring>
#include <cstdlib> 
#include <sstream>

int main(void){
    
    string aux;
    cout << "Se puede introducir numeros enteros, decimales, complejos y racionales (no se pueden combinar entre ellos)" << endl << "Los numeros decimales se introducen con un '.', los complejos entre \"\" y sin espacio al principio y al final, y los racionales dentro de () sin espacio al principio y al final" << endl; 
    cout << "Introduzca la ecuación a realizar: ";
    getline(cin,aux);
    bool f=false;
    int t=0;
    
    char *ent = new char[aux.length() + 1];
    strcpy(ent, aux.c_str());
    char *pch = strtok(ent," ");
    
    if(pch[0]=='"'){
        t=1;
    }
    if(pch[0]=='('){
        t=2;
    }    
    for(int i=0; i<strlen(pch); i++){
        if(pch[i]=='.'){
            f=1;
        }
    }
    
    switch(t){
        case 0:
            if(f){
                pila<float> p;
                calc<float> c;
                float x,y,z;
                while(pch!=NULL){
                    switch(*pch) {
                        case '+':
                            x=p.pop();
                            y=p.pop();
                            z=c.suma(x,y);
                            p.push(z);
                        break;
                        case '-':
                            x=p.pop();
                            y=p.pop();
                            z=y-x;
                            p.push(z);
                        break;
                        case '*':
                            x=p.pop();
                            y=p.pop();
                            z=x*y;
                            p.push(z);
                        break;
                        case '/':
                            x=p.pop();
                            y=p.pop();
                            z=y/x;
                            p.push(z);
                        break;
                        default:
                            p.push(atof(pch));
                        break;
                    }
                    pch = strtok(NULL," ");
                }
                cout << "Resultado: ";
                p.write(cout);
            }else{
                pila<int> p;
                calc<int> c;
                int x,y,z;
                while(pch!=NULL){
                    switch(*pch) {
                        case '+':
                            x=p.pop();
                            y=p.pop();
                            z=c.suma(x,y);
                            p.push(z);
                        break;
                        case '-':
                            x=p.pop();
                            y=p.pop();
                            z=y-x;
                            p.push(z);
                        break;
                        case '*':
                            x=p.pop();
                            y=p.pop();
                            z=x*y;
                            p.push(z);
                        break;
                        case '/':
                            x=p.pop();
                            y=p.pop();
                            z=y/x;
                            p.push(z);
                        break;
                        default:
                            p.push(atoi(pch));
                        break;
                    }
                    pch = strtok(NULL," ");
                }
                cout << "Resultado: ";
                p.write(cout);
            }
        break;
        case 1:
            if(f){
                pila<complex<float> > p;
                calc<complex<float> > c;
                complex<float> x,y,z;
                while(pch!=NULL){
                    switch(*pch) {
                        case '+':
                            x=p.pop();
                            y=p.pop();
                            z=c.suma(x,y);
                            p.push(z);
                        break;
                        case '-':
                            x=p.pop();
                            y=p.pop();
                            z=y-x;
                            p.push(z);
                        break;
                        case '*':
                            x=p.pop();
                            y=p.pop();
                            z=x*y;
                            p.push(z);
                        break;
                        case '/':
                            x=p.pop();
                            y=p.pop();
                            z=y/x;
                            p.push(z);
                        break;
                        default:       
                            float tmp1,tmp2;
                            char *pp = new char[strlen(pch) - 1];
                            for(int i=1; i<strlen(pch); i++){
                                pp[i-1]=pch[i];
                            }
                            tmp1=atof(pp);
                            pch = strtok(NULL," ");
                            pch = strtok(NULL," ");
                            char *pp2 = new char[strlen(pch) - 1];
                            strncpy (pp2, pch, strlen(pch) - 1);
                            tmp2=atof(pp2);
                            complex<float> tmp(tmp1,tmp2);
                            p.push(tmp);
                        break;
                    }
                    pch = strtok(NULL," ");
                }
                cout << "Resultado: ";
                p.write(cout);
            }else{
                pila<complex<int> > p;
                calc<complex<int> > c;
                complex<int> x,y,z;
                while(pch!=NULL){
                    switch(*pch) {
                        case '+':
                            x=p.pop();
                            y=p.pop();
                            z=c.suma(x,y);
                            p.push(z);
                        break;
                        case '-':
                            x=p.pop();
                            y=p.pop();
                            z=y-x;
                            p.push(z);
                        break;
                        case '*':
                            x=p.pop();
                            y=p.pop();
                            z=x*y;
                            p.push(z);
                        break;
                        case '/':
                            x=p.pop();
                            y=p.pop();
                            z=y/x;
                            p.push(z);
                        break;
                        default:     
                            int tmp1,tmp2;
                            char *pp = new char[strlen(pch) - 1];
                            for(int i=1; i<strlen(pch); i++){
                                pp[i-1]=pch[i];
                            }
                            tmp1=atoi(pp);
                            pch = strtok(NULL," ");
                            pch = strtok(NULL," ");
                            char *pp2 = new char[strlen(pch) - 1];
                            strncpy (pp2, pch, strlen(pch) - 1);
                            tmp2=atoi(pp2);
                            complex<int> tmp(tmp1,tmp2);
                            p.push(tmp);
                        break;
                    }
                    pch = strtok(NULL," ");
                }
                cout << "Resultado: ";
                p.write(cout);
            }
        break;
        case 2:
            if(f){
                pila<rad<float> > p;
                calc<rad<float> > c;
                rad<float> x,y,z;
                while(pch!=NULL){
                    switch(*pch) {
                        case '+':
                            x=p.pop();
                            y=p.pop();
                            z=c.suma(x,y);
                            p.push(z);
                        break;
                        case '-':
                            x=p.pop();
                            y=p.pop();
                            z=y-x;
                            p.push(z);
                        break;
                        case '*':
                            x=p.pop();
                            y=p.pop();
                            z=x*y;
                            p.push(z);
                        break;
                        case '/':
                            x=p.pop();
                            y=p.pop();
                            z=y/x;
                            p.push(z);
                        break;
                        default:    
                            float tmp1,tmp2;
                            char *pp = new char[strlen(pch) - 1];
                            for(int i=1; i<strlen(pch); i++){
                                pp[i-1]=pch[i];
                            }
                            tmp1=atof(pp);
                            pch = strtok(NULL," ");
                            pch = strtok(NULL," ");
                            char *pp2 = new char[strlen(pch) - 1];
                            strncpy (pp2, pch, strlen(pch) - 1);
                            tmp2=atof(pp2);
                            rad<float> tmp(tmp1,tmp2);
                            p.push(tmp);
                        break;
                    }
                    pch = strtok(NULL," ");
                }
                cout << "Resultado: ";
                p.write(cout);
            }else{
                pila<rad<int> > p;
                calc<rad<int> > c;
                rad<int> x,y,z;
                while(pch!=NULL){
                    switch(*pch) {
                        case '+':
                            x=p.pop();
                            y=p.pop();
                            z=c.suma(x,y);
                            p.push(z);
                        break;
                        case '-':
                            x=p.pop();
                            y=p.pop();
                            z=y-x;
                            p.push(z);
                        break;
                        case '*':
                            x=p.pop();
                            y=p.pop();
                            z=x*y;
                            p.push(z);
                        break;
                        case '/':
                            x=p.pop();
                            y=p.pop();
                            z=y/x;
                            p.push(z);
                        break;
                        default:
                            int tmp1,tmp2;    
                            char *pp = new char[strlen(pch) - 1];
                            for(int i=1; i<strlen(pch); i++){
                                pp[i-1]=pch[i];
                            }
                            tmp1=atoi(pp);
                            pch = strtok(NULL," ");
                            pch = strtok(NULL," ");
                            char *pp2 = new char[strlen(pch) - 1];
                            strncpy (pp2, pch, strlen(pch) - 1);
                            tmp2=atoi(pp2);
                            rad<int> tmp(tmp1,tmp2);
                            p.push(tmp);
                        break;
                    }
                    pch = strtok(NULL," ");
                }
                cout << "Resultado: ";
                p.write(cout);
            }
        break;
    }
}