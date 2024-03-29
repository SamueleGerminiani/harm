
// Generated from spot.g4 by ANTLR 4.12.0


#include "spotLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct SpotLexerStaticData final {
  SpotLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SpotLexerStaticData(const SpotLexerStaticData&) = delete;
  SpotLexerStaticData(SpotLexerStaticData&&) = delete;
  SpotLexerStaticData& operator=(const SpotLexerStaticData&) = delete;
  SpotLexerStaticData& operator=(SpotLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag spotlexerLexerOnceFlag;
SpotLexerStaticData *spotlexerLexerStaticData = nullptr;

void spotlexerLexerInitialize() {
  assert(spotlexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<SpotLexerStaticData>(
    std::vector<std::string>{
      "PLACEHOLDER", "DT_AND", "DT_NEXT", "DT_NEXT_AND", "DT_NCREPS", "SEP", 
      "FUNCTION", "EVENTUALLY", "ALWAYS", "NEXT", "UNTIL", "RELEASE", "DOTS", 
      "IMPL", "IMPLO", "IFF", "XOR", "SEREIMPL", "SEREIMPLO", "ASS", "DELAY", 
      "SCOL", "COL", "DOLLAR", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", "LOGIC_VARIABLE", 
      "CONST_SUFFIX", "NUMERIC_CONSTANT", "NUMERIC_VARIABLE", "LCURLY", 
      "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "VARIABLE", 
      "VALID_ID_START", "VALID_ID_CHAR", "SINTEGER", "UINTEGER", "FLOAT", 
      "VERILOG_BINARY", "GCC_BINARY", "HEX", "START_VAR", "END_VAR", "PLUS", 
      "MINUS", "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "BAND", 
      "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "", "'..&&..'", "", "", "", "", "'$stable'", "'F'", "'G'", "'X'", 
      "'U'", "'R'", "'..'", "'->'", "'=>'", "'<->'", "'xor'", "", "", "'='", 
      "'##'", "';'", "':'", "'$'", "", "", "", "", "", "", "'{'", "'}'", 
      "'['", "']'", "'('", "')'", "", "", "", "", "", "", "'+'", "'-'", 
      "'*'", "'/'", "'>'", "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", 
      "'|'", "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'"
    },
    std::vector<std::string>{
      "", "PLACEHOLDER", "DT_AND", "DT_NEXT", "DT_NEXT_AND", "DT_NCREPS", 
      "SEP", "FUNCTION", "EVENTUALLY", "ALWAYS", "NEXT", "UNTIL", "RELEASE", 
      "DOTS", "IMPL", "IMPLO", "IFF", "XOR", "SEREIMPL", "SEREIMPLO", "ASS", 
      "DELAY", "SCOL", "COL", "DOLLAR", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", 
      "LOGIC_VARIABLE", "CONST_SUFFIX", "NUMERIC_CONSTANT", "NUMERIC_VARIABLE", 
      "LCURLY", "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "SINTEGER", 
      "UINTEGER", "FLOAT", "VERILOG_BINARY", "GCC_BINARY", "HEX", "PLUS", 
      "MINUS", "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "BAND", 
      "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,62,450,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,
  	7,49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,
  	7,56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,
  	7,63,2,64,7,64,2,65,7,65,2,66,7,66,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,
  	5,3,5,180,8,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,
  	1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,13,1,13,1,13,1,14,1,14,1,14,1,15,
  	1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,17,
  	3,17,224,8,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,233,8,18,1,19,1,
  	19,1,20,1,20,1,20,1,21,1,21,1,22,1,22,1,23,1,23,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,257,8,24,1,25,1,25,1,25,1,25,1,
  	25,1,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,
  	26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,3,27,285,8,27,1,28,1,28,1,29,1,
  	29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,30,1,30,1,
  	31,1,31,1,32,1,32,1,33,1,33,1,34,1,34,1,35,1,35,1,36,1,36,5,36,316,8,
  	36,10,36,12,36,319,9,36,1,37,3,37,322,8,37,1,38,3,38,325,8,38,1,39,1,
  	39,4,39,329,8,39,11,39,12,39,330,1,40,4,40,334,8,40,11,40,12,40,335,1,
  	41,3,41,339,8,41,1,41,4,41,342,8,41,11,41,12,41,343,1,41,1,41,4,41,348,
  	8,41,11,41,12,41,349,1,41,3,41,353,8,41,1,41,4,41,356,8,41,11,41,12,41,
  	357,1,41,1,41,3,41,362,8,41,1,42,1,42,1,42,4,42,367,8,42,11,42,12,42,
  	368,1,43,1,43,1,43,1,43,4,43,375,8,43,11,43,12,43,376,1,44,1,44,1,44,
  	1,44,4,44,383,8,44,11,44,12,44,384,1,44,1,44,1,44,1,44,4,44,391,8,44,
  	11,44,12,44,392,3,44,395,8,44,1,45,1,45,1,46,1,46,1,47,1,47,1,48,1,48,
  	1,49,1,49,1,50,1,50,1,51,1,51,1,52,1,52,1,52,1,53,1,53,1,54,1,54,1,54,
  	1,55,1,55,1,55,1,56,1,56,1,56,1,57,1,57,1,58,1,58,1,59,1,59,1,60,1,60,
  	1,61,1,61,1,61,1,62,1,62,1,62,1,63,1,63,1,63,1,64,1,64,1,64,1,65,1,65,
  	1,66,1,66,1,66,1,66,0,0,67,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,
  	10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,
  	43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,
  	33,67,34,69,35,71,36,73,0,75,0,77,0,79,37,81,38,83,39,85,40,87,41,89,
  	42,91,0,93,0,95,43,97,44,99,45,101,46,103,47,105,48,107,49,109,50,111,
  	51,113,52,115,53,117,54,119,55,121,56,123,57,125,58,127,59,129,60,131,
  	61,133,62,1,0,5,3,0,65,90,95,95,97,122,8,0,40,41,46,46,48,58,65,91,93,
  	93,95,95,97,123,125,125,2,0,48,57,97,102,2,0,48,57,65,70,3,0,9,10,13,
  	13,32,32,463,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,
  	0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,
  	0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,
  	1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,
  	0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,
  	0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,
  	1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,79,1,0,
  	0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,0,0,
  	0,95,1,0,0,0,0,97,1,0,0,0,0,99,1,0,0,0,0,101,1,0,0,0,0,103,1,0,0,0,0,
  	105,1,0,0,0,0,107,1,0,0,0,0,109,1,0,0,0,0,111,1,0,0,0,0,113,1,0,0,0,0,
  	115,1,0,0,0,0,117,1,0,0,0,0,119,1,0,0,0,0,121,1,0,0,0,0,123,1,0,0,0,0,
  	125,1,0,0,0,0,127,1,0,0,0,0,129,1,0,0,0,0,131,1,0,0,0,0,133,1,0,0,0,1,
  	135,1,0,0,0,3,138,1,0,0,0,5,145,1,0,0,0,7,154,1,0,0,0,9,163,1,0,0,0,11,
  	179,1,0,0,0,13,181,1,0,0,0,15,189,1,0,0,0,17,191,1,0,0,0,19,193,1,0,0,
  	0,21,195,1,0,0,0,23,197,1,0,0,0,25,199,1,0,0,0,27,202,1,0,0,0,29,205,
  	1,0,0,0,31,208,1,0,0,0,33,212,1,0,0,0,35,223,1,0,0,0,37,232,1,0,0,0,39,
  	234,1,0,0,0,41,236,1,0,0,0,43,239,1,0,0,0,45,241,1,0,0,0,47,243,1,0,0,
  	0,49,256,1,0,0,0,51,258,1,0,0,0,53,268,1,0,0,0,55,284,1,0,0,0,57,286,
  	1,0,0,0,59,288,1,0,0,0,61,301,1,0,0,0,63,303,1,0,0,0,65,305,1,0,0,0,67,
  	307,1,0,0,0,69,309,1,0,0,0,71,311,1,0,0,0,73,313,1,0,0,0,75,321,1,0,0,
  	0,77,324,1,0,0,0,79,326,1,0,0,0,81,333,1,0,0,0,83,361,1,0,0,0,85,363,
  	1,0,0,0,87,370,1,0,0,0,89,394,1,0,0,0,91,396,1,0,0,0,93,398,1,0,0,0,95,
  	400,1,0,0,0,97,402,1,0,0,0,99,404,1,0,0,0,101,406,1,0,0,0,103,408,1,0,
  	0,0,105,410,1,0,0,0,107,413,1,0,0,0,109,415,1,0,0,0,111,418,1,0,0,0,113,
  	421,1,0,0,0,115,424,1,0,0,0,117,426,1,0,0,0,119,428,1,0,0,0,121,430,1,
  	0,0,0,123,432,1,0,0,0,125,435,1,0,0,0,127,438,1,0,0,0,129,441,1,0,0,0,
  	131,444,1,0,0,0,133,446,1,0,0,0,135,136,5,80,0,0,136,137,3,81,40,0,137,
  	2,1,0,0,0,138,139,5,46,0,0,139,140,5,46,0,0,140,141,5,38,0,0,141,142,
  	5,38,0,0,142,143,5,46,0,0,143,144,5,46,0,0,144,4,1,0,0,0,145,146,5,46,
  	0,0,146,147,5,46,0,0,147,148,5,35,0,0,148,149,5,35,0,0,149,150,1,0,0,
  	0,150,151,3,81,40,0,151,152,5,46,0,0,152,153,5,46,0,0,153,6,1,0,0,0,154,
  	155,5,46,0,0,155,156,5,46,0,0,156,157,5,35,0,0,157,158,1,0,0,0,158,159,
  	3,81,40,0,159,160,5,38,0,0,160,161,5,46,0,0,161,162,5,46,0,0,162,8,1,
  	0,0,0,163,164,5,46,0,0,164,165,5,46,0,0,165,166,5,91,0,0,166,167,5,45,
  	0,0,167,168,5,62,0,0,168,169,1,0,0,0,169,170,3,81,40,0,170,171,5,93,0,
  	0,171,172,3,11,5,0,172,173,5,46,0,0,173,174,5,46,0,0,174,10,1,0,0,0,175,
  	176,5,64,0,0,176,180,5,58,0,0,177,178,5,64,0,0,178,180,5,59,0,0,179,175,
  	1,0,0,0,179,177,1,0,0,0,180,12,1,0,0,0,181,182,5,36,0,0,182,183,5,115,
  	0,0,183,184,5,116,0,0,184,185,5,97,0,0,185,186,5,98,0,0,186,187,5,108,
  	0,0,187,188,5,101,0,0,188,14,1,0,0,0,189,190,5,70,0,0,190,16,1,0,0,0,
  	191,192,5,71,0,0,192,18,1,0,0,0,193,194,5,88,0,0,194,20,1,0,0,0,195,196,
  	5,85,0,0,196,22,1,0,0,0,197,198,5,82,0,0,198,24,1,0,0,0,199,200,5,46,
  	0,0,200,201,5,46,0,0,201,26,1,0,0,0,202,203,5,45,0,0,203,204,5,62,0,0,
  	204,28,1,0,0,0,205,206,5,61,0,0,206,207,5,62,0,0,207,30,1,0,0,0,208,209,
  	5,60,0,0,209,210,5,45,0,0,210,211,5,62,0,0,211,32,1,0,0,0,212,213,5,120,
  	0,0,213,214,5,111,0,0,214,215,5,114,0,0,215,34,1,0,0,0,216,217,5,124,
  	0,0,217,218,5,45,0,0,218,224,5,62,0,0,219,220,5,91,0,0,220,221,5,93,0,
  	0,221,222,5,45,0,0,222,224,5,62,0,0,223,216,1,0,0,0,223,219,1,0,0,0,224,
  	36,1,0,0,0,225,226,5,124,0,0,226,227,5,61,0,0,227,233,5,62,0,0,228,229,
  	5,91,0,0,229,230,5,93,0,0,230,231,5,61,0,0,231,233,5,62,0,0,232,225,1,
  	0,0,0,232,228,1,0,0,0,233,38,1,0,0,0,234,235,5,61,0,0,235,40,1,0,0,0,
  	236,237,5,35,0,0,237,238,5,35,0,0,238,42,1,0,0,0,239,240,5,59,0,0,240,
  	44,1,0,0,0,241,242,5,58,0,0,242,46,1,0,0,0,243,244,5,36,0,0,244,48,1,
  	0,0,0,245,246,5,64,0,0,246,247,5,116,0,0,247,248,5,114,0,0,248,249,5,
  	117,0,0,249,257,5,101,0,0,250,251,5,64,0,0,251,252,5,102,0,0,252,253,
  	5,97,0,0,253,254,5,108,0,0,254,255,5,115,0,0,255,257,5,101,0,0,256,245,
  	1,0,0,0,256,250,1,0,0,0,257,50,1,0,0,0,258,259,3,91,45,0,259,260,3,73,
  	36,0,260,261,5,44,0,0,261,262,5,98,0,0,262,263,5,111,0,0,263,264,5,111,
  	0,0,264,265,5,108,0,0,265,266,1,0,0,0,266,267,3,93,46,0,267,52,1,0,0,
  	0,268,269,3,91,45,0,269,270,3,73,36,0,270,271,5,44,0,0,271,272,5,108,
  	0,0,272,273,5,111,0,0,273,274,5,103,0,0,274,275,5,105,0,0,275,276,5,99,
  	0,0,276,277,1,0,0,0,277,278,3,93,46,0,278,54,1,0,0,0,279,280,5,108,0,
  	0,280,285,5,108,0,0,281,282,5,117,0,0,282,283,5,108,0,0,283,285,5,108,
  	0,0,284,279,1,0,0,0,284,281,1,0,0,0,285,56,1,0,0,0,286,287,3,83,41,0,
  	287,58,1,0,0,0,288,289,3,91,45,0,289,290,3,73,36,0,290,291,5,44,0,0,291,
  	292,5,110,0,0,292,293,5,117,0,0,293,294,5,109,0,0,294,295,5,101,0,0,295,
  	296,5,114,0,0,296,297,5,105,0,0,297,298,5,99,0,0,298,299,1,0,0,0,299,
  	300,3,93,46,0,300,60,1,0,0,0,301,302,5,123,0,0,302,62,1,0,0,0,303,304,
  	5,125,0,0,304,64,1,0,0,0,305,306,5,91,0,0,306,66,1,0,0,0,307,308,5,93,
  	0,0,308,68,1,0,0,0,309,310,5,40,0,0,310,70,1,0,0,0,311,312,5,41,0,0,312,
  	72,1,0,0,0,313,317,3,75,37,0,314,316,3,77,38,0,315,314,1,0,0,0,316,319,
  	1,0,0,0,317,315,1,0,0,0,317,318,1,0,0,0,318,74,1,0,0,0,319,317,1,0,0,
  	0,320,322,7,0,0,0,321,320,1,0,0,0,322,76,1,0,0,0,323,325,7,1,0,0,324,
  	323,1,0,0,0,325,78,1,0,0,0,326,328,5,45,0,0,327,329,2,48,57,0,328,327,
  	1,0,0,0,329,330,1,0,0,0,330,328,1,0,0,0,330,331,1,0,0,0,331,80,1,0,0,
  	0,332,334,2,48,57,0,333,332,1,0,0,0,334,335,1,0,0,0,335,333,1,0,0,0,335,
  	336,1,0,0,0,336,82,1,0,0,0,337,339,5,45,0,0,338,337,1,0,0,0,338,339,1,
  	0,0,0,339,341,1,0,0,0,340,342,2,48,57,0,341,340,1,0,0,0,342,343,1,0,0,
  	0,343,341,1,0,0,0,343,344,1,0,0,0,344,345,1,0,0,0,345,347,5,46,0,0,346,
  	348,2,48,57,0,347,346,1,0,0,0,348,349,1,0,0,0,349,347,1,0,0,0,349,350,
  	1,0,0,0,350,362,1,0,0,0,351,353,5,45,0,0,352,351,1,0,0,0,352,353,1,0,
  	0,0,353,355,1,0,0,0,354,356,2,48,57,0,355,354,1,0,0,0,356,357,1,0,0,0,
  	357,355,1,0,0,0,357,358,1,0,0,0,358,359,1,0,0,0,359,360,5,46,0,0,360,
  	362,5,102,0,0,361,338,1,0,0,0,361,352,1,0,0,0,362,84,1,0,0,0,363,364,
  	5,39,0,0,364,366,5,98,0,0,365,367,2,48,49,0,366,365,1,0,0,0,367,368,1,
  	0,0,0,368,366,1,0,0,0,368,369,1,0,0,0,369,86,1,0,0,0,370,371,5,48,0,0,
  	371,372,5,98,0,0,372,374,1,0,0,0,373,375,2,48,49,0,374,373,1,0,0,0,375,
  	376,1,0,0,0,376,374,1,0,0,0,376,377,1,0,0,0,377,88,1,0,0,0,378,379,5,
  	48,0,0,379,380,5,120,0,0,380,382,1,0,0,0,381,383,7,2,0,0,382,381,1,0,
  	0,0,383,384,1,0,0,0,384,382,1,0,0,0,384,385,1,0,0,0,385,395,1,0,0,0,386,
  	387,5,48,0,0,387,388,5,120,0,0,388,390,1,0,0,0,389,391,7,3,0,0,390,389,
  	1,0,0,0,391,392,1,0,0,0,392,390,1,0,0,0,392,393,1,0,0,0,393,395,1,0,0,
  	0,394,378,1,0,0,0,394,386,1,0,0,0,395,90,1,0,0,0,396,397,5,171,0,0,397,
  	92,1,0,0,0,398,399,5,187,0,0,399,94,1,0,0,0,400,401,5,43,0,0,401,96,1,
  	0,0,0,402,403,5,45,0,0,403,98,1,0,0,0,404,405,5,42,0,0,405,100,1,0,0,
  	0,406,407,5,47,0,0,407,102,1,0,0,0,408,409,5,62,0,0,409,104,1,0,0,0,410,
  	411,5,62,0,0,411,412,5,61,0,0,412,106,1,0,0,0,413,414,5,60,0,0,414,108,
  	1,0,0,0,415,416,5,60,0,0,416,417,5,61,0,0,417,110,1,0,0,0,418,419,5,61,
  	0,0,419,420,5,61,0,0,420,112,1,0,0,0,421,422,5,33,0,0,422,423,5,61,0,
  	0,423,114,1,0,0,0,424,425,5,38,0,0,425,116,1,0,0,0,426,427,5,124,0,0,
  	427,118,1,0,0,0,428,429,5,94,0,0,429,120,1,0,0,0,430,431,5,126,0,0,431,
  	122,1,0,0,0,432,433,5,60,0,0,433,434,5,60,0,0,434,124,1,0,0,0,435,436,
  	5,62,0,0,436,437,5,62,0,0,437,126,1,0,0,0,438,439,5,38,0,0,439,440,5,
  	38,0,0,440,128,1,0,0,0,441,442,5,124,0,0,442,443,5,124,0,0,443,130,1,
  	0,0,0,444,445,5,33,0,0,445,132,1,0,0,0,446,447,7,4,0,0,447,448,1,0,0,
  	0,448,449,6,66,0,0,449,134,1,0,0,0,24,0,179,223,232,256,284,317,321,324,
  	330,335,338,343,349,352,357,361,368,376,382,384,390,392,394,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  spotlexerLexerStaticData = staticData.release();
}

}

spotLexer::spotLexer(CharStream *input) : Lexer(input) {
  spotLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *spotlexerLexerStaticData->atn, spotlexerLexerStaticData->decisionToDFA, spotlexerLexerStaticData->sharedContextCache);
}

spotLexer::~spotLexer() {
  delete _interpreter;
}

std::string spotLexer::getGrammarFileName() const {
  return "spot.g4";
}

const std::vector<std::string>& spotLexer::getRuleNames() const {
  return spotlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& spotLexer::getChannelNames() const {
  return spotlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& spotLexer::getModeNames() const {
  return spotlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& spotLexer::getVocabulary() const {
  return spotlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView spotLexer::getSerializedATN() const {
  return spotlexerLexerStaticData->serializedATN;
}

const atn::ATN& spotLexer::getATN() const {
  return *spotlexerLexerStaticData->atn;
}




void spotLexer::initialize() {
  ::antlr4::internal::call_once(spotlexerLexerOnceFlag, spotlexerLexerInitialize);
}
