#include "utilfloat.h"

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

float Media (float Vector[],int nElementos){
    int i;
    float media=0;
    for(i=0;i<nElementos;i++){
      media+=Vector[i];
    }
    media=media/nElementos;
    return(media);
}
  
