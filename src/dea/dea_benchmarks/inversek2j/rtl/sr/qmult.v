`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:21:14 08/24/2011 
// Design Name: 
// Module Name:    q15_mult 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
`include "deMacro.v"
module qmult #(parameter Q=15, N=32)
	(i_multiplicand,i_multiplier,o_result,ovr, clk ,rst);
	 input			[N-1:0]	i_multiplicand;
	 input			[N-1:0]	i_multiplier;
	 output			[N-1:0]	o_result;
	 //	The underlying assumption, here, is that both fixed-point values are of the same length (N,Q)
	 //		Because of this, the results will be of length N+N = 2N bits....
	 //		This also simplifies the hand-back of results, as the binimal point 
	 //		will always be in the same location...
	input clk, rst;
	output	reg				ovr;
	reg [2*N-1:0]	r_result;		//	Multiplication by 2 values of N bits requires a 
	wire [2*N-1:0]  r_result_tmp;
										//		register that is N+N = 2N deep...
	reg [N-1:0]		r_RetVal;
	
//--------------------------------------------------------------------------------
    //	Only handing back the same number of bits as we received...
											//		with fixed point in same location...
	
//---------------------------------------------------------------------------------
	//always @(i_multiplicand, i_multiplier)	begin						//	Do the multiply any time the inputs change
	always @(r_result_tmp)	begin
		//r_result <= i_multiplicand[N-2:0] * i_multiplier[N-2:0];	//	Removing the sign bits from the multiply - that 
		//Multiplier_31_0_3000 mul0 (r_result, in1, in2);
		`SR(s27,r_result <= r_result_tmp;,r_result <=0;)

																					//		would introduce *big* errors	
		//ovr <= 1'b0;															//	reset overflow flag to zero
		end
	
		//	This always block will throw a warning, as it uses a & b, but only acts on changes in result...
	always @(r_result) begin													//	Any time the result changes, we need to recompute the sign bit,
		`SR(s28,r_RetVal[N-1] <= i_multiplicand[N-1] ^ i_multiplier[N-1];,r_RetVal[N-1]<=0;)
    //		which is the XOR of the input sign bits...  (you do the truth table...)
		`SR(s29,r_RetVal[N-2:0] <= r_result[N-2+Q:Q];,r_RetVal[N-2:0] <=0;)
        //	And we also need to push the proper N bits of result up to 
																						//		the calling entity...
		if (r_result[2*N-2:N-1+Q] > 0)										// And finally, we need to check for an overflow
			`SR(s30,ovr <= 1'b1;,ovr<=0;)
		else
			`SR(s31,ovr <= 1'b0;,ovr<=0;)
		end


	`SR(s32,Multiplier_31_0_3000 mul0 (r_result_tmp, {1'b0,i_multiplicand[N-2:0]}, {1'b0,i_multiplier[N-2:0]}, clk ,rst);,assign r_result_tmp=0;)

	`SR(s33,assign o_result = r_RetVal;,assign o_result=0;)
endmodule
