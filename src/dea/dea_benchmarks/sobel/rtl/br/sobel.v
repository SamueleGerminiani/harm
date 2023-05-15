
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

//Horizontal Gradient
sobel_add_nb #(9) S0 (.a(p2),.b(p0),.ans_out(p2_p0),.subtract(1'b1),.cout()); 		//9-bit Subtractor
sobel_add_nb #(9) S1 (.a(p5),.b(p3),.ans_out(p5_p3),.subtract(1'b1),.cout()); 		//9-bit Subtractor
assign center_1 = `SAC(br0,p5_p3,`MASK_br0) << 1;
sobel_add_nb #(9) S2 (.a(p8),.b(p6),.ans_out(p8_p6),.subtract(1'b1),.cout()); 		//9-bit Subtractor
sobel_add_nb #(9) S3 (.a(`SAC(br1,p2_p0,`MASK_br1)),.b(`SAC(br2,p8_p6,`MASK_br2)),.ans_out(center_rm),.subtract(1'b0),.cout(add_out_1)); 	//9-bit Adder
assign center_2 = {`SAC(br3,add_out_1,`MASK_br3),`SAC(br4,center_rm,`MASK_br4)};
sobel_add_nb #(10) S4 (.a(`SAC(br5,center_1,`MASK_br5)),.b(`SAC(br6,center_2,`MASK_br6)),.ans_out(gx_temp),.subtract(1'b0),.cout(add_out_2)); 	//10-bit Adder
assign gx = {`SAC(br7,add_out_2,`MASK_br7),`SAC(br8,gx_temp,`MASK_br8)};


//Vertical Gradient
sobel_add_nb #(9) S5 (.a(p0),.b(p6),.ans_out(p0_p6),.subtract(1'b1),.cout()); 		//9-bit Subtractor
sobel_add_nb #(9) S6 (.a(p1),.b(p7),.ans_out(p1_p7),.subtract(1'b1),.cout()); 		//9-bit Subtractor
assign center_3 = `SAC(br9,p1_p7,`MASK_br9) << 1;
sobel_add_nb #(9) S7 (.a(p2),.b(p8),.ans_out(p2_p8),.subtract(1'b1),.cout()); 		//9-bit Subtractor
sobel_add_nb #(9) S8 (.a(`SAC(br10,p2_p8,`MASK_br10)),.b(`SAC(br11,p0_p6,`MASK_br11)),.ans_out(center_tm),.subtract(1'b0),.cout(add_out_3));  	//9-bit Adder
assign center_4 = {`SAC(br12,add_out_3,`MASK_br12),`SAC(br13,center_tm,`MASK_br13)};
sobel_add_nb #(10) S9 (.a(`SAC(br14,center_3,`MASK_br14)),.b(`SAC(br15,center_4,`MASK_br15)),.ans_out(gy_temp),.subtract(1'b0),.cout(add_out_4));  //10-bit Adder
assign gy = {`SAC(br16,add_out_4,`MASK_br16),`SAC(br17,gy_temp,`MASK_br17)};


always @(posedge clk)
begin
    gx_reg <= `SAC(br18,gx,`MASK_br18);
    gy_reg <= `SAC(br19,gy,`MASK_br19);
end



not_11b N0 (`SAC(br20,gx_reg,`MASK_br20),gx_comp);
not_11b N1 (`SAC(br21,gy_reg,`MASK_br21),gy_comp);

sobel_add_nb #(11) S10 (.a(11'b1), .b(`SAC(br22,gx_comp,`MASK_br22)), .ans_out(gx_2s_comp), .subtract(1'b0), .cout());	//11-bit Adder
sobel_add_nb #(11) S11 (.a(11'b1), .b(`SAC(br23,gy_comp,`MASK_br23)), .ans_out(gy_2s_comp), .subtract(1'b0), .cout());	//11-bit Adder

mux_11b M0 (`SAC(br24,gx_reg,`MASK_br24), `SAC(br25,gx_2s_comp,`MASK_br25), `SAC(br26,gx_reg[8],`MASK_br26), abs_gx);
mux_11b M1 (`SAC(br27,gy_reg,`MASK_br27), `SAC(br28,gy_2s_comp,`MASK_br28), `SAC(br29,gy_reg[8],`MASK_br29), abs_gy);

sobel_add_nb #(11) S12 (.a(`SAC(br30,abs_gx,`MASK_br30)), .b(`SAC(br31,abs_gy,`MASK_br31)), .ans_out(sum), .subtract(1'b0), .cout());	//11-bit Adder

//or_4b O0 (sum[8], sum[9], sum[10], sum[11], or_out);
mux_8b M2 (`SAC(br32,sum[7:0],`MASK_br32), 8'hff, `SAC(br33,sum[8],`MASK_br33), out);

endmodule
