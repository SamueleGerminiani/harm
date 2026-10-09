
// Generated from varDeclaration.g4 by ANTLR 4.13.2


#include "varDeclarationListener.h"

#include "varDeclarationParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct VarDeclarationParserStaticData final {
  VarDeclarationParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  VarDeclarationParserStaticData(const VarDeclarationParserStaticData&) = delete;
  VarDeclarationParserStaticData(VarDeclarationParserStaticData&&) = delete;
  VarDeclarationParserStaticData& operator=(const VarDeclarationParserStaticData&) = delete;
  VarDeclarationParserStaticData& operator=(VarDeclarationParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag vardeclarationParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<VarDeclarationParserStaticData> vardeclarationParserStaticData = nullptr;

void vardeclarationParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (vardeclarationParserStaticData != nullptr) {
    return;
  }
#else
  assert(vardeclarationParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<VarDeclarationParserStaticData>(
    std::vector<std::string>{
      "file", "varDec", "startBoolean", "startInt", "startLogic", "startFloat", 
      "startString", "booleanTernary", "numericTernary", "boolean", "booleanAtom", 
      "numeric", "concatenation", "concatItem", "range", "sm_range", "min_dollar", 
      "max_dollar", "sm_constant", "intAtom", "int_constant", "logicAtom", 
      "logic_constant", "floatAtom", "string", "stringAtom", "nonTemporalFunction", 
      "pfunc_arg", "relop", "cls_op"
    },
    std::vector<std::string>{
      "", "','", "", "", "", "", "", "", "", "", "", "", "", "'.substr'", 
      "", "", "'{'", "'}'", "'['", "']'", "'('", "')'", "'inside'", "", 
      "", "", "", "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", 
      "'>='", "'<'", "'<='", "'=='", "'!='", "'==='", "'!=='", "'\\u003F'", 
      "'&'", "'|'", "'^'", "'~'", "'<<<'", "'>>>'", "'<<'", "'>>'", "'&&'", 
      "'||'", "'!'", "':'", "'::'", "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "Name", "VARTYPE", "WS", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", 
      "INT_VARIABLE", "CONST_SUFFIX", "LOGIC_VARIABLE", "BIT_VARIABLE", 
      "FLOAT_CONSTANT", "FLOAT_VARIABLE", "SUBSTR", "STRING_CONSTANT", "STRING_VARIABLE", 
      "LCURLY", "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "INSIDE", 
      "FUNCTION", "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", "VERILOG_BASED", 
      "FILL_LITERAL", "SINGLE_QUOTE", "PLUS", "MINUS", "TIMES", "DIV", "GT", 
      "GE", "LT", "LE", "EQ", "NEQ", "CASE_EQ", "CASE_NEQ", "QUESTION", 
      "BAND", "BOR", "BXOR", "NEG", "ALSHIFT", "ARSHIFT", "LSHIFT", "RSHIFT", 
      "AND", "OR", "NOT", "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,59,368,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,1,0,1,0,1,0,1,1,1,1,3,1,66,8,1,1,1,1,1,1,2,1,2,3,2,72,8,
  	2,1,2,1,2,1,3,1,3,3,3,78,8,3,1,3,1,3,1,4,1,4,3,4,84,8,4,1,4,1,4,1,5,1,
  	5,3,5,90,8,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,7,1,7,3,7,101,8,7,1,7,1,7,
  	1,7,3,7,106,8,7,1,8,1,8,1,8,1,8,3,8,112,8,8,1,8,1,8,1,8,3,8,117,8,8,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,145,8,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,5,9,156,8,9,10,9,12,9,159,9,9,1,10,1,10,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,3,11,183,8,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,217,8,11,1,11,1,11,
  	5,11,221,8,11,10,11,12,11,224,9,11,1,11,1,11,3,11,228,8,11,1,11,1,11,
  	5,11,232,8,11,10,11,12,11,235,9,11,1,12,1,12,1,12,1,12,4,12,241,8,12,
  	11,12,12,12,242,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,253,8,12,
  	10,12,12,12,256,9,12,1,12,1,12,1,12,3,12,261,8,12,1,13,1,13,3,13,265,
  	8,13,1,14,1,14,1,14,1,14,3,14,271,8,14,1,14,1,14,1,15,1,15,1,15,3,15,
  	278,8,15,1,15,1,15,1,15,3,15,283,8,15,1,15,1,15,1,16,1,16,1,17,1,17,1,
  	18,1,18,1,19,1,19,3,19,295,8,19,1,20,1,20,1,20,3,20,300,8,20,1,20,3,20,
  	303,8,20,1,21,1,21,1,21,1,21,3,21,309,8,21,1,22,3,22,312,8,22,1,22,1,
  	22,3,22,316,8,22,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,3,24,326,8,24,
  	1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,338,8,24,1,24,
  	5,24,341,8,24,10,24,12,24,344,9,24,1,25,1,25,1,26,1,26,1,26,1,26,1,26,
  	5,26,353,8,26,10,26,12,26,356,9,26,1,26,1,26,1,27,1,27,3,27,362,8,27,
  	1,28,1,28,1,29,1,29,1,29,0,3,18,22,48,30,0,2,4,6,8,10,12,14,16,18,20,
  	22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,0,11,1,0,39,
  	40,1,0,5,6,3,0,31,32,47,47,54,54,1,0,33,34,1,0,31,32,1,0,48,51,1,0,39,
  	42,1,0,11,12,1,0,14,15,1,0,35,38,2,0,35,39,58,58,401,0,60,1,0,0,0,2,63,
  	1,0,0,0,4,71,1,0,0,0,6,77,1,0,0,0,8,83,1,0,0,0,10,89,1,0,0,0,12,93,1,
  	0,0,0,14,96,1,0,0,0,16,107,1,0,0,0,18,144,1,0,0,0,20,160,1,0,0,0,22,182,
  	1,0,0,0,24,260,1,0,0,0,26,264,1,0,0,0,28,266,1,0,0,0,30,274,1,0,0,0,32,
  	286,1,0,0,0,34,288,1,0,0,0,36,290,1,0,0,0,38,294,1,0,0,0,40,302,1,0,0,
  	0,42,308,1,0,0,0,44,315,1,0,0,0,46,317,1,0,0,0,48,325,1,0,0,0,50,345,
  	1,0,0,0,52,347,1,0,0,0,54,361,1,0,0,0,56,363,1,0,0,0,58,365,1,0,0,0,60,
  	61,3,2,1,0,61,62,5,0,0,1,62,1,1,0,0,0,63,65,5,3,0,0,64,66,3,28,14,0,65,
  	64,1,0,0,0,65,66,1,0,0,0,66,67,1,0,0,0,67,68,5,2,0,0,68,3,1,0,0,0,69,
  	72,3,18,9,0,70,72,3,14,7,0,71,69,1,0,0,0,71,70,1,0,0,0,72,73,1,0,0,0,
  	73,74,5,0,0,1,74,5,1,0,0,0,75,78,3,22,11,0,76,78,3,16,8,0,77,75,1,0,0,
  	0,77,76,1,0,0,0,78,79,1,0,0,0,79,80,5,0,0,1,80,7,1,0,0,0,81,84,3,22,11,
  	0,82,84,3,16,8,0,83,81,1,0,0,0,83,82,1,0,0,0,84,85,1,0,0,0,85,86,5,0,
  	0,1,86,9,1,0,0,0,87,90,3,22,11,0,88,90,3,16,8,0,89,87,1,0,0,0,89,88,1,
  	0,0,0,90,91,1,0,0,0,91,92,5,0,0,1,92,11,1,0,0,0,93,94,3,48,24,0,94,95,
  	5,0,0,1,95,13,1,0,0,0,96,97,3,18,9,0,97,100,5,43,0,0,98,101,3,18,9,0,
  	99,101,3,14,7,0,100,98,1,0,0,0,100,99,1,0,0,0,101,102,1,0,0,0,102,105,
  	5,55,0,0,103,106,3,18,9,0,104,106,3,14,7,0,105,103,1,0,0,0,105,104,1,
  	0,0,0,106,15,1,0,0,0,107,108,3,18,9,0,108,111,5,43,0,0,109,112,3,22,11,
  	0,110,112,3,16,8,0,111,109,1,0,0,0,111,110,1,0,0,0,112,113,1,0,0,0,113,
  	116,5,55,0,0,114,117,3,22,11,0,115,117,3,16,8,0,116,114,1,0,0,0,116,115,
  	1,0,0,0,117,17,1,0,0,0,118,119,6,9,-1,0,119,145,3,20,10,0,120,145,3,52,
  	26,0,121,122,3,48,24,0,122,123,3,56,28,0,123,124,3,48,24,0,124,145,1,
  	0,0,0,125,126,3,48,24,0,126,127,5,39,0,0,127,128,3,48,24,0,128,145,1,
  	0,0,0,129,130,3,48,24,0,130,131,5,40,0,0,131,132,3,48,24,0,132,145,1,
  	0,0,0,133,134,5,20,0,0,134,135,3,18,9,0,135,136,5,21,0,0,136,145,1,0,
  	0,0,137,145,3,22,11,0,138,139,5,20,0,0,139,140,3,14,7,0,140,141,5,21,
  	0,0,141,145,1,0,0,0,142,143,5,54,0,0,143,145,3,18,9,4,144,118,1,0,0,0,
  	144,120,1,0,0,0,144,121,1,0,0,0,144,125,1,0,0,0,144,129,1,0,0,0,144,133,
  	1,0,0,0,144,137,1,0,0,0,144,138,1,0,0,0,144,142,1,0,0,0,145,157,1,0,0,
  	0,146,147,10,3,0,0,147,148,7,0,0,0,148,156,3,18,9,4,149,150,10,2,0,0,
  	150,151,5,52,0,0,151,156,3,18,9,3,152,153,10,1,0,0,153,154,5,53,0,0,154,
  	156,3,18,9,2,155,146,1,0,0,0,155,149,1,0,0,0,155,152,1,0,0,0,156,159,
  	1,0,0,0,157,155,1,0,0,0,157,158,1,0,0,0,158,19,1,0,0,0,159,157,1,0,0,
  	0,160,161,7,1,0,0,161,21,1,0,0,0,162,163,6,11,-1,0,163,164,7,2,0,0,164,
  	183,3,22,11,18,165,183,3,52,26,0,166,183,3,38,19,0,167,183,3,42,21,0,
  	168,183,3,46,23,0,169,183,3,24,12,0,170,171,5,20,0,0,171,172,3,22,11,
  	0,172,173,5,21,0,0,173,183,1,0,0,0,174,175,5,20,0,0,175,176,3,16,8,0,
  	176,177,5,21,0,0,177,183,1,0,0,0,178,179,5,20,0,0,179,180,3,18,9,0,180,
  	181,5,21,0,0,181,183,1,0,0,0,182,162,1,0,0,0,182,165,1,0,0,0,182,166,
  	1,0,0,0,182,167,1,0,0,0,182,168,1,0,0,0,182,169,1,0,0,0,182,170,1,0,0,
  	0,182,174,1,0,0,0,182,178,1,0,0,0,183,233,1,0,0,0,184,185,10,16,0,0,185,
  	186,7,3,0,0,186,232,3,22,11,17,187,188,10,15,0,0,188,189,7,4,0,0,189,
  	232,3,22,11,16,190,191,10,14,0,0,191,192,7,5,0,0,192,232,3,22,11,15,193,
  	194,10,13,0,0,194,195,3,56,28,0,195,196,3,22,11,14,196,232,1,0,0,0,197,
  	198,10,11,0,0,198,199,7,6,0,0,199,232,3,22,11,12,200,201,10,10,0,0,201,
  	202,5,44,0,0,202,232,3,22,11,11,203,204,10,9,0,0,204,205,5,46,0,0,205,
  	232,3,22,11,10,206,207,10,8,0,0,207,208,5,45,0,0,208,232,3,22,11,9,209,
  	210,10,19,0,0,210,232,3,28,14,0,211,212,10,12,0,0,212,213,5,22,0,0,213,
  	222,5,16,0,0,214,217,3,36,18,0,215,217,3,30,15,0,216,214,1,0,0,0,216,
  	215,1,0,0,0,217,218,1,0,0,0,218,219,5,1,0,0,219,221,1,0,0,0,220,216,1,
  	0,0,0,221,224,1,0,0,0,222,220,1,0,0,0,222,223,1,0,0,0,223,227,1,0,0,0,
  	224,222,1,0,0,0,225,228,3,36,18,0,226,228,3,30,15,0,227,225,1,0,0,0,227,
  	226,1,0,0,0,228,229,1,0,0,0,229,230,5,17,0,0,230,232,1,0,0,0,231,184,
  	1,0,0,0,231,187,1,0,0,0,231,190,1,0,0,0,231,193,1,0,0,0,231,197,1,0,0,
  	0,231,200,1,0,0,0,231,203,1,0,0,0,231,206,1,0,0,0,231,209,1,0,0,0,231,
  	211,1,0,0,0,232,235,1,0,0,0,233,231,1,0,0,0,233,234,1,0,0,0,234,23,1,
  	0,0,0,235,233,1,0,0,0,236,237,5,16,0,0,237,240,3,26,13,0,238,239,5,1,
  	0,0,239,241,3,26,13,0,240,238,1,0,0,0,241,242,1,0,0,0,242,240,1,0,0,0,
  	242,243,1,0,0,0,243,244,1,0,0,0,244,245,5,17,0,0,245,261,1,0,0,0,246,
  	247,5,16,0,0,247,248,5,24,0,0,248,249,5,16,0,0,249,254,3,26,13,0,250,
  	251,5,1,0,0,251,253,3,26,13,0,252,250,1,0,0,0,253,256,1,0,0,0,254,252,
  	1,0,0,0,254,255,1,0,0,0,255,257,1,0,0,0,256,254,1,0,0,0,257,258,5,17,
  	0,0,258,259,5,17,0,0,259,261,1,0,0,0,260,236,1,0,0,0,260,246,1,0,0,0,
  	261,25,1,0,0,0,262,265,3,22,11,0,263,265,3,20,10,0,264,262,1,0,0,0,264,
  	263,1,0,0,0,265,27,1,0,0,0,266,267,5,18,0,0,267,270,5,24,0,0,268,269,
  	5,55,0,0,269,271,5,24,0,0,270,268,1,0,0,0,270,271,1,0,0,0,271,272,1,0,
  	0,0,272,273,5,19,0,0,273,29,1,0,0,0,274,277,5,18,0,0,275,278,3,22,11,
  	0,276,278,3,32,16,0,277,275,1,0,0,0,277,276,1,0,0,0,278,279,1,0,0,0,279,
  	282,5,55,0,0,280,283,3,22,11,0,281,283,3,34,17,0,282,280,1,0,0,0,282,
  	281,1,0,0,0,283,284,1,0,0,0,284,285,5,19,0,0,285,31,1,0,0,0,286,287,5,
  	57,0,0,287,33,1,0,0,0,288,289,5,57,0,0,289,35,1,0,0,0,290,291,3,22,11,
  	0,291,37,1,0,0,0,292,295,3,40,20,0,293,295,5,7,0,0,294,292,1,0,0,0,294,
  	293,1,0,0,0,295,39,1,0,0,0,296,303,5,26,0,0,297,299,5,24,0,0,298,300,
  	5,8,0,0,299,298,1,0,0,0,299,300,1,0,0,0,300,303,1,0,0,0,301,303,5,27,
  	0,0,302,296,1,0,0,0,302,297,1,0,0,0,302,301,1,0,0,0,303,41,1,0,0,0,304,
  	309,3,44,22,0,305,309,3,40,20,0,306,309,5,9,0,0,307,309,5,10,0,0,308,
  	304,1,0,0,0,308,305,1,0,0,0,308,306,1,0,0,0,308,307,1,0,0,0,309,43,1,
  	0,0,0,310,312,5,24,0,0,311,310,1,0,0,0,311,312,1,0,0,0,312,313,1,0,0,
  	0,313,316,5,28,0,0,314,316,5,29,0,0,315,311,1,0,0,0,315,314,1,0,0,0,316,
  	45,1,0,0,0,317,318,7,7,0,0,318,47,1,0,0,0,319,320,6,24,-1,0,320,326,3,
  	50,25,0,321,322,5,20,0,0,322,323,3,48,24,0,323,324,5,21,0,0,324,326,1,
  	0,0,0,325,319,1,0,0,0,325,321,1,0,0,0,326,342,1,0,0,0,327,328,10,4,0,
  	0,328,329,5,31,0,0,329,341,3,48,24,5,330,331,10,3,0,0,331,332,5,13,0,
  	0,332,337,5,20,0,0,333,334,5,24,0,0,334,335,5,1,0,0,335,338,5,24,0,0,
  	336,338,5,24,0,0,337,333,1,0,0,0,337,336,1,0,0,0,337,338,1,0,0,0,338,
  	339,1,0,0,0,339,341,5,21,0,0,340,327,1,0,0,0,340,330,1,0,0,0,341,344,
  	1,0,0,0,342,340,1,0,0,0,342,343,1,0,0,0,343,49,1,0,0,0,344,342,1,0,0,
  	0,345,346,7,8,0,0,346,51,1,0,0,0,347,348,5,23,0,0,348,349,5,20,0,0,349,
  	354,3,54,27,0,350,351,5,1,0,0,351,353,3,54,27,0,352,350,1,0,0,0,353,356,
  	1,0,0,0,354,352,1,0,0,0,354,355,1,0,0,0,355,357,1,0,0,0,356,354,1,0,0,
  	0,357,358,5,21,0,0,358,53,1,0,0,0,359,362,3,22,11,0,360,362,3,18,9,0,
  	361,359,1,0,0,0,361,360,1,0,0,0,362,55,1,0,0,0,363,364,7,9,0,0,364,57,
  	1,0,0,0,365,366,7,10,0,0,366,59,1,0,0,0,37,65,71,77,83,89,100,105,111,
  	116,144,155,157,182,216,222,227,231,233,242,254,260,264,270,277,282,294,
  	299,302,308,311,315,325,337,340,342,354,361
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  vardeclarationParserStaticData = std::move(staticData);
}

}

varDeclarationParser::varDeclarationParser(TokenStream *input) : varDeclarationParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

varDeclarationParser::varDeclarationParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  varDeclarationParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *vardeclarationParserStaticData->atn, vardeclarationParserStaticData->decisionToDFA, vardeclarationParserStaticData->sharedContextCache, options);
}

varDeclarationParser::~varDeclarationParser() {
  delete _interpreter;
}

const atn::ATN& varDeclarationParser::getATN() const {
  return *vardeclarationParserStaticData->atn;
}

std::string varDeclarationParser::getGrammarFileName() const {
  return "varDeclaration.g4";
}

const std::vector<std::string>& varDeclarationParser::getRuleNames() const {
  return vardeclarationParserStaticData->ruleNames;
}

const dfa::Vocabulary& varDeclarationParser::getVocabulary() const {
  return vardeclarationParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView varDeclarationParser::getSerializedATN() const {
  return vardeclarationParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

varDeclarationParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::VarDecContext* varDeclarationParser::FileContext::varDec() {
  return getRuleContext<varDeclarationParser::VarDecContext>(0);
}

tree::TerminalNode* varDeclarationParser::FileContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
}


size_t varDeclarationParser::FileContext::getRuleIndex() const {
  return varDeclarationParser::RuleFile;
}

void varDeclarationParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void varDeclarationParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

varDeclarationParser::FileContext* varDeclarationParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, varDeclarationParser::RuleFile);

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
    varDec();
    setState(61);
    match(varDeclarationParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDecContext ------------------------------------------------------------------

varDeclarationParser::VarDecContext::VarDecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::VarDecContext::VARTYPE() {
  return getToken(varDeclarationParser::VARTYPE, 0);
}

tree::TerminalNode* varDeclarationParser::VarDecContext::Name() {
  return getToken(varDeclarationParser::Name, 0);
}

varDeclarationParser::RangeContext* varDeclarationParser::VarDecContext::range() {
  return getRuleContext<varDeclarationParser::RangeContext>(0);
}


size_t varDeclarationParser::VarDecContext::getRuleIndex() const {
  return varDeclarationParser::RuleVarDec;
}

void varDeclarationParser::VarDecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDec(this);
}

void varDeclarationParser::VarDecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDec(this);
}

varDeclarationParser::VarDecContext* varDeclarationParser::varDec() {
  VarDecContext *_localctx = _tracker.createInstance<VarDecContext>(_ctx, getState());
  enterRule(_localctx, 2, varDeclarationParser::RuleVarDec);
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
    setState(63);
    match(varDeclarationParser::VARTYPE);
    setState(65);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::LSQUARED) {
      setState(64);
      range();
    }
    setState(67);
    match(varDeclarationParser::Name);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartBooleanContext ------------------------------------------------------------------

varDeclarationParser::StartBooleanContext::StartBooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::StartBooleanContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
}

varDeclarationParser::BooleanContext* varDeclarationParser::StartBooleanContext::boolean() {
  return getRuleContext<varDeclarationParser::BooleanContext>(0);
}

varDeclarationParser::BooleanTernaryContext* varDeclarationParser::StartBooleanContext::booleanTernary() {
  return getRuleContext<varDeclarationParser::BooleanTernaryContext>(0);
}


size_t varDeclarationParser::StartBooleanContext::getRuleIndex() const {
  return varDeclarationParser::RuleStartBoolean;
}

void varDeclarationParser::StartBooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartBoolean(this);
}

void varDeclarationParser::StartBooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartBoolean(this);
}

varDeclarationParser::StartBooleanContext* varDeclarationParser::startBoolean() {
  StartBooleanContext *_localctx = _tracker.createInstance<StartBooleanContext>(_ctx, getState());
  enterRule(_localctx, 4, varDeclarationParser::RuleStartBoolean);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(69);
      boolean(0);
      break;
    }

    case 2: {
      setState(70);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(73);
    match(varDeclarationParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartIntContext ------------------------------------------------------------------

varDeclarationParser::StartIntContext::StartIntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::StartIntContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
}

varDeclarationParser::NumericContext* varDeclarationParser::StartIntContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}

varDeclarationParser::NumericTernaryContext* varDeclarationParser::StartIntContext::numericTernary() {
  return getRuleContext<varDeclarationParser::NumericTernaryContext>(0);
}


size_t varDeclarationParser::StartIntContext::getRuleIndex() const {
  return varDeclarationParser::RuleStartInt;
}

void varDeclarationParser::StartIntContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartInt(this);
}

void varDeclarationParser::StartIntContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartInt(this);
}

varDeclarationParser::StartIntContext* varDeclarationParser::startInt() {
  StartIntContext *_localctx = _tracker.createInstance<StartIntContext>(_ctx, getState());
  enterRule(_localctx, 6, varDeclarationParser::RuleStartInt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(75);
      numeric(0);
      break;
    }

    case 2: {
      setState(76);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(79);
    match(varDeclarationParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartLogicContext ------------------------------------------------------------------

varDeclarationParser::StartLogicContext::StartLogicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::StartLogicContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
}

varDeclarationParser::NumericContext* varDeclarationParser::StartLogicContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}

varDeclarationParser::NumericTernaryContext* varDeclarationParser::StartLogicContext::numericTernary() {
  return getRuleContext<varDeclarationParser::NumericTernaryContext>(0);
}


size_t varDeclarationParser::StartLogicContext::getRuleIndex() const {
  return varDeclarationParser::RuleStartLogic;
}

void varDeclarationParser::StartLogicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartLogic(this);
}

void varDeclarationParser::StartLogicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartLogic(this);
}

varDeclarationParser::StartLogicContext* varDeclarationParser::startLogic() {
  StartLogicContext *_localctx = _tracker.createInstance<StartLogicContext>(_ctx, getState());
  enterRule(_localctx, 8, varDeclarationParser::RuleStartLogic);

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
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(81);
      numeric(0);
      break;
    }

    case 2: {
      setState(82);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(85);
    match(varDeclarationParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartFloatContext ------------------------------------------------------------------

varDeclarationParser::StartFloatContext::StartFloatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::StartFloatContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
}

varDeclarationParser::NumericContext* varDeclarationParser::StartFloatContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}

varDeclarationParser::NumericTernaryContext* varDeclarationParser::StartFloatContext::numericTernary() {
  return getRuleContext<varDeclarationParser::NumericTernaryContext>(0);
}


size_t varDeclarationParser::StartFloatContext::getRuleIndex() const {
  return varDeclarationParser::RuleStartFloat;
}

void varDeclarationParser::StartFloatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartFloat(this);
}

void varDeclarationParser::StartFloatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartFloat(this);
}

varDeclarationParser::StartFloatContext* varDeclarationParser::startFloat() {
  StartFloatContext *_localctx = _tracker.createInstance<StartFloatContext>(_ctx, getState());
  enterRule(_localctx, 10, varDeclarationParser::RuleStartFloat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(87);
      numeric(0);
      break;
    }

    case 2: {
      setState(88);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(91);
    match(varDeclarationParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StartStringContext ------------------------------------------------------------------

varDeclarationParser::StartStringContext::StartStringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::StringContext* varDeclarationParser::StartStringContext::string() {
  return getRuleContext<varDeclarationParser::StringContext>(0);
}

tree::TerminalNode* varDeclarationParser::StartStringContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
}


size_t varDeclarationParser::StartStringContext::getRuleIndex() const {
  return varDeclarationParser::RuleStartString;
}

void varDeclarationParser::StartStringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartString(this);
}

void varDeclarationParser::StartStringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartString(this);
}

varDeclarationParser::StartStringContext* varDeclarationParser::startString() {
  StartStringContext *_localctx = _tracker.createInstance<StartStringContext>(_ctx, getState());
  enterRule(_localctx, 12, varDeclarationParser::RuleStartString);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(93);
    string(0);
    setState(94);
    match(varDeclarationParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanTernaryContext ------------------------------------------------------------------

varDeclarationParser::BooleanTernaryContext::BooleanTernaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<varDeclarationParser::BooleanContext *> varDeclarationParser::BooleanTernaryContext::boolean() {
  return getRuleContexts<varDeclarationParser::BooleanContext>();
}

varDeclarationParser::BooleanContext* varDeclarationParser::BooleanTernaryContext::boolean(size_t i) {
  return getRuleContext<varDeclarationParser::BooleanContext>(i);
}

tree::TerminalNode* varDeclarationParser::BooleanTernaryContext::QUESTION() {
  return getToken(varDeclarationParser::QUESTION, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanTernaryContext::COL() {
  return getToken(varDeclarationParser::COL, 0);
}

std::vector<varDeclarationParser::BooleanTernaryContext *> varDeclarationParser::BooleanTernaryContext::booleanTernary() {
  return getRuleContexts<varDeclarationParser::BooleanTernaryContext>();
}

varDeclarationParser::BooleanTernaryContext* varDeclarationParser::BooleanTernaryContext::booleanTernary(size_t i) {
  return getRuleContext<varDeclarationParser::BooleanTernaryContext>(i);
}


size_t varDeclarationParser::BooleanTernaryContext::getRuleIndex() const {
  return varDeclarationParser::RuleBooleanTernary;
}

void varDeclarationParser::BooleanTernaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanTernary(this);
}

void varDeclarationParser::BooleanTernaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanTernary(this);
}

varDeclarationParser::BooleanTernaryContext* varDeclarationParser::booleanTernary() {
  BooleanTernaryContext *_localctx = _tracker.createInstance<BooleanTernaryContext>(_ctx, getState());
  enterRule(_localctx, 14, varDeclarationParser::RuleBooleanTernary);

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
    match(varDeclarationParser::QUESTION);
    setState(100);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(98);
      boolean(0);
      break;
    }

    case 2: {
      setState(99);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(102);
    match(varDeclarationParser::COL);
    setState(105);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(103);
      boolean(0);
      break;
    }

    case 2: {
      setState(104);
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

varDeclarationParser::NumericTernaryContext::NumericTernaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::BooleanContext* varDeclarationParser::NumericTernaryContext::boolean() {
  return getRuleContext<varDeclarationParser::BooleanContext>(0);
}

tree::TerminalNode* varDeclarationParser::NumericTernaryContext::QUESTION() {
  return getToken(varDeclarationParser::QUESTION, 0);
}

tree::TerminalNode* varDeclarationParser::NumericTernaryContext::COL() {
  return getToken(varDeclarationParser::COL, 0);
}

std::vector<varDeclarationParser::NumericContext *> varDeclarationParser::NumericTernaryContext::numeric() {
  return getRuleContexts<varDeclarationParser::NumericContext>();
}

varDeclarationParser::NumericContext* varDeclarationParser::NumericTernaryContext::numeric(size_t i) {
  return getRuleContext<varDeclarationParser::NumericContext>(i);
}

std::vector<varDeclarationParser::NumericTernaryContext *> varDeclarationParser::NumericTernaryContext::numericTernary() {
  return getRuleContexts<varDeclarationParser::NumericTernaryContext>();
}

varDeclarationParser::NumericTernaryContext* varDeclarationParser::NumericTernaryContext::numericTernary(size_t i) {
  return getRuleContext<varDeclarationParser::NumericTernaryContext>(i);
}


size_t varDeclarationParser::NumericTernaryContext::getRuleIndex() const {
  return varDeclarationParser::RuleNumericTernary;
}

void varDeclarationParser::NumericTernaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericTernary(this);
}

void varDeclarationParser::NumericTernaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericTernary(this);
}

varDeclarationParser::NumericTernaryContext* varDeclarationParser::numericTernary() {
  NumericTernaryContext *_localctx = _tracker.createInstance<NumericTernaryContext>(_ctx, getState());
  enterRule(_localctx, 16, varDeclarationParser::RuleNumericTernary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(107);
    boolean(0);
    setState(108);
    match(varDeclarationParser::QUESTION);
    setState(111);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(109);
      numeric(0);
      break;
    }

    case 2: {
      setState(110);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(113);
    match(varDeclarationParser::COL);
    setState(116);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(114);
      numeric(0);
      break;
    }

    case 2: {
      setState(115);
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

varDeclarationParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::BooleanAtomContext* varDeclarationParser::BooleanContext::booleanAtom() {
  return getRuleContext<varDeclarationParser::BooleanAtomContext>(0);
}

varDeclarationParser::NonTemporalFunctionContext* varDeclarationParser::BooleanContext::nonTemporalFunction() {
  return getRuleContext<varDeclarationParser::NonTemporalFunctionContext>(0);
}

std::vector<varDeclarationParser::StringContext *> varDeclarationParser::BooleanContext::string() {
  return getRuleContexts<varDeclarationParser::StringContext>();
}

varDeclarationParser::StringContext* varDeclarationParser::BooleanContext::string(size_t i) {
  return getRuleContext<varDeclarationParser::StringContext>(i);
}

varDeclarationParser::RelopContext* varDeclarationParser::BooleanContext::relop() {
  return getRuleContext<varDeclarationParser::RelopContext>(0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::EQ() {
  return getToken(varDeclarationParser::EQ, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::NEQ() {
  return getToken(varDeclarationParser::NEQ, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::LROUND() {
  return getToken(varDeclarationParser::LROUND, 0);
}

std::vector<varDeclarationParser::BooleanContext *> varDeclarationParser::BooleanContext::boolean() {
  return getRuleContexts<varDeclarationParser::BooleanContext>();
}

varDeclarationParser::BooleanContext* varDeclarationParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<varDeclarationParser::BooleanContext>(i);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::RROUND() {
  return getToken(varDeclarationParser::RROUND, 0);
}

varDeclarationParser::NumericContext* varDeclarationParser::BooleanContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}

varDeclarationParser::BooleanTernaryContext* varDeclarationParser::BooleanContext::booleanTernary() {
  return getRuleContext<varDeclarationParser::BooleanTernaryContext>(0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::NOT() {
  return getToken(varDeclarationParser::NOT, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::AND() {
  return getToken(varDeclarationParser::AND, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::OR() {
  return getToken(varDeclarationParser::OR, 0);
}


size_t varDeclarationParser::BooleanContext::getRuleIndex() const {
  return varDeclarationParser::RuleBoolean;
}

void varDeclarationParser::BooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolean(this);
}

void varDeclarationParser::BooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolean(this);
}


varDeclarationParser::BooleanContext* varDeclarationParser::boolean() {
   return boolean(0);
}

varDeclarationParser::BooleanContext* varDeclarationParser::boolean(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  varDeclarationParser::BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, parentState);
  varDeclarationParser::BooleanContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, varDeclarationParser::RuleBoolean, precedence);

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
    setState(144);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(119);
      booleanAtom();
      break;
    }

    case 2: {
      setState(120);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(121);
      string(0);
      setState(122);
      relop();
      setState(123);
      string(0);
      break;
    }

    case 4: {
      setState(125);
      string(0);
      setState(126);
      match(varDeclarationParser::EQ);
      setState(127);
      string(0);
      break;
    }

    case 5: {
      setState(129);
      string(0);
      setState(130);
      match(varDeclarationParser::NEQ);
      setState(131);
      string(0);
      break;
    }

    case 6: {
      setState(133);
      match(varDeclarationParser::LROUND);
      setState(134);
      boolean(0);
      setState(135);
      match(varDeclarationParser::RROUND);
      break;
    }

    case 7: {
      setState(137);
      numeric(0);
      break;
    }

    case 8: {
      setState(138);
      match(varDeclarationParser::LROUND);
      setState(139);
      booleanTernary();
      setState(140);
      match(varDeclarationParser::RROUND);
      break;
    }

    case 9: {
      setState(142);
      match(varDeclarationParser::NOT);
      setState(143);
      boolean(4);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(157);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(155);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(146);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(147);
          antlrcpp::downCast<BooleanContext *>(_localctx)->eqop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == varDeclarationParser::EQ

          || _la == varDeclarationParser::NEQ)) {
            antlrcpp::downCast<BooleanContext *>(_localctx)->eqop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(148);
          boolean(4);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(149);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(150);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(varDeclarationParser::AND);
          setState(151);
          boolean(3);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(152);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(153);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(varDeclarationParser::OR);
          setState(154);
          boolean(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(159);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
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

varDeclarationParser::BooleanAtomContext::BooleanAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::BooleanAtomContext::BOOLEAN_CONSTANT() {
  return getToken(varDeclarationParser::BOOLEAN_CONSTANT, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanAtomContext::BOOLEAN_VARIABLE() {
  return getToken(varDeclarationParser::BOOLEAN_VARIABLE, 0);
}


size_t varDeclarationParser::BooleanAtomContext::getRuleIndex() const {
  return varDeclarationParser::RuleBooleanAtom;
}

void varDeclarationParser::BooleanAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanAtom(this);
}

void varDeclarationParser::BooleanAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanAtom(this);
}

varDeclarationParser::BooleanAtomContext* varDeclarationParser::booleanAtom() {
  BooleanAtomContext *_localctx = _tracker.createInstance<BooleanAtomContext>(_ctx, getState());
  enterRule(_localctx, 20, varDeclarationParser::RuleBooleanAtom);
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
    setState(160);
    _la = _input->LA(1);
    if (!(_la == varDeclarationParser::BOOLEAN_CONSTANT

    || _la == varDeclarationParser::BOOLEAN_VARIABLE)) {
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

varDeclarationParser::NumericContext::NumericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<varDeclarationParser::NumericContext *> varDeclarationParser::NumericContext::numeric() {
  return getRuleContexts<varDeclarationParser::NumericContext>();
}

varDeclarationParser::NumericContext* varDeclarationParser::NumericContext::numeric(size_t i) {
  return getRuleContext<varDeclarationParser::NumericContext>(i);
}

tree::TerminalNode* varDeclarationParser::NumericContext::NEG() {
  return getToken(varDeclarationParser::NEG, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::NOT() {
  return getToken(varDeclarationParser::NOT, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::MINUS() {
  return getToken(varDeclarationParser::MINUS, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::PLUS() {
  return getToken(varDeclarationParser::PLUS, 0);
}

varDeclarationParser::NonTemporalFunctionContext* varDeclarationParser::NumericContext::nonTemporalFunction() {
  return getRuleContext<varDeclarationParser::NonTemporalFunctionContext>(0);
}

varDeclarationParser::IntAtomContext* varDeclarationParser::NumericContext::intAtom() {
  return getRuleContext<varDeclarationParser::IntAtomContext>(0);
}

varDeclarationParser::LogicAtomContext* varDeclarationParser::NumericContext::logicAtom() {
  return getRuleContext<varDeclarationParser::LogicAtomContext>(0);
}

varDeclarationParser::FloatAtomContext* varDeclarationParser::NumericContext::floatAtom() {
  return getRuleContext<varDeclarationParser::FloatAtomContext>(0);
}

varDeclarationParser::ConcatenationContext* varDeclarationParser::NumericContext::concatenation() {
  return getRuleContext<varDeclarationParser::ConcatenationContext>(0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::LROUND() {
  return getToken(varDeclarationParser::LROUND, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::RROUND() {
  return getToken(varDeclarationParser::RROUND, 0);
}

varDeclarationParser::NumericTernaryContext* varDeclarationParser::NumericContext::numericTernary() {
  return getRuleContext<varDeclarationParser::NumericTernaryContext>(0);
}

varDeclarationParser::BooleanContext* varDeclarationParser::NumericContext::boolean() {
  return getRuleContext<varDeclarationParser::BooleanContext>(0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::TIMES() {
  return getToken(varDeclarationParser::TIMES, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::DIV() {
  return getToken(varDeclarationParser::DIV, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::LSHIFT() {
  return getToken(varDeclarationParser::LSHIFT, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::RSHIFT() {
  return getToken(varDeclarationParser::RSHIFT, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::ALSHIFT() {
  return getToken(varDeclarationParser::ALSHIFT, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::ARSHIFT() {
  return getToken(varDeclarationParser::ARSHIFT, 0);
}

varDeclarationParser::RelopContext* varDeclarationParser::NumericContext::relop() {
  return getRuleContext<varDeclarationParser::RelopContext>(0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::EQ() {
  return getToken(varDeclarationParser::EQ, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::NEQ() {
  return getToken(varDeclarationParser::NEQ, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::CASE_EQ() {
  return getToken(varDeclarationParser::CASE_EQ, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::CASE_NEQ() {
  return getToken(varDeclarationParser::CASE_NEQ, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::BAND() {
  return getToken(varDeclarationParser::BAND, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::BXOR() {
  return getToken(varDeclarationParser::BXOR, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::BOR() {
  return getToken(varDeclarationParser::BOR, 0);
}

varDeclarationParser::RangeContext* varDeclarationParser::NumericContext::range() {
  return getRuleContext<varDeclarationParser::RangeContext>(0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::INSIDE() {
  return getToken(varDeclarationParser::INSIDE, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::LCURLY() {
  return getToken(varDeclarationParser::LCURLY, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::RCURLY() {
  return getToken(varDeclarationParser::RCURLY, 0);
}

std::vector<varDeclarationParser::Sm_constantContext *> varDeclarationParser::NumericContext::sm_constant() {
  return getRuleContexts<varDeclarationParser::Sm_constantContext>();
}

varDeclarationParser::Sm_constantContext* varDeclarationParser::NumericContext::sm_constant(size_t i) {
  return getRuleContext<varDeclarationParser::Sm_constantContext>(i);
}

std::vector<varDeclarationParser::Sm_rangeContext *> varDeclarationParser::NumericContext::sm_range() {
  return getRuleContexts<varDeclarationParser::Sm_rangeContext>();
}

varDeclarationParser::Sm_rangeContext* varDeclarationParser::NumericContext::sm_range(size_t i) {
  return getRuleContext<varDeclarationParser::Sm_rangeContext>(i);
}


size_t varDeclarationParser::NumericContext::getRuleIndex() const {
  return varDeclarationParser::RuleNumeric;
}

void varDeclarationParser::NumericContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void varDeclarationParser::NumericContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}


varDeclarationParser::NumericContext* varDeclarationParser::numeric() {
   return numeric(0);
}

varDeclarationParser::NumericContext* varDeclarationParser::numeric(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  varDeclarationParser::NumericContext *_localctx = _tracker.createInstance<NumericContext>(_ctx, parentState);
  varDeclarationParser::NumericContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, varDeclarationParser::RuleNumeric, precedence);

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
    setState(182);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(163);
      antlrcpp::downCast<NumericContext *>(_localctx)->unop = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 18155142440288256) != 0))) {
        antlrcpp::downCast<NumericContext *>(_localctx)->unop = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(164);
      numeric(18);
      break;
    }

    case 2: {
      setState(165);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(166);
      intAtom();
      break;
    }

    case 4: {
      setState(167);
      logicAtom();
      break;
    }

    case 5: {
      setState(168);
      floatAtom();
      break;
    }

    case 6: {
      setState(169);
      concatenation();
      break;
    }

    case 7: {
      setState(170);
      match(varDeclarationParser::LROUND);
      setState(171);
      numeric(0);
      setState(172);
      match(varDeclarationParser::RROUND);
      break;
    }

    case 8: {
      setState(174);
      match(varDeclarationParser::LROUND);
      setState(175);
      numericTernary();
      setState(176);
      match(varDeclarationParser::RROUND);
      break;
    }

    case 9: {
      setState(178);
      match(varDeclarationParser::LROUND);
      setState(179);
      boolean(0);
      setState(180);
      match(varDeclarationParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(233);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(231);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(184);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(185);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == varDeclarationParser::TIMES

          || _la == varDeclarationParser::DIV)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(186);
          numeric(17);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(187);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(188);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == varDeclarationParser::PLUS

          || _la == varDeclarationParser::MINUS)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(189);
          numeric(16);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(190);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(191);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 4222124650659840) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->logop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(192);
          numeric(15);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(193);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(194);
          relop();
          setState(195);
          numeric(14);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(197);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(198);
          antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 8246337208320) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(199);
          numeric(12);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(200);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(201);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BAND);
          setState(202);
          numeric(11);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(203);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(204);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BXOR);
          setState(205);
          numeric(10);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(206);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(207);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BOR);
          setState(208);
          numeric(9);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(209);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(210);
          range();
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(211);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(212);
          match(varDeclarationParser::INSIDE);
          setState(213);
          match(varDeclarationParser::LCURLY);
          setState(222);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(216);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case varDeclarationParser::INT_VARIABLE:
                case varDeclarationParser::LOGIC_VARIABLE:
                case varDeclarationParser::BIT_VARIABLE:
                case varDeclarationParser::FLOAT_CONSTANT:
                case varDeclarationParser::FLOAT_VARIABLE:
                case varDeclarationParser::LCURLY:
                case varDeclarationParser::LROUND:
                case varDeclarationParser::FUNCTION:
                case varDeclarationParser::UINTEGER:
                case varDeclarationParser::GCC_BINARY:
                case varDeclarationParser::HEX:
                case varDeclarationParser::VERILOG_BASED:
                case varDeclarationParser::FILL_LITERAL:
                case varDeclarationParser::PLUS:
                case varDeclarationParser::MINUS:
                case varDeclarationParser::NEG:
                case varDeclarationParser::NOT: {
                  setState(214);
                  sm_constant();
                  break;
                }

                case varDeclarationParser::LSQUARED: {
                  setState(215);
                  sm_range();
                  break;
                }

              default:
                throw NoViableAltException(this);
              }
              setState(218);
              match(varDeclarationParser::T__0); 
            }
            setState(224);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
          }
          setState(227);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case varDeclarationParser::INT_VARIABLE:
            case varDeclarationParser::LOGIC_VARIABLE:
            case varDeclarationParser::BIT_VARIABLE:
            case varDeclarationParser::FLOAT_CONSTANT:
            case varDeclarationParser::FLOAT_VARIABLE:
            case varDeclarationParser::LCURLY:
            case varDeclarationParser::LROUND:
            case varDeclarationParser::FUNCTION:
            case varDeclarationParser::UINTEGER:
            case varDeclarationParser::GCC_BINARY:
            case varDeclarationParser::HEX:
            case varDeclarationParser::VERILOG_BASED:
            case varDeclarationParser::FILL_LITERAL:
            case varDeclarationParser::PLUS:
            case varDeclarationParser::MINUS:
            case varDeclarationParser::NEG:
            case varDeclarationParser::NOT: {
              setState(225);
              sm_constant();
              break;
            }

            case varDeclarationParser::LSQUARED: {
              setState(226);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(229);
          match(varDeclarationParser::RCURLY);
          break;
        }

        default:
          break;
        } 
      }
      setState(235);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
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

varDeclarationParser::ConcatenationContext::ConcatenationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> varDeclarationParser::ConcatenationContext::LCURLY() {
  return getTokens(varDeclarationParser::LCURLY);
}

tree::TerminalNode* varDeclarationParser::ConcatenationContext::LCURLY(size_t i) {
  return getToken(varDeclarationParser::LCURLY, i);
}

std::vector<varDeclarationParser::ConcatItemContext *> varDeclarationParser::ConcatenationContext::concatItem() {
  return getRuleContexts<varDeclarationParser::ConcatItemContext>();
}

varDeclarationParser::ConcatItemContext* varDeclarationParser::ConcatenationContext::concatItem(size_t i) {
  return getRuleContext<varDeclarationParser::ConcatItemContext>(i);
}

std::vector<tree::TerminalNode *> varDeclarationParser::ConcatenationContext::RCURLY() {
  return getTokens(varDeclarationParser::RCURLY);
}

tree::TerminalNode* varDeclarationParser::ConcatenationContext::RCURLY(size_t i) {
  return getToken(varDeclarationParser::RCURLY, i);
}

tree::TerminalNode* varDeclarationParser::ConcatenationContext::UINTEGER() {
  return getToken(varDeclarationParser::UINTEGER, 0);
}


size_t varDeclarationParser::ConcatenationContext::getRuleIndex() const {
  return varDeclarationParser::RuleConcatenation;
}

void varDeclarationParser::ConcatenationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConcatenation(this);
}

void varDeclarationParser::ConcatenationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConcatenation(this);
}

varDeclarationParser::ConcatenationContext* varDeclarationParser::concatenation() {
  ConcatenationContext *_localctx = _tracker.createInstance<ConcatenationContext>(_ctx, getState());
  enterRule(_localctx, 24, varDeclarationParser::RuleConcatenation);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(260);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(236);
      match(varDeclarationParser::LCURLY);
      setState(237);
      concatItem();
      setState(240); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(238);
        match(varDeclarationParser::T__0);
        setState(239);
        concatItem();
        setState(242); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == varDeclarationParser::T__0);
      setState(244);
      match(varDeclarationParser::RCURLY);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(246);
      match(varDeclarationParser::LCURLY);
      setState(247);
      match(varDeclarationParser::UINTEGER);
      setState(248);
      match(varDeclarationParser::LCURLY);
      setState(249);
      concatItem();
      setState(254);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == varDeclarationParser::T__0) {
        setState(250);
        match(varDeclarationParser::T__0);
        setState(251);
        concatItem();
        setState(256);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(257);
      match(varDeclarationParser::RCURLY);
      setState(258);
      match(varDeclarationParser::RCURLY);
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

varDeclarationParser::ConcatItemContext::ConcatItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::NumericContext* varDeclarationParser::ConcatItemContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}

varDeclarationParser::BooleanAtomContext* varDeclarationParser::ConcatItemContext::booleanAtom() {
  return getRuleContext<varDeclarationParser::BooleanAtomContext>(0);
}


size_t varDeclarationParser::ConcatItemContext::getRuleIndex() const {
  return varDeclarationParser::RuleConcatItem;
}

void varDeclarationParser::ConcatItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConcatItem(this);
}

void varDeclarationParser::ConcatItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConcatItem(this);
}

varDeclarationParser::ConcatItemContext* varDeclarationParser::concatItem() {
  ConcatItemContext *_localctx = _tracker.createInstance<ConcatItemContext>(_ctx, getState());
  enterRule(_localctx, 26, varDeclarationParser::RuleConcatItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(264);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::BIT_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LCURLY:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::FUNCTION:
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX:
      case varDeclarationParser::VERILOG_BASED:
      case varDeclarationParser::FILL_LITERAL:
      case varDeclarationParser::PLUS:
      case varDeclarationParser::MINUS:
      case varDeclarationParser::NEG:
      case varDeclarationParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(262);
        numeric(0);
        break;
      }

      case varDeclarationParser::BOOLEAN_CONSTANT:
      case varDeclarationParser::BOOLEAN_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(263);
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

varDeclarationParser::RangeContext::RangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::RangeContext::LSQUARED() {
  return getToken(varDeclarationParser::LSQUARED, 0);
}

std::vector<tree::TerminalNode *> varDeclarationParser::RangeContext::UINTEGER() {
  return getTokens(varDeclarationParser::UINTEGER);
}

tree::TerminalNode* varDeclarationParser::RangeContext::UINTEGER(size_t i) {
  return getToken(varDeclarationParser::UINTEGER, i);
}

tree::TerminalNode* varDeclarationParser::RangeContext::RSQUARED() {
  return getToken(varDeclarationParser::RSQUARED, 0);
}

tree::TerminalNode* varDeclarationParser::RangeContext::COL() {
  return getToken(varDeclarationParser::COL, 0);
}


size_t varDeclarationParser::RangeContext::getRuleIndex() const {
  return varDeclarationParser::RuleRange;
}

void varDeclarationParser::RangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRange(this);
}

void varDeclarationParser::RangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRange(this);
}

varDeclarationParser::RangeContext* varDeclarationParser::range() {
  RangeContext *_localctx = _tracker.createInstance<RangeContext>(_ctx, getState());
  enterRule(_localctx, 28, varDeclarationParser::RuleRange);
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
    setState(266);
    match(varDeclarationParser::LSQUARED);
    setState(267);
    match(varDeclarationParser::UINTEGER);
    setState(270);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::COL) {
      setState(268);
      match(varDeclarationParser::COL);
      setState(269);
      match(varDeclarationParser::UINTEGER);
    }
    setState(272);
    match(varDeclarationParser::RSQUARED);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sm_rangeContext ------------------------------------------------------------------

varDeclarationParser::Sm_rangeContext::Sm_rangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::Sm_rangeContext::LSQUARED() {
  return getToken(varDeclarationParser::LSQUARED, 0);
}

tree::TerminalNode* varDeclarationParser::Sm_rangeContext::COL() {
  return getToken(varDeclarationParser::COL, 0);
}

tree::TerminalNode* varDeclarationParser::Sm_rangeContext::RSQUARED() {
  return getToken(varDeclarationParser::RSQUARED, 0);
}

std::vector<varDeclarationParser::NumericContext *> varDeclarationParser::Sm_rangeContext::numeric() {
  return getRuleContexts<varDeclarationParser::NumericContext>();
}

varDeclarationParser::NumericContext* varDeclarationParser::Sm_rangeContext::numeric(size_t i) {
  return getRuleContext<varDeclarationParser::NumericContext>(i);
}

varDeclarationParser::Min_dollarContext* varDeclarationParser::Sm_rangeContext::min_dollar() {
  return getRuleContext<varDeclarationParser::Min_dollarContext>(0);
}

varDeclarationParser::Max_dollarContext* varDeclarationParser::Sm_rangeContext::max_dollar() {
  return getRuleContext<varDeclarationParser::Max_dollarContext>(0);
}


size_t varDeclarationParser::Sm_rangeContext::getRuleIndex() const {
  return varDeclarationParser::RuleSm_range;
}

void varDeclarationParser::Sm_rangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSm_range(this);
}

void varDeclarationParser::Sm_rangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSm_range(this);
}

varDeclarationParser::Sm_rangeContext* varDeclarationParser::sm_range() {
  Sm_rangeContext *_localctx = _tracker.createInstance<Sm_rangeContext>(_ctx, getState());
  enterRule(_localctx, 30, varDeclarationParser::RuleSm_range);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(274);
    match(varDeclarationParser::LSQUARED);
    setState(277);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::BIT_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LCURLY:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::FUNCTION:
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX:
      case varDeclarationParser::VERILOG_BASED:
      case varDeclarationParser::FILL_LITERAL:
      case varDeclarationParser::PLUS:
      case varDeclarationParser::MINUS:
      case varDeclarationParser::NEG:
      case varDeclarationParser::NOT: {
        setState(275);
        numeric(0);
        break;
      }

      case varDeclarationParser::DOLLAR: {
        setState(276);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(279);
    match(varDeclarationParser::COL);
    setState(282);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::BIT_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LCURLY:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::FUNCTION:
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX:
      case varDeclarationParser::VERILOG_BASED:
      case varDeclarationParser::FILL_LITERAL:
      case varDeclarationParser::PLUS:
      case varDeclarationParser::MINUS:
      case varDeclarationParser::NEG:
      case varDeclarationParser::NOT: {
        setState(280);
        numeric(0);
        break;
      }

      case varDeclarationParser::DOLLAR: {
        setState(281);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(284);
    match(varDeclarationParser::RSQUARED);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Min_dollarContext ------------------------------------------------------------------

varDeclarationParser::Min_dollarContext::Min_dollarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::Min_dollarContext::DOLLAR() {
  return getToken(varDeclarationParser::DOLLAR, 0);
}


size_t varDeclarationParser::Min_dollarContext::getRuleIndex() const {
  return varDeclarationParser::RuleMin_dollar;
}

void varDeclarationParser::Min_dollarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMin_dollar(this);
}

void varDeclarationParser::Min_dollarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMin_dollar(this);
}

varDeclarationParser::Min_dollarContext* varDeclarationParser::min_dollar() {
  Min_dollarContext *_localctx = _tracker.createInstance<Min_dollarContext>(_ctx, getState());
  enterRule(_localctx, 32, varDeclarationParser::RuleMin_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(286);
    match(varDeclarationParser::DOLLAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Max_dollarContext ------------------------------------------------------------------

varDeclarationParser::Max_dollarContext::Max_dollarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::Max_dollarContext::DOLLAR() {
  return getToken(varDeclarationParser::DOLLAR, 0);
}


size_t varDeclarationParser::Max_dollarContext::getRuleIndex() const {
  return varDeclarationParser::RuleMax_dollar;
}

void varDeclarationParser::Max_dollarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMax_dollar(this);
}

void varDeclarationParser::Max_dollarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMax_dollar(this);
}

varDeclarationParser::Max_dollarContext* varDeclarationParser::max_dollar() {
  Max_dollarContext *_localctx = _tracker.createInstance<Max_dollarContext>(_ctx, getState());
  enterRule(_localctx, 34, varDeclarationParser::RuleMax_dollar);

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
    match(varDeclarationParser::DOLLAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sm_constantContext ------------------------------------------------------------------

varDeclarationParser::Sm_constantContext::Sm_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::NumericContext* varDeclarationParser::Sm_constantContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}


size_t varDeclarationParser::Sm_constantContext::getRuleIndex() const {
  return varDeclarationParser::RuleSm_constant;
}

void varDeclarationParser::Sm_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSm_constant(this);
}

void varDeclarationParser::Sm_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSm_constant(this);
}

varDeclarationParser::Sm_constantContext* varDeclarationParser::sm_constant() {
  Sm_constantContext *_localctx = _tracker.createInstance<Sm_constantContext>(_ctx, getState());
  enterRule(_localctx, 36, varDeclarationParser::RuleSm_constant);

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

varDeclarationParser::IntAtomContext::IntAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::Int_constantContext* varDeclarationParser::IntAtomContext::int_constant() {
  return getRuleContext<varDeclarationParser::Int_constantContext>(0);
}

tree::TerminalNode* varDeclarationParser::IntAtomContext::INT_VARIABLE() {
  return getToken(varDeclarationParser::INT_VARIABLE, 0);
}


size_t varDeclarationParser::IntAtomContext::getRuleIndex() const {
  return varDeclarationParser::RuleIntAtom;
}

void varDeclarationParser::IntAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntAtom(this);
}

void varDeclarationParser::IntAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntAtom(this);
}

varDeclarationParser::IntAtomContext* varDeclarationParser::intAtom() {
  IntAtomContext *_localctx = _tracker.createInstance<IntAtomContext>(_ctx, getState());
  enterRule(_localctx, 38, varDeclarationParser::RuleIntAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(294);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(292);
        int_constant();
        break;
      }

      case varDeclarationParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(293);
        match(varDeclarationParser::INT_VARIABLE);
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

varDeclarationParser::Int_constantContext::Int_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::Int_constantContext::GCC_BINARY() {
  return getToken(varDeclarationParser::GCC_BINARY, 0);
}

tree::TerminalNode* varDeclarationParser::Int_constantContext::UINTEGER() {
  return getToken(varDeclarationParser::UINTEGER, 0);
}

tree::TerminalNode* varDeclarationParser::Int_constantContext::CONST_SUFFIX() {
  return getToken(varDeclarationParser::CONST_SUFFIX, 0);
}

tree::TerminalNode* varDeclarationParser::Int_constantContext::HEX() {
  return getToken(varDeclarationParser::HEX, 0);
}


size_t varDeclarationParser::Int_constantContext::getRuleIndex() const {
  return varDeclarationParser::RuleInt_constant;
}

void varDeclarationParser::Int_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInt_constant(this);
}

void varDeclarationParser::Int_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInt_constant(this);
}

varDeclarationParser::Int_constantContext* varDeclarationParser::int_constant() {
  Int_constantContext *_localctx = _tracker.createInstance<Int_constantContext>(_ctx, getState());
  enterRule(_localctx, 40, varDeclarationParser::RuleInt_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(302);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(296);
        match(varDeclarationParser::GCC_BINARY);
        break;
      }

      case varDeclarationParser::UINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(297);
        match(varDeclarationParser::UINTEGER);
        setState(299);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          setState(298);
          match(varDeclarationParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case varDeclarationParser::HEX: {
        enterOuterAlt(_localctx, 3);
        setState(301);
        match(varDeclarationParser::HEX);
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

varDeclarationParser::LogicAtomContext::LogicAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::Logic_constantContext* varDeclarationParser::LogicAtomContext::logic_constant() {
  return getRuleContext<varDeclarationParser::Logic_constantContext>(0);
}

varDeclarationParser::Int_constantContext* varDeclarationParser::LogicAtomContext::int_constant() {
  return getRuleContext<varDeclarationParser::Int_constantContext>(0);
}

tree::TerminalNode* varDeclarationParser::LogicAtomContext::LOGIC_VARIABLE() {
  return getToken(varDeclarationParser::LOGIC_VARIABLE, 0);
}

tree::TerminalNode* varDeclarationParser::LogicAtomContext::BIT_VARIABLE() {
  return getToken(varDeclarationParser::BIT_VARIABLE, 0);
}


size_t varDeclarationParser::LogicAtomContext::getRuleIndex() const {
  return varDeclarationParser::RuleLogicAtom;
}

void varDeclarationParser::LogicAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicAtom(this);
}

void varDeclarationParser::LogicAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicAtom(this);
}

varDeclarationParser::LogicAtomContext* varDeclarationParser::logicAtom() {
  LogicAtomContext *_localctx = _tracker.createInstance<LogicAtomContext>(_ctx, getState());
  enterRule(_localctx, 42, varDeclarationParser::RuleLogicAtom);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(304);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(305);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(306);
      match(varDeclarationParser::LOGIC_VARIABLE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(307);
      match(varDeclarationParser::BIT_VARIABLE);
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

varDeclarationParser::Logic_constantContext::Logic_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::Logic_constantContext::VERILOG_BASED() {
  return getToken(varDeclarationParser::VERILOG_BASED, 0);
}

tree::TerminalNode* varDeclarationParser::Logic_constantContext::UINTEGER() {
  return getToken(varDeclarationParser::UINTEGER, 0);
}

tree::TerminalNode* varDeclarationParser::Logic_constantContext::FILL_LITERAL() {
  return getToken(varDeclarationParser::FILL_LITERAL, 0);
}


size_t varDeclarationParser::Logic_constantContext::getRuleIndex() const {
  return varDeclarationParser::RuleLogic_constant;
}

void varDeclarationParser::Logic_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic_constant(this);
}

void varDeclarationParser::Logic_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic_constant(this);
}

varDeclarationParser::Logic_constantContext* varDeclarationParser::logic_constant() {
  Logic_constantContext *_localctx = _tracker.createInstance<Logic_constantContext>(_ctx, getState());
  enterRule(_localctx, 44, varDeclarationParser::RuleLogic_constant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(315);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::VERILOG_BASED: {
        enterOuterAlt(_localctx, 1);
        setState(311);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == varDeclarationParser::UINTEGER) {
          setState(310);
          match(varDeclarationParser::UINTEGER);
        }
        setState(313);
        match(varDeclarationParser::VERILOG_BASED);
        break;
      }

      case varDeclarationParser::FILL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(314);
        match(varDeclarationParser::FILL_LITERAL);
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

varDeclarationParser::FloatAtomContext::FloatAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::FloatAtomContext::FLOAT_CONSTANT() {
  return getToken(varDeclarationParser::FLOAT_CONSTANT, 0);
}

tree::TerminalNode* varDeclarationParser::FloatAtomContext::FLOAT_VARIABLE() {
  return getToken(varDeclarationParser::FLOAT_VARIABLE, 0);
}


size_t varDeclarationParser::FloatAtomContext::getRuleIndex() const {
  return varDeclarationParser::RuleFloatAtom;
}

void varDeclarationParser::FloatAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFloatAtom(this);
}

void varDeclarationParser::FloatAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFloatAtom(this);
}

varDeclarationParser::FloatAtomContext* varDeclarationParser::floatAtom() {
  FloatAtomContext *_localctx = _tracker.createInstance<FloatAtomContext>(_ctx, getState());
  enterRule(_localctx, 46, varDeclarationParser::RuleFloatAtom);
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
    setState(317);
    _la = _input->LA(1);
    if (!(_la == varDeclarationParser::FLOAT_CONSTANT

    || _la == varDeclarationParser::FLOAT_VARIABLE)) {
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

varDeclarationParser::StringContext::StringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::StringAtomContext* varDeclarationParser::StringContext::stringAtom() {
  return getRuleContext<varDeclarationParser::StringAtomContext>(0);
}

tree::TerminalNode* varDeclarationParser::StringContext::LROUND() {
  return getToken(varDeclarationParser::LROUND, 0);
}

std::vector<varDeclarationParser::StringContext *> varDeclarationParser::StringContext::string() {
  return getRuleContexts<varDeclarationParser::StringContext>();
}

varDeclarationParser::StringContext* varDeclarationParser::StringContext::string(size_t i) {
  return getRuleContext<varDeclarationParser::StringContext>(i);
}

tree::TerminalNode* varDeclarationParser::StringContext::RROUND() {
  return getToken(varDeclarationParser::RROUND, 0);
}

tree::TerminalNode* varDeclarationParser::StringContext::PLUS() {
  return getToken(varDeclarationParser::PLUS, 0);
}

tree::TerminalNode* varDeclarationParser::StringContext::SUBSTR() {
  return getToken(varDeclarationParser::SUBSTR, 0);
}

std::vector<tree::TerminalNode *> varDeclarationParser::StringContext::UINTEGER() {
  return getTokens(varDeclarationParser::UINTEGER);
}

tree::TerminalNode* varDeclarationParser::StringContext::UINTEGER(size_t i) {
  return getToken(varDeclarationParser::UINTEGER, i);
}


size_t varDeclarationParser::StringContext::getRuleIndex() const {
  return varDeclarationParser::RuleString;
}

void varDeclarationParser::StringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterString(this);
}

void varDeclarationParser::StringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitString(this);
}


varDeclarationParser::StringContext* varDeclarationParser::string() {
   return string(0);
}

varDeclarationParser::StringContext* varDeclarationParser::string(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  varDeclarationParser::StringContext *_localctx = _tracker.createInstance<StringContext>(_ctx, parentState);
  varDeclarationParser::StringContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, varDeclarationParser::RuleString, precedence);

    

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
    setState(325);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::STRING_CONSTANT:
      case varDeclarationParser::STRING_VARIABLE: {
        setState(320);
        stringAtom();
        break;
      }

      case varDeclarationParser::LROUND: {
        setState(321);
        match(varDeclarationParser::LROUND);
        setState(322);
        string(0);
        setState(323);
        match(varDeclarationParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(342);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(340);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(327);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(328);
          match(varDeclarationParser::PLUS);
          setState(329);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(330);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(331);
          match(varDeclarationParser::SUBSTR);
          setState(332);
          match(varDeclarationParser::LROUND);
          setState(337);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
          case 1: {
            setState(333);
            match(varDeclarationParser::UINTEGER);
            setState(334);
            match(varDeclarationParser::T__0);
            setState(335);
            match(varDeclarationParser::UINTEGER);
            break;
          }

          case 2: {
            setState(336);
            match(varDeclarationParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(339);
          match(varDeclarationParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(344);
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

varDeclarationParser::StringAtomContext::StringAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::StringAtomContext::STRING_CONSTANT() {
  return getToken(varDeclarationParser::STRING_CONSTANT, 0);
}

tree::TerminalNode* varDeclarationParser::StringAtomContext::STRING_VARIABLE() {
  return getToken(varDeclarationParser::STRING_VARIABLE, 0);
}


size_t varDeclarationParser::StringAtomContext::getRuleIndex() const {
  return varDeclarationParser::RuleStringAtom;
}

void varDeclarationParser::StringAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringAtom(this);
}

void varDeclarationParser::StringAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringAtom(this);
}

varDeclarationParser::StringAtomContext* varDeclarationParser::stringAtom() {
  StringAtomContext *_localctx = _tracker.createInstance<StringAtomContext>(_ctx, getState());
  enterRule(_localctx, 50, varDeclarationParser::RuleStringAtom);
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
    setState(345);
    _la = _input->LA(1);
    if (!(_la == varDeclarationParser::STRING_CONSTANT

    || _la == varDeclarationParser::STRING_VARIABLE)) {
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

varDeclarationParser::NonTemporalFunctionContext::NonTemporalFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::NonTemporalFunctionContext::FUNCTION() {
  return getToken(varDeclarationParser::FUNCTION, 0);
}

tree::TerminalNode* varDeclarationParser::NonTemporalFunctionContext::LROUND() {
  return getToken(varDeclarationParser::LROUND, 0);
}

std::vector<varDeclarationParser::Pfunc_argContext *> varDeclarationParser::NonTemporalFunctionContext::pfunc_arg() {
  return getRuleContexts<varDeclarationParser::Pfunc_argContext>();
}

varDeclarationParser::Pfunc_argContext* varDeclarationParser::NonTemporalFunctionContext::pfunc_arg(size_t i) {
  return getRuleContext<varDeclarationParser::Pfunc_argContext>(i);
}

tree::TerminalNode* varDeclarationParser::NonTemporalFunctionContext::RROUND() {
  return getToken(varDeclarationParser::RROUND, 0);
}


size_t varDeclarationParser::NonTemporalFunctionContext::getRuleIndex() const {
  return varDeclarationParser::RuleNonTemporalFunction;
}

void varDeclarationParser::NonTemporalFunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNonTemporalFunction(this);
}

void varDeclarationParser::NonTemporalFunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNonTemporalFunction(this);
}

varDeclarationParser::NonTemporalFunctionContext* varDeclarationParser::nonTemporalFunction() {
  NonTemporalFunctionContext *_localctx = _tracker.createInstance<NonTemporalFunctionContext>(_ctx, getState());
  enterRule(_localctx, 52, varDeclarationParser::RuleNonTemporalFunction);
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
    setState(347);
    match(varDeclarationParser::FUNCTION);
    setState(348);
    match(varDeclarationParser::LROUND);
    setState(349);
    pfunc_arg();
    setState(354);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == varDeclarationParser::T__0) {
      setState(350);
      match(varDeclarationParser::T__0);
      setState(351);
      pfunc_arg();
      setState(356);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(357);
    match(varDeclarationParser::RROUND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pfunc_argContext ------------------------------------------------------------------

varDeclarationParser::Pfunc_argContext::Pfunc_argContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::NumericContext* varDeclarationParser::Pfunc_argContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}

varDeclarationParser::BooleanContext* varDeclarationParser::Pfunc_argContext::boolean() {
  return getRuleContext<varDeclarationParser::BooleanContext>(0);
}


size_t varDeclarationParser::Pfunc_argContext::getRuleIndex() const {
  return varDeclarationParser::RulePfunc_arg;
}

void varDeclarationParser::Pfunc_argContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPfunc_arg(this);
}

void varDeclarationParser::Pfunc_argContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPfunc_arg(this);
}

varDeclarationParser::Pfunc_argContext* varDeclarationParser::pfunc_arg() {
  Pfunc_argContext *_localctx = _tracker.createInstance<Pfunc_argContext>(_ctx, getState());
  enterRule(_localctx, 54, varDeclarationParser::RulePfunc_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(361);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(359);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(360);
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

varDeclarationParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::RelopContext::GT() {
  return getToken(varDeclarationParser::GT, 0);
}

tree::TerminalNode* varDeclarationParser::RelopContext::GE() {
  return getToken(varDeclarationParser::GE, 0);
}

tree::TerminalNode* varDeclarationParser::RelopContext::LT() {
  return getToken(varDeclarationParser::LT, 0);
}

tree::TerminalNode* varDeclarationParser::RelopContext::LE() {
  return getToken(varDeclarationParser::LE, 0);
}


size_t varDeclarationParser::RelopContext::getRuleIndex() const {
  return varDeclarationParser::RuleRelop;
}

void varDeclarationParser::RelopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void varDeclarationParser::RelopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}

varDeclarationParser::RelopContext* varDeclarationParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 56, varDeclarationParser::RuleRelop);
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
    setState(363);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 515396075520) != 0))) {
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

varDeclarationParser::Cls_opContext::Cls_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::Cls_opContext::RANGE() {
  return getToken(varDeclarationParser::RANGE, 0);
}

tree::TerminalNode* varDeclarationParser::Cls_opContext::GT() {
  return getToken(varDeclarationParser::GT, 0);
}

tree::TerminalNode* varDeclarationParser::Cls_opContext::GE() {
  return getToken(varDeclarationParser::GE, 0);
}

tree::TerminalNode* varDeclarationParser::Cls_opContext::LT() {
  return getToken(varDeclarationParser::LT, 0);
}

tree::TerminalNode* varDeclarationParser::Cls_opContext::LE() {
  return getToken(varDeclarationParser::LE, 0);
}

tree::TerminalNode* varDeclarationParser::Cls_opContext::EQ() {
  return getToken(varDeclarationParser::EQ, 0);
}


size_t varDeclarationParser::Cls_opContext::getRuleIndex() const {
  return varDeclarationParser::RuleCls_op;
}

void varDeclarationParser::Cls_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCls_op(this);
}

void varDeclarationParser::Cls_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCls_op(this);
}

varDeclarationParser::Cls_opContext* varDeclarationParser::cls_op() {
  Cls_opContext *_localctx = _tracker.createInstance<Cls_opContext>(_ctx, getState());
  enterRule(_localctx, 58, varDeclarationParser::RuleCls_op);
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
    setState(365);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 288231441303601152) != 0))) {
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

bool varDeclarationParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 9: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 11: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);
    case 24: return stringSempred(antlrcpp::downCast<StringContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool varDeclarationParser::booleanSempred(BooleanContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool varDeclarationParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 16);
    case 4: return precpred(_ctx, 15);
    case 5: return precpred(_ctx, 14);
    case 6: return precpred(_ctx, 13);
    case 7: return precpred(_ctx, 11);
    case 8: return precpred(_ctx, 10);
    case 9: return precpred(_ctx, 9);
    case 10: return precpred(_ctx, 8);
    case 11: return precpred(_ctx, 19);
    case 12: return precpred(_ctx, 12);

  default:
    break;
  }
  return true;
}

bool varDeclarationParser::stringSempred(StringContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 13: return precpred(_ctx, 4);
    case 14: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void varDeclarationParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  vardeclarationParserInitialize();
#else
  ::antlr4::internal::call_once(vardeclarationParserOnceFlag, vardeclarationParserInitialize);
#endif
}
