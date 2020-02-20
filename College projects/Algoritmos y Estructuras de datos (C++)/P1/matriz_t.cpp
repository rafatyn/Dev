#include "matriz_t.hpp"

matriz_t::matriz_t(void):  // Este es el constructor por defecto al que no se le pasan parámetros
  datos_(NULL),
  m_(0),
  n_(0)
  {}

matriz_t::matriz_t (int m, int n):  // Este es el constructor en el que se especifique la dimensión de la matriz
  datos_(NULL),
  m_(m),
  n_(n)
  {
     crea_matriz_t();
  }

void matriz_t::crea_matriz_t(void){  // Este metodo es el que guarda espacio en la memoria para la matriz
     datos_= new double[m_*n_];     
     if (datos_==NULL){       
       cout << "No se pudo crear la matriz" <<endl;
     }
}
  
matriz_t::~matriz_t(void){  // Esto es el destructor
  destruye_matriz_t();
}

void matriz_t::destruye_matriz_t(void){  // Este metodo libera el espacio que se habia reservado anteriormente para la matriz
     if (datos_!=NULL){
       delete[] datos_;
       datos_==NULL;
     }
     m_=0; n_=0;
}

void matriz_t::redimension_matriz_t(int m, int n){  // Este es el metodo que redimensiona la matriz
  destruye_matriz_t();
  m_=m; n_=n;
  crea_matriz_t();
}
  
void matriz_t::set_val(int i, int j, double val){  // Este es el método de acceso que permite la modificación individual de un elemento de la matriz
  
  datos_[posicion(i,j)]=val;
}

double matriz_t::get_val(int i, int j){  // Este es el método de acceso que permite la lectura de un elemento de la matriz
  
  return (datos_[posicion(i,j)]);
}

int matriz_t::get_n(void){  // Este metodo obtiene el valor de n
  
  return (n_);
}

int matriz_t::get_m(void){  // Este metodo obtiene el valor de m
  
  return (m_);
}

int matriz_t::posicion (int i, int j){  // Este es la funcion que devuelve la posición k en el vector del elemento (i,j) de la matriz virtual
  
  return ((i-1)*n_+j-1);
}

void matriz_t::imprime_matriz_t (void){ // Este es el método que muestra por pantalla la matriz
  
  cout << endl;
  for (int i=1; i<=m_ ; i++){
    cout << "|";
    for (int j=1; j <=n_; j++){
      cout << setw(n_+1) << setprecision(3) << datos_[posicion(i,j)] << "" ;
    }
      cout << "|";
      cout << endl;
  }
}

void matriz_t::rellena_matriz_t (void){ // Este es el metodo que le da valores a la matriz
  
  for (int i=1; i<=m_; i++)
    for (int j=1; j<=n_; j++)
      set_val(i,j,posicion(i,j)+1);
}

void matriz_t::rellena_matriz_t_cero (void){ // Este es el metodo que le da valores a la matriz
  
  for (int i=1; i<=m_; i++)
    for (int j=1; j<=n_; j++)
      set_val(i,j,0.0);
}

bool matriz_t::matriz_cuadrado (void){ // Esta función booleana devuelve si la matriz es cuadrada
  
  return(n_==m_);
}

bool matriz_t::matriz_multiplicable (matriz_t& A, matriz_t& B){ // Este metod booleano comprueba si las matrices son multplicables o no
  
  return(A.get_n()==B.get_m());
}

void matriz_t::producto_matrices (matriz_t& A, matriz_t& B){ // Este metodo multiplica las matrices y almacena el producto en la matriz llamante
  
  if(matriz_multiplicable (A,B)==1){
    cout << endl << "La matriz resultante de la multiplicacion es:" << endl;
    redimension_matriz_t(A.get_m(),B.get_n());
    for (int i=1; i<=m_; i++)
      for (int j=1; j<=n_; j++)
	for (int x=1; x<=A.get_n(); x++)
	  datos_[posicion(i,j)]+=(A.get_val(i,x))*(B.get_val(x,j));
  }else { cout << endl << "Las matrices no son multiplicables por lo que la matriz resultante se ha relllenado de ceros" << endl; }
}

void matriz_t::suma_fila_matriz_t(int i){  // Ese metodo se encarga de suma los valores de la fila que elija el usuario
  double suma;
  for (int j=1; j<=n_; j++)
   suma+=get_val(i,j);

  cout << "La suma de los valoes de la fila numero " << i << " es: " << suma << endl;
}

void matriz_t::suma_diagonal (void){  // Este metodo se encarga de sumar los valores de la diagonal de la matriz

double suma=0;
 if (n_==m_){
 
   for (int i=1; i<=m_; i++)
     suma+=get_val(i,i);
 cout << "La suma diagonal es " << suma << endl;
 }else { cout << "La matriz no es cuadrada" << endl; }
}
    

  
