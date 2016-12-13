#ifndef BUS_H
#define BUS_H

#include "Vector.hpp"

using namespace std;

template<class T>
void insercion(vector<T> &x, bool d)
{
    if(d){
        cout << "Vector inicial:  ";
        x.write(cout);
        cout << endl << endl;
        cin.get();
    }
    for(int i=0; i<x.getn(); i++){
        if(d){
            x.write(cout,i);
            cout << endl << "Presiona enter para continuar";
            cin.get();
            cout << endl;
        }
        insertar(x,x.getd(i),i);
        
    }
    
    if(d){
        cout << "Vector final ordenado:  ";
        x.write(cout);
        cout << endl << endl;
    }
}

template<class T>
void insertar(vector<T> &v, T x, int i)
{
    int j=0;
    
    while((x > v.getd(j))&&(j<i)){
        j++;
    }
    
    for(int f=i-1; f>=j; f--){
        v.setd(v.getd(f),f+1);
    }    
    v.setd(x,j);
}


template<class T>
void burbuja(vector<T> &v, bool d)
{
    bool comp=1;
    if(d) cin.get();
    
    for(int i=0; i<v.getn()&&comp; i++){
        if(d) cout << "Paso " << i+1 << ":" << endl;
        comp=0;
        for(int j=v.getn()-2; j>=0; j--){
            if(d){
                v.write(cout,j,j+1);
                cout << endl << "Presiona enter para continuar";
                cin.get();
                cout << endl;
            }
            if(v.getd(j+1)<v.getd(j)){
                comp=1;
                dni tmp = v.getd(j);
                v.setd(v.getd(j+1),j);
                v.setd(tmp,j+1);
            }
        }
        if(d){
            cout << "Vector despues del paso " << i << ":  ";
            v.write(cout);
            cout << endl << "Presiona enter para continuar";
            cin.get();
            cout << endl;
        }
    }
}

template<class T>
void ordenacionrapida(vector<T> &v, int ini, int fin, bool d)
{
    T p = v.getd((ini+fin)/2);
    int i=ini; 
    int j=fin;
            
    if(d&&ini==0&&fin==v.getn()-1) cin.get();
    
    while(i<j){
        while(v.getd(i)<p) {i++;}
        while(v.getd(j)>p) {j--;}
        if(d){
            v.write(cout,i,j,p,ini,fin);
            cout << endl << "Presiona enter para continuar";
            cin.get();
            cout << endl;
        }
        if(i<j){
            T aux=v.getd(i);
            v.setd(v.getd(j),i);
            v.setd(aux,j);
            i++;
            j--;
        }
    }
        
    if((fin-ini)>1){
        if(ini<j) ordenacionrapida(v,ini,j,d);
        if(i<fin) ordenacionrapida(v,i,fin,d);
    }
}

template<class T>
void ordenacionunion(vector<T> &v, int ini, int fin, bool d)
{        
    int centro = (ini+fin)/2;
    
    if(d&&ini==0&&fin==v.getn()-1) cin.get();
    
    if(d){  
        cout << "Subvector:  ";
        v.writeu(cout,ini,fin);
        cout << endl << "Presiona enter para continuar";
        cin.get();
        cout << endl;
    }
    
    if((fin-ini)>1){
        ordenacionunion(v,ini,centro,d);
        ordenacionunion(v,centro+1,fin,d);
    }
        
    unionord(v,ini,centro,fin);
    
    if(fin-ini>1){
        if(d){
            cout << "Union:  ";
            v.writeu(cout,ini,fin);
            cout << endl << "Presiona enter para continuar";
            cin.get();
            cout << endl;
        }
    }
}

template<class T>
void unionord(vector<T> &v, int ini, int centro, int fin) 
{
    vector<T> pepe((fin-ini)+1);
    int i=ini;
    int j=centro+1;
    int k=ini;
    
    while ((i<=centro)&&(j<=fin)){
        if(v.getd(i)<v.getd(j)){
            pepe.setd(v.getd(i),k);
            i++;
        }else{
            pepe.setd(v.getd(j),k);
            j++;
        }
        k++;
    }
    
    if(i>centro){
        while(j<=fin){
            pepe.setd(v.getd(j),k);
            j++;
            k++;
        }
    }else{
        while(i<=centro){
            pepe.setd(v.getd(i),k);
            i++;
            k++;
        }
    }
    
    for(int w=ini; w<=fin; w++){
        v.setd(pepe.getd(w),w);
    }
}

template<class T>
void ordenacionincrementos(vector<T> &v, float alfa, bool d)
{
    if(d) cin.get();
    int delta = v.getn();
    while(delta>1){
        delta=delta*alfa;
        if(delta<1) delta=1;
        if(d) cout << "Para delta " << delta << ":" << endl;
        orddelta(v,delta,d);
    }
}

template<class T>
void orddelta(vector<T> &v, int delta, bool d)
{
    for(int i=delta; i<v.getn(); i++){
        T x=v.getd(i);
        int j=i;
        if(d){
            v.write(cout,j-delta,i);
            cout << endl << "Presiona enter para continuar";
            cin.get();
            cout << endl;
        }
        while((j>=delta)&&(x<v.getd(j-delta))){
            if(j!=i&&d){
                v.write(cout,j-delta,i);
                cout << endl << "Presiona enter para continuar";
                cin.get();
                cout << endl;
            }
            v.setd(v.getd(j-delta),j);
            j=j-delta;
        }
        v.setd(x,j);
    }
    
}

#endif //BUS_H