#include <stdio.h>
#define MAXIMO_NUMERO_LUGARES 10	/*número de estaciones*/
#define MAXIMO_NUMERO_FECHAS 50 	/*número de días que han sido medidos*/
  typedef struct{
    float temperatura;
    float precipitacion;
    float viento;
  }TDatos; 
  TDatos Observacion[MAXIMO_NUMERO_LUGARES][MAXIMO_NUMERO_FECHAS];
  int NumeroLugares=0;
  char NombreLugar[MAXIMO_NUMERO_LUGARES][50];
  int NumeroFechas=0;
  typedef struct{
    int dia;
    int mes;
    int anio;
  }Fecha;
  Fecha FechaObservacion[MAXIMO_NUMERO_FECHAS]; 
  void nuevolugar (void){
    int i;
    if(NumeroLugares>=MAXIMO_NUMERO_LUGARES){
      printf("No puede introducir más lugares.");
    }
    if(NumeroLugares<MAXIMO_NUMERO_LUGARES){
      printf("Introduzca el nombre del nuevo lugar: ");
      getchar();
      scanf("%[^\n]",NombreLugar[NumeroLugares]);
      for(i=0;i<NumeroFechas;i++){
	printf("Introduzca los datos del día %d/%d/%d en %s",FechaObservacion[i].dia,FechaObservacion[i].mes,FechaObservacion[i].anio,NombreLugar[NumeroLugares]);
	printf("\n\tTemperatura: ");
	scanf("%f",&Observacion[NumeroLugares][i].temperatura);
	printf("\tPrecipitación: ");
	scanf("%f",&Observacion[NumeroLugares][i].precipitacion);
	printf("\tViento: ");
	scanf("%f",&Observacion[NumeroLugares][i].viento);
      }
      NumeroLugares++;
    }
  }
  void nuevafecha (void){
    int i;
    if(NumeroFechas>=MAXIMO_NUMERO_FECHAS){
      printf("No puede introducir más fechas.");
    }
    if(NumeroFechas<MAXIMO_NUMERO_FECHAS){
      printf("Introduzca la nueva fecha (dd mm aaaa): ");
      scanf("%d",&FechaObservacion[NumeroFechas].dia);
      scanf("%d",&FechaObservacion[NumeroFechas].mes);
      scanf("%d",&FechaObservacion[NumeroFechas].anio);
      for(i=0;i<NumeroLugares;i++){
	printf("Introduzca los datos de %s: ",NombreLugar[i]);
	printf("\n\tTemperatura: ");
	scanf("%f",&Observacion[i][NumeroFechas].temperatura);
	printf("\tPrecipitación: ");
	scanf("%f",&Observacion[i][NumeroFechas].precipitacion);
	printf("\tViento: ");
	scanf("%f",&Observacion[i][NumeroFechas].viento);
      }
      NumeroFechas++;
    }
  }
  float Minimo (float Vector[],int nElementos,int *Posicion);
  float Media (float Vector[] ,int nElementos);
  int elegirTipoDato (void);
  float Maximo (float Vector[],int nElementos,int *Posicion); 
  void mostrarMedia (int TipoDato){
    int i,j;
    float vectormedia[NumeroFechas];  
    switch(TipoDato){
      case 0:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    vectormedia[j]=Observacion[i][j].temperatura;
	  }
	  printf("La media de las temperaturas en %s fue de: %.2fºC.\n", NombreLugar[i],      Media (vectormedia,NumeroFechas));
	}
	break;
      case 1:
	for(i=0;i<NumeroLugares;i++){  
	  for(j=0;j<NumeroFechas;j++){ 
	    vectormedia[j]=Observacion[i][j].precipitacion;
	  }
	  printf("La media de las precipitaciones en %s fue de: %.2f mm.\n", NombreLugar[i], Media (vectormedia,NumeroFechas));
	}
	break;
      case 2:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    vectormedia[j]=Observacion[i][j].viento;
	  }
	  printf("La media del viento en %s fue de: %.2f km/h.\n", NombreLugar[i], Media (vectormedia,NumeroFechas)); 
	}
	break;
      default: 
	printf("La opción seleccionada no existe, por favor seleccione otra."); mostrarMedia (elegirTipoDato());
	break;
    }
  }
  float Media (float Vector[],int nElementos){
    int i;
    float media=0;
    for(i=0;i<nElementos;i++){
      media+=Vector[i];
    }
    media=media/nElementos;
    return(media);
  }
  void mostrarMaximo (int TipoDato){
    int i,j;
    int Posicion;
    float vectormaximo[NumeroFechas];
    switch(TipoDato){
      case 0:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    vectormaximo[j]=Observacion[i][j].temperatura;
	  }
	  printf("La temperatura máxima en %s se registró el día %d/%d/%d y fue de: %.2fºC.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Maximo (vectormaximo,NumeroFechas,&Posicion));
	}
	break;
      case 1:
	for(i=0;i<NumeroLugares;i++){  
	  for(j=0;j<NumeroFechas;j++){ 
	    vectormaximo[j]=Observacion[i][j].precipitacion;
	  }
	  printf("La precipitación máxima en %s se registró el día %d/%d/%d y fue de: %.2f mm.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Maximo (vectormaximo,NumeroFechas,&Posicion));
	}
	break;
      case 2:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    vectormaximo[j]=Observacion[i][j].viento;
	  }
	  printf("El viento máximo en %s se registró el día %d/%d/%d y fue de: %.2f km/h.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Maximo (vectormaximo,NumeroFechas,&Posicion)); 
	}
	break;
      default: 
	printf("La opción seleccionada no existe, por favor seleccione otra."); mostrarMaximo (elegirTipoDato()); 
	break;
    }
  }
  float Maximo (float Vector[],int nElementos,int *Posicion){
    int i;
    float maximo;
    *Posicion=0;
    maximo=Vector[0];
    for(i=1;i<nElementos;i++){
      if(maximo<Vector[i]){
	maximo=Vector[i];
	*Posicion=i;
      }
    }
    return(maximo);
  }
  void mostrarMinimo (int TipoDato){
    int i,j;
    int Posicion;
    float vectorminimo[NumeroFechas];
    switch(TipoDato){
      case 0:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    vectorminimo[j]=Observacion[i][j].temperatura;
	  }
	  printf("La temperatura mínima en %s se registró el día %d/%d/%d y fue de: %.2fºC.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Minimo (vectorminimo,NumeroFechas,&Posicion));
	}
	break;
      case 1:
	for(i=0;i<NumeroLugares;i++){  
	  for(j=0;j<NumeroFechas;j++){ 
	    vectorminimo[j]=Observacion[i][j].precipitacion;
	  }
	  printf("La precipitación máxima en %s se registró el día %d/%d/%d y fue de: %.2f mm.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Minimo (vectorminimo,NumeroFechas,&Posicion));
	}
	break;
      case 2:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    vectorminimo[j]=Observacion[i][j].viento;
	  }
	  printf("El viento mínimo en %s se registró el día %d/%d/%d y fue de: %.2f km/h.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Minimo (vectorminimo,NumeroFechas,&Posicion)); 
	}
	break;
      default: 
	printf("La opción seleccionada no existe, por favor seleccione otra."); mostrarMinimo (elegirTipoDato());
	break;
    }
  }
  float Minimo (float Vector[],int nElementos,int *Posicion){
    int i;
    float minimo;
    *Posicion=0;
    minimo=Vector[0];
    for(i=1;i<nElementos;i++){
      if(minimo>Vector[i]){
	minimo=Vector[i];
	*Posicion=i;
      }
    }
    return(minimo);
  }
  int elegirTipoDato (void){
    int opcion;
    printf("\n\tOpciones: ");
    printf("\n\t\t0 Temperatura.");
    printf("\n\t\t1 Precipitaciones.");
    printf("\n\t\t2 Viento.");
    printf("\n\tIntroduzca una: ");
    scanf("%d",&opcion);
    return(opcion);
  }
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
	case 3:
	  if(NumeroFechas==0){
	    printf("\nNo se pueden calcular los datos medios porque aun no se han introducido fechas.");
	    break;
	  }
	  if(NumeroLugares==0){
	    printf("\nNo se pueden calcular los datos medios porque aun no se han introducido lugares.");
	    break;
	  }
	  if((NumeroFechas!=0)&&(NumeroLugares!=0)){
	    mostrarMedia (elegirTipoDato());
	    break;
	  }
	case 4:
	  if(NumeroFechas==0){
	    printf("\nNo se pueden calcular los datos máximos porque aun no se han introducido fechas.");
	    break;
	  }
	  if(NumeroLugares==0){
	    printf("\nNo se pueden calcular los datos máximos porque aun no se han introducido lugares.");
	    break;
	  }
	  if((NumeroFechas!=0)&&(NumeroLugares!=0)){
	    mostrarMaximo (elegirTipoDato());
	    break;
	  }
	case 5:
	  if(NumeroFechas==0){
	    printf("\nNo se pueden calcular los datos mínimos porque aun no se han introducido fechas.");
	    break;
	  }
	  if(NumeroLugares==0){
	    printf("\nNo se pueden calcular los datos mínimos porque aun no se han introducido lugares.");
	    break;
	  }
	  if((NumeroFechas!=0)&&(NumeroLugares!=0)){
	    mostrarMinimo (elegirTipoDato());
	    break;
	  }
	default:printf("La opción seleccionada no existe.");break;
      }
    }
  }