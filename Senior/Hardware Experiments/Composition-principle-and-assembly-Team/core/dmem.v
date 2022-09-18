`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/19 21:13:55
// Design Name: 
// Module Name: dmem
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


module dmem(
    input               clk,
    input               rst,
   
    input       [31:0]  rdata,

    input               WE,
    input       [31:0]  A,
    input               SIGN,
    output reg  [31:0]  RD

 
    );
    wire [1:0] ra = A[1:0];

    always @(posedge clk or negedge rst) begin
        if (!rst) begin
            RD <= 32'b0;
        end
        else begin
                if (!WE) begin
                     RD <= rdata;              
                end
        end
    end
    
endmodule