.data
	vetor: .int 10, 9, 8, 7, 6

.text
.globl main
	main:
	addi $t0, $zero, 0
	lw $s0, 0($t0)
	lw $s1, 4($t0)
	lw $s2, 8($t0)
	lw $s3, 12($t0)
	lw $s4, 16($t0)
	addi $t1, $zero, 2
	mult $s0, $t1
	mflo $s0
	mult $s1, $t1
	mflo $s1
	mult $s2, $t1
	mflo $s2
	mult $s3, $t1
	mflo $s3
	mult $s4, $t1
	mflo $s4
	sw $s0, 0($zero)
	sw $s1, 4($zero)
	sw $s2, 8($zero)
	sw $s3, 12($zero)
	sw $s4, 16($zero)
	lw $t0, 0($zero)
	lw $t1, 4($zero)
	lw $t2, 8($zero)
	lw $t3, 12($zero)
	lw $t4, 16($zero)
	syscall
