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
`SR(s0, mul16u_exact component_01(a, W1_0_0, mult_1[1] );,  assign mult_1[1] =0;)
`SR(s1, mul16u_exact component_02(b, W1_1_0, mult_1[2] );,  assign mult_1[2] =0;)
`SR(s2, mul16u_exact component_03(c, W1_2_0, mult_1[3] );,  assign mult_1[3] =0;)
`SR(s3, mul16u_exact component_04(d, W1_3_0, mult_1[4] );,  assign mult_1[4] =0;)
`SR(s4, mul16u_exact component_05(a, W1_0_1, mult_1[5] );,  assign mult_1[5] =0;)
`SR(s5, mul16u_exact component_06(b, W1_1_1, mult_1[6] );,  assign mult_1[6] =0;)
`SR(s6, mul16u_exact component_07(c, W1_2_1, mult_1[7] );,  assign mult_1[7] =0;)
`SR(s7, mul16u_exact component_08(d, W1_3_1, mult_1[8] );,  assign mult_1[8] =0;)
`SR(s8, mul16u_exact component_09(a, W1_0_2, mult_1[9] );,  assign mult_1[9] =0;)
`SR(s9,mul16u_exact component_10(b, W1_1_2,  mult_1[10]);,  assign mult_1[10]=0;)
`SR(s10,mul16u_exact component_11(c, W1_2_2,  mult_1[11]);,  assign mult_1[11]=0;)
`SR(s11,mul16u_exact component_12(d, W1_3_2,  mult_1[12]);,  assign mult_1[12]=0;)
`SR(s12,mul16u_exact component_13(a, W1_0_3,  mult_1[13]);,  assign mult_1[13]=0;)
`SR(s13,mul16u_exact component_14(b, W1_1_3,  mult_1[14]);,  assign mult_1[14]=0;)
`SR(s14,mul16u_exact component_15(c, W1_2_3,  mult_1[15]);,  assign mult_1[15]=0;)
`SR(s15,mul16u_exact component_16(d, W1_3_3,  mult_1[16]);,  assign mult_1[16]=0;)
`SR(s16,mul16u_exact component_17(a, W1_0_4,  mult_1[17]);,  assign mult_1[17]=0;)
`SR(s17,mul16u_exact component_18(b, W1_1_4,  mult_1[18]);,  assign mult_1[18]=0;)
`SR(s18,mul16u_exact component_19(c, W1_2_4,  mult_1[19]);,  assign mult_1[19]=0;)
`SR(s19,mul16u_exact component_20(d, W1_3_4,  mult_1[20]);,  assign mult_1[20]=0;)
`SR(s20,mul16u_exact component_21(a, W1_0_5,  mult_1[21]);,  assign mult_1[21]=0;)
`SR(s21,mul16u_exact component_22(b, W1_1_5,  mult_1[22]);,  assign mult_1[22]=0;)
`SR(s22,mul16u_exact component_23(c, W1_2_5,  mult_1[23]);,  assign mult_1[23]=0;)
`SR(s23,mul16u_exact component_24(d, W1_3_5,  mult_1[24]);,  assign mult_1[24]=0;)
`SR(s24,mul16u_exact component_25(a, W1_0_6,  mult_1[25]);,  assign mult_1[25]=0;)
`SR(s25,mul16u_exact component_26(b, W1_1_6,  mult_1[26]);,  assign mult_1[26]=0;)
`SR(s26,mul16u_exact component_27(c, W1_2_6,  mult_1[27]);,  assign mult_1[27]=0;)
`SR(s27,mul16u_exact component_28(d, W1_3_6,  mult_1[28]);,  assign mult_1[28]=0;)
`SR(s28,mul16u_exact component_29(a, W1_0_7,  mult_1[29]);,  assign mult_1[29]=0;)
`SR(s29,mul16u_exact component_30(b, W1_1_7,  mult_1[30]);,  assign mult_1[30]=0;)
`SR(s30,mul16u_exact component_31(c, W1_2_7,  mult_1[31]);,  assign mult_1[31]=0;)
`SR(s31,mul16u_exact component_32(d, W1_3_7,  mult_1[32]);,  assign mult_1[32]=0;)



// Adders instantiation.
`SR(s32,adder_16bit component_33(mult_1[1], mult_1[2],    sum_1[1]);, assign   sum_1[1]=0;)
`SR(s33,adder_16bit component_34(mult_1[3], mult_1[4],    sum_1[2]);, assign   sum_1[2]=0;)
`SR(s34,adder_16bit component_35(mult_1[5], mult_1[6],    sum_1[3]);, assign   sum_1[3]=0;)
`SR(s35,adder_16bit component_36(mult_1[7], mult_1[8],    sum_1[4]);, assign   sum_1[4]=0;)
`SR(s36,adder_16bit component_37(mult_1[9], mult_1[10],   sum_1[5]);, assign   sum_1[5]=0;)
`SR(s37,adder_16bit component_38(mult_1[11], mult_1[12],  sum_1[6]);, assign   sum_1[6]=0;)
`SR(s38,adder_16bit component_39(mult_1[13], mult_1[14],  sum_1[7]);, assign   sum_1[7]=0;)
`SR(s39,adder_16bit component_40(mult_1[15], mult_1[16],  sum_1[8]);, assign   sum_1[8]=0;)
`SR(s40,adder_16bit component_41(mult_1[17], mult_1[18],  sum_1[9]);, assign   sum_1[9]=0;)
`SR(s41,adder_16bit component_42(mult_1[19], mult_1[20], sum_1[10]);, assign  sum_1[10]=0;)
`SR(s42,adder_16bit component_43(mult_1[21], mult_1[22], sum_1[11]);, assign  sum_1[11]=0;)
`SR(s43,adder_16bit component_44(mult_1[23], mult_1[24], sum_1[12]);, assign  sum_1[12]=0;)
`SR(s44,adder_16bit component_45(mult_1[25], mult_1[26], sum_1[13]);, assign  sum_1[13]=0;)
`SR(s45,adder_16bit component_46(mult_1[27], mult_1[28], sum_1[14]);, assign  sum_1[14]=0;)
`SR(s46,adder_16bit component_47(mult_1[29], mult_1[30], sum_1[15]);, assign  sum_1[15]=0;)
`SR(s47,adder_16bit component_48(mult_1[31], mult_1[32], sum_1[16]);, assign  sum_1[16]=0;)
`SR(s48,adder_16bit component_49(sum_1[1], sum_1[2],     sum_1[17]);, assign  sum_1[17]=0;)
`SR(s49,adder_16bit component_50(sum_1[3], sum_1[4],     sum_1[18]);, assign  sum_1[18]=0;)
`SR(s50,adder_16bit component_51(sum_1[5], sum_1[6],     sum_1[19]);, assign  sum_1[19]=0;)
`SR(s51,adder_16bit component_52(sum_1[7], sum_1[8],     sum_1[20]);, assign  sum_1[20]=0;)
`SR(s52,adder_16bit component_53(sum_1[9], sum_1[10],    sum_1[21]);, assign  sum_1[21]=0;)
`SR(s53,adder_16bit component_54(sum_1[11], sum_1[12],   sum_1[22]);, assign  sum_1[22]=0;)
`SR(s54,adder_16bit component_55(sum_1[13], sum_1[14],   sum_1[23]);, assign  sum_1[23]=0;)
`SR(s55,adder_16bit component_56(sum_1[15], sum_1[16],   sum_1[24]);, assign  sum_1[24]=0;)
`SR(s56,adder_16bit component_57(sum_1[17], b1_0,        sum_1[25]);, assign  sum_1[25]=0;)
`SR(s57,adder_16bit component_58(sum_1[18], b1_1,        sum_1[26]);, assign  sum_1[26]=0;)
`SR(s58,adder_16bit component_59(sum_1[19], b1_2,        sum_1[27]);, assign  sum_1[27]=0;)
`SR(s59,adder_16bit component_60(sum_1[20], b1_3,        sum_1[28]);, assign  sum_1[28]=0;)
`SR(s60,adder_16bit component_61(sum_1[21], b1_4,        sum_1[29]);, assign  sum_1[29]=0;)
`SR(s61,adder_16bit component_62(sum_1[22], b1_5,        sum_1[30]);, assign  sum_1[30]=0;)
`SR(s62,adder_16bit component_63(sum_1[23], b1_6,        sum_1[31]);, assign  sum_1[31]=0;)
`SR(s63,adder_16bit component_64(sum_1[24], b1_7,        sum_1[32]);, assign  sum_1[32]=0;)
`SR(s64,register reg_l1_1(Reset, clk, sum_1[25],     reg_l1_out[1]);, assign  reg_l1_out[1]=0;)
`SR(s65,register reg_l1_2(Reset, clk, sum_1[26],     reg_l1_out[2]);, assign  reg_l1_out[2]=0;)
`SR(s66,register reg_l1_3(Reset, clk, sum_1[27],     reg_l1_out[3]);, assign  reg_l1_out[3]=0;)
`SR(s67,register reg_l1_4(Reset, clk, sum_1[28],     reg_l1_out[4]);, assign  reg_l1_out[4]=0;)
`SR(s68,register reg_l1_5(Reset, clk, sum_1[29],     reg_l1_out[5]);, assign  reg_l1_out[5]=0;)
`SR(s69,register reg_l1_6(Reset, clk, sum_1[30],     reg_l1_out[6]);, assign  reg_l1_out[6]=0;)
`SR(s70,register reg_l1_7(Reset, clk, sum_1[31],     reg_l1_out[7]);, assign  reg_l1_out[7]=0;)
`SR(s71,register reg_l1_8(Reset, clk, sum_1[32],     reg_l1_out[8]);, assign  reg_l1_out[8]=0;)

// Module for Relu lookup:
`SR(s72,RELU_1 RELU1_instance(.Reset(Reset), .clk(clk), .in_1(reg_l1_out[1]), .in_2(reg_l1_out[2]), .in_3(reg_l1_out[3]), .in_4(reg_l1_out[4]), .in_5(reg_l1_out[5]), .in_6(reg_l1_out[6]), .in_7(reg_l1_out[7]), .in_8(reg_l1_out[8]), .out_1(layer1_output[1]), .out_2(layer1_output[2]), .out_3(layer1_output[3]), .out_4(layer1_output[4]), .out_5(layer1_output[5]), .out_6(layer1_output[6]), .out_7(layer1_output[7]), .out_8(layer1_output[8]));,assign layer1_output[1]=0;assign layer1_output[2]=0;assign layer1_output[3]=0;assign layer1_output[4]=0;assign layer1_output[5]=0;assign layer1_output[6]=0;assign layer1_output[7]=0;assign layer1_output[8]=0;)


// Layer 2 computations:

// Multipliers instantiation.
`SR(s73,mul16u_exact component_65(layer1_output[1], W2_0_0,  mult_2[1]);,assign  mult_2[1]=0;)
`SR(s74,mul16u_exact component_66(layer1_output[2], W2_1_0,  mult_2[2]);,assign  mult_2[2]=0;)
`SR(s75,mul16u_exact component_67(layer1_output[3], W2_2_0,  mult_2[3]);,assign  mult_2[3]=0;)
`SR(s76,mul16u_exact component_68(layer1_output[4], W2_3_0,  mult_2[4]);,assign  mult_2[4]=0;)
`SR(s77,mul16u_exact component_69(layer1_output[5], W2_4_0,  mult_2[5]);,assign  mult_2[5]=0;)
`SR(s78,mul16u_exact component_70(layer1_output[6], W2_5_0,  mult_2[6]);,assign  mult_2[6]=0;)
`SR(s79,mul16u_exact component_71(layer1_output[7], W2_6_0,  mult_2[7]);,assign  mult_2[7]=0;)
`SR(s80,mul16u_exact component_72(layer1_output[8], W2_7_0,  mult_2[8]);,assign  mult_2[8]=0;)
`SR(s81,mul16u_exact component_73(layer1_output[1], W2_0_1,  mult_2[9]);,assign  mult_2[9]=0;)
`SR(s82,mul16u_exact component_74(layer1_output[2], W2_1_1, mult_2[10]);,assign mult_2[10]=0;)
`SR(s83,mul16u_exact component_75(layer1_output[3], W2_2_1, mult_2[11]);,assign mult_2[11]=0;)
`SR(s84,mul16u_exact component_76(layer1_output[4], W2_3_1, mult_2[12]);,assign mult_2[12]=0;)
`SR(s85,mul16u_exact component_77(layer1_output[5], W2_4_1, mult_2[13]);,assign mult_2[13]=0;)
`SR(s86,mul16u_exact component_78(layer1_output[6], W2_5_1, mult_2[14]);,assign mult_2[14]=0;)
`SR(s87,mul16u_exact component_79(layer1_output[7], W2_6_1, mult_2[15]);,assign mult_2[15]=0;)
`SR(s88,mul16u_exact component_80(layer1_output[8], W2_7_1, mult_2[16]);,assign mult_2[16]=0;)
`SR(s89,mul16u_exact component_81(layer1_output[1], W2_0_2, mult_2[17]);,assign mult_2[17]=0;)
`SR(s90,mul16u_exact component_82(layer1_output[2], W2_1_2, mult_2[18]);,assign mult_2[18]=0;)
`SR(s91,mul16u_exact component_83(layer1_output[3], W2_2_2, mult_2[19]);,assign mult_2[19]=0;)
`SR(s92,mul16u_exact component_84(layer1_output[4], W2_3_2, mult_2[20]);,assign mult_2[20]=0;)
`SR(s93,mul16u_exact component_85(layer1_output[5], W2_4_2, mult_2[21]);,assign mult_2[21]=0;)
`SR(s94,mul16u_exact component_86(layer1_output[6], W2_5_2, mult_2[22]);,assign mult_2[22]=0;)
`SR(s95,mul16u_exact component_87(layer1_output[7], W2_6_2, mult_2[23]);,assign mult_2[23]=0;)
`SR(s96,mul16u_exact component_88(layer1_output[8], W2_7_2, mult_2[24]);,assign mult_2[24]=0;)
`SR(s97,mul16u_exact component_89(layer1_output[1], W2_0_3, mult_2[25]);,assign mult_2[25]=0;)
`SR(s98,mul16u_exact component_90(layer1_output[2], W2_1_3, mult_2[26]);,assign mult_2[26]=0;)
`SR(s99,mul16u_exact component_91(layer1_output[3], W2_2_3, mult_2[27]);,assign mult_2[27]=0;)
`SR(s100,mul16u_exact component_92(layer1_output[4], W2_3_3, mult_2[28]);,assign mult_2[28]=0;)
`SR(s101,mul16u_exact component_93(layer1_output[5], W2_4_3, mult_2[29]);,assign mult_2[29]=0;)
`SR(s102,mul16u_exact component_94(layer1_output[6], W2_5_3, mult_2[30]);,assign mult_2[30]=0;)
`SR(s103,mul16u_exact component_95(layer1_output[7], W2_6_3, mult_2[31]);,assign mult_2[31]=0;)
`SR(s104,mul16u_exact component_96(layer1_output[8], W2_7_3, mult_2[32]);,assign mult_2[32]=0;)
`SR(s105,mul16u_exact component_97(layer1_output[1], W2_0_4, mult_2[33]);,assign mult_2[33]=0;)
`SR(s106,mul16u_exact component_98(layer1_output[2], W2_1_4, mult_2[34]);,assign mult_2[34]=0;)
`SR(s107,mul16u_exact component_99(layer1_output[3], W2_2_4, mult_2[35]);,assign mult_2[35]=0;)
`SR(s108,mul16u_exact component_100(layer1_output[4], W2_3_4,mult_2[36]);,assign mult_2[36]=0;)
`SR(s109,mul16u_exact component_101(layer1_output[5], W2_4_4,mult_2[37]);,assign mult_2[37]=0;)
`SR(s110,mul16u_exact component_102(layer1_output[6], W2_5_4,mult_2[38]);,assign mult_2[38]=0;)
`SR(s111,mul16u_exact component_103(layer1_output[7], W2_6_4,mult_2[39]);,assign mult_2[39]=0;)
`SR(s112,mul16u_exact component_104(layer1_output[8], W2_7_4,mult_2[40]);,assign mult_2[40]=0;)
`SR(s113,mul16u_exact component_105(layer1_output[1], W2_0_5,mult_2[41]);,assign mult_2[41]=0;)
`SR(s114,mul16u_exact component_106(layer1_output[2], W2_1_5,mult_2[42]);,assign mult_2[42]=0;)
`SR(s115,mul16u_exact component_107(layer1_output[3], W2_2_5,mult_2[43]);,assign mult_2[43]=0;)
`SR(s116,mul16u_exact component_108(layer1_output[4], W2_3_5,mult_2[44]);,assign mult_2[44]=0;)
`SR(s117,mul16u_exact component_109(layer1_output[5], W2_4_5,mult_2[45]);,assign mult_2[45]=0;)
`SR(s118,mul16u_exact component_110(layer1_output[6], W2_5_5,mult_2[46]);,assign mult_2[46]=0;)
`SR(s119,mul16u_exact component_111(layer1_output[7], W2_6_5,mult_2[47]);,assign mult_2[47]=0;)
`SR(s120,mul16u_exact component_112(layer1_output[8], W2_7_5,mult_2[48]);,assign mult_2[48]=0;)
`SR(s121,adder_16bit component_113(mult_2[1], mult_2[2],       sum_2[1]);,assign   sum_2[1]=0;)
`SR(s122,adder_16bit component_114(mult_2[3], mult_2[4],       sum_2[2]);,assign   sum_2[2]=0;)
`SR(s123,adder_16bit component_115(mult_2[5], mult_2[6],       sum_2[3]);,assign   sum_2[3]=0;)
`SR(s124,adder_16bit component_116(mult_2[7], mult_2[8],       sum_2[4]);,assign   sum_2[4]=0;)
`SR(s125,adder_16bit component_117(mult_2[9], mult_2[10],      sum_2[5]);,assign   sum_2[5]=0;)
`SR(s126,adder_16bit component_118(mult_2[11], mult_2[12],     sum_2[6]);,assign   sum_2[6]=0;)
`SR(s127,adder_16bit component_119(mult_2[13], mult_2[14],     sum_2[7]);,assign   sum_2[7]=0;)
`SR(s128,adder_16bit component_120(mult_2[15], mult_2[16],     sum_2[8]);,assign   sum_2[8]=0;)
`SR(s129,adder_16bit component_121(mult_2[17], mult_2[18],     sum_2[9]);,assign   sum_2[9]=0;)
`SR(s130,adder_16bit component_122(mult_2[19], mult_2[20],    sum_2[10]);,assign  sum_2[10]=0;)
`SR(s131,adder_16bit component_123(mult_2[21], mult_2[22],    sum_2[11]);,assign  sum_2[11]=0;)
`SR(s132,adder_16bit component_124(mult_2[23], mult_2[24],    sum_2[12]);,assign  sum_2[12]=0;)
`SR(s133,adder_16bit component_125(mult_2[25], mult_2[26],    sum_2[13]);,assign  sum_2[13]=0;)
`SR(s134,adder_16bit component_126(mult_2[27], mult_2[28],    sum_2[14]);,assign  sum_2[14]=0;)
`SR(s135,adder_16bit component_127(mult_2[29], mult_2[30],    sum_2[15]);,assign  sum_2[15]=0;)
`SR(s136,adder_16bit component_128(mult_2[31], mult_2[32],    sum_2[16]);,assign  sum_2[16]=0;)
`SR(s137,adder_16bit component_129(mult_2[33], mult_2[34],    sum_2[17]);,assign  sum_2[17]=0;)
`SR(s138,adder_16bit component_130(mult_2[35], mult_2[36],    sum_2[18]);,assign  sum_2[18]=0;)
`SR(s139,adder_16bit component_131(mult_2[37], mult_2[38],    sum_2[19]);,assign  sum_2[19]=0;)
`SR(s140,adder_16bit component_132(mult_2[39], mult_2[40],    sum_2[20]);,assign  sum_2[20]=0;)
`SR(s141,adder_16bit component_133(mult_2[41], mult_2[42],    sum_2[21]);,assign  sum_2[21]=0;)
`SR(s142,adder_16bit component_134(mult_2[43], mult_2[44],    sum_2[22]);,assign  sum_2[22]=0;)
`SR(s143,adder_16bit component_135(mult_2[45], mult_2[46],    sum_2[23]);,assign  sum_2[23]=0;)
`SR(s144,adder_16bit component_136(mult_2[47], mult_2[48],    sum_2[24]);,assign  sum_2[24]=0;)
`SR(s145,adder_16bit component_137(sum_2[1], sum_2[2],        sum_2[25]);,assign  sum_2[25]=0;)
`SR(s146,adder_16bit component_138(sum_2[3], sum_2[4],        sum_2[26]);,assign  sum_2[26]=0;)
`SR(s147,adder_16bit component_139(sum_2[5], sum_2[6],        sum_2[27]);,assign  sum_2[27]=0;)
`SR(s148,adder_16bit component_140(sum_2[7], sum_2[8],        sum_2[28]);,assign  sum_2[28]=0;)
`SR(s149,adder_16bit component_141(sum_2[9], sum_2[10],       sum_2[29]);,assign  sum_2[29]=0;)
`SR(s150,adder_16bit component_142(sum_2[11], sum_2[12],      sum_2[30]);,assign  sum_2[30]=0;)
`SR(s151,adder_16bit component_143(sum_2[13], sum_2[14],      sum_2[31]);,assign  sum_2[31]=0;)
`SR(s152,adder_16bit component_144(sum_2[15], sum_2[16],      sum_2[32]);,assign  sum_2[32]=0;)
`SR(s153,adder_16bit component_145(sum_2[17], sum_2[18],      sum_2[33]);,assign  sum_2[33]=0;)
`SR(s154,adder_16bit component_146(sum_2[19], sum_2[20],      sum_2[34]);,assign  sum_2[34]=0;)
`SR(s155,adder_16bit component_147(sum_2[21], sum_2[22],      sum_2[35]);,assign  sum_2[35]=0;)
`SR(s156,adder_16bit component_148(sum_2[23], sum_2[24],      sum_2[36]);,assign  sum_2[36]=0;)
`SR(s157,adder_16bit component_149(sum_2[25], sum_2[26],      sum_2[37]);,assign  sum_2[37]=0;)
`SR(s158,adder_16bit component_150(sum_2[27], sum_2[28],      sum_2[38]);,assign  sum_2[38]=0;)
`SR(s159,adder_16bit component_151(sum_2[29], sum_2[30],      sum_2[39]);,assign  sum_2[39]=0;)
`SR(s160,adder_16bit component_152(sum_2[31], sum_2[32],      sum_2[40]);,assign  sum_2[40]=0;)
`SR(s161,adder_16bit component_153(sum_2[33], sum_2[34],      sum_2[41]);,assign  sum_2[41]=0;)
`SR(s162,adder_16bit component_154(sum_2[35], sum_2[36],      sum_2[42]);,assign  sum_2[42]=0;)
`SR(s163,adder_16bit component_155(sum_2[37], b2_0,           sum_2[43]);,assign  sum_2[43]=0;)
`SR(s164,adder_16bit component_156(sum_2[38], b2_1,           sum_2[44]);,assign  sum_2[44]=0;)
`SR(s165,adder_16bit component_157(sum_2[39], b2_2,           sum_2[45]);,assign  sum_2[45]=0;)
`SR(s166,adder_16bit component_158(sum_2[40], b2_3,           sum_2[46]);,assign  sum_2[46]=0;)
`SR(s167,adder_16bit component_159(sum_2[41], b2_4,           sum_2[47]);,assign  sum_2[47]=0;)
`SR(s168,adder_16bit component_160(sum_2[42], b2_5,           sum_2[48]);,assign  sum_2[48]=0;)
`SR(s169,register reg_l2_1(Reset, clk, sum_2[43],         reg_l2_out[1]);,assign reg_l2_out[1]=0;)
`SR(s170,register reg_l2_2(Reset, clk, sum_2[44],         reg_l2_out[2]);,assign reg_l2_out[2]=0;)
`SR(s171,register reg_l2_3(Reset, clk, sum_2[45],         reg_l2_out[3]);,assign reg_l2_out[3]=0;)
`SR(s172,register reg_l2_4(Reset, clk, sum_2[46],         reg_l2_out[4]);,assign reg_l2_out[4]=0;)
`SR(s173,register reg_l2_5(Reset, clk, sum_2[47],         reg_l2_out[5]);,assign reg_l2_out[5]=0;)
`SR(s174,register reg_l2_6(Reset, clk, sum_2[48],         reg_l2_out[6]);,assign reg_l2_out[6]=0;)



`SR(%s,RELU_2 RELU2_instance(.Reset(Reset), .clk(clk), .l2_in_1(reg_l2_out[1]), .l2_in_2(reg_l2_out[2]), .l2_in_3(reg_l2_out[3]), .l2_in_4(reg_l2_out[4]), .l2_in_5(reg_l2_out[5]), .l2_in_6(reg_l2_out[6]), .l2_out_1(layer2_output[1]), .l2_out_2(layer2_output[2]), .l2_out_3(layer2_output[3]), .l2_out_4(layer2_output[4]), .l2_out_5(layer2_output[5]), .l2_out_6(layer2_output[6]));, assign layer2_output[1]=0; assign layer2_output[2]=0; assign layer2_output[3]=0; assign layer2_output[4]=0; assign layer2_output[5]=0; assign layer2_output[6]=0;)


// Layer 3 computations:

// Multipliers instantiation.
`SR(s175,mul16u_exact component_161(layer2_output[1], W3_0_0,  mult_3[1]); ,assign mult_3[1]=0;)
`SR(s176,mul16u_exact component_162(layer2_output[2], W3_1_0,  mult_3[2]); ,assign mult_3[2]=0;)
`SR(s177,mul16u_exact component_163(layer2_output[3], W3_2_0,  mult_3[3]); ,assign mult_3[3]=0;)
`SR(s178,mul16u_exact component_164(layer2_output[4], W3_3_0,  mult_3[4]); ,assign mult_3[4]=0;)
`SR(s179,mul16u_exact component_165(layer2_output[5], W3_4_0,  mult_3[5]); ,assign mult_3[5]=0;)
`SR(s180,mul16u_exact component_166(layer2_output[6], W3_5_0,  mult_3[6]); ,assign mult_3[6]=0;)
`SR(s181,mul16u_exact component_167(layer2_output[1], W3_0_1,  mult_3[7]); ,assign mult_3[7]=0;)
`SR(s182,mul16u_exact component_168(layer2_output[2], W3_1_1,  mult_3[8]); ,assign mult_3[8]=0;)
`SR(s183,mul16u_exact component_169(layer2_output[3], W3_2_1,  mult_3[9]); ,assign mult_3[9]=0;)
`SR(s184,mul16u_exact component_170(layer2_output[4], W3_3_1, mult_3[10]); ,assign mult_3[10]=0;)
`SR(s185,mul16u_exact component_171(layer2_output[5], W3_4_1, mult_3[11]); ,assign mult_3[11]=0;)
`SR(s186,mul16u_exact component_172(layer2_output[6], W3_5_1, mult_3[12]); ,assign mult_3[12]=0;)
`SR(s187,mul16u_exact component_173(layer2_output[1], W3_0_2, mult_3[13]); ,assign mult_3[13]=0;)
`SR(s188,mul16u_exact component_174(layer2_output[2], W3_1_2, mult_3[14]); ,assign mult_3[14]=0;)
`SR(s189,mul16u_exact component_175(layer2_output[3], W3_2_2, mult_3[15]); ,assign mult_3[15]=0;)
`SR(s190,mul16u_exact component_176(layer2_output[4], W3_3_2, mult_3[16]); ,assign mult_3[16]=0;)
`SR(s191,mul16u_exact component_177(layer2_output[5], W3_4_2, mult_3[17]); ,assign mult_3[17]=0;)
`SR(s192,mul16u_exact component_178(layer2_output[6], W3_5_2, mult_3[18]); ,assign mult_3[18]=0;)
`SR(s193,adder_16bit component_179(mult_3[1], mult_3[2],        sum_3[1]); ,assign sum_3[1]=0;)
`SR(s194,adder_16bit component_180(mult_3[3], mult_3[4],        sum_3[2]); ,assign sum_3[2]=0;)
`SR(s195,adder_16bit component_181(mult_3[5], mult_3[6],        sum_3[3]); ,assign sum_3[3]=0;)
`SR(s196,adder_16bit component_182(mult_3[7], mult_3[8],        sum_3[4]); ,assign sum_3[4]=0;)
`SR(s197,adder_16bit component_183(mult_3[9], mult_3[10],       sum_3[5]); ,assign sum_3[5]=0;)
`SR(s198,adder_16bit component_184(mult_3[11], mult_3[12],      sum_3[6]); ,assign sum_3[6]=0;)
`SR(s199,adder_16bit component_185(mult_3[13], mult_3[14],      sum_3[7]); ,assign sum_3[7]=0;)
`SR(s200,adder_16bit component_186(mult_3[15], mult_3[16],      sum_3[8]); ,assign sum_3[8]=0;)
`SR(s201,adder_16bit component_187(mult_3[17], mult_3[18],      sum_3[9]); ,assign sum_3[9]=0;)
`SR(s202,adder_16bit component_188(sum_3[1], sum_3[2],         sum_3[10]); ,assign sum_3[10]=0;)
`SR(s203,adder_16bit component_189(sum_3[3], sum_3[4],         sum_3[11]); ,assign sum_3[11]=0;)
`SR(s204,adder_16bit component_190(sum_3[5], sum_3[6],         sum_3[12]); ,assign sum_3[12]=0;)
`SR(s205,adder_16bit component_191(sum_3[7], sum_3[8],         sum_3[13]); ,assign sum_3[13]=0;)
`SR(s206,adder_16bit component_192(sum_3[10], sum_3[11],       sum_3[14]); ,assign sum_3[14]=0;)
`SR(s207,adder_16bit component_193(sum_3[12], sum_3[13],       sum_3[15]); ,assign sum_3[15]=0;)
`SR(s208,adder_16bit component_194(sum_3[15], sum_3[9],        sum_3[16]); ,assign sum_3[16]=0;)
`SR(s209,adder_16bit component_195(sum_3[14], b3_0,            sum_3[17]); ,assign sum_3[17]=0;)
`SR(s210,adder_16bit component_196(sum_3[15], b3_1,            sum_3[18]); ,assign sum_3[18]=0;)
`SR(s211,adder_16bit component_197(sum_3[16], b3_2,            sum_3[19]); ,assign sum_3[19]=0;)

`SR(s212,register reg_l3_1(Reset, clk, sum_3[17],               reg_l3_out[1]);, assign reg_l3_out[1]=0;)
`SR(s213,register reg_l3_2(Reset, clk, sum_3[18],               reg_l3_out[2]);, assign reg_l3_out[2]=0;)
`SR(s214,register reg_l3_3(Reset, clk, sum_3[19],               reg_l3_out[3]);, assign reg_l3_out[3]=0;)



// Module for Softmax lookup:
`SR(s215,SOFTMAX SOFTMAX_instance(.Reset(Reset), .clk(clk), .l3_in_1(reg_l3_out[1]), .l3_in_2(reg_l3_out[2]), .l3_in_3(reg_l3_out[3]), .l3_out_1(layer3_output[1]), .l3_out_2(layer3_output[2]), .l3_out_3(layer3_output[3]));, assign layer3_output[1]=0; assign layer3_output[2]=0; assign layer3_output[3]=0;)


`SR(s216,FINDMAX FINDMAX_instance(.Reset(Reset), .clk(clk), .in_1(layer3_output[1]), .in_2(layer3_output[2]), .in_3(layer3_output[3]), .out(output_label_tmp));, assign output_label_tmp=0;)

`SR(s217,register reg_out(Reset, clk, output_label_tmp, out_temp);, assign out_temp=0;)

// Getting output_label:
`SR(s218,assign result = out_temp; , assign result=0;)

endmodule
