#include <stdio.h>
#define MES 30
#define ANNO 365
  typedef struct{
    int dia;
    int mes;
    int ano;
  }TFecha;
  TFecha persona[3];
  int actual[3];
  int vida[3];
int main (void) {
  printf("Introduzca la fecha de nacimiento de la primera persona (día mes año):");
  scanf("%d",&persona[0].dia);
  scanf("%d",&persona[0].mes);
  scanf("%d",&persona[0].ano);
      
  printf("Introduzca la fecha de nacimiento de la segunda persona (día mes año):");
  scanf("%d",&persona[1].dia);
  scanf("%d",&persona[1].mes);
  scanf("%d",&persona[1].ano);
     
  printf("Introduzca la fecha de nacimiento de la primera persona (día mes año):");
  scanf("%d",&persona[2].dia);
  scanf("%d",&persona[2].mes);
  scanf("%d",&persona[2].ano);
    
  printf("Introduzca la fecha actual (día mes año):");
  scanf("%d",&actual[0]);
  scanf("%d",&actual[1]);
  scanf("%d",&actual[2]);
    
  vida[0]=(actual[0]-persona[0].dia)+(actual[1]-persona[0].mes)*MES+(actual[2]-persona[0].ano)*ANNO;
  vida[1]=(actual[0]-persona[1].dia)+(actual[1]-persona[1].mes)*MES+(actual[2]-persona[1].ano)*ANNO;
  vida[2]=(actual[0]-persona[2].dia)+(actual[1]-persona[2].mes)*MES+(actual[2]-persona[2].ano)*ANNO;
      
      printf("La fecha de nacimiento de la primera persona es %d/%d/%d y ha vivido %d días.\n",persona[0].dia, persona[0].mes,persona[0].ano,vida[0]);
      printf("La fecha de nacimiento de la segunda persona es %d/%d/%d y ha vivido %d días.\n",persona[1].dia, persona[1].mes,persona[1].ano,vida[1]);
      printf("La fecha de nacimiento de la tercera persona es %d/%d/%d y ha vivido %d días.\n",persona[2].dia, persona[2].mes,persona[2].ano,vida[2]);
  }
