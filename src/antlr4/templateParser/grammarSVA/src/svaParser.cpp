
// Generated from sva.g4 by ANTLR 4.10.1


#include "svaListener.h"

#include "svaParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SvaParserStaticData final {
  SvaParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SvaParserStaticData(const SvaParserStaticData&) = delete;
  SvaParserStaticData(SvaParserStaticData&&) = delete;
  SvaParserStaticData& operator=(const SvaParserStaticData&) = delete;
  SvaParserStaticData& operator=(SvaParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag svaParserOnceFlag;
SvaParserStaticData *svaParserStaticData = nullptr;

void svaParserInitialize() {
  assert(svaParserStaticData == nullptr);
  auto staticData = std::make_unique<SvaParserStaticData>(
    std::vector<std::string>{
      "file", "formula", "sere", "tformula", "placeholder", "dt_next", "dt_next_and", 
      "dt_NCReps", "boolean", "booleanAtom", "booleanConstant", "booleanVariable", 
      "logic", "bitSelect", "logicAtom", "logicConstant", "logicVariable", 
      "numeric", "numericAtom", "numericConstant", "numericVariable", "variable", 
      "relop"
    },
    std::vector<std::string>{
      "", "'P'", "'..##'", "'..#'", "'..[->'", "',bool>'", "',logic('", 
      "','", "')>'", "',numeric('", "'..&&..'", "", "'eventually'", "'always'", 
      "'nexttime'", "'until'", "'release'", "'..'", "'|->'", "'|=>'", "'iff'", 
      "'xor'", "'[]->'", "'[]=>'", "'='", "'##'", "';'", "':'", "'first_match'", 
      "", "'{'", "'}'", "'['", "']'", "'('", "')'", "", "", "", "", "", 
      "", "'+'", "'-'", "'*'", "'/'", "'>'", "'>='", "'<'", "'<='", "'=='", 
      "'!='", "'&'", "'|'", "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", 
      "'!'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "DT_AND", "SEP", "EVENTUALLY", 
      "ALWAYS", "NEXT", "UNTIL", "RELEASE", "DOTS", "IMPL", "IMPL2", "IFF", 
      "XOR", "BIND1", "BIND2", "ASS", "DELAY", "SCOL", "COL", "FIRST_MATCH", 
      "SIGN", "LGPAREN", "RGPAREN", "LCPAREN", "RCPAREN", "LPAREN", "RPAREN", 
      "VARIABLE", "NUMERIC", "VERILOG_BINARY", "GCC_BINARY", "HEX", "BOOLEAN", 
      "PLUS", "MINUS", "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", 
      "BAND", "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,61,429,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,57,8,0,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,
  	1,95,8,1,1,2,1,2,1,2,3,2,100,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,3,2,114,8,2,1,2,1,2,3,2,118,8,2,1,2,3,2,121,8,2,1,2,3,2,124,
  	8,2,1,2,1,2,1,2,1,2,3,2,130,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,150,8,2,1,2,3,2,153,8,2,1,2,3,2,
  	156,8,2,1,2,3,2,159,8,2,1,2,3,2,162,8,2,1,2,1,2,1,2,1,2,1,2,3,2,169,8,
  	2,1,2,3,2,172,8,2,1,2,3,2,175,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,3,2,187,8,2,1,2,3,2,190,8,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,198,8,2,1,
  	2,3,2,201,8,2,1,2,5,2,204,8,2,10,2,12,2,207,9,2,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,230,
  	8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,247,
  	8,3,10,3,12,3,250,9,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,3,8,304,8,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,5,8,318,8,8,10,8,12,8,321,9,8,1,9,1,9,3,9,325,8,9,1,10,1,10,
  	1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,3,12,341,
  	8,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,366,8,12,10,12,
  	12,12,369,9,12,1,13,1,13,1,13,1,13,3,13,375,8,13,1,13,1,13,1,14,1,14,
  	3,14,381,8,14,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,3,17,400,8,17,1,17,1,17,1,17,1,17,1,17,
  	1,17,5,17,408,8,17,10,17,12,17,411,9,17,1,18,1,18,3,18,415,8,18,1,19,
  	1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,21,1,21,1,22,1,22,1,22,0,5,4,6,16,
  	24,34,23,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,
  	44,0,4,1,0,44,45,1,0,42,43,1,0,37,40,1,0,46,49,490,0,56,1,0,0,0,2,94,
  	1,0,0,0,4,129,1,0,0,0,6,229,1,0,0,0,8,251,1,0,0,0,10,254,1,0,0,0,12,258,
  	1,0,0,0,14,263,1,0,0,0,16,303,1,0,0,0,18,324,1,0,0,0,20,326,1,0,0,0,22,
  	328,1,0,0,0,24,340,1,0,0,0,26,370,1,0,0,0,28,380,1,0,0,0,30,382,1,0,0,
  	0,32,384,1,0,0,0,34,399,1,0,0,0,36,414,1,0,0,0,38,416,1,0,0,0,40,418,
  	1,0,0,0,42,424,1,0,0,0,44,426,1,0,0,0,46,47,5,13,0,0,47,48,3,2,1,0,48,
  	49,5,0,0,1,49,57,1,0,0,0,50,51,5,13,0,0,51,52,5,34,0,0,52,53,3,2,1,0,
  	53,54,5,35,0,0,54,55,5,0,0,1,55,57,1,0,0,0,56,46,1,0,0,0,56,50,1,0,0,
  	0,57,1,1,0,0,0,58,59,3,6,3,0,59,60,5,18,0,0,60,61,3,6,3,0,61,95,1,0,0,
  	0,62,63,3,6,3,0,63,64,5,19,0,0,64,65,3,6,3,0,65,95,1,0,0,0,66,67,5,30,
  	0,0,67,68,3,4,2,0,68,69,5,31,0,0,69,70,5,32,0,0,70,71,5,33,0,0,71,72,
  	5,18,0,0,72,73,3,6,3,0,73,95,1,0,0,0,74,75,5,30,0,0,75,76,3,4,2,0,76,
  	77,5,31,0,0,77,78,5,32,0,0,78,79,5,33,0,0,79,80,5,19,0,0,80,81,3,6,3,
  	0,81,95,1,0,0,0,82,83,5,30,0,0,83,84,3,4,2,0,84,85,5,31,0,0,85,86,5,22,
  	0,0,86,87,3,6,3,0,87,95,1,0,0,0,88,89,5,30,0,0,89,90,3,4,2,0,90,91,5,
  	31,0,0,91,92,5,23,0,0,92,93,3,6,3,0,93,95,1,0,0,0,94,58,1,0,0,0,94,62,
  	1,0,0,0,94,66,1,0,0,0,94,74,1,0,0,0,94,82,1,0,0,0,94,88,1,0,0,0,95,3,
  	1,0,0,0,96,97,6,2,-1,0,97,130,3,16,8,0,98,100,5,60,0,0,99,98,1,0,0,0,
  	99,100,1,0,0,0,100,101,1,0,0,0,101,130,3,8,4,0,102,130,5,10,0,0,103,104,
  	5,34,0,0,104,105,3,4,2,0,105,106,5,35,0,0,106,130,1,0,0,0,107,108,5,30,
  	0,0,108,109,3,4,2,0,109,110,5,31,0,0,110,130,1,0,0,0,111,113,5,25,0,0,
  	112,114,5,32,0,0,113,112,1,0,0,0,113,114,1,0,0,0,114,115,1,0,0,0,115,
  	117,5,37,0,0,116,118,5,17,0,0,117,116,1,0,0,0,117,118,1,0,0,0,118,120,
  	1,0,0,0,119,121,5,37,0,0,120,119,1,0,0,0,120,121,1,0,0,0,121,123,1,0,
  	0,0,122,124,5,33,0,0,123,122,1,0,0,0,123,124,1,0,0,0,124,125,1,0,0,0,
  	125,130,3,4,2,5,126,130,3,10,5,0,127,130,3,12,6,0,128,130,3,14,7,0,129,
  	96,1,0,0,0,129,99,1,0,0,0,129,102,1,0,0,0,129,103,1,0,0,0,129,107,1,0,
  	0,0,129,111,1,0,0,0,129,126,1,0,0,0,129,127,1,0,0,0,129,128,1,0,0,0,130,
  	205,1,0,0,0,131,132,10,14,0,0,132,133,5,53,0,0,133,204,3,4,2,15,134,135,
  	10,13,0,0,135,136,5,52,0,0,136,204,3,4,2,14,137,138,10,12,0,0,138,139,
  	5,58,0,0,139,204,3,4,2,13,140,141,10,11,0,0,141,142,5,26,0,0,142,204,
  	3,4,2,12,143,144,10,10,0,0,144,145,5,27,0,0,145,204,3,4,2,11,146,147,
  	10,4,0,0,147,149,5,25,0,0,148,150,5,32,0,0,149,148,1,0,0,0,149,150,1,
  	0,0,0,150,152,1,0,0,0,151,153,5,37,0,0,152,151,1,0,0,0,152,153,1,0,0,
  	0,153,155,1,0,0,0,154,156,5,17,0,0,155,154,1,0,0,0,155,156,1,0,0,0,156,
  	158,1,0,0,0,157,159,5,37,0,0,158,157,1,0,0,0,158,159,1,0,0,0,159,161,
  	1,0,0,0,160,162,5,33,0,0,161,160,1,0,0,0,161,162,1,0,0,0,162,163,1,0,
  	0,0,163,204,3,4,2,5,164,165,10,9,0,0,165,166,5,32,0,0,166,168,5,44,0,
  	0,167,169,5,37,0,0,168,167,1,0,0,0,168,169,1,0,0,0,169,171,1,0,0,0,170,
  	172,5,17,0,0,171,170,1,0,0,0,171,172,1,0,0,0,172,174,1,0,0,0,173,175,
  	5,37,0,0,174,173,1,0,0,0,174,175,1,0,0,0,175,176,1,0,0,0,176,204,5,33,
  	0,0,177,178,10,8,0,0,178,179,5,32,0,0,179,180,5,42,0,0,180,204,5,33,0,
  	0,181,182,10,7,0,0,182,183,5,32,0,0,183,184,5,24,0,0,184,186,5,37,0,0,
  	185,187,5,17,0,0,186,185,1,0,0,0,186,187,1,0,0,0,187,189,1,0,0,0,188,
  	190,5,37,0,0,189,188,1,0,0,0,189,190,1,0,0,0,190,191,1,0,0,0,191,204,
  	5,33,0,0,192,193,10,6,0,0,193,194,5,32,0,0,194,195,5,18,0,0,195,197,5,
  	37,0,0,196,198,5,17,0,0,197,196,1,0,0,0,197,198,1,0,0,0,198,200,1,0,0,
  	0,199,201,5,37,0,0,200,199,1,0,0,0,200,201,1,0,0,0,201,202,1,0,0,0,202,
  	204,5,33,0,0,203,131,1,0,0,0,203,134,1,0,0,0,203,137,1,0,0,0,203,140,
  	1,0,0,0,203,143,1,0,0,0,203,146,1,0,0,0,203,164,1,0,0,0,203,177,1,0,0,
  	0,203,181,1,0,0,0,203,192,1,0,0,0,204,207,1,0,0,0,205,203,1,0,0,0,205,
  	206,1,0,0,0,206,5,1,0,0,0,207,205,1,0,0,0,208,209,6,3,-1,0,209,230,3,
  	16,8,0,210,230,3,8,4,0,211,230,5,10,0,0,212,213,5,34,0,0,213,214,3,6,
  	3,0,214,215,5,35,0,0,215,230,1,0,0,0,216,217,5,60,0,0,217,230,3,6,3,9,
  	218,219,5,14,0,0,219,220,5,32,0,0,220,221,5,37,0,0,221,222,5,33,0,0,222,
  	230,3,6,3,3,223,224,5,14,0,0,224,230,3,6,3,2,225,226,5,30,0,0,226,227,
  	3,4,2,0,227,228,5,31,0,0,228,230,1,0,0,0,229,208,1,0,0,0,229,210,1,0,
  	0,0,229,211,1,0,0,0,229,212,1,0,0,0,229,216,1,0,0,0,229,218,1,0,0,0,229,
  	223,1,0,0,0,229,225,1,0,0,0,230,248,1,0,0,0,231,232,10,8,0,0,232,233,
  	5,58,0,0,233,247,3,6,3,9,234,235,10,7,0,0,235,236,5,59,0,0,236,247,3,
  	6,3,8,237,238,10,6,0,0,238,239,5,21,0,0,239,247,3,6,3,7,240,241,10,5,
  	0,0,241,242,5,15,0,0,242,247,3,6,3,6,243,244,10,4,0,0,244,245,5,16,0,
  	0,245,247,3,6,3,5,246,231,1,0,0,0,246,234,1,0,0,0,246,237,1,0,0,0,246,
  	240,1,0,0,0,246,243,1,0,0,0,247,250,1,0,0,0,248,246,1,0,0,0,248,249,1,
  	0,0,0,249,7,1,0,0,0,250,248,1,0,0,0,251,252,5,1,0,0,252,253,5,37,0,0,
  	253,9,1,0,0,0,254,255,5,2,0,0,255,256,5,37,0,0,256,257,5,17,0,0,257,11,
  	1,0,0,0,258,259,5,3,0,0,259,260,5,37,0,0,260,261,5,52,0,0,261,262,5,17,
  	0,0,262,13,1,0,0,0,263,264,5,4,0,0,264,265,5,37,0,0,265,266,5,33,0,0,
  	266,267,5,11,0,0,267,268,5,17,0,0,268,15,1,0,0,0,269,270,6,8,-1,0,270,
  	271,5,60,0,0,271,304,3,16,8,15,272,273,3,24,12,0,273,274,3,44,22,0,274,
  	275,3,24,12,0,275,304,1,0,0,0,276,277,3,34,17,0,277,278,3,44,22,0,278,
  	279,3,34,17,0,279,304,1,0,0,0,280,281,3,24,12,0,281,282,5,50,0,0,282,
  	283,3,24,12,0,283,304,1,0,0,0,284,285,3,34,17,0,285,286,5,50,0,0,286,
  	287,3,34,17,0,287,304,1,0,0,0,288,289,3,24,12,0,289,290,5,51,0,0,290,
  	291,3,24,12,0,291,304,1,0,0,0,292,293,3,34,17,0,293,294,5,51,0,0,294,
  	295,3,34,17,0,295,304,1,0,0,0,296,304,3,18,9,0,297,304,3,24,12,0,298,
  	304,3,34,17,0,299,300,5,34,0,0,300,301,3,16,8,0,301,302,5,35,0,0,302,
  	304,1,0,0,0,303,269,1,0,0,0,303,272,1,0,0,0,303,276,1,0,0,0,303,280,1,
  	0,0,0,303,284,1,0,0,0,303,288,1,0,0,0,303,292,1,0,0,0,303,296,1,0,0,0,
  	303,297,1,0,0,0,303,298,1,0,0,0,303,299,1,0,0,0,304,319,1,0,0,0,305,306,
  	10,10,0,0,306,307,5,50,0,0,307,318,3,16,8,11,308,309,10,7,0,0,309,310,
  	5,51,0,0,310,318,3,16,8,8,311,312,10,6,0,0,312,313,5,58,0,0,313,318,3,
  	16,8,7,314,315,10,5,0,0,315,316,5,59,0,0,316,318,3,16,8,6,317,305,1,0,
  	0,0,317,308,1,0,0,0,317,311,1,0,0,0,317,314,1,0,0,0,318,321,1,0,0,0,319,
  	317,1,0,0,0,319,320,1,0,0,0,320,17,1,0,0,0,321,319,1,0,0,0,322,325,3,
  	20,10,0,323,325,3,22,11,0,324,322,1,0,0,0,324,323,1,0,0,0,325,19,1,0,
  	0,0,326,327,5,41,0,0,327,21,1,0,0,0,328,329,5,48,0,0,329,330,3,42,21,
  	0,330,331,5,5,0,0,331,23,1,0,0,0,332,333,6,12,-1,0,333,334,5,55,0,0,334,
  	341,3,24,12,11,335,341,3,28,14,0,336,337,5,34,0,0,337,338,3,24,12,0,338,
  	339,5,35,0,0,339,341,1,0,0,0,340,332,1,0,0,0,340,335,1,0,0,0,340,336,
  	1,0,0,0,341,367,1,0,0,0,342,343,10,9,0,0,343,344,7,0,0,0,344,366,3,24,
  	12,10,345,346,10,8,0,0,346,347,7,1,0,0,347,366,3,24,12,9,348,349,10,7,
  	0,0,349,350,5,56,0,0,350,366,3,24,12,8,351,352,10,6,0,0,352,353,5,57,
  	0,0,353,366,3,24,12,7,354,355,10,5,0,0,355,356,5,52,0,0,356,366,3,24,
  	12,6,357,358,10,4,0,0,358,359,5,54,0,0,359,366,3,24,12,5,360,361,10,3,
  	0,0,361,362,5,53,0,0,362,366,3,24,12,4,363,364,10,10,0,0,364,366,3,26,
  	13,0,365,342,1,0,0,0,365,345,1,0,0,0,365,348,1,0,0,0,365,351,1,0,0,0,
  	365,354,1,0,0,0,365,357,1,0,0,0,365,360,1,0,0,0,365,363,1,0,0,0,366,369,
  	1,0,0,0,367,365,1,0,0,0,367,368,1,0,0,0,368,25,1,0,0,0,369,367,1,0,0,
  	0,370,371,5,32,0,0,371,374,5,37,0,0,372,373,5,27,0,0,373,375,5,37,0,0,
  	374,372,1,0,0,0,374,375,1,0,0,0,375,376,1,0,0,0,376,377,5,33,0,0,377,
  	27,1,0,0,0,378,381,3,30,15,0,379,381,3,32,16,0,380,378,1,0,0,0,380,379,
  	1,0,0,0,381,29,1,0,0,0,382,383,7,2,0,0,383,31,1,0,0,0,384,385,5,48,0,
  	0,385,386,3,42,21,0,386,387,5,6,0,0,387,388,5,29,0,0,388,389,5,7,0,0,
  	389,390,5,37,0,0,390,391,5,8,0,0,391,33,1,0,0,0,392,393,6,17,-1,0,393,
  	400,3,36,18,0,394,400,3,24,12,0,395,396,5,34,0,0,396,397,3,34,17,0,397,
  	398,5,35,0,0,398,400,1,0,0,0,399,392,1,0,0,0,399,394,1,0,0,0,399,395,
  	1,0,0,0,400,409,1,0,0,0,401,402,10,5,0,0,402,403,7,0,0,0,403,408,3,34,
  	17,6,404,405,10,4,0,0,405,406,7,1,0,0,406,408,3,34,17,5,407,401,1,0,0,
  	0,407,404,1,0,0,0,408,411,1,0,0,0,409,407,1,0,0,0,409,410,1,0,0,0,410,
  	35,1,0,0,0,411,409,1,0,0,0,412,415,3,38,19,0,413,415,3,40,20,0,414,412,
  	1,0,0,0,414,413,1,0,0,0,415,37,1,0,0,0,416,417,5,37,0,0,417,39,1,0,0,
  	0,418,419,5,48,0,0,419,420,3,42,21,0,420,421,5,9,0,0,421,422,5,37,0,0,
  	422,423,5,8,0,0,423,41,1,0,0,0,424,425,5,36,0,0,425,43,1,0,0,0,426,427,
  	7,3,0,0,427,45,1,0,0,0,38,56,94,99,113,117,120,123,129,149,152,155,158,
  	161,168,171,174,186,189,197,200,203,205,229,246,248,303,317,319,324,340,
  	365,367,374,380,399,407,409,414
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  svaParserStaticData = staticData.release();
}

}

svaParser::svaParser(TokenStream *input) : svaParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

svaParser::svaParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  svaParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *svaParserStaticData->atn, svaParserStaticData->decisionToDFA, svaParserStaticData->sharedContextCache, options);
}

svaParser::~svaParser() {
  delete _interpreter;
}

const atn::ATN& svaParser::getATN() const {
  return *svaParserStaticData->atn;
}

std::string svaParser::getGrammarFileName() const {
  return "sva.g4";
}

const std::vector<std::string>& svaParser::getRuleNames() const {
  return svaParserStaticData->ruleNames;
}

const dfa::Vocabulary& svaParser::getVocabulary() const {
  return svaParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView svaParser::getSerializedATN() const {
  return svaParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

svaParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::FileContext::ALWAYS() {
  return getToken(svaParser::ALWAYS, 0);
}

svaParser::FormulaContext* svaParser::FileContext::formula() {
  return getRuleContext<svaParser::FormulaContext>(0);
}

tree::TerminalNode* svaParser::FileContext::EOF() {
  return getToken(svaParser::EOF, 0);
}

tree::TerminalNode* svaParser::FileContext::LPAREN() {
  return getToken(svaParser::LPAREN, 0);
}

tree::TerminalNode* svaParser::FileContext::RPAREN() {
  return getToken(svaParser::RPAREN, 0);
}


size_t svaParser::FileContext::getRuleIndex() const {
  return svaParser::RuleFile;
}

void svaParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void svaParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

svaParser::FileContext* svaParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, svaParser::RuleFile);

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
      match(svaParser::ALWAYS);
      setState(47);
      formula();
      setState(48);
      match(svaParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(50);
      match(svaParser::ALWAYS);
      setState(51);
      match(svaParser::LPAREN);
      setState(52);
      formula();
      setState(53);
      match(svaParser::RPAREN);
      setState(54);
      match(svaParser::EOF);
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

svaParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<svaParser::TformulaContext *> svaParser::FormulaContext::tformula() {
  return getRuleContexts<svaParser::TformulaContext>();
}

svaParser::TformulaContext* svaParser::FormulaContext::tformula(size_t i) {
  return getRuleContext<svaParser::TformulaContext>(i);
}

tree::TerminalNode* svaParser::FormulaContext::IMPL() {
  return getToken(svaParser::IMPL, 0);
}

tree::TerminalNode* svaParser::FormulaContext::IMPL2() {
  return getToken(svaParser::IMPL2, 0);
}

tree::TerminalNode* svaParser::FormulaContext::LGPAREN() {
  return getToken(svaParser::LGPAREN, 0);
}

svaParser::SereContext* svaParser::FormulaContext::sere() {
  return getRuleContext<svaParser::SereContext>(0);
}

tree::TerminalNode* svaParser::FormulaContext::RGPAREN() {
  return getToken(svaParser::RGPAREN, 0);
}

tree::TerminalNode* svaParser::FormulaContext::LCPAREN() {
  return getToken(svaParser::LCPAREN, 0);
}

tree::TerminalNode* svaParser::FormulaContext::RCPAREN() {
  return getToken(svaParser::RCPAREN, 0);
}

tree::TerminalNode* svaParser::FormulaContext::BIND1() {
  return getToken(svaParser::BIND1, 0);
}

tree::TerminalNode* svaParser::FormulaContext::BIND2() {
  return getToken(svaParser::BIND2, 0);
}


size_t svaParser::FormulaContext::getRuleIndex() const {
  return svaParser::RuleFormula;
}

void svaParser::FormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormula(this);
}

void svaParser::FormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormula(this);
}

svaParser::FormulaContext* svaParser::formula() {
  FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, getState());
  enterRule(_localctx, 2, svaParser::RuleFormula);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(94);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(58);
      tformula(0);
      setState(59);
      match(svaParser::IMPL);
      setState(60);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(62);
      tformula(0);
      setState(63);
      match(svaParser::IMPL2);
      setState(64);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(66);
      match(svaParser::LGPAREN);
      setState(67);
      sere(0);
      setState(68);
      match(svaParser::RGPAREN);
      setState(69);
      match(svaParser::LCPAREN);
      setState(70);
      match(svaParser::RCPAREN);
      setState(71);
      match(svaParser::IMPL);
      setState(72);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(74);
      match(svaParser::LGPAREN);
      setState(75);
      sere(0);
      setState(76);
      match(svaParser::RGPAREN);
      setState(77);
      match(svaParser::LCPAREN);
      setState(78);
      match(svaParser::RCPAREN);
      setState(79);
      match(svaParser::IMPL2);
      setState(80);
      tformula(0);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(82);
      match(svaParser::LGPAREN);
      setState(83);
      sere(0);
      setState(84);
      match(svaParser::RGPAREN);
      setState(85);
      match(svaParser::BIND1);
      setState(86);
      tformula(0);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(88);
      match(svaParser::LGPAREN);
      setState(89);
      sere(0);
      setState(90);
      match(svaParser::RGPAREN);
      setState(91);
      match(svaParser::BIND2);
      setState(92);
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

svaParser::SereContext::SereContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

svaParser::BooleanContext* svaParser::SereContext::boolean() {
  return getRuleContext<svaParser::BooleanContext>(0);
}

svaParser::PlaceholderContext* svaParser::SereContext::placeholder() {
  return getRuleContext<svaParser::PlaceholderContext>(0);
}

tree::TerminalNode* svaParser::SereContext::NOT() {
  return getToken(svaParser::NOT, 0);
}

tree::TerminalNode* svaParser::SereContext::DT_AND() {
  return getToken(svaParser::DT_AND, 0);
}

tree::TerminalNode* svaParser::SereContext::LPAREN() {
  return getToken(svaParser::LPAREN, 0);
}

std::vector<svaParser::SereContext *> svaParser::SereContext::sere() {
  return getRuleContexts<svaParser::SereContext>();
}

svaParser::SereContext* svaParser::SereContext::sere(size_t i) {
  return getRuleContext<svaParser::SereContext>(i);
}

tree::TerminalNode* svaParser::SereContext::RPAREN() {
  return getToken(svaParser::RPAREN, 0);
}

tree::TerminalNode* svaParser::SereContext::LGPAREN() {
  return getToken(svaParser::LGPAREN, 0);
}

tree::TerminalNode* svaParser::SereContext::RGPAREN() {
  return getToken(svaParser::RGPAREN, 0);
}

tree::TerminalNode* svaParser::SereContext::DELAY() {
  return getToken(svaParser::DELAY, 0);
}

std::vector<tree::TerminalNode *> svaParser::SereContext::NUMERIC() {
  return getTokens(svaParser::NUMERIC);
}

tree::TerminalNode* svaParser::SereContext::NUMERIC(size_t i) {
  return getToken(svaParser::NUMERIC, i);
}

tree::TerminalNode* svaParser::SereContext::LCPAREN() {
  return getToken(svaParser::LCPAREN, 0);
}

tree::TerminalNode* svaParser::SereContext::DOTS() {
  return getToken(svaParser::DOTS, 0);
}

tree::TerminalNode* svaParser::SereContext::RCPAREN() {
  return getToken(svaParser::RCPAREN, 0);
}

svaParser::Dt_nextContext* svaParser::SereContext::dt_next() {
  return getRuleContext<svaParser::Dt_nextContext>(0);
}

svaParser::Dt_next_andContext* svaParser::SereContext::dt_next_and() {
  return getRuleContext<svaParser::Dt_next_andContext>(0);
}

svaParser::Dt_NCRepsContext* svaParser::SereContext::dt_NCReps() {
  return getRuleContext<svaParser::Dt_NCRepsContext>(0);
}

tree::TerminalNode* svaParser::SereContext::BOR() {
  return getToken(svaParser::BOR, 0);
}

tree::TerminalNode* svaParser::SereContext::BAND() {
  return getToken(svaParser::BAND, 0);
}

tree::TerminalNode* svaParser::SereContext::AND() {
  return getToken(svaParser::AND, 0);
}

tree::TerminalNode* svaParser::SereContext::SCOL() {
  return getToken(svaParser::SCOL, 0);
}

tree::TerminalNode* svaParser::SereContext::COL() {
  return getToken(svaParser::COL, 0);
}

tree::TerminalNode* svaParser::SereContext::TIMES() {
  return getToken(svaParser::TIMES, 0);
}

tree::TerminalNode* svaParser::SereContext::PLUS() {
  return getToken(svaParser::PLUS, 0);
}

tree::TerminalNode* svaParser::SereContext::ASS() {
  return getToken(svaParser::ASS, 0);
}

tree::TerminalNode* svaParser::SereContext::IMPL() {
  return getToken(svaParser::IMPL, 0);
}


size_t svaParser::SereContext::getRuleIndex() const {
  return svaParser::RuleSere;
}

void svaParser::SereContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSere(this);
}

void svaParser::SereContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSere(this);
}


svaParser::SereContext* svaParser::sere() {
   return sere(0);
}

svaParser::SereContext* svaParser::sere(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  svaParser::SereContext *_localctx = _tracker.createInstance<SereContext>(_ctx, parentState);
  svaParser::SereContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, svaParser::RuleSere, precedence);

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
    setState(129);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(97);
      boolean(0);
      break;
    }

    case 2: {
      setState(99);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == svaParser::NOT) {
        setState(98);
        match(svaParser::NOT);
      }
      setState(101);
      placeholder();
      break;
    }

    case 3: {
      setState(102);
      match(svaParser::DT_AND);
      break;
    }

    case 4: {
      setState(103);
      match(svaParser::LPAREN);
      setState(104);
      sere(0);
      setState(105);
      match(svaParser::RPAREN);
      break;
    }

    case 5: {
      setState(107);
      match(svaParser::LGPAREN);
      setState(108);
      sere(0);
      setState(109);
      match(svaParser::RGPAREN);
      break;
    }

    case 6: {
      setState(111);
      match(svaParser::DELAY);
      setState(113);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == svaParser::LCPAREN) {
        setState(112);
        match(svaParser::LCPAREN);
      }
      setState(115);
      match(svaParser::NUMERIC);
      setState(117);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == svaParser::DOTS) {
        setState(116);
        match(svaParser::DOTS);
      }
      setState(120);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(119);
        match(svaParser::NUMERIC);
        break;
      }

      default:
        break;
      }
      setState(123);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == svaParser::RCPAREN) {
        setState(122);
        match(svaParser::RCPAREN);
      }
      setState(125);
      sere(5);
      break;
    }

    case 7: {
      setState(126);
      dt_next();
      break;
    }

    case 8: {
      setState(127);
      dt_next_and();
      break;
    }

    case 9: {
      setState(128);
      dt_NCReps();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(205);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(203);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(131);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(132);
          match(svaParser::BOR);
          setState(133);
          sere(15);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(134);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(135);
          match(svaParser::BAND);
          setState(136);
          sere(14);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(137);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(138);
          match(svaParser::AND);
          setState(139);
          sere(13);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(140);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(141);
          match(svaParser::SCOL);
          setState(142);
          sere(12);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(143);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(144);
          match(svaParser::COL);
          setState(145);
          sere(11);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(146);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(147);
          match(svaParser::DELAY);
          setState(149);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == svaParser::LCPAREN) {
            setState(148);
            match(svaParser::LCPAREN);
          }
          setState(152);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
          case 1: {
            setState(151);
            match(svaParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(155);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == svaParser::DOTS) {
            setState(154);
            match(svaParser::DOTS);
          }
          setState(158);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
          case 1: {
            setState(157);
            match(svaParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(161);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == svaParser::RCPAREN) {
            setState(160);
            match(svaParser::RCPAREN);
          }
          setState(163);
          sere(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(164);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(165);
          match(svaParser::LCPAREN);
          setState(166);
          match(svaParser::TIMES);
          setState(168);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
          case 1: {
            setState(167);
            match(svaParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(171);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == svaParser::DOTS) {
            setState(170);
            match(svaParser::DOTS);
          }
          setState(174);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == svaParser::NUMERIC) {
            setState(173);
            match(svaParser::NUMERIC);
          }
          setState(176);
          match(svaParser::RCPAREN);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(177);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(178);
          match(svaParser::LCPAREN);
          setState(179);
          match(svaParser::PLUS);
          setState(180);
          match(svaParser::RCPAREN);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(181);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(182);
          match(svaParser::LCPAREN);
          setState(183);
          match(svaParser::ASS);
          setState(184);
          match(svaParser::NUMERIC);
          setState(186);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == svaParser::DOTS) {
            setState(185);
            match(svaParser::DOTS);
          }
          setState(189);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == svaParser::NUMERIC) {
            setState(188);
            match(svaParser::NUMERIC);
          }
          setState(191);
          match(svaParser::RCPAREN);
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(192);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(193);
          match(svaParser::LCPAREN);
          setState(194);
          match(svaParser::IMPL);
          setState(195);
          match(svaParser::NUMERIC);
          setState(197);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == svaParser::DOTS) {
            setState(196);
            match(svaParser::DOTS);
          }
          setState(200);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == svaParser::NUMERIC) {
            setState(199);
            match(svaParser::NUMERIC);
          }
          setState(202);
          match(svaParser::RCPAREN);
          break;
        }

        default:
          break;
        } 
      }
      setState(207);
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

svaParser::TformulaContext::TformulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

svaParser::BooleanContext* svaParser::TformulaContext::boolean() {
  return getRuleContext<svaParser::BooleanContext>(0);
}

svaParser::PlaceholderContext* svaParser::TformulaContext::placeholder() {
  return getRuleContext<svaParser::PlaceholderContext>(0);
}

tree::TerminalNode* svaParser::TformulaContext::DT_AND() {
  return getToken(svaParser::DT_AND, 0);
}

tree::TerminalNode* svaParser::TformulaContext::LPAREN() {
  return getToken(svaParser::LPAREN, 0);
}

std::vector<svaParser::TformulaContext *> svaParser::TformulaContext::tformula() {
  return getRuleContexts<svaParser::TformulaContext>();
}

svaParser::TformulaContext* svaParser::TformulaContext::tformula(size_t i) {
  return getRuleContext<svaParser::TformulaContext>(i);
}

tree::TerminalNode* svaParser::TformulaContext::RPAREN() {
  return getToken(svaParser::RPAREN, 0);
}

tree::TerminalNode* svaParser::TformulaContext::NOT() {
  return getToken(svaParser::NOT, 0);
}

tree::TerminalNode* svaParser::TformulaContext::NEXT() {
  return getToken(svaParser::NEXT, 0);
}

tree::TerminalNode* svaParser::TformulaContext::LCPAREN() {
  return getToken(svaParser::LCPAREN, 0);
}

tree::TerminalNode* svaParser::TformulaContext::NUMERIC() {
  return getToken(svaParser::NUMERIC, 0);
}

tree::TerminalNode* svaParser::TformulaContext::RCPAREN() {
  return getToken(svaParser::RCPAREN, 0);
}

tree::TerminalNode* svaParser::TformulaContext::LGPAREN() {
  return getToken(svaParser::LGPAREN, 0);
}

svaParser::SereContext* svaParser::TformulaContext::sere() {
  return getRuleContext<svaParser::SereContext>(0);
}

tree::TerminalNode* svaParser::TformulaContext::RGPAREN() {
  return getToken(svaParser::RGPAREN, 0);
}

tree::TerminalNode* svaParser::TformulaContext::AND() {
  return getToken(svaParser::AND, 0);
}

tree::TerminalNode* svaParser::TformulaContext::OR() {
  return getToken(svaParser::OR, 0);
}

tree::TerminalNode* svaParser::TformulaContext::XOR() {
  return getToken(svaParser::XOR, 0);
}

tree::TerminalNode* svaParser::TformulaContext::UNTIL() {
  return getToken(svaParser::UNTIL, 0);
}

tree::TerminalNode* svaParser::TformulaContext::RELEASE() {
  return getToken(svaParser::RELEASE, 0);
}


size_t svaParser::TformulaContext::getRuleIndex() const {
  return svaParser::RuleTformula;
}

void svaParser::TformulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTformula(this);
}

void svaParser::TformulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTformula(this);
}


svaParser::TformulaContext* svaParser::tformula() {
   return tformula(0);
}

svaParser::TformulaContext* svaParser::tformula(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  svaParser::TformulaContext *_localctx = _tracker.createInstance<TformulaContext>(_ctx, parentState);
  svaParser::TformulaContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, svaParser::RuleTformula, precedence);

    

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
    setState(229);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(209);
      boolean(0);
      break;
    }

    case 2: {
      setState(210);
      placeholder();
      break;
    }

    case 3: {
      setState(211);
      match(svaParser::DT_AND);
      break;
    }

    case 4: {
      setState(212);
      match(svaParser::LPAREN);
      setState(213);
      tformula(0);
      setState(214);
      match(svaParser::RPAREN);
      break;
    }

    case 5: {
      setState(216);
      match(svaParser::NOT);
      setState(217);
      tformula(9);
      break;
    }

    case 6: {
      setState(218);
      match(svaParser::NEXT);
      setState(219);
      match(svaParser::LCPAREN);
      setState(220);
      match(svaParser::NUMERIC);
      setState(221);
      match(svaParser::RCPAREN);
      setState(222);
      tformula(3);
      break;
    }

    case 7: {
      setState(223);
      match(svaParser::NEXT);
      setState(224);
      tformula(2);
      break;
    }

    case 8: {
      setState(225);
      match(svaParser::LGPAREN);
      setState(226);
      sere(0);
      setState(227);
      match(svaParser::RGPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(248);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(246);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(231);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(232);
          match(svaParser::AND);
          setState(233);
          tformula(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(234);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(235);
          match(svaParser::OR);
          setState(236);
          tformula(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(237);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(238);
          match(svaParser::XOR);
          setState(239);
          tformula(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(240);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(241);
          match(svaParser::UNTIL);
          setState(242);
          tformula(6);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(243);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(244);
          match(svaParser::RELEASE);
          setState(245);
          tformula(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(250);
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

svaParser::PlaceholderContext::PlaceholderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::PlaceholderContext::NUMERIC() {
  return getToken(svaParser::NUMERIC, 0);
}


size_t svaParser::PlaceholderContext::getRuleIndex() const {
  return svaParser::RulePlaceholder;
}

void svaParser::PlaceholderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlaceholder(this);
}

void svaParser::PlaceholderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlaceholder(this);
}

svaParser::PlaceholderContext* svaParser::placeholder() {
  PlaceholderContext *_localctx = _tracker.createInstance<PlaceholderContext>(_ctx, getState());
  enterRule(_localctx, 8, svaParser::RulePlaceholder);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(251);
    match(svaParser::T__0);
    setState(252);
    match(svaParser::NUMERIC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_nextContext ------------------------------------------------------------------

svaParser::Dt_nextContext::Dt_nextContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::Dt_nextContext::NUMERIC() {
  return getToken(svaParser::NUMERIC, 0);
}

tree::TerminalNode* svaParser::Dt_nextContext::DOTS() {
  return getToken(svaParser::DOTS, 0);
}


size_t svaParser::Dt_nextContext::getRuleIndex() const {
  return svaParser::RuleDt_next;
}

void svaParser::Dt_nextContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_next(this);
}

void svaParser::Dt_nextContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_next(this);
}

svaParser::Dt_nextContext* svaParser::dt_next() {
  Dt_nextContext *_localctx = _tracker.createInstance<Dt_nextContext>(_ctx, getState());
  enterRule(_localctx, 10, svaParser::RuleDt_next);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    match(svaParser::T__1);
    setState(255);
    match(svaParser::NUMERIC);
    setState(256);
    match(svaParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_next_andContext ------------------------------------------------------------------

svaParser::Dt_next_andContext::Dt_next_andContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::Dt_next_andContext::NUMERIC() {
  return getToken(svaParser::NUMERIC, 0);
}

tree::TerminalNode* svaParser::Dt_next_andContext::BAND() {
  return getToken(svaParser::BAND, 0);
}

tree::TerminalNode* svaParser::Dt_next_andContext::DOTS() {
  return getToken(svaParser::DOTS, 0);
}


size_t svaParser::Dt_next_andContext::getRuleIndex() const {
  return svaParser::RuleDt_next_and;
}

void svaParser::Dt_next_andContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_next_and(this);
}

void svaParser::Dt_next_andContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_next_and(this);
}

svaParser::Dt_next_andContext* svaParser::dt_next_and() {
  Dt_next_andContext *_localctx = _tracker.createInstance<Dt_next_andContext>(_ctx, getState());
  enterRule(_localctx, 12, svaParser::RuleDt_next_and);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(258);
    match(svaParser::T__2);
    setState(259);
    match(svaParser::NUMERIC);
    setState(260);
    match(svaParser::BAND);
    setState(261);
    match(svaParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_NCRepsContext ------------------------------------------------------------------

svaParser::Dt_NCRepsContext::Dt_NCRepsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::Dt_NCRepsContext::NUMERIC() {
  return getToken(svaParser::NUMERIC, 0);
}

tree::TerminalNode* svaParser::Dt_NCRepsContext::RCPAREN() {
  return getToken(svaParser::RCPAREN, 0);
}

tree::TerminalNode* svaParser::Dt_NCRepsContext::SEP() {
  return getToken(svaParser::SEP, 0);
}

tree::TerminalNode* svaParser::Dt_NCRepsContext::DOTS() {
  return getToken(svaParser::DOTS, 0);
}


size_t svaParser::Dt_NCRepsContext::getRuleIndex() const {
  return svaParser::RuleDt_NCReps;
}

void svaParser::Dt_NCRepsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_NCReps(this);
}

void svaParser::Dt_NCRepsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_NCReps(this);
}

svaParser::Dt_NCRepsContext* svaParser::dt_NCReps() {
  Dt_NCRepsContext *_localctx = _tracker.createInstance<Dt_NCRepsContext>(_ctx, getState());
  enterRule(_localctx, 14, svaParser::RuleDt_NCReps);

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
    match(svaParser::T__3);
    setState(264);
    match(svaParser::NUMERIC);
    setState(265);
    match(svaParser::RCPAREN);
    setState(266);
    match(svaParser::SEP);
    setState(267);
    match(svaParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

svaParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::BooleanContext::NOT() {
  return getToken(svaParser::NOT, 0);
}

std::vector<svaParser::BooleanContext *> svaParser::BooleanContext::boolean() {
  return getRuleContexts<svaParser::BooleanContext>();
}

svaParser::BooleanContext* svaParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<svaParser::BooleanContext>(i);
}

std::vector<svaParser::LogicContext *> svaParser::BooleanContext::logic() {
  return getRuleContexts<svaParser::LogicContext>();
}

svaParser::LogicContext* svaParser::BooleanContext::logic(size_t i) {
  return getRuleContext<svaParser::LogicContext>(i);
}

svaParser::RelopContext* svaParser::BooleanContext::relop() {
  return getRuleContext<svaParser::RelopContext>(0);
}

std::vector<svaParser::NumericContext *> svaParser::BooleanContext::numeric() {
  return getRuleContexts<svaParser::NumericContext>();
}

svaParser::NumericContext* svaParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<svaParser::NumericContext>(i);
}

tree::TerminalNode* svaParser::BooleanContext::EQ() {
  return getToken(svaParser::EQ, 0);
}

tree::TerminalNode* svaParser::BooleanContext::NEQ() {
  return getToken(svaParser::NEQ, 0);
}

svaParser::BooleanAtomContext* svaParser::BooleanContext::booleanAtom() {
  return getRuleContext<svaParser::BooleanAtomContext>(0);
}

tree::TerminalNode* svaParser::BooleanContext::LPAREN() {
  return getToken(svaParser::LPAREN, 0);
}

tree::TerminalNode* svaParser::BooleanContext::RPAREN() {
  return getToken(svaParser::RPAREN, 0);
}

tree::TerminalNode* svaParser::BooleanContext::AND() {
  return getToken(svaParser::AND, 0);
}

tree::TerminalNode* svaParser::BooleanContext::OR() {
  return getToken(svaParser::OR, 0);
}


size_t svaParser::BooleanContext::getRuleIndex() const {
  return svaParser::RuleBoolean;
}

void svaParser::BooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolean(this);
}

void svaParser::BooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolean(this);
}


svaParser::BooleanContext* svaParser::boolean() {
   return boolean(0);
}

svaParser::BooleanContext* svaParser::boolean(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  svaParser::BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, parentState);
  svaParser::BooleanContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, svaParser::RuleBoolean, precedence);

    

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      setState(270);
      match(svaParser::NOT);
      setState(271);
      boolean(15);
      break;
    }

    case 2: {
      setState(272);
      logic(0);
      setState(273);
      relop();
      setState(274);
      logic(0);
      break;
    }

    case 3: {
      setState(276);
      numeric(0);
      setState(277);
      relop();
      setState(278);
      numeric(0);
      break;
    }

    case 4: {
      setState(280);
      logic(0);
      setState(281);
      match(svaParser::EQ);
      setState(282);
      logic(0);
      break;
    }

    case 5: {
      setState(284);
      numeric(0);
      setState(285);
      match(svaParser::EQ);
      setState(286);
      numeric(0);
      break;
    }

    case 6: {
      setState(288);
      logic(0);
      setState(289);
      match(svaParser::NEQ);
      setState(290);
      logic(0);
      break;
    }

    case 7: {
      setState(292);
      numeric(0);
      setState(293);
      match(svaParser::NEQ);
      setState(294);
      numeric(0);
      break;
    }

    case 8: {
      setState(296);
      booleanAtom();
      break;
    }

    case 9: {
      setState(297);
      logic(0);
      break;
    }

    case 10: {
      setState(298);
      numeric(0);
      break;
    }

    case 11: {
      setState(299);
      match(svaParser::LPAREN);
      setState(300);
      boolean(0);
      setState(301);
      match(svaParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(319);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(317);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(305);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(306);
          match(svaParser::EQ);
          setState(307);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(308);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(309);
          match(svaParser::NEQ);
          setState(310);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(311);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(312);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(svaParser::AND);
          setState(313);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(314);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(315);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(svaParser::OR);
          setState(316);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(321);
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

svaParser::BooleanAtomContext::BooleanAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

svaParser::BooleanConstantContext* svaParser::BooleanAtomContext::booleanConstant() {
  return getRuleContext<svaParser::BooleanConstantContext>(0);
}

svaParser::BooleanVariableContext* svaParser::BooleanAtomContext::booleanVariable() {
  return getRuleContext<svaParser::BooleanVariableContext>(0);
}


size_t svaParser::BooleanAtomContext::getRuleIndex() const {
  return svaParser::RuleBooleanAtom;
}

void svaParser::BooleanAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanAtom(this);
}

void svaParser::BooleanAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanAtom(this);
}

svaParser::BooleanAtomContext* svaParser::booleanAtom() {
  BooleanAtomContext *_localctx = _tracker.createInstance<BooleanAtomContext>(_ctx, getState());
  enterRule(_localctx, 18, svaParser::RuleBooleanAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(324);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case svaParser::BOOLEAN: {
        enterOuterAlt(_localctx, 1);
        setState(322);
        booleanConstant();
        break;
      }

      case svaParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(323);
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

svaParser::BooleanConstantContext::BooleanConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::BooleanConstantContext::BOOLEAN() {
  return getToken(svaParser::BOOLEAN, 0);
}


size_t svaParser::BooleanConstantContext::getRuleIndex() const {
  return svaParser::RuleBooleanConstant;
}

void svaParser::BooleanConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanConstant(this);
}

void svaParser::BooleanConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanConstant(this);
}

svaParser::BooleanConstantContext* svaParser::booleanConstant() {
  BooleanConstantContext *_localctx = _tracker.createInstance<BooleanConstantContext>(_ctx, getState());
  enterRule(_localctx, 20, svaParser::RuleBooleanConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(326);
    match(svaParser::BOOLEAN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanVariableContext ------------------------------------------------------------------

svaParser::BooleanVariableContext::BooleanVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::BooleanVariableContext::LT() {
  return getToken(svaParser::LT, 0);
}

svaParser::VariableContext* svaParser::BooleanVariableContext::variable() {
  return getRuleContext<svaParser::VariableContext>(0);
}


size_t svaParser::BooleanVariableContext::getRuleIndex() const {
  return svaParser::RuleBooleanVariable;
}

void svaParser::BooleanVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanVariable(this);
}

void svaParser::BooleanVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanVariable(this);
}

svaParser::BooleanVariableContext* svaParser::booleanVariable() {
  BooleanVariableContext *_localctx = _tracker.createInstance<BooleanVariableContext>(_ctx, getState());
  enterRule(_localctx, 22, svaParser::RuleBooleanVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(328);
    match(svaParser::LT);
    setState(329);
    variable();
    setState(330);
    match(svaParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicContext ------------------------------------------------------------------

svaParser::LogicContext::LogicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::LogicContext::NEG() {
  return getToken(svaParser::NEG, 0);
}

std::vector<svaParser::LogicContext *> svaParser::LogicContext::logic() {
  return getRuleContexts<svaParser::LogicContext>();
}

svaParser::LogicContext* svaParser::LogicContext::logic(size_t i) {
  return getRuleContext<svaParser::LogicContext>(i);
}

svaParser::LogicAtomContext* svaParser::LogicContext::logicAtom() {
  return getRuleContext<svaParser::LogicAtomContext>(0);
}

tree::TerminalNode* svaParser::LogicContext::LPAREN() {
  return getToken(svaParser::LPAREN, 0);
}

tree::TerminalNode* svaParser::LogicContext::RPAREN() {
  return getToken(svaParser::RPAREN, 0);
}

tree::TerminalNode* svaParser::LogicContext::TIMES() {
  return getToken(svaParser::TIMES, 0);
}

tree::TerminalNode* svaParser::LogicContext::DIV() {
  return getToken(svaParser::DIV, 0);
}

tree::TerminalNode* svaParser::LogicContext::PLUS() {
  return getToken(svaParser::PLUS, 0);
}

tree::TerminalNode* svaParser::LogicContext::MINUS() {
  return getToken(svaParser::MINUS, 0);
}

tree::TerminalNode* svaParser::LogicContext::LSHIFT() {
  return getToken(svaParser::LSHIFT, 0);
}

tree::TerminalNode* svaParser::LogicContext::RSHIFT() {
  return getToken(svaParser::RSHIFT, 0);
}

tree::TerminalNode* svaParser::LogicContext::BAND() {
  return getToken(svaParser::BAND, 0);
}

tree::TerminalNode* svaParser::LogicContext::BXOR() {
  return getToken(svaParser::BXOR, 0);
}

tree::TerminalNode* svaParser::LogicContext::BOR() {
  return getToken(svaParser::BOR, 0);
}

svaParser::BitSelectContext* svaParser::LogicContext::bitSelect() {
  return getRuleContext<svaParser::BitSelectContext>(0);
}


size_t svaParser::LogicContext::getRuleIndex() const {
  return svaParser::RuleLogic;
}

void svaParser::LogicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic(this);
}

void svaParser::LogicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic(this);
}


svaParser::LogicContext* svaParser::logic() {
   return logic(0);
}

svaParser::LogicContext* svaParser::logic(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  svaParser::LogicContext *_localctx = _tracker.createInstance<LogicContext>(_ctx, parentState);
  svaParser::LogicContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, svaParser::RuleLogic, precedence);

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
    setState(340);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case svaParser::NEG: {
        setState(333);
        match(svaParser::NEG);
        setState(334);
        logic(11);
        break;
      }

      case svaParser::NUMERIC:
      case svaParser::VERILOG_BINARY:
      case svaParser::GCC_BINARY:
      case svaParser::HEX:
      case svaParser::LT: {
        setState(335);
        logicAtom();
        break;
      }

      case svaParser::LPAREN: {
        setState(336);
        match(svaParser::LPAREN);
        setState(337);
        logic(0);
        setState(338);
        match(svaParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(367);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(365);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(342);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(343);
          antlrcpp::downCast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == svaParser::TIMES

          || _la == svaParser::DIV)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(344);
          logic(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(345);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(346);
          antlrcpp::downCast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == svaParser::PLUS

          || _la == svaParser::MINUS)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(347);
          logic(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(348);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(349);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(svaParser::LSHIFT);
          setState(350);
          logic(8);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(351);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(352);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(svaParser::RSHIFT);
          setState(353);
          logic(7);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(354);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(355);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(svaParser::BAND);
          setState(356);
          logic(6);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(357);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(358);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(svaParser::BXOR);
          setState(359);
          logic(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(360);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(361);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(svaParser::BOR);
          setState(362);
          logic(4);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(363);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(364);
          bitSelect();
          break;
        }

        default:
          break;
        } 
      }
      setState(369);
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

svaParser::BitSelectContext::BitSelectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::BitSelectContext::LCPAREN() {
  return getToken(svaParser::LCPAREN, 0);
}

std::vector<tree::TerminalNode *> svaParser::BitSelectContext::NUMERIC() {
  return getTokens(svaParser::NUMERIC);
}

tree::TerminalNode* svaParser::BitSelectContext::NUMERIC(size_t i) {
  return getToken(svaParser::NUMERIC, i);
}

tree::TerminalNode* svaParser::BitSelectContext::RCPAREN() {
  return getToken(svaParser::RCPAREN, 0);
}

tree::TerminalNode* svaParser::BitSelectContext::COL() {
  return getToken(svaParser::COL, 0);
}


size_t svaParser::BitSelectContext::getRuleIndex() const {
  return svaParser::RuleBitSelect;
}

void svaParser::BitSelectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitSelect(this);
}

void svaParser::BitSelectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitSelect(this);
}

svaParser::BitSelectContext* svaParser::bitSelect() {
  BitSelectContext *_localctx = _tracker.createInstance<BitSelectContext>(_ctx, getState());
  enterRule(_localctx, 26, svaParser::RuleBitSelect);
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
    setState(370);
    match(svaParser::LCPAREN);
    setState(371);
    match(svaParser::NUMERIC);
    setState(374);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == svaParser::COL) {
      setState(372);
      match(svaParser::COL);
      setState(373);
      match(svaParser::NUMERIC);
    }
    setState(376);
    match(svaParser::RCPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicAtomContext ------------------------------------------------------------------

svaParser::LogicAtomContext::LogicAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

svaParser::LogicConstantContext* svaParser::LogicAtomContext::logicConstant() {
  return getRuleContext<svaParser::LogicConstantContext>(0);
}

svaParser::LogicVariableContext* svaParser::LogicAtomContext::logicVariable() {
  return getRuleContext<svaParser::LogicVariableContext>(0);
}


size_t svaParser::LogicAtomContext::getRuleIndex() const {
  return svaParser::RuleLogicAtom;
}

void svaParser::LogicAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicAtom(this);
}

void svaParser::LogicAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicAtom(this);
}

svaParser::LogicAtomContext* svaParser::logicAtom() {
  LogicAtomContext *_localctx = _tracker.createInstance<LogicAtomContext>(_ctx, getState());
  enterRule(_localctx, 28, svaParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(380);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case svaParser::NUMERIC:
      case svaParser::VERILOG_BINARY:
      case svaParser::GCC_BINARY:
      case svaParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(378);
        logicConstant();
        break;
      }

      case svaParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(379);
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

svaParser::LogicConstantContext::LogicConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::LogicConstantContext::VERILOG_BINARY() {
  return getToken(svaParser::VERILOG_BINARY, 0);
}

tree::TerminalNode* svaParser::LogicConstantContext::GCC_BINARY() {
  return getToken(svaParser::GCC_BINARY, 0);
}

tree::TerminalNode* svaParser::LogicConstantContext::NUMERIC() {
  return getToken(svaParser::NUMERIC, 0);
}

tree::TerminalNode* svaParser::LogicConstantContext::HEX() {
  return getToken(svaParser::HEX, 0);
}


size_t svaParser::LogicConstantContext::getRuleIndex() const {
  return svaParser::RuleLogicConstant;
}

void svaParser::LogicConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicConstant(this);
}

void svaParser::LogicConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicConstant(this);
}

svaParser::LogicConstantContext* svaParser::logicConstant() {
  LogicConstantContext *_localctx = _tracker.createInstance<LogicConstantContext>(_ctx, getState());
  enterRule(_localctx, 30, svaParser::RuleLogicConstant);
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
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << svaParser::NUMERIC)
      | (1ULL << svaParser::VERILOG_BINARY)
      | (1ULL << svaParser::GCC_BINARY)
      | (1ULL << svaParser::HEX))) != 0))) {
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

svaParser::LogicVariableContext::LogicVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::LogicVariableContext::LT() {
  return getToken(svaParser::LT, 0);
}

svaParser::VariableContext* svaParser::LogicVariableContext::variable() {
  return getRuleContext<svaParser::VariableContext>(0);
}

tree::TerminalNode* svaParser::LogicVariableContext::SIGN() {
  return getToken(svaParser::SIGN, 0);
}

tree::TerminalNode* svaParser::LogicVariableContext::NUMERIC() {
  return getToken(svaParser::NUMERIC, 0);
}


size_t svaParser::LogicVariableContext::getRuleIndex() const {
  return svaParser::RuleLogicVariable;
}

void svaParser::LogicVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicVariable(this);
}

void svaParser::LogicVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicVariable(this);
}

svaParser::LogicVariableContext* svaParser::logicVariable() {
  LogicVariableContext *_localctx = _tracker.createInstance<LogicVariableContext>(_ctx, getState());
  enterRule(_localctx, 32, svaParser::RuleLogicVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(384);
    match(svaParser::LT);
    setState(385);
    variable();
    setState(386);
    match(svaParser::T__5);
    setState(387);
    match(svaParser::SIGN);
    setState(388);
    match(svaParser::T__6);
    setState(389);
    match(svaParser::NUMERIC);
    setState(390);
    match(svaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericContext ------------------------------------------------------------------

svaParser::NumericContext::NumericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

svaParser::NumericAtomContext* svaParser::NumericContext::numericAtom() {
  return getRuleContext<svaParser::NumericAtomContext>(0);
}

svaParser::LogicContext* svaParser::NumericContext::logic() {
  return getRuleContext<svaParser::LogicContext>(0);
}

tree::TerminalNode* svaParser::NumericContext::LPAREN() {
  return getToken(svaParser::LPAREN, 0);
}

std::vector<svaParser::NumericContext *> svaParser::NumericContext::numeric() {
  return getRuleContexts<svaParser::NumericContext>();
}

svaParser::NumericContext* svaParser::NumericContext::numeric(size_t i) {
  return getRuleContext<svaParser::NumericContext>(i);
}

tree::TerminalNode* svaParser::NumericContext::RPAREN() {
  return getToken(svaParser::RPAREN, 0);
}

tree::TerminalNode* svaParser::NumericContext::TIMES() {
  return getToken(svaParser::TIMES, 0);
}

tree::TerminalNode* svaParser::NumericContext::DIV() {
  return getToken(svaParser::DIV, 0);
}

tree::TerminalNode* svaParser::NumericContext::PLUS() {
  return getToken(svaParser::PLUS, 0);
}

tree::TerminalNode* svaParser::NumericContext::MINUS() {
  return getToken(svaParser::MINUS, 0);
}


size_t svaParser::NumericContext::getRuleIndex() const {
  return svaParser::RuleNumeric;
}

void svaParser::NumericContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void svaParser::NumericContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}


svaParser::NumericContext* svaParser::numeric() {
   return numeric(0);
}

svaParser::NumericContext* svaParser::numeric(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  svaParser::NumericContext *_localctx = _tracker.createInstance<NumericContext>(_ctx, parentState);
  svaParser::NumericContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, svaParser::RuleNumeric, precedence);

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
    setState(399);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      setState(393);
      numericAtom();
      break;
    }

    case 2: {
      setState(394);
      logic(0);
      break;
    }

    case 3: {
      setState(395);
      match(svaParser::LPAREN);
      setState(396);
      numeric(0);
      setState(397);
      match(svaParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(409);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(407);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(401);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(402);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == svaParser::TIMES

          || _la == svaParser::DIV)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(403);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(404);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(405);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == svaParser::PLUS

          || _la == svaParser::MINUS)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(406);
          numeric(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(411);
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

svaParser::NumericAtomContext::NumericAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

svaParser::NumericConstantContext* svaParser::NumericAtomContext::numericConstant() {
  return getRuleContext<svaParser::NumericConstantContext>(0);
}

svaParser::NumericVariableContext* svaParser::NumericAtomContext::numericVariable() {
  return getRuleContext<svaParser::NumericVariableContext>(0);
}


size_t svaParser::NumericAtomContext::getRuleIndex() const {
  return svaParser::RuleNumericAtom;
}

void svaParser::NumericAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericAtom(this);
}

void svaParser::NumericAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericAtom(this);
}

svaParser::NumericAtomContext* svaParser::numericAtom() {
  NumericAtomContext *_localctx = _tracker.createInstance<NumericAtomContext>(_ctx, getState());
  enterRule(_localctx, 36, svaParser::RuleNumericAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(414);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case svaParser::NUMERIC: {
        enterOuterAlt(_localctx, 1);
        setState(412);
        numericConstant();
        break;
      }

      case svaParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(413);
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

svaParser::NumericConstantContext::NumericConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::NumericConstantContext::NUMERIC() {
  return getToken(svaParser::NUMERIC, 0);
}


size_t svaParser::NumericConstantContext::getRuleIndex() const {
  return svaParser::RuleNumericConstant;
}

void svaParser::NumericConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericConstant(this);
}

void svaParser::NumericConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericConstant(this);
}

svaParser::NumericConstantContext* svaParser::numericConstant() {
  NumericConstantContext *_localctx = _tracker.createInstance<NumericConstantContext>(_ctx, getState());
  enterRule(_localctx, 38, svaParser::RuleNumericConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(416);
    match(svaParser::NUMERIC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericVariableContext ------------------------------------------------------------------

svaParser::NumericVariableContext::NumericVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::NumericVariableContext::LT() {
  return getToken(svaParser::LT, 0);
}

svaParser::VariableContext* svaParser::NumericVariableContext::variable() {
  return getRuleContext<svaParser::VariableContext>(0);
}

tree::TerminalNode* svaParser::NumericVariableContext::NUMERIC() {
  return getToken(svaParser::NUMERIC, 0);
}


size_t svaParser::NumericVariableContext::getRuleIndex() const {
  return svaParser::RuleNumericVariable;
}

void svaParser::NumericVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericVariable(this);
}

void svaParser::NumericVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericVariable(this);
}

svaParser::NumericVariableContext* svaParser::numericVariable() {
  NumericVariableContext *_localctx = _tracker.createInstance<NumericVariableContext>(_ctx, getState());
  enterRule(_localctx, 40, svaParser::RuleNumericVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(418);
    match(svaParser::LT);
    setState(419);
    variable();
    setState(420);
    match(svaParser::T__8);
    setState(421);
    match(svaParser::NUMERIC);
    setState(422);
    match(svaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

svaParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::VariableContext::VARIABLE() {
  return getToken(svaParser::VARIABLE, 0);
}


size_t svaParser::VariableContext::getRuleIndex() const {
  return svaParser::RuleVariable;
}

void svaParser::VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void svaParser::VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

svaParser::VariableContext* svaParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 42, svaParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(424);
    match(svaParser::VARIABLE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelopContext ------------------------------------------------------------------

svaParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* svaParser::RelopContext::GT() {
  return getToken(svaParser::GT, 0);
}

tree::TerminalNode* svaParser::RelopContext::GE() {
  return getToken(svaParser::GE, 0);
}

tree::TerminalNode* svaParser::RelopContext::LT() {
  return getToken(svaParser::LT, 0);
}

tree::TerminalNode* svaParser::RelopContext::LE() {
  return getToken(svaParser::LE, 0);
}


size_t svaParser::RelopContext::getRuleIndex() const {
  return svaParser::RuleRelop;
}

void svaParser::RelopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void svaParser::RelopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<svaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}

svaParser::RelopContext* svaParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 44, svaParser::RuleRelop);
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
    setState(426);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << svaParser::GT)
      | (1ULL << svaParser::GE)
      | (1ULL << svaParser::LT)
      | (1ULL << svaParser::LE))) != 0))) {
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

bool svaParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
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

bool svaParser::sereSempred(SereContext *_localctx, size_t predicateIndex) {
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

bool svaParser::tformulaSempred(TformulaContext *_localctx, size_t predicateIndex) {
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

bool svaParser::booleanSempred(BooleanContext *_localctx, size_t predicateIndex) {
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

bool svaParser::logicSempred(LogicContext *_localctx, size_t predicateIndex) {
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

bool svaParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 27: return precpred(_ctx, 5);
    case 28: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void svaParser::initialize() {
  std::call_once(svaParserOnceFlag, svaParserInitialize);
}
