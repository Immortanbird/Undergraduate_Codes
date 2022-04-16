`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/13 15:08:05
// Design Name: 
// Module Name: testbench
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


module testbench(
    );
    reg[1:3] T;
    
    initial begin
        T[1] = 1'b0;
        #10 T[1] = 1'b0;
        #10 T[1] = 1'b0;
        #10 T[1] = 1'b0;
        #10 T[1] = 1'b1;
        #10 T[1] = 1'b1;
        #10 T[1] = 1'b1;
        #10 T[1] = 1'b1;
        #10;
    end
    
    initial begin
        T[2] = 1'b0;
        #10 T[2] = 1'b0;
        #10 T[2] = 1'b1;
        #10 T[2] = 1'b1;
        #10 T[2] = 1'b0;
        #10 T[2] = 1'b0;
        #10 T[2] = 1'b1;
        #10 T[2] = 1'b1;
        #10;
    end
    
    initial begin
        T[3] = 1'b0;
        #10 T[3] = 1'b1;
        #10 T[3] = 1'b0;
        #10 T[3] = 1'b1;
        #10 T[3] = 1'b0;
        #10 T[3] = 1'b1;
        #10 T[3] = 1'b0;
        #10 T[3] = 1'b1;
        #10;
    end
    
    wire[1:6] F;
    CLC CLC (T, F);
    
endmodule
