    .org 0x0
    .set noat
    .set noreorder
    .set nomacro
    .global _start
_start:
    lui $1, 0xbfaf      # 0000
    ori $1, $1, 0x8000  # 2100    digital num led address
    lui $2, 0xbfc1      # 0000
    ori $2, 0x0000      # 2200    $2 = 0xbfc1_0000 which is the head address of an array where the fibonacci array store
    lui $3, 0x0000
    ori $3, 0x0001      # $3 = 1
    lui $4, 0x0000
    ori $4, 0x0004      # $4 = 4


   
    addi $12, $10, 0x0001   # $12 = $10 + $11
    addi $11, $10, 0x0002   # $12 = $10 + $11
	lui $4, 0x0000
	lui $4, 0x0000
	lui $4, 0x0000
	lui $4, 0x0000
    add $13, $10, $11    # $10 = $11
    sw  $13, 0x0005

    

   
