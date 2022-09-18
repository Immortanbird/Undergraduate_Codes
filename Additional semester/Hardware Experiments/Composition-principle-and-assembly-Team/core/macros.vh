// inst & func def
`define		OP_ADDI			6'b001000
`define		OP_ADDIU		6'b001001
`define		OP_LUI			6'b001111
`define		OP_ORI			6'b001101
`define		OP_XORI			6'b001110
`define		OP_BEQ			6'b000100
`define		OP_BNE			6'b000101
`define		OP_J			6'b000010
`define		OP_JAL			6'b000011
`define		OP_LW			6'b100011
`define		OP_SW			6'b101011
`define		OP_FUNC			6'b000000
`define		FUNC_ADD		6'b100000
`define		FUNC_ADDU		6'b100001
`define		FUNC_SUB		6'b100010
`define		FUNC_SUBU		6'b100011
`define		FUNC_SLT		6'b101010
`define		FUNC_SLTU		6'b101011
`define		FUNC_OR			6'b100101
`define		FUNC_XOR		6'b100110
`define		FUNC_SLL		6'b000000
`define		FUNC_SRL		6'b000010
`define		FUNC_JR			6'b001000
`define		FUNC_AND		6'b100100


// inst_type id def
`define		ID_NULL			0
`define		ID_ADD			1
`define		ID_ADDI			2
`define		ID_ADDU			3
`define		ID_ADDIU		4
`define		ID_SUB			5
`define		ID_SUBU			6
`define		ID_SLT			7
`define		ID_SLTU			8
`define		ID_LUI			9
`define		ID_OR			10
`define		ID_ORI			11
`define		ID_XOR			12
`define		ID_XORI			13
`define		ID_SLL			14
`define		ID_SRL			15
`define		ID_BEQ			16
`define		ID_BNE			17
`define		ID_J			18
`define		ID_JAL			19
`define		ID_JR			20
`define		ID_LW			21
`define		ID_SW			22
`define		ID_AND			23


// alu cmd def
`define		ALU_NULL		0
`define		ALU_ADD			1		//从LW和SW映射
`define		ALU_ADDE		2		//从ADD和ADDI映射
`define		ALU_ADDU		3		//从ADDU和ADDIU映射
`define		ALU_LUI			4		//从LUI映射
`define		ALU_OR			5		//从OR和ORI映射
`define		ALU_SLL			6		//从SLL映射
`define		ALU_SLT			7		//从SLT映射
`define		ALU_SLTU		8		//从SLTU映射
`define		ALU_SRL			9		//从SRL映射
`define		ALU_SUB			10		//从BEQ和BNE映射
`define		ALU_SUBE		11		//从SUB映射
`define		ALU_SUBU		12		//从SUBU映射
`define		ALU_XOR			13		//从XOR和XORI映射
`define		ALU_AND			14		//从AND映射


`define		CTRL_NULL		19'b0000000000000000000
`define		CTRL_ITYPE		19'b1000100000000000000
`define		CTRL_ITYPEU		19'b1000110000000000000
`define		CTRL_RTYPE		19'b1010000000000000000
`define		CTRL_RTYPES		19'b1011000000000000000
`define		CTRL_LW			19'b1000100000000001011
`define		CTRL_SW			19'b0000100000000010011
`define		CTRL_BEQ		19'b0000000000010000000
`define		CTRL_BNE		19'b0000000000100000000
`define		CTRL_J			19'b0000000000001000000
`define		CTRL_JR			19'b0000000000001100000

