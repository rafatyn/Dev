#include "evaluador_RPN_t.hpp"
#include "aed_buffer_t.hpp"

using namespace std;

int main(void){

  char formula[100];
  
  AED::evaluador_RPN_t evaluador_;
  AED::aed_buffer_t buffer_(10);

  cout<< "Introduce la formula que se quiere resolver: ";
  cin.getline(formula,100);
  cout << "El resultado de la formula es: " << evaluador_.eval(formula) << endl;

  cout << "Introduzca el mensaje que desea almacenar en el buffer: ";
  cin.getline(formula,100);

  for(int i=0; formula[i]!='\0';i++)
    buffer_.put(formula[i]);
}
