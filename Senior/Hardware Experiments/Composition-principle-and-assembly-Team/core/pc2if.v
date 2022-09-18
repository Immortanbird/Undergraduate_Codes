`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/07/03 12:38:57
// Design Name: 
// Module Name: pc2if
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


module pc2if(
    input               clk,
    input               rst,
    input               en,
    
    input       [31:0]  PC_next,
    output reg  [31:0]  PCF

    );

    always @(posedge clk or negedge rst) begin
        if (!rst) begin
            PCF <= 32'hbfc00000;    
        end
        else begin
                PCF <= PC_next;
        end
    end 
endmodule
