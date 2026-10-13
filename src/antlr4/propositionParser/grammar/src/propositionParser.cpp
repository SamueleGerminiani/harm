
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
      "signCast", "pfunc_arg", "relop", "cls_op"
    },
    std::vector<std::string>{
      "", "','", "", "", "", "", "", "", "", "", "'.substr'", "", "", "'{'", 
      "'}'", "'['", "']'", "'('", "')'", "'inside'", "", "", "", "", "", 
      "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", "'>='", "'<'", 
      "'<='", "'=='", "'!='", "'==='", "'!=='", "'\\u003F'", "'&'", "'|'", 
      "'^'", "'~'", "'<<<'", "'>>>'", "'<<'", "'>>'", "'&&'", "'||'", "'!'", 
      "':'", "'::'", "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", "INT_VARIABLE", "CONST_SUFFIX", 
      "LOGIC_VARIABLE", "BIT_VARIABLE", "FLOAT_CONSTANT", "FLOAT_VARIABLE", 
      "SUBSTR", "STRING_CONSTANT", "STRING_VARIABLE", "LCURLY", "RCURLY", 
      "LSQUARED", "RSQUARED", "LROUND", "RROUND", "INSIDE", "SIGN_CAST", 
      "FUNCTION", "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", "VERILOG_BASED", 
      "FILL_LITERAL", "SINGLE_QUOTE", "PLUS", "MINUS", "TIMES", "DIV", "GT", 
      "GE", "LT", "LE", "EQ", "NEQ", "CASE_EQ", "CASE_NEQ", "QUESTION", 
      "BAND", "BOR", "BXOR", "NEG", "ALSHIFT", "ARSHIFT", "LSHIFT", "RSHIFT", 
      "AND", "OR", "NOT", "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,58,363,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,1,0,1,0,3,0,61,8,0,1,0,1,0,1,1,1,1,3,1,67,8,1,1,1,1,1,1,2,1,2,3,2,
  	73,8,2,1,2,1,2,1,3,1,3,3,3,79,8,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,
  	3,5,90,8,5,1,5,1,5,1,5,3,5,95,8,5,1,6,1,6,1,6,1,6,3,6,101,8,6,1,6,1,6,
  	1,6,3,6,106,8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,134,8,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,7,5,7,145,8,7,10,7,12,7,148,9,7,1,8,1,8,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,3,9,173,8,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,3,9,207,8,9,1,9,1,9,5,9,211,8,9,10,9,12,9,214,9,9,1,9,1,9,3,
  	9,218,8,9,1,9,1,9,5,9,222,8,9,10,9,12,9,225,9,9,1,10,1,10,1,10,1,10,4,
  	10,231,8,10,11,10,12,10,232,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,5,
  	10,243,8,10,10,10,12,10,246,9,10,1,10,1,10,1,10,3,10,251,8,10,1,11,1,
  	11,3,11,255,8,11,1,12,1,12,1,12,1,12,3,12,261,8,12,1,12,1,12,1,13,1,13,
  	1,13,3,13,268,8,13,1,13,1,13,1,13,3,13,273,8,13,1,13,1,13,1,14,1,14,1,
  	15,1,15,1,16,1,16,1,17,1,17,3,17,285,8,17,1,18,1,18,1,18,3,18,290,8,18,
  	1,18,3,18,293,8,18,1,19,1,19,1,19,1,19,3,19,299,8,19,1,20,3,20,302,8,
  	20,1,20,1,20,3,20,306,8,20,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,3,
  	22,316,8,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,328,
  	8,22,1,22,5,22,331,8,22,10,22,12,22,334,9,22,1,23,1,23,1,24,1,24,1,24,
  	1,24,1,24,5,24,343,8,24,10,24,12,24,346,9,24,1,24,1,24,1,25,1,25,1,25,
  	1,25,1,25,1,26,1,26,3,26,357,8,26,1,27,1,27,1,28,1,28,1,28,0,3,14,18,
  	44,29,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,
  	46,48,50,52,54,56,0,11,1,0,37,38,1,0,2,3,3,0,29,30,45,45,52,52,1,0,31,
  	32,1,0,29,30,1,0,46,49,1,0,37,40,1,0,8,9,1,0,11,12,1,0,33,36,2,0,33,37,
  	56,56,397,0,60,1,0,0,0,2,66,1,0,0,0,4,72,1,0,0,0,6,78,1,0,0,0,8,82,1,
  	0,0,0,10,85,1,0,0,0,12,96,1,0,0,0,14,133,1,0,0,0,16,149,1,0,0,0,18,172,
  	1,0,0,0,20,250,1,0,0,0,22,254,1,0,0,0,24,256,1,0,0,0,26,264,1,0,0,0,28,
  	276,1,0,0,0,30,278,1,0,0,0,32,280,1,0,0,0,34,284,1,0,0,0,36,292,1,0,0,
  	0,38,298,1,0,0,0,40,305,1,0,0,0,42,307,1,0,0,0,44,315,1,0,0,0,46,335,
  	1,0,0,0,48,337,1,0,0,0,50,349,1,0,0,0,52,356,1,0,0,0,54,358,1,0,0,0,56,
  	360,1,0,0,0,58,61,3,14,7,0,59,61,3,10,5,0,60,58,1,0,0,0,60,59,1,0,0,0,
  	61,62,1,0,0,0,62,63,5,0,0,1,63,1,1,0,0,0,64,67,3,18,9,0,65,67,3,12,6,
  	0,66,64,1,0,0,0,66,65,1,0,0,0,67,68,1,0,0,0,68,69,5,0,0,1,69,3,1,0,0,
  	0,70,73,3,18,9,0,71,73,3,12,6,0,72,70,1,0,0,0,72,71,1,0,0,0,73,74,1,0,
  	0,0,74,75,5,0,0,1,75,5,1,0,0,0,76,79,3,18,9,0,77,79,3,12,6,0,78,76,1,
  	0,0,0,78,77,1,0,0,0,79,80,1,0,0,0,80,81,5,0,0,1,81,7,1,0,0,0,82,83,3,
  	44,22,0,83,84,5,0,0,1,84,9,1,0,0,0,85,86,3,14,7,0,86,89,5,41,0,0,87,90,
  	3,14,7,0,88,90,3,10,5,0,89,87,1,0,0,0,89,88,1,0,0,0,90,91,1,0,0,0,91,
  	94,5,53,0,0,92,95,3,14,7,0,93,95,3,10,5,0,94,92,1,0,0,0,94,93,1,0,0,0,
  	95,11,1,0,0,0,96,97,3,14,7,0,97,100,5,41,0,0,98,101,3,18,9,0,99,101,3,
  	12,6,0,100,98,1,0,0,0,100,99,1,0,0,0,101,102,1,0,0,0,102,105,5,53,0,0,
  	103,106,3,18,9,0,104,106,3,12,6,0,105,103,1,0,0,0,105,104,1,0,0,0,106,
  	13,1,0,0,0,107,108,6,7,-1,0,108,134,3,16,8,0,109,134,3,48,24,0,110,111,
  	3,44,22,0,111,112,3,54,27,0,112,113,3,44,22,0,113,134,1,0,0,0,114,115,
  	3,44,22,0,115,116,5,37,0,0,116,117,3,44,22,0,117,134,1,0,0,0,118,119,
  	3,44,22,0,119,120,5,38,0,0,120,121,3,44,22,0,121,134,1,0,0,0,122,123,
  	5,17,0,0,123,124,3,14,7,0,124,125,5,18,0,0,125,134,1,0,0,0,126,134,3,
  	18,9,0,127,128,5,17,0,0,128,129,3,10,5,0,129,130,5,18,0,0,130,134,1,0,
  	0,0,131,132,5,52,0,0,132,134,3,14,7,4,133,107,1,0,0,0,133,109,1,0,0,0,
  	133,110,1,0,0,0,133,114,1,0,0,0,133,118,1,0,0,0,133,122,1,0,0,0,133,126,
  	1,0,0,0,133,127,1,0,0,0,133,131,1,0,0,0,134,146,1,0,0,0,135,136,10,3,
  	0,0,136,137,7,0,0,0,137,145,3,14,7,4,138,139,10,2,0,0,139,140,5,50,0,
  	0,140,145,3,14,7,3,141,142,10,1,0,0,142,143,5,51,0,0,143,145,3,14,7,2,
  	144,135,1,0,0,0,144,138,1,0,0,0,144,141,1,0,0,0,145,148,1,0,0,0,146,144,
  	1,0,0,0,146,147,1,0,0,0,147,15,1,0,0,0,148,146,1,0,0,0,149,150,7,1,0,
  	0,150,17,1,0,0,0,151,152,6,9,-1,0,152,153,7,2,0,0,153,173,3,18,9,19,154,
  	173,3,48,24,0,155,173,3,50,25,0,156,173,3,34,17,0,157,173,3,38,19,0,158,
  	173,3,42,21,0,159,173,3,20,10,0,160,161,5,17,0,0,161,162,3,18,9,0,162,
  	163,5,18,0,0,163,173,1,0,0,0,164,165,5,17,0,0,165,166,3,12,6,0,166,167,
  	5,18,0,0,167,173,1,0,0,0,168,169,5,17,0,0,169,170,3,14,7,0,170,171,5,
  	18,0,0,171,173,1,0,0,0,172,151,1,0,0,0,172,154,1,0,0,0,172,155,1,0,0,
  	0,172,156,1,0,0,0,172,157,1,0,0,0,172,158,1,0,0,0,172,159,1,0,0,0,172,
  	160,1,0,0,0,172,164,1,0,0,0,172,168,1,0,0,0,173,223,1,0,0,0,174,175,10,
  	16,0,0,175,176,7,3,0,0,176,222,3,18,9,17,177,178,10,15,0,0,178,179,7,
  	4,0,0,179,222,3,18,9,16,180,181,10,14,0,0,181,182,7,5,0,0,182,222,3,18,
  	9,15,183,184,10,13,0,0,184,185,3,54,27,0,185,186,3,18,9,14,186,222,1,
  	0,0,0,187,188,10,11,0,0,188,189,7,6,0,0,189,222,3,18,9,12,190,191,10,
  	10,0,0,191,192,5,42,0,0,192,222,3,18,9,11,193,194,10,9,0,0,194,195,5,
  	44,0,0,195,222,3,18,9,10,196,197,10,8,0,0,197,198,5,43,0,0,198,222,3,
  	18,9,9,199,200,10,20,0,0,200,222,3,24,12,0,201,202,10,12,0,0,202,203,
  	5,19,0,0,203,212,5,13,0,0,204,207,3,32,16,0,205,207,3,26,13,0,206,204,
  	1,0,0,0,206,205,1,0,0,0,207,208,1,0,0,0,208,209,5,1,0,0,209,211,1,0,0,
  	0,210,206,1,0,0,0,211,214,1,0,0,0,212,210,1,0,0,0,212,213,1,0,0,0,213,
  	217,1,0,0,0,214,212,1,0,0,0,215,218,3,32,16,0,216,218,3,26,13,0,217,215,
  	1,0,0,0,217,216,1,0,0,0,218,219,1,0,0,0,219,220,5,14,0,0,220,222,1,0,
  	0,0,221,174,1,0,0,0,221,177,1,0,0,0,221,180,1,0,0,0,221,183,1,0,0,0,221,
  	187,1,0,0,0,221,190,1,0,0,0,221,193,1,0,0,0,221,196,1,0,0,0,221,199,1,
  	0,0,0,221,201,1,0,0,0,222,225,1,0,0,0,223,221,1,0,0,0,223,224,1,0,0,0,
  	224,19,1,0,0,0,225,223,1,0,0,0,226,227,5,13,0,0,227,230,3,22,11,0,228,
  	229,5,1,0,0,229,231,3,22,11,0,230,228,1,0,0,0,231,232,1,0,0,0,232,230,
  	1,0,0,0,232,233,1,0,0,0,233,234,1,0,0,0,234,235,5,14,0,0,235,251,1,0,
  	0,0,236,237,5,13,0,0,237,238,5,22,0,0,238,239,5,13,0,0,239,244,3,22,11,
  	0,240,241,5,1,0,0,241,243,3,22,11,0,242,240,1,0,0,0,243,246,1,0,0,0,244,
  	242,1,0,0,0,244,245,1,0,0,0,245,247,1,0,0,0,246,244,1,0,0,0,247,248,5,
  	14,0,0,248,249,5,14,0,0,249,251,1,0,0,0,250,226,1,0,0,0,250,236,1,0,0,
  	0,251,21,1,0,0,0,252,255,3,18,9,0,253,255,3,16,8,0,254,252,1,0,0,0,254,
  	253,1,0,0,0,255,23,1,0,0,0,256,257,5,15,0,0,257,260,5,22,0,0,258,259,
  	5,53,0,0,259,261,5,22,0,0,260,258,1,0,0,0,260,261,1,0,0,0,261,262,1,0,
  	0,0,262,263,5,16,0,0,263,25,1,0,0,0,264,267,5,15,0,0,265,268,3,18,9,0,
  	266,268,3,28,14,0,267,265,1,0,0,0,267,266,1,0,0,0,268,269,1,0,0,0,269,
  	272,5,53,0,0,270,273,3,18,9,0,271,273,3,30,15,0,272,270,1,0,0,0,272,271,
  	1,0,0,0,273,274,1,0,0,0,274,275,5,16,0,0,275,27,1,0,0,0,276,277,5,55,
  	0,0,277,29,1,0,0,0,278,279,5,55,0,0,279,31,1,0,0,0,280,281,3,18,9,0,281,
  	33,1,0,0,0,282,285,3,36,18,0,283,285,5,4,0,0,284,282,1,0,0,0,284,283,
  	1,0,0,0,285,35,1,0,0,0,286,293,5,24,0,0,287,289,5,22,0,0,288,290,5,5,
  	0,0,289,288,1,0,0,0,289,290,1,0,0,0,290,293,1,0,0,0,291,293,5,25,0,0,
  	292,286,1,0,0,0,292,287,1,0,0,0,292,291,1,0,0,0,293,37,1,0,0,0,294,299,
  	3,40,20,0,295,299,3,36,18,0,296,299,5,6,0,0,297,299,5,7,0,0,298,294,1,
  	0,0,0,298,295,1,0,0,0,298,296,1,0,0,0,298,297,1,0,0,0,299,39,1,0,0,0,
  	300,302,5,22,0,0,301,300,1,0,0,0,301,302,1,0,0,0,302,303,1,0,0,0,303,
  	306,5,26,0,0,304,306,5,27,0,0,305,301,1,0,0,0,305,304,1,0,0,0,306,41,
  	1,0,0,0,307,308,7,7,0,0,308,43,1,0,0,0,309,310,6,22,-1,0,310,316,3,46,
  	23,0,311,312,5,17,0,0,312,313,3,44,22,0,313,314,5,18,0,0,314,316,1,0,
  	0,0,315,309,1,0,0,0,315,311,1,0,0,0,316,332,1,0,0,0,317,318,10,4,0,0,
  	318,319,5,29,0,0,319,331,3,44,22,5,320,321,10,3,0,0,321,322,5,10,0,0,
  	322,327,5,17,0,0,323,324,5,22,0,0,324,325,5,1,0,0,325,328,5,22,0,0,326,
  	328,5,22,0,0,327,323,1,0,0,0,327,326,1,0,0,0,327,328,1,0,0,0,328,329,
  	1,0,0,0,329,331,5,18,0,0,330,317,1,0,0,0,330,320,1,0,0,0,331,334,1,0,
  	0,0,332,330,1,0,0,0,332,333,1,0,0,0,333,45,1,0,0,0,334,332,1,0,0,0,335,
  	336,7,8,0,0,336,47,1,0,0,0,337,338,5,21,0,0,338,339,5,17,0,0,339,344,
  	3,52,26,0,340,341,5,1,0,0,341,343,3,52,26,0,342,340,1,0,0,0,343,346,1,
  	0,0,0,344,342,1,0,0,0,344,345,1,0,0,0,345,347,1,0,0,0,346,344,1,0,0,0,
  	347,348,5,18,0,0,348,49,1,0,0,0,349,350,5,20,0,0,350,351,5,17,0,0,351,
  	352,3,18,9,0,352,353,5,18,0,0,353,51,1,0,0,0,354,357,3,18,9,0,355,357,
  	3,14,7,0,356,354,1,0,0,0,356,355,1,0,0,0,357,53,1,0,0,0,358,359,7,9,0,
  	0,359,55,1,0,0,0,360,361,7,10,0,0,361,57,1,0,0,0,36,60,66,72,78,89,94,
  	100,105,133,144,146,172,206,212,217,221,223,232,244,250,254,260,267,272,
  	284,289,292,298,301,305,315,327,330,332,344,356
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
    setState(60);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(58);
      boolean(0);
      break;
    }

    case 2: {
      setState(59);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(62);
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
    setState(66);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(64);
      numeric(0);
      break;
    }

    case 2: {
      setState(65);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(68);
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
    setState(72);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(70);
      numeric(0);
      break;
    }

    case 2: {
      setState(71);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(74);
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
    setState(78);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(76);
      numeric(0);
      break;
    }

    case 2: {
      setState(77);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(80);
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
    setState(82);
    string(0);
    setState(83);
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
    setState(85);
    boolean(0);
    setState(86);
    match(propositionParser::QUESTION);
    setState(89);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(87);
      boolean(0);
      break;
    }

    case 2: {
      setState(88);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(91);
    match(propositionParser::COL);
    setState(94);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(92);
      boolean(0);
      break;
    }

    case 2: {
      setState(93);
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
    setState(96);
    boolean(0);
    setState(97);
    match(propositionParser::QUESTION);
    setState(100);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(98);
      numeric(0);
      break;
    }

    case 2: {
      setState(99);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(102);
    match(propositionParser::COL);
    setState(105);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(103);
      numeric(0);
      break;
    }

    case 2: {
      setState(104);
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

propositionParser::BooleanAtomContext* propositionParser::BooleanContext::booleanAtom() {
  return getRuleContext<propositionParser::BooleanAtomContext>(0);
}

propositionParser::NonTemporalFunctionContext* propositionParser::BooleanContext::nonTemporalFunction() {
  return getRuleContext<propositionParser::NonTemporalFunctionContext>(0);
}

std::vector<propositionParser::StringContext *> propositionParser::BooleanContext::string() {
  return getRuleContexts<propositionParser::StringContext>();
}

propositionParser::StringContext* propositionParser::BooleanContext::string(size_t i) {
  return getRuleContext<propositionParser::StringContext>(i);
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

tree::TerminalNode* propositionParser::BooleanContext::LROUND() {
  return getToken(propositionParser::LROUND, 0);
}

std::vector<propositionParser::BooleanContext *> propositionParser::BooleanContext::boolean() {
  return getRuleContexts<propositionParser::BooleanContext>();
}

propositionParser::BooleanContext* propositionParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<propositionParser::BooleanContext>(i);
}

tree::TerminalNode* propositionParser::BooleanContext::RROUND() {
  return getToken(propositionParser::RROUND, 0);
}

propositionParser::NumericContext* propositionParser::BooleanContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}

propositionParser::BooleanTernaryContext* propositionParser::BooleanContext::booleanTernary() {
  return getRuleContext<propositionParser::BooleanTernaryContext>(0);
}

tree::TerminalNode* propositionParser::BooleanContext::NOT() {
  return getToken(propositionParser::NOT, 0);
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
    setState(133);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(108);
      booleanAtom();
      break;
    }

    case 2: {
      setState(109);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(110);
      string(0);
      setState(111);
      relop();
      setState(112);
      string(0);
      break;
    }

    case 4: {
      setState(114);
      string(0);
      setState(115);
      match(propositionParser::EQ);
      setState(116);
      string(0);
      break;
    }

    case 5: {
      setState(118);
      string(0);
      setState(119);
      match(propositionParser::NEQ);
      setState(120);
      string(0);
      break;
    }

    case 6: {
      setState(122);
      match(propositionParser::LROUND);
      setState(123);
      boolean(0);
      setState(124);
      match(propositionParser::RROUND);
      break;
    }

    case 7: {
      setState(126);
      numeric(0);
      break;
    }

    case 8: {
      setState(127);
      match(propositionParser::LROUND);
      setState(128);
      booleanTernary();
      setState(129);
      match(propositionParser::RROUND);
      break;
    }

    case 9: {
      setState(131);
      match(propositionParser::NOT);
      setState(132);
      boolean(4);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(146);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(144);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(135);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(136);
          antlrcpp::downCast<BooleanContext *>(_localctx)->eqop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::EQ

          || _la == propositionParser::NEQ)) {
            antlrcpp::downCast<BooleanContext *>(_localctx)->eqop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(137);
          boolean(4);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(138);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(139);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::AND);
          setState(140);
          boolean(3);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(141);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(142);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::OR);
          setState(143);
          boolean(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(148);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
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
    setState(149);
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

std::vector<propositionParser::NumericContext *> propositionParser::NumericContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::NumericContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
}

tree::TerminalNode* propositionParser::NumericContext::NEG() {
  return getToken(propositionParser::NEG, 0);
}

tree::TerminalNode* propositionParser::NumericContext::NOT() {
  return getToken(propositionParser::NOT, 0);
}

tree::TerminalNode* propositionParser::NumericContext::MINUS() {
  return getToken(propositionParser::MINUS, 0);
}

tree::TerminalNode* propositionParser::NumericContext::PLUS() {
  return getToken(propositionParser::PLUS, 0);
}

propositionParser::NonTemporalFunctionContext* propositionParser::NumericContext::nonTemporalFunction() {
  return getRuleContext<propositionParser::NonTemporalFunctionContext>(0);
}

propositionParser::SignCastContext* propositionParser::NumericContext::signCast() {
  return getRuleContext<propositionParser::SignCastContext>(0);
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

propositionParser::BooleanContext* propositionParser::NumericContext::boolean() {
  return getRuleContext<propositionParser::BooleanContext>(0);
}

tree::TerminalNode* propositionParser::NumericContext::TIMES() {
  return getToken(propositionParser::TIMES, 0);
}

tree::TerminalNode* propositionParser::NumericContext::DIV() {
  return getToken(propositionParser::DIV, 0);
}

tree::TerminalNode* propositionParser::NumericContext::LSHIFT() {
  return getToken(propositionParser::LSHIFT, 0);
}

tree::TerminalNode* propositionParser::NumericContext::RSHIFT() {
  return getToken(propositionParser::RSHIFT, 0);
}

tree::TerminalNode* propositionParser::NumericContext::ALSHIFT() {
  return getToken(propositionParser::ALSHIFT, 0);
}

tree::TerminalNode* propositionParser::NumericContext::ARSHIFT() {
  return getToken(propositionParser::ARSHIFT, 0);
}

propositionParser::RelopContext* propositionParser::NumericContext::relop() {
  return getRuleContext<propositionParser::RelopContext>(0);
}

tree::TerminalNode* propositionParser::NumericContext::EQ() {
  return getToken(propositionParser::EQ, 0);
}

tree::TerminalNode* propositionParser::NumericContext::NEQ() {
  return getToken(propositionParser::NEQ, 0);
}

tree::TerminalNode* propositionParser::NumericContext::CASE_EQ() {
  return getToken(propositionParser::CASE_EQ, 0);
}

tree::TerminalNode* propositionParser::NumericContext::CASE_NEQ() {
  return getToken(propositionParser::CASE_NEQ, 0);
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

tree::TerminalNode* propositionParser::NumericContext::INSIDE() {
  return getToken(propositionParser::INSIDE, 0);
}

tree::TerminalNode* propositionParser::NumericContext::LCURLY() {
  return getToken(propositionParser::LCURLY, 0);
}

tree::TerminalNode* propositionParser::NumericContext::RCURLY() {
  return getToken(propositionParser::RCURLY, 0);
}

std::vector<propositionParser::Sm_constantContext *> propositionParser::NumericContext::sm_constant() {
  return getRuleContexts<propositionParser::Sm_constantContext>();
}

propositionParser::Sm_constantContext* propositionParser::NumericContext::sm_constant(size_t i) {
  return getRuleContext<propositionParser::Sm_constantContext>(i);
}

std::vector<propositionParser::Sm_rangeContext *> propositionParser::NumericContext::sm_range() {
  return getRuleContexts<propositionParser::Sm_rangeContext>();
}

propositionParser::Sm_rangeContext* propositionParser::NumericContext::sm_range(size_t i) {
  return getRuleContext<propositionParser::Sm_rangeContext>(i);
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
    setState(172);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(152);
      antlrcpp::downCast<NumericContext *>(_localctx)->unop = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4538785610072064) != 0))) {
        antlrcpp::downCast<NumericContext *>(_localctx)->unop = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(153);
      numeric(19);
      break;
    }

    case 2: {
      setState(154);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(155);
      signCast();
      break;
    }

    case 4: {
      setState(156);
      intAtom();
      break;
    }

    case 5: {
      setState(157);
      logicAtom();
      break;
    }

    case 6: {
      setState(158);
      floatAtom();
      break;
    }

    case 7: {
      setState(159);
      concatenation();
      break;
    }

    case 8: {
      setState(160);
      match(propositionParser::LROUND);
      setState(161);
      numeric(0);
      setState(162);
      match(propositionParser::RROUND);
      break;
    }

    case 9: {
      setState(164);
      match(propositionParser::LROUND);
      setState(165);
      numericTernary();
      setState(166);
      match(propositionParser::RROUND);
      break;
    }

    case 10: {
      setState(168);
      match(propositionParser::LROUND);
      setState(169);
      boolean(0);
      setState(170);
      match(propositionParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(223);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(221);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(174);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(175);
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
          setState(176);
          numeric(17);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(177);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(178);
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
          setState(179);
          numeric(16);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(180);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(181);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 1055531162664960) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->logop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(182);
          numeric(15);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(183);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(184);
          relop();
          setState(185);
          numeric(14);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(187);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(188);
          antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 2061584302080) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(189);
          numeric(12);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(190);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(191);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BAND);
          setState(192);
          numeric(11);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(193);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(194);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BXOR);
          setState(195);
          numeric(10);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(196);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(197);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BOR);
          setState(198);
          numeric(9);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(199);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(200);
          range();
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(201);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(202);
          match(propositionParser::INSIDE);
          setState(203);
          match(propositionParser::LCURLY);
          setState(212);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(206);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case propositionParser::INT_VARIABLE:
                case propositionParser::LOGIC_VARIABLE:
                case propositionParser::BIT_VARIABLE:
                case propositionParser::FLOAT_CONSTANT:
                case propositionParser::FLOAT_VARIABLE:
                case propositionParser::LCURLY:
                case propositionParser::LROUND:
                case propositionParser::SIGN_CAST:
                case propositionParser::FUNCTION:
                case propositionParser::UINTEGER:
                case propositionParser::GCC_BINARY:
                case propositionParser::HEX:
                case propositionParser::VERILOG_BASED:
                case propositionParser::FILL_LITERAL:
                case propositionParser::PLUS:
                case propositionParser::MINUS:
                case propositionParser::NEG:
                case propositionParser::NOT: {
                  setState(204);
                  sm_constant();
                  break;
                }

                case propositionParser::LSQUARED: {
                  setState(205);
                  sm_range();
                  break;
                }

              default:
                throw NoViableAltException(this);
              }
              setState(208);
              match(propositionParser::T__0); 
            }
            setState(214);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
          }
          setState(217);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case propositionParser::INT_VARIABLE:
            case propositionParser::LOGIC_VARIABLE:
            case propositionParser::BIT_VARIABLE:
            case propositionParser::FLOAT_CONSTANT:
            case propositionParser::FLOAT_VARIABLE:
            case propositionParser::LCURLY:
            case propositionParser::LROUND:
            case propositionParser::SIGN_CAST:
            case propositionParser::FUNCTION:
            case propositionParser::UINTEGER:
            case propositionParser::GCC_BINARY:
            case propositionParser::HEX:
            case propositionParser::VERILOG_BASED:
            case propositionParser::FILL_LITERAL:
            case propositionParser::PLUS:
            case propositionParser::MINUS:
            case propositionParser::NEG:
            case propositionParser::NOT: {
              setState(215);
              sm_constant();
              break;
            }

            case propositionParser::LSQUARED: {
              setState(216);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(219);
          match(propositionParser::RCURLY);
          break;
        }

        default:
          break;
        } 
      }
      setState(225);
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
    setState(250);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(226);
      match(propositionParser::LCURLY);
      setState(227);
      concatItem();
      setState(230); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(228);
        match(propositionParser::T__0);
        setState(229);
        concatItem();
        setState(232); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == propositionParser::T__0);
      setState(234);
      match(propositionParser::RCURLY);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(236);
      match(propositionParser::LCURLY);
      setState(237);
      match(propositionParser::UINTEGER);
      setState(238);
      match(propositionParser::LCURLY);
      setState(239);
      concatItem();
      setState(244);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == propositionParser::T__0) {
        setState(240);
        match(propositionParser::T__0);
        setState(241);
        concatItem();
        setState(246);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(247);
      match(propositionParser::RCURLY);
      setState(248);
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
    setState(254);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::INT_VARIABLE:
      case propositionParser::LOGIC_VARIABLE:
      case propositionParser::BIT_VARIABLE:
      case propositionParser::FLOAT_CONSTANT:
      case propositionParser::FLOAT_VARIABLE:
      case propositionParser::LCURLY:
      case propositionParser::LROUND:
      case propositionParser::SIGN_CAST:
      case propositionParser::FUNCTION:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BASED:
      case propositionParser::FILL_LITERAL:
      case propositionParser::PLUS:
      case propositionParser::MINUS:
      case propositionParser::NEG:
      case propositionParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(252);
        numeric(0);
        break;
      }

      case propositionParser::BOOLEAN_CONSTANT:
      case propositionParser::BOOLEAN_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(253);
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

std::vector<tree::TerminalNode *> propositionParser::RangeContext::UINTEGER() {
  return getTokens(propositionParser::UINTEGER);
}

tree::TerminalNode* propositionParser::RangeContext::UINTEGER(size_t i) {
  return getToken(propositionParser::UINTEGER, i);
}

tree::TerminalNode* propositionParser::RangeContext::RSQUARED() {
  return getToken(propositionParser::RSQUARED, 0);
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
    setState(256);
    match(propositionParser::LSQUARED);
    setState(257);
    match(propositionParser::UINTEGER);
    setState(260);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == propositionParser::COL) {
      setState(258);
      match(propositionParser::COL);
      setState(259);
      match(propositionParser::UINTEGER);
    }
    setState(262);
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
    setState(264);
    match(propositionParser::LSQUARED);
    setState(267);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::INT_VARIABLE:
      case propositionParser::LOGIC_VARIABLE:
      case propositionParser::BIT_VARIABLE:
      case propositionParser::FLOAT_CONSTANT:
      case propositionParser::FLOAT_VARIABLE:
      case propositionParser::LCURLY:
      case propositionParser::LROUND:
      case propositionParser::SIGN_CAST:
      case propositionParser::FUNCTION:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BASED:
      case propositionParser::FILL_LITERAL:
      case propositionParser::PLUS:
      case propositionParser::MINUS:
      case propositionParser::NEG:
      case propositionParser::NOT: {
        setState(265);
        numeric(0);
        break;
      }

      case propositionParser::DOLLAR: {
        setState(266);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(269);
    match(propositionParser::COL);
    setState(272);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::INT_VARIABLE:
      case propositionParser::LOGIC_VARIABLE:
      case propositionParser::BIT_VARIABLE:
      case propositionParser::FLOAT_CONSTANT:
      case propositionParser::FLOAT_VARIABLE:
      case propositionParser::LCURLY:
      case propositionParser::LROUND:
      case propositionParser::SIGN_CAST:
      case propositionParser::FUNCTION:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BASED:
      case propositionParser::FILL_LITERAL:
      case propositionParser::PLUS:
      case propositionParser::MINUS:
      case propositionParser::NEG:
      case propositionParser::NOT: {
        setState(270);
        numeric(0);
        break;
      }

      case propositionParser::DOLLAR: {
        setState(271);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
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
    setState(276);
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
    setState(278);
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
    setState(280);
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
    setState(284);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(282);
        int_constant();
        break;
      }

      case propositionParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(283);
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

tree::TerminalNode* propositionParser::Int_constantContext::UINTEGER() {
  return getToken(propositionParser::UINTEGER, 0);
}

tree::TerminalNode* propositionParser::Int_constantContext::CONST_SUFFIX() {
  return getToken(propositionParser::CONST_SUFFIX, 0);
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
    setState(292);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(286);
        match(propositionParser::GCC_BINARY);
        break;
      }

      case propositionParser::UINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(287);
        match(propositionParser::UINTEGER);
        setState(289);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
        case 1: {
          setState(288);
          match(propositionParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 3);
        setState(291);
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
    setState(298);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(294);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(295);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(296);
      match(propositionParser::LOGIC_VARIABLE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(297);
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
    setState(305);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::UINTEGER:
      case propositionParser::VERILOG_BASED: {
        enterOuterAlt(_localctx, 1);
        setState(301);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == propositionParser::UINTEGER) {
          setState(300);
          match(propositionParser::UINTEGER);
        }
        setState(303);
        match(propositionParser::VERILOG_BASED);
        break;
      }

      case propositionParser::FILL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(304);
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
    setState(307);
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
    setState(315);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::STRING_CONSTANT:
      case propositionParser::STRING_VARIABLE: {
        setState(310);
        stringAtom();
        break;
      }

      case propositionParser::LROUND: {
        setState(311);
        match(propositionParser::LROUND);
        setState(312);
        string(0);
        setState(313);
        match(propositionParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(332);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(330);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(317);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(318);
          match(propositionParser::PLUS);
          setState(319);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(320);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(321);
          match(propositionParser::SUBSTR);
          setState(322);
          match(propositionParser::LROUND);
          setState(327);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
          case 1: {
            setState(323);
            match(propositionParser::UINTEGER);
            setState(324);
            match(propositionParser::T__0);
            setState(325);
            match(propositionParser::UINTEGER);
            break;
          }

          case 2: {
            setState(326);
            match(propositionParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(329);
          match(propositionParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(334);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
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
    setState(335);
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
    setState(337);
    match(propositionParser::FUNCTION);
    setState(338);
    match(propositionParser::LROUND);
    setState(339);
    pfunc_arg();
    setState(344);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == propositionParser::T__0) {
      setState(340);
      match(propositionParser::T__0);
      setState(341);
      pfunc_arg();
      setState(346);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(347);
    match(propositionParser::RROUND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SignCastContext ------------------------------------------------------------------

propositionParser::SignCastContext::SignCastContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::SignCastContext::SIGN_CAST() {
  return getToken(propositionParser::SIGN_CAST, 0);
}

tree::TerminalNode* propositionParser::SignCastContext::LROUND() {
  return getToken(propositionParser::LROUND, 0);
}

propositionParser::NumericContext* propositionParser::SignCastContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}

tree::TerminalNode* propositionParser::SignCastContext::RROUND() {
  return getToken(propositionParser::RROUND, 0);
}


size_t propositionParser::SignCastContext::getRuleIndex() const {
  return propositionParser::RuleSignCast;
}

void propositionParser::SignCastContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSignCast(this);
}

void propositionParser::SignCastContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSignCast(this);
}

propositionParser::SignCastContext* propositionParser::signCast() {
  SignCastContext *_localctx = _tracker.createInstance<SignCastContext>(_ctx, getState());
  enterRule(_localctx, 50, propositionParser::RuleSignCast);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(349);
    match(propositionParser::SIGN_CAST);
    setState(350);
    match(propositionParser::LROUND);
    setState(351);
    numeric(0);
    setState(352);
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
  enterRule(_localctx, 52, propositionParser::RulePfunc_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(356);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(354);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(355);
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
  enterRule(_localctx, 54, propositionParser::RuleRelop);
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
    setState(358);
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
  enterRule(_localctx, 56, propositionParser::RuleCls_op);
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
    setState(360);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72057860325900288) != 0))) {
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
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool propositionParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 16);
    case 4: return precpred(_ctx, 15);
    case 5: return precpred(_ctx, 14);
    case 6: return precpred(_ctx, 13);
    case 7: return precpred(_ctx, 11);
    case 8: return precpred(_ctx, 10);
    case 9: return precpred(_ctx, 9);
    case 10: return precpred(_ctx, 8);
    case 11: return precpred(_ctx, 20);
    case 12: return precpred(_ctx, 12);

  default:
    break;
  }
  return true;
}

bool propositionParser::stringSempred(StringContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 13: return precpred(_ctx, 4);
    case 14: return precpred(_ctx, 3);

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
