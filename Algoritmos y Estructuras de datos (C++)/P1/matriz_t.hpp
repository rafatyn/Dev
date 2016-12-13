#include <cstdio>	
#include <iostream>	
#include <iomanip>

#pragma nce	

using namespace std;

class matriz_t {
  
private:
  double* datos_; //Vector que alamacena los datos de la matrices
  unsigned int m_; // Este es el numero de filas
  unsigned int n_; // Este es el numero de columnas
public:
  matriz_t(void); // Este es el constructor por defecto al que no se le pasan parámetros
  matriz_t(int m, int n); // Este es el constructor en el que se especifique la dimensión de la matriz
  ~matriz_t(void); // Esto es el destructor
  void crea_matriz_t(void); // Este metodo es el que guarda espacio en la memoria para la matriz
  void destruye_matriz_t(void); // Este metodo libera el espacio que se habia reservado anteriormente para la matriz
  void redimension_matriz_t(int m, int n); // Este es el metodo que redimensiona la matriz
  void set_val(int i, int j, double dato); // Este es el método de acceso que permite la modificación individual de un elemento de la matriz
  double get_val(int i, int j); // Este es el método de acceso que permite la lectura de un elemento de la matriz
  int get_n(void); // Este metodo obtiene el valor de n
  int get_m(void); // Este metodo obtiene el valor de m
  void imprime_matriz_t(void); // Este es el método que muestra por pantalla la matriz
  void rellena_matriz_t(void); // Este es el metodo que le da valores a la matriz
  void rellena_matriz_t_cero(void); // Este es el metodo que rellena la matriz de ceros a la matriz
  bool matriz_cuadrado(void); // Esta función booleana devuelve si la matriz es cuadrada
  bool matriz_multiplicable(matriz_t& A, matriz_t& B); // Este metod booleano comprueba si las matrices son multplicables o no
  void producto_matrices(matriz_t& A, matriz_t& B); // Este metodo multiplica las matrices y almacena el producto en la matriz llamante
  void suma_fila_matriz_t(int i); // Este metodo se encarga de suma los valores de la fila que elija el usuario
  void suma_diagonal (void);  // Este metodo se encarga de sumar los valores de la diagonal de la matriz
private:
  int posicion(int i, int j); // Este es la funcion que devuelve la posición k en el vector del elemento (i,j) de la matriz virtual    
};
