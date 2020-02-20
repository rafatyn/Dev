# PROGRAMA QUE REALIZA UNA BÚSQUEDA LINEAL DE UN ELEMENTO
# EN UN VECTOR.

size = 4		# tamano de los elementos del vector
N = 10			# numero de elementos del vector
			.data
vector:			.word	2,3,5,6,8,1,3,2,5,9	
abuscar:		.word	6        # modifica este valor para que pruebes diferentes busquedas
encontrado:		.word   0	 # tras la ejecucion en Qtspim inspecciona esta posicion de memoria
					 # para comprobar el resultado

			.text
main:
			la	$a0,vector    	# primer parametro la direccion base del vector
			li	$a1,N		# segundo parametro el numero de elementos del vector
			lw	$a2,abuscar     # tercer parametro el elemento a buscar
			jal	blineal     	# quedara en $v0 1 si lo encontro 0 en caso contrario
			sw	$v0,encontrado  # almacenamos en resultado de busqueda en una posicion de memoria
			
			# salida limpia del sistema
			li	$v0,10
			syscall
# FIN DEL PROGRAMA PRINCIPAL

blineal:	# funcion blinealR: 	$a0 direccion base del vector
                #                       $a1 numero de elementos del vector a buscar
                #			$a2 elemento buscado
                #	devuelve:	$v0 = 1 si encontra el elemento $v0 = 0 en caso contrario
		#  INTRODUCE COMO COMENTARIO EL PSEUDOCÓDIGO O EL PROGRAMA EN LENG. ALTO NIVEL
		#			
		#   			
		#    			
        

   # INTRODUCE AQUI EL CÓDIGO DE TU SUBRUTINA
    
