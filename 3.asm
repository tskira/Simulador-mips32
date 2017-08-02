.text
.globl main
	main:
	addi $t1, $zero, 16
	jr $t1
	addi $t0, $zero, 5
	addi $t0, $zero, 5
	teste:
	syscall
