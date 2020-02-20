#include <stdio.h>

#define MAXL 10
#define MAXF 50

typedef struct{ 
  int anno;
  int mes;
  int dia; 
}TfechaObservacion; 
TfechaObservacion fecha[MAXF];

typedef struct{ 
  float temperatura; 
  float pa;
  float vv; 
}Tdatos; 
Tdatos datos[MAXL][MAXF];

int NumeroLugares=0;
char nombreLugares[MAXL][15];
int i,j,k;
int NumeroFechas=0;
int opcion=1;
int mes_solicitado;
int mes_final;
int mes_inicial;
float pMax[MAXL];
float pTMax=0;

int main(){
  printf("Introduzca el número de lugares donde se han tomado las medidas (máximo %d): ", MAXL);
  scanf("%d",&NumeroLugares);
  
  if ((0>NumeroLugares)||(NumeroLugares>MAXL)){
     printf("El numero introducido es menor que 0 o mayor que 10, por favor introduzca un numero entre 0 y 10: ");
     scanf("%d",&NumeroLugares);}
  
  printf("Introduzca el nombre de las estaciones donde se toman las medidas: ");
  for (i=-1;i<NumeroLugares;i++){
    scanf("%[^\n]",nombreLugares[i]);
    getchar();}

  do{
    printf("Introduzca la fecha en la que se observaron estos datos (dia mes año): ");
    scanf("%d",&fecha[NumeroFechas].dia);  
    scanf("%d",&fecha[NumeroFechas].mes);  
    scanf("%d",&fecha[NumeroFechas].anno);
    for (j=0;j<NumeroLugares;j++){
      printf("Introduzca los datos medidos en la estacion de %s\n",nombreLugares[j]);
      printf("Introduzca la temperatura medida en esa fecha: ");    
      scanf("%f",&datos[j][NumeroFechas].temperatura);
      printf("Introduzca la precipitacion acumulada medida en esa fecha: ");    
      scanf("%f",&datos[j][NumeroFechas].pa);
      printf("Introduzca la velocidad del viento medida en esa fecha: ");    
      scanf("%f",&datos[j][NumeroFechas].vv);}
  NumeroFechas++;
  printf("Seleccione 1 si se quiere seguir introduciendo las observaciones de otra fecha\n");
  printf("Seleccione 0 para dejar de introducir datos y visualizar el resultado\n");
  scanf("%d",&opcion);
  }while ((opcion!=0)&&(NumeroFechas<MAXF));

  for (i=0;i<NumeroFechas;i++){
    printf("El dia %d del mes %d del año %d ",fecha[i].dia,fecha[i].mes,fecha[i].anno);
    for (j=0;j<NumeroLugares;j++){ 
      printf("en la estacion de %s\n",nombreLugares[j]);
      printf("La temperatura medida fue: %.2f\n",datos[j][i].temperatura);  
      printf("La precipitacion acumulada medida fue: %.2f\n",datos[j][i].pa);
      printf("La velocidad del viento medida fue: %.2f\n",datos[j][i].vv);}}
  
  printf("Introduzca el numero de mes del que quiera ver los datos meteorologicos de cada estacion: ");
  scanf("%d",&mes_solicitado);
  
  if ((mes_solicitado<1)||(mes_solicitado>12)) {
    printf("El mes introducido no existe (solo hay 12 meses en un año), por favor introduzca el numero de un mes que exista; ");
    scanf("%d",&mes_solicitado);}
    
  for (i=0;i<MAXF;i++){
    if (mes_solicitado==fecha[i].mes){
     printf("El dia %d del mes %d del año %d ",fecha[i].dia,fecha[i].mes,fecha[i].anno);
    for (j=0;j<NumeroLugares;j++){ 
      printf("en la estacion de %s\n",nombreLugares[j]);
      printf("La temperatura medida fue: %.2f\n",datos[j][i].temperatura);  
      printf("La precipitacion acumulada medida fue: %.2f\n",datos[j][i].pa);
      printf("La velocidad del viento medida fue: %.2f\n",datos[j][i].vv);}}}
    
  printf("Introduzca el numero de dos meses\n ");
  printf("Primer mes: ");
  scanf("%d",&mes_inicial);
  printf("Segundo mes: ");
  scanf("%d",&mes_final);
  
  if ((mes_inicial<1)||(mes_inicial>12)) {
    printf("El mes inicial introducido no existe (solo hay 12 meses en un año), por favor introduzca el numero de un mes inicial que exista; ");
    scanf("%d",&mes_inicial);}
   
  if ((mes_final<1)||(mes_final>12)) {
    printf("El mes final introducido no existe (solo hay 12 meses en un año), por favor introduzca el numero de un mes final que exista; ");
    scanf("%d",&mes_final);}
    
  for(j=0;j<NumeroLugares;j++){
    for(i=0;i<NumeroFechas;i++){
      if((fecha[i].mes>=mes_inicial)&&(fecha[i].mes<=mes_final)){
	  pMax[j]=datos[j][i].pa;}}}
	  
  for(i=0;i<NumeroLugares;i++){
    if (pTMax<=pMax[i]){
      pTMax=pMax[i];
      k=i;}}
      
  printf("La maxima precipitacion acumulada fue %.2f, y esta medida fue tomada en la estacion de %s\n",pTMax,nombreLugares[k]);}       