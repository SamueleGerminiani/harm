`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 			Burke
// Engineer: 			Tom Burke
// 
// Create Date:		19:39:14 08/24/2011 
// Design Name: 	
// Module Name:		qdiv.v
// Project Name:		Fixed-point Math Library (Verilog)
// Target Devices: 
// Tool versions:		Xilinx ISE WebPack v14.7
// Description: 		Fixed-point division in (Q,N) format
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
//	Revision 0.02 - 25 May 2014
//							Updated to fix an error
//
// Additional Comments: Based on my description on youtube:
//			http://youtu.be/TEnaPMYiuR8
//
//////////////////////////////////////////////////////////////////////////////////

`include "deMacro.v"
module qdiv #(
    //Parameterized values
    parameter Q = 15,
        parameter N = 32
    )
    (
        input 	[N-1:0] i_dividend,
        input 	[N-1:0] i_divisor,
        input 	i_start,
        input 	i_clk,
        input   rst,
        output 	[N-1:0] o_quotient_out,
        output 	o_complete,
        output	o_overflow
    );

    reg [2*N+Q-3:0]	reg_working_quotient;	//	Our working copy of the quotient
    reg [N-1:0] 		reg_quotient;				//	Final quotient
    reg [N-2+Q:0] 		reg_working_dividend;	//	Working copy of the dividend
    reg [2*N+Q-3:0]	reg_working_divisor;		// Working copy of the divisor

    reg [N-1:0] 			reg_count; 		//	This is obviously a lot bigger than it needs to be, as we only need 
    //		count to N-1+Q but, computing that number of bits requires a 
    //		logarithm (base 2), and I don't know how to do that in a 
    //		way that will work for everyone

    reg					reg_done;			//	Computation completed flag
    reg					reg_sign;			//	The quotient's sign bit
    reg					reg_overflow;		//	Overflow flag

    //initial reg_done = 1'b1;				//	Initial state is to not be doing anything
    //initial reg_overflow = 1'b0;			//		And there should be no woverflow present
    //initial reg_sign = 1'b0;				//		And the sign should be positive

    //initial reg_working_quotient = 0;	
    //initial reg_quotient = 0;				
    //initial reg_working_dividend = 0;	
    //initial reg_working_divisor = 0;		
    //initial reg_count = 0; 		


    `SR(s45,assign o_quotient_out[N-2:0] = reg_quotient[N-2:0];,assign o_quotient_out[N-2:0]=0;)
    `SR(s46,assign o_quotient_out[N-1] = reg_sign;,assign o_quotient_out[N-1]=0;)
    `SR(s47,assign o_complete = reg_done;,assign o_complete=0;)
    `SR(s48,assign o_overflow = reg_overflow;,assign o_overflow=0;)

    always @( posedge i_clk ) begin

        if(rst) begin
            `SR(s49,reg_done  <= 1'b1;,reg_done  <=0;)
            `SR(s50,reg_sign  <= 1'b0;,reg_sign  <=0;)
            `SR(s51,reg_overflow <= 1'b0;,reg_overflow<=0;)
            `SR(s52,reg_working_quotient <= 0;,reg_working_quotient<=0;)
            `SR(s53,reg_quotient <= 0;, reg_quotient<=0;)
            `SR(s54,reg_working_dividend <= 0;,reg_working_dividend<=0;)
            `SR(s55,reg_working_divisor <= 0;,reg_working_divisor<=0;)
            `SR(s56,reg_count <= 0;,reg_count <=0;)    
        end
        else begin
            if( reg_done && i_start ) begin										//	This is our startup condition
                //  Need to check for a divide by zero right here, I think....
                `SR(s57,reg_done <= 1'b0;,reg_done<=0;)
                `SR(s58,reg_count <= N+Q-1;,reg_count<=0;)
                `SR(s59,reg_working_quotient <= 0;,reg_working_quotient<=0;)
                `SR(s60,reg_working_dividend <= 0;,reg_working_dividend<=0;)
                `SR(s61,reg_working_divisor <= 0;,reg_working_divisor<=0;)
                `SR(s62,reg_overflow <= 1'b0;, reg_overflow<=0;)
                `SR(s63,reg_working_dividend[N+Q-2:Q] <= i_dividend[N-2:0];, reg_working_dividend[N+Q-2:Q]<=0;)
                `SR(s64,reg_working_divisor[2*N+Q-3:N+Q-1] <= i_divisor[N-2:0];,reg_working_divisor[2*N+Q-3:N+Q-1] <=0;)
                `SR(s65,reg_sign <= i_dividend[N-1] ^ i_divisor[N-1];, reg_sign <=0;)
                //	Set the sign bit
            end 
            else if(!reg_done) begin
                `SR(s66,reg_working_divisor <= reg_working_divisor >> 1;,reg_working_divisor <=0;)
                `SR(s67,reg_count <= reg_count - 1;,reg_count <=0;)
                //	Decrement the count

                //	If the dividend is greater than the divisor
                if(reg_working_dividend >= reg_working_divisor) begin
                    `SR(s68,reg_working_quotient[reg_count] <= 1'b1;,reg_working_quotient[reg_count] <=0;)
                    `SR(s69,reg_working_dividend <= reg_working_dividend - reg_working_divisor;,reg_working_dividend <=0;)
                    //		and subtract the divisor from the dividend
                end

                //stop condition
                if(reg_count == 0) begin
                    `SR(s70,reg_done <= 1'b1;,reg_done <=0;)
                    `SR(s71,reg_quotient <= reg_working_quotient;,reg_quotient <=0;)
                    //	Move in our working copy to the outside world
                    if (reg_working_quotient[2*N+Q-3:N]>0)
                        `SR(s72,reg_overflow <= 1'b1;,reg_overflow <=0;)
                end
                else
                    `SR(s73,reg_count <= reg_count - 1;	,reg_count <=0;)
            end
        end
    end
    endmodule
