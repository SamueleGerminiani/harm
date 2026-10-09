
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
      "'and'", "'intersect'", "'or'", "", "", "", "", "", "", "", "", "'.substr'", 
      "", "", "'{'", "'}'", "'['", "']'", "'('", "')'", "'inside'", "", 
      "", "", "", "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", 
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
      "FUNCTION", "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", "VERILOG_BASED", 
      "FILL_LITERAL", "SINGLE_QUOTE", "PLUS", "MINUS", "TIMES", "DIV", "GT", 
      "GE", "LT", "LE", "EQ", "NEQ", "CASE_EQ", "CASE_NEQ", "QUESTION", 
      "BAND", "BOR", "BXOR", "NEG", "ALSHIFT", "ARSHIFT", "LSHIFT", "RSHIFT", 
      "AND", "OR", "NOT", "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,84,728,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,1,0,1,0,1,0,1,0,1,0,1,0,1,
  	0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,
  	104,8,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,130,8,1,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,3,2,141,8,2,1,2,1,2,3,2,145,8,2,1,2,1,2,1,2,1,2,3,2,151,8,
  	2,1,2,1,2,3,2,155,8,2,1,2,1,2,1,2,3,2,160,8,2,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,180,8,3,1,3,3,3,183,
  	8,3,1,3,3,3,186,8,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,194,8,3,1,3,3,3,197,8,
  	3,1,3,3,3,200,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,209,8,3,1,3,1,3,1,3,
  	1,3,1,3,3,3,216,8,3,1,3,1,3,3,3,220,8,3,1,3,3,3,223,8,3,1,3,3,3,226,8,
  	3,1,3,3,3,229,8,3,1,3,3,3,232,8,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,240,8,3,
  	1,3,1,3,1,3,1,3,1,3,3,3,247,8,3,1,3,3,3,250,8,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,264,8,3,1,3,3,3,267,8,3,1,3,3,3,270,8,3,
  	1,3,3,3,273,8,3,1,3,3,3,276,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,3,3,289,8,3,1,3,3,3,292,8,3,1,3,3,3,295,8,3,1,3,1,3,1,3,1,3,1,3,
  	5,3,302,8,3,10,3,12,3,305,9,3,1,4,1,4,1,4,1,4,1,4,1,4,3,4,313,8,4,1,4,
  	1,4,1,4,1,4,1,4,3,4,320,8,4,1,4,3,4,323,8,4,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,3,5,332,8,5,1,5,1,5,3,5,336,8,5,1,5,1,5,1,5,1,5,1,5,3,5,343,8,5,1,5,
  	3,5,346,8,5,1,5,3,5,349,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,359,8,
  	5,1,5,3,5,362,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,373,8,5,10,
  	5,12,5,376,9,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,5,6,387,8,6,10,6,12,
  	6,390,9,6,1,6,1,6,3,6,394,8,6,1,7,1,7,1,7,1,7,1,7,3,7,401,8,7,1,7,3,7,
  	404,8,7,1,8,1,8,1,8,5,8,409,8,8,10,8,12,8,412,9,8,1,9,1,9,1,9,1,9,1,10,
  	1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,3,12,
  	432,8,12,1,12,1,12,1,13,1,13,3,13,438,8,13,1,13,1,13,1,14,1,14,3,14,444,
  	8,14,1,14,1,14,1,15,1,15,3,15,450,8,15,1,15,1,15,1,16,1,16,1,16,1,17,
  	1,17,1,17,1,17,3,17,461,8,17,1,17,1,17,1,17,3,17,466,8,17,1,18,1,18,1,
  	18,1,18,3,18,472,8,18,1,18,1,18,1,18,3,18,477,8,18,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,505,8,19,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,5,19,516,8,19,10,19,12,19,519,9,19,1,20,
  	1,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,543,8,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	3,21,577,8,21,1,21,1,21,5,21,581,8,21,10,21,12,21,584,9,21,1,21,1,21,
  	3,21,588,8,21,1,21,1,21,5,21,592,8,21,10,21,12,21,595,9,21,1,22,1,22,
  	1,22,1,22,4,22,601,8,22,11,22,12,22,602,1,22,1,22,1,22,1,22,1,22,1,22,
  	1,22,1,22,5,22,613,8,22,10,22,12,22,616,9,22,1,22,1,22,1,22,3,22,621,
  	8,22,1,23,1,23,3,23,625,8,23,1,24,1,24,1,24,1,24,3,24,631,8,24,1,24,1,
  	24,1,25,1,25,1,25,3,25,638,8,25,1,25,1,25,1,25,3,25,643,8,25,1,25,1,25,
  	1,26,1,26,1,27,1,27,1,28,1,28,1,29,1,29,3,29,655,8,29,1,30,1,30,1,30,
  	3,30,660,8,30,1,30,3,30,663,8,30,1,31,1,31,1,31,1,31,3,31,669,8,31,1,
  	32,3,32,672,8,32,1,32,1,32,3,32,676,8,32,1,33,1,33,1,34,1,34,1,34,1,34,
  	1,34,1,34,3,34,686,8,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,
  	1,34,3,34,698,8,34,1,34,5,34,701,8,34,10,34,12,34,704,9,34,1,35,1,35,
  	1,36,1,36,1,36,1,36,1,36,5,36,713,8,36,10,36,12,36,716,9,36,1,36,1,36,
  	1,37,1,37,3,37,722,8,37,1,38,1,38,1,39,1,39,1,39,0,5,6,10,38,42,68,40,
  	0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,
  	50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,0,20,2,0,15,15,79,79,2,0,
  	48,48,81,81,2,0,26,27,76,76,3,0,28,28,69,69,77,77,2,0,25,25,78,78,1,0,
  	13,14,2,0,26,26,76,76,2,0,17,17,21,21,2,0,23,23,79,79,1,0,63,64,1,0,29,
  	30,3,0,55,56,71,71,78,78,1,0,57,58,1,0,55,56,1,0,72,75,1,0,63,66,1,0,
  	35,36,1,0,38,39,1,0,59,62,2,0,59,63,82,82,833,0,103,1,0,0,0,2,129,1,0,
  	0,0,4,159,1,0,0,0,6,249,1,0,0,0,8,322,1,0,0,0,10,361,1,0,0,0,12,393,1,
  	0,0,0,14,403,1,0,0,0,16,405,1,0,0,0,18,413,1,0,0,0,20,417,1,0,0,0,22,
  	422,1,0,0,0,24,431,1,0,0,0,26,437,1,0,0,0,28,443,1,0,0,0,30,449,1,0,0,
  	0,32,453,1,0,0,0,34,456,1,0,0,0,36,467,1,0,0,0,38,504,1,0,0,0,40,520,
  	1,0,0,0,42,542,1,0,0,0,44,620,1,0,0,0,46,624,1,0,0,0,48,626,1,0,0,0,50,
  	634,1,0,0,0,52,646,1,0,0,0,54,648,1,0,0,0,56,650,1,0,0,0,58,654,1,0,0,
  	0,60,662,1,0,0,0,62,668,1,0,0,0,64,675,1,0,0,0,66,677,1,0,0,0,68,685,
  	1,0,0,0,70,705,1,0,0,0,72,707,1,0,0,0,74,721,1,0,0,0,76,723,1,0,0,0,78,
  	725,1,0,0,0,80,81,5,11,0,0,81,82,5,44,0,0,82,83,3,4,2,0,83,84,5,45,0,
  	0,84,85,5,0,0,1,85,104,1,0,0,0,86,87,5,11,0,0,87,88,3,4,2,0,88,89,5,0,
  	0,1,89,104,1,0,0,0,90,91,3,2,1,0,91,92,5,0,0,1,92,104,1,0,0,0,93,94,5,
  	11,0,0,94,95,5,44,0,0,95,96,3,10,5,0,96,97,5,45,0,0,97,98,5,0,0,1,98,
  	104,1,0,0,0,99,100,5,11,0,0,100,101,3,10,5,0,101,102,5,0,0,1,102,104,
  	1,0,0,0,103,80,1,0,0,0,103,86,1,0,0,0,103,90,1,0,0,0,103,93,1,0,0,0,103,
  	99,1,0,0,0,104,1,1,0,0,0,105,106,5,1,0,0,106,107,5,44,0,0,107,108,3,2,
  	1,0,108,109,5,45,0,0,109,130,1,0,0,0,110,111,5,44,0,0,111,112,3,2,1,0,
  	112,113,5,45,0,0,113,130,1,0,0,0,114,115,5,2,0,0,115,116,3,38,19,0,116,
  	117,5,45,0,0,117,118,3,2,1,0,118,130,1,0,0,0,119,120,5,44,0,0,120,121,
  	3,4,2,0,121,122,5,45,0,0,122,130,1,0,0,0,123,130,3,4,2,0,124,125,5,44,
  	0,0,125,126,3,10,5,0,126,127,5,45,0,0,127,130,1,0,0,0,128,130,3,10,5,
  	0,129,105,1,0,0,0,129,110,1,0,0,0,129,114,1,0,0,0,129,119,1,0,0,0,129,
  	123,1,0,0,0,129,124,1,0,0,0,129,128,1,0,0,0,130,3,1,0,0,0,131,132,3,10,
  	5,0,132,133,5,16,0,0,133,134,3,10,5,0,134,160,1,0,0,0,135,136,3,10,5,
  	0,136,137,5,17,0,0,137,138,3,10,5,0,138,160,1,0,0,0,139,141,5,40,0,0,
  	140,139,1,0,0,0,140,141,1,0,0,0,141,142,1,0,0,0,142,144,3,6,3,0,143,145,
  	5,41,0,0,144,143,1,0,0,0,144,145,1,0,0,0,145,146,1,0,0,0,146,147,5,19,
  	0,0,147,148,3,10,5,0,148,160,1,0,0,0,149,151,5,40,0,0,150,149,1,0,0,0,
  	150,151,1,0,0,0,151,152,1,0,0,0,152,154,3,6,3,0,153,155,5,41,0,0,154,
  	153,1,0,0,0,154,155,1,0,0,0,155,156,1,0,0,0,156,157,5,20,0,0,157,158,
  	3,10,5,0,158,160,1,0,0,0,159,131,1,0,0,0,159,135,1,0,0,0,159,140,1,0,
  	0,0,159,150,1,0,0,0,160,5,1,0,0,0,161,162,6,3,-1,0,162,163,5,24,0,0,163,
  	164,5,44,0,0,164,165,3,6,3,0,165,166,5,45,0,0,166,250,1,0,0,0,167,168,
  	5,44,0,0,168,169,3,6,3,0,169,170,5,45,0,0,170,250,1,0,0,0,171,172,5,40,
  	0,0,172,173,3,6,3,0,173,174,5,41,0,0,174,250,1,0,0,0,175,176,3,8,4,0,
  	176,177,5,42,0,0,177,179,5,21,0,0,178,180,5,48,0,0,179,178,1,0,0,0,179,
  	180,1,0,0,0,180,182,1,0,0,0,181,183,7,0,0,0,182,181,1,0,0,0,182,183,1,
  	0,0,0,183,185,1,0,0,0,184,186,7,1,0,0,185,184,1,0,0,0,185,186,1,0,0,0,
  	186,187,1,0,0,0,187,188,5,43,0,0,188,250,1,0,0,0,189,190,3,8,4,0,190,
  	191,5,42,0,0,191,193,5,17,0,0,192,194,5,48,0,0,193,192,1,0,0,0,193,194,
  	1,0,0,0,194,196,1,0,0,0,195,197,7,0,0,0,196,195,1,0,0,0,196,197,1,0,0,
  	0,197,199,1,0,0,0,198,200,7,1,0,0,199,198,1,0,0,0,199,200,1,0,0,0,200,
  	201,1,0,0,0,201,202,5,43,0,0,202,250,1,0,0,0,203,208,3,22,11,0,204,205,
  	5,44,0,0,205,206,3,16,8,0,206,207,5,45,0,0,207,209,1,0,0,0,208,204,1,
  	0,0,0,208,209,1,0,0,0,209,250,1,0,0,0,210,215,5,9,0,0,211,212,5,44,0,
  	0,212,213,3,16,8,0,213,214,5,45,0,0,214,216,1,0,0,0,215,211,1,0,0,0,215,
  	216,1,0,0,0,216,250,1,0,0,0,217,219,5,22,0,0,218,220,5,42,0,0,219,218,
  	1,0,0,0,219,220,1,0,0,0,220,222,1,0,0,0,221,223,5,48,0,0,222,221,1,0,
  	0,0,222,223,1,0,0,0,223,225,1,0,0,0,224,226,7,0,0,0,225,224,1,0,0,0,225,
  	226,1,0,0,0,226,228,1,0,0,0,227,229,7,1,0,0,228,227,1,0,0,0,228,229,1,
  	0,0,0,229,231,1,0,0,0,230,232,5,43,0,0,231,230,1,0,0,0,231,232,1,0,0,
  	0,232,233,1,0,0,0,233,250,3,6,3,6,234,239,3,18,9,0,235,236,5,44,0,0,236,
  	237,3,16,8,0,237,238,5,45,0,0,238,240,1,0,0,0,239,235,1,0,0,0,239,240,
  	1,0,0,0,240,250,1,0,0,0,241,246,3,20,10,0,242,243,5,44,0,0,243,244,3,
  	16,8,0,244,245,5,45,0,0,245,247,1,0,0,0,246,242,1,0,0,0,246,247,1,0,0,
  	0,247,250,1,0,0,0,248,250,3,8,4,0,249,161,1,0,0,0,249,167,1,0,0,0,249,
  	171,1,0,0,0,249,175,1,0,0,0,249,189,1,0,0,0,249,203,1,0,0,0,249,210,1,
  	0,0,0,249,217,1,0,0,0,249,234,1,0,0,0,249,241,1,0,0,0,249,248,1,0,0,0,
  	250,303,1,0,0,0,251,252,10,11,0,0,252,253,5,68,0,0,253,302,3,6,3,12,254,
  	255,10,10,0,0,255,256,7,2,0,0,256,302,3,6,3,11,257,258,10,8,0,0,258,259,
  	7,3,0,0,259,302,3,6,3,9,260,261,10,7,0,0,261,263,5,22,0,0,262,264,5,42,
  	0,0,263,262,1,0,0,0,263,264,1,0,0,0,264,266,1,0,0,0,265,267,5,48,0,0,
  	266,265,1,0,0,0,266,267,1,0,0,0,267,269,1,0,0,0,268,270,7,0,0,0,269,268,
  	1,0,0,0,269,270,1,0,0,0,270,272,1,0,0,0,271,273,7,1,0,0,272,271,1,0,0,
  	0,272,273,1,0,0,0,273,275,1,0,0,0,274,276,5,43,0,0,275,274,1,0,0,0,275,
  	276,1,0,0,0,276,277,1,0,0,0,277,302,3,6,3,8,278,279,10,3,0,0,279,280,
  	5,79,0,0,280,302,3,6,3,4,281,282,10,2,0,0,282,283,5,23,0,0,283,302,3,
  	6,3,3,284,285,10,16,0,0,285,286,5,42,0,0,286,288,5,57,0,0,287,289,5,48,
  	0,0,288,287,1,0,0,0,288,289,1,0,0,0,289,291,1,0,0,0,290,292,7,0,0,0,291,
  	290,1,0,0,0,291,292,1,0,0,0,292,294,1,0,0,0,293,295,7,1,0,0,294,293,1,
  	0,0,0,294,295,1,0,0,0,295,296,1,0,0,0,296,302,5,43,0,0,297,298,10,15,
  	0,0,298,299,5,42,0,0,299,300,5,55,0,0,300,302,5,43,0,0,301,251,1,0,0,
  	0,301,254,1,0,0,0,301,257,1,0,0,0,301,260,1,0,0,0,301,278,1,0,0,0,301,
  	281,1,0,0,0,301,284,1,0,0,0,301,297,1,0,0,0,302,305,1,0,0,0,303,301,1,
  	0,0,0,303,304,1,0,0,0,304,7,1,0,0,0,305,303,1,0,0,0,306,307,5,44,0,0,
  	307,308,3,8,4,0,308,309,5,45,0,0,309,323,1,0,0,0,310,323,3,38,19,0,311,
  	313,5,78,0,0,312,311,1,0,0,0,312,313,1,0,0,0,313,314,1,0,0,0,314,319,
  	5,8,0,0,315,316,5,44,0,0,316,317,3,16,8,0,317,318,5,45,0,0,318,320,1,
  	0,0,0,319,315,1,0,0,0,319,320,1,0,0,0,320,323,1,0,0,0,321,323,3,12,6,
  	0,322,306,1,0,0,0,322,310,1,0,0,0,322,312,1,0,0,0,322,321,1,0,0,0,323,
  	9,1,0,0,0,324,325,6,5,-1,0,325,326,5,44,0,0,326,327,3,10,5,0,327,328,
  	5,45,0,0,328,362,1,0,0,0,329,331,4,5,8,0,330,332,5,40,0,0,331,330,1,0,
  	0,0,331,332,1,0,0,0,332,333,1,0,0,0,333,335,3,6,3,0,334,336,5,41,0,0,
  	335,334,1,0,0,0,335,336,1,0,0,0,336,362,1,0,0,0,337,338,4,5,9,0,338,339,
  	7,4,0,0,339,362,3,10,5,8,340,342,5,12,0,0,341,343,5,42,0,0,342,341,1,
  	0,0,0,342,343,1,0,0,0,343,345,1,0,0,0,344,346,5,48,0,0,345,344,1,0,0,
  	0,345,346,1,0,0,0,346,348,1,0,0,0,347,349,5,43,0,0,348,347,1,0,0,0,348,
  	349,1,0,0,0,349,350,1,0,0,0,350,362,3,10,5,7,351,352,5,10,0,0,352,362,
  	3,10,5,6,353,358,5,9,0,0,354,355,5,44,0,0,355,356,3,16,8,0,356,357,5,
  	45,0,0,357,359,1,0,0,0,358,354,1,0,0,0,358,359,1,0,0,0,359,362,1,0,0,
  	0,360,362,3,8,4,0,361,324,1,0,0,0,361,329,1,0,0,0,361,337,1,0,0,0,361,
  	340,1,0,0,0,361,351,1,0,0,0,361,353,1,0,0,0,361,360,1,0,0,0,362,374,1,
  	0,0,0,363,364,10,5,0,0,364,365,7,5,0,0,365,373,3,10,5,5,366,367,10,4,
  	0,0,367,368,7,6,0,0,368,373,3,10,5,5,369,370,10,3,0,0,370,371,7,3,0,0,
  	371,373,3,10,5,4,372,363,1,0,0,0,372,366,1,0,0,0,372,369,1,0,0,0,373,
  	376,1,0,0,0,374,372,1,0,0,0,374,375,1,0,0,0,375,11,1,0,0,0,376,374,1,
  	0,0,0,377,378,5,44,0,0,378,379,3,12,6,0,379,380,5,45,0,0,380,394,1,0,
  	0,0,381,382,5,47,0,0,382,383,5,44,0,0,383,388,3,14,7,0,384,385,5,3,0,
  	0,385,387,3,14,7,0,386,384,1,0,0,0,387,390,1,0,0,0,388,386,1,0,0,0,388,
  	389,1,0,0,0,389,391,1,0,0,0,390,388,1,0,0,0,391,392,5,45,0,0,392,394,
  	1,0,0,0,393,377,1,0,0,0,393,381,1,0,0,0,394,13,1,0,0,0,395,400,5,8,0,
  	0,396,397,5,44,0,0,397,398,3,16,8,0,398,399,5,45,0,0,399,401,1,0,0,0,
  	400,396,1,0,0,0,400,401,1,0,0,0,401,404,1,0,0,0,402,404,5,48,0,0,403,
  	395,1,0,0,0,403,402,1,0,0,0,404,15,1,0,0,0,405,410,5,48,0,0,406,407,5,
  	3,0,0,407,409,5,48,0,0,408,406,1,0,0,0,409,412,1,0,0,0,410,408,1,0,0,
  	0,410,411,1,0,0,0,411,17,1,0,0,0,412,410,1,0,0,0,413,414,5,4,0,0,414,
  	415,5,48,0,0,415,416,5,15,0,0,416,19,1,0,0,0,417,418,5,5,0,0,418,419,
  	5,48,0,0,419,420,5,68,0,0,420,421,5,15,0,0,421,21,1,0,0,0,422,423,5,6,
  	0,0,423,424,7,7,0,0,424,425,5,48,0,0,425,426,5,7,0,0,426,427,7,8,0,0,
  	427,428,5,15,0,0,428,23,1,0,0,0,429,432,3,38,19,0,430,432,3,34,17,0,431,
  	429,1,0,0,0,431,430,1,0,0,0,432,433,1,0,0,0,433,434,5,0,0,1,434,25,1,
  	0,0,0,435,438,3,42,21,0,436,438,3,36,18,0,437,435,1,0,0,0,437,436,1,0,
  	0,0,438,439,1,0,0,0,439,440,5,0,0,1,440,27,1,0,0,0,441,444,3,42,21,0,
  	442,444,3,36,18,0,443,441,1,0,0,0,443,442,1,0,0,0,444,445,1,0,0,0,445,
  	446,5,0,0,1,446,29,1,0,0,0,447,450,3,42,21,0,448,450,3,36,18,0,449,447,
  	1,0,0,0,449,448,1,0,0,0,450,451,1,0,0,0,451,452,5,0,0,1,452,31,1,0,0,
  	0,453,454,3,68,34,0,454,455,5,0,0,1,455,33,1,0,0,0,456,457,3,38,19,0,
  	457,460,5,67,0,0,458,461,3,38,19,0,459,461,3,34,17,0,460,458,1,0,0,0,
  	460,459,1,0,0,0,461,462,1,0,0,0,462,465,5,79,0,0,463,466,3,38,19,0,464,
  	466,3,34,17,0,465,463,1,0,0,0,465,464,1,0,0,0,466,35,1,0,0,0,467,468,
  	3,38,19,0,468,471,5,67,0,0,469,472,3,42,21,0,470,472,3,36,18,0,471,469,
  	1,0,0,0,471,470,1,0,0,0,472,473,1,0,0,0,473,476,5,79,0,0,474,477,3,42,
  	21,0,475,477,3,36,18,0,476,474,1,0,0,0,476,475,1,0,0,0,477,37,1,0,0,0,
  	478,479,6,19,-1,0,479,505,3,40,20,0,480,505,3,72,36,0,481,482,3,68,34,
  	0,482,483,3,76,38,0,483,484,3,68,34,0,484,505,1,0,0,0,485,486,3,68,34,
  	0,486,487,5,63,0,0,487,488,3,68,34,0,488,505,1,0,0,0,489,490,3,68,34,
  	0,490,491,5,64,0,0,491,492,3,68,34,0,492,505,1,0,0,0,493,494,5,44,0,0,
  	494,495,3,38,19,0,495,496,5,45,0,0,496,505,1,0,0,0,497,505,3,42,21,0,
  	498,499,5,44,0,0,499,500,3,34,17,0,500,501,5,45,0,0,501,505,1,0,0,0,502,
  	503,5,78,0,0,503,505,3,38,19,4,504,478,1,0,0,0,504,480,1,0,0,0,504,481,
  	1,0,0,0,504,485,1,0,0,0,504,489,1,0,0,0,504,493,1,0,0,0,504,497,1,0,0,
  	0,504,498,1,0,0,0,504,502,1,0,0,0,505,517,1,0,0,0,506,507,10,3,0,0,507,
  	508,7,9,0,0,508,516,3,38,19,4,509,510,10,2,0,0,510,511,5,76,0,0,511,516,
  	3,38,19,3,512,513,10,1,0,0,513,514,5,77,0,0,514,516,3,38,19,2,515,506,
  	1,0,0,0,515,509,1,0,0,0,515,512,1,0,0,0,516,519,1,0,0,0,517,515,1,0,0,
  	0,517,518,1,0,0,0,518,39,1,0,0,0,519,517,1,0,0,0,520,521,7,10,0,0,521,
  	41,1,0,0,0,522,523,6,21,-1,0,523,524,7,11,0,0,524,543,3,42,21,18,525,
  	543,3,72,36,0,526,543,3,58,29,0,527,543,3,62,31,0,528,543,3,66,33,0,529,
  	543,3,44,22,0,530,531,5,44,0,0,531,532,3,42,21,0,532,533,5,45,0,0,533,
  	543,1,0,0,0,534,535,5,44,0,0,535,536,3,36,18,0,536,537,5,45,0,0,537,543,
  	1,0,0,0,538,539,5,44,0,0,539,540,3,38,19,0,540,541,5,45,0,0,541,543,1,
  	0,0,0,542,522,1,0,0,0,542,525,1,0,0,0,542,526,1,0,0,0,542,527,1,0,0,0,
  	542,528,1,0,0,0,542,529,1,0,0,0,542,530,1,0,0,0,542,534,1,0,0,0,542,538,
  	1,0,0,0,543,593,1,0,0,0,544,545,10,16,0,0,545,546,7,12,0,0,546,592,3,
  	42,21,17,547,548,10,15,0,0,548,549,7,13,0,0,549,592,3,42,21,16,550,551,
  	10,14,0,0,551,552,7,14,0,0,552,592,3,42,21,15,553,554,10,13,0,0,554,555,
  	3,76,38,0,555,556,3,42,21,14,556,592,1,0,0,0,557,558,10,11,0,0,558,559,
  	7,15,0,0,559,592,3,42,21,12,560,561,10,10,0,0,561,562,5,68,0,0,562,592,
  	3,42,21,11,563,564,10,9,0,0,564,565,5,70,0,0,565,592,3,42,21,10,566,567,
  	10,8,0,0,567,568,5,69,0,0,568,592,3,42,21,9,569,570,10,19,0,0,570,592,
  	3,48,24,0,571,572,10,12,0,0,572,573,5,46,0,0,573,582,5,40,0,0,574,577,
  	3,56,28,0,575,577,3,50,25,0,576,574,1,0,0,0,576,575,1,0,0,0,577,578,1,
  	0,0,0,578,579,5,3,0,0,579,581,1,0,0,0,580,576,1,0,0,0,581,584,1,0,0,0,
  	582,580,1,0,0,0,582,583,1,0,0,0,583,587,1,0,0,0,584,582,1,0,0,0,585,588,
  	3,56,28,0,586,588,3,50,25,0,587,585,1,0,0,0,587,586,1,0,0,0,588,589,1,
  	0,0,0,589,590,5,41,0,0,590,592,1,0,0,0,591,544,1,0,0,0,591,547,1,0,0,
  	0,591,550,1,0,0,0,591,553,1,0,0,0,591,557,1,0,0,0,591,560,1,0,0,0,591,
  	563,1,0,0,0,591,566,1,0,0,0,591,569,1,0,0,0,591,571,1,0,0,0,592,595,1,
  	0,0,0,593,591,1,0,0,0,593,594,1,0,0,0,594,43,1,0,0,0,595,593,1,0,0,0,
  	596,597,5,40,0,0,597,600,3,46,23,0,598,599,5,3,0,0,599,601,3,46,23,0,
  	600,598,1,0,0,0,601,602,1,0,0,0,602,600,1,0,0,0,602,603,1,0,0,0,603,604,
  	1,0,0,0,604,605,5,41,0,0,605,621,1,0,0,0,606,607,5,40,0,0,607,608,5,48,
  	0,0,608,609,5,40,0,0,609,614,3,46,23,0,610,611,5,3,0,0,611,613,3,46,23,
  	0,612,610,1,0,0,0,613,616,1,0,0,0,614,612,1,0,0,0,614,615,1,0,0,0,615,
  	617,1,0,0,0,616,614,1,0,0,0,617,618,5,41,0,0,618,619,5,41,0,0,619,621,
  	1,0,0,0,620,596,1,0,0,0,620,606,1,0,0,0,621,45,1,0,0,0,622,625,3,42,21,
  	0,623,625,3,40,20,0,624,622,1,0,0,0,624,623,1,0,0,0,625,47,1,0,0,0,626,
  	627,5,42,0,0,627,630,5,48,0,0,628,629,5,79,0,0,629,631,5,48,0,0,630,628,
  	1,0,0,0,630,631,1,0,0,0,631,632,1,0,0,0,632,633,5,43,0,0,633,49,1,0,0,
  	0,634,637,5,42,0,0,635,638,3,42,21,0,636,638,3,52,26,0,637,635,1,0,0,
  	0,637,636,1,0,0,0,638,639,1,0,0,0,639,642,5,79,0,0,640,643,3,42,21,0,
  	641,643,3,54,27,0,642,640,1,0,0,0,642,641,1,0,0,0,643,644,1,0,0,0,644,
  	645,5,43,0,0,645,51,1,0,0,0,646,647,5,81,0,0,647,53,1,0,0,0,648,649,5,
  	81,0,0,649,55,1,0,0,0,650,651,3,42,21,0,651,57,1,0,0,0,652,655,3,60,30,
  	0,653,655,5,31,0,0,654,652,1,0,0,0,654,653,1,0,0,0,655,59,1,0,0,0,656,
  	663,5,50,0,0,657,659,5,48,0,0,658,660,5,32,0,0,659,658,1,0,0,0,659,660,
  	1,0,0,0,660,663,1,0,0,0,661,663,5,51,0,0,662,656,1,0,0,0,662,657,1,0,
  	0,0,662,661,1,0,0,0,663,61,1,0,0,0,664,669,3,64,32,0,665,669,3,60,30,
  	0,666,669,5,33,0,0,667,669,5,34,0,0,668,664,1,0,0,0,668,665,1,0,0,0,668,
  	666,1,0,0,0,668,667,1,0,0,0,669,63,1,0,0,0,670,672,5,48,0,0,671,670,1,
  	0,0,0,671,672,1,0,0,0,672,673,1,0,0,0,673,676,5,52,0,0,674,676,5,53,0,
  	0,675,671,1,0,0,0,675,674,1,0,0,0,676,65,1,0,0,0,677,678,7,16,0,0,678,
  	67,1,0,0,0,679,680,6,34,-1,0,680,686,3,70,35,0,681,682,5,44,0,0,682,683,
  	3,68,34,0,683,684,5,45,0,0,684,686,1,0,0,0,685,679,1,0,0,0,685,681,1,
  	0,0,0,686,702,1,0,0,0,687,688,10,4,0,0,688,689,5,55,0,0,689,701,3,68,
  	34,5,690,691,10,3,0,0,691,692,5,37,0,0,692,697,5,44,0,0,693,694,5,48,
  	0,0,694,695,5,3,0,0,695,698,5,48,0,0,696,698,5,48,0,0,697,693,1,0,0,0,
  	697,696,1,0,0,0,697,698,1,0,0,0,698,699,1,0,0,0,699,701,5,45,0,0,700,
  	687,1,0,0,0,700,690,1,0,0,0,701,704,1,0,0,0,702,700,1,0,0,0,702,703,1,
  	0,0,0,703,69,1,0,0,0,704,702,1,0,0,0,705,706,7,17,0,0,706,71,1,0,0,0,
  	707,708,5,47,0,0,708,709,5,44,0,0,709,714,3,74,37,0,710,711,5,3,0,0,711,
  	713,3,74,37,0,712,710,1,0,0,0,713,716,1,0,0,0,714,712,1,0,0,0,714,715,
  	1,0,0,0,715,717,1,0,0,0,716,714,1,0,0,0,717,718,5,45,0,0,718,73,1,0,0,
  	0,719,722,3,42,21,0,720,722,3,38,19,0,721,719,1,0,0,0,721,720,1,0,0,0,
  	722,75,1,0,0,0,723,724,7,18,0,0,724,77,1,0,0,0,725,726,7,19,0,0,726,79,
  	1,0,0,0,86,103,129,140,144,150,154,159,179,182,185,193,196,199,208,215,
  	219,222,225,228,231,239,246,249,263,266,269,272,275,288,291,294,301,303,
  	312,319,322,331,335,342,345,348,358,361,372,374,388,393,400,403,410,431,
  	437,443,449,460,465,471,476,504,515,517,542,576,582,587,591,593,602,614,
  	620,624,630,637,642,654,659,662,668,671,675,685,697,700,702,714,721
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
    setState(103);
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

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(93);
      match(temporalParser::ALWAYS);
      setState(94);
      match(temporalParser::LROUND);
      setState(95);
      tformula(0);
      setState(96);
      match(temporalParser::RROUND);
      setState(97);
      match(temporalParser::EOF);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(99);
      match(temporalParser::ALWAYS);
      setState(100);
      tformula(0);
      setState(101);
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
    setState(129);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(105);
      match(temporalParser::T__0);
      setState(106);
      match(temporalParser::LROUND);
      setState(107);
      sva_assert();
      setState(108);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(110);
      match(temporalParser::LROUND);
      setState(111);
      sva_assert();
      setState(112);
      match(temporalParser::RROUND);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(114);
      match(temporalParser::T__1);
      setState(115);
      boolean(0);
      setState(116);
      match(temporalParser::RROUND);
      setState(117);
      sva_assert();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(119);
      match(temporalParser::LROUND);
      setState(120);
      implication();
      setState(121);
      match(temporalParser::RROUND);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(123);
      implication();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(124);
      match(temporalParser::LROUND);
      setState(125);
      tformula(0);
      setState(126);
      match(temporalParser::RROUND);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(128);
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
    setState(159);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(131);
      tformula(0);
      setState(132);
      match(temporalParser::IMPL);
      setState(133);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(135);
      tformula(0);
      setState(136);
      match(temporalParser::IMPLO);
      setState(137);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(140);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(139);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(142);
      sere(0);
      setState(144);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RCURLY) {
        setState(143);
        match(temporalParser::RCURLY);
      }
      setState(146);
      match(temporalParser::SEREIMPL);
      setState(147);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(150);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(149);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(152);
      sere(0);
      setState(154);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RCURLY) {
        setState(153);
        match(temporalParser::RCURLY);
      }
      setState(156);
      match(temporalParser::SEREIMPLO);
      setState(157);
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
    setState(249);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(162);
      match(temporalParser::FIRST_MATCH);
      setState(163);
      match(temporalParser::LROUND);
      setState(164);
      sere(0);
      setState(165);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      setState(167);
      match(temporalParser::LROUND);
      setState(168);
      sere(0);
      setState(169);
      match(temporalParser::RROUND);
      break;
    }

    case 3: {
      setState(171);
      match(temporalParser::LCURLY);
      setState(172);
      sere(0);
      setState(173);
      match(temporalParser::RCURLY);
      break;
    }

    case 4: {
      setState(175);
      booleanLayer();
      setState(176);
      match(temporalParser::LSQUARED);
      setState(177);
      match(temporalParser::ASS);
      setState(179);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
      case 1: {
        setState(178);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(182);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS || _la == temporalParser::COL) {
        setState(181);
        _la = _input->LA(1);
        if (!(_la == temporalParser::DOTS || _la == temporalParser::COL)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(185);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER

      || _la == temporalParser::DOLLAR) {
        setState(184);
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
      setState(187);
      match(temporalParser::RSQUARED);
      break;
    }

    case 5: {
      setState(189);
      booleanLayer();
      setState(190);
      match(temporalParser::LSQUARED);
      setState(191);
      match(temporalParser::IMPLO);
      setState(193);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
      case 1: {
        setState(192);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(196);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS || _la == temporalParser::COL) {
        setState(195);
        _la = _input->LA(1);
        if (!(_la == temporalParser::DOTS || _la == temporalParser::COL)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(199);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::UINTEGER

      || _la == temporalParser::DOLLAR) {
        setState(198);
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
      setState(201);
      match(temporalParser::RSQUARED);
      break;
    }

    case 6: {
      setState(203);
      dt_ncreps();
      setState(208);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
      case 1: {
        setState(204);
        match(temporalParser::LROUND);
        setState(205);
        placeholder_domain();
        setState(206);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 7: {
      setState(210);
      match(temporalParser::DT_AND);
      setState(215);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
      case 1: {
        setState(211);
        match(temporalParser::LROUND);
        setState(212);
        placeholder_domain();
        setState(213);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 8: {
      setState(217);
      match(temporalParser::DELAY);
      setState(219);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::LSQUARED) {
        setState(218);
        match(temporalParser::LSQUARED);
      }
      setState(222);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(221);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(225);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::DOTS || _la == temporalParser::COL) {
        setState(224);
        _la = _input->LA(1);
        if (!(_la == temporalParser::DOTS || _la == temporalParser::COL)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
      setState(228);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
      case 1: {
        setState(227);
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
      setState(231);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::RSQUARED) {
        setState(230);
        match(temporalParser::RSQUARED);
      }
      setState(233);
      sere(6);
      break;
    }

    case 9: {
      setState(234);
      dt_next();
      setState(239);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(235);
        match(temporalParser::LROUND);
        setState(236);
        placeholder_domain();
        setState(237);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 10: {
      setState(241);
      dt_next_and();
      setState(246);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
      case 1: {
        setState(242);
        match(temporalParser::LROUND);
        setState(243);
        placeholder_domain();
        setState(244);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 11: {
      setState(248);
      booleanLayer();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(303);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(301);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(251);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(252);
          match(temporalParser::BAND);
          setState(253);
          sere(12);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(254);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(255);
          _la = _input->LA(1);
          if (!(((((_la - 26) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 26)) & 1125899906842627) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(256);
          sere(11);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(257);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(258);
          _la = _input->LA(1);
          if (!(((((_la - 28) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 28)) & 565148976676865) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(259);
          sere(9);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(260);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(261);
          match(temporalParser::DELAY);
          setState(263);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::LSQUARED) {
            setState(262);
            match(temporalParser::LSQUARED);
          }
          setState(266);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
          case 1: {
            setState(265);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(269);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::DOTS || _la == temporalParser::COL) {
            setState(268);
            _la = _input->LA(1);
            if (!(_la == temporalParser::DOTS || _la == temporalParser::COL)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
          }
          setState(272);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
          case 1: {
            setState(271);
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
          setState(275);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::RSQUARED) {
            setState(274);
            match(temporalParser::RSQUARED);
          }
          setState(277);
          sere(8);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(278);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(279);
          match(temporalParser::COL);
          setState(280);
          sere(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(281);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(282);
          match(temporalParser::SCOL);
          setState(283);
          sere(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(284);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(285);
          match(temporalParser::LSQUARED);
          setState(286);
          match(temporalParser::TIMES);
          setState(288);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
          case 1: {
            setState(287);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(291);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::DOTS || _la == temporalParser::COL) {
            setState(290);
            _la = _input->LA(1);
            if (!(_la == temporalParser::DOTS || _la == temporalParser::COL)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
          }
          setState(294);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalParser::UINTEGER

          || _la == temporalParser::DOLLAR) {
            setState(293);
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
          setState(296);
          match(temporalParser::RSQUARED);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(297);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(298);
          match(temporalParser::LSQUARED);
          setState(299);
          match(temporalParser::PLUS);
          setState(300);
          match(temporalParser::RSQUARED);
          break;
        }

        default:
          break;
        } 
      }
      setState(305);
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
    setState(322);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(306);
      match(temporalParser::LROUND);
      setState(307);
      booleanLayer();
      setState(308);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(310);
      boolean(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(312);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalParser::NOT) {
        setState(311);
        match(temporalParser::NOT);
      }
      setState(314);
      match(temporalParser::PLACEHOLDER);
      setState(319);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
      case 1: {
        setState(315);
        match(temporalParser::LROUND);
        setState(316);
        placeholder_domain();
        setState(317);
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
      setState(321);
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
    setState(361);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      setState(325);
      match(temporalParser::LROUND);
      setState(326);
      tformula(0);
      setState(327);
      match(temporalParser::RROUND);
      break;
    }

    case 2: {
      setState(329);

      if (!(canUseSharedOperator(safeTokenText(_input->LT(-1)),safeTokenText(_input->LT(2))))) throw FailedPredicateException(this, "canUseSharedOperator(safeTokenText(_input->LT(-1)),safeTokenText(_input->LT(2)))");
      setState(331);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
      case 1: {
        setState(330);
        match(temporalParser::LCURLY);
        break;
      }

      default:
        break;
      }
      setState(333);
      sere(0);
      setState(335);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
      case 1: {
        setState(334);
        match(temporalParser::RCURLY);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      setState(337);

      if (!(canTakeThisNot(safeTokenText(_input->LT(1)),safeTokenText(_input->LT(2))))) throw FailedPredicateException(this, "canTakeThisNot(safeTokenText(_input->LT(1)),safeTokenText(_input->LT(2)))");
      setState(338);
      _la = _input->LA(1);
      if (!(_la == temporalParser::TNOT

      || _la == temporalParser::NOT)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(339);
      tformula(8);
      break;
    }

    case 4: {
      setState(340);
      match(temporalParser::NEXT);
      setState(342);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
      case 1: {
        setState(341);
        match(temporalParser::LSQUARED);
        break;
      }

      default:
        break;
      }
      setState(345);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
      case 1: {
        setState(344);
        match(temporalParser::UINTEGER);
        break;
      }

      default:
        break;
      }
      setState(348);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
      case 1: {
        setState(347);
        match(temporalParser::RSQUARED);
        break;
      }

      default:
        break;
      }
      setState(350);
      tformula(7);
      break;
    }

    case 5: {
      setState(351);
      match(temporalParser::EVENTUALLY);
      setState(352);
      tformula(6);
      break;
    }

    case 6: {
      setState(353);
      match(temporalParser::DT_AND);
      setState(358);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
      case 1: {
        setState(354);
        match(temporalParser::LROUND);
        setState(355);
        placeholder_domain();
        setState(356);
        match(temporalParser::RROUND);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 7: {
      setState(360);
      booleanLayer();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(374);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(372);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(363);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(364);
          _la = _input->LA(1);
          if (!(_la == temporalParser::UNTIL

          || _la == temporalParser::RELEASE)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(365);
          tformula(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(366);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(367);
          _la = _input->LA(1);
          if (!(_la == temporalParser::TAND

          || _la == temporalParser::AND)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(368);
          tformula(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(369);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(370);
          _la = _input->LA(1);
          if (!(((((_la - 28) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 28)) & 565148976676865) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(371);
          tformula(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(376);
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
    setState(393);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::LROUND: {
        enterOuterAlt(_localctx, 1);
        setState(377);
        match(temporalParser::LROUND);
        setState(378);
        temporalFunction();
        setState(379);
        match(temporalParser::RROUND);
        break;
      }

      case temporalParser::FUNCTION: {
        enterOuterAlt(_localctx, 2);
        setState(381);
        match(temporalParser::FUNCTION);
        setState(382);
        match(temporalParser::LROUND);
        setState(383);
        tfunc_arg();
        setState(388);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == temporalParser::T__2) {
          setState(384);
          match(temporalParser::T__2);
          setState(385);
          tfunc_arg();
          setState(390);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(391);
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
    setState(403);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::PLACEHOLDER: {
        enterOuterAlt(_localctx, 1);
        setState(395);
        match(temporalParser::PLACEHOLDER);
        setState(400);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == temporalParser::LROUND) {
          setState(396);
          match(temporalParser::LROUND);
          setState(397);
          placeholder_domain();
          setState(398);
          match(temporalParser::RROUND);
        }
        break;
      }

      case temporalParser::UINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(402);
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
    setState(405);
    match(temporalParser::UINTEGER);
    setState(410);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == temporalParser::T__2) {
      setState(406);
      match(temporalParser::T__2);

      setState(407);
      match(temporalParser::UINTEGER);
      setState(412);
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
    setState(413);
    match(temporalParser::T__3);
    setState(414);
    match(temporalParser::UINTEGER);
    setState(415);
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
    setState(417);
    match(temporalParser::T__4);
    setState(418);
    match(temporalParser::UINTEGER);
    setState(419);
    match(temporalParser::BAND);
    setState(420);
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
    setState(422);
    match(temporalParser::T__5);
    setState(423);
    _la = _input->LA(1);
    if (!(_la == temporalParser::IMPLO

    || _la == temporalParser::ASS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(424);
    match(temporalParser::UINTEGER);
    setState(425);
    match(temporalParser::T__6);
    setState(426);
    _la = _input->LA(1);
    if (!(_la == temporalParser::SCOL

    || _la == temporalParser::COL)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(427);
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
    setState(431);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      setState(429);
      boolean(0);
      break;
    }

    case 2: {
      setState(430);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(433);
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
    setState(437);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      setState(435);
      numeric(0);
      break;
    }

    case 2: {
      setState(436);
      numericTernary();
      break;
    }

    default:
      break;
    }
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
    setState(443);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
    case 1: {
      setState(441);
      numeric(0);
      break;
    }

    case 2: {
      setState(442);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(445);
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
    setState(449);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      setState(447);
      numeric(0);
      break;
    }

    case 2: {
      setState(448);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(451);
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
    setState(453);
    string(0);
    setState(454);
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
    setState(456);
    boolean(0);
    setState(457);
    match(temporalParser::QUESTION);
    setState(460);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      setState(458);
      boolean(0);
      break;
    }

    case 2: {
      setState(459);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(462);
    match(temporalParser::COL);
    setState(465);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      setState(463);
      boolean(0);
      break;
    }

    case 2: {
      setState(464);
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
    setState(467);
    boolean(0);
    setState(468);
    match(temporalParser::QUESTION);
    setState(471);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      setState(469);
      numeric(0);
      break;
    }

    case 2: {
      setState(470);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(473);
    match(temporalParser::COL);
    setState(476);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      setState(474);
      numeric(0);
      break;
    }

    case 2: {
      setState(475);
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
    setState(504);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(479);
      booleanAtom();
      break;
    }

    case 2: {
      setState(480);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(481);
      string(0);
      setState(482);
      relop();
      setState(483);
      string(0);
      break;
    }

    case 4: {
      setState(485);
      string(0);
      setState(486);
      match(temporalParser::EQ);
      setState(487);
      string(0);
      break;
    }

    case 5: {
      setState(489);
      string(0);
      setState(490);
      match(temporalParser::NEQ);
      setState(491);
      string(0);
      break;
    }

    case 6: {
      setState(493);
      match(temporalParser::LROUND);
      setState(494);
      boolean(0);
      setState(495);
      match(temporalParser::RROUND);
      break;
    }

    case 7: {
      setState(497);
      numeric(0);
      break;
    }

    case 8: {
      setState(498);
      match(temporalParser::LROUND);
      setState(499);
      booleanTernary();
      setState(500);
      match(temporalParser::RROUND);
      break;
    }

    case 9: {
      setState(502);
      match(temporalParser::NOT);
      setState(503);
      boolean(4);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(517);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(515);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(506);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(507);
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
          setState(508);
          boolean(4);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(509);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(510);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(temporalParser::AND);
          setState(511);
          boolean(3);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(512);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(513);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(temporalParser::OR);
          setState(514);
          boolean(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(519);
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
    setState(520);
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
    setState(542);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
    case 1: {
      setState(523);
      antlrcpp::downCast<NumericContext *>(_localctx)->unop = _input->LT(1);
      _la = _input->LA(1);
      if (!(((((_la - 55) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 55)) & 8454147) != 0))) {
        antlrcpp::downCast<NumericContext *>(_localctx)->unop = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(524);
      numeric(18);
      break;
    }

    case 2: {
      setState(525);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(526);
      intAtom();
      break;
    }

    case 4: {
      setState(527);
      logicAtom();
      break;
    }

    case 5: {
      setState(528);
      floatAtom();
      break;
    }

    case 6: {
      setState(529);
      concatenation();
      break;
    }

    case 7: {
      setState(530);
      match(temporalParser::LROUND);
      setState(531);
      numeric(0);
      setState(532);
      match(temporalParser::RROUND);
      break;
    }

    case 8: {
      setState(534);
      match(temporalParser::LROUND);
      setState(535);
      numericTernary();
      setState(536);
      match(temporalParser::RROUND);
      break;
    }

    case 9: {
      setState(538);
      match(temporalParser::LROUND);
      setState(539);
      boolean(0);
      setState(540);
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
          setState(544);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(545);
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
          setState(546);
          numeric(17);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(547);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(548);
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
          setState(549);
          numeric(16);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(550);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(551);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 72) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 72)) & 15) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->logop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(552);
          numeric(15);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(553);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(554);
          relop();
          setState(555);
          numeric(14);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(557);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(558);
          antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _input->LT(1);
          _la = _input->LA(1);
          if (!(((((_la - 63) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 63)) & 15) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(559);
          numeric(12);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(560);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(561);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BAND);
          setState(562);
          numeric(11);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(563);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(564);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BXOR);
          setState(565);
          numeric(10);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(566);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(567);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(temporalParser::BOR);
          setState(568);
          numeric(9);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(569);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(570);
          range();
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(571);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(572);
          match(temporalParser::INSIDE);
          setState(573);
          match(temporalParser::LCURLY);
          setState(582);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(576);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case temporalParser::INT_VARIABLE:
                case temporalParser::LOGIC_VARIABLE:
                case temporalParser::BIT_VARIABLE:
                case temporalParser::FLOAT_CONSTANT:
                case temporalParser::FLOAT_VARIABLE:
                case temporalParser::LCURLY:
                case temporalParser::LROUND:
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
                  setState(574);
                  sm_constant();
                  break;
                }

                case temporalParser::LSQUARED: {
                  setState(575);
                  sm_range();
                  break;
                }

              default:
                throw NoViableAltException(this);
              }
              setState(578);
              match(temporalParser::T__2); 
            }
            setState(584);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
          }
          setState(587);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case temporalParser::INT_VARIABLE:
            case temporalParser::LOGIC_VARIABLE:
            case temporalParser::BIT_VARIABLE:
            case temporalParser::FLOAT_CONSTANT:
            case temporalParser::FLOAT_VARIABLE:
            case temporalParser::LCURLY:
            case temporalParser::LROUND:
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
              setState(585);
              sm_constant();
              break;
            }

            case temporalParser::LSQUARED: {
              setState(586);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(589);
          match(temporalParser::RCURLY);
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
      case temporalParser::BIT_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LCURLY:
      case temporalParser::LROUND:
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
    setState(626);
    match(temporalParser::LSQUARED);
    setState(627);
    match(temporalParser::UINTEGER);
    setState(630);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == temporalParser::COL) {
      setState(628);
      match(temporalParser::COL);
      setState(629);
      match(temporalParser::UINTEGER);
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
      case temporalParser::BIT_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LCURLY:
      case temporalParser::LROUND:
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
      case temporalParser::BIT_VARIABLE:
      case temporalParser::FLOAT_CONSTANT:
      case temporalParser::FLOAT_VARIABLE:
      case temporalParser::LCURLY:
      case temporalParser::LROUND:
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
    setState(662);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(656);
        match(temporalParser::GCC_BINARY);
        break;
      }

      case temporalParser::UINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(657);
        match(temporalParser::UINTEGER);
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

      case temporalParser::HEX: {
        enterOuterAlt(_localctx, 3);
        setState(661);
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
    setState(668);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(664);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(665);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(666);
      match(temporalParser::LOGIC_VARIABLE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(667);
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
    setState(675);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::UINTEGER:
      case temporalParser::VERILOG_BASED: {
        enterOuterAlt(_localctx, 1);
        setState(671);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == temporalParser::UINTEGER) {
          setState(670);
          match(temporalParser::UINTEGER);
        }
        setState(673);
        match(temporalParser::VERILOG_BASED);
        break;
      }

      case temporalParser::FILL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(674);
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
    setState(677);
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
    setState(685);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalParser::STRING_CONSTANT:
      case temporalParser::STRING_VARIABLE: {
        setState(680);
        stringAtom();
        break;
      }

      case temporalParser::LROUND: {
        setState(681);
        match(temporalParser::LROUND);
        setState(682);
        string(0);
        setState(683);
        match(temporalParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(702);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(700);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(687);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(688);
          match(temporalParser::PLUS);
          setState(689);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(690);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(691);
          match(temporalParser::SUBSTR);
          setState(692);
          match(temporalParser::LROUND);
          setState(697);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx)) {
          case 1: {
            setState(693);
            match(temporalParser::UINTEGER);
            setState(694);
            match(temporalParser::T__2);
            setState(695);
            match(temporalParser::UINTEGER);
            break;
          }

          case 2: {
            setState(696);
            match(temporalParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(699);
          match(temporalParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(704);
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
    setState(705);
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
    setState(707);
    match(temporalParser::FUNCTION);
    setState(708);
    match(temporalParser::LROUND);
    setState(709);
    pfunc_arg();
    setState(714);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == temporalParser::T__2) {
      setState(710);
      match(temporalParser::T__2);
      setState(711);
      pfunc_arg();
      setState(716);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(717);
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
    setState(721);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(719);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(720);
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
    setState(723);
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
    setState(725);
    _la = _input->LA(1);
    if (!(((((_la - 59) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 59)) & 8388639) != 0))) {
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
    case 24: return precpred(_ctx, 19);
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
