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
}TObservacion; 
TObservacion datos[MAXL][MAXF];

int NumeroLugares=0;
char nombreLugares[MAXL][15];
int NumeroFechas=0;

void Vminimos (void){
  int i,j;
  float tmin[MAXL];
  if(NumeroFechas==0){
     printf("Aun no se han introducido fechas\n");
    }
  if(NumeroLugares==0){
     printf("Aun no se han introducido lugares\n");
    }
  if((NumeroFechas!=0)&&(NumeroLugares!=0)){
    for(i=0;i<NumeroLugares;i++){
	tmin[i]=datos[i][0].temperatura;
	for(j=1;j<NumeroFechas;j++){
	  if(datos[i][j].temperatura<tmin[i]){
	    tmin[i]=datos[i][j].temperatura; }}
      printf("La temperatura máxima en %s es de %.2f\n",nombreLugares[i],tmin[i]); }}}

void Vmaximos (void){
  int i,j;
  float tmax[MAXL];
  if(NumeroFechas==0){
     printf("Aun no se han introducido fechas\n");
    }
  if(NumeroLugares==0){
     printf("Aun no se han introducido lugares\n");
    }
  if((NumeroFechas!=0)&&(NumeroLugares!=0)){
    for(i=0;i<NumeroLugares;i++){
	tmax[i]=datos[i][0].temperatura;
	for(j=1;j<NumeroFechas;j++){
	  if(datos[i][j].temperatura>tmax[i]){
	    tmax[i]=datos[i][j].temperatura; }}
      printf("La temperatura máxima en %s es de %.2f\n",nombreLugares[i],tmax[i]); }}}

void Vmedios (void){
  int i,j,x,y;
  float tmedt[MAXL];
  float tmed[MAXL];
  float tmaxt;
  
  if(NumeroFechas==0){
     printf("Aun no se han introducido fechas\n");
    }
  if(NumeroLugares==0){
     printf("Aun no se han introducido lugares\n");
    }
  if((NumeroFechas!=0)&&(NumeroLugares!=0)){
      for(i=0;i<NumeroLugares;i++){
	tmed[i]=0;
	for(j=0;j<NumeroFechas;j++){
	  tmed[i]+=datos[i][j].temperatura;
	}
      tmedt[i]=tmed[i]/NumeroFechas;
      printf("La temperatura media en %s es de %.2f\n",nombreLugares[i],tmedt[i]); }
    
    tmaxt=tmedt[0];
    for(x=0;x<NumeroLugares;x++){
      if(tmedt[x]>=tmaxt){
	tmaxt=tmedt[x];
	y=x;}}
    printf("La temeperatura maxima media es %.2f y fue tomada en %s\n",tmaxt,nombreLugares[y]);
  }}
  
void NuevaFecha (void){
  int i;
  if (NumeroFechas>=50){
    printf("No hay espacio para mas fechas\n");
  }else {
    printf("Introduzca una nueva fecha (dia mes año):");
    scanf("%d",&fecha[NumeroFechas].dia);
    scanf("%d",&fecha[NumeroFechas].mes);
    scanf("%d",&fecha[NumeroFechas].anno);
    if (NumeroLugares==0){
      printf("No hay ningun lugar introducido todavia\n");
      printf("Seleccione la primera opcion en el menu\n");
    }else {
      for(i=0;i<NumeroLugares;i++){
      printf("Introduzca los datos para la fecha %d/%d/%d en %s\n",fecha[NumeroFechas].dia,fecha[NumeroFechas].mes,fecha[NumeroFechas].anno,nombreLugares[i]);
      printf("Introduzca la velocidad del viento medida: ");
      scanf("%f",&datos[i][NumeroFechas].vv);
      printf("Introduzca la temperatura medida: ");
      scanf("%f",&datos[i][NumeroFechas].temperatura);
      printf("Introduzca precipitacion acumulada medidas: ");
      scanf("%f",&datos[i][NumeroFechas].pa);}}}
   NumeroFechas++;}

void NuevoLugar (void){
  int i;
  if (NumeroLugares>=10){
    printf("No queda espacio para mas lugares\n");
  }else {
    printf("Introduzca el nombre del nuevo lugar:");
    getchar();
    scanf("%[^\n]", nombreLugares[NumeroLugares]);
  if(NumeroFechas==0){
    printf("No hay ninguna fecha introducida todavia\n");
    printf("Seleccione la segunda opcion en el menu\n");
   }else {
     for(i=0;i<NumeroFechas;i++){
      printf("Introduzca los datos para la fecha %d/%d/%d en %s\n",fecha[i].dia,fecha[i].mes,fecha[i].anno,nombreLugares[NumeroLugares]);
      printf("Introduzca la velocidad del viento medida: ");
      scanf("%f",&datos[NumeroLugares][i].vv);
      printf("Introduzca la temperatura medida: ");
      scanf("%f",&datos[NumeroLugares][i].temperatura);
      printf("Introduzca precipitacion acumulada medidas: ");
      scanf("%f",&datos[NumeroLugares][i].pa);}}}
   NumeroLugares++;}
   
void menu (int x){
  switch(x){
    case 0: printf(" Cerrando...\n");break;
    case 1: NuevoLugar();break;
    case 2: NuevaFecha();break;
    case 3: Vmedios();break;
    case 4: Vmaximos();break;
    case 5: Vminimos();break;
    default: printf("El numero introducido no esta entre las opciones ofrecidas, intentelo de nuevo:\n");break;}}
    
int main (void){
  int x;
  do{
    printf("\nSeleccione una de las siguientes opciones:\n");
    printf(" 0.Salir.\n 1.Introducir nuevo lugar.\n 2.Introducir nueva fecha.\n 3.Mostrar valores medios.\n 4.Mostrar valores máximos.\n 5.Mostrar valores mínimos.\n");
    printf("\n  Opcion elegida: ");
    scanf("%d",&x);
    printf("\n");
    printf("\n");
    menu(x);
  }while(x!=0);}  