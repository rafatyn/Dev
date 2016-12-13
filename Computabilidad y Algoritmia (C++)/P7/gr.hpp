#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <sstream>
#include "transicion.hpp"

using namespace std;

/**
        \author   Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	      \details 	Clase que contiene la gramatica regular. 
	      
*/

class gr{

//========================================================================================
// Atributos.
//========================================================================================

    private:
        set <char> alfabeto;                /**< Conjunto de caracteres de las entradas. */
        vector <set <transicion> > nt;      /**< Vector de los conjuntos de transiciones de cada simbolo no terminal. */
        set <transicion> S;                 /**< Conjunto de transiciones del simbolo de comienzo de la gramatica. */
      
//========================================================================================
// Métodos públicos.
//========================================================================================
  
    public:

/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor por defecto. Crea una gramatica regular vacia.
	
*/

        gr(void);
        
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que crea una gramatica segun los parametros.
	
	      * @param  nt_ vector de los conjuntos de transiciones de cada simbolo no terminal.
	      * @param  S_ conjunto de transiciones del simbolo de comienzo de la gramatica.
	      * @param  alfabeto_ conjunto de caracteres de las entradas.
*/

        void crear_gr(vector <set <transicion> > nt_, set <transicion> S_, set <char> alfabeto_);
        
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Destructor por defecto. Destruye la gramatica regular.
	
*/
        ~gr(void);

/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que exporta la gramatica regular a fichero.
	
	      * @param  nombre es el nombre del fichero al que se quiere exportar la gramatica.
*/

        void exporta(char* nombre);        
};
        