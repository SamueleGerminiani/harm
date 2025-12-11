
// Generated from proposition.g4 by ANTLR 4.10.1


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

std::once_flag propositionParserOnceFlag;
PropositionParserStaticData *propositionParserStaticData = nullptr;

void propositionParserInitialize() {
  assert(propositionParserStaticData == nullptr);
  auto staticData = std::make_unique<PropositionParserStaticData>(
    std::vector<std::string>{
      "startBoolean", "startInt", "startLogic", "startFloat", "startString", 
      "boolean", "booleanAtom", "numeric", "range", "sm_range", "min_dollar", 
      "max_dollar", "sm_constant", "intAtom", "int_constant", "logicAtom", 
      "logic_constant", "floatAtom", "string", "stringAtom", "nonTemporalFunction", 
      "pfunc_arg", "relop", "cls_op"
    },
    std::vector<std::string>{
      "", "','", "", "", "", "", "", "", "", "'.substr'", "", "", "'{'", 
      "'}'", "'['", "']'", "'('", "')'", "'inside'", "", "", "", "", "", 
      "", "", "", "'''", "'+'", "'-'", "'*'", "'/'", "'>'", "'>='", "'<'", 
      "'<='", "'=='", "'!='", "'&'", "'|'", "'^'", "'~'", "'<<'", "'>>'", 
      "'&&'", "'||'", "'!'", "':'", "'::'", "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", "INT_VARIABLE", "CONST_SUFFIX", 
      "LOGIC_VARIABLE", "FLOAT_CONSTANT", "FLOAT_VARIABLE", "SUBSTR", "STRING_CONSTANT", 
      "STRING_VARIABLE", "LCURLY", "RCURLY", "LSQUARED", "RSQUARED", "LROUND", 
      "RROUND", "INSIDE", "FUNCTION", "SINTEGER", "UINTEGER", "FLOAT", "GCC_BINARY", 
      "HEX", "VERILOG_BINARY", "FVL", "SINGLE_QUOTE", "PLUS", "MINUS", "TIMES", 
      "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "BAND", "BOR", "BXOR", 
      "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT", "COL", "DCOL", "DOLLAR", 
      "RANGE", "CLS_TYPE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,52,282,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,1,0,1,0,1,0,1,1,1,1,1,1,1,2,1,2,1,2,1,3,1,3,1,
  	3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,73,8,5,1,5,1,5,
  	5,5,77,8,5,10,5,12,5,80,9,5,1,5,1,5,3,5,84,8,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,118,8,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,132,8,5,10,5,12,5,135,9,5,1,6,1,6,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,150,8,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,5,7,175,8,7,10,7,12,7,178,9,7,1,8,1,8,1,8,1,8,3,8,184,8,8,1,8,1,8,1,
  	9,1,9,1,9,3,9,191,8,9,1,9,1,9,1,9,3,9,196,8,9,1,9,1,9,1,10,1,10,1,11,
  	1,11,1,12,1,12,1,13,1,13,3,13,208,8,13,1,14,1,14,1,14,3,14,213,8,14,1,
  	14,1,14,3,14,217,8,14,1,14,3,14,220,8,14,1,15,1,15,1,15,3,15,225,8,15,
  	1,16,3,16,228,8,16,1,16,1,16,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,
  	3,18,240,8,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,
  	252,8,18,1,18,5,18,255,8,18,10,18,12,18,258,9,18,1,19,1,19,1,20,1,20,
  	1,20,1,20,1,20,5,20,267,8,20,10,20,12,20,270,9,20,1,20,1,20,1,21,1,21,
  	3,21,276,8,21,1,22,1,22,1,23,1,23,1,23,0,3,10,14,36,24,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,0,8,1,0,2,3,1,0,30,
  	31,1,0,28,29,1,0,20,21,1,0,7,8,1,0,10,11,1,0,32,35,2,0,32,36,50,50,307,
  	0,48,1,0,0,0,2,51,1,0,0,0,4,54,1,0,0,0,6,57,1,0,0,0,8,60,1,0,0,0,10,117,
  	1,0,0,0,12,136,1,0,0,0,14,149,1,0,0,0,16,179,1,0,0,0,18,187,1,0,0,0,20,
  	199,1,0,0,0,22,201,1,0,0,0,24,203,1,0,0,0,26,207,1,0,0,0,28,219,1,0,0,
  	0,30,224,1,0,0,0,32,227,1,0,0,0,34,231,1,0,0,0,36,239,1,0,0,0,38,259,
  	1,0,0,0,40,261,1,0,0,0,42,275,1,0,0,0,44,277,1,0,0,0,46,279,1,0,0,0,48,
  	49,3,10,5,0,49,50,5,0,0,1,50,1,1,0,0,0,51,52,3,14,7,0,52,53,5,0,0,1,53,
  	3,1,0,0,0,54,55,3,14,7,0,55,56,5,0,0,1,56,5,1,0,0,0,57,58,3,14,7,0,58,
  	59,5,0,0,1,59,7,1,0,0,0,60,61,3,36,18,0,61,62,5,0,0,1,62,9,1,0,0,0,63,
  	64,6,5,-1,0,64,65,5,46,0,0,65,118,3,10,5,16,66,118,3,40,20,0,67,68,3,
  	14,7,0,68,69,5,18,0,0,69,78,5,12,0,0,70,73,3,24,12,0,71,73,3,18,9,0,72,
  	70,1,0,0,0,72,71,1,0,0,0,73,74,1,0,0,0,74,75,5,1,0,0,75,77,1,0,0,0,76,
  	72,1,0,0,0,77,80,1,0,0,0,78,76,1,0,0,0,78,79,1,0,0,0,79,83,1,0,0,0,80,
  	78,1,0,0,0,81,84,3,24,12,0,82,84,3,18,9,0,83,81,1,0,0,0,83,82,1,0,0,0,
  	84,85,1,0,0,0,85,86,5,13,0,0,86,118,1,0,0,0,87,88,3,14,7,0,88,89,3,44,
  	22,0,89,90,3,14,7,0,90,118,1,0,0,0,91,92,3,14,7,0,92,93,5,36,0,0,93,94,
  	3,14,7,0,94,118,1,0,0,0,95,96,3,14,7,0,96,97,5,37,0,0,97,98,3,14,7,0,
  	98,118,1,0,0,0,99,100,3,36,18,0,100,101,3,44,22,0,101,102,3,36,18,0,102,
  	118,1,0,0,0,103,104,3,36,18,0,104,105,5,36,0,0,105,106,3,36,18,0,106,
  	118,1,0,0,0,107,108,3,36,18,0,108,109,5,37,0,0,109,110,3,36,18,0,110,
  	118,1,0,0,0,111,118,3,12,6,0,112,118,3,14,7,0,113,114,5,16,0,0,114,115,
  	3,10,5,0,115,116,5,17,0,0,116,118,1,0,0,0,117,63,1,0,0,0,117,66,1,0,0,
  	0,117,67,1,0,0,0,117,87,1,0,0,0,117,91,1,0,0,0,117,95,1,0,0,0,117,99,
  	1,0,0,0,117,103,1,0,0,0,117,107,1,0,0,0,117,111,1,0,0,0,117,112,1,0,0,
  	0,117,113,1,0,0,0,118,133,1,0,0,0,119,120,10,7,0,0,120,121,5,36,0,0,121,
  	132,3,10,5,8,122,123,10,6,0,0,123,124,5,37,0,0,124,132,3,10,5,7,125,126,
  	10,5,0,0,126,127,5,44,0,0,127,132,3,10,5,6,128,129,10,4,0,0,129,130,5,
  	45,0,0,130,132,3,10,5,5,131,119,1,0,0,0,131,122,1,0,0,0,131,125,1,0,0,
  	0,131,128,1,0,0,0,132,135,1,0,0,0,133,131,1,0,0,0,133,134,1,0,0,0,134,
  	11,1,0,0,0,135,133,1,0,0,0,136,137,7,0,0,0,137,13,1,0,0,0,138,139,6,7,
  	-1,0,139,140,5,41,0,0,140,150,3,14,7,14,141,150,3,40,20,0,142,150,3,26,
  	13,0,143,150,3,30,15,0,144,150,3,34,17,0,145,146,5,16,0,0,146,147,3,14,
  	7,0,147,148,5,17,0,0,148,150,1,0,0,0,149,138,1,0,0,0,149,141,1,0,0,0,
  	149,142,1,0,0,0,149,143,1,0,0,0,149,144,1,0,0,0,149,145,1,0,0,0,150,176,
  	1,0,0,0,151,152,10,11,0,0,152,153,7,1,0,0,153,175,3,14,7,12,154,155,10,
  	10,0,0,155,156,7,2,0,0,156,175,3,14,7,11,157,158,10,9,0,0,158,159,5,42,
  	0,0,159,175,3,14,7,10,160,161,10,8,0,0,161,162,5,43,0,0,162,175,3,14,
  	7,9,163,164,10,7,0,0,164,165,5,38,0,0,165,175,3,14,7,8,166,167,10,6,0,
  	0,167,168,5,40,0,0,168,175,3,14,7,7,169,170,10,5,0,0,170,171,5,39,0,0,
  	171,175,3,14,7,6,172,173,10,12,0,0,173,175,3,16,8,0,174,151,1,0,0,0,174,
  	154,1,0,0,0,174,157,1,0,0,0,174,160,1,0,0,0,174,163,1,0,0,0,174,166,1,
  	0,0,0,174,169,1,0,0,0,174,172,1,0,0,0,175,178,1,0,0,0,176,174,1,0,0,0,
  	176,177,1,0,0,0,177,15,1,0,0,0,178,176,1,0,0,0,179,180,5,14,0,0,180,183,
  	7,3,0,0,181,182,5,47,0,0,182,184,7,3,0,0,183,181,1,0,0,0,183,184,1,0,
  	0,0,184,185,1,0,0,0,185,186,5,15,0,0,186,17,1,0,0,0,187,190,5,14,0,0,
  	188,191,3,14,7,0,189,191,3,20,10,0,190,188,1,0,0,0,190,189,1,0,0,0,191,
  	192,1,0,0,0,192,195,5,47,0,0,193,196,3,14,7,0,194,196,3,22,11,0,195,193,
  	1,0,0,0,195,194,1,0,0,0,196,197,1,0,0,0,197,198,5,15,0,0,198,19,1,0,0,
  	0,199,200,5,49,0,0,200,21,1,0,0,0,201,202,5,49,0,0,202,23,1,0,0,0,203,
  	204,3,14,7,0,204,25,1,0,0,0,205,208,3,28,14,0,206,208,5,4,0,0,207,205,
  	1,0,0,0,207,206,1,0,0,0,208,27,1,0,0,0,209,220,5,23,0,0,210,212,5,20,
  	0,0,211,213,5,5,0,0,212,211,1,0,0,0,212,213,1,0,0,0,213,220,1,0,0,0,214,
  	216,5,21,0,0,215,217,5,5,0,0,216,215,1,0,0,0,216,217,1,0,0,0,217,220,
  	1,0,0,0,218,220,5,24,0,0,219,209,1,0,0,0,219,210,1,0,0,0,219,214,1,0,
  	0,0,219,218,1,0,0,0,220,29,1,0,0,0,221,225,3,32,16,0,222,225,3,28,14,
  	0,223,225,5,6,0,0,224,221,1,0,0,0,224,222,1,0,0,0,224,223,1,0,0,0,225,
  	31,1,0,0,0,226,228,5,21,0,0,227,226,1,0,0,0,227,228,1,0,0,0,228,229,1,
  	0,0,0,229,230,5,25,0,0,230,33,1,0,0,0,231,232,7,4,0,0,232,35,1,0,0,0,
  	233,234,6,18,-1,0,234,240,3,38,19,0,235,236,5,16,0,0,236,237,3,36,18,
  	0,237,238,5,17,0,0,238,240,1,0,0,0,239,233,1,0,0,0,239,235,1,0,0,0,240,
  	256,1,0,0,0,241,242,10,4,0,0,242,243,5,28,0,0,243,255,3,36,18,5,244,245,
  	10,3,0,0,245,246,5,9,0,0,246,251,5,16,0,0,247,248,5,21,0,0,248,249,5,
  	1,0,0,249,252,5,21,0,0,250,252,5,21,0,0,251,247,1,0,0,0,251,250,1,0,0,
  	0,251,252,1,0,0,0,252,253,1,0,0,0,253,255,5,17,0,0,254,241,1,0,0,0,254,
  	244,1,0,0,0,255,258,1,0,0,0,256,254,1,0,0,0,256,257,1,0,0,0,257,37,1,
  	0,0,0,258,256,1,0,0,0,259,260,7,5,0,0,260,39,1,0,0,0,261,262,5,19,0,0,
  	262,263,5,16,0,0,263,268,3,42,21,0,264,265,5,1,0,0,265,267,3,42,21,0,
  	266,264,1,0,0,0,267,270,1,0,0,0,268,266,1,0,0,0,268,269,1,0,0,0,269,271,
  	1,0,0,0,270,268,1,0,0,0,271,272,5,17,0,0,272,41,1,0,0,0,273,276,3,14,
  	7,0,274,276,3,10,5,0,275,273,1,0,0,0,275,274,1,0,0,0,276,43,1,0,0,0,277,
  	278,7,6,0,0,278,45,1,0,0,0,279,280,7,7,0,0,280,47,1,0,0,0,24,72,78,83,
  	117,131,133,149,174,176,183,190,195,207,212,216,219,224,227,239,251,254,
  	256,268,275
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  propositionParserStaticData = staticData.release();
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

propositionParser::BooleanContext* propositionParser::StartBooleanContext::boolean() {
  return getRuleContext<propositionParser::BooleanContext>(0);
}

tree::TerminalNode* propositionParser::StartBooleanContext::EOF() {
  return getToken(propositionParser::EOF, 0);
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
    setState(48);
    boolean(0);
    setState(49);
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

propositionParser::NumericContext* propositionParser::StartIntContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}

tree::TerminalNode* propositionParser::StartIntContext::EOF() {
  return getToken(propositionParser::EOF, 0);
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
    setState(51);
    numeric(0);
    setState(52);
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

propositionParser::NumericContext* propositionParser::StartLogicContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}

tree::TerminalNode* propositionParser::StartLogicContext::EOF() {
  return getToken(propositionParser::EOF, 0);
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
    setState(54);
    numeric(0);
    setState(55);
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

propositionParser::NumericContext* propositionParser::StartFloatContext::numeric() {
  return getRuleContext<propositionParser::NumericContext>(0);
}

tree::TerminalNode* propositionParser::StartFloatContext::EOF() {
  return getToken(propositionParser::EOF, 0);
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
    setState(57);
    numeric(0);
    setState(58);
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
    setState(60);
    string(0);
    setState(61);
    match(propositionParser::EOF);
   
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

tree::TerminalNode* propositionParser::BooleanContext::NOT() {
  return getToken(propositionParser::NOT, 0);
}

std::vector<propositionParser::BooleanContext *> propositionParser::BooleanContext::boolean() {
  return getRuleContexts<propositionParser::BooleanContext>();
}

propositionParser::BooleanContext* propositionParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<propositionParser::BooleanContext>(i);
}

propositionParser::NonTemporalFunctionContext* propositionParser::BooleanContext::nonTemporalFunction() {
  return getRuleContext<propositionParser::NonTemporalFunctionContext>(0);
}

std::vector<propositionParser::NumericContext *> propositionParser::BooleanContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
}

tree::TerminalNode* propositionParser::BooleanContext::INSIDE() {
  return getToken(propositionParser::INSIDE, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::LCURLY() {
  return getToken(propositionParser::LCURLY, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::RCURLY() {
  return getToken(propositionParser::RCURLY, 0);
}

std::vector<propositionParser::Sm_constantContext *> propositionParser::BooleanContext::sm_constant() {
  return getRuleContexts<propositionParser::Sm_constantContext>();
}

propositionParser::Sm_constantContext* propositionParser::BooleanContext::sm_constant(size_t i) {
  return getRuleContext<propositionParser::Sm_constantContext>(i);
}

std::vector<propositionParser::Sm_rangeContext *> propositionParser::BooleanContext::sm_range() {
  return getRuleContexts<propositionParser::Sm_rangeContext>();
}

propositionParser::Sm_rangeContext* propositionParser::BooleanContext::sm_range(size_t i) {
  return getRuleContext<propositionParser::Sm_rangeContext>(i);
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

std::vector<propositionParser::StringContext *> propositionParser::BooleanContext::string() {
  return getRuleContexts<propositionParser::StringContext>();
}

propositionParser::StringContext* propositionParser::BooleanContext::string(size_t i) {
  return getRuleContext<propositionParser::StringContext>(i);
}

propositionParser::BooleanAtomContext* propositionParser::BooleanContext::booleanAtom() {
  return getRuleContext<propositionParser::BooleanAtomContext>(0);
}

tree::TerminalNode* propositionParser::BooleanContext::LROUND() {
  return getToken(propositionParser::LROUND, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::RROUND() {
  return getToken(propositionParser::RROUND, 0);
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
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, propositionParser::RuleBoolean, precedence);

    

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
    setState(117);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(64);
      match(propositionParser::NOT);
      setState(65);
      boolean(16);
      break;
    }

    case 2: {
      setState(66);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(67);
      numeric(0);
      setState(68);
      match(propositionParser::INSIDE);
      setState(69);
      match(propositionParser::LCURLY);
      setState(78);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(72);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case propositionParser::INT_VARIABLE:
            case propositionParser::LOGIC_VARIABLE:
            case propositionParser::FLOAT_CONSTANT:
            case propositionParser::FLOAT_VARIABLE:
            case propositionParser::LROUND:
            case propositionParser::FUNCTION:
            case propositionParser::SINTEGER:
            case propositionParser::UINTEGER:
            case propositionParser::GCC_BINARY:
            case propositionParser::HEX:
            case propositionParser::VERILOG_BINARY:
            case propositionParser::NEG: {
              setState(70);
              sm_constant();
              break;
            }

            case propositionParser::LSQUARED: {
              setState(71);
              sm_range();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(74);
          match(propositionParser::T__0); 
        }
        setState(80);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
      }
      setState(83);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case propositionParser::INT_VARIABLE:
        case propositionParser::LOGIC_VARIABLE:
        case propositionParser::FLOAT_CONSTANT:
        case propositionParser::FLOAT_VARIABLE:
        case propositionParser::LROUND:
        case propositionParser::FUNCTION:
        case propositionParser::SINTEGER:
        case propositionParser::UINTEGER:
        case propositionParser::GCC_BINARY:
        case propositionParser::HEX:
        case propositionParser::VERILOG_BINARY:
        case propositionParser::NEG: {
          setState(81);
          sm_constant();
          break;
        }

        case propositionParser::LSQUARED: {
          setState(82);
          sm_range();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(85);
      match(propositionParser::RCURLY);
      break;
    }

    case 4: {
      setState(87);
      numeric(0);
      setState(88);
      relop();
      setState(89);
      numeric(0);
      break;
    }

    case 5: {
      setState(91);
      numeric(0);
      setState(92);
      match(propositionParser::EQ);
      setState(93);
      numeric(0);
      break;
    }

    case 6: {
      setState(95);
      numeric(0);
      setState(96);
      match(propositionParser::NEQ);
      setState(97);
      numeric(0);
      break;
    }

    case 7: {
      setState(99);
      string(0);
      setState(100);
      relop();
      setState(101);
      string(0);
      break;
    }

    case 8: {
      setState(103);
      string(0);
      setState(104);
      match(propositionParser::EQ);
      setState(105);
      string(0);
      break;
    }

    case 9: {
      setState(107);
      string(0);
      setState(108);
      match(propositionParser::NEQ);
      setState(109);
      string(0);
      break;
    }

    case 10: {
      setState(111);
      booleanAtom();
      break;
    }

    case 11: {
      setState(112);
      numeric(0);
      break;
    }

    case 12: {
      setState(113);
      match(propositionParser::LROUND);
      setState(114);
      boolean(0);
      setState(115);
      match(propositionParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(133);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(131);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(119);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(120);
          match(propositionParser::EQ);
          setState(121);
          boolean(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(122);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(123);
          match(propositionParser::NEQ);
          setState(124);
          boolean(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(125);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(126);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::AND);
          setState(127);
          boolean(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(128);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(129);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::OR);
          setState(130);
          boolean(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(135);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
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
  enterRule(_localctx, 12, propositionParser::RuleBooleanAtom);
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
    setState(136);
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

tree::TerminalNode* propositionParser::NumericContext::NEG() {
  return getToken(propositionParser::NEG, 0);
}

std::vector<propositionParser::NumericContext *> propositionParser::NumericContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::NumericContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
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

tree::TerminalNode* propositionParser::NumericContext::LROUND() {
  return getToken(propositionParser::LROUND, 0);
}

tree::TerminalNode* propositionParser::NumericContext::RROUND() {
  return getToken(propositionParser::RROUND, 0);
}

tree::TerminalNode* propositionParser::NumericContext::TIMES() {
  return getToken(propositionParser::TIMES, 0);
}

tree::TerminalNode* propositionParser::NumericContext::DIV() {
  return getToken(propositionParser::DIV, 0);
}

tree::TerminalNode* propositionParser::NumericContext::PLUS() {
  return getToken(propositionParser::PLUS, 0);
}

tree::TerminalNode* propositionParser::NumericContext::MINUS() {
  return getToken(propositionParser::MINUS, 0);
}

tree::TerminalNode* propositionParser::NumericContext::LSHIFT() {
  return getToken(propositionParser::LSHIFT, 0);
}

tree::TerminalNode* propositionParser::NumericContext::RSHIFT() {
  return getToken(propositionParser::RSHIFT, 0);
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
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, propositionParser::RuleNumeric, precedence);

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
    setState(149);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(139);
      match(propositionParser::NEG);
      setState(140);
      numeric(14);
      break;
    }

    case 2: {
      setState(141);
      nonTemporalFunction();
      break;
    }

    case 3: {
      setState(142);
      intAtom();
      break;
    }

    case 4: {
      setState(143);
      logicAtom();
      break;
    }

    case 5: {
      setState(144);
      floatAtom();
      break;
    }

    case 6: {
      setState(145);
      match(propositionParser::LROUND);
      setState(146);
      numeric(0);
      setState(147);
      match(propositionParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(176);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(174);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(151);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(152);
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
          setState(153);
          numeric(12);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(154);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(155);
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
          setState(156);
          numeric(11);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(157);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(158);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::LSHIFT);
          setState(159);
          numeric(10);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(160);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(161);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::RSHIFT);
          setState(162);
          numeric(9);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(163);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(164);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BAND);
          setState(165);
          numeric(8);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(166);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(167);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BXOR);
          setState(168);
          numeric(7);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(169);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(170);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BOR);
          setState(171);
          numeric(6);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(172);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(173);
          range();
          break;
        }

        default:
          break;
        } 
      }
      setState(178);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
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

tree::TerminalNode* propositionParser::RangeContext::RSQUARED() {
  return getToken(propositionParser::RSQUARED, 0);
}

std::vector<tree::TerminalNode *> propositionParser::RangeContext::SINTEGER() {
  return getTokens(propositionParser::SINTEGER);
}

tree::TerminalNode* propositionParser::RangeContext::SINTEGER(size_t i) {
  return getToken(propositionParser::SINTEGER, i);
}

std::vector<tree::TerminalNode *> propositionParser::RangeContext::UINTEGER() {
  return getTokens(propositionParser::UINTEGER);
}

tree::TerminalNode* propositionParser::RangeContext::UINTEGER(size_t i) {
  return getToken(propositionParser::UINTEGER, i);
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
  enterRule(_localctx, 16, propositionParser::RuleRange);
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
    setState(179);
    match(propositionParser::LSQUARED);
    setState(180);
    _la = _input->LA(1);
    if (!(_la == propositionParser::SINTEGER

    || _la == propositionParser::UINTEGER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(183);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == propositionParser::COL) {
      setState(181);
      match(propositionParser::COL);
      setState(182);
      _la = _input->LA(1);
      if (!(_la == propositionParser::SINTEGER

      || _la == propositionParser::UINTEGER)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(185);
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
  enterRule(_localctx, 18, propositionParser::RuleSm_range);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    match(propositionParser::LSQUARED);
    setState(190);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::INT_VARIABLE:
      case propositionParser::LOGIC_VARIABLE:
      case propositionParser::FLOAT_CONSTANT:
      case propositionParser::FLOAT_VARIABLE:
      case propositionParser::LROUND:
      case propositionParser::FUNCTION:
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BINARY:
      case propositionParser::NEG: {
        setState(188);
        numeric(0);
        break;
      }

      case propositionParser::DOLLAR: {
        setState(189);
        min_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(192);
    match(propositionParser::COL);
    setState(195);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::INT_VARIABLE:
      case propositionParser::LOGIC_VARIABLE:
      case propositionParser::FLOAT_CONSTANT:
      case propositionParser::FLOAT_VARIABLE:
      case propositionParser::LROUND:
      case propositionParser::FUNCTION:
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BINARY:
      case propositionParser::NEG: {
        setState(193);
        numeric(0);
        break;
      }

      case propositionParser::DOLLAR: {
        setState(194);
        max_dollar();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(197);
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
  enterRule(_localctx, 20, propositionParser::RuleMin_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
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
  enterRule(_localctx, 22, propositionParser::RuleMax_dollar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
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
  enterRule(_localctx, 24, propositionParser::RuleSm_constant);

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
  enterRule(_localctx, 26, propositionParser::RuleIntAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(207);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(205);
        int_constant();
        break;
      }

      case propositionParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(206);
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

tree::TerminalNode* propositionParser::Int_constantContext::SINTEGER() {
  return getToken(propositionParser::SINTEGER, 0);
}

tree::TerminalNode* propositionParser::Int_constantContext::CONST_SUFFIX() {
  return getToken(propositionParser::CONST_SUFFIX, 0);
}

tree::TerminalNode* propositionParser::Int_constantContext::UINTEGER() {
  return getToken(propositionParser::UINTEGER, 0);
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
  enterRule(_localctx, 28, propositionParser::RuleInt_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(219);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(209);
        match(propositionParser::GCC_BINARY);
        break;
      }

      case propositionParser::SINTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(210);
        match(propositionParser::SINTEGER);
        setState(212);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
        case 1: {
          setState(211);
          match(propositionParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case propositionParser::UINTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(214);
        match(propositionParser::UINTEGER);
        setState(216);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
        case 1: {
          setState(215);
          match(propositionParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 4);
        setState(218);
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
  enterRule(_localctx, 30, propositionParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(224);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(221);
      logic_constant();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(222);
      int_constant();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(223);
      match(propositionParser::LOGIC_VARIABLE);
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

tree::TerminalNode* propositionParser::Logic_constantContext::VERILOG_BINARY() {
  return getToken(propositionParser::VERILOG_BINARY, 0);
}

tree::TerminalNode* propositionParser::Logic_constantContext::UINTEGER() {
  return getToken(propositionParser::UINTEGER, 0);
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
  enterRule(_localctx, 32, propositionParser::RuleLogic_constant);
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
    setState(227);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == propositionParser::UINTEGER) {
      setState(226);
      match(propositionParser::UINTEGER);
    }
    setState(229);
    match(propositionParser::VERILOG_BINARY);
   
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
  enterRule(_localctx, 34, propositionParser::RuleFloatAtom);
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
    setState(231);
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
  size_t startState = 36;
  enterRecursionRule(_localctx, 36, propositionParser::RuleString, precedence);

    

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
    setState(239);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::STRING_CONSTANT:
      case propositionParser::STRING_VARIABLE: {
        setState(234);
        stringAtom();
        break;
      }

      case propositionParser::LROUND: {
        setState(235);
        match(propositionParser::LROUND);
        setState(236);
        string(0);
        setState(237);
        match(propositionParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(256);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(254);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(241);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(242);
          match(propositionParser::PLUS);
          setState(243);
          string(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<StringContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleString);
          setState(244);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(245);
          match(propositionParser::SUBSTR);
          setState(246);
          match(propositionParser::LROUND);
          setState(251);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
          case 1: {
            setState(247);
            match(propositionParser::UINTEGER);
            setState(248);
            match(propositionParser::T__0);
            setState(249);
            match(propositionParser::UINTEGER);
            break;
          }

          case 2: {
            setState(250);
            match(propositionParser::UINTEGER);
            break;
          }

          default:
            break;
          }
          setState(253);
          match(propositionParser::RROUND);
          break;
        }

        default:
          break;
        } 
      }
      setState(258);
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
  enterRule(_localctx, 38, propositionParser::RuleStringAtom);
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
    setState(259);
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
  enterRule(_localctx, 40, propositionParser::RuleNonTemporalFunction);
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
    setState(261);
    match(propositionParser::FUNCTION);
    setState(262);
    match(propositionParser::LROUND);
    setState(263);
    pfunc_arg();
    setState(268);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == propositionParser::T__0) {
      setState(264);
      match(propositionParser::T__0);
      setState(265);
      pfunc_arg();
      setState(270);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(271);
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
  enterRule(_localctx, 42, propositionParser::RulePfunc_arg);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(273);
      numeric(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(274);
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
  enterRule(_localctx, 44, propositionParser::RuleRelop);
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
    setState(277);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << propositionParser::GT)
      | (1ULL << propositionParser::GE)
      | (1ULL << propositionParser::LT)
      | (1ULL << propositionParser::LE))) != 0))) {
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
  enterRule(_localctx, 46, propositionParser::RuleCls_op);
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
    setState(279);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << propositionParser::GT)
      | (1ULL << propositionParser::GE)
      | (1ULL << propositionParser::LT)
      | (1ULL << propositionParser::LE)
      | (1ULL << propositionParser::EQ)
      | (1ULL << propositionParser::RANGE))) != 0))) {
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
    case 5: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 7: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);
    case 18: return stringSempred(antlrcpp::downCast<StringContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool propositionParser::booleanSempred(BooleanContext *_localctx, size_t predicateIndex) {
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

bool propositionParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
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

bool propositionParser::stringSempred(StringContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 12: return precpred(_ctx, 4);
    case 13: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void propositionParser::initialize() {
  std::call_once(propositionParserOnceFlag, propositionParserInitialize);
}
