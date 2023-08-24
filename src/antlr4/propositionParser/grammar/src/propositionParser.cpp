
// Generated from proposition.g4 by ANTLR 4.12.0


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
PropositionParserStaticData *propositionParserStaticData = nullptr;

void propositionParserInitialize() {
  assert(propositionParserStaticData == nullptr);
  auto staticData = std::make_unique<PropositionParserStaticData>(
    std::vector<std::string>{
      "file", "boolean", "booleanAtom", "logic", "bitSelect", "logicAtom", 
      "logic_constant", "numeric", "numericAtom", "relop"
    },
    std::vector<std::string>{
      "", "':'", "", "", "", "", "", "", "'{'", "'}'", "'['", "']'", "'('", 
      "')'", "", "", "", "", "", "", "'+'", "'-'", "'*'", "'/'", "'>'", 
      "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", "'|'", "'^'", "'~'", 
      "'<<'", "'>>'", "'&&'", "'||'", "'!'"
    },
    std::vector<std::string>{
      "", "", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", "LOGIC_VARIABLE", 
      "CONST_SUFFIX", "NUMERIC_CONSTANT", "NUMERIC_VARIABLE", "LCURLY", 
      "RCURLY", "LSQUARED", "RSQUARED", "LROUND", "RROUND", "SINTEGER", 
      "UINTEGER", "FLOAT", "VERILOG_BINARY", "GCC_BINARY", "HEX", "PLUS", 
      "MINUS", "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "BAND", 
      "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,39,166,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,58,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,5,1,72,8,1,10,1,12,1,75,9,1,1,2,1,2,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,3,3,87,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,5,3,112,8,3,10,3,
  	12,3,115,9,3,1,4,1,4,1,4,1,4,3,4,121,8,4,1,4,1,4,1,5,1,5,3,5,127,8,5,
  	1,6,1,6,1,6,1,6,3,6,133,8,6,1,6,1,6,3,6,137,8,6,1,6,3,6,140,8,6,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,3,7,149,8,7,1,7,1,7,1,7,1,7,1,7,1,7,5,7,157,8,7,
  	10,7,12,7,160,9,7,1,8,1,8,1,9,1,9,1,9,0,3,2,6,14,10,0,2,4,6,8,10,12,14,
  	16,18,0,5,1,0,2,3,1,0,22,23,1,0,20,21,1,0,6,7,1,0,24,27,191,0,20,1,0,
  	0,0,2,57,1,0,0,0,4,76,1,0,0,0,6,86,1,0,0,0,8,116,1,0,0,0,10,126,1,0,0,
  	0,12,139,1,0,0,0,14,148,1,0,0,0,16,161,1,0,0,0,18,163,1,0,0,0,20,21,3,
  	2,1,0,21,22,5,0,0,1,22,1,1,0,0,0,23,24,6,1,-1,0,24,25,5,38,0,0,25,58,
  	3,2,1,15,26,27,3,6,3,0,27,28,3,18,9,0,28,29,3,6,3,0,29,58,1,0,0,0,30,
  	31,3,14,7,0,31,32,3,18,9,0,32,33,3,14,7,0,33,58,1,0,0,0,34,35,3,6,3,0,
  	35,36,5,28,0,0,36,37,3,6,3,0,37,58,1,0,0,0,38,39,3,14,7,0,39,40,5,28,
  	0,0,40,41,3,14,7,0,41,58,1,0,0,0,42,43,3,6,3,0,43,44,5,29,0,0,44,45,3,
  	6,3,0,45,58,1,0,0,0,46,47,3,14,7,0,47,48,5,29,0,0,48,49,3,14,7,0,49,58,
  	1,0,0,0,50,58,3,4,2,0,51,58,3,6,3,0,52,58,3,14,7,0,53,54,5,12,0,0,54,
  	55,3,2,1,0,55,56,5,13,0,0,56,58,1,0,0,0,57,23,1,0,0,0,57,26,1,0,0,0,57,
  	30,1,0,0,0,57,34,1,0,0,0,57,38,1,0,0,0,57,42,1,0,0,0,57,46,1,0,0,0,57,
  	50,1,0,0,0,57,51,1,0,0,0,57,52,1,0,0,0,57,53,1,0,0,0,58,73,1,0,0,0,59,
  	60,10,10,0,0,60,61,5,28,0,0,61,72,3,2,1,11,62,63,10,7,0,0,63,64,5,29,
  	0,0,64,72,3,2,1,8,65,66,10,6,0,0,66,67,5,36,0,0,67,72,3,2,1,7,68,69,10,
  	5,0,0,69,70,5,37,0,0,70,72,3,2,1,6,71,59,1,0,0,0,71,62,1,0,0,0,71,65,
  	1,0,0,0,71,68,1,0,0,0,72,75,1,0,0,0,73,71,1,0,0,0,73,74,1,0,0,0,74,3,
  	1,0,0,0,75,73,1,0,0,0,76,77,7,0,0,0,77,5,1,0,0,0,78,79,6,3,-1,0,79,80,
  	5,33,0,0,80,87,3,6,3,11,81,87,3,10,5,0,82,83,5,12,0,0,83,84,3,6,3,0,84,
  	85,5,13,0,0,85,87,1,0,0,0,86,78,1,0,0,0,86,81,1,0,0,0,86,82,1,0,0,0,87,
  	113,1,0,0,0,88,89,10,9,0,0,89,90,7,1,0,0,90,112,3,6,3,10,91,92,10,8,0,
  	0,92,93,7,2,0,0,93,112,3,6,3,9,94,95,10,7,0,0,95,96,5,34,0,0,96,112,3,
  	6,3,8,97,98,10,6,0,0,98,99,5,35,0,0,99,112,3,6,3,7,100,101,10,5,0,0,101,
  	102,5,30,0,0,102,112,3,6,3,6,103,104,10,4,0,0,104,105,5,32,0,0,105,112,
  	3,6,3,5,106,107,10,3,0,0,107,108,5,31,0,0,108,112,3,6,3,4,109,110,10,
  	10,0,0,110,112,3,8,4,0,111,88,1,0,0,0,111,91,1,0,0,0,111,94,1,0,0,0,111,
  	97,1,0,0,0,111,100,1,0,0,0,111,103,1,0,0,0,111,106,1,0,0,0,111,109,1,
  	0,0,0,112,115,1,0,0,0,113,111,1,0,0,0,113,114,1,0,0,0,114,7,1,0,0,0,115,
  	113,1,0,0,0,116,117,5,10,0,0,117,120,5,15,0,0,118,119,5,1,0,0,119,121,
  	5,15,0,0,120,118,1,0,0,0,120,121,1,0,0,0,121,122,1,0,0,0,122,123,5,11,
  	0,0,123,9,1,0,0,0,124,127,3,12,6,0,125,127,5,4,0,0,126,124,1,0,0,0,126,
  	125,1,0,0,0,127,11,1,0,0,0,128,140,5,17,0,0,129,140,5,18,0,0,130,132,
  	5,14,0,0,131,133,5,5,0,0,132,131,1,0,0,0,132,133,1,0,0,0,133,140,1,0,
  	0,0,134,136,5,15,0,0,135,137,5,5,0,0,136,135,1,0,0,0,136,137,1,0,0,0,
  	137,140,1,0,0,0,138,140,5,19,0,0,139,128,1,0,0,0,139,129,1,0,0,0,139,
  	130,1,0,0,0,139,134,1,0,0,0,139,138,1,0,0,0,140,13,1,0,0,0,141,142,6,
  	7,-1,0,142,149,3,16,8,0,143,149,3,6,3,0,144,145,5,12,0,0,145,146,3,14,
  	7,0,146,147,5,13,0,0,147,149,1,0,0,0,148,141,1,0,0,0,148,143,1,0,0,0,
  	148,144,1,0,0,0,149,158,1,0,0,0,150,151,10,5,0,0,151,152,7,1,0,0,152,
  	157,3,14,7,6,153,154,10,4,0,0,154,155,7,2,0,0,155,157,3,14,7,5,156,150,
  	1,0,0,0,156,153,1,0,0,0,157,160,1,0,0,0,158,156,1,0,0,0,158,159,1,0,0,
  	0,159,15,1,0,0,0,160,158,1,0,0,0,161,162,7,3,0,0,162,17,1,0,0,0,163,164,
  	7,4,0,0,164,19,1,0,0,0,14,57,71,73,86,111,113,120,126,132,136,139,148,
  	156,158
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


//----------------- FileContext ------------------------------------------------------------------

propositionParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

propositionParser::BooleanContext* propositionParser::FileContext::boolean() {
  return getRuleContext<propositionParser::BooleanContext>(0);
}

tree::TerminalNode* propositionParser::FileContext::EOF() {
  return getToken(propositionParser::EOF, 0);
}


size_t propositionParser::FileContext::getRuleIndex() const {
  return propositionParser::RuleFile;
}

void propositionParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void propositionParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

propositionParser::FileContext* propositionParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, propositionParser::RuleFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(20);
    boolean(0);
    setState(21);
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

std::vector<propositionParser::LogicContext *> propositionParser::BooleanContext::logic() {
  return getRuleContexts<propositionParser::LogicContext>();
}

propositionParser::LogicContext* propositionParser::BooleanContext::logic(size_t i) {
  return getRuleContext<propositionParser::LogicContext>(i);
}

propositionParser::RelopContext* propositionParser::BooleanContext::relop() {
  return getRuleContext<propositionParser::RelopContext>(0);
}

std::vector<propositionParser::NumericContext *> propositionParser::BooleanContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
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
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, propositionParser::RuleBoolean, precedence);

    

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
    setState(57);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(24);
      match(propositionParser::NOT);
      setState(25);
      boolean(15);
      break;
    }

    case 2: {
      setState(26);
      logic(0);
      setState(27);
      relop();
      setState(28);
      logic(0);
      break;
    }

    case 3: {
      setState(30);
      numeric(0);
      setState(31);
      relop();
      setState(32);
      numeric(0);
      break;
    }

    case 4: {
      setState(34);
      logic(0);
      setState(35);
      match(propositionParser::EQ);
      setState(36);
      logic(0);
      break;
    }

    case 5: {
      setState(38);
      numeric(0);
      setState(39);
      match(propositionParser::EQ);
      setState(40);
      numeric(0);
      break;
    }

    case 6: {
      setState(42);
      logic(0);
      setState(43);
      match(propositionParser::NEQ);
      setState(44);
      logic(0);
      break;
    }

    case 7: {
      setState(46);
      numeric(0);
      setState(47);
      match(propositionParser::NEQ);
      setState(48);
      numeric(0);
      break;
    }

    case 8: {
      setState(50);
      booleanAtom();
      break;
    }

    case 9: {
      setState(51);
      logic(0);
      break;
    }

    case 10: {
      setState(52);
      numeric(0);
      break;
    }

    case 11: {
      setState(53);
      match(propositionParser::LROUND);
      setState(54);
      boolean(0);
      setState(55);
      match(propositionParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(73);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(71);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(59);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(60);
          match(propositionParser::EQ);
          setState(61);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(62);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(63);
          match(propositionParser::NEQ);
          setState(64);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(65);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(66);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::AND);
          setState(67);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(68);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(69);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::OR);
          setState(70);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(75);
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
  enterRule(_localctx, 4, propositionParser::RuleBooleanAtom);
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
    setState(76);
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

//----------------- LogicContext ------------------------------------------------------------------

propositionParser::LogicContext::LogicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::LogicContext::NEG() {
  return getToken(propositionParser::NEG, 0);
}

std::vector<propositionParser::LogicContext *> propositionParser::LogicContext::logic() {
  return getRuleContexts<propositionParser::LogicContext>();
}

propositionParser::LogicContext* propositionParser::LogicContext::logic(size_t i) {
  return getRuleContext<propositionParser::LogicContext>(i);
}

propositionParser::LogicAtomContext* propositionParser::LogicContext::logicAtom() {
  return getRuleContext<propositionParser::LogicAtomContext>(0);
}

tree::TerminalNode* propositionParser::LogicContext::LROUND() {
  return getToken(propositionParser::LROUND, 0);
}

tree::TerminalNode* propositionParser::LogicContext::RROUND() {
  return getToken(propositionParser::RROUND, 0);
}

tree::TerminalNode* propositionParser::LogicContext::TIMES() {
  return getToken(propositionParser::TIMES, 0);
}

tree::TerminalNode* propositionParser::LogicContext::DIV() {
  return getToken(propositionParser::DIV, 0);
}

tree::TerminalNode* propositionParser::LogicContext::PLUS() {
  return getToken(propositionParser::PLUS, 0);
}

tree::TerminalNode* propositionParser::LogicContext::MINUS() {
  return getToken(propositionParser::MINUS, 0);
}

tree::TerminalNode* propositionParser::LogicContext::LSHIFT() {
  return getToken(propositionParser::LSHIFT, 0);
}

tree::TerminalNode* propositionParser::LogicContext::RSHIFT() {
  return getToken(propositionParser::RSHIFT, 0);
}

tree::TerminalNode* propositionParser::LogicContext::BAND() {
  return getToken(propositionParser::BAND, 0);
}

tree::TerminalNode* propositionParser::LogicContext::BXOR() {
  return getToken(propositionParser::BXOR, 0);
}

tree::TerminalNode* propositionParser::LogicContext::BOR() {
  return getToken(propositionParser::BOR, 0);
}

propositionParser::BitSelectContext* propositionParser::LogicContext::bitSelect() {
  return getRuleContext<propositionParser::BitSelectContext>(0);
}


size_t propositionParser::LogicContext::getRuleIndex() const {
  return propositionParser::RuleLogic;
}

void propositionParser::LogicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic(this);
}

void propositionParser::LogicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic(this);
}


propositionParser::LogicContext* propositionParser::logic() {
   return logic(0);
}

propositionParser::LogicContext* propositionParser::logic(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  propositionParser::LogicContext *_localctx = _tracker.createInstance<LogicContext>(_ctx, parentState);
  propositionParser::LogicContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, propositionParser::RuleLogic, precedence);

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
    setState(86);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::NEG: {
        setState(79);
        match(propositionParser::NEG);
        setState(80);
        logic(11);
        break;
      }

      case propositionParser::LOGIC_VARIABLE:
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::VERILOG_BINARY:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX: {
        setState(81);
        logicAtom();
        break;
      }

      case propositionParser::LROUND: {
        setState(82);
        match(propositionParser::LROUND);
        setState(83);
        logic(0);
        setState(84);
        match(propositionParser::RROUND);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(113);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(111);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(88);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(89);
          antlrcpp::downCast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::TIMES

          || _la == propositionParser::DIV)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(90);
          logic(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(91);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(92);
          antlrcpp::downCast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::PLUS

          || _la == propositionParser::MINUS)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(93);
          logic(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(94);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(95);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(propositionParser::LSHIFT);
          setState(96);
          logic(8);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(97);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(98);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(propositionParser::RSHIFT);
          setState(99);
          logic(7);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(100);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(101);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(propositionParser::BAND);
          setState(102);
          logic(6);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(103);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(104);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(propositionParser::BXOR);
          setState(105);
          logic(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(106);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(107);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(propositionParser::BOR);
          setState(108);
          logic(4);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(109);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(110);
          bitSelect();
          break;
        }

        default:
          break;
        } 
      }
      setState(115);
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

//----------------- BitSelectContext ------------------------------------------------------------------

propositionParser::BitSelectContext::BitSelectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::BitSelectContext::LSQUARED() {
  return getToken(propositionParser::LSQUARED, 0);
}

std::vector<tree::TerminalNode *> propositionParser::BitSelectContext::UINTEGER() {
  return getTokens(propositionParser::UINTEGER);
}

tree::TerminalNode* propositionParser::BitSelectContext::UINTEGER(size_t i) {
  return getToken(propositionParser::UINTEGER, i);
}

tree::TerminalNode* propositionParser::BitSelectContext::RSQUARED() {
  return getToken(propositionParser::RSQUARED, 0);
}


size_t propositionParser::BitSelectContext::getRuleIndex() const {
  return propositionParser::RuleBitSelect;
}

void propositionParser::BitSelectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitSelect(this);
}

void propositionParser::BitSelectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitSelect(this);
}

propositionParser::BitSelectContext* propositionParser::bitSelect() {
  BitSelectContext *_localctx = _tracker.createInstance<BitSelectContext>(_ctx, getState());
  enterRule(_localctx, 8, propositionParser::RuleBitSelect);
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
    setState(116);
    match(propositionParser::LSQUARED);
    setState(117);
    match(propositionParser::UINTEGER);
    setState(120);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == propositionParser::T__0) {
      setState(118);
      match(propositionParser::T__0);
      setState(119);
      match(propositionParser::UINTEGER);
    }
    setState(122);
    match(propositionParser::RSQUARED);
   
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
  enterRule(_localctx, 10, propositionParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(126);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::SINTEGER:
      case propositionParser::UINTEGER:
      case propositionParser::VERILOG_BINARY:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(124);
        logic_constant();
        break;
      }

      case propositionParser::LOGIC_VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(125);
        match(propositionParser::LOGIC_VARIABLE);
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

propositionParser::Logic_constantContext::Logic_constantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::Logic_constantContext::VERILOG_BINARY() {
  return getToken(propositionParser::VERILOG_BINARY, 0);
}

tree::TerminalNode* propositionParser::Logic_constantContext::GCC_BINARY() {
  return getToken(propositionParser::GCC_BINARY, 0);
}

tree::TerminalNode* propositionParser::Logic_constantContext::SINTEGER() {
  return getToken(propositionParser::SINTEGER, 0);
}

tree::TerminalNode* propositionParser::Logic_constantContext::CONST_SUFFIX() {
  return getToken(propositionParser::CONST_SUFFIX, 0);
}

tree::TerminalNode* propositionParser::Logic_constantContext::UINTEGER() {
  return getToken(propositionParser::UINTEGER, 0);
}

tree::TerminalNode* propositionParser::Logic_constantContext::HEX() {
  return getToken(propositionParser::HEX, 0);
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
  enterRule(_localctx, 12, propositionParser::RuleLogic_constant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(139);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::VERILOG_BINARY: {
        enterOuterAlt(_localctx, 1);
        setState(128);
        match(propositionParser::VERILOG_BINARY);
        break;
      }

      case propositionParser::GCC_BINARY: {
        enterOuterAlt(_localctx, 2);
        setState(129);
        match(propositionParser::GCC_BINARY);
        break;
      }

      case propositionParser::SINTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(130);
        match(propositionParser::SINTEGER);
        setState(132);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          setState(131);
          match(propositionParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case propositionParser::UINTEGER: {
        enterOuterAlt(_localctx, 4);
        setState(134);
        match(propositionParser::UINTEGER);
        setState(136);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          setState(135);
          match(propositionParser::CONST_SUFFIX);
          break;
        }

        default:
          break;
        }
        break;
      }

      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 5);
        setState(138);
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

//----------------- NumericContext ------------------------------------------------------------------

propositionParser::NumericContext::NumericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

propositionParser::NumericAtomContext* propositionParser::NumericContext::numericAtom() {
  return getRuleContext<propositionParser::NumericAtomContext>(0);
}

propositionParser::LogicContext* propositionParser::NumericContext::logic() {
  return getRuleContext<propositionParser::LogicContext>(0);
}

tree::TerminalNode* propositionParser::NumericContext::LROUND() {
  return getToken(propositionParser::LROUND, 0);
}

std::vector<propositionParser::NumericContext *> propositionParser::NumericContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::NumericContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
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
    setState(148);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(142);
      numericAtom();
      break;
    }

    case 2: {
      setState(143);
      logic(0);
      break;
    }

    case 3: {
      setState(144);
      match(propositionParser::LROUND);
      setState(145);
      numeric(0);
      setState(146);
      match(propositionParser::RROUND);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(158);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(156);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(150);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(151);
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
          setState(152);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(153);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(154);
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
          setState(155);
          numeric(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(160);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
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

propositionParser::NumericAtomContext::NumericAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::NumericAtomContext::NUMERIC_CONSTANT() {
  return getToken(propositionParser::NUMERIC_CONSTANT, 0);
}

tree::TerminalNode* propositionParser::NumericAtomContext::NUMERIC_VARIABLE() {
  return getToken(propositionParser::NUMERIC_VARIABLE, 0);
}


size_t propositionParser::NumericAtomContext::getRuleIndex() const {
  return propositionParser::RuleNumericAtom;
}

void propositionParser::NumericAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericAtom(this);
}

void propositionParser::NumericAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericAtom(this);
}

propositionParser::NumericAtomContext* propositionParser::numericAtom() {
  NumericAtomContext *_localctx = _tracker.createInstance<NumericAtomContext>(_ctx, getState());
  enterRule(_localctx, 16, propositionParser::RuleNumericAtom);
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
    setState(161);
    _la = _input->LA(1);
    if (!(_la == propositionParser::NUMERIC_CONSTANT

    || _la == propositionParser::NUMERIC_VARIABLE)) {
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
  enterRule(_localctx, 18, propositionParser::RuleRelop);
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
    setState(163);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 251658240) != 0))) {
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
    case 1: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 3: return logicSempred(antlrcpp::downCast<LogicContext *>(context), predicateIndex);
    case 7: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool propositionParser::booleanSempred(BooleanContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 10);
    case 1: return precpred(_ctx, 7);
    case 2: return precpred(_ctx, 6);
    case 3: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

bool propositionParser::logicSempred(LogicContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 9);
    case 5: return precpred(_ctx, 8);
    case 6: return precpred(_ctx, 7);
    case 7: return precpred(_ctx, 6);
    case 8: return precpred(_ctx, 5);
    case 9: return precpred(_ctx, 4);
    case 10: return precpred(_ctx, 3);
    case 11: return precpred(_ctx, 10);

  default:
    break;
  }
  return true;
}

bool propositionParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 12: return precpred(_ctx, 5);
    case 13: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void propositionParser::initialize() {
  ::antlr4::internal::call_once(propositionParserOnceFlag, propositionParserInitialize);
}
