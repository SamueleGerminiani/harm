`include "deMacro.v"

module imsharp(clk,Reset,input_pixel_1,input_pixel_2,input_pixel_3,input_pixel_4,input_pixel_5,input_pixel_6,input_pixel_7,input_pixel_8,input_pixel_9,input_pixel_10,input_pixel_11,input_pixel_12,input_pixel_13,input_pixel_14,input_pixel_15,input_pixel_16,input_pixel_17,input_pixel_18,input_pixel_19,input_pixel_20,input_pixel_21,input_pixel_22,input_pixel_23,input_pixel_24,input_pixel_25,output_value);
input[7:0] input_pixel_1,input_pixel_2,input_pixel_3,input_pixel_4,input_pixel_5,input_pixel_6,input_pixel_7,input_pixel_8,input_pixel_9,input_pixel_10,input_pixel_11,input_pixel_12,input_pixel_13,input_pixel_14,input_pixel_15,input_pixel_16,input_pixel_17,input_pixel_18,input_pixel_19,input_pixel_20,input_pixel_21,input_pixel_22,input_pixel_23,input_pixel_24,input_pixel_25;

output[7:0] output_value;
input clk,Reset;

parameter G_0_0=32'd16;
parameter G_0_1=32'd64;
parameter G_0_2=32'd112;
parameter G_0_3=32'd64;
parameter G_0_4=32'd16;
parameter G_1_0=32'd64;
parameter G_1_1=32'd256;
parameter G_1_2=32'd416;
parameter G_1_3=32'd256;
parameter G_1_4=32'd64;
parameter G_2_0=32'd112;
parameter G_2_1=32'd416;
parameter G_2_2=32'd656;
parameter G_2_3=32'd416;
parameter G_2_4=32'd112;
parameter G_3_0=32'd64;
parameter G_3_1=32'd256;
parameter G_3_2=32'd416;
parameter G_3_3=32'd256;
parameter G_3_4=32'd64;
parameter G_4_0=32'd16;
parameter G_4_1=32'd64;
parameter G_4_2=32'd112;
parameter G_4_3=32'd64;
parameter G_4_4=32'd1;

wire[31:0] sumConvolution,out_temp,out_temp_shifted;
wire[31:0] sum[1:30];
wire[31:0] prod[1:30];
wire[31:0] prod_reg[1:30];


// Multiplication
`CS(component_25,mul16u_exact,`SUB_component_25) component_25({24'b0,input_pixel_1},G_0_0,prod[1]);
`CS(component_26,mul16u_exact,`SUB_component_26) component_26({24'b0,input_pixel_2},G_0_1,prod[2]);
`CS(component_27,mul16u_exact,`SUB_component_27) component_27({24'b0,input_pixel_3},G_0_2,prod[3]);
`CS(component_28,mul16u_exact,`SUB_component_28) component_28({24'b0,input_pixel_4},G_0_3,prod[4]);
`CS(component_29,mul16u_exact,`SUB_component_29) component_29({24'b0,input_pixel_5},G_0_4,prod[5]);
`CS(component_30,mul16u_exact,`SUB_component_30) component_30({24'b0,input_pixel_6},G_1_0,prod[6]);
`CS(component_31,mul16u_exact,`SUB_component_31) component_31({24'b0,input_pixel_7},G_1_1,prod[7]);
`CS(component_32,mul16u_exact,`SUB_component_32) component_32({24'b0,input_pixel_8},G_1_2,prod[8]);
`CS(component_33,mul16u_exact,`SUB_component_33) component_33({24'b0,input_pixel_9},G_1_3,prod[9]);
`CS(component_34,mul16u_exact,`SUB_component_34) component_34({24'b0,input_pixel_10},G_1_4,prod[10]);
`CS(component_35,mul16u_exact,`SUB_component_35) component_35({24'b0,input_pixel_11},G_2_0,prod[11]);
`CS(component_36,mul16u_exact,`SUB_component_36) component_36({24'b0,input_pixel_12},G_2_1,prod[12]);
`CS(component_37,mul16u_exact,`SUB_component_37) component_37({24'b0,input_pixel_13},G_2_2,prod[13]);
`CS(component_38,mul16u_exact,`SUB_component_38) component_38({24'b0,input_pixel_14},G_2_3,prod[14]);
`CS(component_39,mul16u_exact,`SUB_component_39) component_39({24'b0,input_pixel_15},G_2_4,prod[15]);
`CS(component_40,mul16u_exact,`SUB_component_40) component_40({24'b0,input_pixel_16},G_3_0,prod[16]);
`CS(component_41,mul16u_exact,`SUB_component_41) component_41({24'b0,input_pixel_17},G_3_1,prod[17]);
`CS(component_42,mul16u_exact,`SUB_component_42) component_42({24'b0,input_pixel_18},G_3_2,prod[18]);
`CS(component_43,mul16u_exact,`SUB_component_43) component_43({24'b0,input_pixel_19},G_3_3,prod[19]);
`CS(component_44,mul16u_exact,`SUB_component_44) component_44({24'b0,input_pixel_20},G_3_4,prod[20]);
`CS(component_45,mul16u_exact,`SUB_component_45) component_45({24'b0,input_pixel_21},G_4_0,prod[21]);
`CS(component_46,mul16u_exact,`SUB_component_46) component_46({24'b0,input_pixel_22},G_4_1,prod[22]);
`CS(component_47,mul16u_exact,`SUB_component_47) component_47({24'b0,input_pixel_23},G_4_2,prod[23]);
`CS(component_48,mul16u_exact,`SUB_component_48) component_48({24'b0,input_pixel_24},G_4_3,prod[24]);
`CS(component_49,mul16u_exact,`SUB_component_49) component_49({24'b0,input_pixel_25},G_4_4,prod[25]);

register conv_reg_01(Reset, clk, prod[1], prod_reg[1]);
register conv_reg_02(Reset, clk, prod[2], prod_reg[2]);
register conv_reg_03(Reset, clk, prod[3], prod_reg[3]);
register conv_reg_04(Reset, clk, prod[4], prod_reg[4]);
register conv_reg_05(Reset, clk, prod[5], prod_reg[5]);
register conv_reg_06(Reset, clk, prod[6], prod_reg[6]);
register conv_reg_07(Reset, clk, prod[7], prod_reg[7]);
register conv_reg_08(Reset, clk, prod[8], prod_reg[8]);
register conv_reg_09(Reset, clk, prod[9], prod_reg[9]);
register conv_reg_10(Reset, clk, prod[10], prod_reg[10]);
register conv_reg_11(Reset, clk, prod[11], prod_reg[11]);
register conv_reg_12(Reset, clk, prod[12], prod_reg[12]);
register conv_reg_13(Reset, clk, prod[13], prod_reg[13]);
register conv_reg_14(Reset, clk, prod[14], prod_reg[14]);
register conv_reg_15(Reset, clk, prod[15], prod_reg[15]);
register conv_reg_16(Reset, clk, prod[16], prod_reg[16]);
register conv_reg_17(Reset, clk, prod[17], prod_reg[17]);
register conv_reg_18(Reset, clk, prod[18], prod_reg[18]);
register conv_reg_19(Reset, clk, prod[19], prod_reg[19]);
register conv_reg_20(Reset, clk, prod[20], prod_reg[20]);
register conv_reg_21(Reset, clk, prod[21], prod_reg[21]);
register conv_reg_22(Reset, clk, prod[22], prod_reg[22]);
register conv_reg_23(Reset, clk, prod[23], prod_reg[23]);
register conv_reg_24(Reset, clk, prod[24], prod_reg[24]);
register conv_reg_25(Reset, clk, prod[25], prod_reg[25]);

// Convolution sum
`CS(component_01,adder_16bit,`SUB_component_01) component_01(prod_reg[1],prod_reg[2], sum[1]);
`CS(component_02,adder_16bit,`SUB_component_02) component_02(prod_reg[3],prod_reg[4], sum[2]);
`CS(component_03,adder_16bit,`SUB_component_03) component_03(prod_reg[5],prod_reg[6], sum[3]);
`CS(component_04,adder_16bit,`SUB_component_04) component_04(prod_reg[7],prod_reg[8], sum[4]);
`CS(component_05,adder_16bit,`SUB_component_05) component_05(prod_reg[9],prod_reg[10], sum[5]);
`CS(component_06,adder_16bit,`SUB_component_06) component_06(prod_reg[11],prod_reg[12], sum[6]);
`CS(component_07,adder_16bit,`SUB_component_07) component_07(prod_reg[13],prod_reg[14], sum[7]);
`CS(component_08,adder_16bit,`SUB_component_08) component_08(prod_reg[15],prod_reg[16], sum[8]);
`CS(component_09,adder_16bit,`SUB_component_09) component_09(prod_reg[17],prod_reg[18], sum[9]);
`CS(component_10,adder_16bit,`SUB_component_10) component_10(prod_reg[19],prod_reg[20], sum[10]);
`CS(component_11,adder_16bit,`SUB_component_11) component_11(prod_reg[21],prod_reg[22], sum[11]);
`CS(component_12,adder_16bit,`SUB_component_12) component_12(prod_reg[23],prod_reg[24], sum[12]);
`CS(component_13,adder_16bit,`SUB_component_13) component_13(sum[1],sum[2], sum[13]);
`CS(component_14,adder_16bit,`SUB_component_14) component_14(sum[3],sum[4], sum[14]);
`CS(component_15,adder_16bit,`SUB_component_15) component_15(sum[5],sum[6], sum[15]);
`CS(component_16,adder_16bit,`SUB_component_16) component_16(sum[7],sum[8], sum[16]);
`CS(component_17,adder_16bit,`SUB_component_17) component_17(sum[9],sum[10], sum[17]);
`CS(component_18,adder_16bit,`SUB_component_18) component_18(sum[11],sum[12], sum[18]);
`CS(component_19,adder_16bit,`SUB_component_19) component_19(sum[13],sum[14], sum[19]);
`CS(component_20,adder_16bit,`SUB_component_20) component_20(sum[15],sum[16], sum[20]);
`CS(component_21,adder_16bit,`SUB_component_21) component_21(sum[17],sum[18], sum[21]);
`CS(component_22,adder_16bit,`SUB_component_22) component_22(sum[19],sum[20], sum[22]);
`CS(component_23,adder_16bit,`SUB_component_23) component_23(sum[21],sum[22], sum[23]);
`CS(component_24,adder_16bit,`SUB_component_24) component_24(sum[23], prod_reg[25],sumConvolution);


register conv_reg_26(Reset, clk, sumConvolution,out_temp);

assign out_temp_shifted = (input_pixel_13<<1)-(out_temp>>12);							// out = ((2*(central_pixel)- (sumConvolution/4368))   --> F. LOMARDI et al.,
assign output_value = out_temp_shifted[7:0];

endmodule
