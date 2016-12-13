#include <stdio.h>

int max,min,media,diferencia;

int main (void){
  printf("Escriba la temperatura maxima de su zona en grados: ");
  scanf("%d",&max);
  printf("Escriba la temperatura minima de su zona en grados: ");
  scanf("%d",&min);
  media = (max + min)/2;
  diferencia = max - min;
  printf("La temperatura media de su zona es: %d grados\n",media);
  printf("La diferencia de temperatura en su zona es: %d grados\n",diferencia);
}