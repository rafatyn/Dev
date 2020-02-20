#include <stdio.h>

int n[5];
int numeros[5];
int numero_p[5];
int numero_ip[5];
int suma_np;
float media_np;
int x=0;
int y=0;
int menor;
int mayor;

int main (void){
    
    printf("Introduzca un numero: ");
    scanf("%d",&n[0]);
    printf("Introduzca otro numero: ");
    scanf("%d",&n[1]);
    printf("Introduzca otro numero: ");
    scanf("%d",&n[2]);
    printf("Introduzca otro numero: ");
    scanf("%d",&n[3]);
    printf("Introduzca otro numero: ");
    scanf("%d",&n[4]);
    
    numeros[0]=n[0]%2;
    numeros[1]=n[1]%2;
    numeros[2]=n[2]%2;
    numeros[3]=n[3]%2;
    numeros[4]=n[4]%2;
    
    numero_p[0]=0;
    numero_p[1]=0;
    numero_p[2]=0;
    numero_p[3]=0;
    numero_p[4]=0;
        
    if (numeros[0]==0){
        numero_p[0]=n[0];
        x++;
    }    else {
            numero_ip[0]=n[0];
            y++;
            menor=n[0];
            mayor=n[0];
        }
    if (numeros[1]==0){
        numero_p[1]=n[1];
        x++;
    }    
        else {
            numero_ip[1]=n[1];
            y++;
            if (n[1]<menor){
                menor=n[1];
            }
            if (n[1]>mayor){
                mayor=n[1];
            }
        }
    if (numeros[2]==0){
        numero_p[2]=n[2];
        x++;
    }    
        else {
            numero_ip[2]=n[2];
            y++;
            if (n[2]<menor){
                menor=n[2];
            }
            if (n[2]>mayor){
                mayor=n[2];
            }
        }
    if (numeros[3]==0){
        numero_p[3]=n[3];
        x++;
    }    
        else {
            numero_ip[3]=n[3];
            y++;
            if (n[3]<menor){
                menor=n[3];
            }
            if (n[3]>mayor){
                mayor=n[3];
            }
        }
    if (numeros[4]==0){
        numero_p[4]=n[4];
        x++;
    }    
        else {
            numero_ip[4]=n[4];
            y++;
            if (n[4]<menor){
                menor=n[4];
            }
            if (n[4]>mayor){
                mayor=n[4];
            }
        }
    
    suma_np = numero_p[0]+numero_p[1]+numero_p[2]+numero_p[3]+numero_p[4];
    
    media_np = suma_np/x;
    
    printf("Hay %d numeros pares, la suma de ellos es %d y la media es de ellos es %f\n",x,suma_np,media_np);
    printf("Hay %d numeros impares, el menor de ellos es el %d y el mayor de ellos es el %d\n",y,menor,mayor);
}
 