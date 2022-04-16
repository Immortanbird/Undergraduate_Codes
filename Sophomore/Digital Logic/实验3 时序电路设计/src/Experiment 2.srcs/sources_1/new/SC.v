`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/22 14:31:41
// Design Name: 
// Module Name: SC
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


module SC(input clk, X, output reg Z);

reg [0:1] state;
parameter S0 = 2'b00, S1 = 2'b01, S2 = 2'b10, S3 = 2'b11;

initial
begin
    state = 0;
    Z     = 0;
end

always @(posedge clk)
begin
    if (X)
        case (state)
            S0: state = S1;
            S1: state = S2;
            S2: state = S3;
            S3: state = S0;
        endcase
end

always @(posedge clk)
begin
        if (state == S0 && X == 1'b1)
            Z <= 1'b1;
        else
            Z <= 1'b0;
end

endmodule