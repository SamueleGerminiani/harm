
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
      "", "','", "", "", "", "", "", "", "", "", "", "", "'.substr'", "", 
      "", "'{'", "'}'", "'['", "']'", "'('", "')'", "'inside'", "", "", 
      "", "", "", "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", 
      "'>='", "'<'", "'<='", "'=='", "'!='", "'==='", "'!=='", "'\\u003F'", 
      "'&'", "'|'", "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'", 
      "':'", "'::'", "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "Name", "VARTYPE", "WS", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", 
      "INT_VARIABLE", "CONST_SUFFIX", "LOGIC_VARIABLE", "FLOAT_CONSTANT", 
      "FLOAT_VARIABLE", "SUBSTR", "STRING_CONSTANT", "STRING_VARIABLE", 
      "LCURLY", "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "INSIDE", 
      "FUNCTION", "SINTEGER", "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", 
      "VERILOG_BASED", "FILL_LITERAL", "SINGLE_QUOTE", "PLUS", "MINUS", 
      "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "CASE_EQ", "CASE_NEQ", 
      "QUESTION", "BAND", "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", 
      "OR", "NOT", "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,57,386,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,1,0,1,0,1,0,1,1,1,1,3,1,66,8,1,1,1,1,1,1,2,1,2,3,2,72,8,
  	2,1,2,1,2,1,3,1,3,3,3,78,8,3,1,3,1,3,1,4,1,4,3,4,84,8,4,1,4,1,4,1,5,1,
  	5,3,5,90,8,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,7,1,7,3,7,101,8,7,1,7,1,7,
  	1,7,3,7,106,8,7,1,8,1,8,1,8,1,8,3,8,112,8,8,1,8,1,8,1,8,3,8,117,8,8,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,128,8,9,1,9,1,9,5,9,132,8,9,10,
  	9,12,9,135,9,9,1,9,1,9,3,9,139,8,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,3,9,185,8,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,5,9,199,
  	8,9,10,9,12,9,202,9,9,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,222,8,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,5,11,247,8,11,10,11,12,11,250,9,11,1,
  	12,1,12,1,12,1,12,4,12,256,8,12,11,12,12,12,257,1,12,1,12,1,12,1,12,1,
  	12,1,12,1,12,1,12,5,12,268,8,12,10,12,12,12,271,9,12,1,12,1,12,1,12,3,
  	12,276,8,12,1,13,1,13,3,13,280,8,13,1,14,1,14,1,14,1,14,3,14,286,8,14,
  	1,14,1,14,1,15,1,15,1,15,3,15,293,8,15,1,15,1,15,1,15,3,15,298,8,15,1,
  	15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,19,1,19,3,19,310,8,19,1,20,1,
  	20,1,20,3,20,315,8,20,1,20,1,20,3,20,319,8,20,1,20,3,20,322,8,20,1,21,
  	1,21,1,21,3,21,327,8,21,1,22,3,22,330,8,22,1,22,1,22,3,22,334,8,22,1,
  	23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,3,24,344,8,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,356,8,24,1,24,5,24,359,8,24,10,
  	24,12,24,362,9,24,1,25,1,25,1,26,1,26,1,26,1,26,1,26,5,26,371,8,26,10,
  	26,12,26,374,9,26,1,26,1,26,1,27,1,27,3,27,380,8,27,1,28,1,28,1,29,1,
  	29,1,29,0,3,18,22,48,30,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,
  	34,36,38,40,42,44,46,48,50,52,54,56,58,0,8,1,0,5,6,1,0,33,34,1,0,31,32,
  	1,0,23,24,1,0,10,11,1,0,13,14,1,0,35,38,2,0,35,39,56,56,424,0,60,1,0,
  	0,0,2,63,1,0,0,0,4,71,1,0,0,0,6,77,1,0,0,0,8,83,1,0,0,0,10,89,1,0,0,0,
  	12,93,1,0,0,0,14,96,1,0,0,0,16,107,1,0,0,0,18,184,1,0,0,0,20,203,1,0,
  	0,0,22,221,1,0,0,0,24,275,1,0,0,0,26,279,1,0,0,0,28,281,1,0,0,0,30,289,
  	1,0,0,0,32,301,1,0,0,0,34,303,1,0,0,0,36,305,1,0,0,0,38,309,1,0,0,0,40,
  	321,1,0,0,0,42,326,1,0,0,0,44,333,1,0,0,0,46,335,1,0,0,0,48,343,1,0,0,
  	0,50,363,1,0,0,0,52,365,1,0,0,0,54,379,1,0,0,0,56,381,1,0,0,0,58,383,
  	1,0,0,0,60,61,3,2,1,0,61,62,5,0,0,1,62,1,1,0,0,0,63,65,5,3,0,0,64,66,
  	3,28,14,0,65,64,1,0,0,0,65,66,1,0,0,0,66,67,1,0,0,0,67,68,5,2,0,0,68,
  	3,1,0,0,0,69,72,3,18,9,0,70,72,3,14,7,0,71,69,1,0,0,0,71,70,1,0,0,0,72,
  	73,1,0,0,0,73,74,5,0,0,1,74,5,1,0,0,0,75,78,3,22,11,0,76,78,3,16,8,0,
  	77,75,1,0,0,0,77,76,1,0,0,0,78,79,1,0,0,0,79,80,5,0,0,1,80,7,1,0,0,0,
  	81,84,3,22,11,0,82,84,3,16,8,0,83,81,1,0,0,0,83,82,1,0,0,0,84,85,1,0,
  	0,0,85,86,5,0,0,1,86,9,1,0,0,0,87,90,3,22,11,0,88,90,3,16,8,0,89,87,1,
  	0,0,0,89,88,1,0,0,0,90,91,1,0,0,0,91,92,5,0,0,1,92,11,1,0,0,0,93,94,3,
  	48,24,0,94,95,5,0,0,1,95,13,1,0,0,0,96,97,3,18,9,0,97,100,5,43,0,0,98,
  	101,3,18,9,0,99,101,3,14,7,0,100,98,1,0,0,0,100,99,1,0,0,0,101,102,1,
  	0,0,0,102,105,5,53,0,0,103,106,3,18,9,0,104,106,3,14,7,0,105,103,1,0,
  	0,0,105,104,1,0,0,0,106,15,1,0,0,0,107,108,3,18,9,0,108,111,5,43,0,0,
  	109,112,3,22,11,0,110,112,3,16,8,0,111,109,1,0,0,0,111,110,1,0,0,0,112,
  	113,1,0,0,0,113,116,5,53,0,0,114,117,3,22,11,0,115,117,3,16,8,0,116,114,
  	1,0,0,0,116,115,1,0,0,0,117,17,1,0,0,0,118,119,6,9,-1,0,119,120,5,52,
  	0,0,120,185,3,18,9,19,121,185,3,52,26,0,122,123,3,22,11,0,123,124,5,21,
  	0,0,124,133,5,15,0,0,125,128,3,36,18,0,126,128,3,30,15,0,127,125,1,0,
  	0,0,127,126,1,0,0,0,128,129,1,0,0,0,129,130,5,1,0,0,130,132,1,0,0,0,131,
  	127,1,0,0,0,132,135,1,0,0,0,133,131,1,0,0,0,133,134,1,0,0,0,134,138,1,
  	0,0,0,135,133,1,0,0,0,136,139,3,36,18,0,137,139,3,30,15,0,138,136,1,0,
  	0,0,138,137,1,0,0,0,139,140,1,0,0,0,140,141,5,16,0,0,141,185,1,0,0,0,
  	142,143,3,22,11,0,143,144,3,56,28,0,144,145,3,22,11,0,145,185,1,0,0,0,
  	146,147,3,22,11,0,147,148,5,39,0,0,148,149,3,22,11,0,149,185,1,0,0,0,
  	150,151,3,22,11,0,151,152,5,40,0,0,152,153,3,22,11,0,153,185,1,0,0,0,
  	154,155,3,22,11,0,155,156,5,41,0,0,156,157,3,22,11,0,157,185,1,0,0,0,
  	158,159,3,22,11,0,159,160,5,42,0,0,160,161,3,22,11,0,161,185,1,0,0,0,
  	162,163,3,48,24,0,163,164,3,56,28,0,164,165,3,48,24,0,165,185,1,0,0,0,
  	166,167,3,48,24,0,167,168,5,39,0,0,168,169,3,48,24,0,169,185,1,0,0,0,
  	170,171,3,48,24,0,171,172,5,40,0,0,172,173,3,48,24,0,173,185,1,0,0,0,
  	174,185,3,20,10,0,175,185,3,22,11,0,176,177,5,19,0,0,177,178,3,18,9,0,
  	178,179,5,20,0,0,179,185,1,0,0,0,180,181,5,19,0,0,181,182,3,14,7,0,182,
  	183,5,20,0,0,183,185,1,0,0,0,184,118,1,0,0,0,184,121,1,0,0,0,184,122,
  	1,0,0,0,184,142,1,0,0,0,184,146,1,0,0,0,184,150,1,0,0,0,184,154,1,0,0,
  	0,184,158,1,0,0,0,184,162,1,0,0,0,184,166,1,0,0,0,184,170,1,0,0,0,184,
  	174,1,0,0,0,184,175,1,0,0,0,184,176,1,0,0,0,184,180,1,0,0,0,185,200,1,
  	0,0,0,186,187,10,8,0,0,187,188,5,39,0,0,188,199,3,18,9,9,189,190,10,7,
  	0,0,190,191,5,40,0,0,191,199,3,18,9,8,192,193,10,6,0,0,193,194,5,50,0,
  	0,194,199,3,18,9,7,195,196,10,5,0,0,196,197,5,51,0,0,197,199,3,18,9,6,
  	198,186,1,0,0,0,198,189,1,0,0,0,198,192,1,0,0,0,198,195,1,0,0,0,199,202,
  	1,0,0,0,200,198,1,0,0,0,200,201,1,0,0,0,201,19,1,0,0,0,202,200,1,0,0,
  	0,203,204,7,0,0,0,204,21,1,0,0,0,205,206,6,11,-1,0,206,207,5,47,0,0,207,
  	222,3,22,11,16,208,222,3,52,26,0,209,222,3,38,19,0,210,222,3,42,21,0,
  	211,222,3,46,23,0,212,222,3,24,12,0,213,214,5,19,0,0,214,215,3,22,11,
  	0,215,216,5,20,0,0,216,222,1,0,0,0,217,218,5,19,0,0,218,219,3,16,8,0,
  	219,220,5,20,0,0,220,222,1,0,0,0,221,205,1,0,0,0,221,208,1,0,0,0,221,
  	209,1,0,0,0,221,210,1,0,0,0,221,211,1,0,0,0,221,212,1,0,0,0,221,213,1,
  	0,0,0,221,217,1,0,0,0,222,248,1,0,0,0,223,224,10,13,0,0,224,225,7,1,0,
  	0,225,247,3,22,11,14,226,227,10,12,0,0,227,228,7,2,0,0,228,247,3,22,11,
  	13,229,230,10,11,0,0,230,231,5,48,0,0,231,247,3,22,11,12,232,233,10,10,
  	0,0,233,234,5,49,0,0,234,247,3,22,11,11,235,236,10,9,0,0,236,237,5,44,
  	0,0,237,247,3,22,11,10,238,239,10,8,0,0,239,240,5,46,0,0,240,247,3,22,
  	11,9,241,242,10,7,0,0,242,243,5,45,0,0,243,247,3,22,11,8,244,245,10,14,
  	0,0,245,247,3,28,14,0,246,223,1,0,0,0,246,226,1,0,0,0,246,229,1,0,0,0,
  	246,232,1,0,0,0,246,235,1,0,0,0,246,238,1,0,0,0,246,241,1,0,0,0,246,244,
  	1,0,0,0,247,250,1,0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,249,23,1,0,0,
  	0,250,248,1,0,0,0,251,252,5,15,0,0,252,255,3,26,13,0,253,254,5,1,0,0,
  	254,256,3,26,13,0,255,253,1,0,0,0,256,257,1,0,0,0,257,255,1,0,0,0,257,
  	258,1,0,0,0,258,259,1,0,0,0,259,260,5,16,0,0,260,276,1,0,0,0,261,262,
  	5,15,0,0,262,263,5,24,0,0,263,264,5,15,0,0,264,269,3,26,13,0,265,266,
  	5,1,0,0,266,268,3,26,13,0,267,265,1,0,0,0,268,271,1,0,0,0,269,267,1,0,
  	0,0,269,270,1,0,0,0,270,272,1,0,0,0,271,269,1,0,0,0,272,273,5,16,0,0,
  	273,274,5,16,0,0,274,276,1,0,0,0,275,251,1,0,0,0,275,261,1,0,0,0,276,
  	25,1,0,0,0,277,280,3,22,11,0,278,280,3,20,10,0,279,277,1,0,0,0,279,278,
  	1,0,0,0,280,27,1,0,0,0,281,282,5,17,0,0,282,285,7,3,0,0,283,284,5,53,
  	0,0,284,286,7,3,0,0,285,283,1,0,0,0,285,286,1,0,0,0,286,287,1,0,0,0,287,
  	288,5,18,0,0,288,29,1,0,0,0,289,292,5,17,0,0,290,293,3,22,11,0,291,293,
  	3,32,16,0,292,290,1,0,0,0,292,291,1,0,0,0,293,294,1,0,0,0,294,297,5,53,
  	0,0,295,298,3,22,11,0,296,298,3,34,17,0,297,295,1,0,0,0,297,296,1,0,0,
  	0,298,299,1,0,0,0,299,300,5,18,0,0,300,31,1,0,0,0,301,302,5,55,0,0,302,
  	33,1,0,0,0,303,304,5,55,0,0,304,35,1,0,0,0,305,306,3,22,11,0,306,37,1,
  	0,0,0,307,310,3,40,20,0,308,310,5,7,0,0,309,307,1,0,0,0,309,308,1,0,0,
  	0,310,39,1,0,0,0,311,322,5,26,0,0,312,314,5,23,0,0,313,315,5,8,0,0,314,
  	313,1,0,0,0,314,315,1,0,0,0,315,322,1,0,0,0,316,318,5,24,0,0,317,319,
  	5,8,0,0,318,317,1,0,0,0,318,319,1,0,0,0,319,322,1,0,0,0,320,322,5,27,
  	0,0,321,311,1,0,0,0,321,312,1,0,0,0,321,316,1,0,0,0,321,320,1,0,0,0,322,
  	41,1,0,0,0,323,327,3,44,22,0,324,327,3,40,20,0,325,327,5,9,0,0,326,323,
  	1,0,0,0,326,324,1,0,0,0,326,325,1,0,0,0,327,43,1,0,0,0,328,330,5,24,0,
  	0,329,328,1,0,0,0,329,330,1,0,0,0,330,331,1,0,0,0,331,334,5,28,0,0,332,
  	334,5,29,0,0,333,329,1,0,0,0,333,332,1,0,0,0,334,45,1,0,0,0,335,336,7,
  	4,0,0,336,47,1,0,0,0,337,338,6,24,-1,0,338,344,3,50,25,0,339,340,5,19,
  	0,0,340,341,3,48,24,0,341,342,5,20,0,0,342,344,1,0,0,0,343,337,1,0,0,
  	0,343,339,1,0,0,0,344,360,1,0,0,0,345,346,10,4,0,0,346,347,5,31,0,0,347,
  	359,3,48,24,5,348,349,10,3,0,0,349,350,5,12,0,0,350,355,5,19,0,0,351,
  	352,5,24,0,0,352,353,5,1,0,0,353,356,5,24,0,0,354,356,5,24,0,0,355,351,
  	1,0,0,0,355,354,1,0,0,0,355,356,1,0,0,0,356,357,1,0,0,0,357,359,5,20,
  	0,0,358,345,1,0,0,0,358,348,1,0,0,0,359,362,1,0,0,0,360,358,1,0,0,0,360,
  	361,1,0,0,0,361,49,1,0,0,0,362,360,1,0,0,0,363,364,7,5,0,0,364,51,1,0,
  	0,0,365,366,5,22,0,0,366,367,5,19,0,0,367,372,3,54,27,0,368,369,5,1,0,
  	0,369,371,3,54,27,0,370,368,1,0,0,0,371,374,1,0,0,0,372,370,1,0,0,0,372,
  	373,1,0,0,0,373,375,1,0,0,0,374,372,1,0,0,0,375,376,5,20,0,0,376,53,1,
  	0,0,0,377,380,3,22,11,0,378,380,3,18,9,0,379,377,1,0,0,0,379,378,1,0,
  	0,0,380,55,1,0,0,0,381,382,7,6,0,0,382,57,1,0,0,0,383,384,7,7,0,0,384,
  	59,1,0,0,0,38,65,71,77,83,89,100,105,111,116,127,133,138,184,198,200,
  	221,246,248,257,269,275,279,285,292,297,309,314,318,321,326,329,333,343,
  	355,358,360,372,379
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

tree::TerminalNode* varDeclarationParser::BooleanContext::NOT() {
  return getToken(varDeclarationParser::NOT, 0);
}

std::vector<varDeclarationParser::BooleanContext *> varDeclarationParser::BooleanContext::boolean() {
  return getRuleContexts<varDeclarationParser::BooleanContext>();
}

varDeclarationParser::BooleanContext* varDeclarationParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<varDeclarationParser::BooleanContext>(i);
}

varDeclarationParser::NonTemporalFunctionContext* varDeclarationParser::BooleanContext::nonTemporalFunction() {
  return getRuleContext<varDeclarationParser::NonTemporalFunctionContext>(0);
}

std::vector<varDeclarationParser::NumericContext *> varDeclarationParser::BooleanContext::numeric() {
  return getRuleContexts<varDeclarationParser::NumericContext>();
}

varDeclarationParser::NumericContext* varDeclarationParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<varDeclarationParser::NumericContext>(i);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::INSIDE() {
  return getToken(varDeclarationParser::INSIDE, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::LCURLY() {
  return getToken(varDeclarationParser::LCURLY, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::RCURLY() {
  return getToken(varDeclarationParser::RCURLY, 0);
}

std::vector<varDeclarationParser::Sm_constantContext *> varDeclarationParser::BooleanContext::sm_constant() {
  return getRuleContexts<varDeclarationParser::Sm_constantContext>();
}

varDeclarationParser::Sm_constantContext* varDeclarationParser::BooleanContext::sm_constant(size_t i) {
  return getRuleContext<varDeclarationParser::Sm_constantContext>(i);
}

std::vector<varDeclarationParser::Sm_rangeContext *> varDeclarationParser::BooleanContext::sm_range() {
  return getRuleContexts<varDeclarationParser::Sm_rangeContext>();
}

varDeclarationParser::Sm_rangeContext* varDeclarationParser::BooleanContext::sm_range(size_t i) {
  return getRuleContext<varDeclarationParser::Sm_rangeContext>(i);
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

tree::TerminalNode* varDeclarationParser::BooleanContext::CASE_EQ() {
  return getToken(varDeclarationParser::CASE_EQ, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::CASE_NEQ() {
  return getToken(varDeclarationParser::CASE_NEQ, 0);
}

std::vector<varDeclarationParser::StringContext *> varDeclarationParser::BooleanContext::string() {
  return getRuleContexts<varDeclarationParser::StringContext>();
}

varDeclarationParser::StringContext* varDeclarationParser::BooleanContext::string(size_t i) {
  return getRuleContext<varDeclarationParser::StringContext>(i);
}

varDeclarationParser::BooleanAtomContext* varDeclarationParser::BooleanContext::booleanAtom() {
  return getRuleContext<varDeclarationParser::BooleanAtomContext>(0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::LROUND() {
  return getToken(varDeclarationParser::LROUND, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::RROUND() {
  return getToken(varDeclarationParser::RROUND, 0);
}

varDeclarationParser::BooleanTernaryContext* varDeclarationParser::BooleanContext::booleanTernary() {
  return getRuleContext<varDeclarationParser::BooleanTernaryContext>(0);
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
    setState(184);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(119);
      match(varDeclarationParser::NOT);
      setState(120);
      boolean(19);
      break;
    }

    case 2: {
      setState(121);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(122);
      numeric(0);
      setState(123);
      match(varDeclarationParser::INSIDE);
      setState(124);
      match(varDeclarationParser::LCURLY);
      setState(133);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(127);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case varDeclarationParser::INT_VARIABLE:
            case varDeclarationParser::LOGIC_VARIABLE:
            case varDeclarationParser::FLOAT_CONSTANT:
            case varDeclarationParser::FLOAT_VARIABLE:
            case varDeclarationParser::LCURLY:
            case varDeclarationParser::LROUND:
            case varDeclarationParser::FUNCTION:
            case varDeclarationParser::SINTEGER:
            case varDeclarationParser::UINTEGER:
            case varDeclarationParser::GCC_BINARY:
            case varDeclarationParser::HEX:
            case varDeclarationParser::VERILOG_BASED:
            case varDeclarationParser::FILL_LITERAL:
            case varDeclarationParser::NEG: {
              setState(125);
              sm_constant();
              break;
            }

            case varDeclarationParser::LSQUARED: {
              setState(126);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(129);
          match(varDeclarationParser::T__0); 
        }
        setState(135);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      }
      setState(138);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case varDeclarationParser::INT_VARIABLE:
        case varDeclarationParser::LOGIC_VARIABLE:
        case varDeclarationParser::FLOAT_CONSTANT:
        case varDeclarationParser::FLOAT_VARIABLE:
        case varDeclarationParser::LCURLY:
        case varDeclarationParser::LROUND:
        case varDeclarationParser::FUNCTION:
        case varDeclarationParser::SINTEGER:
        case varDeclarationParser::UINTEGER:
        case varDeclarationParser::GCC_BINARY:
        case varDeclarationParser::HEX:
        case varDeclarationParser::VERILOG_BASED:
        case varDeclarationParser::FILL_LITERAL:
        case varDeclarationParser::NEG: {
          setState(136);
          sm_constant();
          break;
        }

        case varDeclarationParser::LSQUARED: {
          setState(137);
          sm_range();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(140);
      match(varDeclarationParser::RCURLY);
      break;
    }

    case 4: {
      setState(142);
      numeric(0);
      setState(143);
      relop();
      setState(144);
      numeric(0);
      break;
    }

    case 5: {
      setState(146);
      numeric(0);
      setState(147);
      match(varDeclarationParser::EQ);
      setState(148);
      numeric(0);
      break;
    }

    case 6: {
      setState(150);
      numeric(0);
      setState(151);
      match(varDeclarationParser::NEQ);
      setState(152);
      numeric(0);
      break;
    }

    case 7: {
      setState(154);
      numeric(0);
      setState(155);
      match(varDeclarationParser::CASE_EQ);
      setState(156);
      numeric(0);
      break;
    }

    case 8: {
      setState(158);
      numeric(0);
      setState(159);
      match(varDeclarationParser::CASE_NEQ);
      setState(160);
      numeric(0);
      break;
    }

    case 9: {
      setState(162);
      string(0);
      setState(163);
      relop();
      setState(164);
      string(0);
      break;
    }

    case 10: {
      setState(166);
      string(0);
      setState(167);
      match(varDeclarationParser::EQ);
      setState(168);
      string(0);
      break;
    }

    case 11: {
      setState(170);
      string(0);
      setState(171);
      match(varDeclarationParser::NEQ);
      setState(172);
      string(0);
      break;
    }

    case 12: {
      setState(174);
      booleanAtom();
      break;
    }

    case 13: {
      setState(175);
      numeric(0);
      break;
    }

    case 14: {
      setState(176);
      match(varDeclarationParser::LROUND);
      setState(177);
      boolean(0);
      setState(178);
      match(varDeclarationParser::RROUND);
      break;
    }

    case 15: {
      setState(180);
      match(varDeclarationParser::LROUND);
      setState(181);
      booleanTernary();
      setState(182);
      match(varDeclarationParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(200);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(198);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(186);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(187);
          match(varDeclarationParser::EQ);
          setState(188);
          boolean(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(189);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(190);
          match(varDeclarationParser::NEQ);
          setState(191);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(192);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(193);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(varDeclarationParser::AND);
          setState(194);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(195);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(196);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(varDeclarationParser::OR);
          setState(197);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(202);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
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
    setState(203);
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

tree::TerminalNode* varDeclarationParser::NumericContext::NEG() {
  return getToken(varDeclarationParser::NEG, 0);
}

std::vector<varDeclarationParser::NumericContext *> varDeclarationParser::NumericContext::numeric() {
  return getRuleContexts<varDeclarationParser::NumericContext>();
}

varDeclarationParser::NumericContext* varDeclarationParser::NumericContext::numeric(size_t i) {
  return getRuleContext<varDeclarationParser::NumericContext>(i);
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

tree::TerminalNode* varDeclarationParser::NumericContext::TIMES() {
  return getToken(varDeclarationParser::TIMES, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::DIV() {
  return getToken(varDeclarationParser::DIV, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::PLUS() {
  return getToken(varDeclarationParser::PLUS, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::MINUS() {
  return getToken(varDeclarationParser::MINUS, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::LSHIFT() {
  return getToken(varDeclarationParser::LSHIFT, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::RSHIFT() {
  return getToken(varDeclarationParser::RSHIFT, 0);
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
    setState(221);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(206);
      match(varDeclarationParser::NEG);
      setState(207);
      numeric(16);
      break;
    }

    case 2: {
      setState(208);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(209);
      intAtom();
      break;
    }

    case 4: {
      setState(210);
      logicAtom();
      break;
    }

    case 5: {
      setState(211);
      floatAtom();
      break;
    }

    case 6: {
      setState(212);
      concatenation();
      break;
    }

    case 7: {
      setState(213);
      match(varDeclarationParser::LROUND);
      setState(214);
      numeric(0);
      setState(215);
      match(varDeclarationParser::RROUND);
      break;
    }

    case 8: {
      setState(217);
      match(varDeclarationParser::LROUND);
      setState(218);
      numericTernary();
      setState(219);
      match(varDeclarationParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(248);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(246);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(223);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(224);
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
          setState(225);
          numeric(14);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(226);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(227);
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
          setState(228);
          numeric(13);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(229);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(230);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::LSHIFT);
          setState(231);
          numeric(12);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(232);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(233);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::RSHIFT);
          setState(234);
          numeric(11);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(235);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(236);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BAND);
          setState(237);
          numeric(10);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(238);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(239);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BXOR);
          setState(240);
          numeric(9);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(241);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(242);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BOR);
          setState(243);
          numeric(8);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(244);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(245);
          range();
          break;
        }

        default:
          break;
        } 
      }
      setState(250);
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
    setState(275);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(251);
      match(varDeclarationParser::LCURLY);
      setState(252);
      concatItem();
      setState(255); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(253);
        match(varDeclarationParser::T__0);
        setState(254);
        concatItem();
        setState(257); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == varDeclarationParser::T__0);
      setState(259);
      match(varDeclarationParser::RCURLY);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(261);
      match(varDeclarationParser::LCURLY);
      setState(262);
      match(varDeclarationParser::UINTEGER);
      setState(263);
      match(varDeclarationParser::LCURLY);
      setState(264);
      concatItem();
      setState(269);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == varDeclarationParser::T__0) {
        setState(265);
        match(varDeclarationParser::T__0);
        setState(266);
        concatItem();
        setState(271);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(272);
      match(varDeclarationParser::RCURLY);
      setState(273);
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
    setState(279);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LCURLY:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::FUNCTION:
      case varDeclarationParser::SINTEGER:
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX:
      case varDeclarationParser::VERILOG_BASED:
      case varDeclarationParser::FILL_LITERAL:
      case varDeclarationParser::NEG: {
        enterOuterAlt(_localctx, 1);
        setState(277);
        numeric(0);
        break;
      }

      case varDeclarationParser::BOOLEAN_CONSTANT:
      case varDeclarationParser::BOOLEAN_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(278);
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

tree::TerminalNode* varDeclarationParser::RangeContext::RSQUARED() {
  return getToken(varDeclarationParser::RSQUARED, 0);
}

std::vector<tree::TerminalNode *> varDeclarationParser::RangeContext::SINTEGER() {
  return getTokens(varDeclarationParser::SINTEGER);
}

tree::TerminalNode* varDeclarationParser::RangeContext::SINTEGER(size_t i) {
  return getToken(varDeclarationParser::SINTEGER, i);
}

std::vector<tree::TerminalNode *> varDeclarationParser::RangeContext::UINTEGER() {
  return getTokens(varDeclarationParser::UINTEGER);
}

tree::TerminalNode* varDeclarationParser::RangeContext::UINTEGER(size_t i) {
  return getToken(varDeclarationParser::UINTEGER, i);
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
    setState(281);
    match(varDeclarationParser::LSQUARED);
    setState(282);
    _la = _input->LA(1);
    if (!(_la == varDeclarationParser::SINTEGER

    || _la == varDeclarationParser::UINTEGER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(285);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::COL) {
      setState(283);
      match(varDeclarationParser::COL);
      setState(284);
      _la = _input->LA(1);
      if (!(_la == varDeclarationParser::SINTEGER

      || _la == varDeclarationParser::UINTEGER)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(287);
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
    setState(289);
    match(varDeclarationParser::LSQUARED);
    setState(292);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LCURLY:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::FUNCTION:
      case varDeclarationParser::SINTEGER:
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX:
      case varDeclarationParser::VERILOG_BASED:
      case varDeclarationParser::FILL_LITERAL:
      case varDeclarationParser::NEG: {
        setState(290);
        numeric(0);
        break;
      }

      case varDeclarationParser::DOLLAR: {
        setState(291);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(294);
    match(varDeclarationParser::COL);
    setState(297);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LCURLY:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::FUNCTION:
      case varDeclarationParser::SINTEGER:
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX:
      case varDeclarationParser::VERILOG_BASED:
      case varDeclarationParser::FILL_LITERAL:
      case varDeclarationParser::NEG: {
        setState(295);
        numeric(0);
        break;
      }

      case varDeclarationParser::DOLLAR: {
        setState(296);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(299);
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
    setState(301);
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
    setState(303);
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
    setState(305);
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
    setState(309);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::SINTEGER:
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(307);
        int_constant();
        break;
      }

      case varDeclarationParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(308);
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

tree::TerminalNode* varDeclarationParser::Int_constantContext::SINTEGER() {
  return getToken(varDeclarationParser::SINTEGER, 0);
}

tree::TerminalNode* varDeclarationParser::Int_constantContext::CONST_SUFFIX() {
  return getToken(varDeclarationParser::CONST_SUFFIX, 0);
}

tree::TerminalNode* varDeclarationParser::Int_constantContext::UINTEGER() {
  return getToken(varDeclarationParser::UINTEGER, 0);
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
    setState(321);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(311);
        match(varDeclarationParser::GCC_BINARY);
        break;
      }

      case varDeclarationParser::SINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(312);
        match(varDeclarationParser::SINTEGER);
        setState(314);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          setState(313);
          match(varDeclarationParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case varDeclarationParser::UINTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(316);
        match(varDeclarationParser::UINTEGER);
        setState(318);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
        case 1: {
          setState(317);
          match(varDeclarationParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case varDeclarationParser::HEX: {
        enterOuterAlt(_localctx, 4);
        setState(320);
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
    setState(326);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(323);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(324);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(325);
      match(varDeclarationParser::LOGIC_VARIABLE);
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
    setState(333);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::VERILOG_BASED: {
        enterOuterAlt(_localctx, 1);
        setState(329);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == varDeclarationParser::UINTEGER) {
          setState(328);
          match(varDeclarationParser::UINTEGER);
        }
        setState(331);
        match(varDeclarationParser::VERILOG_BASED);
        break;
      }

      case varDeclarationParser::FILL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(332);
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
    setState(335);
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
    setState(343);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::STRING_CONSTANT:
      case varDeclarationParser::STRING_VARIABLE: {
        setState(338);
        stringAtom();
        break;
      }

      case varDeclarationParser::LROUND: {
        setState(339);
        match(varDeclarationParser::LROUND);
        setState(340);
        string(0);
        setState(341);
        match(varDeclarationParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(360);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(358);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(345);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(346);
          match(varDeclarationParser::PLUS);
          setState(347);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(348);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(349);
          match(varDeclarationParser::SUBSTR);
          setState(350);
          match(varDeclarationParser::LROUND);
          setState(355);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
          case 1: {
            setState(351);
            match(varDeclarationParser::UINTEGER);
            setState(352);
            match(varDeclarationParser::T__0);
            setState(353);
            match(varDeclarationParser::UINTEGER);
            break;
          }

          case 2: {
            setState(354);
            match(varDeclarationParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(357);
          match(varDeclarationParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(362);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
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
    setState(363);
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
    setState(365);
    match(varDeclarationParser::FUNCTION);
    setState(366);
    match(varDeclarationParser::LROUND);
    setState(367);
    pfunc_arg();
    setState(372);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == varDeclarationParser::T__0) {
      setState(368);
      match(varDeclarationParser::T__0);
      setState(369);
      pfunc_arg();
      setState(374);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(375);
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
    setState(379);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(377);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(378);
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
    setState(381);
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
    setState(383);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72058659189817344) != 0))) {
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
    case 0: return precpred(_ctx, 8);
    case 1: return precpred(_ctx, 7);
    case 2: return precpred(_ctx, 6);
    case 3: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

bool varDeclarationParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
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

bool varDeclarationParser::stringSempred(StringContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 12: return precpred(_ctx, 4);
    case 13: return precpred(_ctx, 3);

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
