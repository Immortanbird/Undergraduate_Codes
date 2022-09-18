`timescale 1ns / 1ps


module mycpu_top(
	input         resetn,			
    input         clk,				

	output        inst_sram_en,		
	output [3 :0] inst_sram_wen,	
    output [31:0] inst_sram_addr,	
    output [31:0] inst_sram_wdata,
    input  [31:0] inst_sram_rdata,  

	output        data_sram_en,		
	output [3 :0] data_sram_wen,	
    output [31:0] data_sram_addr,	
    output [31:0] data_sram_wdata,
    input  [31:0] data_sram_rdata, 
	
	output [31:0] debug_wb_pc,		
	output [3 :0] debug_wb_rf_wen,	
    output [4 :0] debug_wb_rf_wnum,
    output [31:0] debug_wb_rf_wdata 
	

);
    function [31:0] sel_2to4(input [1:0] sel,
                             input [31:0] in0, input [31:0] in1,
                             input [31:0] in2, input [31:0] in3);
    begin
        case (sel)
            2'b00 : sel_2to4 = in0;
            2'b01 : sel_2to4 = in1;
            2'b10 : sel_2to4 = in2;
            2'b11 : sel_2to4 = in3;
        endcase
    end
    endfunction

// ---------- END OF Functions ----------

    
// ---------- Wires ----------

// PC2IF Buffer
    // input
    wire [31:0]     PC_next;
    wire            InstUnalignedF;
    wire [31:0]     ReturnPCW;
    // output
    (*mark_debug = "true"*)wire [31:0]     PCF;




// IF(F): Instruction Fetch
    // imem input
    wire [31:0]     PhyAddrF;
    //wire            InstUnalignedF;
    // imem output
    wire [31:0]     ReadDataF;
    

// IF2ID Buffer
    // input
    wire [31:0]     PCPlus4F;




    // output
    wire [31:0]     InstrD;
    wire [31:0]     PCPlus4D;

    wire [31:0]     PCD;



// ID(D): Instruction Decode
    // cu decode input
    //wire [31:0]     InstrD;
    // cu decode output
    wire            RegWriteD;
    wire            MemToRegD;
    wire            MemWriteD;
    wire [4:0]      ALUCtrlD;
    wire [1:0]      ALUSrcD;
    wire [1:0]      RegDstD;
    wire [5:0]      BranchD;
    wire            JumpD;
    wire            JRD;


    wire            LoadUnsignedD;
    wire [1:0]      MemWidthD;
    wire            ImmUnsignedD;


    wire            SysCallD;
    wire            EretD;
    // branch input
    wire [31:0]     BranchRsD;
    wire [31:0]     BranchRtD;
    //wire            BranchD;
    wire            CanBranchD;
    // branch output
    wire            BranchExeD;
    // regfile input
    wire [4:0]      A1D;
    wire [4:0]      A2D;
    wire [4:0]      WriteRegW;
    wire            RegWriteW;
    wire [31:0]     ResultW;
    // regfile output
    wire [31:0]     RD1D;
    wire [31:0]     RD2D;
    // next pc selector
    wire [1:0]      PCSrcD;
    wire [31:0]     PCBranchD;
    wire [31:0]     PCJumpD;


// ID2EX Buffer
    // input

    //wire            RegWriteD;
    //wire            MemToRegD;
    //wire            MemWriteD;
    //wire [4:0]      ALUCtrlD;
    //wire [1:0]      ALUSrcD;
    //wire [1:0]      RegDstD;
    //wire [31:0]     RD1D;
    //wire [31:0]     RD2D;
    wire [4:0]      RsD;
    wire [4:0]      RtD;
    wire [4:0]      RdD;
    wire [31:0]     ImmD;
    //wire            LinkD;
    //wire [31:0]     PCPlus8D;
    //wire [1:0]      HiLoWriteD;
    //wire [1:0]      HiLoToRegD;
    //wire            LoadUnsignedD;
    wire [1:0]      MemWidthD;
    //wire            CP0WriteD;
    //wire            CP0ToRegD;
    wire [4:0]      WriteCP0AddrD;
    wire [2:0]      WriteCP0SelD;
    wire [4:0]      ReadCP0AddrD;
    wire [2:0]      ReadCP0SelD;
    //wire [31:0]     PCD;
    //wire            InDelaySlotD;
    wire [31:0]     ExceptionTypeD;
    // output
    wire            RegWriteE;
    wire            MemToRegE;
    wire            MemWriteE;
    wire [4:0]      ALUCtrlE;
    wire [1:0]      ALUSrcE;
    wire [1:0]      RegDstE;
    wire [31:0]     RD1E;
    wire [31:0]     RD2E;
    wire [4:0]      RsE;
    wire [4:0]      RtE;
    wire [4:0]      RdE;
    wire [31:0]     ImmE;
    wire            LinkE;
    wire [31:0]     PCPlus8E;
    wire [1:0]      HiLoWriteE;
    wire [1:0]      HiLoToRegE;
    wire            LoadUnsignedE;
    wire [1:0]      MemWidthE;
    wire            CP0WriteE;
    wire            CP0ToRegE_in;
    wire [4:0]      WriteCP0AddrE;
    wire [2:0]      WriteCP0SelE;
    wire [4:0]      ReadCP0AddrE;
    wire [2:0]      ReadCP0SelE;
    (*mark_debug = "true"*)wire [31:0]     PCE;
    wire            InDelaySlotE;
    wire [31:0]     ExceptionTypeE_in;


// EX(E): Execute
    // alu input
    //wire [4:0]      ALUCtrlE;
    (*mark_debug = "true"*)wire [31:0]     SrcAE;
    (*mark_debug = "true"*)wire [31:0]     SrcBE;
    

    
    // alu output
    wire [31:0]     ALUOutE;
    wire            OverflowE;
    // muldiv input
    //wire [4:0]      ALUCtrlE;
    //wire [31:0]     SrcAE;
    //wire [31:0]     SrcBE;
    wire            DivPendingE;
    wire            CanMulDivE;
    // muldiv output
    // dmemreq input
    //wire            MemToRegE;
    //wire            MemWriteE;
    //wire [1:0]      MemWidthE;
    wire [31:0]     BadVAddrE;
    wire [31:0]     PhyAddrE;
    wire [31:0]     WriteDataE;
    wire            MemAccessE;
    // dmemreq output
    wire            AddrPendingE;


// EX2MEM Buffer
    // input
    wire            FlushM;
    wire            StallM;
    //wire            RegWriteE;
    //wire            MemToRegE;
    //wire            MemWriteE;
    //wire [31:0]     ALUOutE;
    //wire [31:0]     WriteDataE;
    wire [4:0]      WriteRegE;
    //wire            LinkE;
    //wire [31:0]     PCPlus8E;
    //wire            LoadUnsignedE;
    //wire [1:0]      MemWidthE;
    //wire [31:0]     PhyAddrE;
    //wire [1:0]      HiLoWriteE;
    //wire [1:0]      HiLoToRegE;
    wire [31:0]     HiInE;
    wire [31:0]     LoInE;
    (*mark_debug = "true"*)wire [31:0]     HiLoOutE;
    //wire            CP0WriteE;
    wire            CP0ToRegE;
    //wire [4:0]      WriteCP0AddrE;
    //wire [2:0]      WriteCP0SelE,
    wire [31:0]     WriteCP0HiLoDataE;
    wire [31:0]     ReadCP0DataE;
    //wire [31:0]     PCE;
    //wire            InDelaySlotE;
    wire [31:0]     ExceptionTypeE;
    // output
    wire            RegWriteM;
    wire            MemToRegM;
    wire            MemWriteM;
    wire [31:0]     ALUOutM;
    wire [31:0]     WriteDataM;
    wire [4:0]      WriteRegM;
    wire            LinkM;
    wire [31:0]     PCPlus8M;
    wire            LoadUnsignedM;
    wire [1:0]      MemWidthM;
    wire [31:0]     PhyAddrM;
    wire [1:0]      HiLoWriteM;
    wire [1:0]      HiLoToRegM;
    wire [31:0]     HiInM;
    wire [31:0]     LoInM;
    wire [31:0]     HiLoOutM;
    wire            CP0WriteM;
    wire            CP0ToRegM;
    wire [4:0]      WriteCP0AddrM;
    wire [2:0]      WriteCP0SelM;
    wire [31:0]     WriteCP0HiLoDataM;
    wire [31:0]     ReadCP0DataM;
    (*mark_debug = "true"*)wire [31:0]     PCM;
    wire            InDelaySlotM;
    wire [31:0]     BadVAddrM;
    wire [31:0]     ExceptionTypeM_in;


// MEM(M): Memory Access
    // dmem input
    //wire            MemWriteM;
    //wire [31:0]     PhyAddrM;
    //wire [31:0]     WriteDataM;
    //wire [31:0]     MemWidthM;
    //wire            LoadUnsignedM;
    // dmem output
    wire [31:0]     ReadDataM;
    wire            DataPendingM;


// MEM2WB Buffer
    // input
    wire            FlushW;
    wire            StallW;
    //wire            RegWriteM;
    //wire            MemToRegM;
    //wire [31:0]     ReadDataM;
    wire [31:0]     ResultM;
    //wire [4:0]      WriteRegM;
    //wire [1:0]      HiLoWriteM;
    //wire [31:0]     HiInM;
    //wire [31:0]     LoInM;
    //wire            CP0WriteM;
    //wire [4:0]      WriteCP0AddrM;
    //wire [2:0]      WriteCP0SelM;
    //wire [31:0]     WriteCP0HiLoDataM;
    //wire [31:0]     PCM;
    //wire            InDelaySlotM;
    //wire [31:0]     BadVAddrM;
    wire [31:0]     ExceptionTypeM;
    // output
    wire            RegWriteW_in;
    wire            MemToRegW;
    wire [31:0]     ReadDataW;
    wire [31:0]     ResultW_in;
    //wire [4:0]      WriteRegW;
    wire [1:0]      HiLoWriteW_in;
    //wire [31:0]     HiInW;
    //wire [31:0]     LoInW;
    wire            CP0WriteW_in;
    wire [4:0]      WriteCP0AddrW;
    wire [2:0]      WriteCP0SelW;
    wire [31:0]     WriteCP0HiLoDataW;
    (*mark_debug = "true"*)wire [31:0]     PCW;
    wire            InDelaySlotW;
    wire [31:0]     BadVAddrW;
    wire [31:0]     ExceptionTypeW_in;


// WB(W): Registers Write Back
    // no wire


// mmu input
    //wire [31:0]     PCF;
    //wire [31:0]     ALUOutE;
    //wire [1:0]      MemWidthE;
    //wire            StallF;
    //wire [31:0]     ALUOutE;

// mmu output
    //wire [31:0]     PhyAddrF;
    //wire [31:0]     PhyAddrE;
    //wire            InstUnalignedF;
    wire            DataUnalignedE;
    
// cp0 input
    //wire            CP0ToRegE;
    //wire [4:0]      ReadCP0AddrE;
    //wire [2:0]      ReadCP0SelE;
    wire            CP0WriteW;
    //wire [4:0]      WriteCP0AddrW;
    //wire [2:0]      WriteCP0SelW;
    //wire [31:0]     WriteCP0HiLoDataW;
    //wire [31:0]     PCW;
    //wire [31:0]     BadVAddrW;
    wire [31:0]     ExceptionTypeW;
    //wire            InDelaySlotW;
    
// cp0 output
    //wire [31:0]     ReadCP0DataE;
    //wire [31:0]     ReturnPCW;
    //wire            ExceptionW;

// cfu input
    //wire            BranchD;
    //wire            JumpD;
    //wire            CanBranchD;
    //wire            AddrPendingF;
    //wire            DataPendingF;
    //wire            DivPendingE;
    //wire            AddrPendingE;
    //wire            DataPendingM;
    //wire            InExceptionF;
    //wire [4:0]      RsD;
    //wire [4:0]      RtD;
    //wire [4:0]      RsE;
    //wire [4:0]      RtE;
    //wire [4:0]      WriteRegE;
    //wire            MemToRegE;
    //wire            RegWriteE;
    //wire [1:0]      HiLoToRegE;
    //wire            CP0ToRegE;
    //wire [4:0]      WriteRegM;
    //wire            MemToRegM;
    //wire            RegWriteM;
    //wire [1:0]      HiLoWriteM;
    //wire            CP0WriteM;
    //wire [4:0]      WriteRegW;
    //wire            RegWriteW;
    //wire [1:0]      HiLoWriteM;
    //wire            CP0WriteW;

// cfu output
    //wire            StallF;
    //wire            StallD;
    //wire            StallM;
    //wire            StallE;
    //wire            StallW;
    //wire            FlushD;
    //wire            FlushE;
    //wire            FlushM;
    //wire            FlushW;
    wire            ForwardAD;
    wire            ForwardBD;
    wire [1:0]      ForwardAE;
    wire [1:0]      ForwardBE;
    wire [1:0]      ForwardHE;


// ---------- END OF Wires ----------


// ---------- PC ----------
    assign PC_next = sel_2to4(PCSrcD, PCPlus4F, PCBranchD, PCJumpD, 32'b0);
   // assign PC_next = sel_2to4(2'b00, PCPlus4F, PCBranchD, PCJumpD, 32'b0);
    pc2if _pc2if(
        .clk(clk), .rst(resetn),
        // sram-like
//        .addr_ok        (inst_addr_ok),
//        .data_ok        (inst_data_ok),
        //input
        .en             (StallF),
        .PC_next        (PC_next),



        //output
        .PCF            (PCF)
//        .addr_pending   (AddrPendingF),
//        .data_pending   (DataPendingF)
    );

// ---------- IF ----------

    imem _imem(
        .clk(clk), .rst(resetn),
        // sram-like
        .wr             (inst_sram_en     ),
        .addr           (inst_sram_addr   ),
        .rdata          (inst_sram_rdata  ),
        .A              (PhyAddrF),
        .RD             (ReadDataF)
    );

    assign PCPlus4F = PCF + 4;
    assign PCPlus8F = PCF + 8;

    if2id _if2id(
        .clk(clk), .rst(resetn),
        // input

        .ReadDataF          (inst_sram_rdata),
        .PCPlus4F           (PCPlus4F),
        .PCF                (PCF),
    
        // output
        .InstrD             (InstrD),
        .PCPlus4D           (PCPlus4D),
        .PCD                (PCD)
    );

// ---------- ID ----------
    cu _cu(
        .rst(resetn),
        // input
        .instr             (InstrD),
        // output
        .RegWriteD          (RegWriteD),
        .MemToRegD          (MemToRegD),
        .MemWriteD          (MemWriteD),
        .ALUCtrlD           (ALUCtrlD),
        .ALUSrcD            (ALUSrcD),
        .RegDstD            (RegDstD),
        .BranchD            (BranchD),
        .JumpD              (JumpD),
        .MemWidthD          (MemWidthD),
         .ImmUnsigned        (ImmUnsignedD),
        .JRD                (JRD)
    );

    assign NextDelaySlotD = JumpD || BranchD;
    assign CanBranchD = 1;

    assign BranchRsD = RD1D;
    assign BranchRtD = RD2D;
br _br(
        .clk(clk), .rst(resetn),
        // input
        .en             (CanBranchD),
        .rs             (BranchRsD),
        .rt             (BranchRtD),
        .branch         (BranchD),
        // output
        .exe            (BranchExeD)
    );


    assign A1D = InstrD[25:21];
    assign A2D = InstrD[20:16];
   
 

//    reg [1:0] PCSrcD_r;
    reg [31:0] PCBranchD_r;
    reg [31:0] PCJumpD_r;
//    assign PCSrcD = PCSrcD_r;
    assign PCBranchD = PCBranchD_r;
    assign PCJumpD = PCJumpD_r;
    always @(negedge clk or negedge resetn) begin
        if (!resetn) begin
//            PCSrcD_r <= 2'b0;
            PCBranchD_r <= 32'b0;
            PCJumpD_r <= 32'b0;
        end
        else begin
            PCBranchD_r <= {{14{InstrD[15]}}, InstrD[15:0], 2'b0} + PCPlus4D;
            PCJumpD_r <= JRD ? RD1D : {PCPlus4D[31:28], InstrD[25:0], 2'b0};
        end
    end
    assign PCSrcD = {JumpD, BranchExeD};

    assign RsD = InstrD[25:21];
    assign RtD = InstrD[20:16];
    assign RdD = InstrD[15:11];
    assign ImmD = ImmUnsignedD ? {16'b0, InstrD[15:0]} : {{16{InstrD[15]}}, InstrD[15:0]};


    id2ex _id2ex(
        .clk(clk), .rst(resetn),
        // input
        .RegWriteD          (RegWriteD),
        .MemToRegD          (MemToRegD),
        .MemWriteD          (MemWriteD),
        .ALUCtrlD           (ALUCtrlD),
        .ALUSrcD            (ALUSrcD),
        .RegDstD            (RegDstD),
        .RD1D               (RD1D),
        .RD2D               (RD2D),
        .RsD                (RsD),
        .RtD                (RtD),
        .RdD                (RdD),
        .ImmD               (ImmD),
        .MemWidthD          (MemWidthD),

        .PCD                (PCD),

        // output
        .RegWriteE          (RegWriteE),
        .MemToRegE          (MemToRegE),
        .MemWriteE          (MemWriteE),
        .ALUCtrlE           (ALUCtrlE),
        .ALUSrcE            (ALUSrcE),
        .RegDstE            (RegDstE),
        .RD1E               (RD1E),
        .RD2E               (RD2E),
        .RsE                (RsE),
        .RtE                (RtE),
        .RdE                (RdE),
        .ImmE               (ImmE),
        .MemWidthE          (MemWidthE),
        .PCE                (PCE)
    );

// ---------- EX ----------
    wire [31:0] RD1ForwardE = sel_2to4(2'b00, RD1E, ResultW, ResultM, 32'b0);
    wire [31:0] RD2ForwardE = sel_2to4(2'b00, RD2E, ResultW, ResultM, 32'b0);
    assign WriteRegE = sel_2to4(RegDstE, RtE, RdE, 5'b11111, 5'b00000);
    assign WriteDataE = RD2ForwardE;
    
    assign SrcAE = ALUSrcE[1] ? {27'b0, ImmE[10:6]} : RD1ForwardE;
    assign SrcBE = ALUSrcE[0] ? ImmE : WriteDataE;


    alu _alu(
        .rst(resetn),
        // input
        .ctrl           (ALUCtrlE),
        .in1            (SrcAE),
        .in2            (SrcBE),
        // output
        .result         (ALUOutE),
        .overflow       (OverflowE)
    );
    //assign CanMulDivE = ExceptionTypeE_in || ExceptionTypeM_in || ExceptionTypeW_in ? 0 : 1;

    ex2mem _ex2mem(
        .clk(clk), .rst(resetn),
        // input

        .en                 (StallM),
        .RegWriteE          (RegWriteE),
        .MemToRegE          (MemToRegE),
        .MemWriteE          (MemWriteE),
        .ALUOutE            (ALUOutE),
        .WriteDataE         (WriteDataE),
        .WriteRegE          (WriteRegE),
//        .LoadUnsignedE      (LoadUnsignedE),
        .MemWidthE          (MemWidthE),
        .PhyAddrE           (PhyAddrE),
 
        .PCE                (PCE),
   //     .InDelaySlotE       (InDelaySlotE),
   
    
        // output
        .RegWriteM          (RegWriteM),
        .MemToRegM          (MemToRegM),
        .MemWriteM          (MemWriteM),
        .ALUOutM            (ALUOutM),
        .WriteDataM         (WriteDataM),
        .WriteRegM          (WriteRegM),
    
        .CP0ToRegM          (CP0ToRegM),
    

        .PCM                (PCM)
      //  .InDelaySlotM       (InDelaySlotM),
    
    );

// ---------- MEM ----------

    assign ResultM =   ALUOutM;
    
    wire SignedM = ~LoadUnsignedM;
    
    dmem _dmem(
        .clk(clk), .rst(resetn),
        // sram-like
        .rdata          (data_sram_rdata  ),
        // input
        .WE             (MemWriteM),
        .A              (PhyAddrM),
        //.WD             (WriteDataM),
        // output
        .RD             (ReadDataM)
    );

    dmemreq _dmemreq(
        .clk(clk), .rst(resetn),
        // sram-like
        .wr             (data_sram_en     ),
        .size           (data_size   ),
        .addr           (data_sram_addr ),
        .wdata          (data_sram_wdata),
        // input
        .en             (MemAccessE),
        .MemWriteE      (MemWriteE),
        .MemToRegE      (MemToRegE),
        .MemWidthE      (MemWidthE),
        .PhyAddrE       (PhyAddrE),
        .WriteDataE     (WriteDataE),
        // output
        .addr_pending   (AddrPendingE)
    );


    mem2wb _mem2wb(
        .clk(clk), .rst(resetn),
        // input

        .en                 (StallW),
        .RegWriteM          (RegWriteM),
        .MemToRegM          (MemToRegM),
        .ReadDataM          (ReadDataM),
        .ResultM            (ResultM),
        .WriteRegM          (WriteRegM),
        .PCM                (PCM),
 
        // output
        .RegWriteW          (RegWriteW_in),
        .MemToRegW          (MemToRegW),
        .ReadDataW          (ReadDataW),
        .ResultW            (ResultW_in),
        .WriteRegW          (WriteRegW),
    
        .PCW                (PCW)
  
   
    );

// ---------- WB ----------

    assign ResultW = MemToRegW ? ReadDataW : ResultW_in;
    assign RegWriteW =  RegWriteW_in;





// ---------- OTHER ----------
    
    
    // ---------- OTHER ----------
    

//    wire TransIAddrF = StallF;
//    wire TransDAddrE = (ExceptionTypeE_in || ExceptionTypeM_in || ExceptionTypeW_in) ? 0 
//                      : StallE && (MemWriteE || MemToRegE);
//    wire ClearDAddrE = 0;//ExceptionTypeE ? 1 : 0;
    mmu _mmu(
        .clk(clk), .rst(resetn),
        // input
        .i_vaddr        (PCF),
        .i_en           (TransIAddrF),
        .d_vaddr        (ALUOutE),
//        .d_width        (MemWidthE),
        .d_en           (TransDAddrE),
//        .d_clr          (ClearDAddrE),
        // output
        .i_paddr        (PhyAddrF),
//        .i_unaligned    (InstUnalignedF),
        .d_paddr        (PhyAddrE)
//        .d_unaligned    (DataUnalignedE)
    );
    
    
    


       regfile _regfile(
        .clk(clk), .rst(resetn),
        // input
        .A1             (A1D),
        .A2             (A2D),
        .A3             (WriteRegW),
        .WD3            (ResultW),
        .WE3            (RegWriteW),
        // output
        .RD1            (RD1D),
        .RD2            (RD2D)
    );
endmodule
