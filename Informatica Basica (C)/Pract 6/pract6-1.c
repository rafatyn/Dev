#include <stdio.h>

int d,m,a;

int main (void){
  printf("Escriba el año en el que nació:");
  scanf("%d",&a);
  printf("Escriba el numero del mes del año en el que nació:");
  scanf("%d",&m);
  printf("Escriba el dia del mes en el que nació:");
  scanf("%d",&d);
  a= a-1980;
  a= a*365;
  m= m-1;
  m= m*30;
  d= d-1;
  d= a+m+d;
  printf("Desde el 01/01/1980 hasta la su fecha de nacimiento han pasado %d dias \n",d);
}