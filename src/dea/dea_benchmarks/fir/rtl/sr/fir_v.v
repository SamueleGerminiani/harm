`timescale 1ns / 1ps
`include "deMacro.v"

module FIR(
    input clk,
    input reset,
    input signed [15:0] s_axis_fir_tdata, 
    input [3:0] s_axis_fir_tkeep,
    input s_axis_fir_tlast,
    input s_axis_fir_tvalid,
    input m_axis_fir_tready,
    output reg m_axis_fir_tvalid,
    output reg s_axis_fir_tready,
    output reg m_axis_fir_tlast,
    output reg [3:0] m_axis_fir_tkeep,
    output reg signed [31:0] m_axis_fir_tdata
    );


    /* This loop controls tkeep signal on AXI Stream interface */
    always @ (posedge clk)
        begin
            `SR(s0 ,m_axis_fir_tkeep <= 4'hf;,m_axis_fir_tkeep <= 0;)
        end
        
    /* This loop controls tlast signal on AXI Stream interface */
    always @ (posedge clk)
        begin
            if (s_axis_fir_tlast == 1'b1)
                begin
                    `SR(s1,m_axis_fir_tlast <= 1'b1;,m_axis_fir_tlast <= 0;)
                end
            else
                begin
                    `SR(s2,m_axis_fir_tlast <= 1'b0;,m_axis_fir_tlast <= 0;)
                end
        end
    
    // 15-tap FIR 
    reg enable_fir;
    reg signed [15:0] buff0, buff1, buff2, buff3, buff4, buff5, buff6, buff7, buff8, buff9, buff10, buff11, buff12, buff13, buff14;
    wire signed [15:0] tap0, tap1, tap2, tap3, tap4, tap5, tap6, tap7, tap8, tap9, tap10, tap11, tap12, tap13, tap14; 
    reg signed [31:0] acc0, acc1, acc2, acc3, acc4, acc5, acc6, acc7, acc8, acc9, acc10, acc11, acc12, acc13, acc14; 

    
    /* Taps for LPF running @ 1MSps */
    `SR(s3,assign tap0 = 16'hFC9C;,assign tap0 =16'h0;)  // twos(-0.0265 * 32768) = 0xFC9C
    `SR(s4,assign tap1 = 16'h0000;,assign tap1=16'h0;)  // 0
    `SR(s5,assign tap2 = 16'h05A5;,assign tap2=16'h0;)  // 0.0441 * 32768 = 1445.0688 = 1445 = 0x05A5
    `SR(s6,assign tap3 = 16'h0000;,assign tap3=16'h0;)  // 0
    `SR(s7,assign tap4 = 16'hF40C;,assign tap4=16'h0;)  // twos(-0.0934 * 32768) = 0xF40C
    `SR(s8,assign tap5 = 16'h0000;,assign tap5=16'h0;)  // 0
    `SR(s9,assign tap6 = 16'h282D;,assign tap6=16'h0;)  // 0.3139 * 32768 = 10285.8752 = 10285 = 0x282D
    `SR(s10,assign tap7 = 16'h4000;,assign tap7=16'h0;)  // 0.5000 * 32768 = 16384 = 0x4000
    `SR(s11,assign tap8 = 16'h282D;,assign tap8=16'h0;)  // 0.3139 * 32768 = 10285.8752 = 10285 = 0x282D
    `SR(s12,assign tap9 = 16'h0000;,assign tap9=16'h0;)  // 0
   `SR(s13,assign tap10 = 16'hF40C;,assign tap10=16'h0;) // twos(-0.0934 * 32768) = 0xF40C
   `SR(s14,assign tap11 = 16'h0000;,assign tap11=16'h0;) // 0
   `SR(s15,assign tap12 = 16'h05A5;,assign tap12=16'h0;) // 0.0441 * 32768 = 1445.0688 = 1445 = 0x05A5
   `SR(s16,assign tap13 = 16'h0000;,assign tap13=16'h0;) // 0
   `SR(s17,assign tap14 = 16'hFC9C;,assign tap14=16'h0;) // twos(-0.0265 * 32768) = 0xFC9C
    
    /* This loop controls tready & tvalid signals on AXI Stream interface */
    always @ (posedge clk)
        begin
            if(reset == 1'b0 || m_axis_fir_tready == 1'b0 || s_axis_fir_tvalid == 1'b0)
                begin
                    `SR(s18,enable_fir <= 1'b0;,enable_fir <= 1'b0;)
                    `SR(s19,s_axis_fir_tready <= 1'b0;,s_axis_fir_tready <= 1'b0;)
                    `SR(s20,m_axis_fir_tvalid <= 1'b0;,m_axis_fir_tvalid <= 1'b0;)
                end
            else
                begin
                    `SR(s21,enable_fir <= 1'b1;,enable_fir <= 1'b0;)
                    `SR(s22,s_axis_fir_tready <= 1'b1;,s_axis_fir_tready <= 1'b0;)
                    `SR(s23,m_axis_fir_tvalid <= 1'b1;,m_axis_fir_tvalid <= 1'b0;)
                end
        end
    
    reg [3:0] cnt;
    reg signed [31:0] acc01, acc012, acc23, acc34, acc45, acc56, acc67, acc78, acc89, acc910, acc1011, acc1112, acc1213;
    
    /* Circular buffer w/ Multiply & Accumulate stages of FIR */
    always @ (posedge clk or posedge reset)
        begin
            if (reset == 1'b0)
                begin
                    `SR(s24,m_axis_fir_tdata <= 32'd0;,m_axis_fir_tdata <= 32'd0;)
                end
            else if (enable_fir == 1'b1)
                begin
                    `SR(s25,buff0 <= s_axis_fir_tdata;,buff0 <= 0;)
                    `SR(s26,acc0 <= tap0 * buff0;,acc0 <= 0;)
                    `SR(s27,buff1 <= buff0;,buff1 <= 0; )
                    `SR(s28,acc1 <= tap1 * buff1;,acc1 <= 0;  )
                    `SR(s29,acc01 <= acc0 + acc1;,acc01 <= 0;)
                    `SR(s30,buff2 <= buff1;,buff2 <= 0; )
                    `SR(s31,acc2 <= tap2 * buff2;,acc2 <= 0;)
                    `SR(s32,acc012 <= acc01 + acc2;,acc012 <= 0;)
                    `SR(s33,buff3 <= buff2;,buff3 <= 0; )
                    `SR(s34,acc3 <= tap3 * buff3;,acc3 <= 0;)
                    `SR(s35,acc23 <= acc012 + acc3;,acc23 <= 0;)
                    `SR(s36,buff4 <= buff3;,buff4 <= 0; )
                    `SR(s37,acc4 <= tap4 * buff4;,acc4 <= 0;)
                    `SR(s38,acc34 <= acc23 + acc4;,acc34 <= 0;)
                    `SR(s39,buff5 <= buff4;,buff5 <= 0;)
                    `SR(s40,acc5 <= tap5 * buff5;,acc5 <= 0; )
                    `SR(s41,acc45 <= acc34 + acc5;,acc45 <= 0;)
                    `SR(s42,buff6 <= buff5;,buff6 <= 0; )
                    `SR(s43,acc6 <= tap6 * buff6;,acc6 <= 0;)
                    `SR(s44,acc56 <= acc45 + acc6;,acc56 <= 0;)
                    `SR(s45,buff7 <= buff6;,buff7 <= 0; )
                    `SR(s46,acc7 <= tap7 * buff7;,acc7 <= 0;)
                    `SR(s47,acc67 <= acc56 + acc7;,acc67 <= 0;)
                    `SR(s48,buff8 <= buff7;,buff8 <= 0;)
                    `SR(s49,acc8 <= tap8 * buff8;,acc8 <= 0;)
                    `SR(s50,acc78 <= acc67 + acc8;,acc78 <= 0;)
                    `SR(s51,buff9 <= buff8;,buff9 <= 0; )
                    `SR(s52,acc9 <= tap9 * buff9;,acc9 <= 0;)
                    `SR(s53,acc89 <= acc78 + acc9;,acc89 <= 0;)
                    `SR(s54,buff10 <= buff9;,buff10 <= 0; )
                    `SR(s55,acc10 <= tap10 * buff10;,acc10 <= 0;)
                    `SR(s56,acc910 <= acc89 + acc10;,acc910 <= 0;)
                    `SR(s57,buff11 <= buff10;,buff11 <= 0; )
                    `SR(s58,acc11 <= tap11 * buff11;,acc11 <= 0;)
                    `SR(s59,acc1011 <= acc910 + acc11;,acc1011 <= 0;)
                    `SR(s60,buff12 <= buff11;,buff12 <= 0; )
                    `SR(s61,acc12 <= tap12 * buff12;,acc12 <= 0;)
                    `SR(s62,acc1112 <= acc1011 + acc12;,acc1112 <= 0;)
                    `SR(s63,buff13 <= buff12;,buff13 <= 0; )
                    `SR(s64,acc13 <= tap13 * buff13;,acc13 <= 0;)
                    `SR(s65,acc1213 <= acc1112 + acc13;,acc1213 <= 0;)
                    `SR(s66,buff14 <= buff13;,buff14 <= 0; )
                    `SR(s67,acc14 <= tap14 * buff14;,acc14 <= 0;)
                    `SR(s68,m_axis_fir_tdata <= acc1213 + acc14;,m_axis_fir_tdata <= 0;)
                end
        end
    
endmodule
