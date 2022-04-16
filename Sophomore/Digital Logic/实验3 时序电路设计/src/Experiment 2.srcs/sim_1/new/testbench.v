`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/23 18:02:55
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


module testbench();

reg clk, Input;
wire Output;

SC Test(.clk(clk), .X(Input), .Z(Output));

initial
begin
    clk   = 1'b0;
    Input = 1'b0;
    #5  Input = 1'b1;#5  Input = 1'b0;//每5ns投币信号一次，每次持续5ns
    #5  Input = 1'b1;#5  Input = 1'b0;
    #5  Input = 1'b1;#5  Input = 1'b0;
    #5  Input = 1'b1;#5  Input = 1'b0;
    #5  Input = 1'b1;#5  Input = 1'b0;
end

always #5 clk = ~clk;            //时钟周期为10ns，每5ns跳变一次

always
begin
    #100;
    if ($time >= 100)  $finish ;//限制模拟时间小于100ns
end

endmodule
