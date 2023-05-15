//inv_kin.v
//theta1 = acos((x^2+y^2-11^2-12^2)/(2*11*12))
//
//
//theta2  = asin [y(11+12*cos(theta2))-x(12*sin(theta2))/(x^2+y^2)]
//

`timescale 1ns/1ps
`include "deMacro.v"

`define BIT_WIDTH 32
`define FRACTIONS 15
module inv_kin(x, y, theta1, theta2, clock, rst);



	input [`BIT_WIDTH-1:0] x, y;

	output [`BIT_WIDTH-1:0] theta1, theta2;

	input clock;
	input rst;

	wire [`BIT_WIDTH-1:0] xy_sum, cos_theta2_reg, sin_theta2_reg;
 	reg [`BIT_WIDTH-1:0] cos_theta2, sin_theta2;

	reg [`BIT_WIDTH-1:0] cos12, x_sqr, y_sqr, sin12;
	reg [`BIT_WIDTH-1:0]  part_1, part_y, part_x;
	wire [`BIT_WIDTH-1:0] theta2_num, theta1_num, theta2_in,theta1_in;
	wire [`BIT_WIDTH-1:0] x_sqr_reg, y_sqr_reg, part_y_reg, part_x_reg, cos12_reg, sin12_reg, part_1_reg;
	reg [`BIT_WIDTH-2:0] throw_away;
	reg signed_bit;


	wire overflow_flag;
	wire clock;
	reg start, done;
	parameter const_1 = `BIT_WIDTH'b10000000100001001000000000000000;  // -(11^2 + 12^2)
	parameter const_2 = `BIT_WIDTH'b00000000100001000000000000000000;  // 11*12*2


		`SR(s0,qmult #(`FRACTIONS,`BIT_WIDTH) x_multiplier(.i_multiplicand(x), .i_multiplier(x), .o_result(x_sqr_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));,assign x_sqr_reg=0;)
		`SR(s1,qmult #(`FRACTIONS,`BIT_WIDTH) y_multiplier(.i_multiplicand(y), .i_multiplier(y), .o_result(y_sqr_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));,assign y_sqr_reg=0;)
		always @ (posedge clock) begin
			`SR(s2,x_sqr <= x_sqr_reg;, x_sqr <=0;)
			`SR(s3,y_sqr <= y_sqr_reg;, y_sqr <=0;)
			`SR(s4,sin12 <= sin12_reg;, sin12 <=0;)
			`SR(s5,cos12 <= cos12_reg;, cos12 <=0;)
			`SR(s6,part_x<= part_x_reg;,part_x<=0;)
			`SR(s7,part_y<= part_y_reg;,part_y<=0;)
			`SR(s8,part_1<= part_1_reg;,part_1<=0;)
			`SR(s9,sin_theta2 <= sin_theta2_reg;,sin_theta2<=0;)
			`SR(s10,cos_theta2 <= cos_theta2_reg;,cos_theta2<=0;)
		end
		`SR(s11,qadd #(`FRACTIONS,`BIT_WIDTH) xy_adder(.a(x_sqr), .b(y_sqr), .c(xy_sum));,assign xy_sum=0;)
		`SR(s12,qadd #(`FRACTIONS,`BIT_WIDTH) num_adder(.a(const_1), .b(xy_sum), .c(theta2_num));,assign theta2_num=0;)
		`SR(s13,qdiv #(`FRACTIONS,`BIT_WIDTH) my_divider(.i_dividend(theta2_num), .i_divisor(const_2), .i_start(1'b1), .i_clk(clock), .o_quotient_out(theta2_in), .rst(rst), .o_complete(), .o_overflow());,assign theta2_in=0;)

		`SR(s14,acos_lut U0 (theta2_in,theta2);,assign theta2=0;)



		`SR(s15,cos_lut U1 (theta2,cos_theta2_reg);,assign cos_theta2_reg=0;)
		`SR(s16,sin_lut U2 (theta2,sin_theta2_reg);,assign sin_theta2_reg=0;)
		`SR(s17,qmult #(`FRACTIONS,`BIT_WIDTH) cos_multiplier(.i_multiplicand(cos_theta2), .i_multiplier(`BIT_WIDTH'b00000000000001100000000000000000), .o_result(cos12_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));		,assign cos12_reg=0;)
		`SR(s18,qmult #(`FRACTIONS,`BIT_WIDTH) sin_multiplier(.i_multiplicand(sin_theta2), .i_multiplier(`BIT_WIDTH'b00000000000001100000000000000000), .o_result(sin12_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));,assign sin12_reg=0;)
		`SR(s19,qadd #(`FRACTIONS,`BIT_WIDTH) n_adder(.a(cos12), .b(`BIT_WIDTH'b00000000000001011000000000000000), .c(part_1_reg));,assign part_1_reg=0;)
		`SR(s20,qmult #(`FRACTIONS,`BIT_WIDTH) multiplier_1(.i_multiplicand(part_1), .i_multiplier(y), .o_result(part_y_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));,assign part_y_reg=0;)
		`SR(s21,qmult #(`FRACTIONS,`BIT_WIDTH) multiplier_2(.i_multiplicand(sin12), .i_multiplier(x), .o_result(part_x_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));,assign part_x_reg=0;)

	always@(part_x) begin
		if (part_x[31]) begin
			`SR(s22,signed_bit=1'b0;,signed_bit=0;)
		end
		else begin
			`SR(s23,signed_bit=1'b1;,signed_bit=0;)
		end
	end
		`SR(s24,qadd #(`FRACTIONS,`BIT_WIDTH) adder_123 (.a({signed_bit,part_x[30:0]}), .b(part_y), .c(theta1_num));,assign theta1_num=0;)
		`SR(s25,qdiv #(`FRACTIONS,`BIT_WIDTH) m_divider(.i_dividend(theta1_num), .i_divisor(xy_sum), .i_start(1'b1), .i_clk(clock), .rst(rst), .o_quotient_out(theta1_in), .o_complete(), .o_overflow());,assign theta1_in=0;)
		`SR(s26,asin_lut U3 (theta1_in,theta1);,assign theta1=0;)
endmodule

