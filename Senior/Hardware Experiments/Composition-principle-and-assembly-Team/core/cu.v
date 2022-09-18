`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/08/23 18:34:02
// Design Name: 
// Module Name: mycu
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

`include "macros.vh"

module cu(
 input                 rst,
 
 input  [31:0]               instr,
 
    output          RegWriteD,
    output          MemToRegD,
    output          MemWriteD,
    output [4:0]    ALUCtrlD,
    output [1:0]    ALUSrcD,
    output [1:0]    RegDstD,
    output          ImmUnsigned,
    output [5:0]    BranchD,
    output          JumpD,
    output          JRD,
    output          LinkD,
    output [1:0]    HiLoWriteD,
    output [1:0]    HiLoToRegD,
    output          CP0WriteD,
    output          CP0ToRegD,
    output          LoadUnsignedD,
    output [1:0]    MemWidthD,
    output          BadInstrD,
    output          BreakD,
    output          SysCallD,
    output          EretD
    );
    
    
 wire  [5:0]      OpD = instr[31:26];
 wire  [4:0]      Rsd = instr[25:21];
 wire  [4:0]      Rtd = instr[20:16];
 wire  [5:0]      FuncD = instr[5:0];
 wire  [5:0]      inst_id = get_inst_id(OpD,FuncD);
 function [5:0] get_inst_id(input [5:0] opcode, input [5:0] func);
 begin
      case(opcode)
            `OP_SW    : get_inst_id =  `ID_SW;
            `OP_LW    : get_inst_id =  `ID_LW;
            `OP_XORI  : get_inst_id =  `ID_XORI;
            `OP_LUI   : get_inst_id =  `ID_LUI;
            `OP_BEQ   : get_inst_id =  `ID_BEQ;
            `OP_BNE   : get_inst_id =  `ID_BNE;
            `OP_ORI   : get_inst_id =  `ID_ORI;
            `OP_ADDI  : get_inst_id =  `ID_ADDI;
            `OP_ADDIU : get_inst_id =  `ID_ADDIU;
            `OP_JAL   : get_inst_id =  `ID_JAL;
            `OP_J     : get_inst_id =  `ID_J;
            
            `OP_FUNC :
             begin
                case(func)
                    `FUNC_ADD    : get_inst_id =    `ID_ADD;
                    `FUNC_ADDU   : get_inst_id =    `ID_ADDU;
                    `FUNC_OR     : get_inst_id =    `ID_OR;
                    `FUNC_SLTU   : get_inst_id =    `ID_SLTU;
                    `FUNC_SLT    : get_inst_id =    `ID_SLT;
                    `FUNC_SUBU   : get_inst_id =    `ID_SUBU;  
                    `FUNC_SUB    : get_inst_id =    `ID_SUB;
                    `FUNC_XOR    : get_inst_id =    `ID_XOR;
                    `FUNC_SLL    : get_inst_id =    `ID_SLL;
                    `FUNC_SRL    : get_inst_id =    `ID_SRL;
                    `FUNC_JR     : get_inst_id =    `ID_JR;
                     default     : get_inst_id =    `ID_NULL;
                endcase
                end
        endcase
        end
    endfunction    
            
 assign {RegWriteD, RegDstD, ALUSrcD, ImmUnsigned, BranchD, JumpD, JRD,
            MemWriteD, MemToRegD, LoadUnsignedD, MemWidthD} = rst ? get_control(inst_id) : `CTRL_NULL;
    function [18:0] get_control(input [6:0] inst_id);

                begin
                case(inst_id)
                    `ID_SW     :get_control =    `CTRL_SW;
                    `ID_LW     :get_control =    `CTRL_LW;
                    `ID_XORI   :get_control =    `CTRL_ITYPEU;
                    `ID_LUI    :get_control =    `CTRL_ITYPE;
                    `ID_BEQ    :get_control =    `CTRL_BEQ;
                    `ID_BNE    :get_control =    `CTRL_BNE;
                    `ID_ORI    :get_control =    `CTRL_ITYPEU;
                    `ID_ADDI   :get_control =    `CTRL_ITYPE;
                    `ID_ADDIU  :get_control =    `CTRL_ITYPE;
                    `ID_J      :get_control =     `CTRL_J;
                    `ID_ADD    :get_control =    `CTRL_RTYPE;
                    `ID_ADDU   :get_control =    `CTRL_RTYPE;
                    `ID_OR     :get_control =    `CTRL_ITYPEU;
                    `ID_SLTU   :get_control =    `CTRL_RTYPE;
                    `ID_SLT    :get_control =    `CTRL_RTYPE;
                    `ID_SUBU   :get_control =    `CTRL_RTYPE;
                    `ID_SUB    :get_control =    `CTRL_RTYPE;
                    `ID_XOR    :get_control =    `CTRL_RTYPE;
                    `ID_SLL    :get_control =    `CTRL_RTYPES;
                    `ID_SRL    :get_control =    `CTRL_RTYPES;
                    `ID_JR     :get_control =    `CTRL_JR;
                    default    :get_control =    `CTRL_NULL;
                endcase
           end
           endfunction

           
          assign ALUCtrlD = rst? get_alu_op(inst_id):`ALU_NULL;
          function [4:0] get_alu_op(input [5:0] inst_id);
                    begin
                    case(inst_id)
                    `ID_SW         :get_alu_op  =  `ALU_ADD;
                    `ID_LW         :get_alu_op  =  `ALU_ADD;
                    `ID_ADD        :get_alu_op  =  `ALU_ADDE;
                    `ID_ADDI       :get_alu_op  =  `ALU_ADDE;
                    `ID_ADDU       :get_alu_op  =  `ALU_ADDU;
                    `ID_ADDIU      :get_alu_op  =  `ALU_ADDU;
                    `ID_LUI        :get_alu_op  =  `ALU_LUI;
                    `ID_OR         :get_alu_op  =  `ALU_OR;
                    `ID_ORI        :get_alu_op  =  `ALU_OR;
                    `ID_SLL        :get_alu_op  =  `ALU_SLL;
                    `ID_SLT        :get_alu_op  =  `ALU_SLT;
                    `ID_SLTU       :get_alu_op  =  `ALU_SLTU;
                    `ID_SRL        :get_alu_op  =  `ALU_SRL;
                    `ID_BEQ        :get_alu_op  =  `ALU_SUB;
                    `ID_BNE        :get_alu_op  =  `ALU_SUB;
                    `ID_SUB        :get_alu_op  =  `ALU_SUBE;
                    `ID_SUBU       :get_alu_op  =  `ALU_SUBU;
                    `ID_XOR        :get_alu_op  =  `ALU_XOR;
                    `ID_XORI       :get_alu_op  =  `ALU_XOR;
                    default        :get_alu_op  =  `ALU_NULL;
                    endcase
              end
              endfunction
                    
                    
           
endmodule
