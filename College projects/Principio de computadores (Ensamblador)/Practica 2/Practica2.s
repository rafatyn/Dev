#PRACTICA 2 PRINCIPIO DE COMPUTADORAS
#Suma dos número enteros y almacena el resultado
              .data               # Seccion declaracion de datos
op1:            .word 25          # variable op1 con valor inicial 0
op2:            .word 7           # variable op2 con valor inicial 0
suma:           .word 0           # variable suma con valor inicial 0
resta:          .word 0           # variable resta con valor inicial 0
multbajo:       .word 0           # variable multbajo con valor inicial 0
multalto:       .word 0           # variable multalto con valor inicial 0
divs:           .word 0           # variable divs con valor inicial 0
resto:          .word 0           # variable resto con valor inicial 0
cadena:         .asciiz "La suma es: ";
cadena1:        .asciiz "\nLa resta es: ";
cadena2:        .asciiz "\nLa multiplicacion es: ";
cadena3:        .asciiz "\nLa division es: ";
cadena4:        .asciiz "\nEl resto es: ";
 
              .text               # Seccion de codigo de usuario
main:                             # La etiqueta main es el inicio

lw $s0, op1                       # cargo en el registro $s0 el valor de op1
lw $s1, op2                       # cargo en el registro $s1 el valor de op2
       
 # suma de enteros            
add $s2, $s0, $s1   # hace la suma
sw $s2, suma   # almacena en el registro el resultado de la operacion

li $v0,4   # le indica a la maquina que va a imprimir una cadena de caracteres
la $a0,cadena   # muestra la cadena de caracteres 0 por la consola
syscall
li $v0, 1   # le indica a la maquina que va a imprimir un numero
lw $a0,suma   # muestra el resultado de la suma por consola
syscall

 # resta de enteros
sub $t1, $s0, $s1   # hace la resta
sw $t1, resta   # almacena en el registro el resultado de la operacion

li $v0,4   # le indica a la maquina que va a imprimir una cadena de caracteres
la $a0,cadena1   # muestra la cadena de caracteres 1 por la consola
syscall
li $v0, 1   # le indica a la maquina que va a imprimir un numero
lw $a0,resta   # muestra el resultado de la resta por consola
syscall

 # multiplicacion de enteros
mult $s0, $s1   # hace la multiplicacion
mflo $t2   # guarda los valores del low en el registro
sw $t2, multbajo   # almacena en el registro el resultado de la operacion
mfhi $t3   # guarda los valores del high en el registro
sw $t3, multalto   # almacena en el registro el resultado de la operacion


li $v0,4   # le indica a la maquina que va a imprimir una cadena de caracteres 
la $a0,cadena2   # muestra la cadena de caracteres 2 por la consola
syscall
li $v0, 1   # le indica a la maquina que va a imprimir un numero
lw $a0,multbajo   # muestra el resultado de la multiplicacion por consola
syscall

 # Division de enteros
div $s0, $s1    # hace la division
mflo $t4   # guarda los valores del low en el registro
sw $t4, divs   # almacena en el registro el resultado de la operacion
mfhi $t5   # guarda los valores del high en el registro
sw $t5, resto   # almacena en el registro el resultado de la operacion


li $v0,4   # le indica a la maquina que va a imprimir una cadena de caracteres
la $a0,cadena3   # muestra la cadena de caracteres 3 por la consola
syscall
li $v0, 1   # le indica a la maquina que va a imprimir un numero
lw $a0,divs   # muestra el resultado de la division por consola
syscall


li $v0,4   # le indica a la maquina que va a imprimir una cadena de caracteres
la $a0,cadena4   # muestra la cadena de caracteres 4 por la consola
syscall
li $v0, 1   # le indica a la maquina que va a imprimir un numero
lw $a0,resto   # muestra el resultado de el resto por consola
syscall

 # se hace una salida limpia del sistema (exit es codigo 10)
li $v0, 10
  syscall
# END