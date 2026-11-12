
#include <string>
// Forward declaration
bool isUnary(const std::string& token);
bool isSharedOperator(const std::string& token);
bool canUseSharedOperator(const std::string& unaryOp, const std::string& sharedOp);
bool canTakeThisNot(const std::string& unaryOp, const std::string& ph);


// Generated from temporal.g4 by ANTLR 4.13.2


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

::antlr4::internal::OnceFlag temporalParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<TemporalParserStaticData> temporalParserStaticData = nullptr;

void temporalParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (temporalParserStaticData != nullptr) {
    return;
  }
#else
  assert(temporalParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<TemporalParserStaticData>(
    std::vector<std::string>{
      "formula", "sva_assert", "implication", "sere", "booleanLayer", "tformula", 
      "temporalFunction", "tfunc_arg", "placeholder_domain", "dt_next", 
      "dt_next_and", "dt_ncreps", "startBoolean", "startInt", "startLogic", 
      "startFloat", "startString", "booleanTernary", "numericTernary", "boolean", 
      "booleanAtom", "numeric", "concatenation", "concatItem", "range", 
      "sm_range", "min_dollar", "max_dollar", "sm_constant", "intAtom", 
      "int_constant", "logicAtom", "logic_constant", "floatAtom", "string", 
      "stringAtom", "nonTemporalFunction", "signCast", "pfunc_arg", "relop", 
      "cls_op"
    },
    std::vector<std::string>{
      "", "'assert property'", "'@(posedge'", "','", "'..##'", "'..#'", 
      "'..['", "']@'", "", "'..&&..'", "", "", "", "", "'R'", "'..'", "'=>'", 
      "'->'", "'<->'", "", "", "'='", "'##'", "';'", "'first_match'", "'not'", 
      "'and'", "'intersect'", "'or'", "", "", "", "", "", "", "", "", "'.substr'", 
      "", "", "'{'", "'}'", "'['", "']'", "'('", "')'", "'inside'", "", 
      "", "", "", "", "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", 
      "'>='", "'<'", "'<='", "'=='", "'!='", "'==='", "'!=='", "'\\u003F'", 
      "'&'", "'|'", "'^'", "'~'", "'<<<'", "'>>>'", "'<<'", "'>>'", "'&&'", 
      "'||'", "'!'", "':'", "'::'", "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "PLACEHOLDER", "DT_AND", "EVENTUALLY", 
      "ALWAYS", "NEXT", "UNTIL", "RELEASE", "DOTS", "IMPL", "IMPLO", "IFF", 
      "SEREIMPL", "SEREIMPLO", "ASS", "DELAY", "SCOL", "FIRST_MATCH", "TNOT", 
      "TAND", "INTERSECT", "TOR", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", 
      "INT_VARIABLE", "CONST_SUFFIX", "LOGIC_VARIABLE", "BIT_VARIABLE", 
      "FLOAT_CONSTANT", "FLOAT_VARIABLE", "SUBSTR", "STRING_CONSTANT", "STRING_VARIABLE", 
      "LCURLY", "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "INSIDE", 
      "SIGN_CAST", "FUNCTION", "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", 
      "VERILOG_BASED", "FILL_LITERAL", "SINGLE_QUOTE", "PLUS", "MINUS", 
      "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "CASE_EQ", "CASE_NEQ", 
      "QUESTION", "BAND", "BOR", "BXOR", "NEG", "ALSHIFT", "ARSHIFT", "LSHIFT", 
      "RSHIFT", "AND", "OR", "NOT", "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,85,736,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,1,0,1,0,1,0,1,0,
  	1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
  	0,1,0,3,0,106,8,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,132,8,1,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,3,2,143,8,2,1,2,1,2,3,2,147,8,2,1,2,1,2,1,2,1,2,
  	3,2,153,8,2,1,2,1,2,3,2,157,8,2,1,2,1,2,1,2,3,2,162,8,2,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,182,8,3,
  	1,3,3,3,185,8,3,1,3,3,3,188,8,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,196,8,3,1,
  	3,3,3,199,8,3,1,3,3,3,202,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,211,8,3,
  	1,3,1,3,1,3,1,3,1,3,3,3,218,8,3,1,3,1,3,3,3,222,8,3,1,3,3,3,225,8,3,1,
  	3,3,3,228,8,3,1,3,3,3,231,8,3,1,3,3,3,234,8,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	3,3,242,8,3,1,3,1,3,1,3,1,3,1,3,3,3,249,8,3,1,3,3,3,252,8,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,266,8,3,1,3,3,3,269,8,3,1,3,
  	3,3,272,8,3,1,3,3,3,275,8,3,1,3,3,3,278,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,3,3,291,8,3,1,3,3,3,294,8,3,1,3,3,3,297,8,3,1,3,1,3,
  	1,3,1,3,1,3,5,3,304,8,3,10,3,12,3,307,9,3,1,4,1,4,1,4,1,4,1,4,1,4,3,4,
  	315,8,4,1,4,1,4,1,4,1,4,1,4,3,4,322,8,4,1,4,3,4,325,8,4,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,3,5,334,8,5,1,5,1,5,3,5,338,8,5,1,5,1,5,1,5,1,5,1,5,3,5,
  	345,8,5,1,5,3,5,348,8,5,1,5,3,5,351,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,3,5,361,8,5,1,5,3,5,364,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,
  	375,8,5,10,5,12,5,378,9,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,5,6,389,
  	8,6,10,6,12,6,392,9,6,1,6,1,6,3,6,396,8,6,1,7,1,7,1,7,1,7,1,7,3,7,403,
  	8,7,1,7,3,7,406,8,7,1,8,1,8,1,8,5,8,411,8,8,10,8,12,8,414,9,8,1,9,1,9,
  	1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	12,1,12,3,12,434,8,12,1,12,1,12,1,13,1,13,3,13,440,8,13,1,13,1,13,1,14,
  	1,14,3,14,446,8,14,1,14,1,14,1,15,1,15,3,15,452,8,15,1,15,1,15,1,16,1,
  	16,1,16,1,17,1,17,1,17,1,17,3,17,463,8,17,1,17,1,17,1,17,3,17,468,8,17,
  	1,18,1,18,1,18,1,18,3,18,474,8,18,1,18,1,18,1,18,3,18,479,8,18,1,19,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,507,8,19,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,5,19,518,8,19,10,19,12,19,
  	521,9,19,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,546,8,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,3,21,580,8,21,1,21,1,21,5,21,584,8,21,10,21,12,21,
  	587,9,21,1,21,1,21,3,21,591,8,21,1,21,1,21,5,21,595,8,21,10,21,12,21,
  	598,9,21,1,22,1,22,1,22,1,22,4,22,604,8,22,11,22,12,22,605,1,22,1,22,
  	1,22,1,22,1,22,1,22,1,22,1,22,5,22,616,8,22,10,22,12,22,619,9,22,1,22,
  	1,22,1,22,3,22,624,8,22,1,23,1,23,3,23,628,8,23,1,24,1,24,1,24,1,24,3,
  	24,634,8,24,1,24,1,24,1,25,1,25,1,25,3,25,641,8,25,1,25,1,25,1,25,3,25,
  	646,8,25,1,25,1,25,1,26,1,26,1,27,1,27,1,28,1,28,1,29,1,29,3,29,658,8,
  	29,1,30,1,30,1,30,3,30,663,8,30,1,30,3,30,666,8,30,1,31,1,31,1,31,1,31,
  	3,31,672,8,31,1,32,3,32,675,8,32,1,32,1,32,3,32,679,8,32,1,33,1,33,1,
  	34,1,34,1,34,1,34,1,34,1,34,3,34,689,8,34,1,34,1,34,1,34,1,34,1,34,1,
  	34,1,34,1,34,1,34,1,34,3,34,701,8,34,1,34,5,34,704,8,34,10,34,12,34,707,
  	9,34,1,35,1,35,1,36,1,36,1,36,1,36,1,36,5,36,716,8,36,10,36,12,36,719,
  	9,36,1,36,1,36,1,37,1,37,1,37,1,37,1,37,1,38,1,38,3,38,730,8,38,1,39,
  	1,39,1,40,1,40,1,40,0,5,6,10,38,42,68,41,0,2,4,6,8,10,12,14,16,18,20,
  	22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,
  	68,70,72,74,76,78,80,0,20,2,0,15,15,80,80,2,0,49,49,82,82,2,0,26,27,77,
  	77,3,0,28,28,70,70,78,78,2,0,25,25,79,79,1,0,13,14,2,0,26,26,77,77,2,
  	0,17,17,21,21,2,0,23,23,80,80,1,0,64,65,1,0,29,30,3,0,56,57,72,72,79,
  	79,1,0,58,59,1,0,56,57,1,0,73,76,1,0,64,67,1,0,35,36,1,0,38,39,1,0,60,
  	63,2,0,60,64,83,83,841,0,105,1,0,0,0,2,131,1,0,0,0,4,161,1,0,0,0,6,251,
  	1,0,0,0,8,324,1,0,0,0,10,363,1,0,0,0,12,395,1,0,0,0,14,405,1,0,0,0,16,
  	407,1,0,0,0,18,415,1,0,0,0,20,419,1,0,0,0,22,424,1,0,0,0,24,433,1,0,0,
  	0,26,439,1,0,0,0,28,445,1,0,0,0,30,451,1,0,0,0,32,455,1,0,0,0,34,458,
  	1,0,0,0,36,469,1,0,0,0,38,506,1,0,0,0,40,522,1,0,0,0,42,545,1,0,0,0,44,
  	623,1,0,0,0,46,627,1,0,0,0,48,629,1,0,0,0,50,637,1,0,0,0,52,649,1,0,0,
  	0,54,651,1,0,0,0,56,653,1,0,0,0,58,657,1,0,0,0,60,665,1,0,0,0,62,671,
  	1,0,0,0,64,678,1,0,0,0,66,680,1,0,0,0,68,688,1,0,0,0,70,708,1,0,0,0,72,
  	710,1,0,0,0,74,722,1,0,0,0,76,729,1,0,0,0,78,731,1,0,0,0,80,733,1,0,0,
  	0,82,83,5,11,0,0,83,84,5,44,0,0,84,85,3,4,2,0,85,86,5,45,0,0,86,87,5,
  	0,0,1,87,106,1,0,0,0,88,89,5,11,0,0,89,90,3,4,2,0,90,91,5,0,0,1,91,106,
  	1,0,0,0,92,93,3,2,1,0,93,94,5,0,0,1,94,106,1,0,0,0,95,96,5,11,0,0,96,
  	97,5,44,0,0,97,98,3,10,5,0,98,99,5,45,0,0,99,100,5,0,0,1,100,106,1,0,
  	0,0,101,102,5,11,0,0,102,103,3,10,5,0,103,104,5,0,0,1,104,106,1,0,0,0,
  	105,82,1,0,0,0,105,88,1,0,0,0,105,92,1,0,0,0,105,95,1,0,0,0,105,101,1,
  	0,0,0,106,1,1,0,0,0,107,108,5,1,0,0,108,109,5,44,0,0,109,110,3,2,1,0,
  	110,111,5,45,0,0,111,132,1,0,0,0,112,113,5,44,0,0,113,114,3,2,1,0,114,
  	115,5,45,0,0,115,132,1,0,0,0,116,117,5,2,0,0,117,118,3,38,19,0,118,119,
  	5,45,0,0,119,120,3,2,1,0,120,132,1,0,0,0,121,122,5,44,0,0,122,123,3,4,
  	2,0,123,124,5,45,0,0,124,132,1,0,0,0,125,132,3,4,2,0,126,127,5,44,0,0,
  	127,128,3,10,5,0,128,129,5,45,0,0,129,132,1,0,0,0,130,132,3,10,5,0,131,
  	107,1,0,0,0,131,112,1,0,0,0,131,116,1,0,0,0,131,121,1,0,0,0,131,125,1,
  	0,0,0,131,126,1,0,0,0,131,130,1,0,0,0,132,3,1,0,0,0,133,134,3,10,5,0,
  	134,135,5,16,0,0,135,136,3,10,5,0,136,162,1,0,0,0,137,138,3,10,5,0,138,
  	139,5,17,0,0,139,140,3,10,5,0,140,162,1,0,0,0,141,143,5,40,0,0,142,141,
  	1,0,0,0,142,143,1,0,0,0,143,144,1,0,0,0,144,146,3,6,3,0,145,147,5,41,
  	0,0,146,145,1,0,0,0,146,147,1,0,0,0,147,148,1,0,0,0,148,149,5,19,0,0,
  	149,150,3,10,5,0,150,162,1,0,0,0,151,153,5,40,0,0,152,151,1,0,0,0,152,
  	153,1,0,0,0,153,154,1,0,0,0,154,156,3,6,3,0,155,157,5,41,0,0,156,155,
  	1,0,0,0,156,157,1,0,0,0,157,158,1,0,0,0,158,159,5,20,0,0,159,160,3,10,
  	5,0,160,162,1,0,0,0,161,133,1,0,0,0,161,137,1,0,0,0,161,142,1,0,0,0,161,
  	152,1,0,0,0,162,5,1,0,0,0,163,164,6,3,-1,0,164,165,5,24,0,0,165,166,5,
  	44,0,0,166,167,3,6,3,0,167,168,5,45,0,0,168,252,1,0,0,0,169,170,5,44,
  	0,0,170,171,3,6,3,0,171,172,5,45,0,0,172,252,1,0,0,0,173,174,5,40,0,0,
  	174,175,3,6,3,0,175,176,5,41,0,0,176,252,1,0,0,0,177,178,3,8,4,0,178,
  	179,5,42,0,0,179,181,5,21,0,0,180,182,5,49,0,0,181,180,1,0,0,0,181,182,
  	1,0,0,0,182,184,1,0,0,0,183,185,7,0,0,0,184,183,1,0,0,0,184,185,1,0,0,
  	0,185,187,1,0,0,0,186,188,7,1,0,0,187,186,1,0,0,0,187,188,1,0,0,0,188,
  	189,1,0,0,0,189,190,5,43,0,0,190,252,1,0,0,0,191,192,3,8,4,0,192,193,
  	5,42,0,0,193,195,5,17,0,0,194,196,5,49,0,0,195,194,1,0,0,0,195,196,1,
  	0,0,0,196,198,1,0,0,0,197,199,7,0,0,0,198,197,1,0,0,0,198,199,1,0,0,0,
  	199,201,1,0,0,0,200,202,7,1,0,0,201,200,1,0,0,0,201,202,1,0,0,0,202,203,
  	1,0,0,0,203,204,5,43,0,0,204,252,1,0,0,0,205,210,3,22,11,0,206,207,5,
  	44,0,0,207,208,3,16,8,0,208,209,5,45,0,0,209,211,1,0,0,0,210,206,1,0,
  	0,0,210,211,1,0,0,0,211,252,1,0,0,0,212,217,5,9,0,0,213,214,5,44,0,0,
  	214,215,3,16,8,0,215,216,5,45,0,0,216,218,1,0,0,0,217,213,1,0,0,0,217,
  	218,1,0,0,0,218,252,1,0,0,0,219,221,5,22,0,0,220,222,5,42,0,0,221,220,
  	1,0,0,0,221,222,1,0,0,0,222,224,1,0,0,0,223,225,5,49,0,0,224,223,1,0,
  	0,0,224,225,1,0,0,0,225,227,1,0,0,0,226,228,7,0,0,0,227,226,1,0,0,0,227,
  	228,1,0,0,0,228,230,1,0,0,0,229,231,7,1,0,0,230,229,1,0,0,0,230,231,1,
  	0,0,0,231,233,1,0,0,0,232,234,5,43,0,0,233,232,1,0,0,0,233,234,1,0,0,
  	0,234,235,1,0,0,0,235,252,3,6,3,6,236,241,3,18,9,0,237,238,5,44,0,0,238,
  	239,3,16,8,0,239,240,5,45,0,0,240,242,1,0,0,0,241,237,1,0,0,0,241,242,
  	1,0,0,0,242,252,1,0,0,0,243,248,3,20,10,0,244,245,5,44,0,0,245,246,3,
  	16,8,0,246,247,5,45,0,0,247,249,1,0,0,0,248,244,1,0,0,0,248,249,1,0,0,
  	0,249,252,1,0,0,0,250,252,3,8,4,0,251,163,1,0,0,0,251,169,1,0,0,0,251,
  	173,1,0,0,0,251,177,1,0,0,0,251,191,1,0,0,0,251,205,1,0,0,0,251,212,1,
  	0,0,0,251,219,1,0,0,0,251,236,1,0,0,0,251,243,1,0,0,0,251,250,1,0,0,0,
  	252,305,1,0,0,0,253,254,10,11,0,0,254,255,5,69,0,0,255,304,3,6,3,12,256,
  	257,10,10,0,0,257,258,7,2,0,0,258,304,3,6,3,11,259,260,10,8,0,0,260,261,
  	7,3,0,0,261,304,3,6,3,9,262,263,10,7,0,0,263,265,5,22,0,0,264,266,5,42,
  	0,0,265,264,1,0,0,0,265,266,1,0,0,0,266,268,1,0,0,0,267,269,5,49,0,0,
  	268,267,1,0,0,0,268,269,1,0,0,0,269,271,1,0,0,0,270,272,7,0,0,0,271,270,
  	1,0,0,0,271,272,1,0,0,0,272,274,1,0,0,0,273,275,7,1,0,0,274,273,1,0,0,
  	0,274,275,1,0,0,0,275,277,1,0,0,0,276,278,5,43,0,0,277,276,1,0,0,0,277,
  	278,1,0,0,0,278,279,1,0,0,0,279,304,3,6,3,8,280,281,10,3,0,0,281,282,
  	5,80,0,0,282,304,3,6,3,4,283,284,10,2,0,0,284,285,5,23,0,0,285,304,3,
  	6,3,3,286,287,10,16,0,0,287,288,5,42,0,0,288,290,5,58,0,0,289,291,5,49,
  	0,0,290,289,1,0,0,0,290,291,1,0,0,0,291,293,1,0,0,0,292,294,7,0,0,0,293,
  	292,1,0,0,0,293,294,1,0,0,0,294,296,1,0,0,0,295,297,7,1,0,0,296,295,1,
  	0,0,0,296,297,1,0,0,0,297,298,1,0,0,0,298,304,5,43,0,0,299,300,10,15,
  	0,0,300,301,5,42,0,0,301,302,5,56,0,0,302,304,5,43,0,0,303,253,1,0,0,
  	0,303,256,1,0,0,0,303,259,1,0,0,0,303,262,1,0,0,0,303,280,1,0,0,0,303,
  	283,1,0,0,0,303,286,1,0,0,0,303,299,1,0,0,0,304,307,1,0,0,0,305,303,1,
  	0,0,0,305,306,1,0,0,0,306,7,1,0,0,0,307,305,1,0,0,0,308,309,5,44,0,0,
  	309,310,3,8,4,0,310,311,5,45,0,0,311,325,1,0,0,0,312,325,3,38,19,0,313,
  	315,5,79,0,0,314,313,1,0,0,0,314,315,1,0,0,0,315,316,1,0,0,0,316,321,
  	5,8,0,0,317,318,5,44,0,0,318,319,3,16,8,0,319,320,5,45,0,0,320,322,1,
  	0,0,0,321,317,1,0,0,0,321,322,1,0,0,0,322,325,1,0,0,0,323,325,3,12,6,
  	0,324,308,1,0,0,0,324,312,1,0,0,0,324,314,1,0,0,0,324,323,1,0,0,0,325,
  	9,1,0,0,0,326,327,6,5,-1,0,327,328,5,44,0,0,328,329,3,10,5,0,329,330,
  	5,45,0,0,330,364,1,0,0,0,331,333,4,5,8,0,332,334,5,40,0,0,333,332,1,0,
  	0,0,333,334,1,0,0,0,334,335,1,0,0,0,335,337,3,6,3,0,336,338,5,41,0,0,
  	337,336,1,0,0,0,337,338,1,0,0,0,338,364,1,0,0,0,339,340,4,5,9,0,340,341,
  	7,4,0,0,341,364,3,10,5,8,342,344,5,12,0,0,343,345,5,42,0,0,344,343,1,
  	0,0,0,344,345,1,0,0,0,345,347,1,0,0,0,346,348,5,49,0,0,347,346,1,0,0,
  	0,347,348,1,0,0,0,348,350,1,0,0,0,349,351,5,43,0,0,350,349,1,0,0,0,350,
  	351,1,0,0,0,351,352,1,0,0,0,352,364,3,10,5,7,353,354,5,10,0,0,354,364,
  	3,10,5,6,355,360,5,9,0,0,356,357,5,44,0,0,357,358,3,16,8,0,358,359,5,
  	45,0,0,359,361,1,0,0,0,360,356,1,0,0,0,360,361,1,0,0,0,361,364,1,0,0,
  	0,362,364,3,8,4,0,363,326,1,0,0,0,363,331,1,0,0,0,363,339,1,0,0,0,363,
  	342,1,0,0,0,363,353,1,0,0,0,363,355,1,0,0,0,363,362,1,0,0,0,364,376,1,
  	0,0,0,365,366,10,5,0,0,366,367,7,5,0,0,367,375,3,10,5,5,368,369,10,4,
  	0,0,369,370,7,6,0,0,370,375,3,10,5,5,371,372,10,3,0,0,372,373,7,3,0,0,
  	373,375,3,10,5,4,374,365,1,0,0,0,374,368,1,0,0,0,374,371,1,0,0,0,375,
  	378,1,0,0,0,376,374,1,0,0,0,376,377,1,0,0,0,377,11,1,0,0,0,378,376,1,
  	0,0,0,379,380,5,44,0,0,380,381,3,12,6,0,381,382,5,45,0,0,382,396,1,0,
  	0,0,383,384,5,48,0,0,384,385,5,44,0,0,385,390,3,14,7,0,386,387,5,3,0,
  	0,387,389,3,14,7,0,388,386,1,0,0,0,389,392,1,0,0,0,390,388,1,0,0,0,390,
  	391,1,0,0,0,391,393,1,0,0,0,392,390,1,0,0,0,393,394,5,45,0,0,394,396,
  	1,0,0,0,395,379,1,0,0,0,395,383,1,0,0,0,396,13,1,0,0,0,397,402,5,8,0,
  	0,398,399,5,44,0,0,399,400,3,16,8,0,400,401,5,45,0,0,401,403,1,0,0,0,
  	402,398,1,0,0,0,402,403,1,0,0,0,403,406,1,0,0,0,404,406,5,49,0,0,405,
  	397,1,0,0,0,405,404,1,0,0,0,406,15,1,0,0,0,407,412,5,49,0,0,408,409,5,
  	3,0,0,409,411,5,49,0,0,410,408,1,0,0,0,411,414,1,0,0,0,412,410,1,0,0,
  	0,412,413,1,0,0,0,413,17,1,0,0,0,414,412,1,0,0,0,415,416,5,4,0,0,416,
  	417,5,49,0,0,417,418,5,15,0,0,418,19,1,0,0,0,419,420,5,5,0,0,420,421,
  	5,49,0,0,421,422,5,69,0,0,422,423,5,15,0,0,423,21,1,0,0,0,424,425,5,6,
  	0,0,425,426,7,7,0,0,426,427,5,49,0,0,427,428,5,7,0,0,428,429,7,8,0,0,
  	429,430,5,15,0,0,430,23,1,0,0,0,431,434,3,38,19,0,432,434,3,34,17,0,433,
  	431,1,0,0,0,433,432,1,0,0,0,434,435,1,0,0,0,435,436,5,0,0,1,436,25,1,
  	0,0,0,437,440,3,42,21,0,438,440,3,36,18,0,439,437,1,0,0,0,439,438,1,0,
  	0,0,440,441,1,0,0,0,441,442,5,0,0,1,442,27,1,0,0,0,443,446,3,42,21,0,
  	444,446,3,36,18,0,445,443,1,0,0,0,445,444,1,0,0,0,446,447,1,0,0,0,447,
  	448,5,0,0,1,448,29,1,0,0,0,449,452,3,42,21,0,450,452,3,36,18,0,451,449,
  	1,0,0,0,451,450,1,0,0,0,452,453,1,0,0,0,453,454,5,0,0,1,454,31,1,0,0,
  	0,455,456,3,68,34,0,456,457,5,0,0,1,457,33,1,0,0,0,458,459,3,38,19,0,
  	459,462,5,68,0,0,460,463,3,38,19,0,461,463,3,34,17,0,462,460,1,0,0,0,
  	462,461,1,0,0,0,463,464,1,0,0,0,464,467,5,80,0,0,465,468,3,38,19,0,466,
  	468,3,34,17,0,467,465,1,0,0,0,467,466,1,0,0,0,468,35,1,0,0,0,469,470,
  	3,38,19,0,470,473,5,68,0,0,471,474,3,42,21,0,472,474,3,36,18,0,473,471,
  	1,0,0,0,473,472,1,0,0,0,474,475,1,0,0,0,475,478,5,80,0,0,476,479,3,42,
  	21,0,477,479,3,36,18,0,478,476,1,0,0,0,478,477,1,0,0,0,479,37,1,0,0,0,
  	480,481,6,19,-1,0,481,507,3,40,20,0,482,507,3,72,36,0,483,484,3,68,34,
  	0,484,485,3,78,39,0,485,486,3,68,34,0,486,507,1,0,0,0,487,488,3,68,34,
  	0,488,489,5,64,0,0,489,490,3,68,34,0,490,507,1,0,0,0,491,492,3,68,34,
  	0,492,493,5,65,0,0,493,494,3,68,34,0,494,507,1,0,0,0,495,496,5,44,0,0,
  	496,497,3,38,19,0,497,498,5,45,0,0,498,507,1,0,0,0,499,507,3,42,21,0,
  	500,501,5,44,0,0,501,502,3,34,17,0,502,503,5,45,0,0,503,507,1,0,0,0,504,
  	505,5,79,0,0,505,507,3,38,19,4,506,480,1,0,0,0,506,482,1,0,0,0,506,483,
  	1,0,0,0,506,487,1,0,0,0,506,491,1,0,0,0,506,495,1,0,0,0,506,499,1,0,0,
  	0,506,500,1,0,0,0,506,504,1,0,0,0,507,519,1,0,0,0,508,509,10,3,0,0,509,
  	510,7,9,0,0,510,518,3,38,19,4,511,512,10,2,0,0,512,513,5,77,0,0,513,518,
  	3,38,19,3,514,515,10,1,0,0,515,516,5,78,0,0,516,518,3,38,19,2,517,508,
  	1,0,0,0,517,511,1,0,0,0,517,514,1,0,0,0,518,521,1,0,0,0,519,517,1,0,0,
  	0,519,520,1,0,0,0,520,39,1,0,0,0,521,519,1,0,0,0,522,523,7,10,0,0,523,
  	41,1,0,0,0,524,525,6,21,-1,0,525,526,7,11,0,0,526,546,3,42,21,19,527,
  	546,3,72,36,0,528,546,3,74,37,0,529,546,3,58,29,0,530,546,3,62,31,0,531,
  	546,3,66,33,0,532,546,3,44,22,0,533,534,5,44,0,0,534,535,3,42,21,0,535,
  	536,5,45,0,0,536,546,1,0,0,0,537,538,5,44,0,0,538,539,3,36,18,0,539,540,
  	5,45,0,0,540,546,1,0,0,0,541,542,5,44,0,0,542,543,3,38,19,0,543,544,5,
  	45,0,0,544,546,1,0,0,0,545,524,1,0,0,0,545,527,1,0,0,0,545,528,1,0,0,
  	0,545,529,1,0,0,0,545,530,1,0,0,0,545,531,1,0,0,0,545,532,1,0,0,0,545,
  	533,1,0,0,0,545,537,1,0,0,0,545,541,1,0,0,0,546,596,1,0,0,0,547,548,10,
  	16,0,0,548,549,7,12,0,0,549,595,3,42,21,17,550,551,10,15,0,0,551,552,
  	7,13,0,0,552,595,3,42,21,16,553,554,10,14,0,0,554,555,7,14,0,0,555,595,
  	3,42,21,15,556,557,10,13,0,0,557,558,3,78,39,0,558,559,3,42,21,14,559,
  	595,1,0,0,0,560,561,10,11,0,0,561,562,7,15,0,0,562,595,3,42,21,12,563,
  	564,10,10,0,0,564,565,5,69,0,0,565,595,3,42,21,11,566,567,10,9,0,0,567,
  	568,5,71,0,0,568,595,3,42,21,10,569,570,10,8,0,0,570,571,5,70,0,0,571,
  	595,3,42,21,9,572,573,10,20,0,0,573,595,3,48,24,0,574,575,10,12,0,0,575,
  	576,5,46,0,0,576,585,5,40,0,0,577,580,3,56,28,0,578,580,3,50,25,0,579,
  	577,1,0,0,0,579,578,1,0,0,0,580,581,1,0,0,0,581,582,5,3,0,0,582,584,1,
  	0,0,0,583,579,1,0,0,0,584,587,1,0,0,0,585,583,1,0,0,0,585,586,1,0,0,0,
  	586,590,1,0,0,0,587,585,1,0,0,0,588,591,3,56,28,0,589,591,3,50,25,0,590,
  	588,1,0,0,0,590,589,1,0,0,0,591,592,1,0,0,0,592,593,5,41,0,0,593,595,
  	1,0,0,0,594,547,1,0,0,0,594,550,1,0,0,0,594,553,1,0,0,0,594,556,1,0,0,
  	0,594,560,1,0,0,0,594,563,1,0,0,0,594,566,1,0,0,0,594,569,1,0,0,0,594,
  	572,1,0,0,0,594,574,1,0,0,0,595,598,1,0,0,0,596,594,1,0,0,0,596,597,1,
  	0,0,0,597,43,1,0,0,0,598,596,1,0,0,0,599,600,5,40,0,0,600,603,3,46,23,
  	0,601,602,5,3,0,0,602,604,3,46,23,0,603,601,1,0,0,0,604,605,1,0,0,0,605,
  	603,1,0,0,0,605,606,1,0,0,0,606,607,1,0,0,0,607,608,5,41,0,0,608,624,
  	1,0,0,0,609,610,5,40,0,0,610,611,5,49,0,0,611,612,5,40,0,0,612,617,3,
  	46,23,0,613,614,5,3,0,0,614,616,3,46,23,0,615,613,1,0,0,0,616,619,1,0,
  	0,0,617,615,1,0,0,0,617,618,1,0,0,0,618,620,1,0,0,0,619,617,1,0,0,0,620,
  	621,5,41,0,0,621,622,5,41,0,0,622,624,1,0,0,0,623,599,1,0,0,0,623,609,
  	1,0,0,0,624,45,1,0,0,0,625,628,3,42,21,0,626,628,3,40,20,0,627,625,1,
  	0,0,0,627,626,1,0,0,0,628,47,1,0,0,0,629,630,5,42,0,0,630,633,5,49,0,
  	0,631,632,5,80,0,0,632,634,5,49,0,0,633,631,1,0,0,0,633,634,1,0,0,0,634,
  	635,1,0,0,0,635,636,5,43,0,0,636,49,1,0,0,0,637,640,5,42,0,0,638,641,
  	3,42,21,0,639,641,3,52,26,0,640,638,1,0,0,0,640,639,1,0,0,0,641,642,1,
  	0,0,0,642,645,5,80,0,0,643,646,3,42,21,0,644,646,3,54,27,0,645,643,1,
  	0,0,0,645,644,1,0,0,0,646,647,1,0,0,0,647,648,5,43,0,0,648,51,1,0,0,0,
  	649,650,5,82,0,0,650,53,1,0,0,0,651,652,5,82,0,0,652,55,1,0,0,0,653,654,
  	3,42,21,0,654,57,1,0,0,0,655,658,3,60,30,0,656,658,5,31,0,0,657,655,1,
  	0,0,0,657,656,1,0,0,0,658,59,1,0,0,0,659,666,5,51,0,0,660,662,5,49,0,
  	0,661,663,5,32,0,0,662,661,1,0,0,0,662,663,1,0,0,0,663,666,1,0,0,0,664,
  	666,5,52,0,0,665,659,1,0,0,0,665,660,1,0,0,0,665,664,1,0,0,0,666,61,1,
  	0,0,0,667,672,3,64,32,0,668,672,3,60,30,0,669,672,5,33,0,0,670,672,5,
  	34,0,0,671,667,1,0,0,0,671,668,1,0,0,0,671,669,1,0,0,0,671,670,1,0,0,
  	0,672,63,1,0,0,0,673,675,5,49,0,0,674,673,1,0,0,0,674,675,1,0,0,0,675,
  	676,1,0,0,0,676,679,5,53,0,0,677,679,5,54,0,0,678,674,1,0,0,0,678,677,
  	1,0,0,0,679,65,1,0,0,0,680,681,7,16,0,0,681,67,1,0,0,0,682,683,6,34,-1,
  	0,683,689,3,70,35,0,684,685,5,44,0,0,685,686,3,68,34,0,686,687,5,45,0,
  	0,687,689,1,0,0,0,688,682,1,0,0,0,688,684,1,0,0,0,689,705,1,0,0,0,690,
  	691,10,4,0,0,691,692,5,56,0,0,692,704,3,68,34,5,693,694,10,3,0,0,694,
  	695,5,37,0,0,695,700,5,44,0,0,696,697,5,49,0,0,697,698,5,3,0,0,698,701,
  	5,49,0,0,699,701,5,49,0,0,700,696,1,0,0,0,700,699,1,0,0,0,700,701,1,0,
  	0,0,701,702,1,0,0,0,702,704,5,45,0,0,703,690,1,0,0,0,703,693,1,0,0,0,
  	704,707,1,0,0,0,705,703,1,0,0,0,705,706,1,0,0,0,706,69,1,0,0,0,707,705,
  	1,0,0,0,708,709,7,17,0,0,709,71,1,0,0,0,710,711,5,48,0,0,711,712,5,44,
  	0,0,712,717,3,76,38,0,713,714,5,3,0,0,714,716,3,76,38,0,715,713,1,0,0,
  	0,716,719,1,0,0,0,717,715,1,0,0,0,717,718,1,0,0,0,718,720,1,0,0,0,719,
  	717,1,0,0,0,720,721,5,45,0,0,721,73,1,0,0,0,722,723,5,47,0,0,723,724,
  	5,44,0,0,724,725,3,42,21,0,725,726,5,45,0,0,726,75,1,0,0,0,727,730,3,
  	42,21,0,728,730,3,38,19,0,729,727,1,0,0,0,729,728,1,0,0,0,730,77,1,0,
  	0,0,731,732,7,18,0,0,732,79,1,0,0,0,733,734,7,19,0,0,734,81,1,0,0,0,86,
  	105,131,142,146,152,156,161,181,184,187,195,198,201,210,217,221,224,227,
  	230,233,241,248,251,265,268,271,274,277,290,293,296,303,305,314,321,324,
  	333,337,344,347,350,360,363,374,376,390,395,402,405,412,433,439,445,451,
  	462,467,473,478,506,517,519,545,579,585,590,594,596,605,617,623,627,633,
  	640,645,657,662,665,671,674,678,688,700,703,705,717,729
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  temporalParserStaticData = std::move(staticData);
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

temporalParser::TformulaContext* temporalParser::FormulaContext::tformula() {
  return getRuleContext<temporalParser::TformulaContext>(0);
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
    setState(105);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(82);
      match(temporalParser::ALWAYS);
      setState(83);
      match(temporalParser::LROUND);
      setState(84);
      implication();
      setState(85);
      match(temporalParser::RROUND);
      setState(86);
      match(temporalParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(88);
      match(temporalParser::ALWAYS);
      setState(89);
      implication();
      setState(90);
      match(temporalParser::EOF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(92);
      sva_assert();
      setState(93);
      match(temporalParser::EOF);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(95);
      match(temporalParser::ALWAYS);
      setState(96);
      match(temporalParser::LROUND);
      setState(97);
      tformula(0);
      setState(98);
      match(temporalParser::RROUND);
      setState(99);
      match(temporalParser::EOF);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(101);
      match(temporalParser::ALWAYS);
      setState(102);
      tformula(0);
      setState(103);
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

temporalParser::TformulaContext* temporalParser::Sva_assertContext::tformula() {
  return getRuleContext<temporalParser::TformulaContext>(0);
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
    setState(131);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(107);
      match(temporalParser::T__0);
      setState(108);
      match(temporalParser::LROUND);
      setState(109);
      sva_assert();
      setState(110);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(112);
      match(temporalParser::LROUND);
      setState(113);
      sva_assert();
      setState(114);
      match(temporalParser::RROUND);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(116);
      match(temporalParser::T__1);
      setState(117);
      boolean(0);
      setState(118);
      match(temporalParser::RROUND);
      setState(119);
      sva_assert();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(121);
      match(temporalParser::LROUND);
      setState(122);
      implication();
      setState(123);
      match(temporalParser::RROUND);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(125);
      implication();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(126);
      match(temporalParser::LROUND);
      setState(127);
      tformula(0);
      setState(128);
      match(temporalParser::RROUND);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(130);
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
    setState(161);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(133);
      tformula(0);
      setState(134);
      match(temporalParser::IMPL);
      setState(135);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(137);
      tformula(0);
      setState(138);
      match(temporalParser::IMPLO);
      setState(139);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(142);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(141);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(144);
      sere(0);
      setState(146);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RCURLY) {
        setState(145);
        match(temporalParser::RCURLY);
      }
      setState(148);
      match(temporalParser::SEREIMPL);
      setState(149);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(152);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(151);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(154);
      sere(0);
      setState(156);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RCURLY) {
        setState(155);
        match(temporalParser::RCURLY);
      }
      setState(158);
      match(temporalParser::SEREIMPLO);
      setState(159);
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
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(164);
      match(temporalParser::FIRST_MATCH);
      setState(165);
      match(temporalParser::LROUND);
      setState(166);
      sere(0);
      setState(167);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      setState(169);
      match(temporalParser::LROUND);
      setState(170);
      sere(0);
      setState(171);
      match(temporalParser::RROUND);
      break;
    }

    case 3: {
      setState(173);
      match(temporalParser::LCURLY);
      setState(174);
      sere(0);
      setState(175);
      match(temporalParser::RCURLY);
      break;
    }

    case 4: {
      setState(177);
      booleanLayer();
      setState(178);
      match(temporalParser::LSQUARED);
      setState(179);
      match(temporalParser::ASS);
      setState(181);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
      case 1: {
        setState(180);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(184);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS || _la == temporalParser::COL) {
        setState(183);
        _la = _input->LA(1);
        if (!(_la == temporalParser::DOTS || _la == temporalParser::COL)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(187);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER

      || _la == temporalParser::DOLLAR) {
        setState(186);
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
      setState(189);
      match(temporalParser::RSQUARED);
      break;
    }

    case 5: {
      setState(191);
      booleanLayer();
      setState(192);
      match(temporalParser::LSQUARED);
      setState(193);
      match(temporalParser::IMPLO);
      setState(195);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
      case 1: {
        setState(194);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(198);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS || _la == temporalParser::COL) {
        setState(197);
        _la = _input->LA(1);
        if (!(_la == temporalParser::DOTS || _la == temporalParser::COL)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(201);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER

      || _la == temporalParser::DOLLAR) {
        setState(200);
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
      setState(203);
      match(temporalParser::RSQUARED);
      break;
    }

    case 6: {
      setState(205);
      dt_ncreps();
      setState(210);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
      case 1: {
        setState(206);
        match(temporalParser::LROUND);
        setState(207);
        placeholder_domain();
        setState(208);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 7: {
      setState(212);
      match(temporalParser::DT_AND);
      setState(217);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
      case 1: {
        setState(213);
        match(temporalParser::LROUND);
        setState(214);
        placeholder_domain();
        setState(215);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 8: {
      setState(219);
      match(temporalParser::DELAY);
      setState(221);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::LSQUARED) {
        setState(220);
        match(temporalParser::LSQUARED);
      }
      setState(224);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(223);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(227);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS || _la == temporalParser::COL) {
        setState(226);
        _la = _input->LA(1);
        if (!(_la == temporalParser::DOTS || _la == temporalParser::COL)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(230);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
      case 1: {
        setState(229);
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
      setState(233);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RSQUARED) {
        setState(232);
        match(temporalParser::RSQUARED);
      }
      setState(235);
      sere(6);
      break;
    }

    case 9: {
      setState(236);
      dt_next();
      setState(241);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(237);
        match(temporalParser::LROUND);
        setState(238);
        placeholder_domain();
        setState(239);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 10: {
      setState(243);
      dt_next_and();
      setState(248);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
      case 1: {
        setState(244);
        match(temporalParser::LROUND);
        setState(245);
        placeholder_domain();
        setState(246);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 11: {
      setState(250);
      booleanLayer();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(305);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(303);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(253);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(254);
          match(temporalParser::BAND);
          setState(255);
          sere(12);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(256);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(257);
          _la = _input->LA(1);
          if (!(((((_la - 26) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 26)) & 2251799813685251) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(258);
          sere(11);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(259);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(260);
          _la = _input->LA(1);
          if (!(((((_la - 28) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 28)) & 1130297953353729) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(261);
          sere(9);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(262);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(263);
          match(temporalParser::DELAY);
          setState(265);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::LSQUARED) {
            setState(264);
            match(temporalParser::LSQUARED);
          }
          setState(268);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
          case 1: {
            setState(267);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(271);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::DOTS || _la == temporalParser::COL) {
            setState(270);
            _la = _input->LA(1);
            if (!(_la == temporalParser::DOTS || _la == temporalParser::COL)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
          }
          setState(274);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
          case 1: {
            setState(273);
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
          setState(277);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::RSQUARED) {
            setState(276);
            match(temporalParser::RSQUARED);
          }
          setState(279);
          sere(8);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(280);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(281);
          match(temporalParser::COL);
          setState(282);
          sere(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(283);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(284);
          match(temporalParser::SCOL);
          setState(285);
          sere(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(286);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(287);
          match(temporalParser::LSQUARED);
          setState(288);
          match(temporalParser::TIMES);
          setState(290);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
          case 1: {
            setState(289);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(293);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::DOTS || _la == temporalParser::COL) {
            setState(292);
            _la = _input->LA(1);
            if (!(_la == temporalParser::DOTS || _la == temporalParser::COL)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
          }
          setState(296);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::UINTEGER

          || _la == temporalParser::DOLLAR) {
            setState(295);
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
          setState(298);
          match(temporalParser::RSQUARED);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(299);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(300);
          match(temporalParser::LSQUARED);
          setState(301);
          match(temporalParser::PLUS);
          setState(302);
          match(temporalParser::RSQUARED);
          break;
        }

        default:
          break;
        } 
      }
      setState(307);
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
    setState(324);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(308);
      match(temporalParser::LROUND);
      setState(309);
      booleanLayer();
      setState(310);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(312);
      boolean(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(314);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::NOT) {
        setState(313);
        match(temporalParser::NOT);
      }
      setState(316);
      match(temporalParser::PLACEHOLDER);
      setState(321);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
      case 1: {
        setState(317);
        match(temporalParser::LROUND);
        setState(318);
        placeholder_domain();
        setState(319);
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
      setState(323);
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
    setState(363);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      setState(327);
      match(temporalParser::LROUND);
      setState(328);
      tformula(0);
      setState(329);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      setState(331);

      if (!(canUseSharedOperator(safeTokenText(_input->LT(-1)),safeTokenText(_input->LT(2))))) throw FailedPredicateException(this, "canUseSharedOperator(safeTokenText(_input->LT(-1)),safeTokenText(_input->LT(2)))");
      setState(333);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
      case 1: {
        setState(332);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(335);
      sere(0);
      setState(337);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
      case 1: {
        setState(336);
        match(temporalParser::RCURLY);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      setState(339);

      if (!(canTakeThisNot(safeTokenText(_input->LT(1)),safeTokenText(_input->LT(2))))) throw FailedPredicateException(this, "canTakeThisNot(safeTokenText(_input->LT(1)),safeTokenText(_input->LT(2)))");
      setState(340);
      _la = _input->LA(1);
      if (!(_la == temporalParser::TNOT

      || _la == temporalParser::NOT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(341);
      tformula(8);
      break;
    }

    case 4: {
      setState(342);
      match(temporalParser::NEXT);
      setState(344);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
      case 1: {
        setState(343);
        match(temporalParser::LSQUARED);
        break;
      }

      default:
        break;
      }
      setState(347);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
      case 1: {
        setState(346);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(350);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
      case 1: {
        setState(349);
        match(temporalParser::RSQUARED);
        break;
      }

      default:
        break;
      }
      setState(352);
      tformula(7);
      break;
    }

    case 5: {
      setState(353);
      match(temporalParser::EVENTUALLY);
      setState(354);
      tformula(6);
      break;
    }

    case 6: {
      setState(355);
      match(temporalParser::DT_AND);
      setState(360);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
      case 1: {
        setState(356);
        match(temporalParser::LROUND);
        setState(357);
        placeholder_domain();
        setState(358);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 7: {
      setState(362);
      booleanLayer();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(376);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(374);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(365);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(366);
          _la = _input->LA(1);
          if (!(_la == temporalParser::UNTIL

          || _la == temporalParser::RELEASE)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(367);
          tformula(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(368);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(369);
          _la = _input->LA(1);
          if (!(_la == temporalParser::TAND

          || _la == temporalParser::AND)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(370);
          tformula(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(371);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(372);
          _la = _input->LA(1);
          if (!(((((_la - 28) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 28)) & 1130297953353729) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(373);
          tformula(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(378);
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
    setState(395);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::LROUND: {
        enterOuterAlt(_localctx, 1);
        setState(379);
        match(temporalParser::LROUND);
        setState(380);
        temporalFunction();
        setState(381);
        match(temporalParser::RROUND);
        break;
      }

      case temporalParser::FUNCTION: {
        enterOuterAlt(_localctx, 2);
        setState(383);
        match(temporalParser::FUNCTION);
        setState(384);
        match(temporalParser::LROUND);
        setState(385);
        tfunc_arg();
        setState(390);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == temporalParser::T__2) {
          setState(386);
          match(temporalParser::T__2);
          setState(387);
          tfunc_arg();
          setState(392);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(393);
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
    setState(405);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::PLACEHOLDER: {
        enterOuterAlt(_localctx, 1);
        setState(397);
        match(temporalParser::PLACEHOLDER);
        setState(402);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == temporalParser::LROUND) {
          setState(398);
          match(temporalParser::LROUND);
          setState(399);
          placeholder_domain();
          setState(400);
          match(temporalParser::RROUND);
        }
        break;
      }

      case temporalParser::UINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(404);
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
    setState(407);
    match(temporalParser::UINTEGER);
    setState(412);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == temporalParser::T__2) {
      setState(408);
      match(temporalParser::T__2);

      setState(409);
      match(temporalParser::UINTEGER);
      setState(414);
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
    setState(415);
    match(temporalParser::T__3);
    setState(416);
    match(temporalParser::UINTEGER);
    setState(417);
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
    setState(419);
    match(temporalParser::T__4);
    setState(420);
    match(temporalParser::UINTEGER);
    setState(421);
    match(temporalParser::BAND);
    setState(422);
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
    setState(424);
    match(temporalParser::T__5);
    setState(425);
    _la = _input->LA(1);
    if (!(_la == temporalParser::IMPLO

    || _la == temporalParser::ASS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(426);
    match(temporalParser::UINTEGER);
    setState(427);
    match(temporalParser::T__6);
    setState(428);
    _la = _input->LA(1);
    if (!(_la == temporalParser::SCOL

    || _la == temporalParser::COL)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(429);
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

tree::TerminalNode* temporalParser::StartBooleanContext::EOF() {
  return getToken(temporalParser::EOF, 0);
}

temporalParser::BooleanContext* temporalParser::StartBooleanContext::boolean() {
  return getRuleContext<temporalParser::BooleanContext>(0);
}

temporalParser::BooleanTernaryContext* temporalParser::StartBooleanContext::booleanTernary() {
  return getRuleContext<temporalParser::BooleanTernaryContext>(0);
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
    setState(433);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      setState(431);
      boolean(0);
      break;
    }

    case 2: {
      setState(432);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(435);
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

tree::TerminalNode* temporalParser::StartIntContext::EOF() {
  return getToken(temporalParser::EOF, 0);
}

temporalParser::NumericContext* temporalParser::StartIntContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}

temporalParser::NumericTernaryContext* temporalParser::StartIntContext::numericTernary() {
  return getRuleContext<temporalParser::NumericTernaryContext>(0);
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
    setState(439);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      setState(437);
      numeric(0);
      break;
    }

    case 2: {
      setState(438);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(441);
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

tree::TerminalNode* temporalParser::StartLogicContext::EOF() {
  return getToken(temporalParser::EOF, 0);
}

temporalParser::NumericContext* temporalParser::StartLogicContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}

temporalParser::NumericTernaryContext* temporalParser::StartLogicContext::numericTernary() {
  return getRuleContext<temporalParser::NumericTernaryContext>(0);
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
    setState(445);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
    case 1: {
      setState(443);
      numeric(0);
      break;
    }

    case 2: {
      setState(444);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(447);
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

tree::TerminalNode* temporalParser::StartFloatContext::EOF() {
  return getToken(temporalParser::EOF, 0);
}

temporalParser::NumericContext* temporalParser::StartFloatContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}

temporalParser::NumericTernaryContext* temporalParser::StartFloatContext::numericTernary() {
  return getRuleContext<temporalParser::NumericTernaryContext>(0);
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
    setState(451);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      setState(449);
      numeric(0);
      break;
    }

    case 2: {
      setState(450);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(453);
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
    setState(455);
    string(0);
    setState(456);
    match(temporalParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanTernaryContext ------------------------------------------------------------------

temporalParser::BooleanTernaryContext::BooleanTernaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<temporalParser::BooleanContext *> temporalParser::BooleanTernaryContext::boolean() {
  return getRuleContexts<temporalParser::BooleanContext>();
}

temporalParser::BooleanContext* temporalParser::BooleanTernaryContext::boolean(size_t i) {
  return getRuleContext<temporalParser::BooleanContext>(i);
}

tree::TerminalNode* temporalParser::BooleanTernaryContext::QUESTION() {
  return getToken(temporalParser::QUESTION, 0);
}

tree::TerminalNode* temporalParser::BooleanTernaryContext::COL() {
  return getToken(temporalParser::COL, 0);
}

std::vector<temporalParser::BooleanTernaryContext *> temporalParser::BooleanTernaryContext::booleanTernary() {
  return getRuleContexts<temporalParser::BooleanTernaryContext>();
}

temporalParser::BooleanTernaryContext* temporalParser::BooleanTernaryContext::booleanTernary(size_t i) {
  return getRuleContext<temporalParser::BooleanTernaryContext>(i);
}


size_t temporalParser::BooleanTernaryContext::getRuleIndex() const {
  return temporalParser::RuleBooleanTernary;
}

void temporalParser::BooleanTernaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanTernary(this);
}

void temporalParser::BooleanTernaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanTernary(this);
}

temporalParser::BooleanTernaryContext* temporalParser::booleanTernary() {
  BooleanTernaryContext *_localctx = _tracker.createInstance<BooleanTernaryContext>(_ctx, getState());
  enterRule(_localctx, 34, temporalParser::RuleBooleanTernary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(458);
    boolean(0);
    setState(459);
    match(temporalParser::QUESTION);
    setState(462);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      setState(460);
      boolean(0);
      break;
    }

    case 2: {
      setState(461);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(464);
    match(temporalParser::COL);
    setState(467);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      setState(465);
      boolean(0);
      break;
    }

    case 2: {
      setState(466);
      booleanTernary();
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

//----------------- NumericTernaryContext ------------------------------------------------------------------

temporalParser::NumericTernaryContext::NumericTernaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::BooleanContext* temporalParser::NumericTernaryContext::boolean() {
  return getRuleContext<temporalParser::BooleanContext>(0);
}

tree::TerminalNode* temporalParser::NumericTernaryContext::QUESTION() {
  return getToken(temporalParser::QUESTION, 0);
}

tree::TerminalNode* temporalParser::NumericTernaryContext::COL() {
  return getToken(temporalParser::COL, 0);
}

std::vector<temporalParser::NumericContext *> temporalParser::NumericTernaryContext::numeric() {
  return getRuleContexts<temporalParser::NumericContext>();
}

temporalParser::NumericContext* temporalParser::NumericTernaryContext::numeric(size_t i) {
  return getRuleContext<temporalParser::NumericContext>(i);
}

std::vector<temporalParser::NumericTernaryContext *> temporalParser::NumericTernaryContext::numericTernary() {
  return getRuleContexts<temporalParser::NumericTernaryContext>();
}

temporalParser::NumericTernaryContext* temporalParser::NumericTernaryContext::numericTernary(size_t i) {
  return getRuleContext<temporalParser::NumericTernaryContext>(i);
}


size_t temporalParser::NumericTernaryContext::getRuleIndex() const {
  return temporalParser::RuleNumericTernary;
}

void temporalParser::NumericTernaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericTernary(this);
}

void temporalParser::NumericTernaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericTernary(this);
}

temporalParser::NumericTernaryContext* temporalParser::numericTernary() {
  NumericTernaryContext *_localctx = _tracker.createInstance<NumericTernaryContext>(_ctx, getState());
  enterRule(_localctx, 36, temporalParser::RuleNumericTernary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(469);
    boolean(0);
    setState(470);
    match(temporalParser::QUESTION);
    setState(473);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      setState(471);
      numeric(0);
      break;
    }

    case 2: {
      setState(472);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(475);
    match(temporalParser::COL);
    setState(478);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      setState(476);
      numeric(0);
      break;
    }

    case 2: {
      setState(477);
      numericTernary();
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

//----------------- BooleanContext ------------------------------------------------------------------

temporalParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::BooleanAtomContext* temporalParser::BooleanContext::booleanAtom() {
  return getRuleContext<temporalParser::BooleanAtomContext>(0);
}

temporalParser::NonTemporalFunctionContext* temporalParser::BooleanContext::nonTemporalFunction() {
  return getRuleContext<temporalParser::NonTemporalFunctionContext>(0);
}

std::vector<temporalParser::StringContext *> temporalParser::BooleanContext::string() {
  return getRuleContexts<temporalParser::StringContext>();
}

temporalParser::StringContext* temporalParser::BooleanContext::string(size_t i) {
  return getRuleContext<temporalParser::StringContext>(i);
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

tree::TerminalNode* temporalParser::BooleanContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

std::vector<temporalParser::BooleanContext *> temporalParser::BooleanContext::boolean() {
  return getRuleContexts<temporalParser::BooleanContext>();
}

temporalParser::BooleanContext* temporalParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<temporalParser::BooleanContext>(i);
}

tree::TerminalNode* temporalParser::BooleanContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

temporalParser::NumericContext* temporalParser::BooleanContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}

temporalParser::BooleanTernaryContext* temporalParser::BooleanContext::booleanTernary() {
  return getRuleContext<temporalParser::BooleanTernaryContext>(0);
}

tree::TerminalNode* temporalParser::BooleanContext::NOT() {
  return getToken(temporalParser::NOT, 0);
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
  size_t startState = 38;
  enterRecursionRule(_localctx, 38, temporalParser::RuleBoolean, precedence);

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
    setState(506);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(481);
      booleanAtom();
      break;
    }

    case 2: {
      setState(482);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(483);
      string(0);
      setState(484);
      relop();
      setState(485);
      string(0);
      break;
    }

    case 4: {
      setState(487);
      string(0);
      setState(488);
      match(temporalParser::EQ);
      setState(489);
      string(0);
      break;
    }

    case 5: {
      setState(491);
      string(0);
      setState(492);
      match(temporalParser::NEQ);
      setState(493);
      string(0);
      break;
    }

    case 6: {
      setState(495);
      match(temporalParser::LROUND);
      setState(496);
      boolean(0);
      setState(497);
      match(temporalParser::RROUND);
      break;
    }

    case 7: {
      setState(499);
      numeric(0);
      break;
    }

    case 8: {
      setState(500);
      match(temporalParser::LROUND);
      setState(501);
      booleanTernary();
      setState(502);
      match(temporalParser::RROUND);
      break;
    }

    case 9: {
      setState(504);
      match(temporalParser::NOT);
      setState(505);
      boolean(4);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(519);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(517);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(508);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(509);
          antlrcpp::downCast<BooleanContext *>(_localctx)->eqop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == temporalParser::EQ

          || _la == temporalParser::NEQ)) {
            antlrcpp::downCast<BooleanContext *>(_localctx)->eqop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(510);
          boolean(4);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(511);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(512);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(temporalParser::AND);
          setState(513);
          boolean(3);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(514);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(515);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(temporalParser::OR);
          setState(516);
          boolean(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(521);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx);
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
  enterRule(_localctx, 40, temporalParser::RuleBooleanAtom);
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
    setState(522);
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

std::vector<temporalParser::NumericContext *> temporalParser::NumericContext::numeric() {
  return getRuleContexts<temporalParser::NumericContext>();
}

temporalParser::NumericContext* temporalParser::NumericContext::numeric(size_t i) {
  return getRuleContext<temporalParser::NumericContext>(i);
}

tree::TerminalNode* temporalParser::NumericContext::NEG() {
  return getToken(temporalParser::NEG, 0);
}

tree::TerminalNode* temporalParser::NumericContext::NOT() {
  return getToken(temporalParser::NOT, 0);
}

tree::TerminalNode* temporalParser::NumericContext::MINUS() {
  return getToken(temporalParser::MINUS, 0);
}

tree::TerminalNode* temporalParser::NumericContext::PLUS() {
  return getToken(temporalParser::PLUS, 0);
}

temporalParser::NonTemporalFunctionContext* temporalParser::NumericContext::nonTemporalFunction() {
  return getRuleContext<temporalParser::NonTemporalFunctionContext>(0);
}

temporalParser::SignCastContext* temporalParser::NumericContext::signCast() {
  return getRuleContext<temporalParser::SignCastContext>(0);
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

temporalParser::ConcatenationContext* temporalParser::NumericContext::concatenation() {
  return getRuleContext<temporalParser::ConcatenationContext>(0);
}

tree::TerminalNode* temporalParser::NumericContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

tree::TerminalNode* temporalParser::NumericContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}

temporalParser::NumericTernaryContext* temporalParser::NumericContext::numericTernary() {
  return getRuleContext<temporalParser::NumericTernaryContext>(0);
}

temporalParser::BooleanContext* temporalParser::NumericContext::boolean() {
  return getRuleContext<temporalParser::BooleanContext>(0);
}

tree::TerminalNode* temporalParser::NumericContext::TIMES() {
  return getToken(temporalParser::TIMES, 0);
}

tree::TerminalNode* temporalParser::NumericContext::DIV() {
  return getToken(temporalParser::DIV, 0);
}

tree::TerminalNode* temporalParser::NumericContext::LSHIFT() {
  return getToken(temporalParser::LSHIFT, 0);
}

tree::TerminalNode* temporalParser::NumericContext::RSHIFT() {
  return getToken(temporalParser::RSHIFT, 0);
}

tree::TerminalNode* temporalParser::NumericContext::ALSHIFT() {
  return getToken(temporalParser::ALSHIFT, 0);
}

tree::TerminalNode* temporalParser::NumericContext::ARSHIFT() {
  return getToken(temporalParser::ARSHIFT, 0);
}

temporalParser::RelopContext* temporalParser::NumericContext::relop() {
  return getRuleContext<temporalParser::RelopContext>(0);
}

tree::TerminalNode* temporalParser::NumericContext::EQ() {
  return getToken(temporalParser::EQ, 0);
}

tree::TerminalNode* temporalParser::NumericContext::NEQ() {
  return getToken(temporalParser::NEQ, 0);
}

tree::TerminalNode* temporalParser::NumericContext::CASE_EQ() {
  return getToken(temporalParser::CASE_EQ, 0);
}

tree::TerminalNode* temporalParser::NumericContext::CASE_NEQ() {
  return getToken(temporalParser::CASE_NEQ, 0);
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

tree::TerminalNode* temporalParser::NumericContext::INSIDE() {
  return getToken(temporalParser::INSIDE, 0);
}

tree::TerminalNode* temporalParser::NumericContext::LCURLY() {
  return getToken(temporalParser::LCURLY, 0);
}

tree::TerminalNode* temporalParser::NumericContext::RCURLY() {
  return getToken(temporalParser::RCURLY, 0);
}

std::vector<temporalParser::Sm_constantContext *> temporalParser::NumericContext::sm_constant() {
  return getRuleContexts<temporalParser::Sm_constantContext>();
}

temporalParser::Sm_constantContext* temporalParser::NumericContext::sm_constant(size_t i) {
  return getRuleContext<temporalParser::Sm_constantContext>(i);
}

std::vector<temporalParser::Sm_rangeContext *> temporalParser::NumericContext::sm_range() {
  return getRuleContexts<temporalParser::Sm_rangeContext>();
}

temporalParser::Sm_rangeContext* temporalParser::NumericContext::sm_range(size_t i) {
  return getRuleContext<temporalParser::Sm_rangeContext>(i);
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
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, temporalParser::RuleNumeric, precedence);

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
    setState(545);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
    case 1: {
      setState(525);
      antlrcpp::downCast<NumericContext *>(_localctx)->unop = _input->LT(1);
      _la = _input->LA(1);
      if (!(((((_la - 56) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 56)) & 8454147) != 0))) {
        antlrcpp::downCast<NumericContext *>(_localctx)->unop = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(526);
      numeric(19);
      break;
    }

    case 2: {
      setState(527);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(528);
      signCast();
      break;
    }

    case 4: {
      setState(529);
      intAtom();
      break;
    }

    case 5: {
      setState(530);
      logicAtom();
      break;
    }

    case 6: {
      setState(531);
      floatAtom();
      break;
    }

    case 7: {
      setState(532);
      concatenation();
      break;
    }

    case 8: {
      setState(533);
      match(temporalParser::LROUND);
      setState(534);
      numeric(0);
      setState(535);
      match(temporalParser::RROUND);
      break;
    }

    case 9: {
      setState(537);
      match(temporalParser::LROUND);
      setState(538);
      numericTernary();
      setState(539);
      match(temporalParser::RROUND);
      break;
    }

    case 10: {
      setState(541);
      match(temporalParser::LROUND);
      setState(542);
      boolean(0);
      setState(543);
      match(temporalParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(596);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(594);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(547);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(548);
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
          setState(549);
          numeric(17);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(550);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(551);
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
          setState(552);
          numeric(16);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(553);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(554);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 73) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 73)) & 15) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->logop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(555);
          numeric(15);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(556);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(557);
          relop();
          setState(558);
          numeric(14);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(560);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(561);
          antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 64) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 64)) & 15) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(562);
          numeric(12);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(563);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(564);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BAND);
          setState(565);
          numeric(11);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(566);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(567);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BXOR);
          setState(568);
          numeric(10);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(569);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(570);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BOR);
          setState(571);
          numeric(9);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(572);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(573);
          range();
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(574);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(575);
          match(temporalParser::INSIDE);
          setState(576);
          match(temporalParser::LCURLY);
          setState(585);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(579);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case temporalParser::INT_VARIABLE:
                case temporalParser::LOGIC_VARIABLE:
                case temporalParser::BIT_VARIABLE:
                case temporalParser::FLOAT_CONSTANT:
                case temporalParser::FLOAT_VARIABLE:
                case temporalParser::LCURLY:
                case temporalParser::LROUND:
                case temporalParser::SIGN_CAST:
                case temporalParser::FUNCTION:
                case temporalParser::UINTEGER:
                case temporalParser::GCC_BINARY:
                case temporalParser::HEX:
                case temporalParser::VERILOG_BASED:
                case temporalParser::FILL_LITERAL:
                case temporalParser::PLUS:
                case temporalParser::MINUS:
                case temporalParser::NEG:
                case temporalParser::NOT: {
                  setState(577);
                  sm_constant();
                  break;
                }

                case temporalParser::LSQUARED: {
                  setState(578);
                  sm_range();
                  break;
                }

              default:
                throw NoViableAltException(this);
              }
              setState(581);
              match(temporalParser::T__2); 
            }
            setState(587);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
          }
          setState(590);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case temporalParser::INT_VARIABLE:
            case temporalParser::LOGIC_VARIABLE:
            case temporalParser::BIT_VARIABLE:
            case temporalParser::FLOAT_CONSTANT:
            case temporalParser::FLOAT_VARIABLE:
            case temporalParser::LCURLY:
            case temporalParser::LROUND:
            case temporalParser::SIGN_CAST:
            case temporalParser::FUNCTION:
            case temporalParser::UINTEGER:
            case temporalParser::GCC_BINARY:
            case temporalParser::HEX:
            case temporalParser::VERILOG_BASED:
            case temporalParser::FILL_LITERAL:
            case temporalParser::PLUS:
            case temporalParser::MINUS:
            case temporalParser::NEG:
            case temporalParser::NOT: {
              setState(588);
              sm_constant();
              break;
            }

            case temporalParser::LSQUARED: {
              setState(589);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(592);
          match(temporalParser::RCURLY);
          break;
        }

        default:
          break;
        } 
      }
      setState(598);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ConcatenationContext ------------------------------------------------------------------

temporalParser::ConcatenationContext::ConcatenationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> temporalParser::ConcatenationContext::LCURLY() {
  return getTokens(temporalParser::LCURLY);
}

tree::TerminalNode* temporalParser::ConcatenationContext::LCURLY(size_t i) {
  return getToken(temporalParser::LCURLY, i);
}

std::vector<temporalParser::ConcatItemContext *> temporalParser::ConcatenationContext::concatItem() {
  return getRuleContexts<temporalParser::ConcatItemContext>();
}

temporalParser::ConcatItemContext* temporalParser::ConcatenationContext::concatItem(size_t i) {
  return getRuleContext<temporalParser::ConcatItemContext>(i);
}

std::vector<tree::TerminalNode *> temporalParser::ConcatenationContext::RCURLY() {
  return getTokens(temporalParser::RCURLY);
}

tree::TerminalNode* temporalParser::ConcatenationContext::RCURLY(size_t i) {
  return getToken(temporalParser::RCURLY, i);
}

tree::TerminalNode* temporalParser::ConcatenationContext::UINTEGER() {
  return getToken(temporalParser::UINTEGER, 0);
}


size_t temporalParser::ConcatenationContext::getRuleIndex() const {
  return temporalParser::RuleConcatenation;
}

void temporalParser::ConcatenationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConcatenation(this);
}

void temporalParser::ConcatenationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConcatenation(this);
}

temporalParser::ConcatenationContext* temporalParser::concatenation() {
  ConcatenationContext *_localctx = _tracker.createInstance<ConcatenationContext>(_ctx, getState());
  enterRule(_localctx, 44, temporalParser::RuleConcatenation);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(623);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(599);
      match(temporalParser::LCURLY);
      setState(600);
      concatItem();
      setState(603); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(601);
        match(temporalParser::T__2);
        setState(602);
        concatItem();
        setState(605); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == temporalParser::T__2);
      setState(607);
      match(temporalParser::RCURLY);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(609);
      match(temporalParser::LCURLY);
      setState(610);
      match(temporalParser::UINTEGER);
      setState(611);
      match(temporalParser::LCURLY);
      setState(612);
      concatItem();
      setState(617);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == temporalParser::T__2) {
        setState(613);
        match(temporalParser::T__2);
        setState(614);
        concatItem();
        setState(619);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(620);
      match(temporalParser::RCURLY);
      setState(621);
      match(temporalParser::RCURLY);
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

//----------------- ConcatItemContext ------------------------------------------------------------------

temporalParser::ConcatItemContext::ConcatItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalParser::NumericContext* temporalParser::ConcatItemContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}

temporalParser::BooleanAtomContext* temporalParser::ConcatItemContext::booleanAtom() {
  return getRuleContext<temporalParser::BooleanAtomContext>(0);
}


size_t temporalParser::ConcatItemContext::getRuleIndex() const {
  return temporalParser::RuleConcatItem;
}

void temporalParser::ConcatItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConcatItem(this);
}

void temporalParser::ConcatItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConcatItem(this);
}

temporalParser::ConcatItemContext* temporalParser::concatItem() {
  ConcatItemContext *_localctx = _tracker.createInstance<ConcatItemContext>(_ctx, getState());
  enterRule(_localctx, 46, temporalParser::RuleConcatItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(627);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::INT_VARIABLE:
      case temporalParser::LOGIC_VARIABLE:
      case temporalParser::BIT_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LCURLY:
      case temporalParser::LROUND:
      case temporalParser::SIGN_CAST:
      case temporalParser::FUNCTION:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX:
      case temporalParser::VERILOG_BASED:
      case temporalParser::FILL_LITERAL:
      case temporalParser::PLUS:
      case temporalParser::MINUS:
      case temporalParser::NEG:
      case temporalParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(625);
        numeric(0);
        break;
      }

      case temporalParser::BOOLEAN_CONSTANT:
      case temporalParser::BOOLEAN_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(626);
        booleanAtom();
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

//----------------- RangeContext ------------------------------------------------------------------

temporalParser::RangeContext::RangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::RangeContext::LSQUARED() {
  return getToken(temporalParser::LSQUARED, 0);
}

std::vector<tree::TerminalNode *> temporalParser::RangeContext::UINTEGER() {
  return getTokens(temporalParser::UINTEGER);
}

tree::TerminalNode* temporalParser::RangeContext::UINTEGER(size_t i) {
  return getToken(temporalParser::UINTEGER, i);
}

tree::TerminalNode* temporalParser::RangeContext::RSQUARED() {
  return getToken(temporalParser::RSQUARED, 0);
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
  enterRule(_localctx, 48, temporalParser::RuleRange);
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
    setState(629);
    match(temporalParser::LSQUARED);
    setState(630);
    match(temporalParser::UINTEGER);
    setState(633);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == temporalParser::COL) {
      setState(631);
      match(temporalParser::COL);
      setState(632);
      match(temporalParser::UINTEGER);
    }
    setState(635);
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
  enterRule(_localctx, 50, temporalParser::RuleSm_range);

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
    match(temporalParser::LSQUARED);
    setState(640);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::INT_VARIABLE:
      case temporalParser::LOGIC_VARIABLE:
      case temporalParser::BIT_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LCURLY:
      case temporalParser::LROUND:
      case temporalParser::SIGN_CAST:
      case temporalParser::FUNCTION:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX:
      case temporalParser::VERILOG_BASED:
      case temporalParser::FILL_LITERAL:
      case temporalParser::PLUS:
      case temporalParser::MINUS:
      case temporalParser::NEG:
      case temporalParser::NOT: {
        setState(638);
        numeric(0);
        break;
      }

      case temporalParser::DOLLAR: {
        setState(639);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(642);
    match(temporalParser::COL);
    setState(645);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::INT_VARIABLE:
      case temporalParser::LOGIC_VARIABLE:
      case temporalParser::BIT_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LCURLY:
      case temporalParser::LROUND:
      case temporalParser::SIGN_CAST:
      case temporalParser::FUNCTION:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX:
      case temporalParser::VERILOG_BASED:
      case temporalParser::FILL_LITERAL:
      case temporalParser::PLUS:
      case temporalParser::MINUS:
      case temporalParser::NEG:
      case temporalParser::NOT: {
        setState(643);
        numeric(0);
        break;
      }

      case temporalParser::DOLLAR: {
        setState(644);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(647);
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
  enterRule(_localctx, 52, temporalParser::RuleMin_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(649);
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
  enterRule(_localctx, 54, temporalParser::RuleMax_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(651);
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
  enterRule(_localctx, 56, temporalParser::RuleSm_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(653);
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
  enterRule(_localctx, 58, temporalParser::RuleIntAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(657);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(655);
        int_constant();
        break;
      }

      case temporalParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(656);
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

tree::TerminalNode* temporalParser::Int_constantContext::UINTEGER() {
  return getToken(temporalParser::UINTEGER, 0);
}

tree::TerminalNode* temporalParser::Int_constantContext::CONST_SUFFIX() {
  return getToken(temporalParser::CONST_SUFFIX, 0);
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
  enterRule(_localctx, 60, temporalParser::RuleInt_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(665);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(659);
        match(temporalParser::GCC_BINARY);
        break;
      }

      case temporalParser::UINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(660);
        match(temporalParser::UINTEGER);
        setState(662);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
        case 1: {
          setState(661);
          match(temporalParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case temporalParser::HEX: {
        enterOuterAlt(_localctx, 3);
        setState(664);
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

tree::TerminalNode* temporalParser::LogicAtomContext::BIT_VARIABLE() {
  return getToken(temporalParser::BIT_VARIABLE, 0);
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
  enterRule(_localctx, 62, temporalParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(671);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(667);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(668);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(669);
      match(temporalParser::LOGIC_VARIABLE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(670);
      match(temporalParser::BIT_VARIABLE);
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

tree::TerminalNode* temporalParser::Logic_constantContext::VERILOG_BASED() {
  return getToken(temporalParser::VERILOG_BASED, 0);
}

tree::TerminalNode* temporalParser::Logic_constantContext::UINTEGER() {
  return getToken(temporalParser::UINTEGER, 0);
}

tree::TerminalNode* temporalParser::Logic_constantContext::FILL_LITERAL() {
  return getToken(temporalParser::FILL_LITERAL, 0);
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
  enterRule(_localctx, 64, temporalParser::RuleLogic_constant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(678);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::UINTEGER:
      case temporalParser::VERILOG_BASED: {
        enterOuterAlt(_localctx, 1);
        setState(674);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == temporalParser::UINTEGER) {
          setState(673);
          match(temporalParser::UINTEGER);
        }
        setState(676);
        match(temporalParser::VERILOG_BASED);
        break;
      }

      case temporalParser::FILL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(677);
        match(temporalParser::FILL_LITERAL);
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
  enterRule(_localctx, 66, temporalParser::RuleFloatAtom);
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
    setState(680);
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
  size_t startState = 68;
  enterRecursionRule(_localctx, 68, temporalParser::RuleString, precedence);

    

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
    setState(688);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::STRING_CONSTANT:
      case temporalParser::STRING_VARIABLE: {
        setState(683);
        stringAtom();
        break;
      }

      case temporalParser::LROUND: {
        setState(684);
        match(temporalParser::LROUND);
        setState(685);
        string(0);
        setState(686);
        match(temporalParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(705);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(703);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(690);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(691);
          match(temporalParser::PLUS);
          setState(692);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(693);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(694);
          match(temporalParser::SUBSTR);
          setState(695);
          match(temporalParser::LROUND);
          setState(700);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx)) {
          case 1: {
            setState(696);
            match(temporalParser::UINTEGER);
            setState(697);
            match(temporalParser::T__2);
            setState(698);
            match(temporalParser::UINTEGER);
            break;
          }

          case 2: {
            setState(699);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(702);
          match(temporalParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(707);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx);
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
  enterRule(_localctx, 70, temporalParser::RuleStringAtom);
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
    setState(708);
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
  enterRule(_localctx, 72, temporalParser::RuleNonTemporalFunction);
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
    setState(710);
    match(temporalParser::FUNCTION);
    setState(711);
    match(temporalParser::LROUND);
    setState(712);
    pfunc_arg();
    setState(717);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == temporalParser::T__2) {
      setState(713);
      match(temporalParser::T__2);
      setState(714);
      pfunc_arg();
      setState(719);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(720);
    match(temporalParser::RROUND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SignCastContext ------------------------------------------------------------------

temporalParser::SignCastContext::SignCastContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalParser::SignCastContext::SIGN_CAST() {
  return getToken(temporalParser::SIGN_CAST, 0);
}

tree::TerminalNode* temporalParser::SignCastContext::LROUND() {
  return getToken(temporalParser::LROUND, 0);
}

temporalParser::NumericContext* temporalParser::SignCastContext::numeric() {
  return getRuleContext<temporalParser::NumericContext>(0);
}

tree::TerminalNode* temporalParser::SignCastContext::RROUND() {
  return getToken(temporalParser::RROUND, 0);
}


size_t temporalParser::SignCastContext::getRuleIndex() const {
  return temporalParser::RuleSignCast;
}

void temporalParser::SignCastContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSignCast(this);
}

void temporalParser::SignCastContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSignCast(this);
}

temporalParser::SignCastContext* temporalParser::signCast() {
  SignCastContext *_localctx = _tracker.createInstance<SignCastContext>(_ctx, getState());
  enterRule(_localctx, 74, temporalParser::RuleSignCast);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(722);
    match(temporalParser::SIGN_CAST);
    setState(723);
    match(temporalParser::LROUND);
    setState(724);
    numeric(0);
    setState(725);
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
  enterRule(_localctx, 76, temporalParser::RulePfunc_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(729);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(727);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(728);
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
  enterRule(_localctx, 78, temporalParser::RuleRelop);
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
    setState(731);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -1152921504606846976) != 0))) {
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
  enterRule(_localctx, 80, temporalParser::RuleCls_op);
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
    setState(733);
    _la = _input->LA(1);
    if (!(((((_la - 60) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 60)) & 8388639) != 0))) {
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
    case 19: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 21: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);
    case 34: return stringSempred(antlrcpp::downCast<StringContext *>(context), predicateIndex);

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
    case 8: return canUseSharedOperator(safeTokenText(_input->LT(-1)),safeTokenText(_input->LT(2)));
    case 9: return canTakeThisNot(safeTokenText(_input->LT(1)),safeTokenText(_input->LT(2)));
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
    case 13: return precpred(_ctx, 3);
    case 14: return precpred(_ctx, 2);
    case 15: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool temporalParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 16: return precpred(_ctx, 16);
    case 17: return precpred(_ctx, 15);
    case 18: return precpred(_ctx, 14);
    case 19: return precpred(_ctx, 13);
    case 20: return precpred(_ctx, 11);
    case 21: return precpred(_ctx, 10);
    case 22: return precpred(_ctx, 9);
    case 23: return precpred(_ctx, 8);
    case 24: return precpred(_ctx, 20);
    case 25: return precpred(_ctx, 12);

  default:
    break;
  }
  return true;
}

bool temporalParser::stringSempred(StringContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 26: return precpred(_ctx, 4);
    case 27: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void temporalParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  temporalParserInitialize();
#else
  ::antlr4::internal::call_once(temporalParserOnceFlag, temporalParserInitialize);
#endif
}
