#include "evaluador_RPN_t.hpp"

namespace AED{
  
  evaluador_RPN_t::evaluador_RPN_t(void):
   
    stack_()
    {}
  
  evaluador_RPN_t::~evaluador_RPN_t(void)
    {}
    
  float evaluador_RPN_t::eval(char cadena[]){
    
    char * token = strtok (cadena," ");
    while(token!=NULL){
		
	if((token[0]>='0')&&(token[0]<='9')||(token[0]>='-')&&(token[1]!='\0')){
        
	  stack_.push(atoi(token));
        }else{
	
	float aux,aux_izq, aux_dcha;
        switch(*token){
	  
        	case '+':
        	  aux_izq = stack_.pop();        	  aux_dcha = stack_.pop();
		  aux = aux_izq+aux_dcha;
        	  stack_.push(aux);
        	  break;
		  
        	case '-':
        	  aux_dcha = stack_.pop();        	  aux_izq = stack_.pop();
		  aux = aux_izq-aux_dcha;
        	  stack_.push(aux);
        	  break;
		  
        	case '*':
        	  aux_izq = stack_.pop();        	  aux_dcha = stack_.pop();
		  aux = aux_izq*aux_dcha;
        	  stack_.push(aux);
        	  break;
		
		case '/':
        	  aux_dcha = stack_.pop();        	  aux_izq = stack_.pop();
        	  aux = aux_izq/aux_dcha;
		  stack_.push(aux);
		  break;
		  
		case '%':
		  aux_dcha = stack_.pop();        	  aux_izq = stack_.pop();
		  stack_.push(int(aux_izq)%int(aux_dcha));
		  break;
		  
        	default:
        	  cout<<"Error en la cadena de caracteres"<<endl;
        	  break;
  	
        }
        }
       token = strtok (NULL, " ");
    }
    return(stack_.pop());
  }
}
