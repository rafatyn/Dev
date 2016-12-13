#include "operaciones.h"
#include <stdio.h>

int main (void){
    int opcion;
    printf("Instrucciones: ");
    printf("\n\t*Debe introducir las fechas en el formato día mes año.");
    printf("\n\t*Debe introducir temperatura en ºC, la precipitación en mm y la velocidad del viento en Km/h.");
    opcion=1;
    while(opcion!=0){ 
      printf("\nOpciones: ");
      printf("\n\t0->Salir.");
      printf("\n\t1->Introducir nuevo lugar.");
      printf("\n\t2->Introducir nueva fecha.");
      printf("\n\t3->Mostrar valores medios.");
      printf("\n\t4->Mostrar valores máximos.");
      printf("\n\t5->Mostrar valores mínimos.");
      printf("\nIntroduzca una: ");
      scanf("%d",&opcion);
      switch(opcion){
	case 0:break;
	case 1:nuevolugar();break;
	case 2:nuevafecha();break;
	case 3:mostrarMedia (elegirTipoDato());break;
	case 4:mostrarMaximo (elegirTipoDato());break;
	case 5:mostrarMinimo (elegirTipoDato());break;
	default:printf("La opción seleccionada no existe.");break;
      }
    }
  }
