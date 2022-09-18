`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/07/25 06:26:29
// Design Name: 
// Module Name: dmemreq
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


module dmemreq(
    input               clk,
    input               rst,
    input               en,
    
    output reg          wr,
    output reg  [1 :0]  size,
    output reg  [31:0]  addr,
    output reg  [31:0]  wdata,


    input               MemWriteE,
    input               MemToRegE,
    input       [1 :0]  MemWidthE,
    input       [31:0]  PhyAddrE,
    input       [31:0]  WriteDataE,

    output reg          addr_pending
    );

    function [1:0] get_size(input [1:0] width);
    begin
        case (width)
            2'b00: get_size = 2'b00;
            2'b01: get_size = 2'b00;
            2'b10: get_size = 2'b01;
            2'b11: get_size = 2'b10;
        endcase
    end
    endfunction

    function [31:0] get_data(input [31:0] data, input [1:0] offset, input [1:0] width);
    begin
        case (offset)
            2'b00: begin
                case (width)
                    2'b00: get_data = 32'b0;
                    2'b01: get_data = {24'b0, data[7:0]};
                    2'b10: get_data = {16'b0, data[15:0]};
                    2'b11: get_data = data;
                endcase
            end
            2'b01: begin
                case (width)
                    2'b00: get_data = 32'b0;
                    2'b01: get_data = {16'b0, data[7:0], 8'b0};
                    2'b10: get_data = 32'b0;
                    2'b11: get_data = 32'b0;
                endcase
            end
            2'b10: begin
                case (width)
                    2'b00: get_data = 32'b0;
                    2'b01: get_data = {8'b0, data[7:0], 16'b0};
                    2'b10: get_data = {data[15:0], 16'b0};
                    2'b11: get_data = 32'b0;
                endcase
            end
            2'b11: begin
                case (width)
                    2'b00: get_data = 32'b0;
                    2'b01: get_data = {data[7:0], 24'b0};
                    2'b10: get_data = 32'b0;
                    2'b11: get_data = 32'b0;
                endcase
            end
        endcase
    end
    endfunction

    wire [1:0] ra = PhyAddrE[1:0]&&0;

    always @(posedge clk or negedge rst) begin
        if (!rst) begin
            addr_pending <= 0;
            wr <= 0;
            size <= 2'b00;
            addr <= 32'b0;
            wdata <= 32'b0;
        end
        else begin
            if (!rst) begin
                    addr_pending <= 0;
                    wr <= 0;
                    size <= 2'b00;
                    addr <= 32'b0;
                    wdata <= 32'b0;
            end
            else if (en||1) begin
                wr <= MemWriteE;
                size <= get_size(MemWidthE);
                addr <= PhyAddrE;
                wdata <= get_data(WriteDataE, ra, MemWidthE);
            end
        end
    end 

endmodule
