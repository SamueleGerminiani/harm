
// Generated from limits.g4 by ANTLR 4.9.2

#include "limitsListener.h"

#include "limitsParser.h"

using namespace antlrcpp;
using namespace antlr4;

limitsParser::limitsParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA,
                                             _sharedContextCache);
}

limitsParser::~limitsParser() { delete _interpreter; }

std::string limitsParser::getGrammarFileName() const { return "limits.g4"; }

const std::vector<std::string> &limitsParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary &limitsParser::getVocabulary() const { return _vocabulary; }

//----------------- FileContext ------------------------------------------------------------------

limitsParser::FileContext::FileContext(ParserRuleContext *parent,
                                       size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

limitsParser::ParameterContext *limitsParser::FileContext::parameter() {
  return getRuleContext<limitsParser::ParameterContext>(0);
}

tree::TerminalNode *limitsParser::FileContext::EOF() {
  return getToken(limitsParser::EOF, 0);
}

size_t limitsParser::FileContext::getRuleIndex() const {
  return limitsParser::RuleFile;
}

void limitsParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void limitsParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

limitsParser::FileContext *limitsParser::file() {
  FileContext *_localctx =
      _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, limitsParser::RuleFile);

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
    parameter();
    setState(21);
    match(limitsParser::EOF);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterContext ------------------------------------------------------------------

limitsParser::ParameterContext::ParameterContext(ParserRuleContext *parent,
                                                 size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

limitsParser::AtomContext *limitsParser::ParameterContext::atom() {
  return getRuleContext<limitsParser::AtomContext>(0);
}

limitsParser::ParameterContext *limitsParser::ParameterContext::parameter() {
  return getRuleContext<limitsParser::ParameterContext>(0);
}

size_t limitsParser::ParameterContext::getRuleIndex() const {
  return limitsParser::RuleParameter;
}

void limitsParser::ParameterContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter(this);
}

void limitsParser::ParameterContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter(this);
}

limitsParser::ParameterContext *limitsParser::parameter() {
  ParameterContext *_localctx =
      _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 2, limitsParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(28);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(23);
      atom();
      setState(24);
      match(limitsParser::T__0);
      setState(25);
      parameter();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(27);
      atom();
      break;
    }

    default:
      break;
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

limitsParser::AtomContext::AtomContext(ParserRuleContext *parent,
                                       size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

limitsParser::DepContext *limitsParser::AtomContext::dep() {
  return getRuleContext<limitsParser::DepContext>(0);
}

limitsParser::WidthContext *limitsParser::AtomContext::width() {
  return getRuleContext<limitsParser::WidthContext>(0);
}

limitsParser::AllContext *limitsParser::AtomContext::all() {
  return getRuleContext<limitsParser::AllContext>(0);
}

limitsParser::OffsetContext *limitsParser::AtomContext::offset() {
  return getRuleContext<limitsParser::OffsetContext>(0);
}

limitsParser::EffortContext *limitsParser::AtomContext::effort() {
  return getRuleContext<limitsParser::EffortContext>(0);
}

limitsParser::StrategyContext *limitsParser::AtomContext::strategy() {
  return getRuleContext<limitsParser::StrategyContext>(0);
}

limitsParser::NegatedContext *limitsParser::AtomContext::negated() {
  return getRuleContext<limitsParser::NegatedContext>(0);
}

size_t limitsParser::AtomContext::getRuleIndex() const {
  return limitsParser::RuleAtom;
}

void limitsParser::AtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtom(this);
}

void limitsParser::AtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtom(this);
}

limitsParser::AtomContext *limitsParser::atom() {
  AtomContext *_localctx =
      _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 4, limitsParser::RuleAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(37);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(30);
      dep();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(31);
      width();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(32);
      all();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(33);
      offset();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(34);
      effort();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(35);
      strategy();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(36);
      negated();
      break;
    }

    default:
      break;
    }

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DepContext ------------------------------------------------------------------

limitsParser::DepContext::DepContext(ParserRuleContext *parent,
                                     size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *limitsParser::DepContext::NUMERIC() {
  return getToken(limitsParser::NUMERIC, 0);
}

size_t limitsParser::DepContext::getRuleIndex() const {
  return limitsParser::RuleDep;
}

void limitsParser::DepContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDep(this);
}

void limitsParser::DepContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDep(this);
}

limitsParser::DepContext *limitsParser::dep() {
  DepContext *_localctx = _tracker.createInstance<DepContext>(_ctx, getState());
  enterRule(_localctx, 6, limitsParser::RuleDep);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(39);
    match(limitsParser::NUMERIC);
    setState(40);
    match(limitsParser::T__1);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WidthContext ------------------------------------------------------------------

limitsParser::WidthContext::WidthContext(ParserRuleContext *parent,
                                         size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *limitsParser::WidthContext::NUMERIC() {
  return getToken(limitsParser::NUMERIC, 0);
}

size_t limitsParser::WidthContext::getRuleIndex() const {
  return limitsParser::RuleWidth;
}

void limitsParser::WidthContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWidth(this);
}

void limitsParser::WidthContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWidth(this);
}

limitsParser::WidthContext *limitsParser::width() {
  WidthContext *_localctx =
      _tracker.createInstance<WidthContext>(_ctx, getState());
  enterRule(_localctx, 8, limitsParser::RuleWidth);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(42);
    match(limitsParser::NUMERIC);
    setState(43);
    match(limitsParser::T__2);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AllContext ------------------------------------------------------------------

limitsParser::AllContext::AllContext(ParserRuleContext *parent,
                                     size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *limitsParser::AllContext::NUMERIC() {
  return getToken(limitsParser::NUMERIC, 0);
}

size_t limitsParser::AllContext::getRuleIndex() const {
  return limitsParser::RuleAll;
}

void limitsParser::AllContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAll(this);
}

void limitsParser::AllContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAll(this);
}

limitsParser::AllContext *limitsParser::all() {
  AllContext *_localctx = _tracker.createInstance<AllContext>(_ctx, getState());
  enterRule(_localctx, 10, limitsParser::RuleAll);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(45);
    match(limitsParser::NUMERIC);
    setState(46);
    match(limitsParser::T__3);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OffsetContext ------------------------------------------------------------------

limitsParser::OffsetContext::OffsetContext(ParserRuleContext *parent,
                                           size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *limitsParser::OffsetContext::NOT() {
  return getToken(limitsParser::NOT, 0);
}

size_t limitsParser::OffsetContext::getRuleIndex() const {
  return limitsParser::RuleOffset;
}

void limitsParser::OffsetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOffset(this);
}

void limitsParser::OffsetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOffset(this);
}

limitsParser::OffsetContext *limitsParser::offset() {
  OffsetContext *_localctx =
      _tracker.createInstance<OffsetContext>(_ctx, getState());
  enterRule(_localctx, 12, limitsParser::RuleOffset);
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
    setState(49);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == limitsParser::NOT) {
      setState(48);
      match(limitsParser::NOT);
    }
    setState(51);
    match(limitsParser::T__4);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NegatedContext ------------------------------------------------------------------

limitsParser::NegatedContext::NegatedContext(ParserRuleContext *parent,
                                             size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *limitsParser::NegatedContext::NOT() {
  return getToken(limitsParser::NOT, 0);
}

size_t limitsParser::NegatedContext::getRuleIndex() const {
  return limitsParser::RuleNegated;
}

void limitsParser::NegatedContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNegated(this);
}

void limitsParser::NegatedContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNegated(this);
}

limitsParser::NegatedContext *limitsParser::negated() {
  NegatedContext *_localctx =
      _tracker.createInstance<NegatedContext>(_ctx, getState());
  enterRule(_localctx, 14, limitsParser::RuleNegated);
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
    setState(54);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == limitsParser::NOT) {
      setState(53);
      match(limitsParser::NOT);
    }
    setState(56);
    match(limitsParser::T__5);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EffortContext ------------------------------------------------------------------

limitsParser::EffortContext::EffortContext(ParserRuleContext *parent,
                                           size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *limitsParser::EffortContext::NUMERIC() {
  return getToken(limitsParser::NUMERIC, 0);
}

size_t limitsParser::EffortContext::getRuleIndex() const {
  return limitsParser::RuleEffort;
}

void limitsParser::EffortContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEffort(this);
}

void limitsParser::EffortContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEffort(this);
}

limitsParser::EffortContext *limitsParser::effort() {
  EffortContext *_localctx =
      _tracker.createInstance<EffortContext>(_ctx, getState());
  enterRule(_localctx, 16, limitsParser::RuleEffort);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    match(limitsParser::NUMERIC);
    setState(59);
    match(limitsParser::T__6);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StrategyContext ------------------------------------------------------------------

limitsParser::StrategyContext::StrategyContext(ParserRuleContext *parent,
                                               size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *limitsParser::StrategyContext::SEQ() {
  return getToken(limitsParser::SEQ, 0);
}

tree::TerminalNode *limitsParser::StrategyContext::RAN() {
  return getToken(limitsParser::RAN, 0);
}

size_t limitsParser::StrategyContext::getRuleIndex() const {
  return limitsParser::RuleStrategy;
}

void limitsParser::StrategyContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStrategy(this);
}

void limitsParser::StrategyContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<limitsListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStrategy(this);
}

limitsParser::StrategyContext *limitsParser::strategy() {
  StrategyContext *_localctx =
      _tracker.createInstance<StrategyContext>(_ctx, getState());
  enterRule(_localctx, 18, limitsParser::RuleStrategy);
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
    setState(61);
    _la = _input->LA(1);
    if (!(_la == limitsParser::SEQ

          || _la == limitsParser::RAN)) {
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

// Static vars and initialization.
std::vector<dfa::DFA> limitsParser::_decisionToDFA;
atn::PredictionContextCache limitsParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN limitsParser::_atn;
std::vector<uint16_t> limitsParser::_serializedATN;

std::vector<std::string> limitsParser::_ruleNames = {
    "file", "parameter", "atom",    "dep",    "width",
    "all",  "offset",    "negated", "effort", "strategy"};

std::vector<std::string> limitsParser::_literalNames = {
    "", "','", "'D'", "'W'", "'A'", "'O'", "'N'", "'E'", "'S'", "'R'", "'!'"};

std::vector<std::string> limitsParser::_symbolicNames = {
    "", "", "", "", "", "", "", "", "SEQ", "RAN", "NOT", "NUMERIC", "WS"};

dfa::Vocabulary limitsParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> limitsParser::_tokenNames;

limitsParser::Initializer::Initializer() {
  for (size_t i = 0; i < _symbolicNames.size(); ++i) {
    std::string name = _vocabulary.getLiteralName(i);
    if (name.empty()) {
      name = _vocabulary.getSymbolicName(i);
    }

    if (name.empty()) {
      _tokenNames.push_back("<INVALID>");
    } else {
      _tokenNames.push_back(name);
    }
  }

  static const uint16_t serializedATNSegment0[] = {
      0x3,  0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964,
      0x3,  0xe,    0x42,   0x4,    0x2,    0x9,    0x2,    0x4,    0x3,
      0x9,  0x3,    0x4,    0x4,    0x9,    0x4,    0x4,    0x5,    0x9,
      0x5,  0x4,    0x6,    0x9,    0x6,    0x4,    0x7,    0x9,    0x7,
      0x4,  0x8,    0x9,    0x8,    0x4,    0x9,    0x9,    0x9,    0x4,
      0xa,  0x9,    0xa,    0x4,    0xb,    0x9,    0xb,    0x3,    0x2,
      0x3,  0x2,    0x3,    0x2,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,  0x3,    0x3,    0x3,    0x3,    0x5,    0x3,    0x1f,   0xa,
      0x3,  0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,
      0x3,  0x4,    0x3,    0x4,    0x3,    0x4,    0x5,    0x4,    0x28,
      0xa,  0x4,    0x3,    0x5,    0x3,    0x5,    0x3,    0x5,    0x3,
      0x6,  0x3,    0x6,    0x3,    0x6,    0x3,    0x7,    0x3,    0x7,
      0x3,  0x7,    0x3,    0x8,    0x5,    0x8,    0x34,   0xa,    0x8,
      0x3,  0x8,    0x3,    0x8,    0x3,    0x9,    0x5,    0x9,    0x39,
      0xa,  0x9,    0x3,    0x9,    0x3,    0x9,    0x3,    0xa,    0x3,
      0xa,  0x3,    0xa,    0x3,    0xb,    0x3,    0xb,    0x3,    0xb,
      0x2,  0x2,    0xc,    0x2,    0x4,    0x6,    0x8,    0xa,    0xc,
      0xe,  0x10,   0x12,   0x14,   0x2,    0x3,    0x3,    0x2,    0xa,
      0xb,  0x2,    0x40,   0x2,    0x16,   0x3,    0x2,    0x2,    0x2,
      0x4,  0x1e,   0x3,    0x2,    0x2,    0x2,    0x6,    0x27,   0x3,
      0x2,  0x2,    0x2,    0x8,    0x29,   0x3,    0x2,    0x2,    0x2,
      0xa,  0x2c,   0x3,    0x2,    0x2,    0x2,    0xc,    0x2f,   0x3,
      0x2,  0x2,    0x2,    0xe,    0x33,   0x3,    0x2,    0x2,    0x2,
      0x10, 0x38,   0x3,    0x2,    0x2,    0x2,    0x12,   0x3c,   0x3,
      0x2,  0x2,    0x2,    0x14,   0x3f,   0x3,    0x2,    0x2,    0x2,
      0x16, 0x17,   0x5,    0x4,    0x3,    0x2,    0x17,   0x18,   0x7,
      0x2,  0x2,    0x3,    0x18,   0x3,    0x3,    0x2,    0x2,    0x2,
      0x19, 0x1a,   0x5,    0x6,    0x4,    0x2,    0x1a,   0x1b,   0x7,
      0x3,  0x2,    0x2,    0x1b,   0x1c,   0x5,    0x4,    0x3,    0x2,
      0x1c, 0x1f,   0x3,    0x2,    0x2,    0x2,    0x1d,   0x1f,   0x5,
      0x6,  0x4,    0x2,    0x1e,   0x19,   0x3,    0x2,    0x2,    0x2,
      0x1e, 0x1d,   0x3,    0x2,    0x2,    0x2,    0x1f,   0x5,    0x3,
      0x2,  0x2,    0x2,    0x20,   0x28,   0x5,    0x8,    0x5,    0x2,
      0x21, 0x28,   0x5,    0xa,    0x6,    0x2,    0x22,   0x28,   0x5,
      0xc,  0x7,    0x2,    0x23,   0x28,   0x5,    0xe,    0x8,    0x2,
      0x24, 0x28,   0x5,    0x12,   0xa,    0x2,    0x25,   0x28,   0x5,
      0x14, 0xb,    0x2,    0x26,   0x28,   0x5,    0x10,   0x9,    0x2,
      0x27, 0x20,   0x3,    0x2,    0x2,    0x2,    0x27,   0x21,   0x3,
      0x2,  0x2,    0x2,    0x27,   0x22,   0x3,    0x2,    0x2,    0x2,
      0x27, 0x23,   0x3,    0x2,    0x2,    0x2,    0x27,   0x24,   0x3,
      0x2,  0x2,    0x2,    0x27,   0x25,   0x3,    0x2,    0x2,    0x2,
      0x27, 0x26,   0x3,    0x2,    0x2,    0x2,    0x28,   0x7,    0x3,
      0x2,  0x2,    0x2,    0x29,   0x2a,   0x7,    0xd,    0x2,    0x2,
      0x2a, 0x2b,   0x7,    0x4,    0x2,    0x2,    0x2b,   0x9,    0x3,
      0x2,  0x2,    0x2,    0x2c,   0x2d,   0x7,    0xd,    0x2,    0x2,
      0x2d, 0x2e,   0x7,    0x5,    0x2,    0x2,    0x2e,   0xb,    0x3,
      0x2,  0x2,    0x2,    0x2f,   0x30,   0x7,    0xd,    0x2,    0x2,
      0x30, 0x31,   0x7,    0x6,    0x2,    0x2,    0x31,   0xd,    0x3,
      0x2,  0x2,    0x2,    0x32,   0x34,   0x7,    0xc,    0x2,    0x2,
      0x33, 0x32,   0x3,    0x2,    0x2,    0x2,    0x33,   0x34,   0x3,
      0x2,  0x2,    0x2,    0x34,   0x35,   0x3,    0x2,    0x2,    0x2,
      0x35, 0x36,   0x7,    0x7,    0x2,    0x2,    0x36,   0xf,    0x3,
      0x2,  0x2,    0x2,    0x37,   0x39,   0x7,    0xc,    0x2,    0x2,
      0x38, 0x37,   0x3,    0x2,    0x2,    0x2,    0x38,   0x39,   0x3,
      0x2,  0x2,    0x2,    0x39,   0x3a,   0x3,    0x2,    0x2,    0x2,
      0x3a, 0x3b,   0x7,    0x8,    0x2,    0x2,    0x3b,   0x11,   0x3,
      0x2,  0x2,    0x2,    0x3c,   0x3d,   0x7,    0xd,    0x2,    0x2,
      0x3d, 0x3e,   0x7,    0x9,    0x2,    0x2,    0x3e,   0x13,   0x3,
      0x2,  0x2,    0x2,    0x3f,   0x40,   0x9,    0x2,    0x2,    0x2,
      0x40, 0x15,   0x3,    0x2,    0x2,    0x2,    0x6,    0x1e,   0x27,
      0x33, 0x38,
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
                        serializedATNSegment0 +
                            sizeof(serializedATNSegment0) /
                                sizeof(serializedATNSegment0[0]));

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) {
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

limitsParser::Initializer limitsParser::_init;
