#pragma once

#include <iostream>
#include <vector>

using namespace std;

/**
        \author   Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	      \details 	Clase que contiene las transiciones de los estados. 
	      
*/

class transicion{
  
//========================================================================================
// Atributos.
//========================================================================================

  private:
    char entrada;           /**< Caracter de entrada. */
    char escribe;           /**< Caracter que se escribe en la cinta. */
    short int movimiento;   /**< Movimiento en la cinta. */
    int sig_estado;         /**< Estado siguiente para la entrada. */
  
//========================================================================================
// Metodos publicos.
//========================================================================================

  public:
  
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor por defecto. Crea una transicion vacia.
	
*/

    transicion(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor de copia.
	
	      * @param  x transicion que se quiere copiar.
	
*/

    transicion(const transicion &x);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Constructor a partir de los parametros.
	
	      * @param  entrada_ caracter de entrada.
	      * @param  escribe_ caracter que se escribe en la cinta.
	      * @param  movimiento_ direccion hacia donde se mueve la cabeza sobre la cinta.
	      * @param  sig_estado_ siguiente estado para esa entrada.
	
*/

    transicion(char entrada_, char escribe_, short int movimiento_, int sig_estado_);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Destructor. Libera memoria.
		
*/

    ~transicion(void);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si existe una transicion con ese carcater de entrada.
	
	      * @param  x caracter de entrada.
	
*/
    bool existe(char x) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve la entrada de la transicion.
	
	      * @return devuelve el caracter de entrada de la transicion.
	
*/
    char get_entrada(void) const;   
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve el estado siguiente de la transicion.
	
	      * @return devuelve el identificador del siguiente estado de la transicion.
	
*/

    int get_sig_estado(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve el caracter que se escribe en la cinta.
	
	      * @return devuelve el caracter a escribir en la cinta.
	
*/

    char get_escribe(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que devuelve la direccion a la que se mueve la cabeza.
	
	      * @return devuelve la direccion hacia donde se mueve la cabeza.
	
*/

    short int get_movimiento(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que muestra las transiciones por pantalla.
		
*/
    
    void mostrar(void) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que iguala una transicion a otra.
	
	      * @param  x transicion que se quiere igualar.
	      * @return devuelve la transicion resultante.
	
*/

    transicion& operator=(const transicion &x);
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si una transicion es menor que otra.
	
	      * @param  x la transicion que se quiere comparar.
	      * @return devuelve el valor de la comparacion.
	
*/

    int operator<(const transicion &x) const;
    
/**	
        \author 	Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		16 de octubre de 2015

	\details 	Metodo que comprueba si una transicion es igual a otra.
	
	      * @param  x la transicion que se quiere comparar.
	      * @return devuelve el valor de la comparacion.
	      * @retval TRUE las transiciones son iguales.
	      * @retval FALSE las transiciones no son iguales.
	
*/

    bool operator==(const transicion &x) const;
  
//========================================================================================
// Metodos privados.
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

    friend ostream &operator<<(ostream &output, const transicion &);
};
