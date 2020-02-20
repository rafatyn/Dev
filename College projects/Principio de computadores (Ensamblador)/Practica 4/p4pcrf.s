#Practica 4 de Pc;

################################################################
#                     Pseudocodigo en C++:                     #              
################################################################
#int main (void){                                              
#	int n[5][5];                                              
#	int numero;
#         int j;
#         bool error = 1;
#
#cout << "Introduzca el numero de la columna que quiere #comprobar; ";
#		cin  >> j;
#		numero= n[0][j];
#
#		for (int i=1;(i<5)&&(error!=1;i++){
#                   
#                  if( n[i][j] < numero)
#		
#		error= 0;
#	    numero = n[i][j];}
#		
# }
################################################################


################################################################
#                                                              #
#                           MIPS                               #
#                                                              #
################################################################


fila = 4
col =  5
size = 4 

  .data

matriz:   .word 1,2,3,4,5
          .word 1,2,3,4,5
          .word 1,2,3,4,5
          .word 1,2,3,2,5

pedir_numero:   .asciiz "Introduzce la columna a comprobar: "
colum_ordenada: .asciiz "\nLa columna esta ordenada\n"
colum_no_ordenada: .asciiz "\nLa columna no esta ordenada\n"
finalizar: .asciiz "\nEl programa se ha finalizado\n"

  .text

main:

   la $a0,pedir_numero
   li $v0, 4
  syscall     
   li $v0, 5      
  syscall     
   la $s1,matriz
   move $t0,$v0
   sub $t0,1
   li $t1,1  
   li $t6,fila
   li $t3,0 
  
for: 

   bge  $t1,$t6,fin  
   mul $t4,$t1,col      
   addu $t4,$t4,$t0
   mul $t4,$t4,size
   addu $t4,$t4,$s1
   lw $t4,0($t4)   
   
   add $t1,1

   mul $t5,$t1,col
   addu $t5,$t5,$t0
   mul $t5,$t5,size
   addu $t5,$t5,$s1
   lw $t5,0($t5)

   blt $t5,$t4,condi
   add $t3,1
   b for
 
fin:

   la $a0,colum_ordenada
   li $v0,4
  syscall

   la $a0,finalizar
   li $v0,4
  syscall

   li $v0,10
  syscall
  
condi:
  
   la $a0,colum_no_ordenada
   li $v0,4
  syscall
   
   la $a0,finalizar
   li $v0,4
  syscall

   li $v0,10
  syscall

#END

















































































