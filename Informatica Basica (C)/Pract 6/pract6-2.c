#include <stdio.h>

#define CONVERSION 1.26

float euros,dolares,num1,num2;

int main (void){
  printf("Escriba el numero de dolares a convertir a euros: ");
  scanf("%f",&dolares);
  printf("Escriba el numerode euros a convertir a dolares: ");
  scanf("%f",&euros);
  num1= euros*CONVERSION;
  num2= dolares/CONVERSION;
  printf("%f euros es igual a %f dolares\n",euros,num1);
  printf("%f dolares es igual a %f euros\n",dolares,num2);
}