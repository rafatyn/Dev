###############################################################                                                            #
#                        Practica 6                          #
#                                                            #
##############################################################


###############################################################
#int calcular_enteros(matriz& A,int m,int n){ 
#		 for(int i=0;i<m;i++){
#			for(int j=0;j<n;j++){
#				if(A.[i][j]%2=0)
#					par++;
#}
#
#
#int main(){
#
#int n=5;
#int m=5;
#int matriz[m][n];
#int par=0;
#
#cout << "Hay " << par << "numeros pares" << endl;
#}
#
##############################################################


fila=3
col=3
size=4

.data

matriz:   .word 2,4,6
          .word 3,3,3
          .word 3,12,5

Cad:  .asciiz "La matriz tiene "
Cad1: .asciiz " numeros pares\n"

.text


main:

	la $s1,matriz
	li $t9,fila
	li $t5,col
	mul $s3,$t9,$t5
	sub $s3,1
	li $t5,2
	
	j for


for:
	bge $t1,$s3,fin
	mul $t2,$t1,size
	addu $t2,$t2,$s1
	lw $t2,0($t2)
	
	addi $t1,1

	div $t2,$t5
	mfhi $t6
	beq $t6,$t7,par
	j for


fin:
	la $a0,Cad
	li $v0,4
	syscall

	move $a0,$t8
	li $v0,1
	syscall

	la $a0,Cad1
	li $v0,4
	syscall

	li $v0,10
	syscall

	

par:
	addi $t8,1
	j for


