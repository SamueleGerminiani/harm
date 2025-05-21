
#include <string>
// Forward declaration
bool isUnary(const std::string& token);
bool isSharedOperator(const std::string& token);
bool canUseSharedOperator(const std::string& unaryOp, const std::string& sharedOp);
bool canTakeThisNot(const std::string& unaryOp, const std::string& ph);


// Generated from temporal.g4 by ANTLR 4.10.1


#include "temporalListener.h"

#include "temporalParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct TemporalParserStaticData final {
  TemporalParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TemporalParserStaticData(const TemporalParserStaticData&) = delete;
  TemporalParserStaticData(TemporalParserStaticData&&) = delete;
  TemporalParserStaticData& operator=(const TemporalParserStaticData&) = delete;
  TemporalParserStaticData& operator=(TemporalParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag temporalParserOnceFlag;
TemporalParserStaticData *temporalParserStaticData = nullptr;

void temporalParserInitialize() {
  assert(temporalParserStaticData == nullptr);
  auto staticData = std::make_unique<TemporalParserStaticData>(
    std::vector<std::string>{
      "formula", "sva_assert", "implication", "sere", "booleanLayer", "tformula", 
      "dt_next", "dt_next_and", "dt_ncreps", "startBoolean", "startInt", 
      "startFloat", "boolean", "booleanAtom", "numeric", "range", "intAtom", 
      "int_constant", "floatAtom", "relop", "cls_op"
    },
    std::vector<std::string>{
      "", "'assert property'", "'@(posedge'", "'..##'", "'..#'", "'..['", 
      "']@'", "", "'..&&..'", "", "", "", "", "'R'", "'..'", "'=>'", "'->'", 
      "'<->'", "", "", "'='", "'##'", "';'", "'first_match'", "'not'", "'and'", 
      "'intersect'", "'or'", "", "", "", "", "", "", "'{'", "'}'", "'['", 
      "']'", "'('", "')'", "", "", "", "", "", "", "", "'''", "'+'", "'-'", 
      "'*'", "'/'", "'>'", "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", 
      "'|'", "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'", "':'", 
      "'::'", "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "PLACEHOLDER", "DT_AND", "EVENTUALLY", 
      "ALWAYS", "NEXT", "UNTIL", "RELEASE", "DOTS", "IMPL", "IMPLO", "IFF", 
      "SEREIMPL", "SEREIMPLO", "ASS", "DELAY", "SCOL", "FIRST_MATCH", "TNOT", 
      "TAND", "INTERSECT", "TOR", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", 
      "INT_VARIABLE", "CONST_SUFFIX", "FLOAT_CONSTANT", "FLOAT_VARIABLE", 
      "LCURLY", "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "SINTEGER", 
      "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", "VERILOG_BINARY", "FVL", 
      "SINGLE_QUOTE", "PLUS", "MINUS", "TIMES", "DIV", "GT", "GE", "LT", 
      "LE", "EQ", "NEQ", "BAND", "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", 
      "AND", "OR", "NOT", "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,72,428,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,1,0,1,
  	0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,56,8,0,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,77,
  	8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,88,8,2,1,2,1,2,3,2,92,8,2,
  	1,2,1,2,1,2,1,2,3,2,98,8,2,1,2,1,2,3,2,102,8,2,1,2,1,2,1,2,3,2,107,8,
  	2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,3,3,127,8,3,1,3,3,3,130,8,3,1,3,3,3,133,8,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,3,3,141,8,3,1,3,3,3,144,8,3,1,3,3,3,147,8,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	3,3,155,8,3,1,3,3,3,158,8,3,1,3,3,3,161,8,3,1,3,3,3,164,8,3,1,3,3,3,167,
  	8,3,1,3,1,3,1,3,1,3,3,3,173,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,3,3,187,8,3,1,3,3,3,190,8,3,1,3,3,3,193,8,3,1,3,3,3,196,8,3,
  	1,3,3,3,199,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,212,8,
  	3,1,3,3,3,215,8,3,1,3,3,3,218,8,3,1,3,1,3,1,3,1,3,1,3,5,3,225,8,3,10,
  	3,12,3,228,9,3,1,4,1,4,1,4,1,4,1,4,1,4,3,4,236,8,4,1,4,3,4,239,8,4,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,248,8,5,1,5,1,5,3,5,252,8,5,1,5,1,5,1,5,
  	1,5,1,5,3,5,259,8,5,1,5,3,5,262,8,5,1,5,3,5,265,8,5,1,5,1,5,1,5,1,5,1,
  	5,3,5,272,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,283,8,5,10,5,12,
  	5,286,9,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,9,1,9,1,9,1,10,1,10,1,10,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,3,12,334,8,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,1,12,5,12,348,8,12,10,12,12,12,351,9,12,1,13,1,13,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,14,364,8,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,5,14,389,8,14,10,14,12,14,392,9,14,1,15,1,15,
  	1,15,1,15,3,15,398,8,15,1,15,1,15,1,16,1,16,3,16,404,8,16,1,17,1,17,1,
  	17,3,17,409,8,17,1,17,1,17,3,17,413,8,17,1,17,3,17,416,8,17,1,17,1,17,
  	3,17,420,8,17,1,18,1,18,1,19,1,19,1,20,1,20,1,20,0,4,6,10,24,28,21,0,
  	2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0,16,2,0,14,14,
  	67,67,2,0,41,41,69,69,2,0,25,26,64,64,3,0,27,27,59,59,65,65,2,0,24,24,
  	66,66,1,0,12,13,2,0,25,25,64,64,2,0,16,16,20,20,2,0,22,22,67,67,1,0,28,
  	29,1,0,50,51,1,0,48,49,1,0,40,41,1,0,32,33,1,0,52,55,2,0,52,56,70,70,
  	503,0,55,1,0,0,0,2,76,1,0,0,0,4,106,1,0,0,0,6,172,1,0,0,0,8,238,1,0,0,
  	0,10,271,1,0,0,0,12,287,1,0,0,0,14,291,1,0,0,0,16,296,1,0,0,0,18,303,
  	1,0,0,0,20,306,1,0,0,0,22,309,1,0,0,0,24,333,1,0,0,0,26,352,1,0,0,0,28,
  	363,1,0,0,0,30,393,1,0,0,0,32,403,1,0,0,0,34,419,1,0,0,0,36,421,1,0,0,
  	0,38,423,1,0,0,0,40,425,1,0,0,0,42,43,5,10,0,0,43,44,5,38,0,0,44,45,3,
  	4,2,0,45,46,5,39,0,0,46,47,5,0,0,1,47,56,1,0,0,0,48,49,5,10,0,0,49,50,
  	3,4,2,0,50,51,5,0,0,1,51,56,1,0,0,0,52,53,3,2,1,0,53,54,5,0,0,1,54,56,
  	1,0,0,0,55,42,1,0,0,0,55,48,1,0,0,0,55,52,1,0,0,0,56,1,1,0,0,0,57,58,
  	5,1,0,0,58,59,5,38,0,0,59,60,3,2,1,0,60,61,5,39,0,0,61,77,1,0,0,0,62,
  	63,5,38,0,0,63,64,3,2,1,0,64,65,5,39,0,0,65,77,1,0,0,0,66,67,5,2,0,0,
  	67,68,3,24,12,0,68,69,5,39,0,0,69,70,3,2,1,0,70,77,1,0,0,0,71,72,5,38,
  	0,0,72,73,3,4,2,0,73,74,5,39,0,0,74,77,1,0,0,0,75,77,3,4,2,0,76,57,1,
  	0,0,0,76,62,1,0,0,0,76,66,1,0,0,0,76,71,1,0,0,0,76,75,1,0,0,0,77,3,1,
  	0,0,0,78,79,3,10,5,0,79,80,5,15,0,0,80,81,3,10,5,0,81,107,1,0,0,0,82,
  	83,3,10,5,0,83,84,5,16,0,0,84,85,3,10,5,0,85,107,1,0,0,0,86,88,5,34,0,
  	0,87,86,1,0,0,0,87,88,1,0,0,0,88,89,1,0,0,0,89,91,3,6,3,0,90,92,5,35,
  	0,0,91,90,1,0,0,0,91,92,1,0,0,0,92,93,1,0,0,0,93,94,5,18,0,0,94,95,3,
  	10,5,0,95,107,1,0,0,0,96,98,5,34,0,0,97,96,1,0,0,0,97,98,1,0,0,0,98,99,
  	1,0,0,0,99,101,3,6,3,0,100,102,5,35,0,0,101,100,1,0,0,0,101,102,1,0,0,
  	0,102,103,1,0,0,0,103,104,5,19,0,0,104,105,3,10,5,0,105,107,1,0,0,0,106,
  	78,1,0,0,0,106,82,1,0,0,0,106,87,1,0,0,0,106,97,1,0,0,0,107,5,1,0,0,0,
  	108,109,6,3,-1,0,109,110,5,23,0,0,110,111,5,38,0,0,111,112,3,6,3,0,112,
  	113,5,39,0,0,113,173,1,0,0,0,114,115,5,38,0,0,115,116,3,6,3,0,116,117,
  	5,39,0,0,117,173,1,0,0,0,118,119,5,34,0,0,119,120,3,6,3,0,120,121,5,35,
  	0,0,121,173,1,0,0,0,122,123,3,8,4,0,123,124,5,36,0,0,124,126,5,20,0,0,
  	125,127,5,41,0,0,126,125,1,0,0,0,126,127,1,0,0,0,127,129,1,0,0,0,128,
  	130,7,0,0,0,129,128,1,0,0,0,129,130,1,0,0,0,130,132,1,0,0,0,131,133,7,
  	1,0,0,132,131,1,0,0,0,132,133,1,0,0,0,133,134,1,0,0,0,134,135,5,37,0,
  	0,135,173,1,0,0,0,136,137,3,8,4,0,137,138,5,36,0,0,138,140,5,16,0,0,139,
  	141,5,41,0,0,140,139,1,0,0,0,140,141,1,0,0,0,141,143,1,0,0,0,142,144,
  	7,0,0,0,143,142,1,0,0,0,143,144,1,0,0,0,144,146,1,0,0,0,145,147,7,1,0,
  	0,146,145,1,0,0,0,146,147,1,0,0,0,147,148,1,0,0,0,148,149,5,37,0,0,149,
  	173,1,0,0,0,150,173,3,16,8,0,151,173,5,8,0,0,152,154,5,21,0,0,153,155,
  	5,36,0,0,154,153,1,0,0,0,154,155,1,0,0,0,155,157,1,0,0,0,156,158,5,41,
  	0,0,157,156,1,0,0,0,157,158,1,0,0,0,158,160,1,0,0,0,159,161,7,0,0,0,160,
  	159,1,0,0,0,160,161,1,0,0,0,161,163,1,0,0,0,162,164,7,1,0,0,163,162,1,
  	0,0,0,163,164,1,0,0,0,164,166,1,0,0,0,165,167,5,37,0,0,166,165,1,0,0,
  	0,166,167,1,0,0,0,167,168,1,0,0,0,168,173,3,6,3,6,169,173,3,12,6,0,170,
  	173,3,14,7,0,171,173,3,8,4,0,172,108,1,0,0,0,172,114,1,0,0,0,172,118,
  	1,0,0,0,172,122,1,0,0,0,172,136,1,0,0,0,172,150,1,0,0,0,172,151,1,0,0,
  	0,172,152,1,0,0,0,172,169,1,0,0,0,172,170,1,0,0,0,172,171,1,0,0,0,173,
  	226,1,0,0,0,174,175,10,11,0,0,175,176,5,58,0,0,176,225,3,6,3,12,177,178,
  	10,10,0,0,178,179,7,2,0,0,179,225,3,6,3,11,180,181,10,8,0,0,181,182,7,
  	3,0,0,182,225,3,6,3,9,183,184,10,7,0,0,184,186,5,21,0,0,185,187,5,36,
  	0,0,186,185,1,0,0,0,186,187,1,0,0,0,187,189,1,0,0,0,188,190,5,41,0,0,
  	189,188,1,0,0,0,189,190,1,0,0,0,190,192,1,0,0,0,191,193,7,0,0,0,192,191,
  	1,0,0,0,192,193,1,0,0,0,193,195,1,0,0,0,194,196,7,1,0,0,195,194,1,0,0,
  	0,195,196,1,0,0,0,196,198,1,0,0,0,197,199,5,37,0,0,198,197,1,0,0,0,198,
  	199,1,0,0,0,199,200,1,0,0,0,200,225,3,6,3,8,201,202,10,3,0,0,202,203,
  	5,67,0,0,203,225,3,6,3,4,204,205,10,2,0,0,205,206,5,22,0,0,206,225,3,
  	6,3,3,207,208,10,16,0,0,208,209,5,36,0,0,209,211,5,50,0,0,210,212,5,41,
  	0,0,211,210,1,0,0,0,211,212,1,0,0,0,212,214,1,0,0,0,213,215,7,0,0,0,214,
  	213,1,0,0,0,214,215,1,0,0,0,215,217,1,0,0,0,216,218,7,1,0,0,217,216,1,
  	0,0,0,217,218,1,0,0,0,218,219,1,0,0,0,219,225,5,37,0,0,220,221,10,15,
  	0,0,221,222,5,36,0,0,222,223,5,48,0,0,223,225,5,37,0,0,224,174,1,0,0,
  	0,224,177,1,0,0,0,224,180,1,0,0,0,224,183,1,0,0,0,224,201,1,0,0,0,224,
  	204,1,0,0,0,224,207,1,0,0,0,224,220,1,0,0,0,225,228,1,0,0,0,226,224,1,
  	0,0,0,226,227,1,0,0,0,227,7,1,0,0,0,228,226,1,0,0,0,229,230,5,38,0,0,
  	230,231,3,8,4,0,231,232,5,39,0,0,232,239,1,0,0,0,233,239,3,24,12,0,234,
  	236,5,66,0,0,235,234,1,0,0,0,235,236,1,0,0,0,236,237,1,0,0,0,237,239,
  	5,7,0,0,238,229,1,0,0,0,238,233,1,0,0,0,238,235,1,0,0,0,239,9,1,0,0,0,
  	240,241,6,5,-1,0,241,242,5,38,0,0,242,243,3,10,5,0,243,244,5,39,0,0,244,
  	272,1,0,0,0,245,247,4,5,8,0,246,248,5,34,0,0,247,246,1,0,0,0,247,248,
  	1,0,0,0,248,249,1,0,0,0,249,251,3,6,3,0,250,252,5,35,0,0,251,250,1,0,
  	0,0,251,252,1,0,0,0,252,272,1,0,0,0,253,254,4,5,9,0,254,255,7,4,0,0,255,
  	272,3,10,5,8,256,258,5,11,0,0,257,259,5,36,0,0,258,257,1,0,0,0,258,259,
  	1,0,0,0,259,261,1,0,0,0,260,262,5,41,0,0,261,260,1,0,0,0,261,262,1,0,
  	0,0,262,264,1,0,0,0,263,265,5,37,0,0,264,263,1,0,0,0,264,265,1,0,0,0,
  	265,266,1,0,0,0,266,272,3,10,5,7,267,268,5,9,0,0,268,272,3,10,5,6,269,
  	272,5,8,0,0,270,272,3,8,4,0,271,240,1,0,0,0,271,245,1,0,0,0,271,253,1,
  	0,0,0,271,256,1,0,0,0,271,267,1,0,0,0,271,269,1,0,0,0,271,270,1,0,0,0,
  	272,284,1,0,0,0,273,274,10,5,0,0,274,275,7,5,0,0,275,283,3,10,5,5,276,
  	277,10,4,0,0,277,278,7,6,0,0,278,283,3,10,5,5,279,280,10,3,0,0,280,281,
  	7,3,0,0,281,283,3,10,5,4,282,273,1,0,0,0,282,276,1,0,0,0,282,279,1,0,
  	0,0,283,286,1,0,0,0,284,282,1,0,0,0,284,285,1,0,0,0,285,11,1,0,0,0,286,
  	284,1,0,0,0,287,288,5,3,0,0,288,289,5,41,0,0,289,290,5,14,0,0,290,13,
  	1,0,0,0,291,292,5,4,0,0,292,293,5,41,0,0,293,294,5,58,0,0,294,295,5,14,
  	0,0,295,15,1,0,0,0,296,297,5,5,0,0,297,298,7,7,0,0,298,299,5,41,0,0,299,
  	300,5,6,0,0,300,301,7,8,0,0,301,302,5,14,0,0,302,17,1,0,0,0,303,304,3,
  	24,12,0,304,305,5,0,0,1,305,19,1,0,0,0,306,307,3,28,14,0,307,308,5,0,
  	0,1,308,21,1,0,0,0,309,310,3,28,14,0,310,311,5,0,0,1,311,23,1,0,0,0,312,
  	313,6,12,-1,0,313,314,5,66,0,0,314,334,3,24,12,11,315,316,3,28,14,0,316,
  	317,3,38,19,0,317,318,3,28,14,0,318,334,1,0,0,0,319,320,3,28,14,0,320,
  	321,5,56,0,0,321,322,3,28,14,0,322,334,1,0,0,0,323,324,3,28,14,0,324,
  	325,5,57,0,0,325,326,3,28,14,0,326,334,1,0,0,0,327,334,3,26,13,0,328,
  	334,3,28,14,0,329,330,5,38,0,0,330,331,3,24,12,0,331,332,5,39,0,0,332,
  	334,1,0,0,0,333,312,1,0,0,0,333,315,1,0,0,0,333,319,1,0,0,0,333,323,1,
  	0,0,0,333,327,1,0,0,0,333,328,1,0,0,0,333,329,1,0,0,0,334,349,1,0,0,0,
  	335,336,10,7,0,0,336,337,5,56,0,0,337,348,3,24,12,8,338,339,10,6,0,0,
  	339,340,5,57,0,0,340,348,3,24,12,7,341,342,10,5,0,0,342,343,5,64,0,0,
  	343,348,3,24,12,6,344,345,10,4,0,0,345,346,5,65,0,0,346,348,3,24,12,5,
  	347,335,1,0,0,0,347,338,1,0,0,0,347,341,1,0,0,0,347,344,1,0,0,0,348,351,
  	1,0,0,0,349,347,1,0,0,0,349,350,1,0,0,0,350,25,1,0,0,0,351,349,1,0,0,
  	0,352,353,7,9,0,0,353,27,1,0,0,0,354,355,6,14,-1,0,355,356,5,61,0,0,356,
  	364,3,28,14,12,357,364,3,32,16,0,358,364,3,36,18,0,359,360,5,38,0,0,360,
  	361,3,28,14,0,361,362,5,39,0,0,362,364,1,0,0,0,363,354,1,0,0,0,363,357,
  	1,0,0,0,363,358,1,0,0,0,363,359,1,0,0,0,364,390,1,0,0,0,365,366,10,10,
  	0,0,366,367,7,10,0,0,367,389,3,28,14,11,368,369,10,9,0,0,369,370,7,11,
  	0,0,370,389,3,28,14,10,371,372,10,8,0,0,372,373,5,62,0,0,373,389,3,28,
  	14,9,374,375,10,7,0,0,375,376,5,63,0,0,376,389,3,28,14,8,377,378,10,6,
  	0,0,378,379,5,58,0,0,379,389,3,28,14,7,380,381,10,5,0,0,381,382,5,60,
  	0,0,382,389,3,28,14,6,383,384,10,4,0,0,384,385,5,59,0,0,385,389,3,28,
  	14,5,386,387,10,11,0,0,387,389,3,30,15,0,388,365,1,0,0,0,388,368,1,0,
  	0,0,388,371,1,0,0,0,388,374,1,0,0,0,388,377,1,0,0,0,388,380,1,0,0,0,388,
  	383,1,0,0,0,388,386,1,0,0,0,389,392,1,0,0,0,390,388,1,0,0,0,390,391,1,
  	0,0,0,391,29,1,0,0,0,392,390,1,0,0,0,393,394,5,36,0,0,394,397,7,12,0,
  	0,395,396,5,67,0,0,396,398,7,12,0,0,397,395,1,0,0,0,397,398,1,0,0,0,398,
  	399,1,0,0,0,399,400,5,37,0,0,400,31,1,0,0,0,401,404,3,34,17,0,402,404,
  	5,30,0,0,403,401,1,0,0,0,403,402,1,0,0,0,404,33,1,0,0,0,405,420,5,43,
  	0,0,406,408,5,40,0,0,407,409,5,31,0,0,408,407,1,0,0,0,408,409,1,0,0,0,
  	409,420,1,0,0,0,410,412,5,41,0,0,411,413,5,31,0,0,412,411,1,0,0,0,412,
  	413,1,0,0,0,413,420,1,0,0,0,414,416,5,41,0,0,415,414,1,0,0,0,415,416,
  	1,0,0,0,416,417,1,0,0,0,417,420,5,45,0,0,418,420,5,44,0,0,419,405,1,0,
  	0,0,419,406,1,0,0,0,419,410,1,0,0,0,419,415,1,0,0,0,419,418,1,0,0,0,420,
  	35,1,0,0,0,421,422,7,13,0,0,422,37,1,0,0,0,423,424,7,14,0,0,424,39,1,
  	0,0,0,425,426,7,15,0,0,426,41,1,0,0,0,51,55,76,87,91,97,101,106,126,129,
  	132,140,143,146,154,157,160,163,166,172,186,189,192,195,198,211,214,217,
  	224,226,235,238,247,251,258,261,264,271,282,284,333,347,349,363,388,390,
  	397,403,408,412,415,419
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  temporalParserStaticData = staticData.release();
}

}

temporalParser::temporalParser(TokenStream *input) : temporalParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

temporalParser::temporalParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  temporalParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *temporalParserStaticData->atn, temporalParserStaticData->decisionToDFA, temporalParserStaticData->sharedContextCache, options);
}

temporalParser::~temporalParser() {
  delete _interpreter;
}

const atn::ATN& temporalParser::getATN() const {
  return *temporalParserStaticData->atn;
}

std::string temporalParser::getGrammarFileName() const {
  return "temporal.g4";
}

const std::vector<std::string>& temporalParser::getRuleNames() const {
  return temporalParserStaticData->ruleNames;
}

const dfa::Vocabulary& temporalParser::getVocabulary() const {
  return temporalParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView temporalParser::getSerializedATN() const {
  return temporalParserStaticData->serializedATN;
}


//----------------- FormulaContext ------------------------------------------------------------------

temporalParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::FormulaContext::ALWAYS() {
  return getToken(temporalParser::ALWAYS, 0);
}

tree::TerminalNode* temporalParser::FormulaContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

temporalParser::ImplicationContext* temporalParser::FormulaContext::implication() {
  return getRuleContext<temporalParser::ImplicationContext>(0);
}

tree::TerminalNode* temporalParser::FormulaContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

tree::TerminalNode* temporalParser::FormulaContext::EOF() {
  return getToken(temporalParser::EOF, 0);
}

temporalParser::Sva_assertContext* temporalParser::FormulaContext::sva_assert() {
  return getRuleContext<temporalParser::Sva_assertContext>(0);
}


size_t temporalParser::FormulaContext::getRuleIndex() const {
  return temporalParser::RuleFormula;
}

void temporalParser::FormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormula(this);
}

void temporalParser::FormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormula(this);
}

temporalParser::FormulaContext* temporalParser::formula() {
  FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, getState());
  enterRule(_localctx, 0, temporalParser::RuleFormula);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(55);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(42);
      match(temporalParser::ALWAYS);
      setState(43);
      match(temporalParser::LROUND);
      setState(44);
      implication();
      setState(45);
      match(temporalParser::RROUND);
      setState(46);
      match(temporalParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(48);
      match(temporalParser::ALWAYS);
      setState(49);
      implication();
      setState(50);
      match(temporalParser::EOF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(52);
      sva_assert();
      setState(53);
      match(temporalParser::EOF);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sva_assertContext ------------------------------------------------------------------

temporalParser::Sva_assertContext::Sva_assertContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Sva_assertContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

temporalParser::Sva_assertContext* temporalParser::Sva_assertContext::sva_assert() {
  return getRuleContext<temporalParser::Sva_assertContext>(0);
}

tree::TerminalNode* temporalParser::Sva_assertContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

temporalParser::BooleanContext* temporalParser::Sva_assertContext::boolean() {
  return getRuleContext<temporalParser::BooleanContext>(0);
}

temporalParser::ImplicationContext* temporalParser::Sva_assertContext::implication() {
  return getRuleContext<temporalParser::ImplicationContext>(0);
}


size_t temporalParser::Sva_assertContext::getRuleIndex() const {
  return temporalParser::RuleSva_assert;
}

void temporalParser::Sva_assertContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSva_assert(this);
}

void temporalParser::Sva_assertContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSva_assert(this);
}

temporalParser::Sva_assertContext* temporalParser::sva_assert() {
  Sva_assertContext *_localctx = _tracker.createInstance<Sva_assertContext>(_ctx, getState());
  enterRule(_localctx, 2, temporalParser::RuleSva_assert);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(76);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(57);
      match(temporalParser::T__0);
      setState(58);
      match(temporalParser::LROUND);
      setState(59);
      sva_assert();
      setState(60);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(62);
      match(temporalParser::LROUND);
      setState(63);
      sva_assert();
      setState(64);
      match(temporalParser::RROUND);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(66);
      match(temporalParser::T__1);
      setState(67);
      boolean(0);
      setState(68);
      match(temporalParser::RROUND);
      setState(69);
      sva_assert();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(71);
      match(temporalParser::LROUND);
      setState(72);
      implication();
      setState(73);
      match(temporalParser::RROUND);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(75);
      implication();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImplicationContext ------------------------------------------------------------------

temporalParser::ImplicationContext::ImplicationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<temporalParser::TformulaContext *> temporalParser::ImplicationContext::tformula() {
  return getRuleContexts<temporalParser::TformulaContext>();
}

temporalParser::TformulaContext* temporalParser::ImplicationContext::tformula(size_t i) {
  return getRuleContext<temporalParser::TformulaContext>(i);
}

tree::TerminalNode* temporalParser::ImplicationContext::IMPL() {
  return getToken(temporalParser::IMPL, 0);
}

tree::TerminalNode* temporalParser::ImplicationContext::IMPLO() {
  return getToken(temporalParser::IMPLO, 0);
}

temporalParser::SereContext* temporalParser::ImplicationContext::sere() {
  return getRuleContext<temporalParser::SereContext>(0);
}

tree::TerminalNode* temporalParser::ImplicationContext::SEREIMPL() {
  return getToken(temporalParser::SEREIMPL, 0);
}

tree::TerminalNode* temporalParser::ImplicationContext::LCURLY() {
  return getToken(temporalParser::LCURLY, 0);
}

tree::TerminalNode* temporalParser::ImplicationContext::RCURLY() {
  return getToken(temporalParser::RCURLY, 0);
}

tree::TerminalNode* temporalParser::ImplicationContext::SEREIMPLO() {
  return getToken(temporalParser::SEREIMPLO, 0);
}


size_t temporalParser::ImplicationContext::getRuleIndex() const {
  return temporalParser::RuleImplication;
}

void temporalParser::ImplicationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImplication(this);
}

void temporalParser::ImplicationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImplication(this);
}

temporalParser::ImplicationContext* temporalParser::implication() {
  ImplicationContext *_localctx = _tracker.createInstance<ImplicationContext>(_ctx, getState());
  enterRule(_localctx, 4, temporalParser::RuleImplication);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(106);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(78);
      tformula(0);
      setState(79);
      match(temporalParser::IMPL);
      setState(80);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(82);
      tformula(0);
      setState(83);
      match(temporalParser::IMPLO);
      setState(84);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(87);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(86);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(89);
      sere(0);
      setState(91);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RCURLY) {
        setState(90);
        match(temporalParser::RCURLY);
      }
      setState(93);
      match(temporalParser::SEREIMPL);
      setState(94);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(97);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(96);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(99);
      sere(0);
      setState(101);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RCURLY) {
        setState(100);
        match(temporalParser::RCURLY);
      }
      setState(103);
      match(temporalParser::SEREIMPLO);
      setState(104);
      tformula(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SereContext ------------------------------------------------------------------

temporalParser::SereContext::SereContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::SereContext::FIRST_MATCH() {
  return getToken(temporalParser::FIRST_MATCH, 0);
}

tree::TerminalNode* temporalParser::SereContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

std::vector<temporalParser::SereContext *> temporalParser::SereContext::sere() {
  return getRuleContexts<temporalParser::SereContext>();
}

temporalParser::SereContext* temporalParser::SereContext::sere(size_t i) {
  return getRuleContext<temporalParser::SereContext>(i);
}

tree::TerminalNode* temporalParser::SereContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

tree::TerminalNode* temporalParser::SereContext::LCURLY() {
  return getToken(temporalParser::LCURLY, 0);
}

tree::TerminalNode* temporalParser::SereContext::RCURLY() {
  return getToken(temporalParser::RCURLY, 0);
}

temporalParser::BooleanLayerContext* temporalParser::SereContext::booleanLayer() {
  return getRuleContext<temporalParser::BooleanLayerContext>(0);
}

tree::TerminalNode* temporalParser::SereContext::LSQUARED() {
  return getToken(temporalParser::LSQUARED, 0);
}

tree::TerminalNode* temporalParser::SereContext::ASS() {
  return getToken(temporalParser::ASS, 0);
}

tree::TerminalNode* temporalParser::SereContext::RSQUARED() {
  return getToken(temporalParser::RSQUARED, 0);
}

std::vector<tree::TerminalNode *> temporalParser::SereContext::UINTEGER() {
  return getTokens(temporalParser::UINTEGER);
}

tree::TerminalNode* temporalParser::SereContext::UINTEGER(size_t i) {
  return getToken(temporalParser::UINTEGER, i);
}

tree::TerminalNode* temporalParser::SereContext::DOTS() {
  return getToken(temporalParser::DOTS, 0);
}

tree::TerminalNode* temporalParser::SereContext::COL() {
  return getToken(temporalParser::COL, 0);
}

tree::TerminalNode* temporalParser::SereContext::DOLLAR() {
  return getToken(temporalParser::DOLLAR, 0);
}

tree::TerminalNode* temporalParser::SereContext::IMPLO() {
  return getToken(temporalParser::IMPLO, 0);
}

temporalParser::Dt_ncrepsContext* temporalParser::SereContext::dt_ncreps() {
  return getRuleContext<temporalParser::Dt_ncrepsContext>(0);
}

tree::TerminalNode* temporalParser::SereContext::DT_AND() {
  return getToken(temporalParser::DT_AND, 0);
}

tree::TerminalNode* temporalParser::SereContext::DELAY() {
  return getToken(temporalParser::DELAY, 0);
}

temporalParser::Dt_nextContext* temporalParser::SereContext::dt_next() {
  return getRuleContext<temporalParser::Dt_nextContext>(0);
}

temporalParser::Dt_next_andContext* temporalParser::SereContext::dt_next_and() {
  return getRuleContext<temporalParser::Dt_next_andContext>(0);
}

tree::TerminalNode* temporalParser::SereContext::BAND() {
  return getToken(temporalParser::BAND, 0);
}

tree::TerminalNode* temporalParser::SereContext::TAND() {
  return getToken(temporalParser::TAND, 0);
}

tree::TerminalNode* temporalParser::SereContext::INTERSECT() {
  return getToken(temporalParser::INTERSECT, 0);
}

tree::TerminalNode* temporalParser::SereContext::AND() {
  return getToken(temporalParser::AND, 0);
}

tree::TerminalNode* temporalParser::SereContext::TOR() {
  return getToken(temporalParser::TOR, 0);
}

tree::TerminalNode* temporalParser::SereContext::OR() {
  return getToken(temporalParser::OR, 0);
}

tree::TerminalNode* temporalParser::SereContext::BOR() {
  return getToken(temporalParser::BOR, 0);
}

tree::TerminalNode* temporalParser::SereContext::SCOL() {
  return getToken(temporalParser::SCOL, 0);
}

tree::TerminalNode* temporalParser::SereContext::TIMES() {
  return getToken(temporalParser::TIMES, 0);
}

tree::TerminalNode* temporalParser::SereContext::PLUS() {
  return getToken(temporalParser::PLUS, 0);
}


size_t temporalParser::SereContext::getRuleIndex() const {
  return temporalParser::RuleSere;
}

void temporalParser::SereContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSere(this);
}

void temporalParser::SereContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSere(this);
}


temporalParser::SereContext* temporalParser::sere() {
   return sere(0);
}

temporalParser::SereContext* temporalParser::sere(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  temporalParser::SereContext *_localctx = _tracker.createInstance<SereContext>(_ctx, parentState);
  temporalParser::SereContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, temporalParser::RuleSere, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(172);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(109);
      match(temporalParser::FIRST_MATCH);
      setState(110);
      match(temporalParser::LROUND);
      setState(111);
      sere(0);
      setState(112);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      setState(114);
      match(temporalParser::LROUND);
      setState(115);
      sere(0);
      setState(116);
      match(temporalParser::RROUND);
      break;
    }

    case 3: {
      setState(118);
      match(temporalParser::LCURLY);
      setState(119);
      sere(0);
      setState(120);
      match(temporalParser::RCURLY);
      break;
    }

    case 4: {
      setState(122);
      booleanLayer();
      setState(123);
      match(temporalParser::LSQUARED);
      setState(124);
      match(temporalParser::ASS);
      setState(126);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
      case 1: {
        setState(125);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(129);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS

      || _la == temporalParser::COL) {
        setState(128);
        _la = _input->LA(1);
        if (!(_la == temporalParser::DOTS

        || _la == temporalParser::COL)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(132);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER

      || _la == temporalParser::DOLLAR) {
        setState(131);
        _la = _input->LA(1);
        if (!(_la == temporalParser::UINTEGER

        || _la == temporalParser::DOLLAR)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(134);
      match(temporalParser::RSQUARED);
      break;
    }

    case 5: {
      setState(136);
      booleanLayer();
      setState(137);
      match(temporalParser::LSQUARED);
      setState(138);
      match(temporalParser::IMPLO);
      setState(140);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
      case 1: {
        setState(139);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(143);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS

      || _la == temporalParser::COL) {
        setState(142);
        _la = _input->LA(1);
        if (!(_la == temporalParser::DOTS

        || _la == temporalParser::COL)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(146);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER

      || _la == temporalParser::DOLLAR) {
        setState(145);
        _la = _input->LA(1);
        if (!(_la == temporalParser::UINTEGER

        || _la == temporalParser::DOLLAR)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(148);
      match(temporalParser::RSQUARED);
      break;
    }

    case 6: {
      setState(150);
      dt_ncreps();
      break;
    }

    case 7: {
      setState(151);
      match(temporalParser::DT_AND);
      break;
    }

    case 8: {
      setState(152);
      match(temporalParser::DELAY);
      setState(154);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::LSQUARED) {
        setState(153);
        match(temporalParser::LSQUARED);
      }
      setState(157);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
      case 1: {
        setState(156);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(160);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS

      || _la == temporalParser::COL) {
        setState(159);
        _la = _input->LA(1);
        if (!(_la == temporalParser::DOTS

        || _la == temporalParser::COL)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(163);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(162);
        _la = _input->LA(1);
        if (!(_la == temporalParser::UINTEGER

        || _la == temporalParser::DOLLAR)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      default:
        break;
      }
      setState(166);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RSQUARED) {
        setState(165);
        match(temporalParser::RSQUARED);
      }
      setState(168);
      sere(6);
      break;
    }

    case 9: {
      setState(169);
      dt_next();
      break;
    }

    case 10: {
      setState(170);
      dt_next_and();
      break;
    }

    case 11: {
      setState(171);
      booleanLayer();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(226);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(224);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(174);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(175);
          match(temporalParser::BAND);
          setState(176);
          sere(12);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(177);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(178);
          _la = _input->LA(1);
          if (!(((((_la - 25) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 25)) & ((1ULL << (temporalParser::TAND - 25))
            | (1ULL << (temporalParser::INTERSECT - 25))
            | (1ULL << (temporalParser::AND - 25)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(179);
          sere(11);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(180);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(181);
          _la = _input->LA(1);
          if (!(((((_la - 27) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 27)) & ((1ULL << (temporalParser::TOR - 27))
            | (1ULL << (temporalParser::BOR - 27))
            | (1ULL << (temporalParser::OR - 27)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(182);
          sere(9);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(183);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(184);
          match(temporalParser::DELAY);
          setState(186);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::LSQUARED) {
            setState(185);
            match(temporalParser::LSQUARED);
          }
          setState(189);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
          case 1: {
            setState(188);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(192);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::DOTS

          || _la == temporalParser::COL) {
            setState(191);
            _la = _input->LA(1);
            if (!(_la == temporalParser::DOTS

            || _la == temporalParser::COL)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
          }
          setState(195);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
          case 1: {
            setState(194);
            _la = _input->LA(1);
            if (!(_la == temporalParser::UINTEGER

            || _la == temporalParser::DOLLAR)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
            break;
          }

          default:
            break;
          }
          setState(198);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::RSQUARED) {
            setState(197);
            match(temporalParser::RSQUARED);
          }
          setState(200);
          sere(8);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(201);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(202);
          match(temporalParser::COL);
          setState(203);
          sere(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(204);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(205);
          match(temporalParser::SCOL);
          setState(206);
          sere(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(207);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(208);
          match(temporalParser::LSQUARED);
          setState(209);
          match(temporalParser::TIMES);
          setState(211);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
          case 1: {
            setState(210);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(214);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::DOTS

          || _la == temporalParser::COL) {
            setState(213);
            _la = _input->LA(1);
            if (!(_la == temporalParser::DOTS

            || _la == temporalParser::COL)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
          }
          setState(217);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::UINTEGER

          || _la == temporalParser::DOLLAR) {
            setState(216);
            _la = _input->LA(1);
            if (!(_la == temporalParser::UINTEGER

            || _la == temporalParser::DOLLAR)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
          }
          setState(219);
          match(temporalParser::RSQUARED);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(220);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(221);
          match(temporalParser::LSQUARED);
          setState(222);
          match(temporalParser::PLUS);
          setState(223);
          match(temporalParser::RSQUARED);
          break;
        }

        default:
          break;
        } 
      }
      setState(228);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- BooleanLayerContext ------------------------------------------------------------------

temporalParser::BooleanLayerContext::BooleanLayerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::BooleanLayerContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

temporalParser::BooleanLayerContext* temporalParser::BooleanLayerContext::booleanLayer() {
  return getRuleContext<temporalParser::BooleanLayerContext>(0);
}

tree::TerminalNode* temporalParser::BooleanLayerContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

temporalParser::BooleanContext* temporalParser::BooleanLayerContext::boolean() {
  return getRuleContext<temporalParser::BooleanContext>(0);
}

tree::TerminalNode* temporalParser::BooleanLayerContext::PLACEHOLDER() {
  return getToken(temporalParser::PLACEHOLDER, 0);
}

tree::TerminalNode* temporalParser::BooleanLayerContext::NOT() {
  return getToken(temporalParser::NOT, 0);
}


size_t temporalParser::BooleanLayerContext::getRuleIndex() const {
  return temporalParser::RuleBooleanLayer;
}

void temporalParser::BooleanLayerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanLayer(this);
}

void temporalParser::BooleanLayerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanLayer(this);
}

temporalParser::BooleanLayerContext* temporalParser::booleanLayer() {
  BooleanLayerContext *_localctx = _tracker.createInstance<BooleanLayerContext>(_ctx, getState());
  enterRule(_localctx, 8, temporalParser::RuleBooleanLayer);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(238);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(229);
      match(temporalParser::LROUND);
      setState(230);
      booleanLayer();
      setState(231);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(233);
      boolean(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(235);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::NOT) {
        setState(234);
        match(temporalParser::NOT);
      }
      setState(237);
      match(temporalParser::PLACEHOLDER);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TformulaContext ------------------------------------------------------------------

temporalParser::TformulaContext::TformulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::TformulaContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

std::vector<temporalParser::TformulaContext *> temporalParser::TformulaContext::tformula() {
  return getRuleContexts<temporalParser::TformulaContext>();
}

temporalParser::TformulaContext* temporalParser::TformulaContext::tformula(size_t i) {
  return getRuleContext<temporalParser::TformulaContext>(i);
}

tree::TerminalNode* temporalParser::TformulaContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

temporalParser::SereContext* temporalParser::TformulaContext::sere() {
  return getRuleContext<temporalParser::SereContext>(0);
}

tree::TerminalNode* temporalParser::TformulaContext::LCURLY() {
  return getToken(temporalParser::LCURLY, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::RCURLY() {
  return getToken(temporalParser::RCURLY, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::TNOT() {
  return getToken(temporalParser::TNOT, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::NOT() {
  return getToken(temporalParser::NOT, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::NEXT() {
  return getToken(temporalParser::NEXT, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::LSQUARED() {
  return getToken(temporalParser::LSQUARED, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::UINTEGER() {
  return getToken(temporalParser::UINTEGER, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::RSQUARED() {
  return getToken(temporalParser::RSQUARED, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::EVENTUALLY() {
  return getToken(temporalParser::EVENTUALLY, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::DT_AND() {
  return getToken(temporalParser::DT_AND, 0);
}

temporalParser::BooleanLayerContext* temporalParser::TformulaContext::booleanLayer() {
  return getRuleContext<temporalParser::BooleanLayerContext>(0);
}

tree::TerminalNode* temporalParser::TformulaContext::UNTIL() {
  return getToken(temporalParser::UNTIL, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::RELEASE() {
  return getToken(temporalParser::RELEASE, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::TAND() {
  return getToken(temporalParser::TAND, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::AND() {
  return getToken(temporalParser::AND, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::TOR() {
  return getToken(temporalParser::TOR, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::OR() {
  return getToken(temporalParser::OR, 0);
}

tree::TerminalNode* temporalParser::TformulaContext::BOR() {
  return getToken(temporalParser::BOR, 0);
}


size_t temporalParser::TformulaContext::getRuleIndex() const {
  return temporalParser::RuleTformula;
}

void temporalParser::TformulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTformula(this);
}

void temporalParser::TformulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTformula(this);
}


temporalParser::TformulaContext* temporalParser::tformula() {
   return tformula(0);
}

temporalParser::TformulaContext* temporalParser::tformula(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  temporalParser::TformulaContext *_localctx = _tracker.createInstance<TformulaContext>(_ctx, parentState);
  temporalParser::TformulaContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, temporalParser::RuleTformula, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(271);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      setState(241);
      match(temporalParser::LROUND);
      setState(242);
      tformula(0);
      setState(243);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      setState(245);

      if (!(canUseSharedOperator(_input->LT(-1)->getText(),_input->LT(2)->getText()))) throw FailedPredicateException(this, "canUseSharedOperator(_input->LT(-1)->getText(),_input->LT(2)->getText())");
      setState(247);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
      case 1: {
        setState(246);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(249);
      sere(0);
      setState(251);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
      case 1: {
        setState(250);
        match(temporalParser::RCURLY);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      setState(253);

      if (!(canTakeThisNot(_input->LT(1)->getText(),_input->LT(2)->getText()))) throw FailedPredicateException(this, "canTakeThisNot(_input->LT(1)->getText(),_input->LT(2)->getText())");
      setState(254);
      _la = _input->LA(1);
      if (!(_la == temporalParser::TNOT

      || _la == temporalParser::NOT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(255);
      tformula(8);
      break;
    }

    case 4: {
      setState(256);
      match(temporalParser::NEXT);
      setState(258);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
      case 1: {
        setState(257);
        match(temporalParser::LSQUARED);
        break;
      }

      default:
        break;
      }
      setState(261);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
      case 1: {
        setState(260);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(264);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
      case 1: {
        setState(263);
        match(temporalParser::RSQUARED);
        break;
      }

      default:
        break;
      }
      setState(266);
      tformula(7);
      break;
    }

    case 5: {
      setState(267);
      match(temporalParser::EVENTUALLY);
      setState(268);
      tformula(6);
      break;
    }

    case 6: {
      setState(269);
      match(temporalParser::DT_AND);
      break;
    }

    case 7: {
      setState(270);
      booleanLayer();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(284);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(282);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(273);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(274);
          _la = _input->LA(1);
          if (!(_la == temporalParser::UNTIL

          || _la == temporalParser::RELEASE)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(275);
          tformula(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(276);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(277);
          _la = _input->LA(1);
          if (!(_la == temporalParser::TAND

          || _la == temporalParser::AND)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(278);
          tformula(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(279);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(280);
          _la = _input->LA(1);
          if (!(((((_la - 27) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 27)) & ((1ULL << (temporalParser::TOR - 27))
            | (1ULL << (temporalParser::BOR - 27))
            | (1ULL << (temporalParser::OR - 27)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(281);
          tformula(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(286);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Dt_nextContext ------------------------------------------------------------------

temporalParser::Dt_nextContext::Dt_nextContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Dt_nextContext::UINTEGER() {
  return getToken(temporalParser::UINTEGER, 0);
}

tree::TerminalNode* temporalParser::Dt_nextContext::DOTS() {
  return getToken(temporalParser::DOTS, 0);
}


size_t temporalParser::Dt_nextContext::getRuleIndex() const {
  return temporalParser::RuleDt_next;
}

void temporalParser::Dt_nextContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_next(this);
}

void temporalParser::Dt_nextContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_next(this);
}

temporalParser::Dt_nextContext* temporalParser::dt_next() {
  Dt_nextContext *_localctx = _tracker.createInstance<Dt_nextContext>(_ctx, getState());
  enterRule(_localctx, 12, temporalParser::RuleDt_next);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(287);
    match(temporalParser::T__2);
    setState(288);
    match(temporalParser::UINTEGER);
    setState(289);
    match(temporalParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_next_andContext ------------------------------------------------------------------

temporalParser::Dt_next_andContext::Dt_next_andContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Dt_next_andContext::UINTEGER() {
  return getToken(temporalParser::UINTEGER, 0);
}

tree::TerminalNode* temporalParser::Dt_next_andContext::BAND() {
  return getToken(temporalParser::BAND, 0);
}

tree::TerminalNode* temporalParser::Dt_next_andContext::DOTS() {
  return getToken(temporalParser::DOTS, 0);
}


size_t temporalParser::Dt_next_andContext::getRuleIndex() const {
  return temporalParser::RuleDt_next_and;
}

void temporalParser::Dt_next_andContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_next_and(this);
}

void temporalParser::Dt_next_andContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_next_and(this);
}

temporalParser::Dt_next_andContext* temporalParser::dt_next_and() {
  Dt_next_andContext *_localctx = _tracker.createInstance<Dt_next_andContext>(_ctx, getState());
  enterRule(_localctx, 14, temporalParser::RuleDt_next_and);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(291);
    match(temporalParser::T__3);
    setState(292);
    match(temporalParser::UINTEGER);
    setState(293);
    match(temporalParser::BAND);
    setState(294);
    match(temporalParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_ncrepsContext ------------------------------------------------------------------

temporalParser::Dt_ncrepsContext::Dt_ncrepsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Dt_ncrepsContext::UINTEGER() {
  return getToken(temporalParser::UINTEGER, 0);
}

tree::TerminalNode* temporalParser::Dt_ncrepsContext::DOTS() {
  return getToken(temporalParser::DOTS, 0);
}

tree::TerminalNode* temporalParser::Dt_ncrepsContext::IMPLO() {
  return getToken(temporalParser::IMPLO, 0);
}

tree::TerminalNode* temporalParser::Dt_ncrepsContext::ASS() {
  return getToken(temporalParser::ASS, 0);
}

tree::TerminalNode* temporalParser::Dt_ncrepsContext::COL() {
  return getToken(temporalParser::COL, 0);
}

tree::TerminalNode* temporalParser::Dt_ncrepsContext::SCOL() {
  return getToken(temporalParser::SCOL, 0);
}


size_t temporalParser::Dt_ncrepsContext::getRuleIndex() const {
  return temporalParser::RuleDt_ncreps;
}

void temporalParser::Dt_ncrepsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_ncreps(this);
}

void temporalParser::Dt_ncrepsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_ncreps(this);
}

temporalParser::Dt_ncrepsContext* temporalParser::dt_ncreps() {
  Dt_ncrepsContext *_localctx = _tracker.createInstance<Dt_ncrepsContext>(_ctx, getState());
  enterRule(_localctx, 16, temporalParser::RuleDt_ncreps);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(296);
    match(temporalParser::T__4);
    setState(297);
    _la = _input->LA(1);
    if (!(_la == temporalParser::IMPLO

    || _la == temporalParser::ASS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(298);
    match(temporalParser::UINTEGER);
    setState(299);
    match(temporalParser::T__5);
    setState(300);
    _la = _input->LA(1);
    if (!(_la == temporalParser::SCOL

    || _la == temporalParser::COL)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(301);
    match(temporalParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartBooleanContext ------------------------------------------------------------------

temporalParser::StartBooleanContext::StartBooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::BooleanContext* temporalParser::StartBooleanContext::boolean() {
  return getRuleContext<temporalParser::BooleanContext>(0);
}

tree::TerminalNode* temporalParser::StartBooleanContext::EOF() {
  return getToken(temporalParser::EOF, 0);
}


size_t temporalParser::StartBooleanContext::getRuleIndex() const {
  return temporalParser::RuleStartBoolean;
}

void temporalParser::StartBooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartBoolean(this);
}

void temporalParser::StartBooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartBoolean(this);
}

temporalParser::StartBooleanContext* temporalParser::startBoolean() {
  StartBooleanContext *_localctx = _tracker.createInstance<StartBooleanContext>(_ctx, getState());
  enterRule(_localctx, 18, temporalParser::RuleStartBoolean);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(303);
    boolean(0);
    setState(304);
    match(temporalParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartIntContext ------------------------------------------------------------------

temporalParser::StartIntContext::StartIntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::NumericContext* temporalParser::StartIntContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}

tree::TerminalNode* temporalParser::StartIntContext::EOF() {
  return getToken(temporalParser::EOF, 0);
}


size_t temporalParser::StartIntContext::getRuleIndex() const {
  return temporalParser::RuleStartInt;
}

void temporalParser::StartIntContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartInt(this);
}

void temporalParser::StartIntContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartInt(this);
}

temporalParser::StartIntContext* temporalParser::startInt() {
  StartIntContext *_localctx = _tracker.createInstance<StartIntContext>(_ctx, getState());
  enterRule(_localctx, 20, temporalParser::RuleStartInt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(306);
    numeric(0);
    setState(307);
    match(temporalParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartFloatContext ------------------------------------------------------------------

temporalParser::StartFloatContext::StartFloatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::NumericContext* temporalParser::StartFloatContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}

tree::TerminalNode* temporalParser::StartFloatContext::EOF() {
  return getToken(temporalParser::EOF, 0);
}


size_t temporalParser::StartFloatContext::getRuleIndex() const {
  return temporalParser::RuleStartFloat;
}

void temporalParser::StartFloatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartFloat(this);
}

void temporalParser::StartFloatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartFloat(this);
}

temporalParser::StartFloatContext* temporalParser::startFloat() {
  StartFloatContext *_localctx = _tracker.createInstance<StartFloatContext>(_ctx, getState());
  enterRule(_localctx, 22, temporalParser::RuleStartFloat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(309);
    numeric(0);
    setState(310);
    match(temporalParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

temporalParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::BooleanContext::NOT() {
  return getToken(temporalParser::NOT, 0);
}

std::vector<temporalParser::BooleanContext *> temporalParser::BooleanContext::boolean() {
  return getRuleContexts<temporalParser::BooleanContext>();
}

temporalParser::BooleanContext* temporalParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<temporalParser::BooleanContext>(i);
}

std::vector<temporalParser::NumericContext *> temporalParser::BooleanContext::numeric() {
  return getRuleContexts<temporalParser::NumericContext>();
}

temporalParser::NumericContext* temporalParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<temporalParser::NumericContext>(i);
}

temporalParser::RelopContext* temporalParser::BooleanContext::relop() {
  return getRuleContext<temporalParser::RelopContext>(0);
}

tree::TerminalNode* temporalParser::BooleanContext::EQ() {
  return getToken(temporalParser::EQ, 0);
}

tree::TerminalNode* temporalParser::BooleanContext::NEQ() {
  return getToken(temporalParser::NEQ, 0);
}

temporalParser::BooleanAtomContext* temporalParser::BooleanContext::booleanAtom() {
  return getRuleContext<temporalParser::BooleanAtomContext>(0);
}

tree::TerminalNode* temporalParser::BooleanContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

tree::TerminalNode* temporalParser::BooleanContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

tree::TerminalNode* temporalParser::BooleanContext::AND() {
  return getToken(temporalParser::AND, 0);
}

tree::TerminalNode* temporalParser::BooleanContext::OR() {
  return getToken(temporalParser::OR, 0);
}


size_t temporalParser::BooleanContext::getRuleIndex() const {
  return temporalParser::RuleBoolean;
}

void temporalParser::BooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolean(this);
}

void temporalParser::BooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolean(this);
}


temporalParser::BooleanContext* temporalParser::boolean() {
   return boolean(0);
}

temporalParser::BooleanContext* temporalParser::boolean(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  temporalParser::BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, parentState);
  temporalParser::BooleanContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, temporalParser::RuleBoolean, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(333);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      setState(313);
      match(temporalParser::NOT);
      setState(314);
      boolean(11);
      break;
    }

    case 2: {
      setState(315);
      numeric(0);
      setState(316);
      relop();
      setState(317);
      numeric(0);
      break;
    }

    case 3: {
      setState(319);
      numeric(0);
      setState(320);
      match(temporalParser::EQ);
      setState(321);
      numeric(0);
      break;
    }

    case 4: {
      setState(323);
      numeric(0);
      setState(324);
      match(temporalParser::NEQ);
      setState(325);
      numeric(0);
      break;
    }

    case 5: {
      setState(327);
      booleanAtom();
      break;
    }

    case 6: {
      setState(328);
      numeric(0);
      break;
    }

    case 7: {
      setState(329);
      match(temporalParser::LROUND);
      setState(330);
      boolean(0);
      setState(331);
      match(temporalParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(349);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(347);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(335);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(336);
          match(temporalParser::EQ);
          setState(337);
          boolean(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(338);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(339);
          match(temporalParser::NEQ);
          setState(340);
          boolean(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(341);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(342);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(temporalParser::AND);
          setState(343);
          boolean(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(344);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(345);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(temporalParser::OR);
          setState(346);
          boolean(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(351);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- BooleanAtomContext ------------------------------------------------------------------

temporalParser::BooleanAtomContext::BooleanAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::BooleanAtomContext::BOOLEAN_CONSTANT() {
  return getToken(temporalParser::BOOLEAN_CONSTANT, 0);
}

tree::TerminalNode* temporalParser::BooleanAtomContext::BOOLEAN_VARIABLE() {
  return getToken(temporalParser::BOOLEAN_VARIABLE, 0);
}


size_t temporalParser::BooleanAtomContext::getRuleIndex() const {
  return temporalParser::RuleBooleanAtom;
}

void temporalParser::BooleanAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanAtom(this);
}

void temporalParser::BooleanAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanAtom(this);
}

temporalParser::BooleanAtomContext* temporalParser::booleanAtom() {
  BooleanAtomContext *_localctx = _tracker.createInstance<BooleanAtomContext>(_ctx, getState());
  enterRule(_localctx, 26, temporalParser::RuleBooleanAtom);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    _la = _input->LA(1);
    if (!(_la == temporalParser::BOOLEAN_CONSTANT

    || _la == temporalParser::BOOLEAN_VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericContext ------------------------------------------------------------------

temporalParser::NumericContext::NumericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::NumericContext::NEG() {
  return getToken(temporalParser::NEG, 0);
}

std::vector<temporalParser::NumericContext *> temporalParser::NumericContext::numeric() {
  return getRuleContexts<temporalParser::NumericContext>();
}

temporalParser::NumericContext* temporalParser::NumericContext::numeric(size_t i) {
  return getRuleContext<temporalParser::NumericContext>(i);
}

temporalParser::IntAtomContext* temporalParser::NumericContext::intAtom() {
  return getRuleContext<temporalParser::IntAtomContext>(0);
}

temporalParser::FloatAtomContext* temporalParser::NumericContext::floatAtom() {
  return getRuleContext<temporalParser::FloatAtomContext>(0);
}

tree::TerminalNode* temporalParser::NumericContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

tree::TerminalNode* temporalParser::NumericContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

tree::TerminalNode* temporalParser::NumericContext::TIMES() {
  return getToken(temporalParser::TIMES, 0);
}

tree::TerminalNode* temporalParser::NumericContext::DIV() {
  return getToken(temporalParser::DIV, 0);
}

tree::TerminalNode* temporalParser::NumericContext::PLUS() {
  return getToken(temporalParser::PLUS, 0);
}

tree::TerminalNode* temporalParser::NumericContext::MINUS() {
  return getToken(temporalParser::MINUS, 0);
}

tree::TerminalNode* temporalParser::NumericContext::LSHIFT() {
  return getToken(temporalParser::LSHIFT, 0);
}

tree::TerminalNode* temporalParser::NumericContext::RSHIFT() {
  return getToken(temporalParser::RSHIFT, 0);
}

tree::TerminalNode* temporalParser::NumericContext::BAND() {
  return getToken(temporalParser::BAND, 0);
}

tree::TerminalNode* temporalParser::NumericContext::BXOR() {
  return getToken(temporalParser::BXOR, 0);
}

tree::TerminalNode* temporalParser::NumericContext::BOR() {
  return getToken(temporalParser::BOR, 0);
}

temporalParser::RangeContext* temporalParser::NumericContext::range() {
  return getRuleContext<temporalParser::RangeContext>(0);
}


size_t temporalParser::NumericContext::getRuleIndex() const {
  return temporalParser::RuleNumeric;
}

void temporalParser::NumericContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void temporalParser::NumericContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}


temporalParser::NumericContext* temporalParser::numeric() {
   return numeric(0);
}

temporalParser::NumericContext* temporalParser::numeric(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  temporalParser::NumericContext *_localctx = _tracker.createInstance<NumericContext>(_ctx, parentState);
  temporalParser::NumericContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 28;
  enterRecursionRule(_localctx, 28, temporalParser::RuleNumeric, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(363);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::NEG: {
        setState(355);
        match(temporalParser::NEG);
        setState(356);
        numeric(12);
        break;
      }

      case temporalParser::INT_VARIABLE:
      case temporalParser::SINTEGER:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX:
      case temporalParser::VERILOG_BINARY: {
        setState(357);
        intAtom();
        break;
      }

      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE: {
        setState(358);
        floatAtom();
        break;
      }

      case temporalParser::LROUND: {
        setState(359);
        match(temporalParser::LROUND);
        setState(360);
        numeric(0);
        setState(361);
        match(temporalParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(390);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(388);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(365);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(366);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == temporalParser::TIMES

          || _la == temporalParser::DIV)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(367);
          numeric(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(368);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(369);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == temporalParser::PLUS

          || _la == temporalParser::MINUS)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(370);
          numeric(10);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(371);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(372);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::LSHIFT);
          setState(373);
          numeric(9);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(374);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(375);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::RSHIFT);
          setState(376);
          numeric(8);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(377);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(378);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BAND);
          setState(379);
          numeric(7);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(380);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(381);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BXOR);
          setState(382);
          numeric(6);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(383);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(384);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BOR);
          setState(385);
          numeric(5);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(386);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(387);
          range();
          break;
        }

        default:
          break;
        } 
      }
      setState(392);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RangeContext ------------------------------------------------------------------

temporalParser::RangeContext::RangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::RangeContext::LSQUARED() {
  return getToken(temporalParser::LSQUARED, 0);
}

tree::TerminalNode* temporalParser::RangeContext::RSQUARED() {
  return getToken(temporalParser::RSQUARED, 0);
}

std::vector<tree::TerminalNode *> temporalParser::RangeContext::SINTEGER() {
  return getTokens(temporalParser::SINTEGER);
}

tree::TerminalNode* temporalParser::RangeContext::SINTEGER(size_t i) {
  return getToken(temporalParser::SINTEGER, i);
}

std::vector<tree::TerminalNode *> temporalParser::RangeContext::UINTEGER() {
  return getTokens(temporalParser::UINTEGER);
}

tree::TerminalNode* temporalParser::RangeContext::UINTEGER(size_t i) {
  return getToken(temporalParser::UINTEGER, i);
}

tree::TerminalNode* temporalParser::RangeContext::COL() {
  return getToken(temporalParser::COL, 0);
}


size_t temporalParser::RangeContext::getRuleIndex() const {
  return temporalParser::RuleRange;
}

void temporalParser::RangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRange(this);
}

void temporalParser::RangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRange(this);
}

temporalParser::RangeContext* temporalParser::range() {
  RangeContext *_localctx = _tracker.createInstance<RangeContext>(_ctx, getState());
  enterRule(_localctx, 30, temporalParser::RuleRange);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(393);
    match(temporalParser::LSQUARED);
    setState(394);
    _la = _input->LA(1);
    if (!(_la == temporalParser::SINTEGER

    || _la == temporalParser::UINTEGER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(397);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == temporalParser::COL) {
      setState(395);
      match(temporalParser::COL);
      setState(396);
      _la = _input->LA(1);
      if (!(_la == temporalParser::SINTEGER

      || _la == temporalParser::UINTEGER)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(399);
    match(temporalParser::RSQUARED);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntAtomContext ------------------------------------------------------------------

temporalParser::IntAtomContext::IntAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::Int_constantContext* temporalParser::IntAtomContext::int_constant() {
  return getRuleContext<temporalParser::Int_constantContext>(0);
}

tree::TerminalNode* temporalParser::IntAtomContext::INT_VARIABLE() {
  return getToken(temporalParser::INT_VARIABLE, 0);
}


size_t temporalParser::IntAtomContext::getRuleIndex() const {
  return temporalParser::RuleIntAtom;
}

void temporalParser::IntAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntAtom(this);
}

void temporalParser::IntAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntAtom(this);
}

temporalParser::IntAtomContext* temporalParser::intAtom() {
  IntAtomContext *_localctx = _tracker.createInstance<IntAtomContext>(_ctx, getState());
  enterRule(_localctx, 32, temporalParser::RuleIntAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(403);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::SINTEGER:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX:
      case temporalParser::VERILOG_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(401);
        int_constant();
        break;
      }

      case temporalParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(402);
        match(temporalParser::INT_VARIABLE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Int_constantContext ------------------------------------------------------------------

temporalParser::Int_constantContext::Int_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Int_constantContext::GCC_BINARY() {
  return getToken(temporalParser::GCC_BINARY, 0);
}

tree::TerminalNode* temporalParser::Int_constantContext::SINTEGER() {
  return getToken(temporalParser::SINTEGER, 0);
}

tree::TerminalNode* temporalParser::Int_constantContext::CONST_SUFFIX() {
  return getToken(temporalParser::CONST_SUFFIX, 0);
}

tree::TerminalNode* temporalParser::Int_constantContext::UINTEGER() {
  return getToken(temporalParser::UINTEGER, 0);
}

tree::TerminalNode* temporalParser::Int_constantContext::VERILOG_BINARY() {
  return getToken(temporalParser::VERILOG_BINARY, 0);
}

tree::TerminalNode* temporalParser::Int_constantContext::HEX() {
  return getToken(temporalParser::HEX, 0);
}


size_t temporalParser::Int_constantContext::getRuleIndex() const {
  return temporalParser::RuleInt_constant;
}

void temporalParser::Int_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInt_constant(this);
}

void temporalParser::Int_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInt_constant(this);
}

temporalParser::Int_constantContext* temporalParser::int_constant() {
  Int_constantContext *_localctx = _tracker.createInstance<Int_constantContext>(_ctx, getState());
  enterRule(_localctx, 34, temporalParser::RuleInt_constant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(419);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(405);
      match(temporalParser::GCC_BINARY);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(406);
      match(temporalParser::SINTEGER);
      setState(408);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
      case 1: {
        setState(407);
        match(temporalParser::CONST_SUFFIX);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(410);
      match(temporalParser::UINTEGER);
      setState(412);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
      case 1: {
        setState(411);
        match(temporalParser::CONST_SUFFIX);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(415);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER) {
        setState(414);
        match(temporalParser::UINTEGER);
      }
      setState(417);
      match(temporalParser::VERILOG_BINARY);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(418);
      match(temporalParser::HEX);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FloatAtomContext ------------------------------------------------------------------

temporalParser::FloatAtomContext::FloatAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::FloatAtomContext::FLOAT_CONSTANT() {
  return getToken(temporalParser::FLOAT_CONSTANT, 0);
}

tree::TerminalNode* temporalParser::FloatAtomContext::FLOAT_VARIABLE() {
  return getToken(temporalParser::FLOAT_VARIABLE, 0);
}


size_t temporalParser::FloatAtomContext::getRuleIndex() const {
  return temporalParser::RuleFloatAtom;
}

void temporalParser::FloatAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloatAtom(this);
}

void temporalParser::FloatAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloatAtom(this);
}

temporalParser::FloatAtomContext* temporalParser::floatAtom() {
  FloatAtomContext *_localctx = _tracker.createInstance<FloatAtomContext>(_ctx, getState());
  enterRule(_localctx, 36, temporalParser::RuleFloatAtom);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(421);
    _la = _input->LA(1);
    if (!(_la == temporalParser::FLOAT_CONSTANT

    || _la == temporalParser::FLOAT_VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelopContext ------------------------------------------------------------------

temporalParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::RelopContext::GT() {
  return getToken(temporalParser::GT, 0);
}

tree::TerminalNode* temporalParser::RelopContext::GE() {
  return getToken(temporalParser::GE, 0);
}

tree::TerminalNode* temporalParser::RelopContext::LT() {
  return getToken(temporalParser::LT, 0);
}

tree::TerminalNode* temporalParser::RelopContext::LE() {
  return getToken(temporalParser::LE, 0);
}


size_t temporalParser::RelopContext::getRuleIndex() const {
  return temporalParser::RuleRelop;
}

void temporalParser::RelopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void temporalParser::RelopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}

temporalParser::RelopContext* temporalParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 38, temporalParser::RuleRelop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(423);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << temporalParser::GT)
      | (1ULL << temporalParser::GE)
      | (1ULL << temporalParser::LT)
      | (1ULL << temporalParser::LE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Cls_opContext ------------------------------------------------------------------

temporalParser::Cls_opContext::Cls_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Cls_opContext::RANGE() {
  return getToken(temporalParser::RANGE, 0);
}

tree::TerminalNode* temporalParser::Cls_opContext::GT() {
  return getToken(temporalParser::GT, 0);
}

tree::TerminalNode* temporalParser::Cls_opContext::GE() {
  return getToken(temporalParser::GE, 0);
}

tree::TerminalNode* temporalParser::Cls_opContext::LT() {
  return getToken(temporalParser::LT, 0);
}

tree::TerminalNode* temporalParser::Cls_opContext::LE() {
  return getToken(temporalParser::LE, 0);
}

tree::TerminalNode* temporalParser::Cls_opContext::EQ() {
  return getToken(temporalParser::EQ, 0);
}


size_t temporalParser::Cls_opContext::getRuleIndex() const {
  return temporalParser::RuleCls_op;
}

void temporalParser::Cls_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCls_op(this);
}

void temporalParser::Cls_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCls_op(this);
}

temporalParser::Cls_opContext* temporalParser::cls_op() {
  Cls_opContext *_localctx = _tracker.createInstance<Cls_opContext>(_ctx, getState());
  enterRule(_localctx, 40, temporalParser::RuleCls_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(425);
    _la = _input->LA(1);
    if (!(((((_la - 52) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 52)) & ((1ULL << (temporalParser::GT - 52))
      | (1ULL << (temporalParser::GE - 52))
      | (1ULL << (temporalParser::LT - 52))
      | (1ULL << (temporalParser::LE - 52))
      | (1ULL << (temporalParser::EQ - 52))
      | (1ULL << (temporalParser::RANGE - 52)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool temporalParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 3: return sereSempred(antlrcpp::downCast<SereContext *>(context), predicateIndex);
    case 5: return tformulaSempred(antlrcpp::downCast<TformulaContext *>(context), predicateIndex);
    case 12: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 14: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool temporalParser::sereSempred(SereContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 11);
    case 1: return precpred(_ctx, 10);
    case 2: return precpred(_ctx, 8);
    case 3: return precpred(_ctx, 7);
    case 4: return precpred(_ctx, 3);
    case 5: return precpred(_ctx, 2);
    case 6: return precpred(_ctx, 16);
    case 7: return precpred(_ctx, 15);

  default:
    break;
  }
  return true;
}

bool temporalParser::tformulaSempred(TformulaContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 8: return canUseSharedOperator(_input->LT(-1)->getText(),_input->LT(2)->getText());
    case 9: return canTakeThisNot(_input->LT(1)->getText(),_input->LT(2)->getText());
    case 10: return precpred(_ctx, 5);
    case 11: return precpred(_ctx, 4);
    case 12: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool temporalParser::booleanSempred(BooleanContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 13: return precpred(_ctx, 7);
    case 14: return precpred(_ctx, 6);
    case 15: return precpred(_ctx, 5);
    case 16: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

bool temporalParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 17: return precpred(_ctx, 10);
    case 18: return precpred(_ctx, 9);
    case 19: return precpred(_ctx, 8);
    case 20: return precpred(_ctx, 7);
    case 21: return precpred(_ctx, 6);
    case 22: return precpred(_ctx, 5);
    case 23: return precpred(_ctx, 4);
    case 24: return precpred(_ctx, 11);

  default:
    break;
  }
  return true;
}

void temporalParser::initialize() {
  std::call_once(temporalParserOnceFlag, temporalParserInitialize);
}
