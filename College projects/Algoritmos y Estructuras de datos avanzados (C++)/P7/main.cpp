#include "Arbol.hpp"

using namespace std;

int dni::comp = 0;

int main (void) {
        
    int o;
    cout << "Que modo desea usar?" << endl << "0. Demostracion" << endl << "1. Estadistica" << endl << "Opcion: ";
    cin >> o;
    if(o==0){
        int u=1;
        arbol<dni> x; 
        dni r;
        while(u!=0){
            cout << endl << "Que desea hacer?" << endl << "0. Salir" << endl << "1. Insertar elemento" << endl << "2. Eliminar elemento" << endl << "Opcion: ";
            cin >> u;
            cout << endl;
            long int e;
            switch(u){
                case 0:
                break;
                case 1:
                    cout << "Que elemento desea insertar?: ";
                    cin >> e;
                    cout << endl;
                    r.setx(e);
                    x.insertar(r);
                    x.write();
                break;
                case 2:
                    cout << "Que elemento desea eliminar?: ";
                    cin >> e;
                    cout << endl;
                    r.setx(e);
                    x.eliminar(r);
                    x.write();
                break;
                default:
                    cout << "Opcion no valida";
                break;
            }
        }
    }else if(o==1){
        int n,np;
        cout << endl << "De que tamaño desea que sea el arbol?: ";
        cin >> n;
        cout << "Cuantas pruebas desea hacer?: ";
        cin >> np;
        cout << endl;
        
        
        int min[2] = {0,0};
        int max[2] = {0,0};
        int sum[2] = {0,0};        
        
        srand(time(NULL));
        
        for(int j=0; j<np; j++){
                        
            arbol<dni> x;
            dni* vdni = new dni [n];
                
            for(int i=0; i<n; i++){
                long int dn = (rand() % 50000000) + 30000000;
                dni pepe(dn);
                vdni[i] = pepe;
            }
            
            dni::comp = 0;
            
            for(int i=0; i<n; i++){
                x.insertar(vdni[i]);
            }
            
            if(j==0||dni::comp<min[0]){
                min[0]=dni::comp;
            }
            if(j==0||dni::comp>max[0]){
                max[0]=dni::comp;
            }
            sum[0]+=dni::comp;
                        
            dni::comp = 0;
                        
            for(int i=0; i<n; i++){
                x.busqueda(vdni[i]);
            }
                        
            if(j==0||dni::comp<min[1]){
                min[1]=dni::comp;
            }
            if(j==0||dni::comp>max[1]){
                max[1]=dni::comp;
            }
            sum[1]+=dni::comp;
        }
        
        cout << endl << "             Minimo    Media    Maximo" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Insercion     " << min[0] << "       "  << sum[0]/np << "        " << max[0] << endl;
        cout << "Busqueda      " << min[1] << "       "  << sum[1]/np << "        " << max[1] << endl;
        
    }
}