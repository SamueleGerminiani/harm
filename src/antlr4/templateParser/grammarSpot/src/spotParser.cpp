
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
      "file", "formula", "sere", "tformula", "nonTemporalExp", "placeholder", 
      "dt_next", "dt_next_and", "dt_NCReps", "boolean", "booleanAtom", "booleanConstant", 
      "booleanVariable", "logic", "bitSelect", "logicAtom", "logicConstant", 
      "logicVariable", "numeric", "numericAtom", "numericConstant", "numericVariable", 
      "variable", "relop"
    },
    std::vector<std::string>{
      "", "'P'", "'..##'", "'..#'", "'..[->'", "',bool>'", "',logic('", 
      "','", "')>'", "',numeric('", "'..&&..'", "", "'$stable'", "'F'", 
      "'G'", "'X'", "'U'", "'R'", "'..'", "'->'", "'=>'", "'<->'", "'xor'", 
      "'[]->'", "'[]=>'", "'|->'", "'|=>'", "'='", "'##'", "';'", "':'", 
      "'first_match'", "", "", "'{'", "'}'", "'['", "']'", "'('", "')'", 
      "", "", "", "", "", "", "'+'", "'-'", "'*'", "'/'", "'>'", "'>='", 
      "'<'", "'<='", "'=='", "'!='", "'&'", "'|'", "'^'", "'~'", "'<<'", 
      "'>>'", "'&&'", "'||'", "'!'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "DT_AND", "SEP", "FUNCTION", 
      "EVENTUALLY", "ALWAYS", "NEXT", "UNTIL", "RELEASE", "DOTS", "IMPL", 
      "IMPL2", "IFF", "XOR", "BIND1", "BIND2", "SEREIMPL1", "SEREIMPL2", 
      "ASS", "DELAY", "SCOL", "COL", "FIRST_MATCH", "SIGN", "CONST_SUFFIX", 
      "LGPAREN", "RGPAREN", "LCPAREN", "RCPAREN", "LPAREN", "RPAREN", "VARIABLE", 
      "NUMERIC", "VERILOG_BINARY", "GCC_BINARY", "HEX", "BOOLEAN", "PLUS", 
      "MINUS", "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "BAND", 
      "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,65,462,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,59,
  	8,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,109,8,1,1,
  	2,1,2,1,2,3,2,114,8,2,1,2,1,2,3,2,118,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,136,8,2,1,2,1,2,3,2,140,8,2,1,
  	2,3,2,143,8,2,1,2,3,2,146,8,2,1,2,1,2,1,2,1,2,3,2,152,8,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,172,8,
  	2,1,2,3,2,175,8,2,1,2,3,2,178,8,2,1,2,3,2,181,8,2,1,2,3,2,184,8,2,1,2,
  	1,2,1,2,1,2,1,2,3,2,191,8,2,1,2,3,2,194,8,2,1,2,3,2,197,8,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,209,8,2,1,2,3,2,212,8,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,3,2,220,8,2,1,2,3,2,223,8,2,1,2,5,2,226,8,2,10,2,12,2,229,
  	9,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,3,3,252,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,5,3,269,8,3,10,3,12,3,272,9,3,1,4,1,4,3,4,276,8,4,
  	1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,
  	9,330,8,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,5,9,344,8,9,
  	10,9,12,9,347,9,9,1,10,1,10,3,10,351,8,10,1,11,1,11,1,12,1,12,1,12,1,
  	12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,367,8,13,1,13,1,13,1,
  	13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,
  	13,1,13,1,13,1,13,1,13,1,13,1,13,5,13,392,8,13,10,13,12,13,395,9,13,1,
  	14,1,14,1,14,1,14,3,14,401,8,14,1,14,1,14,1,15,1,15,3,15,407,8,15,1,16,
  	1,16,1,16,1,16,3,16,413,8,16,1,16,3,16,416,8,16,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,433,8,18,1,
  	18,1,18,1,18,1,18,1,18,1,18,5,18,441,8,18,10,18,12,18,444,9,18,1,19,1,
  	19,3,19,448,8,19,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,
  	23,1,23,1,23,0,5,4,6,18,26,36,24,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	28,30,32,34,36,38,40,42,44,46,0,3,1,0,48,49,1,0,46,47,1,0,50,53,531,0,
  	58,1,0,0,0,2,108,1,0,0,0,4,151,1,0,0,0,6,251,1,0,0,0,8,275,1,0,0,0,10,
  	277,1,0,0,0,12,280,1,0,0,0,14,284,1,0,0,0,16,289,1,0,0,0,18,329,1,0,0,
  	0,20,350,1,0,0,0,22,352,1,0,0,0,24,354,1,0,0,0,26,366,1,0,0,0,28,396,
  	1,0,0,0,30,406,1,0,0,0,32,415,1,0,0,0,34,417,1,0,0,0,36,432,1,0,0,0,38,
  	447,1,0,0,0,40,449,1,0,0,0,42,451,1,0,0,0,44,457,1,0,0,0,46,459,1,0,0,
  	0,48,49,5,14,0,0,49,50,3,2,1,0,50,51,5,0,0,1,51,59,1,0,0,0,52,53,5,14,
  	0,0,53,54,5,38,0,0,54,55,3,2,1,0,55,56,5,39,0,0,56,57,5,0,0,1,57,59,1,
  	0,0,0,58,48,1,0,0,0,58,52,1,0,0,0,59,1,1,0,0,0,60,61,3,6,3,0,61,62,5,
  	19,0,0,62,63,3,6,3,0,63,109,1,0,0,0,64,65,3,6,3,0,65,66,5,20,0,0,66,67,
  	3,6,3,0,67,109,1,0,0,0,68,69,5,34,0,0,69,70,3,4,2,0,70,71,5,35,0,0,71,
  	72,5,36,0,0,72,73,5,37,0,0,73,74,5,19,0,0,74,75,3,6,3,0,75,109,1,0,0,
  	0,76,77,5,34,0,0,77,78,3,4,2,0,78,79,5,35,0,0,79,80,5,36,0,0,80,81,5,
  	37,0,0,81,82,5,20,0,0,82,83,3,6,3,0,83,109,1,0,0,0,84,85,5,34,0,0,85,
  	86,3,4,2,0,86,87,5,35,0,0,87,88,5,23,0,0,88,89,3,6,3,0,89,109,1,0,0,0,
  	90,91,5,34,0,0,91,92,3,4,2,0,92,93,5,35,0,0,93,94,5,24,0,0,94,95,3,6,
  	3,0,95,109,1,0,0,0,96,97,5,34,0,0,97,98,3,4,2,0,98,99,5,35,0,0,99,100,
  	5,25,0,0,100,101,3,6,3,0,101,109,1,0,0,0,102,103,5,34,0,0,103,104,3,4,
  	2,0,104,105,5,35,0,0,105,106,5,26,0,0,106,107,3,6,3,0,107,109,1,0,0,0,
  	108,60,1,0,0,0,108,64,1,0,0,0,108,68,1,0,0,0,108,76,1,0,0,0,108,84,1,
  	0,0,0,108,90,1,0,0,0,108,96,1,0,0,0,108,102,1,0,0,0,109,3,1,0,0,0,110,
  	111,6,2,-1,0,111,152,3,18,9,0,112,114,5,64,0,0,113,112,1,0,0,0,113,114,
  	1,0,0,0,114,115,1,0,0,0,115,152,3,10,5,0,116,118,5,64,0,0,117,116,1,0,
  	0,0,117,118,1,0,0,0,118,119,1,0,0,0,119,120,5,12,0,0,120,121,5,38,0,0,
  	121,122,3,8,4,0,122,123,5,39,0,0,123,152,1,0,0,0,124,152,5,10,0,0,125,
  	126,5,38,0,0,126,127,3,4,2,0,127,128,5,39,0,0,128,152,1,0,0,0,129,130,
  	5,34,0,0,130,131,3,4,2,0,131,132,5,35,0,0,132,152,1,0,0,0,133,135,5,28,
  	0,0,134,136,5,36,0,0,135,134,1,0,0,0,135,136,1,0,0,0,136,137,1,0,0,0,
  	137,139,5,41,0,0,138,140,5,18,0,0,139,138,1,0,0,0,139,140,1,0,0,0,140,
  	142,1,0,0,0,141,143,5,41,0,0,142,141,1,0,0,0,142,143,1,0,0,0,143,145,
  	1,0,0,0,144,146,5,37,0,0,145,144,1,0,0,0,145,146,1,0,0,0,146,147,1,0,
  	0,0,147,152,3,4,2,5,148,152,3,12,6,0,149,152,3,14,7,0,150,152,3,16,8,
  	0,151,110,1,0,0,0,151,113,1,0,0,0,151,117,1,0,0,0,151,124,1,0,0,0,151,
  	125,1,0,0,0,151,129,1,0,0,0,151,133,1,0,0,0,151,148,1,0,0,0,151,149,1,
  	0,0,0,151,150,1,0,0,0,152,227,1,0,0,0,153,154,10,14,0,0,154,155,5,57,
  	0,0,155,226,3,4,2,15,156,157,10,13,0,0,157,158,5,56,0,0,158,226,3,4,2,
  	14,159,160,10,12,0,0,160,161,5,62,0,0,161,226,3,4,2,13,162,163,10,11,
  	0,0,163,164,5,29,0,0,164,226,3,4,2,12,165,166,10,10,0,0,166,167,5,30,
  	0,0,167,226,3,4,2,11,168,169,10,4,0,0,169,171,5,28,0,0,170,172,5,36,0,
  	0,171,170,1,0,0,0,171,172,1,0,0,0,172,174,1,0,0,0,173,175,5,41,0,0,174,
  	173,1,0,0,0,174,175,1,0,0,0,175,177,1,0,0,0,176,178,5,18,0,0,177,176,
  	1,0,0,0,177,178,1,0,0,0,178,180,1,0,0,0,179,181,5,41,0,0,180,179,1,0,
  	0,0,180,181,1,0,0,0,181,183,1,0,0,0,182,184,5,37,0,0,183,182,1,0,0,0,
  	183,184,1,0,0,0,184,185,1,0,0,0,185,226,3,4,2,5,186,187,10,9,0,0,187,
  	188,5,36,0,0,188,190,5,48,0,0,189,191,5,41,0,0,190,189,1,0,0,0,190,191,
  	1,0,0,0,191,193,1,0,0,0,192,194,5,18,0,0,193,192,1,0,0,0,193,194,1,0,
  	0,0,194,196,1,0,0,0,195,197,5,41,0,0,196,195,1,0,0,0,196,197,1,0,0,0,
  	197,198,1,0,0,0,198,226,5,37,0,0,199,200,10,8,0,0,200,201,5,36,0,0,201,
  	202,5,46,0,0,202,226,5,37,0,0,203,204,10,7,0,0,204,205,5,36,0,0,205,206,
  	5,27,0,0,206,208,5,41,0,0,207,209,5,18,0,0,208,207,1,0,0,0,208,209,1,
  	0,0,0,209,211,1,0,0,0,210,212,5,41,0,0,211,210,1,0,0,0,211,212,1,0,0,
  	0,212,213,1,0,0,0,213,226,5,37,0,0,214,215,10,6,0,0,215,216,5,36,0,0,
  	216,217,5,19,0,0,217,219,5,41,0,0,218,220,5,18,0,0,219,218,1,0,0,0,219,
  	220,1,0,0,0,220,222,1,0,0,0,221,223,5,41,0,0,222,221,1,0,0,0,222,223,
  	1,0,0,0,223,224,1,0,0,0,224,226,5,37,0,0,225,153,1,0,0,0,225,156,1,0,
  	0,0,225,159,1,0,0,0,225,162,1,0,0,0,225,165,1,0,0,0,225,168,1,0,0,0,225,
  	186,1,0,0,0,225,199,1,0,0,0,225,203,1,0,0,0,225,214,1,0,0,0,226,229,1,
  	0,0,0,227,225,1,0,0,0,227,228,1,0,0,0,228,5,1,0,0,0,229,227,1,0,0,0,230,
  	231,6,3,-1,0,231,252,3,18,9,0,232,252,3,10,5,0,233,252,5,10,0,0,234,235,
  	5,38,0,0,235,236,3,6,3,0,236,237,5,39,0,0,237,252,1,0,0,0,238,239,5,64,
  	0,0,239,252,3,6,3,9,240,241,5,15,0,0,241,242,5,36,0,0,242,243,5,41,0,
  	0,243,244,5,37,0,0,244,252,3,6,3,3,245,246,5,15,0,0,246,252,3,6,3,2,247,
  	248,5,34,0,0,248,249,3,4,2,0,249,250,5,35,0,0,250,252,1,0,0,0,251,230,
  	1,0,0,0,251,232,1,0,0,0,251,233,1,0,0,0,251,234,1,0,0,0,251,238,1,0,0,
  	0,251,240,1,0,0,0,251,245,1,0,0,0,251,247,1,0,0,0,252,270,1,0,0,0,253,
  	254,10,8,0,0,254,255,5,62,0,0,255,269,3,6,3,9,256,257,10,7,0,0,257,258,
  	5,63,0,0,258,269,3,6,3,8,259,260,10,6,0,0,260,261,5,22,0,0,261,269,3,
  	6,3,7,262,263,10,5,0,0,263,264,5,16,0,0,264,269,3,6,3,6,265,266,10,4,
  	0,0,266,267,5,17,0,0,267,269,3,6,3,5,268,253,1,0,0,0,268,256,1,0,0,0,
  	268,259,1,0,0,0,268,262,1,0,0,0,268,265,1,0,0,0,269,272,1,0,0,0,270,268,
  	1,0,0,0,270,271,1,0,0,0,271,7,1,0,0,0,272,270,1,0,0,0,273,276,3,10,5,
  	0,274,276,3,18,9,0,275,273,1,0,0,0,275,274,1,0,0,0,276,9,1,0,0,0,277,
  	278,5,1,0,0,278,279,5,41,0,0,279,11,1,0,0,0,280,281,5,2,0,0,281,282,5,
  	41,0,0,282,283,5,18,0,0,283,13,1,0,0,0,284,285,5,3,0,0,285,286,5,41,0,
  	0,286,287,5,56,0,0,287,288,5,18,0,0,288,15,1,0,0,0,289,290,5,4,0,0,290,
  	291,5,41,0,0,291,292,5,37,0,0,292,293,5,11,0,0,293,294,5,18,0,0,294,17,
  	1,0,0,0,295,296,6,9,-1,0,296,297,5,64,0,0,297,330,3,18,9,15,298,299,3,
  	26,13,0,299,300,3,46,23,0,300,301,3,26,13,0,301,330,1,0,0,0,302,303,3,
  	36,18,0,303,304,3,46,23,0,304,305,3,36,18,0,305,330,1,0,0,0,306,307,3,
  	26,13,0,307,308,5,54,0,0,308,309,3,26,13,0,309,330,1,0,0,0,310,311,3,
  	36,18,0,311,312,5,54,0,0,312,313,3,36,18,0,313,330,1,0,0,0,314,315,3,
  	26,13,0,315,316,5,55,0,0,316,317,3,26,13,0,317,330,1,0,0,0,318,319,3,
  	36,18,0,319,320,5,55,0,0,320,321,3,36,18,0,321,330,1,0,0,0,322,330,3,
  	20,10,0,323,330,3,26,13,0,324,330,3,36,18,0,325,326,5,38,0,0,326,327,
  	3,18,9,0,327,328,5,39,0,0,328,330,1,0,0,0,329,295,1,0,0,0,329,298,1,0,
  	0,0,329,302,1,0,0,0,329,306,1,0,0,0,329,310,1,0,0,0,329,314,1,0,0,0,329,
  	318,1,0,0,0,329,322,1,0,0,0,329,323,1,0,0,0,329,324,1,0,0,0,329,325,1,
  	0,0,0,330,345,1,0,0,0,331,332,10,10,0,0,332,333,5,54,0,0,333,344,3,18,
  	9,11,334,335,10,7,0,0,335,336,5,55,0,0,336,344,3,18,9,8,337,338,10,6,
  	0,0,338,339,5,62,0,0,339,344,3,18,9,7,340,341,10,5,0,0,341,342,5,63,0,
  	0,342,344,3,18,9,6,343,331,1,0,0,0,343,334,1,0,0,0,343,337,1,0,0,0,343,
  	340,1,0,0,0,344,347,1,0,0,0,345,343,1,0,0,0,345,346,1,0,0,0,346,19,1,
  	0,0,0,347,345,1,0,0,0,348,351,3,22,11,0,349,351,3,24,12,0,350,348,1,0,
  	0,0,350,349,1,0,0,0,351,21,1,0,0,0,352,353,5,45,0,0,353,23,1,0,0,0,354,
  	355,5,52,0,0,355,356,3,44,22,0,356,357,5,5,0,0,357,25,1,0,0,0,358,359,
  	6,13,-1,0,359,360,5,59,0,0,360,367,3,26,13,11,361,367,3,30,15,0,362,363,
  	5,38,0,0,363,364,3,26,13,0,364,365,5,39,0,0,365,367,1,0,0,0,366,358,1,
  	0,0,0,366,361,1,0,0,0,366,362,1,0,0,0,367,393,1,0,0,0,368,369,10,9,0,
  	0,369,370,7,0,0,0,370,392,3,26,13,10,371,372,10,8,0,0,372,373,7,1,0,0,
  	373,392,3,26,13,9,374,375,10,7,0,0,375,376,5,60,0,0,376,392,3,26,13,8,
  	377,378,10,6,0,0,378,379,5,61,0,0,379,392,3,26,13,7,380,381,10,5,0,0,
  	381,382,5,56,0,0,382,392,3,26,13,6,383,384,10,4,0,0,384,385,5,58,0,0,
  	385,392,3,26,13,5,386,387,10,3,0,0,387,388,5,57,0,0,388,392,3,26,13,4,
  	389,390,10,10,0,0,390,392,3,28,14,0,391,368,1,0,0,0,391,371,1,0,0,0,391,
  	374,1,0,0,0,391,377,1,0,0,0,391,380,1,0,0,0,391,383,1,0,0,0,391,386,1,
  	0,0,0,391,389,1,0,0,0,392,395,1,0,0,0,393,391,1,0,0,0,393,394,1,0,0,0,
  	394,27,1,0,0,0,395,393,1,0,0,0,396,397,5,36,0,0,397,400,5,41,0,0,398,
  	399,5,30,0,0,399,401,5,41,0,0,400,398,1,0,0,0,400,401,1,0,0,0,401,402,
  	1,0,0,0,402,403,5,37,0,0,403,29,1,0,0,0,404,407,3,32,16,0,405,407,3,34,
  	17,0,406,404,1,0,0,0,406,405,1,0,0,0,407,31,1,0,0,0,408,416,5,42,0,0,
  	409,416,5,43,0,0,410,412,5,41,0,0,411,413,5,33,0,0,412,411,1,0,0,0,412,
  	413,1,0,0,0,413,416,1,0,0,0,414,416,5,44,0,0,415,408,1,0,0,0,415,409,
  	1,0,0,0,415,410,1,0,0,0,415,414,1,0,0,0,416,33,1,0,0,0,417,418,5,52,0,
  	0,418,419,3,44,22,0,419,420,5,6,0,0,420,421,5,32,0,0,421,422,5,7,0,0,
  	422,423,5,41,0,0,423,424,5,8,0,0,424,35,1,0,0,0,425,426,6,18,-1,0,426,
  	433,3,38,19,0,427,433,3,26,13,0,428,429,5,38,0,0,429,430,3,36,18,0,430,
  	431,5,39,0,0,431,433,1,0,0,0,432,425,1,0,0,0,432,427,1,0,0,0,432,428,
  	1,0,0,0,433,442,1,0,0,0,434,435,10,5,0,0,435,436,7,0,0,0,436,441,3,36,
  	18,6,437,438,10,4,0,0,438,439,7,1,0,0,439,441,3,36,18,5,440,434,1,0,0,
  	0,440,437,1,0,0,0,441,444,1,0,0,0,442,440,1,0,0,0,442,443,1,0,0,0,443,
  	37,1,0,0,0,444,442,1,0,0,0,445,448,3,40,20,0,446,448,3,42,21,0,447,445,
  	1,0,0,0,447,446,1,0,0,0,448,39,1,0,0,0,449,450,5,41,0,0,450,41,1,0,0,
  	0,451,452,5,52,0,0,452,453,3,44,22,0,453,454,5,9,0,0,454,455,5,41,0,0,
  	455,456,5,8,0,0,456,43,1,0,0,0,457,458,5,40,0,0,458,45,1,0,0,0,459,460,
  	7,2,0,0,460,47,1,0,0,0,42,58,108,113,117,135,139,142,145,151,171,174,
  	177,180,183,190,193,196,208,211,219,222,225,227,251,268,270,275,329,343,
  	345,350,366,391,393,400,406,412,415,432,440,442,447
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

spotParser::FormulaContext* spotParser::FileContext::formula() {
  return getRuleContext<spotParser::FormulaContext>(0);
}

tree::TerminalNode* spotParser::FileContext::EOF() {
  return getToken(spotParser::EOF, 0);
}

tree::TerminalNode* spotParser::FileContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

tree::TerminalNode* spotParser::FileContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
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
    setState(58);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(48);
      match(spotParser::ALWAYS);
      setState(49);
      formula();
      setState(50);
      match(spotParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(52);
      match(spotParser::ALWAYS);
      setState(53);
      match(spotParser::LPAREN);
      setState(54);
      formula();
      setState(55);
      match(spotParser::RPAREN);
      setState(56);
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
    setState(108);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(60);
      tformula(0);
      setState(61);
      match(spotParser::IMPL);
      setState(62);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(64);
      tformula(0);
      setState(65);
      match(spotParser::IMPL2);
      setState(66);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(68);
      match(spotParser::LGPAREN);
      setState(69);
      sere(0);
      setState(70);
      match(spotParser::RGPAREN);
      setState(71);
      match(spotParser::LCPAREN);
      setState(72);
      match(spotParser::RCPAREN);
      setState(73);
      match(spotParser::IMPL);
      setState(74);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(76);
      match(spotParser::LGPAREN);
      setState(77);
      sere(0);
      setState(78);
      match(spotParser::RGPAREN);
      setState(79);
      match(spotParser::LCPAREN);
      setState(80);
      match(spotParser::RCPAREN);
      setState(81);
      match(spotParser::IMPL2);
      setState(82);
      tformula(0);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(84);
      match(spotParser::LGPAREN);
      setState(85);
      sere(0);
      setState(86);
      match(spotParser::RGPAREN);
      setState(87);
      match(spotParser::BIND1);
      setState(88);
      tformula(0);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(90);
      match(spotParser::LGPAREN);
      setState(91);
      sere(0);
      setState(92);
      match(spotParser::RGPAREN);
      setState(93);
      match(spotParser::BIND2);
      setState(94);
      tformula(0);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(96);
      match(spotParser::LGPAREN);
      setState(97);
      sere(0);
      setState(98);
      match(spotParser::RGPAREN);
      setState(99);
      match(spotParser::SEREIMPL1);
      setState(100);
      tformula(0);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(102);
      match(spotParser::LGPAREN);
      setState(103);
      sere(0);
      setState(104);
      match(spotParser::RGPAREN);
      setState(105);
      match(spotParser::SEREIMPL2);
      setState(106);
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

spotParser::PlaceholderContext* spotParser::SereContext::placeholder() {
  return getRuleContext<spotParser::PlaceholderContext>(0);
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

tree::TerminalNode* spotParser::SereContext::DELAY() {
  return getToken(spotParser::DELAY, 0);
}

std::vector<tree::TerminalNode *> spotParser::SereContext::NUMERIC() {
  return getTokens(spotParser::NUMERIC);
}

tree::TerminalNode* spotParser::SereContext::NUMERIC(size_t i) {
  return getToken(spotParser::NUMERIC, i);
}

tree::TerminalNode* spotParser::SereContext::LCPAREN() {
  return getToken(spotParser::LCPAREN, 0);
}

tree::TerminalNode* spotParser::SereContext::DOTS() {
  return getToken(spotParser::DOTS, 0);
}

tree::TerminalNode* spotParser::SereContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

spotParser::Dt_nextContext* spotParser::SereContext::dt_next() {
  return getRuleContext<spotParser::Dt_nextContext>(0);
}

spotParser::Dt_next_andContext* spotParser::SereContext::dt_next_and() {
  return getRuleContext<spotParser::Dt_next_andContext>(0);
}

spotParser::Dt_NCRepsContext* spotParser::SereContext::dt_NCReps() {
  return getRuleContext<spotParser::Dt_NCRepsContext>(0);
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
    setState(151);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(111);
      boolean(0);
      break;
    }

    case 2: {
      setState(113);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::NOT) {
        setState(112);
        match(spotParser::NOT);
      }
      setState(115);
      placeholder();
      break;
    }

    case 3: {
      setState(117);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::NOT) {
        setState(116);
        match(spotParser::NOT);
      }
      setState(119);
      match(spotParser::FUNCTION);
      setState(120);
      match(spotParser::LPAREN);
      setState(121);
      nonTemporalExp();
      setState(122);
      match(spotParser::RPAREN);
      break;
    }

    case 4: {
      setState(124);
      match(spotParser::DT_AND);
      break;
    }

    case 5: {
      setState(125);
      match(spotParser::LPAREN);
      setState(126);
      sere(0);
      setState(127);
      match(spotParser::RPAREN);
      break;
    }

    case 6: {
      setState(129);
      match(spotParser::LGPAREN);
      setState(130);
      sere(0);
      setState(131);
      match(spotParser::RGPAREN);
      break;
    }

    case 7: {
      setState(133);
      match(spotParser::DELAY);
      setState(135);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::LCPAREN) {
        setState(134);
        match(spotParser::LCPAREN);
      }
      setState(137);
      match(spotParser::NUMERIC);
      setState(139);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::DOTS) {
        setState(138);
        match(spotParser::DOTS);
      }
      setState(142);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
      case 1: {
        setState(141);
        match(spotParser::NUMERIC);
        break;
      }

      default:
        break;
      }
      setState(145);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::RCPAREN) {
        setState(144);
        match(spotParser::RCPAREN);
      }
      setState(147);
      sere(5);
      break;
    }

    case 8: {
      setState(148);
      dt_next();
      break;
    }

    case 9: {
      setState(149);
      dt_next_and();
      break;
    }

    case 10: {
      setState(150);
      dt_NCReps();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(227);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(225);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(153);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(154);
          match(spotParser::BOR);
          setState(155);
          sere(15);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(156);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(157);
          match(spotParser::BAND);
          setState(158);
          sere(14);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(159);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(160);
          match(spotParser::AND);
          setState(161);
          sere(13);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(162);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(163);
          match(spotParser::SCOL);
          setState(164);
          sere(12);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(165);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(166);
          match(spotParser::COL);
          setState(167);
          sere(11);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(168);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(169);
          match(spotParser::DELAY);
          setState(171);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::LCPAREN) {
            setState(170);
            match(spotParser::LCPAREN);
          }
          setState(174);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
          case 1: {
            setState(173);
            match(spotParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(177);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(176);
            match(spotParser::DOTS);
          }
          setState(180);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
          case 1: {
            setState(179);
            match(spotParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(183);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::RCPAREN) {
            setState(182);
            match(spotParser::RCPAREN);
          }
          setState(185);
          sere(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(186);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(187);
          match(spotParser::LCPAREN);
          setState(188);
          match(spotParser::TIMES);
          setState(190);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
          case 1: {
            setState(189);
            match(spotParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(193);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(192);
            match(spotParser::DOTS);
          }
          setState(196);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::NUMERIC) {
            setState(195);
            match(spotParser::NUMERIC);
          }
          setState(198);
          match(spotParser::RCPAREN);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(199);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(200);
          match(spotParser::LCPAREN);
          setState(201);
          match(spotParser::PLUS);
          setState(202);
          match(spotParser::RCPAREN);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(203);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(204);
          match(spotParser::LCPAREN);
          setState(205);
          match(spotParser::ASS);
          setState(206);
          match(spotParser::NUMERIC);
          setState(208);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(207);
            match(spotParser::DOTS);
          }
          setState(211);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::NUMERIC) {
            setState(210);
            match(spotParser::NUMERIC);
          }
          setState(213);
          match(spotParser::RCPAREN);
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(214);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(215);
          match(spotParser::LCPAREN);
          setState(216);
          match(spotParser::IMPL);
          setState(217);
          match(spotParser::NUMERIC);
          setState(219);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(218);
            match(spotParser::DOTS);
          }
          setState(222);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::NUMERIC) {
            setState(221);
            match(spotParser::NUMERIC);
          }
          setState(224);
          match(spotParser::RCPAREN);
          break;
        }

        default:
          break;
        } 
      }
      setState(229);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
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

spotParser::PlaceholderContext* spotParser::TformulaContext::placeholder() {
  return getRuleContext<spotParser::PlaceholderContext>(0);
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
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(231);
      boolean(0);
      break;
    }

    case 2: {
      setState(232);
      placeholder();
      break;
    }

    case 3: {
      setState(233);
      match(spotParser::DT_AND);
      break;
    }

    case 4: {
      setState(234);
      match(spotParser::LPAREN);
      setState(235);
      tformula(0);
      setState(236);
      match(spotParser::RPAREN);
      break;
    }

    case 5: {
      setState(238);
      match(spotParser::NOT);
      setState(239);
      tformula(9);
      break;
    }

    case 6: {
      setState(240);
      match(spotParser::NEXT);
      setState(241);
      match(spotParser::LCPAREN);
      setState(242);
      match(spotParser::NUMERIC);
      setState(243);
      match(spotParser::RCPAREN);
      setState(244);
      tformula(3);
      break;
    }

    case 7: {
      setState(245);
      match(spotParser::NEXT);
      setState(246);
      tformula(2);
      break;
    }

    case 8: {
      setState(247);
      match(spotParser::LGPAREN);
      setState(248);
      sere(0);
      setState(249);
      match(spotParser::RGPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(270);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(268);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(253);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(254);
          match(spotParser::AND);
          setState(255);
          tformula(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(256);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(257);
          match(spotParser::OR);
          setState(258);
          tformula(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(259);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(260);
          match(spotParser::XOR);
          setState(261);
          tformula(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(262);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(263);
          match(spotParser::UNTIL);
          setState(264);
          tformula(6);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(265);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(266);
          match(spotParser::RELEASE);
          setState(267);
          tformula(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(272);
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

//----------------- NonTemporalExpContext ------------------------------------------------------------------

spotParser::NonTemporalExpContext::NonTemporalExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

spotParser::PlaceholderContext* spotParser::NonTemporalExpContext::placeholder() {
  return getRuleContext<spotParser::PlaceholderContext>(0);
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
    setState(275);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(273);
        placeholder();
        break;
      }

      case spotParser::LPAREN:
      case spotParser::NUMERIC:
      case spotParser::VERILOG_BINARY:
      case spotParser::GCC_BINARY:
      case spotParser::HEX:
      case spotParser::BOOLEAN:
      case spotParser::LT:
      case spotParser::NEG:
      case spotParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(274);
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

//----------------- PlaceholderContext ------------------------------------------------------------------

spotParser::PlaceholderContext::PlaceholderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::PlaceholderContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}


size_t spotParser::PlaceholderContext::getRuleIndex() const {
  return spotParser::RulePlaceholder;
}

void spotParser::PlaceholderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlaceholder(this);
}

void spotParser::PlaceholderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlaceholder(this);
}

spotParser::PlaceholderContext* spotParser::placeholder() {
  PlaceholderContext *_localctx = _tracker.createInstance<PlaceholderContext>(_ctx, getState());
  enterRule(_localctx, 10, spotParser::RulePlaceholder);

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
    match(spotParser::T__0);
    setState(278);
    match(spotParser::NUMERIC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_nextContext ------------------------------------------------------------------

spotParser::Dt_nextContext::Dt_nextContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::Dt_nextContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

tree::TerminalNode* spotParser::Dt_nextContext::DOTS() {
  return getToken(spotParser::DOTS, 0);
}


size_t spotParser::Dt_nextContext::getRuleIndex() const {
  return spotParser::RuleDt_next;
}

void spotParser::Dt_nextContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_next(this);
}

void spotParser::Dt_nextContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_next(this);
}

spotParser::Dt_nextContext* spotParser::dt_next() {
  Dt_nextContext *_localctx = _tracker.createInstance<Dt_nextContext>(_ctx, getState());
  enterRule(_localctx, 12, spotParser::RuleDt_next);

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
    match(spotParser::T__1);
    setState(281);
    match(spotParser::NUMERIC);
    setState(282);
    match(spotParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_next_andContext ------------------------------------------------------------------

spotParser::Dt_next_andContext::Dt_next_andContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::Dt_next_andContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

tree::TerminalNode* spotParser::Dt_next_andContext::BAND() {
  return getToken(spotParser::BAND, 0);
}

tree::TerminalNode* spotParser::Dt_next_andContext::DOTS() {
  return getToken(spotParser::DOTS, 0);
}


size_t spotParser::Dt_next_andContext::getRuleIndex() const {
  return spotParser::RuleDt_next_and;
}

void spotParser::Dt_next_andContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_next_and(this);
}

void spotParser::Dt_next_andContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_next_and(this);
}

spotParser::Dt_next_andContext* spotParser::dt_next_and() {
  Dt_next_andContext *_localctx = _tracker.createInstance<Dt_next_andContext>(_ctx, getState());
  enterRule(_localctx, 14, spotParser::RuleDt_next_and);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(284);
    match(spotParser::T__2);
    setState(285);
    match(spotParser::NUMERIC);
    setState(286);
    match(spotParser::BAND);
    setState(287);
    match(spotParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_NCRepsContext ------------------------------------------------------------------

spotParser::Dt_NCRepsContext::Dt_NCRepsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::Dt_NCRepsContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

tree::TerminalNode* spotParser::Dt_NCRepsContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

tree::TerminalNode* spotParser::Dt_NCRepsContext::SEP() {
  return getToken(spotParser::SEP, 0);
}

tree::TerminalNode* spotParser::Dt_NCRepsContext::DOTS() {
  return getToken(spotParser::DOTS, 0);
}


size_t spotParser::Dt_NCRepsContext::getRuleIndex() const {
  return spotParser::RuleDt_NCReps;
}

void spotParser::Dt_NCRepsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_NCReps(this);
}

void spotParser::Dt_NCRepsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_NCReps(this);
}

spotParser::Dt_NCRepsContext* spotParser::dt_NCReps() {
  Dt_NCRepsContext *_localctx = _tracker.createInstance<Dt_NCRepsContext>(_ctx, getState());
  enterRule(_localctx, 16, spotParser::RuleDt_NCReps);

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
    match(spotParser::T__3);
    setState(290);
    match(spotParser::NUMERIC);
    setState(291);
    match(spotParser::RCPAREN);
    setState(292);
    match(spotParser::SEP);
    setState(293);
    match(spotParser::DOTS);
   
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
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, spotParser::RuleBoolean, precedence);

    

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
    setState(329);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      setState(296);
      match(spotParser::NOT);
      setState(297);
      boolean(15);
      break;
    }

    case 2: {
      setState(298);
      logic(0);
      setState(299);
      relop();
      setState(300);
      logic(0);
      break;
    }

    case 3: {
      setState(302);
      numeric(0);
      setState(303);
      relop();
      setState(304);
      numeric(0);
      break;
    }

    case 4: {
      setState(306);
      logic(0);
      setState(307);
      match(spotParser::EQ);
      setState(308);
      logic(0);
      break;
    }

    case 5: {
      setState(310);
      numeric(0);
      setState(311);
      match(spotParser::EQ);
      setState(312);
      numeric(0);
      break;
    }

    case 6: {
      setState(314);
      logic(0);
      setState(315);
      match(spotParser::NEQ);
      setState(316);
      logic(0);
      break;
    }

    case 7: {
      setState(318);
      numeric(0);
      setState(319);
      match(spotParser::NEQ);
      setState(320);
      numeric(0);
      break;
    }

    case 8: {
      setState(322);
      booleanAtom();
      break;
    }

    case 9: {
      setState(323);
      logic(0);
      break;
    }

    case 10: {
      setState(324);
      numeric(0);
      break;
    }

    case 11: {
      setState(325);
      match(spotParser::LPAREN);
      setState(326);
      boolean(0);
      setState(327);
      match(spotParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(345);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(343);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(331);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(332);
          match(spotParser::EQ);
          setState(333);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(334);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(335);
          match(spotParser::NEQ);
          setState(336);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(337);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(338);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(spotParser::AND);
          setState(339);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(340);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(341);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(spotParser::OR);
          setState(342);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(347);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
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

spotParser::BooleanConstantContext* spotParser::BooleanAtomContext::booleanConstant() {
  return getRuleContext<spotParser::BooleanConstantContext>(0);
}

spotParser::BooleanVariableContext* spotParser::BooleanAtomContext::booleanVariable() {
  return getRuleContext<spotParser::BooleanVariableContext>(0);
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
  enterRule(_localctx, 20, spotParser::RuleBooleanAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(350);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::BOOLEAN: {
        enterOuterAlt(_localctx, 1);
        setState(348);
        booleanConstant();
        break;
      }

      case spotParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(349);
        booleanVariable();
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

//----------------- BooleanConstantContext ------------------------------------------------------------------

spotParser::BooleanConstantContext::BooleanConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::BooleanConstantContext::BOOLEAN() {
  return getToken(spotParser::BOOLEAN, 0);
}


size_t spotParser::BooleanConstantContext::getRuleIndex() const {
  return spotParser::RuleBooleanConstant;
}

void spotParser::BooleanConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanConstant(this);
}

void spotParser::BooleanConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanConstant(this);
}

spotParser::BooleanConstantContext* spotParser::booleanConstant() {
  BooleanConstantContext *_localctx = _tracker.createInstance<BooleanConstantContext>(_ctx, getState());
  enterRule(_localctx, 22, spotParser::RuleBooleanConstant);

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
    match(spotParser::BOOLEAN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanVariableContext ------------------------------------------------------------------

spotParser::BooleanVariableContext::BooleanVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::BooleanVariableContext::LT() {
  return getToken(spotParser::LT, 0);
}

spotParser::VariableContext* spotParser::BooleanVariableContext::variable() {
  return getRuleContext<spotParser::VariableContext>(0);
}


size_t spotParser::BooleanVariableContext::getRuleIndex() const {
  return spotParser::RuleBooleanVariable;
}

void spotParser::BooleanVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanVariable(this);
}

void spotParser::BooleanVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanVariable(this);
}

spotParser::BooleanVariableContext* spotParser::booleanVariable() {
  BooleanVariableContext *_localctx = _tracker.createInstance<BooleanVariableContext>(_ctx, getState());
  enterRule(_localctx, 24, spotParser::RuleBooleanVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(354);
    match(spotParser::LT);
    setState(355);
    variable();
    setState(356);
    match(spotParser::T__4);
   
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
  size_t startState = 26;
  enterRecursionRule(_localctx, 26, spotParser::RuleLogic, precedence);

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
    setState(366);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::NEG: {
        setState(359);
        match(spotParser::NEG);
        setState(360);
        logic(11);
        break;
      }

      case spotParser::NUMERIC:
      case spotParser::VERILOG_BINARY:
      case spotParser::GCC_BINARY:
      case spotParser::HEX:
      case spotParser::LT: {
        setState(361);
        logicAtom();
        break;
      }

      case spotParser::LPAREN: {
        setState(362);
        match(spotParser::LPAREN);
        setState(363);
        logic(0);
        setState(364);
        match(spotParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(393);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(391);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(368);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(369);
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
          setState(370);
          logic(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(371);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(372);
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
          setState(373);
          logic(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(374);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(375);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::LSHIFT);
          setState(376);
          logic(8);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(377);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(378);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::RSHIFT);
          setState(379);
          logic(7);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(380);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(381);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BAND);
          setState(382);
          logic(6);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(383);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(384);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BXOR);
          setState(385);
          logic(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(386);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(387);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BOR);
          setState(388);
          logic(4);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(389);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(390);
          bitSelect();
          break;
        }

        default:
          break;
        } 
      }
      setState(395);
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
  enterRule(_localctx, 28, spotParser::RuleBitSelect);
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
    setState(396);
    match(spotParser::LCPAREN);
    setState(397);
    match(spotParser::NUMERIC);
    setState(400);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == spotParser::COL) {
      setState(398);
      match(spotParser::COL);
      setState(399);
      match(spotParser::NUMERIC);
    }
    setState(402);
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

spotParser::LogicConstantContext* spotParser::LogicAtomContext::logicConstant() {
  return getRuleContext<spotParser::LogicConstantContext>(0);
}

spotParser::LogicVariableContext* spotParser::LogicAtomContext::logicVariable() {
  return getRuleContext<spotParser::LogicVariableContext>(0);
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
  enterRule(_localctx, 30, spotParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(406);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::NUMERIC:
      case spotParser::VERILOG_BINARY:
      case spotParser::GCC_BINARY:
      case spotParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(404);
        logicConstant();
        break;
      }

      case spotParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(405);
        logicVariable();
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

//----------------- LogicConstantContext ------------------------------------------------------------------

spotParser::LogicConstantContext::LogicConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::LogicConstantContext::VERILOG_BINARY() {
  return getToken(spotParser::VERILOG_BINARY, 0);
}

tree::TerminalNode* spotParser::LogicConstantContext::GCC_BINARY() {
  return getToken(spotParser::GCC_BINARY, 0);
}

tree::TerminalNode* spotParser::LogicConstantContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

tree::TerminalNode* spotParser::LogicConstantContext::CONST_SUFFIX() {
  return getToken(spotParser::CONST_SUFFIX, 0);
}

tree::TerminalNode* spotParser::LogicConstantContext::HEX() {
  return getToken(spotParser::HEX, 0);
}


size_t spotParser::LogicConstantContext::getRuleIndex() const {
  return spotParser::RuleLogicConstant;
}

void spotParser::LogicConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicConstant(this);
}

void spotParser::LogicConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicConstant(this);
}

spotParser::LogicConstantContext* spotParser::logicConstant() {
  LogicConstantContext *_localctx = _tracker.createInstance<LogicConstantContext>(_ctx, getState());
  enterRule(_localctx, 32, spotParser::RuleLogicConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(415);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::VERILOG_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(408);
        match(spotParser::VERILOG_BINARY);
        break;
      }

      case spotParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 2);
        setState(409);
        match(spotParser::GCC_BINARY);
        break;
      }

      case spotParser::NUMERIC: {
        enterOuterAlt(_localctx, 3);
        setState(410);
        match(spotParser::NUMERIC);
        setState(412);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
        case 1: {
          setState(411);
          match(spotParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case spotParser::HEX: {
        enterOuterAlt(_localctx, 4);
        setState(414);
        match(spotParser::HEX);
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

//----------------- LogicVariableContext ------------------------------------------------------------------

spotParser::LogicVariableContext::LogicVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::LogicVariableContext::LT() {
  return getToken(spotParser::LT, 0);
}

spotParser::VariableContext* spotParser::LogicVariableContext::variable() {
  return getRuleContext<spotParser::VariableContext>(0);
}

tree::TerminalNode* spotParser::LogicVariableContext::SIGN() {
  return getToken(spotParser::SIGN, 0);
}

tree::TerminalNode* spotParser::LogicVariableContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}


size_t spotParser::LogicVariableContext::getRuleIndex() const {
  return spotParser::RuleLogicVariable;
}

void spotParser::LogicVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicVariable(this);
}

void spotParser::LogicVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicVariable(this);
}

spotParser::LogicVariableContext* spotParser::logicVariable() {
  LogicVariableContext *_localctx = _tracker.createInstance<LogicVariableContext>(_ctx, getState());
  enterRule(_localctx, 34, spotParser::RuleLogicVariable);

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
    match(spotParser::LT);
    setState(418);
    variable();
    setState(419);
    match(spotParser::T__5);
    setState(420);
    match(spotParser::SIGN);
    setState(421);
    match(spotParser::T__6);
    setState(422);
    match(spotParser::NUMERIC);
    setState(423);
    match(spotParser::T__7);
   
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
  size_t startState = 36;
  enterRecursionRule(_localctx, 36, spotParser::RuleNumeric, precedence);

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
    setState(432);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      setState(426);
      numericAtom();
      break;
    }

    case 2: {
      setState(427);
      logic(0);
      break;
    }

    case 3: {
      setState(428);
      match(spotParser::LPAREN);
      setState(429);
      numeric(0);
      setState(430);
      match(spotParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(442);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(440);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(434);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(435);
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
          setState(436);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(437);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(438);
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
          setState(439);
          numeric(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(444);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
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

spotParser::NumericConstantContext* spotParser::NumericAtomContext::numericConstant() {
  return getRuleContext<spotParser::NumericConstantContext>(0);
}

spotParser::NumericVariableContext* spotParser::NumericAtomContext::numericVariable() {
  return getRuleContext<spotParser::NumericVariableContext>(0);
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
  enterRule(_localctx, 38, spotParser::RuleNumericAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(447);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::NUMERIC: {
        enterOuterAlt(_localctx, 1);
        setState(445);
        numericConstant();
        break;
      }

      case spotParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(446);
        numericVariable();
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

//----------------- NumericConstantContext ------------------------------------------------------------------

spotParser::NumericConstantContext::NumericConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::NumericConstantContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}


size_t spotParser::NumericConstantContext::getRuleIndex() const {
  return spotParser::RuleNumericConstant;
}

void spotParser::NumericConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericConstant(this);
}

void spotParser::NumericConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericConstant(this);
}

spotParser::NumericConstantContext* spotParser::numericConstant() {
  NumericConstantContext *_localctx = _tracker.createInstance<NumericConstantContext>(_ctx, getState());
  enterRule(_localctx, 40, spotParser::RuleNumericConstant);

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
    match(spotParser::NUMERIC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericVariableContext ------------------------------------------------------------------

spotParser::NumericVariableContext::NumericVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::NumericVariableContext::LT() {
  return getToken(spotParser::LT, 0);
}

spotParser::VariableContext* spotParser::NumericVariableContext::variable() {
  return getRuleContext<spotParser::VariableContext>(0);
}

tree::TerminalNode* spotParser::NumericVariableContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}


size_t spotParser::NumericVariableContext::getRuleIndex() const {
  return spotParser::RuleNumericVariable;
}

void spotParser::NumericVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericVariable(this);
}

void spotParser::NumericVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericVariable(this);
}

spotParser::NumericVariableContext* spotParser::numericVariable() {
  NumericVariableContext *_localctx = _tracker.createInstance<NumericVariableContext>(_ctx, getState());
  enterRule(_localctx, 42, spotParser::RuleNumericVariable);

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
    match(spotParser::LT);
    setState(452);
    variable();
    setState(453);
    match(spotParser::T__8);
    setState(454);
    match(spotParser::NUMERIC);
    setState(455);
    match(spotParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

spotParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::VariableContext::VARIABLE() {
  return getToken(spotParser::VARIABLE, 0);
}


size_t spotParser::VariableContext::getRuleIndex() const {
  return spotParser::RuleVariable;
}

void spotParser::VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void spotParser::VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

spotParser::VariableContext* spotParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 44, spotParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(457);
    match(spotParser::VARIABLE);
   
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
  enterRule(_localctx, 46, spotParser::RuleRelop);
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
    setState(459);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16888498602639360) != 0))) {
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
    case 9: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 13: return logicSempred(antlrcpp::downCast<LogicContext *>(context), predicateIndex);
    case 18: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool spotParser::sereSempred(SereContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 14);
    case 1: return precpred(_ctx, 13);
    case 2: return precpred(_ctx, 12);
    case 3: return precpred(_ctx, 11);
    case 4: return precpred(_ctx, 10);
    case 5: return precpred(_ctx, 4);
    case 6: return precpred(_ctx, 9);
    case 7: return precpred(_ctx, 8);
    case 8: return precpred(_ctx, 7);
    case 9: return precpred(_ctx, 6);

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
