
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
      "temporalFunction", "tfunc_arg", "placeholder_domain", "dt_next", 
      "dt_next_and", "dt_ncreps", "startBoolean", "startInt", "startLogic", 
      "startFloat", "startString", "boolean", "booleanAtom", "numeric", 
      "range", "sm_range", "min_dollar", "max_dollar", "sm_constant", "intAtom", 
      "int_constant", "logicAtom", "logic_constant", "floatAtom", "string", 
      "stringAtom", "nonTemporalFunction", "pfunc_arg", "relop", "cls_op"
    },
    std::vector<std::string>{
      "", "'assert property'", "'@(posedge'", "','", "'..##'", "'..#'", 
      "'..['", "']@'", "", "'..&&..'", "", "", "", "", "'R'", "'..'", "'=>'", 
      "'->'", "'<->'", "", "", "'='", "'##'", "';'", "'first_match'", "'not'", 
      "'and'", "'intersect'", "'or'", "", "", "", "", "", "", "", "'.substr'", 
      "", "", "'{'", "'}'", "'['", "']'", "'('", "')'", "'inside'", "", 
      "", "", "", "", "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", 
      "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", "'|'", "'^'", "'~'", 
      "'<<'", "'>>'", "'&&'", "'||'", "'!'", "':'", "'::'", "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "PLACEHOLDER", "DT_AND", "EVENTUALLY", 
      "ALWAYS", "NEXT", "UNTIL", "RELEASE", "DOTS", "IMPL", "IMPLO", "IFF", 
      "SEREIMPL", "SEREIMPLO", "ASS", "DELAY", "SCOL", "FIRST_MATCH", "TNOT", 
      "TAND", "INTERSECT", "TOR", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", 
      "INT_VARIABLE", "CONST_SUFFIX", "LOGIC_VARIABLE", "FLOAT_CONSTANT", 
      "FLOAT_VARIABLE", "SUBSTR", "STRING_CONSTANT", "STRING_VARIABLE", 
      "LCURLY", "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "INSIDE", 
      "FUNCTION", "SINTEGER", "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", 
      "VERILOG_BINARY", "FVL", "SINGLE_QUOTE", "PLUS", "MINUS", "TIMES", 
      "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "BAND", "BOR", "BXOR", 
      "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT", "COL", "DCOL", "DOLLAR", 
      "RANGE", "CLS_TYPE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,79,640,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,86,8,0,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,3,1,107,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,118,8,2,1,2,1,2,
  	3,2,122,8,2,1,2,1,2,1,2,1,2,3,2,128,8,2,1,2,1,2,3,2,132,8,2,1,2,1,2,1,
  	2,3,2,137,8,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,3,3,157,8,3,1,3,3,3,160,8,3,1,3,3,3,163,8,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,3,3,171,8,3,1,3,3,3,174,8,3,1,3,3,3,177,8,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,3,3,186,8,3,1,3,1,3,1,3,1,3,1,3,3,3,193,8,3,1,3,1,3,3,
  	3,197,8,3,1,3,3,3,200,8,3,1,3,3,3,203,8,3,1,3,3,3,206,8,3,1,3,3,3,209,
  	8,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,217,8,3,1,3,1,3,1,3,1,3,1,3,3,3,224,8,
  	3,1,3,3,3,227,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,
  	241,8,3,1,3,3,3,244,8,3,1,3,3,3,247,8,3,1,3,3,3,250,8,3,1,3,3,3,253,8,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,266,8,3,1,3,3,3,269,
  	8,3,1,3,3,3,272,8,3,1,3,1,3,1,3,1,3,1,3,5,3,279,8,3,10,3,12,3,282,9,3,
  	1,4,1,4,1,4,1,4,1,4,1,4,3,4,290,8,4,1,4,1,4,1,4,1,4,1,4,3,4,297,8,4,1,
  	4,3,4,300,8,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,309,8,5,1,5,1,5,3,5,313,
  	8,5,1,5,1,5,1,5,1,5,1,5,3,5,320,8,5,1,5,3,5,323,8,5,1,5,3,5,326,8,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,336,8,5,1,5,3,5,339,8,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,5,5,350,8,5,10,5,12,5,353,9,5,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,5,6,364,8,6,10,6,12,6,367,9,6,1,6,1,6,3,6,371,8,6,
  	1,7,1,7,1,7,1,7,1,7,3,7,378,8,7,1,7,3,7,381,8,7,1,8,1,8,1,8,5,8,386,8,
  	8,10,8,12,8,389,9,8,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,13,1,13,1,13,1,14,1,14,1,14,
  	1,15,1,15,1,15,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,
  	1,17,3,17,431,8,17,1,17,1,17,5,17,435,8,17,10,17,12,17,438,9,17,1,17,
  	1,17,3,17,442,8,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,3,17,476,8,17,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,5,17,490,8,17,10,17,12,17,
  	493,9,17,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,3,19,508,8,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,5,19,
  	533,8,19,10,19,12,19,536,9,19,1,20,1,20,1,20,1,20,3,20,542,8,20,1,20,
  	1,20,1,21,1,21,1,21,3,21,549,8,21,1,21,1,21,1,21,3,21,554,8,21,1,21,1,
  	21,1,22,1,22,1,23,1,23,1,24,1,24,1,25,1,25,3,25,566,8,25,1,26,1,26,1,
  	26,3,26,571,8,26,1,26,1,26,3,26,575,8,26,1,26,3,26,578,8,26,1,27,1,27,
  	1,27,3,27,583,8,27,1,28,3,28,586,8,28,1,28,1,28,1,29,1,29,1,30,1,30,1,
  	30,1,30,1,30,1,30,3,30,598,8,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,
  	30,1,30,1,30,3,30,610,8,30,1,30,5,30,613,8,30,10,30,12,30,616,9,30,1,
  	31,1,31,1,32,1,32,1,32,1,32,1,32,5,32,625,8,32,10,32,12,32,628,9,32,1,
  	32,1,32,1,33,1,33,3,33,634,8,33,1,34,1,34,1,35,1,35,1,35,0,5,6,10,34,
  	38,60,36,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,
  	44,46,48,50,52,54,56,58,60,62,64,66,68,70,0,17,2,0,15,15,74,74,2,0,48,
  	48,76,76,2,0,26,27,71,71,3,0,28,28,66,66,72,72,2,0,25,25,73,73,1,0,13,
  	14,2,0,26,26,71,71,2,0,17,17,21,21,2,0,23,23,74,74,1,0,29,30,1,0,57,58,
  	1,0,55,56,1,0,47,48,1,0,34,35,1,0,37,38,1,0,59,62,2,0,59,63,77,77,732,
  	0,85,1,0,0,0,2,106,1,0,0,0,4,136,1,0,0,0,6,226,1,0,0,0,8,299,1,0,0,0,
  	10,338,1,0,0,0,12,370,1,0,0,0,14,380,1,0,0,0,16,382,1,0,0,0,18,390,1,
  	0,0,0,20,394,1,0,0,0,22,399,1,0,0,0,24,406,1,0,0,0,26,409,1,0,0,0,28,
  	412,1,0,0,0,30,415,1,0,0,0,32,418,1,0,0,0,34,475,1,0,0,0,36,494,1,0,0,
  	0,38,507,1,0,0,0,40,537,1,0,0,0,42,545,1,0,0,0,44,557,1,0,0,0,46,559,
  	1,0,0,0,48,561,1,0,0,0,50,565,1,0,0,0,52,577,1,0,0,0,54,582,1,0,0,0,56,
  	585,1,0,0,0,58,589,1,0,0,0,60,597,1,0,0,0,62,617,1,0,0,0,64,619,1,0,0,
  	0,66,633,1,0,0,0,68,635,1,0,0,0,70,637,1,0,0,0,72,73,5,11,0,0,73,74,5,
  	43,0,0,74,75,3,4,2,0,75,76,5,44,0,0,76,77,5,0,0,1,77,86,1,0,0,0,78,79,
  	5,11,0,0,79,80,3,4,2,0,80,81,5,0,0,1,81,86,1,0,0,0,82,83,3,2,1,0,83,84,
  	5,0,0,1,84,86,1,0,0,0,85,72,1,0,0,0,85,78,1,0,0,0,85,82,1,0,0,0,86,1,
  	1,0,0,0,87,88,5,1,0,0,88,89,5,43,0,0,89,90,3,2,1,0,90,91,5,44,0,0,91,
  	107,1,0,0,0,92,93,5,43,0,0,93,94,3,2,1,0,94,95,5,44,0,0,95,107,1,0,0,
  	0,96,97,5,2,0,0,97,98,3,34,17,0,98,99,5,44,0,0,99,100,3,2,1,0,100,107,
  	1,0,0,0,101,102,5,43,0,0,102,103,3,4,2,0,103,104,5,44,0,0,104,107,1,0,
  	0,0,105,107,3,4,2,0,106,87,1,0,0,0,106,92,1,0,0,0,106,96,1,0,0,0,106,
  	101,1,0,0,0,106,105,1,0,0,0,107,3,1,0,0,0,108,109,3,10,5,0,109,110,5,
  	16,0,0,110,111,3,10,5,0,111,137,1,0,0,0,112,113,3,10,5,0,113,114,5,17,
  	0,0,114,115,3,10,5,0,115,137,1,0,0,0,116,118,5,39,0,0,117,116,1,0,0,0,
  	117,118,1,0,0,0,118,119,1,0,0,0,119,121,3,6,3,0,120,122,5,40,0,0,121,
  	120,1,0,0,0,121,122,1,0,0,0,122,123,1,0,0,0,123,124,5,19,0,0,124,125,
  	3,10,5,0,125,137,1,0,0,0,126,128,5,39,0,0,127,126,1,0,0,0,127,128,1,0,
  	0,0,128,129,1,0,0,0,129,131,3,6,3,0,130,132,5,40,0,0,131,130,1,0,0,0,
  	131,132,1,0,0,0,132,133,1,0,0,0,133,134,5,20,0,0,134,135,3,10,5,0,135,
  	137,1,0,0,0,136,108,1,0,0,0,136,112,1,0,0,0,136,117,1,0,0,0,136,127,1,
  	0,0,0,137,5,1,0,0,0,138,139,6,3,-1,0,139,140,5,24,0,0,140,141,5,43,0,
  	0,141,142,3,6,3,0,142,143,5,44,0,0,143,227,1,0,0,0,144,145,5,43,0,0,145,
  	146,3,6,3,0,146,147,5,44,0,0,147,227,1,0,0,0,148,149,5,39,0,0,149,150,
  	3,6,3,0,150,151,5,40,0,0,151,227,1,0,0,0,152,153,3,8,4,0,153,154,5,41,
  	0,0,154,156,5,21,0,0,155,157,5,48,0,0,156,155,1,0,0,0,156,157,1,0,0,0,
  	157,159,1,0,0,0,158,160,7,0,0,0,159,158,1,0,0,0,159,160,1,0,0,0,160,162,
  	1,0,0,0,161,163,7,1,0,0,162,161,1,0,0,0,162,163,1,0,0,0,163,164,1,0,0,
  	0,164,165,5,42,0,0,165,227,1,0,0,0,166,167,3,8,4,0,167,168,5,41,0,0,168,
  	170,5,17,0,0,169,171,5,48,0,0,170,169,1,0,0,0,170,171,1,0,0,0,171,173,
  	1,0,0,0,172,174,7,0,0,0,173,172,1,0,0,0,173,174,1,0,0,0,174,176,1,0,0,
  	0,175,177,7,1,0,0,176,175,1,0,0,0,176,177,1,0,0,0,177,178,1,0,0,0,178,
  	179,5,42,0,0,179,227,1,0,0,0,180,185,3,22,11,0,181,182,5,43,0,0,182,183,
  	3,16,8,0,183,184,5,44,0,0,184,186,1,0,0,0,185,181,1,0,0,0,185,186,1,0,
  	0,0,186,227,1,0,0,0,187,192,5,9,0,0,188,189,5,43,0,0,189,190,3,16,8,0,
  	190,191,5,44,0,0,191,193,1,0,0,0,192,188,1,0,0,0,192,193,1,0,0,0,193,
  	227,1,0,0,0,194,196,5,22,0,0,195,197,5,41,0,0,196,195,1,0,0,0,196,197,
  	1,0,0,0,197,199,1,0,0,0,198,200,5,48,0,0,199,198,1,0,0,0,199,200,1,0,
  	0,0,200,202,1,0,0,0,201,203,7,0,0,0,202,201,1,0,0,0,202,203,1,0,0,0,203,
  	205,1,0,0,0,204,206,7,1,0,0,205,204,1,0,0,0,205,206,1,0,0,0,206,208,1,
  	0,0,0,207,209,5,42,0,0,208,207,1,0,0,0,208,209,1,0,0,0,209,210,1,0,0,
  	0,210,227,3,6,3,6,211,216,3,18,9,0,212,213,5,43,0,0,213,214,3,16,8,0,
  	214,215,5,44,0,0,215,217,1,0,0,0,216,212,1,0,0,0,216,217,1,0,0,0,217,
  	227,1,0,0,0,218,223,3,20,10,0,219,220,5,43,0,0,220,221,3,16,8,0,221,222,
  	5,44,0,0,222,224,1,0,0,0,223,219,1,0,0,0,223,224,1,0,0,0,224,227,1,0,
  	0,0,225,227,3,8,4,0,226,138,1,0,0,0,226,144,1,0,0,0,226,148,1,0,0,0,226,
  	152,1,0,0,0,226,166,1,0,0,0,226,180,1,0,0,0,226,187,1,0,0,0,226,194,1,
  	0,0,0,226,211,1,0,0,0,226,218,1,0,0,0,226,225,1,0,0,0,227,280,1,0,0,0,
  	228,229,10,11,0,0,229,230,5,65,0,0,230,279,3,6,3,12,231,232,10,10,0,0,
  	232,233,7,2,0,0,233,279,3,6,3,11,234,235,10,8,0,0,235,236,7,3,0,0,236,
  	279,3,6,3,9,237,238,10,7,0,0,238,240,5,22,0,0,239,241,5,41,0,0,240,239,
  	1,0,0,0,240,241,1,0,0,0,241,243,1,0,0,0,242,244,5,48,0,0,243,242,1,0,
  	0,0,243,244,1,0,0,0,244,246,1,0,0,0,245,247,7,0,0,0,246,245,1,0,0,0,246,
  	247,1,0,0,0,247,249,1,0,0,0,248,250,7,1,0,0,249,248,1,0,0,0,249,250,1,
  	0,0,0,250,252,1,0,0,0,251,253,5,42,0,0,252,251,1,0,0,0,252,253,1,0,0,
  	0,253,254,1,0,0,0,254,279,3,6,3,8,255,256,10,3,0,0,256,257,5,74,0,0,257,
  	279,3,6,3,4,258,259,10,2,0,0,259,260,5,23,0,0,260,279,3,6,3,3,261,262,
  	10,16,0,0,262,263,5,41,0,0,263,265,5,57,0,0,264,266,5,48,0,0,265,264,
  	1,0,0,0,265,266,1,0,0,0,266,268,1,0,0,0,267,269,7,0,0,0,268,267,1,0,0,
  	0,268,269,1,0,0,0,269,271,1,0,0,0,270,272,7,1,0,0,271,270,1,0,0,0,271,
  	272,1,0,0,0,272,273,1,0,0,0,273,279,5,42,0,0,274,275,10,15,0,0,275,276,
  	5,41,0,0,276,277,5,55,0,0,277,279,5,42,0,0,278,228,1,0,0,0,278,231,1,
  	0,0,0,278,234,1,0,0,0,278,237,1,0,0,0,278,255,1,0,0,0,278,258,1,0,0,0,
  	278,261,1,0,0,0,278,274,1,0,0,0,279,282,1,0,0,0,280,278,1,0,0,0,280,281,
  	1,0,0,0,281,7,1,0,0,0,282,280,1,0,0,0,283,284,5,43,0,0,284,285,3,8,4,
  	0,285,286,5,44,0,0,286,300,1,0,0,0,287,300,3,34,17,0,288,290,5,73,0,0,
  	289,288,1,0,0,0,289,290,1,0,0,0,290,291,1,0,0,0,291,296,5,8,0,0,292,293,
  	5,43,0,0,293,294,3,16,8,0,294,295,5,44,0,0,295,297,1,0,0,0,296,292,1,
  	0,0,0,296,297,1,0,0,0,297,300,1,0,0,0,298,300,3,12,6,0,299,283,1,0,0,
  	0,299,287,1,0,0,0,299,289,1,0,0,0,299,298,1,0,0,0,300,9,1,0,0,0,301,302,
  	6,5,-1,0,302,303,5,43,0,0,303,304,3,10,5,0,304,305,5,44,0,0,305,339,1,
  	0,0,0,306,308,4,5,8,0,307,309,5,39,0,0,308,307,1,0,0,0,308,309,1,0,0,
  	0,309,310,1,0,0,0,310,312,3,6,3,0,311,313,5,40,0,0,312,311,1,0,0,0,312,
  	313,1,0,0,0,313,339,1,0,0,0,314,315,4,5,9,0,315,316,7,4,0,0,316,339,3,
  	10,5,8,317,319,5,12,0,0,318,320,5,41,0,0,319,318,1,0,0,0,319,320,1,0,
  	0,0,320,322,1,0,0,0,321,323,5,48,0,0,322,321,1,0,0,0,322,323,1,0,0,0,
  	323,325,1,0,0,0,324,326,5,42,0,0,325,324,1,0,0,0,325,326,1,0,0,0,326,
  	327,1,0,0,0,327,339,3,10,5,7,328,329,5,10,0,0,329,339,3,10,5,6,330,335,
  	5,9,0,0,331,332,5,43,0,0,332,333,3,16,8,0,333,334,5,44,0,0,334,336,1,
  	0,0,0,335,331,1,0,0,0,335,336,1,0,0,0,336,339,1,0,0,0,337,339,3,8,4,0,
  	338,301,1,0,0,0,338,306,1,0,0,0,338,314,1,0,0,0,338,317,1,0,0,0,338,328,
  	1,0,0,0,338,330,1,0,0,0,338,337,1,0,0,0,339,351,1,0,0,0,340,341,10,5,
  	0,0,341,342,7,5,0,0,342,350,3,10,5,5,343,344,10,4,0,0,344,345,7,6,0,0,
  	345,350,3,10,5,5,346,347,10,3,0,0,347,348,7,3,0,0,348,350,3,10,5,4,349,
  	340,1,0,0,0,349,343,1,0,0,0,349,346,1,0,0,0,350,353,1,0,0,0,351,349,1,
  	0,0,0,351,352,1,0,0,0,352,11,1,0,0,0,353,351,1,0,0,0,354,355,5,43,0,0,
  	355,356,3,12,6,0,356,357,5,44,0,0,357,371,1,0,0,0,358,359,5,46,0,0,359,
  	360,5,43,0,0,360,365,3,14,7,0,361,362,5,3,0,0,362,364,3,14,7,0,363,361,
  	1,0,0,0,364,367,1,0,0,0,365,363,1,0,0,0,365,366,1,0,0,0,366,368,1,0,0,
  	0,367,365,1,0,0,0,368,369,5,44,0,0,369,371,1,0,0,0,370,354,1,0,0,0,370,
  	358,1,0,0,0,371,13,1,0,0,0,372,377,5,8,0,0,373,374,5,43,0,0,374,375,3,
  	16,8,0,375,376,5,44,0,0,376,378,1,0,0,0,377,373,1,0,0,0,377,378,1,0,0,
  	0,378,381,1,0,0,0,379,381,5,48,0,0,380,372,1,0,0,0,380,379,1,0,0,0,381,
  	15,1,0,0,0,382,387,5,48,0,0,383,384,5,3,0,0,384,386,5,48,0,0,385,383,
  	1,0,0,0,386,389,1,0,0,0,387,385,1,0,0,0,387,388,1,0,0,0,388,17,1,0,0,
  	0,389,387,1,0,0,0,390,391,5,4,0,0,391,392,5,48,0,0,392,393,5,15,0,0,393,
  	19,1,0,0,0,394,395,5,5,0,0,395,396,5,48,0,0,396,397,5,65,0,0,397,398,
  	5,15,0,0,398,21,1,0,0,0,399,400,5,6,0,0,400,401,7,7,0,0,401,402,5,48,
  	0,0,402,403,5,7,0,0,403,404,7,8,0,0,404,405,5,15,0,0,405,23,1,0,0,0,406,
  	407,3,34,17,0,407,408,5,0,0,1,408,25,1,0,0,0,409,410,3,38,19,0,410,411,
  	5,0,0,1,411,27,1,0,0,0,412,413,3,38,19,0,413,414,5,0,0,1,414,29,1,0,0,
  	0,415,416,3,38,19,0,416,417,5,0,0,1,417,31,1,0,0,0,418,419,3,60,30,0,
  	419,420,5,0,0,1,420,33,1,0,0,0,421,422,6,17,-1,0,422,423,5,73,0,0,423,
  	476,3,34,17,16,424,476,3,64,32,0,425,426,3,38,19,0,426,427,5,45,0,0,427,
  	436,5,39,0,0,428,431,3,48,24,0,429,431,3,42,21,0,430,428,1,0,0,0,430,
  	429,1,0,0,0,431,432,1,0,0,0,432,433,5,3,0,0,433,435,1,0,0,0,434,430,1,
  	0,0,0,435,438,1,0,0,0,436,434,1,0,0,0,436,437,1,0,0,0,437,441,1,0,0,0,
  	438,436,1,0,0,0,439,442,3,48,24,0,440,442,3,42,21,0,441,439,1,0,0,0,441,
  	440,1,0,0,0,442,443,1,0,0,0,443,444,5,40,0,0,444,476,1,0,0,0,445,446,
  	3,38,19,0,446,447,3,68,34,0,447,448,3,38,19,0,448,476,1,0,0,0,449,450,
  	3,38,19,0,450,451,5,63,0,0,451,452,3,38,19,0,452,476,1,0,0,0,453,454,
  	3,38,19,0,454,455,5,64,0,0,455,456,3,38,19,0,456,476,1,0,0,0,457,458,
  	3,60,30,0,458,459,3,68,34,0,459,460,3,60,30,0,460,476,1,0,0,0,461,462,
  	3,60,30,0,462,463,5,63,0,0,463,464,3,60,30,0,464,476,1,0,0,0,465,466,
  	3,60,30,0,466,467,5,64,0,0,467,468,3,60,30,0,468,476,1,0,0,0,469,476,
  	3,36,18,0,470,476,3,38,19,0,471,472,5,43,0,0,472,473,3,34,17,0,473,474,
  	5,44,0,0,474,476,1,0,0,0,475,421,1,0,0,0,475,424,1,0,0,0,475,425,1,0,
  	0,0,475,445,1,0,0,0,475,449,1,0,0,0,475,453,1,0,0,0,475,457,1,0,0,0,475,
  	461,1,0,0,0,475,465,1,0,0,0,475,469,1,0,0,0,475,470,1,0,0,0,475,471,1,
  	0,0,0,476,491,1,0,0,0,477,478,10,7,0,0,478,479,5,63,0,0,479,490,3,34,
  	17,8,480,481,10,6,0,0,481,482,5,64,0,0,482,490,3,34,17,7,483,484,10,5,
  	0,0,484,485,5,71,0,0,485,490,3,34,17,6,486,487,10,4,0,0,487,488,5,72,
  	0,0,488,490,3,34,17,5,489,477,1,0,0,0,489,480,1,0,0,0,489,483,1,0,0,0,
  	489,486,1,0,0,0,490,493,1,0,0,0,491,489,1,0,0,0,491,492,1,0,0,0,492,35,
  	1,0,0,0,493,491,1,0,0,0,494,495,7,9,0,0,495,37,1,0,0,0,496,497,6,19,-1,
  	0,497,498,5,68,0,0,498,508,3,38,19,14,499,508,3,64,32,0,500,508,3,50,
  	25,0,501,508,3,54,27,0,502,508,3,58,29,0,503,504,5,43,0,0,504,505,3,38,
  	19,0,505,506,5,44,0,0,506,508,1,0,0,0,507,496,1,0,0,0,507,499,1,0,0,0,
  	507,500,1,0,0,0,507,501,1,0,0,0,507,502,1,0,0,0,507,503,1,0,0,0,508,534,
  	1,0,0,0,509,510,10,11,0,0,510,511,7,10,0,0,511,533,3,38,19,12,512,513,
  	10,10,0,0,513,514,7,11,0,0,514,533,3,38,19,11,515,516,10,9,0,0,516,517,
  	5,69,0,0,517,533,3,38,19,10,518,519,10,8,0,0,519,520,5,70,0,0,520,533,
  	3,38,19,9,521,522,10,7,0,0,522,523,5,65,0,0,523,533,3,38,19,8,524,525,
  	10,6,0,0,525,526,5,67,0,0,526,533,3,38,19,7,527,528,10,5,0,0,528,529,
  	5,66,0,0,529,533,3,38,19,6,530,531,10,12,0,0,531,533,3,40,20,0,532,509,
  	1,0,0,0,532,512,1,0,0,0,532,515,1,0,0,0,532,518,1,0,0,0,532,521,1,0,0,
  	0,532,524,1,0,0,0,532,527,1,0,0,0,532,530,1,0,0,0,533,536,1,0,0,0,534,
  	532,1,0,0,0,534,535,1,0,0,0,535,39,1,0,0,0,536,534,1,0,0,0,537,538,5,
  	41,0,0,538,541,7,12,0,0,539,540,5,74,0,0,540,542,7,12,0,0,541,539,1,0,
  	0,0,541,542,1,0,0,0,542,543,1,0,0,0,543,544,5,42,0,0,544,41,1,0,0,0,545,
  	548,5,41,0,0,546,549,3,38,19,0,547,549,3,44,22,0,548,546,1,0,0,0,548,
  	547,1,0,0,0,549,550,1,0,0,0,550,553,5,74,0,0,551,554,3,38,19,0,552,554,
  	3,46,23,0,553,551,1,0,0,0,553,552,1,0,0,0,554,555,1,0,0,0,555,556,5,42,
  	0,0,556,43,1,0,0,0,557,558,5,76,0,0,558,45,1,0,0,0,559,560,5,76,0,0,560,
  	47,1,0,0,0,561,562,3,38,19,0,562,49,1,0,0,0,563,566,3,52,26,0,564,566,
  	5,31,0,0,565,563,1,0,0,0,565,564,1,0,0,0,566,51,1,0,0,0,567,578,5,50,
  	0,0,568,570,5,47,0,0,569,571,5,32,0,0,570,569,1,0,0,0,570,571,1,0,0,0,
  	571,578,1,0,0,0,572,574,5,48,0,0,573,575,5,32,0,0,574,573,1,0,0,0,574,
  	575,1,0,0,0,575,578,1,0,0,0,576,578,5,51,0,0,577,567,1,0,0,0,577,568,
  	1,0,0,0,577,572,1,0,0,0,577,576,1,0,0,0,578,53,1,0,0,0,579,583,3,56,28,
  	0,580,583,3,52,26,0,581,583,5,33,0,0,582,579,1,0,0,0,582,580,1,0,0,0,
  	582,581,1,0,0,0,583,55,1,0,0,0,584,586,5,48,0,0,585,584,1,0,0,0,585,586,
  	1,0,0,0,586,587,1,0,0,0,587,588,5,52,0,0,588,57,1,0,0,0,589,590,7,13,
  	0,0,590,59,1,0,0,0,591,592,6,30,-1,0,592,598,3,62,31,0,593,594,5,43,0,
  	0,594,595,3,60,30,0,595,596,5,44,0,0,596,598,1,0,0,0,597,591,1,0,0,0,
  	597,593,1,0,0,0,598,614,1,0,0,0,599,600,10,4,0,0,600,601,5,55,0,0,601,
  	613,3,60,30,5,602,603,10,3,0,0,603,604,5,36,0,0,604,609,5,43,0,0,605,
  	606,5,48,0,0,606,607,5,3,0,0,607,610,5,48,0,0,608,610,5,48,0,0,609,605,
  	1,0,0,0,609,608,1,0,0,0,609,610,1,0,0,0,610,611,1,0,0,0,611,613,5,44,
  	0,0,612,599,1,0,0,0,612,602,1,0,0,0,613,616,1,0,0,0,614,612,1,0,0,0,614,
  	615,1,0,0,0,615,61,1,0,0,0,616,614,1,0,0,0,617,618,7,14,0,0,618,63,1,
  	0,0,0,619,620,5,46,0,0,620,621,5,43,0,0,621,626,3,66,33,0,622,623,5,3,
  	0,0,623,625,3,66,33,0,624,622,1,0,0,0,625,628,1,0,0,0,626,624,1,0,0,0,
  	626,627,1,0,0,0,627,629,1,0,0,0,628,626,1,0,0,0,629,630,5,44,0,0,630,
  	65,1,0,0,0,631,634,3,38,19,0,632,634,3,34,17,0,633,631,1,0,0,0,633,632,
  	1,0,0,0,634,67,1,0,0,0,635,636,7,15,0,0,636,69,1,0,0,0,637,638,7,16,0,
  	0,638,71,1,0,0,0,74,85,106,117,121,127,131,136,156,159,162,170,173,176,
  	185,192,196,199,202,205,208,216,223,226,240,243,246,249,252,265,268,271,
  	278,280,289,296,299,308,312,319,322,325,335,338,349,351,365,370,377,380,
  	387,430,436,441,475,489,491,507,532,534,541,548,553,565,570,574,577,582,
  	585,597,609,612,614,626,633
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
    setState(85);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(72);
      match(temporalParser::ALWAYS);
      setState(73);
      match(temporalParser::LROUND);
      setState(74);
      implication();
      setState(75);
      match(temporalParser::RROUND);
      setState(76);
      match(temporalParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(78);
      match(temporalParser::ALWAYS);
      setState(79);
      implication();
      setState(80);
      match(temporalParser::EOF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(82);
      sva_assert();
      setState(83);
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
    setState(106);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(87);
      match(temporalParser::T__0);
      setState(88);
      match(temporalParser::LROUND);
      setState(89);
      sva_assert();
      setState(90);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(92);
      match(temporalParser::LROUND);
      setState(93);
      sva_assert();
      setState(94);
      match(temporalParser::RROUND);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(96);
      match(temporalParser::T__1);
      setState(97);
      boolean(0);
      setState(98);
      match(temporalParser::RROUND);
      setState(99);
      sva_assert();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(101);
      match(temporalParser::LROUND);
      setState(102);
      implication();
      setState(103);
      match(temporalParser::RROUND);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(105);
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
    setState(136);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(108);
      tformula(0);
      setState(109);
      match(temporalParser::IMPL);
      setState(110);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(112);
      tformula(0);
      setState(113);
      match(temporalParser::IMPLO);
      setState(114);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(117);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(116);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(119);
      sere(0);
      setState(121);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RCURLY) {
        setState(120);
        match(temporalParser::RCURLY);
      }
      setState(123);
      match(temporalParser::SEREIMPL);
      setState(124);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(127);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(126);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(129);
      sere(0);
      setState(131);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RCURLY) {
        setState(130);
        match(temporalParser::RCURLY);
      }
      setState(133);
      match(temporalParser::SEREIMPLO);
      setState(134);
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

temporalParser::Placeholder_domainContext* temporalParser::SereContext::placeholder_domain() {
  return getRuleContext<temporalParser::Placeholder_domainContext>(0);
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
    setState(226);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(139);
      match(temporalParser::FIRST_MATCH);
      setState(140);
      match(temporalParser::LROUND);
      setState(141);
      sere(0);
      setState(142);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      setState(144);
      match(temporalParser::LROUND);
      setState(145);
      sere(0);
      setState(146);
      match(temporalParser::RROUND);
      break;
    }

    case 3: {
      setState(148);
      match(temporalParser::LCURLY);
      setState(149);
      sere(0);
      setState(150);
      match(temporalParser::RCURLY);
      break;
    }

    case 4: {
      setState(152);
      booleanLayer();
      setState(153);
      match(temporalParser::LSQUARED);
      setState(154);
      match(temporalParser::ASS);
      setState(156);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
      case 1: {
        setState(155);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(159);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS

      || _la == temporalParser::COL) {
        setState(158);
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
      setState(162);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER

      || _la == temporalParser::DOLLAR) {
        setState(161);
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
      setState(164);
      match(temporalParser::RSQUARED);
      break;
    }

    case 5: {
      setState(166);
      booleanLayer();
      setState(167);
      match(temporalParser::LSQUARED);
      setState(168);
      match(temporalParser::IMPLO);
      setState(170);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
      case 1: {
        setState(169);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(173);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS

      || _la == temporalParser::COL) {
        setState(172);
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
      setState(176);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER

      || _la == temporalParser::DOLLAR) {
        setState(175);
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
      setState(178);
      match(temporalParser::RSQUARED);
      break;
    }

    case 6: {
      setState(180);
      dt_ncreps();
      setState(185);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
      case 1: {
        setState(181);
        match(temporalParser::LROUND);
        setState(182);
        placeholder_domain();
        setState(183);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 7: {
      setState(187);
      match(temporalParser::DT_AND);
      setState(192);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
      case 1: {
        setState(188);
        match(temporalParser::LROUND);
        setState(189);
        placeholder_domain();
        setState(190);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 8: {
      setState(194);
      match(temporalParser::DELAY);
      setState(196);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::LSQUARED) {
        setState(195);
        match(temporalParser::LSQUARED);
      }
      setState(199);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(198);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(202);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS

      || _la == temporalParser::COL) {
        setState(201);
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
      setState(205);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
      case 1: {
        setState(204);
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
      setState(208);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RSQUARED) {
        setState(207);
        match(temporalParser::RSQUARED);
      }
      setState(210);
      sere(6);
      break;
    }

    case 9: {
      setState(211);
      dt_next();
      setState(216);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(212);
        match(temporalParser::LROUND);
        setState(213);
        placeholder_domain();
        setState(214);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 10: {
      setState(218);
      dt_next_and();
      setState(223);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
      case 1: {
        setState(219);
        match(temporalParser::LROUND);
        setState(220);
        placeholder_domain();
        setState(221);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 11: {
      setState(225);
      booleanLayer();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(280);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(278);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(228);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(229);
          match(temporalParser::BAND);
          setState(230);
          sere(12);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(231);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(232);
          _la = _input->LA(1);
          if (!(((((_la - 26) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 26)) & ((1ULL << (temporalParser::TAND - 26))
            | (1ULL << (temporalParser::INTERSECT - 26))
            | (1ULL << (temporalParser::AND - 26)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(233);
          sere(11);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(234);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(235);
          _la = _input->LA(1);
          if (!(((((_la - 28) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 28)) & ((1ULL << (temporalParser::TOR - 28))
            | (1ULL << (temporalParser::BOR - 28))
            | (1ULL << (temporalParser::OR - 28)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(236);
          sere(9);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(237);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(238);
          match(temporalParser::DELAY);
          setState(240);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::LSQUARED) {
            setState(239);
            match(temporalParser::LSQUARED);
          }
          setState(243);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
          case 1: {
            setState(242);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(246);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::DOTS

          || _la == temporalParser::COL) {
            setState(245);
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
          setState(249);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
          case 1: {
            setState(248);
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
          setState(252);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::RSQUARED) {
            setState(251);
            match(temporalParser::RSQUARED);
          }
          setState(254);
          sere(8);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(255);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(256);
          match(temporalParser::COL);
          setState(257);
          sere(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(258);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(259);
          match(temporalParser::SCOL);
          setState(260);
          sere(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(261);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(262);
          match(temporalParser::LSQUARED);
          setState(263);
          match(temporalParser::TIMES);
          setState(265);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
          case 1: {
            setState(264);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(268);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::DOTS

          || _la == temporalParser::COL) {
            setState(267);
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
          setState(271);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::UINTEGER

          || _la == temporalParser::DOLLAR) {
            setState(270);
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
          setState(273);
          match(temporalParser::RSQUARED);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(274);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(275);
          match(temporalParser::LSQUARED);
          setState(276);
          match(temporalParser::PLUS);
          setState(277);
          match(temporalParser::RSQUARED);
          break;
        }

        default:
          break;
        } 
      }
      setState(282);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
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

temporalParser::Placeholder_domainContext* temporalParser::BooleanLayerContext::placeholder_domain() {
  return getRuleContext<temporalParser::Placeholder_domainContext>(0);
}

temporalParser::TemporalFunctionContext* temporalParser::BooleanLayerContext::temporalFunction() {
  return getRuleContext<temporalParser::TemporalFunctionContext>(0);
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
    setState(299);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(283);
      match(temporalParser::LROUND);
      setState(284);
      booleanLayer();
      setState(285);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(287);
      boolean(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(289);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::NOT) {
        setState(288);
        match(temporalParser::NOT);
      }
      setState(291);
      match(temporalParser::PLACEHOLDER);
      setState(296);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
      case 1: {
        setState(292);
        match(temporalParser::LROUND);
        setState(293);
        placeholder_domain();
        setState(294);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(298);
      temporalFunction();
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

temporalParser::Placeholder_domainContext* temporalParser::TformulaContext::placeholder_domain() {
  return getRuleContext<temporalParser::Placeholder_domainContext>(0);
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
    setState(338);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      setState(302);
      match(temporalParser::LROUND);
      setState(303);
      tformula(0);
      setState(304);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      setState(306);

      if (!(canUseSharedOperator(_input->LT(-1)->getText(),_input->LT(2)->getText()))) throw FailedPredicateException(this, "canUseSharedOperator(_input->LT(-1)->getText(),_input->LT(2)->getText())");
      setState(308);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
      case 1: {
        setState(307);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(310);
      sere(0);
      setState(312);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
      case 1: {
        setState(311);
        match(temporalParser::RCURLY);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      setState(314);

      if (!(canTakeThisNot(_input->LT(1)->getText(),_input->LT(2)->getText()))) throw FailedPredicateException(this, "canTakeThisNot(_input->LT(1)->getText(),_input->LT(2)->getText())");
      setState(315);
      _la = _input->LA(1);
      if (!(_la == temporalParser::TNOT

      || _la == temporalParser::NOT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(316);
      tformula(8);
      break;
    }

    case 4: {
      setState(317);
      match(temporalParser::NEXT);
      setState(319);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
      case 1: {
        setState(318);
        match(temporalParser::LSQUARED);
        break;
      }

      default:
        break;
      }
      setState(322);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
      case 1: {
        setState(321);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(325);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
      case 1: {
        setState(324);
        match(temporalParser::RSQUARED);
        break;
      }

      default:
        break;
      }
      setState(327);
      tformula(7);
      break;
    }

    case 5: {
      setState(328);
      match(temporalParser::EVENTUALLY);
      setState(329);
      tformula(6);
      break;
    }

    case 6: {
      setState(330);
      match(temporalParser::DT_AND);
      setState(335);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
      case 1: {
        setState(331);
        match(temporalParser::LROUND);
        setState(332);
        placeholder_domain();
        setState(333);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 7: {
      setState(337);
      booleanLayer();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(351);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(349);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(340);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(341);
          _la = _input->LA(1);
          if (!(_la == temporalParser::UNTIL

          || _la == temporalParser::RELEASE)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(342);
          tformula(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(343);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(344);
          _la = _input->LA(1);
          if (!(_la == temporalParser::TAND

          || _la == temporalParser::AND)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(345);
          tformula(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(346);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(347);
          _la = _input->LA(1);
          if (!(((((_la - 28) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 28)) & ((1ULL << (temporalParser::TOR - 28))
            | (1ULL << (temporalParser::BOR - 28))
            | (1ULL << (temporalParser::OR - 28)))) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(348);
          tformula(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(353);
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

//----------------- TemporalFunctionContext ------------------------------------------------------------------

temporalParser::TemporalFunctionContext::TemporalFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::TemporalFunctionContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

temporalParser::TemporalFunctionContext* temporalParser::TemporalFunctionContext::temporalFunction() {
  return getRuleContext<temporalParser::TemporalFunctionContext>(0);
}

tree::TerminalNode* temporalParser::TemporalFunctionContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

tree::TerminalNode* temporalParser::TemporalFunctionContext::FUNCTION() {
  return getToken(temporalParser::FUNCTION, 0);
}

std::vector<temporalParser::Tfunc_argContext *> temporalParser::TemporalFunctionContext::tfunc_arg() {
  return getRuleContexts<temporalParser::Tfunc_argContext>();
}

temporalParser::Tfunc_argContext* temporalParser::TemporalFunctionContext::tfunc_arg(size_t i) {
  return getRuleContext<temporalParser::Tfunc_argContext>(i);
}


size_t temporalParser::TemporalFunctionContext::getRuleIndex() const {
  return temporalParser::RuleTemporalFunction;
}

void temporalParser::TemporalFunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemporalFunction(this);
}

void temporalParser::TemporalFunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemporalFunction(this);
}

temporalParser::TemporalFunctionContext* temporalParser::temporalFunction() {
  TemporalFunctionContext *_localctx = _tracker.createInstance<TemporalFunctionContext>(_ctx, getState());
  enterRule(_localctx, 12, temporalParser::RuleTemporalFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(370);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::LROUND: {
        enterOuterAlt(_localctx, 1);
        setState(354);
        match(temporalParser::LROUND);
        setState(355);
        temporalFunction();
        setState(356);
        match(temporalParser::RROUND);
        break;
      }

      case temporalParser::FUNCTION: {
        enterOuterAlt(_localctx, 2);
        setState(358);
        match(temporalParser::FUNCTION);
        setState(359);
        match(temporalParser::LROUND);
        setState(360);
        tfunc_arg();
        setState(365);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == temporalParser::T__2) {
          setState(361);
          match(temporalParser::T__2);
          setState(362);
          tfunc_arg();
          setState(367);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(368);
        match(temporalParser::RROUND);
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

//----------------- Tfunc_argContext ------------------------------------------------------------------

temporalParser::Tfunc_argContext::Tfunc_argContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Tfunc_argContext::PLACEHOLDER() {
  return getToken(temporalParser::PLACEHOLDER, 0);
}

tree::TerminalNode* temporalParser::Tfunc_argContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

temporalParser::Placeholder_domainContext* temporalParser::Tfunc_argContext::placeholder_domain() {
  return getRuleContext<temporalParser::Placeholder_domainContext>(0);
}

tree::TerminalNode* temporalParser::Tfunc_argContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

tree::TerminalNode* temporalParser::Tfunc_argContext::UINTEGER() {
  return getToken(temporalParser::UINTEGER, 0);
}


size_t temporalParser::Tfunc_argContext::getRuleIndex() const {
  return temporalParser::RuleTfunc_arg;
}

void temporalParser::Tfunc_argContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTfunc_arg(this);
}

void temporalParser::Tfunc_argContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTfunc_arg(this);
}

temporalParser::Tfunc_argContext* temporalParser::tfunc_arg() {
  Tfunc_argContext *_localctx = _tracker.createInstance<Tfunc_argContext>(_ctx, getState());
  enterRule(_localctx, 14, temporalParser::RuleTfunc_arg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(380);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::PLACEHOLDER: {
        enterOuterAlt(_localctx, 1);
        setState(372);
        match(temporalParser::PLACEHOLDER);
        setState(377);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == temporalParser::LROUND) {
          setState(373);
          match(temporalParser::LROUND);
          setState(374);
          placeholder_domain();
          setState(375);
          match(temporalParser::RROUND);
        }
        break;
      }

      case temporalParser::UINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(379);
        match(temporalParser::UINTEGER);
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

//----------------- Placeholder_domainContext ------------------------------------------------------------------

temporalParser::Placeholder_domainContext::Placeholder_domainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> temporalParser::Placeholder_domainContext::UINTEGER() {
  return getTokens(temporalParser::UINTEGER);
}

tree::TerminalNode* temporalParser::Placeholder_domainContext::UINTEGER(size_t i) {
  return getToken(temporalParser::UINTEGER, i);
}


size_t temporalParser::Placeholder_domainContext::getRuleIndex() const {
  return temporalParser::RulePlaceholder_domain;
}

void temporalParser::Placeholder_domainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlaceholder_domain(this);
}

void temporalParser::Placeholder_domainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlaceholder_domain(this);
}

temporalParser::Placeholder_domainContext* temporalParser::placeholder_domain() {
  Placeholder_domainContext *_localctx = _tracker.createInstance<Placeholder_domainContext>(_ctx, getState());
  enterRule(_localctx, 16, temporalParser::RulePlaceholder_domain);
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
    setState(382);
    match(temporalParser::UINTEGER);
    setState(387);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == temporalParser::T__2) {
      setState(383);
      match(temporalParser::T__2);

      setState(384);
      match(temporalParser::UINTEGER);
      setState(389);
      _errHandler->sync(this);
      _la = _input->LA(1);
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
  enterRule(_localctx, 18, temporalParser::RuleDt_next);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(390);
    match(temporalParser::T__3);
    setState(391);
    match(temporalParser::UINTEGER);
    setState(392);
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
  enterRule(_localctx, 20, temporalParser::RuleDt_next_and);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(394);
    match(temporalParser::T__4);
    setState(395);
    match(temporalParser::UINTEGER);
    setState(396);
    match(temporalParser::BAND);
    setState(397);
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
  enterRule(_localctx, 22, temporalParser::RuleDt_ncreps);
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
    setState(399);
    match(temporalParser::T__5);
    setState(400);
    _la = _input->LA(1);
    if (!(_la == temporalParser::IMPLO

    || _la == temporalParser::ASS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(401);
    match(temporalParser::UINTEGER);
    setState(402);
    match(temporalParser::T__6);
    setState(403);
    _la = _input->LA(1);
    if (!(_la == temporalParser::SCOL

    || _la == temporalParser::COL)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(404);
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
  enterRule(_localctx, 24, temporalParser::RuleStartBoolean);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(406);
    boolean(0);
    setState(407);
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
  enterRule(_localctx, 26, temporalParser::RuleStartInt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(409);
    numeric(0);
    setState(410);
    match(temporalParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartLogicContext ------------------------------------------------------------------

temporalParser::StartLogicContext::StartLogicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::NumericContext* temporalParser::StartLogicContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}

tree::TerminalNode* temporalParser::StartLogicContext::EOF() {
  return getToken(temporalParser::EOF, 0);
}


size_t temporalParser::StartLogicContext::getRuleIndex() const {
  return temporalParser::RuleStartLogic;
}

void temporalParser::StartLogicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartLogic(this);
}

void temporalParser::StartLogicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartLogic(this);
}

temporalParser::StartLogicContext* temporalParser::startLogic() {
  StartLogicContext *_localctx = _tracker.createInstance<StartLogicContext>(_ctx, getState());
  enterRule(_localctx, 28, temporalParser::RuleStartLogic);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(412);
    numeric(0);
    setState(413);
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
  enterRule(_localctx, 30, temporalParser::RuleStartFloat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(415);
    numeric(0);
    setState(416);
    match(temporalParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartStringContext ------------------------------------------------------------------

temporalParser::StartStringContext::StartStringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::StringContext* temporalParser::StartStringContext::string() {
  return getRuleContext<temporalParser::StringContext>(0);
}

tree::TerminalNode* temporalParser::StartStringContext::EOF() {
  return getToken(temporalParser::EOF, 0);
}


size_t temporalParser::StartStringContext::getRuleIndex() const {
  return temporalParser::RuleStartString;
}

void temporalParser::StartStringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartString(this);
}

void temporalParser::StartStringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartString(this);
}

temporalParser::StartStringContext* temporalParser::startString() {
  StartStringContext *_localctx = _tracker.createInstance<StartStringContext>(_ctx, getState());
  enterRule(_localctx, 32, temporalParser::RuleStartString);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(418);
    string(0);
    setState(419);
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

temporalParser::NonTemporalFunctionContext* temporalParser::BooleanContext::nonTemporalFunction() {
  return getRuleContext<temporalParser::NonTemporalFunctionContext>(0);
}

std::vector<temporalParser::NumericContext *> temporalParser::BooleanContext::numeric() {
  return getRuleContexts<temporalParser::NumericContext>();
}

temporalParser::NumericContext* temporalParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<temporalParser::NumericContext>(i);
}

tree::TerminalNode* temporalParser::BooleanContext::INSIDE() {
  return getToken(temporalParser::INSIDE, 0);
}

tree::TerminalNode* temporalParser::BooleanContext::LCURLY() {
  return getToken(temporalParser::LCURLY, 0);
}

tree::TerminalNode* temporalParser::BooleanContext::RCURLY() {
  return getToken(temporalParser::RCURLY, 0);
}

std::vector<temporalParser::Sm_constantContext *> temporalParser::BooleanContext::sm_constant() {
  return getRuleContexts<temporalParser::Sm_constantContext>();
}

temporalParser::Sm_constantContext* temporalParser::BooleanContext::sm_constant(size_t i) {
  return getRuleContext<temporalParser::Sm_constantContext>(i);
}

std::vector<temporalParser::Sm_rangeContext *> temporalParser::BooleanContext::sm_range() {
  return getRuleContexts<temporalParser::Sm_rangeContext>();
}

temporalParser::Sm_rangeContext* temporalParser::BooleanContext::sm_range(size_t i) {
  return getRuleContext<temporalParser::Sm_rangeContext>(i);
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

std::vector<temporalParser::StringContext *> temporalParser::BooleanContext::string() {
  return getRuleContexts<temporalParser::StringContext>();
}

temporalParser::StringContext* temporalParser::BooleanContext::string(size_t i) {
  return getRuleContext<temporalParser::StringContext>(i);
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
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, temporalParser::RuleBoolean, precedence);

    

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
    setState(475);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      setState(422);
      match(temporalParser::NOT);
      setState(423);
      boolean(16);
      break;
    }

    case 2: {
      setState(424);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(425);
      numeric(0);
      setState(426);
      match(temporalParser::INSIDE);
      setState(427);
      match(temporalParser::LCURLY);
      setState(436);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(430);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case temporalParser::INT_VARIABLE:
            case temporalParser::LOGIC_VARIABLE:
            case temporalParser::FLOAT_CONSTANT:
            case temporalParser::FLOAT_VARIABLE:
            case temporalParser::LROUND:
            case temporalParser::FUNCTION:
            case temporalParser::SINTEGER:
            case temporalParser::UINTEGER:
            case temporalParser::GCC_BINARY:
            case temporalParser::HEX:
            case temporalParser::VERILOG_BINARY:
            case temporalParser::NEG: {
              setState(428);
              sm_constant();
              break;
            }

            case temporalParser::LSQUARED: {
              setState(429);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(432);
          match(temporalParser::T__2); 
        }
        setState(438);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
      }
      setState(441);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case temporalParser::INT_VARIABLE:
        case temporalParser::LOGIC_VARIABLE:
        case temporalParser::FLOAT_CONSTANT:
        case temporalParser::FLOAT_VARIABLE:
        case temporalParser::LROUND:
        case temporalParser::FUNCTION:
        case temporalParser::SINTEGER:
        case temporalParser::UINTEGER:
        case temporalParser::GCC_BINARY:
        case temporalParser::HEX:
        case temporalParser::VERILOG_BINARY:
        case temporalParser::NEG: {
          setState(439);
          sm_constant();
          break;
        }

        case temporalParser::LSQUARED: {
          setState(440);
          sm_range();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(443);
      match(temporalParser::RCURLY);
      break;
    }

    case 4: {
      setState(445);
      numeric(0);
      setState(446);
      relop();
      setState(447);
      numeric(0);
      break;
    }

    case 5: {
      setState(449);
      numeric(0);
      setState(450);
      match(temporalParser::EQ);
      setState(451);
      numeric(0);
      break;
    }

    case 6: {
      setState(453);
      numeric(0);
      setState(454);
      match(temporalParser::NEQ);
      setState(455);
      numeric(0);
      break;
    }

    case 7: {
      setState(457);
      string(0);
      setState(458);
      relop();
      setState(459);
      string(0);
      break;
    }

    case 8: {
      setState(461);
      string(0);
      setState(462);
      match(temporalParser::EQ);
      setState(463);
      string(0);
      break;
    }

    case 9: {
      setState(465);
      string(0);
      setState(466);
      match(temporalParser::NEQ);
      setState(467);
      string(0);
      break;
    }

    case 10: {
      setState(469);
      booleanAtom();
      break;
    }

    case 11: {
      setState(470);
      numeric(0);
      break;
    }

    case 12: {
      setState(471);
      match(temporalParser::LROUND);
      setState(472);
      boolean(0);
      setState(473);
      match(temporalParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(491);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(489);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(477);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(478);
          match(temporalParser::EQ);
          setState(479);
          boolean(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(480);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(481);
          match(temporalParser::NEQ);
          setState(482);
          boolean(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(483);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(484);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(temporalParser::AND);
          setState(485);
          boolean(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(486);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(487);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(temporalParser::OR);
          setState(488);
          boolean(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(493);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
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
  enterRule(_localctx, 36, temporalParser::RuleBooleanAtom);
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
    setState(494);
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

temporalParser::NonTemporalFunctionContext* temporalParser::NumericContext::nonTemporalFunction() {
  return getRuleContext<temporalParser::NonTemporalFunctionContext>(0);
}

temporalParser::IntAtomContext* temporalParser::NumericContext::intAtom() {
  return getRuleContext<temporalParser::IntAtomContext>(0);
}

temporalParser::LogicAtomContext* temporalParser::NumericContext::logicAtom() {
  return getRuleContext<temporalParser::LogicAtomContext>(0);
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
  size_t startState = 38;
  enterRecursionRule(_localctx, 38, temporalParser::RuleNumeric, precedence);

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
    setState(507);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      setState(497);
      match(temporalParser::NEG);
      setState(498);
      numeric(14);
      break;
    }

    case 2: {
      setState(499);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(500);
      intAtom();
      break;
    }

    case 4: {
      setState(501);
      logicAtom();
      break;
    }

    case 5: {
      setState(502);
      floatAtom();
      break;
    }

    case 6: {
      setState(503);
      match(temporalParser::LROUND);
      setState(504);
      numeric(0);
      setState(505);
      match(temporalParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(534);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(532);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(509);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(510);
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
          setState(511);
          numeric(12);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(512);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(513);
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
          setState(514);
          numeric(11);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(515);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(516);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::LSHIFT);
          setState(517);
          numeric(10);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(518);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(519);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::RSHIFT);
          setState(520);
          numeric(9);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(521);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(522);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BAND);
          setState(523);
          numeric(8);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(524);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(525);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BXOR);
          setState(526);
          numeric(7);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(527);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(528);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BOR);
          setState(529);
          numeric(6);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(530);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(531);
          range();
          break;
        }

        default:
          break;
        } 
      }
      setState(536);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
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
  enterRule(_localctx, 40, temporalParser::RuleRange);
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
    setState(537);
    match(temporalParser::LSQUARED);
    setState(538);
    _la = _input->LA(1);
    if (!(_la == temporalParser::SINTEGER

    || _la == temporalParser::UINTEGER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(541);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == temporalParser::COL) {
      setState(539);
      match(temporalParser::COL);
      setState(540);
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
    setState(543);
    match(temporalParser::RSQUARED);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sm_rangeContext ------------------------------------------------------------------

temporalParser::Sm_rangeContext::Sm_rangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Sm_rangeContext::LSQUARED() {
  return getToken(temporalParser::LSQUARED, 0);
}

tree::TerminalNode* temporalParser::Sm_rangeContext::COL() {
  return getToken(temporalParser::COL, 0);
}

tree::TerminalNode* temporalParser::Sm_rangeContext::RSQUARED() {
  return getToken(temporalParser::RSQUARED, 0);
}

std::vector<temporalParser::NumericContext *> temporalParser::Sm_rangeContext::numeric() {
  return getRuleContexts<temporalParser::NumericContext>();
}

temporalParser::NumericContext* temporalParser::Sm_rangeContext::numeric(size_t i) {
  return getRuleContext<temporalParser::NumericContext>(i);
}

temporalParser::Min_dollarContext* temporalParser::Sm_rangeContext::min_dollar() {
  return getRuleContext<temporalParser::Min_dollarContext>(0);
}

temporalParser::Max_dollarContext* temporalParser::Sm_rangeContext::max_dollar() {
  return getRuleContext<temporalParser::Max_dollarContext>(0);
}


size_t temporalParser::Sm_rangeContext::getRuleIndex() const {
  return temporalParser::RuleSm_range;
}

void temporalParser::Sm_rangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSm_range(this);
}

void temporalParser::Sm_rangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSm_range(this);
}

temporalParser::Sm_rangeContext* temporalParser::sm_range() {
  Sm_rangeContext *_localctx = _tracker.createInstance<Sm_rangeContext>(_ctx, getState());
  enterRule(_localctx, 42, temporalParser::RuleSm_range);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(545);
    match(temporalParser::LSQUARED);
    setState(548);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::INT_VARIABLE:
      case temporalParser::LOGIC_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LROUND:
      case temporalParser::FUNCTION:
      case temporalParser::SINTEGER:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX:
      case temporalParser::VERILOG_BINARY:
      case temporalParser::NEG: {
        setState(546);
        numeric(0);
        break;
      }

      case temporalParser::DOLLAR: {
        setState(547);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(550);
    match(temporalParser::COL);
    setState(553);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::INT_VARIABLE:
      case temporalParser::LOGIC_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LROUND:
      case temporalParser::FUNCTION:
      case temporalParser::SINTEGER:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX:
      case temporalParser::VERILOG_BINARY:
      case temporalParser::NEG: {
        setState(551);
        numeric(0);
        break;
      }

      case temporalParser::DOLLAR: {
        setState(552);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(555);
    match(temporalParser::RSQUARED);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Min_dollarContext ------------------------------------------------------------------

temporalParser::Min_dollarContext::Min_dollarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Min_dollarContext::DOLLAR() {
  return getToken(temporalParser::DOLLAR, 0);
}


size_t temporalParser::Min_dollarContext::getRuleIndex() const {
  return temporalParser::RuleMin_dollar;
}

void temporalParser::Min_dollarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMin_dollar(this);
}

void temporalParser::Min_dollarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMin_dollar(this);
}

temporalParser::Min_dollarContext* temporalParser::min_dollar() {
  Min_dollarContext *_localctx = _tracker.createInstance<Min_dollarContext>(_ctx, getState());
  enterRule(_localctx, 44, temporalParser::RuleMin_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(557);
    match(temporalParser::DOLLAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Max_dollarContext ------------------------------------------------------------------

temporalParser::Max_dollarContext::Max_dollarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Max_dollarContext::DOLLAR() {
  return getToken(temporalParser::DOLLAR, 0);
}


size_t temporalParser::Max_dollarContext::getRuleIndex() const {
  return temporalParser::RuleMax_dollar;
}

void temporalParser::Max_dollarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMax_dollar(this);
}

void temporalParser::Max_dollarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMax_dollar(this);
}

temporalParser::Max_dollarContext* temporalParser::max_dollar() {
  Max_dollarContext *_localctx = _tracker.createInstance<Max_dollarContext>(_ctx, getState());
  enterRule(_localctx, 46, temporalParser::RuleMax_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(559);
    match(temporalParser::DOLLAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sm_constantContext ------------------------------------------------------------------

temporalParser::Sm_constantContext::Sm_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::NumericContext* temporalParser::Sm_constantContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}


size_t temporalParser::Sm_constantContext::getRuleIndex() const {
  return temporalParser::RuleSm_constant;
}

void temporalParser::Sm_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSm_constant(this);
}

void temporalParser::Sm_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSm_constant(this);
}

temporalParser::Sm_constantContext* temporalParser::sm_constant() {
  Sm_constantContext *_localctx = _tracker.createInstance<Sm_constantContext>(_ctx, getState());
  enterRule(_localctx, 48, temporalParser::RuleSm_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(561);
    numeric(0);
   
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
  enterRule(_localctx, 50, temporalParser::RuleIntAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(565);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::SINTEGER:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(563);
        int_constant();
        break;
      }

      case temporalParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(564);
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
  enterRule(_localctx, 52, temporalParser::RuleInt_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(577);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(567);
        match(temporalParser::GCC_BINARY);
        break;
      }

      case temporalParser::SINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(568);
        match(temporalParser::SINTEGER);
        setState(570);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
        case 1: {
          setState(569);
          match(temporalParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case temporalParser::UINTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(572);
        match(temporalParser::UINTEGER);
        setState(574);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
        case 1: {
          setState(573);
          match(temporalParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case temporalParser::HEX: {
        enterOuterAlt(_localctx, 4);
        setState(576);
        match(temporalParser::HEX);
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

//----------------- LogicAtomContext ------------------------------------------------------------------

temporalParser::LogicAtomContext::LogicAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::Logic_constantContext* temporalParser::LogicAtomContext::logic_constant() {
  return getRuleContext<temporalParser::Logic_constantContext>(0);
}

temporalParser::Int_constantContext* temporalParser::LogicAtomContext::int_constant() {
  return getRuleContext<temporalParser::Int_constantContext>(0);
}

tree::TerminalNode* temporalParser::LogicAtomContext::LOGIC_VARIABLE() {
  return getToken(temporalParser::LOGIC_VARIABLE, 0);
}


size_t temporalParser::LogicAtomContext::getRuleIndex() const {
  return temporalParser::RuleLogicAtom;
}

void temporalParser::LogicAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicAtom(this);
}

void temporalParser::LogicAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicAtom(this);
}

temporalParser::LogicAtomContext* temporalParser::logicAtom() {
  LogicAtomContext *_localctx = _tracker.createInstance<LogicAtomContext>(_ctx, getState());
  enterRule(_localctx, 54, temporalParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(582);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(579);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(580);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(581);
      match(temporalParser::LOGIC_VARIABLE);
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

//----------------- Logic_constantContext ------------------------------------------------------------------

temporalParser::Logic_constantContext::Logic_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::Logic_constantContext::VERILOG_BINARY() {
  return getToken(temporalParser::VERILOG_BINARY, 0);
}

tree::TerminalNode* temporalParser::Logic_constantContext::UINTEGER() {
  return getToken(temporalParser::UINTEGER, 0);
}


size_t temporalParser::Logic_constantContext::getRuleIndex() const {
  return temporalParser::RuleLogic_constant;
}

void temporalParser::Logic_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic_constant(this);
}

void temporalParser::Logic_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic_constant(this);
}

temporalParser::Logic_constantContext* temporalParser::logic_constant() {
  Logic_constantContext *_localctx = _tracker.createInstance<Logic_constantContext>(_ctx, getState());
  enterRule(_localctx, 56, temporalParser::RuleLogic_constant);
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
    setState(585);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == temporalParser::UINTEGER) {
      setState(584);
      match(temporalParser::UINTEGER);
    }
    setState(587);
    match(temporalParser::VERILOG_BINARY);
   
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
  enterRule(_localctx, 58, temporalParser::RuleFloatAtom);
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
    setState(589);
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

//----------------- StringContext ------------------------------------------------------------------

temporalParser::StringContext::StringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::StringAtomContext* temporalParser::StringContext::stringAtom() {
  return getRuleContext<temporalParser::StringAtomContext>(0);
}

tree::TerminalNode* temporalParser::StringContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

std::vector<temporalParser::StringContext *> temporalParser::StringContext::string() {
  return getRuleContexts<temporalParser::StringContext>();
}

temporalParser::StringContext* temporalParser::StringContext::string(size_t i) {
  return getRuleContext<temporalParser::StringContext>(i);
}

tree::TerminalNode* temporalParser::StringContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

tree::TerminalNode* temporalParser::StringContext::PLUS() {
  return getToken(temporalParser::PLUS, 0);
}

tree::TerminalNode* temporalParser::StringContext::SUBSTR() {
  return getToken(temporalParser::SUBSTR, 0);
}

std::vector<tree::TerminalNode *> temporalParser::StringContext::UINTEGER() {
  return getTokens(temporalParser::UINTEGER);
}

tree::TerminalNode* temporalParser::StringContext::UINTEGER(size_t i) {
  return getToken(temporalParser::UINTEGER, i);
}


size_t temporalParser::StringContext::getRuleIndex() const {
  return temporalParser::RuleString;
}

void temporalParser::StringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterString(this);
}

void temporalParser::StringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitString(this);
}


temporalParser::StringContext* temporalParser::string() {
   return string(0);
}

temporalParser::StringContext* temporalParser::string(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  temporalParser::StringContext *_localctx = _tracker.createInstance<StringContext>(_ctx, parentState);
  temporalParser::StringContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, temporalParser::RuleString, precedence);

    

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
    setState(597);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::STRING_CONSTANT:
      case temporalParser::STRING_VARIABLE: {
        setState(592);
        stringAtom();
        break;
      }

      case temporalParser::LROUND: {
        setState(593);
        match(temporalParser::LROUND);
        setState(594);
        string(0);
        setState(595);
        match(temporalParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(614);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(612);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(599);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(600);
          match(temporalParser::PLUS);
          setState(601);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(602);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(603);
          match(temporalParser::SUBSTR);
          setState(604);
          match(temporalParser::LROUND);
          setState(609);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
          case 1: {
            setState(605);
            match(temporalParser::UINTEGER);
            setState(606);
            match(temporalParser::T__2);
            setState(607);
            match(temporalParser::UINTEGER);
            break;
          }

          case 2: {
            setState(608);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(611);
          match(temporalParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(616);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- StringAtomContext ------------------------------------------------------------------

temporalParser::StringAtomContext::StringAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::StringAtomContext::STRING_CONSTANT() {
  return getToken(temporalParser::STRING_CONSTANT, 0);
}

tree::TerminalNode* temporalParser::StringAtomContext::STRING_VARIABLE() {
  return getToken(temporalParser::STRING_VARIABLE, 0);
}


size_t temporalParser::StringAtomContext::getRuleIndex() const {
  return temporalParser::RuleStringAtom;
}

void temporalParser::StringAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringAtom(this);
}

void temporalParser::StringAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringAtom(this);
}

temporalParser::StringAtomContext* temporalParser::stringAtom() {
  StringAtomContext *_localctx = _tracker.createInstance<StringAtomContext>(_ctx, getState());
  enterRule(_localctx, 62, temporalParser::RuleStringAtom);
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
    setState(617);
    _la = _input->LA(1);
    if (!(_la == temporalParser::STRING_CONSTANT

    || _la == temporalParser::STRING_VARIABLE)) {
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

//----------------- NonTemporalFunctionContext ------------------------------------------------------------------

temporalParser::NonTemporalFunctionContext::NonTemporalFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::NonTemporalFunctionContext::FUNCTION() {
  return getToken(temporalParser::FUNCTION, 0);
}

tree::TerminalNode* temporalParser::NonTemporalFunctionContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

std::vector<temporalParser::Pfunc_argContext *> temporalParser::NonTemporalFunctionContext::pfunc_arg() {
  return getRuleContexts<temporalParser::Pfunc_argContext>();
}

temporalParser::Pfunc_argContext* temporalParser::NonTemporalFunctionContext::pfunc_arg(size_t i) {
  return getRuleContext<temporalParser::Pfunc_argContext>(i);
}

tree::TerminalNode* temporalParser::NonTemporalFunctionContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}


size_t temporalParser::NonTemporalFunctionContext::getRuleIndex() const {
  return temporalParser::RuleNonTemporalFunction;
}

void temporalParser::NonTemporalFunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNonTemporalFunction(this);
}

void temporalParser::NonTemporalFunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNonTemporalFunction(this);
}

temporalParser::NonTemporalFunctionContext* temporalParser::nonTemporalFunction() {
  NonTemporalFunctionContext *_localctx = _tracker.createInstance<NonTemporalFunctionContext>(_ctx, getState());
  enterRule(_localctx, 64, temporalParser::RuleNonTemporalFunction);
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
    setState(619);
    match(temporalParser::FUNCTION);
    setState(620);
    match(temporalParser::LROUND);
    setState(621);
    pfunc_arg();
    setState(626);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == temporalParser::T__2) {
      setState(622);
      match(temporalParser::T__2);
      setState(623);
      pfunc_arg();
      setState(628);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(629);
    match(temporalParser::RROUND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pfunc_argContext ------------------------------------------------------------------

temporalParser::Pfunc_argContext::Pfunc_argContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::NumericContext* temporalParser::Pfunc_argContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}

temporalParser::BooleanContext* temporalParser::Pfunc_argContext::boolean() {
  return getRuleContext<temporalParser::BooleanContext>(0);
}


size_t temporalParser::Pfunc_argContext::getRuleIndex() const {
  return temporalParser::RulePfunc_arg;
}

void temporalParser::Pfunc_argContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPfunc_arg(this);
}

void temporalParser::Pfunc_argContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPfunc_arg(this);
}

temporalParser::Pfunc_argContext* temporalParser::pfunc_arg() {
  Pfunc_argContext *_localctx = _tracker.createInstance<Pfunc_argContext>(_ctx, getState());
  enterRule(_localctx, 66, temporalParser::RulePfunc_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(633);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(631);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(632);
      boolean(0);
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
  enterRule(_localctx, 68, temporalParser::RuleRelop);
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
    setState(635);
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
  enterRule(_localctx, 70, temporalParser::RuleCls_op);
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
    setState(637);
    _la = _input->LA(1);
    if (!(((((_la - 59) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 59)) & ((1ULL << (temporalParser::GT - 59))
      | (1ULL << (temporalParser::GE - 59))
      | (1ULL << (temporalParser::LT - 59))
      | (1ULL << (temporalParser::LE - 59))
      | (1ULL << (temporalParser::EQ - 59))
      | (1ULL << (temporalParser::RANGE - 59)))) != 0))) {
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
    case 17: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 19: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);
    case 30: return stringSempred(antlrcpp::downCast<StringContext *>(context), predicateIndex);

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
    case 17: return precpred(_ctx, 11);
    case 18: return precpred(_ctx, 10);
    case 19: return precpred(_ctx, 9);
    case 20: return precpred(_ctx, 8);
    case 21: return precpred(_ctx, 7);
    case 22: return precpred(_ctx, 6);
    case 23: return precpred(_ctx, 5);
    case 24: return precpred(_ctx, 12);

  default:
    break;
  }
  return true;
}

bool temporalParser::stringSempred(StringContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 25: return precpred(_ctx, 4);
    case 26: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void temporalParser::initialize() {
  std::call_once(temporalParserOnceFlag, temporalParserInitialize);
}
