#include "Hash.hpp"

int main(void)
{    
    int n, m, d, e;
    
    cout << "De que tamaño desea que sea la tabla hash?" << endl << "Filas: ";
    cin >> m;
    
    cout << "Columnas: ";
    cin >> n;
    
    cout << endl << "Que funcion de dispersion desea usar?" << endl << "1. Modulo" << endl << "2. Pseudo-aleatoria" << endl << "Opcion: ";
    cin >> d;
    
    cout << endl << "Que funcion de exploracion desea usar?" << endl << "1. Lineal" << endl << "2. Cuadratica" << endl << "3. Dispersion doble" << endl << "4. Redispersion" << endl << "Opcion: ";
    cin >> e;
    
    float f;
    cout << endl << "Introduzca el factor: ";
    cin >> f;
    
    int np;
    cout << "Introduzca el numero de pruebas: ";
    cin >> np;
    cout << endl;
    
    cout << "Celdas: " << n << "    " << "Bloques: " << m << "    " << "Exploracion: ";
    
    switch(e){
        case 1:
            cout << "Lineal";
        break;
        case 2:
            cout << "Cuadratica";
        break;
        case 3:
            cout << "Dispersion doble";
        break;
        case 4:
            cout << "Redispersion";
        break;
    }
    
    cout << "    " << "Carga: " << f << "    " << "Numero de pruebas: " << np << endl << endl;
    
    int pos=0;
    hash<dni> p(n,m,d,e);
    
    int min=0;
    int max=0;
    float med=0;
    float smed=0;
    
    int bas=0;
    float basf=0;
    
    int N=f*n*m;
    dni* vdni = new dni [2*N];
    
    srand(time(NULL));
    
    for(int i=0; i<2*N; i++){
        long int dn = (rand() % 50000000) + 30000000;
        dni pepe(dn);
        vdni[i] = pepe;
    }
    
    for(int i=0; i<N; i++){
        p.insertar(vdni[i],bas,bas,basf);
    }
        
    for(int i=1; i<=np; i++){
        
        int minl=0;
        int maxl=0;
        float medl=0;
        
        int var = rand() % N;
        p.buscar(vdni[(var)],pos,maxl,minl,medl);
        
        if(minl<min) min=minl;
        if(i==1) min=minl;
        if(maxl>max) max=maxl;
        smed += medl;
        med = smed/i;
    }
    
    cout << "Busqueda:     " << "Minimo: " << min << "    " << "Maximo: " << max << "    " << "Media: " << med << endl;
    
    min = max = med = smed = bas = basf = 0;
    
    for(int i=1; i<=np; i++){
        
        int minl=0;
        int maxl=0;
        float medl=0;
        
        int var = rand() % 2*N + N;
        p.insertar(vdni[(var)],maxl,minl,medl);
        
        if(minl<min) min=minl;
        if(i==1) min=minl;
        if(maxl>max) max=maxl;
        smed += medl;
        med = smed/i;
    }
    
    cout << "Insercion:     " << "Minimo: " << min << "    " << "Maximo: " << max << "    " << "Media: " << med << endl;
}