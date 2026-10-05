
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
      "stringAtom", "nonTemporalFunction", "pfunc_arg", "relop", "cls_op"
    },
    std::vector<std::string>{
      "", "'assert property'", "'@(posedge'", "','", "'..##'", "'..#'", 
      "'..['", "']@'", "", "'..&&..'", "", "", "", "", "'R'", "'..'", "'=>'", 
      "'->'", "'<->'", "", "", "'='", "'##'", "';'", "'first_match'", "'not'", 
      "'and'", "'intersect'", "'or'", "", "", "", "", "", "", "", "'.substr'", 
      "", "", "'{'", "'}'", "'['", "']'", "'('", "')'", "'inside'", "", 
      "", "", "", "", "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", 
      "'>='", "'<'", "'<='", "'=='", "'!='", "'==='", "'!=='", "'\\u003F'", 
      "'&'", "'|'", "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'", 
      "':'", "'::'", "'$'", "'><'"
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
      "VERILOG_BASED", "FILL_LITERAL", "SINGLE_QUOTE", "PLUS", "MINUS", 
      "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "CASE_EQ", "CASE_NEQ", 
      "QUESTION", "BAND", "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", 
      "OR", "NOT", "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,82,731,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,1,0,1,0,1,0,1,0,1,0,1,0,1,
  	0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,94,8,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,115,8,1,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,3,2,126,8,2,1,2,1,2,3,2,130,8,2,1,2,1,2,1,2,1,2,
  	3,2,136,8,2,1,2,1,2,3,2,140,8,2,1,2,1,2,1,2,3,2,145,8,2,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,165,8,3,
  	1,3,3,3,168,8,3,1,3,3,3,171,8,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,179,8,3,1,
  	3,3,3,182,8,3,1,3,3,3,185,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,194,8,3,
  	1,3,1,3,1,3,1,3,1,3,3,3,201,8,3,1,3,1,3,3,3,205,8,3,1,3,3,3,208,8,3,1,
  	3,3,3,211,8,3,1,3,3,3,214,8,3,1,3,3,3,217,8,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	3,3,225,8,3,1,3,1,3,1,3,1,3,1,3,3,3,232,8,3,1,3,3,3,235,8,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,249,8,3,1,3,3,3,252,8,3,1,3,
  	3,3,255,8,3,1,3,3,3,258,8,3,1,3,3,3,261,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,3,3,274,8,3,1,3,3,3,277,8,3,1,3,3,3,280,8,3,1,3,1,3,
  	1,3,1,3,1,3,5,3,287,8,3,10,3,12,3,290,9,3,1,4,1,4,1,4,1,4,1,4,1,4,3,4,
  	298,8,4,1,4,1,4,1,4,1,4,1,4,3,4,305,8,4,1,4,3,4,308,8,4,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,3,5,317,8,5,1,5,1,5,3,5,321,8,5,1,5,1,5,1,5,1,5,1,5,3,5,
  	328,8,5,1,5,3,5,331,8,5,1,5,3,5,334,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,3,5,344,8,5,1,5,3,5,347,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,
  	358,8,5,10,5,12,5,361,9,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,5,6,372,
  	8,6,10,6,12,6,375,9,6,1,6,1,6,3,6,379,8,6,1,7,1,7,1,7,1,7,1,7,3,7,386,
  	8,7,1,7,3,7,389,8,7,1,8,1,8,1,8,5,8,394,8,8,10,8,12,8,397,9,8,1,9,1,9,
  	1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	12,1,12,3,12,417,8,12,1,12,1,12,1,13,1,13,3,13,423,8,13,1,13,1,13,1,14,
  	1,14,3,14,429,8,14,1,14,1,14,1,15,1,15,3,15,435,8,15,1,15,1,15,1,16,1,
  	16,1,16,1,17,1,17,1,17,1,17,3,17,446,8,17,1,17,1,17,1,17,3,17,451,8,17,
  	1,18,1,18,1,18,1,18,3,18,457,8,18,1,18,1,18,1,18,3,18,462,8,18,1,19,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,473,8,19,1,19,1,19,5,19,477,
  	8,19,10,19,12,19,480,9,19,1,19,1,19,3,19,484,8,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,530,
  	8,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,5,19,
  	544,8,19,10,19,12,19,547,9,19,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,567,8,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,5,21,592,8,21,10,21,12,21,595,
  	9,21,1,22,1,22,1,22,1,22,4,22,601,8,22,11,22,12,22,602,1,22,1,22,1,22,
  	1,22,1,22,1,22,1,22,1,22,5,22,613,8,22,10,22,12,22,616,9,22,1,22,1,22,
  	1,22,3,22,621,8,22,1,23,1,23,3,23,625,8,23,1,24,1,24,1,24,1,24,3,24,631,
  	8,24,1,24,1,24,1,25,1,25,1,25,3,25,638,8,25,1,25,1,25,1,25,3,25,643,8,
  	25,1,25,1,25,1,26,1,26,1,27,1,27,1,28,1,28,1,29,1,29,3,29,655,8,29,1,
  	30,1,30,1,30,3,30,660,8,30,1,30,1,30,3,30,664,8,30,1,30,3,30,667,8,30,
  	1,31,1,31,1,31,3,31,672,8,31,1,32,3,32,675,8,32,1,32,1,32,3,32,679,8,
  	32,1,33,1,33,1,34,1,34,1,34,1,34,1,34,1,34,3,34,689,8,34,1,34,1,34,1,
  	34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,3,34,701,8,34,1,34,5,34,704,8,34,
  	10,34,12,34,707,9,34,1,35,1,35,1,36,1,36,1,36,1,36,1,36,5,36,716,8,36,
  	10,36,12,36,719,9,36,1,36,1,36,1,37,1,37,3,37,725,8,37,1,38,1,38,1,39,
  	1,39,1,39,0,5,6,10,38,42,68,40,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,
  	76,78,0,17,2,0,15,15,77,77,2,0,48,48,79,79,2,0,26,27,74,74,3,0,28,28,
  	69,69,75,75,2,0,25,25,76,76,1,0,13,14,2,0,26,26,74,74,2,0,17,17,21,21,
  	2,0,23,23,77,77,1,0,29,30,1,0,57,58,1,0,55,56,1,0,47,48,1,0,34,35,1,0,
  	37,38,1,0,59,62,2,0,59,63,80,80,837,0,93,1,0,0,0,2,114,1,0,0,0,4,144,
  	1,0,0,0,6,234,1,0,0,0,8,307,1,0,0,0,10,346,1,0,0,0,12,378,1,0,0,0,14,
  	388,1,0,0,0,16,390,1,0,0,0,18,398,1,0,0,0,20,402,1,0,0,0,22,407,1,0,0,
  	0,24,416,1,0,0,0,26,422,1,0,0,0,28,428,1,0,0,0,30,434,1,0,0,0,32,438,
  	1,0,0,0,34,441,1,0,0,0,36,452,1,0,0,0,38,529,1,0,0,0,40,548,1,0,0,0,42,
  	566,1,0,0,0,44,620,1,0,0,0,46,624,1,0,0,0,48,626,1,0,0,0,50,634,1,0,0,
  	0,52,646,1,0,0,0,54,648,1,0,0,0,56,650,1,0,0,0,58,654,1,0,0,0,60,666,
  	1,0,0,0,62,671,1,0,0,0,64,678,1,0,0,0,66,680,1,0,0,0,68,688,1,0,0,0,70,
  	708,1,0,0,0,72,710,1,0,0,0,74,724,1,0,0,0,76,726,1,0,0,0,78,728,1,0,0,
  	0,80,81,5,11,0,0,81,82,5,43,0,0,82,83,3,4,2,0,83,84,5,44,0,0,84,85,5,
  	0,0,1,85,94,1,0,0,0,86,87,5,11,0,0,87,88,3,4,2,0,88,89,5,0,0,1,89,94,
  	1,0,0,0,90,91,3,2,1,0,91,92,5,0,0,1,92,94,1,0,0,0,93,80,1,0,0,0,93,86,
  	1,0,0,0,93,90,1,0,0,0,94,1,1,0,0,0,95,96,5,1,0,0,96,97,5,43,0,0,97,98,
  	3,2,1,0,98,99,5,44,0,0,99,115,1,0,0,0,100,101,5,43,0,0,101,102,3,2,1,
  	0,102,103,5,44,0,0,103,115,1,0,0,0,104,105,5,2,0,0,105,106,3,38,19,0,
  	106,107,5,44,0,0,107,108,3,2,1,0,108,115,1,0,0,0,109,110,5,43,0,0,110,
  	111,3,4,2,0,111,112,5,44,0,0,112,115,1,0,0,0,113,115,3,4,2,0,114,95,1,
  	0,0,0,114,100,1,0,0,0,114,104,1,0,0,0,114,109,1,0,0,0,114,113,1,0,0,0,
  	115,3,1,0,0,0,116,117,3,10,5,0,117,118,5,16,0,0,118,119,3,10,5,0,119,
  	145,1,0,0,0,120,121,3,10,5,0,121,122,5,17,0,0,122,123,3,10,5,0,123,145,
  	1,0,0,0,124,126,5,39,0,0,125,124,1,0,0,0,125,126,1,0,0,0,126,127,1,0,
  	0,0,127,129,3,6,3,0,128,130,5,40,0,0,129,128,1,0,0,0,129,130,1,0,0,0,
  	130,131,1,0,0,0,131,132,5,19,0,0,132,133,3,10,5,0,133,145,1,0,0,0,134,
  	136,5,39,0,0,135,134,1,0,0,0,135,136,1,0,0,0,136,137,1,0,0,0,137,139,
  	3,6,3,0,138,140,5,40,0,0,139,138,1,0,0,0,139,140,1,0,0,0,140,141,1,0,
  	0,0,141,142,5,20,0,0,142,143,3,10,5,0,143,145,1,0,0,0,144,116,1,0,0,0,
  	144,120,1,0,0,0,144,125,1,0,0,0,144,135,1,0,0,0,145,5,1,0,0,0,146,147,
  	6,3,-1,0,147,148,5,24,0,0,148,149,5,43,0,0,149,150,3,6,3,0,150,151,5,
  	44,0,0,151,235,1,0,0,0,152,153,5,43,0,0,153,154,3,6,3,0,154,155,5,44,
  	0,0,155,235,1,0,0,0,156,157,5,39,0,0,157,158,3,6,3,0,158,159,5,40,0,0,
  	159,235,1,0,0,0,160,161,3,8,4,0,161,162,5,41,0,0,162,164,5,21,0,0,163,
  	165,5,48,0,0,164,163,1,0,0,0,164,165,1,0,0,0,165,167,1,0,0,0,166,168,
  	7,0,0,0,167,166,1,0,0,0,167,168,1,0,0,0,168,170,1,0,0,0,169,171,7,1,0,
  	0,170,169,1,0,0,0,170,171,1,0,0,0,171,172,1,0,0,0,172,173,5,42,0,0,173,
  	235,1,0,0,0,174,175,3,8,4,0,175,176,5,41,0,0,176,178,5,17,0,0,177,179,
  	5,48,0,0,178,177,1,0,0,0,178,179,1,0,0,0,179,181,1,0,0,0,180,182,7,0,
  	0,0,181,180,1,0,0,0,181,182,1,0,0,0,182,184,1,0,0,0,183,185,7,1,0,0,184,
  	183,1,0,0,0,184,185,1,0,0,0,185,186,1,0,0,0,186,187,5,42,0,0,187,235,
  	1,0,0,0,188,193,3,22,11,0,189,190,5,43,0,0,190,191,3,16,8,0,191,192,5,
  	44,0,0,192,194,1,0,0,0,193,189,1,0,0,0,193,194,1,0,0,0,194,235,1,0,0,
  	0,195,200,5,9,0,0,196,197,5,43,0,0,197,198,3,16,8,0,198,199,5,44,0,0,
  	199,201,1,0,0,0,200,196,1,0,0,0,200,201,1,0,0,0,201,235,1,0,0,0,202,204,
  	5,22,0,0,203,205,5,41,0,0,204,203,1,0,0,0,204,205,1,0,0,0,205,207,1,0,
  	0,0,206,208,5,48,0,0,207,206,1,0,0,0,207,208,1,0,0,0,208,210,1,0,0,0,
  	209,211,7,0,0,0,210,209,1,0,0,0,210,211,1,0,0,0,211,213,1,0,0,0,212,214,
  	7,1,0,0,213,212,1,0,0,0,213,214,1,0,0,0,214,216,1,0,0,0,215,217,5,42,
  	0,0,216,215,1,0,0,0,216,217,1,0,0,0,217,218,1,0,0,0,218,235,3,6,3,6,219,
  	224,3,18,9,0,220,221,5,43,0,0,221,222,3,16,8,0,222,223,5,44,0,0,223,225,
  	1,0,0,0,224,220,1,0,0,0,224,225,1,0,0,0,225,235,1,0,0,0,226,231,3,20,
  	10,0,227,228,5,43,0,0,228,229,3,16,8,0,229,230,5,44,0,0,230,232,1,0,0,
  	0,231,227,1,0,0,0,231,232,1,0,0,0,232,235,1,0,0,0,233,235,3,8,4,0,234,
  	146,1,0,0,0,234,152,1,0,0,0,234,156,1,0,0,0,234,160,1,0,0,0,234,174,1,
  	0,0,0,234,188,1,0,0,0,234,195,1,0,0,0,234,202,1,0,0,0,234,219,1,0,0,0,
  	234,226,1,0,0,0,234,233,1,0,0,0,235,288,1,0,0,0,236,237,10,11,0,0,237,
  	238,5,68,0,0,238,287,3,6,3,12,239,240,10,10,0,0,240,241,7,2,0,0,241,287,
  	3,6,3,11,242,243,10,8,0,0,243,244,7,3,0,0,244,287,3,6,3,9,245,246,10,
  	7,0,0,246,248,5,22,0,0,247,249,5,41,0,0,248,247,1,0,0,0,248,249,1,0,0,
  	0,249,251,1,0,0,0,250,252,5,48,0,0,251,250,1,0,0,0,251,252,1,0,0,0,252,
  	254,1,0,0,0,253,255,7,0,0,0,254,253,1,0,0,0,254,255,1,0,0,0,255,257,1,
  	0,0,0,256,258,7,1,0,0,257,256,1,0,0,0,257,258,1,0,0,0,258,260,1,0,0,0,
  	259,261,5,42,0,0,260,259,1,0,0,0,260,261,1,0,0,0,261,262,1,0,0,0,262,
  	287,3,6,3,8,263,264,10,3,0,0,264,265,5,77,0,0,265,287,3,6,3,4,266,267,
  	10,2,0,0,267,268,5,23,0,0,268,287,3,6,3,3,269,270,10,16,0,0,270,271,5,
  	41,0,0,271,273,5,57,0,0,272,274,5,48,0,0,273,272,1,0,0,0,273,274,1,0,
  	0,0,274,276,1,0,0,0,275,277,7,0,0,0,276,275,1,0,0,0,276,277,1,0,0,0,277,
  	279,1,0,0,0,278,280,7,1,0,0,279,278,1,0,0,0,279,280,1,0,0,0,280,281,1,
  	0,0,0,281,287,5,42,0,0,282,283,10,15,0,0,283,284,5,41,0,0,284,285,5,55,
  	0,0,285,287,5,42,0,0,286,236,1,0,0,0,286,239,1,0,0,0,286,242,1,0,0,0,
  	286,245,1,0,0,0,286,263,1,0,0,0,286,266,1,0,0,0,286,269,1,0,0,0,286,282,
  	1,0,0,0,287,290,1,0,0,0,288,286,1,0,0,0,288,289,1,0,0,0,289,7,1,0,0,0,
  	290,288,1,0,0,0,291,292,5,43,0,0,292,293,3,8,4,0,293,294,5,44,0,0,294,
  	308,1,0,0,0,295,308,3,38,19,0,296,298,5,76,0,0,297,296,1,0,0,0,297,298,
  	1,0,0,0,298,299,1,0,0,0,299,304,5,8,0,0,300,301,5,43,0,0,301,302,3,16,
  	8,0,302,303,5,44,0,0,303,305,1,0,0,0,304,300,1,0,0,0,304,305,1,0,0,0,
  	305,308,1,0,0,0,306,308,3,12,6,0,307,291,1,0,0,0,307,295,1,0,0,0,307,
  	297,1,0,0,0,307,306,1,0,0,0,308,9,1,0,0,0,309,310,6,5,-1,0,310,311,5,
  	43,0,0,311,312,3,10,5,0,312,313,5,44,0,0,313,347,1,0,0,0,314,316,4,5,
  	8,0,315,317,5,39,0,0,316,315,1,0,0,0,316,317,1,0,0,0,317,318,1,0,0,0,
  	318,320,3,6,3,0,319,321,5,40,0,0,320,319,1,0,0,0,320,321,1,0,0,0,321,
  	347,1,0,0,0,322,323,4,5,9,0,323,324,7,4,0,0,324,347,3,10,5,8,325,327,
  	5,12,0,0,326,328,5,41,0,0,327,326,1,0,0,0,327,328,1,0,0,0,328,330,1,0,
  	0,0,329,331,5,48,0,0,330,329,1,0,0,0,330,331,1,0,0,0,331,333,1,0,0,0,
  	332,334,5,42,0,0,333,332,1,0,0,0,333,334,1,0,0,0,334,335,1,0,0,0,335,
  	347,3,10,5,7,336,337,5,10,0,0,337,347,3,10,5,6,338,343,5,9,0,0,339,340,
  	5,43,0,0,340,341,3,16,8,0,341,342,5,44,0,0,342,344,1,0,0,0,343,339,1,
  	0,0,0,343,344,1,0,0,0,344,347,1,0,0,0,345,347,3,8,4,0,346,309,1,0,0,0,
  	346,314,1,0,0,0,346,322,1,0,0,0,346,325,1,0,0,0,346,336,1,0,0,0,346,338,
  	1,0,0,0,346,345,1,0,0,0,347,359,1,0,0,0,348,349,10,5,0,0,349,350,7,5,
  	0,0,350,358,3,10,5,5,351,352,10,4,0,0,352,353,7,6,0,0,353,358,3,10,5,
  	5,354,355,10,3,0,0,355,356,7,3,0,0,356,358,3,10,5,4,357,348,1,0,0,0,357,
  	351,1,0,0,0,357,354,1,0,0,0,358,361,1,0,0,0,359,357,1,0,0,0,359,360,1,
  	0,0,0,360,11,1,0,0,0,361,359,1,0,0,0,362,363,5,43,0,0,363,364,3,12,6,
  	0,364,365,5,44,0,0,365,379,1,0,0,0,366,367,5,46,0,0,367,368,5,43,0,0,
  	368,373,3,14,7,0,369,370,5,3,0,0,370,372,3,14,7,0,371,369,1,0,0,0,372,
  	375,1,0,0,0,373,371,1,0,0,0,373,374,1,0,0,0,374,376,1,0,0,0,375,373,1,
  	0,0,0,376,377,5,44,0,0,377,379,1,0,0,0,378,362,1,0,0,0,378,366,1,0,0,
  	0,379,13,1,0,0,0,380,385,5,8,0,0,381,382,5,43,0,0,382,383,3,16,8,0,383,
  	384,5,44,0,0,384,386,1,0,0,0,385,381,1,0,0,0,385,386,1,0,0,0,386,389,
  	1,0,0,0,387,389,5,48,0,0,388,380,1,0,0,0,388,387,1,0,0,0,389,15,1,0,0,
  	0,390,395,5,48,0,0,391,392,5,3,0,0,392,394,5,48,0,0,393,391,1,0,0,0,394,
  	397,1,0,0,0,395,393,1,0,0,0,395,396,1,0,0,0,396,17,1,0,0,0,397,395,1,
  	0,0,0,398,399,5,4,0,0,399,400,5,48,0,0,400,401,5,15,0,0,401,19,1,0,0,
  	0,402,403,5,5,0,0,403,404,5,48,0,0,404,405,5,68,0,0,405,406,5,15,0,0,
  	406,21,1,0,0,0,407,408,5,6,0,0,408,409,7,7,0,0,409,410,5,48,0,0,410,411,
  	5,7,0,0,411,412,7,8,0,0,412,413,5,15,0,0,413,23,1,0,0,0,414,417,3,38,
  	19,0,415,417,3,34,17,0,416,414,1,0,0,0,416,415,1,0,0,0,417,418,1,0,0,
  	0,418,419,5,0,0,1,419,25,1,0,0,0,420,423,3,42,21,0,421,423,3,36,18,0,
  	422,420,1,0,0,0,422,421,1,0,0,0,423,424,1,0,0,0,424,425,5,0,0,1,425,27,
  	1,0,0,0,426,429,3,42,21,0,427,429,3,36,18,0,428,426,1,0,0,0,428,427,1,
  	0,0,0,429,430,1,0,0,0,430,431,5,0,0,1,431,29,1,0,0,0,432,435,3,42,21,
  	0,433,435,3,36,18,0,434,432,1,0,0,0,434,433,1,0,0,0,435,436,1,0,0,0,436,
  	437,5,0,0,1,437,31,1,0,0,0,438,439,3,68,34,0,439,440,5,0,0,1,440,33,1,
  	0,0,0,441,442,3,38,19,0,442,445,5,67,0,0,443,446,3,38,19,0,444,446,3,
  	34,17,0,445,443,1,0,0,0,445,444,1,0,0,0,446,447,1,0,0,0,447,450,5,77,
  	0,0,448,451,3,38,19,0,449,451,3,34,17,0,450,448,1,0,0,0,450,449,1,0,0,
  	0,451,35,1,0,0,0,452,453,3,38,19,0,453,456,5,67,0,0,454,457,3,42,21,0,
  	455,457,3,36,18,0,456,454,1,0,0,0,456,455,1,0,0,0,457,458,1,0,0,0,458,
  	461,5,77,0,0,459,462,3,42,21,0,460,462,3,36,18,0,461,459,1,0,0,0,461,
  	460,1,0,0,0,462,37,1,0,0,0,463,464,6,19,-1,0,464,465,5,76,0,0,465,530,
  	3,38,19,19,466,530,3,72,36,0,467,468,3,42,21,0,468,469,5,45,0,0,469,478,
  	5,39,0,0,470,473,3,56,28,0,471,473,3,50,25,0,472,470,1,0,0,0,472,471,
  	1,0,0,0,473,474,1,0,0,0,474,475,5,3,0,0,475,477,1,0,0,0,476,472,1,0,0,
  	0,477,480,1,0,0,0,478,476,1,0,0,0,478,479,1,0,0,0,479,483,1,0,0,0,480,
  	478,1,0,0,0,481,484,3,56,28,0,482,484,3,50,25,0,483,481,1,0,0,0,483,482,
  	1,0,0,0,484,485,1,0,0,0,485,486,5,40,0,0,486,530,1,0,0,0,487,488,3,42,
  	21,0,488,489,3,76,38,0,489,490,3,42,21,0,490,530,1,0,0,0,491,492,3,42,
  	21,0,492,493,5,63,0,0,493,494,3,42,21,0,494,530,1,0,0,0,495,496,3,42,
  	21,0,496,497,5,64,0,0,497,498,3,42,21,0,498,530,1,0,0,0,499,500,3,42,
  	21,0,500,501,5,65,0,0,501,502,3,42,21,0,502,530,1,0,0,0,503,504,3,42,
  	21,0,504,505,5,66,0,0,505,506,3,42,21,0,506,530,1,0,0,0,507,508,3,68,
  	34,0,508,509,3,76,38,0,509,510,3,68,34,0,510,530,1,0,0,0,511,512,3,68,
  	34,0,512,513,5,63,0,0,513,514,3,68,34,0,514,530,1,0,0,0,515,516,3,68,
  	34,0,516,517,5,64,0,0,517,518,3,68,34,0,518,530,1,0,0,0,519,530,3,40,
  	20,0,520,530,3,42,21,0,521,522,5,43,0,0,522,523,3,38,19,0,523,524,5,44,
  	0,0,524,530,1,0,0,0,525,526,5,43,0,0,526,527,3,34,17,0,527,528,5,44,0,
  	0,528,530,1,0,0,0,529,463,1,0,0,0,529,466,1,0,0,0,529,467,1,0,0,0,529,
  	487,1,0,0,0,529,491,1,0,0,0,529,495,1,0,0,0,529,499,1,0,0,0,529,503,1,
  	0,0,0,529,507,1,0,0,0,529,511,1,0,0,0,529,515,1,0,0,0,529,519,1,0,0,0,
  	529,520,1,0,0,0,529,521,1,0,0,0,529,525,1,0,0,0,530,545,1,0,0,0,531,532,
  	10,8,0,0,532,533,5,63,0,0,533,544,3,38,19,9,534,535,10,7,0,0,535,536,
  	5,64,0,0,536,544,3,38,19,8,537,538,10,6,0,0,538,539,5,74,0,0,539,544,
  	3,38,19,7,540,541,10,5,0,0,541,542,5,75,0,0,542,544,3,38,19,6,543,531,
  	1,0,0,0,543,534,1,0,0,0,543,537,1,0,0,0,543,540,1,0,0,0,544,547,1,0,0,
  	0,545,543,1,0,0,0,545,546,1,0,0,0,546,39,1,0,0,0,547,545,1,0,0,0,548,
  	549,7,9,0,0,549,41,1,0,0,0,550,551,6,21,-1,0,551,552,5,71,0,0,552,567,
  	3,42,21,16,553,567,3,72,36,0,554,567,3,58,29,0,555,567,3,62,31,0,556,
  	567,3,66,33,0,557,567,3,44,22,0,558,559,5,43,0,0,559,560,3,42,21,0,560,
  	561,5,44,0,0,561,567,1,0,0,0,562,563,5,43,0,0,563,564,3,36,18,0,564,565,
  	5,44,0,0,565,567,1,0,0,0,566,550,1,0,0,0,566,553,1,0,0,0,566,554,1,0,
  	0,0,566,555,1,0,0,0,566,556,1,0,0,0,566,557,1,0,0,0,566,558,1,0,0,0,566,
  	562,1,0,0,0,567,593,1,0,0,0,568,569,10,13,0,0,569,570,7,10,0,0,570,592,
  	3,42,21,14,571,572,10,12,0,0,572,573,7,11,0,0,573,592,3,42,21,13,574,
  	575,10,11,0,0,575,576,5,72,0,0,576,592,3,42,21,12,577,578,10,10,0,0,578,
  	579,5,73,0,0,579,592,3,42,21,11,580,581,10,9,0,0,581,582,5,68,0,0,582,
  	592,3,42,21,10,583,584,10,8,0,0,584,585,5,70,0,0,585,592,3,42,21,9,586,
  	587,10,7,0,0,587,588,5,69,0,0,588,592,3,42,21,8,589,590,10,14,0,0,590,
  	592,3,48,24,0,591,568,1,0,0,0,591,571,1,0,0,0,591,574,1,0,0,0,591,577,
  	1,0,0,0,591,580,1,0,0,0,591,583,1,0,0,0,591,586,1,0,0,0,591,589,1,0,0,
  	0,592,595,1,0,0,0,593,591,1,0,0,0,593,594,1,0,0,0,594,43,1,0,0,0,595,
  	593,1,0,0,0,596,597,5,39,0,0,597,600,3,46,23,0,598,599,5,3,0,0,599,601,
  	3,46,23,0,600,598,1,0,0,0,601,602,1,0,0,0,602,600,1,0,0,0,602,603,1,0,
  	0,0,603,604,1,0,0,0,604,605,5,40,0,0,605,621,1,0,0,0,606,607,5,39,0,0,
  	607,608,5,48,0,0,608,609,5,39,0,0,609,614,3,46,23,0,610,611,5,3,0,0,611,
  	613,3,46,23,0,612,610,1,0,0,0,613,616,1,0,0,0,614,612,1,0,0,0,614,615,
  	1,0,0,0,615,617,1,0,0,0,616,614,1,0,0,0,617,618,5,40,0,0,618,619,5,40,
  	0,0,619,621,1,0,0,0,620,596,1,0,0,0,620,606,1,0,0,0,621,45,1,0,0,0,622,
  	625,3,42,21,0,623,625,3,40,20,0,624,622,1,0,0,0,624,623,1,0,0,0,625,47,
  	1,0,0,0,626,627,5,41,0,0,627,630,7,12,0,0,628,629,5,77,0,0,629,631,7,
  	12,0,0,630,628,1,0,0,0,630,631,1,0,0,0,631,632,1,0,0,0,632,633,5,42,0,
  	0,633,49,1,0,0,0,634,637,5,41,0,0,635,638,3,42,21,0,636,638,3,52,26,0,
  	637,635,1,0,0,0,637,636,1,0,0,0,638,639,1,0,0,0,639,642,5,77,0,0,640,
  	643,3,42,21,0,641,643,3,54,27,0,642,640,1,0,0,0,642,641,1,0,0,0,643,644,
  	1,0,0,0,644,645,5,42,0,0,645,51,1,0,0,0,646,647,5,79,0,0,647,53,1,0,0,
  	0,648,649,5,79,0,0,649,55,1,0,0,0,650,651,3,42,21,0,651,57,1,0,0,0,652,
  	655,3,60,30,0,653,655,5,31,0,0,654,652,1,0,0,0,654,653,1,0,0,0,655,59,
  	1,0,0,0,656,667,5,50,0,0,657,659,5,47,0,0,658,660,5,32,0,0,659,658,1,
  	0,0,0,659,660,1,0,0,0,660,667,1,0,0,0,661,663,5,48,0,0,662,664,5,32,0,
  	0,663,662,1,0,0,0,663,664,1,0,0,0,664,667,1,0,0,0,665,667,5,51,0,0,666,
  	656,1,0,0,0,666,657,1,0,0,0,666,661,1,0,0,0,666,665,1,0,0,0,667,61,1,
  	0,0,0,668,672,3,64,32,0,669,672,3,60,30,0,670,672,5,33,0,0,671,668,1,
  	0,0,0,671,669,1,0,0,0,671,670,1,0,0,0,672,63,1,0,0,0,673,675,5,48,0,0,
  	674,673,1,0,0,0,674,675,1,0,0,0,675,676,1,0,0,0,676,679,5,52,0,0,677,
  	679,5,53,0,0,678,674,1,0,0,0,678,677,1,0,0,0,679,65,1,0,0,0,680,681,7,
  	13,0,0,681,67,1,0,0,0,682,683,6,34,-1,0,683,689,3,70,35,0,684,685,5,43,
  	0,0,685,686,3,68,34,0,686,687,5,44,0,0,687,689,1,0,0,0,688,682,1,0,0,
  	0,688,684,1,0,0,0,689,705,1,0,0,0,690,691,10,4,0,0,691,692,5,55,0,0,692,
  	704,3,68,34,5,693,694,10,3,0,0,694,695,5,36,0,0,695,700,5,43,0,0,696,
  	697,5,48,0,0,697,698,5,3,0,0,698,701,5,48,0,0,699,701,5,48,0,0,700,696,
  	1,0,0,0,700,699,1,0,0,0,700,701,1,0,0,0,701,702,1,0,0,0,702,704,5,44,
  	0,0,703,690,1,0,0,0,703,693,1,0,0,0,704,707,1,0,0,0,705,703,1,0,0,0,705,
  	706,1,0,0,0,706,69,1,0,0,0,707,705,1,0,0,0,708,709,7,14,0,0,709,71,1,
  	0,0,0,710,711,5,46,0,0,711,712,5,43,0,0,712,717,3,74,37,0,713,714,5,3,
  	0,0,714,716,3,74,37,0,715,713,1,0,0,0,716,719,1,0,0,0,717,715,1,0,0,0,
  	717,718,1,0,0,0,718,720,1,0,0,0,719,717,1,0,0,0,720,721,5,44,0,0,721,
  	73,1,0,0,0,722,725,3,42,21,0,723,725,3,38,19,0,724,722,1,0,0,0,724,723,
  	1,0,0,0,725,75,1,0,0,0,726,727,7,15,0,0,727,77,1,0,0,0,728,729,7,16,0,
  	0,729,79,1,0,0,0,87,93,114,125,129,135,139,144,164,167,170,178,181,184,
  	193,200,204,207,210,213,216,224,231,234,248,251,254,257,260,273,276,279,
  	286,288,297,304,307,316,320,327,330,333,343,346,357,359,373,378,385,388,
  	395,416,422,428,434,445,450,456,461,472,478,483,529,543,545,566,591,593,
  	602,614,620,624,630,637,642,654,659,663,666,671,674,678,688,700,703,705,
  	717,724
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
    setState(93);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(80);
      match(temporalParser::ALWAYS);
      setState(81);
      match(temporalParser::LROUND);
      setState(82);
      implication();
      setState(83);
      match(temporalParser::RROUND);
      setState(84);
      match(temporalParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(86);
      match(temporalParser::ALWAYS);
      setState(87);
      implication();
      setState(88);
      match(temporalParser::EOF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(90);
      sva_assert();
      setState(91);
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
    setState(114);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(95);
      match(temporalParser::T__0);
      setState(96);
      match(temporalParser::LROUND);
      setState(97);
      sva_assert();
      setState(98);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(100);
      match(temporalParser::LROUND);
      setState(101);
      sva_assert();
      setState(102);
      match(temporalParser::RROUND);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(104);
      match(temporalParser::T__1);
      setState(105);
      boolean(0);
      setState(106);
      match(temporalParser::RROUND);
      setState(107);
      sva_assert();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(109);
      match(temporalParser::LROUND);
      setState(110);
      implication();
      setState(111);
      match(temporalParser::RROUND);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(113);
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
    setState(144);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(116);
      tformula(0);
      setState(117);
      match(temporalParser::IMPL);
      setState(118);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(120);
      tformula(0);
      setState(121);
      match(temporalParser::IMPLO);
      setState(122);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(125);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(124);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(127);
      sere(0);
      setState(129);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RCURLY) {
        setState(128);
        match(temporalParser::RCURLY);
      }
      setState(131);
      match(temporalParser::SEREIMPL);
      setState(132);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(135);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(134);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(137);
      sere(0);
      setState(139);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RCURLY) {
        setState(138);
        match(temporalParser::RCURLY);
      }
      setState(141);
      match(temporalParser::SEREIMPLO);
      setState(142);
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
    setState(234);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(147);
      match(temporalParser::FIRST_MATCH);
      setState(148);
      match(temporalParser::LROUND);
      setState(149);
      sere(0);
      setState(150);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      setState(152);
      match(temporalParser::LROUND);
      setState(153);
      sere(0);
      setState(154);
      match(temporalParser::RROUND);
      break;
    }

    case 3: {
      setState(156);
      match(temporalParser::LCURLY);
      setState(157);
      sere(0);
      setState(158);
      match(temporalParser::RCURLY);
      break;
    }

    case 4: {
      setState(160);
      booleanLayer();
      setState(161);
      match(temporalParser::LSQUARED);
      setState(162);
      match(temporalParser::ASS);
      setState(164);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
      case 1: {
        setState(163);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(167);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS

      || _la == temporalParser::COL) {
        setState(166);
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
      setState(170);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER

      || _la == temporalParser::DOLLAR) {
        setState(169);
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
      setState(172);
      match(temporalParser::RSQUARED);
      break;
    }

    case 5: {
      setState(174);
      booleanLayer();
      setState(175);
      match(temporalParser::LSQUARED);
      setState(176);
      match(temporalParser::IMPLO);
      setState(178);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
      case 1: {
        setState(177);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(181);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS

      || _la == temporalParser::COL) {
        setState(180);
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
      setState(184);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER

      || _la == temporalParser::DOLLAR) {
        setState(183);
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
      setState(186);
      match(temporalParser::RSQUARED);
      break;
    }

    case 6: {
      setState(188);
      dt_ncreps();
      setState(193);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
      case 1: {
        setState(189);
        match(temporalParser::LROUND);
        setState(190);
        placeholder_domain();
        setState(191);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 7: {
      setState(195);
      match(temporalParser::DT_AND);
      setState(200);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
      case 1: {
        setState(196);
        match(temporalParser::LROUND);
        setState(197);
        placeholder_domain();
        setState(198);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 8: {
      setState(202);
      match(temporalParser::DELAY);
      setState(204);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::LSQUARED) {
        setState(203);
        match(temporalParser::LSQUARED);
      }
      setState(207);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(206);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(210);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS

      || _la == temporalParser::COL) {
        setState(209);
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
      setState(213);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
      case 1: {
        setState(212);
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
      setState(216);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RSQUARED) {
        setState(215);
        match(temporalParser::RSQUARED);
      }
      setState(218);
      sere(6);
      break;
    }

    case 9: {
      setState(219);
      dt_next();
      setState(224);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(220);
        match(temporalParser::LROUND);
        setState(221);
        placeholder_domain();
        setState(222);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 10: {
      setState(226);
      dt_next_and();
      setState(231);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
      case 1: {
        setState(227);
        match(temporalParser::LROUND);
        setState(228);
        placeholder_domain();
        setState(229);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 11: {
      setState(233);
      booleanLayer();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(288);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(286);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(236);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(237);
          match(temporalParser::BAND);
          setState(238);
          sere(12);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(239);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(240);
          _la = _input->LA(1);
          if (!(((((_la - 26) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 26)) & 281474976710659) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(241);
          sere(11);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(242);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(243);
          _la = _input->LA(1);
          if (!(((((_la - 28) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 28)) & 142936511610881) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(244);
          sere(9);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(245);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(246);
          match(temporalParser::DELAY);
          setState(248);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::LSQUARED) {
            setState(247);
            match(temporalParser::LSQUARED);
          }
          setState(251);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
          case 1: {
            setState(250);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(254);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::DOTS

          || _la == temporalParser::COL) {
            setState(253);
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
          setState(257);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
          case 1: {
            setState(256);
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
          setState(260);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::RSQUARED) {
            setState(259);
            match(temporalParser::RSQUARED);
          }
          setState(262);
          sere(8);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(263);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(264);
          match(temporalParser::COL);
          setState(265);
          sere(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(266);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(267);
          match(temporalParser::SCOL);
          setState(268);
          sere(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(269);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(270);
          match(temporalParser::LSQUARED);
          setState(271);
          match(temporalParser::TIMES);
          setState(273);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
          case 1: {
            setState(272);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(276);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::DOTS

          || _la == temporalParser::COL) {
            setState(275);
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
          setState(279);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::UINTEGER

          || _la == temporalParser::DOLLAR) {
            setState(278);
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
          setState(281);
          match(temporalParser::RSQUARED);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(282);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(283);
          match(temporalParser::LSQUARED);
          setState(284);
          match(temporalParser::PLUS);
          setState(285);
          match(temporalParser::RSQUARED);
          break;
        }

        default:
          break;
        } 
      }
      setState(290);
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
    setState(307);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(291);
      match(temporalParser::LROUND);
      setState(292);
      booleanLayer();
      setState(293);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(295);
      boolean(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(297);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::NOT) {
        setState(296);
        match(temporalParser::NOT);
      }
      setState(299);
      match(temporalParser::PLACEHOLDER);
      setState(304);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
      case 1: {
        setState(300);
        match(temporalParser::LROUND);
        setState(301);
        placeholder_domain();
        setState(302);
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
      setState(306);
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
    setState(346);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      setState(310);
      match(temporalParser::LROUND);
      setState(311);
      tformula(0);
      setState(312);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      setState(314);

      if (!(canUseSharedOperator(_input->LT(-1)->getText(),_input->LT(2)->getText()))) throw FailedPredicateException(this, "canUseSharedOperator(_input->LT(-1)->getText(),_input->LT(2)->getText())");
      setState(316);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
      case 1: {
        setState(315);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(318);
      sere(0);
      setState(320);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
      case 1: {
        setState(319);
        match(temporalParser::RCURLY);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      setState(322);

      if (!(canTakeThisNot(_input->LT(1)->getText(),_input->LT(2)->getText()))) throw FailedPredicateException(this, "canTakeThisNot(_input->LT(1)->getText(),_input->LT(2)->getText())");
      setState(323);
      _la = _input->LA(1);
      if (!(_la == temporalParser::TNOT

      || _la == temporalParser::NOT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(324);
      tformula(8);
      break;
    }

    case 4: {
      setState(325);
      match(temporalParser::NEXT);
      setState(327);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
      case 1: {
        setState(326);
        match(temporalParser::LSQUARED);
        break;
      }

      default:
        break;
      }
      setState(330);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
      case 1: {
        setState(329);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(333);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
      case 1: {
        setState(332);
        match(temporalParser::RSQUARED);
        break;
      }

      default:
        break;
      }
      setState(335);
      tformula(7);
      break;
    }

    case 5: {
      setState(336);
      match(temporalParser::EVENTUALLY);
      setState(337);
      tformula(6);
      break;
    }

    case 6: {
      setState(338);
      match(temporalParser::DT_AND);
      setState(343);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
      case 1: {
        setState(339);
        match(temporalParser::LROUND);
        setState(340);
        placeholder_domain();
        setState(341);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 7: {
      setState(345);
      booleanLayer();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(359);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(357);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(348);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(349);
          _la = _input->LA(1);
          if (!(_la == temporalParser::UNTIL

          || _la == temporalParser::RELEASE)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(350);
          tformula(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(351);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(352);
          _la = _input->LA(1);
          if (!(_la == temporalParser::TAND

          || _la == temporalParser::AND)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(353);
          tformula(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(354);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(355);
          _la = _input->LA(1);
          if (!(((((_la - 28) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 28)) & 142936511610881) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(356);
          tformula(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(361);
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
    setState(378);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::LROUND: {
        enterOuterAlt(_localctx, 1);
        setState(362);
        match(temporalParser::LROUND);
        setState(363);
        temporalFunction();
        setState(364);
        match(temporalParser::RROUND);
        break;
      }

      case temporalParser::FUNCTION: {
        enterOuterAlt(_localctx, 2);
        setState(366);
        match(temporalParser::FUNCTION);
        setState(367);
        match(temporalParser::LROUND);
        setState(368);
        tfunc_arg();
        setState(373);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == temporalParser::T__2) {
          setState(369);
          match(temporalParser::T__2);
          setState(370);
          tfunc_arg();
          setState(375);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(376);
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
    setState(388);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::PLACEHOLDER: {
        enterOuterAlt(_localctx, 1);
        setState(380);
        match(temporalParser::PLACEHOLDER);
        setState(385);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == temporalParser::LROUND) {
          setState(381);
          match(temporalParser::LROUND);
          setState(382);
          placeholder_domain();
          setState(383);
          match(temporalParser::RROUND);
        }
        break;
      }

      case temporalParser::UINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(387);
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
    setState(390);
    match(temporalParser::UINTEGER);
    setState(395);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == temporalParser::T__2) {
      setState(391);
      match(temporalParser::T__2);

      setState(392);
      match(temporalParser::UINTEGER);
      setState(397);
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
    setState(398);
    match(temporalParser::T__3);
    setState(399);
    match(temporalParser::UINTEGER);
    setState(400);
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
    setState(402);
    match(temporalParser::T__4);
    setState(403);
    match(temporalParser::UINTEGER);
    setState(404);
    match(temporalParser::BAND);
    setState(405);
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
    setState(407);
    match(temporalParser::T__5);
    setState(408);
    _la = _input->LA(1);
    if (!(_la == temporalParser::IMPLO

    || _la == temporalParser::ASS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(409);
    match(temporalParser::UINTEGER);
    setState(410);
    match(temporalParser::T__6);
    setState(411);
    _la = _input->LA(1);
    if (!(_la == temporalParser::SCOL

    || _la == temporalParser::COL)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(412);
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
    setState(416);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      setState(414);
      boolean(0);
      break;
    }

    case 2: {
      setState(415);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(418);
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
    setState(422);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      setState(420);
      numeric(0);
      break;
    }

    case 2: {
      setState(421);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(424);
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
    setState(428);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
    case 1: {
      setState(426);
      numeric(0);
      break;
    }

    case 2: {
      setState(427);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(430);
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
    setState(434);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      setState(432);
      numeric(0);
      break;
    }

    case 2: {
      setState(433);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(436);
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
    setState(438);
    string(0);
    setState(439);
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
    setState(441);
    boolean(0);
    setState(442);
    match(temporalParser::QUESTION);
    setState(445);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      setState(443);
      boolean(0);
      break;
    }

    case 2: {
      setState(444);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(447);
    match(temporalParser::COL);
    setState(450);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      setState(448);
      boolean(0);
      break;
    }

    case 2: {
      setState(449);
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
    setState(452);
    boolean(0);
    setState(453);
    match(temporalParser::QUESTION);
    setState(456);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      setState(454);
      numeric(0);
      break;
    }

    case 2: {
      setState(455);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(458);
    match(temporalParser::COL);
    setState(461);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      setState(459);
      numeric(0);
      break;
    }

    case 2: {
      setState(460);
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

tree::TerminalNode* temporalParser::BooleanContext::CASE_EQ() {
  return getToken(temporalParser::CASE_EQ, 0);
}

tree::TerminalNode* temporalParser::BooleanContext::CASE_NEQ() {
  return getToken(temporalParser::CASE_NEQ, 0);
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

temporalParser::BooleanTernaryContext* temporalParser::BooleanContext::booleanTernary() {
  return getRuleContext<temporalParser::BooleanTernaryContext>(0);
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
    setState(529);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
    case 1: {
      setState(464);
      match(temporalParser::NOT);
      setState(465);
      boolean(19);
      break;
    }

    case 2: {
      setState(466);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(467);
      numeric(0);
      setState(468);
      match(temporalParser::INSIDE);
      setState(469);
      match(temporalParser::LCURLY);
      setState(478);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(472);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case temporalParser::INT_VARIABLE:
            case temporalParser::LOGIC_VARIABLE:
            case temporalParser::FLOAT_CONSTANT:
            case temporalParser::FLOAT_VARIABLE:
            case temporalParser::LCURLY:
            case temporalParser::LROUND:
            case temporalParser::FUNCTION:
            case temporalParser::SINTEGER:
            case temporalParser::UINTEGER:
            case temporalParser::GCC_BINARY:
            case temporalParser::HEX:
            case temporalParser::VERILOG_BASED:
            case temporalParser::FILL_LITERAL:
            case temporalParser::NEG: {
              setState(470);
              sm_constant();
              break;
            }

            case temporalParser::LSQUARED: {
              setState(471);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(474);
          match(temporalParser::T__2); 
        }
        setState(480);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
      }
      setState(483);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case temporalParser::INT_VARIABLE:
        case temporalParser::LOGIC_VARIABLE:
        case temporalParser::FLOAT_CONSTANT:
        case temporalParser::FLOAT_VARIABLE:
        case temporalParser::LCURLY:
        case temporalParser::LROUND:
        case temporalParser::FUNCTION:
        case temporalParser::SINTEGER:
        case temporalParser::UINTEGER:
        case temporalParser::GCC_BINARY:
        case temporalParser::HEX:
        case temporalParser::VERILOG_BASED:
        case temporalParser::FILL_LITERAL:
        case temporalParser::NEG: {
          setState(481);
          sm_constant();
          break;
        }

        case temporalParser::LSQUARED: {
          setState(482);
          sm_range();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(485);
      match(temporalParser::RCURLY);
      break;
    }

    case 4: {
      setState(487);
      numeric(0);
      setState(488);
      relop();
      setState(489);
      numeric(0);
      break;
    }

    case 5: {
      setState(491);
      numeric(0);
      setState(492);
      match(temporalParser::EQ);
      setState(493);
      numeric(0);
      break;
    }

    case 6: {
      setState(495);
      numeric(0);
      setState(496);
      match(temporalParser::NEQ);
      setState(497);
      numeric(0);
      break;
    }

    case 7: {
      setState(499);
      numeric(0);
      setState(500);
      match(temporalParser::CASE_EQ);
      setState(501);
      numeric(0);
      break;
    }

    case 8: {
      setState(503);
      numeric(0);
      setState(504);
      match(temporalParser::CASE_NEQ);
      setState(505);
      numeric(0);
      break;
    }

    case 9: {
      setState(507);
      string(0);
      setState(508);
      relop();
      setState(509);
      string(0);
      break;
    }

    case 10: {
      setState(511);
      string(0);
      setState(512);
      match(temporalParser::EQ);
      setState(513);
      string(0);
      break;
    }

    case 11: {
      setState(515);
      string(0);
      setState(516);
      match(temporalParser::NEQ);
      setState(517);
      string(0);
      break;
    }

    case 12: {
      setState(519);
      booleanAtom();
      break;
    }

    case 13: {
      setState(520);
      numeric(0);
      break;
    }

    case 14: {
      setState(521);
      match(temporalParser::LROUND);
      setState(522);
      boolean(0);
      setState(523);
      match(temporalParser::RROUND);
      break;
    }

    case 15: {
      setState(525);
      match(temporalParser::LROUND);
      setState(526);
      booleanTernary();
      setState(527);
      match(temporalParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(545);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(543);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(531);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(532);
          match(temporalParser::EQ);
          setState(533);
          boolean(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(534);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(535);
          match(temporalParser::NEQ);
          setState(536);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(537);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(538);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(temporalParser::AND);
          setState(539);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(540);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(541);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(temporalParser::OR);
          setState(542);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(547);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
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
    setState(548);
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
    setState(566);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      setState(551);
      match(temporalParser::NEG);
      setState(552);
      numeric(16);
      break;
    }

    case 2: {
      setState(553);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(554);
      intAtom();
      break;
    }

    case 4: {
      setState(555);
      logicAtom();
      break;
    }

    case 5: {
      setState(556);
      floatAtom();
      break;
    }

    case 6: {
      setState(557);
      concatenation();
      break;
    }

    case 7: {
      setState(558);
      match(temporalParser::LROUND);
      setState(559);
      numeric(0);
      setState(560);
      match(temporalParser::RROUND);
      break;
    }

    case 8: {
      setState(562);
      match(temporalParser::LROUND);
      setState(563);
      numericTernary();
      setState(564);
      match(temporalParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(593);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(591);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(568);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(569);
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
          setState(570);
          numeric(14);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(571);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(572);
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
          setState(573);
          numeric(13);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(574);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(575);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::LSHIFT);
          setState(576);
          numeric(12);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(577);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(578);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::RSHIFT);
          setState(579);
          numeric(11);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(580);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(581);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BAND);
          setState(582);
          numeric(10);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(583);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(584);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BXOR);
          setState(585);
          numeric(9);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(586);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(587);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BOR);
          setState(588);
          numeric(8);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(589);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(590);
          range();
          break;
        }

        default:
          break;
        } 
      }
      setState(595);
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
    setState(620);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(596);
      match(temporalParser::LCURLY);
      setState(597);
      concatItem();
      setState(600); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(598);
        match(temporalParser::T__2);
        setState(599);
        concatItem();
        setState(602); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == temporalParser::T__2);
      setState(604);
      match(temporalParser::RCURLY);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(606);
      match(temporalParser::LCURLY);
      setState(607);
      match(temporalParser::UINTEGER);
      setState(608);
      match(temporalParser::LCURLY);
      setState(609);
      concatItem();
      setState(614);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == temporalParser::T__2) {
        setState(610);
        match(temporalParser::T__2);
        setState(611);
        concatItem();
        setState(616);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(617);
      match(temporalParser::RCURLY);
      setState(618);
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
    setState(624);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::INT_VARIABLE:
      case temporalParser::LOGIC_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LCURLY:
      case temporalParser::LROUND:
      case temporalParser::FUNCTION:
      case temporalParser::SINTEGER:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX:
      case temporalParser::VERILOG_BASED:
      case temporalParser::FILL_LITERAL:
      case temporalParser::NEG: {
        enterOuterAlt(_localctx, 1);
        setState(622);
        numeric(0);
        break;
      }

      case temporalParser::BOOLEAN_CONSTANT:
      case temporalParser::BOOLEAN_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(623);
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
    setState(626);
    match(temporalParser::LSQUARED);
    setState(627);
    _la = _input->LA(1);
    if (!(_la == temporalParser::SINTEGER

    || _la == temporalParser::UINTEGER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(630);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == temporalParser::COL) {
      setState(628);
      match(temporalParser::COL);
      setState(629);
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
    setState(632);
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
    setState(634);
    match(temporalParser::LSQUARED);
    setState(637);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::INT_VARIABLE:
      case temporalParser::LOGIC_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LCURLY:
      case temporalParser::LROUND:
      case temporalParser::FUNCTION:
      case temporalParser::SINTEGER:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX:
      case temporalParser::VERILOG_BASED:
      case temporalParser::FILL_LITERAL:
      case temporalParser::NEG: {
        setState(635);
        numeric(0);
        break;
      }

      case temporalParser::DOLLAR: {
        setState(636);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(639);
    match(temporalParser::COL);
    setState(642);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::INT_VARIABLE:
      case temporalParser::LOGIC_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LCURLY:
      case temporalParser::LROUND:
      case temporalParser::FUNCTION:
      case temporalParser::SINTEGER:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX:
      case temporalParser::VERILOG_BASED:
      case temporalParser::FILL_LITERAL:
      case temporalParser::NEG: {
        setState(640);
        numeric(0);
        break;
      }

      case temporalParser::DOLLAR: {
        setState(641);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(644);
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
    setState(646);
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
    setState(648);
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
    setState(650);
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
    setState(654);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::SINTEGER:
      case temporalParser::UINTEGER:
      case temporalParser::GCC_BINARY:
      case temporalParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(652);
        int_constant();
        break;
      }

      case temporalParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(653);
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
  enterRule(_localctx, 60, temporalParser::RuleInt_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(666);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(656);
        match(temporalParser::GCC_BINARY);
        break;
      }

      case temporalParser::SINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(657);
        match(temporalParser::SINTEGER);
        setState(659);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
        case 1: {
          setState(658);
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
        setState(661);
        match(temporalParser::UINTEGER);
        setState(663);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx)) {
        case 1: {
          setState(662);
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
        setState(665);
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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(668);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(669);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(670);
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
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(703);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx)) {
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

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx)) {
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
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx);
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
  enterRule(_localctx, 74, temporalParser::RulePfunc_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(724);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(722);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(723);
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
  enterRule(_localctx, 76, temporalParser::RuleRelop);
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
    setState(726);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8646911284551352320) != 0))) {
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
  enterRule(_localctx, 78, temporalParser::RuleCls_op);
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
    setState(728);
    _la = _input->LA(1);
    if (!(((((_la - 59) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 59)) & 2097183) != 0))) {
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
    case 13: return precpred(_ctx, 8);
    case 14: return precpred(_ctx, 7);
    case 15: return precpred(_ctx, 6);
    case 16: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

bool temporalParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 17: return precpred(_ctx, 13);
    case 18: return precpred(_ctx, 12);
    case 19: return precpred(_ctx, 11);
    case 20: return precpred(_ctx, 10);
    case 21: return precpred(_ctx, 9);
    case 22: return precpred(_ctx, 8);
    case 23: return precpred(_ctx, 7);
    case 24: return precpred(_ctx, 14);

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
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  temporalParserInitialize();
#else
  ::antlr4::internal::call_once(temporalParserOnceFlag, temporalParserInitialize);
#endif
}
