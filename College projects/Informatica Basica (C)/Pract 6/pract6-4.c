#include <stdio.h>

float C,F;

int main (void){
  printf("Escriba la temperatura en grados celcius: ");
  scanf("%f",&C);
  F= ((C*9)/5)+32;
  printf("La temperatura en grados Fahrenheit es: %f\n",F);
}
