`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/19 21:13:55
// Design Name: 
// Module Name: imem
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
module imem(
    input               clk,
    input               rst,
    
    output      [31:0]  addr,       //A
    output              wr,         //0
    input       [31:0]  rdata,
    input       [31:0]  A,
    output reg  [31:0]  RD
    );
    
    
    assign wr = 1;
    assign addr = A;

    always @(posedge clk or negedge rst) begin
        if (!rst) begin
            RD <= 32'b0;
        end
        else if (1) begin
            RD <= rdata;
        end
    end
endmodule
