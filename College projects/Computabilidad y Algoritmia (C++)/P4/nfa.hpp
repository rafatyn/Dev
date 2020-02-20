#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <set>
#include <iomanip>
#include "estado.hpp"

using namespace std;

/**
        \author   Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	      \details 	Clase que contiene el nfa. 
	      
*/

class nfa{
  
//========================================================================================
// Atributos.
//========================================================================================

  private:
    set <estado> estados;     /**< Conjunto de estados del nfa. */
    estado estado_inicial;    /**< Estado inicial. */

//========================================================================================
// Métodos públicos.
//========================================================================================

  public:
  
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor por defecto. Crea un nfa vacio.
	
*/

    nfa(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Destructor. Libera memoria.
	
*/

    ~nfa(void); 
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo calcula cuantos estados tiene la nfa.
	
	      * @return   numero de estados de la nfa.
*/

    int get_n_estados(void) const; 
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve el estado inicial.
	 
	      * @see estado.
        * @return devuelve el estado inicial.
*/

    estado get_inicial(void) const; 
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve el conjunto de estados del nfa.
	  
	      * @see estado.
        * @return devuelve el conjunto de estados del nfa.
*/

    set<estado> get_estados(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que muestra los estados de muerte.
	
*/

    void mostrar_estados_muerte(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que lee el nfa desde un fichero.
	
	      * @return devuelve si se ha leido el fichero o no.
	      * @retval TRUE se ha leido el fichero satisfactoriamente.
	      * @retval FALSE no se ha leido el archivo satisfactoriamente.
*/

    bool leer_fichero(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que muestra el nfa por pantalla.
	
*/

    void mostrar(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que analiza la cadena de entrada en el nfa.
	
*/

    void analizar_cadena(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo recursivo que analiza la cadena.
	
	      * @param  n numero de caminos.  
	      * @param  cadena 
        * @param  i posicion de inicio de lectura.
        * @param  buffer cadena en la que se alamacena los parametros.
        * @param  os salida en la que se imprime.
        * @param  estado_ estado en el que se inicia el camino.
        * @param  baux variable de aceptacion de la cadena
*/

    void analizar_cadena_recursivo(int &n, char cadena [], int i, const stringbuf &buffer, const ostream &os, estado estado_, bool &baux);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve uno de los estados del nfa.
	
	      * @param  x identificador del estado que se quiere obtener.
	      * @return estado con el identificador que se le pasa al metodo por parametros.
*/

    estado get_estado(int x);

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

    friend ostream &operator<<(ostream &output, const nfa &x);
};