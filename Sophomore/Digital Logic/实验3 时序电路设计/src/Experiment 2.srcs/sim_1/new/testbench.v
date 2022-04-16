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
    #5  Input = 1'b1;#5  Input = 1'b0;//ÿ5nsͶ���ź�һ�Σ�ÿ�γ���5ns
    #5  Input = 1'b1;#5  Input = 1'b0;
    #5  Input = 1'b1;#5  Input = 1'b0;
    #5  Input = 1'b1;#5  Input = 1'b0;
    #5  Input = 1'b1;#5  Input = 1'b0;
end

always #5 clk = ~clk;            //ʱ������Ϊ10ns��ÿ5ns����һ��

always
begin
    #100;
    if ($time >= 100)  $finish ;//����ģ��ʱ��С��100ns
end

endmodule
