
// Generated from proposition.g4 by ANTLR 4.12.0


#include "propositionLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct PropositionLexerStaticData final {
  PropositionLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PropositionLexerStaticData(const PropositionLexerStaticData&) = delete;
  PropositionLexerStaticData(PropositionLexerStaticData&&) = delete;
  PropositionLexerStaticData& operator=(const PropositionLexerStaticData&) = delete;
  PropositionLexerStaticData& operator=(PropositionLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag propositionlexerLexerOnceFlag;
PropositionLexerStaticData *propositionlexerLexerStaticData = nullptr;

void propositionlexerLexerInitialize() {
  assert(propositionlexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<PropositionLexerStaticData>(
    std::vector<std::string>{
      "T__0", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", "LOGIC_CONSTANT", 
      "LOGIC_VARIABLE", "SIGN", "CONST_SUFFIX", "NUMERIC_CONSTANT", "NUMERIC_VARIABLE", 
      "LGPAREN", "RGPAREN", "LCPAREN", "RCPAREN", "LPAREN", "RPAREN", "VARIABLE", 
      "VALID_ID_START", "VALID_ID_CHAR", "NUMERIC", "VERILOG_BINARY", "GCC_BINARY", 
      "HEX", "START_VAR", "END_VAR", "PLUS", "MINUS", "TIMES", "DIV", "GT", 
      "GE", "LT", "LE", "EQ", "NEQ", "BAND", "BOR", "BXOR", "NEG", "LSHIFT", 
      "RSHIFT", "AND", "OR", "NOT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "':'", "", "", "", "", "", "", "", "", "'{'", "'}'", "'['", "']'", 
      "'('", "')'", "", "", "", "", "'+'", "'-'", "'*'", "'/'", "'>'", "'>='", 
      "'<'", "'<='", "'=='", "'!='", "'&'", "'|'", "'^'", "'~'", "'<<'", 
      "'>>'", "'&&'", "'||'", "'!'"
    },
    std::vector<std::string>{
      "", "", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", "LOGIC_CONSTANT", 
      "LOGIC_VARIABLE", "SIGN", "CONST_SUFFIX", "NUMERIC_CONSTANT", "NUMERIC_VARIABLE", 
      "LGPAREN", "RGPAREN", "LCPAREN", "RCPAREN", "LPAREN", "RPAREN", "NUMERIC", 
      "VERILOG_BINARY", "GCC_BINARY", "HEX", "PLUS", "MINUS", "TIMES", "DIV", 
      "GT", "GE", "LT", "LE", "EQ", "NEQ", "BAND", "BOR", "BXOR", "NEG", 
      "LSHIFT", "RSHIFT", "AND", "OR", "NOT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,39,294,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,
  	1,103,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,3,3,
  	119,8,3,1,3,3,3,122,8,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,
  	4,1,4,1,4,1,4,1,4,1,5,1,5,1,6,1,6,1,6,1,6,1,6,3,6,147,8,6,1,7,1,7,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,
  	10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,5,15,181,8,
  	15,10,15,12,15,184,9,15,1,16,3,16,187,8,16,1,17,3,17,190,8,17,1,18,3,
  	18,193,8,18,1,18,4,18,196,8,18,11,18,12,18,197,1,18,1,18,4,18,202,8,18,
  	11,18,12,18,203,3,18,206,8,18,1,19,1,19,1,19,4,19,211,8,19,11,19,12,19,
  	212,1,20,1,20,1,20,1,20,4,20,219,8,20,11,20,12,20,220,1,21,1,21,1,21,
  	1,21,4,21,227,8,21,11,21,12,21,228,1,21,1,21,1,21,1,21,4,21,235,8,21,
  	11,21,12,21,236,3,21,239,8,21,1,22,1,22,1,23,1,23,1,24,1,24,1,25,1,25,
  	1,26,1,26,1,27,1,27,1,28,1,28,1,29,1,29,1,29,1,30,1,30,1,31,1,31,1,31,
  	1,32,1,32,1,32,1,33,1,33,1,33,1,34,1,34,1,35,1,35,1,36,1,36,1,37,1,37,
  	1,38,1,38,1,38,1,39,1,39,1,39,1,40,1,40,1,40,1,41,1,41,1,41,1,42,1,42,
  	1,43,1,43,1,43,1,43,0,0,44,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,
  	10,21,11,23,12,25,13,27,14,29,15,31,0,33,0,35,0,37,16,39,17,41,18,43,
  	19,45,0,47,0,49,20,51,21,53,22,55,23,57,24,59,25,61,26,63,27,65,28,67,
  	29,69,30,71,31,73,32,75,33,77,34,79,35,81,36,83,37,85,38,87,39,1,0,6,
  	2,0,115,115,117,117,3,0,65,90,95,95,97,122,8,0,40,41,46,46,48,58,65,91,
  	93,93,95,95,97,123,125,125,2,0,48,57,97,102,2,0,48,57,65,70,3,0,9,10,
  	13,13,32,32,304,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,
  	0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,
  	0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,
  	37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,49,1,0,0,0,0,51,1,
  	0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,
  	0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,
  	73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,1,
  	0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,1,89,1,0,0,0,3,102,1,0,0,0,5,104,1,0,
  	0,0,7,121,1,0,0,0,9,123,1,0,0,0,11,139,1,0,0,0,13,146,1,0,0,0,15,148,
  	1,0,0,0,17,150,1,0,0,0,19,166,1,0,0,0,21,168,1,0,0,0,23,170,1,0,0,0,25,
  	172,1,0,0,0,27,174,1,0,0,0,29,176,1,0,0,0,31,178,1,0,0,0,33,186,1,0,0,
  	0,35,189,1,0,0,0,37,192,1,0,0,0,39,207,1,0,0,0,41,214,1,0,0,0,43,238,
  	1,0,0,0,45,240,1,0,0,0,47,242,1,0,0,0,49,244,1,0,0,0,51,246,1,0,0,0,53,
  	248,1,0,0,0,55,250,1,0,0,0,57,252,1,0,0,0,59,254,1,0,0,0,61,257,1,0,0,
  	0,63,259,1,0,0,0,65,262,1,0,0,0,67,265,1,0,0,0,69,268,1,0,0,0,71,270,
  	1,0,0,0,73,272,1,0,0,0,75,274,1,0,0,0,77,276,1,0,0,0,79,279,1,0,0,0,81,
  	282,1,0,0,0,83,285,1,0,0,0,85,288,1,0,0,0,87,290,1,0,0,0,89,90,5,58,0,
  	0,90,2,1,0,0,0,91,92,5,64,0,0,92,93,5,116,0,0,93,94,5,114,0,0,94,95,5,
  	117,0,0,95,103,5,101,0,0,96,97,5,64,0,0,97,98,5,102,0,0,98,99,5,97,0,
  	0,99,100,5,108,0,0,100,101,5,115,0,0,101,103,5,101,0,0,102,91,1,0,0,0,
  	102,96,1,0,0,0,103,4,1,0,0,0,104,105,3,45,22,0,105,106,3,31,15,0,106,
  	107,5,44,0,0,107,108,5,98,0,0,108,109,5,111,0,0,109,110,5,111,0,0,110,
  	111,5,108,0,0,111,112,1,0,0,0,112,113,3,47,23,0,113,6,1,0,0,0,114,122,
  	3,39,19,0,115,122,3,41,20,0,116,118,3,37,18,0,117,119,3,13,6,0,118,117,
  	1,0,0,0,118,119,1,0,0,0,119,122,1,0,0,0,120,122,3,43,21,0,121,114,1,0,
  	0,0,121,115,1,0,0,0,121,116,1,0,0,0,121,120,1,0,0,0,122,8,1,0,0,0,123,
  	124,3,45,22,0,124,125,3,31,15,0,125,126,5,44,0,0,126,127,5,108,0,0,127,
  	128,5,111,0,0,128,129,5,103,0,0,129,130,5,105,0,0,130,131,5,99,0,0,131,
  	132,5,40,0,0,132,133,1,0,0,0,133,134,3,11,5,0,134,135,5,44,0,0,135,136,
  	3,37,18,0,136,137,5,41,0,0,137,138,3,47,23,0,138,10,1,0,0,0,139,140,7,
  	0,0,0,140,12,1,0,0,0,141,142,5,108,0,0,142,147,5,108,0,0,143,144,5,117,
  	0,0,144,145,5,108,0,0,145,147,5,108,0,0,146,141,1,0,0,0,146,143,1,0,0,
  	0,147,14,1,0,0,0,148,149,3,37,18,0,149,16,1,0,0,0,150,151,3,45,22,0,151,
  	152,3,31,15,0,152,153,5,44,0,0,153,154,5,110,0,0,154,155,5,117,0,0,155,
  	156,5,109,0,0,156,157,5,101,0,0,157,158,5,114,0,0,158,159,5,105,0,0,159,
  	160,5,99,0,0,160,161,5,40,0,0,161,162,1,0,0,0,162,163,3,37,18,0,163,164,
  	5,41,0,0,164,165,3,47,23,0,165,18,1,0,0,0,166,167,5,123,0,0,167,20,1,
  	0,0,0,168,169,5,125,0,0,169,22,1,0,0,0,170,171,5,91,0,0,171,24,1,0,0,
  	0,172,173,5,93,0,0,173,26,1,0,0,0,174,175,5,40,0,0,175,28,1,0,0,0,176,
  	177,5,41,0,0,177,30,1,0,0,0,178,182,3,33,16,0,179,181,3,35,17,0,180,179,
  	1,0,0,0,181,184,1,0,0,0,182,180,1,0,0,0,182,183,1,0,0,0,183,32,1,0,0,
  	0,184,182,1,0,0,0,185,187,7,1,0,0,186,185,1,0,0,0,187,34,1,0,0,0,188,
  	190,7,2,0,0,189,188,1,0,0,0,190,36,1,0,0,0,191,193,5,45,0,0,192,191,1,
  	0,0,0,192,193,1,0,0,0,193,195,1,0,0,0,194,196,2,48,57,0,195,194,1,0,0,
  	0,196,197,1,0,0,0,197,195,1,0,0,0,197,198,1,0,0,0,198,205,1,0,0,0,199,
  	201,5,46,0,0,200,202,2,48,57,0,201,200,1,0,0,0,202,203,1,0,0,0,203,201,
  	1,0,0,0,203,204,1,0,0,0,204,206,1,0,0,0,205,199,1,0,0,0,205,206,1,0,0,
  	0,206,38,1,0,0,0,207,208,5,39,0,0,208,210,5,98,0,0,209,211,2,48,49,0,
  	210,209,1,0,0,0,211,212,1,0,0,0,212,210,1,0,0,0,212,213,1,0,0,0,213,40,
  	1,0,0,0,214,215,5,48,0,0,215,216,5,98,0,0,216,218,1,0,0,0,217,219,2,48,
  	49,0,218,217,1,0,0,0,219,220,1,0,0,0,220,218,1,0,0,0,220,221,1,0,0,0,
  	221,42,1,0,0,0,222,223,5,48,0,0,223,224,5,120,0,0,224,226,1,0,0,0,225,
  	227,7,3,0,0,226,225,1,0,0,0,227,228,1,0,0,0,228,226,1,0,0,0,228,229,1,
  	0,0,0,229,239,1,0,0,0,230,231,5,48,0,0,231,232,5,120,0,0,232,234,1,0,
  	0,0,233,235,7,4,0,0,234,233,1,0,0,0,235,236,1,0,0,0,236,234,1,0,0,0,236,
  	237,1,0,0,0,237,239,1,0,0,0,238,222,1,0,0,0,238,230,1,0,0,0,239,44,1,
  	0,0,0,240,241,5,171,0,0,241,46,1,0,0,0,242,243,5,187,0,0,243,48,1,0,0,
  	0,244,245,5,43,0,0,245,50,1,0,0,0,246,247,5,45,0,0,247,52,1,0,0,0,248,
  	249,5,42,0,0,249,54,1,0,0,0,250,251,5,47,0,0,251,56,1,0,0,0,252,253,5,
  	62,0,0,253,58,1,0,0,0,254,255,5,62,0,0,255,256,5,61,0,0,256,60,1,0,0,
  	0,257,258,5,60,0,0,258,62,1,0,0,0,259,260,5,60,0,0,260,261,5,61,0,0,261,
  	64,1,0,0,0,262,263,5,61,0,0,263,264,5,61,0,0,264,66,1,0,0,0,265,266,5,
  	33,0,0,266,267,5,61,0,0,267,68,1,0,0,0,268,269,5,38,0,0,269,70,1,0,0,
  	0,270,271,5,124,0,0,271,72,1,0,0,0,272,273,5,94,0,0,273,74,1,0,0,0,274,
  	275,5,126,0,0,275,76,1,0,0,0,276,277,5,60,0,0,277,278,5,60,0,0,278,78,
  	1,0,0,0,279,280,5,62,0,0,280,281,5,62,0,0,281,80,1,0,0,0,282,283,5,38,
  	0,0,283,284,5,38,0,0,284,82,1,0,0,0,285,286,5,124,0,0,286,287,5,124,0,
  	0,287,84,1,0,0,0,288,289,5,33,0,0,289,86,1,0,0,0,290,291,7,5,0,0,291,
  	292,1,0,0,0,292,293,6,43,0,0,293,88,1,0,0,0,19,0,102,118,121,146,182,
  	186,189,192,197,203,205,212,220,226,228,234,236,238,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  propositionlexerLexerStaticData = staticData.release();
}

}

propositionLexer::propositionLexer(CharStream *input) : Lexer(input) {
  propositionLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *propositionlexerLexerStaticData->atn, propositionlexerLexerStaticData->decisionToDFA, propositionlexerLexerStaticData->sharedContextCache);
}

propositionLexer::~propositionLexer() {
  delete _interpreter;
}

std::string propositionLexer::getGrammarFileName() const {
  return "proposition.g4";
}

const std::vector<std::string>& propositionLexer::getRuleNames() const {
  return propositionlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& propositionLexer::getChannelNames() const {
  return propositionlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& propositionLexer::getModeNames() const {
  return propositionlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& propositionLexer::getVocabulary() const {
  return propositionlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView propositionLexer::getSerializedATN() const {
  return propositionlexerLexerStaticData->serializedATN;
}

const atn::ATN& propositionLexer::getATN() const {
  return *propositionlexerLexerStaticData->atn;
}




void propositionLexer::initialize() {
  ::antlr4::internal::call_once(propositionlexerLexerOnceFlag, propositionlexerLexerInitialize);
}
