
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
      "signCast", "pfunc_arg", "relop", "cls_op"
    },
    std::vector<std::string>{
      "", "','", "", "", "", "", "", "", "", "", "", "", "", "'.substr'", 
      "", "", "'{'", "'}'", "'['", "']'", "'('", "')'", "'inside'", "", 
      "", "", "", "", "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", 
      "'>='", "'<'", "'<='", "'=='", "'!='", "'==='", "'!=='", "'\\u003F'", 
      "'&'", "'|'", "'^'", "'~'", "'<<<'", "'>>>'", "'<<'", "'>>'", "'&&'", 
      "'||'", "'!'", "':'", "'::'", "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "Name", "VARTYPE", "WS", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", 
      "INT_VARIABLE", "CONST_SUFFIX", "LOGIC_VARIABLE", "BIT_VARIABLE", 
      "FLOAT_CONSTANT", "FLOAT_VARIABLE", "SUBSTR", "STRING_CONSTANT", "STRING_VARIABLE", 
      "LCURLY", "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "INSIDE", 
      "SIGN_CAST", "FUNCTION", "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", 
      "VERILOG_BASED", "FILL_LITERAL", "SINGLE_QUOTE", "PLUS", "MINUS", 
      "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "CASE_EQ", "CASE_NEQ", 
      "QUESTION", "BAND", "BOR", "BXOR", "NEG", "ALSHIFT", "ARSHIFT", "LSHIFT", 
      "RSHIFT", "AND", "OR", "NOT", "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,60,376,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,1,0,1,0,1,0,1,1,1,1,3,1,68,8,1,1,1,1,1,1,2,1,2,
  	3,2,74,8,2,1,2,1,2,1,3,1,3,3,3,80,8,3,1,3,1,3,1,4,1,4,3,4,86,8,4,1,4,
  	1,4,1,5,1,5,3,5,92,8,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,7,1,7,3,7,103,8,
  	7,1,7,1,7,1,7,3,7,108,8,7,1,8,1,8,1,8,1,8,3,8,114,8,8,1,8,1,8,1,8,3,8,
  	119,8,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,147,8,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,5,9,158,8,9,10,9,12,9,161,9,9,1,10,1,10,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,3,11,186,8,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,220,
  	8,11,1,11,1,11,5,11,224,8,11,10,11,12,11,227,9,11,1,11,1,11,3,11,231,
  	8,11,1,11,1,11,5,11,235,8,11,10,11,12,11,238,9,11,1,12,1,12,1,12,1,12,
  	4,12,244,8,12,11,12,12,12,245,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,
  	5,12,256,8,12,10,12,12,12,259,9,12,1,12,1,12,1,12,3,12,264,8,12,1,13,
  	1,13,3,13,268,8,13,1,14,1,14,1,14,1,14,3,14,274,8,14,1,14,1,14,1,15,1,
  	15,1,15,3,15,281,8,15,1,15,1,15,1,15,3,15,286,8,15,1,15,1,15,1,16,1,16,
  	1,17,1,17,1,18,1,18,1,19,1,19,3,19,298,8,19,1,20,1,20,1,20,3,20,303,8,
  	20,1,20,3,20,306,8,20,1,21,1,21,1,21,1,21,3,21,312,8,21,1,22,3,22,315,
  	8,22,1,22,1,22,3,22,319,8,22,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,
  	3,24,329,8,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,
  	341,8,24,1,24,5,24,344,8,24,10,24,12,24,347,9,24,1,25,1,25,1,26,1,26,
  	1,26,1,26,1,26,5,26,356,8,26,10,26,12,26,359,9,26,1,26,1,26,1,27,1,27,
  	1,27,1,27,1,27,1,28,1,28,3,28,370,8,28,1,29,1,29,1,30,1,30,1,30,0,3,18,
  	22,48,31,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,
  	44,46,48,50,52,54,56,58,60,0,11,1,0,40,41,1,0,5,6,3,0,32,33,48,48,55,
  	55,1,0,34,35,1,0,32,33,1,0,49,52,1,0,40,43,1,0,11,12,1,0,14,15,1,0,36,
  	39,2,0,36,40,59,59,409,0,62,1,0,0,0,2,65,1,0,0,0,4,73,1,0,0,0,6,79,1,
  	0,0,0,8,85,1,0,0,0,10,91,1,0,0,0,12,95,1,0,0,0,14,98,1,0,0,0,16,109,1,
  	0,0,0,18,146,1,0,0,0,20,162,1,0,0,0,22,185,1,0,0,0,24,263,1,0,0,0,26,
  	267,1,0,0,0,28,269,1,0,0,0,30,277,1,0,0,0,32,289,1,0,0,0,34,291,1,0,0,
  	0,36,293,1,0,0,0,38,297,1,0,0,0,40,305,1,0,0,0,42,311,1,0,0,0,44,318,
  	1,0,0,0,46,320,1,0,0,0,48,328,1,0,0,0,50,348,1,0,0,0,52,350,1,0,0,0,54,
  	362,1,0,0,0,56,369,1,0,0,0,58,371,1,0,0,0,60,373,1,0,0,0,62,63,3,2,1,
  	0,63,64,5,0,0,1,64,1,1,0,0,0,65,67,5,3,0,0,66,68,3,28,14,0,67,66,1,0,
  	0,0,67,68,1,0,0,0,68,69,1,0,0,0,69,70,5,2,0,0,70,3,1,0,0,0,71,74,3,18,
  	9,0,72,74,3,14,7,0,73,71,1,0,0,0,73,72,1,0,0,0,74,75,1,0,0,0,75,76,5,
  	0,0,1,76,5,1,0,0,0,77,80,3,22,11,0,78,80,3,16,8,0,79,77,1,0,0,0,79,78,
  	1,0,0,0,80,81,1,0,0,0,81,82,5,0,0,1,82,7,1,0,0,0,83,86,3,22,11,0,84,86,
  	3,16,8,0,85,83,1,0,0,0,85,84,1,0,0,0,86,87,1,0,0,0,87,88,5,0,0,1,88,9,
  	1,0,0,0,89,92,3,22,11,0,90,92,3,16,8,0,91,89,1,0,0,0,91,90,1,0,0,0,92,
  	93,1,0,0,0,93,94,5,0,0,1,94,11,1,0,0,0,95,96,3,48,24,0,96,97,5,0,0,1,
  	97,13,1,0,0,0,98,99,3,18,9,0,99,102,5,44,0,0,100,103,3,18,9,0,101,103,
  	3,14,7,0,102,100,1,0,0,0,102,101,1,0,0,0,103,104,1,0,0,0,104,107,5,56,
  	0,0,105,108,3,18,9,0,106,108,3,14,7,0,107,105,1,0,0,0,107,106,1,0,0,0,
  	108,15,1,0,0,0,109,110,3,18,9,0,110,113,5,44,0,0,111,114,3,22,11,0,112,
  	114,3,16,8,0,113,111,1,0,0,0,113,112,1,0,0,0,114,115,1,0,0,0,115,118,
  	5,56,0,0,116,119,3,22,11,0,117,119,3,16,8,0,118,116,1,0,0,0,118,117,1,
  	0,0,0,119,17,1,0,0,0,120,121,6,9,-1,0,121,147,3,20,10,0,122,147,3,52,
  	26,0,123,124,3,48,24,0,124,125,3,58,29,0,125,126,3,48,24,0,126,147,1,
  	0,0,0,127,128,3,48,24,0,128,129,5,40,0,0,129,130,3,48,24,0,130,147,1,
  	0,0,0,131,132,3,48,24,0,132,133,5,41,0,0,133,134,3,48,24,0,134,147,1,
  	0,0,0,135,136,5,20,0,0,136,137,3,18,9,0,137,138,5,21,0,0,138,147,1,0,
  	0,0,139,147,3,22,11,0,140,141,5,20,0,0,141,142,3,14,7,0,142,143,5,21,
  	0,0,143,147,1,0,0,0,144,145,5,55,0,0,145,147,3,18,9,4,146,120,1,0,0,0,
  	146,122,1,0,0,0,146,123,1,0,0,0,146,127,1,0,0,0,146,131,1,0,0,0,146,135,
  	1,0,0,0,146,139,1,0,0,0,146,140,1,0,0,0,146,144,1,0,0,0,147,159,1,0,0,
  	0,148,149,10,3,0,0,149,150,7,0,0,0,150,158,3,18,9,4,151,152,10,2,0,0,
  	152,153,5,53,0,0,153,158,3,18,9,3,154,155,10,1,0,0,155,156,5,54,0,0,156,
  	158,3,18,9,2,157,148,1,0,0,0,157,151,1,0,0,0,157,154,1,0,0,0,158,161,
  	1,0,0,0,159,157,1,0,0,0,159,160,1,0,0,0,160,19,1,0,0,0,161,159,1,0,0,
  	0,162,163,7,1,0,0,163,21,1,0,0,0,164,165,6,11,-1,0,165,166,7,2,0,0,166,
  	186,3,22,11,19,167,186,3,52,26,0,168,186,3,54,27,0,169,186,3,38,19,0,
  	170,186,3,42,21,0,171,186,3,46,23,0,172,186,3,24,12,0,173,174,5,20,0,
  	0,174,175,3,22,11,0,175,176,5,21,0,0,176,186,1,0,0,0,177,178,5,20,0,0,
  	178,179,3,16,8,0,179,180,5,21,0,0,180,186,1,0,0,0,181,182,5,20,0,0,182,
  	183,3,18,9,0,183,184,5,21,0,0,184,186,1,0,0,0,185,164,1,0,0,0,185,167,
  	1,0,0,0,185,168,1,0,0,0,185,169,1,0,0,0,185,170,1,0,0,0,185,171,1,0,0,
  	0,185,172,1,0,0,0,185,173,1,0,0,0,185,177,1,0,0,0,185,181,1,0,0,0,186,
  	236,1,0,0,0,187,188,10,16,0,0,188,189,7,3,0,0,189,235,3,22,11,17,190,
  	191,10,15,0,0,191,192,7,4,0,0,192,235,3,22,11,16,193,194,10,14,0,0,194,
  	195,7,5,0,0,195,235,3,22,11,15,196,197,10,13,0,0,197,198,3,58,29,0,198,
  	199,3,22,11,14,199,235,1,0,0,0,200,201,10,11,0,0,201,202,7,6,0,0,202,
  	235,3,22,11,12,203,204,10,10,0,0,204,205,5,45,0,0,205,235,3,22,11,11,
  	206,207,10,9,0,0,207,208,5,47,0,0,208,235,3,22,11,10,209,210,10,8,0,0,
  	210,211,5,46,0,0,211,235,3,22,11,9,212,213,10,20,0,0,213,235,3,28,14,
  	0,214,215,10,12,0,0,215,216,5,22,0,0,216,225,5,16,0,0,217,220,3,36,18,
  	0,218,220,3,30,15,0,219,217,1,0,0,0,219,218,1,0,0,0,220,221,1,0,0,0,221,
  	222,5,1,0,0,222,224,1,0,0,0,223,219,1,0,0,0,224,227,1,0,0,0,225,223,1,
  	0,0,0,225,226,1,0,0,0,226,230,1,0,0,0,227,225,1,0,0,0,228,231,3,36,18,
  	0,229,231,3,30,15,0,230,228,1,0,0,0,230,229,1,0,0,0,231,232,1,0,0,0,232,
  	233,5,17,0,0,233,235,1,0,0,0,234,187,1,0,0,0,234,190,1,0,0,0,234,193,
  	1,0,0,0,234,196,1,0,0,0,234,200,1,0,0,0,234,203,1,0,0,0,234,206,1,0,0,
  	0,234,209,1,0,0,0,234,212,1,0,0,0,234,214,1,0,0,0,235,238,1,0,0,0,236,
  	234,1,0,0,0,236,237,1,0,0,0,237,23,1,0,0,0,238,236,1,0,0,0,239,240,5,
  	16,0,0,240,243,3,26,13,0,241,242,5,1,0,0,242,244,3,26,13,0,243,241,1,
  	0,0,0,244,245,1,0,0,0,245,243,1,0,0,0,245,246,1,0,0,0,246,247,1,0,0,0,
  	247,248,5,17,0,0,248,264,1,0,0,0,249,250,5,16,0,0,250,251,5,25,0,0,251,
  	252,5,16,0,0,252,257,3,26,13,0,253,254,5,1,0,0,254,256,3,26,13,0,255,
  	253,1,0,0,0,256,259,1,0,0,0,257,255,1,0,0,0,257,258,1,0,0,0,258,260,1,
  	0,0,0,259,257,1,0,0,0,260,261,5,17,0,0,261,262,5,17,0,0,262,264,1,0,0,
  	0,263,239,1,0,0,0,263,249,1,0,0,0,264,25,1,0,0,0,265,268,3,22,11,0,266,
  	268,3,20,10,0,267,265,1,0,0,0,267,266,1,0,0,0,268,27,1,0,0,0,269,270,
  	5,18,0,0,270,273,5,25,0,0,271,272,5,56,0,0,272,274,5,25,0,0,273,271,1,
  	0,0,0,273,274,1,0,0,0,274,275,1,0,0,0,275,276,5,19,0,0,276,29,1,0,0,0,
  	277,280,5,18,0,0,278,281,3,22,11,0,279,281,3,32,16,0,280,278,1,0,0,0,
  	280,279,1,0,0,0,281,282,1,0,0,0,282,285,5,56,0,0,283,286,3,22,11,0,284,
  	286,3,34,17,0,285,283,1,0,0,0,285,284,1,0,0,0,286,287,1,0,0,0,287,288,
  	5,19,0,0,288,31,1,0,0,0,289,290,5,58,0,0,290,33,1,0,0,0,291,292,5,58,
  	0,0,292,35,1,0,0,0,293,294,3,22,11,0,294,37,1,0,0,0,295,298,3,40,20,0,
  	296,298,5,7,0,0,297,295,1,0,0,0,297,296,1,0,0,0,298,39,1,0,0,0,299,306,
  	5,27,0,0,300,302,5,25,0,0,301,303,5,8,0,0,302,301,1,0,0,0,302,303,1,0,
  	0,0,303,306,1,0,0,0,304,306,5,28,0,0,305,299,1,0,0,0,305,300,1,0,0,0,
  	305,304,1,0,0,0,306,41,1,0,0,0,307,312,3,44,22,0,308,312,3,40,20,0,309,
  	312,5,9,0,0,310,312,5,10,0,0,311,307,1,0,0,0,311,308,1,0,0,0,311,309,
  	1,0,0,0,311,310,1,0,0,0,312,43,1,0,0,0,313,315,5,25,0,0,314,313,1,0,0,
  	0,314,315,1,0,0,0,315,316,1,0,0,0,316,319,5,29,0,0,317,319,5,30,0,0,318,
  	314,1,0,0,0,318,317,1,0,0,0,319,45,1,0,0,0,320,321,7,7,0,0,321,47,1,0,
  	0,0,322,323,6,24,-1,0,323,329,3,50,25,0,324,325,5,20,0,0,325,326,3,48,
  	24,0,326,327,5,21,0,0,327,329,1,0,0,0,328,322,1,0,0,0,328,324,1,0,0,0,
  	329,345,1,0,0,0,330,331,10,4,0,0,331,332,5,32,0,0,332,344,3,48,24,5,333,
  	334,10,3,0,0,334,335,5,13,0,0,335,340,5,20,0,0,336,337,5,25,0,0,337,338,
  	5,1,0,0,338,341,5,25,0,0,339,341,5,25,0,0,340,336,1,0,0,0,340,339,1,0,
  	0,0,340,341,1,0,0,0,341,342,1,0,0,0,342,344,5,21,0,0,343,330,1,0,0,0,
  	343,333,1,0,0,0,344,347,1,0,0,0,345,343,1,0,0,0,345,346,1,0,0,0,346,49,
  	1,0,0,0,347,345,1,0,0,0,348,349,7,8,0,0,349,51,1,0,0,0,350,351,5,24,0,
  	0,351,352,5,20,0,0,352,357,3,56,28,0,353,354,5,1,0,0,354,356,3,56,28,
  	0,355,353,1,0,0,0,356,359,1,0,0,0,357,355,1,0,0,0,357,358,1,0,0,0,358,
  	360,1,0,0,0,359,357,1,0,0,0,360,361,5,21,0,0,361,53,1,0,0,0,362,363,5,
  	23,0,0,363,364,5,20,0,0,364,365,3,22,11,0,365,366,5,21,0,0,366,55,1,0,
  	0,0,367,370,3,22,11,0,368,370,3,18,9,0,369,367,1,0,0,0,369,368,1,0,0,
  	0,370,57,1,0,0,0,371,372,7,9,0,0,372,59,1,0,0,0,373,374,7,10,0,0,374,
  	61,1,0,0,0,37,67,73,79,85,91,102,107,113,118,146,157,159,185,219,225,
  	230,234,236,245,257,263,267,273,280,285,297,302,305,311,314,318,328,340,
  	343,345,357,369
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
    setState(62);
    varDec();
    setState(63);
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
    setState(65);
    match(varDeclarationParser::VARTYPE);
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::LSQUARED) {
      setState(66);
      range();
    }
    setState(69);
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
    setState(73);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(71);
      boolean(0);
      break;
    }

    case 2: {
      setState(72);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(75);
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
    setState(79);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(77);
      numeric(0);
      break;
    }

    case 2: {
      setState(78);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(81);
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
    setState(85);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(83);
      numeric(0);
      break;
    }

    case 2: {
      setState(84);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(87);
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
    setState(91);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(89);
      numeric(0);
      break;
    }

    case 2: {
      setState(90);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(93);
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
    setState(95);
    string(0);
    setState(96);
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
    setState(98);
    boolean(0);
    setState(99);
    match(varDeclarationParser::QUESTION);
    setState(102);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(100);
      boolean(0);
      break;
    }

    case 2: {
      setState(101);
      booleanTernary();
      break;
    }

    default:
      break;
    }
    setState(104);
    match(varDeclarationParser::COL);
    setState(107);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(105);
      boolean(0);
      break;
    }

    case 2: {
      setState(106);
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
    setState(109);
    boolean(0);
    setState(110);
    match(varDeclarationParser::QUESTION);
    setState(113);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(111);
      numeric(0);
      break;
    }

    case 2: {
      setState(112);
      numericTernary();
      break;
    }

    default:
      break;
    }
    setState(115);
    match(varDeclarationParser::COL);
    setState(118);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(116);
      numeric(0);
      break;
    }

    case 2: {
      setState(117);
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
    setState(146);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(121);
      booleanAtom();
      break;
    }

    case 2: {
      setState(122);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(123);
      string(0);
      setState(124);
      relop();
      setState(125);
      string(0);
      break;
    }

    case 4: {
      setState(127);
      string(0);
      setState(128);
      match(varDeclarationParser::EQ);
      setState(129);
      string(0);
      break;
    }

    case 5: {
      setState(131);
      string(0);
      setState(132);
      match(varDeclarationParser::NEQ);
      setState(133);
      string(0);
      break;
    }

    case 6: {
      setState(135);
      match(varDeclarationParser::LROUND);
      setState(136);
      boolean(0);
      setState(137);
      match(varDeclarationParser::RROUND);
      break;
    }

    case 7: {
      setState(139);
      numeric(0);
      break;
    }

    case 8: {
      setState(140);
      match(varDeclarationParser::LROUND);
      setState(141);
      booleanTernary();
      setState(142);
      match(varDeclarationParser::RROUND);
      break;
    }

    case 9: {
      setState(144);
      match(varDeclarationParser::NOT);
      setState(145);
      boolean(4);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(159);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(157);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(148);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(149);
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
          setState(150);
          boolean(4);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(151);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(152);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(varDeclarationParser::AND);
          setState(153);
          boolean(3);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(154);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(155);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(varDeclarationParser::OR);
          setState(156);
          boolean(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(161);
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
    setState(162);
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

varDeclarationParser::SignCastContext* varDeclarationParser::NumericContext::signCast() {
  return getRuleContext<varDeclarationParser::SignCastContext>(0);
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
    setState(185);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(165);
      antlrcpp::downCast<NumericContext *>(_localctx)->unop = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 36310284880576512) != 0))) {
        antlrcpp::downCast<NumericContext *>(_localctx)->unop = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(166);
      numeric(19);
      break;
    }

    case 2: {
      setState(167);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(168);
      signCast();
      break;
    }

    case 4: {
      setState(169);
      intAtom();
      break;
    }

    case 5: {
      setState(170);
      logicAtom();
      break;
    }

    case 6: {
      setState(171);
      floatAtom();
      break;
    }

    case 7: {
      setState(172);
      concatenation();
      break;
    }

    case 8: {
      setState(173);
      match(varDeclarationParser::LROUND);
      setState(174);
      numeric(0);
      setState(175);
      match(varDeclarationParser::RROUND);
      break;
    }

    case 9: {
      setState(177);
      match(varDeclarationParser::LROUND);
      setState(178);
      numericTernary();
      setState(179);
      match(varDeclarationParser::RROUND);
      break;
    }

    case 10: {
      setState(181);
      match(varDeclarationParser::LROUND);
      setState(182);
      boolean(0);
      setState(183);
      match(varDeclarationParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(236);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(234);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(187);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(188);
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
          setState(189);
          numeric(17);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(190);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(191);
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
          setState(192);
          numeric(16);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(193);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(194);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 8444249301319680) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->logop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(195);
          numeric(15);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(196);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(197);
          relop();
          setState(198);
          numeric(14);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(200);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(201);
          antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 16492674416640) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(202);
          numeric(12);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(203);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(204);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BAND);
          setState(205);
          numeric(11);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(206);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(207);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BXOR);
          setState(208);
          numeric(10);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(209);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(210);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BOR);
          setState(211);
          numeric(9);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(212);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(213);
          range();
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(214);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(215);
          match(varDeclarationParser::INSIDE);
          setState(216);
          match(varDeclarationParser::LCURLY);
          setState(225);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(219);
              _errHandler->sync(this);
              switch (_input->LA(1)) {
                case varDeclarationParser::INT_VARIABLE:
                case varDeclarationParser::LOGIC_VARIABLE:
                case varDeclarationParser::BIT_VARIABLE:
                case varDeclarationParser::FLOAT_CONSTANT:
                case varDeclarationParser::FLOAT_VARIABLE:
                case varDeclarationParser::LCURLY:
                case varDeclarationParser::LROUND:
                case varDeclarationParser::SIGN_CAST:
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
                  setState(217);
                  sm_constant();
                  break;
                }

                case varDeclarationParser::LSQUARED: {
                  setState(218);
                  sm_range();
                  break;
                }

              default:
                throw NoViableAltException(this);
              }
              setState(221);
              match(varDeclarationParser::T__0); 
            }
            setState(227);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
          }
          setState(230);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case varDeclarationParser::INT_VARIABLE:
            case varDeclarationParser::LOGIC_VARIABLE:
            case varDeclarationParser::BIT_VARIABLE:
            case varDeclarationParser::FLOAT_CONSTANT:
            case varDeclarationParser::FLOAT_VARIABLE:
            case varDeclarationParser::LCURLY:
            case varDeclarationParser::LROUND:
            case varDeclarationParser::SIGN_CAST:
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
              setState(228);
              sm_constant();
              break;
            }

            case varDeclarationParser::LSQUARED: {
              setState(229);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(232);
          match(varDeclarationParser::RCURLY);
          break;
        }

        default:
          break;
        } 
      }
      setState(238);
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
    setState(263);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(239);
      match(varDeclarationParser::LCURLY);
      setState(240);
      concatItem();
      setState(243); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(241);
        match(varDeclarationParser::T__0);
        setState(242);
        concatItem();
        setState(245); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == varDeclarationParser::T__0);
      setState(247);
      match(varDeclarationParser::RCURLY);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(249);
      match(varDeclarationParser::LCURLY);
      setState(250);
      match(varDeclarationParser::UINTEGER);
      setState(251);
      match(varDeclarationParser::LCURLY);
      setState(252);
      concatItem();
      setState(257);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == varDeclarationParser::T__0) {
        setState(253);
        match(varDeclarationParser::T__0);
        setState(254);
        concatItem();
        setState(259);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(260);
      match(varDeclarationParser::RCURLY);
      setState(261);
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
    setState(267);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::BIT_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LCURLY:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::SIGN_CAST:
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
        setState(265);
        numeric(0);
        break;
      }

      case varDeclarationParser::BOOLEAN_CONSTANT:
      case varDeclarationParser::BOOLEAN_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(266);
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
    setState(269);
    match(varDeclarationParser::LSQUARED);
    setState(270);
    match(varDeclarationParser::UINTEGER);
    setState(273);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::COL) {
      setState(271);
      match(varDeclarationParser::COL);
      setState(272);
      match(varDeclarationParser::UINTEGER);
    }
    setState(275);
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
    setState(277);
    match(varDeclarationParser::LSQUARED);
    setState(280);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::BIT_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LCURLY:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::SIGN_CAST:
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
        setState(278);
        numeric(0);
        break;
      }

      case varDeclarationParser::DOLLAR: {
        setState(279);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(282);
    match(varDeclarationParser::COL);
    setState(285);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::BIT_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LCURLY:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::SIGN_CAST:
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
        setState(283);
        numeric(0);
        break;
      }

      case varDeclarationParser::DOLLAR: {
        setState(284);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
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
    setState(289);
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
    setState(291);
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
    setState(293);
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
    setState(297);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(295);
        int_constant();
        break;
      }

      case varDeclarationParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(296);
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
    setState(305);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(299);
        match(varDeclarationParser::GCC_BINARY);
        break;
      }

      case varDeclarationParser::UINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(300);
        match(varDeclarationParser::UINTEGER);
        setState(302);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          setState(301);
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
        setState(304);
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
    setState(311);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(307);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(308);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(309);
      match(varDeclarationParser::LOGIC_VARIABLE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(310);
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
    setState(318);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::VERILOG_BASED: {
        enterOuterAlt(_localctx, 1);
        setState(314);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == varDeclarationParser::UINTEGER) {
          setState(313);
          match(varDeclarationParser::UINTEGER);
        }
        setState(316);
        match(varDeclarationParser::VERILOG_BASED);
        break;
      }

      case varDeclarationParser::FILL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(317);
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
    setState(320);
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
    setState(328);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::STRING_CONSTANT:
      case varDeclarationParser::STRING_VARIABLE: {
        setState(323);
        stringAtom();
        break;
      }

      case varDeclarationParser::LROUND: {
        setState(324);
        match(varDeclarationParser::LROUND);
        setState(325);
        string(0);
        setState(326);
        match(varDeclarationParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(345);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(343);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(330);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(331);
          match(varDeclarationParser::PLUS);
          setState(332);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(333);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(334);
          match(varDeclarationParser::SUBSTR);
          setState(335);
          match(varDeclarationParser::LROUND);
          setState(340);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
          case 1: {
            setState(336);
            match(varDeclarationParser::UINTEGER);
            setState(337);
            match(varDeclarationParser::T__0);
            setState(338);
            match(varDeclarationParser::UINTEGER);
            break;
          }

          case 2: {
            setState(339);
            match(varDeclarationParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(342);
          match(varDeclarationParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(347);
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
    setState(348);
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
    setState(350);
    match(varDeclarationParser::FUNCTION);
    setState(351);
    match(varDeclarationParser::LROUND);
    setState(352);
    pfunc_arg();
    setState(357);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == varDeclarationParser::T__0) {
      setState(353);
      match(varDeclarationParser::T__0);
      setState(354);
      pfunc_arg();
      setState(359);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(360);
    match(varDeclarationParser::RROUND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SignCastContext ------------------------------------------------------------------

varDeclarationParser::SignCastContext::SignCastContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::SignCastContext::SIGN_CAST() {
  return getToken(varDeclarationParser::SIGN_CAST, 0);
}

tree::TerminalNode* varDeclarationParser::SignCastContext::LROUND() {
  return getToken(varDeclarationParser::LROUND, 0);
}

varDeclarationParser::NumericContext* varDeclarationParser::SignCastContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}

tree::TerminalNode* varDeclarationParser::SignCastContext::RROUND() {
  return getToken(varDeclarationParser::RROUND, 0);
}


size_t varDeclarationParser::SignCastContext::getRuleIndex() const {
  return varDeclarationParser::RuleSignCast;
}

void varDeclarationParser::SignCastContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSignCast(this);
}

void varDeclarationParser::SignCastContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSignCast(this);
}

varDeclarationParser::SignCastContext* varDeclarationParser::signCast() {
  SignCastContext *_localctx = _tracker.createInstance<SignCastContext>(_ctx, getState());
  enterRule(_localctx, 54, varDeclarationParser::RuleSignCast);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(362);
    match(varDeclarationParser::SIGN_CAST);
    setState(363);
    match(varDeclarationParser::LROUND);
    setState(364);
    numeric(0);
    setState(365);
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
  enterRule(_localctx, 56, varDeclarationParser::RulePfunc_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(369);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(367);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(368);
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
  enterRule(_localctx, 58, varDeclarationParser::RuleRelop);
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
      ((1ULL << _la) & 1030792151040) != 0))) {
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
  enterRule(_localctx, 60, varDeclarationParser::RuleCls_op);
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
    setState(373);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 576462882607202304) != 0))) {
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
    case 11: return precpred(_ctx, 20);
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
