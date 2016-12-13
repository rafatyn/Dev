#include <stdio.h>

typedef struct{ 
  int anno,mes,dia; 
}Tfecha; 
Tfecha fecha[5];

typedef struct{ 
  int temperatura; 
  float pa,vv; 
}Tdatos; 
Tdatos datos[2][5];

char nombreLugares[2][15]={"La Laguna","Los Cristianos"};

int i,j,z,x,k,y,m,a,b; 
int temp_max[2]; 
int temp_min[2]; 
int fecha_max[3]; 
int dif_temp[2];
float media_pa[2];

int main(){
  
  for (i=0;i<5;i++){
  printf("Introduzca la fecha en la que se observaron estos datos (dia mes año): ");
  scanf("%d",&fecha[i].dia);  
  scanf("%d",&fecha[i].mes);  
  scanf("%d",&fecha[i].anno);
    for (j=0;j<2;j++){
    printf("Introduzca los datos medidos en la estacion de %s\n", nombreLugares[j]);
    printf("Introduzca la temperatura medida en esa fecha: ");    
    scanf("%d",&datos[j][i].temperatura);
    printf("Introduzca la precipitacion acumulada medida en esa fecha: ");    
    scanf("%f",&datos[j][i].pa);
    printf("Introduzca la velocidad del viento medida en esa fecha: ");    
    scanf("%f",&datos[j][i].vv);} 
 }
  
  temp_max[0]=datos[0][0].temperatura;  
  temp_max[1]=datos[1][0].temperatura;  
  temp_min[0]=datos[0][0].temperatura;  
  temp_min[1]=datos[1][0].temperatura;
      
  for (x=0;x<2;x++){
    for (z=0;z<5;z++){
	if (temp_max[x]<=datos[x][z].temperatura) { 
	  temp_max[x]=datos[x][z].temperatura;   
	  fecha_max[0]=fecha[z].dia;   
	  fecha_max[1]=fecha[z].mes;   
	  fecha_max[2]=fecha[z].anno;	
        }
	if (temp_min[x]>=datos[x][z].temperatura) { 
	  temp_min[x]=datos[x][z].temperatura;}  
    }
  }
  
  dif_temp[0]=temp_max[0]-temp_min[0];  dif_temp[1]=temp_max[1]-temp_min[1];
  
  if (temp_max[0]>temp_max[1]) { 
    printf("La temperatura maxima fue %d, tomada el dia %d %d %d en la estacion de %s\n", temp_max[0], fecha_max[0], fecha_max[1], fecha_max[2], nombreLugares[0]);
  }else { 
    printf("La temperatura maxima fue %d, tomada el dia %d %d %d en la estacion de %s\n", temp_max[1], fecha_max[0], fecha_max[1], fecha_max[2], nombreLugares[1]);
   }
  
  if (dif_temp[0]>dif_temp[1]) { 
    printf("La mayor diferencia de temperatura es %d y fue tomada en %s\n", dif_temp[0], nombreLugares[0]);
  }else { printf("La mayor diferencia de temperatura es %d y fue tomada en %s\n", dif_temp[1], nombreLugares[1]);
   }
   
  media_pa[0]=(datos[0][0].pa+datos[0][1].pa+datos[0][2].pa+datos[0][3].pa+datos[0][4].pa)/5;
  media_pa[1]=(datos[1][0].pa+datos[1][1].pa+datos[1][2].pa+datos[1][3].pa+datos[1][4].pa)/5;
  
  printf("El valor medio de la precipitacion acumulada en la estación de La Laguna es %f\n", media_pa[0]);
  printf("El valor medio de la precipitacion acumulada en la estación de Los Cristianos es %f\n", media_pa[0]);
}