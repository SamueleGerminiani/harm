
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
      "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", "'>='", "'<'", "'<='", 
      "'=='", "'!='", "'==='", "'!=='", "'\\u003F'", "'&'", "'|'", "'^'", 
      "'~'", "'<<<'", "'>>>'", "'<<'", "'>>'", "'&&'", "'||'", "'!'", "':'", 
      "'::'", "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", "INT_VARIABLE", "CONST_SUFFIX", 
      "LOGIC_VARIABLE", "BIT_VARIABLE", "FLOAT_CONSTANT", "FLOAT_VARIABLE", 
      "SUBSTR", "STRING_CONSTANT", "STRING_VARIABLE", "LCURLY", "RCURLY", 
      "LSQUARED", "RSQUARED", "LROUND", "RROUND", "INSIDE", "FUNCTION", 
      "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", "VERILOG_BASED", "FILL_LITERAL", 
      "SINGLE_QUOTE", "PLUS", "MINUS", "TIMES", "DIV", "GT", "GE", "LT", 
      "LE", "EQ", "NEQ", "CASE_EQ", "CASE_NEQ", "QUESTION", "BAND", "BOR", 
      "BXOR", "NEG", "ALSHIFT", "ARSHIFT", "LSHIFT", "RSHIFT", "AND", "OR", 
      "NOT", "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,57,355,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,1,
  	0,3,0,59,8,0,1,0,1,0,1,1,1,1,3,1,65,8,1,1,1,1,1,1,2,1,2,3,2,71,8,2,1,
  	2,1,2,1,3,1,3,3,3,77,8,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,3,5,88,8,
  	5,1,5,1,5,1,5,3,5,93,8,5,1,6,1,6,1,6,1,6,3,6,99,8,6,1,6,1,6,1,6,3,6,104,
  	8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,132,8,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,5,7,143,8,7,10,7,12,7,146,9,7,1,8,1,8,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,170,
  	8,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,204,
  	8,9,1,9,1,9,5,9,208,8,9,10,9,12,9,211,9,9,1,9,1,9,3,9,215,8,9,1,9,1,9,
  	5,9,219,8,9,10,9,12,9,222,9,9,1,10,1,10,1,10,1,10,4,10,228,8,10,11,10,
  	12,10,229,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,5,10,240,8,10,10,10,
  	12,10,243,9,10,1,10,1,10,1,10,3,10,248,8,10,1,11,1,11,3,11,252,8,11,1,
  	12,1,12,1,12,1,12,3,12,258,8,12,1,12,1,12,1,13,1,13,1,13,3,13,265,8,13,
  	1,13,1,13,1,13,3,13,270,8,13,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,
  	1,17,1,17,3,17,282,8,17,1,18,1,18,1,18,3,18,287,8,18,1,18,3,18,290,8,
  	18,1,19,1,19,1,19,1,19,3,19,296,8,19,1,20,3,20,299,8,20,1,20,1,20,3,20,
  	303,8,20,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,3,22,313,8,22,1,22,1,
  	22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,3,22,325,8,22,1,22,5,22,328,
  	8,22,10,22,12,22,331,9,22,1,23,1,23,1,24,1,24,1,24,1,24,1,24,5,24,340,
  	8,24,10,24,12,24,343,9,24,1,24,1,24,1,25,1,25,3,25,349,8,25,1,26,1,26,
  	1,27,1,27,1,27,0,3,14,18,44,28,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,40,42,44,46,48,50,52,54,0,11,1,0,36,37,1,0,2,3,3,0,28,
  	29,44,44,51,51,1,0,30,31,1,0,28,29,1,0,45,48,1,0,36,39,1,0,8,9,1,0,11,
  	12,1,0,32,35,2,0,32,36,55,55,389,0,58,1,0,0,0,2,64,1,0,0,0,4,70,1,0,0,
  	0,6,76,1,0,0,0,8,80,1,0,0,0,10,83,1,0,0,0,12,94,1,0,0,0,14,131,1,0,0,
  	0,16,147,1,0,0,0,18,169,1,0,0,0,20,247,1,0,0,0,22,251,1,0,0,0,24,253,
  	1,0,0,0,26,261,1,0,0,0,28,273,1,0,0,0,30,275,1,0,0,0,32,277,1,0,0,0,34,
  	281,1,0,0,0,36,289,1,0,0,0,38,295,1,0,0,0,40,302,1,0,0,0,42,304,1,0,0,
  	0,44,312,1,0,0,0,46,332,1,0,0,0,48,334,1,0,0,0,50,348,1,0,0,0,52,350,
  	1,0,0,0,54,352,1,0,0,0,56,59,3,14,7,0,57,59,3,10,5,0,58,56,1,0,0,0,58,
  	57,1,0,0,0,59,60,1,0,0,0,60,61,5,0,0,1,61,1,1,0,0,0,62,65,3,18,9,0,63,
  	65,3,12,6,0,64,62,1,0,0,0,64,63,1,0,0,0,65,66,1,0,0,0,66,67,5,0,0,1,67,
  	3,1,0,0,0,68,71,3,18,9,0,69,71,3,12,6,0,70,68,1,0,0,0,70,69,1,0,0,0,71,
  	72,1,0,0,0,72,73,5,0,0,1,73,5,1,0,0,0,74,77,3,18,9,0,75,77,3,12,6,0,76,
  	74,1,0,0,0,76,75,1,0,0,0,77,78,1,0,0,0,78,79,5,0,0,1,79,7,1,0,0,0,80,
  	81,3,44,22,0,81,82,5,0,0,1,82,9,1,0,0,0,83,84,3,14,7,0,84,87,5,40,0,0,
  	85,88,3,14,7,0,86,88,3,10,5,0,87,85,1,0,0,0,87,86,1,0,0,0,88,89,1,0,0,
  	0,89,92,5,52,0,0,90,93,3,14,7,0,91,93,3,10,5,0,92,90,1,0,0,0,92,91,1,
  	0,0,0,93,11,1,0,0,0,94,95,3,14,7,0,95,98,5,40,0,0,96,99,3,18,9,0,97,99,
  	3,12,6,0,98,96,1,0,0,0,98,97,1,0,0,0,99,100,1,0,0,0,100,103,5,52,0,0,
  	101,104,3,18,9,0,102,104,3,12,6,0,103,101,1,0,0,0,103,102,1,0,0,0,104,
  	13,1,0,0,0,105,106,6,7,-1,0,106,132,3,16,8,0,107,132,3,48,24,0,108,109,
  	3,44,22,0,109,110,3,52,26,0,110,111,3,44,22,0,111,132,1,0,0,0,112,113,
  	3,44,22,0,113,114,5,36,0,0,114,115,3,44,22,0,115,132,1,0,0,0,116,117,
  	3,44,22,0,117,118,5,37,0,0,118,119,3,44,22,0,119,132,1,0,0,0,120,121,
  	5,17,0,0,121,122,3,14,7,0,122,123,5,18,0,0,123,132,1,0,0,0,124,132,3,
  	18,9,0,125,126,5,17,0,0,126,127,3,10,5,0,127,128,5,18,0,0,128,132,1,0,
  	0,0,129,130,5,51,0,0,130,132,3,14,7,4,131,105,1,0,0,0,131,107,1,0,0,0,
  	131,108,1,0,0,0,131,112,1,0,0,0,131,116,1,0,0,0,131,120,1,0,0,0,131,124,
  	1,0,0,0,131,125,1,0,0,0,131,129,1,0,0,0,132,144,1,0,0,0,133,134,10,3,
  	0,0,134,135,7,0,0,0,135,143,3,14,7,4,136,137,10,2,0,0,137,138,5,49,0,
  	0,138,143,3,14,7,3,139,140,10,1,0,0,140,141,5,50,0,0,141,143,3,14,7,2,
  	142,133,1,0,0,0,142,136,1,0,0,0,142,139,1,0,0,0,143,146,1,0,0,0,144,142,
  	1,0,0,0,144,145,1,0,0,0,145,15,1,0,0,0,146,144,1,0,0,0,147,148,7,1,0,
  	0,148,17,1,0,0,0,149,150,6,9,-1,0,150,151,7,2,0,0,151,170,3,18,9,18,152,
  	170,3,48,24,0,153,170,3,34,17,0,154,170,3,38,19,0,155,170,3,42,21,0,156,
  	170,3,20,10,0,157,158,5,17,0,0,158,159,3,18,9,0,159,160,5,18,0,0,160,
  	170,1,0,0,0,161,162,5,17,0,0,162,163,3,12,6,0,163,164,5,18,0,0,164,170,
  	1,0,0,0,165,166,5,17,0,0,166,167,3,14,7,0,167,168,5,18,0,0,168,170,1,
  	0,0,0,169,149,1,0,0,0,169,152,1,0,0,0,169,153,1,0,0,0,169,154,1,0,0,0,
  	169,155,1,0,0,0,169,156,1,0,0,0,169,157,1,0,0,0,169,161,1,0,0,0,169,165,
  	1,0,0,0,170,220,1,0,0,0,171,172,10,16,0,0,172,173,7,3,0,0,173,219,3,18,
  	9,17,174,175,10,15,0,0,175,176,7,4,0,0,176,219,3,18,9,16,177,178,10,14,
  	0,0,178,179,7,5,0,0,179,219,3,18,9,15,180,181,10,13,0,0,181,182,3,52,
  	26,0,182,183,3,18,9,14,183,219,1,0,0,0,184,185,10,11,0,0,185,186,7,6,
  	0,0,186,219,3,18,9,12,187,188,10,10,0,0,188,189,5,41,0,0,189,219,3,18,
  	9,11,190,191,10,9,0,0,191,192,5,43,0,0,192,219,3,18,9,10,193,194,10,8,
  	0,0,194,195,5,42,0,0,195,219,3,18,9,9,196,197,10,19,0,0,197,219,3,24,
  	12,0,198,199,10,12,0,0,199,200,5,19,0,0,200,209,5,13,0,0,201,204,3,32,
  	16,0,202,204,3,26,13,0,203,201,1,0,0,0,203,202,1,0,0,0,204,205,1,0,0,
  	0,205,206,5,1,0,0,206,208,1,0,0,0,207,203,1,0,0,0,208,211,1,0,0,0,209,
  	207,1,0,0,0,209,210,1,0,0,0,210,214,1,0,0,0,211,209,1,0,0,0,212,215,3,
  	32,16,0,213,215,3,26,13,0,214,212,1,0,0,0,214,213,1,0,0,0,215,216,1,0,
  	0,0,216,217,5,14,0,0,217,219,1,0,0,0,218,171,1,0,0,0,218,174,1,0,0,0,
  	218,177,1,0,0,0,218,180,1,0,0,0,218,184,1,0,0,0,218,187,1,0,0,0,218,190,
  	1,0,0,0,218,193,1,0,0,0,218,196,1,0,0,0,218,198,1,0,0,0,219,222,1,0,0,
  	0,220,218,1,0,0,0,220,221,1,0,0,0,221,19,1,0,0,0,222,220,1,0,0,0,223,
  	224,5,13,0,0,224,227,3,22,11,0,225,226,5,1,0,0,226,228,3,22,11,0,227,
  	225,1,0,0,0,228,229,1,0,0,0,229,227,1,0,0,0,229,230,1,0,0,0,230,231,1,
  	0,0,0,231,232,5,14,0,0,232,248,1,0,0,0,233,234,5,13,0,0,234,235,5,21,
  	0,0,235,236,5,13,0,0,236,241,3,22,11,0,237,238,5,1,0,0,238,240,3,22,11,
  	0,239,237,1,0,0,0,240,243,1,0,0,0,241,239,1,0,0,0,241,242,1,0,0,0,242,
  	244,1,0,0,0,243,241,1,0,0,0,244,245,5,14,0,0,245,246,5,14,0,0,246,248,
  	1,0,0,0,247,223,1,0,0,0,247,233,1,0,0,0,248,21,1,0,0,0,249,252,3,18,9,
  	0,250,252,3,16,8,0,251,249,1,0,0,0,251,250,1,0,0,0,252,23,1,0,0,0,253,
  	254,5,15,0,0,254,257,5,21,0,0,255,256,5,52,0,0,256,258,5,21,0,0,257,255,
  	1,0,0,0,257,258,1,0,0,0,258,259,1,0,0,0,259,260,5,16,0,0,260,25,1,0,0,
  	0,261,264,5,15,0,0,262,265,3,18,9,0,263,265,3,28,14,0,264,262,1,0,0,0,
  	264,263,1,0,0,0,265,266,1,0,0,0,266,269,5,52,0,0,267,270,3,18,9,0,268,
  	270,3,30,15,0,269,267,1,0,0,0,269,268,1,0,0,0,270,271,1,0,0,0,271,272,
  	5,16,0,0,272,27,1,0,0,0,273,274,5,54,0,0,274,29,1,0,0,0,275,276,5,54,
  	0,0,276,31,1,0,0,0,277,278,3,18,9,0,278,33,1,0,0,0,279,282,3,36,18,0,
  	280,282,5,4,0,0,281,279,1,0,0,0,281,280,1,0,0,0,282,35,1,0,0,0,283,290,
  	5,23,0,0,284,286,5,21,0,0,285,287,5,5,0,0,286,285,1,0,0,0,286,287,1,0,
  	0,0,287,290,1,0,0,0,288,290,5,24,0,0,289,283,1,0,0,0,289,284,1,0,0,0,
  	289,288,1,0,0,0,290,37,1,0,0,0,291,296,3,40,20,0,292,296,3,36,18,0,293,
  	296,5,6,0,0,294,296,5,7,0,0,295,291,1,0,0,0,295,292,1,0,0,0,295,293,1,
  	0,0,0,295,294,1,0,0,0,296,39,1,0,0,0,297,299,5,21,0,0,298,297,1,0,0,0,
  	298,299,1,0,0,0,299,300,1,0,0,0,300,303,5,25,0,0,301,303,5,26,0,0,302,
  	298,1,0,0,0,302,301,1,0,0,0,303,41,1,0,0,0,304,305,7,7,0,0,305,43,1,0,
  	0,0,306,307,6,22,-1,0,307,313,3,46,23,0,308,309,5,17,0,0,309,310,3,44,
  	22,0,310,311,5,18,0,0,311,313,1,0,0,0,312,306,1,0,0,0,312,308,1,0,0,0,
  	313,329,1,0,0,0,314,315,10,4,0,0,315,316,5,28,0,0,316,328,3,44,22,5,317,
  	318,10,3,0,0,318,319,5,10,0,0,319,324,5,17,0,0,320,321,5,21,0,0,321,322,
  	5,1,0,0,322,325,5,21,0,0,323,325,5,21,0,0,324,320,1,0,0,0,324,323,1,0,
  	0,0,324,325,1,0,0,0,325,326,1,0,0,0,326,328,5,18,0,0,327,314,1,0,0,0,
  	327,317,1,0,0,0,328,331,1,0,0,0,329,327,1,0,0,0,329,330,1,0,0,0,330,45,
  	1,0,0,0,331,329,1,0,0,0,332,333,7,8,0,0,333,47,1,0,0,0,334,335,5,20,0,
  	0,335,336,5,17,0,0,336,341,3,50,25,0,337,338,5,1,0,0,338,340,3,50,25,
  	0,339,337,1,0,0,0,340,343,1,0,0,0,341,339,1,0,0,0,341,342,1,0,0,0,342,
  	344,1,0,0,0,343,341,1,0,0,0,344,345,5,18,0,0,345,49,1,0,0,0,346,349,3,
  	18,9,0,347,349,3,14,7,0,348,346,1,0,0,0,348,347,1,0,0,0,349,51,1,0,0,
  	0,350,351,7,9,0,0,351,53,1,0,0,0,352,353,7,10,0,0,353,55,1,0,0,0,36,58,
  	64,70,76,87,92,98,103,131,142,144,169,203,209,214,218,220,229,241,247,
  	251,257,264,269,281,286,289,295,298,302,312,324,327,329,341,348
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
    setState(131);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(106);
      booleanAtom();
      break;
    }

    case 2: {
      setState(107);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(108);
      string(0);
      setState(109);
      relop();
      setState(110);
      string(0);
      break;
    }

    case 4: {
      setState(112);
      string(0);
      setState(113);
      match(propositionParser::EQ);
      setState(114);
      string(0);
      break;
    }

    case 5: {
      setState(116);
      string(0);
      setState(117);
      match(propositionParser::NEQ);
      setState(118);
      string(0);
      break;
    }

    case 6: {
      setState(120);
      match(propositionParser::LROUND);
      setState(121);
      boolean(0);
      setState(122);
      match(propositionParser::RROUND);
      break;
    }

    case 7: {
      setState(124);
      numeric(0);
      break;
    }

    case 8: {
      setState(125);
      match(propositionParser::LROUND);
      setState(126);
      booleanTernary();
      setState(127);
      match(propositionParser::RROUND);
      break;
    }

    case 9: {
      setState(129);
      match(propositionParser::NOT);
      setState(130);
      boolean(4);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(144);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(142);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(133);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(134);
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
          setState(135);
          boolean(4);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(136);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(137);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::AND);
          setState(138);
          boolean(3);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(139);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(140);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::OR);
          setState(141);
          boolean(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(146);
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
    setState(147);
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
    setState(169);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(150);
      antlrcpp::downCast<NumericContext *>(_localctx)->unop = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 2269392805036032) != 0))) {
        antlrcpp::downCast<NumericContext *>(_localctx)->unop = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(151);
      numeric(18);
      break;
    }

    case 2: {
      setState(152);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(153);
      intAtom();
      break;
    }

    case 4: {
      setState(154);
      logicAtom();
      break;
    }

    case 5: {
      setState(155);
      floatAtom();
      break;
    }

    case 6: {
      setState(156);
      concatenation();
      break;
    }

    case 7: {
      setState(157);
      match(propositionParser::LROUND);
      setState(158);
      numeric(0);
      setState(159);
      match(propositionParser::RROUND);
      break;
    }

    case 8: {
      setState(161);
      match(propositionParser::LROUND);
      setState(162);
      numericTernary();
      setState(163);
      match(propositionParser::RROUND);
      break;
    }

    case 9: {
      setState(165);
      match(propositionParser::LROUND);
      setState(166);
      boolean(0);
      setState(167);
      match(propositionParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(220);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(218);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(171);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(172);
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
          setState(173);
          numeric(17);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(174);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(175);
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
          setState(176);
          numeric(16);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(177);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(178);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 527765581332480) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->logop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(179);
          numeric(15);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(180);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(181);
          relop();
          setState(182);
          numeric(14);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(184);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(185);
          antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 1030792151040) != 0))) {
            antlrcpp::downCast<NumericContext *>(_localctx)->eqop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(186);
          numeric(12);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(187);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(188);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BAND);
          setState(189);
          numeric(11);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(190);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(191);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BXOR);
          setState(192);
          numeric(10);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(193);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(194);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BOR);
          setState(195);
          numeric(9);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(196);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(197);
          range();
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(198);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(199);
          match(propositionParser::INSIDE);
          setState(200);
          match(propositionParser::LCURLY);
          setState(209);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(203);
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
                case propositionParser::UINTEGER:
                case propositionParser::GCC_BINARY:
                case propositionParser::HEX:
                case propositionParser::VERILOG_BASED:
                case propositionParser::FILL_LITERAL:
                case propositionParser::PLUS:
                case propositionParser::MINUS:
                case propositionParser::NEG:
                case propositionParser::NOT: {
                  setState(201);
                  sm_constant();
                  break;
                }

                case propositionParser::LSQUARED: {
                  setState(202);
                  sm_range();
                  break;
                }

              default:
                throw NoViableAltException(this);
              }
              setState(205);
              match(propositionParser::T__0); 
            }
            setState(211);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
          }
          setState(214);
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
            case propositionParser::UINTEGER:
            case propositionParser::GCC_BINARY:
            case propositionParser::HEX:
            case propositionParser::VERILOG_BASED:
            case propositionParser::FILL_LITERAL:
            case propositionParser::PLUS:
            case propositionParser::MINUS:
            case propositionParser::NEG:
            case propositionParser::NOT: {
              setState(212);
              sm_constant();
              break;
            }

            case propositionParser::LSQUARED: {
              setState(213);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(216);
          match(propositionParser::RCURLY);
          break;
        }

        default:
          break;
        } 
      }
      setState(222);
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
    setState(247);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(223);
      match(propositionParser::LCURLY);
      setState(224);
      concatItem();
      setState(227); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(225);
        match(propositionParser::T__0);
        setState(226);
        concatItem();
        setState(229); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == propositionParser::T__0);
      setState(231);
      match(propositionParser::RCURLY);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(233);
      match(propositionParser::LCURLY);
      setState(234);
      match(propositionParser::UINTEGER);
      setState(235);
      match(propositionParser::LCURLY);
      setState(236);
      concatItem();
      setState(241);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == propositionParser::T__0) {
        setState(237);
        match(propositionParser::T__0);
        setState(238);
        concatItem();
        setState(243);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(244);
      match(propositionParser::RCURLY);
      setState(245);
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
    setState(251);
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
        setState(249);
        numeric(0);
        break;
      }

      case propositionParser::BOOLEAN_CONSTANT:
      case propositionParser::BOOLEAN_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(250);
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
    setState(253);
    match(propositionParser::LSQUARED);
    setState(254);
    match(propositionParser::UINTEGER);
    setState(257);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == propositionParser::COL) {
      setState(255);
      match(propositionParser::COL);
      setState(256);
      match(propositionParser::UINTEGER);
    }
    setState(259);
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
    setState(261);
    match(propositionParser::LSQUARED);
    setState(264);
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
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BASED:
      case propositionParser::FILL_LITERAL:
      case propositionParser::PLUS:
      case propositionParser::MINUS:
      case propositionParser::NEG:
      case propositionParser::NOT: {
        setState(262);
        numeric(0);
        break;
      }

      case propositionParser::DOLLAR: {
        setState(263);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(266);
    match(propositionParser::COL);
    setState(269);
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
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BASED:
      case propositionParser::FILL_LITERAL:
      case propositionParser::PLUS:
      case propositionParser::MINUS:
      case propositionParser::NEG:
      case propositionParser::NOT: {
        setState(267);
        numeric(0);
        break;
      }

      case propositionParser::DOLLAR: {
        setState(268);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(271);
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
    setState(273);
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
    setState(275);
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
    setState(277);
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
    setState(281);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(279);
        int_constant();
        break;
      }

      case propositionParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(280);
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
    setState(289);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(283);
        match(propositionParser::GCC_BINARY);
        break;
      }

      case propositionParser::UINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(284);
        match(propositionParser::UINTEGER);
        setState(286);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
        case 1: {
          setState(285);
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
        setState(288);
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
    setState(295);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(291);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(292);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(293);
      match(propositionParser::LOGIC_VARIABLE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(294);
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
    setState(302);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::UINTEGER:
      case propositionParser::VERILOG_BASED: {
        enterOuterAlt(_localctx, 1);
        setState(298);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == propositionParser::UINTEGER) {
          setState(297);
          match(propositionParser::UINTEGER);
        }
        setState(300);
        match(propositionParser::VERILOG_BASED);
        break;
      }

      case propositionParser::FILL_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(301);
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
    setState(304);
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
    setState(312);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::STRING_CONSTANT:
      case propositionParser::STRING_VARIABLE: {
        setState(307);
        stringAtom();
        break;
      }

      case propositionParser::LROUND: {
        setState(308);
        match(propositionParser::LROUND);
        setState(309);
        string(0);
        setState(310);
        match(propositionParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(329);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(327);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(314);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(315);
          match(propositionParser::PLUS);
          setState(316);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(317);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(318);
          match(propositionParser::SUBSTR);
          setState(319);
          match(propositionParser::LROUND);
          setState(324);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
          case 1: {
            setState(320);
            match(propositionParser::UINTEGER);
            setState(321);
            match(propositionParser::T__0);
            setState(322);
            match(propositionParser::UINTEGER);
            break;
          }

          case 2: {
            setState(323);
            match(propositionParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(326);
          match(propositionParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(331);
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
    setState(332);
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
    setState(334);
    match(propositionParser::FUNCTION);
    setState(335);
    match(propositionParser::LROUND);
    setState(336);
    pfunc_arg();
    setState(341);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == propositionParser::T__0) {
      setState(337);
      match(propositionParser::T__0);
      setState(338);
      pfunc_arg();
      setState(343);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(344);
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
    setState(348);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(346);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(347);
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
    setState(350);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 64424509440) != 0))) {
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
    setState(352);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 36028930162950144) != 0))) {
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
    case 11: return precpred(_ctx, 19);
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
