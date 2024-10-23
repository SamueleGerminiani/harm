
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
      "startBoolean", "startInt", "startFloat", "boolean", "booleanAtom", 
      "numeric", "range", "intAtom", "int_constant", "floatAtom", "relop", 
      "cls_op"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "'{'", "'}'", "'['", "']'", "'('", "')'", 
      "'inside'", "", "", "", "", "", "", "", "", "'''", "'+'", "'-'", "'*'", 
      "'/'", "'>'", "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", "'|'", 
      "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'", "':'", "'::'", 
      "'$'", "'><'"
    },
    std::vector<std::string>{
      "", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", "INT_VARIABLE", "CONST_SUFFIX", 
      "FLOAT_CONSTANT", "FLOAT_VARIABLE", "LCURLY", "RCURLY", "LSQUARED", 
      "RSQUARED", "LROUND", "RROUND", "INSIDE", "FUNCTION", "SINTEGER", 
      "UINTEGER", "FLOAT", "GCC_BINARY", "HEX", "VERILOG_BINARY", "FVL", 
      "SINGLE_QUOTE", "PLUS", "MINUS", "TIMES", "DIV", "GT", "GE", "LT", 
      "LE", "EQ", "NEQ", "BAND", "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", 
      "AND", "OR", "NOT", "COL", "DCOL", "DOLLAR", "RANGE", "CLS_TYPE", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,47,149,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,1,0,1,0,1,0,1,1,1,1,1,1,1,2,
  	1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,3,3,55,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,5,3,69,8,3,10,3,12,3,72,9,3,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,1,5,3,5,85,8,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,110,8,5,10,5,12,5,
  	113,9,5,1,6,1,6,1,6,1,6,3,6,119,8,6,1,6,1,6,1,7,1,7,3,7,125,8,7,1,8,1,
  	8,1,8,3,8,130,8,8,1,8,1,8,3,8,134,8,8,1,8,3,8,137,8,8,1,8,1,8,3,8,141,
  	8,8,1,9,1,9,1,10,1,10,1,11,1,11,1,11,0,2,6,10,12,0,2,4,6,8,10,12,14,16,
  	18,20,22,0,7,1,0,1,2,1,0,25,26,1,0,23,24,1,0,15,16,1,0,5,6,1,0,27,30,
  	2,0,27,31,45,45,166,0,24,1,0,0,0,2,27,1,0,0,0,4,30,1,0,0,0,6,54,1,0,0,
  	0,8,73,1,0,0,0,10,84,1,0,0,0,12,114,1,0,0,0,14,124,1,0,0,0,16,140,1,0,
  	0,0,18,142,1,0,0,0,20,144,1,0,0,0,22,146,1,0,0,0,24,25,3,6,3,0,25,26,
  	5,0,0,1,26,1,1,0,0,0,27,28,3,10,5,0,28,29,5,0,0,1,29,3,1,0,0,0,30,31,
  	3,10,5,0,31,32,5,0,0,1,32,5,1,0,0,0,33,34,6,3,-1,0,34,35,5,41,0,0,35,
  	55,3,6,3,11,36,37,3,10,5,0,37,38,3,20,10,0,38,39,3,10,5,0,39,55,1,0,0,
  	0,40,41,3,10,5,0,41,42,5,31,0,0,42,43,3,10,5,0,43,55,1,0,0,0,44,45,3,
  	10,5,0,45,46,5,32,0,0,46,47,3,10,5,0,47,55,1,0,0,0,48,55,3,8,4,0,49,55,
  	3,10,5,0,50,51,5,11,0,0,51,52,3,6,3,0,52,53,5,12,0,0,53,55,1,0,0,0,54,
  	33,1,0,0,0,54,36,1,0,0,0,54,40,1,0,0,0,54,44,1,0,0,0,54,48,1,0,0,0,54,
  	49,1,0,0,0,54,50,1,0,0,0,55,70,1,0,0,0,56,57,10,7,0,0,57,58,5,31,0,0,
  	58,69,3,6,3,8,59,60,10,6,0,0,60,61,5,32,0,0,61,69,3,6,3,7,62,63,10,5,
  	0,0,63,64,5,39,0,0,64,69,3,6,3,6,65,66,10,4,0,0,66,67,5,40,0,0,67,69,
  	3,6,3,5,68,56,1,0,0,0,68,59,1,0,0,0,68,62,1,0,0,0,68,65,1,0,0,0,69,72,
  	1,0,0,0,70,68,1,0,0,0,70,71,1,0,0,0,71,7,1,0,0,0,72,70,1,0,0,0,73,74,
  	7,0,0,0,74,9,1,0,0,0,75,76,6,5,-1,0,76,77,5,36,0,0,77,85,3,10,5,12,78,
  	85,3,14,7,0,79,85,3,18,9,0,80,81,5,11,0,0,81,82,3,10,5,0,82,83,5,12,0,
  	0,83,85,1,0,0,0,84,75,1,0,0,0,84,78,1,0,0,0,84,79,1,0,0,0,84,80,1,0,0,
  	0,85,111,1,0,0,0,86,87,10,10,0,0,87,88,7,1,0,0,88,110,3,10,5,11,89,90,
  	10,9,0,0,90,91,7,2,0,0,91,110,3,10,5,10,92,93,10,8,0,0,93,94,5,37,0,0,
  	94,110,3,10,5,9,95,96,10,7,0,0,96,97,5,38,0,0,97,110,3,10,5,8,98,99,10,
  	6,0,0,99,100,5,33,0,0,100,110,3,10,5,7,101,102,10,5,0,0,102,103,5,35,
  	0,0,103,110,3,10,5,6,104,105,10,4,0,0,105,106,5,34,0,0,106,110,3,10,5,
  	5,107,108,10,11,0,0,108,110,3,12,6,0,109,86,1,0,0,0,109,89,1,0,0,0,109,
  	92,1,0,0,0,109,95,1,0,0,0,109,98,1,0,0,0,109,101,1,0,0,0,109,104,1,0,
  	0,0,109,107,1,0,0,0,110,113,1,0,0,0,111,109,1,0,0,0,111,112,1,0,0,0,112,
  	11,1,0,0,0,113,111,1,0,0,0,114,115,5,9,0,0,115,118,7,3,0,0,116,117,5,
  	42,0,0,117,119,7,3,0,0,118,116,1,0,0,0,118,119,1,0,0,0,119,120,1,0,0,
  	0,120,121,5,10,0,0,121,13,1,0,0,0,122,125,3,16,8,0,123,125,5,3,0,0,124,
  	122,1,0,0,0,124,123,1,0,0,0,125,15,1,0,0,0,126,141,5,18,0,0,127,129,5,
  	15,0,0,128,130,5,4,0,0,129,128,1,0,0,0,129,130,1,0,0,0,130,141,1,0,0,
  	0,131,133,5,16,0,0,132,134,5,4,0,0,133,132,1,0,0,0,133,134,1,0,0,0,134,
  	141,1,0,0,0,135,137,5,16,0,0,136,135,1,0,0,0,136,137,1,0,0,0,137,138,
  	1,0,0,0,138,141,5,20,0,0,139,141,5,19,0,0,140,126,1,0,0,0,140,127,1,0,
  	0,0,140,131,1,0,0,0,140,136,1,0,0,0,140,139,1,0,0,0,141,17,1,0,0,0,142,
  	143,7,4,0,0,143,19,1,0,0,0,144,145,7,5,0,0,145,21,1,0,0,0,146,147,7,6,
  	0,0,147,23,1,0,0,0,12,54,68,70,84,109,111,118,124,129,133,136,140
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
    setState(24);
    boolean(0);
    setState(25);
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
    setState(27);
    numeric(0);
    setState(28);
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
  enterRule(_localctx, 4, propositionParser::RuleStartFloat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(30);
    numeric(0);
    setState(31);
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

std::vector<propositionParser::NumericContext *> propositionParser::BooleanContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
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
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, propositionParser::RuleBoolean, precedence);

    

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
    setState(54);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(34);
      match(propositionParser::NOT);
      setState(35);
      boolean(11);
      break;
    }

    case 2: {
      setState(36);
      numeric(0);
      setState(37);
      relop();
      setState(38);
      numeric(0);
      break;
    }

    case 3: {
      setState(40);
      numeric(0);
      setState(41);
      match(propositionParser::EQ);
      setState(42);
      numeric(0);
      break;
    }

    case 4: {
      setState(44);
      numeric(0);
      setState(45);
      match(propositionParser::NEQ);
      setState(46);
      numeric(0);
      break;
    }

    case 5: {
      setState(48);
      booleanAtom();
      break;
    }

    case 6: {
      setState(49);
      numeric(0);
      break;
    }

    case 7: {
      setState(50);
      match(propositionParser::LROUND);
      setState(51);
      boolean(0);
      setState(52);
      match(propositionParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(70);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(68);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(56);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(57);
          match(propositionParser::EQ);
          setState(58);
          boolean(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(59);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(60);
          match(propositionParser::NEQ);
          setState(61);
          boolean(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(62);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(63);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::AND);
          setState(64);
          boolean(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(65);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(66);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::OR);
          setState(67);
          boolean(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(72);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
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
  enterRule(_localctx, 8, propositionParser::RuleBooleanAtom);
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
    setState(73);
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

propositionParser::IntAtomContext* propositionParser::NumericContext::intAtom() {
  return getRuleContext<propositionParser::IntAtomContext>(0);
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
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, propositionParser::RuleNumeric, precedence);

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
    setState(84);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::NEG: {
        setState(76);
        match(propositionParser::NEG);
        setState(77);
        numeric(12);
        break;
      }

      case propositionParser::INT_VARIABLE:
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BINARY: {
        setState(78);
        intAtom();
        break;
      }

      case propositionParser::FLOAT_CONSTANT:
      case propositionParser::FLOAT_VARIABLE: {
        setState(79);
        floatAtom();
        break;
      }

      case propositionParser::LROUND: {
        setState(80);
        match(propositionParser::LROUND);
        setState(81);
        numeric(0);
        setState(82);
        match(propositionParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(111);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(109);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(86);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(87);
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
          setState(88);
          numeric(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(89);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(90);
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
          setState(91);
          numeric(10);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(92);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(93);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::LSHIFT);
          setState(94);
          numeric(9);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(95);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(96);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::RSHIFT);
          setState(97);
          numeric(8);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(98);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(99);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BAND);
          setState(100);
          numeric(7);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(101);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(102);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BXOR);
          setState(103);
          numeric(6);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(104);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(105);
          antlrcpp::downCast<NumericContext *>(_localctx)->logop = match(propositionParser::BOR);
          setState(106);
          numeric(5);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(107);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(108);
          range();
          break;
        }

        default:
          break;
        } 
      }
      setState(113);
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
  enterRule(_localctx, 12, propositionParser::RuleRange);
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
    setState(114);
    match(propositionParser::LSQUARED);
    setState(115);
    _la = _input->LA(1);
    if (!(_la == propositionParser::SINTEGER

    || _la == propositionParser::UINTEGER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(118);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == propositionParser::COL) {
      setState(116);
      match(propositionParser::COL);
      setState(117);
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
    setState(120);
    match(propositionParser::RSQUARED);
   
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
  enterRule(_localctx, 14, propositionParser::RuleIntAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(124);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::VERILOG_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(122);
        int_constant();
        break;
      }

      case propositionParser::INT_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(123);
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

tree::TerminalNode* propositionParser::Int_constantContext::VERILOG_BINARY() {
  return getToken(propositionParser::VERILOG_BINARY, 0);
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
  enterRule(_localctx, 16, propositionParser::RuleInt_constant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(140);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(126);
      match(propositionParser::GCC_BINARY);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(127);
      match(propositionParser::SINTEGER);
      setState(129);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
      case 1: {
        setState(128);
        match(propositionParser::CONST_SUFFIX);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(131);
      match(propositionParser::UINTEGER);
      setState(133);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
      case 1: {
        setState(132);
        match(propositionParser::CONST_SUFFIX);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(136);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == propositionParser::UINTEGER) {
        setState(135);
        match(propositionParser::UINTEGER);
      }
      setState(138);
      match(propositionParser::VERILOG_BINARY);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(139);
      match(propositionParser::HEX);
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
  enterRule(_localctx, 18, propositionParser::RuleFloatAtom);
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
    setState(142);
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
  enterRule(_localctx, 20, propositionParser::RuleRelop);
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
    setState(144);
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
  enterRule(_localctx, 22, propositionParser::RuleCls_op);
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
    setState(146);
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
    case 3: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 5: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);

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
    case 4: return precpred(_ctx, 10);
    case 5: return precpred(_ctx, 9);
    case 6: return precpred(_ctx, 8);
    case 7: return precpred(_ctx, 7);
    case 8: return precpred(_ctx, 6);
    case 9: return precpred(_ctx, 5);
    case 10: return precpred(_ctx, 4);
    case 11: return precpred(_ctx, 11);

  default:
    break;
  }
  return true;
}

void propositionParser::initialize() {
  std::call_once(propositionParserOnceFlag, propositionParserInitialize);
}
