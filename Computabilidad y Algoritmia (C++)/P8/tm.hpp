#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <set>
#include <iomanip>
#include <algorithm>
#include "estado.hpp"
#include "cinta.hpp"

using namespace std;

/**
        \author   Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	      \details 	Clase que contiene la tm. 
	      
*/

class tuma{
  
//========================================================================================
// Atributos.
//========================================================================================

  private:
      set <estado> estados;     /**< Conjunto de estados de la tm. */
      estado estado_inicial;    /**< Estado inicial. */
      set <char> alfabeto;      /**< Conjunto de las posibles entradas de la tm. */
      cinta cintaa;               /**< Cinta de la tm. */

//========================================================================================
// Métodos públicos.
//========================================================================================

  public:
  
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor por defecto. Crea una tm vacia.
	
*/

    tuma(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Destructor. Libera memoria.
	
*/

    ~tuma(void); 
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo calcula cuantos estados tiene la tm.
	
	      * @return   numero de estados de la tm.
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

	\details 	Metodo que devuelve el conjunto de estados de la tm.
	  
	      * @see estado.
              * @return devuelve el conjunto de estados de la tm.
*/

    set <estado> get_estados(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que muestra los estados de muerte.
	
*/

    void mostrar_estados_muerte(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que lee la tm desde un fichero.
	
	      * @return devuelve si se ha leido el fichero o no.
	      * @retval TRUE se ha leido el fichero satisfactoriamente.
	      * @retval FALSE no se ha leido el archivo satisfactoriamente.
*/

    bool leer_fichero(char* fichero);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que lee la tape desde un fichero.
	
	      * @return devuelve si se ha leido el fichero o no.
	      * @retval TRUE se ha leido el fichero satisfactoriamente.
	      * @retval FALSE no se ha leido el archivo satisfactoriamente.
*/

    bool leer_tape(char* fichero);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que muestra la tm por pantalla.
	
*/

    void mostrar(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que analiza la cadena de entrada en la tm.
	
*/

    void analizar_cadena(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve uno de los estados de la tm.
	
	      * @param  x identificador del estado que se quiere obtener.
	      * @return estado con el identificador que se le pasa al metodo por parametros.
*/

    estado get_estado(int x);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si ya existe esa entrada en el conjunto de entradas.
	
	      * @param  x identificador de la entrada.
	      * @return devuelve si existe o no.
	      * @retval TRUE la entrada ya existe en el conjunto.
	      * @retval FALSE la entrada no existe en el conjunto.
*/

    bool alfabeto_existe(char x);
        
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve el alfabeto de la tm.
	
	      * @return devuelve el conjunto de caracteres del alfabeto.
*/

    set <char> get_alfabeto(void) const;
      
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve el identificador del estado inicial.
	
	      * @return el identificador del estado inicial.
*/

    int get_id_inicial(void) const;
    
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

    friend ostream &operator<<(ostream &output, const tuma &x);
};