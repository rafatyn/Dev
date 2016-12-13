#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <cstring>
#include <sstream>

#include "transiciones.hpp"

using namespace std;


class state_t {
/**
        \author   Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		22 de octubre de 2015

	\details 	Clase que representa los estados. 
*/  
  private:
  
    set <transition_state_t> transiciones_; /**< Conjunto de transiciones. */
    bool aceptacion_;/**< Bool de aceptación. */
    int ID_;/**< Identificador del estado. */
    
  public:
  
/**

	\details 	Constructor por defecto.
*/   
    state_t(void); //
  
/**

	\details 	Constructor sw copia.
*/ 
    state_t(const state_t &); //
/** 

	\details 	Destructor. 
 */
    ~state_t(void);  //
/**

	\details 	Constructor.
	
       * @param   transiciones Conjunto de transiciones del estado.
       * @param 	aceptacion Indicador de aceptación del estado.
       * @param 	id Identificador del estado.

*/    
    state_t(set<transition_state_t> transiciones, bool aceptacion, int id);

    /**
	\details 	Compara el caracter x con el necesario para pasar al siguiente estado de forma constante.

       * @param   x Carácter a comparar.
       * @return 	El resultado de coincidencias con las transiciones.
       * @retval TRUE   El carácter coincide con alguna de las transiciones.
       * @retval FALSE  El carácter no coincide con nignuna transición.
 */
    bool reconocido(char x) const;

/**
	\details 	Devuelve el estado siguiente de forma constante.

       * @return 	Estado siguiente.

 */ 
    int estado_siguiente(char x) const;  
    
/**

	\details 	Devuelve el identificador del estado de forma constante.

       * @return 	Identificador del estado.
 */

    int get_id(void) const;  

/**
  
	\details 	Retorna el conjunto de transiciones accesibles con un determinado carácter (NFA_t).

       * @param   x Carácter del cual queremos conocer su conjunto de transiciones.
       * @return 	El conjunto de transiciones del caracter pasado por parametro.
 */
    set<int> get_conjunto_transiciones(char x) const;  
 
/**
 	\details 	Retorna el conjunto de epsilon transiciones(accesibles con la cadena vacía)(NFA_t).

       * @return 	El conjunto de transiciones con la cadena vacía.
 */
    set<int> get_epsilon_clausura(void) const; 

/**
	\details 	Devuelve el conjunto de transiciones.

       * @return 	Conjunto de transiciones.
 */    
    set <transition_state_t> get_transiciones(void) const; 
/**

	\details 	Sobrecarga del operador == .
	
       * @param 	x constante que comparamos con el identificador del estado.
       * @return 	Resultado de la comparación.
       * @retval TRUE   El entero coincide con el identificador del estado.
       * @retval FALSE  El entero no coincide con el identificador del estado.
 */        
    state_t& operator=(const state_t &x); 
/**

	\details 	Sobrecarga del operador < .
	
       * @param 	x referencia del estado.
       * @return 	El resultado de la comparación.
       * @retval TRUE   El estado constante es menor que el pasado a la funcion.
       * @retval FALSE  El estado constante es mayor que el pasado a la funcion.
 */
    bool operator<(const state_t &x) const; 
    
/**
 
	\details 	Devuelve si el estado es aceptado o no de forma constante.

       * @return 	Bool de aceptación.
       * @retval TRUE   Estado de aceptación.
       * @retval FALSE  Estado de no aceptación.
 */  
    bool aceptacion(void) const;   
/**

	\details 	Devuelve un bool que indica si el estado es de muerte.

       * @return 	Resultado de la comparación.
       * @retval TRUE   Es un estado de muerte.
       * @retval FALSE  No es un estado de muerte.
  
 */
    bool estado_muerte(void) const;  
/**

	\details 	Devuelve un bool que indica si el estado contiene o no más de una transición para un mismo símbolo.
	
       * @return 	Bool.
       * @retval TRUE   Contiene más de una transición con el mismo símbolo.
       * @retval FALSE  No contiene más de una transición con el mismo símbolo.
 */    
    bool error(void) const;  
/**

	\details 	Escribe los estados por pantalla.
			

       * @param  	os Referencia del flujo de salida.
       * @return 	Referencia del flujo de salida.
 */
    ostream& mostrar(ostream& os) const;  
    
/**

	\details 	Sobrecarga operador ==.

 */  
    bool operator==(const state_t &x) const; 
    
  private:
/**

	\details 	Sobrecarga del operador <<.
	      
       * @param  	os flujo de salida.
       * @param  	x  constante al estado.
       * @return 	flujo de salida.
 */  
    friend ostream &operator<<(ostream &, const state_t &); 
    
};
  
  
  