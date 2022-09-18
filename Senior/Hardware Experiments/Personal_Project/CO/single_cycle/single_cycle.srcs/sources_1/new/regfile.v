`timescale 1ns / 1ps
`include "head.vh"

module regfile(
    input  wire       clk,
    input  wire       rst,

    input  wire[4:0]  reg_raddr1,
    input  wire[4:0]  reg_raddr2,
    
    input  wire       reg_wen,
    input  wire[4:0]  reg_waddr,
    input  wire[31:0] reg_wdata,
    
    output wire[31:0] reg_rdata1,
    output wire[31:0] reg_rdata2
    );
    reg [31:0] regs[31:0];
    
    assign reg_rdata1 = reg_raddr1 == 0 ? `ZERO : regs[reg_raddr1];
    assign reg_rdata2 = reg_raddr2 == 0 ? `ZERO : regs[reg_raddr2];
    
    integer i;
    always @(posedge clk or negedge rst) begin
        if (!rst) begin
            for (i = 0; i <= 31; i = i + 1) regs[i] <= `ZERO;
        end
        else if (reg_wen == 1'b1 && reg_waddr != 5'b0) regs[reg_waddr] <= reg_wdata;
    end
    
endmodule
