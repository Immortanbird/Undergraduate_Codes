// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
// Date        : Tue Aug 30 10:52:23 2022
// Host        : LAPTOP-DNH7HGSV running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               D:/code/vivado/senior_curriculum/Composition-principle-and-assembly-Team/teach_soc/teach_soc.srcs/sources_1/ip/clk_pll/clk_pll_stub.v
// Design      : clk_pll
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a35tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module clk_pll(soc_clk, clk_vga, clk_in1)
/* synthesis syn_black_box black_box_pad_pin="soc_clk,clk_vga,clk_in1" */;
  output soc_clk;
  output clk_vga;
  input clk_in1;
endmodule
