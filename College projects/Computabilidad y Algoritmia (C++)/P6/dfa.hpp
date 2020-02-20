
#pragma once
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

#include "estados.hpp"

using namespace std;

class DFA_t {

/**
        \author   Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		22 de octubre de 2015

	\details 	Clase que representa un DFA. 
*/
  private:
  
    set <state_t> estados_; /**< Conjunto de estados. */
    int estado_inicial_; /**< Estado inicial. */
    set <char> alfabeto_; /**< Conjunto de símbolos. */
    
  public:
  
/**

	\details 	Constructor por defecto.
*/  
    DFA_t(void);
    
/**
	\details 	Constructor.

       * @param   estados Conjunto de estados.
       * @param   estado_inicial  Estado inicial.
       * @param   alfabeto Conjunto de símbolos reconocidos.
*/
    DFA_t(set<state_t> estados, int estado_inicial, set<char> alfabeto);
  
/**

	\details 	Destructor. 
 */
    ~DFA_t(void);
    
/**
	\details 	Devuelve el índice del estado inicial.
			
       * @return 	El índice del estado inicial.
 */
    int get_estado_inicial(void) const;
/**

	\details 	Devuelve el conjunto de estados.

       * @return  Conjunto de estados.
 */
    set<state_t> get_estados(void) const;

/**
 * 
	\details 	Mostrar DFA por pantalla.

       * @param  	os Flujo de salida.
       * @return 	Flujo de salida.
 */
    ostream& mostrar(ostream& os) const;
/**

	\details 	Muestra los estados de muerte.
 */
    void mostrar_estados_muerte(void);
/**

	\details 	Función que recibe una cadena y la analiza según el DFA definido. 
	Como resultado final obtendremos si el DFA reconoce o no la cadena introducida previamente.
	
	
       * @param   cadena Cadena a analizar.
       * @return  Booleano indicador.
 */   
    bool analizar_cadena(char* cadena);
/**


	\details 	Lee el fichero que se desea cargar.

       * @param   fichero Nombre del fichero que deseamos cargar.
       * @return 	Bool que indica si el fichero ha sido cargado correctamente o no.
       * @retval TRUE   El fichero se cargó correctamente.
       * @retval FALSE  Hubo problemas en el proceso de cargar del fichero.
 */
   bool leer_fichero(char* fichero);

/**
	\details  Devuelve un bool que índica si el carácter pasado pertenece al alfabeto.

       * @param   x El carácter para la comprobación.
       * @return 	El bool resultado de la comprobación.
       * @retval TRUE   Símbolo contenido en el alfabeto.
       * @retval FALSE  Símbolo no conteni9do en el alfabeto.
 */    
    bool encontrado_alfabeto(char x);
/**
	\details 	Sobrecarga del operador.
 */
    DFA_t& operator=(const DFA_t &x);
/**

	\details 	Devuelve el conjunto de símbolos que admite en DFA.

       * @return 	El conjunto de símbolos.
 */    
  set<char> get_alfabeto(void) const; 
   
  
  private:
/**

	\details 	Sobrecarga del operador <<

 */  
    friend ostream &operator<<(ostream &, const DFA_t &);
    /**

	\details 	Devuelve el estado correspondiente a un identificador.
			

       * @param  	x Entero que almacena el identificador del estado siguiente.
       * @return 	El estado del identificador.
 */
    state_t get_state(int x);
    
};