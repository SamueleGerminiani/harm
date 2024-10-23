
// Generated from varDeclaration.g4 by ANTLR 4.10.1


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

std::once_flag vardeclarationParserOnceFlag;
VarDeclarationParserStaticData *vardeclarationParserStaticData = nullptr;

void vardeclarationParserInitialize() {
  assert(vardeclarationParserStaticData == nullptr);
  auto staticData = std::make_unique<VarDeclarationParserStaticData>(
    std::vector<std::string>{
      "file", "varDec", "startBoolean", "startInt", "startLogic", "startFloat", 
      "startString", "boolean", "booleanAtom", "numeric", "range", "sm_range", 
      "min_dollar", "max_dollar", "sm_constant", "intAtom", "int_constant", 
      "logicAtom", "logic_constant", "floatAtom", "string", "stringAtom", 
      "nonTemporalFunction", "pfunc_arg", "relop", "cls_op"
    },
    std::vector<std::string>{
      "", "','", "", "", "", "", "", "", "", "", "", "", "'.substr'", "", 
      "", "'{'", "'}'", "'['", "']'", "'('", "')'", "'inside'", "", "", 
      "", "", "", "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", 
      "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", "'|'", "'^'", "'~'", 
      "'<<'", "'>>'", "'&&'", "'||'", "'!'", "':'", "'::'", "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "Name", "VARTYPE", "WS", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", 
      "INT_VARIABLE", "CONST_SUFFIX", "LOGIC_VARIABLE", "FLOAT_CONSTANT", 
      "FLOAT_VARIABLE", "SUBSTR", "STRING_CONSTANT", "STRING_VARIABLE", 
      "LCURLY", "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "INSIDE", 
      "FUNCTION", "SINTEGER", "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", 
      "VERILOG_BINARY", "FVL", "SINGLE_QUOTE", "PLUS", "MINUS", "TIMES", 
      "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "BAND", "BOR", "BXOR", 
      "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT", "COL", "DCOL", "DOLLAR", 
      "RANGE", "CLS_TYPE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,54,295,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,1,0,1,0,1,0,1,1,1,1,3,1,58,
  	8,1,1,1,1,1,1,2,1,2,1,2,1,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,6,1,6,1,
  	6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,86,8,7,1,7,1,7,5,7,90,8,7,10,
  	7,12,7,93,9,7,1,7,1,7,3,7,97,8,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,3,7,131,8,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,5,7,145,8,7,10,7,12,7,148,9,7,1,8,1,8,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,3,9,163,8,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,5,9,188,8,9,
  	10,9,12,9,191,9,9,1,10,1,10,1,10,1,10,3,10,197,8,10,1,10,1,10,1,11,1,
  	11,1,11,3,11,204,8,11,1,11,1,11,1,11,3,11,209,8,11,1,11,1,11,1,12,1,12,
  	1,13,1,13,1,14,1,14,1,15,1,15,3,15,221,8,15,1,16,1,16,1,16,3,16,226,8,
  	16,1,16,1,16,3,16,230,8,16,1,16,3,16,233,8,16,1,17,1,17,1,17,3,17,238,
  	8,17,1,18,3,18,241,8,18,1,18,1,18,1,19,1,19,1,20,1,20,1,20,1,20,1,20,
  	1,20,3,20,253,8,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	3,20,265,8,20,1,20,5,20,268,8,20,10,20,12,20,271,9,20,1,21,1,21,1,22,
  	1,22,1,22,1,22,1,22,5,22,280,8,22,10,22,12,22,283,9,22,1,22,1,22,1,23,
  	1,23,3,23,289,8,23,1,24,1,24,1,25,1,25,1,25,0,3,14,18,40,26,0,2,4,6,8,
  	10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,0,8,1,
  	0,5,6,1,0,33,34,1,0,31,32,1,0,23,24,1,0,10,11,1,0,13,14,1,0,35,38,2,0,
  	35,39,53,53,319,0,52,1,0,0,0,2,55,1,0,0,0,4,61,1,0,0,0,6,64,1,0,0,0,8,
  	67,1,0,0,0,10,70,1,0,0,0,12,73,1,0,0,0,14,130,1,0,0,0,16,149,1,0,0,0,
  	18,162,1,0,0,0,20,192,1,0,0,0,22,200,1,0,0,0,24,212,1,0,0,0,26,214,1,
  	0,0,0,28,216,1,0,0,0,30,220,1,0,0,0,32,232,1,0,0,0,34,237,1,0,0,0,36,
  	240,1,0,0,0,38,244,1,0,0,0,40,252,1,0,0,0,42,272,1,0,0,0,44,274,1,0,0,
  	0,46,288,1,0,0,0,48,290,1,0,0,0,50,292,1,0,0,0,52,53,3,2,1,0,53,54,5,
  	0,0,1,54,1,1,0,0,0,55,57,5,3,0,0,56,58,3,20,10,0,57,56,1,0,0,0,57,58,
  	1,0,0,0,58,59,1,0,0,0,59,60,5,2,0,0,60,3,1,0,0,0,61,62,3,14,7,0,62,63,
  	5,0,0,1,63,5,1,0,0,0,64,65,3,18,9,0,65,66,5,0,0,1,66,7,1,0,0,0,67,68,
  	3,18,9,0,68,69,5,0,0,1,69,9,1,0,0,0,70,71,3,18,9,0,71,72,5,0,0,1,72,11,
  	1,0,0,0,73,74,3,40,20,0,74,75,5,0,0,1,75,13,1,0,0,0,76,77,6,7,-1,0,77,
  	78,5,49,0,0,78,131,3,14,7,16,79,131,3,44,22,0,80,81,3,18,9,0,81,82,5,
  	21,0,0,82,91,5,15,0,0,83,86,3,28,14,0,84,86,3,22,11,0,85,83,1,0,0,0,85,
  	84,1,0,0,0,86,87,1,0,0,0,87,88,5,1,0,0,88,90,1,0,0,0,89,85,1,0,0,0,90,
  	93,1,0,0,0,91,89,1,0,0,0,91,92,1,0,0,0,92,96,1,0,0,0,93,91,1,0,0,0,94,
  	97,3,28,14,0,95,97,3,22,11,0,96,94,1,0,0,0,96,95,1,0,0,0,97,98,1,0,0,
  	0,98,99,5,16,0,0,99,131,1,0,0,0,100,101,3,18,9,0,101,102,3,48,24,0,102,
  	103,3,18,9,0,103,131,1,0,0,0,104,105,3,18,9,0,105,106,5,39,0,0,106,107,
  	3,18,9,0,107,131,1,0,0,0,108,109,3,18,9,0,109,110,5,40,0,0,110,111,3,
  	18,9,0,111,131,1,0,0,0,112,113,3,40,20,0,113,114,3,48,24,0,114,115,3,
  	40,20,0,115,131,1,0,0,0,116,117,3,40,20,0,117,118,5,39,0,0,118,119,3,
  	40,20,0,119,131,1,0,0,0,120,121,3,40,20,0,121,122,5,40,0,0,122,123,3,
  	40,20,0,123,131,1,0,0,0,124,131,3,16,8,0,125,131,3,18,9,0,126,127,5,19,
  	0,0,127,128,3,14,7,0,128,129,5,20,0,0,129,131,1,0,0,0,130,76,1,0,0,0,
  	130,79,1,0,0,0,130,80,1,0,0,0,130,100,1,0,0,0,130,104,1,0,0,0,130,108,
  	1,0,0,0,130,112,1,0,0,0,130,116,1,0,0,0,130,120,1,0,0,0,130,124,1,0,0,
  	0,130,125,1,0,0,0,130,126,1,0,0,0,131,146,1,0,0,0,132,133,10,7,0,0,133,
  	134,5,39,0,0,134,145,3,14,7,8,135,136,10,6,0,0,136,137,5,40,0,0,137,145,
  	3,14,7,7,138,139,10,5,0,0,139,140,5,47,0,0,140,145,3,14,7,6,141,142,10,
  	4,0,0,142,143,5,48,0,0,143,145,3,14,7,5,144,132,1,0,0,0,144,135,1,0,0,
  	0,144,138,1,0,0,0,144,141,1,0,0,0,145,148,1,0,0,0,146,144,1,0,0,0,146,
  	147,1,0,0,0,147,15,1,0,0,0,148,146,1,0,0,0,149,150,7,0,0,0,150,17,1,0,
  	0,0,151,152,6,9,-1,0,152,153,5,44,0,0,153,163,3,18,9,14,154,163,3,44,
  	22,0,155,163,3,30,15,0,156,163,3,34,17,0,157,163,3,38,19,0,158,159,5,
  	19,0,0,159,160,3,18,9,0,160,161,5,20,0,0,161,163,1,0,0,0,162,151,1,0,
  	0,0,162,154,1,0,0,0,162,155,1,0,0,0,162,156,1,0,0,0,162,157,1,0,0,0,162,
  	158,1,0,0,0,163,189,1,0,0,0,164,165,10,11,0,0,165,166,7,1,0,0,166,188,
  	3,18,9,12,167,168,10,10,0,0,168,169,7,2,0,0,169,188,3,18,9,11,170,171,
  	10,9,0,0,171,172,5,45,0,0,172,188,3,18,9,10,173,174,10,8,0,0,174,175,
  	5,46,0,0,175,188,3,18,9,9,176,177,10,7,0,0,177,178,5,41,0,0,178,188,3,
  	18,9,8,179,180,10,6,0,0,180,181,5,43,0,0,181,188,3,18,9,7,182,183,10,
  	5,0,0,183,184,5,42,0,0,184,188,3,18,9,6,185,186,10,12,0,0,186,188,3,20,
  	10,0,187,164,1,0,0,0,187,167,1,0,0,0,187,170,1,0,0,0,187,173,1,0,0,0,
  	187,176,1,0,0,0,187,179,1,0,0,0,187,182,1,0,0,0,187,185,1,0,0,0,188,191,
  	1,0,0,0,189,187,1,0,0,0,189,190,1,0,0,0,190,19,1,0,0,0,191,189,1,0,0,
  	0,192,193,5,17,0,0,193,196,7,3,0,0,194,195,5,50,0,0,195,197,7,3,0,0,196,
  	194,1,0,0,0,196,197,1,0,0,0,197,198,1,0,0,0,198,199,5,18,0,0,199,21,1,
  	0,0,0,200,203,5,17,0,0,201,204,3,18,9,0,202,204,3,24,12,0,203,201,1,0,
  	0,0,203,202,1,0,0,0,204,205,1,0,0,0,205,208,5,50,0,0,206,209,3,18,9,0,
  	207,209,3,26,13,0,208,206,1,0,0,0,208,207,1,0,0,0,209,210,1,0,0,0,210,
  	211,5,18,0,0,211,23,1,0,0,0,212,213,5,52,0,0,213,25,1,0,0,0,214,215,5,
  	52,0,0,215,27,1,0,0,0,216,217,3,18,9,0,217,29,1,0,0,0,218,221,3,32,16,
  	0,219,221,5,7,0,0,220,218,1,0,0,0,220,219,1,0,0,0,221,31,1,0,0,0,222,
  	233,5,26,0,0,223,225,5,23,0,0,224,226,5,8,0,0,225,224,1,0,0,0,225,226,
  	1,0,0,0,226,233,1,0,0,0,227,229,5,24,0,0,228,230,5,8,0,0,229,228,1,0,
  	0,0,229,230,1,0,0,0,230,233,1,0,0,0,231,233,5,27,0,0,232,222,1,0,0,0,
  	232,223,1,0,0,0,232,227,1,0,0,0,232,231,1,0,0,0,233,33,1,0,0,0,234,238,
  	3,36,18,0,235,238,3,32,16,0,236,238,5,9,0,0,237,234,1,0,0,0,237,235,1,
  	0,0,0,237,236,1,0,0,0,238,35,1,0,0,0,239,241,5,24,0,0,240,239,1,0,0,0,
  	240,241,1,0,0,0,241,242,1,0,0,0,242,243,5,28,0,0,243,37,1,0,0,0,244,245,
  	7,4,0,0,245,39,1,0,0,0,246,247,6,20,-1,0,247,253,3,42,21,0,248,249,5,
  	19,0,0,249,250,3,40,20,0,250,251,5,20,0,0,251,253,1,0,0,0,252,246,1,0,
  	0,0,252,248,1,0,0,0,253,269,1,0,0,0,254,255,10,4,0,0,255,256,5,31,0,0,
  	256,268,3,40,20,5,257,258,10,3,0,0,258,259,5,12,0,0,259,264,5,19,0,0,
  	260,261,5,24,0,0,261,262,5,1,0,0,262,265,5,24,0,0,263,265,5,24,0,0,264,
  	260,1,0,0,0,264,263,1,0,0,0,264,265,1,0,0,0,265,266,1,0,0,0,266,268,5,
  	20,0,0,267,254,1,0,0,0,267,257,1,0,0,0,268,271,1,0,0,0,269,267,1,0,0,
  	0,269,270,1,0,0,0,270,41,1,0,0,0,271,269,1,0,0,0,272,273,7,5,0,0,273,
  	43,1,0,0,0,274,275,5,22,0,0,275,276,5,19,0,0,276,281,3,46,23,0,277,278,
  	5,1,0,0,278,280,3,46,23,0,279,277,1,0,0,0,280,283,1,0,0,0,281,279,1,0,
  	0,0,281,282,1,0,0,0,282,284,1,0,0,0,283,281,1,0,0,0,284,285,5,20,0,0,
  	285,45,1,0,0,0,286,289,3,18,9,0,287,289,3,14,7,0,288,286,1,0,0,0,288,
  	287,1,0,0,0,289,47,1,0,0,0,290,291,7,6,0,0,291,49,1,0,0,0,292,293,7,7,
  	0,0,293,51,1,0,0,0,25,57,85,91,96,130,144,146,162,187,189,196,203,208,
  	220,225,229,232,237,240,252,264,267,269,281,288
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  vardeclarationParserStaticData = staticData.release();
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
    setState(52);
    varDec();
    setState(53);
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
    setState(55);
    match(varDeclarationParser::VARTYPE);
    setState(57);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::LSQUARED) {
      setState(56);
      range();
    }
    setState(59);
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

varDeclarationParser::BooleanContext* varDeclarationParser::StartBooleanContext::boolean() {
  return getRuleContext<varDeclarationParser::BooleanContext>(0);
}

tree::TerminalNode* varDeclarationParser::StartBooleanContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
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
    setState(61);
    boolean(0);
    setState(62);
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

varDeclarationParser::NumericContext* varDeclarationParser::StartIntContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}

tree::TerminalNode* varDeclarationParser::StartIntContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
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
    setState(64);
    numeric(0);
    setState(65);
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

varDeclarationParser::NumericContext* varDeclarationParser::StartLogicContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}

tree::TerminalNode* varDeclarationParser::StartLogicContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
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
    setState(67);
    numeric(0);
    setState(68);
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

varDeclarationParser::NumericContext* varDeclarationParser::StartFloatContext::numeric() {
  return getRuleContext<varDeclarationParser::NumericContext>(0);
}

tree::TerminalNode* varDeclarationParser::StartFloatContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
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
    setState(70);
    numeric(0);
    setState(71);
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
    setState(73);
    string(0);
    setState(74);
    match(varDeclarationParser::EOF);
   
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
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, varDeclarationParser::RuleBoolean, precedence);

    

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
    setState(130);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(77);
      match(varDeclarationParser::NOT);
      setState(78);
      boolean(16);
      break;
    }

    case 2: {
      setState(79);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(80);
      numeric(0);
      setState(81);
      match(varDeclarationParser::INSIDE);
      setState(82);
      match(varDeclarationParser::LCURLY);
      setState(91);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(85);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case varDeclarationParser::INT_VARIABLE:
            case varDeclarationParser::LOGIC_VARIABLE:
            case varDeclarationParser::FLOAT_CONSTANT:
            case varDeclarationParser::FLOAT_VARIABLE:
            case varDeclarationParser::LROUND:
            case varDeclarationParser::FUNCTION:
            case varDeclarationParser::SINTEGER:
            case varDeclarationParser::UINTEGER:
            case varDeclarationParser::GCC_BINARY:
            case varDeclarationParser::HEX:
            case varDeclarationParser::VERILOG_BINARY:
            case varDeclarationParser::NEG: {
              setState(83);
              sm_constant();
              break;
            }

            case varDeclarationParser::LSQUARED: {
              setState(84);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(87);
          match(varDeclarationParser::T__0); 
        }
        setState(93);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
      }
      setState(96);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case varDeclarationParser::INT_VARIABLE:
        case varDeclarationParser::LOGIC_VARIABLE:
        case varDeclarationParser::FLOAT_CONSTANT:
        case varDeclarationParser::FLOAT_VARIABLE:
        case varDeclarationParser::LROUND:
        case varDeclarationParser::FUNCTION:
        case varDeclarationParser::SINTEGER:
        case varDeclarationParser::UINTEGER:
        case varDeclarationParser::GCC_BINARY:
        case varDeclarationParser::HEX:
        case varDeclarationParser::VERILOG_BINARY:
        case varDeclarationParser::NEG: {
          setState(94);
          sm_constant();
          break;
        }

        case varDeclarationParser::LSQUARED: {
          setState(95);
          sm_range();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(98);
      match(varDeclarationParser::RCURLY);
      break;
    }

    case 4: {
      setState(100);
      numeric(0);
      setState(101);
      relop();
      setState(102);
      numeric(0);
      break;
    }

    case 5: {
      setState(104);
      numeric(0);
      setState(105);
      match(varDeclarationParser::EQ);
      setState(106);
      numeric(0);
      break;
    }

    case 6: {
      setState(108);
      numeric(0);
      setState(109);
      match(varDeclarationParser::NEQ);
      setState(110);
      numeric(0);
      break;
    }

    case 7: {
      setState(112);
      string(0);
      setState(113);
      relop();
      setState(114);
      string(0);
      break;
    }

    case 8: {
      setState(116);
      string(0);
      setState(117);
      match(varDeclarationParser::EQ);
      setState(118);
      string(0);
      break;
    }

    case 9: {
      setState(120);
      string(0);
      setState(121);
      match(varDeclarationParser::NEQ);
      setState(122);
      string(0);
      break;
    }

    case 10: {
      setState(124);
      booleanAtom();
      break;
    }

    case 11: {
      setState(125);
      numeric(0);
      break;
    }

    case 12: {
      setState(126);
      match(varDeclarationParser::LROUND);
      setState(127);
      boolean(0);
      setState(128);
      match(varDeclarationParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(146);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(144);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(132);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(133);
          match(varDeclarationParser::EQ);
          setState(134);
          boolean(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(135);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(136);
          match(varDeclarationParser::NEQ);
          setState(137);
          boolean(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(138);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(139);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(varDeclarationParser::AND);
          setState(140);
          boolean(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(141);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(142);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(varDeclarationParser::OR);
          setState(143);
          boolean(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(148);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
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
  enterRule(_localctx, 16, varDeclarationParser::RuleBooleanAtom);
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
    setState(149);
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

tree::TerminalNode* varDeclarationParser::NumericContext::LROUND() {
  return getToken(varDeclarationParser::LROUND, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::RROUND() {
  return getToken(varDeclarationParser::RROUND, 0);
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
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, varDeclarationParser::RuleNumeric, precedence);

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
    setState(162);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(152);
      match(varDeclarationParser::NEG);
      setState(153);
      numeric(14);
      break;
    }

    case 2: {
      setState(154);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(155);
      intAtom();
      break;
    }

    case 4: {
      setState(156);
      logicAtom();
      break;
    }

    case 5: {
      setState(157);
      floatAtom();
      break;
    }

    case 6: {
      setState(158);
      match(varDeclarationParser::LROUND);
      setState(159);
      numeric(0);
      setState(160);
      match(varDeclarationParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(189);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(187);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(164);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(165);
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
          setState(166);
          numeric(12);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(167);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(168);
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
          setState(169);
          numeric(11);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(170);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(171);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::LSHIFT);
          setState(172);
          numeric(10);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(173);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(174);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::RSHIFT);
          setState(175);
          numeric(9);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(176);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(177);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BAND);
          setState(178);
          numeric(8);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(179);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(180);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BXOR);
          setState(181);
          numeric(7);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(182);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(183);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(varDeclarationParser::BOR);
          setState(184);
          numeric(6);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(185);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(186);
          range();
          break;
        }

        default:
          break;
        } 
      }
      setState(191);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
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
  enterRule(_localctx, 20, varDeclarationParser::RuleRange);
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
    setState(192);
    match(varDeclarationParser::LSQUARED);
    setState(193);
    _la = _input->LA(1);
    if (!(_la == varDeclarationParser::SINTEGER

    || _la == varDeclarationParser::UINTEGER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(196);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::COL) {
      setState(194);
      match(varDeclarationParser::COL);
      setState(195);
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
    setState(198);
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
  enterRule(_localctx, 22, varDeclarationParser::RuleSm_range);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(200);
    match(varDeclarationParser::LSQUARED);
    setState(203);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::FUNCTION:
      case varDeclarationParser::SINTEGER:
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX:
      case varDeclarationParser::VERILOG_BINARY:
      case varDeclarationParser::NEG: {
        setState(201);
        numeric(0);
        break;
      }

      case varDeclarationParser::DOLLAR: {
        setState(202);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(205);
    match(varDeclarationParser::COL);
    setState(208);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::INT_VARIABLE:
      case varDeclarationParser::LOGIC_VARIABLE:
      case varDeclarationParser::FLOAT_CONSTANT:
      case varDeclarationParser::FLOAT_VARIABLE:
      case varDeclarationParser::LROUND:
      case varDeclarationParser::FUNCTION:
      case varDeclarationParser::SINTEGER:
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX:
      case varDeclarationParser::VERILOG_BINARY:
      case varDeclarationParser::NEG: {
        setState(206);
        numeric(0);
        break;
      }

      case varDeclarationParser::DOLLAR: {
        setState(207);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(210);
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
  enterRule(_localctx, 24, varDeclarationParser::RuleMin_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
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
  enterRule(_localctx, 26, varDeclarationParser::RuleMax_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
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
  enterRule(_localctx, 28, varDeclarationParser::RuleSm_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(216);
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
  enterRule(_localctx, 30, varDeclarationParser::RuleIntAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(220);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::SINTEGER:
      case varDeclarationParser::UINTEGER:
      case varDeclarationParser::GCC_BINARY:
      case varDeclarationParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(218);
        int_constant();
        break;
      }

      case varDeclarationParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(219);
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
  enterRule(_localctx, 32, varDeclarationParser::RuleInt_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(232);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(222);
        match(varDeclarationParser::GCC_BINARY);
        break;
      }

      case varDeclarationParser::SINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(223);
        match(varDeclarationParser::SINTEGER);
        setState(225);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
        case 1: {
          setState(224);
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
        setState(227);
        match(varDeclarationParser::UINTEGER);
        setState(229);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
        case 1: {
          setState(228);
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
        setState(231);
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
  enterRule(_localctx, 34, varDeclarationParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(237);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(234);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(235);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(236);
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

tree::TerminalNode* varDeclarationParser::Logic_constantContext::VERILOG_BINARY() {
  return getToken(varDeclarationParser::VERILOG_BINARY, 0);
}

tree::TerminalNode* varDeclarationParser::Logic_constantContext::UINTEGER() {
  return getToken(varDeclarationParser::UINTEGER, 0);
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
  enterRule(_localctx, 36, varDeclarationParser::RuleLogic_constant);
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
    setState(240);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::UINTEGER) {
      setState(239);
      match(varDeclarationParser::UINTEGER);
    }
    setState(242);
    match(varDeclarationParser::VERILOG_BINARY);
   
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
  enterRule(_localctx, 38, varDeclarationParser::RuleFloatAtom);
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
    setState(244);
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
  size_t startState = 40;
  enterRecursionRule(_localctx, 40, varDeclarationParser::RuleString, precedence);

    

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
    setState(252);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::STRING_CONSTANT:
      case varDeclarationParser::STRING_VARIABLE: {
        setState(247);
        stringAtom();
        break;
      }

      case varDeclarationParser::LROUND: {
        setState(248);
        match(varDeclarationParser::LROUND);
        setState(249);
        string(0);
        setState(250);
        match(varDeclarationParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(269);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(267);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(254);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(255);
          match(varDeclarationParser::PLUS);
          setState(256);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(257);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(258);
          match(varDeclarationParser::SUBSTR);
          setState(259);
          match(varDeclarationParser::LROUND);
          setState(264);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
          case 1: {
            setState(260);
            match(varDeclarationParser::UINTEGER);
            setState(261);
            match(varDeclarationParser::T__0);
            setState(262);
            match(varDeclarationParser::UINTEGER);
            break;
          }

          case 2: {
            setState(263);
            match(varDeclarationParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(266);
          match(varDeclarationParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(271);
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
  enterRule(_localctx, 42, varDeclarationParser::RuleStringAtom);
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
    setState(272);
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
  enterRule(_localctx, 44, varDeclarationParser::RuleNonTemporalFunction);
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
    setState(274);
    match(varDeclarationParser::FUNCTION);
    setState(275);
    match(varDeclarationParser::LROUND);
    setState(276);
    pfunc_arg();
    setState(281);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == varDeclarationParser::T__0) {
      setState(277);
      match(varDeclarationParser::T__0);
      setState(278);
      pfunc_arg();
      setState(283);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(284);
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
  enterRule(_localctx, 46, varDeclarationParser::RulePfunc_arg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(288);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(286);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(287);
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
  enterRule(_localctx, 48, varDeclarationParser::RuleRelop);
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
    setState(290);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << varDeclarationParser::GT)
      | (1ULL << varDeclarationParser::GE)
      | (1ULL << varDeclarationParser::LT)
      | (1ULL << varDeclarationParser::LE))) != 0))) {
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
  enterRule(_localctx, 50, varDeclarationParser::RuleCls_op);
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
    setState(292);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << varDeclarationParser::GT)
      | (1ULL << varDeclarationParser::GE)
      | (1ULL << varDeclarationParser::LT)
      | (1ULL << varDeclarationParser::LE)
      | (1ULL << varDeclarationParser::EQ)
      | (1ULL << varDeclarationParser::RANGE))) != 0))) {
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
    case 7: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 9: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);
    case 20: return stringSempred(antlrcpp::downCast<StringContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool varDeclarationParser::booleanSempred(BooleanContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 7);
    case 1: return precpred(_ctx, 6);
    case 2: return precpred(_ctx, 5);
    case 3: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

bool varDeclarationParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 11);
    case 5: return precpred(_ctx, 10);
    case 6: return precpred(_ctx, 9);
    case 7: return precpred(_ctx, 8);
    case 8: return precpred(_ctx, 7);
    case 9: return precpred(_ctx, 6);
    case 10: return precpred(_ctx, 5);
    case 11: return precpred(_ctx, 12);

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
  std::call_once(vardeclarationParserOnceFlag, vardeclarationParserInitialize);
}
