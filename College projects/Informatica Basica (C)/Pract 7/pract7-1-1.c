#include <stdio.h>

#define MAX 5
int numero[MAX];

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

 printf("Los numeros que usted ha introducido son %d\t %d\t %d\t %d\t %d\n", numero[0],numero[1],numero[2],numero[3],numero[4]);
}
