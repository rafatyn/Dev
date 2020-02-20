#include <vector>
#include <iostream>

using namespace std;

int monedas[] = {200,100,50,20,10,5,2,1};
    
int Seleccion(int &suma, int totalint, int i)
{  
    if(monedas[i]<=(totalint-suma)){
        suma+=monedas[i];
        return i;
    }else{
        return -1;
    }
}

int main(void){
    
    float total;
    
    cout << "Introduzca la cantidad de la que quiera calcular el cambio con el mínimo de monedas: ";
    cin >> total;
    
    int totalint = total*100;
    vector<int> resultado(8,0);   
    
    int i=0;
    int suma = 0;
    
    while(suma<totalint&&i<resultado.size()){
        int x=Seleccion(suma,totalint,i);
        if(x!=-1){
            resultado[x]++;
        }else{
            i++;
        }
    }
            
    if(suma!=totalint){
        cout << "No hay solución" << endl;
    }else{
        cout << "Monedas necesarias: {";
        for(int j=0; j<resultado.size(); j++){
            if(resultado[j]>0){
                if(monedas[j]>=100){
                    cout << " "  << resultado[j] << "x" << monedas[j]/100 << "€";
                }else{
                    cout << " "  << resultado[j] << "x" << monedas[j] << "Céntimos";
                }
            }
        }
        cout << " }" << endl;  
    }
        
}