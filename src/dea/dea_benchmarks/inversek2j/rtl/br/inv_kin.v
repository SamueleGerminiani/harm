//inv_kin.v
//theta1 = acos((x^2+y^2-11^2-12^2)/(2*11*12))
//
//
//theta2  = asin [y(11+12*cos(theta2))-x(12*sin(theta2))/(x^2+y^2)]
//
//
`include "deMacro.v"


`timescale 1ns/1ps

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

	wire _overflow_flag;
	wire _start, _done;

    assign _overflow_flag = `SAC(br25,overflow_flag,`MASK_br25);
    assign _start = `SAC(br26,start,`MASK_br26);
    assign _done = `SAC(br27,done,`MASK_br27);



	parameter const_1 = `BIT_WIDTH'b10000000100001001000000000000000;  // -(11^2 + 12^2)
	parameter const_2 = `BIT_WIDTH'b00000000100001000000000000000000;  // 11*12*2

		qmult #(`FRACTIONS,`BIT_WIDTH) x_multiplier(.i_multiplicand(x), .i_multiplier(x), .o_result(x_sqr_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));
		qmult #(`FRACTIONS,`BIT_WIDTH) y_multiplier(.i_multiplicand(y), .i_multiplier(y), .o_result(y_sqr_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));
		always @ (posedge clock) begin
			x_sqr <= `SAC(br0,x_sqr_reg,`MASK_br0);
			y_sqr <= `SAC(br1,y_sqr_reg,`MASK_br1);
			sin12 <= `SAC(br2,sin12_reg,`MASK_br2);
			cos12 <= `SAC(br3,cos12_reg,`MASK_br3);
			part_x<= `SAC(br4,part_x_reg,`MASK_br4);
			part_y<= `SAC(br5,part_y_reg,`MASK_br5);
			part_1<= `SAC(br6,part_1_reg,`MASK_br6);
			sin_theta2 <= `SAC(br7,sin_theta2_reg,`MASK_br7);
			cos_theta2 <= `SAC(br8,cos_theta2_reg,`MASK_br8);
		end
		qadd #(`FRACTIONS,`BIT_WIDTH) xy_adder(.a(`SAC(br9,x_sqr,`MASK_br9)), .b(`SAC(br10,y_sqr,`MASK_br10)), .c(xy_sum));
		qadd #(`FRACTIONS,`BIT_WIDTH) num_adder(.a(const_1), .b(`SAC(br11,xy_sum,`MASK_br11)), .c(theta2_num));
		qdiv #(`FRACTIONS,`BIT_WIDTH) my_divider(.i_dividend(`SAC(br12,theta2_num,`MASK_br12)), .i_divisor(const_2), .i_start(1'b1), .i_clk(clock), .o_quotient_out(theta2_in), .rst(rst), 
		.o_complete(), .o_overflow());

		acos_lut U0 (`SAC(br13,theta2_in,`MASK_br13),theta2);



		cos_lut U1 (theta2,cos_theta2_reg);
		sin_lut U2 (theta2,sin_theta2_reg);
		qmult #(`FRACTIONS,`BIT_WIDTH) cos_multiplier(.i_multiplicand(`SAC(br14,cos_theta2,`MASK_br14)), .i_multiplier(`BIT_WIDTH'b00000000000001100000000000000000), .o_result(cos12_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));		
		qmult #(`FRACTIONS,`BIT_WIDTH) sin_multiplier(.i_multiplicand(`SAC(br15,sin_theta2,`MASK_br15)), .i_multiplier(`BIT_WIDTH'b00000000000001100000000000000000), .o_result(sin12_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));
		qadd #(`FRACTIONS,`BIT_WIDTH) n_adder(.a(`SAC(br16,cos12,`MASK_br16)), .b(`BIT_WIDTH'b00000000000001011000000000000000), .c(part_1_reg));
		qmult #(`FRACTIONS,`BIT_WIDTH) multiplier_1(.i_multiplicand(`SAC(br17,part_1,`MASK_br17)), .i_multiplier(y), .o_result(part_y_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));
		qmult #(`FRACTIONS,`BIT_WIDTH) multiplier_2(.i_multiplicand(`SAC(br18,sin12,`MASK_br18)), .i_multiplier(x), .o_result(part_x_reg), .ovr(overflow_flag), .clk(clock), .rst(rst));

	always@(part_x) begin
		if (`SAC(br19,part_x[31],`MASK_br19)) begin
			signed_bit=1'b0;
		end
		else begin
			signed_bit=1'b1;
		end
	end
		qadd #(`FRACTIONS,`BIT_WIDTH) adder_123 (.a({`SAC(br20,signed_bit,`MASK_br20),`SAC(br28,part_x[30:0],`MASK_br28)}), .b(`SAC(br21,part_y,`MASK_br21)), .c(theta1_num));
		qdiv #(`FRACTIONS,`BIT_WIDTH) m_divider(.i_dividend(`SAC(br22,theta1_num,`MASK_br22)), .i_divisor(`SAC(br23,xy_sum,`MASK_br23)), .i_start(1'b1), .i_clk(clock), .rst(rst), .o_quotient_out(theta1_in), 
		.o_complete(), .o_overflow());
		asin_lut U3 (`SAC(br24,theta1_in,`MASK_br24),theta1);

endmodule
