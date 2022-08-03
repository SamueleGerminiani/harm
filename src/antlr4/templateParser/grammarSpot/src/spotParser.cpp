
// Generated from spot.g4 by ANTLR 4.10.1


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

std::once_flag spotParserOnceFlag;
SpotParserStaticData *spotParserStaticData = nullptr;

void spotParserInitialize() {
  assert(spotParserStaticData == nullptr);
  auto staticData = std::make_unique<SpotParserStaticData>(
    std::vector<std::string>{
      "file", "formula", "sere", "tformula", "placeholder", "dt_next", "dt_next_and", 
      "dt_NCReps", "boolean", "booleanAtom", "booleanConstant", "booleanVariable", 
      "logic", "bitSelect", "logicAtom", "logicConstant", "logicVariable", 
      "numeric", "numericAtom", "numericConstant", "numericVariable", "variable", 
      "relop"
    },
    std::vector<std::string>{
      "", "'P'", "'..##'", "'..#'", "'..[->'", "',bool>'", "',logic('", 
      "','", "')>'", "',numeric('", "'..&&..'", "", "'F'", "'G'", "'X'", 
      "'U'", "'R'", "'..'", "'->'", "'=>'", "'<->'", "'xor'", "'[]->'", 
      "'[]=>'", "'|->'", "'|=>'", "'='", "'##'", "';'", "':'", "'first_match'", 
      "", "'{'", "'}'", "'['", "']'", "'('", "')'", "", "", "", "", "", 
      "", "'+'", "'-'", "'*'", "'/'", "'>'", "'>='", "'<'", "'<='", "'=='", 
      "'!='", "'&'", "'|'", "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", 
      "'!'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "DT_AND", "SEP", "EVENTUALLY", 
      "ALWAYS", "NEXT", "UNTIL", "RELEASE", "DOTS", "IMPL", "IMPL2", "IFF", 
      "XOR", "BIND1", "BIND2", "SEREIMPL1", "SEREIMPL2", "ASS", "DELAY", 
      "SCOL", "COL", "FIRST_MATCH", "SIGN", "LGPAREN", "RGPAREN", "LCPAREN", 
      "RCPAREN", "LPAREN", "RPAREN", "VARIABLE", "NUMERIC", "VERILOG_BINARY", 
      "GCC_BINARY", "HEX", "BOOLEAN", "PLUS", "MINUS", "TIMES", "DIV", "GT", 
      "GE", "LT", "LE", "EQ", "NEQ", "BAND", "BOR", "BXOR", "NEG", "LSHIFT", 
      "RSHIFT", "AND", "OR", "NOT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,63,441,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,57,8,0,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,107,8,1,1,2,1,2,1,2,
  	3,2,112,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,126,8,
  	2,1,2,1,2,3,2,130,8,2,1,2,3,2,133,8,2,1,2,3,2,136,8,2,1,2,1,2,1,2,1,2,
  	3,2,142,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,3,2,162,8,2,1,2,3,2,165,8,2,1,2,3,2,168,8,2,1,2,3,2,171,
  	8,2,1,2,3,2,174,8,2,1,2,1,2,1,2,1,2,1,2,3,2,181,8,2,1,2,3,2,184,8,2,1,
  	2,3,2,187,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,199,8,2,1,2,
  	3,2,202,8,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,210,8,2,1,2,3,2,213,8,2,1,2,5,
  	2,216,8,2,10,2,12,2,219,9,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,242,8,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,259,8,3,10,3,12,3,262,
  	9,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,3,8,316,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,5,8,330,
  	8,8,10,8,12,8,333,9,8,1,9,1,9,3,9,337,8,9,1,10,1,10,1,11,1,11,1,11,1,
  	11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,3,12,353,8,12,1,12,1,12,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,378,8,12,10,12,12,12,381,9,12,1,
  	13,1,13,1,13,1,13,3,13,387,8,13,1,13,1,13,1,14,1,14,3,14,393,8,14,1,15,
  	1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,17,3,17,412,8,17,1,17,1,17,1,17,1,17,1,17,1,17,5,17,420,8,17,10,
  	17,12,17,423,9,17,1,18,1,18,3,18,427,8,18,1,19,1,19,1,20,1,20,1,20,1,
  	20,1,20,1,20,1,21,1,21,1,22,1,22,1,22,0,5,4,6,16,24,34,23,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,0,4,1,0,46,47,1,0,
  	44,45,1,0,39,42,1,0,48,51,504,0,56,1,0,0,0,2,106,1,0,0,0,4,141,1,0,0,
  	0,6,241,1,0,0,0,8,263,1,0,0,0,10,266,1,0,0,0,12,270,1,0,0,0,14,275,1,
  	0,0,0,16,315,1,0,0,0,18,336,1,0,0,0,20,338,1,0,0,0,22,340,1,0,0,0,24,
  	352,1,0,0,0,26,382,1,0,0,0,28,392,1,0,0,0,30,394,1,0,0,0,32,396,1,0,0,
  	0,34,411,1,0,0,0,36,426,1,0,0,0,38,428,1,0,0,0,40,430,1,0,0,0,42,436,
  	1,0,0,0,44,438,1,0,0,0,46,47,5,13,0,0,47,48,3,2,1,0,48,49,5,0,0,1,49,
  	57,1,0,0,0,50,51,5,13,0,0,51,52,5,36,0,0,52,53,3,2,1,0,53,54,5,37,0,0,
  	54,55,5,0,0,1,55,57,1,0,0,0,56,46,1,0,0,0,56,50,1,0,0,0,57,1,1,0,0,0,
  	58,59,3,6,3,0,59,60,5,18,0,0,60,61,3,6,3,0,61,107,1,0,0,0,62,63,3,6,3,
  	0,63,64,5,19,0,0,64,65,3,6,3,0,65,107,1,0,0,0,66,67,5,32,0,0,67,68,3,
  	4,2,0,68,69,5,33,0,0,69,70,5,34,0,0,70,71,5,35,0,0,71,72,5,18,0,0,72,
  	73,3,6,3,0,73,107,1,0,0,0,74,75,5,32,0,0,75,76,3,4,2,0,76,77,5,33,0,0,
  	77,78,5,34,0,0,78,79,5,35,0,0,79,80,5,19,0,0,80,81,3,6,3,0,81,107,1,0,
  	0,0,82,83,5,32,0,0,83,84,3,4,2,0,84,85,5,33,0,0,85,86,5,22,0,0,86,87,
  	3,6,3,0,87,107,1,0,0,0,88,89,5,32,0,0,89,90,3,4,2,0,90,91,5,33,0,0,91,
  	92,5,23,0,0,92,93,3,6,3,0,93,107,1,0,0,0,94,95,5,32,0,0,95,96,3,4,2,0,
  	96,97,5,33,0,0,97,98,5,24,0,0,98,99,3,6,3,0,99,107,1,0,0,0,100,101,5,
  	32,0,0,101,102,3,4,2,0,102,103,5,33,0,0,103,104,5,25,0,0,104,105,3,6,
  	3,0,105,107,1,0,0,0,106,58,1,0,0,0,106,62,1,0,0,0,106,66,1,0,0,0,106,
  	74,1,0,0,0,106,82,1,0,0,0,106,88,1,0,0,0,106,94,1,0,0,0,106,100,1,0,0,
  	0,107,3,1,0,0,0,108,109,6,2,-1,0,109,142,3,16,8,0,110,112,5,62,0,0,111,
  	110,1,0,0,0,111,112,1,0,0,0,112,113,1,0,0,0,113,142,3,8,4,0,114,142,5,
  	10,0,0,115,116,5,36,0,0,116,117,3,4,2,0,117,118,5,37,0,0,118,142,1,0,
  	0,0,119,120,5,32,0,0,120,121,3,4,2,0,121,122,5,33,0,0,122,142,1,0,0,0,
  	123,125,5,27,0,0,124,126,5,34,0,0,125,124,1,0,0,0,125,126,1,0,0,0,126,
  	127,1,0,0,0,127,129,5,39,0,0,128,130,5,17,0,0,129,128,1,0,0,0,129,130,
  	1,0,0,0,130,132,1,0,0,0,131,133,5,39,0,0,132,131,1,0,0,0,132,133,1,0,
  	0,0,133,135,1,0,0,0,134,136,5,35,0,0,135,134,1,0,0,0,135,136,1,0,0,0,
  	136,137,1,0,0,0,137,142,3,4,2,5,138,142,3,10,5,0,139,142,3,12,6,0,140,
  	142,3,14,7,0,141,108,1,0,0,0,141,111,1,0,0,0,141,114,1,0,0,0,141,115,
  	1,0,0,0,141,119,1,0,0,0,141,123,1,0,0,0,141,138,1,0,0,0,141,139,1,0,0,
  	0,141,140,1,0,0,0,142,217,1,0,0,0,143,144,10,14,0,0,144,145,5,55,0,0,
  	145,216,3,4,2,15,146,147,10,13,0,0,147,148,5,54,0,0,148,216,3,4,2,14,
  	149,150,10,12,0,0,150,151,5,60,0,0,151,216,3,4,2,13,152,153,10,11,0,0,
  	153,154,5,28,0,0,154,216,3,4,2,12,155,156,10,10,0,0,156,157,5,29,0,0,
  	157,216,3,4,2,11,158,159,10,4,0,0,159,161,5,27,0,0,160,162,5,34,0,0,161,
  	160,1,0,0,0,161,162,1,0,0,0,162,164,1,0,0,0,163,165,5,39,0,0,164,163,
  	1,0,0,0,164,165,1,0,0,0,165,167,1,0,0,0,166,168,5,17,0,0,167,166,1,0,
  	0,0,167,168,1,0,0,0,168,170,1,0,0,0,169,171,5,39,0,0,170,169,1,0,0,0,
  	170,171,1,0,0,0,171,173,1,0,0,0,172,174,5,35,0,0,173,172,1,0,0,0,173,
  	174,1,0,0,0,174,175,1,0,0,0,175,216,3,4,2,5,176,177,10,9,0,0,177,178,
  	5,34,0,0,178,180,5,46,0,0,179,181,5,39,0,0,180,179,1,0,0,0,180,181,1,
  	0,0,0,181,183,1,0,0,0,182,184,5,17,0,0,183,182,1,0,0,0,183,184,1,0,0,
  	0,184,186,1,0,0,0,185,187,5,39,0,0,186,185,1,0,0,0,186,187,1,0,0,0,187,
  	188,1,0,0,0,188,216,5,35,0,0,189,190,10,8,0,0,190,191,5,34,0,0,191,192,
  	5,44,0,0,192,216,5,35,0,0,193,194,10,7,0,0,194,195,5,34,0,0,195,196,5,
  	26,0,0,196,198,5,39,0,0,197,199,5,17,0,0,198,197,1,0,0,0,198,199,1,0,
  	0,0,199,201,1,0,0,0,200,202,5,39,0,0,201,200,1,0,0,0,201,202,1,0,0,0,
  	202,203,1,0,0,0,203,216,5,35,0,0,204,205,10,6,0,0,205,206,5,34,0,0,206,
  	207,5,18,0,0,207,209,5,39,0,0,208,210,5,17,0,0,209,208,1,0,0,0,209,210,
  	1,0,0,0,210,212,1,0,0,0,211,213,5,39,0,0,212,211,1,0,0,0,212,213,1,0,
  	0,0,213,214,1,0,0,0,214,216,5,35,0,0,215,143,1,0,0,0,215,146,1,0,0,0,
  	215,149,1,0,0,0,215,152,1,0,0,0,215,155,1,0,0,0,215,158,1,0,0,0,215,176,
  	1,0,0,0,215,189,1,0,0,0,215,193,1,0,0,0,215,204,1,0,0,0,216,219,1,0,0,
  	0,217,215,1,0,0,0,217,218,1,0,0,0,218,5,1,0,0,0,219,217,1,0,0,0,220,221,
  	6,3,-1,0,221,242,3,16,8,0,222,242,3,8,4,0,223,242,5,10,0,0,224,225,5,
  	36,0,0,225,226,3,6,3,0,226,227,5,37,0,0,227,242,1,0,0,0,228,229,5,62,
  	0,0,229,242,3,6,3,9,230,231,5,14,0,0,231,232,5,34,0,0,232,233,5,39,0,
  	0,233,234,5,35,0,0,234,242,3,6,3,3,235,236,5,14,0,0,236,242,3,6,3,2,237,
  	238,5,32,0,0,238,239,3,4,2,0,239,240,5,33,0,0,240,242,1,0,0,0,241,220,
  	1,0,0,0,241,222,1,0,0,0,241,223,1,0,0,0,241,224,1,0,0,0,241,228,1,0,0,
  	0,241,230,1,0,0,0,241,235,1,0,0,0,241,237,1,0,0,0,242,260,1,0,0,0,243,
  	244,10,8,0,0,244,245,5,60,0,0,245,259,3,6,3,9,246,247,10,7,0,0,247,248,
  	5,61,0,0,248,259,3,6,3,8,249,250,10,6,0,0,250,251,5,21,0,0,251,259,3,
  	6,3,7,252,253,10,5,0,0,253,254,5,15,0,0,254,259,3,6,3,6,255,256,10,4,
  	0,0,256,257,5,16,0,0,257,259,3,6,3,5,258,243,1,0,0,0,258,246,1,0,0,0,
  	258,249,1,0,0,0,258,252,1,0,0,0,258,255,1,0,0,0,259,262,1,0,0,0,260,258,
  	1,0,0,0,260,261,1,0,0,0,261,7,1,0,0,0,262,260,1,0,0,0,263,264,5,1,0,0,
  	264,265,5,39,0,0,265,9,1,0,0,0,266,267,5,2,0,0,267,268,5,39,0,0,268,269,
  	5,17,0,0,269,11,1,0,0,0,270,271,5,3,0,0,271,272,5,39,0,0,272,273,5,54,
  	0,0,273,274,5,17,0,0,274,13,1,0,0,0,275,276,5,4,0,0,276,277,5,39,0,0,
  	277,278,5,35,0,0,278,279,5,11,0,0,279,280,5,17,0,0,280,15,1,0,0,0,281,
  	282,6,8,-1,0,282,283,5,62,0,0,283,316,3,16,8,15,284,285,3,24,12,0,285,
  	286,3,44,22,0,286,287,3,24,12,0,287,316,1,0,0,0,288,289,3,34,17,0,289,
  	290,3,44,22,0,290,291,3,34,17,0,291,316,1,0,0,0,292,293,3,24,12,0,293,
  	294,5,52,0,0,294,295,3,24,12,0,295,316,1,0,0,0,296,297,3,34,17,0,297,
  	298,5,52,0,0,298,299,3,34,17,0,299,316,1,0,0,0,300,301,3,24,12,0,301,
  	302,5,53,0,0,302,303,3,24,12,0,303,316,1,0,0,0,304,305,3,34,17,0,305,
  	306,5,53,0,0,306,307,3,34,17,0,307,316,1,0,0,0,308,316,3,18,9,0,309,316,
  	3,24,12,0,310,316,3,34,17,0,311,312,5,36,0,0,312,313,3,16,8,0,313,314,
  	5,37,0,0,314,316,1,0,0,0,315,281,1,0,0,0,315,284,1,0,0,0,315,288,1,0,
  	0,0,315,292,1,0,0,0,315,296,1,0,0,0,315,300,1,0,0,0,315,304,1,0,0,0,315,
  	308,1,0,0,0,315,309,1,0,0,0,315,310,1,0,0,0,315,311,1,0,0,0,316,331,1,
  	0,0,0,317,318,10,10,0,0,318,319,5,52,0,0,319,330,3,16,8,11,320,321,10,
  	7,0,0,321,322,5,53,0,0,322,330,3,16,8,8,323,324,10,6,0,0,324,325,5,60,
  	0,0,325,330,3,16,8,7,326,327,10,5,0,0,327,328,5,61,0,0,328,330,3,16,8,
  	6,329,317,1,0,0,0,329,320,1,0,0,0,329,323,1,0,0,0,329,326,1,0,0,0,330,
  	333,1,0,0,0,331,329,1,0,0,0,331,332,1,0,0,0,332,17,1,0,0,0,333,331,1,
  	0,0,0,334,337,3,20,10,0,335,337,3,22,11,0,336,334,1,0,0,0,336,335,1,0,
  	0,0,337,19,1,0,0,0,338,339,5,43,0,0,339,21,1,0,0,0,340,341,5,50,0,0,341,
  	342,3,42,21,0,342,343,5,5,0,0,343,23,1,0,0,0,344,345,6,12,-1,0,345,346,
  	5,57,0,0,346,353,3,24,12,11,347,353,3,28,14,0,348,349,5,36,0,0,349,350,
  	3,24,12,0,350,351,5,37,0,0,351,353,1,0,0,0,352,344,1,0,0,0,352,347,1,
  	0,0,0,352,348,1,0,0,0,353,379,1,0,0,0,354,355,10,9,0,0,355,356,7,0,0,
  	0,356,378,3,24,12,10,357,358,10,8,0,0,358,359,7,1,0,0,359,378,3,24,12,
  	9,360,361,10,7,0,0,361,362,5,58,0,0,362,378,3,24,12,8,363,364,10,6,0,
  	0,364,365,5,59,0,0,365,378,3,24,12,7,366,367,10,5,0,0,367,368,5,54,0,
  	0,368,378,3,24,12,6,369,370,10,4,0,0,370,371,5,56,0,0,371,378,3,24,12,
  	5,372,373,10,3,0,0,373,374,5,55,0,0,374,378,3,24,12,4,375,376,10,10,0,
  	0,376,378,3,26,13,0,377,354,1,0,0,0,377,357,1,0,0,0,377,360,1,0,0,0,377,
  	363,1,0,0,0,377,366,1,0,0,0,377,369,1,0,0,0,377,372,1,0,0,0,377,375,1,
  	0,0,0,378,381,1,0,0,0,379,377,1,0,0,0,379,380,1,0,0,0,380,25,1,0,0,0,
  	381,379,1,0,0,0,382,383,5,34,0,0,383,386,5,39,0,0,384,385,5,29,0,0,385,
  	387,5,39,0,0,386,384,1,0,0,0,386,387,1,0,0,0,387,388,1,0,0,0,388,389,
  	5,35,0,0,389,27,1,0,0,0,390,393,3,30,15,0,391,393,3,32,16,0,392,390,1,
  	0,0,0,392,391,1,0,0,0,393,29,1,0,0,0,394,395,7,2,0,0,395,31,1,0,0,0,396,
  	397,5,50,0,0,397,398,3,42,21,0,398,399,5,6,0,0,399,400,5,31,0,0,400,401,
  	5,7,0,0,401,402,5,39,0,0,402,403,5,8,0,0,403,33,1,0,0,0,404,405,6,17,
  	-1,0,405,412,3,36,18,0,406,412,3,24,12,0,407,408,5,36,0,0,408,409,3,34,
  	17,0,409,410,5,37,0,0,410,412,1,0,0,0,411,404,1,0,0,0,411,406,1,0,0,0,
  	411,407,1,0,0,0,412,421,1,0,0,0,413,414,10,5,0,0,414,415,7,0,0,0,415,
  	420,3,34,17,6,416,417,10,4,0,0,417,418,7,1,0,0,418,420,3,34,17,5,419,
  	413,1,0,0,0,419,416,1,0,0,0,420,423,1,0,0,0,421,419,1,0,0,0,421,422,1,
  	0,0,0,422,35,1,0,0,0,423,421,1,0,0,0,424,427,3,38,19,0,425,427,3,40,20,
  	0,426,424,1,0,0,0,426,425,1,0,0,0,427,37,1,0,0,0,428,429,5,39,0,0,429,
  	39,1,0,0,0,430,431,5,50,0,0,431,432,3,42,21,0,432,433,5,9,0,0,433,434,
  	5,39,0,0,434,435,5,8,0,0,435,41,1,0,0,0,436,437,5,38,0,0,437,43,1,0,0,
  	0,438,439,7,3,0,0,439,45,1,0,0,0,38,56,106,111,125,129,132,135,141,161,
  	164,167,170,173,180,183,186,198,201,209,212,215,217,241,258,260,315,329,
  	331,336,352,377,379,386,392,411,419,421,426
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
    setState(56);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(46);
      match(spotParser::ALWAYS);
      setState(47);
      formula();
      setState(48);
      match(spotParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(50);
      match(spotParser::ALWAYS);
      setState(51);
      match(spotParser::LPAREN);
      setState(52);
      formula();
      setState(53);
      match(spotParser::RPAREN);
      setState(54);
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
    setState(106);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(58);
      tformula(0);
      setState(59);
      match(spotParser::IMPL);
      setState(60);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(62);
      tformula(0);
      setState(63);
      match(spotParser::IMPL2);
      setState(64);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(66);
      match(spotParser::LGPAREN);
      setState(67);
      sere(0);
      setState(68);
      match(spotParser::RGPAREN);
      setState(69);
      match(spotParser::LCPAREN);
      setState(70);
      match(spotParser::RCPAREN);
      setState(71);
      match(spotParser::IMPL);
      setState(72);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(74);
      match(spotParser::LGPAREN);
      setState(75);
      sere(0);
      setState(76);
      match(spotParser::RGPAREN);
      setState(77);
      match(spotParser::LCPAREN);
      setState(78);
      match(spotParser::RCPAREN);
      setState(79);
      match(spotParser::IMPL2);
      setState(80);
      tformula(0);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(82);
      match(spotParser::LGPAREN);
      setState(83);
      sere(0);
      setState(84);
      match(spotParser::RGPAREN);
      setState(85);
      match(spotParser::BIND1);
      setState(86);
      tformula(0);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(88);
      match(spotParser::LGPAREN);
      setState(89);
      sere(0);
      setState(90);
      match(spotParser::RGPAREN);
      setState(91);
      match(spotParser::BIND2);
      setState(92);
      tformula(0);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(94);
      match(spotParser::LGPAREN);
      setState(95);
      sere(0);
      setState(96);
      match(spotParser::RGPAREN);
      setState(97);
      match(spotParser::SEREIMPL1);
      setState(98);
      tformula(0);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(100);
      match(spotParser::LGPAREN);
      setState(101);
      sere(0);
      setState(102);
      match(spotParser::RGPAREN);
      setState(103);
      match(spotParser::SEREIMPL2);
      setState(104);
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

tree::TerminalNode* spotParser::SereContext::DT_AND() {
  return getToken(spotParser::DT_AND, 0);
}

tree::TerminalNode* spotParser::SereContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

std::vector<spotParser::SereContext *> spotParser::SereContext::sere() {
  return getRuleContexts<spotParser::SereContext>();
}

spotParser::SereContext* spotParser::SereContext::sere(size_t i) {
  return getRuleContext<spotParser::SereContext>(i);
}

tree::TerminalNode* spotParser::SereContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
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
    setState(141);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(109);
      boolean(0);
      break;
    }

    case 2: {
      setState(111);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::NOT) {
        setState(110);
        match(spotParser::NOT);
      }
      setState(113);
      placeholder();
      break;
    }

    case 3: {
      setState(114);
      match(spotParser::DT_AND);
      break;
    }

    case 4: {
      setState(115);
      match(spotParser::LPAREN);
      setState(116);
      sere(0);
      setState(117);
      match(spotParser::RPAREN);
      break;
    }

    case 5: {
      setState(119);
      match(spotParser::LGPAREN);
      setState(120);
      sere(0);
      setState(121);
      match(spotParser::RGPAREN);
      break;
    }

    case 6: {
      setState(123);
      match(spotParser::DELAY);
      setState(125);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::LCPAREN) {
        setState(124);
        match(spotParser::LCPAREN);
      }
      setState(127);
      match(spotParser::NUMERIC);
      setState(129);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::DOTS) {
        setState(128);
        match(spotParser::DOTS);
      }
      setState(132);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(131);
        match(spotParser::NUMERIC);
        break;
      }

      default:
        break;
      }
      setState(135);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::RCPAREN) {
        setState(134);
        match(spotParser::RCPAREN);
      }
      setState(137);
      sere(5);
      break;
    }

    case 7: {
      setState(138);
      dt_next();
      break;
    }

    case 8: {
      setState(139);
      dt_next_and();
      break;
    }

    case 9: {
      setState(140);
      dt_NCReps();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(217);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(215);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(143);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(144);
          match(spotParser::BOR);
          setState(145);
          sere(15);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(146);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(147);
          match(spotParser::BAND);
          setState(148);
          sere(14);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(149);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(150);
          match(spotParser::AND);
          setState(151);
          sere(13);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(152);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(153);
          match(spotParser::SCOL);
          setState(154);
          sere(12);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(155);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(156);
          match(spotParser::COL);
          setState(157);
          sere(11);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(158);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(159);
          match(spotParser::DELAY);
          setState(161);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::LCPAREN) {
            setState(160);
            match(spotParser::LCPAREN);
          }
          setState(164);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
          case 1: {
            setState(163);
            match(spotParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(167);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(166);
            match(spotParser::DOTS);
          }
          setState(170);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
          case 1: {
            setState(169);
            match(spotParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(173);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::RCPAREN) {
            setState(172);
            match(spotParser::RCPAREN);
          }
          setState(175);
          sere(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(176);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(177);
          match(spotParser::LCPAREN);
          setState(178);
          match(spotParser::TIMES);
          setState(180);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
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
          if (_la == spotParser::DOTS) {
            setState(182);
            match(spotParser::DOTS);
          }
          setState(186);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::NUMERIC) {
            setState(185);
            match(spotParser::NUMERIC);
          }
          setState(188);
          match(spotParser::RCPAREN);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(189);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(190);
          match(spotParser::LCPAREN);
          setState(191);
          match(spotParser::PLUS);
          setState(192);
          match(spotParser::RCPAREN);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(193);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(194);
          match(spotParser::LCPAREN);
          setState(195);
          match(spotParser::ASS);
          setState(196);
          match(spotParser::NUMERIC);
          setState(198);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(197);
            match(spotParser::DOTS);
          }
          setState(201);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::NUMERIC) {
            setState(200);
            match(spotParser::NUMERIC);
          }
          setState(203);
          match(spotParser::RCPAREN);
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(204);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(205);
          match(spotParser::LCPAREN);
          setState(206);
          match(spotParser::IMPL);
          setState(207);
          match(spotParser::NUMERIC);
          setState(209);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(208);
            match(spotParser::DOTS);
          }
          setState(212);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::NUMERIC) {
            setState(211);
            match(spotParser::NUMERIC);
          }
          setState(214);
          match(spotParser::RCPAREN);
          break;
        }

        default:
          break;
        } 
      }
      setState(219);
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
    setState(241);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(221);
      boolean(0);
      break;
    }

    case 2: {
      setState(222);
      placeholder();
      break;
    }

    case 3: {
      setState(223);
      match(spotParser::DT_AND);
      break;
    }

    case 4: {
      setState(224);
      match(spotParser::LPAREN);
      setState(225);
      tformula(0);
      setState(226);
      match(spotParser::RPAREN);
      break;
    }

    case 5: {
      setState(228);
      match(spotParser::NOT);
      setState(229);
      tformula(9);
      break;
    }

    case 6: {
      setState(230);
      match(spotParser::NEXT);
      setState(231);
      match(spotParser::LCPAREN);
      setState(232);
      match(spotParser::NUMERIC);
      setState(233);
      match(spotParser::RCPAREN);
      setState(234);
      tformula(3);
      break;
    }

    case 7: {
      setState(235);
      match(spotParser::NEXT);
      setState(236);
      tformula(2);
      break;
    }

    case 8: {
      setState(237);
      match(spotParser::LGPAREN);
      setState(238);
      sere(0);
      setState(239);
      match(spotParser::RGPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(260);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(258);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(243);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(244);
          match(spotParser::AND);
          setState(245);
          tformula(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(246);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(247);
          match(spotParser::OR);
          setState(248);
          tformula(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(249);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(250);
          match(spotParser::XOR);
          setState(251);
          tformula(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(252);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(253);
          match(spotParser::UNTIL);
          setState(254);
          tformula(6);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(255);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(256);
          match(spotParser::RELEASE);
          setState(257);
          tformula(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(262);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
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
  enterRule(_localctx, 8, spotParser::RulePlaceholder);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(263);
    match(spotParser::T__0);
    setState(264);
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
  enterRule(_localctx, 10, spotParser::RuleDt_next);

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
    match(spotParser::T__1);
    setState(267);
    match(spotParser::NUMERIC);
    setState(268);
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
  enterRule(_localctx, 12, spotParser::RuleDt_next_and);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(270);
    match(spotParser::T__2);
    setState(271);
    match(spotParser::NUMERIC);
    setState(272);
    match(spotParser::BAND);
    setState(273);
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
  enterRule(_localctx, 14, spotParser::RuleDt_NCReps);

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
    match(spotParser::T__3);
    setState(276);
    match(spotParser::NUMERIC);
    setState(277);
    match(spotParser::RCPAREN);
    setState(278);
    match(spotParser::SEP);
    setState(279);
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
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, spotParser::RuleBoolean, precedence);

    

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      setState(282);
      match(spotParser::NOT);
      setState(283);
      boolean(15);
      break;
    }

    case 2: {
      setState(284);
      logic(0);
      setState(285);
      relop();
      setState(286);
      logic(0);
      break;
    }

    case 3: {
      setState(288);
      numeric(0);
      setState(289);
      relop();
      setState(290);
      numeric(0);
      break;
    }

    case 4: {
      setState(292);
      logic(0);
      setState(293);
      match(spotParser::EQ);
      setState(294);
      logic(0);
      break;
    }

    case 5: {
      setState(296);
      numeric(0);
      setState(297);
      match(spotParser::EQ);
      setState(298);
      numeric(0);
      break;
    }

    case 6: {
      setState(300);
      logic(0);
      setState(301);
      match(spotParser::NEQ);
      setState(302);
      logic(0);
      break;
    }

    case 7: {
      setState(304);
      numeric(0);
      setState(305);
      match(spotParser::NEQ);
      setState(306);
      numeric(0);
      break;
    }

    case 8: {
      setState(308);
      booleanAtom();
      break;
    }

    case 9: {
      setState(309);
      logic(0);
      break;
    }

    case 10: {
      setState(310);
      numeric(0);
      break;
    }

    case 11: {
      setState(311);
      match(spotParser::LPAREN);
      setState(312);
      boolean(0);
      setState(313);
      match(spotParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(331);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(329);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(317);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(318);
          match(spotParser::EQ);
          setState(319);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(320);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(321);
          match(spotParser::NEQ);
          setState(322);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(323);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(324);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(spotParser::AND);
          setState(325);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(326);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(327);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(spotParser::OR);
          setState(328);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(333);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
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
  enterRule(_localctx, 18, spotParser::RuleBooleanAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(336);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::BOOLEAN: {
        enterOuterAlt(_localctx, 1);
        setState(334);
        booleanConstant();
        break;
      }

      case spotParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(335);
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
  enterRule(_localctx, 20, spotParser::RuleBooleanConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(338);
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
  enterRule(_localctx, 22, spotParser::RuleBooleanVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(340);
    match(spotParser::LT);
    setState(341);
    variable();
    setState(342);
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
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, spotParser::RuleLogic, precedence);

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
    setState(352);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::NEG: {
        setState(345);
        match(spotParser::NEG);
        setState(346);
        logic(11);
        break;
      }

      case spotParser::NUMERIC:
      case spotParser::VERILOG_BINARY:
      case spotParser::GCC_BINARY:
      case spotParser::HEX:
      case spotParser::LT: {
        setState(347);
        logicAtom();
        break;
      }

      case spotParser::LPAREN: {
        setState(348);
        match(spotParser::LPAREN);
        setState(349);
        logic(0);
        setState(350);
        match(spotParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(379);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(377);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(354);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(355);
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
          setState(356);
          logic(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(357);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(358);
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
          setState(359);
          logic(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(360);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(361);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::LSHIFT);
          setState(362);
          logic(8);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(363);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(364);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::RSHIFT);
          setState(365);
          logic(7);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(366);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(367);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BAND);
          setState(368);
          logic(6);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(369);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(370);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BXOR);
          setState(371);
          logic(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(372);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(373);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BOR);
          setState(374);
          logic(4);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(375);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(376);
          bitSelect();
          break;
        }

        default:
          break;
        } 
      }
      setState(381);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
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
  enterRule(_localctx, 26, spotParser::RuleBitSelect);
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
    setState(382);
    match(spotParser::LCPAREN);
    setState(383);
    match(spotParser::NUMERIC);
    setState(386);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == spotParser::COL) {
      setState(384);
      match(spotParser::COL);
      setState(385);
      match(spotParser::NUMERIC);
    }
    setState(388);
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
  enterRule(_localctx, 28, spotParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(392);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::NUMERIC:
      case spotParser::VERILOG_BINARY:
      case spotParser::GCC_BINARY:
      case spotParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(390);
        logicConstant();
        break;
      }

      case spotParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(391);
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
  enterRule(_localctx, 30, spotParser::RuleLogicConstant);
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
    setState(394);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << spotParser::NUMERIC)
      | (1ULL << spotParser::VERILOG_BINARY)
      | (1ULL << spotParser::GCC_BINARY)
      | (1ULL << spotParser::HEX))) != 0))) {
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
  enterRule(_localctx, 32, spotParser::RuleLogicVariable);

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
    match(spotParser::LT);
    setState(397);
    variable();
    setState(398);
    match(spotParser::T__5);
    setState(399);
    match(spotParser::SIGN);
    setState(400);
    match(spotParser::T__6);
    setState(401);
    match(spotParser::NUMERIC);
    setState(402);
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
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, spotParser::RuleNumeric, precedence);

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
    setState(411);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      setState(405);
      numericAtom();
      break;
    }

    case 2: {
      setState(406);
      logic(0);
      break;
    }

    case 3: {
      setState(407);
      match(spotParser::LPAREN);
      setState(408);
      numeric(0);
      setState(409);
      match(spotParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(421);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(419);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(413);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(414);
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
          setState(415);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(416);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(417);
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
          setState(418);
          numeric(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(423);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
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
  enterRule(_localctx, 36, spotParser::RuleNumericAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(426);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::NUMERIC: {
        enterOuterAlt(_localctx, 1);
        setState(424);
        numericConstant();
        break;
      }

      case spotParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(425);
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
  enterRule(_localctx, 38, spotParser::RuleNumericConstant);

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
  enterRule(_localctx, 40, spotParser::RuleNumericVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(430);
    match(spotParser::LT);
    setState(431);
    variable();
    setState(432);
    match(spotParser::T__8);
    setState(433);
    match(spotParser::NUMERIC);
    setState(434);
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
  enterRule(_localctx, 42, spotParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436);
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
  enterRule(_localctx, 44, spotParser::RuleRelop);
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
    setState(438);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << spotParser::GT)
      | (1ULL << spotParser::GE)
      | (1ULL << spotParser::LT)
      | (1ULL << spotParser::LE))) != 0))) {
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
    case 8: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 12: return logicSempred(antlrcpp::downCast<LogicContext *>(context), predicateIndex);
    case 17: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);

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
  std::call_once(spotParserOnceFlag, spotParserInitialize);
}
