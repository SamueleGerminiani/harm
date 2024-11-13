
/* mod */
module PDKGENAND2X1(input A, input B, output Y );
     assign Y = A & B;
endmodule
/* mod */
module PDKGENFAX1( input A, input B, input C, output YS, output YC );
    assign YS = (A ^ B) ^ C;
    assign YC = (A & B) | (B & C) | (A & C);
endmodule
/* mod */
module PDKGENBUFX2(input A, output Y );
     assign Y = A;
endmodule

module PDKGENHAX1( input A, input B, output YS, output YC );
    assign YS = A ^ B;
    assign YC = A & B;
endmodule
/* mod */



module mult8_cgp14_wc79_csamrca (
    A,
    B,
    O
);

input [7:0] A;
input [7:0] B;
output [15:0] O;

wire sig_20,sig_21,sig_22,sig_23,sig_29,sig_31,sig_40,sig_41,sig_42,sig_43,sig_44,sig_47,sig_49,sig_50,sig_51,sig_52,sig_53,sig_56,sig_70,sig_74;
wire sig_75,sig_76,sig_77,sig_78,sig_79,sig_80,sig_81,sig_82,sig_83,sig_84,sig_86,sig_87,sig_88,sig_92,sig_93,sig_94,sig_95,sig_96,sig_106,sig_112;
wire sig_113,sig_114,sig_115,sig_116,sig_117,sig_118,sig_119,sig_120,sig_121,sig_122,sig_123,sig_124,sig_125,sig_126,sig_127,sig_128,sig_129,sig_130,sig_131,sig_133;
wire sig_134,sig_135,sig_136,sig_137,sig_138,sig_139,sig_150,sig_151,sig_155,sig_156,sig_157,sig_158,sig_159,sig_160,sig_161,sig_162,sig_163,sig_164,sig_165,sig_166;
wire sig_167,sig_168,sig_169,sig_170,sig_171,sig_172,sig_173,sig_174,sig_176,sig_177,sig_178,sig_179,sig_180,sig_181,sig_182,sig_186,sig_188,sig_189,sig_190,sig_191;
wire sig_192,sig_193,sig_194,sig_195,sig_196,sig_197,sig_198,sig_199,sig_200,sig_201,sig_202,sig_203,sig_204,sig_205,sig_206,sig_207,sig_208,sig_209,sig_210,sig_211;
wire sig_212,sig_213,sig_214,sig_215,sig_216,sig_217,sig_218,sig_219,sig_220,sig_221,sig_222,sig_223,sig_224,sig_225,sig_226,sig_227,sig_228,sig_229,sig_230,sig_231;
wire sig_232,sig_233,sig_234,sig_235,sig_236,sig_237,sig_238,sig_239,sig_240,sig_241,sig_242,sig_243,sig_244,sig_245,sig_246,sig_247,sig_248,sig_249,sig_250,sig_251;
wire sig_252,sig_253,sig_254,sig_255,sig_256,sig_257,sig_258,sig_259,sig_260,sig_261,sig_262,sig_263,sig_264,sig_265,sig_266,sig_267,sig_268,sig_269,sig_270,sig_271;
wire sig_272,sig_273,sig_274,sig_275,sig_276,sig_277,sig_278,sig_279,sig_280,sig_281,sig_282,sig_283,sig_284,sig_285,sig_286,sig_287,sig_288,sig_289,sig_290,sig_291;
wire sig_292,sig_293,sig_294,sig_295,sig_296,sig_297,sig_298,sig_299,sig_300,sig_301,sig_302,sig_303,sig_304,sig_305,sig_306,sig_307,sig_308,sig_309,sig_310,sig_311;
wire sig_312,sig_313,sig_314,sig_315,sig_316,sig_317,sig_318,sig_319,sig_320,sig_321,sig_322,sig_323,sig_324,sig_325,sig_326,sig_327,sig_328,sig_329,sig_330,sig_331;
wire sig_332,sig_333,sig_334,sig_335;

assign sig_20 = B[6] & A[1];
assign sig_21 = A[1] & A[0];
assign sig_22 = B[6] & A[0];
assign sig_23 = B[7] & A[0];
assign sig_29 = B[5] & A[1];
assign sig_31 = B[7] & A[1];
assign sig_40 = A[1] | A[0];
assign sig_41 = sig_21 & B[4];
assign sig_42 = sig_22 ^ sig_29;
assign sig_43 = sig_22 & sig_29;
assign sig_44 = sig_23 ^ sig_20;
assign sig_47 = B[7] & sig_21;
assign sig_49 = B[3] & A[2];
assign sig_50 = B[4] & A[2];
assign sig_51 = B[5] & A[2];
assign sig_52 = B[6] & A[2];
assign sig_53 = B[7] & A[2];
assign sig_56 = sig_52 & sig_31;
assign sig_70 = sig_40 & sig_49;
assign sig_74 = sig_42 ^ sig_50;
assign sig_75 = sig_42 & sig_50;
assign sig_76 = sig_74 & sig_41;
assign sig_77 = sig_74 ^ sig_41;
assign sig_78 = sig_75 | sig_76;
assign sig_79 = sig_44 ^ sig_51;
assign sig_80 = sig_44 & sig_51;
assign sig_81 = sig_79 & sig_43;
assign sig_82 = sig_79 ^ sig_43;
assign sig_83 = sig_80 | sig_81;
assign sig_84 = sig_31 ^ sig_52;
assign sig_86 = B[6] & sig_47;
assign sig_87 = sig_84 ^ sig_86;
assign sig_88 = sig_56 | sig_86;
assign sig_92 = B[3] & A[3];
assign sig_93 = B[4] & A[3];
assign sig_94 = B[5] & A[3];
assign sig_95 = B[6] & A[3];
assign sig_96 = B[7] & A[3];
assign sig_106 = B[2] & A[3];
assign sig_112 = sig_77 ^ sig_92;
assign sig_113 = sig_77 & sig_92;
assign sig_114 = sig_112 & sig_70;
assign sig_115 = sig_112 ^ sig_70;
assign sig_116 = sig_113 | sig_114;
assign sig_117 = sig_82 ^ sig_93;
assign sig_118 = sig_82 & sig_93;
assign sig_119 = sig_117 & sig_78;
assign sig_120 = sig_117 ^ sig_78;
assign sig_121 = sig_118 | sig_119;
assign sig_122 = sig_87 ^ sig_94;
assign sig_123 = sig_87 & sig_94;
assign sig_124 = sig_122 & sig_83;
assign sig_125 = sig_122 ^ sig_83;
assign sig_126 = sig_123 | sig_124;
assign sig_127 = sig_53 ^ sig_95;
assign sig_128 = sig_53 & sig_95;
assign sig_129 = sig_127 & sig_88;
assign sig_130 = sig_127 ^ sig_88;
assign sig_131 = sig_128 | sig_129;
assign sig_133 = B[1] & A[4];
assign sig_134 = B[2] & A[4];
assign sig_135 = B[3] & A[4];
assign sig_136 = B[4] & A[4];
assign sig_137 = B[5] & A[4];
assign sig_138 = B[6] & A[4];
assign sig_139 = B[7] & A[4];
assign sig_150 = sig_115 ^ sig_134;
assign sig_151 = sig_115 & sig_134;
assign sig_155 = sig_120 ^ sig_135;
assign sig_156 = sig_120 & sig_135;
assign sig_157 = sig_155 & sig_116;
assign sig_158 = sig_155 ^ sig_116;
assign sig_159 = sig_156 | sig_157;
assign sig_160 = sig_125 ^ sig_136;
assign sig_161 = sig_125 & sig_136;
assign sig_162 = sig_160 & sig_121;
assign sig_163 = sig_160 ^ sig_121;
assign sig_164 = sig_161 | sig_162;
assign sig_165 = sig_130 ^ sig_137;
assign sig_166 = sig_130 & sig_137;
assign sig_167 = sig_165 & sig_126;
assign sig_168 = sig_165 ^ sig_126;
assign sig_169 = sig_166 | sig_167;
assign sig_170 = sig_96 ^ sig_138;
assign sig_171 = sig_96 & sig_138;
assign sig_172 = sig_170 & sig_131;
assign sig_173 = sig_170 ^ sig_131;
assign sig_174 = sig_171 | sig_172;
assign sig_176 = B[1] & A[5];
assign sig_177 = B[2] & A[5];
assign sig_178 = B[3] & A[5];
assign sig_179 = B[4] & A[5];
assign sig_180 = B[5] & A[5];
assign sig_181 = B[6] & A[5];
assign sig_182 = B[7] & A[5];
assign sig_186 = ~sig_133;
assign sig_188 = sig_150 ^ sig_176;
assign sig_189 = sig_150 & sig_176;
assign sig_190 = sig_188 & sig_106;
assign sig_191 = sig_188 ^ sig_106;
assign sig_192 = sig_189 | sig_190;
assign sig_193 = sig_158 ^ sig_177;
assign sig_194 = sig_158 & sig_177;
assign sig_195 = sig_193 & sig_151;
assign sig_196 = sig_193 ^ sig_151;
assign sig_197 = sig_194 | sig_195;
assign sig_198 = sig_163 ^ sig_178;
assign sig_199 = sig_163 & sig_178;
assign sig_200 = sig_198 & sig_159;
assign sig_201 = sig_198 ^ sig_159;
assign sig_202 = sig_199 | sig_200;
assign sig_203 = sig_168 ^ sig_179;
assign sig_204 = sig_168 & sig_179;
assign sig_205 = sig_203 & sig_164;
assign sig_206 = sig_203 ^ sig_164;
assign sig_207 = sig_204 | sig_205;
assign sig_208 = sig_173 ^ sig_180;
assign sig_209 = sig_173 & sig_180;
assign sig_210 = sig_208 & sig_169;
assign sig_211 = sig_208 ^ sig_169;
assign sig_212 = sig_209 | sig_210;
assign sig_213 = sig_139 ^ sig_181;
assign sig_214 = sig_139 & sig_181;
assign sig_215 = sig_213 & sig_174;
assign sig_216 = sig_213 ^ sig_174;
assign sig_217 = sig_214 | sig_215;
assign sig_218 = B[0] & A[6];
assign sig_219 = B[1] & A[6];
assign sig_220 = B[2] & A[6];
assign sig_221 = B[3] & A[6];
assign sig_222 = B[4] & A[6];
assign sig_223 = B[5] & A[6];
assign sig_224 = B[6] & A[6];
assign sig_225 = B[7] & A[6];
assign sig_226 = sig_191 ^ sig_218;
assign sig_227 = sig_191 & sig_218;
assign sig_228 = sig_226 & sig_133;
assign sig_229 = sig_226 ^ sig_133;
assign sig_230 = sig_227 | sig_228;
assign sig_231 = sig_196 ^ sig_219;
assign sig_232 = sig_196 & sig_219;
assign sig_233 = sig_231 & sig_192;
assign sig_234 = sig_231 ^ sig_192;
assign sig_235 = sig_232 | sig_233;
assign sig_236 = sig_201 ^ sig_220;
assign sig_237 = sig_201 & sig_220;
assign sig_238 = sig_236 & sig_197;
assign sig_239 = sig_236 ^ sig_197;
assign sig_240 = sig_237 | sig_238;
assign sig_241 = sig_206 ^ sig_221;
assign sig_242 = sig_206 & sig_221;
assign sig_243 = sig_241 & sig_202;
assign sig_244 = sig_241 ^ sig_202;
assign sig_245 = sig_242 | sig_243;
assign sig_246 = sig_211 ^ sig_222;
assign sig_247 = sig_211 & sig_222;
assign sig_248 = sig_246 & sig_207;
assign sig_249 = sig_246 ^ sig_207;
assign sig_250 = sig_247 | sig_248;
assign sig_251 = sig_216 ^ sig_223;
assign sig_252 = sig_216 & sig_223;
assign sig_253 = sig_251 & sig_212;
assign sig_254 = sig_251 ^ sig_212;
assign sig_255 = sig_252 | sig_253;
assign sig_256 = sig_182 ^ sig_224;
assign sig_257 = sig_182 & sig_224;
assign sig_258 = sig_256 & sig_217;
assign sig_259 = sig_256 ^ sig_217;
assign sig_260 = sig_257 | sig_258;
assign sig_261 = B[0] & A[7];
assign sig_262 = B[1] & A[7];
assign sig_263 = B[2] & A[7];
assign sig_264 = B[3] & A[7];
assign sig_265 = B[4] & A[7];
assign sig_266 = B[5] & A[7];
assign sig_267 = B[6] & A[7];
assign sig_268 = B[7] & A[7];
assign sig_269 = sig_234 ^ sig_261;
assign sig_270 = sig_234 & sig_261;
assign sig_271 = sig_269 & sig_230;
assign sig_272 = sig_269 ^ sig_230;
assign sig_273 = sig_270 | sig_271;
assign sig_274 = sig_239 ^ sig_262;
assign sig_275 = sig_239 & sig_262;
assign sig_276 = sig_274 & sig_235;
assign sig_277 = sig_274 ^ sig_235;
assign sig_278 = sig_275 | sig_276;
assign sig_279 = sig_244 ^ sig_263;
assign sig_280 = sig_244 & sig_263;
assign sig_281 = sig_279 & sig_240;
assign sig_282 = sig_279 ^ sig_240;
assign sig_283 = sig_280 | sig_281;
assign sig_284 = sig_249 ^ sig_264;
assign sig_285 = sig_249 & sig_264;
assign sig_286 = sig_284 & sig_245;
assign sig_287 = sig_284 ^ sig_245;
assign sig_288 = sig_285 | sig_286;
assign sig_289 = sig_254 ^ sig_265;
assign sig_290 = sig_254 & sig_265;
assign sig_291 = sig_289 & sig_250;
assign sig_292 = sig_289 ^ sig_250;
assign sig_293 = sig_290 | sig_291;
assign sig_294 = sig_259 ^ sig_266;
assign sig_295 = sig_259 & sig_266;
assign sig_296 = sig_294 & sig_255;
assign sig_297 = sig_294 ^ sig_255;
assign sig_298 = sig_295 | sig_296;
assign sig_299 = sig_225 ^ sig_267;
assign sig_300 = sig_225 & sig_267;
assign sig_301 = sig_299 & sig_260;
assign sig_302 = sig_299 ^ sig_260;
assign sig_303 = sig_300 | sig_301;
assign sig_304 = sig_277 ^ sig_273;
assign sig_305 = sig_277 & sig_273;
assign sig_306 = sig_282 ^ sig_278;
assign sig_307 = sig_282 & sig_278;
assign sig_308 = sig_306 & sig_305;
assign sig_309 = sig_306 ^ sig_305;
assign sig_310 = sig_307 | sig_308;
assign sig_311 = sig_287 ^ sig_283;
assign sig_312 = sig_287 & sig_283;
assign sig_313 = sig_311 & sig_310;
assign sig_314 = sig_311 ^ sig_310;
assign sig_315 = sig_312 | sig_313;
assign sig_316 = sig_292 ^ sig_288;
assign sig_317 = sig_292 & sig_288;
assign sig_318 = sig_316 & sig_315;
assign sig_319 = sig_316 ^ sig_315;
assign sig_320 = sig_317 | sig_318;
assign sig_321 = sig_297 ^ sig_293;
assign sig_322 = sig_297 & sig_293;
assign sig_323 = sig_321 & sig_320;
assign sig_324 = sig_321 ^ sig_320;
assign sig_325 = sig_322 | sig_323;
assign sig_326 = sig_302 ^ sig_298;
assign sig_327 = sig_302 & sig_298;
assign sig_328 = sig_326 & sig_325;
assign sig_329 = sig_326 ^ sig_325;
assign sig_330 = sig_327 | sig_328;
assign sig_331 = sig_268 ^ sig_303;
assign sig_332 = A[7] & sig_303;
assign sig_333 = sig_331 & sig_330;
assign sig_334 = sig_331 ^ sig_330;
assign sig_335 = sig_332 | sig_333;

assign O[15] = sig_335;
assign O[14] = sig_334;
assign O[13] = sig_329;
assign O[12] = sig_324;
assign O[11] = sig_319;
assign O[10] = sig_314;
assign O[9] = sig_309;
assign O[8] = sig_304;
assign O[7] = sig_272;
assign O[6] = sig_229;
assign O[5] = sig_186;
assign O[4] = sig_133;
assign O[3] = sig_180;
assign O[2] = A[5];
assign O[1] = sig_252;
assign O[0] = sig_134;

endmodule


module trun8_tam00b ( A, B, O );
  input [7:0] A;
  input [7:0] B;
  output [15:0] O;

  wire C_1_0,C_1_1,C_1_2,C_1_3,C_1_4,C_1_5,C_1_6,C_2_0,C_2_1,C_2_2,C_2_3,C_2_4,C_2_5,C_2_6,C_3_0,C_3_1,C_3_2,C_3_3,C_3_4,C_3_5,C_3_6,C_4_0,C_4_1,C_4_2,C_4_3,C_4_4,C_4_5,C_4_6,C_5_0,C_5_1,C_5_2,C_5_3,C_5_4,C_5_5,C_5_6,C_6_0,C_6_1,C_6_2,C_6_3,C_6_4,C_6_5,C_6_6,C_7_0,C_7_1,C_7_2,C_7_3,C_7_4,C_7_5,C_7_6,S_0_0,S_0_1,S_0_2,S_0_3,S_0_4,S_0_5,S_0_6,S_0_7,S_1_0,S_1_1,S_1_2,S_1_3,S_1_4,S_1_5,S_1_6,S_1_7,S_2_0,S_2_1,S_2_2,S_2_3,S_2_4,S_2_5,S_2_6,S_2_7,S_3_0,S_3_1,S_3_2,S_3_3,S_3_4,S_3_5,S_3_6,S_3_7,S_4_0,S_4_1,S_4_2,S_4_3,S_4_4,S_4_5,S_4_6,S_4_7,S_5_0,S_5_1,S_5_2,S_5_3,S_5_4,S_5_5,S_5_6,S_5_7,S_6_0,S_6_1,S_6_2,S_6_3,S_6_4,S_6_5,S_6_6,S_6_7,S_7_0,S_7_1,S_7_2,S_7_3,S_7_4,S_7_5,S_7_6,S_7_7,S_8_0,S_8_1,S_8_2,S_8_3,S_8_4,S_8_5,S_8_6,S_8_7;

  assign S_0_0 = (A[0] & B[0]);
  assign S_0_1 = (A[0] & B[1]);
  assign S_0_2 = (A[0] & B[2]);
  assign S_0_3 = (A[0] & B[3]);
  assign S_0_4 = (A[0] & B[4]);
  assign S_0_5 = (A[0] & B[5]);
  assign S_0_6 = (A[0] & B[6]);
  assign S_0_7 = (A[0] & B[7]);
  PDKGENHAX1 U13609 (.A(S_0_1), .B((A[1] & B[0])), .YS(S_1_0), .YC(C_1_0));
  PDKGENHAX1 U13610 (.A(S_0_2), .B((A[1] & B[1])), .YS(S_1_1), .YC(C_1_1));
  PDKGENHAX1 U13611 (.A(S_0_3), .B((A[1] & B[2])), .YS(S_1_2), .YC(C_1_2));
  PDKGENHAX1 U13612 (.A(S_0_4), .B((A[1] & B[3])), .YS(S_1_3), .YC(C_1_3));
  PDKGENHAX1 U13613 (.A(S_0_5), .B((A[1] & B[4])), .YS(S_1_4), .YC(C_1_4));
  PDKGENHAX1 U13614 (.A(S_0_6), .B((A[1] & B[5])), .YS(S_1_5), .YC(C_1_5));
  PDKGENHAX1 U13615 (.A(S_0_7), .B((A[1] & B[6])), .YS(S_1_6), .YC(C_1_6));
  assign S_1_7 = (A[1] & B[7]);
  PDKGENFAX1 U13617 (.A(S_1_1), .B(C_1_0), .C((A[2] & B[0])), .YS(S_2_0), .YC(C_2_0));
  PDKGENFAX1 U13618 (.A(S_1_2), .B(C_1_1), .C((A[2] & B[1])), .YS(S_2_1), .YC(C_2_1));
  PDKGENFAX1 U13619 (.A(S_1_3), .B(C_1_2), .C((A[2] & B[2])), .YS(S_2_2), .YC(C_2_2));
  PDKGENFAX1 U13620 (.A(S_1_4), .B(C_1_3), .C((A[2] & B[3])), .YS(S_2_3), .YC(C_2_3));
  PDKGENFAX1 U13621 (.A(S_1_5), .B(C_1_4), .C((A[2] & B[4])), .YS(S_2_4), .YC(C_2_4));
  PDKGENFAX1 U13622 (.A(S_1_6), .B(C_1_5), .C((A[2] & B[5])), .YS(S_2_5), .YC(C_2_5));
  PDKGENFAX1 U13623 (.A(S_1_7), .B(C_1_6), .C((A[2] & B[6])), .YS(S_2_6), .YC(C_2_6));
  assign S_2_7 = (A[2] & B[7]);
  PDKGENFAX1 U13625 (.A(S_2_1), .B(C_2_0), .C((A[3] & B[0])), .YS(S_3_0), .YC(C_3_0));
  PDKGENFAX1 U13626 (.A(S_2_2), .B(C_2_1), .C((A[3] & B[1])), .YS(S_3_1), .YC(C_3_1));
  PDKGENFAX1 U13627 (.A(S_2_3), .B(C_2_2), .C((A[3] & B[2])), .YS(S_3_2), .YC(C_3_2));
  PDKGENFAX1 U13628 (.A(S_2_4), .B(C_2_3), .C((A[3] & B[3])), .YS(S_3_3), .YC(C_3_3));
  PDKGENFAX1 U13629 (.A(S_2_5), .B(C_2_4), .C((A[3] & B[4])), .YS(S_3_4), .YC(C_3_4));
  PDKGENFAX1 U13630 (.A(S_2_6), .B(C_2_5), .C((A[3] & B[5])), .YS(S_3_5), .YC(C_3_5));
  PDKGENFAX1 U13631 (.A(S_2_7), .B(C_2_6), .C((A[3] & B[6])), .YS(S_3_6), .YC(C_3_6));
  assign S_3_7 = (A[3] & B[7]);
  PDKGENFAX1 U13633 (.A(S_3_1), .B(C_3_0), .C((A[4] & B[0])), .YS(S_4_0), .YC(C_4_0));
  PDKGENFAX1 U13634 (.A(S_3_2), .B(C_3_1), .C((A[4] & B[1])), .YS(S_4_1), .YC(C_4_1));
  PDKGENFAX1 U13635 (.A(S_3_3), .B(C_3_2), .C((A[4] & B[2])), .YS(S_4_2), .YC(C_4_2));
  PDKGENFAX1 U13636 (.A(S_3_4), .B(C_3_3), .C((A[4] & B[3])), .YS(S_4_3), .YC(C_4_3));
  PDKGENFAX1 U13637 (.A(S_3_5), .B(C_3_4), .C((A[4] & B[4])), .YS(S_4_4), .YC(C_4_4));
  PDKGENFAX1 U13638 (.A(S_3_6), .B(C_3_5), .C((A[4] & B[5])), .YS(S_4_5), .YC(C_4_5));
  PDKGENFAX1 U13639 (.A(S_3_7), .B(C_3_6), .C((A[4] & B[6])), .YS(S_4_6), .YC(C_4_6));
  assign S_4_7 = (A[4] & B[7]);
  PDKGENFAX1 U13641 (.A(S_4_1), .B(C_4_0), .C((A[5] & B[0])), .YS(S_5_0), .YC(C_5_0));
  PDKGENFAX1 U13642 (.A(S_4_2), .B(C_4_1), .C((A[5] & B[1])), .YS(S_5_1), .YC(C_5_1));
  PDKGENFAX1 U13643 (.A(S_4_3), .B(C_4_2), .C((A[5] & B[2])), .YS(S_5_2), .YC(C_5_2));
  PDKGENFAX1 U13644 (.A(S_4_4), .B(C_4_3), .C((A[5] & B[3])), .YS(S_5_3), .YC(C_5_3));
  PDKGENFAX1 U13645 (.A(S_4_5), .B(C_4_4), .C((A[5] & B[4])), .YS(S_5_4), .YC(C_5_4));
  PDKGENFAX1 U13646 (.A(S_4_6), .B(C_4_5), .C((A[5] & B[5])), .YS(S_5_5), .YC(C_5_5));
  PDKGENFAX1 U13647 (.A(S_4_7), .B(C_4_6), .C((A[5] & B[6])), .YS(S_5_6), .YC(C_5_6));
  assign S_5_7 = (A[5] & B[7]);
  PDKGENFAX1 U13649 (.A(S_5_1), .B(C_5_0), .C((A[6] & B[0])), .YS(S_6_0), .YC(C_6_0));
  PDKGENFAX1 U13650 (.A(S_5_2), .B(C_5_1), .C((A[6] & B[1])), .YS(S_6_1), .YC(C_6_1));
  PDKGENFAX1 U13651 (.A(S_5_3), .B(C_5_2), .C((A[6] & B[2])), .YS(S_6_2), .YC(C_6_2));
  PDKGENFAX1 U13652 (.A(S_5_4), .B(C_5_3), .C((A[6] & B[3])), .YS(S_6_3), .YC(C_6_3));
  PDKGENFAX1 U13653 (.A(S_5_5), .B(C_5_4), .C((A[6] & B[4])), .YS(S_6_4), .YC(C_6_4));
  PDKGENFAX1 U13654 (.A(S_5_6), .B(C_5_5), .C((A[6] & B[5])), .YS(S_6_5), .YC(C_6_5));
  PDKGENFAX1 U13655 (.A(S_5_7), .B(C_5_6), .C((A[6] & B[6])), .YS(S_6_6), .YC(C_6_6));
  assign S_6_7 = (A[6] & B[7]);
  PDKGENFAX1 U13657 (.A(S_6_1), .B(C_6_0), .C((A[7] & B[0])), .YS(S_7_0), .YC(C_7_0));
  PDKGENFAX1 U13658 (.A(S_6_2), .B(C_6_1), .C((A[7] & B[1])), .YS(S_7_1), .YC(C_7_1));
  PDKGENFAX1 U13659 (.A(S_6_3), .B(C_6_2), .C((A[7] & B[2])), .YS(S_7_2), .YC(C_7_2));
  PDKGENFAX1 U13660 (.A(S_6_4), .B(C_6_3), .C((A[7] & B[3])), .YS(S_7_3), .YC(C_7_3));
  PDKGENFAX1 U13661 (.A(S_6_5), .B(C_6_4), .C((A[7] & B[4])), .YS(S_7_4), .YC(C_7_4));
  PDKGENFAX1 U13662 (.A(S_6_6), .B(C_6_5), .C((A[7] & B[5])), .YS(S_7_5), .YC(C_7_5));
  PDKGENFAX1 U13663 (.A(S_6_7), .B(C_6_6), .C((A[7] & B[6])), .YS(S_7_6), .YC(C_7_6));
  assign S_7_7 = (A[7] & B[7]);
  assign {S_8_7, S_8_6, S_8_5, S_8_4, S_8_3, S_8_2, S_8_1, S_8_0} = {C_7_6, C_7_5, C_7_4, C_7_3, C_7_2, C_7_1, C_7_0} + {S_7_7, S_7_6, S_7_5, S_7_4, S_7_3, S_7_2, S_7_1};
  assign O = {S_8_7,S_8_6,S_8_5,S_8_4,S_8_3,S_8_2,S_8_1,S_8_0,S_7_0,S_6_0,S_5_0,S_4_0,S_3_0,S_2_0,S_1_0,S_0_0};

endmodule



module mult8_cgp14ep_ep55705_wc4_csamrca (
    A,
    B,
    O
);

input [7:0] A;
input [7:0] B;
output [15:0] O;

wire sig_17,sig_19,sig_20,sig_21,sig_22,sig_23,sig_26,sig_27,sig_28,sig_29,sig_30,sig_31,sig_35,sig_36,sig_37,sig_38,sig_39,sig_40,sig_41,sig_42;
wire sig_43,sig_44,sig_45,sig_46,sig_47,sig_48,sig_49,sig_50,sig_51,sig_52,sig_53,sig_56,sig_57,sig_59,sig_60,sig_61,sig_62,sig_63,sig_64,sig_65;
wire sig_66,sig_67,sig_68,sig_69,sig_70,sig_71,sig_72,sig_73,sig_74,sig_75,sig_76,sig_77,sig_78,sig_79,sig_80,sig_81,sig_82,sig_83,sig_84,sig_85;
wire sig_86,sig_87,sig_88,sig_89,sig_90,sig_91,sig_92,sig_93,sig_94,sig_95,sig_96,sig_97,sig_98,sig_99,sig_100,sig_101,sig_102,sig_103,sig_104,sig_105;
wire sig_106,sig_107,sig_108,sig_109,sig_110,sig_111,sig_112,sig_113,sig_114,sig_115,sig_116,sig_117,sig_118,sig_119,sig_120,sig_121,sig_122,sig_123,sig_124,sig_125;
wire sig_126,sig_127,sig_128,sig_129,sig_130,sig_131,sig_132,sig_133,sig_134,sig_135,sig_136,sig_137,sig_138,sig_139,sig_140,sig_141,sig_142,sig_143,sig_144,sig_145;
wire sig_146,sig_147,sig_148,sig_149,sig_150,sig_151,sig_152,sig_153,sig_154,sig_155,sig_156,sig_157,sig_158,sig_159,sig_160,sig_161,sig_162,sig_163,sig_164,sig_165;
wire sig_166,sig_167,sig_168,sig_169,sig_170,sig_171,sig_172,sig_173,sig_174,sig_175,sig_176,sig_177,sig_178,sig_179,sig_180,sig_181,sig_182,sig_183,sig_184,sig_185;
wire sig_186,sig_187,sig_188,sig_189,sig_190,sig_191,sig_192,sig_193,sig_194,sig_195,sig_196,sig_197,sig_198,sig_199,sig_200,sig_201,sig_202,sig_203,sig_204,sig_205;
wire sig_206,sig_207,sig_208,sig_209,sig_210,sig_211,sig_212,sig_213,sig_214,sig_215,sig_216,sig_217,sig_218,sig_219,sig_220,sig_221,sig_222,sig_223,sig_224,sig_225;
wire sig_226,sig_227,sig_228,sig_229,sig_230,sig_231,sig_232,sig_233,sig_234,sig_235,sig_236,sig_237,sig_238,sig_239,sig_240,sig_241,sig_242,sig_243,sig_244,sig_245;
wire sig_246,sig_247,sig_248,sig_249,sig_250,sig_251,sig_252,sig_253,sig_254,sig_255,sig_256,sig_257,sig_258,sig_259,sig_260,sig_261,sig_262,sig_263,sig_264,sig_265;
wire sig_266,sig_267,sig_268,sig_269,sig_270,sig_271,sig_272,sig_273,sig_274,sig_275,sig_276,sig_277,sig_278,sig_279,sig_280,sig_281,sig_282,sig_283,sig_284,sig_285;
wire sig_286,sig_287,sig_288,sig_289,sig_290,sig_291,sig_292,sig_293,sig_294,sig_295,sig_296,sig_297,sig_298,sig_299,sig_300,sig_301,sig_302,sig_303,sig_304,sig_305;
wire sig_306,sig_307,sig_308,sig_309,sig_310,sig_311,sig_312,sig_313,sig_314,sig_315,sig_316,sig_317,sig_318,sig_319,sig_320,sig_321,sig_322,sig_323,sig_324,sig_325;
wire sig_326,sig_327,sig_328,sig_329,sig_330,sig_331,sig_332,sig_333,sig_334,sig_335;

assign sig_17 = B[1] & A[1];
assign sig_19 = B[3] & A[0];
assign sig_20 = B[4] & A[0];
assign sig_21 = B[5] & A[0];
assign sig_22 = B[6] & A[0];
assign sig_23 = B[7] & A[0];
assign sig_26 = B[2] & A[1];
assign sig_27 = B[3] & A[1];
assign sig_28 = B[4] & A[1];
assign sig_29 = B[5] & A[1];
assign sig_30 = B[6] & A[1];
assign sig_31 = B[7] & A[1];
assign sig_35 = B[2] & A[0];
assign sig_36 = sig_19 ^ sig_26;
assign sig_37 = sig_19 & sig_26;
assign sig_38 = sig_20 ^ sig_27;
assign sig_39 = sig_20 & sig_27;
assign sig_40 = sig_21 ^ sig_28;
assign sig_41 = sig_21 & sig_28;
assign sig_42 = sig_22 ^ sig_29;
assign sig_43 = sig_22 & sig_29;
assign sig_44 = sig_23 ^ sig_30;
assign sig_45 = B[6] & sig_31;
assign sig_46 = B[0] & A[2];
assign sig_47 = B[1] & A[2];
assign sig_48 = B[2] & A[2];
assign sig_49 = B[3] & A[2];
assign sig_50 = B[4] & A[2];
assign sig_51 = B[5] & A[2];
assign sig_52 = B[6] & A[2];
assign sig_53 = B[7] & A[2];
assign sig_56 = sig_46 & sig_17;
assign sig_57 = sig_46 | sig_17;
assign sig_59 = sig_36 ^ sig_47;
assign sig_60 = sig_36 & sig_47;
assign sig_61 = sig_59 & sig_35;
assign sig_62 = sig_59 ^ sig_35;
assign sig_63 = sig_60 | sig_61;
assign sig_64 = sig_38 ^ sig_48;
assign sig_65 = sig_38 & sig_48;
assign sig_66 = sig_64 & sig_37;
assign sig_67 = sig_64 ^ sig_37;
assign sig_68 = sig_65 | sig_66;
assign sig_69 = sig_40 ^ sig_49;
assign sig_70 = sig_40 & sig_49;
assign sig_71 = sig_69 & sig_39;
assign sig_72 = sig_69 ^ sig_39;
assign sig_73 = sig_70 | sig_71;
assign sig_74 = sig_42 ^ sig_50;
assign sig_75 = sig_42 & sig_50;
assign sig_76 = sig_74 & sig_41;
assign sig_77 = sig_74 ^ sig_41;
assign sig_78 = sig_75 | sig_76;
assign sig_79 = sig_44 ^ sig_51;
assign sig_80 = sig_44 & sig_51;
assign sig_81 = sig_79 & sig_43;
assign sig_82 = sig_79 ^ sig_43;
assign sig_83 = sig_80 | sig_81;
assign sig_84 = sig_31 ^ sig_52;
assign sig_85 = sig_45 & A[2];
assign sig_86 = A[0] & sig_45;
assign sig_87 = sig_84 ^ sig_86;
assign sig_88 = sig_85 | sig_86;
assign sig_89 = B[0] & A[3];
assign sig_90 = B[1] & A[3];
assign sig_91 = B[2] & A[3];
assign sig_92 = B[3] & A[3];
assign sig_93 = B[4] & A[3];
assign sig_94 = B[5] & A[3];
assign sig_95 = B[6] & A[3];
assign sig_96 = B[7] & A[3];
assign sig_97 = sig_62 ^ sig_89;
assign sig_98 = sig_62 & sig_89;
assign sig_99 = sig_97 & sig_56;
assign sig_100 = sig_97 ^ sig_56;
assign sig_101 = sig_98 | sig_99;
assign sig_102 = sig_67 ^ sig_90;
assign sig_103 = sig_67 & sig_90;
assign sig_104 = sig_102 & sig_63;
assign sig_105 = sig_102 ^ sig_63;
assign sig_106 = sig_103 | sig_104;
assign sig_107 = sig_72 ^ sig_91;
assign sig_108 = sig_72 & sig_91;
assign sig_109 = sig_107 & sig_68;
assign sig_110 = sig_107 ^ sig_68;
assign sig_111 = sig_108 | sig_109;
assign sig_112 = sig_77 ^ sig_92;
assign sig_113 = sig_77 & sig_92;
assign sig_114 = sig_112 & sig_73;
assign sig_115 = sig_112 ^ sig_73;
assign sig_116 = sig_113 | sig_114;
assign sig_117 = sig_82 ^ sig_93;
assign sig_118 = sig_82 & sig_93;
assign sig_119 = sig_117 & sig_78;
assign sig_120 = sig_117 ^ sig_78;
assign sig_121 = sig_118 | sig_119;
assign sig_122 = sig_87 ^ sig_94;
assign sig_123 = sig_87 & sig_94;
assign sig_124 = sig_122 & sig_83;
assign sig_125 = sig_122 ^ sig_83;
assign sig_126 = sig_123 | sig_124;
assign sig_127 = sig_53 ^ sig_95;
assign sig_128 = sig_53 & sig_95;
assign sig_129 = sig_127 & sig_88;
assign sig_130 = sig_127 ^ sig_88;
assign sig_131 = sig_128 | sig_129;
assign sig_132 = B[0] & A[4];
assign sig_133 = B[1] & A[4];
assign sig_134 = B[2] & A[4];
assign sig_135 = B[3] & A[4];
assign sig_136 = B[4] & A[4];
assign sig_137 = B[5] & A[4];
assign sig_138 = B[6] & A[4];
assign sig_139 = B[7] & A[4];
assign sig_140 = sig_105 ^ sig_132;
assign sig_141 = sig_105 & sig_132;
assign sig_142 = sig_140 & sig_101;
assign sig_143 = sig_140 ^ sig_101;
assign sig_144 = sig_141 | sig_142;
assign sig_145 = sig_110 ^ sig_133;
assign sig_146 = sig_110 & sig_133;
assign sig_147 = sig_145 & sig_106;
assign sig_148 = sig_145 ^ sig_106;
assign sig_149 = sig_146 | sig_147;
assign sig_150 = sig_115 ^ sig_134;
assign sig_151 = sig_115 & sig_134;
assign sig_152 = sig_150 & sig_111;
assign sig_153 = sig_150 ^ sig_111;
assign sig_154 = sig_151 | sig_152;
assign sig_155 = sig_120 ^ sig_135;
assign sig_156 = sig_120 & sig_135;
assign sig_157 = sig_155 & sig_116;
assign sig_158 = sig_155 ^ sig_116;
assign sig_159 = sig_156 | sig_157;
assign sig_160 = sig_125 ^ sig_136;
assign sig_161 = sig_125 & sig_136;
assign sig_162 = sig_160 & sig_121;
assign sig_163 = sig_160 ^ sig_121;
assign sig_164 = sig_161 | sig_162;
assign sig_165 = sig_130 ^ sig_137;
assign sig_166 = sig_130 & sig_137;
assign sig_167 = sig_165 & sig_126;
assign sig_168 = sig_165 ^ sig_126;
assign sig_169 = sig_166 | sig_167;
assign sig_170 = sig_96 ^ sig_138;
assign sig_171 = sig_96 & sig_138;
assign sig_172 = sig_170 & sig_131;
assign sig_173 = sig_170 ^ sig_131;
assign sig_174 = sig_171 | sig_172;
assign sig_175 = B[0] & A[5];
assign sig_176 = B[1] & A[5];
assign sig_177 = B[2] & A[5];
assign sig_178 = B[3] & A[5];
assign sig_179 = B[4] & A[5];
assign sig_180 = B[5] & A[5];
assign sig_181 = B[6] & A[5];
assign sig_182 = B[7] & A[5];
assign sig_183 = sig_148 ^ sig_175;
assign sig_184 = sig_148 & sig_175;
assign sig_185 = sig_183 & sig_144;
assign sig_186 = sig_183 ^ sig_144;
assign sig_187 = sig_184 | sig_185;
assign sig_188 = sig_153 ^ sig_176;
assign sig_189 = sig_153 & sig_176;
assign sig_190 = sig_188 & sig_149;
assign sig_191 = sig_188 ^ sig_149;
assign sig_192 = sig_189 | sig_190;
assign sig_193 = sig_158 ^ sig_177;
assign sig_194 = sig_158 & sig_177;
assign sig_195 = sig_193 & sig_154;
assign sig_196 = sig_193 ^ sig_154;
assign sig_197 = sig_194 | sig_195;
assign sig_198 = sig_163 ^ sig_178;
assign sig_199 = sig_163 & sig_178;
assign sig_200 = sig_198 & sig_159;
assign sig_201 = sig_198 ^ sig_159;
assign sig_202 = sig_199 | sig_200;
assign sig_203 = sig_168 ^ sig_179;
assign sig_204 = sig_168 & sig_179;
assign sig_205 = sig_203 & sig_164;
assign sig_206 = sig_203 ^ sig_164;
assign sig_207 = sig_204 | sig_205;
assign sig_208 = sig_173 ^ sig_180;
assign sig_209 = sig_173 & sig_180;
assign sig_210 = sig_208 & sig_169;
assign sig_211 = sig_208 ^ sig_169;
assign sig_212 = sig_209 | sig_210;
assign sig_213 = sig_139 ^ sig_181;
assign sig_214 = sig_139 & sig_181;
assign sig_215 = sig_213 & sig_174;
assign sig_216 = sig_213 ^ sig_174;
assign sig_217 = sig_214 | sig_215;
assign sig_218 = B[0] & A[6];
assign sig_219 = B[1] & A[6];
assign sig_220 = B[2] & A[6];
assign sig_221 = B[3] & A[6];
assign sig_222 = B[4] & A[6];
assign sig_223 = B[5] & A[6];
assign sig_224 = B[6] & A[6];
assign sig_225 = B[7] & A[6];
assign sig_226 = sig_191 ^ sig_218;
assign sig_227 = sig_191 & sig_218;
assign sig_228 = sig_226 & sig_187;
assign sig_229 = sig_226 ^ sig_187;
assign sig_230 = sig_227 | sig_228;
assign sig_231 = sig_196 ^ sig_219;
assign sig_232 = sig_196 & sig_219;
assign sig_233 = sig_231 & sig_192;
assign sig_234 = sig_231 ^ sig_192;
assign sig_235 = sig_232 | sig_233;
assign sig_236 = sig_201 ^ sig_220;
assign sig_237 = sig_201 & sig_220;
assign sig_238 = sig_236 & sig_197;
assign sig_239 = sig_236 ^ sig_197;
assign sig_240 = sig_237 | sig_238;
assign sig_241 = sig_206 ^ sig_221;
assign sig_242 = sig_206 & sig_221;
assign sig_243 = sig_241 & sig_202;
assign sig_244 = sig_241 ^ sig_202;
assign sig_245 = sig_242 | sig_243;
assign sig_246 = sig_211 ^ sig_222;
assign sig_247 = sig_211 & sig_222;
assign sig_248 = sig_246 & sig_207;
assign sig_249 = sig_246 ^ sig_207;
assign sig_250 = sig_247 | sig_248;
assign sig_251 = sig_216 ^ sig_223;
assign sig_252 = sig_216 & sig_223;
assign sig_253 = sig_251 & sig_212;
assign sig_254 = sig_251 ^ sig_212;
assign sig_255 = sig_252 | sig_253;
assign sig_256 = sig_182 ^ sig_224;
assign sig_257 = sig_182 & sig_224;
assign sig_258 = sig_256 & sig_217;
assign sig_259 = sig_256 ^ sig_217;
assign sig_260 = sig_257 | sig_258;
assign sig_261 = B[0] & A[7];
assign sig_262 = B[1] & A[7];
assign sig_263 = B[2] & A[7];
assign sig_264 = B[3] & A[7];
assign sig_265 = B[4] & A[7];
assign sig_266 = B[5] & A[7];
assign sig_267 = B[6] & A[7];
assign sig_268 = B[7] & A[7];
assign sig_269 = sig_234 ^ sig_261;
assign sig_270 = sig_234 & sig_261;
assign sig_271 = sig_269 & sig_230;
assign sig_272 = sig_269 ^ sig_230;
assign sig_273 = sig_270 | sig_271;
assign sig_274 = sig_239 ^ sig_262;
assign sig_275 = sig_239 & sig_262;
assign sig_276 = sig_274 & sig_235;
assign sig_277 = sig_274 ^ sig_235;
assign sig_278 = sig_275 | sig_276;
assign sig_279 = sig_244 ^ sig_263;
assign sig_280 = sig_244 & sig_263;
assign sig_281 = sig_279 & sig_240;
assign sig_282 = sig_279 ^ sig_240;
assign sig_283 = sig_280 | sig_281;
assign sig_284 = sig_249 ^ sig_264;
assign sig_285 = sig_249 & sig_264;
assign sig_286 = sig_284 & sig_245;
assign sig_287 = sig_284 ^ sig_245;
assign sig_288 = sig_285 | sig_286;
assign sig_289 = sig_254 ^ sig_265;
assign sig_290 = sig_254 & sig_265;
assign sig_291 = sig_289 & sig_250;
assign sig_292 = sig_289 ^ sig_250;
assign sig_293 = sig_290 | sig_291;
assign sig_294 = sig_259 ^ sig_266;
assign sig_295 = sig_259 & sig_266;
assign sig_296 = sig_294 & sig_255;
assign sig_297 = sig_294 ^ sig_255;
assign sig_298 = sig_295 | sig_296;
assign sig_299 = sig_225 ^ sig_267;
assign sig_300 = sig_225 & sig_267;
assign sig_301 = sig_299 & sig_260;
assign sig_302 = sig_299 ^ sig_260;
assign sig_303 = sig_300 | sig_301;
assign sig_304 = sig_277 ^ sig_273;
assign sig_305 = sig_277 & sig_273;
assign sig_306 = sig_282 ^ sig_278;
assign sig_307 = sig_282 & sig_278;
assign sig_308 = sig_306 & sig_305;
assign sig_309 = sig_306 ^ sig_305;
assign sig_310 = sig_307 | sig_308;
assign sig_311 = sig_287 ^ sig_283;
assign sig_312 = sig_287 & sig_283;
assign sig_313 = sig_311 & sig_310;
assign sig_314 = sig_311 ^ sig_310;
assign sig_315 = sig_312 | sig_313;
assign sig_316 = sig_292 ^ sig_288;
assign sig_317 = sig_292 & sig_288;
assign sig_318 = sig_316 & sig_315;
assign sig_319 = sig_316 ^ sig_315;
assign sig_320 = sig_317 | sig_318;
assign sig_321 = sig_297 ^ sig_293;
assign sig_322 = sig_297 & sig_293;
assign sig_323 = sig_321 & sig_320;
assign sig_324 = sig_321 ^ sig_320;
assign sig_325 = sig_322 | sig_323;
assign sig_326 = sig_302 ^ sig_298;
assign sig_327 = sig_302 & sig_298;
assign sig_328 = sig_326 & sig_325;
assign sig_329 = sig_326 ^ sig_325;
assign sig_330 = sig_327 | sig_328;
assign sig_331 = sig_268 ^ sig_303;
assign sig_332 = A[7] & sig_303;
assign sig_333 = sig_331 & sig_330;
assign sig_334 = sig_331 ^ sig_330;
assign sig_335 = sig_332 | sig_333;

assign O[15] = sig_335;
assign O[14] = sig_334;
assign O[13] = sig_329;
assign O[12] = sig_324;
assign O[11] = sig_319;
assign O[10] = sig_314;
assign O[9] = sig_309;
assign O[8] = sig_304;
assign O[7] = sig_272;
assign O[6] = sig_229;
assign O[5] = sig_186;
assign O[4] = sig_143;
assign O[3] = sig_100;
assign O[2] = sig_57;
assign O[1] = 1'b0;
assign O[0] = sig_57;

endmodule



module cla_4bit(aa,bb,cin,summ,pp,gg);
input  [3:0] aa,bb,pp,gg;  
input cin;
output [3:0] summ;

wire [3:0] c;

assign c[0] = cin;
assign c[1] = gg[0] | (pp[0] & c[0]);
assign c[2] = gg[1] | (pp[1] & gg[0]) | (pp[1] & pp[0] & c[0]);
assign c[3] = gg[2] | (pp[2] & gg[1]) | (pp[2] & pp[1] & gg[0])| (pp[2] & pp[1] & pp[0] & c[0]);

assign summ[3:0] = pp[3:0]  ^  c[3:0];
endmodule



module mult8_cgp14zr_wc907_rcam (
    A,
    B,
    O
);

input [7:0] A;
input [7:0] B;
output [15:0] O;

wire sig_65,sig_72,sig_73,sig_101,sig_102,sig_106,sig_107,sig_108,sig_109,sig_110,sig_116,sig_117,sig_118,sig_146,sig_148,sig_149,sig_150,sig_151,sig_152,sig_153;
wire sig_154,sig_155,sig_160,sig_161,sig_162,sig_163,sig_186,sig_187,sig_188,sig_189,sig_190,sig_191,sig_192,sig_193,sig_194,sig_195,sig_196,sig_197,sig_198,sig_199;
wire sig_200,sig_203,sig_205,sig_206,sig_207,sig_208,sig_222,sig_226,sig_227,sig_228,sig_229,sig_230,sig_231,sig_232,sig_233,sig_234,sig_235,sig_236,sig_237,sig_238;
wire sig_239,sig_240,sig_241,sig_242,sig_243,sig_244,sig_245,sig_249,sig_250,sig_251,sig_252,sig_253,sig_266,sig_267,sig_268,sig_269,sig_270,sig_271,sig_272,sig_273;
wire sig_274,sig_275,sig_276,sig_277,sig_278,sig_279,sig_280,sig_281,sig_282,sig_283,sig_284,sig_285,sig_286,sig_287,sig_288,sig_289,sig_290,sig_292,sig_293,sig_294;
wire sig_295,sig_296,sig_297,sig_298,sig_306,sig_307,sig_311,sig_312,sig_313,sig_314,sig_315,sig_316,sig_317,sig_318,sig_319,sig_320,sig_321,sig_322,sig_323,sig_324;
wire sig_325,sig_326,sig_327,sig_328,sig_329,sig_330,sig_331,sig_332,sig_333,sig_334,sig_335;

assign sig_65 = B[7] & A[1];
assign sig_72 = B[6] & A[2];
assign sig_73 = B[7] & A[2];
assign sig_101 = B[5] | B[6];
assign sig_102 = B[5] & sig_72;
assign sig_106 = sig_65 ^ sig_73;
assign sig_107 = sig_65 & A[2];
assign sig_108 = B[7] & sig_102;
assign sig_109 = sig_106 ^ sig_102;
assign sig_110 = sig_107 | sig_108;
assign sig_116 = sig_101 & A[3];
assign sig_117 = B[6] & A[3];
assign sig_118 = B[7] & A[3];
assign sig_146 = sig_109 ^ sig_117;
assign sig_148 = sig_106 & sig_116;
assign sig_149 = sig_146 ^ sig_116;
assign sig_150 = sig_117 | sig_148;
assign sig_151 = sig_110 ^ sig_118;
assign sig_152 = sig_107 & A[3];
assign sig_153 = sig_118 & sig_150;
assign sig_154 = sig_151 ^ sig_150;
assign sig_155 = sig_152 | sig_153;
assign sig_160 = B[4] & A[4];
assign sig_161 = B[5] & A[4];
assign sig_162 = B[6] & A[4];
assign sig_163 = B[7] & A[4];
assign sig_186 = sig_149 ^ sig_161;
assign sig_187 = sig_149 & sig_161;
assign sig_188 = sig_186 & sig_160;
assign sig_189 = sig_186 ^ sig_160;
assign sig_190 = sig_187 | sig_188;
assign sig_191 = sig_154 ^ sig_162;
assign sig_192 = sig_154 & sig_162;
assign sig_193 = sig_191 & sig_190;
assign sig_194 = sig_191 ^ sig_190;
assign sig_195 = sig_192 | sig_193;
assign sig_196 = sig_155 ^ sig_163;
assign sig_197 = sig_155 & A[4];
assign sig_198 = B[7] & sig_195;
assign sig_199 = sig_196 ^ sig_195;
assign sig_200 = sig_197 | sig_198;
assign sig_203 = B[2] & A[6];
assign sig_205 = B[4] & A[5];
assign sig_206 = B[5] & A[5];
assign sig_207 = B[6] & A[5];
assign sig_208 = B[7] & A[5];
assign sig_222 = B[3] & A[5];
assign sig_226 = sig_189 ^ sig_205;
assign sig_227 = sig_189 & sig_205;
assign sig_228 = sig_226 & sig_222;
assign sig_229 = sig_226 ^ sig_222;
assign sig_230 = sig_227 | sig_228;
assign sig_231 = sig_194 ^ sig_206;
assign sig_232 = sig_194 & sig_206;
assign sig_233 = sig_231 & sig_230;
assign sig_234 = sig_231 ^ sig_230;
assign sig_235 = sig_232 | sig_233;
assign sig_236 = sig_199 ^ sig_207;
assign sig_237 = sig_199 & sig_207;
assign sig_238 = sig_236 & sig_235;
assign sig_239 = sig_236 ^ sig_235;
assign sig_240 = sig_237 | sig_238;
assign sig_241 = sig_200 ^ sig_208;
assign sig_242 = sig_200 & A[5];
assign sig_243 = sig_208 & sig_240;
assign sig_244 = sig_241 ^ sig_240;
assign sig_245 = sig_242 | sig_243;
assign sig_249 = B[3] & A[6];
assign sig_250 = B[4] & A[6];
assign sig_251 = B[5] & A[6];
assign sig_252 = B[6] & A[6];
assign sig_253 = B[7] & A[6];
assign sig_266 = sig_229 ^ sig_249;
assign sig_267 = sig_229 & sig_249;
assign sig_268 = sig_266 & sig_203;
assign sig_269 = sig_266 ^ sig_203;
assign sig_270 = sig_267 | sig_268;
assign sig_271 = sig_234 ^ sig_250;
assign sig_272 = sig_234 & sig_250;
assign sig_273 = sig_271 & sig_270;
assign sig_274 = sig_271 ^ sig_270;
assign sig_275 = sig_272 | sig_273;
assign sig_276 = sig_239 ^ sig_251;
assign sig_277 = sig_239 & sig_251;
assign sig_278 = sig_276 & sig_275;
assign sig_279 = sig_276 ^ sig_275;
assign sig_280 = sig_277 | sig_278;
assign sig_281 = sig_244 ^ sig_252;
assign sig_282 = sig_244 & sig_252;
assign sig_283 = sig_281 & sig_280;
assign sig_284 = sig_281 ^ sig_280;
assign sig_285 = sig_282 | sig_283;
assign sig_286 = sig_245 ^ sig_253;
assign sig_287 = sig_245 & A[6];
assign sig_288 = B[7] & sig_285;
assign sig_289 = sig_286 ^ sig_285;
assign sig_290 = sig_287 | sig_288;
assign sig_292 = B[1] & A[7];
assign sig_293 = B[2] & A[7];
assign sig_294 = B[3] & A[7];
assign sig_295 = B[4] & A[7];
assign sig_296 = B[5] & A[7];
assign sig_297 = B[6] & A[7];
assign sig_298 = B[7] & A[7];
assign sig_306 = sig_269 ^ sig_293;
assign sig_307 = sig_269 & sig_293;
assign sig_311 = sig_274 ^ sig_294;
assign sig_312 = sig_274 & sig_294;
assign sig_313 = sig_311 & sig_307;
assign sig_314 = sig_311 ^ sig_307;
assign sig_315 = sig_312 | sig_313;
assign sig_316 = sig_279 ^ sig_295;
assign sig_317 = sig_279 & sig_295;
assign sig_318 = sig_316 & sig_315;
assign sig_319 = sig_316 ^ sig_315;
assign sig_320 = sig_317 | sig_318;
assign sig_321 = sig_284 ^ sig_296;
assign sig_322 = sig_284 & sig_296;
assign sig_323 = sig_321 & sig_320;
assign sig_324 = sig_321 ^ sig_320;
assign sig_325 = sig_322 | sig_323;
assign sig_326 = sig_289 ^ sig_297;
assign sig_327 = sig_289 & sig_297;
assign sig_328 = sig_326 & sig_325;
assign sig_329 = sig_326 ^ sig_325;
assign sig_330 = sig_327 | sig_328;
assign sig_331 = sig_290 ^ sig_298;
assign sig_332 = sig_290 & A[7];
assign sig_333 = B[7] & sig_330;
assign sig_334 = sig_331 ^ sig_330;
assign sig_335 = sig_332 | sig_333;

assign O[15] = sig_335;
assign O[14] = sig_334;
assign O[13] = sig_329;
assign O[12] = sig_324;
assign O[11] = sig_319;
assign O[10] = sig_314;
assign O[9] = sig_306;
assign O[8] = sig_292;
assign O[7] = sig_292;
assign O[6] = sig_72;
assign O[5] = 1'b0;
assign O[4] = sig_317;
assign O[3] = 1'b0;
assign O[2] = sig_312;
assign O[1] = sig_293;
assign O[0] = sig_249;

endmodule


module mult8_cgp14zr_wc7391_rcam (
    A,
    B,
    O
);

input [7:0] A;
input [7:0] B;
output [15:0] O;

wire sig_242,sig_246,sig_251,sig_252,sig_253,sig_286,sig_288,sig_289,sig_290,sig_295,sig_296,sig_297,sig_298,sig_323,sig_324,sig_326,sig_327,sig_328,sig_329,sig_330;
wire sig_331,sig_332,sig_333,sig_334,sig_335;

assign sig_242 = A[5] & B[7];
assign sig_246 = sig_242 & A[6];
assign sig_251 = B[5] & A[4];
assign sig_252 = B[6] & A[6];
assign sig_253 = B[7] & A[6];
assign sig_286 = sig_242 ^ sig_253;
assign sig_288 = B[7] & sig_252;
assign sig_289 = sig_286 ^ sig_252;
assign sig_290 = sig_246 | sig_288;
assign sig_295 = B[4] & A[7];
assign sig_296 = B[5] & A[7];
assign sig_297 = B[6] & A[7];
assign sig_298 = B[7] & A[7];
assign sig_323 = sig_296 & B[4];
assign sig_324 = sig_296 ^ sig_295;
assign sig_326 = sig_289 ^ sig_297;
assign sig_327 = sig_289 & sig_297;
assign sig_328 = sig_326 & sig_323;
assign sig_329 = sig_326 ^ sig_323;
assign sig_330 = sig_327 | sig_328;
assign sig_331 = sig_290 ^ sig_298;
assign sig_332 = sig_290 & sig_298;
assign sig_333 = B[7] & sig_330;
assign sig_334 = sig_331 ^ sig_330;
assign sig_335 = sig_332 | sig_333;

assign O[15] = sig_335;
assign O[14] = sig_334;
assign O[13] = sig_329;
assign O[12] = sig_324;
assign O[11] = sig_251;
assign O[10] = sig_329;
assign O[9] = 1'b0;
assign O[8] = sig_298;
assign O[7] = sig_335;
assign O[6] = sig_332;
assign O[5] = 1'b0;
assign O[4] = 1'b0;
assign O[3] = 1'b0;
assign O[2] = 1'b0;
assign O[1] = sig_251;
assign O[0] = 1'b0;

endmodule


module mult8_cgp14ep_ep64716_wc26_csamrca (
    A,
    B,
    O
);

input [7:0] A;
input [7:0] B;
output [15:0] O;

wire sig_20,sig_21,sig_22,sig_23,sig_27,sig_28,sig_29,sig_30,sig_31,sig_38,sig_39,sig_40,sig_41,sig_42,sig_43,sig_44,sig_45,sig_48,sig_49,sig_50;
wire sig_51,sig_52,sig_53,sig_63,sig_64,sig_65,sig_69,sig_70,sig_71,sig_72,sig_73,sig_74,sig_75,sig_76,sig_77,sig_78,sig_79,sig_80,sig_81,sig_82;
wire sig_83,sig_84,sig_85,sig_87,sig_88,sig_91,sig_92,sig_93,sig_94,sig_95,sig_96,sig_103,sig_105,sig_107,sig_108,sig_109,sig_110,sig_111,sig_112,sig_113;
wire sig_114,sig_115,sig_116,sig_117,sig_118,sig_119,sig_120,sig_121,sig_122,sig_123,sig_124,sig_125,sig_126,sig_127,sig_128,sig_129,sig_130,sig_131,sig_132,sig_133;
wire sig_134,sig_135,sig_136,sig_137,sig_138,sig_139,sig_140,sig_141,sig_145,sig_146,sig_147,sig_148,sig_149,sig_150,sig_151,sig_152,sig_153,sig_154,sig_155,sig_156;
wire sig_157,sig_158,sig_159,sig_160,sig_161,sig_162,sig_163,sig_164,sig_165,sig_166,sig_167,sig_168,sig_169,sig_170,sig_171,sig_172,sig_173,sig_174,sig_175,sig_176;
wire sig_177,sig_178,sig_179,sig_180,sig_181,sig_182,sig_183,sig_184,sig_185,sig_186,sig_187,sig_188,sig_189,sig_190,sig_191,sig_192,sig_193,sig_194,sig_195,sig_196;
wire sig_197,sig_198,sig_199,sig_200,sig_201,sig_202,sig_203,sig_204,sig_205,sig_206,sig_207,sig_208,sig_209,sig_210,sig_211,sig_212,sig_213,sig_214,sig_215,sig_216;
wire sig_217,sig_218,sig_219,sig_220,sig_221,sig_222,sig_223,sig_224,sig_225,sig_226,sig_227,sig_228,sig_229,sig_230,sig_231,sig_232,sig_233,sig_234,sig_235,sig_236;
wire sig_237,sig_238,sig_239,sig_240,sig_241,sig_242,sig_243,sig_244,sig_245,sig_246,sig_247,sig_248,sig_249,sig_250,sig_251,sig_252,sig_253,sig_254,sig_255,sig_256;
wire sig_257,sig_258,sig_259,sig_260,sig_261,sig_262,sig_263,sig_264,sig_265,sig_266,sig_267,sig_268,sig_269,sig_270,sig_271,sig_272,sig_273,sig_274,sig_275,sig_276;
wire sig_277,sig_278,sig_279,sig_280,sig_281,sig_282,sig_283,sig_284,sig_285,sig_286,sig_287,sig_288,sig_289,sig_290,sig_291,sig_292,sig_293,sig_294,sig_295,sig_296;
wire sig_297,sig_298,sig_299,sig_300,sig_301,sig_302,sig_303,sig_304,sig_305,sig_306,sig_307,sig_308,sig_309,sig_310,sig_311,sig_312,sig_313,sig_314,sig_315,sig_316;
wire sig_317,sig_318,sig_319,sig_320,sig_321,sig_322,sig_323,sig_324,sig_325,sig_326,sig_327,sig_328,sig_329,sig_330,sig_331,sig_332,sig_333,sig_334,sig_335;

assign sig_20 = B[4] & A[0];
assign sig_21 = B[5] & A[0];
assign sig_22 = B[6] & A[0];
assign sig_23 = B[7] & A[0];
assign sig_27 = B[3] & A[1];
assign sig_28 = B[4] & A[1];
assign sig_29 = B[5] & A[1];
assign sig_30 = B[6] & A[1];
assign sig_31 = B[7] & A[1];
assign sig_38 = sig_20 | sig_27;
assign sig_39 = sig_20 & sig_27;
assign sig_40 = sig_21 ^ sig_28;
assign sig_41 = sig_21 & sig_28;
assign sig_42 = sig_22 ^ sig_29;
assign sig_43 = sig_22 & sig_29;
assign sig_44 = sig_23 ^ sig_30;
assign sig_45 = sig_23 & sig_30;
assign sig_48 = B[2] & A[2];
assign sig_49 = B[3] & A[2];
assign sig_50 = B[4] & A[2];
assign sig_51 = B[5] & A[2];
assign sig_52 = B[6] & A[2];
assign sig_53 = B[7] & A[2];
assign sig_63 = A[3] & B[1];
assign sig_64 = sig_38 | sig_48;
assign sig_65 = sig_38 & sig_48;
assign sig_69 = sig_40 ^ sig_49;
assign sig_70 = sig_40 & sig_49;
assign sig_71 = sig_69 & sig_39;
assign sig_72 = sig_69 ^ sig_39;
assign sig_73 = sig_70 | sig_71;
assign sig_74 = sig_42 ^ sig_50;
assign sig_75 = sig_42 & sig_50;
assign sig_76 = sig_74 & sig_41;
assign sig_77 = sig_74 ^ sig_41;
assign sig_78 = sig_75 | sig_76;
assign sig_79 = sig_44 ^ sig_51;
assign sig_80 = sig_44 & sig_51;
assign sig_81 = sig_79 & sig_43;
assign sig_82 = sig_79 ^ sig_43;
assign sig_83 = sig_80 | sig_81;
assign sig_84 = sig_31 ^ sig_52;
assign sig_85 = sig_31 & sig_52;
assign sig_87 = sig_84 ^ sig_45;
assign sig_88 = sig_85 | sig_45;
assign sig_91 = B[2] & A[3];
assign sig_92 = B[3] & A[3];
assign sig_93 = B[4] & A[3];
assign sig_94 = B[5] & A[3];
assign sig_95 = B[6] & A[3];
assign sig_96 = B[7] & A[3];
assign sig_103 = sig_64 & sig_63;
assign sig_105 = sig_64 | sig_63;
assign sig_107 = sig_72 ^ sig_91;
assign sig_108 = sig_72 & sig_91;
assign sig_109 = sig_107 & sig_65;
assign sig_110 = sig_107 ^ sig_65;
assign sig_111 = sig_108 | sig_109;
assign sig_112 = sig_77 ^ sig_92;
assign sig_113 = sig_77 & sig_92;
assign sig_114 = sig_112 & sig_73;
assign sig_115 = sig_112 ^ sig_73;
assign sig_116 = sig_113 | sig_114;
assign sig_117 = sig_82 ^ sig_93;
assign sig_118 = sig_82 & sig_93;
assign sig_119 = sig_117 & sig_78;
assign sig_120 = sig_117 ^ sig_78;
assign sig_121 = sig_118 | sig_119;
assign sig_122 = sig_87 ^ sig_94;
assign sig_123 = sig_87 & sig_94;
assign sig_124 = sig_122 & sig_83;
assign sig_125 = sig_122 ^ sig_83;
assign sig_126 = sig_123 | sig_124;
assign sig_127 = sig_53 ^ sig_95;
assign sig_128 = sig_53 & sig_95;
assign sig_129 = sig_127 & sig_88;
assign sig_130 = sig_127 ^ sig_88;
assign sig_131 = sig_128 | sig_129;
assign sig_132 = B[0] & A[4];
assign sig_133 = B[1] & A[4];
assign sig_134 = B[2] & A[4];
assign sig_135 = B[3] & A[4];
assign sig_136 = B[4] & A[4];
assign sig_137 = B[5] & A[4];
assign sig_138 = B[6] & A[4];
assign sig_139 = B[7] & A[4];
assign sig_140 = sig_105 ^ sig_132;
assign sig_141 = sig_105 & sig_132;
assign sig_145 = sig_110 ^ sig_133;
assign sig_146 = sig_110 & sig_133;
assign sig_147 = sig_145 & sig_103;
assign sig_148 = sig_145 ^ sig_103;
assign sig_149 = sig_146 | sig_147;
assign sig_150 = sig_115 ^ sig_134;
assign sig_151 = sig_115 & sig_134;
assign sig_152 = sig_150 & sig_111;
assign sig_153 = sig_150 ^ sig_111;
assign sig_154 = sig_151 | sig_152;
assign sig_155 = sig_120 ^ sig_135;
assign sig_156 = sig_120 & sig_135;
assign sig_157 = sig_155 & sig_116;
assign sig_158 = sig_155 ^ sig_116;
assign sig_159 = sig_156 | sig_157;
assign sig_160 = sig_125 ^ sig_136;
assign sig_161 = sig_125 & sig_136;
assign sig_162 = sig_160 & sig_121;
assign sig_163 = sig_160 ^ sig_121;
assign sig_164 = sig_161 | sig_162;
assign sig_165 = sig_130 ^ sig_137;
assign sig_166 = sig_130 & sig_137;
assign sig_167 = sig_165 & sig_126;
assign sig_168 = sig_165 ^ sig_126;
assign sig_169 = sig_166 | sig_167;
assign sig_170 = sig_96 ^ sig_138;
assign sig_171 = sig_96 & sig_138;
assign sig_172 = sig_170 & sig_131;
assign sig_173 = sig_170 ^ sig_131;
assign sig_174 = sig_171 | sig_172;
assign sig_175 = B[0] & A[5];
assign sig_176 = B[1] & A[5];
assign sig_177 = B[2] & A[5];
assign sig_178 = B[3] & A[5];
assign sig_179 = B[4] & A[5];
assign sig_180 = B[5] & A[5];
assign sig_181 = B[6] & A[5];
assign sig_182 = B[7] & A[5];
assign sig_183 = sig_148 ^ sig_175;
assign sig_184 = sig_148 & sig_175;
assign sig_185 = sig_183 & sig_141;
assign sig_186 = sig_183 ^ sig_141;
assign sig_187 = sig_184 | sig_185;
assign sig_188 = sig_153 ^ sig_176;
assign sig_189 = sig_153 & sig_176;
assign sig_190 = sig_188 & sig_149;
assign sig_191 = sig_188 ^ sig_149;
assign sig_192 = sig_189 | sig_190;
assign sig_193 = sig_158 ^ sig_177;
assign sig_194 = sig_158 & sig_177;
assign sig_195 = sig_193 & sig_154;
assign sig_196 = sig_193 ^ sig_154;
assign sig_197 = sig_194 | sig_195;
assign sig_198 = sig_163 ^ sig_178;
assign sig_199 = sig_163 & sig_178;
assign sig_200 = sig_198 & sig_159;
assign sig_201 = sig_198 ^ sig_159;
assign sig_202 = sig_199 | sig_200;
assign sig_203 = sig_168 ^ sig_179;
assign sig_204 = sig_168 & sig_179;
assign sig_205 = sig_203 & sig_164;
assign sig_206 = sig_203 ^ sig_164;
assign sig_207 = sig_204 | sig_205;
assign sig_208 = sig_173 ^ sig_180;
assign sig_209 = sig_173 & sig_180;
assign sig_210 = sig_208 & sig_169;
assign sig_211 = sig_208 ^ sig_169;
assign sig_212 = sig_209 | sig_210;
assign sig_213 = sig_139 ^ sig_181;
assign sig_214 = sig_139 & sig_181;
assign sig_215 = sig_213 & sig_174;
assign sig_216 = sig_213 ^ sig_174;
assign sig_217 = sig_214 | sig_215;
assign sig_218 = B[0] & A[6];
assign sig_219 = B[1] & A[6];
assign sig_220 = B[2] & A[6];
assign sig_221 = B[3] & A[6];
assign sig_222 = B[4] & A[6];
assign sig_223 = B[5] & A[6];
assign sig_224 = B[6] & A[6];
assign sig_225 = B[7] & A[6];
assign sig_226 = sig_191 ^ sig_218;
assign sig_227 = sig_191 & sig_218;
assign sig_228 = sig_226 & sig_187;
assign sig_229 = sig_226 ^ sig_187;
assign sig_230 = sig_227 | sig_228;
assign sig_231 = sig_196 ^ sig_219;
assign sig_232 = sig_196 & sig_219;
assign sig_233 = sig_231 & sig_192;
assign sig_234 = sig_231 ^ sig_192;
assign sig_235 = sig_232 | sig_233;
assign sig_236 = sig_201 ^ sig_220;
assign sig_237 = sig_201 & sig_220;
assign sig_238 = sig_236 & sig_197;
assign sig_239 = sig_236 ^ sig_197;
assign sig_240 = sig_237 | sig_238;
assign sig_241 = sig_206 ^ sig_221;
assign sig_242 = sig_206 & sig_221;
assign sig_243 = sig_241 & sig_202;
assign sig_244 = sig_241 ^ sig_202;
assign sig_245 = sig_242 | sig_243;
assign sig_246 = sig_211 ^ sig_222;
assign sig_247 = sig_211 & sig_222;
assign sig_248 = sig_246 & sig_207;
assign sig_249 = sig_246 ^ sig_207;
assign sig_250 = sig_247 | sig_248;
assign sig_251 = sig_216 ^ sig_223;
assign sig_252 = sig_216 & sig_223;
assign sig_253 = sig_251 & sig_212;
assign sig_254 = sig_251 ^ sig_212;
assign sig_255 = sig_252 | sig_253;
assign sig_256 = sig_182 ^ sig_224;
assign sig_257 = sig_182 & sig_224;
assign sig_258 = sig_256 & sig_217;
assign sig_259 = sig_256 ^ sig_217;
assign sig_260 = sig_257 | sig_258;
assign sig_261 = B[0] & A[7];
assign sig_262 = B[1] & A[7];
assign sig_263 = B[2] & A[7];
assign sig_264 = B[3] & A[7];
assign sig_265 = B[4] & A[7];
assign sig_266 = B[5] & A[7];
assign sig_267 = B[6] & A[7];
assign sig_268 = B[7] & A[7];
assign sig_269 = sig_234 ^ sig_261;
assign sig_270 = sig_234 & sig_261;
assign sig_271 = sig_269 & sig_230;
assign sig_272 = sig_269 ^ sig_230;
assign sig_273 = sig_270 | sig_271;
assign sig_274 = sig_239 ^ sig_262;
assign sig_275 = sig_239 & sig_262;
assign sig_276 = sig_274 & sig_235;
assign sig_277 = sig_274 ^ sig_235;
assign sig_278 = sig_275 | sig_276;
assign sig_279 = sig_244 ^ sig_263;
assign sig_280 = sig_244 & sig_263;
assign sig_281 = sig_279 & sig_240;
assign sig_282 = sig_279 ^ sig_240;
assign sig_283 = sig_280 | sig_281;
assign sig_284 = sig_249 ^ sig_264;
assign sig_285 = sig_249 & sig_264;
assign sig_286 = sig_284 & sig_245;
assign sig_287 = sig_284 ^ sig_245;
assign sig_288 = sig_285 | sig_286;
assign sig_289 = sig_254 ^ sig_265;
assign sig_290 = sig_254 & sig_265;
assign sig_291 = sig_289 & sig_250;
assign sig_292 = sig_289 ^ sig_250;
assign sig_293 = sig_290 | sig_291;
assign sig_294 = sig_259 ^ sig_266;
assign sig_295 = sig_259 & sig_266;
assign sig_296 = sig_294 & sig_255;
assign sig_297 = sig_294 ^ sig_255;
assign sig_298 = sig_295 | sig_296;
assign sig_299 = sig_225 ^ sig_267;
assign sig_300 = sig_225 & sig_267;
assign sig_301 = sig_299 & sig_260;
assign sig_302 = sig_299 ^ sig_260;
assign sig_303 = sig_300 | sig_301;
assign sig_304 = sig_277 ^ sig_273;
assign sig_305 = sig_277 & sig_273;
assign sig_306 = sig_282 ^ sig_278;
assign sig_307 = sig_282 & sig_278;
assign sig_308 = sig_306 & sig_305;
assign sig_309 = sig_306 ^ sig_305;
assign sig_310 = sig_307 | sig_308;
assign sig_311 = sig_287 ^ sig_283;
assign sig_312 = sig_287 & sig_283;
assign sig_313 = sig_311 & sig_310;
assign sig_314 = sig_311 ^ sig_310;
assign sig_315 = sig_312 | sig_313;
assign sig_316 = sig_292 ^ sig_288;
assign sig_317 = sig_292 & sig_288;
assign sig_318 = sig_316 & sig_315;
assign sig_319 = sig_316 ^ sig_315;
assign sig_320 = sig_317 | sig_318;
assign sig_321 = sig_297 ^ sig_293;
assign sig_322 = sig_297 & sig_293;
assign sig_323 = sig_321 & sig_320;
assign sig_324 = sig_321 ^ sig_320;
assign sig_325 = sig_322 | sig_323;
assign sig_326 = sig_302 ^ sig_298;
assign sig_327 = sig_302 & sig_298;
assign sig_328 = sig_326 & sig_325;
assign sig_329 = sig_326 ^ sig_325;
assign sig_330 = sig_327 | sig_328;
assign sig_331 = sig_268 ^ sig_303;
assign sig_332 = A[7] & sig_303;
assign sig_333 = sig_331 & sig_330;
assign sig_334 = sig_331 ^ sig_330;
assign sig_335 = sig_332 | sig_333;

assign O[15] = sig_335;
assign O[14] = sig_334;
assign O[13] = sig_329;
assign O[12] = sig_324;
assign O[11] = sig_319;
assign O[10] = sig_314;
assign O[9] = sig_309;
assign O[8] = sig_304;
assign O[7] = sig_272;
assign O[6] = sig_229;
assign O[5] = sig_186;
assign O[4] = sig_140;
assign O[3] = sig_105;
assign O[2] = sig_132;
assign O[1] = sig_218;
assign O[0] = 1'b0;

endmodule


module mult8_cgp14ep_ep65536_wc16384_2_csamcsa (
    A,
    B,
    O
);

input [7:0] A;
input [7:0] B;
output [15:0] O;

wire sig_225,sig_267,sig_268,sig_299,sig_300,sig_302,sig_328,sig_331;

assign sig_225 = B[7] & A[6];
assign sig_267 = B[6] & A[7];
assign sig_268 = B[7] & A[7];
assign sig_299 = sig_225 | sig_267;
assign sig_300 = sig_225 & sig_267;
assign sig_302 = sig_299 | sig_268;
assign sig_328 = sig_268 ^ sig_300;
assign sig_331 = sig_328 ^ sig_302;

assign O[15] = sig_268;
assign O[14] = sig_331;
assign O[13] = 1'b0;
assign O[12] = 1'b0;
assign O[11] = 1'b0;
assign O[10] = 1'b0;
assign O[9] = 1'b0;
assign O[8] = 1'b0;
assign O[7] = 1'b0;
assign O[6] = 1'b0;
assign O[5] = 1'b0;
assign O[4] = 1'b0;
assign O[3] = 1'b0;
assign O[2] = 1'b0;
assign O[1] = 1'b0;
assign O[0] = 1'b0;

endmodule


module mult8_cgp14ep_ep63897_wc377_rcam (
    A,
    B,
    O
);

input [7:0] A;
input [7:0] B;
output [15:0] O;

wire sig_23,sig_30,sig_31,sig_59,sig_60,sig_63,sig_64,sig_72,sig_73,sig_90,sig_97,sig_101,sig_102,sig_103,sig_104,sig_105,sig_106,sig_107,sig_108,sig_109;
wire sig_110,sig_114,sig_115,sig_117,sig_118,sig_141,sig_142,sig_143,sig_144,sig_145,sig_146,sig_147,sig_148,sig_149,sig_150,sig_151,sig_152,sig_153,sig_154,sig_155;
wire sig_160,sig_161,sig_162,sig_163,sig_165,sig_172,sig_173,sig_176,sig_177,sig_181,sig_182,sig_183,sig_184,sig_185,sig_186,sig_187,sig_188,sig_189,sig_190,sig_191;
wire sig_193,sig_194,sig_195,sig_196,sig_198,sig_199,sig_200,sig_204,sig_205,sig_206,sig_207,sig_208,sig_216,sig_221,sig_222,sig_223,sig_224,sig_225,sig_226,sig_227;
wire sig_228,sig_229,sig_230,sig_231,sig_232,sig_233,sig_234,sig_235,sig_236,sig_237,sig_238,sig_239,sig_240,sig_241,sig_242,sig_243,sig_244,sig_245,sig_247,sig_248;
wire sig_249,sig_250,sig_251,sig_252,sig_253,sig_256,sig_259,sig_261,sig_262,sig_263,sig_264,sig_265,sig_266,sig_267,sig_268,sig_269,sig_270,sig_271,sig_272,sig_273;
wire sig_274,sig_275,sig_276,sig_277,sig_278,sig_279,sig_280,sig_281,sig_282,sig_283,sig_284,sig_285,sig_286,sig_287,sig_288,sig_289,sig_290,sig_291,sig_292,sig_293;
wire sig_294,sig_295,sig_296,sig_297,sig_298,sig_299,sig_300,sig_301,sig_302,sig_303,sig_304,sig_305,sig_306,sig_307,sig_308,sig_309,sig_310,sig_311,sig_312,sig_313;
wire sig_314,sig_315,sig_316,sig_317,sig_318,sig_319,sig_320,sig_321,sig_322,sig_323,sig_324,sig_325,sig_326,sig_327,sig_328,sig_329,sig_330,sig_331,sig_332,sig_333;
wire sig_334,sig_335;

assign sig_23 = B[7] & A[0];
assign sig_30 = B[6] & A[1];
assign sig_31 = B[7] & A[1];
assign sig_59 = sig_23 | sig_30;
assign sig_60 = sig_23 & sig_30;
assign sig_63 = sig_31 & B[6];
assign sig_64 = sig_60 ^ sig_31;
assign sig_72 = B[6] & A[2];
assign sig_73 = B[7] & A[2];
assign sig_90 = sig_63 & A[0];
assign sig_97 = A[2] & B[5];
assign sig_101 = sig_64 ^ sig_72;
assign sig_102 = sig_64 & sig_72;
assign sig_103 = sig_101 & sig_97;
assign sig_104 = sig_101 ^ sig_97;
assign sig_105 = sig_102 | sig_103;
assign sig_106 = sig_90 ^ sig_73;
assign sig_107 = sig_63 & A[2];
assign sig_108 = sig_73 & sig_105;
assign sig_109 = sig_106 ^ sig_105;
assign sig_110 = sig_107 | sig_108;
assign sig_114 = B[5] & A[3];
assign sig_115 = B[4] & A[3];
assign sig_117 = B[6] & A[3];
assign sig_118 = B[7] & A[3];
assign sig_141 = sig_104 ^ sig_114;
assign sig_142 = sig_104 & sig_114;
assign sig_143 = sig_141 & sig_115;
assign sig_144 = sig_141 ^ sig_115;
assign sig_145 = sig_142 | sig_143;
assign sig_146 = sig_109 ^ sig_117;
assign sig_147 = sig_109 & sig_117;
assign sig_148 = sig_146 & sig_145;
assign sig_149 = sig_146 ^ sig_145;
assign sig_150 = sig_147 | sig_148;
assign sig_151 = sig_110 ^ sig_118;
assign sig_152 = sig_110 & A[3];
assign sig_153 = B[7] & sig_150;
assign sig_154 = sig_151 ^ sig_150;
assign sig_155 = sig_152 | sig_153;
assign sig_160 = B[4] & A[4];
assign sig_161 = B[5] & A[4];
assign sig_162 = B[6] & A[4];
assign sig_163 = B[7] & A[4];
assign sig_165 = sig_162 & sig_154;
assign sig_172 = B[2] & A[5];
assign sig_173 = sig_155 & A[4];
assign sig_176 = sig_59 | sig_172;
assign sig_177 = A[4] & B[3];
assign sig_181 = sig_144 ^ sig_160;
assign sig_182 = sig_144 & sig_160;
assign sig_183 = sig_181 & sig_177;
assign sig_184 = sig_181 ^ sig_177;
assign sig_185 = sig_182 | sig_183;
assign sig_186 = sig_149 ^ sig_161;
assign sig_187 = sig_149 & sig_161;
assign sig_188 = sig_186 & sig_185;
assign sig_189 = sig_186 ^ sig_185;
assign sig_190 = sig_187 | sig_188;
assign sig_191 = sig_154 ^ sig_162;
assign sig_193 = sig_191 & sig_190;
assign sig_194 = sig_191 ^ sig_190;
assign sig_195 = sig_165 | sig_193;
assign sig_196 = sig_155 ^ sig_163;
assign sig_198 = sig_163 & sig_195;
assign sig_199 = sig_196 ^ sig_195;
assign sig_200 = sig_173 | sig_198;
assign sig_204 = B[3] & A[5];
assign sig_205 = B[4] & A[5];
assign sig_206 = B[5] & A[5];
assign sig_207 = B[6] & A[5];
assign sig_208 = B[7] & A[5];
assign sig_216 = sig_176 ^ sig_172;
assign sig_221 = sig_184 ^ sig_204;
assign sig_222 = sig_184 & sig_204;
assign sig_223 = sig_221 & sig_172;
assign sig_224 = sig_221 ^ sig_172;
assign sig_225 = sig_222 | sig_223;
assign sig_226 = sig_189 ^ sig_205;
assign sig_227 = sig_189 & sig_205;
assign sig_228 = sig_226 & sig_225;
assign sig_229 = sig_226 ^ sig_225;
assign sig_230 = sig_227 | sig_228;
assign sig_231 = sig_194 ^ sig_206;
assign sig_232 = sig_194 & sig_206;
assign sig_233 = sig_231 & sig_230;
assign sig_234 = sig_231 ^ sig_230;
assign sig_235 = sig_232 | sig_233;
assign sig_236 = sig_199 ^ sig_207;
assign sig_237 = sig_199 & sig_207;
assign sig_238 = sig_236 & sig_235;
assign sig_239 = sig_236 ^ sig_235;
assign sig_240 = sig_237 | sig_238;
assign sig_241 = sig_200 ^ sig_208;
assign sig_242 = sig_200 & A[5];
assign sig_243 = sig_208 & sig_240;
assign sig_244 = sig_241 ^ sig_240;
assign sig_245 = sig_242 | sig_243;
assign sig_247 = B[1] & A[6];
assign sig_248 = B[2] & A[6];
assign sig_249 = B[3] & A[6];
assign sig_250 = B[4] & A[6];
assign sig_251 = B[5] & A[6];
assign sig_252 = B[6] & A[6];
assign sig_253 = B[7] & A[6];
assign sig_256 = sig_216 | sig_247;
assign sig_259 = sig_256 ^ sig_247;
assign sig_261 = sig_224 ^ sig_248;
assign sig_262 = sig_224 & sig_248;
assign sig_263 = sig_261 & sig_247;
assign sig_264 = sig_261 ^ sig_247;
assign sig_265 = sig_262 | sig_263;
assign sig_266 = sig_229 ^ sig_249;
assign sig_267 = sig_229 & sig_249;
assign sig_268 = sig_266 & sig_265;
assign sig_269 = sig_266 ^ sig_265;
assign sig_270 = sig_267 | sig_268;
assign sig_271 = sig_234 ^ sig_250;
assign sig_272 = sig_234 & sig_250;
assign sig_273 = sig_271 & sig_270;
assign sig_274 = sig_271 ^ sig_270;
assign sig_275 = sig_272 | sig_273;
assign sig_276 = sig_239 ^ sig_251;
assign sig_277 = sig_239 & sig_251;
assign sig_278 = sig_276 & sig_275;
assign sig_279 = sig_276 ^ sig_275;
assign sig_280 = sig_277 | sig_278;
assign sig_281 = sig_244 ^ sig_252;
assign sig_282 = sig_244 & sig_252;
assign sig_283 = sig_281 & sig_280;
assign sig_284 = sig_281 ^ sig_280;
assign sig_285 = sig_282 | sig_283;
assign sig_286 = sig_245 ^ sig_253;
assign sig_287 = sig_245 & A[6];
assign sig_288 = sig_253 & sig_285;
assign sig_289 = sig_286 ^ sig_285;
assign sig_290 = sig_287 | sig_288;
assign sig_291 = B[0] & A[7];
assign sig_292 = B[1] & A[7];
assign sig_293 = B[2] & A[7];
assign sig_294 = B[3] & A[7];
assign sig_295 = B[4] & A[7];
assign sig_296 = B[5] & A[7];
assign sig_297 = B[6] & A[7];
assign sig_298 = B[7] & A[7];
assign sig_299 = sig_259 | sig_291;
assign sig_300 = sig_259 & sig_291;
assign sig_301 = sig_264 ^ sig_292;
assign sig_302 = sig_264 & sig_292;
assign sig_303 = sig_301 & sig_300;
assign sig_304 = sig_301 ^ sig_300;
assign sig_305 = sig_302 | sig_303;
assign sig_306 = sig_269 ^ sig_293;
assign sig_307 = sig_269 & sig_293;
assign sig_308 = sig_306 & sig_305;
assign sig_309 = sig_306 ^ sig_305;
assign sig_310 = sig_307 | sig_308;
assign sig_311 = sig_274 ^ sig_294;
assign sig_312 = sig_274 & sig_294;
assign sig_313 = sig_311 & sig_310;
assign sig_314 = sig_311 ^ sig_310;
assign sig_315 = sig_312 | sig_313;
assign sig_316 = sig_279 ^ sig_295;
assign sig_317 = sig_279 & sig_295;
assign sig_318 = sig_316 & sig_315;
assign sig_319 = sig_316 ^ sig_315;
assign sig_320 = sig_317 | sig_318;
assign sig_321 = sig_284 ^ sig_296;
assign sig_322 = sig_284 & sig_296;
assign sig_323 = sig_321 & sig_320;
assign sig_324 = sig_321 ^ sig_320;
assign sig_325 = sig_322 | sig_323;
assign sig_326 = sig_289 ^ sig_297;
assign sig_327 = sig_289 & sig_297;
assign sig_328 = sig_326 & sig_325;
assign sig_329 = sig_326 ^ sig_325;
assign sig_330 = sig_327 | sig_328;
assign sig_331 = sig_290 ^ sig_298;
assign sig_332 = sig_290 & A[7];
assign sig_333 = B[7] & sig_330;
assign sig_334 = sig_331 ^ sig_330;
assign sig_335 = sig_332 | sig_333;

assign O[15] = sig_335;
assign O[14] = sig_334;
assign O[13] = sig_329;
assign O[12] = sig_324;
assign O[11] = sig_319;
assign O[10] = sig_314;
assign O[9] = sig_309;
assign O[8] = sig_304;
assign O[7] = sig_299;
assign O[6] = sig_59;
assign O[5] = sig_222;
assign O[4] = 1'b0;
assign O[3] = sig_115;
assign O[2] = sig_172;
assign O[1] = sig_73;
assign O[0] = 1'b0;

endmodule


module mult8_cgp14ep_ep65536_wc4545_rcam (
    A,
    B,
    O
);

input [7:0] A;
input [7:0] B;
output [15:0] O;

wire sig_163,sig_208,sig_241,sig_242,sig_251,sig_252,sig_253,sig_260,sig_272,sig_281,sig_283,sig_284,sig_285,sig_286,sig_287,sig_288,sig_289,sig_290,sig_295,sig_296;
wire sig_297,sig_298,sig_312,sig_313,sig_315,sig_316,sig_317,sig_318,sig_319,sig_320,sig_321,sig_322,sig_323,sig_324,sig_325,sig_326,sig_327,sig_328,sig_329,sig_330;
wire sig_331,sig_332,sig_333,sig_334,sig_335;

assign sig_163 = B[7] & A[4];
assign sig_208 = B[7] & A[5];
assign sig_241 = sig_163 ^ sig_208;
assign sig_242 = sig_163 & A[5];
assign sig_251 = B[5] & A[6];
assign sig_252 = B[6] & A[6];
assign sig_253 = B[7] & A[6];
assign sig_260 = sig_252 & sig_241;
assign sig_272 = A[5] & B[6];
assign sig_281 = sig_241 ^ sig_252;
assign sig_283 = sig_281 & sig_251;
assign sig_284 = sig_281 ^ sig_251;
assign sig_285 = sig_260 | sig_283;
assign sig_286 = sig_242 ^ sig_253;
assign sig_287 = sig_242 & sig_253;
assign sig_288 = sig_253 & sig_285;
assign sig_289 = sig_286 ^ sig_285;
assign sig_290 = sig_287 | sig_288;
assign sig_295 = B[4] & A[7];
assign sig_296 = B[5] & A[7];
assign sig_297 = B[6] & A[7];
assign sig_298 = B[7] & A[7];
assign sig_312 = A[7] & B[3];
assign sig_313 = B[4] & A[3];
assign sig_315 = sig_312 | sig_313;
assign sig_316 = sig_272 ^ sig_295;
assign sig_317 = sig_272 & sig_295;
assign sig_318 = sig_316 & sig_315;
assign sig_319 = sig_316 ^ sig_315;
assign sig_320 = sig_317 | sig_318;
assign sig_321 = sig_284 ^ sig_296;
assign sig_322 = sig_284 & sig_296;
assign sig_323 = sig_321 & sig_320;
assign sig_324 = sig_321 ^ sig_320;
assign sig_325 = sig_322 | sig_323;
assign sig_326 = sig_289 ^ sig_297;
assign sig_327 = sig_289 & sig_297;
assign sig_328 = sig_326 & sig_325;
assign sig_329 = sig_326 ^ sig_325;
assign sig_330 = sig_327 | sig_328;
assign sig_331 = sig_290 ^ sig_298;
assign sig_332 = sig_290 & A[7];
assign sig_333 = B[7] & sig_330;
assign sig_334 = sig_331 ^ sig_330;
assign sig_335 = sig_332 | sig_333;

assign O[15] = sig_335;
assign O[14] = sig_334;
assign O[13] = sig_329;
assign O[12] = sig_324;
assign O[11] = sig_319;
assign O[10] = sig_272;
assign O[9] = sig_298;
assign O[8] = sig_295;
assign O[7] = sig_331;
assign O[6] = 1'b0;
assign O[5] = sig_298;
assign O[4] = 1'b0;
assign O[3] = sig_288;
assign O[2] = sig_331;
assign O[1] = sig_287;
assign O[0] = 1'b0;

endmodule


module mult8_cgp14_wc3_csamcsa (
    A,
    B,
    O
);

input [7:0] A;
input [7:0] B;
output [15:0] O;

wire sig_18,sig_19,sig_20,sig_21,sig_22,sig_23,sig_25,sig_26,sig_27,sig_28,sig_29,sig_30,sig_31,sig_32,sig_34,sig_35,sig_36,sig_37,sig_38,sig_39;
wire sig_40,sig_41,sig_42,sig_43,sig_44,sig_45,sig_46,sig_47,sig_48,sig_49,sig_50,sig_51,sig_52,sig_53,sig_54,sig_55,sig_59,sig_60,sig_61,sig_62;
wire sig_63,sig_64,sig_65,sig_66,sig_67,sig_68,sig_69,sig_70,sig_71,sig_72,sig_73,sig_74,sig_75,sig_76,sig_77,sig_78,sig_79,sig_80,sig_81,sig_82;
wire sig_83,sig_84,sig_85,sig_87,sig_88,sig_89,sig_90,sig_91,sig_92,sig_93,sig_94,sig_95,sig_96,sig_97,sig_98,sig_99,sig_100,sig_101,sig_102,sig_103;
wire sig_104,sig_105,sig_106,sig_107,sig_108,sig_109,sig_110,sig_111,sig_112,sig_113,sig_114,sig_115,sig_116,sig_117,sig_118,sig_119,sig_120,sig_121,sig_122,sig_123;
wire sig_124,sig_125,sig_126,sig_127,sig_128,sig_129,sig_130,sig_131,sig_132,sig_133,sig_134,sig_135,sig_136,sig_137,sig_138,sig_139,sig_140,sig_141,sig_142,sig_143;
wire sig_144,sig_145,sig_146,sig_147,sig_148,sig_149,sig_150,sig_151,sig_152,sig_153,sig_154,sig_155,sig_156,sig_157,sig_158,sig_159,sig_160,sig_161,sig_162,sig_163;
wire sig_164,sig_165,sig_166,sig_167,sig_168,sig_169,sig_170,sig_171,sig_172,sig_173,sig_174,sig_175,sig_176,sig_177,sig_178,sig_179,sig_180,sig_181,sig_182,sig_183;
wire sig_184,sig_185,sig_186,sig_187,sig_188,sig_189,sig_190,sig_191,sig_192,sig_193,sig_194,sig_195,sig_196,sig_197,sig_198,sig_199,sig_200,sig_201,sig_202,sig_203;
wire sig_204,sig_205,sig_206,sig_207,sig_208,sig_209,sig_210,sig_211,sig_212,sig_213,sig_214,sig_215,sig_216,sig_217,sig_218,sig_219,sig_220,sig_221,sig_222,sig_223;
wire sig_224,sig_225,sig_226,sig_227,sig_228,sig_229,sig_230,sig_231,sig_232,sig_233,sig_234,sig_235,sig_236,sig_237,sig_238,sig_239,sig_240,sig_241,sig_242,sig_243;
wire sig_244,sig_245,sig_246,sig_247,sig_248,sig_249,sig_250,sig_251,sig_252,sig_253,sig_254,sig_255,sig_256,sig_257,sig_258,sig_259,sig_260,sig_261,sig_262,sig_263;
wire sig_264,sig_265,sig_266,sig_267,sig_268,sig_269,sig_270,sig_271,sig_272,sig_273,sig_274,sig_275,sig_276,sig_277,sig_278,sig_279,sig_280,sig_281,sig_282,sig_283;
wire sig_284,sig_285,sig_286,sig_287,sig_288,sig_289,sig_290,sig_291,sig_292,sig_293,sig_294,sig_295,sig_296,sig_297,sig_298,sig_299,sig_300,sig_301,sig_302,sig_303;
wire sig_304,sig_305,sig_306,sig_307,sig_308,sig_309,sig_310,sig_311,sig_312,sig_313,sig_314,sig_315,sig_316,sig_317,sig_318,sig_319,sig_320,sig_321,sig_322,sig_323;
wire sig_324,sig_325,sig_326,sig_327,sig_328,sig_329,sig_330,sig_331,sig_332,sig_333,sig_335,sig_336,sig_338,sig_339,sig_340,sig_341,sig_344,sig_345,sig_348,sig_349;
wire sig_350,sig_352,sig_353,sig_354,sig_355,sig_356,sig_357,sig_358,sig_361,sig_362;

assign sig_18 = B[2] & A[0];
assign sig_19 = B[3] & A[0];
assign sig_20 = B[4] & A[0];
assign sig_21 = B[5] & A[0];
assign sig_22 = B[6] & sig_21;
assign sig_23 = B[7] & A[0];
assign sig_25 = B[1] & A[1];
assign sig_26 = B[2] & A[1];
assign sig_27 = B[3] & A[1];
assign sig_28 = B[4] & A[1];
assign sig_29 = B[5] & A[1];
assign sig_30 = B[6] & A[1];
assign sig_31 = B[7] & A[1];
assign sig_32 = A[0] & B[6];
assign sig_34 = sig_18 ^ sig_25;
assign sig_35 = sig_18 & sig_25;
assign sig_36 = sig_19 ^ sig_26;
assign sig_37 = sig_19 & sig_26;
assign sig_38 = sig_20 ^ sig_27;
assign sig_39 = sig_20 & sig_27;
assign sig_40 = sig_21 ^ sig_28;
assign sig_41 = sig_21 & sig_28;
assign sig_42 = sig_32 ^ sig_29;
assign sig_43 = sig_22 & A[1];
assign sig_44 = sig_23 ^ sig_30;
assign sig_45 = sig_31 & sig_32;
assign sig_46 = B[0] & A[2];
assign sig_47 = B[1] & A[2];
assign sig_48 = B[2] & A[2];
assign sig_49 = B[3] & A[2];
assign sig_50 = B[4] & A[2];
assign sig_51 = B[5] & A[2];
assign sig_52 = B[6] & A[2];
assign sig_53 = B[7] & A[2];
assign sig_54 = sig_34 ^ sig_46;
assign sig_55 = sig_34 & sig_46;
assign sig_59 = sig_36 ^ sig_47;
assign sig_60 = sig_36 & sig_47;
assign sig_61 = sig_59 & sig_35;
assign sig_62 = sig_59 ^ sig_35;
assign sig_63 = sig_60 | sig_61;
assign sig_64 = sig_38 ^ sig_48;
assign sig_65 = sig_38 & sig_48;
assign sig_66 = sig_64 & sig_37;
assign sig_67 = sig_64 ^ sig_37;
assign sig_68 = sig_65 | sig_66;
assign sig_69 = sig_40 ^ sig_49;
assign sig_70 = sig_40 & sig_49;
assign sig_71 = sig_69 & sig_39;
assign sig_72 = sig_69 ^ sig_39;
assign sig_73 = sig_70 | sig_71;
assign sig_74 = sig_42 ^ sig_50;
assign sig_75 = sig_42 & sig_50;
assign sig_76 = sig_74 & sig_41;
assign sig_77 = sig_74 ^ sig_41;
assign sig_78 = sig_75 | sig_76;
assign sig_79 = sig_44 ^ sig_51;
assign sig_80 = sig_44 & sig_51;
assign sig_81 = sig_79 & sig_43;
assign sig_82 = sig_79 ^ sig_43;
assign sig_83 = sig_80 | sig_81;
assign sig_84 = sig_31 ^ sig_52;
assign sig_85 = sig_31 & sig_52;
assign sig_87 = sig_84 ^ sig_45;
assign sig_88 = sig_85 | sig_45;
assign sig_89 = B[0] & A[3];
assign sig_90 = B[1] & A[3];
assign sig_91 = B[2] & A[3];
assign sig_92 = B[3] & A[3];
assign sig_93 = B[4] & A[3];
assign sig_94 = B[5] & A[3];
assign sig_95 = B[6] & A[3];
assign sig_96 = B[7] & A[3];
assign sig_97 = sig_62 ^ sig_89;
assign sig_98 = sig_62 & sig_89;
assign sig_99 = sig_97 & sig_55;
assign sig_100 = sig_97 ^ sig_55;
assign sig_101 = sig_98 | sig_99;
assign sig_102 = sig_67 ^ sig_90;
assign sig_103 = sig_67 & sig_90;
assign sig_104 = sig_102 & sig_63;
assign sig_105 = sig_102 ^ sig_63;
assign sig_106 = sig_103 | sig_104;
assign sig_107 = sig_72 ^ sig_91;
assign sig_108 = sig_72 & sig_91;
assign sig_109 = sig_107 & sig_68;
assign sig_110 = sig_107 ^ sig_68;
assign sig_111 = sig_108 | sig_109;
assign sig_112 = sig_77 ^ sig_92;
assign sig_113 = sig_77 & sig_92;
assign sig_114 = sig_112 & sig_73;
assign sig_115 = sig_112 ^ sig_73;
assign sig_116 = sig_113 | sig_114;
assign sig_117 = sig_82 ^ sig_93;
assign sig_118 = sig_82 & sig_93;
assign sig_119 = sig_117 & sig_78;
assign sig_120 = sig_117 ^ sig_78;
assign sig_121 = sig_118 | sig_119;
assign sig_122 = sig_87 ^ sig_94;
assign sig_123 = sig_87 & sig_94;
assign sig_124 = sig_122 & sig_83;
assign sig_125 = sig_122 ^ sig_83;
assign sig_126 = sig_123 | sig_124;
assign sig_127 = sig_53 ^ sig_95;
assign sig_128 = sig_53 & sig_95;
assign sig_129 = sig_127 & sig_88;
assign sig_130 = sig_127 ^ sig_88;
assign sig_131 = sig_128 | sig_129;
assign sig_132 = B[0] & A[4];
assign sig_133 = B[1] & A[4];
assign sig_134 = B[2] & A[4];
assign sig_135 = B[3] & A[4];
assign sig_136 = B[4] & A[4];
assign sig_137 = B[5] & A[4];
assign sig_138 = B[6] & A[4];
assign sig_139 = B[7] & A[4];
assign sig_140 = sig_105 ^ sig_132;
assign sig_141 = sig_105 & sig_132;
assign sig_142 = sig_140 & sig_101;
assign sig_143 = sig_140 ^ sig_101;
assign sig_144 = sig_141 | sig_142;
assign sig_145 = sig_110 ^ sig_133;
assign sig_146 = sig_110 & sig_133;
assign sig_147 = sig_145 & sig_106;
assign sig_148 = sig_145 ^ sig_106;
assign sig_149 = sig_146 | sig_147;
assign sig_150 = sig_115 ^ sig_134;
assign sig_151 = sig_115 & sig_134;
assign sig_152 = sig_150 & sig_111;
assign sig_153 = sig_150 ^ sig_111;
assign sig_154 = sig_151 | sig_152;
assign sig_155 = sig_120 ^ sig_135;
assign sig_156 = sig_120 & sig_135;
assign sig_157 = sig_155 & sig_116;
assign sig_158 = sig_155 ^ sig_116;
assign sig_159 = sig_156 | sig_157;
assign sig_160 = sig_125 ^ sig_136;
assign sig_161 = sig_125 & sig_136;
assign sig_162 = sig_160 & sig_121;
assign sig_163 = sig_160 ^ sig_121;
assign sig_164 = sig_161 | sig_162;
assign sig_165 = sig_130 ^ sig_137;
assign sig_166 = sig_130 & sig_137;
assign sig_167 = sig_165 & sig_126;
assign sig_168 = sig_165 ^ sig_126;
assign sig_169 = sig_166 | sig_167;
assign sig_170 = sig_96 ^ sig_138;
assign sig_171 = sig_96 & sig_138;
assign sig_172 = sig_170 & sig_131;
assign sig_173 = sig_170 ^ sig_131;
assign sig_174 = sig_171 | sig_172;
assign sig_175 = B[0] & A[5];
assign sig_176 = B[1] & A[5];
assign sig_177 = B[2] & A[5];
assign sig_178 = B[3] & A[5];
assign sig_179 = B[4] & A[5];
assign sig_180 = B[5] & A[5];
assign sig_181 = B[6] & A[5];
assign sig_182 = B[7] & A[5];
assign sig_183 = sig_148 ^ sig_175;
assign sig_184 = sig_148 & sig_175;
assign sig_185 = sig_183 & sig_144;
assign sig_186 = sig_183 ^ sig_144;
assign sig_187 = sig_184 | sig_185;
assign sig_188 = sig_153 ^ sig_176;
assign sig_189 = sig_153 & sig_176;
assign sig_190 = sig_188 & sig_149;
assign sig_191 = sig_188 ^ sig_149;
assign sig_192 = sig_189 | sig_190;
assign sig_193 = sig_158 ^ sig_177;
assign sig_194 = sig_158 & sig_177;
assign sig_195 = sig_193 & sig_154;
assign sig_196 = sig_193 ^ sig_154;
assign sig_197 = sig_194 | sig_195;
assign sig_198 = sig_163 ^ sig_178;
assign sig_199 = sig_163 & sig_178;
assign sig_200 = sig_198 & sig_159;
assign sig_201 = sig_198 ^ sig_159;
assign sig_202 = sig_199 | sig_200;
assign sig_203 = sig_168 ^ sig_179;
assign sig_204 = sig_168 & sig_179;
assign sig_205 = sig_203 & sig_164;
assign sig_206 = sig_203 ^ sig_164;
assign sig_207 = sig_204 | sig_205;
assign sig_208 = sig_173 ^ sig_180;
assign sig_209 = sig_173 & sig_180;
assign sig_210 = sig_208 & sig_169;
assign sig_211 = sig_208 ^ sig_169;
assign sig_212 = sig_209 | sig_210;
assign sig_213 = sig_139 ^ sig_181;
assign sig_214 = sig_139 & sig_181;
assign sig_215 = sig_213 & sig_174;
assign sig_216 = sig_213 ^ sig_174;
assign sig_217 = sig_214 | sig_215;
assign sig_218 = B[0] & A[6];
assign sig_219 = B[1] & A[6];
assign sig_220 = B[2] & A[6];
assign sig_221 = B[3] & A[6];
assign sig_222 = B[4] & A[6];
assign sig_223 = B[5] & A[6];
assign sig_224 = B[6] & A[6];
assign sig_225 = B[7] & A[6];
assign sig_226 = sig_191 ^ sig_218;
assign sig_227 = sig_191 & sig_218;
assign sig_228 = sig_226 & sig_187;
assign sig_229 = sig_226 ^ sig_187;
assign sig_230 = sig_227 | sig_228;
assign sig_231 = sig_196 ^ sig_219;
assign sig_232 = sig_196 & sig_219;
assign sig_233 = sig_231 & sig_192;
assign sig_234 = sig_231 ^ sig_192;
assign sig_235 = sig_232 | sig_233;
assign sig_236 = sig_201 ^ sig_220;
assign sig_237 = sig_201 & sig_220;
assign sig_238 = sig_236 & sig_197;
assign sig_239 = sig_236 ^ sig_197;
assign sig_240 = sig_237 | sig_238;
assign sig_241 = sig_206 ^ sig_221;
assign sig_242 = sig_206 & sig_221;
assign sig_243 = sig_241 & sig_202;
assign sig_244 = sig_241 ^ sig_202;
assign sig_245 = sig_242 | sig_243;
assign sig_246 = sig_211 ^ sig_222;
assign sig_247 = sig_211 & sig_222;
assign sig_248 = sig_246 & sig_207;
assign sig_249 = sig_246 ^ sig_207;
assign sig_250 = sig_247 | sig_248;
assign sig_251 = sig_216 ^ sig_223;
assign sig_252 = sig_216 & sig_223;
assign sig_253 = sig_251 & sig_212;
assign sig_254 = sig_251 ^ sig_212;
assign sig_255 = sig_252 | sig_253;
assign sig_256 = sig_182 ^ sig_224;
assign sig_257 = sig_182 & sig_224;
assign sig_258 = sig_256 & sig_217;
assign sig_259 = sig_256 ^ sig_217;
assign sig_260 = sig_257 | sig_258;
assign sig_261 = B[0] & A[7];
assign sig_262 = B[1] & A[7];
assign sig_263 = B[2] & A[7];
assign sig_264 = B[3] & A[7];
assign sig_265 = B[4] & A[7];
assign sig_266 = B[5] & A[7];
assign sig_267 = B[6] & A[7];
assign sig_268 = B[7] & A[7];
assign sig_269 = sig_234 ^ sig_261;
assign sig_270 = sig_234 & sig_261;
assign sig_271 = sig_269 & sig_230;
assign sig_272 = sig_269 ^ sig_230;
assign sig_273 = sig_270 | sig_271;
assign sig_274 = sig_239 ^ sig_262;
assign sig_275 = sig_239 & sig_262;
assign sig_276 = sig_274 & sig_235;
assign sig_277 = sig_274 ^ sig_235;
assign sig_278 = sig_275 | sig_276;
assign sig_279 = sig_244 ^ sig_263;
assign sig_280 = sig_244 & sig_263;
assign sig_281 = sig_279 & sig_240;
assign sig_282 = sig_279 ^ sig_240;
assign sig_283 = sig_280 | sig_281;
assign sig_284 = sig_249 ^ sig_264;
assign sig_285 = sig_249 & sig_264;
assign sig_286 = sig_284 & sig_245;
assign sig_287 = sig_284 ^ sig_245;
assign sig_288 = sig_285 | sig_286;
assign sig_289 = sig_254 ^ sig_265;
assign sig_290 = sig_254 & sig_265;
assign sig_291 = sig_289 & sig_250;
assign sig_292 = sig_289 ^ sig_250;
assign sig_293 = sig_290 | sig_291;
assign sig_294 = sig_259 ^ sig_266;
assign sig_295 = sig_259 & sig_266;
assign sig_296 = sig_294 & sig_255;
assign sig_297 = sig_294 ^ sig_255;
assign sig_298 = sig_295 | sig_296;
assign sig_299 = sig_225 ^ sig_267;
assign sig_300 = sig_225 & sig_267;
assign sig_301 = sig_299 & sig_260;
assign sig_302 = sig_299 ^ sig_260;
assign sig_303 = sig_300 | sig_301;
assign sig_304 = sig_277 ^ sig_273;
assign sig_305 = sig_277 & sig_273;
assign sig_306 = sig_282 ^ sig_278;
assign sig_307 = sig_282 & sig_278;
assign sig_308 = sig_306 & sig_305;
assign sig_309 = sig_306 ^ sig_305;
assign sig_310 = sig_307 | sig_308;
assign sig_311 = sig_287 ^ sig_283;
assign sig_312 = sig_287 & sig_283;
assign sig_313 = sig_311 & sig_310;
assign sig_314 = sig_311 ^ sig_310;
assign sig_315 = sig_312 | sig_313;
assign sig_316 = sig_292 ^ sig_288;
assign sig_317 = sig_292 & sig_288;
assign sig_318 = sig_316 & sig_315;
assign sig_319 = sig_316 ^ sig_315;
assign sig_320 = sig_317 | sig_318;
assign sig_321 = ~sig_320;
assign sig_322 = sig_297 & sig_293;
assign sig_323 = sig_302 ^ sig_298;
assign sig_324 = sig_302 & sig_298;
assign sig_325 = sig_323 & sig_322;
assign sig_326 = sig_323 ^ sig_322;
assign sig_327 = sig_324 | sig_325;
assign sig_328 = sig_268 ^ sig_303;
assign sig_329 = A[7] & sig_303;
assign sig_330 = sig_328 & sig_327;
assign sig_331 = sig_328 ^ sig_327;
assign sig_332 = sig_329 | sig_330;
assign sig_333 = sig_297 ^ sig_293;
assign sig_335 = ~sig_333;
assign sig_336 = sig_322 | sig_333;
assign sig_338 = ~sig_320;
assign sig_339 = sig_323 & sig_336;
assign sig_340 = sig_323 ^ sig_336;
assign sig_341 = sig_324 | sig_339;
assign sig_344 = sig_328 & sig_341;
assign sig_345 = sig_328 ^ sig_341;
assign sig_348 = sig_333 & sig_338;
assign sig_349 = sig_335 & sig_320;
assign sig_350 = sig_348 | sig_349;
assign sig_352 = sig_326 & sig_321;
assign sig_353 = sig_340 & sig_320;
assign sig_354 = sig_352 | sig_353;
assign sig_355 = ~sig_320;
assign sig_356 = sig_331 & sig_355;
assign sig_357 = sig_345 & sig_320;
assign sig_358 = sig_356 | sig_357;
assign sig_361 = sig_344 & sig_320;
assign sig_362 = sig_332 | sig_361;

assign O[15] = sig_362;
assign O[14] = sig_358;
assign O[13] = sig_354;
assign O[12] = sig_350;
assign O[11] = sig_319;
assign O[10] = sig_314;
assign O[9] = sig_309;
assign O[8] = sig_304;
assign O[7] = sig_272;
assign O[6] = sig_229;
assign O[5] = sig_186;
assign O[4] = sig_143;
assign O[3] = sig_100;
assign O[2] = sig_54;
assign O[1] = sig_25;
assign O[0] = sig_265;

endmodule



module CLA32bit(a,b,c_in,sum,c_out);

input [31:0]a,b;
input c_in;
output [31:0]sum;
output c_out;

wire [31:0] sum_out,  p,  g;
wire [7:0] PPP, GGG;
wire [8:0] CC;

assign p[31:0] = a[31:0] ^ b[31:0];
assign g[31:0] = a[31:0] & b[31:0];

assign PPP[0]= p [3] & p [2] & p [1] & p [0];
assign PPP[1]= p [7] & p [6] & p [5] & p [4];
assign PPP[2]= p[11] & p[10] & p [9] & p [8];
assign PPP[3]= p[15] & p[14] & p[13] & p[12];
assign PPP[4]= p[19] & p[18] & p[17] & p[16];
assign PPP[5]= p[23] & p[22] & p[21] & p[20];
assign PPP[6]= p[27] & p[26] & p[25] & p[24];
assign PPP[7]= p[31] & p[30] & p[29] & p[28];

assign GGG[0]= g[3]  | (p [3] & g [2])  | (p [3] & p [2] & g [1])  | (p [3] & p [2] & p [1] & g [0]) ;
assign GGG[1]= g[7]  | (p [7] & g [6])  | (p [7] & p [6] & g [5])  | (p [7] & p [6] & p [5] & g [4]);
assign GGG[2]= g[11] | (p[11] & g[10])  | (p[11] & p[10] & g [9])  | (p[11] & p[10] & p [9] & g [8]);
assign GGG[3]= g[15] | (p[15] & g[14])  | (p[15] & p[14] & g[13])  | (p[15] & p[14] & p[13] & g[12]);
assign GGG[4]= g[19] | (p[19] & g[18])  | (p[19] & p[18] & g[17])  | (p[19] & p[18] & p[17] & g[16]);
assign GGG[5]= g[23] | (p[23] & g[22])  | (p[23] & p[22] & g[21])  | (p[23] & p[22] & p[21] & g[20]);
assign GGG[6]= g[27] | (p[27] & g[26])  | (p[27] & p[26] & g[25])  | (p[27] & p[26] & p[25] & g[24]);
assign GGG[7]= g[31] | (p[31] & g[30])  | (p[31] & p[30] & g[29])  | (p[31] & p[30] & p[29] & g[28]);
assign CC[0] = c_in;
assign CC[1] = GGG[0]  |  PPP[0]&  CC[0];
assign CC[2] = GGG[1]  |  PPP[1]&GGG[0]  |  PPP[1]&PPP[0]&  CC[0];
assign CC[3] = GGG[2]  |  PPP[2]&GGG[1]  |  PPP[2]&PPP[1]&GGG[0]  |  PPP[2]&PPP[1]&PPP[0]&  CC[0];
assign CC[4] = GGG[3]  |  PPP[3]&GGG[2]  |  PPP[3]&PPP[2]&GGG[1]  |  PPP[3]&PPP[2]&PPP[1]&GGG[0]  |  PPP[3]&PPP[2]&PPP[1]&PPP[0]&  CC[0];
assign CC[5] = GGG[4]  |  PPP[4]&GGG[3]  |  PPP[4]&PPP[3]&GGG[2]  |  PPP[4]&PPP[3]&PPP[2]&GGG[1]  |  PPP[4]&PPP[3]&PPP[2]&PPP[1]&GGG[0] |  PPP[4]&PPP[3]&PPP[2]&PPP[1]&PPP[0]&  CC[0];
assign CC[6] = GGG[5]  |  PPP[5]&GGG[4]  |  PPP[5]&PPP[4]&GGG[3]  |  PPP[5]&PPP[4]&PPP[3]&GGG[2]  |  PPP[5]&PPP[4]&PPP[3]&PPP[2]&GGG[1] |  PPP[5]&PPP[4]&PPP[3]&PPP[2]&PPP[1]&GGG[0] |  PPP[5]&PPP[4]&PPP[3]&PPP[2]&PPP[1]&PPP[0]& CC[0];
assign CC[7] = GGG[6]  | PPP[6]&GGG[5]  |  PPP[6]&PPP[5]&GGG[4]  |  PPP[6]&PPP[5]&PPP[4]&GGG[3]  |  PPP[6]&PPP[5]&PPP[4]&PPP[3]&GGG[2]  |  PPP[6]&PPP[5]&PPP[4]&PPP[3]&PPP[2]&GGG[1] |  PPP[6]&PPP[5]&PPP[4]&PPP[3]&PPP[2]&PPP[1]&GGG[0] |  PPP[6]&PPP[5]&PPP[4]&PPP[3]&PPP[2]&PPP[1]&PPP[0] & CC[0];
assign CC[8] = GGG[7] | PPP[7]&GGG[6]  | PPP[7]&PPP[6]&GGG[5]  |  PPP[7]&PPP[6]&PPP[5]&GGG[4]  |  PPP[7]&PPP[6]&PPP[5]&PPP[4]&GGG[3]  |  PPP[7]&PPP[6]&PPP[5]&PPP[4]&PPP[3]&GGG[2]  |  PPP[7]&PPP[6]&PPP[5]&PPP[4]&PPP[3]&PPP[2]&GGG[1] |  PPP[7]&PPP[6]&PPP[5]&PPP[4]&PPP[3]&PPP[2]&PPP[1]&GGG[0] |  PPP[7]&PPP[6]&PPP[5]&PPP[4]&PPP[3]&PPP[2]&PPP[1]&PPP[0] & CC[0];
cla_4bit cla4bit1(.aa(a  [3:0]),  .bb(b  [3:0]),  .cin(CC[0]),   .pp(p  [3:0]),  .gg(g  [3:0]),   .summ(sum  [3:0]));
cla_4bit cla4bit2(.aa(a  [7:4]),  .bb(b  [7:4]),  .cin(CC[1]),   .pp(p  [7:4]),  .gg(g  [7:4]),   .summ(sum  [7:4]));
cla_4bit cla4bit3(.aa(a [11:8]),  .bb(b [11:8]),  .cin(CC[2]),   .pp(p [11:8]),  .gg(g [11:8]),   .summ(sum [11:8]));
cla_4bit cla4bit4(.aa(a[15:12]),  .bb(b[15:12]),  .cin(CC[3]),   .pp(p[15:12]),  .gg(g[15:12]),   .summ(sum[15:12]));
cla_4bit cla4bit5(.aa(a[19:16]),  .bb(b[19:16]),  .cin(CC[4]),   .pp(p[19:16]),  .gg(g[19:16]),   .summ(sum[19:16]));
cla_4bit cla4bit6(.aa(a[23:20]),  .bb(b[23:20]),  .cin(CC[5]),   .pp(p[23:20]),  .gg(g[23:20]),   .summ(sum[23:20]));
cla_4bit cla4bit7(.aa(a[27:24]),  .bb(b[27:24]),  .cin(CC[6]),   .pp(p[27:24]),  .gg(g[27:24]),   .summ(sum[27:24]));
cla_4bit cla4bit8(.aa(a[31:28]),  .bb(b[31:28]),  .cin(CC[7]),   .pp(p[31:28]),  .gg(g[31:28]),   .summ(sum[31:28]));

assign c_out=CC[8];

endmodule


// -----------------------------Multipliers--------------------------

module mul16u_8VH ( input [63:0] A,
                   input [63:0] B,
                   output [63:0] Out
                 );
wire res_sign;
wire [63:0] tmp,a_signless,b_signless;

assign res_sign = A[15] ^ B[15];
assign a_signless = {49'b0,A[14:0]};
assign b_signless = {49'b0,B[14:0]};

wire[63:0] O;
wire [15:0] ll,lh,hl,hh;
wire [31:0] llhhlh_sum;
wire [31:0] shifted_llhh, shifted_lh, shifted_hl;

localparam MAX1 = 15;
localparam MIN1 = 8;

localparam MAX2 = 7;
localparam MIN2 = 0;

mult8_cgp14ep_ep65536_wc16384_2_csamcsa LxL (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX2:MIN2]), .O(ll));
mult8_cgp14ep_ep65536_wc4545_rcam HxL (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX2:MIN2]), .O(hl));
mult8_cgp14ep_ep65536_wc4545_rcam LxH (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX1:MIN1]), .O(lh));
mult8_cgp14_wc3_csamcsa HxH (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX1:MIN1]), .O(hh));

assign shifted_llhh = { hh, ll }; 
assign shifted_lh = { {8{1'b0}}, lh, {8{1'b0}}}; 
assign shifted_hl = { {8{1'b0}}, hl, {8{1'b0}}};
CLA32bit LLHHLH (.a(shifted_llhh), .b(shifted_lh), .c_in(1'b0), .sum(llhhlh_sum), .c_out());
CLA32bit SUMO (.a(llhhlh_sum), .b(shifted_hl), .c_in(1'b0), .sum(O[31:0]), .c_out());

assign Out={48'b0,res_sign,O[19:10],O[9:5]};
endmodule


module mul16u_CK3 ( input [63:0] A,
                   input [63:0] B,
                   output [63:0] Out
                 );
wire [63:0] O;
wire [15:0] ll,lh,hl,hh;
wire [31:0] llhhlh_sum;
wire [31:0] shifted_llhh, shifted_lh, shifted_hl;
wire res_sign;
wire [63:0] tmp,a_signless,b_signless;

assign res_sign = A[15] ^ B[15];
assign a_signless = {49'b0,A[14:0]};
assign b_signless = {49'b0,B[14:0]};

localparam MAX1 = 15;
localparam MIN1 = 8;

localparam MAX2 = 7;
localparam MIN2 = 0;

mult8_cgp14ep_ep65536_wc16384_2_csamcsa LxL (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX2:MIN2]), .O(ll));
mult8_cgp14ep_ep63897_wc377_rcam HxL (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX2:MIN2]), .O(hl));
mult8_cgp14ep_ep63897_wc377_rcam LxH (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX1:MIN1]), .O(lh));
mul8_364 HxH (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX1:MIN1]), .O(hh));

assign shifted_llhh = { hh, ll }; 
assign shifted_lh = { {8{1'b0}}, lh, {8{1'b0}}}; 
assign shifted_hl = { {8{1'b0}}, hl, {8{1'b0}}};
CLA32bit LLHHLH (.a(shifted_llhh), .b(shifted_lh), .c_in(1'b0), .sum(llhhlh_sum), .c_out());
CLA32bit SUMO (.a(llhhlh_sum), .b(shifted_hl), .c_in(1'b0), .sum(O[31:0]), .c_out());

assign Out={48'b0,res_sign,O[19:10],O[9:5]};
endmodule


module mul16u_F6B ( input [63:0] A,
                   input [63:0] B,
                   output [63:0] Out
                 );
wire [63:0] O;
wire [15:0] ll,lh,hl,hh;
wire [31:0] llhhlh_sum;
wire [31:0] shifted_llhh, shifted_lh, shifted_hl;

wire res_sign;
wire [63:0] tmp,a_signless,b_signless;

assign res_sign = A[15] ^ B[15];
assign a_signless = {49'b0,A[14:0]};
assign b_signless = {49'b0,B[14:0]};

localparam MAX1 = 15;
localparam MIN1 = 8;

localparam MAX2 = 7;
localparam MIN2 = 0;

mult8_cgp14zr_wc7391_rcam LxL (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX2:MIN2]), .O(ll));
mult8_cgp14ep_ep64716_wc26_csamrca HxL (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX2:MIN2]), .O(hl));
mult8_cgp14ep_ep64716_wc26_csamrca LxH (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX1:MIN1]), .O(lh));
mul8_364 HxH (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX1:MIN1]), .O(hh));

assign shifted_llhh = { hh, ll }; 
assign shifted_lh = { {8{1'b0}}, lh, {8{1'b0}}}; 
assign shifted_hl = { {8{1'b0}}, hl, {8{1'b0}}};
CLA32bit LLHHLH (.a(shifted_llhh), .b(shifted_lh), .c_in(1'b0), .sum(llhhlh_sum), .c_out());
CLA32bit SUMO (.a(llhhlh_sum), .b(shifted_hl), .c_in(1'b0), .sum(O[31:0]), .c_out());

assign Out={48'b0,res_sign,O[19:10],O[9:5]};
endmodule


module mul16u_DAE ( input [63:0] A,
                   input [63:0] B,
                   output [63:0] Out
                 );
wire [63:0] O;
wire [15:0] ll,lh,hl,hh;
wire [31:0] llhhlh_sum;
wire [31:0] shifted_llhh, shifted_lh, shifted_hl;
wire res_sign;
wire[63:0] tmp,a_signless,b_signless;

assign res_sign = A[15] ^ B[15];
assign a_signless = {49'b0,A[14:0]};
assign b_signless = {49'b0,B[14:0]};

localparam MAX1 = 15;
localparam MIN1 = 8;

localparam MAX2 = 7;
localparam MIN2 = 0;

mult8_cgp14zr_wc907_rcam LxL (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX2:MIN2]), .O(ll));
mul8_364 HxL (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX2:MIN2]), .O(hl));
trun8_tam00b LxH (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX1:MIN1]), .O(lh));
trun8_tam00b HxH (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX1:MIN1]), .O(hh));

assign shifted_llhh = { hh, ll }; 
assign shifted_lh = { {8{1'b0}}, lh, {8{1'b0}}}; 
assign shifted_hl = { {8{1'b0}}, hl, {8{1'b0}}};
CLA32bit LLHHLH (.a(shifted_llhh), .b(shifted_lh), .c_in(1'b0), .sum(llhhlh_sum), .c_out());
CLA32bit SUMO (.a(llhhlh_sum), .b(shifted_hl), .c_in(1'b0), .sum(O[31:0]), .c_out());

assign Out={48'b0,res_sign,O[19:10],O[9:5]};
endmodule


module mul16u_5FA ( input [63:0] A,
                   input [63:0] B,
                   output [63:0] Out
                 );
wire [63:0] O;
wire [15:0] ll,lh,hl,hh;
wire [31:0] llhhlh_sum;
wire [31:0] shifted_llhh, shifted_lh, shifted_hl;

wire res_sign;
wire [63:0] tmp,a_signless,b_signless;
assign res_sign = A[15] ^ B[15];
assign a_signless = {49'b0,A[14:0]};
assign b_signless = {49'b0,B[14:0]};

localparam MAX1 = 15;
localparam MIN1 = 8;

localparam MAX2 = 7;
localparam MIN2 = 0;

mult8_cgp14_wc79_csamrca LxL (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX2:MIN2]), .O(ll));
mul8_364 HxL (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX2:MIN2]), .O(hl));
trun8_tam00b LxH (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX1:MIN1]), .O(lh));
trun8_tam00b HxH (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX1:MIN1]), .O(hh));

assign shifted_llhh = { hh, ll }; 
assign shifted_lh = { {8{1'b0}}, lh, {8{1'b0}}}; 
assign shifted_hl = { {8{1'b0}}, hl, {8{1'b0}}};
CLA32bit LLHHLH (.a(shifted_llhh), .b(shifted_lh), .c_in(1'b0), .sum(llhhlh_sum), .c_out());
CLA32bit SUMO (.a(llhhlh_sum), .b(shifted_hl), .c_in(1'b0), .sum(O[31:0]), .c_out());

assign Out={48'b0,res_sign,O[19:10],O[9:5]};
endmodule


module mul16u_AQ1 ( input[63:0] A,
                   input[63:0] B,
                   output [63:0] Out
                 );
wire[63:0] O;
wire [15:0] ll,lh,hl,hh;
wire [31:0] llhhlh_sum;
wire [31:0] shifted_llhh, shifted_lh, shifted_hl;

wire res_sign;
wire[63:0] tmp,a_signless,b_signless;
assign res_sign = A[15] ^ B[15];
assign a_signless = {49'b0,A[14:0]};
assign b_signless = {49'b0,B[14:0]};

localparam MAX1 = 15;
localparam MIN1 = 8;

localparam MAX2 = 7;
localparam MIN2 = 0;

mult8_cgp14ep_ep55705_wc4_csamrca LxL (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX2:MIN2]), .O(ll));
mul8_364 HxL (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX2:MIN2]), .O(hl));
mul8_364 LxH (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX1:MIN1]), .O(lh));
mul8_364 HxH (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX1:MIN1]), .O(hh));

assign shifted_llhh = { hh, ll }; 
assign shifted_lh = { {8{1'b0}}, lh, {8{1'b0}}}; 
assign shifted_hl = { {8{1'b0}}, hl, {8{1'b0}}};
CLA32bit LLHHLH (.a(shifted_llhh), .b(shifted_lh), .c_in(1'b0), .sum(llhhlh_sum), .c_out());

assign Out={48'b0,res_sign,O[19:10],O[9:5]};
endmodule


module mul16u_BMC ( input [63:0] A,
                   input [63:0] B,
                   output [63:0] Out
                 );
wire [63:0] O;
wire [15:0] ll,lh,hl,hh;
wire [31:0] llhhlh_sum;
wire [31:0] shifted_llhh, shifted_lh, shifted_hl;

wire res_sign;
wire[63:0] tmp,a_signless,b_signless;
assign res_sign = A[15] ^ B[15];
assign a_signless = {49'b0,A[14:0]};
assign b_signless = {49'b0,B[14:0]};

localparam MAX1 = 15;
localparam MIN1 = 8;

localparam MAX2 = 7;
localparam MIN2 = 0;

mul8_364 LxL (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX2:MIN2]), .O(ll));
trun8_tam00b HxL (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX2:MIN2]), .O(hl));
mul8_364 LxH (.A(a_signless[MAX2:MIN2]), .B(b_signless[MAX1:MIN1]), .O(lh));
mul8_364 HxH (.A(a_signless[MAX1:MIN1]), .B(b_signless[MAX1:MIN1]), .O(hh));

assign shifted_llhh = { hh, ll }; 
assign shifted_lh = { {8{1'b0}}, lh, {8{1'b0}}}; 
assign shifted_hl = { {8{1'b0}}, hl, {8{1'b0}}};
CLA32bit LLHHLH (.a(shifted_llhh), .b(shifted_lh), .c_in(1'b0), .sum(llhhlh_sum), .c_out());
CLA32bit SUMO (.a(llhhlh_sum), .b(shifted_hl), .c_in(1'b0), .sum(O[31:0]), .c_out());

assign Out={48'b0,res_sign,O[19:10],O[9:5]};
endmodule


module mul16u_HGY( A, B, Out );
input [63:0] A;
input [63:0] B;
wire [63:0] O;
output [63:0] Out;

wire [2*(16-15)-1:0] tmpZ;

wire res_sign;
wire[63:0] tmp,a_signless,b_signless;
assign res_sign = A[15] ^ B[15];
assign a_signless = {49'b0,A[14:0]};
assign b_signless = {49'b0,B[14:0]};

assign tmpZ = a_signless[16-1:15] * b_signless[16-1:15];
assign O = {tmpZ,{30{1'b0}}};

assign Out={48'b0,res_sign,O[19:10],O[9:5]};
endmodule


module mul16u_HGP ( A, B, Out );
  input [63:0] A;
  input [63:0] B;
  output [63:0] Out;
  wire [63:0] O;

  wire C_12_11,C_12_12,C_12_13,C_12_14,C_13_11,C_13_12,C_13_13,C_13_14,C_14_11,C_14_12,C_14_13,C_14_14,C_15_11,C_15_12,C_15_13,C_15_14,S_11_11,S_11_12,S_11_13,S_11_14,S_11_15,S_12_10,S_12_11,S_12_12,S_12_13,S_12_14,S_12_15,S_13_10,S_13_11,S_13_12,S_13_13,S_13_14,S_13_15,S_13_9,S_14_10,S_14_11,S_14_12,S_14_13,S_14_14,S_14_15,S_14_8,S_14_9,S_15_10,S_15_11,S_15_12,S_15_13,S_15_14,S_15_15,S_15_7,S_15_8,S_15_9,S_16_10,S_16_11,S_16_12,S_16_13,S_16_14,S_16_15,S_16_6,S_16_7,S_16_8,S_16_9;

  wire res_sign;
  wire[63:0] tmp,a_signless,b_signless;
  assign res_sign = A[15] ^ B[15];
  assign a_signless = {49'b0,A[14:0]};
  assign b_signless = {49'b0,B[14:0]};

  assign S_11_11 = (a_signless[11] & b_signless[11]);
  assign S_11_12 = (a_signless[11] & b_signless[12]);
  assign S_11_13 = (a_signless[11] & b_signless[13]);
  assign S_11_14 = (a_signless[11] & b_signless[14]);
  assign S_11_15 = (a_signless[11] & b_signless[15]);
  assign S_12_10 = S_11_11;
  PDKGENHAX1 U24214 (.A(S_11_12), .B((a_signless[12] & b_signless[11])), .YS(S_12_11), .YC(C_12_11));
  PDKGENHAX1 U24215 (.A(S_11_13), .B((a_signless[12] & b_signless[12])), .YS(S_12_12), .YC(C_12_12));
  PDKGENHAX1 U24216 (.A(S_11_14), .B((a_signless[12] & b_signless[13])), .YS(S_12_13), .YC(C_12_13));
  PDKGENHAX1 U24217 (.A(S_11_15), .B((a_signless[12] & b_signless[14])), .YS(S_12_14), .YC(C_12_14));
  assign S_12_15 = (a_signless[12] & b_signless[15]);
  assign S_13_9 = S_12_10;
  assign S_13_10 = S_12_11;
  PDKGENFAX1 U24230 (.A(S_12_12), .B(C_12_11), .C((a_signless[13] & b_signless[11])), .YS(S_13_11), .YC(C_13_11));
  PDKGENFAX1 U24231 (.A(S_12_13), .B(C_12_12), .C((a_signless[13] & b_signless[12])), .YS(S_13_12), .YC(C_13_12));
  PDKGENFAX1 U24232 (.A(S_12_14), .B(C_12_13), .C((a_signless[13] & b_signless[13])), .YS(S_13_13), .YC(C_13_13));
  PDKGENFAX1 U24233 (.A(S_12_15), .B(C_12_14), .C((a_signless[13] & b_signless[14])), .YS(S_13_14), .YC(C_13_14));
  assign S_13_15 = (a_signless[13] & b_signless[15]);
  assign S_14_8 = S_13_9;
  assign S_14_9 = S_13_10;
  assign S_14_10 = S_13_11;
  PDKGENFAX1 U24246 (.A(S_13_12), .B(C_13_11), .C((a_signless[14] & b_signless[11])), .YS(S_14_11), .YC(C_14_11));
  PDKGENFAX1 U24247 (.A(S_13_13), .B(C_13_12), .C((a_signless[14] & b_signless[12])), .YS(S_14_12), .YC(C_14_12));
  PDKGENFAX1 U24248 (.A(S_13_14), .B(C_13_13), .C((a_signless[14] & b_signless[13])), .YS(S_14_13), .YC(C_14_13));
  PDKGENFAX1 U24249 (.A(S_13_15), .B(C_13_14), .C((a_signless[14] & b_signless[14])), .YS(S_14_14), .YC(C_14_14));
  assign S_14_15 = (a_signless[14] & b_signless[15]);
  assign S_15_7 = S_14_8;
  assign S_15_8 = S_14_9;
  assign S_15_9 = S_14_10;
  assign S_15_10 = S_14_11;
  PDKGENFAX1 U24262 (.A(S_14_12), .B(C_14_11), .C((a_signless[15] & b_signless[11])), .YS(S_15_11), .YC(C_15_11));
  PDKGENFAX1 U24263 (.A(S_14_13), .B(C_14_12), .C((a_signless[15] & b_signless[12])), .YS(S_15_12), .YC(C_15_12));
  PDKGENFAX1 U24264 (.A(S_14_14), .B(C_14_13), .C((a_signless[15] & b_signless[13])), .YS(S_15_13), .YC(C_15_13));
  PDKGENFAX1 U24265 (.A(S_14_15), .B(C_14_14), .C((a_signless[15] & b_signless[14])), .YS(S_15_14), .YC(C_15_14));
  assign S_15_15 = (a_signless[15] & b_signless[15]);
  assign S_16_6 = S_15_7;
  assign S_16_7 = S_15_8;
  assign S_16_8 = S_15_9;
  assign S_16_9 = S_15_10;
  assign S_16_10 = S_15_11;
  assign {S_16_15, S_16_14, S_16_13, S_16_12, S_16_11} = {C_15_14, C_15_13, C_15_12, C_15_11} + {S_15_15, S_15_14, S_15_13, S_15_12};
  assign O = {S_16_15,S_16_14,S_16_13,S_16_12,S_16_11,S_16_10,S_16_9,S_16_8,S_16_7,S_16_6,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0};
  
  assign Out={48'b0,res_sign,O[19:10],O[9:5]};
endmodule


module mul16u_GPF ( A, B, Out );
  input [63:0] A;
  input [63:0] B;
  output [63:0] Out;
  wire [63:0] O;

  wire res_sign;
  wire[63:0] tmp,a_signless,b_signless;
  assign res_sign = A[15] ^ B[15];
  assign a_signless = {49'b0,A[14:0]};
  assign b_signless = {49'b0,B[14:0]};

  wire C_10_10,C_10_11,C_10_12,C_10_13,C_10_14,C_11_10,C_11_11,C_11_12,C_11_13,C_11_14,C_11_9,C_12_10,C_12_11,C_12_12,C_12_13,C_12_14,C_12_8,C_12_9,C_13_10,C_13_11,C_13_12,C_13_13,C_13_14,C_13_7,C_13_8,C_13_9,C_14_10,C_14_11,C_14_12,C_14_13,C_14_14,C_14_6,C_14_7,C_14_8,C_14_9,C_15_10,C_15_11,C_15_12,C_15_13,C_15_14,C_15_5,C_15_6,C_15_7,C_15_8,C_15_9,C_16_10,C_16_11,C_16_12,C_16_13,C_16_14,C_16_5,C_16_6,C_16_7,C_16_8,C_16_9,C_8_12,C_8_13,C_8_14,C_9_11,C_9_12,C_9_13,C_9_14,S_10_10,S_10_11,S_10_12,S_10_13,S_10_14,S_10_15,S_11_10,S_11_11,S_11_12,S_11_13,S_11_14,S_11_15,S_11_9,S_12_10,S_12_11,S_12_12,S_12_13,S_12_14,S_12_15,S_12_8,S_12_9,S_13_10,S_13_11,S_13_12,S_13_13,S_13_14,S_13_15,S_13_7,S_13_8,S_13_9,S_14_10,S_14_11,S_14_12,S_14_13,S_14_14,S_14_15,S_14_6,S_14_7,S_14_8,S_14_9,S_15_10,S_15_11,S_15_12,S_15_13,S_15_14,S_15_15,S_15_5,S_15_6,S_15_7,S_15_8,S_15_9,S_16_10,S_16_11,S_16_12,S_16_13,S_16_14,S_16_15,S_16_4,S_16_5,S_16_6,S_16_7,S_16_8,S_16_9,S_7_13,S_7_14,S_7_15,S_8_12,S_8_13,S_8_14,S_8_15,S_9_11,S_9_12,S_9_13,S_9_14,S_9_15;

  assign S_7_13 = (A[7] & B[13]);
  assign S_7_14 = (A[7] & B[14]);
  assign S_7_15 = (A[7] & B[15]);
  PDKGENHAX1 U183901 (.A(S_7_13), .B((A[8] & B[12])), .YS(S_8_12), .YC(C_8_12));
  PDKGENHAX1 U183902 (.A(S_7_14), .B((A[8] & B[13])), .YS(S_8_13), .YC(C_8_13));
  PDKGENHAX1 U183903 (.A(S_7_15), .B((A[8] & B[14])), .YS(S_8_14), .YC(C_8_14));
  assign S_8_15 = (A[8] & B[15]);
  PDKGENHAX1 U183916 (.A(S_8_12), .B((A[9] & B[11])), .YS(S_9_11), .YC(C_9_11));
  PDKGENFAX1 U183917 (.A(S_8_13), .B(C_8_12), .C((A[9] & B[12])), .YS(S_9_12), .YC(C_9_12));
  PDKGENFAX1 U183918 (.A(S_8_14), .B(C_8_13), .C((A[9] & B[13])), .YS(S_9_13), .YC(C_9_13));
  PDKGENFAX1 U183919 (.A(S_8_15), .B(C_8_14), .C((A[9] & B[14])), .YS(S_9_14), .YC(C_9_14));
  assign S_9_15 = (A[9] & B[15]);
  PDKGENHAX1 U183931 (.A(S_9_11), .B((A[10] & B[10])), .YS(S_10_10), .YC(C_10_10));
  PDKGENFAX1 U183932 (.A(S_9_12), .B(C_9_11), .C((A[10] & B[11])), .YS(S_10_11), .YC(C_10_11));
  PDKGENFAX1 U183933 (.A(S_9_13), .B(C_9_12), .C((A[10] & B[12])), .YS(S_10_12), .YC(C_10_12));
  PDKGENFAX1 U183934 (.A(S_9_14), .B(C_9_13), .C((A[10] & B[13])), .YS(S_10_13), .YC(C_10_13));
  PDKGENFAX1 U183935 (.A(S_9_15), .B(C_9_14), .C((A[10] & B[14])), .YS(S_10_14), .YC(C_10_14));
  assign S_10_15 = (A[10] & B[15]);
  PDKGENHAX1 U183946 (.A(S_10_10), .B((A[11] & B[9])), .YS(S_11_9), .YC(C_11_9));
  PDKGENFAX1 U183947 (.A(S_10_11), .B(C_10_10), .C((A[11] & B[10])), .YS(S_11_10), .YC(C_11_10));
  PDKGENFAX1 U183948 (.A(S_10_12), .B(C_10_11), .C((A[11] & B[11])), .YS(S_11_11), .YC(C_11_11));
  PDKGENFAX1 U183949 (.A(S_10_13), .B(C_10_12), .C((A[11] & B[12])), .YS(S_11_12), .YC(C_11_12));
  PDKGENFAX1 U183950 (.A(S_10_14), .B(C_10_13), .C((A[11] & B[13])), .YS(S_11_13), .YC(C_11_13));
  PDKGENFAX1 U183951 (.A(S_10_15), .B(C_10_14), .C((A[11] & B[14])), .YS(S_11_14), .YC(C_11_14));
  assign S_11_15 = (A[11] & B[15]);
  PDKGENHAX1 U183961 (.A(S_11_9), .B((A[12] & B[8])), .YS(S_12_8), .YC(C_12_8));
  PDKGENFAX1 U183962 (.A(S_11_10), .B(C_11_9), .C((A[12] & B[9])), .YS(S_12_9), .YC(C_12_9));
  PDKGENFAX1 U183963 (.A(S_11_11), .B(C_11_10), .C((A[12] & B[10])), .YS(S_12_10), .YC(C_12_10));
  PDKGENFAX1 U183964 (.A(S_11_12), .B(C_11_11), .C((A[12] & B[11])), .YS(S_12_11), .YC(C_12_11));
  PDKGENFAX1 U183965 (.A(S_11_13), .B(C_11_12), .C((A[12] & B[12])), .YS(S_12_12), .YC(C_12_12));
  PDKGENFAX1 U183966 (.A(S_11_14), .B(C_11_13), .C((A[12] & B[13])), .YS(S_12_13), .YC(C_12_13));
  PDKGENFAX1 U183967 (.A(S_11_15), .B(C_11_14), .C((A[12] & B[14])), .YS(S_12_14), .YC(C_12_14));
  assign S_12_15 = (A[12] & B[15]);
  PDKGENHAX1 U183976 (.A(S_12_8), .B((A[13] & B[7])), .YS(S_13_7), .YC(C_13_7));
  PDKGENFAX1 U183977 (.A(S_12_9), .B(C_12_8), .C((A[13] & B[8])), .YS(S_13_8), .YC(C_13_8));
  PDKGENFAX1 U183978 (.A(S_12_10), .B(C_12_9), .C((A[13] & B[9])), .YS(S_13_9), .YC(C_13_9));
  PDKGENFAX1 U183979 (.A(S_12_11), .B(C_12_10), .C((A[13] & B[10])), .YS(S_13_10), .YC(C_13_10));
  PDKGENFAX1 U183980 (.A(S_12_12), .B(C_12_11), .C((A[13] & B[11])), .YS(S_13_11), .YC(C_13_11));
  PDKGENFAX1 U183981 (.A(S_12_13), .B(C_12_12), .C((A[13] & B[12])), .YS(S_13_12), .YC(C_13_12));
  PDKGENFAX1 U183982 (.A(S_12_14), .B(C_12_13), .C((A[13] & B[13])), .YS(S_13_13), .YC(C_13_13));
  PDKGENFAX1 U183983 (.A(S_12_15), .B(C_12_14), .C((A[13] & B[14])), .YS(S_13_14), .YC(C_13_14));
  assign S_13_15 = (A[13] & B[15]);
  PDKGENHAX1 U183991 (.A(S_13_7), .B((A[14] & B[6])), .YS(S_14_6), .YC(C_14_6));
  PDKGENFAX1 U183992 (.A(S_13_8), .B(C_13_7), .C((A[14] & B[7])), .YS(S_14_7), .YC(C_14_7));
  PDKGENFAX1 U183993 (.A(S_13_9), .B(C_13_8), .C((A[14] & B[8])), .YS(S_14_8), .YC(C_14_8));
  PDKGENFAX1 U183994 (.A(S_13_10), .B(C_13_9), .C((A[14] & B[9])), .YS(S_14_9), .YC(C_14_9));
  PDKGENFAX1 U183995 (.A(S_13_11), .B(C_13_10), .C((A[14] & B[10])), .YS(S_14_10), .YC(C_14_10));
  PDKGENFAX1 U183996 (.A(S_13_12), .B(C_13_11), .C((A[14] & B[11])), .YS(S_14_11), .YC(C_14_11));
  PDKGENFAX1 U183997 (.A(S_13_13), .B(C_13_12), .C((A[14] & B[12])), .YS(S_14_12), .YC(C_14_12));
  PDKGENFAX1 U183998 (.A(S_13_14), .B(C_13_13), .C((A[14] & B[13])), .YS(S_14_13), .YC(C_14_13));
  PDKGENFAX1 U183999 (.A(S_13_15), .B(C_13_14), .C((A[14] & B[14])), .YS(S_14_14), .YC(C_14_14));
  assign S_14_15 = (A[14] & B[15]);
  PDKGENHAX1 U184006 (.A(S_14_6), .B((A[15] & B[5])), .YS(S_15_5), .YC(C_15_5));
  PDKGENFAX1 U184007 (.A(S_14_7), .B(C_14_6), .C((A[15] & B[6])), .YS(S_15_6), .YC(C_15_6));
  PDKGENFAX1 U184008 (.A(S_14_8), .B(C_14_7), .C((A[15] & B[7])), .YS(S_15_7), .YC(C_15_7));
  PDKGENFAX1 U184009 (.A(S_14_9), .B(C_14_8), .C((A[15] & B[8])), .YS(S_15_8), .YC(C_15_8));
  PDKGENFAX1 U184010 (.A(S_14_10), .B(C_14_9), .C((A[15] & B[9])), .YS(S_15_9), .YC(C_15_9));
  PDKGENFAX1 U184011 (.A(S_14_11), .B(C_14_10), .C((A[15] & B[10])), .YS(S_15_10), .YC(C_15_10));
  PDKGENFAX1 U184012 (.A(S_14_12), .B(C_14_11), .C((A[15] & B[11])), .YS(S_15_11), .YC(C_15_11));
  PDKGENFAX1 U184013 (.A(S_14_13), .B(C_14_12), .C((A[15] & B[12])), .YS(S_15_12), .YC(C_15_12));
  PDKGENFAX1 U184014 (.A(S_14_14), .B(C_14_13), .C((A[15] & B[13])), .YS(S_15_13), .YC(C_15_13));
  PDKGENFAX1 U184015 (.A(S_14_15), .B(C_14_14), .C((A[15] & B[14])), .YS(S_15_14), .YC(C_15_14));
  assign S_15_15 = (A[15] & B[15]);
  assign S_16_4 = S_15_5;
  PDKGENHAX1 U184022 (.A(S_15_6), .B(C_15_5), .YS(S_16_5), .YC(C_16_5));
  PDKGENFAX1 U184023 (.A(S_15_7), .B(C_16_5), .C(C_15_6), .YS(S_16_6), .YC(C_16_6));
  PDKGENFAX1 U184024 (.A(S_15_8), .B(C_16_6), .C(C_15_7), .YS(S_16_7), .YC(C_16_7));
  PDKGENFAX1 U184025 (.A(S_15_9), .B(C_16_7), .C(C_15_8), .YS(S_16_8), .YC(C_16_8));
  PDKGENFAX1 U184026 (.A(S_15_10), .B(C_16_8), .C(C_15_9), .YS(S_16_9), .YC(C_16_9));
  PDKGENFAX1 U184027 (.A(S_15_11), .B(C_16_9), .C(C_15_10), .YS(S_16_10), .YC(C_16_10));
  PDKGENFAX1 U184028 (.A(S_15_12), .B(C_16_10), .C(C_15_11), .YS(S_16_11), .YC(C_16_11));
  PDKGENFAX1 U184029 (.A(S_15_13), .B(C_16_11), .C(C_15_12), .YS(S_16_12), .YC(C_16_12));
  PDKGENFAX1 U184030 (.A(S_15_14), .B(C_16_12), .C(C_15_13), .YS(S_16_13), .YC(C_16_13));
  PDKGENFAX1 U184031 (.A(S_15_15), .B(C_16_13), .C(C_15_14), .YS(S_16_14), .YC(C_16_14));
  assign S_16_15 = C_16_14;
  assign O = {S_16_15,S_16_14,S_16_13,S_16_12,S_16_11,S_16_10,S_16_9,S_16_8,S_16_7,S_16_6,S_16_5,S_16_4,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0};
  
  assign Out={48'b0,res_sign,O[19:10],O[9:5]};
endmodule


//---------------------------------------Adders----------------------------------------------

module add16u_0AV(a, b, o);
  input [63:0] a, b;  //Modified by Awais
  output [63:0] o;

  reg [63:0] A,B,O;  //Added by Awais

  reg sig_33, sig_34, sig_35, sig_36, sig_38, sig_39;
  reg sig_40, sig_41, sig_43, sig_44, sig_45, sig_46;
  reg sig_48, sig_49, sig_50, sig_51, sig_53, sig_54;
  reg sig_55, sig_56, sig_58, sig_59, sig_60, sig_61;
  reg sig_63, sig_64, sig_65, sig_66, sig_68, sig_69;
  reg sig_70, sig_71, sig_73, sig_74, sig_75, sig_76;
  reg sig_78, sig_79, sig_80, sig_81, sig_83, sig_84;
  reg sig_85, sig_86, sig_88, sig_89, sig_90, sig_91;
  reg sig_93, sig_94, sig_95, sig_96, sig_98, sig_99;
  reg sig_100, sig_101, sig_103, sig_104, sig_105, sig_106;


  // Part-1:

  reg [63:0] tmp_res;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b


  // Part-2

  always @(a, b) 
  begin
    A = {49'b0,a[14:0]};                    // extract the magnitude from a
    B = {49'b0,b[14:0]};                    // extract the magnitude from b

    
    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
      begin
        result_sign = a_sign;
      end
    else if(B > A)                          // this means we perform b-a and set the sign
      begin
          A = -{49'b0,a[14:0]};
          result_sign = b_sign;             // result sign is 1 unless result is 0
      end
    else                                    // this means we perform a-b and set the sign
      begin
          B = -{49'b0,b[14:0]};
          result_sign = a_sign;            // result sign is 1 unless result is 0
      end
    

    // Following is what constitutes a+b
    O[0] = A[0] ^ B[0];
    sig_33 = A[0] & B[0];
    sig_34 = A[1] ^ B[1];
    sig_35 = A[1] & B[1];
    sig_36 = A[0] & B[0];
    O[1] = sig_34 ^ sig_33;
    sig_38 = sig_35 | sig_36;
    sig_39 = A[2] ^ B[2];
    sig_40 = A[2] & B[2];
    sig_41 = sig_39 & sig_38;
    O[2] = sig_39 ^ sig_38;
    sig_43 = sig_40 | sig_41;
    sig_44 = A[3] ^ B[3];
    sig_45 = A[3] & B[3];
    sig_46 = sig_44 & sig_43;
    O[3] = sig_44 ^ sig_43;
    sig_48 = sig_45 | sig_46;
    sig_49 = A[4] ^ B[4];
    sig_50 = A[4] & B[4];
    sig_51 = sig_49 & sig_48;
    O[4] = sig_49 ^ sig_48;
    sig_53 = sig_50 | sig_51;
    sig_54 = A[5] ^ B[5];
    sig_55 = A[5] & B[5];
    sig_56 = sig_54 & sig_53;
    O[5] = sig_54 ^ sig_53;
    sig_58 = sig_55 | sig_56;
    sig_59 = A[6] ^ B[6];
    sig_60 = A[6] & B[6];
    sig_61 = sig_59 & sig_58;
    O[6] = sig_59 ^ sig_58;
    sig_63 = sig_60 | sig_61;
    sig_64 = A[7] ^ B[7];
    sig_65 = A[7] & B[7];
    sig_66 = sig_64 & sig_63;
    O[7] = sig_64 ^ sig_63;
    sig_68 = sig_65 | sig_66;
    sig_69 = A[8] ^ B[8];
    sig_70 = A[8] & B[8];
    sig_71 = sig_69 & sig_68;
    O[8] = sig_69 ^ sig_68;
    sig_73 = sig_70 | sig_71;
    sig_74 = A[9] ^ B[9];
    sig_75 = A[9] & B[9];
    sig_76 = sig_74 & sig_73;
    O[9] = sig_74 ^ sig_73;
    sig_78 = sig_75 | sig_76;
    sig_79 = A[10] ^ B[10];
    sig_80 = A[10] & B[10];
    sig_81 = sig_79 & sig_78;
    O[10] = sig_79 ^ sig_78;
    sig_83 = sig_80 | sig_81;
    sig_84 = A[11] ^ B[11];
    sig_85 = A[11] & B[11];
    sig_86 = sig_84 & sig_83;
    O[11] = sig_84 ^ sig_83;
    sig_88 = sig_85 | sig_86;
    sig_89 = A[12] ^ B[12];
    sig_90 = A[12] & B[12];
    sig_91 = sig_89 & sig_88;
    O[12] = sig_89 ^ sig_88;
    sig_93 = sig_90 | sig_91;
    sig_94 = A[13] ^ B[13];
    sig_95 = A[13] & B[13];
    sig_96 = sig_94 & sig_93;
    O[13] = sig_94 ^ sig_93;
    sig_98 = sig_95 | sig_96;
    sig_99 = A[14] ^ B[14];
    sig_100 = A[14] & B[14];
    sig_101 = sig_99 & sig_98;
    O[14] = sig_99 ^ sig_98;
    sig_103 = sig_100 | sig_101;
    sig_104 = A[15] ^ B[15];
    sig_105 = A[15] & B[15];
    sig_106 = sig_104 & sig_103;
    O[15] = sig_104 ^ sig_103;
    O[16] = sig_105 | sig_106;


    if(O == 0) 
    begin 
      result_sign = 0;              // if the resultant value is 0, then we set the sign +ve
    end

  end

  assign o = {48'b0,result_sign,O[14:0]}; // get the final result

endmodule


module add16u_0EM(a, b, o);
  input [63:0] a, b;
  output [63:0] o;

  reg [63:0] A, B, O;

  reg sig_45, sig_48, sig_49, sig_50, sig_51, sig_53;
  reg sig_54, sig_55, sig_56, sig_58, sig_59, sig_60;
  reg sig_61, sig_63, sig_64, sig_65, sig_66, sig_68;
  reg sig_69, sig_70, sig_71, sig_73, sig_74, sig_75;
  reg sig_76, sig_78, sig_79, sig_80, sig_81, sig_83;
  reg sig_84, sig_85, sig_86, sig_88, sig_89, sig_90;
  reg sig_91, sig_93, sig_94, sig_95, sig_96, sig_98;
  reg sig_99, sig_100, sig_101, sig_103, sig_104, sig_105; 
  reg sig_106;

  // Part-1:

  reg [63:0] tmp_res;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b


  // Part-2

  always @(a, b) 
  begin
    A = {49'b0,a[14:0]};                    // extract the magnitude from a
    B = {49'b0,b[14:0]};                    // extract the magnitude from b

    
    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
      begin
        result_sign = a_sign;
      end
    else if(B > A)                          // this means we perform b-a and set the sign
      begin
          A = -{49'b0,a[14:0]};
          result_sign = b_sign;             // result sign is 1 unless result is 0
      end
    else                                    // this means we perform a-b and set the sign
      begin
          B = -{49'b0,b[14:0]};
          result_sign = a_sign;            // result sign is 1 unless result is 0
      end
    

    // Following is what constitutes a+b

    O[0] = 1'b1;
    O[2] = 1'b1;
    O[3] = B[3] ^ A[3];
    sig_45 = A[3] & B[3];
    sig_48 = sig_45;
    sig_49 = A[4] ^ B[4];
    sig_50 = A[4] & B[4];
    sig_51 = sig_49 & sig_48;
    O[4] = sig_49 ^ sig_48;
    sig_53 = sig_50 | sig_51;
    sig_54 = A[5] ^ B[5];
    sig_55 = A[5] & B[5];
    sig_56 = sig_54 & sig_53;
    O[5] = sig_54 ^ sig_53;
    sig_58 = sig_55 | sig_56;
    sig_59 = A[6] ^ B[6];
    sig_60 = A[6] & B[6];
    sig_61 = sig_59 & sig_58;
    O[6] = sig_59 ^ sig_58;
    sig_63 = sig_60 | sig_61;
    sig_64 = A[7] ^ B[7];
    sig_65 = A[7] & B[7];
    sig_66 = sig_64 & sig_63;
    O[7] = sig_64 ^ sig_63;
    sig_68 = sig_65 | sig_66;
    sig_69 = A[8] ^ B[8];
    sig_70 = A[8] & B[8];
    sig_71 = sig_69 & sig_68;
    O[8] = sig_69 ^ sig_68;
    sig_73 = sig_70 | sig_71;
    sig_74 = A[9] ^ B[9];
    sig_75 = A[9] & B[9];
    sig_76 = sig_74 & sig_73;
    O[9] = sig_74 ^ sig_73;
    sig_78 = sig_75 | sig_76;
    sig_79 = A[10] ^ B[10];
    sig_80 = A[10] & B[10];
    sig_81 = sig_79 & sig_78;
    O[10] = sig_79 ^ sig_78;
    sig_83 = sig_80 | sig_81;
    sig_84 = A[11] ^ B[11];
    sig_85 = A[11] & B[11];
    sig_86 = sig_84 & sig_83;
    O[11] = sig_84 ^ sig_83;
    sig_88 = sig_85 | sig_86;
    sig_89 = A[12] ^ B[12];
    sig_90 = A[12] & B[12];
    sig_91 = sig_89 & sig_88;
    O[12] = sig_89 ^ sig_88;
    sig_93 = sig_90 | sig_91;
    sig_94 = A[13] ^ B[13];
    sig_95 = A[13] & B[13];
    sig_96 = sig_94 & sig_93;
    O[13] = sig_94 ^ sig_93;
    sig_98 = sig_95 | sig_96;
    sig_99 = A[14] ^ B[14];
    sig_100 = A[14] & B[14];
    sig_101 = sig_99 & sig_98;
    O[14] = sig_99 ^ sig_98;
    sig_103 = sig_100 | sig_101;
    sig_104 = A[15] ^ B[15];
    sig_105 = A[15] & B[15];
    sig_106 = sig_104 & sig_103;
    O[15] = sig_104 ^ sig_103;
    O[16] = sig_105 | sig_106;

    O[1] = A[2];

    if(O == 0) 
    begin 
      result_sign = 0;              // if the resultant value is 0, then we set the sign +ve
    end

  end

  assign o = {48'b0,result_sign,O[14:0]}; // get the final result

endmodule


module add16u_0Q7(a, b, o);
  input [63:0] a, b;
  output [63:0] o;

  reg [63:0] A, B, O;

  reg sig_50, sig_53, sig_54, sig_55, sig_56, sig_58;
  reg sig_59, sig_60, sig_61, sig_63, sig_64, sig_65;
  reg sig_66, sig_68, sig_69, sig_70, sig_71, sig_73;
  reg sig_74, sig_75, sig_76, sig_78, sig_79, sig_80;
  reg sig_81, sig_84, sig_85, sig_86, sig_88, sig_89;
  reg sig_90, sig_91, sig_93, sig_94, sig_95, sig_96;
  reg sig_98, sig_99, sig_100, sig_101, sig_103, sig_104;
  reg sig_105, sig_106;

  // Part-1:

  reg [63:0] tmp_res;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b


  // Part-2

  always @(a, b) 
  begin
    A = {49'b0,a[14:0]};                    // extract the magnitude from a
    B = {49'b0,b[14:0]};                    // extract the magnitude from b

    
    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
      begin
        result_sign = a_sign;
      end
    else if(B > A)                          // this means we perform b-a and set the sign
      begin
          A = -{49'b0,a[14:0]};
          result_sign = b_sign;             // result sign is 1 unless result is 0
      end
    else                                    // this means we perform a-b and set the sign
      begin
          B = -{49'b0,b[14:0]};
          result_sign = a_sign;            // result sign is 1 unless result is 0
      end
    

    // Following is what constitutes a+b

    sig_50 = A[4] | B[4];
    O[4] = 1'b0;
    sig_53 = sig_50;
    sig_54 = A[5] ^ B[5];
    sig_55 = A[5] & B[5];
    sig_56 = sig_54 & sig_53;
    O[5] = sig_54 ^ sig_53;
    sig_58 = sig_55 | sig_56;
    sig_59 = A[6] ^ B[6];
    sig_60 = A[6] & B[6];
    sig_61 = sig_59 & sig_58;
    O[6] = sig_59 ^ sig_58;
    sig_63 = sig_60 | sig_61;
    sig_64 = A[7] ^ B[7];
    sig_65 = A[7] & B[7];
    sig_66 = sig_64 & sig_63;
    O[7] = sig_64 ^ sig_63;
    sig_68 = sig_65 | sig_66;
    sig_69 = A[8] ^ B[8];
    sig_70 = A[8] & B[8];
    sig_71 = sig_69 & sig_68;
    O[2] = sig_69 ^ sig_68;
    sig_73 = sig_70 | sig_71;
    sig_74 = A[9] ^ B[9];
    sig_75 = A[9] & B[9];
    sig_76 = sig_74 & sig_73;
    O[9] = sig_74 ^ sig_73;
    sig_78 = sig_75 | sig_76;
    sig_79 = A[10] ^ B[10];
    sig_80 = A[10] & B[10];
    sig_81 = sig_79 & sig_78;
    O[10] = sig_79 ^ sig_78;
    O[1] = sig_80 | sig_81;
    sig_84 = A[11] ^ B[11];
    sig_85 = A[11] & B[11];
    sig_86 = sig_84 & O[1];
    O[11] = sig_84 ^ O[1];
    sig_88 = sig_85 | sig_86;
    sig_89 = A[12] ^ B[12];
    sig_90 = A[12] & B[12];
    sig_91 = sig_89 & sig_88;
    O[12] = sig_89 ^ sig_88;
    sig_93 = sig_90 | sig_91;
    sig_94 = A[13] ^ B[13];
    sig_95 = A[13] & B[13];
    sig_96 = sig_94 & sig_93;
    O[13] = sig_94 ^ sig_93;
    sig_98 = sig_95 | sig_96;
    sig_99 = A[14] ^ B[14];
    sig_100 = A[14] & B[14];
    sig_101 = sig_99 & sig_98;
    O[14] = sig_99 ^ sig_98;
    sig_103 = sig_100 | sig_101;
    sig_104 = A[15] ^ B[15];
    sig_105 = A[15] & B[15];
    sig_106 = sig_104 & sig_103;
    O[15] = sig_104 ^ sig_103;
    O[16] = sig_105 | sig_106;
    O[0] = B[14];
    O[3] = A[3];
    O[8] = O[2];

    if(O == 0) 
    begin 
      result_sign = 0;              // if the resultant value is 0, then we set the sign +ve
    end

  end

  assign o = {48'b0,result_sign,O[14:0]}; // get the final result
  
endmodule


module add16u_073(a, b, o);
  input [63:0] a, b;
  output [63:0] o;

  reg [63:0] A, B, O;

  reg sig_59, sig_60, sig_63, sig_64, sig_65, sig_66;
  reg sig_68, sig_69, sig_70, sig_71, sig_73, sig_74;
  reg sig_75, sig_76, sig_78, sig_79, sig_80, sig_81;
  reg sig_83, sig_84, sig_86, sig_88, sig_89, sig_90;
  reg sig_91, sig_93, sig_94, sig_95, sig_96, sig_98;
  reg sig_99, sig_100, sig_101, sig_103, sig_104, sig_105;
  reg sig_106;

  // Part-1:

  reg [63:0] tmp_res;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b


  // Part-2

  always @(a, b) 
  begin
    A = {49'b0,a[14:0]};                    // extract the magnitude from a
    B = {49'b0,b[14:0]};                    // extract the magnitude from b

    
    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
      begin
        result_sign = a_sign;
      end
    else if(B > A)                          // this means we perform b-a and set the sign
      begin
          A = -{49'b0,a[14:0]};
          result_sign = b_sign;             // result sign is 1 unless result is 0
      end
    else                                    // this means we perform a-b and set the sign
      begin
          B = -{49'b0,b[14:0]};
          result_sign = a_sign;            // result sign is 1 unless result is 0
      end
    

    // Following is what constitutes a+b

    O[4] = 1'b0;
    O[2] = A[11];
    sig_59 = A[6] ^ B[6];
    sig_60 = A[6] | B[6];
    O[6] = !sig_59;
    sig_63 = sig_60;
    sig_64 = A[7] ^ B[7];
    sig_65 = A[7] & B[7];
    sig_66 = sig_64 & sig_63;
    O[7] = sig_64 ^ sig_63;
    sig_68 = sig_65 | sig_66;
    sig_69 = A[8] ^ B[8];
    sig_70 = A[8] & B[8];
    sig_71 = sig_69 & sig_68;
    O[8] = sig_69 ^ sig_68;
    sig_73 = sig_70 | sig_71;
    sig_74 = A[9] ^ B[9];
    sig_75 = A[9] & B[9];
    sig_76 = sig_74 & sig_73;
    O[9] = sig_74 ^ sig_73;
    sig_78 = sig_75 | sig_76;
    sig_79 = A[10] ^ B[10];
    sig_80 = A[10] & B[10];
    sig_81 = sig_79 & sig_78;
    O[10] = sig_79 ^ sig_78;
    sig_83 = sig_80 | sig_81;
    sig_84 = A[11] ^ B[11];
    O[5] = A[11] & B[11];
    sig_86 = sig_84 & sig_83;
    O[11] = sig_84 ^ sig_83;
    sig_88 = O[5] | sig_86;
    sig_89 = A[12] ^ B[12];
    sig_90 = A[12] & B[12];
    sig_91 = sig_89 & sig_88;
    O[12] = sig_89 ^ sig_88;
    sig_93 = sig_90 | sig_91;
    sig_94 = A[13] ^ B[13];
    sig_95 = A[13] & B[13];
    sig_96 = sig_94 & sig_93;
    O[13] = sig_94 ^ sig_93;
    sig_98 = sig_95 | sig_96;
    sig_99 = A[14] ^ B[14];
    sig_100 = A[14] & B[14];
    sig_101 = sig_99 & sig_98;
    O[0] = sig_99 ^ sig_98;
    sig_103 = sig_100 | sig_101;
    sig_104 = A[15] ^ B[15];
    sig_105 = A[15] & B[15];
    sig_106 = sig_104 & sig_103;
    O[15] = sig_104 ^ sig_103;
    O[16] = sig_105 | sig_106;
    O[1] = B[9];
    O[3] = A[4];
    O[14] = O[0];

    if(O == 0) 
    begin 
      result_sign = 0;              // if the resultant value is 0, then we set the sign +ve
    end

  end

  assign o = {48'b0,result_sign,O[14:0]}; // get the final result

endmodule


module add16u_0M0(a, b, o);
  input [63:0] a, b;
  output [63:0] o;

  reg [63:0] A, B, O;

  reg sig_69, sig_70, sig_71, sig_73, sig_74, sig_75;
  reg sig_76, sig_78, sig_79, sig_80, sig_81, sig_83;
  reg sig_84, sig_85, sig_86, sig_89, sig_90, sig_91;
  reg sig_93, sig_94, sig_95, sig_96, sig_98, sig_99;
  reg sig_100, sig_101, sig_103, sig_104, sig_105, sig_106;

  // Part-1:

  reg [63:0] tmp_res;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b


  // Part-2

  always @(a, b) 
  begin
    A = {49'b0,a[14:0]};                    // extract the magnitude from a
    B = {49'b0,b[14:0]};                    // extract the magnitude from b

    
    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
      begin
        result_sign = a_sign;
      end
    else if(B > A)                          // this means we perform b-a and set the sign
      begin
          A = -{49'b0,a[14:0]};
          result_sign = b_sign;             // result sign is 1 unless result is 0
      end
    else                                    // this means we perform a-b and set the sign
      begin
          B = -{49'b0,b[14:0]};
          result_sign = a_sign;            // result sign is 1 unless result is 0
      end
    

    // Following is what constitutes a+b

    O[6] = 1'b1;
    sig_69 = A[8] ^ B[8];
    sig_70 = A[8] & B[8];
    sig_71 = sig_69 & B[7];
    O[8] = sig_69 ^ B[7];
    sig_73 = sig_70 | sig_71;
    sig_74 = A[9] ^ B[9];
    sig_75 = A[9] & B[9];
    sig_76 = sig_74 & sig_73;
    O[9] = sig_74 ^ sig_73;
    sig_78 = sig_75 | sig_76;
    sig_79 = A[10] ^ B[10];
    sig_80 = A[10] & B[10];
    sig_81 = sig_79 & sig_78;
    O[10] = sig_79 ^ sig_78;
    sig_83 = sig_80 | sig_81;
    sig_84 = A[11] ^ B[11];
    sig_85 = A[11] & B[11];
    sig_86 = sig_84 & sig_83;
    O[11] = sig_84 ^ sig_83;
    O[2] = sig_85 | sig_86;
    sig_89 = A[12] ^ B[12];
    sig_90 = A[12] & B[12];
    sig_91 = sig_89 & O[2];
    O[12] = sig_89 ^ O[2];
    sig_93 = sig_90 | sig_91;
    sig_94 = A[13] ^ B[13];
    sig_95 = A[13] & B[13];
    sig_96 = sig_94 & sig_93;
    O[13] = sig_94 ^ sig_93;
    sig_98 = sig_95 | sig_96;
    sig_99 = A[14] ^ B[14];
    sig_100 = A[14] & B[14];
    sig_101 = sig_99 & sig_98;
    O[14] = sig_99 ^ sig_98;
    sig_103 = sig_100 | sig_101;
    sig_104 = A[15] ^ B[15];
    sig_105 = A[15] & B[15];
    sig_106 = sig_104 & sig_103;
    O[5] = sig_104 ^ sig_103;
    O[16] = sig_105 | sig_106;
    O[0] = B[11];
    O[1] = A[13];
    O[3] = B[13];
    O[4] = B[2];
    O[7] = A[7];
    O[15] = O[5];

    if(O == 0) 
    begin 
      result_sign = 0;              // if the resultant value is 0, then we set the sign +ve
    end

  end

  assign o = {48'b0,result_sign,O[14:0]}; // get the final result

endmodule


module add16u_0DL(a, b, o);
  input [63:0] a, b;
  output [63:0] o;

  reg [63:0] A, B, O;

  reg sig_79, sig_80, sig_81, sig_83, sig_84, sig_85;
  reg sig_86, sig_88, sig_89, sig_90, sig_91, sig_93;
  reg sig_94, sig_96, sig_98, sig_99, sig_100, sig_101;
  reg sig_103, sig_104, sig_105, sig_106;

  // Part-1:

  reg [63:0] tmp_res;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b


  // Part-2

  always @(a, b) 
  begin
    A = {49'b0,a[14:0]};                    // extract the magnitude from a
    B = {49'b0,b[14:0]};                    // extract the magnitude from b

    
    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
      begin
        result_sign = a_sign;
      end
    else if(B > A)                          // this means we perform b-a and set the sign
      begin
          A = -{49'b0,a[14:0]};
          result_sign = b_sign;             // result sign is 1 unless result is 0
      end
    else                                    // this means we perform a-b and set the sign
      begin
          B = -{49'b0,b[14:0]};
          result_sign = a_sign;            // result sign is 1 unless result is 0
      end
    

    // Following is what constitutes a+b

    O[0] = B[10];
    O[1] = 1'b0;
    sig_79 = A[10] ^ B[10];
    sig_80 = A[10] & B[10];
    sig_81 = sig_79 & B[9];
    O[10] = sig_79 ^ B[9];
    sig_83 = sig_80 | sig_81;
    sig_84 = A[11] ^ B[11];
    sig_85 = A[11] & B[11];
    sig_86 = sig_84 & sig_83;
    O[11] = sig_84 ^ sig_83;
    sig_88 = sig_85 | sig_86;
    sig_89 = A[12] ^ B[12];
    sig_90 = A[12] & B[12];
    sig_91 = sig_89 & sig_88;
    O[3] = sig_89 ^ sig_88;
    sig_93 = sig_90 | sig_91;
    sig_94 = A[13] ^ B[13];
    O[5] = A[13] & B[13];
    sig_96 = sig_94 & sig_93;
    O[13] = sig_94 ^ sig_93;
    sig_98 = O[5] | sig_96;
    sig_99 = A[14] ^ B[14];
    sig_100 = A[14] & B[14];
    sig_101 = sig_99 & sig_98;
    O[14] = sig_99 ^ sig_98;
    sig_103 = sig_100 | sig_101;
    sig_104 = A[15] ^ B[15];
    sig_105 = A[15] & B[15];
    sig_106 = sig_104 & sig_103;
    O[15] = sig_104 ^ sig_103;
    O[16] = sig_105 | sig_106;
    O[2] = B[14];
    O[4] = A[8];
    O[6] = A[7];
    O[7] = B[1];
    O[8] = B[8];
    O[9] = A[9];
    O[12] = O[3];

    if(O == 0) 
    begin 
      result_sign = 0;              // if the resultant value is 0, then we set the sign +ve
    end

  end

  assign o = {48'b0,result_sign,O[14:0]}; // get the final result

endmodule


module add16u_0GK(a, b, o);
  input [63:0] a, b;
  output [63:0] o;

  reg [63:0] A, B, O;

  reg sig_89, sig_90, sig_91, sig_93, sig_94, sig_95;
  reg sig_96, sig_98, sig_99, sig_100, sig_101, sig_103;
  reg sig_105;

  // Part-1:

  reg [63:0] tmp_res;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b


  // Part-2

  always @(a, b) 
  begin
    A = {49'b0,a[14:0]};                    // extract the magnitude from a
    B = {49'b0,b[14:0]};                    // extract the magnitude from b

    
    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
      begin
        result_sign = a_sign;
      end
    else if(B > A)                          // this means we perform b-a and set the sign
      begin
          A = -{49'b0,a[14:0]};
          result_sign = b_sign;             // result sign is 1 unless result is 0
      end
    else                                    // this means we perform a-b and set the sign
      begin
          B = -{49'b0,b[14:0]};
          result_sign = a_sign;            // result sign is 1 unless result is 0
      end
    

    // Following is what constitutes a+b

    sig_89 = A[12] ^ B[12];
    sig_90 = A[12] & B[12];
    sig_91 = sig_89 & B[11];
    O[12] = sig_89 ^ B[11];
    sig_93 = sig_90 | sig_91;
    sig_94 = A[13] ^ B[13];
    sig_95 = A[13] & B[13];
    sig_96 = sig_94 & sig_93;
    O[13] = sig_94 ^ sig_93;
    sig_98 = sig_95 | sig_96;
    sig_99 = A[14] ^ B[14];
    sig_100 = A[14] & B[14];
    sig_101 = sig_99 & sig_98;
    O[14] = sig_99 ^ sig_98;
    sig_103 = sig_100 | sig_101;
    O[6] = A[15] ^ B[15];
    sig_105 = A[15] & B[15];
    O[3] = O[6] & sig_103;
    O[15] = O[6] ^ sig_103;
    O[16] = sig_105 | O[3];
    O[0] = B[13];
    O[1] = A[6];
    O[2] = B[7];
    O[4] = B[12];
    O[5] = A[10];
    O[7] = B[9];
    O[8] = B[6];
    O[9] = O[3];
    O[10] = A[6];
    O[11] = A[11];

    if(O == 0) 
    begin 
      result_sign = 0;              // if the resultant value is 0, then we set the sign +ve
    end

  end

  assign o = {48'b0,result_sign,O[14:0]}; // get the final result

endmodule


module add16u_02E(a, b, o);
  input [63:0] a, b;
  output [63:0] o;

  reg [63:0] A, B, O;

  reg sig_95, sig_99, sig_100, sig_103, sig_104, sig_105;
  reg sig_106;

  // Part-1:

  reg [63:0] tmp_res;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b


  // Part-2

  always @(a, b) 
  begin
    A = {49'b0,a[14:0]};                    // extract the magnitude from a
    B = {49'b0,b[14:0]};                    // extract the magnitude from b

    
    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
      begin
        result_sign = a_sign;
      end
    else if(B > A)                          // this means we perform b-a and set the sign
      begin
          A = -{49'b0,a[14:0]};
          result_sign = b_sign;             // result sign is 1 unless result is 0
      end
    else                                    // this means we perform a-b and set the sign
      begin
          B = -{49'b0,b[14:0]};
          result_sign = a_sign;            // result sign is 1 unless result is 0
      end
    

    // Following is what constitutes a+b

    O[6] = A[3];
    O[13] = 1'b0;
    sig_95 = A[13] | B[13];
    O[5] = sig_95;
    sig_99 = A[14] ^ B[14];
    sig_100 = A[14] & B[14];
    O[7] = sig_99 & O[5];
    O[14] = sig_99 ^ O[5];
    sig_103 = sig_100 | O[7];
    sig_104 = A[15] ^ B[15];
    sig_105 = A[15] & B[15];
    sig_106 = sig_104 & sig_103;
    O[1] = sig_104 ^ sig_103;
    O[16] = sig_105 | sig_106;
    O[0] = A[9];
    O[2] = A[7];
    O[3] = A[6];
    O[4] = B[12];
    O[8] = O[5];
    O[9] = A[15];
    O[10] = B[10];
    O[11] = B[11];
    O[12] = A[9];
    O[15] = O[1];

    if(O == 0) 
    begin 
      result_sign = 0;              // if the resultant value is 0, then we set the sign +ve
    end

  end

  assign o = {48'b0,result_sign,O[14:0]}; // get the final result

endmodule


module add16u_0MH(a, b, o);
  input [63:0] a, b;
  output [63:0] o;

  reg [63:0] A, B, O;

  reg sig_103, sig_104, sig_105;

  // Part-1:

  reg [63:0] tmp_res;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b


  // Part-2

  always @(a, b) 
  begin
    A = {49'b0,a[14:0]};                    // extract the magnitude from a
    B = {49'b0,b[14:0]};                    // extract the magnitude from b

    
    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
      begin
        result_sign = a_sign;
      end
    else if(B > A)                          // this means we perform b-a and set the sign
      begin
          A = -{49'b0,a[14:0]};
          result_sign = b_sign;             // result sign is 1 unless result is 0
      end
    else                                    // this means we perform a-b and set the sign
      begin
          B = -{49'b0,b[14:0]};
          result_sign = a_sign;            // result sign is 1 unless result is 0
      end
    

    // Following is what constitutes a+b

    O[4] = B[11];
    O[12] = 1'b0;
    O[6] = 1'b1;
    O[1] = 1'b0;
    sig_103 = A[14];
    sig_104 = A[15] | B[15];
    sig_105 = A[15] & B[15];
    O[5] = sig_104 & sig_103;
    O[15] = sig_104 ^ sig_103;
    O[16] = sig_105 | O[5];
    O[0] = B[2];
    O[2] = A[8];
    O[3] = A[7];
    O[7] = O[4];
    O[8] = B[11];
    O[9] = B[13];
    O[10] = A[8];
    O[11] = B[13];
    O[13] = B[10];
    O[14] = B[14];

    if(O == 0) 
    begin 
      result_sign = 0;              // if the resultant value is 0, then we set the sign +ve
    end

  end

  assign o = {48'b0,result_sign,O[14:0]}; // get the final result
   
endmodule



//======================= MULS ============================

module mul8_364(A, B, O);
  input [7:0] A;
  input [7:0] B;
  output [15:0] O;
  wire [2031:0] N;

  assign N[0] = A[0];
  assign N[1] = A[0];
  assign N[2] = A[1];
  assign N[3] = A[1];
  assign N[4] = A[2];
  assign N[5] = A[2];
  assign N[6] = A[3];
  assign N[7] = A[3];
  assign N[8] = A[4];
  assign N[9] = A[4];
  assign N[10] = A[5];
  assign N[11] = A[5];
  assign N[12] = A[6];
  assign N[13] = A[6];
  assign N[14] = A[7];
  assign N[15] = A[7];
  assign N[16] = B[0];
  assign N[17] = B[0];
  assign N[18] = B[1];
  assign N[19] = B[1];
  assign N[20] = B[2];
  assign N[21] = B[2];
  assign N[22] = B[3];
  assign N[23] = B[3];
  assign N[24] = B[4];
  assign N[25] = B[4];
  assign N[26] = B[5];
  assign N[27] = B[5];
  assign N[28] = B[6];
  assign N[29] = B[6];
  assign N[30] = B[7];
  assign N[31] = B[7];

  PDKGENAND2X1 n32(.A(N[0]), .B(N[16]), .Y(N[32]));
  PDKGENAND2X1 n48(.A(N[2]), .B(N[16]), .Y(N[48]));
  PDKGENAND2X1 n64(.A(N[4]), .B(N[16]), .Y(N[64]));
  PDKGENAND2X1 n82(.A(N[6]), .B(N[16]), .Y(N[82]));
  PDKGENAND2X1 n98(.A(N[8]), .B(N[16]), .Y(N[98]));
  PDKGENAND2X1 n114(.A(N[10]), .B(N[16]), .Y(N[114]));
  PDKGENAND2X1 n132(.A(N[12]), .B(N[16]), .Y(N[132]));
  PDKGENAND2X1 n148(.A(N[14]), .B(N[16]), .Y(N[148]));
  assign N[149] = N[148];
  PDKGENAND2X1 n164(.A(N[0]), .B(N[18]), .Y(N[164]));
  PDKGENBUFX2 n166(.A(N[149]), .Y(N[166]));
  assign N[167] = N[166];
  PDKGENAND2X1 n182(.A(N[2]), .B(N[18]), .Y(N[182]));
  PDKGENAND2X1 n198(.A(N[4]), .B(N[18]), .Y(N[198]));
  PDKGENAND2X1 n214(.A(N[6]), .B(N[18]), .Y(N[214]));
  PDKGENAND2X1 n232(.A(N[8]), .B(N[18]), .Y(N[232]));
  PDKGENAND2X1 n248(.A(N[10]), .B(N[18]), .Y(N[248]));
  PDKGENAND2X1 n264(.A(N[12]), .B(N[18]), .Y(N[264]));
  PDKGENAND2X1 n282(.A(N[14]), .B(N[18]), .Y(N[282]));
  PDKGENHAX1 n298(.A(N[48]), .B(N[164]), .YS(N[298]), .YC(N[299]));
  PDKGENHAX1 n314(.A(N[64]), .B(N[182]), .YS(N[314]), .YC(N[315]));
  PDKGENHAX1 n332(.A(N[82]), .B(N[198]), .YS(N[332]), .YC(N[333]));
  PDKGENHAX1 n348(.A(N[98]), .B(N[214]), .YS(N[348]), .YC(N[349]));
  PDKGENHAX1 n364(.A(N[114]), .B(N[232]), .YS(N[364]), .YC(N[365]));
  PDKGENHAX1 n382(.A(N[132]), .B(N[248]), .YS(N[382]), .YC(N[383]));
  PDKGENHAX1 n398(.A(N[167]), .B(N[264]), .YS(N[398]), .YC(N[399]));
  PDKGENAND2X1 n414(.A(N[0]), .B(N[20]), .Y(N[414]));
  PDKGENAND2X1 n432(.A(N[2]), .B(N[20]), .Y(N[432]));
  PDKGENAND2X1 n448(.A(N[4]), .B(N[20]), .Y(N[448]));
  PDKGENAND2X1 n464(.A(N[6]), .B(N[20]), .Y(N[464]));
  PDKGENAND2X1 n482(.A(N[8]), .B(N[20]), .Y(N[482]));
  PDKGENAND2X1 n498(.A(N[10]), .B(N[20]), .Y(N[498]));
  PDKGENAND2X1 n514(.A(N[12]), .B(N[20]), .Y(N[514]));
  PDKGENAND2X1 n532(.A(N[14]), .B(N[20]), .Y(N[532]));
  PDKGENFAX1 n548(.A(N[314]), .B(N[414]), .C(N[299]), .YS(N[548]), .YC(N[549]));
  PDKGENFAX1 n564(.A(N[332]), .B(N[432]), .C(N[315]), .YS(N[564]), .YC(N[565]));
  PDKGENFAX1 n582(.A(N[348]), .B(N[448]), .C(N[333]), .YS(N[582]), .YC(N[583]));
  PDKGENFAX1 n598(.A(N[364]), .B(N[464]), .C(N[349]), .YS(N[598]), .YC(N[599]));
  PDKGENFAX1 n614(.A(N[382]), .B(N[482]), .C(N[365]), .YS(N[614]), .YC(N[615]));
  PDKGENFAX1 n632(.A(N[398]), .B(N[498]), .C(N[383]), .YS(N[632]), .YC(N[633]));
  PDKGENFAX1 n648(.A(N[282]), .B(N[514]), .C(N[399]), .YS(N[648]), .YC(N[649]));
  PDKGENAND2X1 n664(.A(N[0]), .B(N[22]), .Y(N[664]));
  PDKGENAND2X1 n682(.A(N[2]), .B(N[22]), .Y(N[682]));
  PDKGENAND2X1 n698(.A(N[4]), .B(N[22]), .Y(N[698]));
  PDKGENAND2X1 n714(.A(N[6]), .B(N[22]), .Y(N[714]));
  PDKGENAND2X1 n732(.A(N[8]), .B(N[22]), .Y(N[732]));
  PDKGENAND2X1 n748(.A(N[10]), .B(N[22]), .Y(N[748]));
  PDKGENAND2X1 n764(.A(N[12]), .B(N[22]), .Y(N[764]));
  PDKGENAND2X1 n782(.A(N[14]), .B(N[22]), .Y(N[782]));
  PDKGENFAX1 n798(.A(N[564]), .B(N[664]), .C(N[549]), .YS(N[798]), .YC(N[799]));
  PDKGENFAX1 n814(.A(N[582]), .B(N[682]), .C(N[565]), .YS(N[814]), .YC(N[815]));
  PDKGENFAX1 n832(.A(N[598]), .B(N[698]), .C(N[583]), .YS(N[832]), .YC(N[833]));
  PDKGENFAX1 n848(.A(N[614]), .B(N[714]), .C(N[599]), .YS(N[848]), .YC(N[849]));
  PDKGENFAX1 n864(.A(N[632]), .B(N[732]), .C(N[615]), .YS(N[864]), .YC(N[865]));
  PDKGENFAX1 n882(.A(N[648]), .B(N[748]), .C(N[633]), .YS(N[882]), .YC(N[883]));
  PDKGENFAX1 n898(.A(N[532]), .B(N[764]), .C(N[649]), .YS(N[898]), .YC(N[899]));
  PDKGENAND2X1 n914(.A(N[0]), .B(N[24]), .Y(N[914]));
  PDKGENAND2X1 n932(.A(N[2]), .B(N[24]), .Y(N[932]));
  PDKGENAND2X1 n948(.A(N[4]), .B(N[24]), .Y(N[948]));
  PDKGENAND2X1 n964(.A(N[6]), .B(N[24]), .Y(N[964]));
  PDKGENAND2X1 n982(.A(N[8]), .B(N[24]), .Y(N[982]));
  PDKGENAND2X1 n998(.A(N[10]), .B(N[24]), .Y(N[998]));
  PDKGENAND2X1 n1014(.A(N[12]), .B(N[24]), .Y(N[1014]));
  PDKGENAND2X1 n1032(.A(N[14]), .B(N[24]), .Y(N[1032]));
  PDKGENFAX1 n1048(.A(N[814]), .B(N[914]), .C(N[799]), .YS(N[1048]), .YC(N[1049]));
  PDKGENFAX1 n1064(.A(N[832]), .B(N[932]), .C(N[815]), .YS(N[1064]), .YC(N[1065]));
  PDKGENFAX1 n1082(.A(N[848]), .B(N[948]), .C(N[833]), .YS(N[1082]), .YC(N[1083]));
  PDKGENFAX1 n1098(.A(N[864]), .B(N[964]), .C(N[849]), .YS(N[1098]), .YC(N[1099]));
  PDKGENFAX1 n1114(.A(N[882]), .B(N[982]), .C(N[865]), .YS(N[1114]), .YC(N[1115]));
  PDKGENFAX1 n1132(.A(N[898]), .B(N[998]), .C(N[883]), .YS(N[1132]), .YC(N[1133]));
  PDKGENFAX1 n1148(.A(N[782]), .B(N[1014]), .C(N[899]), .YS(N[1148]), .YC(N[1149]));
  PDKGENAND2X1 n1164(.A(N[0]), .B(N[26]), .Y(N[1164]));
  PDKGENAND2X1 n1182(.A(N[2]), .B(N[26]), .Y(N[1182]));
  PDKGENAND2X1 n1198(.A(N[4]), .B(N[26]), .Y(N[1198]));
  PDKGENAND2X1 n1214(.A(N[6]), .B(N[26]), .Y(N[1214]));
  PDKGENAND2X1 n1232(.A(N[8]), .B(N[26]), .Y(N[1232]));
  PDKGENAND2X1 n1248(.A(N[10]), .B(N[26]), .Y(N[1248]));
  PDKGENAND2X1 n1264(.A(N[12]), .B(N[26]), .Y(N[1264]));
  PDKGENAND2X1 n1282(.A(N[14]), .B(N[26]), .Y(N[1282]));
  PDKGENFAX1 n1298(.A(N[1064]), .B(N[1164]), .C(N[1049]), .YS(N[1298]), .YC(N[1299]));
  PDKGENFAX1 n1314(.A(N[1082]), .B(N[1182]), .C(N[1065]), .YS(N[1314]), .YC(N[1315]));
  PDKGENFAX1 n1332(.A(N[1098]), .B(N[1198]), .C(N[1083]), .YS(N[1332]), .YC(N[1333]));
  PDKGENFAX1 n1348(.A(N[1114]), .B(N[1214]), .C(N[1099]), .YS(N[1348]), .YC(N[1349]));
  PDKGENFAX1 n1364(.A(N[1132]), .B(N[1232]), .C(N[1115]), .YS(N[1364]), .YC(N[1365]));
  PDKGENFAX1 n1382(.A(N[1148]), .B(N[1248]), .C(N[1133]), .YS(N[1382]), .YC(N[1383]));
  PDKGENFAX1 n1398(.A(N[1032]), .B(N[1264]), .C(N[1149]), .YS(N[1398]), .YC(N[1399]));
  PDKGENAND2X1 n1414(.A(N[0]), .B(N[28]), .Y(N[1414]));
  PDKGENAND2X1 n1432(.A(N[2]), .B(N[28]), .Y(N[1432]));
  PDKGENAND2X1 n1448(.A(N[4]), .B(N[28]), .Y(N[1448]));
  PDKGENAND2X1 n1464(.A(N[6]), .B(N[28]), .Y(N[1464]));
  PDKGENAND2X1 n1482(.A(N[8]), .B(N[28]), .Y(N[1482]));
  PDKGENAND2X1 n1498(.A(N[10]), .B(N[28]), .Y(N[1498]));
  PDKGENAND2X1 n1514(.A(N[12]), .B(N[28]), .Y(N[1514]));
  PDKGENAND2X1 n1532(.A(N[14]), .B(N[28]), .Y(N[1532]));
  PDKGENFAX1 n1548(.A(N[1314]), .B(N[1414]), .C(N[1299]), .YS(N[1548]), .YC(N[1549]));
  PDKGENFAX1 n1564(.A(N[1332]), .B(N[1432]), .C(N[1315]), .YS(N[1564]), .YC(N[1565]));
  PDKGENFAX1 n1582(.A(N[1348]), .B(N[1448]), .C(N[1333]), .YS(N[1582]), .YC(N[1583]));
  PDKGENFAX1 n1598(.A(N[1364]), .B(N[1464]), .C(N[1349]), .YS(N[1598]), .YC(N[1599]));
  PDKGENFAX1 n1614(.A(N[1382]), .B(N[1482]), .C(N[1365]), .YS(N[1614]), .YC(N[1615]));
  PDKGENFAX1 n1632(.A(N[1398]), .B(N[1498]), .C(N[1383]), .YS(N[1632]), .YC(N[1633]));
  PDKGENFAX1 n1648(.A(N[1282]), .B(N[1514]), .C(N[1399]), .YS(N[1648]), .YC(N[1649]));
  PDKGENAND2X1 n1664(.A(N[0]), .B(N[30]), .Y(N[1664]));
  PDKGENAND2X1 n1682(.A(N[2]), .B(N[30]), .Y(N[1682]));
  PDKGENAND2X1 n1698(.A(N[4]), .B(N[30]), .Y(N[1698]));
  PDKGENAND2X1 n1714(.A(N[6]), .B(N[30]), .Y(N[1714]));
  PDKGENAND2X1 n1732(.A(N[8]), .B(N[30]), .Y(N[1732]));
  PDKGENAND2X1 n1748(.A(N[10]), .B(N[30]), .Y(N[1748]));
  PDKGENAND2X1 n1764(.A(N[12]), .B(N[30]), .Y(N[1764]));
  PDKGENAND2X1 n1782(.A(N[14]), .B(N[30]), .Y(N[1782]));
  PDKGENFAX1 n1798(.A(N[1564]), .B(N[1664]), .C(N[1549]), .YS(N[1798]), .YC(N[1799]));
  PDKGENFAX1 n1814(.A(N[1582]), .B(N[1682]), .C(N[1565]), .YS(N[1814]), .YC(N[1815]));
  PDKGENFAX1 n1832(.A(N[1598]), .B(N[1698]), .C(N[1583]), .YS(N[1832]), .YC(N[1833]));
  PDKGENFAX1 n1848(.A(N[1614]), .B(N[1714]), .C(N[1599]), .YS(N[1848]), .YC(N[1849]));
  PDKGENFAX1 n1864(.A(N[1632]), .B(N[1732]), .C(N[1615]), .YS(N[1864]), .YC(N[1865]));
  PDKGENFAX1 n1882(.A(N[1648]), .B(N[1748]), .C(N[1633]), .YS(N[1882]), .YC(N[1883]));
  PDKGENFAX1 n1898(.A(N[1532]), .B(N[1764]), .C(N[1649]), .YS(N[1898]), .YC(N[1899]));
  PDKGENHAX1 n1914(.A(N[1814]), .B(N[1799]), .YS(N[1914]), .YC(N[1915]));
  PDKGENFAX1 n1932(.A(N[1832]), .B(N[1815]), .C(N[1915]), .YS(N[1932]), .YC(N[1933]));
  PDKGENFAX1 n1948(.A(N[1848]), .B(N[1833]), .C(N[1933]), .YS(N[1948]), .YC(N[1949]));
  PDKGENFAX1 n1964(.A(N[1864]), .B(N[1849]), .C(N[1949]), .YS(N[1964]), .YC(N[1965]));
  PDKGENFAX1 n1982(.A(N[1882]), .B(N[1865]), .C(N[1965]), .YS(N[1982]), .YC(N[1983]));
  PDKGENFAX1 n1998(.A(N[1898]), .B(N[1883]), .C(N[1983]), .YS(N[1998]), .YC(N[1999]));
  PDKGENFAX1 n2014(.A(N[1782]), .B(N[1899]), .C(N[1999]), .YS(N[2014]), .YC(N[2015]));

  assign O[0] = N[32];
  assign O[1] = N[298];
  assign O[2] = N[548];
  assign O[3] = N[798];
  assign O[4] = N[1048];
  assign O[5] = N[1298];
  assign O[6] = N[1548];
  assign O[7] = N[1798];
  assign O[8] = N[1914];
  assign O[9] = N[1932];
  assign O[10] = N[1948];
  assign O[11] = N[1964];
  assign O[12] = N[1982];
  assign O[13] = N[1998];
  assign O[14] = N[2014];
  assign O[15] = N[2015];

endmodule


// ========================================================= //

module negate_16(in,out);
  parameter SIZE  = 64;
  input wire [SIZE-1:0] in;
  output wire [SIZE-1:0] out;
  wire result_sign;
  assign result_sign = (in[15:0] == 16'd0)?1'b0:~in[15];
  assign out = {in[31:16],result_sign,in[14:0]};
endmodule


module adder_16bit(a,b,o);                  //Modified by AWais
  parameter SIZE  = 64;
  input wire [SIZE-1:0] a,b;
  output wire [SIZE-1:0] o;
  reg [63:0] tmp_res;
  reg[63:0] a_signless, b_signless;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b
  
  always @(a, b) 
  begin
    a_signless = {49'b0,a[14:0]};           // extract the magnitude from a
    b_signless = {49'b0,b[14:0]};           // extract the magnitude from b

    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
    begin
      result_sign = a_sign;
    end
    else if(b_signless > a_signless)        // this means we perform b-a and set the sign
    begin
      a_signless = -{49'b0,a[14:0]};
      result_sign = b_sign;                 // result sign is 1 unless result is 0                              
    end
    else                                    // this means we perform a-b and set the sign
    begin
      b_signless = -{49'b0,b[14:0]};
      result_sign = a_sign;                 // result sign is 1 unless result is 0                    
    end

    tmp_res = a_signless + b_signless;      // here we perform the addition

    if(tmp_res == 0) 
    begin 
      result_sign = 0;                      // if the resultant value is 0, then we set the sign +ve
    end    
  end
  assign o = {48'b0,result_sign,tmp_res[14:0]}; // get the final result
endmodule

    
module mul16u_exact(a,b,o);
parameter SIZE  = 64;
input wire [SIZE-1:0] a,b;
output wire [SIZE-1:0] o;
 
wire res_sign;
wire[SIZE-1:0] tmp,a_signless,b_signless;

assign res_sign = a[15] ^ b[15];
assign a_signless = {49'b0,a[14:0]};
assign b_signless = {49'b0,b[14:0]};
assign tmp = a_signless*b_signless;

assign o = {48'b0,res_sign,tmp[19:10],tmp[9:5]};
endmodule



module register (input Reset,Clk, input [63:0] Din, output [63:0] Dout);
  reg [63:0] q;
  always @(posedge Clk)
    begin
      if(Reset == 1)
        q <= 0;
      else
        q <= Din;
      end
    assign Dout = q;
endmodule


//--------------------------Lookup table for RELU---------------------------------//
module RELU_1(Reset,clk,in_1,in_2,in_3,in_4,in_5,in_6,in_7,in_8,out_1,out_2,out_3,out_4,out_5,out_6,out_7,out_8);

parameter SIZE = 64;
input Reset,clk;

input[SIZE-1:0] in_1;
input[SIZE-1:0] in_2;
input[SIZE-1:0] in_3;
input[SIZE-1:0] in_4;
input[SIZE-1:0] in_5;
input[SIZE-1:0] in_6;
input[SIZE-1:0] in_7;
input[SIZE-1:0] in_8;

reg[SIZE-1:0] t_out_1;
reg[SIZE-1:0] t_out_2;
reg[SIZE-1:0] t_out_3;
reg[SIZE-1:0] t_out_4;
reg[SIZE-1:0] t_out_5;
reg[SIZE-1:0] t_out_6;
reg[SIZE-1:0] t_out_7;
reg[SIZE-1:0] t_out_8;


output[SIZE-1:0] out_1;
output[SIZE-1:0] out_2;
output[SIZE-1:0] out_3;
output[SIZE-1:0] out_4;
output[SIZE-1:0] out_5;
output[SIZE-1:0] out_6;
output[SIZE-1:0] out_7;
output[SIZE-1:0] out_8;

always @(in_1,in_2,in_3,in_4,in_5,in_6,in_7,in_8) begin
case({in_1,in_2,in_3,in_4,in_5,in_6,in_7,in_8})
{64'd7,64'd32820,64'd32811,64'd50,64'd32786,64'd32783,64'd39,64'd32775}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<={64'd7,64'd0,64'd0,64'd50,64'd0,64'd0,64'd39,64'd0};
{64'd7,64'd32815,64'd32811,64'd45,64'd32787,64'd32783,64'd37,64'd32774}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd7,64'd0,64'd0,64'd45,64'd0,64'd0,64'd37,64'd0};
{64'd20,64'd32769,64'd32781,64'd32769,64'd32781,64'd32772,64'd32769,64'd22}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd20,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd22};
{64'd32774,64'd32840,64'd32825,64'd69,64'd32785,64'd32779,64'd63,64'd32789}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd69,64'd0,64'd0,64'd63,64'd0};
{64'd0,64'd32820,64'd32814,64'd51,64'd32784,64'd32780,64'd45,64'd32782}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd51,64'd0,64'd0,64'd45,64'd0};
{64'd27,64'd32773,64'd32789,64'd1,64'd32787,64'd32773,64'd1,64'd32}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd27,64'd0,64'd0,64'd1,64'd0,64'd0,64'd1,64'd32};
{64'd0,64'd32820,64'd32810,64'd51,64'd32782,64'd32779,64'd44,64'd32784}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd51,64'd0,64'd0,64'd44,64'd0};
{64'd5,64'd32812,64'd32807,64'd42,64'd32783,64'd32779,64'd36,64'd32774}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd5,64'd0,64'd0,64'd42,64'd0,64'd0,64'd36,64'd0};
{64'd3,64'd32849,64'd32834,64'd81,64'd32795,64'd32795,64'd61,64'd32788}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd3,64'd0,64'd0,64'd81,64'd0,64'd0,64'd61,64'd0};
{64'd6,64'd32816,64'd32812,64'd44,64'd32788,64'd32778,64'd40,64'd32771}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd6,64'd0,64'd0,64'd44,64'd0,64'd0,64'd40,64'd0};
{64'd4,64'd32807,64'd32801,64'd38,64'd32780,64'd32777,64'd32,64'd32776}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd4,64'd0,64'd0,64'd38,64'd0,64'd0,64'd32,64'd0};
{64'd21,64'd32770,64'd32785,64'd32770,64'd32784,64'd32771,64'd0,64'd25}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd21,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd25};
{64'd25,64'd1,64'd32786,64'd32773,64'd32786,64'd32772,64'd32770,64'd32}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd25,64'd1,64'd0,64'd0,64'd0,64'd0,64'd0,64'd32};
{64'd32769,64'd32820,64'd32808,64'd52,64'd32782,64'd32780,64'd43,64'd32787}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd52,64'd0,64'd0,64'd43,64'd0};
{64'd32775,64'd32821,64'd32807,64'd53,64'd32777,64'd32776,64'd48,64'd32794}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd53,64'd0,64'd0,64'd48,64'd0};
{64'd32,64'd32777,64'd32793,64'd5,64'd32792,64'd32777,64'd2,64'd37}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd32,64'd0,64'd0,64'd5,64'd0,64'd0,64'd2,64'd37};
{64'd27,64'd32779,64'd32793,64'd7,64'd32789,64'd32775,64'd5,64'd31}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd27,64'd0,64'd0,64'd7,64'd0,64'd0,64'd5,64'd31};
{64'd9,64'd32813,64'd32809,64'd43,64'd32786,64'd32780,64'd35,64'd32771}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd9,64'd0,64'd0,64'd43,64'd0,64'd0,64'd35,64'd0};
{64'd27,64'd32775,64'd32791,64'd3,64'd32789,64'd32776,64'd1,64'd31}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd27,64'd0,64'd0,64'd3,64'd0,64'd0,64'd1,64'd31};
{64'd6,64'd32804,64'd32801,64'd34,64'd32780,64'd32774,64'd31,64'd32772}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd6,64'd0,64'd0,64'd34,64'd0,64'd0,64'd31,64'd0};
{64'd6,64'd32816,64'd32811,64'd46,64'd32788,64'd32783,64'd37,64'd32776}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd6,64'd0,64'd0,64'd46,64'd0,64'd0,64'd37,64'd0};
{64'd20,64'd32772,64'd32783,64'd2,64'd32781,64'd32772,64'd1,64'd21}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd20,64'd0,64'd0,64'd2,64'd0,64'd0,64'd1,64'd21};
{64'd26,64'd32773,64'd32789,64'd2,64'd32787,64'd32775,64'd1,64'd29}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd26,64'd0,64'd0,64'd2,64'd0,64'd0,64'd1,64'd29};
{64'd32773,64'd32825,64'd32809,64'd56,64'd32777,64'd32777,64'd48,64'd32791}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd56,64'd0,64'd0,64'd48,64'd0};
{64'd32770,64'd32806,64'd32793,64'd38,64'd32773,64'd32775,64'd32,64'd32786}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd38,64'd0,64'd0,64'd32,64'd0};
{64'd8,64'd32805,64'd32802,64'd37,64'd32784,64'd32781,64'd27,64'd32773}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd8,64'd0,64'd0,64'd37,64'd0,64'd0,64'd27,64'd0};
{64'd32773,64'd32837,64'd32821,64'd67,64'd32784,64'd32781,64'd60,64'd32787}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd67,64'd0,64'd0,64'd60,64'd0};
{64'd26,64'd32772,64'd32787,64'd0,64'd32785,64'd32774,64'd0,64'd30}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd26,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd30};
{64'd30,64'd32775,64'd32795,64'd3,64'd32793,64'd32777,64'd2,64'd37}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd30,64'd0,64'd0,64'd3,64'd0,64'd0,64'd2,64'd37};
{64'd3,64'd32848,64'd32834,64'd79,64'd32792,64'd32790,64'd64,64'd32784}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd3,64'd0,64'd0,64'd79,64'd0,64'd0,64'd64,64'd0};
{64'd32774,64'd32830,64'd32820,64'd58,64'd32785,64'd32778,64'd56,64'd32787}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd58,64'd0,64'd0,64'd56,64'd0};
{64'd32775,64'd32832,64'd32821,64'd60,64'd32784,64'd32778,64'd58,64'd32787}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd60,64'd0,64'd0,64'd58,64'd0};
{64'd32769,64'd32803,64'd32795,64'd33,64'd32775,64'd32773,64'd31,64'd32781}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd33,64'd0,64'd0,64'd31,64'd0};
{64'd30,64'd32775,64'd32796,64'd3,64'd32794,64'd32778,64'd1,64'd38}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd30,64'd0,64'd0,64'd3,64'd0,64'd0,64'd1,64'd38};
{64'd22,64'd32771,64'd32785,64'd0,64'd32784,64'd32774,64'd0,64'd24}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd22,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd24};
{64'd0,64'd32818,64'd32811,64'd49,64'd32783,64'd32779,64'd44,64'd32782}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd49,64'd0,64'd0,64'd44,64'd0};     
{64'd23,64'd32769,64'd32783,64'd32770,64'd32783,64'd32772,64'd32769,64'd26}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd23,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd26};
{64'd11,64'd32820,64'd32814,64'd50,64'd32790,64'd32785,64'd38,64'd32770}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<={64'd11,64'd0,64'd0,64'd50,64'd0,64'd0,64'd38,64'd0};
{64'd24,64'd32772,64'd32788,64'd0,64'd32787,64'd32774,64'd0,64'd27}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd24,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd27};
{64'd19,64'd2,64'd32778,64'd32772,64'd32778,64'd32770,64'd32770,64'd20}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd19,64'd2,64'd0,64'd0,64'd0,64'd0,64'd0,64'd20};
{64'd1,64'd32820,64'd32808,64'd51,64'd32782,64'd32782,64'd39,64'd32784}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd1,64'd0,64'd0,64'd51,64'd0,64'd0,64'd39,64'd0};
{64'd3,64'd32816,64'd32803,64'd48,64'd32779,64'd32781,64'd35,64'd32783}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd3,64'd0,64'd0,64'd48,64'd0,64'd0,64'd35,64'd0};
{64'd11,64'd32825,64'd32821,64'd56,64'd32793,64'd32788,64'd42,64'd32769}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<={64'd11,64'd0,64'd0,64'd56,64'd0,64'd0,64'd42,64'd0};
{64'd7,64'd32835,64'd32830,64'd67,64'd32797,64'd32791,64'd53,64'd32778}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd7,64'd0,64'd0,64'd67,64'd0,64'd0,64'd53,64'd0};
{64'd9,64'd32800,64'd32798,64'd32,64'd32780,64'd32777,64'd24,64'd32771}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd9,64'd0,64'd0,64'd32,64'd0,64'd0,64'd24,64'd0};
 default: {t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<={512'd0};

endcase
end 

assign out_1 = t_out_1;
assign out_2 = t_out_2;
assign out_3 = t_out_3;
assign out_4 = t_out_4;
assign out_5 = t_out_5;
assign out_6 = t_out_6;
assign out_7 = t_out_7;
assign out_8 = t_out_8;
endmodule


//--------------------------Lookup table for RELU---------------------------------//
module RELU_2(Reset, clk, l2_in_1,l2_in_2,l2_in_3,l2_in_4,l2_in_5,l2_in_6, l2_out_1,l2_out_2,l2_out_3,l2_out_4,l2_out_5,l2_out_6);

parameter SIZE = 64;
input Reset, clk;

input[SIZE-1 : 0] l2_in_1;
input[SIZE-1 : 0] l2_in_2;
input[SIZE-1 : 0] l2_in_3;
input[SIZE-1 : 0] l2_in_4;
input[SIZE-1 : 0] l2_in_5;
input[SIZE-1 : 0] l2_in_6;

reg[SIZE-1 : 0] l2_t_out_1;
reg[SIZE-1 : 0] l2_t_out_2;
reg[SIZE-1 : 0] l2_t_out_3;
reg[SIZE-1 : 0] l2_t_out_4;
reg[SIZE-1 : 0] l2_t_out_5;
reg[SIZE-1 : 0] l2_t_out_6;

output[SIZE-1 : 0] l2_out_1;
output[SIZE-1 : 0] l2_out_2;
output[SIZE-1 : 0] l2_out_3;
output[SIZE-1 : 0] l2_out_4;
output[SIZE-1 : 0] l2_out_5;
output[SIZE-1 : 0] l2_out_6;

always @(l2_in_1,l2_in_2,l2_in_3,l2_in_4,l2_in_5,l2_in_6) begin
case({l2_in_1,l2_in_2,l2_in_3,l2_in_4,l2_in_5,l2_in_6})
{64'd63, 64'd24, 64'd51, 64'd48, 64'd58, 64'd32777} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd63, 64'd24, 64'd51, 64'd48, 64'd58, 64'd0};
{64'd58, 64'd21, 64'd47, 64'd45, 64'd54, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd58, 64'd21, 64'd47, 64'd45, 64'd54, 64'd0};
{64'd39, 64'd32791, 64'd32784, 64'd0, 64'd32772, 64'd32779} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd39, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd86, 64'd52, 64'd79, 64'd62, 64'd86, 64'd32783} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd86, 64'd52, 64'd79, 64'd62, 64'd86, 64'd0};
{64'd62, 64'd33, 64'd55, 64'd49, 64'd64, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd62, 64'd33, 64'd55, 64'd49, 64'd64, 64'd0};
{64'd55, 64'd32792, 64'd32789, 64'd32777, 64'd32776, 64'd32782} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd55, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd62, 64'd32, 64'd54, 64'd48, 64'd63, 64'd32777} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd62, 64'd32, 64'd54, 64'd48, 64'd63, 64'd0};
{64'd55, 64'd20, 64'd45, 64'd44, 64'd52, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd55, 64'd20, 64'd45, 64'd44, 64'd52, 64'd0};
{64'd96, 64'd56, 64'd82, 64'd66, 64'd91, 64'd32776} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd96, 64'd56, 64'd82, 64'd66, 64'd91, 64'd0};
{64'd58, 64'd22, 64'd50, 64'd45, 64'd55, 64'd32780} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd58, 64'd22, 64'd50, 64'd45, 64'd55, 64'd0};
{64'd48, 64'd17, 64'd39, 64'd41, 64'd48, 64'd32776} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd48, 64'd17, 64'd39, 64'd41, 64'd48, 64'd0};
{64'd43, 64'd32790, 64'd32786, 64'd32771, 64'd32772, 64'd32780} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd43, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd54, 64'd32790, 64'd32790, 64'd32777, 64'd32776, 64'd32781} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd54, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd62, 64'd33, 64'd53, 64'd49, 64'd64, 64'd32775} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd62, 64'd33, 64'd53, 64'd49, 64'd64, 64'd0};
{64'd66, 64'd36, 64'd59, 64'd51, 64'd68, 64'd32779} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd66, 64'd36, 64'd59, 64'd51, 64'd68, 64'd0};
{64'd70, 64'd32792, 64'd32787, 64'd32777, 64'd32775, 64'd32785} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd70, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd60, 64'd32787, 64'd32782, 64'd32773, 64'd32769, 64'd32783} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd60, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd57, 64'd16, 64'd45, 64'd44, 64'd50, 64'd32779} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd57, 64'd16, 64'd45, 64'd44, 64'd50, 64'd0};
{64'd55, 64'd32792, 64'd32787, 64'd32775, 64'd32774, 64'd32782} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd55, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd45, 64'd12, 64'd36, 64'd38, 64'd44, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd45, 64'd12, 64'd36, 64'd38, 64'd44, 64'd0};
{64'd58, 64'd22, 64'd47, 64'd45, 64'd54, 64'd32776} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd58, 64'd22, 64'd47, 64'd45, 64'd54, 64'd0};
{64'd38, 64'd32791, 64'd32782, 64'd1, 64'd32770, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd38, 64'd0, 64'd0, 64'd1, 64'd0, 64'd0};
{64'd52, 64'd32792, 64'd32786, 64'd32774, 64'd32774, 64'd32782} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd52, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd68, 64'd38, 64'd60, 64'd52, 64'd70, 64'd32777} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd68, 64'd38, 64'd60, 64'd52, 64'd70, 64'd0};
{64'd45, 64'd20, 64'd38, 64'd40, 64'd49, 64'd32774} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd45, 64'd20, 64'd38, 64'd40, 64'd49, 64'd0};
{64'd48, 64'd10, 64'd34, 64'd40, 64'd43, 64'd32776} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd48, 64'd10, 64'd34, 64'd40, 64'd43, 64'd0};
{64'd83, 64'd49, 64'd76, 64'd60, 64'd82, 64'd32781} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd83, 64'd49, 64'd76, 64'd60, 64'd82, 64'd0};
{64'd52, 64'd32793, 64'd32788, 64'd32775, 64'd32775, 64'd32783} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd52, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd66, 64'd32792, 64'd32788, 64'd32779, 64'd32776, 64'd32784} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd66, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd97, 64'd57, 64'd86, 64'd67, 64'd92, 64'd32780} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd97, 64'd57, 64'd86, 64'd67, 64'd92, 64'd0};
{64'd74, 64'd42, 64'd68, 64'd55, 64'd75, 64'd32782} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd74, 64'd42, 64'd68, 64'd55, 64'd75, 64'd0};
{64'd76, 64'd44, 64'd71, 64'd57, 64'd77, 64'd32783} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd76, 64'd44, 64'd71, 64'd57, 64'd77, 64'd0};
{64'd40, 64'd16, 64'd34, 64'd37, 64'd45, 64'd32776} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd40, 64'd16, 64'd34, 64'd37, 64'd45, 64'd0};
{64'd66, 64'd32791, 64'd32790, 64'd32780, 64'd32778, 64'd32783} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd66, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd42, 64'd32792, 64'd32786, 64'd32770, 64'd32772, 64'd32780} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd42, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd60, 64'd31, 64'd53, 64'd47, 64'd62, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd60, 64'd31, 64'd53, 64'd47, 64'd62, 64'd0};     
{64'd45, 64'd32792, 64'd32786, 64'd32772, 64'd32773, 64'd32781} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd45, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd66, 64'd20, 64'd52, 64'd48, 64'd56, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd66, 64'd20, 64'd52, 64'd48, 64'd56, 64'd0};
{64'd47, 64'd32792, 64'd32787, 64'd32772, 64'd32774, 64'd32782} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd47, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd35, 64'd32790, 64'd32783, 64'd1, 64'd32771, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd35, 64'd0, 64'd0, 64'd1, 64'd0, 64'd0};
{64'd59, 64'd30, 64'd49, 64'd47, 64'd60, 64'd32773} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd59, 64'd30, 64'd49, 64'd47, 64'd60, 64'd0};
{64'd57, 64'd26, 64'd45, 64'd44, 64'd56, 64'd32772} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd57, 64'd26, 64'd45, 64'd44, 64'd56, 64'd0};
{64'd73, 64'd26, 64'd58, 64'd52, 64'd62, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd73, 64'd26, 64'd58, 64'd52, 64'd62, 64'd0};
{64'd84, 64'd40, 64'd71, 64'd59, 64'd76, 64'd32780} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd84, 64'd40, 64'd71, 64'd59, 64'd76, 64'd0};
{64'd44, 64'd5, 64'd30, 64'd37, 64'd38, 64'd32775} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd44, 64'd5, 64'd30, 64'd37, 64'd38, 64'd0};
default :  {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {512'd0};

endcase
end 

assign l2_out_1 = l2_t_out_1;
assign l2_out_2 = l2_t_out_2;
assign l2_out_3 = l2_t_out_3;
assign l2_out_4 = l2_t_out_4;
assign l2_out_5 = l2_t_out_5;
assign l2_out_6 = l2_t_out_6;

endmodule


//--------------------------Lookup table for Softmax---------------------------------//
module SOFTMAX(Reset, clk, l3_in_1, l3_in_2, l3_in_3, l3_out_1, l3_out_2, l3_out_3);

parameter SIZE = 64;
input Reset, clk;

input[SIZE-1 : 0] l3_in_1;
input[SIZE-1 : 0] l3_in_2;
input[SIZE-1 : 0] l3_in_3;

reg[SIZE-1 : 0] l3_t_out_1;
reg[SIZE-1 : 0] l3_t_out_2;
reg[SIZE-1 : 0] l3_t_out_3;

output[SIZE-1 : 0] l3_out_1;
output[SIZE-1 : 0] l3_out_2;
output[SIZE-1 : 0] l3_out_3;

always @(l3_in_1, l3_in_2, l3_in_3) begin
case({l3_in_1, l3_in_2, l3_in_3})
{64'd32959, 64'd62, 64'd9}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8};    
{64'd32942, 64'd59, 64'd7}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd11, 64'd32772, 64'd32804}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd33079, 64'd102,64'd38}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32984, 64'd74, 64'd18}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd7, 64'd32776, 64'd32808}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32980, 64'd72, 64'd17}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32933, 64'd55, 64'd4}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd33100, 64'd106, 64'd40}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32948, 64'd59, 64'd7}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd32915, 64'd52, 64'd2}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd10, 64'd32773, 64'd32805}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd7, 64'd32775, 64'd32807}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32982, 64'd74, 64'd18}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32999, 64'd78, 64'd21}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd3, 64'd32779, 64'd32811}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd5, 64'd32777, 64'd32809}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32926, 64'd51, 64'd1}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd7, 64'd32776, 64'd32808}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32896, 64'd45, 64'd32771}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd32944, 64'd60, 64'd8}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd12, 64'd32772, 64'd32804}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd7, 64'd32775, 64'd32807}:  {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd33007, 64'd81, 64'd23}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32917, 64'd54, 64'd4}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd32892, 64'd41, 64'd32775}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd33064, 64'd96, 64'd34}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd7, 64'd32775, 64'd32807}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd4, 64'd32778, 64'd32810}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd33108, 64'd108, 64'd42}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd33030, 64'd85, 64'd25}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd33042, 64'd89, 64'd29}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32899, 64'd48, 64'd0}:{l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd4, 64'd32778, 64'd32810}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd10, 64'd32773, 64'd32805}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32974, 64'd69, 64'd14}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd9, 64'd32773, 64'd32805}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32951, 64'd57, 64'd4}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <={64'd0, 64'd23, 64'd8}; 
{64'd8, 64'd32774, 64'd32806}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <={64'd13, 64'd13, 64'd4}; 
{64'd12, 64'd32771, 64'd32803}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <={64'd13, 64'd13, 64'd4}; 
{64'd32965, 64'd68, 64'd14}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32947, 64'd63, 64'd10}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd32980, 64'd66, 64'd11}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd33039, 64'd86, 64'd26}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32870, 64'd35, 64'd32779}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 

default: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {512'd0};

endcase
end 

assign l3_out_1 = l3_t_out_1;
assign l3_out_2 = l3_t_out_2;
assign l3_out_3 = l3_t_out_3;

endmodule