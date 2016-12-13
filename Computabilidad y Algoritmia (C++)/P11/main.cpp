#include <iostream>
#include <vector>

using namespace std;

vector<int> fusionar(vector<int> v, vector<int> x, vector<int> y)
{
    int i=0,j=0,k=0;
    for(k; i<x.size()&&j<y.size(); k++){
        if(x[i]>=y[j]){
            v[k]=y[j];
            j++;
        }else{
            v[k]=x[i];
            i++;
        }     
    }
    if(i==x.size()){
        for(j; j<y.size(); j++){
            v[k]=y[j];
            k++;
        }
    }else{
        for(i; i<x.size(); i++){
            v[k]=x[i];
            k++;
        }
    }
    return v; 
}

vector<int> ordenar_recursivo(vector<int> v, bool verbose)
{
    if(v.size()<=2){
        if(v.size()==2){
            if(v[0]>v[1]){
                int aux=v[0];
                v[0]=v[1];
                v[1]=aux;
            }    
        }
    }else{
        
        int mitad=v.size()/2;
        
        vector<int> z(mitad,0);
        vector<int> q(v.size()-mitad,0);
        
        for(int i=0; i<z.size(); i++){
            z[i]=v[i];
        }
        for(int i=0; i<q.size();i++){
            q[i]=v[i+mitad];
        }
        
        if (verbose){
        
            cout << "Parte izquierda del vector: "; 
            for (int i=0; i<z.size(); i++) {
                cout << z[i] << " ";
            }
            cout << endl << "Parte derecha del vector: ";
            for (int i=0; i<q.size(); i++) {
                cout << q[i] << " ";
            }
            cout << endl << "-----------------------------" << endl;
        }
        
        vector<int> x = ordenar_recursivo(z,verbose);
        vector<int> y = ordenar_recursivo(q,verbose);
        
        v=fusionar(v,x,y);
    }
    return v;  
}

int main(void)
{
  
    bool verbose = 1;
    vector<int> v;
    int sz;
    cout << "Introduzca el tamaño del vector: ";
    cin >> sz;
    v.resize(sz);
    for(int i=0; i<sz; i++){
        cout << "Introduzca el " << i+1 << " número: ";
        cin >> v[i];
    }
    cout << endl;
    vector<int> h = ordenar_recursivo(v,verbose);
    
    cout << endl << "El vector ordenado recusivamente es: ";
    
    for(int i=0; i<h.size(); i++){
        cout << h[i] << " ";
    }
    cout << endl;
    
    for(int i=1; i<v.size(); i++){ 
        int aux = v[i];
        for(int j=i-1; j>=0; j--){ 
            if(aux<v[j]){
                v[j+1]=v[j];
                v[j]=aux;
            }
        }
    }
    
    cout << "EL vector ordenado iterativamente es: ";
    for(int k=0; k<v.size(); k++) {
        cout << v[k] << " ";
    }
    cout << endl;
}