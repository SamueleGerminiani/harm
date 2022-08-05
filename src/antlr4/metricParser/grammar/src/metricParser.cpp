
// Generated from metric.g4 by ANTLR 4.10.1

#include "metricListener.h"

#include "metricParser.h"

using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MetricParserStaticData final {
  MetricParserStaticData(std::vector<std::string> ruleNames,
                         std::vector<std::string> literalNames,
                         std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MetricParserStaticData(const MetricParserStaticData &) = delete;
  MetricParserStaticData(MetricParserStaticData &&) = delete;
  MetricParserStaticData &operator=(const MetricParserStaticData &) = delete;
  MetricParserStaticData &operator=(MetricParserStaticData &&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag metricParserOnceFlag;
MetricParserStaticData *metricParserStaticData = nullptr;

void metricParserInitialize() {
  assert(metricParserStaticData == nullptr);
  auto staticData = std::make_unique<MetricParserStaticData>(
      std::vector<std::string>{"file", "logic", "logicAtom", "logicConstant",
                               "logicVariable", "numeric", "numericAtom",
                               "numericConstant", "numericVariable", "variable",
                               "relop"},
      std::vector<std::string>{
          "",     "',logic('", "','",  "')>'", "',numeric('",
          "",     "'{'",       "'}'",  "'['",  "']'",
          "'('",  "')'",       "",     "",     "",
          "",     "",          "",     "",     "'+'",
          "'-'",  "'*'",       "'/'",  "'>'",  "'>='",
          "'<'",  "'<='",      "'=='", "'!='", "'&'",
          "'|'",  "'^'",       "'~'",  "'<<'", "'>>'",
          "'&&'", "'||'",      "'!'"},
      std::vector<std::string>{
          "",           "",        "",        "",
          "",           "SIGN",    "LGPAREN", "RGPAREN",
          "LCPAREN",    "RCPAREN", "LPAREN",  "RPAREN",
          "VARIABLE",   "INDEX",   "NUMERIC", "VERILOG_BINARY",
          "GCC_BINARY", "HEX",     "BOOLEAN", "PLUS",
          "MINUS",      "TIMES",   "DIV",     "GT",
          "GE",         "LT",      "LE",      "EQ",
          "NEQ",        "BAND",    "BOR",     "BXOR",
          "NEG",        "LSHIFT",  "RSHIFT",  "AND",
          "OR",         "NOT",     "WS"});
  static const int32_t serializedATNSegment[] = {
      4,   1,  38,  106, 2,  0,  7,  0,   2,  1,   7,   1,  2,  2,   7,   2,
      2,   3,  7,   3,   2,  4,  7,  4,   2,  5,   7,   5,  2,  6,   7,   6,
      2,   7,  7,   7,   2,  8,  7,  8,   2,  9,   7,   9,  2,  10,  7,   10,
      1,   0,  1,   0,   1,  0,  1,  1,   1,  1,   1,   1,  1,  1,   1,   1,
      1,   1,  1,   1,   1,  1,  3,  1,   34, 8,   1,   1,  1,  1,   1,   1,
      1,   1,  1,   1,   1,  1,  1,  1,   1,  1,   1,   1,  1,  1,   1,   1,
      1,   1,  1,   1,   1,  1,  1,  1,   1,  5,   1,   51, 8,  1,   10,  1,
      12,  1,  54,  9,   1,  1,  2,  1,   2,  3,   2,   58, 8,  2,   1,   3,
      1,   3,  1,   4,   1,  4,  1,  4,   1,  4,   1,   4,  1,  4,   1,   4,
      1,   4,  1,   5,   1,  5,  1,  5,   1,  5,   1,   5,  1,  5,   1,   5,
      3,   5,  77,  8,   5,  1,  5,  1,   5,  1,   5,   1,  5,  1,   5,   1,
      5,   5,  5,   85,  8,  5,  10, 5,   12, 5,   88,  9,  5,  1,   6,   1,
      6,   3,  6,   92,  8,  6,  1,  7,   1,  7,   1,   8,  1,  8,   1,   8,
      1,   8,  1,   8,   1,  8,  1,  9,   1,  9,   1,   10, 1,  10,  1,   10,
      0,   2,  2,   10,  11, 0,  2,  4,   6,  8,   10,  12, 14, 16,  18,  20,
      0,   4,  1,   0,   14, 17, 1,  0,   21, 22,  1,   0,  19, 20,  1,   0,
      23,  26, 107, 0,   22, 1,  0,  0,   0,  2,   33,  1,  0,  0,   0,   4,
      57,  1,  0,   0,   0,  6,  59, 1,   0,  0,   0,   8,  61, 1,   0,   0,
      0,   10, 76,  1,   0,  0,  0,  12,  91, 1,   0,   0,  0,  14,  93,  1,
      0,   0,  0,   16,  95, 1,  0,  0,   0,  18,  101, 1,  0,  0,   0,   20,
      103, 1,  0,   0,   0,  22, 23, 3,   10, 5,   0,   23, 24, 5,   0,   0,
      1,   24, 1,   1,   0,  0,  0,  25,  26, 6,   1,   -1, 0,  26,  27,  5,
      32,  0,  0,   27,  34, 3,  2,  1,   8,  28,  34,  3,  4,  2,   0,   29,
      30,  5,  10,  0,   0,  30, 31, 3,   2,  1,   0,   31, 32, 5,   11,  0,
      0,   32, 34,  1,   0,  0,  0,  33,  25, 1,   0,   0,  0,  33,  28,  1,
      0,   0,  0,   33,  29, 1,  0,  0,   0,  34,  52,  1,  0,  0,   0,   35,
      36,  10, 7,   0,   0,  36, 37, 5,   33, 0,   0,   37, 51, 3,   2,   1,
      8,   38, 39,  10,  6,  0,  0,  39,  40, 5,   34,  0,  0,  40,  51,  3,
      2,   1,  7,   41,  42, 10, 5,  0,   0,  42,  43,  5,  29, 0,   0,   43,
      51,  3,  2,   1,   6,  44, 45, 10,  4,  0,   0,   45, 46, 5,   31,  0,
      0,   46, 51,  3,   2,  1,  5,  47,  48, 10,  3,   0,  0,  48,  49,  5,
      30,  0,  0,   49,  51, 3,  2,  1,   4,  50,  35,  1,  0,  0,   0,   50,
      38,  1,  0,   0,   0,  50, 41, 1,   0,  0,   0,   50, 44, 1,   0,   0,
      0,   50, 47,  1,   0,  0,  0,  51,  54, 1,   0,   0,  0,  52,  50,  1,
      0,   0,  0,   52,  53, 1,  0,  0,   0,  53,  3,   1,  0,  0,   0,   54,
      52,  1,  0,   0,   0,  55, 58, 3,   6,  3,   0,   56, 58, 3,   8,   4,
      0,   57, 55,  1,   0,  0,  0,  57,  56, 1,   0,   0,  0,  58,  5,   1,
      0,   0,  0,   59,  60, 7,  0,  0,   0,  60,  7,   1,  0,  0,   0,   61,
      62,  5,  25,  0,   0,  62, 63, 3,   18, 9,   0,   63, 64, 5,   1,   0,
      0,   64, 65,  5,   5,  0,  0,  65,  66, 5,   2,   0,  0,  66,  67,  5,
      14,  0,  0,   67,  68, 5,  3,  0,   0,  68,  9,   1,  0,  0,   0,   69,
      70,  6,  5,   -1,  0,  70, 77, 3,   12, 6,   0,   71, 77, 3,   2,   1,
      0,   72, 73,  5,   10, 0,  0,  73,  74, 3,   10,  5,  0,  74,  75,  5,
      11,  0,  0,   75,  77, 1,  0,  0,   0,  76,  69,  1,  0,  0,   0,   76,
      71,  1,  0,   0,   0,  76, 72, 1,   0,  0,   0,   77, 86, 1,   0,   0,
      0,   78, 79,  10,  5,  0,  0,  79,  80, 7,   1,   0,  0,  80,  85,  3,
      10,  5,  6,   81,  82, 10, 4,  0,   0,  82,  83,  7,  2,  0,   0,   83,
      85,  3,  10,  5,   5,  84, 78, 1,   0,  0,   0,   84, 81, 1,   0,   0,
      0,   85, 88,  1,   0,  0,  0,  86,  84, 1,   0,   0,  0,  86,  87,  1,
      0,   0,  0,   87,  11, 1,  0,  0,   0,  88,  86,  1,  0,  0,   0,   89,
      92,  3,  14,  7,   0,  90, 92, 3,   16, 8,   0,   91, 89, 1,   0,   0,
      0,   91, 90,  1,   0,  0,  0,  92,  13, 1,   0,   0,  0,  93,  94,  5,
      14,  0,  0,   94,  15, 1,  0,  0,   0,  95,  96,  5,  25, 0,   0,   96,
      97,  3,  18,  9,   0,  97, 98, 5,   4,  0,   0,   98, 99, 5,   14,  0,
      0,   99, 100, 5,   3,  0,  0,  100, 17, 1,   0,   0,  0,  101, 102, 5,
      12,  0,  0,   102, 19, 1,  0,  0,   0,  103, 104, 7,  3,  0,   0,   104,
      21,  1,  0,   0,   0,  8,  33, 50,  52, 57,  76,  84, 86, 91};
  staticData->serializedATN = antlr4::atn::SerializedATNView(
      serializedATNSegment,
      sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) {
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i),
                                           i);
  }
  metricParserStaticData = staticData.release();
}

} // namespace

metricParser::metricParser(TokenStream *input)
    : metricParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

metricParser::metricParser(
    TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options)
    : Parser(input) {
  metricParser::initialize();
  _interpreter = new atn::ParserATNSimulator(
      this, *metricParserStaticData->atn, metricParserStaticData->decisionToDFA,
      metricParserStaticData->sharedContextCache, options);
}

metricParser::~metricParser() { delete _interpreter; }

const atn::ATN &metricParser::getATN() const {
  return *metricParserStaticData->atn;
}

std::string metricParser::getGrammarFileName() const { return "metric.g4"; }

const std::vector<std::string> &metricParser::getRuleNames() const {
  return metricParserStaticData->ruleNames;
}

const dfa::Vocabulary &metricParser::getVocabulary() const {
  return metricParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView metricParser::getSerializedATN() const {
  return metricParserStaticData->serializedATN;
}

//----------------- FileContext ------------------------------------------------------------------

metricParser::FileContext::FileContext(ParserRuleContext *parent,
                                       size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

metricParser::NumericContext *metricParser::FileContext::numeric() {
  return getRuleContext<metricParser::NumericContext>(0);
}

tree::TerminalNode *metricParser::FileContext::EOF() {
  return getToken(metricParser::EOF, 0);
}

size_t metricParser::FileContext::getRuleIndex() const {
  return metricParser::RuleFile;
}

void metricParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void metricParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

metricParser::FileContext *metricParser::file() {
  FileContext *_localctx =
      _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, metricParser::RuleFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(22);
    numeric(0);
    setState(23);
    match(metricParser::EOF);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicContext ------------------------------------------------------------------

metricParser::LogicContext::LogicContext(ParserRuleContext *parent,
                                         size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *metricParser::LogicContext::NEG() {
  return getToken(metricParser::NEG, 0);
}

std::vector<metricParser::LogicContext *> metricParser::LogicContext::logic() {
  return getRuleContexts<metricParser::LogicContext>();
}

metricParser::LogicContext *metricParser::LogicContext::logic(size_t i) {
  return getRuleContext<metricParser::LogicContext>(i);
}

metricParser::LogicAtomContext *metricParser::LogicContext::logicAtom() {
  return getRuleContext<metricParser::LogicAtomContext>(0);
}

tree::TerminalNode *metricParser::LogicContext::LPAREN() {
  return getToken(metricParser::LPAREN, 0);
}

tree::TerminalNode *metricParser::LogicContext::RPAREN() {
  return getToken(metricParser::RPAREN, 0);
}

tree::TerminalNode *metricParser::LogicContext::LSHIFT() {
  return getToken(metricParser::LSHIFT, 0);
}

tree::TerminalNode *metricParser::LogicContext::RSHIFT() {
  return getToken(metricParser::RSHIFT, 0);
}

tree::TerminalNode *metricParser::LogicContext::BAND() {
  return getToken(metricParser::BAND, 0);
}

tree::TerminalNode *metricParser::LogicContext::BXOR() {
  return getToken(metricParser::BXOR, 0);
}

tree::TerminalNode *metricParser::LogicContext::BOR() {
  return getToken(metricParser::BOR, 0);
}

size_t metricParser::LogicContext::getRuleIndex() const {
  return metricParser::RuleLogic;
}

void metricParser::LogicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic(this);
}

void metricParser::LogicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic(this);
}

metricParser::LogicContext *metricParser::logic() { return logic(0); }

metricParser::LogicContext *metricParser::logic(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  metricParser::LogicContext *_localctx =
      _tracker.createInstance<LogicContext>(_ctx, parentState);
  metricParser::LogicContext *previousContext = _localctx;
  (void)
      previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, metricParser::RuleLogic, precedence);

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
    setState(33);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case metricParser::NEG: {
      setState(26);
      match(metricParser::NEG);
      setState(27);
      logic(8);
      break;
    }

    case metricParser::NUMERIC:
    case metricParser::VERILOG_BINARY:
    case metricParser::GCC_BINARY:
    case metricParser::HEX:
    case metricParser::LT: {
      setState(28);
      logicAtom();
      break;
    }

    case metricParser::LPAREN: {
      setState(29);
      match(metricParser::LPAREN);
      setState(30);
      logic(0);
      setState(31);
      match(metricParser::RPAREN);
      break;
    }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(52);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2,
                                                                     _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(50);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 1, _ctx)) {
        case 1: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(35);

          if (!(precpred(_ctx, 7)))
            throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(36);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop =
              match(metricParser::LSHIFT);
          setState(37);
          logic(8);
          break;
        }

        case 2: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(38);

          if (!(precpred(_ctx, 6)))
            throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(39);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop =
              match(metricParser::RSHIFT);
          setState(40);
          logic(7);
          break;
        }

        case 3: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(41);

          if (!(precpred(_ctx, 5)))
            throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(42);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop =
              match(metricParser::BAND);
          setState(43);
          logic(6);
          break;
        }

        case 4: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(44);

          if (!(precpred(_ctx, 4)))
            throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(45);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop =
              match(metricParser::BXOR);
          setState(46);
          logic(5);
          break;
        }

        case 5: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(47);

          if (!(precpred(_ctx, 3)))
            throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(48);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop =
              match(metricParser::BOR);
          setState(49);
          logic(4);
          break;
        }

        default:
          break;
        }
      }
      setState(54);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input,
                                                                       2, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LogicAtomContext ------------------------------------------------------------------

metricParser::LogicAtomContext::LogicAtomContext(ParserRuleContext *parent,
                                                 size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

metricParser::LogicConstantContext *
metricParser::LogicAtomContext::logicConstant() {
  return getRuleContext<metricParser::LogicConstantContext>(0);
}

metricParser::LogicVariableContext *
metricParser::LogicAtomContext::logicVariable() {
  return getRuleContext<metricParser::LogicVariableContext>(0);
}

size_t metricParser::LogicAtomContext::getRuleIndex() const {
  return metricParser::RuleLogicAtom;
}

void metricParser::LogicAtomContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicAtom(this);
}

void metricParser::LogicAtomContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicAtom(this);
}

metricParser::LogicAtomContext *metricParser::logicAtom() {
  LogicAtomContext *_localctx =
      _tracker.createInstance<LogicAtomContext>(_ctx, getState());
  enterRule(_localctx, 4, metricParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(57);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case metricParser::NUMERIC:
    case metricParser::VERILOG_BINARY:
    case metricParser::GCC_BINARY:
    case metricParser::HEX: {
      enterOuterAlt(_localctx, 1);
      setState(55);
      logicConstant();
      break;
    }

    case metricParser::LT: {
      enterOuterAlt(_localctx, 2);
      setState(56);
      logicVariable();
      break;
    }

    default:
      throw NoViableAltException(this);
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicConstantContext ------------------------------------------------------------------

metricParser::LogicConstantContext::LogicConstantContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *metricParser::LogicConstantContext::VERILOG_BINARY() {
  return getToken(metricParser::VERILOG_BINARY, 0);
}

tree::TerminalNode *metricParser::LogicConstantContext::GCC_BINARY() {
  return getToken(metricParser::GCC_BINARY, 0);
}

tree::TerminalNode *metricParser::LogicConstantContext::NUMERIC() {
  return getToken(metricParser::NUMERIC, 0);
}

tree::TerminalNode *metricParser::LogicConstantContext::HEX() {
  return getToken(metricParser::HEX, 0);
}

size_t metricParser::LogicConstantContext::getRuleIndex() const {
  return metricParser::RuleLogicConstant;
}

void metricParser::LogicConstantContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicConstant(this);
}

void metricParser::LogicConstantContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicConstant(this);
}

metricParser::LogicConstantContext *metricParser::logicConstant() {
  LogicConstantContext *_localctx =
      _tracker.createInstance<LogicConstantContext>(_ctx, getState());
  enterRule(_localctx, 6, metricParser::RuleLogicConstant);
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
    setState(59);
    _la = _input->LA(1);
    if (!((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) & ((1ULL << metricParser::NUMERIC) |
                             (1ULL << metricParser::VERILOG_BINARY) |
                             (1ULL << metricParser::GCC_BINARY) |
                             (1ULL << metricParser::HEX))) != 0))) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicVariableContext ------------------------------------------------------------------

metricParser::LogicVariableContext::LogicVariableContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *metricParser::LogicVariableContext::LT() {
  return getToken(metricParser::LT, 0);
}

metricParser::VariableContext *metricParser::LogicVariableContext::variable() {
  return getRuleContext<metricParser::VariableContext>(0);
}

tree::TerminalNode *metricParser::LogicVariableContext::SIGN() {
  return getToken(metricParser::SIGN, 0);
}

tree::TerminalNode *metricParser::LogicVariableContext::NUMERIC() {
  return getToken(metricParser::NUMERIC, 0);
}

size_t metricParser::LogicVariableContext::getRuleIndex() const {
  return metricParser::RuleLogicVariable;
}

void metricParser::LogicVariableContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicVariable(this);
}

void metricParser::LogicVariableContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicVariable(this);
}

metricParser::LogicVariableContext *metricParser::logicVariable() {
  LogicVariableContext *_localctx =
      _tracker.createInstance<LogicVariableContext>(_ctx, getState());
  enterRule(_localctx, 8, metricParser::RuleLogicVariable);

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
    match(metricParser::LT);
    setState(62);
    variable();
    setState(63);
    match(metricParser::T__0);
    setState(64);
    match(metricParser::SIGN);
    setState(65);
    match(metricParser::T__1);
    setState(66);
    match(metricParser::NUMERIC);
    setState(67);
    match(metricParser::T__2);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericContext ------------------------------------------------------------------

metricParser::NumericContext::NumericContext(ParserRuleContext *parent,
                                             size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

metricParser::NumericAtomContext *metricParser::NumericContext::numericAtom() {
  return getRuleContext<metricParser::NumericAtomContext>(0);
}

metricParser::LogicContext *metricParser::NumericContext::logic() {
  return getRuleContext<metricParser::LogicContext>(0);
}

tree::TerminalNode *metricParser::NumericContext::LPAREN() {
  return getToken(metricParser::LPAREN, 0);
}

std::vector<metricParser::NumericContext *>
metricParser::NumericContext::numeric() {
  return getRuleContexts<metricParser::NumericContext>();
}

metricParser::NumericContext *metricParser::NumericContext::numeric(size_t i) {
  return getRuleContext<metricParser::NumericContext>(i);
}

tree::TerminalNode *metricParser::NumericContext::RPAREN() {
  return getToken(metricParser::RPAREN, 0);
}

tree::TerminalNode *metricParser::NumericContext::TIMES() {
  return getToken(metricParser::TIMES, 0);
}

tree::TerminalNode *metricParser::NumericContext::DIV() {
  return getToken(metricParser::DIV, 0);
}

tree::TerminalNode *metricParser::NumericContext::PLUS() {
  return getToken(metricParser::PLUS, 0);
}

tree::TerminalNode *metricParser::NumericContext::MINUS() {
  return getToken(metricParser::MINUS, 0);
}

size_t metricParser::NumericContext::getRuleIndex() const {
  return metricParser::RuleNumeric;
}

void metricParser::NumericContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void metricParser::NumericContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}

metricParser::NumericContext *metricParser::numeric() { return numeric(0); }

metricParser::NumericContext *metricParser::numeric(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  metricParser::NumericContext *_localctx =
      _tracker.createInstance<NumericContext>(_ctx, parentState);
  metricParser::NumericContext *previousContext = _localctx;
  (void)
      previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, metricParser::RuleNumeric, precedence);

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
    setState(76);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 4, _ctx)) {
    case 1: {
      setState(70);
      numericAtom();
      break;
    }

    case 2: {
      setState(71);
      logic(0);
      break;
    }

    case 3: {
      setState(72);
      match(metricParser::LPAREN);
      setState(73);
      numeric(0);
      setState(74);
      match(metricParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(86);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6,
                                                                     _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(84);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 5, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(78);

          if (!(precpred(_ctx, 5)))
            throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(79);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop =
              _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == metricParser::TIMES

                || _la == metricParser::DIV)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop =
                _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(80);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(81);

          if (!(precpred(_ctx, 4)))
            throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(82);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop =
              _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == metricParser::PLUS

                || _la == metricParser::MINUS)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop =
                _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(83);
          numeric(5);
          break;
        }

        default:
          break;
        }
      }
      setState(88);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input,
                                                                       6, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- NumericAtomContext ------------------------------------------------------------------

metricParser::NumericAtomContext::NumericAtomContext(ParserRuleContext *parent,
                                                     size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

metricParser::NumericConstantContext *
metricParser::NumericAtomContext::numericConstant() {
  return getRuleContext<metricParser::NumericConstantContext>(0);
}

metricParser::NumericVariableContext *
metricParser::NumericAtomContext::numericVariable() {
  return getRuleContext<metricParser::NumericVariableContext>(0);
}

size_t metricParser::NumericAtomContext::getRuleIndex() const {
  return metricParser::RuleNumericAtom;
}

void metricParser::NumericAtomContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericAtom(this);
}

void metricParser::NumericAtomContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericAtom(this);
}

metricParser::NumericAtomContext *metricParser::numericAtom() {
  NumericAtomContext *_localctx =
      _tracker.createInstance<NumericAtomContext>(_ctx, getState());
  enterRule(_localctx, 12, metricParser::RuleNumericAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(91);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case metricParser::NUMERIC: {
      enterOuterAlt(_localctx, 1);
      setState(89);
      numericConstant();
      break;
    }

    case metricParser::LT: {
      enterOuterAlt(_localctx, 2);
      setState(90);
      numericVariable();
      break;
    }

    default:
      throw NoViableAltException(this);
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericConstantContext ------------------------------------------------------------------

metricParser::NumericConstantContext::NumericConstantContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *metricParser::NumericConstantContext::NUMERIC() {
  return getToken(metricParser::NUMERIC, 0);
}

size_t metricParser::NumericConstantContext::getRuleIndex() const {
  return metricParser::RuleNumericConstant;
}

void metricParser::NumericConstantContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericConstant(this);
}

void metricParser::NumericConstantContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericConstant(this);
}

metricParser::NumericConstantContext *metricParser::numericConstant() {
  NumericConstantContext *_localctx =
      _tracker.createInstance<NumericConstantContext>(_ctx, getState());
  enterRule(_localctx, 14, metricParser::RuleNumericConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(93);
    match(metricParser::NUMERIC);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericVariableContext ------------------------------------------------------------------

metricParser::NumericVariableContext::NumericVariableContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *metricParser::NumericVariableContext::LT() {
  return getToken(metricParser::LT, 0);
}

metricParser::VariableContext *
metricParser::NumericVariableContext::variable() {
  return getRuleContext<metricParser::VariableContext>(0);
}

tree::TerminalNode *metricParser::NumericVariableContext::NUMERIC() {
  return getToken(metricParser::NUMERIC, 0);
}

size_t metricParser::NumericVariableContext::getRuleIndex() const {
  return metricParser::RuleNumericVariable;
}

void metricParser::NumericVariableContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericVariable(this);
}

void metricParser::NumericVariableContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericVariable(this);
}

metricParser::NumericVariableContext *metricParser::numericVariable() {
  NumericVariableContext *_localctx =
      _tracker.createInstance<NumericVariableContext>(_ctx, getState());
  enterRule(_localctx, 16, metricParser::RuleNumericVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(95);
    match(metricParser::LT);
    setState(96);
    variable();
    setState(97);
    match(metricParser::T__3);
    setState(98);
    match(metricParser::NUMERIC);
    setState(99);
    match(metricParser::T__2);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

metricParser::VariableContext::VariableContext(ParserRuleContext *parent,
                                               size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *metricParser::VariableContext::VARIABLE() {
  return getToken(metricParser::VARIABLE, 0);
}

size_t metricParser::VariableContext::getRuleIndex() const {
  return metricParser::RuleVariable;
}

void metricParser::VariableContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void metricParser::VariableContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

metricParser::VariableContext *metricParser::variable() {
  VariableContext *_localctx =
      _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 18, metricParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    match(metricParser::VARIABLE);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelopContext ------------------------------------------------------------------

metricParser::RelopContext::RelopContext(ParserRuleContext *parent,
                                         size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *metricParser::RelopContext::GT() {
  return getToken(metricParser::GT, 0);
}

tree::TerminalNode *metricParser::RelopContext::GE() {
  return getToken(metricParser::GE, 0);
}

tree::TerminalNode *metricParser::RelopContext::LT() {
  return getToken(metricParser::LT, 0);
}

tree::TerminalNode *metricParser::RelopContext::LE() {
  return getToken(metricParser::LE, 0);
}

size_t metricParser::RelopContext::getRuleIndex() const {
  return metricParser::RuleRelop;
}

void metricParser::RelopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void metricParser::RelopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<metricListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}

metricParser::RelopContext *metricParser::relop() {
  RelopContext *_localctx =
      _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 20, metricParser::RuleRelop);
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
    setState(103);
    _la = _input->LA(1);
    if (!((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) &
            ((1ULL << metricParser::GT) | (1ULL << metricParser::GE) |
             (1ULL << metricParser::LT) | (1ULL << metricParser::LE))) != 0))) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool metricParser::sempred(RuleContext *context, size_t ruleIndex,
                           size_t predicateIndex) {
  switch (ruleIndex) {
  case 1:
    return logicSempred(antlrcpp::downCast<LogicContext *>(context),
                        predicateIndex);
  case 5:
    return numericSempred(antlrcpp::downCast<NumericContext *>(context),
                          predicateIndex);

  default:
    break;
  }
  return true;
}

bool metricParser::logicSempred(LogicContext *_localctx,
                                size_t predicateIndex) {
  switch (predicateIndex) {
  case 0:
    return precpred(_ctx, 7);
  case 1:
    return precpred(_ctx, 6);
  case 2:
    return precpred(_ctx, 5);
  case 3:
    return precpred(_ctx, 4);
  case 4:
    return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool metricParser::numericSempred(NumericContext *_localctx,
                                  size_t predicateIndex) {
  switch (predicateIndex) {
  case 5:
    return precpred(_ctx, 5);
  case 6:
    return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void metricParser::initialize() {
  std::call_once(metricParserOnceFlag, metricParserInitialize);
}
