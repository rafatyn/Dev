# PRACTICA 4. PRINCIPIO DE COMPUTADORES.
# programa que valida si una columna de la matriz expuesta
# esta ordenada de forma creciente
# La matriz tiene dimension mxn

m = 4		# numero de filas de m1
n = 5		# numero de columnas de  m1
size = 4	# tamano de cada elemento

			.data
m1:			.word	1,2,3,4,5
			.word	1,2,3,4,5
                        .word	1,2,3,4,5
                        .word	1,2,3,2,5
            

col:                    .word   3 # variable con la columna que queremos comprobar
                                  # la primera fila es la fila 0
                                  # la primera columna es la columna 0

ordenada:		.asciiz "La columna esta ORDENADA\n"
desordenada:		.asciiz "La columna esta DESORDENADA\n"
                                
			
			.text

# INTRODUCIR COMENTADO EL ALGORITMO PROPUESTO EN LENGUAJE DE ALTO NIVEL



main:
        

	    # salida del sistema
            li	$v0,10
            syscall
			
