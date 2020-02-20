# Programa que busca un elemento en un vector.

size = 4		# tamano de los elementos del vector
N = 10			# numero de elementos del vector
			.data
vector:			.word	2,3,5,6,8,1,3,2,5,9	
abuscar:		.word	0      # modifica este valor para que pruebes diferentes busquedas
encontrado:		.word   0	 # tras la ejecucion en Qtspim inspecciona esta posicion de memoria
cadena : .asciiz  "Introduzca el numero que quiere comprobar: "
cadena1: .asciiz  "\nValor '0' = no encontrado , Valor '1' = encontrado. "
					 # para comprobar el resultado

			.text
main:
	la $a3,vector    	# primer parametro la direccion base del vector
	li $a1,N		# segundo parametro el numero de elementos del vector
	li $s0,size
empieza:
      li $s3,0
      
      la $a0,cadena
      li $v0,4
      syscall
      
      li $v0,5
      syscall
      move $a2,$v0

      li  $v0,0
	
	jal	blineal     	# quedara en $v0 1 si lo encontro 0 en caso contrario
			
      sw $v0,encontrado  # almacenamos en resultado de busqueda en una posicion de memoria
      move $s2,$v0
			
      li $v0,1
      move $a0,$s2
      syscall
      
      la $a0,cadena1
      li $v0,4
      syscall
			
      # salida limpia del sistema
	 li	$v0,10
	 syscall

# FIN DEL PROGRAMA PRINCIPAL

blineal:	# funcion blinealR: 	$a0 direccion base del vector
                #                       $a1 numero de elementos del vector a buscar
                #			$a2 elemento buscado
                #	devuelve:	$v0 = 1 si encontra el elemento $v0 = 0 en caso contrario
                
                
                
		#  INTRODUCE COMO COMENTARIO EL PSEUDOCÓDIGO O EL PROGRAMA EN LENG. ALTO NIVEL
		#	int main (void){		
		#   		int vector[10]={2,3,5,6,8,1,3,2,5,9};
		#    		int abuscar=6;
		#		int encontrado=0;	
    #		     for(int i=10;i<10;i++)
    #	      		if(vector[i]==abuscar){
    #		         		encontrado=1;
    #		         		break;
		#			} cout<<encontrado;
		#	}
   	
    # INTRODUCE AQUI EL CÓDIGO DE TU SUBRUTINA
   		
   		for:
   			mul $t1,$s0,$s3
   			addi $s3,$s3,1
   			addu $t1,$a3,$t1
   			lw $s1,0($t1)
   			beq $a2,$s1,encontrar
   			blt $s3,$a1,for
   			jr $ra
   			
   		encontrar: 
   			li $v0,1
   			jr $ra
   			
   		
   		
   			
   			
   		
   		
