/*----------------------------------------------------------------------------
  Copyright (c) 2004 Aoki laboratory. All rights reserved.

  Top module: UBBKA_31_0_31_0

  Operand-1 length: 32
  Operand-2 length: 32
  Two-operand addition algorithm: Brent-Kung adder
----------------------------------------------------------------------------*/
`include "deMacro.v"

module GPGenerator(Go, Po, A, B);
  output Go;
  output Po;
  input A;
  input B;
  assign Go = A & B;
  assign Po = A ^ B;
endmodule

module CarryOperator(Go, Po, Gi1, Pi1, Gi2, Pi2);
  output Go;
  output Po;
  input Gi1;
  input Gi2;
  input Pi1;
  input Pi2;
  assign Go = Gi1 | ( Gi2 & Pi1 );
  assign Po = Pi1 & Pi2;
endmodule

module UBPriBKA_31_0(S, X, Y, Cin);
  output [32:0] S;
  input Cin;
  input [31:0] X;
  input [31:0] Y;
  wire [31:0] G0;
  wire [31:0] G1;
  wire [31:0] G10;
  wire [31:0] G2;
  wire [31:0] G3;
  wire [31:0] G4;
  wire [31:0] G5;
  wire [31:0] G6;
  wire [31:0] G7;
  wire [31:0] G8;
  wire [31:0] G9;
  wire [31:0] P0;
  wire [31:0] P1;
  wire [31:0] P10;
  wire [31:0] P2;
  wire [31:0] P3;
  wire [31:0] P4;
  wire [31:0] P5;
  wire [31:0] P6;
  wire [31:0] P7;
  wire [31:0] P8;
  wire [31:0] P9;
  

  //_count
  //655

  assign P1[0] = `SAC(br0,P0[0],`MASK_br0);
  assign G1[0] = `SAC(br1,G0[0],`MASK_br1);
  assign P1[2] = `SAC(br2,P0[2],`MASK_br2);
  assign G1[2] = `SAC(br3,G0[2],`MASK_br3);
  assign P1[4] = `SAC(br4,P0[4],`MASK_br4);
  assign G1[4] = `SAC(br5,G0[4],`MASK_br5);
  assign P1[6] = `SAC(br6,P0[6],`MASK_br6);
  assign G1[6] = `SAC(br7,G0[6],`MASK_br7);
  assign P1[8] = `SAC(br8,P0[8],`MASK_br8);
  assign G1[8] = `SAC(br9,G0[8],`MASK_br9);
  assign P1[10] = `SAC(br10,P0[10],`MASK_br10);
  assign G1[10] = `SAC(br11,G0[10],`MASK_br11);
  assign P1[12] = `SAC(br12,P0[12],`MASK_br12);
  assign G1[12] = `SAC(br13,G0[12],`MASK_br13);
  assign P1[14] = `SAC(br14,P0[14],`MASK_br14);
  assign G1[14] = `SAC(br15,G0[14],`MASK_br15);
  assign P1[16] = `SAC(br16,P0[16],`MASK_br16);
  assign G1[16] = `SAC(br17,G0[16],`MASK_br17);
  assign P1[18] = `SAC(br18,P0[18],`MASK_br18);
  assign G1[18] = `SAC(br19,G0[18],`MASK_br19);
  assign P1[20] = `SAC(br20,P0[20],`MASK_br20);
  assign G1[20] = `SAC(br21,G0[20],`MASK_br21);
  assign P1[22] = `SAC(br22,P0[22],`MASK_br22);
  assign G1[22] = `SAC(br23,G0[22],`MASK_br23);
  assign P1[24] = `SAC(br24,P0[24],`MASK_br24);
  assign G1[24] = `SAC(br25,G0[24],`MASK_br25);
  assign P1[26] = `SAC(br26,P0[26],`MASK_br26);
  assign G1[26] = `SAC(br27,G0[26],`MASK_br27);
  assign P1[28] = `SAC(br28,P0[28],`MASK_br28);
  assign G1[28] = `SAC(br29,G0[28],`MASK_br29);
  assign P1[30] = `SAC(br30,P0[30],`MASK_br30);
  assign G1[30] = `SAC(br31,G0[30],`MASK_br31);
  assign P2[0] = `SAC(br32,P1[0],`MASK_br32);
  assign G2[0] = `SAC(br33,G1[0],`MASK_br33);
  assign P2[1] = `SAC(br34,P1[1],`MASK_br34);
  assign G2[1] = `SAC(br35,G1[1],`MASK_br35);
  assign P2[2] = `SAC(br36,P1[2],`MASK_br36);
  assign G2[2] = `SAC(br37,G1[2],`MASK_br37);
  assign P2[4] = `SAC(br38,P1[4],`MASK_br38);
  assign G2[4] = `SAC(br39,G1[4],`MASK_br39);
  assign P2[5] = `SAC(br40,P1[5],`MASK_br40);
  assign G2[5] = `SAC(br41,G1[5],`MASK_br41);
  assign P2[6] = `SAC(br42,P1[6],`MASK_br42);
  assign G2[6] = `SAC(br43,G1[6],`MASK_br43);
  assign P2[8] = `SAC(br44,P1[8],`MASK_br44);
  assign G2[8] = `SAC(br45,G1[8],`MASK_br45);
  assign P2[9] = `SAC(br46,P1[9],`MASK_br46);
  assign G2[9] = `SAC(br47,G1[9],`MASK_br47);
  assign P2[10] = `SAC(br48,P1[10],`MASK_br48);
  assign G2[10] = `SAC(br49,G1[10],`MASK_br49);
  assign P2[12] = `SAC(br50,P1[12],`MASK_br50);
  assign G2[12] = `SAC(br51,G1[12],`MASK_br51);
  assign P2[13] = `SAC(br52,P1[13],`MASK_br52);
  assign G2[13] = `SAC(br53,G1[13],`MASK_br53);
  assign P2[14] = `SAC(br54,P1[14],`MASK_br54);
  assign G2[14] = `SAC(br55,G1[14],`MASK_br55);
  assign P2[16] = `SAC(br56,P1[16],`MASK_br56);
  assign G2[16] = `SAC(br57,G1[16],`MASK_br57);
  assign P2[17] = `SAC(br58,P1[17],`MASK_br58);
  assign G2[17] = `SAC(br59,G1[17],`MASK_br59);
  assign P2[18] = `SAC(br60,P1[18],`MASK_br60);
  assign G2[18] = `SAC(br61,G1[18],`MASK_br61);
  assign P2[20] = `SAC(br62,P1[20],`MASK_br62);
  assign G2[20] = `SAC(br63,G1[20],`MASK_br63);
  assign P2[21] = `SAC(br64,P1[21],`MASK_br64);
  assign G2[21] = `SAC(br65,G1[21],`MASK_br65);
  assign P2[22] = `SAC(br66,P1[22],`MASK_br66);
  assign G2[22] = `SAC(br67,G1[22],`MASK_br67);
  assign P2[24] = `SAC(br68,P1[24],`MASK_br68);
  assign G2[24] = `SAC(br69,G1[24],`MASK_br69);
  assign P2[25] = `SAC(br70,P1[25],`MASK_br70);
  assign G2[25] = `SAC(br71,G1[25],`MASK_br71);
  assign P2[26] = `SAC(br72,P1[26],`MASK_br72);
  assign G2[26] = `SAC(br73,G1[26],`MASK_br73);
  assign P2[28] = `SAC(br74,P1[28],`MASK_br74);
  assign G2[28] = `SAC(br75,G1[28],`MASK_br75);
  assign P2[29] = `SAC(br76,P1[29],`MASK_br76);
  assign G2[29] = `SAC(br77,G1[29],`MASK_br77);
  assign P2[30] = `SAC(br78,P1[30],`MASK_br78);
  assign G2[30] = `SAC(br79,G1[30],`MASK_br79);
  assign P3[0] = `SAC(br80,P2[0],`MASK_br80);
  assign G3[0] = `SAC(br81,G2[0],`MASK_br81);
  assign P3[1] = `SAC(br82,P2[1],`MASK_br82);
  assign G3[1] = `SAC(br83,G2[1],`MASK_br83);
  assign P3[2] = `SAC(br84,P2[2],`MASK_br84);
  assign G3[2] = `SAC(br85,G2[2],`MASK_br85);
  assign P3[3] = `SAC(br86,P2[3],`MASK_br86);
  assign G3[3] = `SAC(br87,G2[3],`MASK_br87);
  assign P3[4] = `SAC(br88,P2[4],`MASK_br88);
  assign G3[4] = `SAC(br89,G2[4],`MASK_br89);
  assign P3[5] = `SAC(br90,P2[5],`MASK_br90);
  assign G3[5] = `SAC(br91,G2[5],`MASK_br91);
  assign P3[6] = `SAC(br92,P2[6],`MASK_br92);
  assign G3[6] = `SAC(br93,G2[6],`MASK_br93);
  assign P3[8] = `SAC(br94,P2[8],`MASK_br94);
  assign G3[8] = `SAC(br95,G2[8],`MASK_br95);
  assign P3[9] = `SAC(br96,P2[9],`MASK_br96);
  assign G3[9] = `SAC(br97,G2[9],`MASK_br97);
  assign P3[10] = `SAC(br98,P2[10],`MASK_br98);
  assign G3[10] = `SAC(br99,G2[10],`MASK_br99);
  assign P3[11] = `SAC(br100,P2[11],`MASK_br100);
  assign G3[11] = `SAC(br101,G2[11],`MASK_br101);
  assign P3[12] = `SAC(br102,P2[12],`MASK_br102);
  assign G3[12] = `SAC(br103,G2[12],`MASK_br103);
  assign P3[13] = `SAC(br104,P2[13],`MASK_br104);
  assign G3[13] = `SAC(br105,G2[13],`MASK_br105);
  assign P3[14] = `SAC(br106,P2[14],`MASK_br106);
  assign G3[14] = `SAC(br107,G2[14],`MASK_br107);
  assign P3[16] = `SAC(br108,P2[16],`MASK_br108);
  assign G3[16] = `SAC(br109,G2[16],`MASK_br109);
  assign P3[17] = `SAC(br110,P2[17],`MASK_br110);
  assign G3[17] = `SAC(br111,G2[17],`MASK_br111);
  assign P3[18] = `SAC(br112,P2[18],`MASK_br112);
  assign G3[18] = `SAC(br113,G2[18],`MASK_br113);
  assign P3[19] = `SAC(br114,P2[19],`MASK_br114);
  assign G3[19] = `SAC(br115,G2[19],`MASK_br115);
  assign P3[20] = `SAC(br116,P2[20],`MASK_br116);
  assign G3[20] = `SAC(br117,G2[20],`MASK_br117);
  assign P3[21] = `SAC(br118,P2[21],`MASK_br118);
  assign G3[21] = `SAC(br119,G2[21],`MASK_br119);
  assign P3[22] = `SAC(br120,P2[22],`MASK_br120);
  assign G3[22] = `SAC(br121,G2[22],`MASK_br121);
  assign P3[24] = `SAC(br122,P2[24],`MASK_br122);
  assign G3[24] = `SAC(br123,G2[24],`MASK_br123);
  assign P3[25] = `SAC(br124,P2[25],`MASK_br124);
  assign G3[25] = `SAC(br125,G2[25],`MASK_br125);
  assign P3[26] = `SAC(br126,P2[26],`MASK_br126);
  assign G3[26] = `SAC(br127,G2[26],`MASK_br127);
  assign P3[27] = `SAC(br128,P2[27],`MASK_br128);
  assign G3[27] = `SAC(br129,G2[27],`MASK_br129);
  assign P3[28] = `SAC(br130,P2[28],`MASK_br130);
  assign G3[28] = `SAC(br131,G2[28],`MASK_br131);
  assign P3[29] = `SAC(br132,P2[29],`MASK_br132);
  assign G3[29] = `SAC(br133,G2[29],`MASK_br133);
  assign P3[30] = `SAC(br134,P2[30],`MASK_br134);
  assign G3[30] = `SAC(br135,G2[30],`MASK_br135);
  assign P4[0] = `SAC(br136,P3[0],`MASK_br136);
  assign G4[0] = `SAC(br137,G3[0],`MASK_br137);
  assign P4[1] = `SAC(br138,P3[1],`MASK_br138);
  assign G4[1] = `SAC(br139,G3[1],`MASK_br139);
  assign P4[2] = `SAC(br140,P3[2],`MASK_br140);
  assign G4[2] = `SAC(br141,G3[2],`MASK_br141);
  assign P4[3] = `SAC(br142,P3[3],`MASK_br142);
  assign G4[3] = `SAC(br143,G3[3],`MASK_br143);
  assign P4[4] = `SAC(br144,P3[4],`MASK_br144);
  assign G4[4] = `SAC(br145,G3[4],`MASK_br145);
  assign P4[5] = `SAC(br146,P3[5],`MASK_br146);
  assign G4[5] = `SAC(br147,G3[5],`MASK_br147);
  assign P4[6] = `SAC(br148,P3[6],`MASK_br148);
  assign G4[6] = `SAC(br149,G3[6],`MASK_br149);
  assign P4[7] = `SAC(br150,P3[7],`MASK_br150);
  assign G4[7] = `SAC(br151,G3[7],`MASK_br151);
  assign P4[8] = `SAC(br152,P3[8],`MASK_br152);
  assign G4[8] = `SAC(br153,G3[8],`MASK_br153);
  assign P4[9] = `SAC(br154,P3[9],`MASK_br154);
  assign G4[9] = `SAC(br155,G3[9],`MASK_br155);
  assign P4[10] = `SAC(br156,P3[10],`MASK_br156);
  assign G4[10] = `SAC(br157,G3[10],`MASK_br157);
  assign P4[11] = `SAC(br158,P3[11],`MASK_br158);
  assign G4[11] = `SAC(br159,G3[11],`MASK_br159);
  assign P4[12] = `SAC(br160,P3[12],`MASK_br160);
  assign G4[12] = `SAC(br161,G3[12],`MASK_br161);
  assign P4[13] = `SAC(br162,P3[13],`MASK_br162);
  assign G4[13] = `SAC(br163,G3[13],`MASK_br163);
  assign P4[14] = `SAC(br164,P3[14],`MASK_br164);
  assign G4[14] = `SAC(br165,G3[14],`MASK_br165);
  assign P4[16] = `SAC(br166,P3[16],`MASK_br166);
  assign G4[16] = `SAC(br167,G3[16],`MASK_br167);
  assign P4[17] = `SAC(br168,P3[17],`MASK_br168);
  assign G4[17] = `SAC(br169,G3[17],`MASK_br169);
  assign P4[18] = `SAC(br170,P3[18],`MASK_br170);
  assign G4[18] = `SAC(br171,G3[18],`MASK_br171);
  assign P4[19] = `SAC(br172,P3[19],`MASK_br172);
  assign G4[19] = `SAC(br173,G3[19],`MASK_br173);
  assign P4[20] = `SAC(br174,P3[20],`MASK_br174);
  assign G4[20] = `SAC(br175,G3[20],`MASK_br175);
  assign P4[21] = `SAC(br176,P3[21],`MASK_br176);
  assign G4[21] = `SAC(br177,G3[21],`MASK_br177);
  assign P4[22] = `SAC(br178,P3[22],`MASK_br178);
  assign G4[22] = `SAC(br179,G3[22],`MASK_br179);
  assign P4[23] = `SAC(br180,P3[23],`MASK_br180);
  assign G4[23] = `SAC(br181,G3[23],`MASK_br181);
  assign P4[24] = `SAC(br182,P3[24],`MASK_br182);
  assign G4[24] = `SAC(br183,G3[24],`MASK_br183);
  assign P4[25] = `SAC(br184,P3[25],`MASK_br184);
  assign G4[25] = `SAC(br185,G3[25],`MASK_br185);
  assign P4[26] = `SAC(br186,P3[26],`MASK_br186);
  assign G4[26] = `SAC(br187,G3[26],`MASK_br187);
  assign P4[27] = `SAC(br188,P3[27],`MASK_br188);
  assign G4[27] = `SAC(br189,G3[27],`MASK_br189);
  assign P4[28] = `SAC(br190,P3[28],`MASK_br190);
  assign G4[28] = `SAC(br191,G3[28],`MASK_br191);
  assign P4[29] = `SAC(br192,P3[29],`MASK_br192);
  assign G4[29] = `SAC(br193,G3[29],`MASK_br193);
  assign P4[30] = `SAC(br194,P3[30],`MASK_br194);
  assign G4[30] = `SAC(br195,G3[30],`MASK_br195);
  assign P5[0] = `SAC(br196,P4[0],`MASK_br196);
  assign G5[0] = `SAC(br197,G4[0],`MASK_br197);
  assign P5[1] = `SAC(br198,P4[1],`MASK_br198);
  assign G5[1] = `SAC(br199,G4[1],`MASK_br199);
  assign P5[2] = `SAC(br200,P4[2],`MASK_br200);
  assign G5[2] = `SAC(br201,G4[2],`MASK_br201);
  assign P5[3] = `SAC(br202,P4[3],`MASK_br202);
  assign G5[3] = `SAC(br203,G4[3],`MASK_br203);
  assign P5[4] = `SAC(br204,P4[4],`MASK_br204);
  assign G5[4] = `SAC(br205,G4[4],`MASK_br205);
  assign P5[5] = `SAC(br206,P4[5],`MASK_br206);
  assign G5[5] = `SAC(br207,G4[5],`MASK_br207);
  assign P5[6] = `SAC(br208,P4[6],`MASK_br208);
  assign G5[6] = `SAC(br209,G4[6],`MASK_br209);
  assign P5[7] = `SAC(br210,P4[7],`MASK_br210);
  assign G5[7] = `SAC(br211,G4[7],`MASK_br211);
  assign P5[8] = `SAC(br212,P4[8],`MASK_br212);
  assign G5[8] = `SAC(br213,G4[8],`MASK_br213);
  assign P5[9] = `SAC(br214,P4[9],`MASK_br214);
  assign G5[9] = `SAC(br215,G4[9],`MASK_br215);
  assign P5[10] = `SAC(br216,P4[10],`MASK_br216);
  assign G5[10] = `SAC(br217,G4[10],`MASK_br217);
  assign P5[11] = `SAC(br218,P4[11],`MASK_br218);
  assign G5[11] = `SAC(br219,G4[11],`MASK_br219);
  assign P5[12] = `SAC(br220,P4[12],`MASK_br220);
  assign G5[12] = `SAC(br221,G4[12],`MASK_br221);
  assign P5[13] = `SAC(br222,P4[13],`MASK_br222);
  assign G5[13] = `SAC(br223,G4[13],`MASK_br223);
  assign P5[14] = `SAC(br224,P4[14],`MASK_br224);
  assign G5[14] = `SAC(br225,G4[14],`MASK_br225);
  assign P5[15] = `SAC(br226,P4[15],`MASK_br226);
  assign G5[15] = `SAC(br227,G4[15],`MASK_br227);
  assign P5[16] = `SAC(br228,P4[16],`MASK_br228);
  assign G5[16] = `SAC(br229,G4[16],`MASK_br229);
  assign P5[17] = `SAC(br230,P4[17],`MASK_br230);
  assign G5[17] = `SAC(br231,G4[17],`MASK_br231);
  assign P5[18] = `SAC(br232,P4[18],`MASK_br232);
  assign G5[18] = `SAC(br233,G4[18],`MASK_br233);
  assign P5[19] = `SAC(br234,P4[19],`MASK_br234);
  assign G5[19] = `SAC(br235,G4[19],`MASK_br235);
  assign P5[20] = `SAC(br236,P4[20],`MASK_br236);
  assign G5[20] = `SAC(br237,G4[20],`MASK_br237);
  assign P5[21] = `SAC(br238,P4[21],`MASK_br238);
  assign G5[21] = `SAC(br239,G4[21],`MASK_br239);
  assign P5[22] = `SAC(br240,P4[22],`MASK_br240);
  assign G5[22] = `SAC(br241,G4[22],`MASK_br241);
  assign P5[23] = `SAC(br242,P4[23],`MASK_br242);
  assign G5[23] = `SAC(br243,G4[23],`MASK_br243);
  assign P5[24] = `SAC(br244,P4[24],`MASK_br244);
  assign G5[24] = `SAC(br245,G4[24],`MASK_br245);
  assign P5[25] = `SAC(br246,P4[25],`MASK_br246);
  assign G5[25] = `SAC(br247,G4[25],`MASK_br247);
  assign P5[26] = `SAC(br248,P4[26],`MASK_br248);
  assign G5[26] = `SAC(br249,G4[26],`MASK_br249);
  assign P5[27] = `SAC(br250,P4[27],`MASK_br250);
  assign G5[27] = `SAC(br251,G4[27],`MASK_br251);
  assign P5[28] = `SAC(br252,P4[28],`MASK_br252);
  assign G5[28] = `SAC(br253,G4[28],`MASK_br253);
  assign P5[29] = `SAC(br254,P4[29],`MASK_br254);
  assign G5[29] = `SAC(br255,G4[29],`MASK_br255);
  assign P5[30] = `SAC(br256,P4[30],`MASK_br256);
  assign G5[30] = `SAC(br257,G4[30],`MASK_br257);
  assign P6[0] = `SAC(br258,P5[0],`MASK_br258);
  assign G6[0] = `SAC(br259,G5[0],`MASK_br259);
  assign P6[1] = `SAC(br260,P5[1],`MASK_br260);
  assign G6[1] = `SAC(br261,G5[1],`MASK_br261);
  assign P6[2] = `SAC(br262,P5[2],`MASK_br262);
  assign G6[2] = `SAC(br263,G5[2],`MASK_br263);
  assign P6[3] = `SAC(br264,P5[3],`MASK_br264);
  assign G6[3] = `SAC(br265,G5[3],`MASK_br265);
  assign P6[4] = `SAC(br266,P5[4],`MASK_br266);
  assign G6[4] = `SAC(br267,G5[4],`MASK_br267);
  assign P6[5] = `SAC(br268,P5[5],`MASK_br268);
  assign G6[5] = `SAC(br269,G5[5],`MASK_br269);
  assign P6[6] = `SAC(br270,P5[6],`MASK_br270);
  assign G6[6] = `SAC(br271,G5[6],`MASK_br271);
  assign P6[7] = `SAC(br272,P5[7],`MASK_br272);
  assign G6[7] = `SAC(br273,G5[7],`MASK_br273);
  assign P6[8] = `SAC(br274,P5[8],`MASK_br274);
  assign G6[8] = `SAC(br275,G5[8],`MASK_br275);
  assign P6[9] = `SAC(br276,P5[9],`MASK_br276);
  assign G6[9] = `SAC(br277,G5[9],`MASK_br277);
  assign P6[10] = `SAC(br278,P5[10],`MASK_br278);
  assign G6[10] = `SAC(br279,G5[10],`MASK_br279);
  assign P6[11] = `SAC(br280,P5[11],`MASK_br280);
  assign G6[11] = `SAC(br281,G5[11],`MASK_br281);
  assign P6[12] = `SAC(br282,P5[12],`MASK_br282);
  assign G6[12] = `SAC(br283,G5[12],`MASK_br283);
  assign P6[13] = `SAC(br284,P5[13],`MASK_br284);
  assign G6[13] = `SAC(br285,G5[13],`MASK_br285);
  assign P6[14] = `SAC(br286,P5[14],`MASK_br286);
  assign G6[14] = `SAC(br287,G5[14],`MASK_br287);
  assign P6[15] = `SAC(br288,P5[15],`MASK_br288);
  assign G6[15] = `SAC(br289,G5[15],`MASK_br289);
  assign P6[16] = `SAC(br290,P5[16],`MASK_br290);
  assign G6[16] = `SAC(br291,G5[16],`MASK_br291);
  assign P6[17] = `SAC(br292,P5[17],`MASK_br292);
  assign G6[17] = `SAC(br293,G5[17],`MASK_br293);
  assign P6[18] = `SAC(br294,P5[18],`MASK_br294);
  assign G6[18] = `SAC(br295,G5[18],`MASK_br295);
  assign P6[19] = `SAC(br296,P5[19],`MASK_br296);
  assign G6[19] = `SAC(br297,G5[19],`MASK_br297);
  assign P6[20] = `SAC(br298,P5[20],`MASK_br298);
  assign G6[20] = `SAC(br299,G5[20],`MASK_br299);
  assign P6[21] = `SAC(br300,P5[21],`MASK_br300);
  assign G6[21] = `SAC(br301,G5[21],`MASK_br301);
  assign P6[22] = `SAC(br302,P5[22],`MASK_br302);
  assign G6[22] = `SAC(br303,G5[22],`MASK_br303);
  assign P6[23] = `SAC(br304,P5[23],`MASK_br304);
  assign G6[23] = `SAC(br305,G5[23],`MASK_br305);
  assign P6[24] = `SAC(br306,P5[24],`MASK_br306);
  assign G6[24] = `SAC(br307,G5[24],`MASK_br307);
  assign P6[25] = `SAC(br308,P5[25],`MASK_br308);
  assign G6[25] = `SAC(br309,G5[25],`MASK_br309);
  assign P6[26] = `SAC(br310,P5[26],`MASK_br310);
  assign G6[26] = `SAC(br311,G5[26],`MASK_br311);
  assign P6[27] = `SAC(br312,P5[27],`MASK_br312);
  assign G6[27] = `SAC(br313,G5[27],`MASK_br313);
  assign P6[28] = `SAC(br314,P5[28],`MASK_br314);
  assign G6[28] = `SAC(br315,G5[28],`MASK_br315);
  assign P6[29] = `SAC(br316,P5[29],`MASK_br316);
  assign G6[29] = `SAC(br317,G5[29],`MASK_br317);
  assign P6[30] = `SAC(br318,P5[30],`MASK_br318);
  assign G6[30] = `SAC(br319,G5[30],`MASK_br319);
  assign P6[31] = `SAC(br320,P5[31],`MASK_br320);
  assign G6[31] = `SAC(br321,G5[31],`MASK_br321);
  assign P7[0] = `SAC(br322,P6[0],`MASK_br322);
  assign G7[0] = `SAC(br323,G6[0],`MASK_br323);
  assign P7[1] = `SAC(br324,P6[1],`MASK_br324);
  assign G7[1] = `SAC(br325,G6[1],`MASK_br325);
  assign P7[2] = `SAC(br326,P6[2],`MASK_br326);
  assign G7[2] = `SAC(br327,G6[2],`MASK_br327);
  assign P7[3] = `SAC(br328,P6[3],`MASK_br328);
  assign G7[3] = `SAC(br329,G6[3],`MASK_br329);
  assign P7[4] = `SAC(br330,P6[4],`MASK_br330);
  assign G7[4] = `SAC(br331,G6[4],`MASK_br331);
  assign P7[5] = `SAC(br332,P6[5],`MASK_br332);
  assign G7[5] = `SAC(br333,G6[5],`MASK_br333);
  assign P7[6] = `SAC(br334,P6[6],`MASK_br334);
  assign G7[6] = `SAC(br335,G6[6],`MASK_br335);
  assign P7[7] = `SAC(br336,P6[7],`MASK_br336);
  assign G7[7] = `SAC(br337,G6[7],`MASK_br337);
  assign P7[8] = `SAC(br338,P6[8],`MASK_br338);
  assign G7[8] = `SAC(br339,G6[8],`MASK_br339);
  assign P7[9] = `SAC(br340,P6[9],`MASK_br340);
  assign G7[9] = `SAC(br341,G6[9],`MASK_br341);
  assign P7[10] = `SAC(br342,P6[10],`MASK_br342);
  assign G7[10] = `SAC(br343,G6[10],`MASK_br343);
  assign P7[11] = `SAC(br344,P6[11],`MASK_br344);
  assign G7[11] = `SAC(br345,G6[11],`MASK_br345);
  assign P7[12] = `SAC(br346,P6[12],`MASK_br346);
  assign G7[12] = `SAC(br347,G6[12],`MASK_br347);
  assign P7[13] = `SAC(br348,P6[13],`MASK_br348);
  assign G7[13] = `SAC(br349,G6[13],`MASK_br349);
  assign P7[14] = `SAC(br350,P6[14],`MASK_br350);
  assign G7[14] = `SAC(br351,G6[14],`MASK_br351);
  assign P7[15] = `SAC(br352,P6[15],`MASK_br352);
  assign G7[15] = `SAC(br353,G6[15],`MASK_br353);
  assign P7[16] = `SAC(br354,P6[16],`MASK_br354);
  assign G7[16] = `SAC(br355,G6[16],`MASK_br355);
  assign P7[17] = `SAC(br356,P6[17],`MASK_br356);
  assign G7[17] = `SAC(br357,G6[17],`MASK_br357);
  assign P7[18] = `SAC(br358,P6[18],`MASK_br358);
  assign G7[18] = `SAC(br359,G6[18],`MASK_br359);
  assign P7[19] = `SAC(br360,P6[19],`MASK_br360);
  assign G7[19] = `SAC(br361,G6[19],`MASK_br361);
  assign P7[20] = `SAC(br362,P6[20],`MASK_br362);
  assign G7[20] = `SAC(br363,G6[20],`MASK_br363);
  assign P7[21] = `SAC(br364,P6[21],`MASK_br364);
  assign G7[21] = `SAC(br365,G6[21],`MASK_br365);
  assign P7[22] = `SAC(br366,P6[22],`MASK_br366);
  assign G7[22] = `SAC(br367,G6[22],`MASK_br367);
  assign P7[24] = `SAC(br368,P6[24],`MASK_br368);
  assign G7[24] = `SAC(br369,G6[24],`MASK_br369);
  assign P7[25] = `SAC(br370,P6[25],`MASK_br370);
  assign G7[25] = `SAC(br371,G6[25],`MASK_br371);
  assign P7[26] = `SAC(br372,P6[26],`MASK_br372);
  assign G7[26] = `SAC(br373,G6[26],`MASK_br373);
  assign P7[27] = `SAC(br374,P6[27],`MASK_br374);
  assign G7[27] = `SAC(br375,G6[27],`MASK_br375);
  assign P7[28] = `SAC(br376,P6[28],`MASK_br376);
  assign G7[28] = `SAC(br377,G6[28],`MASK_br377);
  assign P7[29] = `SAC(br378,P6[29],`MASK_br378);
  assign G7[29] = `SAC(br379,G6[29],`MASK_br379);
  assign P7[30] = `SAC(br380,P6[30],`MASK_br380);
  assign G7[30] = `SAC(br381,G6[30],`MASK_br381);
  assign P7[31] = `SAC(br382,P6[31],`MASK_br382);
  assign G7[31] = `SAC(br383,G6[31],`MASK_br383);
  assign P8[0] = `SAC(br384,P7[0],`MASK_br384);
  assign G8[0] = `SAC(br385,G7[0],`MASK_br385);
  assign P8[1] = `SAC(br386,P7[1],`MASK_br386);
  assign G8[1] = `SAC(br387,G7[1],`MASK_br387);
  assign P8[2] = `SAC(br388,P7[2],`MASK_br388);
  assign G8[2] = `SAC(br389,G7[2],`MASK_br389);
  assign P8[3] = `SAC(br390,P7[3],`MASK_br390);
  assign G8[3] = `SAC(br391,G7[3],`MASK_br391);
  assign P8[4] = `SAC(br392,P7[4],`MASK_br392);
  assign G8[4] = `SAC(br393,G7[4],`MASK_br393);
  assign P8[5] = `SAC(br394,P7[5],`MASK_br394);
  assign G8[5] = `SAC(br395,G7[5],`MASK_br395);
  assign P8[6] = `SAC(br396,P7[6],`MASK_br396);
  assign G8[6] = `SAC(br397,G7[6],`MASK_br397);
  assign P8[7] = `SAC(br398,P7[7],`MASK_br398);
  assign G8[7] = `SAC(br399,G7[7],`MASK_br399);
  assign P8[8] = `SAC(br400,P7[8],`MASK_br400);
  assign G8[8] = `SAC(br401,G7[8],`MASK_br401);
  assign P8[9] = `SAC(br402,P7[9],`MASK_br402);
  assign G8[9] = `SAC(br403,G7[9],`MASK_br403);
  assign P8[10] = `SAC(br404,P7[10],`MASK_br404);
  assign G8[10] = `SAC(br405,G7[10],`MASK_br405);
  assign P8[12] = `SAC(br406,P7[12],`MASK_br406);
  assign G8[12] = `SAC(br407,G7[12],`MASK_br407);
  assign P8[13] = `SAC(br408,P7[13],`MASK_br408);
  assign G8[13] = `SAC(br409,G7[13],`MASK_br409);
  assign P8[14] = `SAC(br410,P7[14],`MASK_br410);
  assign G8[14] = `SAC(br411,G7[14],`MASK_br411);
  assign P8[15] = `SAC(br412,P7[15],`MASK_br412);
  assign G8[15] = `SAC(br413,G7[15],`MASK_br413);
  assign P8[16] = `SAC(br414,P7[16],`MASK_br414);
  assign G8[16] = `SAC(br415,G7[16],`MASK_br415);
  assign P8[17] = `SAC(br416,P7[17],`MASK_br416);
  assign G8[17] = `SAC(br417,G7[17],`MASK_br417);
  assign P8[18] = `SAC(br418,P7[18],`MASK_br418);
  assign G8[18] = `SAC(br419,G7[18],`MASK_br419);
  assign P8[20] = `SAC(br420,P7[20],`MASK_br420);
  assign G8[20] = `SAC(br421,G7[20],`MASK_br421);
  assign P8[21] = `SAC(br422,P7[21],`MASK_br422);
  assign G8[21] = `SAC(br423,G7[21],`MASK_br423);
  assign P8[22] = `SAC(br424,P7[22],`MASK_br424);
  assign G8[22] = `SAC(br425,G7[22],`MASK_br425);
  assign P8[23] = `SAC(br426,P7[23],`MASK_br426);
  assign G8[23] = `SAC(br427,G7[23],`MASK_br427);
  assign P8[24] = `SAC(br428,P7[24],`MASK_br428);
  assign G8[24] = `SAC(br429,G7[24],`MASK_br429);
  assign P8[25] = `SAC(br430,P7[25],`MASK_br430);
  assign G8[25] = `SAC(br431,G7[25],`MASK_br431);
  assign P8[26] = `SAC(br432,P7[26],`MASK_br432);
  assign G8[26] = `SAC(br433,G7[26],`MASK_br433);
  assign P8[28] = `SAC(br434,P7[28],`MASK_br434);
  assign G8[28] = `SAC(br435,G7[28],`MASK_br435);
  assign P8[29] = `SAC(br436,P7[29],`MASK_br436);
  assign G8[29] = `SAC(br437,G7[29],`MASK_br437);
  assign P8[30] = `SAC(br438,P7[30],`MASK_br438);
  assign G8[30] = `SAC(br439,G7[30],`MASK_br439);
  assign P8[31] = `SAC(br440,P7[31],`MASK_br440);
  assign G8[31] = `SAC(br441,G7[31],`MASK_br441);
  assign P9[0] = `SAC(br442,P8[0],`MASK_br442);
  assign G9[0] = `SAC(br443,G8[0],`MASK_br443);
  assign P9[1] = `SAC(br444,P8[1],`MASK_br444);
  assign G9[1] = `SAC(br445,G8[1],`MASK_br445);
  assign P9[2] = `SAC(br446,P8[2],`MASK_br446);
  assign G9[2] = `SAC(br447,G8[2],`MASK_br447);
  assign P9[3] = `SAC(br448,P8[3],`MASK_br448);
  assign G9[3] = `SAC(br449,G8[3],`MASK_br449);
  assign P9[4] = `SAC(br450,P8[4],`MASK_br450);
  assign G9[4] = `SAC(br451,G8[4],`MASK_br451);
  assign P9[6] = `SAC(br452,P8[6],`MASK_br452);
  assign G9[6] = `SAC(br453,G8[6],`MASK_br453);
  assign P9[7] = `SAC(br454,P8[7],`MASK_br454);
  assign G9[7] = `SAC(br455,G8[7],`MASK_br455);
  assign P9[8] = `SAC(br456,P8[8],`MASK_br456);
  assign G9[8] = `SAC(br457,G8[8],`MASK_br457);
  assign P9[10] = `SAC(br458,P8[10],`MASK_br458);
  assign G9[10] = `SAC(br459,G8[10],`MASK_br459);
  assign P9[11] = `SAC(br460,P8[11],`MASK_br460);
  assign G9[11] = `SAC(br461,G8[11],`MASK_br461);
  assign P9[12] = `SAC(br462,P8[12],`MASK_br462);
  assign G9[12] = `SAC(br463,G8[12],`MASK_br463);
  assign P9[14] = `SAC(br464,P8[14],`MASK_br464);
  assign G9[14] = `SAC(br465,G8[14],`MASK_br465);
  assign P9[15] = `SAC(br466,P8[15],`MASK_br466);
  assign G9[15] = `SAC(br467,G8[15],`MASK_br467);
  assign P9[16] = `SAC(br468,P8[16],`MASK_br468);
  assign G9[16] = `SAC(br469,G8[16],`MASK_br469);
  assign P9[18] = `SAC(br470,P8[18],`MASK_br470);
  assign G9[18] = `SAC(br471,G8[18],`MASK_br471);
  assign P9[19] = `SAC(br472,P8[19],`MASK_br472);
  assign G9[19] = `SAC(br473,G8[19],`MASK_br473);
  assign P9[20] = `SAC(br474,P8[20],`MASK_br474);
  assign G9[20] = `SAC(br475,G8[20],`MASK_br475);
  assign P9[22] = `SAC(br476,P8[22],`MASK_br476);
  assign G9[22] = `SAC(br477,G8[22],`MASK_br477);
  assign P9[23] = `SAC(br478,P8[23],`MASK_br478);
  assign G9[23] = `SAC(br479,G8[23],`MASK_br479);
  assign P9[24] = `SAC(br480,P8[24],`MASK_br480);
  assign G9[24] = `SAC(br481,G8[24],`MASK_br481);
  assign P9[26] = `SAC(br482,P8[26],`MASK_br482);
  assign G9[26] = `SAC(br483,G8[26],`MASK_br483);
  assign P9[27] = `SAC(br484,P8[27],`MASK_br484);
  assign G9[27] = `SAC(br485,G8[27],`MASK_br485);
  assign P9[28] = `SAC(br486,P8[28],`MASK_br486);
  assign G9[28] = `SAC(br487,G8[28],`MASK_br487);
  assign P9[30] = `SAC(br488,P8[30],`MASK_br488);
  assign G9[30] = `SAC(br489,G8[30],`MASK_br489);
  assign P9[31] = `SAC(br490,P8[31],`MASK_br490);
  assign G9[31] = `SAC(br491,G8[31],`MASK_br491);
  assign P10[0] = `SAC(br492,P9[0],`MASK_br492);
  assign G10[0] = `SAC(br493,G9[0],`MASK_br493);
  assign P10[1] = `SAC(br494,P9[1],`MASK_br494);
  assign G10[1] = `SAC(br495,G9[1],`MASK_br495);
  assign P10[3] = `SAC(br496,P9[3],`MASK_br496);
  assign G10[3] = `SAC(br497,G9[3],`MASK_br497);
  assign P10[5] = `SAC(br498,P9[5],`MASK_br498);
  assign G10[5] = `SAC(br499,G9[5],`MASK_br499);
  assign P10[7] = `SAC(br500,P9[7],`MASK_br500);
  assign G10[7] = `SAC(br501,G9[7],`MASK_br501);
  assign P10[9] = `SAC(br502,P9[9],`MASK_br502);
  assign G10[9] = `SAC(br503,G9[9],`MASK_br503);
  assign P10[11] = `SAC(br504,P9[11],`MASK_br504);
  assign G10[11] = `SAC(br505,G9[11],`MASK_br505);
  assign P10[13] = `SAC(br506,P9[13],`MASK_br506);
  assign G10[13] = `SAC(br507,G9[13],`MASK_br507);
  assign P10[15] = `SAC(br508,P9[15],`MASK_br508);
  assign G10[15] = `SAC(br509,G9[15],`MASK_br509);
  assign P10[17] = `SAC(br510,P9[17],`MASK_br510);
  assign G10[17] = `SAC(br511,G9[17],`MASK_br511);
  assign P10[19] = `SAC(br512,P9[19],`MASK_br512);
  assign G10[19] = `SAC(br513,G9[19],`MASK_br513);
  assign P10[21] = `SAC(br514,P9[21],`MASK_br514);
  assign G10[21] = `SAC(br515,G9[21],`MASK_br515);
  assign P10[23] = `SAC(br516,P9[23],`MASK_br516);
  assign G10[23] = `SAC(br517,G9[23],`MASK_br517);
  assign P10[25] = `SAC(br518,P9[25],`MASK_br518);
  assign G10[25] = `SAC(br519,G9[25],`MASK_br519);
  assign P10[27] = `SAC(br520,P9[27],`MASK_br520);
  assign G10[27] = `SAC(br521,G9[27],`MASK_br521);
  assign P10[29] = `SAC(br522,P9[29],`MASK_br522);
  assign G10[29] = `SAC(br523,G9[29],`MASK_br523);
  assign P10[31] = `SAC(br524,P9[31],`MASK_br524);
  assign G10[31] = `SAC(br525,G9[31],`MASK_br525);
  assign S[0] = `SAC(br526,Cin,`MASK_br526) ^ `SAC(br527,P0[0],`MASK_br527);
  assign S[1] =  ( `SAC(br528,G10[0],`MASK_br528) |  ( `SAC(br529,P10[0],`MASK_br529) & `SAC(br530,Cin,`MASK_br530) ) ) ^  `SAC(br531,P0[1],`MASK_br531);
  assign S[2] =  ( `SAC(br532,G10[1],`MASK_br532) |  ( `SAC(br533,P10[1],`MASK_br533) & `SAC(br534,Cin,`MASK_br534) ) ) ^  `SAC(br535,P0[2],`MASK_br535);
  assign S[3] =  ( `SAC(br536,G10[2],`MASK_br536) |  ( `SAC(br537,P10[2],`MASK_br537) & `SAC(br538,Cin,`MASK_br538) ) ) ^  `SAC(br539,P0[3],`MASK_br539);
  assign S[4] =  ( `SAC(br540,G10[3],`MASK_br540) |  ( `SAC(br541,P10[3],`MASK_br541) & `SAC(br542,Cin,`MASK_br542) ) ) ^  `SAC(br543,P0[4],`MASK_br543);
  assign S[5] =  ( `SAC(br544,G10[4],`MASK_br544) |  ( `SAC(br545,P10[4],`MASK_br545) & `SAC(br546,Cin,`MASK_br546) ) ) ^  `SAC(br547,P0[5],`MASK_br547);
  assign S[6] =  ( `SAC(br548,G10[5],`MASK_br548) |  ( `SAC(br549,P10[5],`MASK_br549) & `SAC(br550,Cin,`MASK_br550) ) ) ^  `SAC(br551,P0[6],`MASK_br551);
  assign S[7] =  ( `SAC(br552,G10[6],`MASK_br552) |  ( `SAC(br553,P10[6],`MASK_br553) & `SAC(br554,Cin,`MASK_br554) ) ) ^  `SAC(br555,P0[7],`MASK_br555);
  assign S[8] =  ( `SAC(br556,G10[7],`MASK_br556) |  ( `SAC(br557,P10[7],`MASK_br557) & `SAC(br558,Cin,`MASK_br558) ) ) ^  `SAC(br559,P0[8],`MASK_br559);
  assign S[9] =  ( `SAC(br560,G10[8],`MASK_br560) |  ( `SAC(br561,P10[8],`MASK_br561) & `SAC(br562,Cin,`MASK_br562) ) ) ^  `SAC(br563,P0[9],`MASK_br563);
  assign S[10] = ( `SAC(br564,G10[9],`MASK_br564) |  ( `SAC(br565,P10[9],`MASK_br565) & `SAC(br566,Cin,`MASK_br566) ) ) ^  `SAC(br567,P0[10],`MASK_br567);
  assign S[11] = ( `SAC(br568,G10[10],`MASK_br568) | ( `SAC(br569,P10[10],`MASK_br569) & `SAC(br570,Cin,`MASK_br570) ) ) ^ `SAC(br571,P0[11],`MASK_br571);
  assign S[12] = ( `SAC(br572,G10[11],`MASK_br572) | ( `SAC(br573,P10[11],`MASK_br573) & `SAC(br574,Cin,`MASK_br574) ) ) ^ `SAC(br575,P0[12],`MASK_br575);
  assign S[13] = ( `SAC(br576,G10[12],`MASK_br576) | ( `SAC(br577,P10[12],`MASK_br577) & `SAC(br578,Cin,`MASK_br578) ) ) ^ `SAC(br579,P0[13],`MASK_br579);
  assign S[14] = ( `SAC(br580,G10[13],`MASK_br580) | ( `SAC(br581,P10[13],`MASK_br581) & `SAC(br582,Cin,`MASK_br582) ) ) ^ `SAC(br583,P0[14],`MASK_br583);
  assign S[15] = ( `SAC(br584,G10[14],`MASK_br584) | ( `SAC(br585,P10[14],`MASK_br585) & `SAC(br586,Cin,`MASK_br586) ) ) ^ `SAC(br587,P0[15],`MASK_br587);
  assign S[16] = ( `SAC(br588,G10[15],`MASK_br588) | ( `SAC(br589,P10[15],`MASK_br589) & `SAC(br590,Cin,`MASK_br590) ) ) ^ `SAC(br591,P0[16],`MASK_br591);
  assign S[17] = ( `SAC(br592,G10[16],`MASK_br592) | ( `SAC(br593,P10[16],`MASK_br593) & `SAC(br594,Cin,`MASK_br594) ) ) ^ `SAC(br595,P0[17],`MASK_br595);
  assign S[18] = ( `SAC(br596,G10[17],`MASK_br596) | ( `SAC(br597,P10[17],`MASK_br597) & `SAC(br598,Cin,`MASK_br598) ) ) ^ `SAC(br599,P0[18],`MASK_br599);
  assign S[19] = ( `SAC(br600,G10[18],`MASK_br600) | ( `SAC(br601,P10[18],`MASK_br601) & `SAC(br602,Cin,`MASK_br602) ) ) ^ `SAC(br603,P0[19],`MASK_br603);
  assign S[20] = ( `SAC(br604,G10[19],`MASK_br604) | ( `SAC(br605,P10[19],`MASK_br605) & `SAC(br606,Cin,`MASK_br606) ) ) ^ `SAC(br607,P0[20],`MASK_br607);
  assign S[21] = ( `SAC(br608,G10[20],`MASK_br608) | ( `SAC(br609,P10[20],`MASK_br609) & `SAC(br610,Cin,`MASK_br610) ) ) ^ `SAC(br611,P0[21],`MASK_br611);
  assign S[22] = ( `SAC(br612,G10[21],`MASK_br612) | ( `SAC(br613,P10[21],`MASK_br613) & `SAC(br614,Cin,`MASK_br614) ) ) ^ `SAC(br615,P0[22],`MASK_br615);
  assign S[23] = ( `SAC(br616,G10[22],`MASK_br616) | ( `SAC(br617,P10[22],`MASK_br617) & `SAC(br618,Cin,`MASK_br618) ) ) ^ `SAC(br619,P0[23],`MASK_br619);
  assign S[24] = ( `SAC(br620,G10[23],`MASK_br620) | ( `SAC(br621,P10[23],`MASK_br621) & `SAC(br622,Cin,`MASK_br622) ) ) ^ `SAC(br623,P0[24],`MASK_br623);
  assign S[25] = ( `SAC(br624,G10[24],`MASK_br624) | ( `SAC(br625,P10[24],`MASK_br625) & `SAC(br626,Cin,`MASK_br626) ) ) ^ `SAC(br627,P0[25],`MASK_br627);
  assign S[26] = ( `SAC(br628,G10[25],`MASK_br628) | ( `SAC(br629,P10[25],`MASK_br629) & `SAC(br630,Cin,`MASK_br630) ) ) ^ `SAC(br631,P0[26],`MASK_br631);
  assign S[27] = ( `SAC(br632,G10[26],`MASK_br632) | ( `SAC(br633,P10[26],`MASK_br633) & `SAC(br634,Cin,`MASK_br634) ) ) ^ `SAC(br635,P0[27],`MASK_br635);
  assign S[28] = ( `SAC(br636,G10[27],`MASK_br636) | ( `SAC(br637,P10[27],`MASK_br637) & `SAC(br638,Cin,`MASK_br638) ) ) ^ `SAC(br639,P0[28],`MASK_br639);
  assign S[29] = ( `SAC(br640,G10[28],`MASK_br640) | ( `SAC(br641,P10[28],`MASK_br641) & `SAC(br642,Cin,`MASK_br642) ) ) ^ `SAC(br643,P0[29],`MASK_br643);
  assign S[30] = ( `SAC(br644,G10[29],`MASK_br644) | ( `SAC(br645,P10[29],`MASK_br645) & `SAC(br646,Cin,`MASK_br646) ) ) ^ `SAC(br647,P0[30],`MASK_br647);
  assign S[31] = ( `SAC(br648,G10[30],`MASK_br648) | ( `SAC(br649,P10[30],`MASK_br649) & `SAC(br650,Cin,`MASK_br650) ) ) ^ `SAC(br651,P0[31],`MASK_br651);
  assign S[32] = `SAC(br652,G10[31],`MASK_br652) | ( `SAC(br653,P10[31],`MASK_br653) & `SAC(br654,Cin,`MASK_br654) );

  GPGenerator U0 (G0[0], P0[0], X[0], Y[0]);
  GPGenerator U1 (G0[1], P0[1], X[1], Y[1]);
  GPGenerator U2 (G0[2], P0[2], X[2], Y[2]);
  GPGenerator U3 (G0[3], P0[3], X[3], Y[3]);
  GPGenerator U4 (G0[4], P0[4], X[4], Y[4]);
  GPGenerator U5 (G0[5], P0[5], X[5], Y[5]);
  GPGenerator U6 (G0[6], P0[6], X[6], Y[6]);
  GPGenerator U7 (G0[7], P0[7], X[7], Y[7]);
  GPGenerator U8 (G0[8], P0[8], X[8], Y[8]);
  GPGenerator U9 (G0[9], P0[9], X[9], Y[9]);
  GPGenerator U10 (G0[10], P0[10], X[10], Y[10]);
  GPGenerator U11 (G0[11], P0[11], X[11], Y[11]);
  GPGenerator U12 (G0[12], P0[12], X[12], Y[12]);
  GPGenerator U13 (G0[13], P0[13], X[13], Y[13]);
  GPGenerator U14 (G0[14], P0[14], X[14], Y[14]);
  GPGenerator U15 (G0[15], P0[15], X[15], Y[15]);
  GPGenerator U16 (G0[16], P0[16], X[16], Y[16]);
  GPGenerator U17 (G0[17], P0[17], X[17], Y[17]);
  GPGenerator U18 (G0[18], P0[18], X[18], Y[18]);
  GPGenerator U19 (G0[19], P0[19], X[19], Y[19]);
  GPGenerator U20 (G0[20], P0[20], X[20], Y[20]);
  GPGenerator U21 (G0[21], P0[21], X[21], Y[21]);
  GPGenerator U22 (G0[22], P0[22], X[22], Y[22]);
  GPGenerator U23 (G0[23], P0[23], X[23], Y[23]);
  GPGenerator U24 (G0[24], P0[24], X[24], Y[24]);
  GPGenerator U25 (G0[25], P0[25], X[25], Y[25]);
  GPGenerator U26 (G0[26], P0[26], X[26], Y[26]);
  GPGenerator U27 (G0[27], P0[27], X[27], Y[27]);
  GPGenerator U28 (G0[28], P0[28], X[28], Y[28]);
  GPGenerator U29 (G0[29], P0[29], X[29], Y[29]);
  GPGenerator U30 (G0[30], P0[30], X[30], Y[30]);
  GPGenerator U31 (G0[31], P0[31], X[31], Y[31]);
  CarryOperator U32 (G1[1], P1[1], G0[1], P0[1], G0[0], P0[0]);
  CarryOperator U33 (G1[3], P1[3], G0[3], P0[3], G0[2], P0[2]);
  CarryOperator U34 (G1[5], P1[5], G0[5], P0[5], G0[4], P0[4]);
  CarryOperator U35 (G1[7], P1[7], G0[7], P0[7], G0[6], P0[6]);
  CarryOperator U36 (G1[9], P1[9], G0[9], P0[9], G0[8], P0[8]);
  CarryOperator U37 (G1[11], P1[11], G0[11], P0[11], G0[10], P0[10]);
  CarryOperator U38 (G1[13], P1[13], G0[13], P0[13], G0[12], P0[12]);
  CarryOperator U39 (G1[15], P1[15], G0[15], P0[15], G0[14], P0[14]);
  CarryOperator U40 (G1[17], P1[17], G0[17], P0[17], G0[16], P0[16]);
  CarryOperator U41 (G1[19], P1[19], G0[19], P0[19], G0[18], P0[18]);
  CarryOperator U42 (G1[21], P1[21], G0[21], P0[21], G0[20], P0[20]);
  CarryOperator U43 (G1[23], P1[23], G0[23], P0[23], G0[22], P0[22]);
  CarryOperator U44 (G1[25], P1[25], G0[25], P0[25], G0[24], P0[24]);
  CarryOperator U45 (G1[27], P1[27], G0[27], P0[27], G0[26], P0[26]);
  CarryOperator U46 (G1[29], P1[29], G0[29], P0[29], G0[28], P0[28]);
  CarryOperator U47 (G1[31], P1[31], G0[31], P0[31], G0[30], P0[30]);
  CarryOperator U48 (G2[3], P2[3], G1[3], P1[3], G1[1], P1[1]);
  CarryOperator U49 (G2[7], P2[7], G1[7], P1[7], G1[5], P1[5]);
  CarryOperator U50 (G2[11], P2[11], G1[11], P1[11], G1[9], P1[9]);
  CarryOperator U51 (G2[15], P2[15], G1[15], P1[15], G1[13], P1[13]);
  CarryOperator U52 (G2[19], P2[19], G1[19], P1[19], G1[17], P1[17]);
  CarryOperator U53 (G2[23], P2[23], G1[23], P1[23], G1[21], P1[21]);
  CarryOperator U54 (G2[27], P2[27], G1[27], P1[27], G1[25], P1[25]);
  CarryOperator U55 (G2[31], P2[31], G1[31], P1[31], G1[29], P1[29]);
  CarryOperator U56 (G3[7], P3[7], G2[7], P2[7], G2[3], P2[3]);
  CarryOperator U57 (G3[15], P3[15], G2[15], P2[15], G2[11], P2[11]);
  CarryOperator U58 (G3[23], P3[23], G2[23], P2[23], G2[19], P2[19]);
  CarryOperator U59 (G3[31], P3[31], G2[31], P2[31], G2[27], P2[27]);
  CarryOperator U60 (G4[15], P4[15], G3[15], P3[15], G3[7], P3[7]);
  CarryOperator U61 (G4[31], P4[31], G3[31], P3[31], G3[23], P3[23]);
  CarryOperator U62 (G5[31], P5[31], G4[31], P4[31], G4[15], P4[15]);
  CarryOperator U63 (G7[23], P7[23], G6[23], P6[23], G6[15], P6[15]);
  CarryOperator U64 (G8[11], P8[11], G7[11], P7[11], G7[7], P7[7]);
  CarryOperator U65 (G8[19], P8[19], G7[19], P7[19], G7[15], P7[15]);
  CarryOperator U66 (G8[27], P8[27], G7[27], P7[27], G7[23], P7[23]);
  CarryOperator U67 (G9[5], P9[5], G8[5], P8[5], G8[3], P8[3]);
  CarryOperator U68 (G9[9], P9[9], G8[9], P8[9], G8[7], P8[7]);
  CarryOperator U69 (G9[13], P9[13], G8[13], P8[13], G8[11], P8[11]);
  CarryOperator U70 (G9[17], P9[17], G8[17], P8[17], G8[15], P8[15]);
  CarryOperator U71 (G9[21], P9[21], G8[21], P8[21], G8[19], P8[19]);
  CarryOperator U72 (G9[25], P9[25], G8[25], P8[25], G8[23], P8[23]);
  CarryOperator U73 (G9[29], P9[29], G8[29], P8[29], G8[27], P8[27]);
  CarryOperator U74 (G10[2], P10[2], G9[2], P9[2], G9[1], P9[1]);
  CarryOperator U75 (G10[4], P10[4], G9[4], P9[4], G9[3], P9[3]);
  CarryOperator U76 (G10[6], P10[6], G9[6], P9[6], G9[5], P9[5]);
  CarryOperator U77 (G10[8], P10[8], G9[8], P9[8], G9[7], P9[7]);
  CarryOperator U78 (G10[10], P10[10], G9[10], P9[10], G9[9], P9[9]);
  CarryOperator U79 (G10[12], P10[12], G9[12], P9[12], G9[11], P9[11]);
  CarryOperator U80 (G10[14], P10[14], G9[14], P9[14], G9[13], P9[13]);
  CarryOperator U81 (G10[16], P10[16], G9[16], P9[16], G9[15], P9[15]);
  CarryOperator U82 (G10[18], P10[18], G9[18], P9[18], G9[17], P9[17]);
  CarryOperator U83 (G10[20], P10[20], G9[20], P9[20], G9[19], P9[19]);
  CarryOperator U84 (G10[22], P10[22], G9[22], P9[22], G9[21], P9[21]);
  CarryOperator U85 (G10[24], P10[24], G9[24], P9[24], G9[23], P9[23]);
  CarryOperator U86 (G10[26], P10[26], G9[26], P9[26], G9[25], P9[25]);
  CarryOperator U87 (G10[28], P10[28], G9[28], P9[28], G9[27], P9[27]);
  CarryOperator U88 (G10[30], P10[30], G9[30], P9[30], G9[29], P9[29]);
endmodule

module UBZero_0_0(O);
  output [0:0] O;
  assign O[0] = 0;
endmodule

module UBBKA_31_0_31_0 (S, X, Y);
  output [32:0] S;
  input [31:0] X;
  input [31:0] Y;
  UBPureBKA_31_0 U0 (S[32:0], X[31:0], Y[31:0]);
endmodule

module UBPureBKA_31_0 (S, X, Y);
  output [32:0] S;
  input [31:0] X;
  input [31:0] Y;
  wire C;
  UBPriBKA_31_0 U0 (S, X, Y, 1'b0);
  //UBZero_0_0 U1 (C);
endmodule
