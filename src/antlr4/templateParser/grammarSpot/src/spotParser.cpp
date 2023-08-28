
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
      "booleanAtom", "logic", "bitSelect", "logicAtom", "logic_constant", 
      "numeric", "numericAtom", "relop"
    },
    std::vector<std::string>{
      "", "", "'..&&..'", "", "", "", "", "'$stable'", "'F'", "'G'", "'X'", 
      "'U'", "'R'", "'..'", "'->'", "'=>'", "'<->'", "'xor'", "", "", "'='", 
      "'##'", "';'", "':'", "'$'", "", "", "", "", "", "", "'{'", "'}'", 
      "'['", "']'", "'('", "')'", "", "", "", "", "", "", "'+'", "'-'", 
      "'*'", "'/'", "'>'", "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", 
      "'|'", "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'"
    },
    std::vector<std::string>{
      "", "PLACEHOLDER", "DT_AND", "DT_NEXT", "DT_NEXT_AND", "DT_NCREPS", 
      "SEP", "FUNCTION", "EVENTUALLY", "ALWAYS", "NEXT", "UNTIL", "RELEASE", 
      "DOTS", "IMPL", "IMPLO", "IFF", "XOR", "SEREIMPL", "SEREIMPLO", "ASS", 
      "DELAY", "SCOL", "COL", "DOLLAR", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", 
      "LOGIC_VARIABLE", "CONST_SUFFIX", "NUMERIC_CONSTANT", "NUMERIC_VARIABLE", 
      "LCURLY", "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "SINTEGER", 
      "UINTEGER", "FLOAT", "VERILOG_BINARY", "GCC_BINARY", "HEX", "PLUS", 
      "MINUS", "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "BAND", 
      "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,62,357,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,1,0,1,0,
  	1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,39,8,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,61,8,1,1,2,
  	1,2,1,2,3,2,66,8,2,1,2,1,2,3,2,70,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,89,8,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,109,8,2,1,2,3,2,
  	112,8,2,1,2,3,2,115,8,2,1,2,3,2,118,8,2,1,2,3,2,121,8,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,3,2,132,8,2,1,2,3,2,135,8,2,1,2,3,2,138,8,2,1,2,
  	1,2,1,2,1,2,1,2,1,2,3,2,146,8,2,1,2,3,2,149,8,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,3,2,157,8,2,1,2,3,2,160,8,2,1,2,5,2,163,8,2,10,2,12,2,166,9,2,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,3,3,189,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,5,3,206,8,3,10,3,12,3,209,9,3,1,4,1,4,3,4,213,8,4,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,249,8,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,263,8,5,10,5,12,5,266,
  	9,5,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,278,8,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,5,7,303,8,7,10,7,12,7,306,9,7,1,8,1,8,1,8,1,8,3,8,312,8,8,1,8,
  	1,8,1,9,1,9,3,9,318,8,9,1,10,1,10,1,10,1,10,3,10,324,8,10,1,10,1,10,3,
  	10,328,8,10,1,10,3,10,331,8,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,
  	340,8,11,1,11,1,11,1,11,1,11,1,11,1,11,5,11,348,8,11,10,11,12,11,351,
  	9,11,1,12,1,12,1,13,1,13,1,13,0,5,4,6,10,14,22,14,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,0,6,2,0,24,24,38,38,1,0,25,26,1,0,45,46,1,0,43,44,1,
  	0,29,30,1,0,47,50,427,0,38,1,0,0,0,2,60,1,0,0,0,4,88,1,0,0,0,6,188,1,
  	0,0,0,8,212,1,0,0,0,10,248,1,0,0,0,12,267,1,0,0,0,14,277,1,0,0,0,16,307,
  	1,0,0,0,18,317,1,0,0,0,20,330,1,0,0,0,22,339,1,0,0,0,24,352,1,0,0,0,26,
  	354,1,0,0,0,28,29,5,9,0,0,29,30,5,35,0,0,30,31,3,2,1,0,31,32,5,36,0,0,
  	32,33,5,0,0,1,33,39,1,0,0,0,34,35,5,9,0,0,35,36,3,2,1,0,36,37,5,0,0,1,
  	37,39,1,0,0,0,38,28,1,0,0,0,38,34,1,0,0,0,39,1,1,0,0,0,40,41,3,6,3,0,
  	41,42,5,14,0,0,42,43,3,6,3,0,43,61,1,0,0,0,44,45,3,6,3,0,45,46,5,15,0,
  	0,46,47,3,6,3,0,47,61,1,0,0,0,48,49,5,31,0,0,49,50,3,4,2,0,50,51,5,32,
  	0,0,51,52,5,18,0,0,52,53,3,6,3,0,53,61,1,0,0,0,54,55,5,31,0,0,55,56,3,
  	4,2,0,56,57,5,32,0,0,57,58,5,19,0,0,58,59,3,6,3,0,59,61,1,0,0,0,60,40,
  	1,0,0,0,60,44,1,0,0,0,60,48,1,0,0,0,60,54,1,0,0,0,61,3,1,0,0,0,62,63,
  	6,2,-1,0,63,89,3,10,5,0,64,66,5,61,0,0,65,64,1,0,0,0,65,66,1,0,0,0,66,
  	67,1,0,0,0,67,89,5,1,0,0,68,70,5,61,0,0,69,68,1,0,0,0,69,70,1,0,0,0,70,
  	71,1,0,0,0,71,72,5,7,0,0,72,73,5,35,0,0,73,74,3,8,4,0,74,75,5,36,0,0,
  	75,89,1,0,0,0,76,89,5,2,0,0,77,78,5,35,0,0,78,79,3,4,2,0,79,80,5,36,0,
  	0,80,89,1,0,0,0,81,82,5,31,0,0,82,83,3,4,2,0,83,84,5,32,0,0,84,89,1,0,
  	0,0,85,89,5,3,0,0,86,89,5,4,0,0,87,89,5,5,0,0,88,62,1,0,0,0,88,65,1,0,
  	0,0,88,69,1,0,0,0,88,76,1,0,0,0,88,77,1,0,0,0,88,81,1,0,0,0,88,85,1,0,
  	0,0,88,86,1,0,0,0,88,87,1,0,0,0,89,164,1,0,0,0,90,91,10,13,0,0,91,92,
  	5,54,0,0,92,163,3,4,2,14,93,94,10,12,0,0,94,95,5,53,0,0,95,163,3,4,2,
  	13,96,97,10,11,0,0,97,98,5,59,0,0,98,163,3,4,2,12,99,100,10,10,0,0,100,
  	101,5,22,0,0,101,163,3,4,2,11,102,103,10,9,0,0,103,104,5,23,0,0,104,163,
  	3,4,2,10,105,106,10,4,0,0,106,108,5,21,0,0,107,109,5,33,0,0,108,107,1,
  	0,0,0,108,109,1,0,0,0,109,111,1,0,0,0,110,112,5,38,0,0,111,110,1,0,0,
  	0,111,112,1,0,0,0,112,114,1,0,0,0,113,115,5,13,0,0,114,113,1,0,0,0,114,
  	115,1,0,0,0,115,117,1,0,0,0,116,118,7,0,0,0,117,116,1,0,0,0,117,118,1,
  	0,0,0,118,120,1,0,0,0,119,121,5,34,0,0,120,119,1,0,0,0,120,121,1,0,0,
  	0,121,122,1,0,0,0,122,163,3,4,2,5,123,124,10,8,0,0,124,125,5,33,0,0,125,
  	126,5,43,0,0,126,163,5,34,0,0,127,128,10,7,0,0,128,129,5,33,0,0,129,131,
  	5,45,0,0,130,132,5,38,0,0,131,130,1,0,0,0,131,132,1,0,0,0,132,134,1,0,
  	0,0,133,135,5,13,0,0,134,133,1,0,0,0,134,135,1,0,0,0,135,137,1,0,0,0,
  	136,138,7,0,0,0,137,136,1,0,0,0,137,138,1,0,0,0,138,139,1,0,0,0,139,163,
  	5,34,0,0,140,141,10,6,0,0,141,142,5,33,0,0,142,143,5,20,0,0,143,145,5,
  	38,0,0,144,146,5,13,0,0,145,144,1,0,0,0,145,146,1,0,0,0,146,148,1,0,0,
  	0,147,149,7,0,0,0,148,147,1,0,0,0,148,149,1,0,0,0,149,150,1,0,0,0,150,
  	163,5,34,0,0,151,152,10,5,0,0,152,153,5,33,0,0,153,154,5,14,0,0,154,156,
  	5,38,0,0,155,157,5,13,0,0,156,155,1,0,0,0,156,157,1,0,0,0,157,159,1,0,
  	0,0,158,160,7,0,0,0,159,158,1,0,0,0,159,160,1,0,0,0,160,161,1,0,0,0,161,
  	163,5,34,0,0,162,90,1,0,0,0,162,93,1,0,0,0,162,96,1,0,0,0,162,99,1,0,
  	0,0,162,102,1,0,0,0,162,105,1,0,0,0,162,123,1,0,0,0,162,127,1,0,0,0,162,
  	140,1,0,0,0,162,151,1,0,0,0,163,166,1,0,0,0,164,162,1,0,0,0,164,165,1,
  	0,0,0,165,5,1,0,0,0,166,164,1,0,0,0,167,168,6,3,-1,0,168,189,3,10,5,0,
  	169,189,5,1,0,0,170,189,5,2,0,0,171,172,5,35,0,0,172,173,3,6,3,0,173,
  	174,5,36,0,0,174,189,1,0,0,0,175,176,5,61,0,0,176,189,3,6,3,9,177,178,
  	5,10,0,0,178,179,5,33,0,0,179,180,5,38,0,0,180,181,5,34,0,0,181,189,3,
  	6,3,3,182,183,5,10,0,0,183,189,3,6,3,2,184,185,5,31,0,0,185,186,3,4,2,
  	0,186,187,5,32,0,0,187,189,1,0,0,0,188,167,1,0,0,0,188,169,1,0,0,0,188,
  	170,1,0,0,0,188,171,1,0,0,0,188,175,1,0,0,0,188,177,1,0,0,0,188,182,1,
  	0,0,0,188,184,1,0,0,0,189,207,1,0,0,0,190,191,10,8,0,0,191,192,5,59,0,
  	0,192,206,3,6,3,9,193,194,10,7,0,0,194,195,5,60,0,0,195,206,3,6,3,8,196,
  	197,10,6,0,0,197,198,5,17,0,0,198,206,3,6,3,7,199,200,10,5,0,0,200,201,
  	5,11,0,0,201,206,3,6,3,6,202,203,10,4,0,0,203,204,5,12,0,0,204,206,3,
  	6,3,5,205,190,1,0,0,0,205,193,1,0,0,0,205,196,1,0,0,0,205,199,1,0,0,0,
  	205,202,1,0,0,0,206,209,1,0,0,0,207,205,1,0,0,0,207,208,1,0,0,0,208,7,
  	1,0,0,0,209,207,1,0,0,0,210,213,5,1,0,0,211,213,3,10,5,0,212,210,1,0,
  	0,0,212,211,1,0,0,0,213,9,1,0,0,0,214,215,6,5,-1,0,215,216,5,61,0,0,216,
  	249,3,10,5,15,217,218,3,14,7,0,218,219,3,26,13,0,219,220,3,14,7,0,220,
  	249,1,0,0,0,221,222,3,22,11,0,222,223,3,26,13,0,223,224,3,22,11,0,224,
  	249,1,0,0,0,225,226,3,14,7,0,226,227,5,51,0,0,227,228,3,14,7,0,228,249,
  	1,0,0,0,229,230,3,22,11,0,230,231,5,51,0,0,231,232,3,22,11,0,232,249,
  	1,0,0,0,233,234,3,14,7,0,234,235,5,52,0,0,235,236,3,14,7,0,236,249,1,
  	0,0,0,237,238,3,22,11,0,238,239,5,52,0,0,239,240,3,22,11,0,240,249,1,
  	0,0,0,241,249,3,12,6,0,242,249,3,14,7,0,243,249,3,22,11,0,244,245,5,35,
  	0,0,245,246,3,10,5,0,246,247,5,36,0,0,247,249,1,0,0,0,248,214,1,0,0,0,
  	248,217,1,0,0,0,248,221,1,0,0,0,248,225,1,0,0,0,248,229,1,0,0,0,248,233,
  	1,0,0,0,248,237,1,0,0,0,248,241,1,0,0,0,248,242,1,0,0,0,248,243,1,0,0,
  	0,248,244,1,0,0,0,249,264,1,0,0,0,250,251,10,10,0,0,251,252,5,51,0,0,
  	252,263,3,10,5,11,253,254,10,7,0,0,254,255,5,52,0,0,255,263,3,10,5,8,
  	256,257,10,6,0,0,257,258,5,59,0,0,258,263,3,10,5,7,259,260,10,5,0,0,260,
  	261,5,60,0,0,261,263,3,10,5,6,262,250,1,0,0,0,262,253,1,0,0,0,262,256,
  	1,0,0,0,262,259,1,0,0,0,263,266,1,0,0,0,264,262,1,0,0,0,264,265,1,0,0,
  	0,265,11,1,0,0,0,266,264,1,0,0,0,267,268,7,1,0,0,268,13,1,0,0,0,269,270,
  	6,7,-1,0,270,271,5,56,0,0,271,278,3,14,7,11,272,278,3,18,9,0,273,274,
  	5,35,0,0,274,275,3,14,7,0,275,276,5,36,0,0,276,278,1,0,0,0,277,269,1,
  	0,0,0,277,272,1,0,0,0,277,273,1,0,0,0,278,304,1,0,0,0,279,280,10,9,0,
  	0,280,281,7,2,0,0,281,303,3,14,7,10,282,283,10,8,0,0,283,284,7,3,0,0,
  	284,303,3,14,7,9,285,286,10,7,0,0,286,287,5,57,0,0,287,303,3,14,7,8,288,
  	289,10,6,0,0,289,290,5,58,0,0,290,303,3,14,7,7,291,292,10,5,0,0,292,293,
  	5,53,0,0,293,303,3,14,7,6,294,295,10,4,0,0,295,296,5,55,0,0,296,303,3,
  	14,7,5,297,298,10,3,0,0,298,299,5,54,0,0,299,303,3,14,7,4,300,301,10,
  	10,0,0,301,303,3,16,8,0,302,279,1,0,0,0,302,282,1,0,0,0,302,285,1,0,0,
  	0,302,288,1,0,0,0,302,291,1,0,0,0,302,294,1,0,0,0,302,297,1,0,0,0,302,
  	300,1,0,0,0,303,306,1,0,0,0,304,302,1,0,0,0,304,305,1,0,0,0,305,15,1,
  	0,0,0,306,304,1,0,0,0,307,308,5,33,0,0,308,311,5,38,0,0,309,310,5,23,
  	0,0,310,312,5,38,0,0,311,309,1,0,0,0,311,312,1,0,0,0,312,313,1,0,0,0,
  	313,314,5,34,0,0,314,17,1,0,0,0,315,318,3,20,10,0,316,318,5,27,0,0,317,
  	315,1,0,0,0,317,316,1,0,0,0,318,19,1,0,0,0,319,331,5,40,0,0,320,331,5,
  	41,0,0,321,323,5,37,0,0,322,324,5,28,0,0,323,322,1,0,0,0,323,324,1,0,
  	0,0,324,331,1,0,0,0,325,327,5,38,0,0,326,328,5,28,0,0,327,326,1,0,0,0,
  	327,328,1,0,0,0,328,331,1,0,0,0,329,331,5,42,0,0,330,319,1,0,0,0,330,
  	320,1,0,0,0,330,321,1,0,0,0,330,325,1,0,0,0,330,329,1,0,0,0,331,21,1,
  	0,0,0,332,333,6,11,-1,0,333,340,3,24,12,0,334,340,3,14,7,0,335,336,5,
  	35,0,0,336,337,3,22,11,0,337,338,5,36,0,0,338,340,1,0,0,0,339,332,1,0,
  	0,0,339,334,1,0,0,0,339,335,1,0,0,0,340,349,1,0,0,0,341,342,10,5,0,0,
  	342,343,7,2,0,0,343,348,3,22,11,6,344,345,10,4,0,0,345,346,7,3,0,0,346,
  	348,3,22,11,5,347,341,1,0,0,0,347,344,1,0,0,0,348,351,1,0,0,0,349,347,
  	1,0,0,0,349,350,1,0,0,0,350,23,1,0,0,0,351,349,1,0,0,0,352,353,7,4,0,
  	0,353,25,1,0,0,0,354,355,7,5,0,0,355,27,1,0,0,0,37,38,60,65,69,88,108,
  	111,114,117,120,131,134,137,145,148,156,159,162,164,188,205,207,212,248,
  	262,264,277,302,304,311,317,323,327,330,339,347,349
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

tree::TerminalNode* spotParser::FileContext::LROUND() {
  return getToken(spotParser::LROUND, 0);
}

spotParser::FormulaContext* spotParser::FileContext::formula() {
  return getRuleContext<spotParser::FormulaContext>(0);
}

tree::TerminalNode* spotParser::FileContext::RROUND() {
  return getToken(spotParser::RROUND, 0);
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
    setState(38);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(28);
      match(spotParser::ALWAYS);
      setState(29);
      match(spotParser::LROUND);
      setState(30);
      formula();
      setState(31);
      match(spotParser::RROUND);
      setState(32);
      match(spotParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(34);
      match(spotParser::ALWAYS);
      setState(35);
      formula();
      setState(36);
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

tree::TerminalNode* spotParser::FormulaContext::IMPLO() {
  return getToken(spotParser::IMPLO, 0);
}

tree::TerminalNode* spotParser::FormulaContext::LCURLY() {
  return getToken(spotParser::LCURLY, 0);
}

spotParser::SereContext* spotParser::FormulaContext::sere() {
  return getRuleContext<spotParser::SereContext>(0);
}

tree::TerminalNode* spotParser::FormulaContext::RCURLY() {
  return getToken(spotParser::RCURLY, 0);
}

tree::TerminalNode* spotParser::FormulaContext::SEREIMPL() {
  return getToken(spotParser::SEREIMPL, 0);
}

tree::TerminalNode* spotParser::FormulaContext::SEREIMPLO() {
  return getToken(spotParser::SEREIMPLO, 0);
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
    setState(60);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(40);
      tformula(0);
      setState(41);
      match(spotParser::IMPL);
      setState(42);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(44);
      tformula(0);
      setState(45);
      match(spotParser::IMPLO);
      setState(46);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(48);
      match(spotParser::LCURLY);
      setState(49);
      sere(0);
      setState(50);
      match(spotParser::RCURLY);
      setState(51);
      match(spotParser::SEREIMPL);
      setState(52);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(54);
      match(spotParser::LCURLY);
      setState(55);
      sere(0);
      setState(56);
      match(spotParser::RCURLY);
      setState(57);
      match(spotParser::SEREIMPLO);
      setState(58);
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

tree::TerminalNode* spotParser::SereContext::LROUND() {
  return getToken(spotParser::LROUND, 0);
}

spotParser::NonTemporalExpContext* spotParser::SereContext::nonTemporalExp() {
  return getRuleContext<spotParser::NonTemporalExpContext>(0);
}

tree::TerminalNode* spotParser::SereContext::RROUND() {
  return getToken(spotParser::RROUND, 0);
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

tree::TerminalNode* spotParser::SereContext::LCURLY() {
  return getToken(spotParser::LCURLY, 0);
}

tree::TerminalNode* spotParser::SereContext::RCURLY() {
  return getToken(spotParser::RCURLY, 0);
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

tree::TerminalNode* spotParser::SereContext::LSQUARED() {
  return getToken(spotParser::LSQUARED, 0);
}

std::vector<tree::TerminalNode *> spotParser::SereContext::UINTEGER() {
  return getTokens(spotParser::UINTEGER);
}

tree::TerminalNode* spotParser::SereContext::UINTEGER(size_t i) {
  return getToken(spotParser::UINTEGER, i);
}

tree::TerminalNode* spotParser::SereContext::DOTS() {
  return getToken(spotParser::DOTS, 0);
}

tree::TerminalNode* spotParser::SereContext::RSQUARED() {
  return getToken(spotParser::RSQUARED, 0);
}

tree::TerminalNode* spotParser::SereContext::DOLLAR() {
  return getToken(spotParser::DOLLAR, 0);
}

tree::TerminalNode* spotParser::SereContext::PLUS() {
  return getToken(spotParser::PLUS, 0);
}

tree::TerminalNode* spotParser::SereContext::TIMES() {
  return getToken(spotParser::TIMES, 0);
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
    setState(88);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(63);
      boolean(0);
      break;
    }

    case 2: {
      setState(65);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::NOT) {
        setState(64);
        match(spotParser::NOT);
      }
      setState(67);
      match(spotParser::PLACEHOLDER);
      break;
    }

    case 3: {
      setState(69);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::NOT) {
        setState(68);
        match(spotParser::NOT);
      }
      setState(71);
      match(spotParser::FUNCTION);
      setState(72);
      match(spotParser::LROUND);
      setState(73);
      nonTemporalExp();
      setState(74);
      match(spotParser::RROUND);
      break;
    }

    case 4: {
      setState(76);
      match(spotParser::DT_AND);
      break;
    }

    case 5: {
      setState(77);
      match(spotParser::LROUND);
      setState(78);
      sere(0);
      setState(79);
      match(spotParser::RROUND);
      break;
    }

    case 6: {
      setState(81);
      match(spotParser::LCURLY);
      setState(82);
      sere(0);
      setState(83);
      match(spotParser::RCURLY);
      break;
    }

    case 7: {
      setState(85);
      match(spotParser::DT_NEXT);
      break;
    }

    case 8: {
      setState(86);
      match(spotParser::DT_NEXT_AND);
      break;
    }

    case 9: {
      setState(87);
      match(spotParser::DT_NCREPS);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(164);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(162);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(90);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(91);
          match(spotParser::BOR);
          setState(92);
          sere(14);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(93);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(94);
          match(spotParser::BAND);
          setState(95);
          sere(13);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(96);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(97);
          match(spotParser::AND);
          setState(98);
          sere(12);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(99);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(100);
          match(spotParser::SCOL);
          setState(101);
          sere(11);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(102);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(103);
          match(spotParser::COL);
          setState(104);
          sere(10);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(105);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(106);
          match(spotParser::DELAY);
          setState(108);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::LSQUARED) {
            setState(107);
            match(spotParser::LSQUARED);
          }
          setState(111);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
          case 1: {
            setState(110);
            match(spotParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(114);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(113);
            match(spotParser::DOTS);
          }
          setState(117);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
          case 1: {
            setState(116);
            _la = _input->LA(1);
            if (!(_la == spotParser::DOLLAR

            || _la == spotParser::UINTEGER)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
            break;
          }

          default:
            break;
          }
          setState(120);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::RSQUARED) {
            setState(119);
            match(spotParser::RSQUARED);
          }
          setState(122);
          sere(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(123);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(124);
          match(spotParser::LSQUARED);
          setState(125);
          match(spotParser::PLUS);
          setState(126);
          match(spotParser::RSQUARED);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(127);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(128);
          match(spotParser::LSQUARED);
          setState(129);
          match(spotParser::TIMES);
          setState(131);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
          case 1: {
            setState(130);
            match(spotParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(134);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(133);
            match(spotParser::DOTS);
          }
          setState(137);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOLLAR

          || _la == spotParser::UINTEGER) {
            setState(136);
            _la = _input->LA(1);
            if (!(_la == spotParser::DOLLAR

            || _la == spotParser::UINTEGER)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
          }
          setState(139);
          match(spotParser::RSQUARED);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(140);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(141);
          match(spotParser::LSQUARED);
          setState(142);
          match(spotParser::ASS);
          setState(143);
          match(spotParser::UINTEGER);
          setState(145);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(144);
            match(spotParser::DOTS);
          }
          setState(148);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOLLAR

          || _la == spotParser::UINTEGER) {
            setState(147);
            _la = _input->LA(1);
            if (!(_la == spotParser::DOLLAR

            || _la == spotParser::UINTEGER)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
          }
          setState(150);
          match(spotParser::RSQUARED);
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(151);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(152);
          match(spotParser::LSQUARED);
          setState(153);
          match(spotParser::IMPL);
          setState(154);
          match(spotParser::UINTEGER);
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
          if (_la == spotParser::DOLLAR

          || _la == spotParser::UINTEGER) {
            setState(158);
            _la = _input->LA(1);
            if (!(_la == spotParser::DOLLAR

            || _la == spotParser::UINTEGER)) {
            _errHandler->recoverInline(this);
            }
            else {
              _errHandler->reportMatch(this);
              consume();
            }
          }
          setState(161);
          match(spotParser::RSQUARED);
          break;
        }

        default:
          break;
        } 
      }
      setState(166);
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

tree::TerminalNode* spotParser::TformulaContext::LROUND() {
  return getToken(spotParser::LROUND, 0);
}

std::vector<spotParser::TformulaContext *> spotParser::TformulaContext::tformula() {
  return getRuleContexts<spotParser::TformulaContext>();
}

spotParser::TformulaContext* spotParser::TformulaContext::tformula(size_t i) {
  return getRuleContext<spotParser::TformulaContext>(i);
}

tree::TerminalNode* spotParser::TformulaContext::RROUND() {
  return getToken(spotParser::RROUND, 0);
}

tree::TerminalNode* spotParser::TformulaContext::NOT() {
  return getToken(spotParser::NOT, 0);
}

tree::TerminalNode* spotParser::TformulaContext::NEXT() {
  return getToken(spotParser::NEXT, 0);
}

tree::TerminalNode* spotParser::TformulaContext::LSQUARED() {
  return getToken(spotParser::LSQUARED, 0);
}

tree::TerminalNode* spotParser::TformulaContext::UINTEGER() {
  return getToken(spotParser::UINTEGER, 0);
}

tree::TerminalNode* spotParser::TformulaContext::RSQUARED() {
  return getToken(spotParser::RSQUARED, 0);
}

tree::TerminalNode* spotParser::TformulaContext::LCURLY() {
  return getToken(spotParser::LCURLY, 0);
}

spotParser::SereContext* spotParser::TformulaContext::sere() {
  return getRuleContext<spotParser::SereContext>(0);
}

tree::TerminalNode* spotParser::TformulaContext::RCURLY() {
  return getToken(spotParser::RCURLY, 0);
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
    setState(188);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(168);
      boolean(0);
      break;
    }

    case 2: {
      setState(169);
      match(spotParser::PLACEHOLDER);
      break;
    }

    case 3: {
      setState(170);
      match(spotParser::DT_AND);
      break;
    }

    case 4: {
      setState(171);
      match(spotParser::LROUND);
      setState(172);
      tformula(0);
      setState(173);
      match(spotParser::RROUND);
      break;
    }

    case 5: {
      setState(175);
      match(spotParser::NOT);
      setState(176);
      tformula(9);
      break;
    }

    case 6: {
      setState(177);
      match(spotParser::NEXT);
      setState(178);
      match(spotParser::LSQUARED);
      setState(179);
      match(spotParser::UINTEGER);
      setState(180);
      match(spotParser::RSQUARED);
      setState(181);
      tformula(3);
      break;
    }

    case 7: {
      setState(182);
      match(spotParser::NEXT);
      setState(183);
      tformula(2);
      break;
    }

    case 8: {
      setState(184);
      match(spotParser::LCURLY);
      setState(185);
      sere(0);
      setState(186);
      match(spotParser::RCURLY);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(207);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(205);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(190);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(191);
          match(spotParser::AND);
          setState(192);
          tformula(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(193);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(194);
          match(spotParser::OR);
          setState(195);
          tformula(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(196);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(197);
          match(spotParser::XOR);
          setState(198);
          tformula(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(199);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(200);
          match(spotParser::UNTIL);
          setState(201);
          tformula(6);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(202);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(203);
          match(spotParser::RELEASE);
          setState(204);
          tformula(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(209);
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
    setState(212);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::PLACEHOLDER: {
        enterOuterAlt(_localctx, 1);
        setState(210);
        match(spotParser::PLACEHOLDER);
        break;
      }

      case spotParser::BOOLEAN_CONSTANT:
      case spotParser::BOOLEAN_VARIABLE:
      case spotParser::LOGIC_VARIABLE:
      case spotParser::NUMERIC_CONSTANT:
      case spotParser::NUMERIC_VARIABLE:
      case spotParser::LROUND:
      case spotParser::SINTEGER:
      case spotParser::UINTEGER:
      case spotParser::VERILOG_BINARY:
      case spotParser::GCC_BINARY:
      case spotParser::HEX:
      case spotParser::NEG:
      case spotParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(211);
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

tree::TerminalNode* spotParser::BooleanContext::LROUND() {
  return getToken(spotParser::LROUND, 0);
}

tree::TerminalNode* spotParser::BooleanContext::RROUND() {
  return getToken(spotParser::RROUND, 0);
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
    setState(248);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(215);
      match(spotParser::NOT);
      setState(216);
      boolean(15);
      break;
    }

    case 2: {
      setState(217);
      logic(0);
      setState(218);
      relop();
      setState(219);
      logic(0);
      break;
    }

    case 3: {
      setState(221);
      numeric(0);
      setState(222);
      relop();
      setState(223);
      numeric(0);
      break;
    }

    case 4: {
      setState(225);
      logic(0);
      setState(226);
      match(spotParser::EQ);
      setState(227);
      logic(0);
      break;
    }

    case 5: {
      setState(229);
      numeric(0);
      setState(230);
      match(spotParser::EQ);
      setState(231);
      numeric(0);
      break;
    }

    case 6: {
      setState(233);
      logic(0);
      setState(234);
      match(spotParser::NEQ);
      setState(235);
      logic(0);
      break;
    }

    case 7: {
      setState(237);
      numeric(0);
      setState(238);
      match(spotParser::NEQ);
      setState(239);
      numeric(0);
      break;
    }

    case 8: {
      setState(241);
      booleanAtom();
      break;
    }

    case 9: {
      setState(242);
      logic(0);
      break;
    }

    case 10: {
      setState(243);
      numeric(0);
      break;
    }

    case 11: {
      setState(244);
      match(spotParser::LROUND);
      setState(245);
      boolean(0);
      setState(246);
      match(spotParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(264);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(262);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(250);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(251);
          match(spotParser::EQ);
          setState(252);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(253);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(254);
          match(spotParser::NEQ);
          setState(255);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(256);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(257);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(spotParser::AND);
          setState(258);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(259);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(260);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(spotParser::OR);
          setState(261);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(266);
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
    setState(267);
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

tree::TerminalNode* spotParser::LogicContext::LROUND() {
  return getToken(spotParser::LROUND, 0);
}

tree::TerminalNode* spotParser::LogicContext::RROUND() {
  return getToken(spotParser::RROUND, 0);
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
    setState(277);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::NEG: {
        setState(270);
        match(spotParser::NEG);
        setState(271);
        logic(11);
        break;
      }

      case spotParser::LOGIC_VARIABLE:
      case spotParser::SINTEGER:
      case spotParser::UINTEGER:
      case spotParser::VERILOG_BINARY:
      case spotParser::GCC_BINARY:
      case spotParser::HEX: {
        setState(272);
        logicAtom();
        break;
      }

      case spotParser::LROUND: {
        setState(273);
        match(spotParser::LROUND);
        setState(274);
        logic(0);
        setState(275);
        match(spotParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(304);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(302);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(279);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(280);
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
          setState(281);
          logic(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(282);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(283);
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
          setState(284);
          logic(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(285);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(286);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::LSHIFT);
          setState(287);
          logic(8);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(288);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(289);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::RSHIFT);
          setState(290);
          logic(7);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(291);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(292);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BAND);
          setState(293);
          logic(6);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(294);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(295);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BXOR);
          setState(296);
          logic(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(297);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(298);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(spotParser::BOR);
          setState(299);
          logic(4);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(300);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(301);
          bitSelect();
          break;
        }

        default:
          break;
        } 
      }
      setState(306);
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

tree::TerminalNode* spotParser::BitSelectContext::LSQUARED() {
  return getToken(spotParser::LSQUARED, 0);
}

std::vector<tree::TerminalNode *> spotParser::BitSelectContext::UINTEGER() {
  return getTokens(spotParser::UINTEGER);
}

tree::TerminalNode* spotParser::BitSelectContext::UINTEGER(size_t i) {
  return getToken(spotParser::UINTEGER, i);
}

tree::TerminalNode* spotParser::BitSelectContext::RSQUARED() {
  return getToken(spotParser::RSQUARED, 0);
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
    setState(307);
    match(spotParser::LSQUARED);
    setState(308);
    match(spotParser::UINTEGER);
    setState(311);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == spotParser::COL) {
      setState(309);
      match(spotParser::COL);
      setState(310);
      match(spotParser::UINTEGER);
    }
    setState(313);
    match(spotParser::RSQUARED);
   
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

spotParser::Logic_constantContext* spotParser::LogicAtomContext::logic_constant() {
  return getRuleContext<spotParser::Logic_constantContext>(0);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(317);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::SINTEGER:
      case spotParser::UINTEGER:
      case spotParser::VERILOG_BINARY:
      case spotParser::GCC_BINARY:
      case spotParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(315);
        logic_constant();
        break;
      }

      case spotParser::LOGIC_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(316);
        match(spotParser::LOGIC_VARIABLE);
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

//----------------- Logic_constantContext ------------------------------------------------------------------

spotParser::Logic_constantContext::Logic_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* spotParser::Logic_constantContext::VERILOG_BINARY() {
  return getToken(spotParser::VERILOG_BINARY, 0);
}

tree::TerminalNode* spotParser::Logic_constantContext::GCC_BINARY() {
  return getToken(spotParser::GCC_BINARY, 0);
}

tree::TerminalNode* spotParser::Logic_constantContext::SINTEGER() {
  return getToken(spotParser::SINTEGER, 0);
}

tree::TerminalNode* spotParser::Logic_constantContext::CONST_SUFFIX() {
  return getToken(spotParser::CONST_SUFFIX, 0);
}

tree::TerminalNode* spotParser::Logic_constantContext::UINTEGER() {
  return getToken(spotParser::UINTEGER, 0);
}

tree::TerminalNode* spotParser::Logic_constantContext::HEX() {
  return getToken(spotParser::HEX, 0);
}


size_t spotParser::Logic_constantContext::getRuleIndex() const {
  return spotParser::RuleLogic_constant;
}

void spotParser::Logic_constantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic_constant(this);
}

void spotParser::Logic_constantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic_constant(this);
}

spotParser::Logic_constantContext* spotParser::logic_constant() {
  Logic_constantContext *_localctx = _tracker.createInstance<Logic_constantContext>(_ctx, getState());
  enterRule(_localctx, 20, spotParser::RuleLogic_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(330);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case spotParser::VERILOG_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(319);
        match(spotParser::VERILOG_BINARY);
        break;
      }

      case spotParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 2);
        setState(320);
        match(spotParser::GCC_BINARY);
        break;
      }

      case spotParser::SINTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(321);
        match(spotParser::SINTEGER);
        setState(323);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          setState(322);
          match(spotParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case spotParser::UINTEGER: {
        enterOuterAlt(_localctx, 4);
        setState(325);
        match(spotParser::UINTEGER);
        setState(327);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          setState(326);
          match(spotParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case spotParser::HEX: {
        enterOuterAlt(_localctx, 5);
        setState(329);
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

tree::TerminalNode* spotParser::NumericContext::LROUND() {
  return getToken(spotParser::LROUND, 0);
}

std::vector<spotParser::NumericContext *> spotParser::NumericContext::numeric() {
  return getRuleContexts<spotParser::NumericContext>();
}

spotParser::NumericContext* spotParser::NumericContext::numeric(size_t i) {
  return getRuleContext<spotParser::NumericContext>(i);
}

tree::TerminalNode* spotParser::NumericContext::RROUND() {
  return getToken(spotParser::RROUND, 0);
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
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, spotParser::RuleNumeric, precedence);

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
    setState(339);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      setState(333);
      numericAtom();
      break;
    }

    case 2: {
      setState(334);
      logic(0);
      break;
    }

    case 3: {
      setState(335);
      match(spotParser::LROUND);
      setState(336);
      numeric(0);
      setState(337);
      match(spotParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(349);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(347);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(341);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(342);
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
          setState(343);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(344);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(345);
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
          setState(346);
          numeric(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(351);
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
  enterRule(_localctx, 24, spotParser::RuleNumericAtom);
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
  enterRule(_localctx, 26, spotParser::RuleRelop);
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
    setState(354);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2111062325329920) != 0))) {
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
    case 11: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);

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
