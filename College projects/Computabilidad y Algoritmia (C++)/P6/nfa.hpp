
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

#include "dfa.hpp"

#pragma once
using namespace std;

/**
        \author   Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		15 de Octubre de 2015

	      \details 	Clase que representa un NFA. 
	
*/

class NFA_t {
  
//========================================================================================
// Atributos privados.
//========================================================================================
  
  private:
  
    set <state_t> estados_; /**< Conjunto de estados. */
    int estado_inicial_; /**< Entero que almacena el estado inicial. */
    set<char> alfabeto_;/**< Conjunto de símbolos. */
    
//========================================================================================
// Métodos públicos.
//========================================================================================    
    
  public:
  
  /**

	\details 	Constructor por defecto. Construye NFA con el estado inicial con valor -1.
	
*/
    NFA_t(void); 
    
/**
 	\details 	Constructor. Inicializa el conjunto de estados y estado inicial a sus respectivos tipos de datos pasados como parámetros por valor.

       * @param   estados Conjunto de estados del NFA.
       * @param   estado_inicial Índice del estado inicial del NFA.
       * @param   alfabeto Conjunto de símbolos.

*/
    NFA_t(set<state_t> estados, int estado_inicial, set<char> alfabeto); 
    
/**

	\details 	Destructor por defecto.
	
 */
 
    ~NFA_t(void); 

/**
		\details 	Retorna el índice correspondiente al estado inicial del NFA.
			
       * @return 	El índice del estado inicial.
 */
    int get_estado_inicial(void) const;   
/**
 * 
	\details 	Retorna el conjunto de símbolos del alfabeto del DFA.

       * @return 	El conjunto de símbolos.
 */
    set<char> get_alfabeto(void) const; 

 /**
  	\details 	Función que retorna un booleano que índica si el carácter pasado por parámetro pertenece ya al alfabeto.

       * @param   x El carácter con el cual queremos realizar la comprobación.
       * @return 	Bool indicador.
       * @retval TRUE   El símbolo ya está contenido en el alfabeto.
       * @retval FALSE  El símbolo no pertenece al alfabeto.
 */
    bool encontrado_alfabeto(char x);
    
/**
	\details 	Devuelve el conjunto de estados del NFA.

       * @return 	El conjunto de estados.

 */ 
    set<state_t> get_estados(void) const; 
    
/**
 	\details 	Función que recibe una cadena de carácteres que interpretará como nombre del fichero que se desea abrir.
	Posteriormente la funcion procederá a la lectura de dicho fichero y retornará un booleano en función de si se ha cargado correctamente su contenido.

       * @param   fichero Puntero que contiene el principio de la cadena de carácteres que contiene el nombre del fichero que deseamos cargar.
       * @return 	Bool que indica el intento de carga del fichero.
       * @retval TRUE   El fichero se cargó correctamente.
       * @retval FALSE  Hubo problemas al intentar cargar el fichero.
 */

    bool leer_fichero(char* fichero); 
/**

	\details 	Muestra los estados de muerte del NFA.


 */    
 
    void mostrar_estados_muerte(void); 
    
/**
 
	\details 	Escribe un NFA en el flujo de salida.
	
       * @param  	os Referencia del flujo de salida.
       * @return 	Referencia del flujo de salida.
 */
    ostream& mostrar(ostream& os) const; 
    
/**
	\details 	Función que recibe una cadena y la analiza según el NFA definido (llama a la función recursiva). 
	Como resultado final retornará un booleano que indica si el NFA reconoce o no la cadena introducida previamente.
	
	
       * @param   cadena Cadena a analizar.
       * @return  Booleano indicador.
 */ 
    bool analizar_cadena(char* cadena); 

/**
  
	\details 	Función que calcula el DFA_t equivalente al NFA_t cargado y lo retorna.
			

       * @return 	DFA_t equivalente.
 */ 
    DFA_t convert2DFA(void); 
/** 
	\details 	Sobrecarga del operador = que iguala el NFA llamante al NFA constantepasado por referencia.

       * @param  	x Referencia constante del NFA.
       * @return 	Referencia del NFA llamante.
 */
    NFA_t& operator=(const NFA_t &x);
    
//========================================================================================
// Métodos privados.
//========================================================================================

  private:

    
/**

	\details 	Devuelve el estado correspondiente a un identificador que se le ha pasado previamente por paramentro.

       * @param  	x Almacena el identificador del estado a acceder.
       * @return 	Estado al que corresponde el identificador.
 */
 
    state_t get_state(const int x) const;
    
/**
  	\details 	Función que retorna el conjunto de estados accesibles desde un conjunto de estados pasado por referencia con epsilon transiciones.
			

       * @param  	T conjunto de estados que deseamos calcular sus siguientes estados.
       * @return 	Conjunto de estados alcanzables.
 */
    set<state_t> e_clausura(const set<state_t> &conjunto);
    
/**
  	\details 	Función que retorna el conjunto de estados accesibles desde un conjunto de estados pasado por referencia con un determinado carácter.
			

       * @param  	T conjunto de estados que deseamos calcular sus siguientes estados.
       * @param  	x Carácter de las transiciones.
       * @return 	Conjunto de estados alcanzables.
 */
    set<state_t> move(const set<state_t> &T, char a); 
    
/**

	\details 	Sobrecarga del operador << que escribe un NFA en el flujo de salida. 
 */  
    friend ostream &operator<<(ostream &, const NFA_t &);
};