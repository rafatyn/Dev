#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib> 
#include <set>
#include <iomanip>
#include <algorithm>
#include "estado.hpp"
#include "gr.hpp"

using namespace std;

/**
        \author   Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	      \details 	Clase que contiene el dfa. 
	      
*/

class dfa{
  
//========================================================================================
// Atributos.
//========================================================================================

  private:
      set <estado> estados;     /**< Conjunto de estados del dfa. */
      estado estado_inicial;    /**< Estado inicial. */
      set <char> alfabeto;      /**< Conjunto de las posibles entradas del dfa. */
      gr gram;                  /**< Gramatica regular del dfa. */

//========================================================================================
// Métodos públicos.
//========================================================================================

  public:
  
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor por defecto. Crea un dfa vacio.
	
*/

    dfa(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Destructor. Libera memoria.
	
*/

    ~dfa(void); 
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo calcula cuantos estados tiene la dfa.
	
	      * @return   numero de estados de la dfa.
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

	\details 	Metodo que devuelve el conjunto de estados del dfa.
	  
	      * @see estado.
              * @return devuelve el conjunto de estados del dfa.
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

	\details 	Metodo que lee el dfa desde un fichero.
	
	      * @return devuelve si se ha leido el fichero o no.
	      * @retval TRUE se ha leido el fichero satisfactoriamente.
	      * @retval FALSE no se ha leido el archivo satisfactoriamente.
*/

    bool leer_fichero(char fichero[]);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que muestra el dfa por pantalla.
	
*/

    void mostrar(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que analiza la cadena de entrada en el dfa.
	
*/

    void analizar_cadena(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si la cadena introducida es aceptada o no.
	
	      * @param  cadena cadena introducida a comprobar.
	      * @return devuelve si es aceptada o no.
	      * @retval TRUE la cadena es aceptada.
	      * @retval FALSE la cadena no es aceptada.
*/

    bool analizar_cadena_sin(char* cadena);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve uno de los estados del dfa.
	
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

	\details 	Metodo que comprueba si el estado x estado contenido en el cojunto de estados cactual.
	
	      * @param  x identificador del estado.
	      * @param  cactual conjunto de estados donde se busca.
	      * @return devuelve si esta contenido o no.
	      * @retval TRUE esta contenido en ese conjunto.
	      * @retval FALSE no esta contenido en ese conjunto.
*/

    bool contenido(set <estado> cactual, int x);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que parte el conjunto actual a partir de la entrada.
	
	      * @param  x identificador de la entrada.
	      * @param  conjuntoactual conjunto que se desea partir.
	      * @return devuelve el conjunto de conjuntos de estados actualizado.
	      * @param  conjuntoviejo conjunto de conjuntos que contiene la particion actual de la dfa.
*/

    set <set <estado> > partir(set <estado> conjuntoactual, char x, set <set <estado> > conjuntoviejo);
        
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que el conjunto de estados actual.
	
	      * @param  conjuntoestados conjunto de estados que se desea descomponer.
	      * @return devuelve el conjunto de conjuntos de estados actualizado.
	      * @param  conjuntoviejo conjunto de conjuntos que contiene la particion actual de la dfa.
*/

    set <set <estado> > descomponer(set <estado> conjuntoestados, set <set <estado> > conjuntoviejo);

/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que crea una nueva particion del dfa.
	
	      * @return devuelve el conjunto de conjuntos de estados actualizado.
	      * @param  conjuntoviejo conjunto de conjuntos que contiene el estado actual de la dfa.
*/

    set <set <estado> > nueva_particion(set <set <estado> > conjuntoviejo);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que minimiza la dfa.
	
	      * @return devuelve la nueva dfa.
*/

    dfa minimizar(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que crea un nuevo dfa.
	
	      * @return devuelve la nueva dfa minimizada.
	      * @param  conjuntofinal es el conjunto de conjuntos final, lo mas minimizado posible.
*/

    dfa crear_nueva_dfa(set <set <estado> > conjuntofinal);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que busca en que conjunto de estados esta el estado que se le pasa.
	
	      * @param  conjuntototal es el conjunto de conjuntos que contiene la particion de la dfa.
	      * @return devuelve el numero de conjunto donde esta el estado.
	      * @param  x estado que se desea buscar.
*/

    int donde(set <set <estado> > conjuntototal, int x);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor de la dfa a partir de sus parametros.
	
	      * @param  estados_ conjunto de estados de la dfa.
	      * @param  estado_inicial_ estado por el que empieza la dfa.
	      * @param  alfabeto_ el alfabeto de los caracteres que se usan en la transiciones de los estados de la dfa.
*/

    void crear_dfa(set <estado> estados_,estado estado_inicial_,set <char> alfabeto_);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que copia una dfa a la actual.
	
	      * @param  x la dfa de la que se quiere copiar.
*/

    void copiar(dfa &x);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve el alfabeto de la dfa.
	
	      * @return devuelve el conjunto de caracteres del alfabeto.
*/

    set <char> get_alfabeto(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que imprime por pantalla un conjunto de estados.
	
	      * @param Cjto es el conjunto de estados que se quiere imprimir por pantalla.
*/

    void print(set <estado> Cjto);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que exporta la dfa a un fichero.
	
	      * @param nombre es el npmbre del fichero donde se va a guardar la dfa.
*/

    void crear_fichero(char* nombre);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que imprime por pantalla un conjunto de conjuntos de estados.
	
	      * @param Cjto es el conjunto de conjuntos de estados que se quiere imprimir por pantalla.
*/

    void print(set <set <estado> > Cjto);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve el identificador del estado inicial.
	
	      * @return el identificador del estado inicial.
*/

    int get_id_inicial(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que resetea los atributos de la dfa.
	
*/

    void destruir(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si todos los cojuntos de estados son de dimension 1.
	
	      * @param  conjunto conjunto de conjunto que se quiere analizar.
	      * @return devuelve si todos los conjuntos de estados son de dimension 1 o no.
	      * @retval TRUE todos son de dimension 1.
	      * @retval FALSE no todos son de dimension 1.
	
*/

    bool alldim1(set <set <estado> > conjunto);

/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que convierte la dfa en una gramatica regular.
	
*/

    void convert2gr(char* fichero);

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

    friend ostream &operator<<(ostream &output, const dfa &x);
};