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
`CS(cs0,mul16u_exact,`SUB_cs0) component_01(a, W1_0_0, mult_1[1]);
`CS(cs1,mul16u_exact,`SUB_cs1) component_02(b, W1_1_0, mult_1[2]);
`CS(cs2,mul16u_exact,`SUB_cs2) component_03(c, W1_2_0, mult_1[3]);
`CS(cs3,mul16u_exact,`SUB_cs3) component_04(d, W1_3_0, mult_1[4]);
`CS(cs4,mul16u_exact,`SUB_cs4) component_05(a, W1_0_1, mult_1[5]);
`CS(cs5,mul16u_exact,`SUB_cs5) component_06(b, W1_1_1, mult_1[6]);
`CS(cs6,mul16u_exact,`SUB_cs6) component_07(c, W1_2_1, mult_1[7]);
`CS(cs7,mul16u_exact,`SUB_cs7) component_08(d, W1_3_1, mult_1[8]);
`CS(cs8,mul16u_exact,`SUB_cs8) component_09(a, W1_0_2, mult_1[9]);
`CS(cs9,mul16u_exact,`SUB_cs9) component_10(b, W1_1_2, mult_1[10]);
`CS(cs10,mul16u_exact,`SUB_cs10) component_11(c, W1_2_2, mult_1[11]);
`CS(cs11,mul16u_exact,`SUB_cs11) component_12(d, W1_3_2, mult_1[12]);
`CS(cs12,mul16u_exact,`SUB_cs12) component_13(a, W1_0_3, mult_1[13]);
`CS(cs13,mul16u_exact,`SUB_cs13) component_14(b, W1_1_3, mult_1[14]);
`CS(cs14,mul16u_exact,`SUB_cs14) component_15(c, W1_2_3, mult_1[15]);
`CS(cs15,mul16u_exact,`SUB_cs15) component_16(d, W1_3_3, mult_1[16]);
`CS(cs16,mul16u_exact,`SUB_cs16) component_17(a, W1_0_4, mult_1[17]);
`CS(cs17,mul16u_exact,`SUB_cs17) component_18(b, W1_1_4, mult_1[18]);
`CS(cs18,mul16u_exact,`SUB_cs18) component_19(c, W1_2_4, mult_1[19]);
`CS(cs19,mul16u_exact,`SUB_cs19) component_20(d, W1_3_4, mult_1[20]);
`CS(cs20,mul16u_exact,`SUB_cs20) component_21(a, W1_0_5, mult_1[21]);
`CS(cs21,mul16u_exact,`SUB_cs21) component_22(b, W1_1_5, mult_1[22]);
`CS(cs22,mul16u_exact,`SUB_cs22) component_23(c, W1_2_5, mult_1[23]);
`CS(cs23,mul16u_exact,`SUB_cs23) component_24(d, W1_3_5, mult_1[24]);
`CS(cs24,mul16u_exact,`SUB_cs24) component_25(a, W1_0_6, mult_1[25]);
`CS(cs25,mul16u_exact,`SUB_cs25) component_26(b, W1_1_6, mult_1[26]);
`CS(cs26,mul16u_exact,`SUB_cs26) component_27(c, W1_2_6, mult_1[27]);
`CS(cs27,mul16u_exact,`SUB_cs27) component_28(d, W1_3_6, mult_1[28]);
`CS(cs28,mul16u_exact,`SUB_cs28) component_29(a, W1_0_7, mult_1[29]);
`CS(cs29,mul16u_exact,`SUB_cs29) component_30(b, W1_1_7, mult_1[30]);
`CS(cs30,mul16u_exact,`SUB_cs30) component_31(c, W1_2_7, mult_1[31]);
`CS(cs31,mul16u_exact,`SUB_cs31) component_32(d, W1_3_7, mult_1[32]);

// Adders instantiation.
`CS(cs32,adder_16bit,`SUB_cs32) component_33(mult_1[1], mult_1[2], sum_1[1]);
`CS(cs33,adder_16bit,`SUB_cs33) component_34(mult_1[3], mult_1[4], sum_1[2]);
`CS(cs34,adder_16bit,`SUB_cs34) component_35(mult_1[5], mult_1[6], sum_1[3]);
`CS(cs35,adder_16bit,`SUB_cs35) component_36(mult_1[7], mult_1[8], sum_1[4]);
`CS(cs36,adder_16bit,`SUB_cs36) component_37(mult_1[9], mult_1[10], sum_1[5]);
`CS(cs37,adder_16bit,`SUB_cs37) component_38(mult_1[11], mult_1[12], sum_1[6]);
`CS(cs38,adder_16bit,`SUB_cs38) component_39(mult_1[13], mult_1[14], sum_1[7]);
`CS(cs39,adder_16bit,`SUB_cs39) component_40(mult_1[15], mult_1[16], sum_1[8]);
`CS(cs40,adder_16bit,`SUB_cs40) component_41(mult_1[17], mult_1[18], sum_1[9]);
`CS(cs41,adder_16bit,`SUB_cs41) component_42(mult_1[19], mult_1[20], sum_1[10]);
`CS(cs42,adder_16bit,`SUB_cs42) component_43(mult_1[21], mult_1[22], sum_1[11]);
`CS(cs43,adder_16bit,`SUB_cs43) component_44(mult_1[23], mult_1[24], sum_1[12]);
`CS(cs44,adder_16bit,`SUB_cs44) component_45(mult_1[25], mult_1[26], sum_1[13]);
`CS(cs45,adder_16bit,`SUB_cs45) component_46(mult_1[27], mult_1[28], sum_1[14]);
`CS(cs46,adder_16bit,`SUB_cs46) component_47(mult_1[29], mult_1[30], sum_1[15]);
`CS(cs47,adder_16bit,`SUB_cs47) component_48(mult_1[31], mult_1[32], sum_1[16]);

`CS(cs48,adder_16bit,`SUB_cs48) component_49(sum_1[1], sum_1[2], sum_1[17]);
`CS(cs49,adder_16bit,`SUB_cs49) component_50(sum_1[3], sum_1[4], sum_1[18]);
`CS(cs50,adder_16bit,`SUB_cs50) component_51(sum_1[5], sum_1[6], sum_1[19]);
`CS(cs51,adder_16bit,`SUB_cs51) component_52(sum_1[7], sum_1[8], sum_1[20]);
`CS(cs52,adder_16bit,`SUB_cs52) component_53(sum_1[9], sum_1[10], sum_1[21]);
`CS(cs53,adder_16bit,`SUB_cs53) component_54(sum_1[11], sum_1[12], sum_1[22]);
`CS(cs54,adder_16bit,`SUB_cs54) component_55(sum_1[13], sum_1[14], sum_1[23]);
`CS(cs55,adder_16bit,`SUB_cs55) component_56(sum_1[15], sum_1[16], sum_1[24]);

`CS(cs56,adder_16bit,`SUB_cs56) component_57(sum_1[17], b1_0, sum_1[25]);
`CS(cs57,adder_16bit,`SUB_cs57) component_58(sum_1[18], b1_1, sum_1[26]);
`CS(cs58,adder_16bit,`SUB_cs58) component_59(sum_1[19], b1_2, sum_1[27]);
`CS(cs59,adder_16bit,`SUB_cs59) component_60(sum_1[20], b1_3, sum_1[28]);
`CS(cs60,adder_16bit,`SUB_cs60) component_61(sum_1[21], b1_4, sum_1[29]);
`CS(cs61,adder_16bit,`SUB_cs61) component_62(sum_1[22], b1_5, sum_1[30]);
`CS(cs62,adder_16bit,`SUB_cs62) component_63(sum_1[23], b1_6, sum_1[31]);
`CS(cs63,adder_16bit,`SUB_cs63) component_64(sum_1[24], b1_7, sum_1[32]);


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
`CS(cs64,mul16u_exact,`SUB_cs64) component_65(layer1_output[1], W2_0_0, mult_2[1]);
`CS(cs65,mul16u_exact,`SUB_cs65) component_66(layer1_output[2], W2_1_0, mult_2[2]);
`CS(cs66,mul16u_exact,`SUB_cs66) component_67(layer1_output[3], W2_2_0, mult_2[3]);
`CS(cs67,mul16u_exact,`SUB_cs67) component_68(layer1_output[4], W2_3_0, mult_2[4]);
`CS(cs68,mul16u_exact,`SUB_cs68) component_69(layer1_output[5], W2_4_0, mult_2[5]);
`CS(cs69,mul16u_exact,`SUB_cs69) component_70(layer1_output[6], W2_5_0, mult_2[6]);
`CS(cs70,mul16u_exact,`SUB_cs70) component_71(layer1_output[7], W2_6_0, mult_2[7]);
`CS(cs71,mul16u_exact,`SUB_cs71) component_72(layer1_output[8], W2_7_0, mult_2[8]);
`CS(cs72,mul16u_exact,`SUB_cs72) component_73(layer1_output[1], W2_0_1, mult_2[9]);
`CS(cs73,mul16u_exact,`SUB_cs73) component_74(layer1_output[2], W2_1_1, mult_2[10]);
`CS(cs74,mul16u_exact,`SUB_cs74) component_75(layer1_output[3], W2_2_1, mult_2[11]);
`CS(cs75,mul16u_exact,`SUB_cs75) component_76(layer1_output[4], W2_3_1, mult_2[12]);
`CS(cs76,mul16u_exact,`SUB_cs76) component_77(layer1_output[5], W2_4_1, mult_2[13]);
`CS(cs77,mul16u_exact,`SUB_cs77) component_78(layer1_output[6], W2_5_1, mult_2[14]);
`CS(cs78,mul16u_exact,`SUB_cs78) component_79(layer1_output[7], W2_6_1, mult_2[15]);
`CS(cs79,mul16u_exact,`SUB_cs79) component_80(layer1_output[8], W2_7_1, mult_2[16]);
`CS(cs80,mul16u_exact,`SUB_cs80) component_81(layer1_output[1], W2_0_2, mult_2[17]);
`CS(cs81,mul16u_exact,`SUB_cs81) component_82(layer1_output[2], W2_1_2, mult_2[18]);
`CS(cs82,mul16u_exact,`SUB_cs82) component_83(layer1_output[3], W2_2_2, mult_2[19]);
`CS(cs83,mul16u_exact,`SUB_cs83) component_84(layer1_output[4], W2_3_2, mult_2[20]);
`CS(cs84,mul16u_exact,`SUB_cs84) component_85(layer1_output[5], W2_4_2, mult_2[21]);
`CS(cs85,mul16u_exact,`SUB_cs85) component_86(layer1_output[6], W2_5_2, mult_2[22]);
`CS(cs86,mul16u_exact,`SUB_cs86) component_87(layer1_output[7], W2_6_2, mult_2[23]);
`CS(cs87,mul16u_exact,`SUB_cs87) component_88(layer1_output[8], W2_7_2, mult_2[24]);
`CS(cs88,mul16u_exact,`SUB_cs88) component_89(layer1_output[1], W2_0_3, mult_2[25]);
`CS(cs89,mul16u_exact,`SUB_cs89) component_90(layer1_output[2], W2_1_3, mult_2[26]);
`CS(cs90,mul16u_exact,`SUB_cs90) component_91(layer1_output[3], W2_2_3, mult_2[27]);
`CS(cs91,mul16u_exact,`SUB_cs91) component_92(layer1_output[4], W2_3_3, mult_2[28]);
`CS(cs92,mul16u_exact,`SUB_cs92) component_93(layer1_output[5], W2_4_3, mult_2[29]);
`CS(cs93,mul16u_exact,`SUB_cs93) component_94(layer1_output[6], W2_5_3, mult_2[30]);
`CS(cs94,mul16u_exact,`SUB_cs94) component_95(layer1_output[7], W2_6_3, mult_2[31]);
`CS(cs95,mul16u_exact,`SUB_cs95) component_96(layer1_output[8], W2_7_3, mult_2[32]);
`CS(cs96,mul16u_exact,`SUB_cs96) component_97(layer1_output[1], W2_0_4, mult_2[33]);
`CS(cs97,mul16u_exact,`SUB_cs97) component_98(layer1_output[2], W2_1_4, mult_2[34]);
`CS(cs98,mul16u_exact,`SUB_cs98) component_99(layer1_output[3], W2_2_4, mult_2[35]);
`CS(cs99,mul16u_exact,`SUB_cs99) component_100(layer1_output[4], W2_3_4, mult_2[36]);
`CS(cs100,mul16u_exact,`SUB_cs100) component_101(layer1_output[5], W2_4_4, mult_2[37]);
`CS(cs101,mul16u_exact,`SUB_cs101) component_102(layer1_output[6], W2_5_4, mult_2[38]);
`CS(cs102,mul16u_exact,`SUB_cs102) component_103(layer1_output[7], W2_6_4, mult_2[39]);
`CS(cs103,mul16u_exact,`SUB_cs103) component_104(layer1_output[8], W2_7_4, mult_2[40]);
`CS(cs104,mul16u_exact,`SUB_cs104) component_105(layer1_output[1], W2_0_5, mult_2[41]);
`CS(cs105,mul16u_exact,`SUB_cs105) component_106(layer1_output[2], W2_1_5, mult_2[42]);
`CS(cs106,mul16u_exact,`SUB_cs106) component_107(layer1_output[3], W2_2_5, mult_2[43]);
`CS(cs107,mul16u_exact,`SUB_cs107) component_108(layer1_output[4], W2_3_5, mult_2[44]);
`CS(cs108,mul16u_exact,`SUB_cs108) component_109(layer1_output[5], W2_4_5, mult_2[45]);
`CS(cs109,mul16u_exact,`SUB_cs109) component_110(layer1_output[6], W2_5_5, mult_2[46]);
`CS(cs110,mul16u_exact,`SUB_cs110) component_111(layer1_output[7], W2_6_5, mult_2[47]);
`CS(cs111,mul16u_exact,`SUB_cs111) component_112(layer1_output[8], W2_7_5, mult_2[48]);

// Adders instantiation.
`CS(cs112,adder_16bit,`SUB_cs112) component_113(mult_2[1], mult_2[2], sum_2[1]);
`CS(cs113,adder_16bit,`SUB_cs113) component_114(mult_2[3], mult_2[4], sum_2[2]);
`CS(cs114,adder_16bit,`SUB_cs114) component_115(mult_2[5], mult_2[6], sum_2[3]);
`CS(cs115,adder_16bit,`SUB_cs115) component_116(mult_2[7], mult_2[8], sum_2[4]);
`CS(cs116,adder_16bit,`SUB_cs116) component_117(mult_2[9], mult_2[10], sum_2[5]);
`CS(cs117,adder_16bit,`SUB_cs117) component_118(mult_2[11], mult_2[12], sum_2[6]);
`CS(cs118,adder_16bit,`SUB_cs118) component_119(mult_2[13], mult_2[14], sum_2[7]);
`CS(cs119,adder_16bit,`SUB_cs119) component_120(mult_2[15], mult_2[16], sum_2[8]);
`CS(cs120,adder_16bit,`SUB_cs120) component_121(mult_2[17], mult_2[18], sum_2[9]);
`CS(cs121,adder_16bit,`SUB_cs121) component_122(mult_2[19], mult_2[20], sum_2[10]);
`CS(cs122,adder_16bit,`SUB_cs122) component_123(mult_2[21], mult_2[22], sum_2[11]);
`CS(cs123,adder_16bit,`SUB_cs123) component_124(mult_2[23], mult_2[24], sum_2[12]);
`CS(cs124,adder_16bit,`SUB_cs124) component_125(mult_2[25], mult_2[26], sum_2[13]);
`CS(cs125,adder_16bit,`SUB_cs125) component_126(mult_2[27], mult_2[28], sum_2[14]);
`CS(cs126,adder_16bit,`SUB_cs126) component_127(mult_2[29], mult_2[30], sum_2[15]);
`CS(cs127,adder_16bit,`SUB_cs127) component_128(mult_2[31], mult_2[32], sum_2[16]);
`CS(cs128,adder_16bit,`SUB_cs128) component_129(mult_2[33], mult_2[34], sum_2[17]);
`CS(cs129,adder_16bit,`SUB_cs129) component_130(mult_2[35], mult_2[36], sum_2[18]);
`CS(cs130,adder_16bit,`SUB_cs130) component_131(mult_2[37], mult_2[38], sum_2[19]);
`CS(cs131,adder_16bit,`SUB_cs131) component_132(mult_2[39], mult_2[40], sum_2[20]);
`CS(cs132,adder_16bit,`SUB_cs132) component_133(mult_2[41], mult_2[42], sum_2[21]);
`CS(cs133,adder_16bit,`SUB_cs133) component_134(mult_2[43], mult_2[44], sum_2[22]);
`CS(cs134,adder_16bit,`SUB_cs134) component_135(mult_2[45], mult_2[46], sum_2[23]);
`CS(cs135,adder_16bit,`SUB_cs135) component_136(mult_2[47], mult_2[48], sum_2[24]);

`CS(cs136,adder_16bit,`SUB_cs136) component_137(sum_2[1], sum_2[2], sum_2[25]);
`CS(cs137,adder_16bit,`SUB_cs137) component_138(sum_2[3], sum_2[4], sum_2[26]);
`CS(cs138,adder_16bit,`SUB_cs138) component_139(sum_2[5], sum_2[6], sum_2[27]);
`CS(cs139,adder_16bit,`SUB_cs139) component_140(sum_2[7], sum_2[8], sum_2[28]);
`CS(cs140,adder_16bit,`SUB_cs140) component_141(sum_2[9], sum_2[10], sum_2[29]);
`CS(cs141,adder_16bit,`SUB_cs141) component_142(sum_2[11], sum_2[12], sum_2[30]);
`CS(cs142,adder_16bit,`SUB_cs142) component_143(sum_2[13], sum_2[14], sum_2[31]);
`CS(cs143,adder_16bit,`SUB_cs143) component_144(sum_2[15], sum_2[16], sum_2[32]);
`CS(cs144,adder_16bit,`SUB_cs144) component_145(sum_2[17], sum_2[18], sum_2[33]);
`CS(cs145,adder_16bit,`SUB_cs145) component_146(sum_2[19], sum_2[20], sum_2[34]);
`CS(cs146,adder_16bit,`SUB_cs146) component_147(sum_2[21], sum_2[22], sum_2[35]);
`CS(cs147,adder_16bit,`SUB_cs147) component_148(sum_2[23], sum_2[24], sum_2[36]);

`CS(cs148,adder_16bit,`SUB_cs148) component_149(sum_2[25], sum_2[26], sum_2[37]);
`CS(cs149,adder_16bit,`SUB_cs149) component_150(sum_2[27], sum_2[28], sum_2[38]);
`CS(cs150,adder_16bit,`SUB_cs150) component_151(sum_2[29], sum_2[30], sum_2[39]);
`CS(cs151,adder_16bit,`SUB_cs151) component_152(sum_2[31], sum_2[32], sum_2[40]);
`CS(cs152,adder_16bit,`SUB_cs152) component_153(sum_2[33], sum_2[34], sum_2[41]);
`CS(cs153,adder_16bit,`SUB_cs153) component_154(sum_2[35], sum_2[36], sum_2[42]);

`CS(cs154,adder_16bit,`SUB_cs154) component_155(sum_2[37], b2_0, sum_2[43]);
`CS(cs155,adder_16bit,`SUB_cs155) component_156(sum_2[38], b2_1, sum_2[44]);
`CS(cs156,adder_16bit,`SUB_cs156) component_157(sum_2[39], b2_2, sum_2[45]);
`CS(cs157,adder_16bit,`SUB_cs157) component_158(sum_2[40], b2_3, sum_2[46]);
`CS(cs158,adder_16bit,`SUB_cs158) component_159(sum_2[41], b2_4, sum_2[47]);
`CS(cs159,adder_16bit,`SUB_cs159) component_160(sum_2[42], b2_5, sum_2[48]);


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
`CS(cs160,mul16u_exact,`SUB_cs160) component_161(layer2_output[1], W3_0_0, mult_3[1]);
`CS(cs161,mul16u_exact,`SUB_cs161) component_162(layer2_output[2], W3_1_0, mult_3[2]);
`CS(cs162,mul16u_exact,`SUB_cs162) component_163(layer2_output[3], W3_2_0, mult_3[3]);
`CS(cs163,mul16u_exact,`SUB_cs163) component_164(layer2_output[4], W3_3_0, mult_3[4]);
`CS(cs164,mul16u_exact,`SUB_cs164) component_165(layer2_output[5], W3_4_0, mult_3[5]);
`CS(cs165,mul16u_exact,`SUB_cs165) component_166(layer2_output[6], W3_5_0, mult_3[6]);
`CS(cs166,mul16u_exact,`SUB_cs166) component_167(layer2_output[1], W3_0_1, mult_3[7]);
`CS(cs167,mul16u_exact,`SUB_cs167) component_168(layer2_output[2], W3_1_1, mult_3[8]);
`CS(cs168,mul16u_exact,`SUB_cs168) component_169(layer2_output[3], W3_2_1, mult_3[9]);
`CS(cs169,mul16u_exact,`SUB_cs169) component_170(layer2_output[4], W3_3_1, mult_3[10]);
`CS(cs170,mul16u_exact,`SUB_cs170) component_171(layer2_output[5], W3_4_1, mult_3[11]);
`CS(cs171,mul16u_exact,`SUB_cs171) component_172(layer2_output[6], W3_5_1, mult_3[12]);
`CS(cs172,mul16u_exact,`SUB_cs172) component_173(layer2_output[1], W3_0_2, mult_3[13]);
`CS(cs173,mul16u_exact,`SUB_cs173) component_174(layer2_output[2], W3_1_2, mult_3[14]);
`CS(cs174,mul16u_exact,`SUB_cs174) component_175(layer2_output[3], W3_2_2, mult_3[15]);
`CS(cs175,mul16u_exact,`SUB_cs175) component_176(layer2_output[4], W3_3_2, mult_3[16]);
`CS(cs176,mul16u_exact,`SUB_cs176) component_177(layer2_output[5], W3_4_2, mult_3[17]);
`CS(cs177,mul16u_exact,`SUB_cs177) component_178(layer2_output[6], W3_5_2, mult_3[18]);

// Adders instantiation.
`CS(cs178,adder_16bit,`SUB_cs178) component_179(mult_3[1], mult_3[2], sum_3[1]);
`CS(cs179,adder_16bit,`SUB_cs179) component_180(mult_3[3], mult_3[4], sum_3[2]);
`CS(cs180,adder_16bit,`SUB_cs180) component_181(mult_3[5], mult_3[6], sum_3[3]);
`CS(cs181,adder_16bit,`SUB_cs181) component_182(mult_3[7], mult_3[8], sum_3[4]);
`CS(cs182,adder_16bit,`SUB_cs182) component_183(mult_3[9], mult_3[10], sum_3[5]);
`CS(cs183,adder_16bit,`SUB_cs183) component_184(mult_3[11], mult_3[12], sum_3[6]);
`CS(cs184,adder_16bit,`SUB_cs184) component_185(mult_3[13], mult_3[14], sum_3[7]);
`CS(cs185,adder_16bit,`SUB_cs185) component_186(mult_3[15], mult_3[16], sum_3[8]);
`CS(cs186,adder_16bit,`SUB_cs186) component_187(mult_3[17], mult_3[18], sum_3[9]);

`CS(cs187,adder_16bit,`SUB_cs187) component_188(sum_3[1], sum_3[2], sum_3[10]);
`CS(cs188,adder_16bit,`SUB_cs188) component_189(sum_3[3], sum_3[4], sum_3[11]);
`CS(cs189,adder_16bit,`SUB_cs189) component_190(sum_3[5], sum_3[6], sum_3[12]);
`CS(cs190,adder_16bit,`SUB_cs190) component_191(sum_3[7], sum_3[8], sum_3[13]);

`CS(cs191,adder_16bit,`SUB_cs191) component_192(sum_3[10], sum_3[11], sum_3[14]);
`CS(cs192,adder_16bit,`SUB_cs192) component_193(sum_3[12], sum_3[13], sum_3[15]);

`CS(cs193,adder_16bit,`SUB_cs193) component_194(sum_3[15], sum_3[9], sum_3[16]);

`CS(cs194,adder_16bit,`SUB_cs194) component_195(sum_3[14], b3_0, sum_3[17]);
`CS(cs195,adder_16bit,`SUB_cs195) component_196(sum_3[15], b3_1, sum_3[18]);
`CS(cs196,adder_16bit,`SUB_cs196) component_197(sum_3[16], b3_2, sum_3[19]);

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
