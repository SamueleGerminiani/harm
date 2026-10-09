
// Generated from proposition.g4 by ANTLR 4.13.2


#include "propositionListener.h"

#include "propositionParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct PropositionParserStaticData final {
  PropositionParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PropositionParserStaticData(const PropositionParserStaticData&) = delete;
  PropositionParserStaticData(PropositionParserStaticData&&) = delete;
  PropositionParserStaticData& operator=(const PropositionParserStaticData&) = delete;
  PropositionParserStaticData& operator=(PropositionParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag propositionParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<PropositionParserStaticData> propositionParserStaticData = nullptr;

void propositionParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (propositionParserStaticData != nullptr) {
    return;
  }
#else
  assert(propositionParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<PropositionParserStaticData>(
    std::vector<std::string>{
      "startBoolean", "startInt", "startLogic", "startFloat", "startString", 
      "booleanTernary", "numericTernary", "boolean", "booleanAtom", "numeric", 
      "concatenation", "concatItem", "range", "sm_range", "min_dollar", 
      "max_dollar", "sm_constant", "intAtom", "int_constant", "logicAtom", 
      "logic_constant", "floatAtom", "string", "stringAtom", "nonTemporalFunction", 
      "pfunc_arg", "relop", "cls_op"
    },
    std::vector<std::string>{
      "", "','", "", "", "", "", "", "", "", "", "'.substr'", "", "", "'{'", 
      "'}'", "'['", "']'", "'('", "')'", "'inside'", "", "", "", "", "", 
      "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", "'>='", "'<'", 
      "'<='", "'=='", "'!='", "'==='", "'!=='", "'\\u003F'", "'&'", "'|'", 
      "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'", "':'", "'::'", 
      "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", "INT_VARIABLE", "CONST_SUFFIX", 
      "LOGIC_VARIABLE", "BIT_VARIABLE", "FLOAT_CONSTANT", "FLOAT_VARIABLE", 
      "SUBSTR", "STRING_CONSTANT", "STRING_VARIABLE", "LCURLY", "RCURLY", 
      "LSQUARED", "RSQUARED", "LROUND", "RROUND", "INSIDE", "FUNCTION", 
      "SINTEGER", "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", "VERILOG_BASED", 
      "FILL_LITERAL", "SINGLE_QUOTE", "PLUS", "MINUS", "TIMES", "DIV", "GT", 
      "GE", "LT", "LE", "EQ", "NEQ", "CASE_EQ", "CASE_NEQ", "QUESTION", 
      "BAND", "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT", 
      "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,56,374,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,1,
  	0,3,0,59,8,0,1,0,1,0,1,1,1,1,3,1,65,8,1,1,1,1,1,1,2,1,2,3,2,71,8,2,1,
  	2,1,2,1,3,1,3,3,3,77,8,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,3,5,88,8,
  	5,1,5,1,5,1,5,3,5,93,8,5,1,6,1,6,1,6,1,6,3,6,99,8,6,1,6,1,6,1,6,3,6,104,
  	8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,115,8,7,1,7,1,7,5,7,119,8,
  	7,10,7,12,7,122,9,7,1,7,1,7,3,7,126,8,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,3,7,172,8,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,5,7,
  	186,8,7,10,7,12,7,189,9,7,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,209,8,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,5,9,234,
  	8,9,10,9,12,9,237,9,9,1,10,1,10,1,10,1,10,4,10,243,8,10,11,10,12,10,244,
  	1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,5,10,255,8,10,10,10,12,10,258,
  	9,10,1,10,1,10,1,10,3,10,263,8,10,1,11,1,11,3,11,267,8,11,1,12,1,12,1,
  	12,1,12,3,12,273,8,12,1,12,1,12,1,13,1,13,1,13,3,13,280,8,13,1,13,1,13,
  	1,13,3,13,285,8,13,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,
  	3,17,297,8,17,1,18,1,18,1,18,3,18,302,8,18,1,18,1,18,3,18,306,8,18,1,
  	18,3,18,309,8,18,1,19,1,19,1,19,1,19,3,19,315,8,19,1,20,3,20,318,8,20,
  	1,20,1,20,3,20,322,8,20,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,3,22,
  	332,8,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,344,8,
  	22,1,22,5,22,347,8,22,10,22,12,22,350,9,22,1,23,1,23,1,24,1,24,1,24,1,
  	24,1,24,5,24,359,8,24,10,24,12,24,362,9,24,1,24,1,24,1,25,1,25,3,25,368,
  	8,25,1,26,1,26,1,27,1,27,1,27,0,3,14,18,44,28,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,0,8,1,0,2,3,1,0,
  	31,32,1,0,29,30,1,0,21,22,1,0,8,9,1,0,11,12,1,0,33,36,2,0,33,37,54,54,
  	414,0,58,1,0,0,0,2,64,1,0,0,0,4,70,1,0,0,0,6,76,1,0,0,0,8,80,1,0,0,0,
  	10,83,1,0,0,0,12,94,1,0,0,0,14,171,1,0,0,0,16,190,1,0,0,0,18,208,1,0,
  	0,0,20,262,1,0,0,0,22,266,1,0,0,0,24,268,1,0,0,0,26,276,1,0,0,0,28,288,
  	1,0,0,0,30,290,1,0,0,0,32,292,1,0,0,0,34,296,1,0,0,0,36,308,1,0,0,0,38,
  	314,1,0,0,0,40,321,1,0,0,0,42,323,1,0,0,0,44,331,1,0,0,0,46,351,1,0,0,
  	0,48,353,1,0,0,0,50,367,1,0,0,0,52,369,1,0,0,0,54,371,1,0,0,0,56,59,3,
  	14,7,0,57,59,3,10,5,0,58,56,1,0,0,0,58,57,1,0,0,0,59,60,1,0,0,0,60,61,
  	5,0,0,1,61,1,1,0,0,0,62,65,3,18,9,0,63,65,3,12,6,0,64,62,1,0,0,0,64,63,
  	1,0,0,0,65,66,1,0,0,0,66,67,5,0,0,1,67,3,1,0,0,0,68,71,3,18,9,0,69,71,
  	3,12,6,0,70,68,1,0,0,0,70,69,1,0,0,0,71,72,1,0,0,0,72,73,5,0,0,1,73,5,
  	1,0,0,0,74,77,3,18,9,0,75,77,3,12,6,0,76,74,1,0,0,0,76,75,1,0,0,0,77,
  	78,1,0,0,0,78,79,5,0,0,1,79,7,1,0,0,0,80,81,3,44,22,0,81,82,5,0,0,1,82,
  	9,1,0,0,0,83,84,3,14,7,0,84,87,5,41,0,0,85,88,3,14,7,0,86,88,3,10,5,0,
  	87,85,1,0,0,0,87,86,1,0,0,0,88,89,1,0,0,0,89,92,5,51,0,0,90,93,3,14,7,
  	0,91,93,3,10,5,0,92,90,1,0,0,0,92,91,1,0,0,0,93,11,1,0,0,0,94,95,3,14,
  	7,0,95,98,5,41,0,0,96,99,3,18,9,0,97,99,3,12,6,0,98,96,1,0,0,0,98,97,
  	1,0,0,0,99,100,1,0,0,0,100,103,5,51,0,0,101,104,3,18,9,0,102,104,3,12,
  	6,0,103,101,1,0,0,0,103,102,1,0,0,0,104,13,1,0,0,0,105,106,6,7,-1,0,106,
  	107,5,50,0,0,107,172,3,14,7,19,108,172,3,48,24,0,109,110,3,18,9,0,110,
  	111,5,19,0,0,111,120,5,13,0,0,112,115,3,32,16,0,113,115,3,26,13,0,114,
  	112,1,0,0,0,114,113,1,0,0,0,115,116,1,0,0,0,116,117,5,1,0,0,117,119,1,
  	0,0,0,118,114,1,0,0,0,119,122,1,0,0,0,120,118,1,0,0,0,120,121,1,0,0,0,
  	121,125,1,0,0,0,122,120,1,0,0,0,123,126,3,32,16,0,124,126,3,26,13,0,125,
  	123,1,0,0,0,125,124,1,0,0,0,126,127,1,0,0,0,127,128,5,14,0,0,128,172,
  	1,0,0,0,129,130,3,18,9,0,130,131,3,52,26,0,131,132,3,18,9,0,132,172,1,
  	0,0,0,133,134,3,18,9,0,134,135,5,37,0,0,135,136,3,18,9,0,136,172,1,0,
  	0,0,137,138,3,18,9,0,138,139,5,38,0,0,139,140,3,18,9,0,140,172,1,0,0,
  	0,141,142,3,18,9,0,142,143,5,39,0,0,143,144,3,18,9,0,144,172,1,0,0,0,
  	145,146,3,18,9,0,146,147,5,40,0,0,147,148,3,18,9,0,148,172,1,0,0,0,149,
  	150,3,44,22,0,150,151,3,52,26,0,151,152,3,44,22,0,152,172,1,0,0,0,153,
  	154,3,44,22,0,154,155,5,37,0,0,155,156,3,44,22,0,156,172,1,0,0,0,157,
  	158,3,44,22,0,158,159,5,38,0,0,159,160,3,44,22,0,160,172,1,0,0,0,161,
  	172,3,16,8,0,162,172,3,18,9,0,163,164,5,17,0,0,164,165,3,14,7,0,165,166,
  	5,18,0,0,166,172,1,0,0,0,167,168,5,17,0,0,168,169,3,10,5,0,169,170,5,
  	18,0,0,170,172,1,0,0,0,171,105,1,0,0,0,171,108,1,0,0,0,171,109,1,0,0,
  	0,171,129,1,0,0,0,171,133,1,0,0,0,171,137,1,0,0,0,171,141,1,0,0,0,171,
  	145,1,0,0,0,171,149,1,0,0,0,171,153,1,0,0,0,171,157,1,0,0,0,171,161,1,
  	0,0,0,171,162,1,0,0,0,171,163,1,0,0,0,171,167,1,0,0,0,172,187,1,0,0,0,
  	173,174,10,8,0,0,174,175,5,37,0,0,175,186,3,14,7,9,176,177,10,7,0,0,177,
  	178,5,38,0,0,178,186,3,14,7,8,179,180,10,6,0,0,180,181,5,48,0,0,181,186,
  	3,14,7,7,182,183,10,5,0,0,183,184,5,49,0,0,184,186,3,14,7,6,185,173,1,
  	0,0,0,185,176,1,0,0,0,185,179,1,0,0,0,185,182,1,0,0,0,186,189,1,0,0,0,
  	187,185,1,0,0,0,187,188,1,0,0,0,188,15,1,0,0,0,189,187,1,0,0,0,190,191,
  	7,0,0,0,191,17,1,0,0,0,192,193,6,9,-1,0,193,194,5,45,0,0,194,209,3,18,
  	9,16,195,209,3,48,24,0,196,209,3,34,17,0,197,209,3,38,19,0,198,209,3,
  	42,21,0,199,209,3,20,10,0,200,201,5,17,0,0,201,202,3,18,9,0,202,203,5,
  	18,0,0,203,209,1,0,0,0,204,205,5,17,0,0,205,206,3,12,6,0,206,207,5,18,
  	0,0,207,209,1,0,0,0,208,192,1,0,0,0,208,195,1,0,0,0,208,196,1,0,0,0,208,
  	197,1,0,0,0,208,198,1,0,0,0,208,199,1,0,0,0,208,200,1,0,0,0,208,204,1,
  	0,0,0,209,235,1,0,0,0,210,211,10,13,0,0,211,212,7,1,0,0,212,234,3,18,
  	9,14,213,214,10,12,0,0,214,215,7,2,0,0,215,234,3,18,9,13,216,217,10,11,
  	0,0,217,218,5,46,0,0,218,234,3,18,9,12,219,220,10,10,0,0,220,221,5,47,
  	0,0,221,234,3,18,9,11,222,223,10,9,0,0,223,224,5,42,0,0,224,234,3,18,
  	9,10,225,226,10,8,0,0,226,227,5,44,0,0,227,234,3,18,9,9,228,229,10,7,
  	0,0,229,230,5,43,0,0,230,234,3,18,9,8,231,232,10,14,0,0,232,234,3,24,
  	12,0,233,210,1,0,0,0,233,213,1,0,0,0,233,216,1,0,0,0,233,219,1,0,0,0,
  	233,222,1,0,0,0,233,225,1,0,0,0,233,228,1,0,0,0,233,231,1,0,0,0,234,237,
  	1,0,0,0,235,233,1,0,0,0,235,236,1,0,0,0,236,19,1,0,0,0,237,235,1,0,0,
  	0,238,239,5,13,0,0,239,242,3,22,11,0,240,241,5,1,0,0,241,243,3,22,11,
  	0,242,240,1,0,0,0,243,244,1,0,0,0,244,242,1,0,0,0,244,245,1,0,0,0,245,
  	246,1,0,0,0,246,247,5,14,0,0,247,263,1,0,0,0,248,249,5,13,0,0,249,250,
  	5,22,0,0,250,251,5,13,0,0,251,256,3,22,11,0,252,253,5,1,0,0,253,255,3,
  	22,11,0,254,252,1,0,0,0,255,258,1,0,0,0,256,254,1,0,0,0,256,257,1,0,0,
  	0,257,259,1,0,0,0,258,256,1,0,0,0,259,260,5,14,0,0,260,261,5,14,0,0,261,
  	263,1,0,0,0,262,238,1,0,0,0,262,248,1,0,0,0,263,21,1,0,0,0,264,267,3,
  	18,9,0,265,267,3,16,8,0,266,264,1,0,0,0,266,265,1,0,0,0,267,23,1,0,0,
  	0,268,269,5,15,0,0,269,272,7,3,0,0,270,271,5,51,0,0,271,273,7,3,0,0,272,
  	270,1,0,0,0,272,273,1,0,0,0,273,274,1,0,0,0,274,275,5,16,0,0,275,25,1,
  	0,0,0,276,279,5,15,0,0,277,280,3,18,9,0,278,280,3,28,14,0,279,277,1,0,
  	0,0,279,278,1,0,0,0,280,281,1,0,0,0,281,284,5,51,0,0,282,285,3,18,9,0,
  	283,285,3,30,15,0,284,282,1,0,0,0,284,283,1,0,0,0,285,286,1,0,0,0,286,
  	287,5,16,0,0,287,27,1,0,0,0,288,289,5,53,0,0,289,29,1,0,0,0,290,291,5,
  	53,0,0,291,31,1,0,0,0,292,293,3,18,9,0,293,33,1,0,0,0,294,297,3,36,18,
  	0,295,297,5,4,0,0,296,294,1,0,0,0,296,295,1,0,0,0,297,35,1,0,0,0,298,
  	309,5,24,0,0,299,301,5,21,0,0,300,302,5,5,0,0,301,300,1,0,0,0,301,302,
  	1,0,0,0,302,309,1,0,0,0,303,305,5,22,0,0,304,306,5,5,0,0,305,304,1,0,
  	0,0,305,306,1,0,0,0,306,309,1,0,0,0,307,309,5,25,0,0,308,298,1,0,0,0,
  	308,299,1,0,0,0,308,303,1,0,0,0,308,307,1,0,0,0,309,37,1,0,0,0,310,315,
  	3,40,20,0,311,315,3,36,18,0,312,315,5,6,0,0,313,315,5,7,0,0,314,310,1,
  	0,0,0,314,311,1,0,0,0,314,312,1,0,0,0,314,313,1,0,0,0,315,39,1,0,0,0,
  	316,318,5,22,0,0,317,316,1,0,0,0,317,318,1,0,0,0,318,319,1,0,0,0,319,
  	322,5,26,0,0,320,322,5,27,0,0,321,317,1,0,0,0,321,320,1,0,0,0,322,41,
  	1,0,0,0,323,324,7,4,0,0,324,43,1,0,0,0,325,326,6,22,-1,0,326,332,3,46,
  	23,0,327,328,5,17,0,0,328,329,3,44,22,0,329,330,5,18,0,0,330,332,1,0,
  	0,0,331,325,1,0,0,0,331,327,1,0,0,0,332,348,1,0,0,0,333,334,10,4,0,0,
  	334,335,5,29,0,0,335,347,3,44,22,5,336,337,10,3,0,0,337,338,5,10,0,0,
  	338,343,5,17,0,0,339,340,5,22,0,0,340,341,5,1,0,0,341,344,5,22,0,0,342,
  	344,5,22,0,0,343,339,1,0,0,0,343,342,1,0,0,0,343,344,1,0,0,0,344,345,
  	1,0,0,0,345,347,5,18,0,0,346,333,1,0,0,0,346,336,1,0,0,0,347,350,1,0,
  	0,0,348,346,1,0,0,0,348,349,1,0,0,0,349,45,1,0,0,0,350,348,1,0,0,0,351,
  	352,7,5,0,0,352,47,1,0,0,0,353,354,5,20,0,0,354,355,5,17,0,0,355,360,
  	3,50,25,0,356,357,5,1,0,0,357,359,3,50,25,0,358,356,1,0,0,0,359,362,1,
  	0,0,0,360,358,1,0,0,0,360,361,1,0,0,0,361,363,1,0,0,0,362,360,1,0,0,0,
  	363,364,5,18,0,0,364,49,1,0,0,0,365,368,3,18,9,0,366,368,3,14,7,0,367,
  	365,1,0,0,0,367,366,1,0,0,0,368,51,1,0,0,0,369,370,7,6,0,0,370,53,1,0,
  	0,0,371,372,7,7,0,0,372,55,1,0,0,0,37,58,64,70,76,87,92,98,103,114,120,
  	125,171,185,187,208,233,235,244,256,262,266,272,279,284,296,301,305,308,
  	314,317,321,331,343,346,348,360,367
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  propositionParserStaticData = std::move(staticData);
}

}

propositionParser::propositionParser(TokenStream *input) : propositionParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

propositionParser::propositionParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  propositionParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *propositionParserStaticData->atn, propositionParserStaticData->decisionToDFA, propositionParserStaticData->sharedContextCache, options);
}

propositionParser::~propositionParser() {
  delete _interpreter;
}

const atn::ATN& propositionParser::getATN() const {
  return *propositionParserStaticData->atn;
}

std::string propositionParser::getGrammarFileName() const {
  return "proposition.g4";
}

const std::vector<std::string>& propositionParser::getRuleNames() const {
  return propositionParserStaticData->ruleNames;
}

const dfa::Vocabulary& propositionParser::getVocabulary() const {
  return propositionParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView propositionParser::getSerializedATN() const {
  return propositionParserStaticData->serializedATN;
}


//----------------- StartBooleanContext ------------------------------------------------------------------

propositionParser::StartBooleanContext::StartBooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::StartBooleanContext::EOF() {
  return getToken(propositionParser::EOF, 0);
}

propositionParser::BooleanContext* propositionParser::StartBooleanContext::boolean() {
  return getRuleContext<propositionParser::BooleanContext>(0);
}

propositionParser::BooleanTernaryContext* propositionParser::StartBooleanContext::booleanTernary() {
  return getRuleContext<propositionParser::BooleanTernaryContext>(0);
}


size_t propositionParser::StartBooleanContext::getRuleIndex() const {
  return propositionParser::RuleStartBoolean;
}

void propositionParser::StartBooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartBoolean(this);
}

void propositionParser::StartBooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartBoolean(this);
}

propositionParser::StartBooleanContext* propositionParser::startBoolean() {
  StartBooleanContext *_localctx = _tracker.createInstance<StartBooleanContext>(_ctx, getState());
  enterRule(_localctx, 0, propositionParser::RuleStartBoolean);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(56);
      boolean(0);
      break;
    }

    case 2: {
      setState(57);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(60);
    match(propositionParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartIntContext ------------------------------------------------------------------

propositionParser::StartIntContext::StartIntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::StartIntContext::EOF() {
  return getToken(propositionParser::EOF, 0);
}

propositionParser::NumericContext* propositionParser::StartIntContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}

propositionParser::NumericTernaryContext* propositionParser::StartIntContext::numericTernary() {
  return getRuleContext<propositionParser::NumericTernaryContext>(0);
}


size_t propositionParser::StartIntContext::getRuleIndex() const {
  return propositionParser::RuleStartInt;
}

void propositionParser::StartIntContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartInt(this);
}

void propositionParser::StartIntContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartInt(this);
}

propositionParser::StartIntContext* propositionParser::startInt() {
  StartIntContext *_localctx = _tracker.createInstance<StartIntContext>(_ctx, getState());
  enterRule(_localctx, 2, propositionParser::RuleStartInt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(62);
      numeric(0);
      break;
    }

    case 2: {
      setState(63);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(66);
    match(propositionParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartLogicContext ------------------------------------------------------------------

propositionParser::StartLogicContext::StartLogicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::StartLogicContext::EOF() {
  return getToken(propositionParser::EOF, 0);
}

propositionParser::NumericContext* propositionParser::StartLogicContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}

propositionParser::NumericTernaryContext* propositionParser::StartLogicContext::numericTernary() {
  return getRuleContext<propositionParser::NumericTernaryContext>(0);
}


size_t propositionParser::StartLogicContext::getRuleIndex() const {
  return propositionParser::RuleStartLogic;
}

void propositionParser::StartLogicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartLogic(this);
}

void propositionParser::StartLogicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartLogic(this);
}

propositionParser::StartLogicContext* propositionParser::startLogic() {
  StartLogicContext *_localctx = _tracker.createInstance<StartLogicContext>(_ctx, getState());
  enterRule(_localctx, 4, propositionParser::RuleStartLogic);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(70);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(68);
      numeric(0);
      break;
    }

    case 2: {
      setState(69);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(72);
    match(propositionParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartFloatContext ------------------------------------------------------------------

propositionParser::StartFloatContext::StartFloatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::StartFloatContext::EOF() {
  return getToken(propositionParser::EOF, 0);
}

propositionParser::NumericContext* propositionParser::StartFloatContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}

propositionParser::NumericTernaryContext* propositionParser::StartFloatContext::numericTernary() {
  return getRuleContext<propositionParser::NumericTernaryContext>(0);
}


size_t propositionParser::StartFloatContext::getRuleIndex() const {
  return propositionParser::RuleStartFloat;
}

void propositionParser::StartFloatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartFloat(this);
}

void propositionParser::StartFloatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartFloat(this);
}

propositionParser::StartFloatContext* propositionParser::startFloat() {
  StartFloatContext *_localctx = _tracker.createInstance<StartFloatContext>(_ctx, getState());
  enterRule(_localctx, 6, propositionParser::RuleStartFloat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(74);
      numeric(0);
      break;
    }

    case 2: {
      setState(75);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(78);
    match(propositionParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartStringContext ------------------------------------------------------------------

propositionParser::StartStringContext::StartStringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

propositionParser::StringContext* propositionParser::StartStringContext::string() {
  return getRuleContext<propositionParser::StringContext>(0);
}

tree::TerminalNode* propositionParser::StartStringContext::EOF() {
  return getToken(propositionParser::EOF, 0);
}


size_t propositionParser::StartStringContext::getRuleIndex() const {
  return propositionParser::RuleStartString;
}

void propositionParser::StartStringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartString(this);
}

void propositionParser::StartStringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartString(this);
}

propositionParser::StartStringContext* propositionParser::startString() {
  StartStringContext *_localctx = _tracker.createInstance<StartStringContext>(_ctx, getState());
  enterRule(_localctx, 8, propositionParser::RuleStartString);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    string(0);
    setState(81);
    match(propositionParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanTernaryContext ------------------------------------------------------------------

propositionParser::BooleanTernaryContext::BooleanTernaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<propositionParser::BooleanContext *> propositionParser::BooleanTernaryContext::boolean() {
  return getRuleContexts<propositionParser::BooleanContext>();
}

propositionParser::BooleanContext* propositionParser::BooleanTernaryContext::boolean(size_t i) {
  return getRuleContext<propositionParser::BooleanContext>(i);
}

tree::TerminalNode* propositionParser::BooleanTernaryContext::QUESTION() {
  return getToken(propositionParser::QUESTION, 0);
}

tree::TerminalNode* propositionParser::BooleanTernaryContext::COL() {
  return getToken(propositionParser::COL, 0);
}

std::vector<propositionParser::BooleanTernaryContext *> propositionParser::BooleanTernaryContext::booleanTernary() {
  return getRuleContexts<propositionParser::BooleanTernaryContext>();
}

propositionParser::BooleanTernaryContext* propositionParser::BooleanTernaryContext::booleanTernary(size_t i) {
  return getRuleContext<propositionParser::BooleanTernaryContext>(i);
}


size_t propositionParser::BooleanTernaryContext::getRuleIndex() const {
  return propositionParser::RuleBooleanTernary;
}

void propositionParser::BooleanTernaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanTernary(this);
}

void propositionParser::BooleanTernaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanTernary(this);
}

propositionParser::BooleanTernaryContext* propositionParser::booleanTernary() {
  BooleanTernaryContext *_localctx = _tracker.createInstance<BooleanTernaryContext>(_ctx, getState());
  enterRule(_localctx, 10, propositionParser::RuleBooleanTernary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    boolean(0);
    setState(84);
    match(propositionParser::QUESTION);
    setState(87);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(85);
      boolean(0);
      break;
    }

    case 2: {
      setState(86);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(89);
    match(propositionParser::COL);
    setState(92);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(90);
      boolean(0);
      break;
    }

    case 2: {
      setState(91);
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

propositionParser::NumericTernaryContext::NumericTernaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

propositionParser::BooleanContext* propositionParser::NumericTernaryContext::boolean() {
  return getRuleContext<propositionParser::BooleanContext>(0);
}

tree::TerminalNode* propositionParser::NumericTernaryContext::QUESTION() {
  return getToken(propositionParser::QUESTION, 0);
}

tree::TerminalNode* propositionParser::NumericTernaryContext::COL() {
  return getToken(propositionParser::COL, 0);
}

std::vector<propositionParser::NumericContext *> propositionParser::NumericTernaryContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::NumericTernaryContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
}

std::vector<propositionParser::NumericTernaryContext *> propositionParser::NumericTernaryContext::numericTernary() {
  return getRuleContexts<propositionParser::NumericTernaryContext>();
}

propositionParser::NumericTernaryContext* propositionParser::NumericTernaryContext::numericTernary(size_t i) {
  return getRuleContext<propositionParser::NumericTernaryContext>(i);
}


size_t propositionParser::NumericTernaryContext::getRuleIndex() const {
  return propositionParser::RuleNumericTernary;
}

void propositionParser::NumericTernaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericTernary(this);
}

void propositionParser::NumericTernaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericTernary(this);
}

propositionParser::NumericTernaryContext* propositionParser::numericTernary() {
  NumericTernaryContext *_localctx = _tracker.createInstance<NumericTernaryContext>(_ctx, getState());
  enterRule(_localctx, 12, propositionParser::RuleNumericTernary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    boolean(0);
    setState(95);
    match(propositionParser::QUESTION);
    setState(98);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(96);
      numeric(0);
      break;
    }

    case 2: {
      setState(97);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(100);
    match(propositionParser::COL);
    setState(103);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(101);
      numeric(0);
      break;
    }

    case 2: {
      setState(102);
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

propositionParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::BooleanContext::NOT() {
  return getToken(propositionParser::NOT, 0);
}

std::vector<propositionParser::BooleanContext *> propositionParser::BooleanContext::boolean() {
  return getRuleContexts<propositionParser::BooleanContext>();
}

propositionParser::BooleanContext* propositionParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<propositionParser::BooleanContext>(i);
}

propositionParser::NonTemporalFunctionContext* propositionParser::BooleanContext::nonTemporalFunction() {
  return getRuleContext<propositionParser::NonTemporalFunctionContext>(0);
}

std::vector<propositionParser::NumericContext *> propositionParser::BooleanContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
}

tree::TerminalNode* propositionParser::BooleanContext::INSIDE() {
  return getToken(propositionParser::INSIDE, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::LCURLY() {
  return getToken(propositionParser::LCURLY, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::RCURLY() {
  return getToken(propositionParser::RCURLY, 0);
}

std::vector<propositionParser::Sm_constantContext *> propositionParser::BooleanContext::sm_constant() {
  return getRuleContexts<propositionParser::Sm_constantContext>();
}

propositionParser::Sm_constantContext* propositionParser::BooleanContext::sm_constant(size_t i) {
  return getRuleContext<propositionParser::Sm_constantContext>(i);
}

std::vector<propositionParser::Sm_rangeContext *> propositionParser::BooleanContext::sm_range() {
  return getRuleContexts<propositionParser::Sm_rangeContext>();
}

propositionParser::Sm_rangeContext* propositionParser::BooleanContext::sm_range(size_t i) {
  return getRuleContext<propositionParser::Sm_rangeContext>(i);
}

propositionParser::RelopContext* propositionParser::BooleanContext::relop() {
  return getRuleContext<propositionParser::RelopContext>(0);
}

tree::TerminalNode* propositionParser::BooleanContext::EQ() {
  return getToken(propositionParser::EQ, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::NEQ() {
  return getToken(propositionParser::NEQ, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::CASE_EQ() {
  return getToken(propositionParser::CASE_EQ, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::CASE_NEQ() {
  return getToken(propositionParser::CASE_NEQ, 0);
}

std::vector<propositionParser::StringContext *> propositionParser::BooleanContext::string() {
  return getRuleContexts<propositionParser::StringContext>();
}

propositionParser::StringContext* propositionParser::BooleanContext::string(size_t i) {
  return getRuleContext<propositionParser::StringContext>(i);
}

propositionParser::BooleanAtomContext* propositionParser::BooleanContext::booleanAtom() {
  return getRuleContext<propositionParser::BooleanAtomContext>(0);
}

tree::TerminalNode* propositionParser::BooleanContext::LROUND() {
  return getToken(propositionParser::LROUND, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::RROUND() {
  return getToken(propositionParser::RROUND, 0);
}

propositionParser::BooleanTernaryContext* propositionParser::BooleanContext::booleanTernary() {
  return getRuleContext<propositionParser::BooleanTernaryContext>(0);
}

tree::TerminalNode* propositionParser::BooleanContext::AND() {
  return getToken(propositionParser::AND, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::OR() {
  return getToken(propositionParser::OR, 0);
}


size_t propositionParser::BooleanContext::getRuleIndex() const {
  return propositionParser::RuleBoolean;
}

void propositionParser::BooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolean(this);
}

void propositionParser::BooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolean(this);
}


propositionParser::BooleanContext* propositionParser::boolean() {
   return boolean(0);
}

propositionParser::BooleanContext* propositionParser::boolean(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  propositionParser::BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, parentState);
  propositionParser::BooleanContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, propositionParser::RuleBoolean, precedence);

    

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
    setState(171);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(106);
      match(propositionParser::NOT);
      setState(107);
      boolean(19);
      break;
    }

    case 2: {
      setState(108);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(109);
      numeric(0);
      setState(110);
      match(propositionParser::INSIDE);
      setState(111);
      match(propositionParser::LCURLY);
      setState(120);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(114);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case propositionParser::INT_VARIABLE:
            case propositionParser::LOGIC_VARIABLE:
            case propositionParser::BIT_VARIABLE:
            case propositionParser::FLOAT_CONSTANT:
            case propositionParser::FLOAT_VARIABLE:
            case propositionParser::LCURLY:
            case propositionParser::LROUND:
            case propositionParser::FUNCTION:
            case propositionParser::SINTEGER:
            case propositionParser::UINTEGER:
            case propositionParser::GCC_BINARY:
            case propositionParser::HEX:
            case propositionParser::VERILOG_BASED:
            case propositionParser::FILL_LITERAL:
            case propositionParser::NEG: {
              setState(112);
              sm_constant();
              break;
            }

            case propositionParser::LSQUARED: {
              setState(113);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(116);
          match(propositionParser::T__0); 
        }
        setState(122);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
      }
      setState(125);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case propositionParser::INT_VARIABLE:
        case propositionParser::LOGIC_VARIABLE:
        case propositionParser::BIT_VARIABLE:
        case propositionParser::FLOAT_CONSTANT:
        case propositionParser::FLOAT_VARIABLE:
        case propositionParser::LCURLY:
        case propositionParser::LROUND:
        case propositionParser::FUNCTION:
        case propositionParser::SINTEGER:
        case propositionParser::UINTEGER:
        case propositionParser::GCC_BINARY:
        case propositionParser::HEX:
        case propositionParser::VERILOG_BASED:
        case propositionParser::FILL_LITERAL:
        case propositionParser::NEG: {
          setState(123);
          sm_constant();
          break;
        }

        case propositionParser::LSQUARED: {
          setState(124);
          sm_range();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(127);
      match(propositionParser::RCURLY);
      break;
    }

    case 4: {
      setState(129);
      numeric(0);
      setState(130);
      relop();
      setState(131);
      numeric(0);
      break;
    }

    case 5: {
      setState(133);
      numeric(0);
      setState(134);
      match(propositionParser::EQ);
      setState(135);
      numeric(0);
      break;
    }

    case 6: {
      setState(137);
      numeric(0);
      setState(138);
      match(propositionParser::NEQ);
      setState(139);
      numeric(0);
      break;
    }

    case 7: {
      setState(141);
      numeric(0);
      setState(142);
      match(propositionParser::CASE_EQ);
      setState(143);
      numeric(0);
      break;
    }

    case 8: {
      setState(145);
      numeric(0);
      setState(146);
      match(propositionParser::CASE_NEQ);
      setState(147);
      numeric(0);
      break;
    }

    case 9: {
      setState(149);
      string(0);
      setState(150);
      relop();
      setState(151);
      string(0);
      break;
    }

    case 10: {
      setState(153);
      string(0);
      setState(154);
      match(propositionParser::EQ);
      setState(155);
      string(0);
      break;
    }

    case 11: {
      setState(157);
      string(0);
      setState(158);
      match(propositionParser::NEQ);
      setState(159);
      string(0);
      break;
    }

    case 12: {
      setState(161);
      booleanAtom();
      break;
    }

    case 13: {
      setState(162);
      numeric(0);
      break;
    }

    case 14: {
      setState(163);
      match(propositionParser::LROUND);
      setState(164);
      boolean(0);
      setState(165);
      match(propositionParser::RROUND);
      break;
    }

    case 15: {
      setState(167);
      match(propositionParser::LROUND);
      setState(168);
      booleanTernary();
      setState(169);
      match(propositionParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(187);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(185);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(173);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(174);
          match(propositionParser::EQ);
          setState(175);
          boolean(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(176);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(177);
          match(propositionParser::NEQ);
          setState(178);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(179);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(180);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::AND);
          setState(181);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(182);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(183);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::OR);
          setState(184);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(189);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
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

propositionParser::BooleanAtomContext::BooleanAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::BooleanAtomContext::BOOLEAN_CONSTANT() {
  return getToken(propositionParser::BOOLEAN_CONSTANT, 0);
}

tree::TerminalNode* propositionParser::BooleanAtomContext::BOOLEAN_VARIABLE() {
  return getToken(propositionParser::BOOLEAN_VARIABLE, 0);
}


size_t propositionParser::BooleanAtomContext::getRuleIndex() const {
  return propositionParser::RuleBooleanAtom;
}

void propositionParser::BooleanAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanAtom(this);
}

void propositionParser::BooleanAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanAtom(this);
}

propositionParser::BooleanAtomContext* propositionParser::booleanAtom() {
  BooleanAtomContext *_localctx = _tracker.createInstance<BooleanAtomContext>(_ctx, getState());
  enterRule(_localctx, 16, propositionParser::RuleBooleanAtom);
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
    setState(190);
    _la = _input->LA(1);
    if (!(_la == propositionParser::BOOLEAN_CONSTANT

    || _la == propositionParser::BOOLEAN_VARIABLE)) {
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

propositionParser::NumericContext::NumericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::NumericContext::NEG() {
  return getToken(propositionParser::NEG, 0);
}

std::vector<propositionParser::NumericContext *> propositionParser::NumericContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::NumericContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
}

propositionParser::NonTemporalFunctionContext* propositionParser::NumericContext::nonTemporalFunction() {
  return getRuleContext<propositionParser::NonTemporalFunctionContext>(0);
}

propositionParser::IntAtomContext* propositionParser::NumericContext::intAtom() {
  return getRuleContext<propositionParser::IntAtomContext>(0);
}

propositionParser::LogicAtomContext* propositionParser::NumericContext::logicAtom() {
  return getRuleContext<propositionParser::LogicAtomContext>(0);
}

propositionParser::FloatAtomContext* propositionParser::NumericContext::floatAtom() {
  return getRuleContext<propositionParser::FloatAtomContext>(0);
}

propositionParser::ConcatenationContext* propositionParser::NumericContext::concatenation() {
  return getRuleContext<propositionParser::ConcatenationContext>(0);
}

tree::TerminalNode* propositionParser::NumericContext::LROUND() {
  return getToken(propositionParser::LROUND, 0);
}

tree::TerminalNode* propositionParser::NumericContext::RROUND() {
  return getToken(propositionParser::RROUND, 0);
}

propositionParser::NumericTernaryContext* propositionParser::NumericContext::numericTernary() {
  return getRuleContext<propositionParser::NumericTernaryContext>(0);
}

tree::TerminalNode* propositionParser::NumericContext::TIMES() {
  return getToken(propositionParser::TIMES, 0);
}

tree::TerminalNode* propositionParser::NumericContext::DIV() {
  return getToken(propositionParser::DIV, 0);
}

tree::TerminalNode* propositionParser::NumericContext::PLUS() {
  return getToken(propositionParser::PLUS, 0);
}

tree::TerminalNode* propositionParser::NumericContext::MINUS() {
  return getToken(propositionParser::MINUS, 0);
}

tree::TerminalNode* propositionParser::NumericContext::LSHIFT() {
  return getToken(propositionParser::LSHIFT, 0);
}

tree::TerminalNode* propositionParser::NumericContext::RSHIFT() {
  return getToken(propositionParser::RSHIFT, 0);
}

tree::TerminalNode* propositionParser::NumericContext::BAND() {
  return getToken(propositionParser::BAND, 0);
}

tree::TerminalNode* propositionParser::NumericContext::BXOR() {
  return getToken(propositionParser::BXOR, 0);
}

tree::TerminalNode* propositionParser::NumericContext::BOR() {
  return getToken(propositionParser::BOR, 0);
}

propositionParser::RangeContext* propositionParser::NumericContext::range() {
  return getRuleContext<propositionParser::RangeContext>(0);
}


size_t propositionParser::NumericContext::getRuleIndex() const {
  return propositionParser::RuleNumeric;
}

void propositionParser::NumericContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void propositionParser::NumericContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}


propositionParser::NumericContext* propositionParser::numeric() {
   return numeric(0);
}

propositionParser::NumericContext* propositionParser::numeric(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  propositionParser::NumericContext *_localctx = _tracker.createInstance<NumericContext>(_ctx, parentState);
  propositionParser::NumericContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, propositionParser::RuleNumeric, precedence);

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
    setState(208);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      setState(193);
      match(propositionParser::NEG);
      setState(194);
      numeric(16);
      break;
    }

    case 2: {
      setState(195);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(196);
      intAtom();
      break;
    }

    case 4: {
      setState(197);
      logicAtom();
      break;
    }

    case 5: {
      setState(198);
      floatAtom();
      break;
    }

    case 6: {
      setState(199);
      concatenation();
      break;
    }

    case 7: {
      setState(200);
      match(propositionParser::LROUND);
      setState(201);
      numeric(0);
      setState(202);
      match(propositionParser::RROUND);
      break;
    }

    case 8: {
      setState(204);
      match(propositionParser::LROUND);
      setState(205);
      numericTernary();
      setState(206);
      match(propositionParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(235);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(233);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(210);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(211);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::TIMES

          || _la == propositionParser::DIV)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(212);
          numeric(14);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(213);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(214);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::PLUS

          || _la == propositionParser::MINUS)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(215);
          numeric(13);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(216);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(217);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::LSHIFT);
          setState(218);
          numeric(12);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(219);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(220);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::RSHIFT);
          setState(221);
          numeric(11);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(222);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(223);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BAND);
          setState(224);
          numeric(10);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(225);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(226);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BXOR);
          setState(227);
          numeric(9);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(228);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(229);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BOR);
          setState(230);
          numeric(8);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(231);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(232);
          range();
          break;
        }

        default:
          break;
        } 
      }
      setState(237);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
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

propositionParser::ConcatenationContext::ConcatenationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> propositionParser::ConcatenationContext::LCURLY() {
  return getTokens(propositionParser::LCURLY);
}

tree::TerminalNode* propositionParser::ConcatenationContext::LCURLY(size_t i) {
  return getToken(propositionParser::LCURLY, i);
}

std::vector<propositionParser::ConcatItemContext *> propositionParser::ConcatenationContext::concatItem() {
  return getRuleContexts<propositionParser::ConcatItemContext>();
}

propositionParser::ConcatItemContext* propositionParser::ConcatenationContext::concatItem(size_t i) {
  return getRuleContext<propositionParser::ConcatItemContext>(i);
}

std::vector<tree::TerminalNode *> propositionParser::ConcatenationContext::RCURLY() {
  return getTokens(propositionParser::RCURLY);
}

tree::TerminalNode* propositionParser::ConcatenationContext::RCURLY(size_t i) {
  return getToken(propositionParser::RCURLY, i);
}

tree::TerminalNode* propositionParser::ConcatenationContext::UINTEGER() {
  return getToken(propositionParser::UINTEGER, 0);
}


size_t propositionParser::ConcatenationContext::getRuleIndex() const {
  return propositionParser::RuleConcatenation;
}

void propositionParser::ConcatenationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConcatenation(this);
}

void propositionParser::ConcatenationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConcatenation(this);
}

propositionParser::ConcatenationContext* propositionParser::concatenation() {
  ConcatenationContext *_localctx = _tracker.createInstance<ConcatenationContext>(_ctx, getState());
  enterRule(_localctx, 20, propositionParser::RuleConcatenation);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(262);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(238);
      match(propositionParser::LCURLY);
      setState(239);
      concatItem();
      setState(242); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(240);
        match(propositionParser::T__0);
        setState(241);
        concatItem();
        setState(244); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == propositionParser::T__0);
      setState(246);
      match(propositionParser::RCURLY);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(248);
      match(propositionParser::LCURLY);
      setState(249);
      match(propositionParser::UINTEGER);
      setState(250);
      match(propositionParser::LCURLY);
      setState(251);
      concatItem();
      setState(256);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == propositionParser::T__0) {
        setState(252);
        match(propositionParser::T__0);
        setState(253);
        concatItem();
        setState(258);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(259);
      match(propositionParser::RCURLY);
      setState(260);
      match(propositionParser::RCURLY);
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

propositionParser::ConcatItemContext::ConcatItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

propositionParser::NumericContext* propositionParser::ConcatItemContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}

propositionParser::BooleanAtomContext* propositionParser::ConcatItemContext::booleanAtom() {
  return getRuleContext<propositionParser::BooleanAtomContext>(0);
}


size_t propositionParser::ConcatItemContext::getRuleIndex() const {
  return propositionParser::RuleConcatItem;
}

void propositionParser::ConcatItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConcatItem(this);
}

void propositionParser::ConcatItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConcatItem(this);
}

propositionParser::ConcatItemContext* propositionParser::concatItem() {
  ConcatItemContext *_localctx = _tracker.createInstance<ConcatItemContext>(_ctx, getState());
  enterRule(_localctx, 22, propositionParser::RuleConcatItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(266);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::INT_VARIABLE:
      case propositionParser::LOGIC_VARIABLE:
      case propositionParser::BIT_VARIABLE:
      case propositionParser::FLOAT_CONSTANT:
      case propositionParser::FLOAT_VARIABLE:
      case propositionParser::LCURLY:
      case propositionParser::LROUND:
      case propositionParser::FUNCTION:
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BASED:
      case propositionParser::FILL_LITERAL:
      case propositionParser::NEG: {
        enterOuterAlt(_localctx, 1);
        setState(264);
        numeric(0);
        break;
      }

      case propositionParser::BOOLEAN_CONSTANT:
      case propositionParser::BOOLEAN_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(265);
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

propositionParser::RangeContext::RangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::RangeContext::LSQUARED() {
  return getToken(propositionParser::LSQUARED, 0);
}

tree::TerminalNode* propositionParser::RangeContext::RSQUARED() {
  return getToken(propositionParser::RSQUARED, 0);
}

std::vector<tree::TerminalNode *> propositionParser::RangeContext::SINTEGER() {
  return getTokens(propositionParser::SINTEGER);
}

tree::TerminalNode* propositionParser::RangeContext::SINTEGER(size_t i) {
  return getToken(propositionParser::SINTEGER, i);
}

std::vector<tree::TerminalNode *> propositionParser::RangeContext::UINTEGER() {
  return getTokens(propositionParser::UINTEGER);
}

tree::TerminalNode* propositionParser::RangeContext::UINTEGER(size_t i) {
  return getToken(propositionParser::UINTEGER, i);
}

tree::TerminalNode* propositionParser::RangeContext::COL() {
  return getToken(propositionParser::COL, 0);
}


size_t propositionParser::RangeContext::getRuleIndex() const {
  return propositionParser::RuleRange;
}

void propositionParser::RangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRange(this);
}

void propositionParser::RangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRange(this);
}

propositionParser::RangeContext* propositionParser::range() {
  RangeContext *_localctx = _tracker.createInstance<RangeContext>(_ctx, getState());
  enterRule(_localctx, 24, propositionParser::RuleRange);
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
    setState(268);
    match(propositionParser::LSQUARED);
    setState(269);
    _la = _input->LA(1);
    if (!(_la == propositionParser::SINTEGER

    || _la == propositionParser::UINTEGER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(272);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == propositionParser::COL) {
      setState(270);
      match(propositionParser::COL);
      setState(271);
      _la = _input->LA(1);
      if (!(_la == propositionParser::SINTEGER

      || _la == propositionParser::UINTEGER)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(274);
    match(propositionParser::RSQUARED);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sm_rangeContext ------------------------------------------------------------------

propositionParser::Sm_rangeContext::Sm_rangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::Sm_rangeContext::LSQUARED() {
  return getToken(propositionParser::LSQUARED, 0);
}

tree::TerminalNode* propositionParser::Sm_rangeContext::COL() {
  return getToken(propositionParser::COL, 0);
}

tree::TerminalNode* propositionParser::Sm_rangeContext::RSQUARED() {
  return getToken(propositionParser::RSQUARED, 0);
}

std::vector<propositionParser::NumericContext *> propositionParser::Sm_rangeContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::Sm_rangeContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
}

propositionParser::Min_dollarContext* propositionParser::Sm_rangeContext::min_dollar() {
  return getRuleContext<propositionParser::Min_dollarContext>(0);
}

propositionParser::Max_dollarContext* propositionParser::Sm_rangeContext::max_dollar() {
  return getRuleContext<propositionParser::Max_dollarContext>(0);
}


size_t propositionParser::Sm_rangeContext::getRuleIndex() const {
  return propositionParser::RuleSm_range;
}

void propositionParser::Sm_rangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSm_range(this);
}

void propositionParser::Sm_rangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSm_range(this);
}

propositionParser::Sm_rangeContext* propositionParser::sm_range() {
  Sm_rangeContext *_localctx = _tracker.createInstance<Sm_rangeContext>(_ctx, getState());
  enterRule(_localctx, 26, propositionParser::RuleSm_range);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(276);
    match(propositionParser::LSQUARED);
    setState(279);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::INT_VARIABLE:
      case propositionParser::LOGIC_VARIABLE:
      case propositionParser::BIT_VARIABLE:
      case propositionParser::FLOAT_CONSTANT:
      case propositionParser::FLOAT_VARIABLE:
      case propositionParser::LCURLY:
      case propositionParser::LROUND:
      case propositionParser::FUNCTION:
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BASED:
      case propositionParser::FILL_LITERAL:
      case propositionParser::NEG: {
        setState(277);
        numeric(0);
        break;
      }

      case propositionParser::DOLLAR: {
        setState(278);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(281);
    match(propositionParser::COL);
    setState(284);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::INT_VARIABLE:
      case propositionParser::LOGIC_VARIABLE:
      case propositionParser::BIT_VARIABLE:
      case propositionParser::FLOAT_CONSTANT:
      case propositionParser::FLOAT_VARIABLE:
      case propositionParser::LCURLY:
      case propositionParser::LROUND:
      case propositionParser::FUNCTION:
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BASED:
      case propositionParser::FILL_LITERAL:
      case propositionParser::NEG: {
        setState(282);
        numeric(0);
        break;
      }

      case propositionParser::DOLLAR: {
        setState(283);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(286);
    match(propositionParser::RSQUARED);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Min_dollarContext ------------------------------------------------------------------

propositionParser::Min_dollarContext::Min_dollarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::Min_dollarContext::DOLLAR() {
  return getToken(propositionParser::DOLLAR, 0);
}


size_t propositionParser::Min_dollarContext::getRuleIndex() const {
  return propositionParser::RuleMin_dollar;
}

void propositionParser::Min_dollarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMin_dollar(this);
}

void propositionParser::Min_dollarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMin_dollar(this);
}

propositionParser::Min_dollarContext* propositionParser::min_dollar() {
  Min_dollarContext *_localctx = _tracker.createInstance<Min_dollarContext>(_ctx, getState());
  enterRule(_localctx, 28, propositionParser::RuleMin_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(288);
    match(propositionParser::DOLLAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Max_dollarContext ------------------------------------------------------------------

propositionParser::Max_dollarContext::Max_dollarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::Max_dollarContext::DOLLAR() {
  return getToken(propositionParser::DOLLAR, 0);
}


size_t propositionParser::Max_dollarContext::getRuleIndex() const {
  return propositionParser::RuleMax_dollar;
}

void propositionParser::Max_dollarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMax_dollar(this);
}

void propositionParser::Max_dollarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMax_dollar(this);
}

propositionParser::Max_dollarContext* propositionParser::max_dollar() {
  Max_dollarContext *_localctx = _tracker.createInstance<Max_dollarContext>(_ctx, getState());
  enterRule(_localctx, 30, propositionParser::RuleMax_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(290);
    match(propositionParser::DOLLAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sm_constantContext ------------------------------------------------------------------

propositionParser::Sm_constantContext::Sm_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

propositionParser::NumericContext* propositionParser::Sm_constantContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}


size_t propositionParser::Sm_constantContext::getRuleIndex() const {
  return propositionParser::RuleSm_constant;
}

void propositionParser::Sm_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSm_constant(this);
}

void propositionParser::Sm_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSm_constant(this);
}

propositionParser::Sm_constantContext* propositionParser::sm_constant() {
  Sm_constantContext *_localctx = _tracker.createInstance<Sm_constantContext>(_ctx, getState());
  enterRule(_localctx, 32, propositionParser::RuleSm_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(292);
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

propositionParser::IntAtomContext::IntAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

propositionParser::Int_constantContext* propositionParser::IntAtomContext::int_constant() {
  return getRuleContext<propositionParser::Int_constantContext>(0);
}

tree::TerminalNode* propositionParser::IntAtomContext::INT_VARIABLE() {
  return getToken(propositionParser::INT_VARIABLE, 0);
}


size_t propositionParser::IntAtomContext::getRuleIndex() const {
  return propositionParser::RuleIntAtom;
}

void propositionParser::IntAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntAtom(this);
}

void propositionParser::IntAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntAtom(this);
}

propositionParser::IntAtomContext* propositionParser::intAtom() {
  IntAtomContext *_localctx = _tracker.createInstance<IntAtomContext>(_ctx, getState());
  enterRule(_localctx, 34, propositionParser::RuleIntAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(296);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(294);
        int_constant();
        break;
      }

      case propositionParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(295);
        match(propositionParser::INT_VARIABLE);
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

propositionParser::Int_constantContext::Int_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::Int_constantContext::GCC_BINARY() {
  return getToken(propositionParser::GCC_BINARY, 0);
}

tree::TerminalNode* propositionParser::Int_constantContext::SINTEGER() {
  return getToken(propositionParser::SINTEGER, 0);
}

tree::TerminalNode* propositionParser::Int_constantContext::CONST_SUFFIX() {
  return getToken(propositionParser::CONST_SUFFIX, 0);
}

tree::TerminalNode* propositionParser::Int_constantContext::UINTEGER() {
  return getToken(propositionParser::UINTEGER, 0);
}

tree::TerminalNode* propositionParser::Int_constantContext::HEX() {
  return getToken(propositionParser::HEX, 0);
}


size_t propositionParser::Int_constantContext::getRuleIndex() const {
  return propositionParser::RuleInt_constant;
}

void propositionParser::Int_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInt_constant(this);
}

void propositionParser::Int_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInt_constant(this);
}

propositionParser::Int_constantContext* propositionParser::int_constant() {
  Int_constantContext *_localctx = _tracker.createInstance<Int_constantContext>(_ctx, getState());
  enterRule(_localctx, 36, propositionParser::RuleInt_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(308);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(298);
        match(propositionParser::GCC_BINARY);
        break;
      }

      case propositionParser::SINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(299);
        match(propositionParser::SINTEGER);
        setState(301);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
        case 1: {
          setState(300);
          match(propositionParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case propositionParser::UINTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(303);
        match(propositionParser::UINTEGER);
        setState(305);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          setState(304);
          match(propositionParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 4);
        setState(307);
        match(propositionParser::HEX);
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

propositionParser::LogicAtomContext::LogicAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

propositionParser::Logic_constantContext* propositionParser::LogicAtomContext::logic_constant() {
  return getRuleContext<propositionParser::Logic_constantContext>(0);
}

propositionParser::Int_constantContext* propositionParser::LogicAtomContext::int_constant() {
  return getRuleContext<propositionParser::Int_constantContext>(0);
}

tree::TerminalNode* propositionParser::LogicAtomContext::LOGIC_VARIABLE() {
  return getToken(propositionParser::LOGIC_VARIABLE, 0);
}

tree::TerminalNode* propositionParser::LogicAtomContext::BIT_VARIABLE() {
  return getToken(propositionParser::BIT_VARIABLE, 0);
}


size_t propositionParser::LogicAtomContext::getRuleIndex() const {
  return propositionParser::RuleLogicAtom;
}

void propositionParser::LogicAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicAtom(this);
}

void propositionParser::LogicAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicAtom(this);
}

propositionParser::LogicAtomContext* propositionParser::logicAtom() {
  LogicAtomContext *_localctx = _tracker.createInstance<LogicAtomContext>(_ctx, getState());
  enterRule(_localctx, 38, propositionParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(314);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(310);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(311);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(312);
      match(propositionParser::LOGIC_VARIABLE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(313);
      match(propositionParser::BIT_VARIABLE);
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

propositionParser::Logic_constantContext::Logic_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::Logic_constantContext::VERILOG_BASED() {
  return getToken(propositionParser::VERILOG_BASED, 0);
}

tree::TerminalNode* propositionParser::Logic_constantContext::UINTEGER() {
  return getToken(propositionParser::UINTEGER, 0);
}

tree::TerminalNode* propositionParser::Logic_constantContext::FILL_LITERAL() {
  return getToken(propositionParser::FILL_LITERAL, 0);
}


size_t propositionParser::Logic_constantContext::getRuleIndex() const {
  return propositionParser::RuleLogic_constant;
}

void propositionParser::Logic_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic_constant(this);
}

void propositionParser::Logic_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic_constant(this);
}

propositionParser::Logic_constantContext* propositionParser::logic_constant() {
  Logic_constantContext *_localctx = _tracker.createInstance<Logic_constantContext>(_ctx, getState());
  enterRule(_localctx, 40, propositionParser::RuleLogic_constant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(321);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::UINTEGER:
      case propositionParser::VERILOG_BASED: {
        enterOuterAlt(_localctx, 1);
        setState(317);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == propositionParser::UINTEGER) {
          setState(316);
          match(propositionParser::UINTEGER);
        }
        setState(319);
        match(propositionParser::VERILOG_BASED);
        break;
      }

      case propositionParser::FILL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(320);
        match(propositionParser::FILL_LITERAL);
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

propositionParser::FloatAtomContext::FloatAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::FloatAtomContext::FLOAT_CONSTANT() {
  return getToken(propositionParser::FLOAT_CONSTANT, 0);
}

tree::TerminalNode* propositionParser::FloatAtomContext::FLOAT_VARIABLE() {
  return getToken(propositionParser::FLOAT_VARIABLE, 0);
}


size_t propositionParser::FloatAtomContext::getRuleIndex() const {
  return propositionParser::RuleFloatAtom;
}

void propositionParser::FloatAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloatAtom(this);
}

void propositionParser::FloatAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloatAtom(this);
}

propositionParser::FloatAtomContext* propositionParser::floatAtom() {
  FloatAtomContext *_localctx = _tracker.createInstance<FloatAtomContext>(_ctx, getState());
  enterRule(_localctx, 42, propositionParser::RuleFloatAtom);
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
    setState(323);
    _la = _input->LA(1);
    if (!(_la == propositionParser::FLOAT_CONSTANT

    || _la == propositionParser::FLOAT_VARIABLE)) {
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

propositionParser::StringContext::StringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

propositionParser::StringAtomContext* propositionParser::StringContext::stringAtom() {
  return getRuleContext<propositionParser::StringAtomContext>(0);
}

tree::TerminalNode* propositionParser::StringContext::LROUND() {
  return getToken(propositionParser::LROUND, 0);
}

std::vector<propositionParser::StringContext *> propositionParser::StringContext::string() {
  return getRuleContexts<propositionParser::StringContext>();
}

propositionParser::StringContext* propositionParser::StringContext::string(size_t i) {
  return getRuleContext<propositionParser::StringContext>(i);
}

tree::TerminalNode* propositionParser::StringContext::RROUND() {
  return getToken(propositionParser::RROUND, 0);
}

tree::TerminalNode* propositionParser::StringContext::PLUS() {
  return getToken(propositionParser::PLUS, 0);
}

tree::TerminalNode* propositionParser::StringContext::SUBSTR() {
  return getToken(propositionParser::SUBSTR, 0);
}

std::vector<tree::TerminalNode *> propositionParser::StringContext::UINTEGER() {
  return getTokens(propositionParser::UINTEGER);
}

tree::TerminalNode* propositionParser::StringContext::UINTEGER(size_t i) {
  return getToken(propositionParser::UINTEGER, i);
}


size_t propositionParser::StringContext::getRuleIndex() const {
  return propositionParser::RuleString;
}

void propositionParser::StringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterString(this);
}

void propositionParser::StringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitString(this);
}


propositionParser::StringContext* propositionParser::string() {
   return string(0);
}

propositionParser::StringContext* propositionParser::string(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  propositionParser::StringContext *_localctx = _tracker.createInstance<StringContext>(_ctx, parentState);
  propositionParser::StringContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 44;
  enterRecursionRule(_localctx, 44, propositionParser::RuleString, precedence);

    

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
    setState(331);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::STRING_CONSTANT:
      case propositionParser::STRING_VARIABLE: {
        setState(326);
        stringAtom();
        break;
      }

      case propositionParser::LROUND: {
        setState(327);
        match(propositionParser::LROUND);
        setState(328);
        string(0);
        setState(329);
        match(propositionParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(348);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(346);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(333);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(334);
          match(propositionParser::PLUS);
          setState(335);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(336);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(337);
          match(propositionParser::SUBSTR);
          setState(338);
          match(propositionParser::LROUND);
          setState(343);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
          case 1: {
            setState(339);
            match(propositionParser::UINTEGER);
            setState(340);
            match(propositionParser::T__0);
            setState(341);
            match(propositionParser::UINTEGER);
            break;
          }

          case 2: {
            setState(342);
            match(propositionParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(345);
          match(propositionParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(350);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
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

propositionParser::StringAtomContext::StringAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::StringAtomContext::STRING_CONSTANT() {
  return getToken(propositionParser::STRING_CONSTANT, 0);
}

tree::TerminalNode* propositionParser::StringAtomContext::STRING_VARIABLE() {
  return getToken(propositionParser::STRING_VARIABLE, 0);
}


size_t propositionParser::StringAtomContext::getRuleIndex() const {
  return propositionParser::RuleStringAtom;
}

void propositionParser::StringAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringAtom(this);
}

void propositionParser::StringAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringAtom(this);
}

propositionParser::StringAtomContext* propositionParser::stringAtom() {
  StringAtomContext *_localctx = _tracker.createInstance<StringAtomContext>(_ctx, getState());
  enterRule(_localctx, 46, propositionParser::RuleStringAtom);
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
    setState(351);
    _la = _input->LA(1);
    if (!(_la == propositionParser::STRING_CONSTANT

    || _la == propositionParser::STRING_VARIABLE)) {
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

propositionParser::NonTemporalFunctionContext::NonTemporalFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::NonTemporalFunctionContext::FUNCTION() {
  return getToken(propositionParser::FUNCTION, 0);
}

tree::TerminalNode* propositionParser::NonTemporalFunctionContext::LROUND() {
  return getToken(propositionParser::LROUND, 0);
}

std::vector<propositionParser::Pfunc_argContext *> propositionParser::NonTemporalFunctionContext::pfunc_arg() {
  return getRuleContexts<propositionParser::Pfunc_argContext>();
}

propositionParser::Pfunc_argContext* propositionParser::NonTemporalFunctionContext::pfunc_arg(size_t i) {
  return getRuleContext<propositionParser::Pfunc_argContext>(i);
}

tree::TerminalNode* propositionParser::NonTemporalFunctionContext::RROUND() {
  return getToken(propositionParser::RROUND, 0);
}


size_t propositionParser::NonTemporalFunctionContext::getRuleIndex() const {
  return propositionParser::RuleNonTemporalFunction;
}

void propositionParser::NonTemporalFunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNonTemporalFunction(this);
}

void propositionParser::NonTemporalFunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNonTemporalFunction(this);
}

propositionParser::NonTemporalFunctionContext* propositionParser::nonTemporalFunction() {
  NonTemporalFunctionContext *_localctx = _tracker.createInstance<NonTemporalFunctionContext>(_ctx, getState());
  enterRule(_localctx, 48, propositionParser::RuleNonTemporalFunction);
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
    setState(353);
    match(propositionParser::FUNCTION);
    setState(354);
    match(propositionParser::LROUND);
    setState(355);
    pfunc_arg();
    setState(360);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == propositionParser::T__0) {
      setState(356);
      match(propositionParser::T__0);
      setState(357);
      pfunc_arg();
      setState(362);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(363);
    match(propositionParser::RROUND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pfunc_argContext ------------------------------------------------------------------

propositionParser::Pfunc_argContext::Pfunc_argContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

propositionParser::NumericContext* propositionParser::Pfunc_argContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}

propositionParser::BooleanContext* propositionParser::Pfunc_argContext::boolean() {
  return getRuleContext<propositionParser::BooleanContext>(0);
}


size_t propositionParser::Pfunc_argContext::getRuleIndex() const {
  return propositionParser::RulePfunc_arg;
}

void propositionParser::Pfunc_argContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPfunc_arg(this);
}

void propositionParser::Pfunc_argContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPfunc_arg(this);
}

propositionParser::Pfunc_argContext* propositionParser::pfunc_arg() {
  Pfunc_argContext *_localctx = _tracker.createInstance<Pfunc_argContext>(_ctx, getState());
  enterRule(_localctx, 50, propositionParser::RulePfunc_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(367);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(365);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(366);
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

propositionParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::RelopContext::GT() {
  return getToken(propositionParser::GT, 0);
}

tree::TerminalNode* propositionParser::RelopContext::GE() {
  return getToken(propositionParser::GE, 0);
}

tree::TerminalNode* propositionParser::RelopContext::LT() {
  return getToken(propositionParser::LT, 0);
}

tree::TerminalNode* propositionParser::RelopContext::LE() {
  return getToken(propositionParser::LE, 0);
}


size_t propositionParser::RelopContext::getRuleIndex() const {
  return propositionParser::RuleRelop;
}

void propositionParser::RelopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void propositionParser::RelopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}

propositionParser::RelopContext* propositionParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 52, propositionParser::RuleRelop);
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
    setState(369);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 128849018880) != 0))) {
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

propositionParser::Cls_opContext::Cls_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::Cls_opContext::RANGE() {
  return getToken(propositionParser::RANGE, 0);
}

tree::TerminalNode* propositionParser::Cls_opContext::GT() {
  return getToken(propositionParser::GT, 0);
}

tree::TerminalNode* propositionParser::Cls_opContext::GE() {
  return getToken(propositionParser::GE, 0);
}

tree::TerminalNode* propositionParser::Cls_opContext::LT() {
  return getToken(propositionParser::LT, 0);
}

tree::TerminalNode* propositionParser::Cls_opContext::LE() {
  return getToken(propositionParser::LE, 0);
}

tree::TerminalNode* propositionParser::Cls_opContext::EQ() {
  return getToken(propositionParser::EQ, 0);
}


size_t propositionParser::Cls_opContext::getRuleIndex() const {
  return propositionParser::RuleCls_op;
}

void propositionParser::Cls_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCls_op(this);
}

void propositionParser::Cls_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCls_op(this);
}

propositionParser::Cls_opContext* propositionParser::cls_op() {
  Cls_opContext *_localctx = _tracker.createInstance<Cls_opContext>(_ctx, getState());
  enterRule(_localctx, 54, propositionParser::RuleCls_op);
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
    setState(371);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 18014664797454336) != 0))) {
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

bool propositionParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 7: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 9: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);
    case 22: return stringSempred(antlrcpp::downCast<StringContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool propositionParser::booleanSempred(BooleanContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 8);
    case 1: return precpred(_ctx, 7);
    case 2: return precpred(_ctx, 6);
    case 3: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

bool propositionParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 13);
    case 5: return precpred(_ctx, 12);
    case 6: return precpred(_ctx, 11);
    case 7: return precpred(_ctx, 10);
    case 8: return precpred(_ctx, 9);
    case 9: return precpred(_ctx, 8);
    case 10: return precpred(_ctx, 7);
    case 11: return precpred(_ctx, 14);

  default:
    break;
  }
  return true;
}

bool propositionParser::stringSempred(StringContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 12: return precpred(_ctx, 4);
    case 13: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void propositionParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  propositionParserInitialize();
#else
  ::antlr4::internal::call_once(propositionParserOnceFlag, propositionParserInitialize);
#endif
}
