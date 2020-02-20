##################################################################                        Programa en C++                        #
#################################################################
 
# #Define M 10
# Int n[M];
# Float suma;
# Float media;

# int main(void){
#  for (int i=0; i<M; i++)
#    cout << "Introduzca un numero: "; cin >> n[i];
#    suma += n[i];
# media = suma/M;
# cout << "La media de los numeros es: " << media << endl;
# }

###############################################################                                                                            
#                 Programa en presicion simple                #
###############################################################

           .data   
     		 	
# Cadena a mostrar por pantalla

cad1:	.asciiz "Introduce un numero: ";                   
cad2:	.asciiz "La media es: ";  
                 
        	.text			

main:

# Carga en los registros salvados $s1, $s2, $s3 los numeros #empleados para hacer el contador

li   $s1 0
li   $s2,10
li   $s3,1

# Hace una copia "cruda" del registro $s2 al registro $f0 y #despues lo convierte en un flotante de presicion simple

mtc1 $s2,$f0
cvt.s.w $f21,$f0

# Etiqueta del for

for:

# Imprime por pantalla la cadena 1

li	$v0,4		
la	$a0,cad1
syscall

# Pide por teclado un numero en presicion simple

li   $v0,6
syscall

# Se suma el numero de f20 con el tomado en $f0 y lo guardo de #nuevo en $f20 para que al volver a hacer el for no haga falta #hacer ningun move

add.s $f20,$f20,$f0

# Esta es la suma del contador, le suma el valor de $s3 (1.0) a #el valor de $s1 

add $s1,$s1,$s3

# Hace la comparacion entre el valor del registro $s1 con el del #registro $s2, si el valor de la comparacion es verdadero salta a #la etiqueta Fin_for, la cual se salta la orden de jump hacia la #etiqueta del for

beq $s1,$s2,Fin_for

# Salta hacia la etiqueta for

j for

# Aqui se acaba el for

Fin_for:

# Hace la division de la suma de los numeros entre el numero de #numeros pedidos (La media)

div.s $f20,$f20,$f21

# Mueve el valor del registro $f20 al registro $f12 que es el que #se muestra por pantalla cuando se hace el li $v0,2

mov.s $f12,$f20

# Imprime por pantalla la cadena 2

li	$v0,4		
la	$a0,cad2
syscall


# Muestra por pantalla el valor de la media en flotante de #presicion simple

li $v0,2
syscall

# Es el exit
li $v0,10
syscall

#################################################################
#                          Cuestion 1                           #
#################################################################


# En el programa use los registros $f0, $f20, $f21, $s1, $s2, 
#$s3 y $f12. 

# El registro $f0 lo use porque es donde se almacena el valor #pedido por teclado en flotante de presicion simple, por lo 
#que para evitar el uso de moves innecesarios lo use tambie 
#para sumar, y ademas tambien lo uso como registro intermedio #cuando hago la copia "cruda" de $s2 a $f0 y despues convierto #el valor de $f0 en un flotante de presicion simple y lo #almaceno en $f21

# EL registro $f20 fue el que use para guardar el resultado de #la suma y mas tarde el de la division, y elegi usar el $f20 #porque es un registro salvado y no se modifica durante los #saltos hacia etiquetas

# Los registros $s1, $s2, $s3 son los que use para cargar los #datos del contador necesarios para delimitar el recorrido del #for y use estos porque son registros salvados que no se #modifican con los slatos hacia etiquetas

# El registro $f12 lo use para almacenar el resultado de la #media porque ese es el registro que usa el lenguaje para #mostrar por pantalla un numero flotante en presicion simple 

##################################################################                           Cuestion 2                          #
#################################################################

# Para que el programa funcione en presicion doble solo hay 
#que cambiar los regististros usados para almacenar los 
#valores ya que los valores en presicion doble ocupan un #registro y el contiguo, por lo que tanmbien hay que cambiar 
#las operaciones para que trabajen con los nuevos registros en #presicion doble 

##################################################################                    Programa en presicion doble                #
#################################################################

#      	.data   
     		 	
#  Cadena a mostrar por pantalla

# cad1:	.asciiz "Introduce un numero: ";                   
# cad2:	.asciiz "La media es: ";  
                 
#        	.text			

# main:

#  Carga en los registros salvados $s1, $s2, $s3 los numeros
# empleados para hacer el contador

# li   $s1 0
# li   $s2,10
# li   $s3,1

#  Hace una copia "cruda" del registro $s2 al registro $f0 y
# despues lo convierte en un flotante de presicion simple

# mtc1 $s2,$f0
# cvt.d.w $f22,$f0

#  Etiqueta del for

# for:

#  Imprime por pantalla la cadena 1

# li	$v0,4		
# la	$a0,cad1
# syscall

#  Pide por teclado un numero en presicion simple

# li   $v0,7
# syscall

#  Se suma el numero de f20 con el tomado en $f0 y lo guardo
# de nuevo en $f20 para que al volver a hacer el for no haga
# falta hacer ningun move

# add.d $f20,$f20,$f0

#  Esta es la suma del contador, le suma el valor de $s3 (1.0) 
# a el valor de $s1 

# add $s1,$s1,$s3

#  Hace la comparacion entre el valor del registro $s1 con el 
# del registro $s2, si el valor de la comparacion es verdadero 
# salta a la etiqueta Fin_for, la cual se salta la orden de
# jump hacia la etiqueta del for

# beq $s1,$s2,Fin_for

#  Salta hacia la etiqueta for

# j for

#  Aqui se acaba el for

# Fin_for:

#  Hace la division de la suma de los numeros entre el numero
# de numeros pedidos (La media)

# div.d $f20,$f20,$f22

#  Mueve el valor del registro $f20 al registro $f12 que es el 
# que se muestra por pantalla cuando se hace el li $v0,2

# mov.d $f12,$f20

#  Imprime por pantalla la cadena 2

# li	$v0,4		
# la	$a0,cad2
# syscall


#  Muestra por pantalla el valor de la media en flotante de
# presicion simple

# li $v0,3
# syscall

#  Es el exit

# li $v0,10
# syscall             

