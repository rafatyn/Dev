#include "stack_char_t.hpp"
#include <cstdio>

using namespace std;

 namespace AED {
  
    stack_char_t::stack_char_t(void):
     
      list_()
      {}
      
    stack_char_t::~stack_char_t(void){}
    
    void stack_char_t::push(char c){
      
      list_.insert_beginning(new dll_char_node_t(c));
    }
    
    char stack_char_t::pop(void){
      
      dll_char_node_t* aux = (dll_char_node_t*)(list_.extract_beginning());
    
      return (aux->get_data());
    }
    
    bool stack_char_t::empty(void){
      
      return(list_.empty());
    }
    ostream& stack_char_t::write(ostream& os){
      
      return(list_.write(os)); 
    }
 }   
      
      
