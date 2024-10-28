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
mul16u_exact component_01(`SAC(br0,a,`MASK_br0), W1_0_0, mult_1[1]);
mul16u_exact component_02(`SAC(br1,b,`MASK_br1), W1_1_0, mult_1[2]);
mul16u_exact component_03(`SAC(br2,c,`MASK_br2), W1_2_0, mult_1[3]);
mul16u_exact component_04(`SAC(br3,d,`MASK_br3), W1_3_0, mult_1[4]);
mul16u_exact component_05(`SAC(br4,a,`MASK_br4), W1_0_1, mult_1[5]);
mul16u_exact component_06(`SAC(br5,b,`MASK_br5), W1_1_1, mult_1[6]);
mul16u_exact component_07(`SAC(br6,c,`MASK_br6), W1_2_1, mult_1[7]);
mul16u_exact component_08(`SAC(br7,d,`MASK_br7), W1_3_1, mult_1[8]);
mul16u_exact component_09(`SAC(br8,a,`MASK_br8), W1_0_2, mult_1[9]);
mul16u_exact component_10(`SAC(br9,b,`MASK_br9), W1_1_2, mult_1[10]);
mul16u_exact component_11(`SAC(br10,c,`MASK_br10), W1_2_2, mult_1[11]);
mul16u_exact component_12(`SAC(br11,d,`MASK_br11), W1_3_2, mult_1[12]);
mul16u_exact component_13(`SAC(br12,a,`MASK_br12), W1_0_3, mult_1[13]);
mul16u_exact component_14(`SAC(br13,b,`MASK_br13), W1_1_3, mult_1[14]);
mul16u_exact component_15(`SAC(br14,c,`MASK_br14), W1_2_3, mult_1[15]);
mul16u_exact component_16(`SAC(br15,d,`MASK_br15), W1_3_3, mult_1[16]);
mul16u_exact component_17(`SAC(br16,a,`MASK_br16), W1_0_4, mult_1[17]);
mul16u_exact component_18(`SAC(br17,b,`MASK_br17), W1_1_4, mult_1[18]);
mul16u_exact component_19(`SAC(br18,c,`MASK_br18), W1_2_4, mult_1[19]);
mul16u_exact component_20(`SAC(br19,d,`MASK_br19), W1_3_4, mult_1[20]);
mul16u_exact component_21(`SAC(br20,a,`MASK_br20), W1_0_5, mult_1[21]);
mul16u_exact component_22(`SAC(br21,b,`MASK_br21), W1_1_5, mult_1[22]);
mul16u_exact component_23(`SAC(br22,c,`MASK_br22), W1_2_5, mult_1[23]);
mul16u_exact component_24(`SAC(br23,d,`MASK_br23), W1_3_5, mult_1[24]);
mul16u_exact component_25(`SAC(br24,a,`MASK_br24), W1_0_6, mult_1[25]);
mul16u_exact component_26(`SAC(br25,b,`MASK_br25), W1_1_6, mult_1[26]);
mul16u_exact component_27(`SAC(br26,c,`MASK_br26), W1_2_6, mult_1[27]);
mul16u_exact component_28(`SAC(br27,d,`MASK_br27), W1_3_6, mult_1[28]);
mul16u_exact component_29(`SAC(br28,a,`MASK_br28), W1_0_7, mult_1[29]);
mul16u_exact component_30(`SAC(br29,b,`MASK_br29), W1_1_7, mult_1[30]);
mul16u_exact component_31(`SAC(br30,c,`MASK_br30), W1_2_7, mult_1[31]);
mul16u_exact component_32(`SAC(br31,d,`MASK_br31), W1_3_7, mult_1[32]);

// Adders instantiation.
adder_16bit component_33(`SAC(br32,mult_1[1],`MASK_br32), `SAC(br33,mult_1[2],`MASK_br33), sum_1[1]);
adder_16bit component_34(`SAC(br34,mult_1[3],`MASK_br34), `SAC(br35,mult_1[4],`MASK_br35), sum_1[2]);
adder_16bit component_35(`SAC(br36,mult_1[5],`MASK_br36), `SAC(br37,mult_1[6],`MASK_br37), sum_1[3]);
adder_16bit component_36(`SAC(br38,mult_1[7],`MASK_br38), `SAC(br39,mult_1[8],`MASK_br39), sum_1[4]);
adder_16bit component_37(`SAC(br40,mult_1[9],`MASK_br40), `SAC(br41,mult_1[10],`MASK_br41), sum_1[5]);
adder_16bit component_38(`SAC(br42,mult_1[11],`MASK_br42), `SAC(br43,mult_1[12],`MASK_br43), sum_1[6]);
adder_16bit component_39(`SAC(br44,mult_1[13],`MASK_br44), `SAC(br45,mult_1[14],`MASK_br45), sum_1[7]);
adder_16bit component_40(`SAC(br46,mult_1[15],`MASK_br46), `SAC(br47,mult_1[16],`MASK_br47), sum_1[8]);
adder_16bit component_41(`SAC(br48,mult_1[17],`MASK_br48), `SAC(br49,mult_1[18],`MASK_br49), sum_1[9]);
adder_16bit component_42(`SAC(br50,mult_1[19],`MASK_br50), `SAC(br51,mult_1[20],`MASK_br51), sum_1[10]);
adder_16bit component_43(`SAC(br52,mult_1[21],`MASK_br52), `SAC(br53,mult_1[22],`MASK_br53), sum_1[11]);
adder_16bit component_44(`SAC(br54,mult_1[23],`MASK_br54), `SAC(br55,mult_1[24],`MASK_br55), sum_1[12]);
adder_16bit component_45(`SAC(br56,mult_1[25],`MASK_br56), `SAC(br57,mult_1[26],`MASK_br57), sum_1[13]);
adder_16bit component_46(`SAC(br58,mult_1[27],`MASK_br58), `SAC(br59,mult_1[28],`MASK_br59), sum_1[14]);
adder_16bit component_47(`SAC(br60,mult_1[29],`MASK_br60), `SAC(br61,mult_1[30],`MASK_br61), sum_1[15]);
adder_16bit component_48(`SAC(br62,mult_1[31],`MASK_br62), `SAC(br63,mult_1[32],`MASK_br63), sum_1[16]);

adder_16bit component_49(`SAC(br64,sum_1[1],`MASK_br64), `SAC(br65,sum_1[2],`MASK_br65), sum_1[17]);
adder_16bit component_50(`SAC(br66,sum_1[3],`MASK_br66), `SAC(br67,sum_1[4],`MASK_br67), sum_1[18]);
adder_16bit component_51(`SAC(br68,sum_1[5],`MASK_br68), `SAC(br69,sum_1[6],`MASK_br69), sum_1[19]);
adder_16bit component_52(`SAC(br70,sum_1[7],`MASK_br70), `SAC(br71,sum_1[8],`MASK_br71), sum_1[20]);
adder_16bit component_53(`SAC(br72,sum_1[9],`MASK_br72), `SAC(br73,sum_1[10],`MASK_br73), sum_1[21]);
adder_16bit component_54(`SAC(br74,sum_1[11],`MASK_br74), `SAC(br75,sum_1[12],`MASK_br75), sum_1[22]);
adder_16bit component_55(`SAC(br76,sum_1[13],`MASK_br76), `SAC(br77,sum_1[14],`MASK_br77), sum_1[23]);
adder_16bit component_56(`SAC(br78,sum_1[15],`MASK_br78), `SAC(br79,sum_1[16],`MASK_br79), sum_1[24]);

adder_16bit component_57(`SAC(br80,sum_1[17],`MASK_br80), b1_0, sum_1[25]);
adder_16bit component_58(`SAC(br81,sum_1[18],`MASK_br81), b1_1, sum_1[26]);
adder_16bit component_59(`SAC(br82,sum_1[19],`MASK_br82), b1_2, sum_1[27]);
adder_16bit component_60(`SAC(br83,sum_1[20],`MASK_br83), b1_3, sum_1[28]);
adder_16bit component_61(`SAC(br84,sum_1[21],`MASK_br84), b1_4, sum_1[29]);
adder_16bit component_62(`SAC(br85,sum_1[22],`MASK_br85), b1_5, sum_1[30]);
adder_16bit component_63(`SAC(br86,sum_1[23],`MASK_br86), b1_6, sum_1[31]);
adder_16bit component_64(`SAC(br87,sum_1[24],`MASK_br87), b1_7, sum_1[32]);


register reg_l1_1(Reset, clk, `SAC(br88,sum_1[25],`MASK_br88), reg_l1_out[1]);
register reg_l1_2(Reset, clk, `SAC(br89,sum_1[26],`MASK_br89), reg_l1_out[2]);
register reg_l1_3(Reset, clk, `SAC(br90,sum_1[27],`MASK_br90), reg_l1_out[3]);
register reg_l1_4(Reset, clk, `SAC(br91,sum_1[28],`MASK_br91), reg_l1_out[4]);
register reg_l1_5(Reset, clk, `SAC(br92,sum_1[29],`MASK_br92), reg_l1_out[5]);
register reg_l1_6(Reset, clk, `SAC(br93,sum_1[30],`MASK_br93), reg_l1_out[6]);
register reg_l1_7(Reset, clk, `SAC(br94,sum_1[31],`MASK_br94), reg_l1_out[7]);
register reg_l1_8(Reset, clk, `SAC(br95,sum_1[32],`MASK_br95), reg_l1_out[8]);

// Module for Relu lookup:
RELU_1 RELU1_instance(.Reset(Reset), .clk(clk), .in_1(`SAC(br96,reg_l1_out[1],`MASK_br96)), .in_2(`SAC(br97,reg_l1_out[2],`MASK_br97)), .in_3(`SAC(br98,reg_l1_out[3],`MASK_br98)), .in_4(`SAC(br99,reg_l1_out[4],`MASK_br99)), .in_5(`SAC(br100,reg_l1_out[5],`MASK_br100)), .in_6(`SAC(br101,reg_l1_out[6],`MASK_br101)), .in_7(`SAC(br102,reg_l1_out[7],`MASK_br102)), .in_8(`SAC(br103,reg_l1_out[8],`MASK_br103)), .out_1(layer1_output[1]), .out_2(layer1_output[2]), .out_3(layer1_output[3]), .out_4(layer1_output[4]), .out_5(layer1_output[5]), .out_6(layer1_output[6]), .out_7(layer1_output[7]), .out_8(layer1_output[8]));


// Layer 2 computations:

// Multipliers instantiation.
mul16u_exact component_65(`SAC(br104,layer1_output[1],`MASK_br104), W2_0_0, mult_2[1]);
mul16u_exact component_66(`SAC(br105,layer1_output[2],`MASK_br105), W2_1_0, mult_2[2]);
mul16u_exact component_67(`SAC(br106,layer1_output[3],`MASK_br106), W2_2_0, mult_2[3]);
mul16u_exact component_68(`SAC(br107,layer1_output[4],`MASK_br107), W2_3_0, mult_2[4]);
mul16u_exact component_69(`SAC(br108,layer1_output[5],`MASK_br108), W2_4_0, mult_2[5]);
mul16u_exact component_70(`SAC(br109,layer1_output[6],`MASK_br109), W2_5_0, mult_2[6]);
mul16u_exact component_71(`SAC(br110,layer1_output[7],`MASK_br110), W2_6_0, mult_2[7]);
mul16u_exact component_72(`SAC(br111,layer1_output[8],`MASK_br111), W2_7_0, mult_2[8]);
mul16u_exact component_73(`SAC(br112,layer1_output[1],`MASK_br112), W2_0_1, mult_2[9]);
mul16u_exact component_74(`SAC(br113,layer1_output[2],`MASK_br113), W2_1_1, mult_2[10]);
mul16u_exact component_75(`SAC(br114,layer1_output[3],`MASK_br114), W2_2_1, mult_2[11]);
mul16u_exact component_76(`SAC(br115,layer1_output[4],`MASK_br115), W2_3_1, mult_2[12]);
mul16u_exact component_77(`SAC(br116,layer1_output[5],`MASK_br116), W2_4_1, mult_2[13]);
mul16u_exact component_78(`SAC(br117,layer1_output[6],`MASK_br117), W2_5_1, mult_2[14]);
mul16u_exact component_79(`SAC(br118,layer1_output[7],`MASK_br118), W2_6_1, mult_2[15]);
mul16u_exact component_80(`SAC(br119,layer1_output[8],`MASK_br119), W2_7_1, mult_2[16]);
mul16u_exact component_81(`SAC(br120,layer1_output[1],`MASK_br120), W2_0_2, mult_2[17]);
mul16u_exact component_82(`SAC(br121,layer1_output[2],`MASK_br121), W2_1_2, mult_2[18]);
mul16u_exact component_83(`SAC(br122,layer1_output[3],`MASK_br122), W2_2_2, mult_2[19]);
mul16u_exact component_84(`SAC(br123,layer1_output[4],`MASK_br123), W2_3_2, mult_2[20]);
mul16u_exact component_85(`SAC(br124,layer1_output[5],`MASK_br124), W2_4_2, mult_2[21]);
mul16u_exact component_86(`SAC(br125,layer1_output[6],`MASK_br125), W2_5_2, mult_2[22]);
mul16u_exact component_87(`SAC(br126,layer1_output[7],`MASK_br126), W2_6_2, mult_2[23]);
mul16u_exact component_88(`SAC(br127,layer1_output[8],`MASK_br127), W2_7_2, mult_2[24]);
mul16u_exact component_89(`SAC(br128,layer1_output[1],`MASK_br128), W2_0_3, mult_2[25]);
mul16u_exact component_90(`SAC(br129,layer1_output[2],`MASK_br129), W2_1_3, mult_2[26]);
mul16u_exact component_91(`SAC(br130,layer1_output[3],`MASK_br130), W2_2_3, mult_2[27]);
mul16u_exact component_92(`SAC(br131,layer1_output[4],`MASK_br131), W2_3_3, mult_2[28]);
mul16u_exact component_93(`SAC(br132,layer1_output[5],`MASK_br132), W2_4_3, mult_2[29]);
mul16u_exact component_94(`SAC(br133,layer1_output[6],`MASK_br133), W2_5_3, mult_2[30]);
mul16u_exact component_95(`SAC(br134,layer1_output[7],`MASK_br134), W2_6_3, mult_2[31]);
mul16u_exact component_96(`SAC(br135,layer1_output[8],`MASK_br135), W2_7_3, mult_2[32]);
mul16u_exact component_97(`SAC(br136,layer1_output[1],`MASK_br136), W2_0_4, mult_2[33]);
mul16u_exact component_98(`SAC(br137,layer1_output[2],`MASK_br137), W2_1_4, mult_2[34]);
mul16u_exact component_99(`SAC(br138,layer1_output[3],`MASK_br138), W2_2_4, mult_2[35]);
mul16u_exact component_100(`SAC(br139,layer1_output[4],`MASK_br139), W2_3_4, mult_2[36]);
mul16u_exact component_101(`SAC(br140,layer1_output[5],`MASK_br140), W2_4_4, mult_2[37]);
mul16u_exact component_102(`SAC(br141,layer1_output[6],`MASK_br141), W2_5_4, mult_2[38]);
mul16u_exact component_103(`SAC(br142,layer1_output[7],`MASK_br142), W2_6_4, mult_2[39]);
mul16u_exact component_104(`SAC(br143,layer1_output[8],`MASK_br143), W2_7_4, mult_2[40]);
mul16u_exact component_105(`SAC(br144,layer1_output[1],`MASK_br144), W2_0_5, mult_2[41]);
mul16u_exact component_106(`SAC(br145,layer1_output[2],`MASK_br145), W2_1_5, mult_2[42]);
mul16u_exact component_107(`SAC(br146,layer1_output[3],`MASK_br146), W2_2_5, mult_2[43]);
mul16u_exact component_108(`SAC(br147,layer1_output[4],`MASK_br147), W2_3_5, mult_2[44]);
mul16u_exact component_109(`SAC(br148,layer1_output[5],`MASK_br148), W2_4_5, mult_2[45]);
mul16u_exact component_110(`SAC(br149,layer1_output[6],`MASK_br149), W2_5_5, mult_2[46]);
mul16u_exact component_111(`SAC(br150,layer1_output[7],`MASK_br150), W2_6_5, mult_2[47]);
mul16u_exact component_112(`SAC(br151,layer1_output[8],`MASK_br151), W2_7_5, mult_2[48]);

// Adders instantiation.
adder_16bit component_113(`SAC(br152,mult_2[1],`MASK_br152), `SAC(br153,mult_2[2],`MASK_br153), sum_2[1]);
adder_16bit component_114(`SAC(br154,mult_2[3],`MASK_br154), `SAC(br155,mult_2[4],`MASK_br155), sum_2[2]);
adder_16bit component_115(`SAC(br156,mult_2[5],`MASK_br156), `SAC(br157,mult_2[6],`MASK_br157), sum_2[3]);
adder_16bit component_116(`SAC(br158,mult_2[7],`MASK_br158), `SAC(br159,mult_2[8],`MASK_br159), sum_2[4]);
adder_16bit component_117(`SAC(br160,mult_2[9],`MASK_br160), `SAC(br161,mult_2[10],`MASK_br161), sum_2[5]);
adder_16bit component_118(`SAC(br162,mult_2[11],`MASK_br162), `SAC(br163,mult_2[12],`MASK_br163), sum_2[6]);
adder_16bit component_119(`SAC(br164,mult_2[13],`MASK_br164), `SAC(br165,mult_2[14],`MASK_br165), sum_2[7]);
adder_16bit component_120(`SAC(br166,mult_2[15],`MASK_br166), `SAC(br167,mult_2[16],`MASK_br167), sum_2[8]);
adder_16bit component_121(`SAC(br168,mult_2[17],`MASK_br168), `SAC(br169,mult_2[18],`MASK_br169), sum_2[9]);
adder_16bit component_122(`SAC(br170,mult_2[19],`MASK_br170), `SAC(br171,mult_2[20],`MASK_br171), sum_2[10]);
adder_16bit component_123(`SAC(br172,mult_2[21],`MASK_br172), `SAC(br173,mult_2[22],`MASK_br173), sum_2[11]);
adder_16bit component_124(`SAC(br174,mult_2[23],`MASK_br174), `SAC(br175,mult_2[24],`MASK_br175), sum_2[12]);
adder_16bit component_125(`SAC(br176,mult_2[25],`MASK_br176), `SAC(br177,mult_2[26],`MASK_br177), sum_2[13]);
adder_16bit component_126(`SAC(br178,mult_2[27],`MASK_br178), `SAC(br179,mult_2[28],`MASK_br179), sum_2[14]);
adder_16bit component_127(`SAC(br180,mult_2[29],`MASK_br180), `SAC(br181,mult_2[30],`MASK_br181), sum_2[15]);
adder_16bit component_128(`SAC(br182,mult_2[31],`MASK_br182), `SAC(br183,mult_2[32],`MASK_br183), sum_2[16]);
adder_16bit component_129(`SAC(br184,mult_2[33],`MASK_br184), `SAC(br185,mult_2[34],`MASK_br185), sum_2[17]);
adder_16bit component_130(`SAC(br186,mult_2[35],`MASK_br186), `SAC(br187,mult_2[36],`MASK_br187), sum_2[18]);
adder_16bit component_131(`SAC(br188,mult_2[37],`MASK_br188), `SAC(br189,mult_2[38],`MASK_br189), sum_2[19]);
adder_16bit component_132(`SAC(br190,mult_2[39],`MASK_br190), `SAC(br191,mult_2[40],`MASK_br191), sum_2[20]);
adder_16bit component_133(`SAC(br192,mult_2[41],`MASK_br192), `SAC(br193,mult_2[42],`MASK_br193), sum_2[21]);
adder_16bit component_134(`SAC(br194,mult_2[43],`MASK_br194), `SAC(br195,mult_2[44],`MASK_br195), sum_2[22]);
adder_16bit component_135(`SAC(br196,mult_2[45],`MASK_br196), `SAC(br197,mult_2[46],`MASK_br197), sum_2[23]);
adder_16bit component_136(`SAC(br198,mult_2[47],`MASK_br198), `SAC(br199,mult_2[48],`MASK_br199), sum_2[24]);

adder_16bit component_137(`SAC(br200,sum_2[1],`MASK_br200), `SAC(br201,sum_2[2],`MASK_br201), sum_2[25]);
adder_16bit component_138(`SAC(br202,sum_2[3],`MASK_br202), `SAC(br203,sum_2[4],`MASK_br203), sum_2[26]);
adder_16bit component_139(`SAC(br204,sum_2[5],`MASK_br204), `SAC(br205,sum_2[6],`MASK_br205), sum_2[27]);
adder_16bit component_140(`SAC(br206,sum_2[7],`MASK_br206), `SAC(br207,sum_2[8],`MASK_br207), sum_2[28]);
adder_16bit component_141(`SAC(br208,sum_2[9],`MASK_br208), `SAC(br209,sum_2[10],`MASK_br209), sum_2[29]);
adder_16bit component_142(`SAC(br210,sum_2[11],`MASK_br210), `SAC(br211,sum_2[12],`MASK_br211), sum_2[30]);
adder_16bit component_143(`SAC(br212,sum_2[13],`MASK_br212), `SAC(br213,sum_2[14],`MASK_br213), sum_2[31]);
adder_16bit component_144(`SAC(br214,sum_2[15],`MASK_br214), `SAC(br215,sum_2[16],`MASK_br215), sum_2[32]);
adder_16bit component_145(`SAC(br216,sum_2[17],`MASK_br216), `SAC(br217,sum_2[18],`MASK_br217), sum_2[33]);
adder_16bit component_146(`SAC(br218,sum_2[19],`MASK_br218), `SAC(br219,sum_2[20],`MASK_br219), sum_2[34]);
adder_16bit component_147(`SAC(br220,sum_2[21],`MASK_br220), `SAC(br221,sum_2[22],`MASK_br221), sum_2[35]);
adder_16bit component_148(`SAC(br222,sum_2[23],`MASK_br222), `SAC(br223,sum_2[24],`MASK_br223), sum_2[36]);

adder_16bit component_149(`SAC(br224,sum_2[25],`MASK_br224), `SAC(br225,sum_2[26],`MASK_br225), sum_2[37]);
adder_16bit component_150(`SAC(br226,sum_2[27],`MASK_br226), `SAC(br227,sum_2[28],`MASK_br227), sum_2[38]);
adder_16bit component_151(`SAC(br228,sum_2[29],`MASK_br228), `SAC(br229,sum_2[30],`MASK_br229), sum_2[39]);
adder_16bit component_152(`SAC(br230,sum_2[31],`MASK_br230), `SAC(br231,sum_2[32],`MASK_br231), sum_2[40]);
adder_16bit component_153(`SAC(br232,sum_2[33],`MASK_br232), `SAC(br233,sum_2[34],`MASK_br233), sum_2[41]);
adder_16bit component_154(`SAC(br234,sum_2[35],`MASK_br234), `SAC(br235,sum_2[36],`MASK_br235), sum_2[42]);

adder_16bit component_155(`SAC(br236,sum_2[37],`MASK_br236), `SAC(br237,b2_0,`MASK_br237), sum_2[43]);
adder_16bit component_156(`SAC(br238,sum_2[38],`MASK_br238), `SAC(br239,b2_1,`MASK_br239), sum_2[44]);
adder_16bit component_157(`SAC(br240,sum_2[39],`MASK_br240), `SAC(br241,b2_2,`MASK_br241), sum_2[45]);
adder_16bit component_158(`SAC(br242,sum_2[40],`MASK_br242), `SAC(br243,b2_3,`MASK_br243), sum_2[46]);
adder_16bit component_159(`SAC(br244,sum_2[41],`MASK_br244), `SAC(br245,b2_4,`MASK_br245), sum_2[47]);
adder_16bit component_160(`SAC(br246,sum_2[42],`MASK_br246), `SAC(br247,b2_5,`MASK_br247), sum_2[48]);


register reg_l2_1(Reset, clk, `SAC(br248,sum_2[43],`MASK_br248), reg_l2_out[1]);
register reg_l2_2(Reset, clk, `SAC(br249,sum_2[44],`MASK_br249), reg_l2_out[2]);
register reg_l2_3(Reset, clk, `SAC(br250,sum_2[45],`MASK_br250), reg_l2_out[3]);
register reg_l2_4(Reset, clk, `SAC(br251,sum_2[46],`MASK_br251), reg_l2_out[4]);
register reg_l2_5(Reset, clk, `SAC(br252,sum_2[47],`MASK_br252), reg_l2_out[5]);
register reg_l2_6(Reset, clk, `SAC(br253,sum_2[48],`MASK_br253), reg_l2_out[6]);


RELU_2 RELU2_instance(.Reset(Reset), .clk(clk), .l2_in_1(`SAC(br254,reg_l2_out[1],`MASK_br254)), .l2_in_2(`SAC(br255,reg_l2_out[2],`MASK_br255)), .l2_in_3(`SAC(br256,reg_l2_out[3],`MASK_br256)), .l2_in_4(`SAC(br257,reg_l2_out[4],`MASK_br257)), .l2_in_5(`SAC(br258,reg_l2_out[5],`MASK_br258)), .l2_in_6(`SAC(br259,reg_l2_out[6],`MASK_br259)), .l2_out_1(layer2_output[1]), .l2_out_2(layer2_output[2]), .l2_out_3(layer2_output[3]), .l2_out_4(layer2_output[4]), .l2_out_5(layer2_output[5]), .l2_out_6(layer2_output[6]));


// Layer 3 computations:

// Multipliers instantiation.
mul16u_exact component_161(`SAC(br260,layer2_output[1],`MASK_br260), W3_0_0, mult_3[1]);
mul16u_exact component_162(`SAC(br261,layer2_output[2],`MASK_br261), W3_1_0, mult_3[2]);
mul16u_exact component_163(`SAC(br262,layer2_output[3],`MASK_br262), W3_2_0, mult_3[3]);
mul16u_exact component_164(`SAC(br263,layer2_output[4],`MASK_br263), W3_3_0, mult_3[4]);
mul16u_exact component_165(`SAC(br264,layer2_output[5],`MASK_br264), W3_4_0, mult_3[5]);
mul16u_exact component_166(`SAC(br265,layer2_output[6],`MASK_br265), W3_5_0, mult_3[6]);
mul16u_exact component_167(`SAC(br266,layer2_output[1],`MASK_br266), W3_0_1, mult_3[7]);
mul16u_exact component_168(`SAC(br267,layer2_output[2],`MASK_br267), W3_1_1, mult_3[8]);
mul16u_exact component_169(`SAC(br268,layer2_output[3],`MASK_br268), W3_2_1, mult_3[9]);
mul16u_exact component_170(`SAC(br269,layer2_output[4],`MASK_br269), W3_3_1, mult_3[10]);
mul16u_exact component_171(`SAC(br270,layer2_output[5],`MASK_br270), W3_4_1, mult_3[11]);
mul16u_exact component_172(`SAC(br271,layer2_output[6],`MASK_br271), W3_5_1, mult_3[12]);
mul16u_exact component_173(`SAC(br272,layer2_output[1],`MASK_br272), W3_0_2, mult_3[13]);
mul16u_exact component_174(`SAC(br273,layer2_output[2],`MASK_br273), W3_1_2, mult_3[14]);
mul16u_exact component_175(`SAC(br274,layer2_output[3],`MASK_br274), W3_2_2, mult_3[15]);
mul16u_exact component_176(`SAC(br275,layer2_output[4],`MASK_br275), W3_3_2, mult_3[16]);
mul16u_exact component_177(`SAC(br276,layer2_output[5],`MASK_br276), W3_4_2, mult_3[17]);
mul16u_exact component_178(`SAC(br277,layer2_output[6],`MASK_br277), W3_5_2, mult_3[18]);

// Adders instantiation.
adder_16bit component_179(`SAC(br278,mult_3[1],`MASK_br278), `SAC(br279,mult_3[2],`MASK_br279), sum_3[1]);
adder_16bit component_180(`SAC(br280,mult_3[3],`MASK_br280), `SAC(br281,mult_3[4],`MASK_br281), sum_3[2]);
adder_16bit component_181(`SAC(br282,mult_3[5],`MASK_br282), `SAC(br283,mult_3[6],`MASK_br283), sum_3[3]);
adder_16bit component_182(`SAC(br284,mult_3[7],`MASK_br284), `SAC(br285,mult_3[8],`MASK_br285), sum_3[4]);
adder_16bit component_183(`SAC(br286,mult_3[9],`MASK_br286), `SAC(br287,mult_3[10],`MASK_br287), sum_3[5]);
adder_16bit component_184(`SAC(br288,mult_3[11],`MASK_br288), `SAC(br289,mult_3[12],`MASK_br289), sum_3[6]);
adder_16bit component_185(`SAC(br290,mult_3[13],`MASK_br290), `SAC(br291,mult_3[14],`MASK_br291), sum_3[7]);
adder_16bit component_186(`SAC(br292,mult_3[15],`MASK_br292), `SAC(br293,mult_3[16],`MASK_br293), sum_3[8]);
adder_16bit component_187(`SAC(br294,mult_3[17],`MASK_br294), `SAC(br295,mult_3[18],`MASK_br295), sum_3[9]);

adder_16bit component_188(`SAC(br296,sum_3[1],`MASK_br296), `SAC(br297,sum_3[2],`MASK_br297), sum_3[10]);
adder_16bit component_189(`SAC(br298,sum_3[3],`MASK_br298), `SAC(br299,sum_3[4],`MASK_br299), sum_3[11]);
adder_16bit component_190(`SAC(br300,sum_3[5],`MASK_br300), `SAC(br301,sum_3[6],`MASK_br301), sum_3[12]);
adder_16bit component_191(`SAC(br302,sum_3[7],`MASK_br302), `SAC(br303,sum_3[8],`MASK_br303), sum_3[13]);

adder_16bit component_192(`SAC(br304,sum_3[10],`MASK_br304), `SAC(br305,sum_3[11],`MASK_br305), sum_3[14]);
adder_16bit component_193(`SAC(br306,sum_3[12],`MASK_br306), `SAC(br307,sum_3[13],`MASK_br307), sum_3[15]);
adder_16bit component_194(`SAC(br308,sum_3[15],`MASK_br308), `SAC(br309,sum_3[9],`MASK_br309), sum_3[16]);
adder_16bit component_195(`SAC(br310,sum_3[14],`MASK_br310), `SAC(br311,b3_0,`MASK_br311), sum_3[17]);
adder_16bit component_196(`SAC(br312,sum_3[15],`MASK_br312), `SAC(br313,b3_1,`MASK_br313), sum_3[18]);
adder_16bit component_197(`SAC(br314,sum_3[16],`MASK_br314), `SAC(br315,b3_2,`MASK_br315), sum_3[19]);

register reg_l3_1(Reset, clk, `SAC(br316,sum_3[17],`MASK_br316), reg_l3_out[1]);
register reg_l3_2(Reset, clk, `SAC(br317,sum_3[18],`MASK_br317), reg_l3_out[2]);
register reg_l3_3(Reset, clk, `SAC(br318,sum_3[19],`MASK_br318), reg_l3_out[3]);



SOFTMAX SOFTMAX_instance(.Reset(Reset), .clk(clk), .l3_in_1(`SAC(br319,reg_l3_out[1],`MASK_br319)), .l3_in_2(`SAC(br320,reg_l3_out[2],`MASK_br320)), .l3_in_3(`SAC(br321,reg_l3_out[3],`MASK_br321)), .l3_out_1(layer3_output[1]), .l3_out_2(layer3_output[2]), .l3_out_3(layer3_output[3]));


FINDMAX FINDMAX_instance(.Reset(Reset), .clk(clk), .in_1(`SAC(br322,layer3_output[1],`MASK_br322)), .in_2(`SAC(br323,layer3_output[2],`MASK_br323)), .in_3(`SAC(br324,layer3_output[3],`MASK_br324)), .out(output_label_tmp));

register reg_out(Reset, clk, `SAC(br325,output_label_tmp,`MASK_br325), out_temp);

// Getting output_label:
assign result = `SAC(br326,out_temp,`MASK_br326);

endmodule
