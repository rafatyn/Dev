#include <stdio.h>

#define MAX 5
int numero[MAX];
float suma;
float media;

int main (void){
 printf("Introduzca un numero: ");
 scanf("%d",&numero[0]);
 printf("Introduzca un numero: ");
 scanf("%d",&numero[1]);
 printf("Introduzca un numero: ");
 scanf("%d",&numero[2]);
 printf("Introduzca un numero: ");
 scanf("%d",&numero[3]);
 printf("Introduzca un numero: ");
 scanf("%d",&numero[4]);

 suma=(numero[0]+numero[1]+numero[2]+numero[3]+numero[4]);
 media= suma/MAX;

 printf("La media de todos los numeros introducidos es %f\n",media);
}
