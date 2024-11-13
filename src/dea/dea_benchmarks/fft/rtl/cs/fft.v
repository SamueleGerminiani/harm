`include "deMacro.v"

module fft(clk, rst,
                 x0_r, x0_im, x1_r, x1_im, x2_r, x2_im, x3_r, x3_im, x4_r, x4_im, x5_r, x5_im, x6_r, x6_im, x7_r, x7_im,
                 y0_r, y0_im, y1_r, y1_im, y2_r, y2_im, y3_r, y3_im, y4_r, y4_im, y5_r, y5_im, y6_r, y6_im, y7_r, y7_im);
  input clk,rst;
  input[63:0] x0_r,x0_im,x1_r,x1_im,x2_r,x2_im,x3_r,x3_im,x4_r,x4_im,x5_r,x5_im,x6_r,x6_im,x7_r,x7_im;
  output[63:0] y0_r,y0_im,y1_r,y1_im,y2_r,y2_im,y3_r,y3_im,y4_r,y4_im,y5_r,y5_im,y6_r,y6_im,y7_r,y7_im;

  parameter [63:0] w0_8_r = 64'b00000000000100000000000000000000; 		//1.0
  parameter [63:0] w0_8_im = 64'b00000000000000000000000000000000;		//0.0
  parameter [63:0] w1_8_r = 64'b00000000000010110101000001001000;		//0.7071
  parameter [63:0] w1_8_im = 64'b10000000000010110101000001001000;		//-0.7071
  parameter [63:0] w2_8_r = 64'b00000000000000000000000000000000;		//0.0
  parameter [63:0] w2_8_im = 64'b10000000000100000000000000000000;		//-1.0
  parameter [63:0] w3_8_r = 64'b10000000000010110101000001001000;		//-0.7071
  parameter [63:0] w3_8_im = 64'b10000000000010110101000001001000;		//-0.7071

  wire[63:0] st1_but1_tmp[1:13];
  wire[63:0] st1_but2_tmp[1:13];
  wire[63:0] st1_but3_tmp[1:13];
  wire[63:0] st1_but4_tmp[1:13];

  wire[63:0] st2_but1_tmp[1:13];
  wire[63:0] st2_but2_tmp[1:13];
  wire[63:0] st2_but3_tmp[1:13];
  wire[63:0] st2_but4_tmp[1:13];
  
  wire[63:0] st3_but1_tmp[1:13];
  wire[63:0] st3_but2_tmp[1:13];
  wire[63:0] st3_but3_tmp[1:13];
  wire[63:0] st3_but4_tmp[1:13];
  
  wire[63:0] but_out1_r[0:11];
  wire[63:0] but_out1_im[0:11];
  wire[63:0] but_out2_r[0:11];
  wire[63:0] but_out2_im[0:11];


//Stage-1
 
`CS(component_73,mul16u_exact,`SUB_component_73) component_73(w0_8_r, x4_r, st1_but1_tmp[1]);
`CS(component_74,mul16u_exact,`SUB_component_74) component_74(w0_8_im, x4_im, st1_but1_tmp[2]);
`CS(component_75,mul16u_exact,`SUB_component_75) component_75(w0_8_r, x4_im, st1_but1_tmp[3]);
`CS(component_76,mul16u_exact,`SUB_component_76) component_76(w0_8_im, x4_r, st1_but1_tmp[4]);

// settling of i^2 (for imaginary part)
negate_16 n0(st1_but1_tmp[2], st1_but1_tmp[5]);

// Final addition to produce the result of complex multiplication (x4*w0_8)
`CS(component_01,adder_16bit,`SUB_component_01) component_01(st1_but1_tmp[1], st1_but1_tmp[5], st1_but1_tmp[6]);	
`CS(component_02,adder_16bit,`SUB_component_02) component_02(st1_but1_tmp[3], st1_but1_tmp[4], st1_but1_tmp[7]);		
// Addition of butterfly 1 (x0_r+x4_r)
`CS(component_03,adder_16bit,`SUB_component_03) component_03(x0_r, st1_but1_tmp[6], st1_but1_tmp[8]);		
// x0_im+x4_im
`CS(component_04,adder_16bit,`SUB_component_04) component_04(x0_im, st1_but1_tmp[7], st1_but1_tmp[9]);		

// Changing the sign of real and imaginary parts ( of product) to make it
negate_16 n1(st1_but1_tmp[6], st1_but1_tmp[10]);
negate_16 n2(st1_but1_tmp[7], st1_but1_tmp[11]);

// x0_r + (-x4_r)
`CS(component_05,adder_16bit,`SUB_component_05) component_05(x0_r, st1_but1_tmp[10], st1_but1_tmp[12]);		 
// x0_im + (-x4_im)
`CS(component_06,adder_16bit,`SUB_component_06) component_06(x0_im, st1_but1_tmp[11], st1_but1_tmp[13]);		

// Result of butterly 1
register reg_s1_00 (rst, clk, st1_but1_tmp[8], but_out1_r[0]);
register reg_s1_01 (rst, clk, st1_but1_tmp[9], but_out1_im[0]);
register reg_s1_02 (rst, clk, st1_but1_tmp[12], but_out2_r[0]);
register reg_s1_03 (rst, clk, st1_but1_tmp[13], but_out2_im[0]);


`CS(component_77,mul16u_exact,`SUB_component_77) component_77(w0_8_r, x6_r, st1_but2_tmp[1]);
`CS(component_78,mul16u_exact,`SUB_component_78) component_78(w0_8_im, x6_im, st1_but2_tmp[2]);
`CS(component_79,mul16u_exact,`SUB_component_79) component_79(w0_8_r, x6_im, st1_but2_tmp[3]);
`CS(component_80,mul16u_exact,`SUB_component_80) component_80(w0_8_im, x6_r, st1_but2_tmp[4]);

negate_16 n3(st1_but2_tmp[2],st1_but2_tmp[5]);

`CS(component_07,adder_16bit,`SUB_component_07) component_07(st1_but2_tmp[1],st1_but2_tmp[5],st1_but2_tmp[6]);		
`CS(component_08,adder_16bit,`SUB_component_08) component_08(st1_but2_tmp[3],st1_but2_tmp[4],st1_but2_tmp[7]);		
`CS(component_09,adder_16bit,`SUB_component_09) component_09(x2_r,st1_but2_tmp[6],st1_but2_tmp[8]);		
`CS(component_10,adder_16bit,`SUB_component_10) component_10(x2_im,st1_but2_tmp[7],st1_but2_tmp[9]);		
negate_16 n4(st1_but2_tmp[6],st1_but2_tmp[10]);
negate_16 n5(st1_but2_tmp[7],st1_but2_tmp[11]);
`CS(component_11,adder_16bit,`SUB_component_11) component_11(x2_r,st1_but2_tmp[10],st1_but2_tmp[12]);		 
`CS(component_12,adder_16bit,`SUB_component_12) component_12(x2_im,st1_but2_tmp[11],st1_but2_tmp[13]);		

register reg_s1_04 (rst, clk, st1_but2_tmp[8], but_out1_r[1]);
register reg_s1_05 (rst, clk, st1_but2_tmp[9], but_out1_im[1]);
register reg_s1_06 (rst, clk, st1_but2_tmp[12], but_out2_r[1]);
register reg_s1_07 (rst, clk, st1_but2_tmp[13], but_out2_im[1]);
    

`CS(component_81,mul16u_exact,`SUB_component_81) component_81(w0_8_r, x5_r, st1_but3_tmp[1]);
`CS(component_82,mul16u_exact,`SUB_component_82) component_82(w0_8_im, x5_im, st1_but3_tmp[2]);
`CS(component_83,mul16u_exact,`SUB_component_83) component_83(w0_8_r, x5_im, st1_but3_tmp[3]);
`CS(component_84,mul16u_exact,`SUB_component_84) component_84(w0_8_im, x5_r, st1_but3_tmp[4]);

negate_16 n6(st1_but3_tmp[2],st1_but3_tmp[5]);
`CS(component_13,adder_16bit,`SUB_component_13) component_13(st1_but3_tmp[1],st1_but3_tmp[5],st1_but3_tmp[6]);		
`CS(component_14,adder_16bit,`SUB_component_14) component_14(st1_but3_tmp[3],st1_but3_tmp[4],st1_but3_tmp[7]);		
`CS(component_15,adder_16bit,`SUB_component_15) component_15(x1_r,st1_but3_tmp[6],st1_but3_tmp[8]);		
`CS(component_16,adder_16bit,`SUB_component_16) component_16(x1_im,st1_but3_tmp[7],st1_but3_tmp[9]);		
negate_16 n7(st1_but3_tmp[6],st1_but3_tmp[10]);
negate_16 n8(st1_but3_tmp[7],st1_but3_tmp[11]);
`CS(component_17,adder_16bit,`SUB_component_17) component_17(x1_r,st1_but3_tmp[10],st1_but3_tmp[12]);		 
`CS(component_18,adder_16bit,`SUB_component_18) component_18(x1_im,st1_but3_tmp[11],st1_but3_tmp[13]);		

register reg_s1_08 (rst, clk, st1_but3_tmp[8], but_out1_r[2]);
register reg_s1_09 (rst, clk, st1_but3_tmp[9], but_out1_im[2]);
register reg_s1_10 (rst, clk, st1_but3_tmp[12], but_out2_r[2]);
register reg_s1_11 (rst, clk, st1_but3_tmp[13], but_out2_im[2]);
  

`CS(component_85,mul16u_exact,`SUB_component_85) component_85(w0_8_r, x7_r, st1_but4_tmp[1]);
`CS(component_86,mul16u_exact,`SUB_component_86) component_86(w0_8_im, x7_im, st1_but4_tmp[2]);
`CS(component_87,mul16u_exact,`SUB_component_87) component_87(w0_8_r, x7_im, st1_but4_tmp[3]);
`CS(component_88,mul16u_exact,`SUB_component_88) component_88(w0_8_im, x7_r, st1_but4_tmp[4]);

negate_16 n9(st1_but4_tmp[2],st1_but4_tmp[5]);
`CS(component_19,adder_16bit,`SUB_component_19) component_19(st1_but4_tmp[1],st1_but4_tmp[5],st1_but4_tmp[6]);		
`CS(component_20,adder_16bit,`SUB_component_20) component_20(st1_but4_tmp[3],st1_but4_tmp[4],st1_but4_tmp[7]);		
`CS(component_21,adder_16bit,`SUB_component_21) component_21(x3_r,st1_but4_tmp[6],st1_but4_tmp[8]);		
`CS(component_22,adder_16bit,`SUB_component_22) component_22(x3_im,st1_but4_tmp[7],st1_but4_tmp[9]);		
negate_16 n10(st1_but4_tmp[6],st1_but4_tmp[10]);
negate_16 n11(st1_but4_tmp[7],st1_but4_tmp[11]);
`CS(component_23,adder_16bit,`SUB_component_23) component_23(x3_r,st1_but4_tmp[10],st1_but4_tmp[12]);		 
`CS(component_24,adder_16bit,`SUB_component_24) component_24(x3_im,st1_but4_tmp[11],st1_but4_tmp[13]);		

register reg_s1_12 (rst, clk, st1_but4_tmp[8], but_out1_r[3]);
register reg_s1_13 (rst, clk, st1_but4_tmp[9], but_out1_im[3]);
register reg_s1_14 (rst, clk, st1_but4_tmp[12], but_out2_r[3]);
register reg_s1_15 (rst, clk, st1_but4_tmp[13], but_out2_im[3]);
  
//Stage-2
  

`CS(component_89,mul16u_exact,`SUB_component_89) component_89(w0_8_r, but_out1_r[1], st2_but1_tmp[1]);
`CS(component_90,mul16u_exact,`SUB_component_90) component_90(w0_8_im, but_out1_im[1], st2_but1_tmp[2]);
`CS(component_91,mul16u_exact,`SUB_component_91) component_91(w0_8_r, but_out1_im[1], st2_but1_tmp[3]);
`CS(component_92,mul16u_exact,`SUB_component_92) component_92(w0_8_im, but_out1_r[1], st2_but1_tmp[4]);

negate_16 n12(st2_but1_tmp[2], st2_but1_tmp[5]);
`CS(component_25,adder_16bit,`SUB_component_25) component_25(st2_but1_tmp[1], st2_but1_tmp[5], st2_but1_tmp[6]);		
`CS(component_26,adder_16bit,`SUB_component_26) component_26(st2_but1_tmp[3], st2_but1_tmp[4], st2_but1_tmp[7]);		
`CS(component_27,adder_16bit,`SUB_component_27) component_27(but_out1_r[0], st2_but1_tmp[6], st2_but1_tmp[8]);		
`CS(component_28,adder_16bit,`SUB_component_28) component_28(but_out1_im[0], st2_but1_tmp[7], st2_but1_tmp[9]);		
negate_16 n13(st2_but1_tmp[6], st2_but1_tmp[10]);
negate_16 n14(st2_but1_tmp[7], st2_but1_tmp[11]);
`CS(component_29,adder_16bit,`SUB_component_29) component_29(but_out1_r[0], st2_but1_tmp[10], st2_but1_tmp[12]);		 
`CS(component_30,adder_16bit,`SUB_component_30) component_30(but_out1_im[0], st2_but1_tmp[11], st2_but1_tmp[13]);		

register reg_s1_16 (rst, clk, st2_but1_tmp[8], but_out1_r[4]);
register reg_s1_17 (rst, clk, st2_but1_tmp[9], but_out1_im[4]);
register reg_s1_18 (rst, clk, st2_but1_tmp[12], but_out2_r[4]);
register reg_s1_19 (rst, clk, st2_but1_tmp[13], but_out2_im[4]);
  

`CS(component_93,mul16u_exact,`SUB_component_93) component_93(w2_8_r, but_out2_r[1], st2_but2_tmp[1]);
`CS(component_94,mul16u_exact,`SUB_component_94) component_94(w2_8_im, but_out2_im[1], st2_but2_tmp[2]);
`CS(component_95,mul16u_exact,`SUB_component_95) component_95(w2_8_r, but_out2_im[1], st2_but2_tmp[3]);
`CS(component_96,mul16u_exact,`SUB_component_96) component_96(w2_8_im, but_out2_r[1], st2_but2_tmp[4]);

negate_16 n15(st2_but2_tmp[2],st2_but2_tmp[5]);
`CS(component_31,adder_16bit,`SUB_component_31) component_31(st2_but2_tmp[1],st2_but2_tmp[5],st2_but2_tmp[6]);		
`CS(component_32,adder_16bit,`SUB_component_32) component_32(st2_but2_tmp[3],st2_but2_tmp[4],st2_but2_tmp[7]);		
`CS(component_33,adder_16bit,`SUB_component_33) component_33(but_out2_r[0],st2_but2_tmp[6],st2_but2_tmp[8]);		
`CS(component_34,adder_16bit,`SUB_component_34) component_34(but_out2_im[0],st2_but2_tmp[7],st2_but2_tmp[9]);		
negate_16 n16(st2_but2_tmp[6],st2_but2_tmp[10]);
negate_16 n17(st2_but2_tmp[7],st2_but2_tmp[11]);
`CS(component_35,adder_16bit,`SUB_component_35) component_35(but_out2_r[0],st2_but2_tmp[10],st2_but2_tmp[12]);		 
`CS(component_36,adder_16bit,`SUB_component_36) component_36(but_out2_im[0],st2_but2_tmp[11],st2_but2_tmp[13]);		

register reg_s1_20 (rst, clk, st2_but2_tmp[8], but_out1_r[5]);
register reg_s1_21 (rst, clk, st2_but2_tmp[9], but_out1_im[5]);
register reg_s1_22 (rst, clk, st2_but2_tmp[12], but_out2_r[5]);
register reg_s1_23 (rst, clk, st2_but2_tmp[13], but_out2_im[5]);
  
`CS(component_97,mul16u_exact,`SUB_component_97) component_97(w0_8_r, but_out1_r[3], st2_but3_tmp[1]);
`CS(component_98,mul16u_exact,`SUB_component_98) component_98(w0_8_im, but_out1_im[3], st2_but3_tmp[2]);
`CS(component_99,mul16u_exact,`SUB_component_99) component_99(w0_8_r, but_out1_im[3], st2_but3_tmp[3]);
`CS(component_100,mul16u_exact,`SUB_component_100) component_100(w0_8_im, but_out1_r[3], st2_but3_tmp[4]);

negate_16 n18(st2_but3_tmp[2],st2_but3_tmp[5]);
`CS(component_37,adder_16bit,`SUB_component_37) component_37(st2_but3_tmp[1],st2_but3_tmp[5],st2_but3_tmp[6]);		
`CS(component_38,adder_16bit,`SUB_component_38) component_38(st2_but3_tmp[3],st2_but3_tmp[4],st2_but3_tmp[7]);		
`CS(component_39,adder_16bit,`SUB_component_39) component_39(but_out1_r[2],st2_but3_tmp[6],st2_but3_tmp[8]);		
`CS(component_40,adder_16bit,`SUB_component_40) component_40(but_out1_im[2],st2_but3_tmp[7],st2_but3_tmp[9]);		
negate_16 n19(st2_but3_tmp[6],st2_but3_tmp[10]);
negate_16 n20(st2_but3_tmp[7],st2_but3_tmp[11]);
`CS(component_41,adder_16bit,`SUB_component_41) component_41(but_out1_r[2],st2_but3_tmp[10],st2_but3_tmp[12]);		 
`CS(component_42,adder_16bit,`SUB_component_42) component_42(but_out1_im[2],st2_but3_tmp[11],st2_but3_tmp[13]);		

register reg_s1_24 (rst, clk, st2_but3_tmp[8], but_out1_r[6]);  
register reg_s1_25 (rst, clk, st2_but3_tmp[9], but_out1_im[6]);
register reg_s1_26 (rst, clk, st2_but3_tmp[12], but_out2_r[6]);
register reg_s1_27 (rst, clk, st2_but3_tmp[13], but_out2_im[6]);  
  
`CS(component_101,mul16u_exact,`SUB_component_101) component_101(w2_8_r, but_out2_r[3], st2_but4_tmp[1]);
`CS(component_102,mul16u_exact,`SUB_component_102) component_102(w2_8_im, but_out2_im[3], st2_but4_tmp[2]);
`CS(component_103,mul16u_exact,`SUB_component_103) component_103(w2_8_r, but_out2_im[3], st2_but4_tmp[3]);
`CS(component_104,mul16u_exact,`SUB_component_104) component_104(w2_8_im, but_out2_r[3], st2_but4_tmp[4]);

negate_16 n21(st2_but4_tmp[2],st2_but4_tmp[5]);
`CS(component_43,adder_16bit,`SUB_component_43) component_43(st2_but4_tmp[1],st2_but4_tmp[5],st2_but4_tmp[6]);		
`CS(component_44,adder_16bit,`SUB_component_44) component_44(st2_but4_tmp[3],st2_but4_tmp[4],st2_but4_tmp[7]);		
`CS(component_45,adder_16bit,`SUB_component_45) component_45(but_out2_r[2],st2_but4_tmp[6],st2_but4_tmp[8]);		
`CS(component_46,adder_16bit,`SUB_component_46) component_46(but_out2_im[2],st2_but4_tmp[7],st2_but4_tmp[9]);		
negate_16 n22(st2_but4_tmp[6],st2_but4_tmp[10]);
negate_16 n23(st2_but4_tmp[7],st2_but4_tmp[11]);
`CS(component_47,adder_16bit,`SUB_component_47) component_47(but_out2_r[2],st2_but4_tmp[10],st2_but4_tmp[12]);		 
`CS(component_48,adder_16bit,`SUB_component_48) component_48(but_out2_im[2],st2_but4_tmp[11],st2_but4_tmp[13]);		

register reg_s1_28 (rst, clk, st2_but4_tmp[8], but_out1_r[7]);
register reg_s1_29 (rst, clk, st2_but4_tmp[9], but_out1_im[7]);
register reg_s1_30 (rst, clk, st2_but4_tmp[12], but_out2_r[7]);
register reg_s1_31 (rst, clk, st2_but4_tmp[13], but_out2_im[7]);  
  
// Stage-3
  
`CS(component_105,mul16u_exact,`SUB_component_105) component_105(w0_8_r, but_out1_r[6], st3_but1_tmp[1]);
`CS(component_106,mul16u_exact,`SUB_component_106) component_106(w0_8_im, but_out1_im[6], st3_but1_tmp[2]);
`CS(component_107,mul16u_exact,`SUB_component_107) component_107(w0_8_r, but_out1_im[6], st3_but1_tmp[3]);
`CS(component_108,mul16u_exact,`SUB_component_108) component_108(w0_8_im, but_out1_r[6], st3_but1_tmp[4]);

negate_16 n24(st3_but1_tmp[2], st3_but1_tmp[5]);
`CS(component_49,adder_16bit,`SUB_component_49) component_49(st3_but1_tmp[1], st3_but1_tmp[5], st3_but1_tmp[6]);		
`CS(component_50,adder_16bit,`SUB_component_50) component_50(st3_but1_tmp[3], st3_but1_tmp[4], st3_but1_tmp[7]);		
`CS(component_51,adder_16bit,`SUB_component_51) component_51(but_out1_r[4], st3_but1_tmp[6], st3_but1_tmp[8]);		
`CS(component_52,adder_16bit,`SUB_component_52) component_52(but_out1_im[4], st3_but1_tmp[7], st3_but1_tmp[9]);		
negate_16 n25(st3_but1_tmp[6], st3_but1_tmp[10]);
negate_16 n26(st3_but1_tmp[7], st3_but1_tmp[11]);
`CS(component_53,adder_16bit,`SUB_component_53) component_53(but_out1_r[4], st3_but1_tmp[10], st3_but1_tmp[12]);		 
`CS(component_54,adder_16bit,`SUB_component_54) component_54(but_out1_im[4], st3_but1_tmp[11], st3_but1_tmp[13]);		

register reg_s1_32 (rst, clk, st3_but1_tmp[8], but_out1_r[8]);
register reg_s1_33 (rst, clk, st3_but1_tmp[9], but_out1_im[8]); 
register reg_s1_34 (rst, clk, st3_but1_tmp[12], but_out2_r[8]);
register reg_s1_35 (rst, clk, st3_but1_tmp[13], but_out2_im[8]);

  
`CS(component_109,mul16u_exact,`SUB_component_109) component_109(w1_8_r, but_out1_r[7], st3_but2_tmp[1]);
`CS(component_110,mul16u_exact,`SUB_component_110) component_110(w1_8_im, but_out1_im[7], st3_but2_tmp[2]);
`CS(component_111,mul16u_exact,`SUB_component_111) component_111(w1_8_r, but_out1_im[7], st3_but2_tmp[3]);
`CS(component_112,mul16u_exact,`SUB_component_112) component_112(w1_8_im, but_out1_r[7], st3_but2_tmp[4]);

negate_16 n27(st3_but2_tmp[2],st3_but2_tmp[5]);
`CS(component_55,adder_16bit,`SUB_component_55) component_55(st3_but2_tmp[1],st3_but2_tmp[5],st3_but2_tmp[6]);		
`CS(component_56,adder_16bit,`SUB_component_56) component_56(st3_but2_tmp[3],st3_but2_tmp[4],st3_but2_tmp[7]);		
`CS(component_57,adder_16bit,`SUB_component_57) component_57(but_out1_r[5],st3_but2_tmp[6],st3_but2_tmp[8]);		
`CS(component_58,adder_16bit,`SUB_component_58) component_58(but_out1_im[5],st3_but2_tmp[7],st3_but2_tmp[9]);		
negate_16 n28(st3_but2_tmp[6],st3_but2_tmp[10]);
negate_16 n29(st3_but2_tmp[7],st3_but2_tmp[11]);
`CS(component_59,adder_16bit,`SUB_component_59) component_59(but_out1_r[5],st3_but2_tmp[10],st3_but2_tmp[12]);		 
`CS(component_60,adder_16bit,`SUB_component_60) component_60(but_out1_im[5],st3_but2_tmp[11],st3_but2_tmp[13]);		

register reg_s1_36 (rst, clk, st3_but2_tmp[8], but_out1_r[9]);
register reg_s1_37 (rst, clk, st3_but2_tmp[9], but_out1_im[9]);
register reg_s1_38 (rst, clk, st3_but2_tmp[12], but_out2_r[9]);
register reg_s1_39 (rst, clk, st3_but2_tmp[13], but_out2_im[9]);
  
`CS(component_113,mul16u_exact,`SUB_component_113) component_113(w2_8_r, but_out2_r[6], st3_but3_tmp[1]);
`CS(component_114,mul16u_exact,`SUB_component_114) component_114(w2_8_im, but_out2_im[6], st3_but3_tmp[2]);
`CS(component_115,mul16u_exact,`SUB_component_115) component_115(w2_8_r, but_out2_im[6], st3_but3_tmp[3]);
`CS(component_116,mul16u_exact,`SUB_component_116) component_116(w2_8_im, but_out2_r[6], st3_but3_tmp[4]);

negate_16 n30(st3_but3_tmp[2],st3_but3_tmp[5]);
`CS(component_61,adder_16bit,`SUB_component_61) component_61(st3_but3_tmp[1],st3_but3_tmp[5],st3_but3_tmp[6]);		
`CS(component_62,adder_16bit,`SUB_component_62) component_62(st3_but3_tmp[3],st3_but3_tmp[4],st3_but3_tmp[7]);		
`CS(component_63,adder_16bit,`SUB_component_63) component_63(but_out2_r[4],st3_but3_tmp[6],st3_but3_tmp[8]);		
`CS(component_64,adder_16bit,`SUB_component_64) component_64(but_out2_im[4],st3_but3_tmp[7],st3_but3_tmp[9]);		
negate_16 n31(st3_but3_tmp[6],st3_but3_tmp[10]);
negate_16 n32(st3_but3_tmp[7],st3_but3_tmp[11]);
`CS(component_65,adder_16bit,`SUB_component_65) component_65(but_out2_r[4],st3_but3_tmp[10],st3_but3_tmp[12]);		 
`CS(component_66,adder_16bit,`SUB_component_66) component_66(but_out2_im[4],st3_but3_tmp[11],st3_but3_tmp[13]);		

register reg_s1_40 (rst, clk, st3_but3_tmp[8], but_out1_r[10]);
register reg_s1_41 (rst, clk, st3_but3_tmp[9], but_out1_im[10]);
register reg_s1_42 (rst, clk, st3_but3_tmp[12], but_out2_r[10]);
register reg_s1_43 (rst, clk, st3_but3_tmp[13], but_out2_im[10]);
  
`CS(component_117,mul16u_exact,`SUB_component_117) component_117(w3_8_r, but_out2_r[7], st3_but4_tmp[1]);
`CS(component_118,mul16u_exact,`SUB_component_118) component_118(w3_8_im, but_out2_im[7], st3_but4_tmp[2]);
`CS(component_119,mul16u_exact,`SUB_component_119) component_119(w3_8_r, but_out2_im[7], st3_but4_tmp[3]);
`CS(component_120,mul16u_exact,`SUB_component_120) component_120(w3_8_im, but_out2_r[7], st3_but4_tmp[4]);

negate_16 n33(st3_but4_tmp[2],st3_but4_tmp[5]);
`CS(component_67,adder_16bit,`SUB_component_67) component_67(st3_but4_tmp[1],st3_but4_tmp[5],st3_but4_tmp[6]);		
`CS(component_68,adder_16bit,`SUB_component_68) component_68(st3_but4_tmp[3],st3_but4_tmp[4],st3_but4_tmp[7]);		
`CS(component_69,adder_16bit,`SUB_component_69) component_69(but_out2_r[5],st3_but4_tmp[6],st3_but4_tmp[8]);		
`CS(component_70,adder_16bit,`SUB_component_70) component_70(but_out2_im[5],st3_but4_tmp[7],st3_but4_tmp[9]);		
negate_16 n34(st3_but4_tmp[6],st3_but4_tmp[10]);
negate_16 n35(st3_but4_tmp[7],st3_but4_tmp[11]);
`CS(component_71,adder_16bit,`SUB_component_71) component_71(but_out2_r[5],st3_but4_tmp[10],st3_but4_tmp[12]);		 
`CS(component_72,adder_16bit,`SUB_component_72) component_72(but_out2_im[5],st3_but4_tmp[11],st3_but4_tmp[13]);		

register reg_s1_44 (rst, clk, st3_but4_tmp[8],  but_out1_r[11]);
register reg_s1_45 (rst, clk, st3_but4_tmp[9], but_out1_im[11]);
register reg_s1_46 (rst, clk, st3_but4_tmp[12], but_out2_r[11]);
register reg_s1_47 (rst, clk, st3_but4_tmp[13], but_out2_im[11]);

assign y0_r=but_out1_r[8];
assign y0_im=but_out1_im[8];

assign y1_r=but_out1_r[9];
assign y1_im=but_out1_im[9];

assign y2_r=but_out1_r[10];
assign y2_im=but_out1_im[10];

assign y3_r=but_out1_r[11];
assign y3_im=but_out1_im[11];

assign y4_r=but_out2_r[8];
assign y4_im=but_out2_im[8];

assign y5_r=but_out2_r[9];
assign y5_im=but_out2_im[9];

assign y6_r=but_out2_r[10];
assign y6_im=but_out2_im[10];

assign y7_r=but_out2_r[11];
assign y7_im=but_out2_im[11];

endmodule
