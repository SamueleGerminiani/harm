//////////////////////////////////////////////////////////////////////////////////////////
// 8-order gaussian low-pass FIR filter
// By: Hassan Ghasemzadeh
// Last modified: 30.01.2017
//
//////////////////////////////////////////////////////////////////////////////////////////

module fir_approx (Data_in, clk, Reset, Data_out);

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
wire [8:0] carry;
wire [6:0] tmp_signal_sum;
wire [5:0] tmp_signal_carry;
reg [in_size-1:0] Samples[1:8];

assign tmp[0] = Data_in;
assign carry[0] = 0;

//Multipliers instantiation
mul16u_exact component_09(tmp[0], b0, zmp[0]);
mul16u_exact component_10(tmp[1], b1, zmp[1]);
mul16u_exact component_11(tmp[2], b2, zmp[2]);
mul16u_exact component_12(tmp[3], b3, zmp[3]);
mul16u_exact component_13(tmp[4], b4, zmp[4]);
mul16u_exact component_14(tmp[5], b5, zmp[5]);
mul16u_exact component_15(tmp[6], b6, zmp[6]);
mul16u_exact component_16(tmp[7], b7, zmp[7]);
mul16u_exact component_17(tmp[8], b8, zmp[8]);
             
//Registers instantiation
register fir_reg_0(Reset, clk, tmp[0], tmp[1]);
register fir_reg_1(Reset, clk, tmp[1], tmp[2]);
register fir_reg_2(Reset, clk, tmp[2], tmp[3]);
register fir_reg_3(Reset, clk, tmp[3], tmp[4]);
register fir_reg_4(Reset, clk, tmp[4], tmp[5]);
register fir_reg_5(Reset, clk, tmp[5], tmp[6]);
register fir_reg_6(Reset, clk, tmp[6], tmp[7]);
register fir_reg_7(Reset, clk, tmp[7], tmp[8]);

module register (input Reset,Clk, input [31:0] Din, output [31:0] Dout);
  reg [31:0] q;
  always @(posedge Clk)
    begin
      if(Reset == 1)
        q <= 0;
      else
        q <= Din;
      end
    assign Dout = q;
endmodule

//Adders instantiation
adder_16bit component_01(zmp[1], zmp[0], pout[1]);
adder_16bit component_02(pout[1], zmp[2], pout[2]);
adder_16bit component_03(pout[2], zmp[3], pout[3]);
adder_16bit component_04(pout[3], zmp[4], pout[4]);
adder_16bit component_05(pout[4], zmp[5], pout[5]);
adder_16bit component_06(pout[5], zmp[6], pout[6]);
adder_16bit component_07(pout[6], zmp[7], pout[7]);
adder_16bit component_08(pout[7], zmp[8], pout[8]);

assign Data_out[31:0] = pout[8];                

module adder_16bit(a,b,o);
  parameter SIZE  = 32;
  input wire [SIZE-1:0] a,b;
  output wire [SIZE-1:0] o;
  wire [31:0] tmp;
  assign tmp = a + b;
  assign o = tmp;
endmodule

module mul16u_exact(a,b,o);
  parameter SIZE  = 32;
  input wire [SIZE-1:0] a,b;
  output wire [SIZE-1:0] o;
  //wire[SIZE-1:0] tmp;
  //assign tmp = a * b;
  assign o = a*b;
endmodule
endmodule
