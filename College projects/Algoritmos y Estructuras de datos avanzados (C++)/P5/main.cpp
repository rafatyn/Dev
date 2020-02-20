#define LINUX
#include "Busqueda.hpp"
#include <cstdlib>

using namespace std;

int dni::comp = 0;

int main(void){
    
    int m,e,t;
    srand(time(NULL));
    cout << "Que modo desea ejecutar?" << endl << "1. Demo" << endl << "2. Estadistica" << endl << "Opcion: ";
    cin >> m;
    cout << endl;
    
    
    cout << "De que tamaño desea que sea el vector?: ";
    cin >> t;
        
    
        
    if(m==1){        
        while(e!=0){            
            
            vector<dni> v(t);
            for(int i=0; i<t; i++){
                long int dn = (rand() % 50000000) + 30000000;
                dni pepe(dn);
                v.setd(pepe, i);
            }
            
            cout << endl << "Con que metodo desea ordenar el vector?" << endl << "0. Salir" << endl << "1. Insercion" << endl << "2. Burbuja" << endl << "3. QuickSort" << endl << "4. MergeSort" << endl << "5. ShellSort" << endl << "Opcion: ";
            cin >> e;
            cout << endl;
            switch(e){
                case 0:
                break;
                case 1:
                    insercion(v,1);
                break;
                case 2:
                    burbuja(v,1);
                break;
                case 3:
                    cout << "Vector inicial: ";
                    v.write(cout);
                    cout << endl << endl;
                    ordenacionrapida(v,0,v.getn()-1,1);
                    cout << endl << "Vector final ordenado: ";
                    v.write(cout);
                    cout << endl;
                break;
                case 4:
                    cout << "Vector inicial: ";
                    v.write(cout);
                    cout << endl << endl;
                    ordenacionunion(v,0,v.getn()-1,1);
                    cout << "Vector final ordenado: ";
                    v.write(cout);
                    cout << endl;
                break;
                case 5:
                    float a;
                    cout << "Con que alfa desea hacer la ordenacion (entre 0 y 1): ";
                    cin >> a;
                    cout << endl << "Vector inicial: ";
                    v.write(cout);
                    cout << endl << endl;
                    ordenacionincrementos(v,a,1);
                    cout << "Vector final ordenado: ";
                    v.write(cout);
                    cout << endl;
                break;
                default:
                    cout << "La opcion introducida no es valida";
                break;
            }
        }
    }else if(m==2){
        
        int np=0;
        
        cout << "Cuantas pruebas desea hacer?: ";
        cin >> np;
        
        float a;
        cout << "Con que alfa desea hacer la ordenacion (entre 0 y 1): ";
        cin >> a;
        
        int min[5] = {0,0,0,0,0};
        int max[5] = {0,0,0,0,0};
        int sum[5] = {0,0,0,0,0};
        
        for(int j=0; j<np; j++){
            
            vector<dni> v(t);
            
            for(int i=0; i<t; i++){
                long int dn = (rand() % 50000000) + 30000000;
                dni pepe(dn);
                v.setd(pepe, i);
            }
            
            dni::comp = 0;
            
            insercion(v,0);
            
            if(j==0||dni::comp<min[0]){
                min[0]=dni::comp;
            }
            if(j==0||dni::comp>max[0]){
                max[0]=dni::comp;
            }
            sum[0]+=dni::comp;
            
            for(int i=0; i<t; i++){
                long int dn = (rand() % 50000000) + 30000000;
                dni pepe(dn);
                v.setd(pepe, i);
            }
            
            dni::comp = 0;
            
            burbuja(v,0);
            
            if(j==0||dni::comp<min[1]){
                min[1]=dni::comp;
            }
            if(j==0||dni::comp>max[1]){
                max[1]=dni::comp;
            }
            sum[1]+=dni::comp;
            
            for(int i=0; i<t; i++){
                long int dn = (rand() % 50000000) + 30000000;
                dni pepe(dn);
                v.setd(pepe, i);
            }
            
            dni::comp = 0;
            
            ordenacionrapida(v,0,v.getn()-1,0);
            
            if(j==0||dni::comp<min[2]){
                min[2]=dni::comp;
            }
            if(j==0||dni::comp>max[2]){
                max[2]=dni::comp;
            }
            sum[2]+=dni::comp;
            
            for(int i=0; i<t; i++){
                long int dn = (rand() % 50000000) + 30000000;
                dni pepe(dn);
                v.setd(pepe, i);
            }
            
            dni::comp = 0;
            
            ordenacionunion(v,0,v.getn()-1,0);
            
            if(j==0||dni::comp<min[3]){
                min[3]=dni::comp;
            }
            if(j==0||dni::comp>max[3]){
                max[3]=dni::comp;
            }
            sum[3]+=dni::comp;
            
            for(int i=0; i<t; i++){
                long int dn = (rand() % 50000000) + 30000000;
                dni pepe(dn);
                v.setd(pepe, i);
            }
            
            dni::comp = 0;
            
            ordenacionincrementos(v,a,0);
            
            if(j==0||dni::comp<min[4]){
                min[4]=dni::comp;
            }
            if(j==0||dni::comp>max[4]){
                max[4]=dni::comp;
            }
            sum[4]+=dni::comp;
        }
        
        cout << endl << "          Minimo    Media    Maximo" << endl;
        cout << "Metodo1     " << min[0] << "       "  << sum[0]/np << "        " << max[0] << endl;
        cout << "Metodo2     " << min[1] << "       "  << sum[1]/np << "        " << max[1] << endl;
        cout << "Metodo3     " << min[2] << "       "  << sum[2]/np << "        " << max[2] << endl;
        cout << "Metodo4     " << min[3] << "       "  << sum[3]/np << "        " << max[3] << endl;
        cout << "Metodo5     " << min[4] << "       "  << sum[4]/np << "        " << max[4] << endl;
    }    
}