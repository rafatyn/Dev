#include <stdio.h>
#define MAXL 10
#define MAXF 50 	
  typedef struct{
    float temperatura;
    float precipitacion;
    float viento;
  }TDatos; 
  TDatos Observacion[MAXL][MAXF];
  int NumeroLugares=0;
  char NombreLugar[MAXL][50];
  int NumeroFechas=0;
  typedef struct{
    int dia;
    int mes;
    int anio;
  }Fecha;
  Fecha FechaObservacion[MAXF];   
  
  void nuevolugar (void){
    int i;
    if(NumeroLugares>=MAXL){
      printf("No puede introducir más lugares.");}
    else{
      printf("Introduzca el nombre del nuevo lugar: ");
      getchar();
      scanf("%[^\n]",NombreLugar[NumeroLugares]);
      for(i=0;i<NumeroFechas;i++){
	printf("Introduzca los datos del día %d/%d/%d en %s",FechaObservacion[i].dia,FechaObservacion[i].mes,FechaObservacion[i].anio,NombreLugar[NumeroLugares]);
	printf("\nTemperatura: ");
	scanf("%f",&Observacion[NumeroLugares][i].temperatura);
	printf("\nPrecipitación: ");
	scanf("%f",&Observacion[NumeroLugares][i].precipitacion);
	printf("\nViento: ");
	scanf("%f",&Observacion[NumeroLugares][i].viento);}
      NumeroLugares++;}}
      
  void nuevafecha (void){
    int i;
    if(NumeroFechas>=MAXF){
      printf("No puede introducir más fechas.");}
    else{
      printf("Introduzca la nueva fecha (dd mm aaaa): ");
      scanf("%d",&FechaObservacion[NumeroFechas].dia);
      scanf("%d",&FechaObservacion[NumeroFechas].mes);
      scanf("%d",&FechaObservacion[NumeroFechas].anio);
      for(i=0;i<NumeroLugares;i++){
	printf("Introduzca los datos de %s: ",NombreLugar[i]);
	printf("\nTemperatura: ");
	scanf("%f",&Observacion[i][NumeroFechas].temperatura);
	printf("\nPrecipitación: ");
	scanf("%f",&Observacion[i][NumeroFechas].precipitacion);
	printf("\nViento: ");
	scanf("%f",&Observacion[i][NumeroFechas].viento);}
      NumeroFechas++;}}
    
  float Minimo (float Vector[],int nElementos,int *Posicion);
  float Media (float Vector[] ,int nElementos);
  int elegirTipoDato (void);
  float Maximo (float Vector[],int nElementos,int *Posicion);
  
  void mostrarMedia (int TipoDato){
    int i,j;
    float med[NumeroFechas];  
    switch(TipoDato){
      case 0:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    med[j]=Observacion[i][j].temperatura;}
	  printf("La media de las temperaturas en %s fue de: %.2fºC.\n", NombreLugar[i],      Media (med,NumeroFechas));}break;
      case 1:
	for(i=0;i<NumeroLugares;i++){  
	  for(j=0;j<NumeroFechas;j++){ 
	    med[j]=Observacion[i][j].precipitacion;}
	  printf("La media de las precipitaciones en %s fue de: %.2f mm.\n", NombreLugar[i], Media (med,NumeroFechas));}break;
      case 2:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    med[j]=Observacion[i][j].viento;}
	  printf("La media del viento en %s fue de: %.2f km/h.\n", NombreLugar[i], Media (med,NumeroFechas));}break;
      default: printf("La opción seleccionada no existe, por favor seleccione otra."); mostrarMedia (elegirTipoDato());break;}}
      
  float Media (float Vector[],int nElementos){
    int i;
    float media=0;
    for(i=0;i<nElementos;i++){
      media+=Vector[i];}
    media=media/nElementos;
    return(media);}

  void mostrarMaximo (int TipoDato){
    int i,j;
    int Posicion;
    float max[NumeroFechas];
    switch(TipoDato){
      case 0:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    max[j]=Observacion[i][j].temperatura;}
	  printf("La temperatura máxima en %s se registró el día %d/%d/%d y fue de: %.2fºC.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Maximo (max,NumeroFechas,&Posicion));}break;
      case 1:
	for(i=0;i<NumeroLugares;i++){  
	  for(j=0;j<NumeroFechas;j++){ 
	    max[j]=Observacion[i][j].precipitacion;}
	  printf("La precipitación máxima en %s se registró el día %d/%d/%d y fue de: %.2f mm.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Maximo (max,NumeroFechas,&Posicion));}break;
      case 2:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    max[j]=Observacion[i][j].viento;}
	  printf("El viento máximo en %s se registró el día %d/%d/%d y fue de: %.2f km/h.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Maximo (max,NumeroFechas,&Posicion));}break;
      default: printf("La opción seleccionada no existe, por favor seleccione otra."); mostrarMaximo (elegirTipoDato());break;}}

  float Maximo (float Vector[],int nElementos,int *Posicion){
    int i;
    float maximo;
    *Posicion=0;
    maximo=Vector[0];
    for(i=1;i<nElementos;i++){
      if(maximo<Vector[i]){
	maximo=Vector[i];
	*Posicion=i;}}
    return(maximo);}

  void mostrarMinimo (int TipoDato){
    int i,j;
    int Posicion;
    float min[NumeroFechas];
    switch(TipoDato){
      case 0:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    min[j]=Observacion[i][j].temperatura;}
	  printf("La temperatura mínima en %s se registró el día %d/%d/%d y fue de: %.2fºC.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Minimo (min,NumeroFechas,&Posicion));}break;
      case 1:
	for(i=0;i<NumeroLugares;i++){  
	  for(j=0;j<NumeroFechas;j++){ 
	    min[j]=Observacion[i][j].precipitacion;}
	  printf("La precipitación máxima en %s se registró el día %d/%d/%d y fue de: %.2f mm.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Minimo (min,NumeroFechas,&Posicion));}break;
      case 2:
	for(i=0;i<NumeroLugares;i++){
	  for(j=0;j<NumeroFechas;j++){ 
	    min[j]=Observacion[i][j].viento;}
	  printf("El viento mínimo en %s se registró el día %d/%d/%d y fue de: %.2f km/h.\n", NombreLugar[i], FechaObservacion[Posicion].dia, FechaObservacion[Posicion].mes, FechaObservacion[Posicion].anio, Minimo (min,NumeroFechas,&Posicion));}break;
      default: printf("La opción seleccionada no existe, por favor seleccione otra."); mostrarMinimo (elegirTipoDato());break;}}

  float Minimo (float Vector[],int nElementos,int *Posicion){
    int i;
    float minimo;
    *Posicion=0;
    minimo=Vector[0];
    for(i=1;i<nElementos;i++){
      if(minimo>Vector[i]){
	minimo=Vector[i];
	*Posicion=i;}}
    return(minimo);}

  int elegirTipoDato (void){
    int opcion;
    printf("\nElija el tipo de dato: ");
    printf("\n\t0-Temperatura.");
    printf("\n\t1-Precipitaciones.");
    printf("\n\t2-Viento.");
    printf("\nTipo de dato elegido: ");
    scanf("%d",&opcion);
    return(opcion);}

  int main (void){
    int opcion,x,i,j;
    char nombrefichero[50];
    opcion=1;
    x=1;

    while(x!=0){
      printf("\nIntroduzca la ruta o nombre del fichero si se encuentra en este mismo directorio(si no existe se creará): ");
      scanf("%s",nombrefichero);
      FILE *fich;
      fich=fopen(nombrefichero,"r");
      if(fich!=NULL){
	int feof(FILE *fich);
	fscanf(fich,"%d\n",&NumeroLugares);
	for(i=0;i<NumeroLugares;i++){
	  fscanf(fich," %[^\n]\n",NombreLugar[i]);}
	while(feof(fich)==0){
	  fscanf(fich,"%d %d %d\n",&FechaObservacion[NumeroFechas].dia,&FechaObservacion[NumeroFechas].mes,&FechaObservacion[NumeroFechas].anio);
	  for(i=0;i<NumeroLugares;i++){
	    fscanf(fich,"%f %f %f\n",&Observacion[i][NumeroFechas].temperatura,&Observacion[i][NumeroFechas].precipitacion,&Observacion[i][NumeroFechas].viento);}
	  NumeroFechas++;}
	fclose(fich);
	x=0;}
      else{
	printf("\nNo existe el fichero introducido asi que se la estructura de datos se iniciará vacia");
	fich=fopen(nombrefichero,"a");
	if(fich!=NULL){
	  fclose(fich);
	  x=0;}
	else{printf("\nNo tiene permisos para crear o abrir el fichero");}}} 
	
    printf("El numero de lugares es %d y el numero de fechas es %d\n", NumeroLugares, NumeroFechas);
    
    while(opcion!=0){ 
      printf("\nOpciones: ");
      printf("\n\t0-Salir.");
      printf("\n\t1-Introducir nuevo lugar.");
      printf("\n\t2-Introducir nueva fecha.");
      printf("\n\t3-Mostrar valores medios.");
      printf("\n\t4-Mostrar valores máximos.");
      printf("\n\t5-Mostrar valores mínimos.");
      printf("\nOpción introducida: ");
      scanf("%d",&opcion);
      switch(opcion){
	case 0:break;
	case 1:nuevolugar();break;
	case 2:nuevafecha();break;
	case 3:mostrarMedia (elegirTipoDato());break;
	case 4:mostrarMaximo (elegirTipoDato());break;
	case 5:mostrarMinimo (elegirTipoDato());break;
	default:printf("La opción seleccionada no existe.");break;}}
    x=1;

    while(x!=0){
      FILE *fich;
      fich=fopen(nombrefichero,"w");
      if(fich!=NULL){
	int feof(FILE *fich);
	fprintf(fich,"%d\n",NumeroLugares);
	for(i=0;i<NumeroLugares;i++){
	  fprintf(fich,"%s\n",NombreLugar[i]);}
	for(j=0;j<NumeroFechas;j++){
	  fprintf(fich,"%d %d %d\n",FechaObservacion[j].dia,FechaObservacion[j].mes,FechaObservacion[j].anio);
	  for(i=0;i<NumeroLugares;i++){
	    fprintf(fich,"%.1f %.1f %.1f\n",Observacion[i][j].temperatura,Observacion[i][j].precipitacion,Observacion[i][j].viento);}}
	x=0;
	fclose(fich);}
      else{
	printf("\nNo tiene permisos para crear o modificar el fichero, introduzca una nueva ruta:");
	scanf("%s",nombrefichero);}}
    printf("El fichero se ha sido guardado\n");}
