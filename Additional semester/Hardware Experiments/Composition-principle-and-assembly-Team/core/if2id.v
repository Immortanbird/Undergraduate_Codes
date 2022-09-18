`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/07/03 12:37:06
// Design Name: 
// Module Name: if2id
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


module if2id(
    input               clk,
    input               rst,

    
    input  [31:0]       ReadDataF,             //
    input  [31:0]       PCPlus4F,              //PCPlus4F = PCF + 4;下一条指令地址
    input               NextDelaySlotD,       //JumpD || BranchD
    input  [31:0]       PCF,                  //当前指令地址
    //input  [31:0]       ExceptionTypeF,       //异常类型
    
    output reg [31:0]   InstrD,
    output reg [31:0]   PCPlus4D,
    output reg [31:0]   PCD
    //output reg [31:0]   ExceptionTypeD
    );
    
    always @(posedge clk or negedge rst) begin
        if (!rst) begin
            InstrD          <= 32'b0;
            PCPlus4D        <= 32'b0;
            PCD             <= 32'b0;
        end
        else  begin
            InstrD          <= ReadDataF;
            PCPlus4D        <= PCPlus4F;
            PCD             <= PCF;
        end
    end 

endmodule
