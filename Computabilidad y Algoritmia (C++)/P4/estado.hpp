#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <sstream>

using namespace std;

#include "transicion.hpp"

/**
        \author   Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	      \details 	Clase que representa a un estado de la nfa. 
	      
*/

class estado{
  
//========================================================================================
// Atributos.
//========================================================================================

  private:
    set <transicion> transiciones;  /**< Conjunto de transiciones del estado. */
    bool aceptacion;  /**< Variable booleana que indica si el estado es de aceptación o no.  */
    int id;  /**< Variable que contiene el identificador del estado. */
    
//========================================================================================
// Métodos públicos.
//========================================================================================

  public:

/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor por defecto. Crea un estado vacio.

*/

    estado(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor de copia. Crea un estado que es copia del otro.
	
	      * @param  x estado del cual se hace la copia.

*/

    estado(const estado &x);    
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor a partir de un conjunto de transiciones, una variable aceptacion y la variable que contiene el identificador.
	
	      * @param  transiciones_ conjunto de transiciones del estado.  
	      * @see transicion.
        * @param  aceptacion_ variable que indica si es un estado de aceptacion o no.
        * @param  id_ variable que contiene el identificador del estado.
*/

    estado(set<transicion> transiciones_, bool aceptacion_, int id_);    
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Destructor. Libera memoria.

*/
    ~estado(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si existe alguna transicion de este estado con el caracter que se le pasa por parametros.
	
	      * @param  x caracter de entrada al estado.
	      * @return devuelve si la transicion existe o no.
	      * @retval TRUE  existe una transicion que responde al caracter de entrada.
	      * @retval FALSE no existe una transicion que responde al caracter de entrada.

*/
    bool existe(char x) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que muestra los atributos del estado.
	
*/

    void mostrar(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si el estado es de aceptacion o no.
	
	      * @return devuelve si es un stado de aceptacion o no.
	      * @retval TRUE  el estado es un estado de aceptacion.
	      * @retval FALSE el estado no es un estado de aceptacion.

*/
    bool get_aceptacion(void) const; 
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si es un estado de muerte o no.
	
	      * @return devuelve si es un estado de muerte o no.
	      * @retval TRUE  es un estado de muerte.
	      * @retval FALSE no es un estado de muerte.

*/

    bool estado_muerte(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve el identificador del estado.
	
	      * @return el identificador del estado.

*/

    int get_id(void) const;    
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve las transiciones del estado.
	
	      * @return el conjunto de transiciones.

*/

    set <transicion> get_transiciones(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelde un conjunto de los estados siguientes para el caracter que se pasa por parametros.
	
	      * @param  x caracter de entrada al estado.
	      * @return conjunto de siguientes estados.
	      * @see transicion

*/

    set <int> get_conjunto_transiciones(char x) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelde un conjunto de los estados siguientes para el caracter ~.
	
	      * @return conjunto de siguientes estados.
	      * @see transicion

*/

    set <int> get_epsilon_clausura(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si dos estados son iguales.
	
	      * @param  x caracter del identificador del estado con el que se quiere comparar.
	      * @return valor de la igualdad.
	      * @see transicion

*/

    int operator==(const int x) const;    
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que iguala un estado a otro.
	
	      * @param  x estado con el que se quiere igualar.
	      * @return estado igualado.

*/

    estado& operator=(const estado &x);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si un estado es menor que otro.
	
	      * @param  x estado que se quiere comprobar.
	      * @return valor de la comprobacion.

*/

    int operator<(const estado &x) const;

//========================================================================================
// Métodos privados.
//========================================================================================

  private:
  
  /**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que imprime un estado en la salida especificada.
	
	      * @param  x estado que se quiere imprimir.
	      * @param  output salida que se le pasa
	      * @return la salida impresa.

*/

    friend ostream &operator<<(ostream &output, const estado &x);
};
  