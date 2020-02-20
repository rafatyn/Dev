#include <iostream>
#include "stack_char_t.hpp"

using namespace std; 

int main(void){

  AED::stack_char_t inverse_stack;
  AED::stack_char_t bracket_stack;
  
  char cadena[100];
  //char letra;

  cout << "Introduzca una frase: ";
  cin.getline(cadena,100);
  cout << endl;
  
  for(int i=0; cadena[i] != '\0'; i++)

     inverse_stack.push(cadena[i]);
  
  /*
  for(int i=0; inverse_stack.empty() != true; i++){
 
     letra = inverse_stack.pop();
     cout << letra;
  }*/
  
  inverse_stack.write(cout);

  char balanced[100];
  char carac;
  bool uerror = true;
  int cont = 0;

  cout << endl << endl << "Introduzca una frase: ";
  cin.getline(balanced,100);

  for(int i=0; balanced[i] != '\0' && uerror == true; i++){
    
    if(balanced[i] == '(')
      bracket_stack.push(')');
    else
      if(balanced[i] == '{')
	bracket_stack.push('}');
      else
	if(balanced[i] == '[')
	  bracket_stack.push(']');
	else
	  if((bracket_stack.empty()==false)&&(balanced[i] == ')')){
            carac = bracket_stack.pop();
	    if(carac != ')'){
	      uerror = false;
              cont++;}
	  }else
            if((bracket_stack.empty()==false)&&(balanced[i] == '}')){
	      carac = bracket_stack.pop();
	      if(carac != '}'){
		uerror = false;
                cont++;}
	    }else
	      if((bracket_stack.empty()==false)&&(balanced[i] == ']')){
	        carac = bracket_stack.pop();
	        if(carac != ']'){
		  uerror = false;
	          cont++;}
              }
	     
	      
  }
  if((uerror == false )||(bracket_stack.empty() != true)){
    
    while(bracket_stack.empty() != true){
    bracket_stack.pop();
    cont++;
    } 
  }
  
  
  if(uerror==true)
    cout << "La pila esta balanceada" << endl;
  else
    cout << "La pila no esta balanceada" << endl << "El numero de elmentos que queda dentro de la pila es: " << cont << endl;
}
  
  
