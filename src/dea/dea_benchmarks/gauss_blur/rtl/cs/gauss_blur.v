`include "deMacro.v"

module gauss_blur(clk,Reset,input_pixel_1,input_pixel_2,input_pixel_3,input_pixel_4,input_pixel_5,input_pixel_6,input_pixel_7,input_pixel_8,input_pixel_9,output_value);
input[7:0] input_pixel_1,input_pixel_2,input_pixel_3,input_pixel_4,input_pixel_5,input_pixel_6,input_pixel_7,input_pixel_8,input_pixel_9;

output[7:0] output_value;
input clk,Reset;

parameter G_0_0=32'd16;
parameter G_0_1=32'd32;
parameter G_0_2=32'd16;
parameter G_1_0=32'd32;
parameter G_1_1=32'd64;
parameter G_1_2=32'd32;
parameter G_2_0=32'd16;
parameter G_2_1=32'd32;
parameter G_2_2=32'd16;
    
wire[31:0] sumConvolution,out_temp,out_temp_shifted;
wire[31:0] sum[1:20];
wire[31:0] prod[1:20];
wire[31:0] prod_reg[1:20];

// Multiplication
`CS(component_09,mul16u_exact,`SUB_component_09) component_09({24'b0,input_pixel_1},G_0_0,prod[1]);
`CS(component_10,mul16u_exact,`SUB_component_10) component_10({24'b0,input_pixel_2},G_0_1,prod[2]);
`CS(component_11,mul16u_exact,`SUB_component_11) component_11({24'b0,input_pixel_3},G_0_2,prod[3]);
`CS(component_12,mul16u_exact,`SUB_component_12) component_12({24'b0,input_pixel_4},G_1_0,prod[4]);
`CS(component_13,mul16u_exact,`SUB_component_13) component_13({24'b0,input_pixel_5},G_1_1,prod[5]);
`CS(component_14,mul16u_exact,`SUB_component_14) component_14({24'b0,input_pixel_6},G_1_2,prod[6]);
`CS(component_15,mul16u_exact,`SUB_component_15) component_15({24'b0,input_pixel_7},G_2_0,prod[7]);
`CS(component_16,mul16u_exact,`SUB_component_16) component_16({24'b0,input_pixel_8},G_2_1,prod[8]);
`CS(component_17,mul16u_exact,`SUB_component_17) component_17({24'b0,input_pixel_9},G_2_2,prod[9]);

register conv_reg_01(Reset, clk, prod[1], prod_reg[1]);
register conv_reg_02(Reset, clk, prod[2], prod_reg[2]);
register conv_reg_03(Reset, clk, prod[3], prod_reg[3]);
register conv_reg_04(Reset, clk, prod[4], prod_reg[4]);
register conv_reg_05(Reset, clk, prod[5], prod_reg[5]);
register conv_reg_06(Reset, clk, prod[6], prod_reg[6]);
register conv_reg_07(Reset, clk, prod[7], prod_reg[7]);
register conv_reg_08(Reset, clk, prod[8], prod_reg[8]);
register conv_reg_09(Reset, clk, prod[9], prod_reg[9]);

// Convolution sum
`CS(component_01,adder_16bit,`SUB_component_01) component_01(prod_reg[1],prod_reg[2], sum[1]);
`CS(component_02,adder_16bit,`SUB_component_02) component_02(prod_reg[3],prod_reg[4], sum[2]);
`CS(component_03,adder_16bit,`SUB_component_03) component_03(prod_reg[5],prod_reg[6], sum[3]);
`CS(component_04,adder_16bit,`SUB_component_04) component_04(prod_reg[7],prod_reg[8], sum[4]);
`CS(component_05,adder_16bit,`SUB_component_05) component_05(sum[1],sum[2], sum[5]);
`CS(component_06,adder_16bit,`SUB_component_06) component_06(sum[3],sum[4], sum[6]);
`CS(component_07,adder_16bit,`SUB_component_07) component_07(sum[5],sum[6], sum[7]);
`CS(component_08,adder_16bit,`SUB_component_08) component_08(sum[7], prod_reg[9],sumConvolution);

register conv_reg_10(Reset, clk, sumConvolution,out_temp);
assign out_temp_shifted = out_temp>>8;						// Divide by 256
assign output_value = out_temp_shifted[7:0];

endmodule
