`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/07/11 15:59:13
// Design Name: 
// Module Name: mmu
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


module mmu (
    input               clk,
    input               rst,
    
    input      [31:0]   i_vaddr,        //PCF
    input               i_en,           //TransIAddrF
    output reg [31:0]   i_paddr,        
    input      [31:0]   d_vaddr,        //ALUOutE
    input               d_en,           //TransDAddrE
    output reg [31:0]   d_paddr

    );
    

    function [31:0] memory_mapping(input [31:0] address);
    begin
        case (address[31:29])
            3'b000, 3'b001, 3'b010, 3'b011, 3'b110, 3'b111: begin
                memory_mapping = address;
            end
            3'b100, 3'b101: begin
                memory_mapping = {3'b0, address[28:0]};
            end
        endcase

    end
    endfunction

    always @(*) begin
        if (!rst) begin
            i_paddr <= 32'hbfc00000;
            d_paddr <= 32'h0;
        end
        else begin
            if (i_en || 1) begin
                i_paddr <= memory_mapping(i_vaddr);
            end
            if(d_en || 1) begin    
                d_paddr <= d_vaddr;
            end
        end
    end

endmodule
