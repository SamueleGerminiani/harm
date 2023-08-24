
// Generated from spot.g4 by ANTLR 4.12.0


#include "spotListener.h"

#include "spotParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SpotParserStaticData final {
  SpotParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SpotParserStaticData(const SpotParserStaticData&) = delete;
  SpotParserStaticData(SpotParserStaticData&&) = delete;
  SpotParserStaticData& operator=(const SpotParserStaticData&) = delete;
  SpotParserStaticData& operator=(SpotParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag spotParserOnceFlag;
SpotParserStaticData *spotParserStaticData = nullptr;

void spotParserInitialize() {
  assert(spotParserStaticData == nullptr);
  auto staticData = std::make_unique<SpotParserStaticData>(
    std::vector<std::string>{
      "file", "formula", "sere", "tformula", "nonTemporalExp", "boolean", 
      "booleanAtom", "logic", "bitSelect", "logicAtom", "numeric", "numericAtom", 
      "relop"
    },
    std::vector<std::string>{
      "", "", "'..&&..'", "", "", "", "", "'$stable'", "'F'", "'G'", "'X'", 
      "'U'", "'R'", "'..'", "'->'", "'=>'", "'<->'", "'xor'", "'[]->'", 
      "'[]=>'", "'|->'", "'|=>'", "'='", "'##'", "';'", "':'", "'first_match'", 
      "", "", "", "", "", "", "", "", "'{'", "'}'", "'['", "']'", "'('", 
      "')'", "", "", "", "", "'+'", "'-'", "'*'", "'/'", "'>'", "'>='", 
      "'<'", "'<='", "'=='", "'!='", "'&'", "'|'", "'^'", "'~'", "'<<'", 
      "'>>'", "'&&'", "'||'", "'!'"
    },
    std::vector<std::string>{
      "", "PLACEHOLDER", "DT_AND", "DT_NEXT", "DT_NEXT_AND", "DT_NCREPS", 
      "SEP", "FUNCTION", "EVENTUALLY", "ALWAYS", "NEXT", "UNTIL", "RELEASE", 
      "DOTS", "IMPL", "IMPL2", "IFF", "XOR", "BIND1", "BIND2", "SEREIMPL1", 
      "SEREIMPL2", "ASS", "DELAY", "SCOL", "COL", "FIRST_MATCH", "BOOLEAN_CONSTANT", 
      "BOOLEAN_VARIABLE", "LOGIC_CONSTANT", "LOGIC_VARIABLE", "SIGN", "CONST_SUFFIX", 
      "NUMERIC_CONSTANT", "NUMERIC_VARIABLE", "LGPAREN", "RGPAREN", "LCPAREN", 
      "RCPAREN", "LPAREN", "RPAREN", "NUMERIC", "VERILOG_BINARY", "GCC_BINARY", 
      "HEX", "PLUS", "MINUS", "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", 
      "NEQ", "BAND", "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", "OR", 
      "NOT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,64,368,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,1,0,1,0,1,0,1,0,1,
  	0,1,0,1,0,1,0,1,0,1,0,3,0,37,8,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,3,1,87,8,1,1,2,1,2,1,2,3,2,92,8,2,1,2,1,2,3,2,96,8,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,
  	2,115,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,3,2,135,8,2,1,2,3,2,138,8,2,1,2,3,2,141,8,2,1,2,3,2,144,8,
  	2,1,2,3,2,147,8,2,1,2,1,2,1,2,1,2,1,2,3,2,154,8,2,1,2,3,2,157,8,2,1,2,
  	3,2,160,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,172,8,2,1,2,3,
  	2,175,8,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,183,8,2,1,2,3,2,186,8,2,1,2,5,2,
  	189,8,2,10,2,12,2,192,9,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,215,8,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,232,8,3,10,3,12,3,235,9,
  	3,1,4,1,4,3,4,239,8,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,3,5,275,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,5,5,289,8,5,10,5,12,5,292,9,5,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,3,7,304,8,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,5,7,329,8,7,10,7,12,7,332,9,
  	7,1,8,1,8,1,8,1,8,3,8,338,8,8,1,8,1,8,1,9,1,9,1,10,1,10,1,10,1,10,1,10,
  	1,10,1,10,3,10,351,8,10,1,10,1,10,1,10,1,10,1,10,1,10,5,10,359,8,10,10,
  	10,12,10,362,9,10,1,11,1,11,1,12,1,12,1,12,0,5,4,6,10,14,20,13,0,2,4,
  	6,8,10,12,14,16,18,20,22,24,0,6,1,0,27,28,1,0,47,48,1,0,45,46,1,0,29,
  	30,1,0,33,34,1,0,49,52,436,0,36,1,0,0,0,2,86,1,0,0,0,4,114,1,0,0,0,6,
  	214,1,0,0,0,8,238,1,0,0,0,10,274,1,0,0,0,12,293,1,0,0,0,14,303,1,0,0,
  	0,16,333,1,0,0,0,18,341,1,0,0,0,20,350,1,0,0,0,22,363,1,0,0,0,24,365,
  	1,0,0,0,26,27,5,9,0,0,27,28,5,39,0,0,28,29,3,2,1,0,29,30,5,40,0,0,30,
  	31,5,0,0,1,31,37,1,0,0,0,32,33,5,9,0,0,33,34,3,2,1,0,34,35,5,0,0,1,35,
  	37,1,0,0,0,36,26,1,0,0,0,36,32,1,0,0,0,37,1,1,0,0,0,38,39,3,6,3,0,39,
  	40,5,14,0,0,40,41,3,6,3,0,41,87,1,0,0,0,42,43,3,6,3,0,43,44,5,15,0,0,
  	44,45,3,6,3,0,45,87,1,0,0,0,46,47,5,35,0,0,47,48,3,4,2,0,48,49,5,36,0,
  	0,49,50,5,37,0,0,50,51,5,38,0,0,51,52,5,14,0,0,52,53,3,6,3,0,53,87,1,
  	0,0,0,54,55,5,35,0,0,55,56,3,4,2,0,56,57,5,36,0,0,57,58,5,37,0,0,58,59,
  	5,38,0,0,59,60,5,15,0,0,60,61,3,6,3,0,61,87,1,0,0,0,62,63,5,35,0,0,63,
  	64,3,4,2,0,64,65,5,36,0,0,65,66,5,18,0,0,66,67,3,6,3,0,67,87,1,0,0,0,
  	68,69,5,35,0,0,69,70,3,4,2,0,70,71,5,36,0,0,71,72,5,19,0,0,72,73,3,6,
  	3,0,73,87,1,0,0,0,74,75,5,35,0,0,75,76,3,4,2,0,76,77,5,36,0,0,77,78,5,
  	20,0,0,78,79,3,6,3,0,79,87,1,0,0,0,80,81,5,35,0,0,81,82,3,4,2,0,82,83,
  	5,36,0,0,83,84,5,21,0,0,84,85,3,6,3,0,85,87,1,0,0,0,86,38,1,0,0,0,86,
  	42,1,0,0,0,86,46,1,0,0,0,86,54,1,0,0,0,86,62,1,0,0,0,86,68,1,0,0,0,86,
  	74,1,0,0,0,86,80,1,0,0,0,87,3,1,0,0,0,88,89,6,2,-1,0,89,115,3,10,5,0,
  	90,92,5,63,0,0,91,90,1,0,0,0,91,92,1,0,0,0,92,93,1,0,0,0,93,115,5,1,0,
  	0,94,96,5,63,0,0,95,94,1,0,0,0,95,96,1,0,0,0,96,97,1,0,0,0,97,98,5,7,
  	0,0,98,99,5,39,0,0,99,100,3,8,4,0,100,101,5,40,0,0,101,115,1,0,0,0,102,
  	115,5,2,0,0,103,104,5,39,0,0,104,105,3,4,2,0,105,106,5,40,0,0,106,115,
  	1,0,0,0,107,108,5,35,0,0,108,109,3,4,2,0,109,110,5,36,0,0,110,115,1,0,
  	0,0,111,115,5,3,0,0,112,115,5,4,0,0,113,115,5,5,0,0,114,88,1,0,0,0,114,
  	91,1,0,0,0,114,95,1,0,0,0,114,102,1,0,0,0,114,103,1,0,0,0,114,107,1,0,
  	0,0,114,111,1,0,0,0,114,112,1,0,0,0,114,113,1,0,0,0,115,190,1,0,0,0,116,
  	117,10,13,0,0,117,118,5,56,0,0,118,189,3,4,2,14,119,120,10,12,0,0,120,
  	121,5,55,0,0,121,189,3,4,2,13,122,123,10,11,0,0,123,124,5,61,0,0,124,
  	189,3,4,2,12,125,126,10,10,0,0,126,127,5,24,0,0,127,189,3,4,2,11,128,
  	129,10,9,0,0,129,130,5,25,0,0,130,189,3,4,2,10,131,132,10,4,0,0,132,134,
  	5,23,0,0,133,135,5,37,0,0,134,133,1,0,0,0,134,135,1,0,0,0,135,137,1,0,
  	0,0,136,138,5,29,0,0,137,136,1,0,0,0,137,138,1,0,0,0,138,140,1,0,0,0,
  	139,141,5,13,0,0,140,139,1,0,0,0,140,141,1,0,0,0,141,143,1,0,0,0,142,
  	144,5,29,0,0,143,142,1,0,0,0,143,144,1,0,0,0,144,146,1,0,0,0,145,147,
  	5,38,0,0,146,145,1,0,0,0,146,147,1,0,0,0,147,148,1,0,0,0,148,189,3,4,
  	2,5,149,150,10,8,0,0,150,151,5,37,0,0,151,153,5,47,0,0,152,154,5,29,0,
  	0,153,152,1,0,0,0,153,154,1,0,0,0,154,156,1,0,0,0,155,157,5,13,0,0,156,
  	155,1,0,0,0,156,157,1,0,0,0,157,159,1,0,0,0,158,160,5,29,0,0,159,158,
  	1,0,0,0,159,160,1,0,0,0,160,161,1,0,0,0,161,189,5,38,0,0,162,163,10,7,
  	0,0,163,164,5,37,0,0,164,165,5,45,0,0,165,189,5,38,0,0,166,167,10,6,0,
  	0,167,168,5,37,0,0,168,169,5,22,0,0,169,171,5,29,0,0,170,172,5,13,0,0,
  	171,170,1,0,0,0,171,172,1,0,0,0,172,174,1,0,0,0,173,175,5,29,0,0,174,
  	173,1,0,0,0,174,175,1,0,0,0,175,176,1,0,0,0,176,189,5,38,0,0,177,178,
  	10,5,0,0,178,179,5,37,0,0,179,180,5,14,0,0,180,182,5,29,0,0,181,183,5,
  	13,0,0,182,181,1,0,0,0,182,183,1,0,0,0,183,185,1,0,0,0,184,186,5,29,0,
  	0,185,184,1,0,0,0,185,186,1,0,0,0,186,187,1,0,0,0,187,189,5,38,0,0,188,
  	116,1,0,0,0,188,119,1,0,0,0,188,122,1,0,0,0,188,125,1,0,0,0,188,128,1,
  	0,0,0,188,131,1,0,0,0,188,149,1,0,0,0,188,162,1,0,0,0,188,166,1,0,0,0,
  	188,177,1,0,0,0,189,192,1,0,0,0,190,188,1,0,0,0,190,191,1,0,0,0,191,5,
  	1,0,0,0,192,190,1,0,0,0,193,194,6,3,-1,0,194,215,3,10,5,0,195,215,5,1,
  	0,0,196,215,5,2,0,0,197,198,5,39,0,0,198,199,3,6,3,0,199,200,5,40,0,0,
  	200,215,1,0,0,0,201,202,5,63,0,0,202,215,3,6,3,9,203,204,5,10,0,0,204,
  	205,5,37,0,0,205,206,5,41,0,0,206,207,5,38,0,0,207,215,3,6,3,3,208,209,
  	5,10,0,0,209,215,3,6,3,2,210,211,5,35,0,0,211,212,3,4,2,0,212,213,5,36,
  	0,0,213,215,1,0,0,0,214,193,1,0,0,0,214,195,1,0,0,0,214,196,1,0,0,0,214,
  	197,1,0,0,0,214,201,1,0,0,0,214,203,1,0,0,0,214,208,1,0,0,0,214,210,1,
  	0,0,0,215,233,1,0,0,0,216,217,10,8,0,0,217,218,5,61,0,0,218,232,3,6,3,
  	9,219,220,10,7,0,0,220,221,5,62,0,0,221,232,3,6,3,8,222,223,10,6,0,0,
  	223,224,5,17,0,0,224,232,3,6,3,7,225,226,10,5,0,0,226,227,5,11,0,0,227,
  	232,3,6,3,6,228,229,10,4,0,0,229,230,5,12,0,0,230,232,3,6,3,5,231,216,
  	1,0,0,0,231,219,1,0,0,0,231,222,1,0,0,0,231,225,1,0,0,0,231,228,1,0,0,
  	0,232,235,1,0,0,0,233,231,1,0,0,0,233,234,1,0,0,0,234,7,1,0,0,0,235,233,
  	1,0,0,0,236,239,5,1,0,0,237,239,3,10,5,0,238,236,1,0,0,0,238,237,1,0,
  	0,0,239,9,1,0,0,0,240,241,6,5,-1,0,241,242,5,63,0,0,242,275,3,10,5,15,
  	243,244,3,14,7,0,244,245,3,24,12,0,245,246,3,14,7,0,246,275,1,0,0,0,247,
  	248,3,20,10,0,248,249,3,24,12,0,249,250,3,20,10,0,250,275,1,0,0,0,251,
  	252,3,14,7,0,252,253,5,53,0,0,253,254,3,14,7,0,254,275,1,0,0,0,255,256,
  	3,20,10,0,256,257,5,53,0,0,257,258,3,20,10,0,258,275,1,0,0,0,259,260,
  	3,14,7,0,260,261,5,54,0,0,261,262,3,14,7,0,262,275,1,0,0,0,263,264,3,
  	20,10,0,264,265,5,54,0,0,265,266,3,20,10,0,266,275,1,0,0,0,267,275,3,
  	12,6,0,268,275,3,14,7,0,269,275,3,20,10,0,270,271,5,39,0,0,271,272,3,
  	10,5,0,272,273,5,40,0,0,273,275,1,0,0,0,274,240,1,0,0,0,274,243,1,0,0,
  	0,274,247,1,0,0,0,274,251,1,0,0,0,274,255,1,0,0,0,274,259,1,0,0,0,274,
  	263,1,0,0,0,274,267,1,0,0,0,274,268,1,0,0,0,274,269,1,0,0,0,274,270,1,
  	0,0,0,275,290,1,0,0,0,276,277,10,10,0,0,277,278,5,53,0,0,278,289,3,10,
  	5,11,279,280,10,7,0,0,280,281,5,54,0,0,281,289,3,10,5,8,282,283,10,6,
  	0,0,283,284,5,61,0,0,284,289,3,10,5,7,285,286,10,5,0,0,286,287,5,62,0,
  	0,287,289,3,10,5,6,288,276,1,0,0,0,288,279,1,0,0,0,288,282,1,0,0,0,288,
  	285,1,0,0,0,289,292,1,0,0,0,290,288,1,0,0,0,290,291,1,0,0,0,291,11,1,
  	0,0,0,292,290,1,0,0,0,293,294,7,0,0,0,294,13,1,0,0,0,295,296,6,7,-1,0,
  	296,297,5,58,0,0,297,304,3,14,7,11,298,304,3,18,9,0,299,300,5,39,0,0,
  	300,301,3,14,7,0,301,302,5,40,0,0,302,304,1,0,0,0,303,295,1,0,0,0,303,
  	298,1,0,0,0,303,299,1,0,0,0,304,330,1,0,0,0,305,306,10,9,0,0,306,307,
  	7,1,0,0,307,329,3,14,7,10,308,309,10,8,0,0,309,310,7,2,0,0,310,329,3,
  	14,7,9,311,312,10,7,0,0,312,313,5,59,0,0,313,329,3,14,7,8,314,315,10,
  	6,0,0,315,316,5,60,0,0,316,329,3,14,7,7,317,318,10,5,0,0,318,319,5,55,
  	0,0,319,329,3,14,7,6,320,321,10,4,0,0,321,322,5,57,0,0,322,329,3,14,7,
  	5,323,324,10,3,0,0,324,325,5,56,0,0,325,329,3,14,7,4,326,327,10,10,0,
  	0,327,329,3,16,8,0,328,305,1,0,0,0,328,308,1,0,0,0,328,311,1,0,0,0,328,
  	314,1,0,0,0,328,317,1,0,0,0,328,320,1,0,0,0,328,323,1,0,0,0,328,326,1,
  	0,0,0,329,332,1,0,0,0,330,328,1,0,0,0,330,331,1,0,0,0,331,15,1,0,0,0,
  	332,330,1,0,0,0,333,334,5,37,0,0,334,337,5,41,0,0,335,336,5,25,0,0,336,
  	338,5,41,0,0,337,335,1,0,0,0,337,338,1,0,0,0,338,339,1,0,0,0,339,340,
  	5,38,0,0,340,17,1,0,0,0,341,342,7,3,0,0,342,19,1,0,0,0,343,344,6,10,-1,
  	0,344,351,3,22,11,0,345,351,3,14,7,0,346,347,5,39,0,0,347,348,3,20,10,
  	0,348,349,5,40,0,0,349,351,1,0,0,0,350,343,1,0,0,0,350,345,1,0,0,0,350,
  	346,1,0,0,0,351,360,1,0,0,0,352,353,10,5,0,0,353,354,7,1,0,0,354,359,
  	3,20,10,6,355,356,10,4,0,0,356,357,7,2,0,0,357,359,3,20,10,5,358,352,
  	1,0,0,0,358,355,1,0,0,0,359,362,1,0,0,0,360,358,1,0,0,0,360,361,1,0,0,
  	0,361,21,1,0,0,0,362,360,1,0,0,0,363,364,7,4,0,0,364,23,1,0,0,0,365,366,
  	7,5,0,0,366,25,1,0,0,0,33,36,86,91,95,114,134,137,140,143,146,153,156,
  	159,171,174,182,185,188,190,214,231,233,238,274,288,290,303,328,330,337,
  	350,358,360
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  spotParserStaticData = staticData.release();
}

}

spotParser::spotParser(TokenStream *input) : spotParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

spotParser::spotParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  spotParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *spotParserStaticData->atn, spotParserStaticData->decisionToDFA, spotParserStaticData->sharedContextCache, options);
}

spotParser::~spotParser() {
  delete _interpreter;
}

const atn::ATN& spotParser::getATN() const {
  return *spotParserStaticData->atn;
}

std::string spotParser::getGrammarFileName() const {
  return "spot.g4";
}

const std::vector<std::string>& spotParser::getRuleNames() const {
  return spotParserStaticData->ruleNames;
}

const dfa::Vocabulary& spotParser::getVocabulary() const {
  return spotParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView spotParser::getSerializedATN() const {
  return spotParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

spotParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::FileContext::ALWAYS() {
  return getToken(spotParser::ALWAYS, 0);
}

tree::TerminalNode* spotParser::FileContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

spotParser::FormulaContext* spotParser::FileContext::formula() {
  return getRuleContext<spotParser::FormulaContext>(0);
}

tree::TerminalNode* spotParser::FileContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode* spotParser::FileContext::EOF() {
  return getToken(spotParser::EOF, 0);
}


size_t spotParser::FileContext::getRuleIndex() const {
  return spotParser::RuleFile;
}

void spotParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void spotParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

spotParser::FileContext* spotParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, spotParser::RuleFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(36);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(26);
      match(spotParser::ALWAYS);
      setState(27);
      match(spotParser::LPAREN);
      setState(28);
      formula();
      setState(29);
      match(spotParser::RPAREN);
      setState(30);
      match(spotParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(32);
      match(spotParser::ALWAYS);
      setState(33);
      formula();
      setState(34);
      match(spotParser::EOF);
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

//----------------- FormulaContext ------------------------------------------------------------------

spotParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<spotParser::TformulaContext *> spotParser::FormulaContext::tformula() {
  return getRuleContexts<spotParser::TformulaContext>();
}

spotParser::TformulaContext* spotParser::FormulaContext::tformula(size_t i) {
  return getRuleContext<spotParser::TformulaContext>(i);
}

tree::TerminalNode* spotParser::FormulaContext::IMPL() {
  return getToken(spotParser::IMPL, 0);
}

tree::TerminalNode* spotParser::FormulaContext::IMPL2() {
  return getToken(spotParser::IMPL2, 0);
}

tree::TerminalNode* spotParser::FormulaContext::LGPAREN() {
  return getToken(spotParser::LGPAREN, 0);
}

spotParser::SereContext* spotParser::FormulaContext::sere() {
  return getRuleContext<spotParser::SereContext>(0);
}

tree::TerminalNode* spotParser::FormulaContext::RGPAREN() {
  return getToken(spotParser::RGPAREN, 0);
}

tree::TerminalNode* spotParser::FormulaContext::LCPAREN() {
  return getToken(spotParser::LCPAREN, 0);
}

tree::TerminalNode* spotParser::FormulaContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

tree::TerminalNode* spotParser::FormulaContext::BIND1() {
  return getToken(spotParser::BIND1, 0);
}

tree::TerminalNode* spotParser::FormulaContext::BIND2() {
  return getToken(spotParser::BIND2, 0);
}

tree::TerminalNode* spotParser::FormulaContext::SEREIMPL1() {
  return getToken(spotParser::SEREIMPL1, 0);
}

tree::TerminalNode* spotParser::FormulaContext::SEREIMPL2() {
  return getToken(spotParser::SEREIMPL2, 0);
}


size_t spotParser::FormulaContext::getRuleIndex() const {
  return spotParser::RuleFormula;
}

void spotParser::FormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormula(this);
}

void spotParser::FormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormula(this);
}

spotParser::FormulaContext* spotParser::formula() {
  FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, getState());
  enterRule(_localctx, 2, spotParser::RuleFormula);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(86);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(38);
      tformula(0);
      setState(39);
      match(spotParser::IMPL);
      setState(40);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(42);
      tformula(0);
      setState(43);
      match(spotParser::IMPL2);
      setState(44);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(46);
      match(spotParser::LGPAREN);
      setState(47);
      sere(0);
      setState(48);
      match(spotParser::RGPAREN);
      setState(49);
      match(spotParser::LCPAREN);
      setState(50);
      match(spotParser::RCPAREN);
      setState(51);
      match(spotParser::IMPL);
      setState(52);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(54);
      match(spotParser::LGPAREN);
      setState(55);
      sere(0);
      setState(56);
      match(spotParser::RGPAREN);
      setState(57);
      match(spotParser::LCPAREN);
      setState(58);
      match(spotParser::RCPAREN);
      setState(59);
      match(spotParser::IMPL2);
      setState(60);
      tformula(0);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(62);
      match(spotParser::LGPAREN);
      setState(63);
      sere(0);
      setState(64);
      match(spotParser::RGPAREN);
      setState(65);
      match(spotParser::BIND1);
      setState(66);
      tformula(0);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(68);
      match(spotParser::LGPAREN);
      setState(69);
      sere(0);
      setState(70);
      match(spotParser::RGPAREN);
      setState(71);
      match(spotParser::BIND2);
      setState(72);
      tformula(0);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(74);
      match(spotParser::LGPAREN);
      setState(75);
      sere(0);
      setState(76);
      match(spotParser::RGPAREN);
      setState(77);
      match(spotParser::SEREIMPL1);
      setState(78);
      tformula(0);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(80);
      match(spotParser::LGPAREN);
      setState(81);
      sere(0);
      setState(82);
      match(spotParser::RGPAREN);
      setState(83);
      match(spotParser::SEREIMPL2);
      setState(84);
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

spotParser::SereContext::SereContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

spotParser::BooleanContext* spotParser::SereContext::boolean() {
  return getRuleContext<spotParser::BooleanContext>(0);
}

tree::TerminalNode* spotParser::SereContext::PLACEHOLDER() {
  return getToken(spotParser::PLACEHOLDER, 0);
}

tree::TerminalNode* spotParser::SereContext::NOT() {
  return getToken(spotParser::NOT, 0);
}

tree::TerminalNode* spotParser::SereContext::FUNCTION() {
  return getToken(spotParser::FUNCTION, 0);
}

tree::TerminalNode* spotParser::SereContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

spotParser::NonTemporalExpContext* spotParser::SereContext::nonTemporalExp() {
  return getRuleContext<spotParser::NonTemporalExpContext>(0);
}

tree::TerminalNode* spotParser::SereContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode* spotParser::SereContext::DT_AND() {
  return getToken(spotParser::DT_AND, 0);
}

std::vector<spotParser::SereContext *> spotParser::SereContext::sere() {
  return getRuleContexts<spotParser::SereContext>();
}

spotParser::SereContext* spotParser::SereContext::sere(size_t i) {
  return getRuleContext<spotParser::SereContext>(i);
}

tree::TerminalNode* spotParser::SereContext::LGPAREN() {
  return getToken(spotParser::LGPAREN, 0);
}

tree::TerminalNode* spotParser::SereContext::RGPAREN() {
  return getToken(spotParser::RGPAREN, 0);
}

tree::TerminalNode* spotParser::SereContext::DT_NEXT() {
  return getToken(spotParser::DT_NEXT, 0);
}

tree::TerminalNode* spotParser::SereContext::DT_NEXT_AND() {
  return getToken(spotParser::DT_NEXT_AND, 0);
}

tree::TerminalNode* spotParser::SereContext::DT_NCREPS() {
  return getToken(spotParser::DT_NCREPS, 0);
}

tree::TerminalNode* spotParser::SereContext::BOR() {
  return getToken(spotParser::BOR, 0);
}

tree::TerminalNode* spotParser::SereContext::BAND() {
  return getToken(spotParser::BAND, 0);
}

tree::TerminalNode* spotParser::SereContext::AND() {
  return getToken(spotParser::AND, 0);
}

tree::TerminalNode* spotParser::SereContext::SCOL() {
  return getToken(spotParser::SCOL, 0);
}

tree::TerminalNode* spotParser::SereContext::COL() {
  return getToken(spotParser::COL, 0);
}

tree::TerminalNode* spotParser::SereContext::DELAY() {
  return getToken(spotParser::DELAY, 0);
}

tree::TerminalNode* spotParser::SereContext::LCPAREN() {
  return getToken(spotParser::LCPAREN, 0);
}

std::vector<tree::TerminalNode *> spotParser::SereContext::LOGIC_CONSTANT() {
  return getTokens(spotParser::LOGIC_CONSTANT);
}

tree::TerminalNode* spotParser::SereContext::LOGIC_CONSTANT(size_t i) {
  return getToken(spotParser::LOGIC_CONSTANT, i);
}

tree::TerminalNode* spotParser::SereContext::DOTS() {
  return getToken(spotParser::DOTS, 0);
}

tree::TerminalNode* spotParser::SereContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

tree::TerminalNode* spotParser::SereContext::TIMES() {
  return getToken(spotParser::TIMES, 0);
}

tree::TerminalNode* spotParser::SereContext::PLUS() {
  return getToken(spotParser::PLUS, 0);
}

tree::TerminalNode* spotParser::SereContext::ASS() {
  return getToken(spotParser::ASS, 0);
}

tree::TerminalNode* spotParser::SereContext::IMPL() {
  return getToken(spotParser::IMPL, 0);
}


size_t spotParser::SereContext::getRuleIndex() const {
  return spotParser::RuleSere;
}

void spotParser::SereContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSere(this);
}

void spotParser::SereContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSere(this);
}


spotParser::SereContext* spotParser::sere() {
   return sere(0);
}

spotParser::SereContext* spotParser::sere(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  spotParser::SereContext *_localctx = _tracker.createInstance<SereContext>(_ctx, parentState);
  spotParser::SereContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, spotParser::RuleSere, precedence);

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
    setState(114);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(89);
      boolean(0);
      break;
    }

    case 2: {
      setState(91);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::NOT) {
        setState(90);
        match(spotParser::NOT);
      }
      setState(93);
      match(spotParser::PLACEHOLDER);
      break;
    }

    case 3: {
      setState(95);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::NOT) {
        setState(94);
        match(spotParser::NOT);
      }
      setState(97);
      match(spotParser::FUNCTION);
      setState(98);
      match(spotParser::LPAREN);
      setState(99);
      nonTemporalExp();
      setState(100);
      match(spotParser::RPAREN);
      break;
    }

    case 4: {
      setState(102);
      match(spotParser::DT_AND);
      break;
    }

    case 5: {
      setState(103);
      match(spotParser::LPAREN);
      setState(104);
      sere(0);
      setState(105);
      match(spotParser::RPAREN);
      break;
    }

    case 6: {
      setState(107);
      match(spotParser::LGPAREN);
      setState(108);
      sere(0);
      setState(109);
      match(spotParser::RGPAREN);
      break;
    }

    case 7: {
      setState(111);
      match(spotParser::DT_NEXT);
      break;
    }

    case 8: {
      setState(112);
      match(spotParser::DT_NEXT_AND);
      break;
    }

    case 9: {
      setState(113);
      match(spotParser::DT_NCREPS);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(190);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(188);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(116);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(117);
          match(spotParser::BOR);
          setState(118);
          sere(14);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(119);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(120);
          match(spotParser::BAND);
          setState(121);
          sere(13);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(122);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(123);
          match(spotParser::AND);
          setState(124);
          sere(12);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(125);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(126);
          match(spotParser::SCOL);
          setState(127);
          sere(11);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(128);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(129);
          match(spotParser::COL);
          setState(130);
          sere(10);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(131);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(132);
          match(spotParser::DELAY);
          setState(134);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::LCPAREN) {
            setState(133);
            match(spotParser::LCPAREN);
          }
          setState(137);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
          case 1: {
            setState(136);
            match(spotParser::LOGIC_CONSTANT);
            break;
          }

          default:
            break;
          }
          setState(140);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(139);
            match(spotParser::DOTS);
          }
          setState(143);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
          case 1: {
            setState(142);
            match(spotParser::LOGIC_CONSTANT);
            break;
          }

          default:
            break;
          }
          setState(146);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::RCPAREN) {
            setState(145);
            match(spotParser::RCPAREN);
          }
          setState(148);
          sere(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(149);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(150);
          match(spotParser::LCPAREN);
          setState(151);
          match(spotParser::TIMES);
          setState(153);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
          case 1: {
            setState(152);
            match(spotParser::LOGIC_CONSTANT);
            break;
          }

          default:
            break;
          }
          setState(156);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(155);
            match(spotParser::DOTS);
          }
          setState(159);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::LOGIC_CONSTANT) {
            setState(158);
            match(spotParser::LOGIC_CONSTANT);
          }
          setState(161);
          match(spotParser::RCPAREN);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(162);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(163);
          match(spotParser::LCPAREN);
          setState(164);
          match(spotParser::PLUS);
          setState(165);
          match(spotParser::RCPAREN);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(166);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(167);
          match(spotParser::LCPAREN);
          setState(168);
          match(spotParser::ASS);
          setState(169);
          match(spotParser::LOGIC_CONSTANT);
          setState(171);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(170);
            match(spotParser::DOTS);
          }
          setState(174);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::LOGIC_CONSTANT) {
            setState(173);
            match(spotParser::LOGIC_CONSTANT);
          }
          setState(176);
          match(spotParser::RCPAREN);
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(177);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(178);
          match(spotParser::LCPAREN);
          setState(179);
          match(spotParser::IMPL);
          setState(180);
          match(spotParser::LOGIC_CONSTANT);
          setState(182);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(181);
            match(spotParser::DOTS);
          }
          setState(185);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::LOGIC_CONSTANT) {
            setState(184);
            match(spotParser::LOGIC_CONSTANT);
          }
          setState(187);
          match(spotParser::RCPAREN);
          break;
        }

        default:
          break;
        } 
      }
      setState(192);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
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

spotParser::TformulaContext::TformulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

spotParser::BooleanContext* spotParser::TformulaContext::boolean() {
  return getRuleContext<spotParser::BooleanContext>(0);
}

tree::TerminalNode* spotParser::TformulaContext::PLACEHOLDER() {
  return getToken(spotParser::PLACEHOLDER, 0);
}

tree::TerminalNode* spotParser::TformulaContext::DT_AND() {
  return getToken(spotParser::DT_AND, 0);
}

tree::TerminalNode* spotParser::TformulaContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

std::vector<spotParser::TformulaContext *> spotParser::TformulaContext::tformula() {
  return getRuleContexts<spotParser::TformulaContext>();
}

spotParser::TformulaContext* spotParser::TformulaContext::tformula(size_t i) {
  return getRuleContext<spotParser::TformulaContext>(i);
}

tree::TerminalNode* spotParser::TformulaContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode* spotParser::TformulaContext::NOT() {
  return getToken(spotParser::NOT, 0);
}

tree::TerminalNode* spotParser::TformulaContext::NEXT() {
  return getToken(spotParser::NEXT, 0);
}

tree::TerminalNode* spotParser::TformulaContext::LCPAREN() {
  return getToken(spotParser::LCPAREN, 0);
}

tree::TerminalNode* spotParser::TformulaContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

tree::TerminalNode* spotParser::TformulaContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

tree::TerminalNode* spotParser::TformulaContext::LGPAREN() {
  return getToken(spotParser::LGPAREN, 0);
}

spotParser::SereContext* spotParser::TformulaContext::sere() {
  return getRuleContext<spotParser::SereContext>(0);
}

tree::TerminalNode* spotParser::TformulaContext::RGPAREN() {
  return getToken(spotParser::RGPAREN, 0);
}

tree::TerminalNode* spotParser::TformulaContext::AND() {
  return getToken(spotParser::AND, 0);
}

tree::TerminalNode* spotParser::TformulaContext::OR() {
  return getToken(spotParser::OR, 0);
}

tree::TerminalNode* spotParser::TformulaContext::XOR() {
  return getToken(spotParser::XOR, 0);
}

tree::TerminalNode* spotParser::TformulaContext::UNTIL() {
  return getToken(spotParser::UNTIL, 0);
}

tree::TerminalNode* spotParser::TformulaContext::RELEASE() {
  return getToken(spotParser::RELEASE, 0);
}


size_t spotParser::TformulaContext::getRuleIndex() const {
  return spotParser::RuleTformula;
}

void spotParser::TformulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTformula(this);
}

void spotParser::TformulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTformula(this);
}


spotParser::TformulaContext* spotParser::tformula() {
   return tformula(0);
}

spotParser::TformulaContext* spotParser::tformula(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  spotParser::TformulaContext *_localctx = _tracker.createInstance<TformulaContext>(_ctx, parentState);
  spotParser::TformulaContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, spotParser::RuleTformula, precedence);

    

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
    setState(214);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(194);
      boolean(0);
      break;
    }

    case 2: {
      setState(195);
      match(spotParser::PLACEHOLDER);
      break;
    }

    case 3: {
      setState(196);
      match(spotParser::DT_AND);
      break;
    }

    case 4: {
      setState(197);
      match(spotParser::LPAREN);
      setState(198);
      tformula(0);
      setState(199);
      match(spotParser::RPAREN);
      break;
    }

    case 5: {
      setState(201);
      match(spotParser::NOT);
      setState(202);
      tformula(9);
      break;
    }

    case 6: {
      setState(203);
      match(spotParser::NEXT);
      setState(204);
      match(spotParser::LCPAREN);
      setState(205);
      match(spotParser::NUMERIC);
      setState(206);
      match(spotParser::RCPAREN);
      setState(207);
      tformula(3);
      break;
    }

    case 7: {
      setState(208);
      match(spotParser::NEXT);
      setState(209);
      tformula(2);
      break;
    }

    case 8: {
      setState(210);
      match(spotParser::LGPAREN);
      setState(211);
      sere(0);
      setState(212);
      match(spotParser::RGPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(233);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(231);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(216);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(217);
          match(spotParser::AND);
          setState(218);
          tformula(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(219);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(220);
          match(spotParser::OR);
          setState(221);
          tformula(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(222);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(223);
          match(spotParser::XOR);
          setState(224);
          tformula(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(225);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(226);
          match(spotParser::UNTIL);
          setState(227);
          tformula(6);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(228);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(229);
          match(spotParser::RELEASE);
          setState(230);
          tformula(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(235);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- NonTemporalExpContext ------------------------------------------------------------------

spotParser::NonTemporalExpContext::NonTemporalExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::NonTemporalExpContext::PLACEHOLDER() {
  return getToken(spotParser::PLACEHOLDER, 0);
}

spotParser::BooleanContext* spotParser::NonTemporalExpContext::boolean() {
  return getRuleContext<spotParser::BooleanContext>(0);
}


size_t spotParser::NonTemporalExpContext::getRuleIndex() const {
  return spotParser::RuleNonTemporalExp;
}

void spotParser::NonTemporalExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNonTemporalExp(this);
}

void spotParser::NonTemporalExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNonTemporalExp(this);
}

spotParser::NonTemporalExpContext* spotParser::nonTemporalExp() {
  NonTemporalExpContext *_localctx = _tracker.createInstance<NonTemporalExpContext>(_ctx, getState());
  enterRule(_localctx, 8, spotParser::RuleNonTemporalExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(238);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::PLACEHOLDER: {
        enterOuterAlt(_localctx, 1);
        setState(236);
        match(spotParser::PLACEHOLDER);
        break;
      }

      case spotParser::BOOLEAN_CONSTANT:
      case spotParser::BOOLEAN_VARIABLE:
      case spotParser::LOGIC_CONSTANT:
      case spotParser::LOGIC_VARIABLE:
      case spotParser::NUMERIC_CONSTANT:
      case spotParser::NUMERIC_VARIABLE:
      case spotParser::LPAREN:
      case spotParser::NEG:
      case spotParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(237);
        boolean(0);
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

//----------------- BooleanContext ------------------------------------------------------------------

spotParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::BooleanContext::NOT() {
  return getToken(spotParser::NOT, 0);
}

std::vector<spotParser::BooleanContext *> spotParser::BooleanContext::boolean() {
  return getRuleContexts<spotParser::BooleanContext>();
}

spotParser::BooleanContext* spotParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<spotParser::BooleanContext>(i);
}

std::vector<spotParser::LogicContext *> spotParser::BooleanContext::logic() {
  return getRuleContexts<spotParser::LogicContext>();
}

spotParser::LogicContext* spotParser::BooleanContext::logic(size_t i) {
  return getRuleContext<spotParser::LogicContext>(i);
}

spotParser::RelopContext* spotParser::BooleanContext::relop() {
  return getRuleContext<spotParser::RelopContext>(0);
}

std::vector<spotParser::NumericContext *> spotParser::BooleanContext::numeric() {
  return getRuleContexts<spotParser::NumericContext>();
}

spotParser::NumericContext* spotParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<spotParser::NumericContext>(i);
}

tree::TerminalNode* spotParser::BooleanContext::EQ() {
  return getToken(spotParser::EQ, 0);
}

tree::TerminalNode* spotParser::BooleanContext::NEQ() {
  return getToken(spotParser::NEQ, 0);
}

spotParser::BooleanAtomContext* spotParser::BooleanContext::booleanAtom() {
  return getRuleContext<spotParser::BooleanAtomContext>(0);
}

tree::TerminalNode* spotParser::BooleanContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

tree::TerminalNode* spotParser::BooleanContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode* spotParser::BooleanContext::AND() {
  return getToken(spotParser::AND, 0);
}

tree::TerminalNode* spotParser::BooleanContext::OR() {
  return getToken(spotParser::OR, 0);
}


size_t spotParser::BooleanContext::getRuleIndex() const {
  return spotParser::RuleBoolean;
}

void spotParser::BooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolean(this);
}

void spotParser::BooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolean(this);
}


spotParser::BooleanContext* spotParser::boolean() {
   return boolean(0);
}

spotParser::BooleanContext* spotParser::boolean(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  spotParser::BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, parentState);
  spotParser::BooleanContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, spotParser::RuleBoolean, precedence);

    

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
    setState(274);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(241);
      match(spotParser::NOT);
      setState(242);
      boolean(15);
      break;
    }

    case 2: {
      setState(243);
      logic(0);
      setState(244);
      relop();
      setState(245);
      logic(0);
      break;
    }

    case 3: {
      setState(247);
      numeric(0);
      setState(248);
      relop();
      setState(249);
      numeric(0);
      break;
    }

    case 4: {
      setState(251);
      logic(0);
      setState(252);
      match(spotParser::EQ);
      setState(253);
      logic(0);
      break;
    }

    case 5: {
      setState(255);
      numeric(0);
      setState(256);
      match(spotParser::EQ);
      setState(257);
      numeric(0);
      break;
    }

    case 6: {
      setState(259);
      logic(0);
      setState(260);
      match(spotParser::NEQ);
      setState(261);
      logic(0);
      break;
    }

    case 7: {
      setState(263);
      numeric(0);
      setState(264);
      match(spotParser::NEQ);
      setState(265);
      numeric(0);
      break;
    }

    case 8: {
      setState(267);
      booleanAtom();
      break;
    }

    case 9: {
      setState(268);
      logic(0);
      break;
    }

    case 10: {
      setState(269);
      numeric(0);
      break;
    }

    case 11: {
      setState(270);
      match(spotParser::LPAREN);
      setState(271);
      boolean(0);
      setState(272);
      match(spotParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(290);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(288);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(276);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(277);
          match(spotParser::EQ);
          setState(278);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(279);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(280);
          match(spotParser::NEQ);
          setState(281);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(282);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(283);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(spotParser::AND);
          setState(284);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(285);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(286);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(spotParser::OR);
          setState(287);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(292);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
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

spotParser::BooleanAtomContext::BooleanAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::BooleanAtomContext::BOOLEAN_CONSTANT() {
  return getToken(spotParser::BOOLEAN_CONSTANT, 0);
}

tree::TerminalNode* spotParser::BooleanAtomContext::BOOLEAN_VARIABLE() {
  return getToken(spotParser::BOOLEAN_VARIABLE, 0);
}


size_t spotParser::BooleanAtomContext::getRuleIndex() const {
  return spotParser::RuleBooleanAtom;
}

void spotParser::BooleanAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanAtom(this);
}

void spotParser::BooleanAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanAtom(this);
}

spotParser::BooleanAtomContext* spotParser::booleanAtom() {
  BooleanAtomContext *_localctx = _tracker.createInstance<BooleanAtomContext>(_ctx, getState());
  enterRule(_localctx, 12, spotParser::RuleBooleanAtom);
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
    setState(293);
    _la = _input->LA(1);
    if (!(_la == spotParser::BOOLEAN_CONSTANT

    || _la == spotParser::BOOLEAN_VARIABLE)) {
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

//----------------- LogicContext ------------------------------------------------------------------

spotParser::LogicContext::LogicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::LogicContext::NEG() {
  return getToken(spotParser::NEG, 0);
}

std::vector<spotParser::LogicContext *> spotParser::LogicContext::logic() {
  return getRuleContexts<spotParser::LogicContext>();
}

spotParser::LogicContext* spotParser::LogicContext::logic(size_t i) {
  return getRuleContext<spotParser::LogicContext>(i);
}

spotParser::LogicAtomContext* spotParser::LogicContext::logicAtom() {
  return getRuleContext<spotParser::LogicAtomContext>(0);
}

tree::TerminalNode* spotParser::LogicContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

tree::TerminalNode* spotParser::LogicContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode* spotParser::LogicContext::TIMES() {
  return getToken(spotParser::TIMES, 0);
}

tree::TerminalNode* spotParser::LogicContext::DIV() {
  return getToken(spotParser::DIV, 0);
}

tree::TerminalNode* spotParser::LogicContext::PLUS() {
  return getToken(spotParser::PLUS, 0);
}

tree::TerminalNode* spotParser::LogicContext::MINUS() {
  return getToken(spotParser::MINUS, 0);
}

tree::TerminalNode* spotParser::LogicContext::LSHIFT() {
  return getToken(spotParser::LSHIFT, 0);
}

tree::TerminalNode* spotParser::LogicContext::RSHIFT() {
  return getToken(spotParser::RSHIFT, 0);
}

tree::TerminalNode* spotParser::LogicContext::BAND() {
  return getToken(spotParser::BAND, 0);
}

tree::TerminalNode* spotParser::LogicContext::BXOR() {
  return getToken(spotParser::BXOR, 0);
}

tree::TerminalNode* spotParser::LogicContext::BOR() {
  return getToken(spotParser::BOR, 0);
}

spotParser::BitSelectContext* spotParser::LogicContext::bitSelect() {
  return getRuleContext<spotParser::BitSelectContext>(0);
}


size_t spotParser::LogicContext::getRuleIndex() const {
  return spotParser::RuleLogic;
}

void spotParser::LogicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic(this);
}

void spotParser::LogicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic(this);
}


spotParser::LogicContext* spotParser::logic() {
   return logic(0);
}

spotParser::LogicContext* spotParser::logic(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  spotParser::LogicContext *_localctx = _tracker.createInstance<LogicContext>(_ctx, parentState);
  spotParser::LogicContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, spotParser::RuleLogic, precedence);

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
    setState(303);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::NEG: {
        setState(296);
        match(spotParser::NEG);
        setState(297);
        logic(11);
        break;
      }

      case spotParser::LOGIC_CONSTANT:
      case spotParser::LOGIC_VARIABLE: {
        setState(298);
        logicAtom();
        break;
      }

      case spotParser::LPAREN: {
        setState(299);
        match(spotParser::LPAREN);
        setState(300);
        logic(0);
        setState(301);
        match(spotParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(330);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(328);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(305);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(306);
          antlrcpp::downCast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == spotParser::TIMES

          || _la == spotParser::DIV)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(307);
          logic(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(308);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(309);
          antlrcpp::downCast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == spotParser::PLUS

          || _la == spotParser::MINUS)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(310);
          logic(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(311);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(312);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::LSHIFT);
          setState(313);
          logic(8);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(314);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(315);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::RSHIFT);
          setState(316);
          logic(7);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(317);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(318);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BAND);
          setState(319);
          logic(6);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(320);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(321);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BXOR);
          setState(322);
          logic(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(323);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(324);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BOR);
          setState(325);
          logic(4);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(326);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(327);
          bitSelect();
          break;
        }

        default:
          break;
        } 
      }
      setState(332);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- BitSelectContext ------------------------------------------------------------------

spotParser::BitSelectContext::BitSelectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::BitSelectContext::LCPAREN() {
  return getToken(spotParser::LCPAREN, 0);
}

std::vector<tree::TerminalNode *> spotParser::BitSelectContext::NUMERIC() {
  return getTokens(spotParser::NUMERIC);
}

tree::TerminalNode* spotParser::BitSelectContext::NUMERIC(size_t i) {
  return getToken(spotParser::NUMERIC, i);
}

tree::TerminalNode* spotParser::BitSelectContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

tree::TerminalNode* spotParser::BitSelectContext::COL() {
  return getToken(spotParser::COL, 0);
}


size_t spotParser::BitSelectContext::getRuleIndex() const {
  return spotParser::RuleBitSelect;
}

void spotParser::BitSelectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitSelect(this);
}

void spotParser::BitSelectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitSelect(this);
}

spotParser::BitSelectContext* spotParser::bitSelect() {
  BitSelectContext *_localctx = _tracker.createInstance<BitSelectContext>(_ctx, getState());
  enterRule(_localctx, 16, spotParser::RuleBitSelect);
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
    setState(333);
    match(spotParser::LCPAREN);
    setState(334);
    match(spotParser::NUMERIC);
    setState(337);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == spotParser::COL) {
      setState(335);
      match(spotParser::COL);
      setState(336);
      match(spotParser::NUMERIC);
    }
    setState(339);
    match(spotParser::RCPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicAtomContext ------------------------------------------------------------------

spotParser::LogicAtomContext::LogicAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::LogicAtomContext::LOGIC_CONSTANT() {
  return getToken(spotParser::LOGIC_CONSTANT, 0);
}

tree::TerminalNode* spotParser::LogicAtomContext::LOGIC_VARIABLE() {
  return getToken(spotParser::LOGIC_VARIABLE, 0);
}


size_t spotParser::LogicAtomContext::getRuleIndex() const {
  return spotParser::RuleLogicAtom;
}

void spotParser::LogicAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicAtom(this);
}

void spotParser::LogicAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicAtom(this);
}

spotParser::LogicAtomContext* spotParser::logicAtom() {
  LogicAtomContext *_localctx = _tracker.createInstance<LogicAtomContext>(_ctx, getState());
  enterRule(_localctx, 18, spotParser::RuleLogicAtom);
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
    setState(341);
    _la = _input->LA(1);
    if (!(_la == spotParser::LOGIC_CONSTANT

    || _la == spotParser::LOGIC_VARIABLE)) {
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

spotParser::NumericContext::NumericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

spotParser::NumericAtomContext* spotParser::NumericContext::numericAtom() {
  return getRuleContext<spotParser::NumericAtomContext>(0);
}

spotParser::LogicContext* spotParser::NumericContext::logic() {
  return getRuleContext<spotParser::LogicContext>(0);
}

tree::TerminalNode* spotParser::NumericContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

std::vector<spotParser::NumericContext *> spotParser::NumericContext::numeric() {
  return getRuleContexts<spotParser::NumericContext>();
}

spotParser::NumericContext* spotParser::NumericContext::numeric(size_t i) {
  return getRuleContext<spotParser::NumericContext>(i);
}

tree::TerminalNode* spotParser::NumericContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode* spotParser::NumericContext::TIMES() {
  return getToken(spotParser::TIMES, 0);
}

tree::TerminalNode* spotParser::NumericContext::DIV() {
  return getToken(spotParser::DIV, 0);
}

tree::TerminalNode* spotParser::NumericContext::PLUS() {
  return getToken(spotParser::PLUS, 0);
}

tree::TerminalNode* spotParser::NumericContext::MINUS() {
  return getToken(spotParser::MINUS, 0);
}


size_t spotParser::NumericContext::getRuleIndex() const {
  return spotParser::RuleNumeric;
}

void spotParser::NumericContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void spotParser::NumericContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}


spotParser::NumericContext* spotParser::numeric() {
   return numeric(0);
}

spotParser::NumericContext* spotParser::numeric(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  spotParser::NumericContext *_localctx = _tracker.createInstance<NumericContext>(_ctx, parentState);
  spotParser::NumericContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 20;
  enterRecursionRule(_localctx, 20, spotParser::RuleNumeric, precedence);

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
    setState(350);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      setState(344);
      numericAtom();
      break;
    }

    case 2: {
      setState(345);
      logic(0);
      break;
    }

    case 3: {
      setState(346);
      match(spotParser::LPAREN);
      setState(347);
      numeric(0);
      setState(348);
      match(spotParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(360);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(358);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(352);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(353);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == spotParser::TIMES

          || _la == spotParser::DIV)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(354);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(355);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(356);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == spotParser::PLUS

          || _la == spotParser::MINUS)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(357);
          numeric(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(362);
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

//----------------- NumericAtomContext ------------------------------------------------------------------

spotParser::NumericAtomContext::NumericAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::NumericAtomContext::NUMERIC_CONSTANT() {
  return getToken(spotParser::NUMERIC_CONSTANT, 0);
}

tree::TerminalNode* spotParser::NumericAtomContext::NUMERIC_VARIABLE() {
  return getToken(spotParser::NUMERIC_VARIABLE, 0);
}


size_t spotParser::NumericAtomContext::getRuleIndex() const {
  return spotParser::RuleNumericAtom;
}

void spotParser::NumericAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericAtom(this);
}

void spotParser::NumericAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericAtom(this);
}

spotParser::NumericAtomContext* spotParser::numericAtom() {
  NumericAtomContext *_localctx = _tracker.createInstance<NumericAtomContext>(_ctx, getState());
  enterRule(_localctx, 22, spotParser::RuleNumericAtom);
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
    if (!(_la == spotParser::NUMERIC_CONSTANT

    || _la == spotParser::NUMERIC_VARIABLE)) {
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

//----------------- RelopContext ------------------------------------------------------------------

spotParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::RelopContext::GT() {
  return getToken(spotParser::GT, 0);
}

tree::TerminalNode* spotParser::RelopContext::GE() {
  return getToken(spotParser::GE, 0);
}

tree::TerminalNode* spotParser::RelopContext::LT() {
  return getToken(spotParser::LT, 0);
}

tree::TerminalNode* spotParser::RelopContext::LE() {
  return getToken(spotParser::LE, 0);
}


size_t spotParser::RelopContext::getRuleIndex() const {
  return spotParser::RuleRelop;
}

void spotParser::RelopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void spotParser::RelopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}

spotParser::RelopContext* spotParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 24, spotParser::RuleRelop);
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
      ((1ULL << _la) & 8444249301319680) != 0))) {
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

bool spotParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return sereSempred(antlrcpp::downCast<SereContext *>(context), predicateIndex);
    case 3: return tformulaSempred(antlrcpp::downCast<TformulaContext *>(context), predicateIndex);
    case 5: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 7: return logicSempred(antlrcpp::downCast<LogicContext *>(context), predicateIndex);
    case 10: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool spotParser::sereSempred(SereContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 13);
    case 1: return precpred(_ctx, 12);
    case 2: return precpred(_ctx, 11);
    case 3: return precpred(_ctx, 10);
    case 4: return precpred(_ctx, 9);
    case 5: return precpred(_ctx, 4);
    case 6: return precpred(_ctx, 8);
    case 7: return precpred(_ctx, 7);
    case 8: return precpred(_ctx, 6);
    case 9: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

bool spotParser::tformulaSempred(TformulaContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 10: return precpred(_ctx, 8);
    case 11: return precpred(_ctx, 7);
    case 12: return precpred(_ctx, 6);
    case 13: return precpred(_ctx, 5);
    case 14: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

bool spotParser::booleanSempred(BooleanContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 15: return precpred(_ctx, 10);
    case 16: return precpred(_ctx, 7);
    case 17: return precpred(_ctx, 6);
    case 18: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

bool spotParser::logicSempred(LogicContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 19: return precpred(_ctx, 9);
    case 20: return precpred(_ctx, 8);
    case 21: return precpred(_ctx, 7);
    case 22: return precpred(_ctx, 6);
    case 23: return precpred(_ctx, 5);
    case 24: return precpred(_ctx, 4);
    case 25: return precpred(_ctx, 3);
    case 26: return precpred(_ctx, 10);

  default:
    break;
  }
  return true;
}

bool spotParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 27: return precpred(_ctx, 5);
    case 28: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void spotParser::initialize() {
  ::antlr4::internal::call_once(spotParserOnceFlag, spotParserInitialize);
}
