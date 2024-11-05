//////////////////////////////////////////////////////////////////////////////////////////
// 8-order gaussian low-pass FIR filter
// By: Hassan Ghasemzadeh
// Last modified: 30.01.2017
//
//////////////////////////////////////////////////////////////////////////////////////////
`include "deMacro.v"

module fir(Data_in, clk, Reset, Data_out);

parameter order = 8; 
parameter in_size = 32;
parameter out_size = 32;
parameter b0=32'd7;
parameter b1=32'd17;
parameter b2=32'd32;
parameter b3=32'd46;
parameter b4=32'd52;
parameter b5=32'd46;
parameter b6=32'd32;
parameter b7=32'd17;
parameter b8=32'd7;

output [out_size-1:0] Data_out;
input [in_size-1:0] Data_in;
input clk, Reset;
wire [31:0] tmp[0:8];
wire [31:0] zmp[0:8];
wire [31:0] pout[1:8];
wire [6:0] tmp_signal_sum;
wire [5:0] tmp_signal_carry;
reg [in_size-1:0] Samples[1:8];
reg [31:0] q0;
reg [31:0] q1;
reg [31:0] q2;
reg [31:0] q3;
reg [31:0] q4;
reg [31:0] q5;
reg [31:0] q6;
reg [31:0] q7;

assign tmp[0] = Data_in;


//Multipliers instantiation
`SR(s0,assign zmp[0] = tmp[0] * b0;, assign zmp[0] = 0;)
`SR(s1,assign zmp[1] = tmp[1] * b1;, assign zmp[1] = 0;)
`SR(s2,assign zmp[2] = tmp[2] * b2;, assign zmp[2] = 0;)
`SR(s3,assign zmp[3] = tmp[3] * b3;, assign zmp[3] = 0;)
`SR(s4,assign zmp[4] = tmp[4] * b4;, assign zmp[4] = 0;)
`SR(s5,assign zmp[5] = tmp[5] * b5;, assign zmp[5] = 0;)
`SR(s6,assign zmp[6] = tmp[6] * b6;, assign zmp[6] = 0;)
`SR(s7,assign zmp[7] = tmp[7] * b7;, assign zmp[7] = 0;)
`SR(s8,assign zmp[8] = tmp[8] * b8;, assign zmp[8] = 0;)
             

//Registers instantiation
always @(posedge clk) begin
  if(Reset == 1) begin
      q0 <= 0;
      q1 <= 0;
      q2 <= 0;
      q3 <= 0;
      q4 <= 0;
      q5 <= 0;
      q6 <= 0;
      q7 <= 0;
   end else begin
      `SR(s9,q0 <= tmp[0];,q0 <=0;) 
      `SR(s10,q1 <= tmp[1];,q1 <=0;) 
      `SR(s11,q2 <= tmp[2];,q2 <=0;) 
      `SR(s12,q3 <= tmp[3];,q3 <=0;) 
      `SR(s13,q4 <= tmp[4];,q4 <=0;) 
      `SR(s14,q5 <= tmp[5];,q5 <=0;) 
      `SR(s15,q6 <= tmp[6];,q6 <=0;) 
      `SR(s16,q7 <= tmp[7];,q7 <=0;) 
   end
end

`SR(s17,assign tmp[1] = q0;, assign tmp[1] =0;) 
`SR(s18,assign tmp[2] = q1;, assign tmp[2] =0;) 
`SR(s19,assign tmp[3] = q2;, assign tmp[3] =0;) 
`SR(s20,assign tmp[4] = q3;, assign tmp[4] =0;) 
`SR(s21,assign tmp[5] = q4;, assign tmp[5] =0;) 
`SR(s22,assign tmp[6] = q5;, assign tmp[6] =0;) 
`SR(s23,assign tmp[7] = q6;, assign tmp[7] =0;) 
`SR(s24,assign tmp[8] = q7;, assign tmp[8] =0;) 

//Adders instantiation
`SR(s25,assign pout[1] = zmp[1] + zmp[0]; , assign pout[1] =0;) 
`SR(s26,assign pout[2] = pout[1] + zmp[2];, assign pout[2] =0;) 
`SR(s27,assign pout[3] = pout[2] + zmp[3];, assign pout[3] =0;) 
`SR(s28,assign pout[4] = pout[3] + zmp[4];, assign pout[4] =0;) 
`SR(s29,assign pout[5] = pout[4] + zmp[5];, assign pout[5] =0;) 
`SR(s30,assign pout[6] = pout[5] + zmp[6];, assign pout[6] =0;) 
`SR(s31,assign pout[7] = pout[6] + zmp[7];, assign pout[7] =0;) 
`SR(s32,assign pout[8] = pout[7] + zmp[8];, assign pout[8] =0;) 

`SR(s33,assign Data_out[31:0] = pout[8];, assign Data_out[31:0] =0;)

endmodule
