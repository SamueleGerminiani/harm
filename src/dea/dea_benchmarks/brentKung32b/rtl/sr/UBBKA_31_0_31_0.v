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
`SR(s0,assign Go = A & B;,assign Go =1'b0;)
`SR(s1,assign Po = A ^ B;,assign Po =1'b0;)
endmodule

module CarryOperator(Go, Po, Gi1, Pi1, Gi2, Pi2);
output Go;
output Po;
input Gi1;
input Gi2;
input Pi1;
input Pi2;
`SR(s2,assign Go = Gi1 | ( Gi2 & Pi1 );,assign Go =1'b0;)
`SR(s3,assign Po = Pi1 & Pi2;,assign Po =1'b0;)
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



`SR(s4,assign P1[0] = P0[0];,assign P1[0] =1'b0;)
`SR(s5,assign G1[0] = G0[0];,assign G1[0] =1'b0;)
`SR(s6,assign P1[2] = P0[2];,assign P1[2] =1'b0;)
`SR(s7,assign G1[2] = G0[2];,assign G1[2] =1'b0;)
`SR(s8,assign P1[4] = P0[4];,assign P1[4] =1'b0;)
`SR(s9,assign G1[4] = G0[4];,assign G1[4] =1'b0;)
`SR(s10,assign P1[6] = P0[6];,assign P1[6] =1'b0;)
`SR(s11,assign G1[6] = G0[6];,assign G1[6] =1'b0;)
`SR(s12,assign P1[8] = P0[8];,assign P1[8] =1'b0;)
`SR(s13,assign G1[8] = G0[8];,assign G1[8] =1'b0;)
`SR(s14,assign P1[10] = P0[10];,assign P1[10] =1'b0;)
`SR(s15,assign G1[10] = G0[10];,assign G1[10] =1'b0;)
`SR(s16,assign P1[12] = P0[12];,assign P1[12] =1'b0;)
`SR(s17,assign G1[12] = G0[12];,assign G1[12] =1'b0;)
`SR(s18,assign P1[14] = P0[14];,assign P1[14] =1'b0;)
`SR(s19,assign G1[14] = G0[14];,assign G1[14] =1'b0;)
`SR(s20,assign P1[16] = P0[16];,assign P1[16] =1'b0;)
`SR(s21,assign G1[16] = G0[16];,assign G1[16] =1'b0;)
`SR(s22,assign P1[18] = P0[18];,assign P1[18] =1'b0;)
`SR(s23,assign G1[18] = G0[18];,assign G1[18] =1'b0;)
`SR(s24,assign P1[20] = P0[20];,assign P1[20] =1'b0;)
`SR(s25,assign G1[20] = G0[20];,assign G1[20] =1'b0;)
`SR(s26,assign P1[22] = P0[22];,assign P1[22] =1'b0;)
`SR(s27,assign G1[22] = G0[22];,assign G1[22] =1'b0;)
`SR(s28,assign P1[24] = P0[24];,assign P1[24] =1'b0;)
`SR(s29,assign G1[24] = G0[24];,assign G1[24] =1'b0;)
`SR(s30,assign P1[26] = P0[26];,assign P1[26] =1'b0;)
`SR(s31,assign G1[26] = G0[26];,assign G1[26] =1'b0;)
`SR(s32,assign P1[28] = P0[28];,assign P1[28] =1'b0;)
`SR(s33,assign G1[28] = G0[28];,assign G1[28] =1'b0;)
`SR(s34,assign P1[30] = P0[30];,assign P1[30] =1'b0;)
`SR(s35,assign G1[30] = G0[30];,assign G1[30] =1'b0;)
`SR(s36,assign P2[0] = P1[0];,assign P2[0] =1'b0;)
`SR(s37,assign G2[0] = G1[0];,assign G2[0] =1'b0;)
`SR(s38,assign P2[1] = P1[1];,assign P2[1] =1'b0;)
`SR(s39,assign G2[1] = G1[1];,assign G2[1] =1'b0;)
`SR(s40,assign P2[2] = P1[2];,assign P2[2] =1'b0;)
`SR(s41,assign G2[2] = G1[2];,assign G2[2] =1'b0;)
`SR(s42,assign P2[4] = P1[4];,assign P2[4] =1'b0;)
`SR(s43,assign G2[4] = G1[4];,assign G2[4] =1'b0;)
`SR(s44,assign P2[5] = P1[5];,assign P2[5] =1'b0;)
`SR(s45,assign G2[5] = G1[5];,assign G2[5] =1'b0;)
`SR(s46,assign P2[6] = P1[6];,assign P2[6] =1'b0;)
`SR(s47,assign G2[6] = G1[6];,assign G2[6] =1'b0;)
`SR(s48,assign P2[8] = P1[8];,assign P2[8] =1'b0;)
`SR(s49,assign G2[8] = G1[8];,assign G2[8] =1'b0;)
`SR(s50,assign P2[9] = P1[9];,assign P2[9] =1'b0;)
`SR(s51,assign G2[9] = G1[9];,assign G2[9] =1'b0;)
`SR(s52,assign P2[10] = P1[10];,assign P2[10] =1'b0;)
`SR(s53,assign G2[10] = G1[10];,assign G2[10] =1'b0;)
`SR(s54,assign P2[12] = P1[12];,assign P2[12] =1'b0;)
`SR(s55,assign G2[12] = G1[12];,assign G2[12] =1'b0;)
`SR(s56,assign P2[13] = P1[13];,assign P2[13] =1'b0;)
`SR(s57,assign G2[13] = G1[13];,assign G2[13] =1'b0;)
`SR(s58,assign P2[14] = P1[14];,assign P2[14] =1'b0;)
`SR(s59,assign G2[14] = G1[14];,assign G2[14] =1'b0;)
`SR(s60,assign P2[16] = P1[16];,assign P2[16] =1'b0;)
`SR(s61,assign G2[16] = G1[16];,assign G2[16] =1'b0;)
`SR(s62,assign P2[17] = P1[17];,assign P2[17] =1'b0;)
`SR(s63,assign G2[17] = G1[17];,assign G2[17] =1'b0;)
`SR(s64,assign P2[18] = P1[18];,assign P2[18] =1'b0;)
`SR(s65,assign G2[18] = G1[18];,assign G2[18] =1'b0;)
`SR(s66,assign P2[20] = P1[20];,assign P2[20] =1'b0;)
`SR(s67,assign G2[20] = G1[20];,assign G2[20] =1'b0;)
`SR(s68,assign P2[21] = P1[21];,assign P2[21] =1'b0;)
`SR(s69,assign G2[21] = G1[21];,assign G2[21] =1'b0;)
`SR(s70,assign P2[22] = P1[22];,assign P2[22] =1'b0;)
`SR(s71,assign G2[22] = G1[22];,assign G2[22] =1'b0;)
`SR(s72,assign P2[24] = P1[24];,assign P2[24] =1'b0;)
`SR(s73,assign G2[24] = G1[24];,assign G2[24] =1'b0;)
`SR(s74,assign P2[25] = P1[25];,assign P2[25] =1'b0;)
`SR(s75,assign G2[25] = G1[25];,assign G2[25] =1'b0;)
`SR(s76,assign P2[26] = P1[26];,assign P2[26] =1'b0;)
`SR(s77,assign G2[26] = G1[26];,assign G2[26] =1'b0;)
`SR(s78,assign P2[28] = P1[28];,assign P2[28] =1'b0;)
`SR(s79,assign G2[28] = G1[28];,assign G2[28] =1'b0;)
`SR(s80,assign P2[29] = P1[29];,assign P2[29] =1'b0;)
`SR(s81,assign G2[29] = G1[29];,assign G2[29] =1'b0;)
`SR(s82,assign P2[30] = P1[30];,assign P2[30] =1'b0;)
`SR(s83,assign G2[30] = G1[30];,assign G2[30] =1'b0;)
`SR(s84,assign P3[0] = P2[0];,assign P3[0] =1'b0;)
`SR(s85,assign G3[0] = G2[0];,assign G3[0] =1'b0;)
`SR(s86,assign P3[1] = P2[1];,assign P3[1] =1'b0;)
`SR(s87,assign G3[1] = G2[1];,assign G3[1] =1'b0;)
`SR(s88,assign P3[2] = P2[2];,assign P3[2] =1'b0;)
`SR(s89,assign G3[2] = G2[2];,assign G3[2] =1'b0;)
`SR(s90,assign P3[3] = P2[3];,assign P3[3] =1'b0;)
`SR(s91,assign G3[3] = G2[3];,assign G3[3] =1'b0;)
`SR(s92,assign P3[4] = P2[4];,assign P3[4] =1'b0;)
`SR(s93,assign G3[4] = G2[4];,assign G3[4] =1'b0;)
`SR(s94,assign P3[5] = P2[5];,assign P3[5] =1'b0;)
`SR(s95,assign G3[5] = G2[5];,assign G3[5] =1'b0;)
`SR(s96,assign P3[6] = P2[6];,assign P3[6] =1'b0;)
`SR(s97,assign G3[6] = G2[6];,assign G3[6] =1'b0;)
`SR(s98,assign P3[8] = P2[8];,assign P3[8] =1'b0;)
`SR(s99,assign G3[8] = G2[8];,assign G3[8] =1'b0;)
`SR(s100,assign P3[9] = P2[9];,assign P3[9] =1'b0;)
`SR(s101,assign G3[9] = G2[9];,assign G3[9] =1'b0;)
`SR(s102,assign P3[10] = P2[10];,assign P3[10] =1'b0;)
`SR(s103,assign G3[10] = G2[10];,assign G3[10] =1'b0;)
`SR(s104,assign P3[11] = P2[11];,assign P3[11] =1'b0;)
`SR(s105,assign G3[11] = G2[11];,assign G3[11] =1'b0;)
`SR(s106,assign P3[12] = P2[12];,assign P3[12] =1'b0;)
`SR(s107,assign G3[12] = G2[12];,assign G3[12] =1'b0;)
`SR(s108,assign P3[13] = P2[13];,assign P3[13] =1'b0;)
`SR(s109,assign G3[13] = G2[13];,assign G3[13] =1'b0;)
`SR(s110,assign P3[14] = P2[14];,assign P3[14] =1'b0;)
`SR(s111,assign G3[14] = G2[14];,assign G3[14] =1'b0;)
`SR(s112,assign P3[16] = P2[16];,assign P3[16] =1'b0;)
`SR(s113,assign G3[16] = G2[16];,assign G3[16] =1'b0;)
`SR(s114,assign P3[17] = P2[17];,assign P3[17] =1'b0;)
`SR(s115,assign G3[17] = G2[17];,assign G3[17] =1'b0;)
`SR(s116,assign P3[18] = P2[18];,assign P3[18] =1'b0;)
`SR(s117,assign G3[18] = G2[18];,assign G3[18] =1'b0;)
`SR(s118,assign P3[19] = P2[19];,assign P3[19] =1'b0;)
`SR(s119,assign G3[19] = G2[19];,assign G3[19] =1'b0;)
`SR(s120,assign P3[20] = P2[20];,assign P3[20] =1'b0;)
`SR(s121,assign G3[20] = G2[20];,assign G3[20] =1'b0;)
`SR(s122,assign P3[21] = P2[21];,assign P3[21] =1'b0;)
`SR(s123,assign G3[21] = G2[21];,assign G3[21] =1'b0;)
`SR(s124,assign P3[22] = P2[22];,assign P3[22] =1'b0;)
`SR(s125,assign G3[22] = G2[22];,assign G3[22] =1'b0;)
`SR(s126,assign P3[24] = P2[24];,assign P3[24] =1'b0;)
`SR(s127,assign G3[24] = G2[24];,assign G3[24] =1'b0;)
`SR(s128,assign P3[25] = P2[25];,assign P3[25] =1'b0;)
`SR(s129,assign G3[25] = G2[25];,assign G3[25] =1'b0;)
`SR(s130,assign P3[26] = P2[26];,assign P3[26] =1'b0;)
`SR(s131,assign G3[26] = G2[26];,assign G3[26] =1'b0;)
`SR(s132,assign P3[27] = P2[27];,assign P3[27] =1'b0;)
`SR(s133,assign G3[27] = G2[27];,assign G3[27] =1'b0;)
`SR(s134,assign P3[28] = P2[28];,assign P3[28] =1'b0;)
`SR(s135,assign G3[28] = G2[28];,assign G3[28] =1'b0;)
`SR(s136,assign P3[29] = P2[29];,assign P3[29] =1'b0;)
`SR(s137,assign G3[29] = G2[29];,assign G3[29] =1'b0;)
`SR(s138,assign P3[30] = P2[30];,assign P3[30] =1'b0;)
`SR(s139,assign G3[30] = G2[30];,assign G3[30] =1'b0;)
`SR(s140,assign P4[0] = P3[0];,assign P4[0] =1'b0;)
`SR(s141,assign G4[0] = G3[0];,assign G4[0] =1'b0;)
`SR(s142,assign P4[1] = P3[1];,assign P4[1] =1'b0;)
`SR(s143,assign G4[1] = G3[1];,assign G4[1] =1'b0;)
`SR(s144,assign P4[2] = P3[2];,assign P4[2] =1'b0;)
`SR(s145,assign G4[2] = G3[2];,assign G4[2] =1'b0;)
`SR(s146,assign P4[3] = P3[3];,assign P4[3] =1'b0;)
`SR(s147,assign G4[3] = G3[3];,assign G4[3] =1'b0;)
`SR(s148,assign P4[4] = P3[4];,assign P4[4] =1'b0;)
`SR(s149,assign G4[4] = G3[4];,assign G4[4] =1'b0;)
`SR(s150,assign P4[5] = P3[5];,assign P4[5] =1'b0;)
`SR(s151,assign G4[5] = G3[5];,assign G4[5] =1'b0;)
`SR(s152,assign P4[6] = P3[6];,assign P4[6] =1'b0;)
`SR(s153,assign G4[6] = G3[6];,assign G4[6] =1'b0;)
`SR(s154,assign P4[7] = P3[7];,assign P4[7] =1'b0;)
`SR(s155,assign G4[7] = G3[7];,assign G4[7] =1'b0;)
`SR(s156,assign P4[8] = P3[8];,assign P4[8] =1'b0;)
`SR(s157,assign G4[8] = G3[8];,assign G4[8] =1'b0;)
`SR(s158,assign P4[9] = P3[9];,assign P4[9] =1'b0;)
`SR(s159,assign G4[9] = G3[9];,assign G4[9] =1'b0;)
`SR(s160,assign P4[10] = P3[10];,assign P4[10] =1'b0;)
`SR(s161,assign G4[10] = G3[10];,assign G4[10] =1'b0;)
`SR(s162,assign P4[11] = P3[11];,assign P4[11] =1'b0;)
`SR(s163,assign G4[11] = G3[11];,assign G4[11] =1'b0;)
`SR(s164,assign P4[12] = P3[12];,assign P4[12] =1'b0;)
`SR(s165,assign G4[12] = G3[12];,assign G4[12] =1'b0;)
`SR(s166,assign P4[13] = P3[13];,assign P4[13] =1'b0;)
`SR(s167,assign G4[13] = G3[13];,assign G4[13] =1'b0;)
`SR(s168,assign P4[14] = P3[14];,assign P4[14] =1'b0;)
`SR(s169,assign G4[14] = G3[14];,assign G4[14] =1'b0;)
`SR(s170,assign P4[16] = P3[16];,assign P4[16] =1'b0;)
`SR(s171,assign G4[16] = G3[16];,assign G4[16] =1'b0;)
`SR(s172,assign P4[17] = P3[17];,assign P4[17] =1'b0;)
`SR(s173,assign G4[17] = G3[17];,assign G4[17] =1'b0;)
`SR(s174,assign P4[18] = P3[18];,assign P4[18] =1'b0;)
`SR(s175,assign G4[18] = G3[18];,assign G4[18] =1'b0;)
`SR(s176,assign P4[19] = P3[19];,assign P4[19] =1'b0;)
`SR(s177,assign G4[19] = G3[19];,assign G4[19] =1'b0;)
`SR(s178,assign P4[20] = P3[20];,assign P4[20] =1'b0;)
`SR(s179,assign G4[20] = G3[20];,assign G4[20] =1'b0;)
`SR(s180,assign P4[21] = P3[21];,assign P4[21] =1'b0;)
`SR(s181,assign G4[21] = G3[21];,assign G4[21] =1'b0;)
`SR(s182,assign P4[22] = P3[22];,assign P4[22] =1'b0;)
`SR(s183,assign G4[22] = G3[22];,assign G4[22] =1'b0;)
`SR(s184,assign P4[23] = P3[23];,assign P4[23] =1'b0;)
`SR(s185,assign G4[23] = G3[23];,assign G4[23] =1'b0;)
`SR(s186,assign P4[24] = P3[24];,assign P4[24] =1'b0;)
`SR(s187,assign G4[24] = G3[24];,assign G4[24] =1'b0;)
`SR(s188,assign P4[25] = P3[25];,assign P4[25] =1'b0;)
`SR(s189,assign G4[25] = G3[25];,assign G4[25] =1'b0;)
`SR(s190,assign P4[26] = P3[26];,assign P4[26] =1'b0;)
`SR(s191,assign G4[26] = G3[26];,assign G4[26] =1'b0;)
`SR(s192,assign P4[27] = P3[27];,assign P4[27] =1'b0;)
`SR(s193,assign G4[27] = G3[27];,assign G4[27] =1'b0;)
`SR(s194,assign P4[28] = P3[28];,assign P4[28] =1'b0;)
`SR(s195,assign G4[28] = G3[28];,assign G4[28] =1'b0;)
`SR(s196,assign P4[29] = P3[29];,assign P4[29] =1'b0;)
`SR(s197,assign G4[29] = G3[29];,assign G4[29] =1'b0;)
`SR(s198,assign P4[30] = P3[30];,assign P4[30] =1'b0;)
`SR(s199,assign G4[30] = G3[30];,assign G4[30] =1'b0;)
`SR(s200,assign P5[0] = P4[0];,assign P5[0] =1'b0;)
`SR(s201,assign G5[0] = G4[0];,assign G5[0] =1'b0;)
`SR(s202,assign P5[1] = P4[1];,assign P5[1] =1'b0;)
`SR(s203,assign G5[1] = G4[1];,assign G5[1] =1'b0;)
`SR(s204,assign P5[2] = P4[2];,assign P5[2] =1'b0;)
`SR(s205,assign G5[2] = G4[2];,assign G5[2] =1'b0;)
`SR(s206,assign P5[3] = P4[3];,assign P5[3] =1'b0;)
`SR(s207,assign G5[3] = G4[3];,assign G5[3] =1'b0;)
`SR(s208,assign P5[4] = P4[4];,assign P5[4] =1'b0;)
`SR(s209,assign G5[4] = G4[4];,assign G5[4] =1'b0;)
`SR(s210,assign P5[5] = P4[5];,assign P5[5] =1'b0;)
`SR(s211,assign G5[5] = G4[5];,assign G5[5] =1'b0;)
`SR(s212,assign P5[6] = P4[6];,assign P5[6] =1'b0;)
`SR(s213,assign G5[6] = G4[6];,assign G5[6] =1'b0;)
`SR(s214,assign P5[7] = P4[7];,assign P5[7] =1'b0;)
`SR(s215,assign G5[7] = G4[7];,assign G5[7] =1'b0;)
`SR(s216,assign P5[8] = P4[8];,assign P5[8] =1'b0;)
`SR(s217,assign G5[8] = G4[8];,assign G5[8] =1'b0;)
`SR(s218,assign P5[9] = P4[9];,assign P5[9] =1'b0;)
`SR(s219,assign G5[9] = G4[9];,assign G5[9] =1'b0;)
`SR(s220,assign P5[10] = P4[10];,assign P5[10] =1'b0;)
`SR(s221,assign G5[10] = G4[10];,assign G5[10] =1'b0;)
`SR(s222,assign P5[11] = P4[11];,assign P5[11] =1'b0;)
`SR(s223,assign G5[11] = G4[11];,assign G5[11] =1'b0;)
`SR(s224,assign P5[12] = P4[12];,assign P5[12] =1'b0;)
`SR(s225,assign G5[12] = G4[12];,assign G5[12] =1'b0;)
`SR(s226,assign P5[13] = P4[13];,assign P5[13] =1'b0;)
`SR(s227,assign G5[13] = G4[13];,assign G5[13] =1'b0;)
`SR(s228,assign P5[14] = P4[14];,assign P5[14] =1'b0;)
`SR(s229,assign G5[14] = G4[14];,assign G5[14] =1'b0;)
`SR(s230,assign P5[15] = P4[15];,assign P5[15] =1'b0;)
`SR(s231,assign G5[15] = G4[15];,assign G5[15] =1'b0;)
`SR(s232,assign P5[16] = P4[16];,assign P5[16] =1'b0;)
`SR(s233,assign G5[16] = G4[16];,assign G5[16] =1'b0;)
`SR(s234,assign P5[17] = P4[17];,assign P5[17] =1'b0;)
`SR(s235,assign G5[17] = G4[17];,assign G5[17] =1'b0;)
`SR(s236,assign P5[18] = P4[18];,assign P5[18] =1'b0;)
`SR(s237,assign G5[18] = G4[18];,assign G5[18] =1'b0;)
`SR(s238,assign P5[19] = P4[19];,assign P5[19] =1'b0;)
`SR(s239,assign G5[19] = G4[19];,assign G5[19] =1'b0;)
`SR(s240,assign P5[20] = P4[20];,assign P5[20] =1'b0;)
`SR(s241,assign G5[20] = G4[20];,assign G5[20] =1'b0;)
`SR(s242,assign P5[21] = P4[21];,assign P5[21] =1'b0;)
`SR(s243,assign G5[21] = G4[21];,assign G5[21] =1'b0;)
`SR(s244,assign P5[22] = P4[22];,assign P5[22] =1'b0;)
`SR(s245,assign G5[22] = G4[22];,assign G5[22] =1'b0;)
`SR(s246,assign P5[23] = P4[23];,assign P5[23] =1'b0;)
`SR(s247,assign G5[23] = G4[23];,assign G5[23] =1'b0;)
`SR(s248,assign P5[24] = P4[24];,assign P5[24] =1'b0;)
`SR(s249,assign G5[24] = G4[24];,assign G5[24] =1'b0;)
`SR(s250,assign P5[25] = P4[25];,assign P5[25] =1'b0;)
`SR(s251,assign G5[25] = G4[25];,assign G5[25] =1'b0;)
`SR(s252,assign P5[26] = P4[26];,assign P5[26] =1'b0;)
`SR(s253,assign G5[26] = G4[26];,assign G5[26] =1'b0;)
`SR(s254,assign P5[27] = P4[27];,assign P5[27] =1'b0;)
`SR(s255,assign G5[27] = G4[27];,assign G5[27] =1'b0;)
`SR(s256,assign P5[28] = P4[28];,assign P5[28] =1'b0;)
`SR(s257,assign G5[28] = G4[28];,assign G5[28] =1'b0;)
`SR(s258,assign P5[29] = P4[29];,assign P5[29] =1'b0;)
`SR(s259,assign G5[29] = G4[29];,assign G5[29] =1'b0;)
`SR(s260,assign P5[30] = P4[30];,assign P5[30] =1'b0;)
`SR(s261,assign G5[30] = G4[30];,assign G5[30] =1'b0;)
`SR(s262,assign P6[0] = P5[0];,assign P6[0] =1'b0;)
`SR(s263,assign G6[0] = G5[0];,assign G6[0] =1'b0;)
`SR(s264,assign P6[1] = P5[1];,assign P6[1] =1'b0;)
`SR(s265,assign G6[1] = G5[1];,assign G6[1] =1'b0;)
`SR(s266,assign P6[2] = P5[2];,assign P6[2] =1'b0;)
`SR(s267,assign G6[2] = G5[2];,assign G6[2] =1'b0;)
`SR(s268,assign P6[3] = P5[3];,assign P6[3] =1'b0;)
`SR(s269,assign G6[3] = G5[3];,assign G6[3] =1'b0;)
`SR(s270,assign P6[4] = P5[4];,assign P6[4] =1'b0;)
`SR(s271,assign G6[4] = G5[4];,assign G6[4] =1'b0;)
`SR(s272,assign P6[5] = P5[5];,assign P6[5] =1'b0;)
`SR(s273,assign G6[5] = G5[5];,assign G6[5] =1'b0;)
`SR(s274,assign P6[6] = P5[6];,assign P6[6] =1'b0;)
`SR(s275,assign G6[6] = G5[6];,assign G6[6] =1'b0;)
`SR(s276,assign P6[7] = P5[7];,assign P6[7] =1'b0;)
`SR(s277,assign G6[7] = G5[7];,assign G6[7] =1'b0;)
`SR(s278,assign P6[8] = P5[8];,assign P6[8] =1'b0;)
`SR(s279,assign G6[8] = G5[8];,assign G6[8] =1'b0;)
`SR(s280,assign P6[9] = P5[9];,assign P6[9] =1'b0;)
`SR(s281,assign G6[9] = G5[9];,assign G6[9] =1'b0;)
`SR(s282,assign P6[10] = P5[10];,assign P6[10] =1'b0;)
`SR(s283,assign G6[10] = G5[10];,assign G6[10] =1'b0;)
`SR(s284,assign P6[11] = P5[11];,assign P6[11] =1'b0;)
`SR(s285,assign G6[11] = G5[11];,assign G6[11] =1'b0;)
`SR(s286,assign P6[12] = P5[12];,assign P6[12] =1'b0;)
`SR(s287,assign G6[12] = G5[12];,assign G6[12] =1'b0;)
`SR(s288,assign P6[13] = P5[13];,assign P6[13] =1'b0;)
`SR(s289,assign G6[13] = G5[13];,assign G6[13] =1'b0;)
`SR(s290,assign P6[14] = P5[14];,assign P6[14] =1'b0;)
`SR(s291,assign G6[14] = G5[14];,assign G6[14] =1'b0;)
`SR(s292,assign P6[15] = P5[15];,assign P6[15] =1'b0;)
`SR(s293,assign G6[15] = G5[15];,assign G6[15] =1'b0;)
`SR(s294,assign P6[16] = P5[16];,assign P6[16] =1'b0;)
`SR(s295,assign G6[16] = G5[16];,assign G6[16] =1'b0;)
`SR(s296,assign P6[17] = P5[17];,assign P6[17] =1'b0;)
`SR(s297,assign G6[17] = G5[17];,assign G6[17] =1'b0;)
`SR(s298,assign P6[18] = P5[18];,assign P6[18] =1'b0;)
`SR(s299,assign G6[18] = G5[18];,assign G6[18] =1'b0;)
`SR(s300,assign P6[19] = P5[19];,assign P6[19] =1'b0;)
`SR(s301,assign G6[19] = G5[19];,assign G6[19] =1'b0;)
`SR(s302,assign P6[20] = P5[20];,assign P6[20] =1'b0;)
`SR(s303,assign G6[20] = G5[20];,assign G6[20] =1'b0;)
`SR(s304,assign P6[21] = P5[21];,assign P6[21] =1'b0;)
`SR(s305,assign G6[21] = G5[21];,assign G6[21] =1'b0;)
`SR(s306,assign P6[22] = P5[22];,assign P6[22] =1'b0;)
`SR(s307,assign G6[22] = G5[22];,assign G6[22] =1'b0;)
`SR(s308,assign P6[23] = P5[23];,assign P6[23] =1'b0;)
`SR(s309,assign G6[23] = G5[23];,assign G6[23] =1'b0;)
`SR(s310,assign P6[24] = P5[24];,assign P6[24] =1'b0;)
`SR(s311,assign G6[24] = G5[24];,assign G6[24] =1'b0;)
`SR(s312,assign P6[25] = P5[25];,assign P6[25] =1'b0;)
`SR(s313,assign G6[25] = G5[25];,assign G6[25] =1'b0;)
`SR(s314,assign P6[26] = P5[26];,assign P6[26] =1'b0;)
`SR(s315,assign G6[26] = G5[26];,assign G6[26] =1'b0;)
`SR(s316,assign P6[27] = P5[27];,assign P6[27] =1'b0;)
`SR(s317,assign G6[27] = G5[27];,assign G6[27] =1'b0;)
`SR(s318,assign P6[28] = P5[28];,assign P6[28] =1'b0;)
`SR(s319,assign G6[28] = G5[28];,assign G6[28] =1'b0;)
`SR(s320,assign P6[29] = P5[29];,assign P6[29] =1'b0;)
`SR(s321,assign G6[29] = G5[29];,assign G6[29] =1'b0;)
`SR(s322,assign P6[30] = P5[30];,assign P6[30] =1'b0;)
`SR(s323,assign G6[30] = G5[30];,assign G6[30] =1'b0;)
`SR(s324,assign P6[31] = P5[31];,assign P6[31] =1'b0;)
`SR(s325,assign G6[31] = G5[31];,assign G6[31] =1'b0;)
`SR(s326,assign P7[0] = P6[0];,assign P7[0] =1'b0;)
`SR(s327,assign G7[0] = G6[0];,assign G7[0] =1'b0;)
`SR(s328,assign P7[1] = P6[1];,assign P7[1] =1'b0;)
`SR(s329,assign G7[1] = G6[1];,assign G7[1] =1'b0;)
`SR(s330,assign P7[2] = P6[2];,assign P7[2] =1'b0;)
`SR(s331,assign G7[2] = G6[2];,assign G7[2] =1'b0;)
`SR(s332,assign P7[3] = P6[3];,assign P7[3] =1'b0;)
`SR(s333,assign G7[3] = G6[3];,assign G7[3] =1'b0;)
`SR(s334,assign P7[4] = P6[4];,assign P7[4] =1'b0;)
`SR(s335,assign G7[4] = G6[4];,assign G7[4] =1'b0;)
`SR(s336,assign P7[5] = P6[5];,assign P7[5] =1'b0;)
`SR(s337,assign G7[5] = G6[5];,assign G7[5] =1'b0;)
`SR(s338,assign P7[6] = P6[6];,assign P7[6] =1'b0;)
`SR(s339,assign G7[6] = G6[6];,assign G7[6] =1'b0;)
`SR(s340,assign P7[7] = P6[7];,assign P7[7] =1'b0;)
`SR(s341,assign G7[7] = G6[7];,assign G7[7] =1'b0;)
`SR(s342,assign P7[8] = P6[8];,assign P7[8] =1'b0;)
`SR(s343,assign G7[8] = G6[8];,assign G7[8] =1'b0;)
`SR(s344,assign P7[9] = P6[9];,assign P7[9] =1'b0;)
`SR(s345,assign G7[9] = G6[9];,assign G7[9] =1'b0;)
`SR(s346,assign P7[10] = P6[10];,assign P7[10] =1'b0;)
`SR(s347,assign G7[10] = G6[10];,assign G7[10] =1'b0;)
`SR(s348,assign P7[11] = P6[11];,assign P7[11] =1'b0;)
`SR(s349,assign G7[11] = G6[11];,assign G7[11] =1'b0;)
`SR(s350,assign P7[12] = P6[12];,assign P7[12] =1'b0;)
`SR(s351,assign G7[12] = G6[12];,assign G7[12] =1'b0;)
`SR(s352,assign P7[13] = P6[13];,assign P7[13] =1'b0;)
`SR(s353,assign G7[13] = G6[13];,assign G7[13] =1'b0;)
`SR(s354,assign P7[14] = P6[14];,assign P7[14] =1'b0;)
`SR(s355,assign G7[14] = G6[14];,assign G7[14] =1'b0;)
`SR(s356,assign P7[15] = P6[15];,assign P7[15] =1'b0;)
`SR(s357,assign G7[15] = G6[15];,assign G7[15] =1'b0;)
`SR(s358,assign P7[16] = P6[16];,assign P7[16] =1'b0;)
`SR(s359,assign G7[16] = G6[16];,assign G7[16] =1'b0;)
`SR(s360,assign P7[17] = P6[17];,assign P7[17] =1'b0;)
`SR(s361,assign G7[17] = G6[17];,assign G7[17] =1'b0;)
`SR(s362,assign P7[18] = P6[18];,assign P7[18] =1'b0;)
`SR(s363,assign G7[18] = G6[18];,assign G7[18] =1'b0;)
`SR(s364,assign P7[19] = P6[19];,assign P7[19] =1'b0;)
`SR(s365,assign G7[19] = G6[19];,assign G7[19] =1'b0;)
`SR(s366,assign P7[20] = P6[20];,assign P7[20] =1'b0;)
`SR(s367,assign G7[20] = G6[20];,assign G7[20] =1'b0;)
`SR(s368,assign P7[21] = P6[21];,assign P7[21] =1'b0;)
`SR(s369,assign G7[21] = G6[21];,assign G7[21] =1'b0;)
`SR(s370,assign P7[22] = P6[22];,assign P7[22] =1'b0;)
`SR(s371,assign G7[22] = G6[22];,assign G7[22] =1'b0;)
`SR(s372,assign P7[24] = P6[24];,assign P7[24] =1'b0;)
`SR(s373,assign G7[24] = G6[24];,assign G7[24] =1'b0;)
`SR(s374,assign P7[25] = P6[25];,assign P7[25] =1'b0;)
`SR(s375,assign G7[25] = G6[25];,assign G7[25] =1'b0;)
`SR(s376,assign P7[26] = P6[26];,assign P7[26] =1'b0;)
`SR(s377,assign G7[26] = G6[26];,assign G7[26] =1'b0;)
`SR(s378,assign P7[27] = P6[27];,assign P7[27] =1'b0;)
`SR(s379,assign G7[27] = G6[27];,assign G7[27] =1'b0;)
`SR(s380,assign P7[28] = P6[28];,assign P7[28] =1'b0;)
`SR(s381,assign G7[28] = G6[28];,assign G7[28] =1'b0;)
`SR(s382,assign P7[29] = P6[29];,assign P7[29] =1'b0;)
`SR(s383,assign G7[29] = G6[29];,assign G7[29] =1'b0;)
`SR(s384,assign P7[30] = P6[30];,assign P7[30] =1'b0;)
`SR(s385,assign G7[30] = G6[30];,assign G7[30] =1'b0;)
`SR(s386,assign P7[31] = P6[31];,assign P7[31] =1'b0;)
`SR(s387,assign G7[31] = G6[31];,assign G7[31] =1'b0;)
`SR(s388,assign P8[0] = P7[0];,assign P8[0] =1'b0;)
`SR(s389,assign G8[0] = G7[0];,assign G8[0] =1'b0;)
`SR(s390,assign P8[1] = P7[1];,assign P8[1] =1'b0;)
`SR(s391,assign G8[1] = G7[1];,assign G8[1] =1'b0;)
`SR(s392,assign P8[2] = P7[2];,assign P8[2] =1'b0;)
`SR(s393,assign G8[2] = G7[2];,assign G8[2] =1'b0;)
`SR(s394,assign P8[3] = P7[3];,assign P8[3] =1'b0;)
`SR(s395,assign G8[3] = G7[3];,assign G8[3] =1'b0;)
`SR(s396,assign P8[4] = P7[4];,assign P8[4] =1'b0;)
`SR(s397,assign G8[4] = G7[4];,assign G8[4] =1'b0;)
`SR(s398,assign P8[5] = P7[5];,assign P8[5] =1'b0;)
`SR(s399,assign G8[5] = G7[5];,assign G8[5] =1'b0;)
`SR(s400,assign P8[6] = P7[6];,assign P8[6] =1'b0;)
`SR(s401,assign G8[6] = G7[6];,assign G8[6] =1'b0;)
`SR(s402,assign P8[7] = P7[7];,assign P8[7] =1'b0;)
`SR(s403,assign G8[7] = G7[7];,assign G8[7] =1'b0;)
`SR(s404,assign P8[8] = P7[8];,assign P8[8] =1'b0;)
`SR(s405,assign G8[8] = G7[8];,assign G8[8] =1'b0;)
`SR(s406,assign P8[9] = P7[9];,assign P8[9] =1'b0;)
`SR(s407,assign G8[9] = G7[9];,assign G8[9] =1'b0;)
`SR(s408,assign P8[10] = P7[10];,assign P8[10] =1'b0;)
`SR(s409,assign G8[10] = G7[10];,assign G8[10] =1'b0;)
`SR(s410,assign P8[12] = P7[12];,assign P8[12] =1'b0;)
`SR(s411,assign G8[12] = G7[12];,assign G8[12] =1'b0;)
`SR(s412,assign P8[13] = P7[13];,assign P8[13] =1'b0;)
`SR(s413,assign G8[13] = G7[13];,assign G8[13] =1'b0;)
`SR(s414,assign P8[14] = P7[14];,assign P8[14] =1'b0;)
`SR(s415,assign G8[14] = G7[14];,assign G8[14] =1'b0;)
`SR(s416,assign P8[15] = P7[15];,assign P8[15] =1'b0;)
`SR(s417,assign G8[15] = G7[15];,assign G8[15] =1'b0;)
`SR(s418,assign P8[16] = P7[16];,assign P8[16] =1'b0;)
`SR(s419,assign G8[16] = G7[16];,assign G8[16] =1'b0;)
`SR(s420,assign P8[17] = P7[17];,assign P8[17] =1'b0;)
`SR(s421,assign G8[17] = G7[17];,assign G8[17] =1'b0;)
`SR(s422,assign P8[18] = P7[18];,assign P8[18] =1'b0;)
`SR(s423,assign G8[18] = G7[18];,assign G8[18] =1'b0;)
`SR(s424,assign P8[20] = P7[20];,assign P8[20] =1'b0;)
`SR(s425,assign G8[20] = G7[20];,assign G8[20] =1'b0;)
`SR(s426,assign P8[21] = P7[21];,assign P8[21] =1'b0;)
`SR(s427,assign G8[21] = G7[21];,assign G8[21] =1'b0;)
`SR(s428,assign P8[22] = P7[22];,assign P8[22] =1'b0;)
`SR(s429,assign G8[22] = G7[22];,assign G8[22] =1'b0;)
`SR(s430,assign P8[23] = P7[23];,assign P8[23] =1'b0;)
`SR(s431,assign G8[23] = G7[23];,assign G8[23] =1'b0;)
`SR(s432,assign P8[24] = P7[24];,assign P8[24] =1'b0;)
`SR(s433,assign G8[24] = G7[24];,assign G8[24] =1'b0;)
`SR(s434,assign P8[25] = P7[25];,assign P8[25] =1'b0;)
`SR(s435,assign G8[25] = G7[25];,assign G8[25] =1'b0;)
`SR(s436,assign P8[26] = P7[26];,assign P8[26] =1'b0;)
`SR(s437,assign G8[26] = G7[26];,assign G8[26] =1'b0;)
`SR(s438,assign P8[28] = P7[28];,assign P8[28] =1'b0;)
`SR(s439,assign G8[28] = G7[28];,assign G8[28] =1'b0;)
`SR(s440,assign P8[29] = P7[29];,assign P8[29] =1'b0;)
`SR(s441,assign G8[29] = G7[29];,assign G8[29] =1'b0;)
`SR(s442,assign P8[30] = P7[30];,assign P8[30] =1'b0;)
`SR(s443,assign G8[30] = G7[30];,assign G8[30] =1'b0;)
`SR(s444,assign P8[31] = P7[31];,assign P8[31] =1'b0;)
`SR(s445,assign G8[31] = G7[31];,assign G8[31] =1'b0;)
`SR(s446,assign P9[0] = P8[0];,assign P9[0] =1'b0;)
`SR(s447,assign G9[0] = G8[0];,assign G9[0] =1'b0;)
`SR(s448,assign P9[1] = P8[1];,assign P9[1] =1'b0;)
`SR(s449,assign G9[1] = G8[1];,assign G9[1] =1'b0;)
`SR(s450,assign P9[2] = P8[2];,assign P9[2] =1'b0;)
`SR(s451,assign G9[2] = G8[2];,assign G9[2] =1'b0;)
`SR(s452,assign P9[3] = P8[3];,assign P9[3] =1'b0;)
`SR(s453,assign G9[3] = G8[3];,assign G9[3] =1'b0;)
`SR(s454,assign P9[4] = P8[4];,assign P9[4] =1'b0;)
`SR(s455,assign G9[4] = G8[4];,assign G9[4] =1'b0;)
`SR(s456,assign P9[6] = P8[6];,assign P9[6] =1'b0;)
`SR(s457,assign G9[6] = G8[6];,assign G9[6] =1'b0;)
`SR(s458,assign P9[7] = P8[7];,assign P9[7] =1'b0;)
`SR(s459,assign G9[7] = G8[7];,assign G9[7] =1'b0;)
`SR(s460,assign P9[8] = P8[8];,assign P9[8] =1'b0;)
`SR(s461,assign G9[8] = G8[8];,assign G9[8] =1'b0;)
`SR(s462,assign P9[10] = P8[10];,assign P9[10] =1'b0;)
`SR(s463,assign G9[10] = G8[10];,assign G9[10] =1'b0;)
`SR(s464,assign P9[11] = P8[11];,assign P9[11] =1'b0;)
`SR(s465,assign G9[11] = G8[11];,assign G9[11] =1'b0;)
`SR(s466,assign P9[12] = P8[12];,assign P9[12] =1'b0;)
`SR(s467,assign G9[12] = G8[12];,assign G9[12] =1'b0;)
`SR(s468,assign P9[14] = P8[14];,assign P9[14] =1'b0;)
`SR(s469,assign G9[14] = G8[14];,assign G9[14] =1'b0;)
`SR(s470,assign P9[15] = P8[15];,assign P9[15] =1'b0;)
`SR(s471,assign G9[15] = G8[15];,assign G9[15] =1'b0;)
`SR(s472,assign P9[16] = P8[16];,assign P9[16] =1'b0;)
`SR(s473,assign G9[16] = G8[16];,assign G9[16] =1'b0;)
`SR(s474,assign P9[18] = P8[18];,assign P9[18] =1'b0;)
`SR(s475,assign G9[18] = G8[18];,assign G9[18] =1'b0;)
`SR(s476,assign P9[19] = P8[19];,assign P9[19] =1'b0;)
`SR(s477,assign G9[19] = G8[19];,assign G9[19] =1'b0;)
`SR(s478,assign P9[20] = P8[20];,assign P9[20] =1'b0;)
`SR(s479,assign G9[20] = G8[20];,assign G9[20] =1'b0;)
`SR(s480,assign P9[22] = P8[22];,assign P9[22] =1'b0;)
`SR(s481,assign G9[22] = G8[22];,assign G9[22] =1'b0;)
`SR(s482,assign P9[23] = P8[23];,assign P9[23] =1'b0;)
`SR(s483,assign G9[23] = G8[23];,assign G9[23] =1'b0;)
`SR(s484,assign P9[24] = P8[24];,assign P9[24] =1'b0;)
`SR(s485,assign G9[24] = G8[24];,assign G9[24] =1'b0;)
`SR(s486,assign P9[26] = P8[26];,assign P9[26] =1'b0;)
`SR(s487,assign G9[26] = G8[26];,assign G9[26] =1'b0;)
`SR(s488,assign P9[27] = P8[27];,assign P9[27] =1'b0;)
`SR(s489,assign G9[27] = G8[27];,assign G9[27] =1'b0;)
`SR(s490,assign P9[28] = P8[28];,assign P9[28] =1'b0;)
`SR(s491,assign G9[28] = G8[28];,assign G9[28] =1'b0;)
`SR(s492,assign P9[30] = P8[30];,assign P9[30] =1'b0;)
`SR(s493,assign G9[30] = G8[30];,assign G9[30] =1'b0;)
`SR(s494,assign P9[31] = P8[31];,assign P9[31] =1'b0;)
`SR(s495,assign G9[31] = G8[31];,assign G9[31] =1'b0;)
`SR(s496,assign P10[0] = P9[0];,assign P10[0] =1'b0;)
`SR(s497,assign G10[0] = G9[0];,assign G10[0] =1'b0;)
`SR(s498,assign P10[1] = P9[1];,assign P10[1] =1'b0;)
`SR(s499,assign G10[1] = G9[1];,assign G10[1] =1'b0;)
`SR(s500,assign P10[3] = P9[3];,assign P10[3] =1'b0;)
`SR(s501,assign G10[3] = G9[3];,assign G10[3] =1'b0;)
`SR(s502,assign P10[5] = P9[5];,assign P10[5] =1'b0;)
`SR(s503,assign G10[5] = G9[5];,assign G10[5] =1'b0;)
`SR(s504,assign P10[7] = P9[7];,assign P10[7] =1'b0;)
`SR(s505,assign G10[7] = G9[7];,assign G10[7] =1'b0;)
`SR(s506,assign P10[9] = P9[9];,assign P10[9] =1'b0;)
`SR(s507,assign G10[9] = G9[9];,assign G10[9] =1'b0;)
`SR(s508,assign P10[11] = P9[11];,assign P10[11] =1'b0;)
`SR(s509,assign G10[11] = G9[11];,assign G10[11] =1'b0;)
`SR(s510,assign P10[13] = P9[13];,assign P10[13] =1'b0;)
`SR(s511,assign G10[13] = G9[13];,assign G10[13] =1'b0;)
`SR(s512,assign P10[15] = P9[15];,assign P10[15] =1'b0;)
`SR(s513,assign G10[15] = G9[15];,assign G10[15] =1'b0;)
`SR(s514,assign P10[17] = P9[17];,assign P10[17] =1'b0;)
`SR(s515,assign G10[17] = G9[17];,assign G10[17] =1'b0;)
`SR(s516,assign P10[19] = P9[19];,assign P10[19] =1'b0;)
`SR(s517,assign G10[19] = G9[19];,assign G10[19] =1'b0;)
`SR(s518,assign P10[21] = P9[21];,assign P10[21] =1'b0;)
`SR(s519,assign G10[21] = G9[21];,assign G10[21] =1'b0;)
`SR(s520,assign P10[23] = P9[23];,assign P10[23] =1'b0;)
`SR(s521,assign G10[23] = G9[23];,assign G10[23] =1'b0;)
`SR(s522,assign P10[25] = P9[25];,assign P10[25] =1'b0;)
`SR(s523,assign G10[25] = G9[25];,assign G10[25] =1'b0;)
`SR(s524,assign P10[27] = P9[27];,assign P10[27] =1'b0;)
`SR(s525,assign G10[27] = G9[27];,assign G10[27] =1'b0;)
`SR(s526,assign P10[29] = P9[29];,assign P10[29] =1'b0;)
`SR(s527,assign G10[29] = G9[29];,assign G10[29] =1'b0;)
`SR(s528,assign P10[31] = P9[31];,assign P10[31] =1'b0;)
`SR(s529,assign G10[31] = G9[31];,assign G10[31] =1'b0;)
`SR(s530,assign S[0] = Cin ^ P0[0];,assign S[0] =1'b0;)
`SR(s531,assign S[1] = ( G10[0] | ( P10[0] & Cin ) ) ^ P0[1];,assign S[1] =1'b0;)
`SR(s532,assign S[2] = ( G10[1] | ( P10[1] & Cin ) ) ^ P0[2];,assign S[2] =1'b0;)
`SR(s533,assign S[3] = ( G10[2] | ( P10[2] & Cin ) ) ^ P0[3];,assign S[3] =1'b0;)
`SR(s534,assign S[4] = ( G10[3] | ( P10[3] & Cin ) ) ^ P0[4];,assign S[4] =1'b0;)
`SR(s535,assign S[5] = ( G10[4] | ( P10[4] & Cin ) ) ^ P0[5];,assign S[5] =1'b0;)
`SR(s536,assign S[6] = ( G10[5] | ( P10[5] & Cin ) ) ^ P0[6];,assign S[6] =1'b0;)
`SR(s537,assign S[7] = ( G10[6] | ( P10[6] & Cin ) ) ^ P0[7];,assign S[7] =1'b0;)
`SR(s538,assign S[8] = ( G10[7] | ( P10[7] & Cin ) ) ^ P0[8];,assign S[8] =1'b0;)
`SR(s539,assign S[9] = ( G10[8] | ( P10[8] & Cin ) ) ^ P0[9];,assign S[9] =1'b0;)
`SR(s540,assign S[10] = ( G10[9] | ( P10[9] & Cin ) ) ^ P0[10];,assign S[10] =1'b0;)
`SR(s541,assign S[11] = ( G10[10] | ( P10[10] & Cin ) ) ^ P0[11];,assign S[11] =1'b0;)
`SR(s542,assign S[12] = ( G10[11] | ( P10[11] & Cin ) ) ^ P0[12];,assign S[12] =1'b0;)
`SR(s543,assign S[13] = ( G10[12] | ( P10[12] & Cin ) ) ^ P0[13];,assign S[13] =1'b0;)
`SR(s544,assign S[14] = ( G10[13] | ( P10[13] & Cin ) ) ^ P0[14];,assign S[14] =1'b0;)
`SR(s545,assign S[15] = ( G10[14] | ( P10[14] & Cin ) ) ^ P0[15];,assign S[15] =1'b0;)
`SR(s546,assign S[16] = ( G10[15] | ( P10[15] & Cin ) ) ^ P0[16];,assign S[16] =1'b0;)
`SR(s547,assign S[17] = ( G10[16] | ( P10[16] & Cin ) ) ^ P0[17];,assign S[17] =1'b0;)
`SR(s548,assign S[18] = ( G10[17] | ( P10[17] & Cin ) ) ^ P0[18];,assign S[18] =1'b0;)
`SR(s549,assign S[19] = ( G10[18] | ( P10[18] & Cin ) ) ^ P0[19];,assign S[19] =1'b0;)
`SR(s550,assign S[20] = ( G10[19] | ( P10[19] & Cin ) ) ^ P0[20];,assign S[20] =1'b0;)
`SR(s551,assign S[21] = ( G10[20] | ( P10[20] & Cin ) ) ^ P0[21];,assign S[21] =1'b0;)
`SR(s552,assign S[22] = ( G10[21] | ( P10[21] & Cin ) ) ^ P0[22];,assign S[22] =1'b0;)
`SR(s553,assign S[23] = ( G10[22] | ( P10[22] & Cin ) ) ^ P0[23];,assign S[23] =1'b0;)
`SR(s554,assign S[24] = ( G10[23] | ( P10[23] & Cin ) ) ^ P0[24];,assign S[24] =1'b0;)
`SR(s555,assign S[25] = ( G10[24] | ( P10[24] & Cin ) ) ^ P0[25];,assign S[25] =1'b0;)
`SR(s556,assign S[26] = ( G10[25] | ( P10[25] & Cin ) ) ^ P0[26];,assign S[26] =1'b0;)
`SR(s557,assign S[27] = ( G10[26] | ( P10[26] & Cin ) ) ^ P0[27];,assign S[27] =1'b0;)
`SR(s558,assign S[28] = ( G10[27] | ( P10[27] & Cin ) ) ^ P0[28];,assign S[28] =1'b0;)
`SR(s559,assign S[29] = ( G10[28] | ( P10[28] & Cin ) ) ^ P0[29];,assign S[29] =1'b0;)
`SR(s560,assign S[30] = ( G10[29] | ( P10[29] & Cin ) ) ^ P0[30];,assign S[30] =1'b0;)
`SR(s561,assign S[31] = ( G10[30] | ( P10[30] & Cin ) ) ^ P0[31];,assign S[31] =1'b0;)
`SR(s562,assign S[32] = G10[31] | ( P10[31] & Cin );,assign S[32] =1'b0;)
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
`SR(s563,assign O[0] = 0;,)
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

