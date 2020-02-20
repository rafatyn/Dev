# Programa que realiza la busqueda en un vector 
# Version recursiva

size = 4		# tamano de los elementos del vector
N = 10			# numero de elementos del vector
			.data
vector:			.word 	2,3,5,6,8,1,3,2,5,9	
abuscar:		.word   	4        # modifica este valor para que pruebes diferentes busquedas
encontrado:		.word   0	 # tras la ejecucion en Qtspim inspecciona esta posicion de memoria
					 # para comprobar el resultado
cadena : .asciiz  "Introduzca el numero que quiere comprobar: "
cadena1: .asciiz  "\nValor '0' = no encontrado , Valor '1' = encontrado. "



			.text
main:
			la	$a3,vector    	# primer parametro la direccion base del vector
			li	$a1,size		# segundo parametro el numero de elementos del vector
			li  $s0,N
		empieza:
			li $s3,0
                la $a0,cadena
                li $v0,4
                syscall
      
      		li $v0,5
     		syscall
     		move $a2,$v0
     			
      
		jal	blineal     	# quedara en $v0 1 si lo encontro 0 en caso contrario
		
			sw	$v0,encontrado  # almacenamos en resultado de busqueda en una posicion de memoria
			li $v0,1
			lw $a0,encontrado
			syscall
			
			
			
			# salida limpia del sistema

                la $a0,cadena1
                li $v0,4
                syscall

			li	$v0,10
			syscall

# FIN DEL PROGRAMA PRINCIPAL

blineal:	# funcion blinealR: 	$a0 direccion base del vector
                #           $a1 numero de elementos del vector a buscar
                #			$a2 elemento buscado
                #			devuelve:	$v0 = 1 si encontra el elemento $v0 = 0 en caso contrario
           li $v0,0
           beq $a1,$zero,nulo
           

           bucle:
           		blt $s3,$s0,siguiente
           		jr $ra

           		siguiente:
           			addi $sp,$sp,-4
           			sw $ra,0($sp)
           			mul $t0,$s3,$a1
           			addu $t0,$a3,$t0
           			lw $s1,0($t0)
           			addi $s3,$s3,1
           			beq $a2,$s1,found
           			jal bucle

           			lw $ra,0($sp)
           			addi $sp,$sp,4
           			jr $ra

           	found:
           		li $v0,1
           		jr $ra

           	nulo:
           		jr $ra
           			




                
                
                
                
		#  INTRODUCE COMO COMENTARIO EL PSEUDOCÓDIGO O EL PROGRAMA EN LENG. ALTO NIVEL
		
		#int v[10]={1,2,3,4,5,6,7,8,8,0};
		#int recorrido(int i,int abuscar){
		#	if(i<0) return 0;
		#	else
		#		if(v[i]==abuscar) 
		#			return 1;
		#		else 
		#			return recorrido(i-1,abuscar);
		#}
		#int main (void){
		#	int abuscar;
		#	int encontrado=0;
		#	cout << "Introduce valor a buscar:";
		#	cin >> abuscar;
		#	encontrado=recorrido(10,abuscar);
		#	cout << endl << encontrado;
		#}

   # INTRODUCE AQUI EL CÓDIGO DE TU SUBRUTINA
   
   
    
