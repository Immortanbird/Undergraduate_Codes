`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/07/03 12:37:06
// Design Name: 
// Module Name: mem2wb
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


module mem2wb(
    input               clk,
    input               rst,
    input               en,
    
    input               RegWriteM,
    input               MemToRegM,
    input [31:0]        ReadDataM,
    input [31:0]        ResultM,
    input [4:0]         WriteRegM,

   
    input [31:0]        PCM,

    
    output reg          RegWriteW,
    output reg          MemToRegW,
    output reg [31:0]   ReadDataW,
    output reg [31:0]   ResultW,
    output reg [4:0]    WriteRegW,
 
    output reg [31:0]   PCW

    );
    
    always @(posedge clk or negedge rst) begin
        if (!rst ) begin
            RegWriteW           <= 1'b0;
            MemToRegW           <= 1'b0;
            ReadDataW           <= 32'b0;
            ResultW             <= 32'b0;
            WriteRegW           <= 5'b0;    
            PCW                 <= 32'b0;
    
        end
        else if (en || 1) begin
            RegWriteW           <= RegWriteM;
            MemToRegW           <= MemToRegM;
            ReadDataW           <= ReadDataM;
            ResultW             <= ResultM;
            WriteRegW           <= WriteRegM;      
            PCW                 <= PCM;
        end
    end 
    
endmodule
