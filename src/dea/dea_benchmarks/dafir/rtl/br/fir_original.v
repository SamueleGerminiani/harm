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
assign zmp[0] = `SAC(br0,tmp[0],`MASK_br0) * b0;
assign zmp[1] = `SAC(br1,tmp[1],`MASK_br1) * b1;
assign zmp[2] = `SAC(br2,tmp[2],`MASK_br2) * b2;
assign zmp[3] = `SAC(br3,tmp[3],`MASK_br3) * b3;
assign zmp[4] = `SAC(br4,tmp[4],`MASK_br4) * b4;
assign zmp[5] = `SAC(br5,tmp[5],`MASK_br5) * b5;
assign zmp[6] = `SAC(br6,tmp[6],`MASK_br6) * b6;
assign zmp[7] = `SAC(br7,tmp[7],`MASK_br7) * b7;
assign zmp[8] = `SAC(br8,tmp[8],`MASK_br8) * b8;
             

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
      q0 <= `SAC(br17,tmp[0],`MASK_br17);
      q1 <= `SAC(br18,tmp[1],`MASK_br18);
      q2 <= `SAC(br19,tmp[2],`MASK_br19);
      q3 <= `SAC(br20,tmp[3],`MASK_br20);
      q4 <= `SAC(br21,tmp[4],`MASK_br21);
      q5 <= `SAC(br22,tmp[5],`MASK_br22);
      q6 <= `SAC(br23,tmp[6],`MASK_br23);
      q7 <= `SAC(br24,tmp[7],`MASK_br24);
   end
end

assign tmp[1] = `SAC(br25,q0,`MASK_br25);
assign tmp[2] = `SAC(br26,q1,`MASK_br26);
assign tmp[3] = `SAC(br27,q2,`MASK_br27);
assign tmp[4] = `SAC(br28,q3,`MASK_br28);
assign tmp[5] = `SAC(br29,q4,`MASK_br29);
assign tmp[6] = `SAC(br30,q5,`MASK_br30);
assign tmp[7] = `SAC(br31,q6,`MASK_br31);
assign tmp[8] = `SAC(br32,q7,`MASK_br32);

//Adders instantiation
assign pout[1] = `SAC(br33,zmp[1],`MASK_br33)  + `SAC(br34,zmp[0],`MASK_br34);
assign pout[2] = `SAC(br35,pout[1],`MASK_br35) + `SAC(br36,zmp[2],`MASK_br36);
assign pout[3] = `SAC(br37,pout[2],`MASK_br37) + `SAC(br38,zmp[3],`MASK_br38);
assign pout[4] = `SAC(br39,pout[3],`MASK_br39) + `SAC(br40,zmp[4],`MASK_br40);
assign pout[5] = `SAC(br41,pout[4],`MASK_br41) + `SAC(br42,zmp[5],`MASK_br42);
assign pout[6] = `SAC(br43,pout[5],`MASK_br43) + `SAC(br44,zmp[6],`MASK_br44);
assign pout[7] = `SAC(br45,pout[6],`MASK_br45) + `SAC(br46,zmp[7],`MASK_br46);
assign pout[8] = `SAC(br47,pout[7],`MASK_br47) + `SAC(br48,zmp[8],`MASK_br48);

assign Data_out[31:0] = `SAC(br49,pout[8],`MASK_br49);

endmodule
