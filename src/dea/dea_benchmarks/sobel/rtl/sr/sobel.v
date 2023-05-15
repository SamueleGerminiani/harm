`include "deMacro.v"

module sobel( clk, p0, p1, p2, p3, p5, p6, p7, p8, out);

input  [8:0] p0,p1,p2,p3,p5,p6,p7,p8;	
input clk;

output [7:0] out;					

wire [8:0] p2_p0, p8_p6, p0_p6, p2_p8, p5_p3, p1_p7, center_rm, center_tm;
wire [9:0] center_1, center_2, center_3, center_4, gx_temp, gy_temp;

wire or_out, add_out_1, add_out_2, add_out_3, add_out_4;
wire [10:0] gx , gy, gx_comp, gy_comp;
wire [10:0] gx_2s_comp, gy_2s_comp;   

wire [10:0] abs_gx,abs_gy;	
wire [10:0] sum;


reg [10:0] gx_reg, gy_reg;		

`SR(s0,
    sobel_add_nb #(9) S0 (.a(p2),.b(p0),.ans_out(p2_p0),.subtract(1'b1),.cout());,
    assign p2_p0='b0;)

    `SR(s1,sobel_add_nb #(9) S1 (.a(p5),.b(p3),.ans_out(p5_p3),.subtract(1'b1),.cout());,assign p5_p3='b0;) 	
    `SR(s2,assign center_1 = p5_p3 << 1;,assign center_1='b0;)
    `SR(s3,sobel_add_nb #(9) S2 (.a(p8),.b(p6),.ans_out(p8_p6),.subtract(1'b1),.cout());,assign p8_p6='b0;assign p8_p6='b0;) 
    `SR(s4,sobel_add_nb #(9) S3 (.a(p2_p0),.b(p8_p6),.ans_out(center_rm),.subtract(1'b0),.cout(add_out_1));,assign center_rm='b0;assign add_out_1='b0;) 
    `SR(s5,assign center_2 = {add_out_1,center_rm};,assign center_2='b0;)
    `SR(s6,sobel_add_nb #(10) S4 (.a(center_1),.b(center_2),.ans_out(gx_temp),.subtract(1'b0),.cout(add_out_2));,assign gx_temp='b0;assign add_out_2='b0;)
    `SR(s7,assign gx = {add_out_2,gx_temp};,assign gx='b0;)


    `SR(s8,	sobel_add_nb #(9) S5 (.a(p0),.b(p6),.ans_out(p0_p6),.subtract(1'b1),.cout());,assign p0_p6='b0;)
    `SR(s9,sobel_add_nb #(9) S6 (.a(p1),.b(p7),.ans_out(p1_p7),.subtract(1'b1),.cout());,assign p1_p7='b0;)
    `SR(s10,assign center_3 = p1_p7 << 1;,assign center_3='b0 ;)
    `SR(s11,sobel_add_nb #(9) S7 (.a(p2),.b(p8),.ans_out(p2_p8),.subtract(1'b1),.cout());,assign p2_p8='b0;)
    `SR(s12,sobel_add_nb #(9) S8 (.a(p2_p8),.b(p0_p6),.ans_out(center_tm),.subtract(1'b0),.cout(add_out_3));,assign center_tm='b0;assign add_out_3=0;)
    `SR(s13,assign center_4 = {add_out_3,center_tm};,assign center_4='b0;)
    `SR(s14,sobel_add_nb #(10) S9 (.a(center_3),.b(center_4),.ans_out(gy_temp),.subtract(1'b0),.cout(add_out_4));,assign gy_temp='b0;assign add_out_4='b0;)
    `SR(s15,assign gy = {add_out_4,gy_temp};,assign gy='b0;)


    always @(posedge clk)
    begin
        `SR(s16,	gx_reg <= gx;,gx_reg<='b0;)
        `SR(s17,gy_reg <= gy;,gy_reg<='b0;)
    end


    `SR(s18,not_11b N0 (gx_reg,gx_comp);,assign gx_comp='b0;)
    `SR(s19,not_11b N1 (gy_reg,gy_comp);,assign gy_comp='b0;)

    `SR(s20,sobel_add_nb #(11) S10 (.a(11'b1), .b(gx_comp), .ans_out(gx_2s_comp), .subtract(1'b0), .cout());,assign gx_2s_comp='b0	;)
    `SR(s21,sobel_add_nb #(11) S11 (.a(11'b1), .b(gy_comp), .ans_out(gy_2s_comp), .subtract(1'b0), .cout());,assign gy_2s_comp='b0;)
    `SR(s22,mux_11b M0 (gx_reg, gx_2s_comp, gx_reg[8], abs_gx);,assign abs_gx='b0;)
    `SR(s23,mux_11b M1 (gy_reg, gy_2s_comp, gy_reg[8], abs_gy);,assign abs_gy='b0;)
    `SR(s24,sobel_add_nb #(11) S12 (.a(abs_gx), .b(abs_gy), .ans_out(sum), .subtract(1'b0), .cout());,assign sum='b0;)
    `SR(s25,mux_8b M2 (sum[7:0], 8'hff, sum[8], out);,assign out='b0 ;)

    endmodule
