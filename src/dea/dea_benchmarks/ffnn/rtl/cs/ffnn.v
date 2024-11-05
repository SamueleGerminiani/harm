`include "deMacro.v"

// Top level module for ffnn.
module ffnn_approx(Reset, clk, a, b, c, d, result);

parameter SIZE = 64;

input Reset, clk;

input[SIZE-1:0] a;
input[SIZE-1:0] b;
input[SIZE-1:0] c;
input[SIZE-1:0] d;

output[SIZE-1:0] result;


wire[SIZE-1:0] mult_1[1:32];
wire[SIZE-1:0] sum_1[1:32];
wire[SIZE-1:0] layer1_output[1:8];

wire[SIZE-1:0] mult_2[1:48];
wire[SIZE-1:0] sum_2[1:48];
wire[SIZE-1:0] layer2_output[1:6];

wire[SIZE-1:0] mult_3[1:18];
wire[SIZE-1:0] sum_3[1:19];
wire[SIZE-1:0] layer3_output[1:3];

wire[SIZE-1:0] reg_l1_out[1:8];
wire[SIZE-1:0] reg_l2_out[1:6];
wire[SIZE-1:0] reg_l3_out[1:3];

wire [SIZE-1:0] output_label_tmp,out_temp;

// Weights.
parameter W1_0_0 = 64'd30;
parameter W1_1_0 = 64'd17;
parameter W1_2_0 = 64'd32788;
parameter W1_3_0 = 64'd32801;
parameter W1_0_1 = 64'd32805;
parameter W1_1_1 = 64'd5;
parameter W1_2_1 = 64'd32795;
parameter W1_3_1 = 64'd32797;
parameter W1_0_2 = 64'd32806;
parameter W1_1_2 = 64'd32793;
parameter W1_2_2 = 64'd32791;
parameter W1_3_2 = 64'd32771;
parameter W1_0_3 = 64'd37;
parameter W1_1_3 = 64'd32777;
parameter W1_2_3 = 64'd35;
parameter W1_3_3 = 64'd24;
parameter W1_0_4 = 64'd32794;
parameter W1_1_4 = 64'd32795;
parameter W1_2_4 = 64'd32784;
parameter W1_3_4 = 64'd26;
parameter W1_0_5 = 64'd32791;
parameter W1_1_5 = 64'd32773;
parameter W1_2_5 = 64'd32792;
parameter W1_3_5 = 64'd24;
parameter W1_0_6 = 64'd13;
parameter W1_1_6 = 64'd1;
parameter W1_2_6 = 64'd19;
parameter W1_3_6 = 64'd44;
parameter W1_0_7 = 64'd29;
parameter W1_1_7 = 64'd39;
parameter W1_2_7 = 64'd32809;
parameter W1_3_7 = 64'd32803;

parameter W2_0_0 = 64'd26;
parameter W2_1_0 = 64'd11;
parameter W2_2_0 = 64'd20;
parameter W2_3_0 = 64'd26;
parameter W2_4_0 = 64'd26;
parameter W2_5_0 = 64'd32790;
parameter W2_6_0 = 64'd16;
parameter W2_7_0 = 64'd35;
parameter W2_0_1 = 64'd32799;
parameter W2_1_1 = 64'd27;
parameter W2_2_1 = 64'd32783;
parameter W2_3_1 = 64'd20;
parameter W2_4_1 = 64'd32776;
parameter W2_5_1 = 64'd32778;
parameter W2_6_1 = 64'd13;
parameter W2_7_1 = 64'd18;
parameter W2_0_2 = 64'd13;
parameter W2_1_2 = 64'd18;
parameter W2_2_2 = 64'd32786;
parameter W2_3_2 = 64'd11;
parameter W2_4_2 = 64'd32788;
parameter W2_5_2 = 64'd12;
parameter W2_6_2 = 64'd33;
parameter W2_7_2 = 64'd32792;
parameter W2_0_3 = 64'd8;
parameter W2_1_3 = 64'd4;
parameter W2_2_3 = 64'd32771;
parameter W2_3_3 = 64'd13;
parameter W2_4_3 = 64'd32792;
parameter W2_5_3 = 64'd9;
parameter W2_6_3 = 64'd10;
parameter W2_7_3 = 64'd32798;
parameter W2_0_4 = 64'd32781;
parameter W2_1_4 = 64'd32787;
parameter W2_2_4 = 64'd32771;
parameter W2_3_4 = 64'd20;
parameter W2_4_4 = 64'd32784;
parameter W2_5_4 = 64'd32773;
parameter W2_6_4 = 64'd18;
parameter W2_7_4 = 64'd32774;
parameter W2_0_5 = 64'd32788;
parameter W2_1_5 = 64'd32770;
parameter W2_2_5 = 64'd22;
parameter W2_3_5 = 64'd16;
parameter W2_4_5 = 64'd32776;
parameter W2_5_5 = 64'd32771;
parameter W2_6_5 = 64'd32793;
parameter W2_7_5 = 64'd2;

parameter W3_0_0 = 64'd17;
parameter W3_1_0 = 64'd32790;
parameter W3_2_0 = 64'd32800;
parameter W3_3_0 = 64'd32797;
parameter W3_4_0 = 64'd32805;
parameter W3_5_0 = 64'd32774;
parameter W3_0_1 = 64'd32794;
parameter W3_1_1 = 64'd32793;
parameter W3_2_1 = 64'd32784;
parameter W3_3_1 = 64'd23;
parameter W3_4_1 = 64'd19;
parameter W3_5_1 = 64'd4;
parameter W3_0_2 = 64'd32775;
parameter W3_1_2 = 64'd25;
parameter W3_2_2 = 64'd15;
parameter W3_3_2 = 64'd32777;
parameter W3_4_2 = 64'd32780;
parameter W3_5_2 = 64'd0;

// Biases.
parameter b1_0 = 64'd14;
parameter b1_1 = 64'd0;
parameter b1_2 = 64'd0;
parameter b1_3 = 64'd32770;
parameter b1_4 = 64'd0;
parameter b1_5 = 64'd0;
parameter b1_6 = 64'd32771;
parameter b1_7 = 64'd7;

parameter b2_0 = 64'd32769;
parameter b2_1 = 64'd32784;
parameter b2_2 = 64'd32776;
parameter b2_3 = 64'd15;
parameter b2_4 = 64'd8;
parameter b2_5 = 64'd0;

parameter b3_0 = 64'd22;
parameter b3_1 = 64'd4;
parameter b3_2 = 64'd32796;

// Behavioral description of operations.


// Layer 1 computations:

// Multipliers instantiation.
`CS(component_01, mul16u_exact,`SUB_component_01)  component_01(a, W1_0_0, mult_1[1]);
`CS(component_02, mul16u_exact,`SUB_component_02)  component_02(b, W1_1_0, mult_1[2]);
`CS(component_03, mul16u_exact,`SUB_component_03)  component_03(c, W1_2_0, mult_1[3]);
`CS(component_04, mul16u_exact,`SUB_component_04)  component_04(d, W1_3_0, mult_1[4]);
`CS(component_05, mul16u_exact,`SUB_component_05)  component_05(a, W1_0_1, mult_1[5]);
`CS(component_06, mul16u_exact,`SUB_component_06)  component_06(b, W1_1_1, mult_1[6]);
`CS(component_07, mul16u_exact,`SUB_component_07)  component_07(c, W1_2_1, mult_1[7]);
`CS(component_08, mul16u_exact,`SUB_component_08)  component_08(d, W1_3_1, mult_1[8]);
`CS(component_09, mul16u_exact,`SUB_component_09)  component_09(a, W1_0_2, mult_1[9]);
`CS(component_10, mul16u_exact,`SUB_component_10)  component_10(b, W1_1_2, mult_1[10]);
`CS(component_11, mul16u_exact,`SUB_component_11) component_11(c, W1_2_2, mult_1[11]);
`CS(component_12, mul16u_exact,`SUB_component_12) component_12(d, W1_3_2, mult_1[12]);
`CS(component_13, mul16u_exact,`SUB_component_13) component_13(a, W1_0_3, mult_1[13]);
`CS(component_14, mul16u_exact,`SUB_component_14) component_14(b, W1_1_3, mult_1[14]);
`CS(component_15, mul16u_exact,`SUB_component_15) component_15(c, W1_2_3, mult_1[15]);
`CS(component_16, mul16u_exact,`SUB_component_16) component_16(d, W1_3_3, mult_1[16]);
`CS(component_17, mul16u_exact,`SUB_component_17) component_17(a, W1_0_4, mult_1[17]);
`CS(component_18, mul16u_exact,`SUB_component_18) component_18(b, W1_1_4, mult_1[18]);
`CS(component_19, mul16u_exact,`SUB_component_19) component_19(c, W1_2_4, mult_1[19]);
`CS(component_20, mul16u_exact,`SUB_component_20) component_20(d, W1_3_4, mult_1[20]);
`CS(component_21, mul16u_exact,`SUB_component_21) component_21(a, W1_0_5, mult_1[21]);
`CS(component_22, mul16u_exact,`SUB_component_22) component_22(b, W1_1_5, mult_1[22]);
`CS(component_23, mul16u_exact,`SUB_component_23) component_23(c, W1_2_5, mult_1[23]);
`CS(component_24, mul16u_exact,`SUB_component_24) component_24(d, W1_3_5, mult_1[24]);
`CS(component_25, mul16u_exact,`SUB_component_25) component_25(a, W1_0_6, mult_1[25]);
`CS(component_26, mul16u_exact,`SUB_component_26) component_26(b, W1_1_6, mult_1[26]);
`CS(component_27, mul16u_exact,`SUB_component_27) component_27(c, W1_2_6, mult_1[27]);
`CS(component_28, mul16u_exact,`SUB_component_28) component_28(d, W1_3_6, mult_1[28]);
`CS(component_29, mul16u_exact,`SUB_component_29) component_29(a, W1_0_7, mult_1[29]);
`CS(component_30, mul16u_exact,`SUB_component_30) component_30(b, W1_1_7, mult_1[30]);
`CS(component_31, mul16u_exact,`SUB_component_31) component_31(c, W1_2_7, mult_1[31]);
`CS(component_32, mul16u_exact,`SUB_component_32) component_32(d, W1_3_7, mult_1[32]);

// Adders instantiation.
`CS(component_33, adder_16bit, `SUB_component_33) component_33(mult_1[1], mult_1[2], sum_1[1]);
`CS(component_34, adder_16bit, `SUB_component_34) component_34(mult_1[3], mult_1[4], sum_1[2]);
`CS(component_35, adder_16bit, `SUB_component_35) component_35(mult_1[5], mult_1[6], sum_1[3]);
`CS(component_36, adder_16bit, `SUB_component_36) component_36(mult_1[7], mult_1[8], sum_1[4]);
`CS(component_37, adder_16bit, `SUB_component_37) component_37(mult_1[9], mult_1[10], sum_1[5]);
`CS(component_38, adder_16bit, `SUB_component_38) component_38(mult_1[11], mult_1[12], sum_1[6]);
`CS(component_39, adder_16bit, `SUB_component_39) component_39(mult_1[13], mult_1[14], sum_1[7]);
`CS(component_40, adder_16bit, `SUB_component_40) component_40(mult_1[15], mult_1[16], sum_1[8]);
`CS(component_41, adder_16bit, `SUB_component_41) component_41(mult_1[17], mult_1[18], sum_1[9]);
`CS(component_42, adder_16bit, `SUB_component_42) component_42(mult_1[19], mult_1[20], sum_1[10]);
`CS(component_43, adder_16bit, `SUB_component_43) component_43(mult_1[21], mult_1[22], sum_1[11]);
`CS(component_44, adder_16bit, `SUB_component_44) component_44(mult_1[23], mult_1[24], sum_1[12]);
`CS(component_45, adder_16bit, `SUB_component_45) component_45(mult_1[25], mult_1[26], sum_1[13]);
`CS(component_46, adder_16bit, `SUB_component_46) component_46(mult_1[27], mult_1[28], sum_1[14]);
`CS(component_47, adder_16bit, `SUB_component_47) component_47(mult_1[29], mult_1[30], sum_1[15]);
`CS(component_48, adder_16bit, `SUB_component_48) component_48(mult_1[31], mult_1[32], sum_1[16]);
                                                
`CS(component_49, adder_16bit, `SUB_component_49) component_49(sum_1[1], sum_1[2], sum_1[17]);
`CS(component_50, adder_16bit, `SUB_component_50) component_50(sum_1[3], sum_1[4], sum_1[18]);
`CS(component_51, adder_16bit, `SUB_component_51) component_51(sum_1[5], sum_1[6], sum_1[19]);
`CS(component_52, adder_16bit, `SUB_component_52) component_52(sum_1[7], sum_1[8], sum_1[20]);
`CS(component_53, adder_16bit, `SUB_component_53) component_53(sum_1[9], sum_1[10], sum_1[21]);
`CS(component_54, adder_16bit, `SUB_component_54) component_54(sum_1[11], sum_1[12], sum_1[22]);
`CS(component_55, adder_16bit, `SUB_component_55) component_55(sum_1[13], sum_1[14], sum_1[23]);
`CS(component_56, adder_16bit, `SUB_component_56) component_56(sum_1[15], sum_1[16], sum_1[24]);
                                                
`CS(component_57, adder_16bit, `SUB_component_57) component_57(sum_1[17], b1_0, sum_1[25]);
`CS(component_58, adder_16bit, `SUB_component_58) component_58(sum_1[18], b1_1, sum_1[26]);
`CS(component_59, adder_16bit, `SUB_component_59) component_59(sum_1[19], b1_2, sum_1[27]);
`CS(component_60, adder_16bit, `SUB_component_60) component_60(sum_1[20], b1_3, sum_1[28]);
`CS(component_61, adder_16bit, `SUB_component_61) component_61(sum_1[21], b1_4, sum_1[29]);
`CS(component_62, adder_16bit, `SUB_component_62) component_62(sum_1[22], b1_5, sum_1[30]);
`CS(component_63, adder_16bit, `SUB_component_63) component_63(sum_1[23], b1_6, sum_1[31]);
`CS(component_64, adder_16bit, `SUB_component_64) component_64(sum_1[24], b1_7, sum_1[32]);


register reg_l1_1(Reset, clk, sum_1[25], reg_l1_out[1]);
register reg_l1_2(Reset, clk, sum_1[26], reg_l1_out[2]);
register reg_l1_3(Reset, clk, sum_1[27], reg_l1_out[3]);
register reg_l1_4(Reset, clk, sum_1[28], reg_l1_out[4]);
register reg_l1_5(Reset, clk, sum_1[29], reg_l1_out[5]);
register reg_l1_6(Reset, clk, sum_1[30], reg_l1_out[6]);
register reg_l1_7(Reset, clk, sum_1[31], reg_l1_out[7]);
register reg_l1_8(Reset, clk, sum_1[32], reg_l1_out[8]);

// Module for Relu lookup:
RELU_1 RELU1_instance(.Reset(Reset), .clk(clk), .in_1(reg_l1_out[1]), .in_2(reg_l1_out[2]), .in_3(reg_l1_out[3]), .in_4(reg_l1_out[4]), .in_5(reg_l1_out[5]), .in_6(reg_l1_out[6]), .in_7(reg_l1_out[7]), .in_8(reg_l1_out[8]), .out_1(layer1_output[1]), .out_2(layer1_output[2]), .out_3(layer1_output[3]), .out_4(layer1_output[4]), .out_5(layer1_output[5]), .out_6(layer1_output[6]), .out_7(layer1_output[7]), .out_8(layer1_output[8]));


// Layer 2 computations:
// Multipliers instantiation.
`CS(component_65, mul16u_exact,`SUB_component_65)   component_65 (layer1_output[1], W2_0_0, mult_2[1]);
`CS(component_66, mul16u_exact,`SUB_component_66)   component_66 (layer1_output[2], W2_1_0, mult_2[2]);
`CS(component_67, mul16u_exact,`SUB_component_67)   component_67 (layer1_output[3], W2_2_0, mult_2[3]);
`CS(component_68, mul16u_exact,`SUB_component_68)   component_68 (layer1_output[4], W2_3_0, mult_2[4]);
`CS(component_69, mul16u_exact,`SUB_component_69)   component_69 (layer1_output[5], W2_4_0, mult_2[5]);
`CS(component_70, mul16u_exact,`SUB_component_70)   component_70 (layer1_output[6], W2_5_0, mult_2[6]);
`CS(component_71, mul16u_exact,`SUB_component_71)   component_71 (layer1_output[7], W2_6_0, mult_2[7]);
`CS(component_72, mul16u_exact,`SUB_component_72)   component_72 (layer1_output[8], W2_7_0, mult_2[8]);
`CS(component_73, mul16u_exact,`SUB_component_73)   component_73 (layer1_output[1], W2_0_1, mult_2[9]);
`CS(component_74, mul16u_exact,`SUB_component_74)   component_74 (layer1_output[2], W2_1_1, mult_2[10]);
`CS(component_75, mul16u_exact,`SUB_component_75)   component_75 (layer1_output[3], W2_2_1, mult_2[11]);
`CS(component_76, mul16u_exact,`SUB_component_76)   component_76 (layer1_output[4], W2_3_1, mult_2[12]);
`CS(component_77, mul16u_exact,`SUB_component_77)   component_77 (layer1_output[5], W2_4_1, mult_2[13]);
`CS(component_78, mul16u_exact,`SUB_component_78)   component_78 (layer1_output[6], W2_5_1, mult_2[14]);
`CS(component_79, mul16u_exact,`SUB_component_79)   component_79 (layer1_output[7], W2_6_1, mult_2[15]);
`CS(component_80, mul16u_exact,`SUB_component_80)   component_80 (layer1_output[8], W2_7_1, mult_2[16]);
`CS(component_81, mul16u_exact,`SUB_component_81)   component_81 (layer1_output[1], W2_0_2, mult_2[17]);
`CS(component_82, mul16u_exact,`SUB_component_82)   component_82 (layer1_output[2], W2_1_2, mult_2[18]);
`CS(component_83, mul16u_exact,`SUB_component_83)   component_83 (layer1_output[3], W2_2_2, mult_2[19]);
`CS(component_84, mul16u_exact,`SUB_component_84)   component_84 (layer1_output[4], W2_3_2, mult_2[20]);
`CS(component_85, mul16u_exact,`SUB_component_85)   component_85 (layer1_output[5], W2_4_2, mult_2[21]);
`CS(component_86, mul16u_exact,`SUB_component_86)   component_86 (layer1_output[6], W2_5_2, mult_2[22]);
`CS(component_87, mul16u_exact,`SUB_component_87)   component_87 (layer1_output[7], W2_6_2, mult_2[23]);
`CS(component_88, mul16u_exact,`SUB_component_88)   component_88 (layer1_output[8], W2_7_2, mult_2[24]);
`CS(component_89, mul16u_exact,`SUB_component_89)   component_89 (layer1_output[1], W2_0_3, mult_2[25]);
`CS(component_90, mul16u_exact,`SUB_component_90)   component_90 (layer1_output[2], W2_1_3, mult_2[26]);
`CS(component_91, mul16u_exact,`SUB_component_91)   component_91 (layer1_output[3], W2_2_3, mult_2[27]);
`CS(component_92, mul16u_exact,`SUB_component_92)   component_92 (layer1_output[4], W2_3_3, mult_2[28]);
`CS(component_93, mul16u_exact,`SUB_component_93)   component_93 (layer1_output[5], W2_4_3, mult_2[29]);
`CS(component_94, mul16u_exact,`SUB_component_94)   component_94 (layer1_output[6], W2_5_3, mult_2[30]);
`CS(component_95, mul16u_exact,`SUB_component_95)   component_95 (layer1_output[7], W2_6_3, mult_2[31]);
`CS(component_96, mul16u_exact,`SUB_component_96)   component_96 (layer1_output[8], W2_7_3, mult_2[32]);
`CS(component_97, mul16u_exact,`SUB_component_97)   component_97 (layer1_output[1], W2_0_4, mult_2[33]);
`CS(component_98, mul16u_exact,`SUB_component_98)   component_98 (layer1_output[2], W2_1_4, mult_2[34]);
`CS(component_99, mul16u_exact,`SUB_component_99)   component_99 (layer1_output[3], W2_2_4, mult_2[35]);

`CS(component_100, mul16u_exact,`SUB_component_100)   component_100(layer1_output[4], W2_3_4, mult_2[36]);
`CS(component_101, mul16u_exact,`SUB_component_101)  component_101(layer1_output[5], W2_4_4, mult_2[37]);
`CS(component_102, mul16u_exact,`SUB_component_102)  component_102(layer1_output[6], W2_5_4, mult_2[38]);
`CS(component_103, mul16u_exact,`SUB_component_103)  component_103(layer1_output[7], W2_6_4, mult_2[39]);
`CS(component_104, mul16u_exact,`SUB_component_104)  component_104(layer1_output[8], W2_7_4, mult_2[40]);
`CS(component_105, mul16u_exact,`SUB_component_105)  component_105(layer1_output[1], W2_0_5, mult_2[41]);
`CS(component_106, mul16u_exact,`SUB_component_106)  component_106(layer1_output[2], W2_1_5, mult_2[42]);
`CS(component_107, mul16u_exact,`SUB_component_107)  component_107(layer1_output[3], W2_2_5, mult_2[43]);
`CS(component_108, mul16u_exact,`SUB_component_108)  component_108(layer1_output[4], W2_3_5, mult_2[44]);
`CS(component_109, mul16u_exact,`SUB_component_109)  component_109(layer1_output[5], W2_4_5, mult_2[45]);
`CS(component_110, mul16u_exact,`SUB_component_110)  component_110(layer1_output[6], W2_5_5, mult_2[46]);
`CS(component_111, mul16u_exact,`SUB_component_111)  component_111(layer1_output[7], W2_6_5, mult_2[47]);
`CS(component_112, mul16u_exact,`SUB_component_112)  component_112(layer1_output[8], W2_7_5, mult_2[48]);

// Adders instantiation.
`CS(component_113, adder_16bit,`SUB_component_113)  component_113(mult_2[1], mult_2[2], sum_2[1]);
`CS(component_114, adder_16bit,`SUB_component_114)  component_114(mult_2[3], mult_2[4], sum_2[2]);
`CS(component_115, adder_16bit,`SUB_component_115)  component_115(mult_2[5], mult_2[6], sum_2[3]);
`CS(component_116, adder_16bit,`SUB_component_116)  component_116(mult_2[7], mult_2[8], sum_2[4]);
`CS(component_117, adder_16bit,`SUB_component_117)  component_117(mult_2[9], mult_2[10], sum_2[5]);
`CS(component_118, adder_16bit,`SUB_component_118)  component_118(mult_2[11], mult_2[12], sum_2[6]);
`CS(component_119, adder_16bit,`SUB_component_119)  component_119(mult_2[13], mult_2[14], sum_2[7]);
`CS(component_120, adder_16bit,`SUB_component_120)  component_120(mult_2[15], mult_2[16], sum_2[8]);
`CS(component_121, adder_16bit,`SUB_component_121)  component_121(mult_2[17], mult_2[18], sum_2[9]);
`CS(component_122, adder_16bit,`SUB_component_122)  component_122(mult_2[19], mult_2[20], sum_2[10]);
`CS(component_123, adder_16bit,`SUB_component_123)  component_123(mult_2[21], mult_2[22], sum_2[11]);
`CS(component_124, adder_16bit,`SUB_component_124)  component_124(mult_2[23], mult_2[24], sum_2[12]);
`CS(component_125, adder_16bit,`SUB_component_125)  component_125(mult_2[25], mult_2[26], sum_2[13]);
`CS(component_126, adder_16bit,`SUB_component_126)  component_126(mult_2[27], mult_2[28], sum_2[14]);
`CS(component_127, adder_16bit,`SUB_component_127)  component_127(mult_2[29], mult_2[30], sum_2[15]);
`CS(component_128, adder_16bit,`SUB_component_128)  component_128(mult_2[31], mult_2[32], sum_2[16]);
`CS(component_129, adder_16bit,`SUB_component_129)  component_129(mult_2[33], mult_2[34], sum_2[17]);
`CS(component_130, adder_16bit,`SUB_component_130)  component_130(mult_2[35], mult_2[36], sum_2[18]);
`CS(component_131, adder_16bit,`SUB_component_131)  component_131(mult_2[37], mult_2[38], sum_2[19]);
`CS(component_132, adder_16bit,`SUB_component_132)  component_132(mult_2[39], mult_2[40], sum_2[20]);
`CS(component_133, adder_16bit,`SUB_component_133)  component_133(mult_2[41], mult_2[42], sum_2[21]);
`CS(component_134, adder_16bit,`SUB_component_134)  component_134(mult_2[43], mult_2[44], sum_2[22]);
`CS(component_135, adder_16bit,`SUB_component_135)  component_135(mult_2[45], mult_2[46], sum_2[23]);
`CS(component_136, adder_16bit,`SUB_component_136)  component_136(mult_2[47], mult_2[48], sum_2[24]);
                                                 
`CS(component_137, adder_16bit,`SUB_component_137)  component_137(sum_2[1], sum_2[2], sum_2[25]);
`CS(component_138, adder_16bit,`SUB_component_138)  component_138(sum_2[3], sum_2[4], sum_2[26]);
`CS(component_139, adder_16bit,`SUB_component_139)  component_139(sum_2[5], sum_2[6], sum_2[27]);
`CS(component_140, adder_16bit,`SUB_component_140)  component_140(sum_2[7], sum_2[8], sum_2[28]);
`CS(component_141, adder_16bit,`SUB_component_141)  component_141(sum_2[9], sum_2[10], sum_2[29]);
`CS(component_142, adder_16bit,`SUB_component_142)  component_142(sum_2[11], sum_2[12], sum_2[30]);
`CS(component_143, adder_16bit,`SUB_component_143)  component_143(sum_2[13], sum_2[14], sum_2[31]);
`CS(component_144, adder_16bit,`SUB_component_144)  component_144(sum_2[15], sum_2[16], sum_2[32]);
`CS(component_145, adder_16bit,`SUB_component_145)  component_145(sum_2[17], sum_2[18], sum_2[33]);
`CS(component_146, adder_16bit,`SUB_component_146)  component_146(sum_2[19], sum_2[20], sum_2[34]);
`CS(component_147, adder_16bit,`SUB_component_147)  component_147(sum_2[21], sum_2[22], sum_2[35]);
`CS(component_148, adder_16bit,`SUB_component_148)  component_148(sum_2[23], sum_2[24], sum_2[36]);
                                                 
`CS(component_149, adder_16bit,`SUB_component_149)  component_149(sum_2[25], sum_2[26], sum_2[37]);
`CS(component_150, adder_16bit,`SUB_component_150)  component_150(sum_2[27], sum_2[28], sum_2[38]);
`CS(component_151, adder_16bit,`SUB_component_151)  component_151(sum_2[29], sum_2[30], sum_2[39]);
`CS(component_152, adder_16bit,`SUB_component_152)  component_152(sum_2[31], sum_2[32], sum_2[40]);
`CS(component_153, adder_16bit,`SUB_component_153)  component_153(sum_2[33], sum_2[34], sum_2[41]);
`CS(component_154, adder_16bit,`SUB_component_154)  component_154(sum_2[35], sum_2[36], sum_2[42]);
                                                 
`CS(component_155, adder_16bit,`SUB_component_155)  component_155(sum_2[37], b2_0, sum_2[43]);
`CS(component_156, adder_16bit,`SUB_component_156)  component_156(sum_2[38], b2_1, sum_2[44]);
`CS(component_157, adder_16bit,`SUB_component_157)  component_157(sum_2[39], b2_2, sum_2[45]);
`CS(component_158, adder_16bit,`SUB_component_158)  component_158(sum_2[40], b2_3, sum_2[46]);
`CS(component_159, adder_16bit,`SUB_component_159)  component_159(sum_2[41], b2_4, sum_2[47]);
`CS(component_160, adder_16bit,`SUB_component_160)  component_160(sum_2[42], b2_5, sum_2[48]);


register reg_l2_1(Reset, clk, sum_2[43], reg_l2_out[1]);
register reg_l2_2(Reset, clk, sum_2[44], reg_l2_out[2]);
register reg_l2_3(Reset, clk, sum_2[45], reg_l2_out[3]);
register reg_l2_4(Reset, clk, sum_2[46], reg_l2_out[4]);
register reg_l2_5(Reset, clk, sum_2[47], reg_l2_out[5]);
register reg_l2_6(Reset, clk, sum_2[48], reg_l2_out[6]);



// Module for Relu lookup:
RELU_2 RELU2_instance(.Reset(Reset), .clk(clk), .l2_in_1(reg_l2_out[1]), .l2_in_2(reg_l2_out[2]), .l2_in_3(reg_l2_out[3]), .l2_in_4(reg_l2_out[4]), .l2_in_5(reg_l2_out[5]), .l2_in_6(reg_l2_out[6]), .l2_out_1(layer2_output[1]), .l2_out_2(layer2_output[2]), .l2_out_3(layer2_output[3]), .l2_out_4(layer2_output[4]), .l2_out_5(layer2_output[5]), .l2_out_6(layer2_output[6]));


// Layer 3 computations:

// Multipliers instantiation.
`CS(component_161,mul16u_exact,`SUB_component_161) component_161(layer2_output[1], W3_0_0, mult_3[1]);
`CS(component_162,mul16u_exact,`SUB_component_162) component_162(layer2_output[2], W3_1_0, mult_3[2]);
`CS(component_163,mul16u_exact,`SUB_component_163) component_163(layer2_output[3], W3_2_0, mult_3[3]);
`CS(component_164,mul16u_exact,`SUB_component_164) component_164(layer2_output[4], W3_3_0, mult_3[4]);
`CS(component_165,mul16u_exact,`SUB_component_165) component_165(layer2_output[5], W3_4_0, mult_3[5]);
`CS(component_166,mul16u_exact,`SUB_component_166) component_166(layer2_output[6], W3_5_0, mult_3[6]);
`CS(component_167,mul16u_exact,`SUB_component_167) component_167(layer2_output[1], W3_0_1, mult_3[7]);
`CS(component_168,mul16u_exact,`SUB_component_168) component_168(layer2_output[2], W3_1_1, mult_3[8]);
`CS(component_169,mul16u_exact,`SUB_component_169) component_169(layer2_output[3], W3_2_1, mult_3[9]);
`CS(component_170,mul16u_exact,`SUB_component_170) component_170(layer2_output[4], W3_3_1, mult_3[10]);
`CS(component_171,mul16u_exact,`SUB_component_171) component_171(layer2_output[5], W3_4_1, mult_3[11]);
`CS(component_172,mul16u_exact,`SUB_component_172) component_172(layer2_output[6], W3_5_1, mult_3[12]);
`CS(component_173,mul16u_exact,`SUB_component_173) component_173(layer2_output[1], W3_0_2, mult_3[13]);
`CS(component_174,mul16u_exact,`SUB_component_174) component_174(layer2_output[2], W3_1_2, mult_3[14]);
`CS(component_175,mul16u_exact,`SUB_component_175) component_175(layer2_output[3], W3_2_2, mult_3[15]);
`CS(component_176,mul16u_exact,`SUB_component_176) component_176(layer2_output[4], W3_3_2, mult_3[16]);
`CS(component_177,mul16u_exact,`SUB_component_177) component_177(layer2_output[5], W3_4_2, mult_3[17]);
`CS(component_178,mul16u_exact,`SUB_component_178) component_178(layer2_output[6], W3_5_2, mult_3[18]);
                 
`CS(component_179,adder_16bit,`SUB_component_179)  component_179(mult_3[1], mult_3[2], sum_3[1]);
`CS(component_180,adder_16bit,`SUB_component_180)  component_180(mult_3[3], mult_3[4], sum_3[2]);
`CS(component_181,adder_16bit,`SUB_component_181)  component_181(mult_3[5], mult_3[6], sum_3[3]);
`CS(component_182,adder_16bit,`SUB_component_182)  component_182(mult_3[7], mult_3[8], sum_3[4]);
`CS(component_183,adder_16bit,`SUB_component_183)  component_183(mult_3[9], mult_3[10], sum_3[5]);
`CS(component_184,adder_16bit,`SUB_component_184)  component_184(mult_3[11], mult_3[12], sum_3[6]);
`CS(component_185,adder_16bit,`SUB_component_185)  component_185(mult_3[13], mult_3[14], sum_3[7]);
`CS(component_186,adder_16bit,`SUB_component_186)  component_186(mult_3[15], mult_3[16], sum_3[8]);
`CS(component_187,adder_16bit,`SUB_component_187)  component_187(mult_3[17], mult_3[18], sum_3[9]);
                 
`CS(component_188,adder_16bit,`SUB_component_188)  component_188(sum_3[1], sum_3[2], sum_3[10]);
`CS(component_189,adder_16bit,`SUB_component_189)  component_189(sum_3[3], sum_3[4], sum_3[11]);
`CS(component_190,adder_16bit,`SUB_component_190)  component_190(sum_3[5], sum_3[6], sum_3[12]);
`CS(component_191,adder_16bit,`SUB_component_191)  component_191(sum_3[7], sum_3[8], sum_3[13]);
                                                
`CS(component_192,adder_16bit,`SUB_component_192)  component_192(sum_3[10], sum_3[11], sum_3[14]);
`CS(component_193,adder_16bit,`SUB_component_193)  component_193(sum_3[12], sum_3[13], sum_3[15]);
                                                
`CS(component_194,adder_16bit,`SUB_component_194)  component_194(sum_3[15], sum_3[9], sum_3[16]);
                                                
`CS(component_195,adder_16bit,`SUB_component_195)  component_195(sum_3[14], b3_0, sum_3[17]);
`CS(component_196,adder_16bit,`SUB_component_196)  component_196(sum_3[15], b3_1, sum_3[18]);
`CS(component_197,adder_16bit,`SUB_component_197)  component_197(sum_3[16], b3_2, sum_3[19]);

register reg_l3_1(Reset, clk, sum_3[17], reg_l3_out[1]);
register reg_l3_2(Reset, clk, sum_3[18], reg_l3_out[2]);
register reg_l3_3(Reset, clk, sum_3[19], reg_l3_out[3]);



// Module for Softmax lookup:
SOFTMAX SOFTMAX_instance(.Reset(Reset), .clk(clk), .l3_in_1(reg_l3_out[1]), .l3_in_2(reg_l3_out[2]), .l3_in_3(reg_l3_out[3]), .l3_out_1(layer3_output[1]), .l3_out_2(layer3_output[2]), .l3_out_3(layer3_output[3]));


FINDMAX FINDMAX_instance(.Reset(Reset), .clk(clk), .in_1(layer3_output[1]), .in_2(layer3_output[2]), .in_3(layer3_output[3]), .out(output_label_tmp));

register reg_out(Reset, clk, output_label_tmp, out_temp);

// Getting output_label:
assign result = out_temp;

endmodule
