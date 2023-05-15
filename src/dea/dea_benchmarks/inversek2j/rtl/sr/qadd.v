`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:28:18 08/24/2011 
// Design Name: 
// Module Name:    q15_add 
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
module qadd #(parameter Q = 15, N = 32)
	(
    input [N-1:0] a,
    input [N-1:0] b,
    output [N-1:0] c
    );

reg [N-1:0] res;

assign c = res;

always @(a,b) begin
	// both negative or both positive
	if(a[N-1] == b[N-1]) begin						//	Since they have the same sign, absolute magnitude increases
		`SR(s34,res[N-2:0] = a[N-2:0] + b[N-2:0];	,res[N-2:0]=0;)
        //		So we just add the two numbers
		`SR(s35,res[N-1] = a[N-1];,res[N-1]=0;)
        //		and set the sign appropriately...  Doesn't matter which one we use, 
															//		they both have the same sign
															//	Do the sign last, on the off-chance there was an overflow...  
		end												//		Not doing any error checking on this...
	//	one of them is negative...
	else if(a[N-1] == 0 && b[N-1] == 1) begin		//	subtract a-b
		if( a[N-2:0] > b[N-2:0] ) begin					//	if a is greater than b,
			`SR(s36,res[N-2:0] = a[N-2:0] - b[N-2:0];,res[N-2:0]=0;)
        //		then just subtract b from a
			`SR(s37,res[N-1] = 0;,res[N-1]=0;)
            //		and manually set the sign to positive
			end
		else begin												//	if a is less than b,
			`SR(s38,res[N-2:0] = b[N-2:0] - a[N-2:0];,res[N-2:0] =0;)
        //		we'll actually subtract a from b to avoid a 2's complement answer
			if (res[N-2:0] == 0)
				res[N-1] = 0;
            //		I don't like negative zero....
			else
				`SR(s39,res[N-1] = 1;,res[N-1]=0;)
            //		and manually set the sign to negative
			end
		end
	else begin												//	subtract b-a (a negative, b positive)
		if( a[N-2:0] > b[N-2:0] ) begin					//	if a is greater than b,
			`SR(s40,res[N-2:0] = a[N-2:0] - b[N-2:0];,res[N-2:0]=0;)
        //		we'll actually subtract b from a to avoid a 2's complement answer
			if (res[N-2:0] == 0)
				`SR(s41,res[N-1] = 0;,res[N-1]=0;)
            //		I don't like negative zero....
			else
				`SR(s42,res[N-1] = 1;,res[N-1]=0;)
            //		and manually set the sign to negative
			end
		else begin												//	if a is less than b,
			`SR(s43,res[N-2:0] = b[N-2:0] - a[N-2:0];,res[N-2:0]=0;)
        //		then just subtract a from b
			`SR(s44,res[N-1] = 0;,res[N-1] =0;)
            //		and manually set the sign to positive
			end
		end
	end
endmodule
