#include <stdio.h>

typedef struct{
  char nombre[25];
  char apellido[30];
}TNombre;

typedef struct{
  int dia;
  int mes;
  int anno;
}TFecha;

typedef struct{
  TNombre nombre;
  TFecha fecha_de_contrato;
  float salario_base;
  float complemento;
}Templeado;

Templeado empleado[2];

typedef struct{
  int dia;
  int mes;
  int anno;
}Tfecha_a;

Tfecha_a fecha_actual;

int antiguedad_empleado[2];
float bonificacion[2];
float sueldo[2];

int main (void){
  
  printf("Introduzca el nombre y apellido de el primer empleado: ");
  scanf("%s",empleado[0].nombre.nombre);
  scanf("%s",empleado[0].nombre.apellido);
  printf("Introduzca su fecha de contratacion (dia, mes, año): ");
  scanf("%d",&empleado[0].fecha_de_contrato.dia);
  scanf("%d",&empleado[0].fecha_de_contrato.mes);
  scanf("%d",&empleado[0].fecha_de_contrato.anno);
  printf("Introduzca su salario base: ");
  scanf("%f",&empleado[0].salario_base);
  
  if (empleado[0].salario_base<500){
    printf("Introduzca el valor del complemento: ");
    scanf("%f",&empleado[0].complemento);
  }
  else {
    empleado[0].complemento=0;
  }
  
  printf("Introduzca el nombre y apellido de el segundo empleado: ");
  scanf("%s",empleado[1].nombre.nombre);
  scanf("%s",empleado[1].nombre.apellido);
  printf("Introduzca su fecha de contratacion (dia, mes, año): ");
  scanf("%d",&empleado[1].fecha_de_contrato.dia);
  scanf("%d",&empleado[1].fecha_de_contrato.mes);
  scanf("%d",&empleado[1].fecha_de_contrato.anno);
  printf("Introduzca su salario base: ");
  scanf("%f",&empleado[1].salario_base);
  
  printf("Introduzca la fecha actual (dia mes año): ");
  scanf("%d",&fecha_actual.dia);
  scanf("%d",&fecha_actual.mes);
  scanf("%d",&fecha_actual.anno);
  
  if (empleado[1].salario_base<500){
    printf("Introduzca el valor del complemento: ");
    scanf("%f",&empleado[1].complemento);
  }
  else {
    empleado[1].complemento=0;
  }
  
  switch (fecha_actual.mes){
    case 1:printf("Sueldos del mes de enero");break;
    case 2:printf("Sueldos del mes de febrero");break;
    case 3:printf("Sueldos del mes de marzo");break;
    case 4:printf("Sueldos del mes de abril");break;
    case 5:printf("Sueldos del mes de mayo");break;
    case 6:printf("Sueldos del mes de junio");break;
    case 7:printf("Sueldos del mes de julio");break;
    case 8:printf("Sueldos del mes de agosto");break;
    case 9:printf("Sueldos del mes de septiembre");break;
    case 10:printf("Sueldos del mes de octubre");break;
    case 11:printf("Sueldos del mes de noviembre");break;
    case 12:printf("Sueldos del mes de diciembre");break;
    default: printf("El mes introducido no existe");
  }
  
  antiguedad_empleado[0]=((fecha_actual.anno-empleado[0].fecha_de_contrato.anno)*365)+((fecha_actual.mes-empleado[0].fecha_de_contrato.mes)*30)+(fecha_actual.dia-empleado[0].fecha_de_contrato.dia);
    
  if (antiguedad_empleado[0]>=7300){
    bonificacion[0]=empleado[0].salario_base*0.250000;
  }
  else {
    if (antiguedad_empleado[0]<365){
      bonificacion[0]=empleado[0].salario_base*0.000000;
    }
    else {
      if (antiguedad_empleado[0]<1095){
	bonificacion[0]=empleado[0].salario_base*0.050000;
      }
      else {
	if (antiguedad_empleado[0]<1825){
	  bonificacion[0]=empleado[0].salario_base*0.100000;
	}
	else {
	  if (antiguedad_empleado[0]<3650){
	    bonificacion[0]=empleado[0].salario_base*0.150000;
	  }
	  else {	    
	      bonificacion[0]=empleado[0].salario_base*0.200000;
	  }
	}
      }
    }
  }
  
  sueldo[0]=empleado[0].salario_base+bonificacion[0]+empleado[0].complemento;
  
  printf("Empleado 1: %s %s\n",empleado[0].nombre.nombre, empleado[0].nombre.apellido);
  printf("Antiguedad: %d dias\n",antiguedad_empleado[0]);
  printf("Sueldo base: %f\n",empleado[0].salario_base);
  printf("Bonificacion: %f\n",bonificacion[0]);
  printf("Sueldo: %f\n",sueldo[0]);
  
  antiguedad_empleado[1]=((fecha_actual.anno-empleado[1].fecha_de_contrato.anno)*365)+((fecha_actual.mes-empleado[1].fecha_de_contrato.mes)*30)+(fecha_actual.dia-empleado[1].fecha_de_contrato.dia);
  
   if (antiguedad_empleado[1]>=7300){
    bonificacion[1]=empleado[1].salario_base*0.250000;
  }
  else {
    if (antiguedad_empleado[1]<365){
      bonificacion[1]=empleado[1].salario_base*0.00000;
    }
    else {
      if (antiguedad_empleado[1]<1095){
	bonificacion[1]=empleado[1].salario_base*0.050000;
      }
      else {
	if (antiguedad_empleado[1]<1825){
	  bonificacion[1]=empleado[1].salario_base*0.100000;
	}
	else {
	  if (antiguedad_empleado[1]<3650){
	    bonificacion[1]=empleado[1].salario_base*0.150000;
	  }
	  else {	    
	      bonificacion[1]=empleado[1].salario_base*0.200000;
	  }
	}
      }
    }
  }
  
  sueldo[1]=empleado[1].salario_base+bonificacion[1]+empleado[0].complemento;
  
  printf("Empleado 1: %s %s\n",empleado[1].nombre.nombre, empleado[1].nombre.apellido);
  printf("Antiguedad: %d dias\n",antiguedad_empleado[1]);
  printf("Sueldo base: %f\n",empleado[1].salario_base);
  printf("Bonificacion: %f\n",bonificacion[1]);
  printf("Sueldo: %f\n",sueldo[1]);
}