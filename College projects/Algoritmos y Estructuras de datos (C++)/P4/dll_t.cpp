#include "dll_t.hpp"
#include <cstdio>
#include <iostream>

using namespace std;

 namespace AED {

    dll_t::dll_t(void):

     beginning_(NULL),
     end_(NULL)
     {}
  
    dll_t::~dll_t(void){

      while(beginning_!= NULL){

        dll_node_t* aux = beginning_;
        beginning_= beginning_-> get_next();
        delete aux;
      }
    }
  
    void dll_t::insert_beginning(dll_node_t* n){
    
      n-> set_next(beginning_);
      
      if(beginning_!= NULL)
        beginning_-> set_prev(n);
	
      else{
        end_= n;
      }      
      beginning_= n;
    }
  
    dll_node_t* dll_t::extract_beginning(void){
    
      dll_node_t* aux = beginning_;
      beginning_= beginning_-> get_next();
      
      if(beginning_!= NULL)
        beginning_-> set_prev(NULL);
      else{
        end_= NULL;
      }
      aux-> set_next(NULL);
  
      return (aux);
  }
  
  void dll_t::insert_end(dll_node_t* n){
    
    n-> set_prev(end_);
    
    if(end_!= NULL)
      end_-> set_next(n);
    else{
      beginning_= n;
    }
    end_= n;
  }
  
  dll_node_t* dll_t::extract_end(void){
    
    dll_node_t* aux=end_;
    end_= end_-> get_prev();
    
    if(end_!=NULL)
      end_-> set_next(NULL);
    else{
      beginning_= NULL;
    }
    aux-> set_prev(NULL);
    return (aux); 
  }
  
  bool dll_t::empty(void) const{
    
    if(beginning_== NULL)
      return true;
    else
      return false;
  }
  
  ostream& dll_t::write(ostream& os) const{
    
    dll_node_t* aux=beginning_;
    
    while(aux!= NULL){
      
      aux-> write(os);
      aux = aux-> get_next();
    }
    return(os);
  }
 }
