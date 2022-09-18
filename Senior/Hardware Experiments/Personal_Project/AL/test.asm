.org 0x0
.set noat
.set noreorder
.set nomacro
.global _start
	    
_start:
	addiu $t1, $t1, 10
	add $t2, $t1, $t1
	addu $t3, $t2, $t2
	lui $t4, 0x1001
	sw $t3, ($t4)
	lw $t5, ($t4)
	beq $t3, $t5, loop
	addi $t1, $t1, 100

loop:
	add $t2, $t2, $t2
	j loop
	addi $t1, $t1, 100
