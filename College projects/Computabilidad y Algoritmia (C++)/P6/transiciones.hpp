#pragma once
#include <iostream>
#include <vector>

using namespace std;

/**
        \author   Rafael González de Chaves González (alu0100891812@ull.edu.es)
        \date 		22 de octubre de 2015

	\details 	Clase que representa las transiciones, con cada carácter a su respectivo estado. 
*/

class transition_state_t {
  
  private:
  
    char caracter_;
    int next_state_;

  public:
/**

	\details 	Constructor por defecto.
*/    
    transition_state_t(void);
    
/**

	\details 	Constructor de copia.

       * @param  	cp transición del que queremos realizar la copia.
       * @see 		transition_state_t.

*/
    transition_state_t(const transition_state_t &cp);
/**

	\details 	Constructor. 

       * @param 	caracter carácter para realizar la transición.       
       * @param 	next_state indica el estado siguiente.       

*/
    transition_state_t(char caracter, int next_state);
/**

	\details 	Destructor.
 */
    ~transition_state_t(void);
/**

	\details 	Devuelve el caracter para realizar la transición de forma constante.

       * @return 	Carácter con el que realiza la transición.
 */    
    char get_char(void) const;
/**

	\details 	Devuelve un bool que indica si el carácter es reconocido o no de forma constante.

       * @param 	x carácter comparado.
       * @return 	resultado de la comparación.
       * @retval TRUE   carácter coincide.
       * @retval FALSE  carácter no coincide.
 */  
    bool reconocido(char x) const;
/**

	\details 	Devuelve el identificador del estado siguiente de forma constante.

       * @return 	Identificador del estado siguiente.
  
 */  
    int get_next_state(void) const;

/**
  
	\details 	Muestra el estado siguiente pantalla.
			
 */        
    ostream& mostrar(ostream& os) const;
/**

	\details 	Sobrecarga del operador =
	
       * @param  	x constante de la transición.
       * @return  transición llamante.
 */     
    transition_state_t& operator=(const transition_state_t &x);
/**

	\details 	Sobrecarga del operador <.
	
       * @param 	x  constante de la transición.
       * @return 	resultado de la comparación.
       * @retval TRUE   transición llamante menor que la transición pasada.
       * @retval FALSE  transición llamante mayor que la transición pasada.
 */
    bool operator<(const transition_state_t &x) const;
    
/**

	\details 	Sobrecarga operador ==.

 */     
    bool operator==(const transition_state_t &x) const;
    
  private:
/**

	\details 	Sobrecarga del operador << 
	
       * @param  	os flujo de salida.
       * @param  	x  constante a la transición.
       * @return  flujo de salida.
 */   
    friend ostream &operator<<(ostream &, const transition_state_t &);
    
};

