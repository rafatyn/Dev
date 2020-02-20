// Crear cola 

#include "queue_char_t.hpp"
#include "dll_char_node_t.hpp"
#include <iostream>

using namespace std;

namespace AED{
  queue_char_t::queue_char_t(void):   // Constructor
    list_()
  {
  }

  queue_char_t::~queue_char_t(void)  // Destructor
  {} 

  void queue_char_t::put(char c)    // Poner
  {
    list_.insert_beginning(new dll_char_node_t(c));
  }

  char queue_char_t::get(void)    // Sacar 
  {
    dll_char_node_t* aux = (dll_char_node_t*)(list_.extract_end());
    return (aux->get_data());
  }

  bool queue_char_t::empty(void)  // Comprobar si esta vacia
  {
    return(list_.empty());
  }

  ostream& queue_char_t::write(ostream& os)  // Mostrar
  {
    return(list_.write(os));
  }
   
 


}