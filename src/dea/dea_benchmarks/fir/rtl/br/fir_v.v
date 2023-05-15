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
            m_axis_fir_tkeep <= `SAC(br97,4'hf,`MASK_br97);
        end
        
    /* This loop controls tlast signal on AXI Stream interface */
    always @ (posedge clk)
        begin
            if (s_axis_fir_tlast == 1'b1)
                begin
                    m_axis_fir_tlast <= `SAC(br98,1'b1,`MASK_br98);
                end
            else
                begin
                    m_axis_fir_tlast <= `SAC(br99,1'b0,`MASK_br99);
                end
        end
    
    // 15-tap FIR 
    reg enable_fir;
    reg signed [15:0] buff0, buff1, buff2, buff3, buff4, buff5, buff6, buff7, buff8, buff9, buff10, buff11, buff12, buff13, buff14;
    wire signed [15:0] tap0, tap1, tap2, tap3, tap4, tap5, tap6, tap7, tap8, tap9, tap10, tap11, tap12, tap13, tap14; 
    reg signed [31:0] acc0, acc1, acc2, acc3, acc4, acc5, acc6, acc7, acc8, acc9, acc10, acc11, acc12, acc13, acc14; 

    
    /* Taps for LPF running @ 1MSps */
    assign tap0 = `SAC(br0,16'hFC9C,`MASK_br0);  // twos(-0.0265 * 32768) = 0xFC9C
    assign tap1 = `SAC(br1,16'h0000,`MASK_br1);  // 0
    assign tap2 = `SAC(br2,16'h05A5,`MASK_br2);  // 0.0441 * 32768 = 1445.0688 = 1445 = 0x05A5
    assign tap3 = `SAC(br3,16'h0000,`MASK_br3);  // 0
    assign tap4 = `SAC(br4,16'hF40C,`MASK_br4);  // twos(-0.0934 * 32768) = 0xF40C
    assign tap5 = `SAC(br5,16'h0000,`MASK_br5);  // 0
    assign tap6 = `SAC(br6,16'h282D,`MASK_br6);  // 0.3139 * 32768 = 10285.8752 = 10285 = 0x282D
    assign tap7 = `SAC(br7,16'h4000,`MASK_br7);  // 0.5000 * 32768 = 16384 = 0x4000
    assign tap8 = `SAC(br8,16'h282D,`MASK_br8);  // 0.3139 * 32768 = 10285.8752 = 10285 = 0x282D
    assign tap9 = `SAC(br9,16'h0000,`MASK_br9);  // 0
    assign tap10 = `SAC(br10,16'hF40C,`MASK_br10); // twos(-0.0934 * 32768) = 0xF40C
    assign tap11 = `SAC(br11,16'h0000,`MASK_br11); // 0
    assign tap12 = `SAC(br12,16'h05A5,`MASK_br12); // 0.0441 * 32768 = 1445.0688 = 1445 = 0x05A5
    assign tap13 = `SAC(br13,16'h0000,`MASK_br13); // 0
    assign tap14 = `SAC(br14,16'hFC9C,`MASK_br14); // twos(-0.0265 * 32768) = 0xFC9C
    
    /* This loop controls tready & tvalid signals on AXI Stream interface */
    always @ (posedge clk)
        begin
            if(reset == 1'b0 || m_axis_fir_tready == 1'b0 || s_axis_fir_tvalid == 1'b0)
                begin
                    enable_fir <= `SAC(br15,1'b0,`MASK_br15);
                    s_axis_fir_tready <= `SAC(br16,1'b0,`MASK_br16);
                    m_axis_fir_tvalid <= `SAC(br17,1'b0,`MASK_br17);
                end
            else
                begin
                    enable_fir <= `SAC(br18,1'b1,`MASK_br18);
                    s_axis_fir_tready <= `SAC(br19,1'b1,`MASK_br19);
                    m_axis_fir_tvalid <= `SAC(br20,1'b1,`MASK_br20);
                end
        end
    
    reg [3:0] cnt;
    reg signed [31:0] acc01, acc012, acc23, acc34, acc45, acc56, acc67, acc78, acc89, acc910, acc1011, acc1112, acc1213;
    
    /* Circular buffer w/ Multiply & Accumulate stages of FIR */
    always @ (posedge clk or posedge reset)
        begin
            if (`SAC(br21,reset,`MASK_br21) == `SAC(br22,1'b0,`MASK_br22))
                begin
                    m_axis_fir_tdata <= `SAC(br23,32'd0,`MASK_br23);
                end
            else if (`SAC(br24,enable_fir,`MASK_br24) == `SAC(br25,1'b1,`MASK_br25))
                begin
                    buff0 <= `SAC(br26,s_axis_fir_tdata,`MASK_br26);
                    acc0 <= `SAC(br27,tap0,`MASK_br27) * `SAC(br28,buff0,`MASK_br28);
                    
                    buff1 <= `SAC(br29,buff0,`MASK_br29); 
                    acc1 <= `SAC(br30,tap1,`MASK_br30) * `SAC(br31,buff1,`MASK_br31);  
                    acc01 <= `SAC(br32,acc0,`MASK_br32) + `SAC(br33,acc1,`MASK_br33);
                         
                    buff2 <= `SAC(br34,buff1,`MASK_br34); 
                    acc2 <= `SAC(br35,tap2,`MASK_br35) * `SAC(br36,buff2,`MASK_br36);
                    acc012 <= `SAC(br37,acc01,`MASK_br37) + `SAC(br38,acc2,`MASK_br38);
                            
                    buff3 <= `SAC(br39,buff2,`MASK_br39); 
                    acc3 <= `SAC(br40,tap3,`MASK_br40) * `SAC(br41,buff3,`MASK_br41);
                    acc23 <= `SAC(br42,acc012,`MASK_br42) + `SAC(br43,acc3,`MASK_br43);
                         
                    buff4 <= `SAC(br44,buff3,`MASK_br44); 
                    acc4 <= `SAC(br45,tap4,`MASK_br45) * `SAC(br46,buff4,`MASK_br46);
                    acc34 <= `SAC(br47,acc23,`MASK_br47) + `SAC(br48,acc4,`MASK_br48);
                         
                    buff5 <= `SAC(br49,buff4,`MASK_br49);
                    acc5 <= `SAC(br50,tap5,`MASK_br50) * `SAC(br51,buff5,`MASK_br51); 
                    acc45 <= `SAC(br52,acc34,`MASK_br52) + `SAC(br53,acc5,`MASK_br53);
                          
                    buff6 <= `SAC(br54,buff5,`MASK_br54); 
                    acc6 <= `SAC(br55,tap6,`MASK_br55) * `SAC(br56,buff6,`MASK_br56);
                    acc56 <= `SAC(br57,acc45,`MASK_br57) + `SAC(br58,acc6,`MASK_br58);
                       
                    buff7 <= `SAC(br59,buff6,`MASK_br59); 
                    acc7 <= `SAC(br60,tap7,`MASK_br60) * `SAC(br61,buff7,`MASK_br61);
                    acc67 <= `SAC(br62,acc56,`MASK_br62) + `SAC(br63,acc7,`MASK_br63);
                          
                    buff8 <= `SAC(br64,buff7,`MASK_br64);
                    acc8 <= `SAC(br65,tap8,`MASK_br65) * `SAC(br66,buff8,`MASK_br66);
                    acc78 <= `SAC(br67,acc67,`MASK_br67) + `SAC(br68,acc8,`MASK_br68);
                           
                    buff9 <= `SAC(br69,buff8,`MASK_br69); 
                    acc9 <= `SAC(br70,tap9,`MASK_br70) * `SAC(br71,buff9,`MASK_br71);
                    acc89 <= acc78 + acc9;
                          
                    buff10 <= `SAC(br72,buff9,`MASK_br72); 
                    acc10 <= `SAC(br73,tap10,`MASK_br73) * `SAC(br74,buff10,`MASK_br74);
                    acc910 <= `SAC(br75,acc89,`MASK_br75) + `SAC(br76,acc10,`MASK_br76);
                           
                    buff11 <= `SAC(br77,buff10,`MASK_br77); 
                    acc11 <= `SAC(br78,tap11,`MASK_br78) * `SAC(br79,buff11,`MASK_br79);
                    acc1011 <= `SAC(br80,acc910,`MASK_br80) + `SAC(br81,acc11,`MASK_br81);
                          
                    buff12 <= `SAC(br82,buff11,`MASK_br82); 
                    acc12 <= `SAC(br83,tap12,`MASK_br83) * `SAC(br84,buff12,`MASK_br84);
                    acc1112 <= `SAC(br85,acc1011,`MASK_br85) + `SAC(br86,acc12,`MASK_br86);
                          
                    buff13 <= `SAC(br87,buff12,`MASK_br87); 
                    acc13 <= `SAC(br88,tap13,`MASK_br88) * `SAC(br89,buff13,`MASK_br89);
                    acc1213 <= `SAC(br90,acc1112,`MASK_br90) + `SAC(br91,acc13,`MASK_br91);
                          
                    buff14 <= `SAC(br92,buff13,`MASK_br92); 
                    acc14 <= `SAC(br93,tap14,`MASK_br93) * `SAC(br94,buff14,`MASK_br94);
                    m_axis_fir_tdata <= `SAC(br95,acc1213,`MASK_br95) + `SAC(br96,acc14,`MASK_br96);
                    
                end
        end
    
endmodule
