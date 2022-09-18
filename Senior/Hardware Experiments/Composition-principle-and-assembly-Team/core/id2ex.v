`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/07/03 12:37:06
// Design Name: 
// Module Name: id2ex
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


module id2ex(
    input               clk,
    input               rst,
    
    input               RegWriteD,
    input               MemToRegD,
    input               MemWriteD,
    input [4:0]         ALUCtrlD,
    input [1:0]         ALUSrcD,
    input [1:0]         RegDstD,
    input [31:0]        RD1D,
    input [31:0]        RD2D,
    input [4:0]         RsD,
    input [4:0]         RtD,
    input [4:0]         RdD,
    input [31:0]        ImmD,

    input               LoadUnsignedD,
    input [1:0]         MemWidthD, 
 
    input [31:0]        PCD,

    
    output reg          RegWriteE,
    output reg          MemToRegE,
    output reg          MemWriteE,
    output reg [4:0]    ALUCtrlE,
    output reg [1:0]    ALUSrcE,
    output reg [1:0]    RegDstE,
    output reg [31:0]   RD1E,
    output reg [31:0]   RD2E,
    output reg [4:0]    RsE,
    output reg [4:0]    RtE,
    output reg [4:0]    RdE,
    output reg [31:0]   ImmE,

    output reg          LoadUnsignedE,
    output reg [1:0]    MemWidthE,
    output reg [31:0]   PCE
    );
    
    always @(posedge clk or negedge rst) begin
        if (!rst) begin
            RegWriteE           <= 1'b0;
            MemToRegE           <= 1'b0;
            MemWriteE           <= 1'b0;
            ALUCtrlE            <= 5'b0;
            ALUSrcE             <= 2'b0;
            RegDstE             <= 2'b0;
            RD1E                <= 32'b0;
            RD2E                <= 32'b0;
            RsE                 <= 5'b0;
            RtE                 <= 5'b0;
            RdE                 <= 5'b0;
            ImmE                <= 32'b0;   
            LoadUnsignedE       <= 1'b0;
            MemWidthE           <= 2'b0;
            PCE                 <= 32'b0;
        end
        else  begin
            RegWriteE           <= RegWriteD;
            MemToRegE           <= MemToRegD;
            MemWriteE           <= MemWriteD;
            ALUCtrlE            <= ALUCtrlD;
            ALUSrcE             <= ALUSrcD;
            RegDstE             <= RegDstD;
            RD1E                <= RD1D;
            RD2E                <= RD2D;
            RsE                 <= RsD;
            RtE                 <= RtD;
            RdE                 <= RdD;
            ImmE                <= ImmD;
            LoadUnsignedE       <= LoadUnsignedD;
            MemWidthE           <= MemWidthD;
            PCE                 <= PCD;
        end
    end 
    
endmodule
