
// Generated from metric.g4 by ANTLR 4.9.2

#include "metricListener.h"

#include "metricParser.h"

using namespace antlrcpp;
using namespace antlr4;

metricParser::metricParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA,
                                             _sharedContextCache);
}

metricParser::~metricParser() { delete _interpreter; }

std::string metricParser::getGrammarFileName() const { return "metric.g4"; }

const std::vector<std::string> &metricParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary &metricParser::getVocabulary() const { return _vocabulary; }

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
          dynamic_cast<LogicContext *>(_localctx)->logop =
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
          dynamic_cast<LogicContext *>(_localctx)->logop =
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
          dynamic_cast<LogicContext *>(_localctx)->logop =
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
          dynamic_cast<LogicContext *>(_localctx)->logop =
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
          dynamic_cast<LogicContext *>(_localctx)->logop =
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
          dynamic_cast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == metricParser::TIMES

                || _la == metricParser::DIV)) {
            dynamic_cast<NumericContext *>(_localctx)->artop =
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
          dynamic_cast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == metricParser::PLUS

                || _la == metricParser::MINUS)) {
            dynamic_cast<NumericContext *>(_localctx)->artop =
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
    return logicSempred(dynamic_cast<LogicContext *>(context), predicateIndex);
  case 5:
    return numericSempred(dynamic_cast<NumericContext *>(context),
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

// Static vars and initialization.
std::vector<dfa::DFA> metricParser::_decisionToDFA;
atn::PredictionContextCache metricParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN metricParser::_atn;
std::vector<uint16_t> metricParser::_serializedATN;

std::vector<std::string> metricParser::_ruleNames = {"file",
                                                     "logic",
                                                     "logicAtom",
                                                     "logicConstant",
                                                     "logicVariable",
                                                     "numeric",
                                                     "numericAtom",
                                                     "numericConstant",
                                                     "numericVariable",
                                                     "variable",
                                                     "relop"};

std::vector<std::string> metricParser::_literalNames = {
    "",     "',logic('", "','",  "')>'", "',numeric('",
    "",     "'{'",       "'}'",  "'['",  "']'",
    "'('",  "')'",       "",     "",     "",
    "",     "",          "",     "",     "'+'",
    "'-'",  "'*'",       "'/'",  "'>'",  "'>='",
    "'<'",  "'<='",      "'=='", "'!='", "'&'",
    "'|'",  "'^'",       "'~'",  "'<<'", "'>>'",
    "'&&'", "'||'",      "'!'"};

std::vector<std::string> metricParser::_symbolicNames = {
    "",           "",        "",        "",
    "",           "SIGN",    "LGPAREN", "RGPAREN",
    "LCPAREN",    "RCPAREN", "LPAREN",  "RPAREN",
    "VARIABLE",   "INDEX",   "NUMERIC", "VERILOG_BINARY",
    "GCC_BINARY", "HEX",     "BOOLEAN", "PLUS",
    "MINUS",      "TIMES",   "DIV",     "GT",
    "GE",         "LT",      "LE",      "EQ",
    "NEQ",        "BAND",    "BOR",     "BXOR",
    "NEG",        "LSHIFT",  "RSHIFT",  "AND",
    "OR",         "NOT",     "WS"};

dfa::Vocabulary metricParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> metricParser::_tokenNames;

metricParser::Initializer::Initializer() {
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
      0x3,  0x28,   0x6c,   0x4,    0x2,    0x9,    0x2,    0x4,    0x3,
      0x9,  0x3,    0x4,    0x4,    0x9,    0x4,    0x4,    0x5,    0x9,
      0x5,  0x4,    0x6,    0x9,    0x6,    0x4,    0x7,    0x9,    0x7,
      0x4,  0x8,    0x9,    0x8,    0x4,    0x9,    0x9,    0x9,    0x4,
      0xa,  0x9,    0xa,    0x4,    0xb,    0x9,    0xb,    0x4,    0xc,
      0x9,  0xc,    0x3,    0x2,    0x3,    0x2,    0x3,    0x2,    0x3,
      0x3,  0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,  0x3,    0x3,    0x3,    0x3,    0x3,    0x5,    0x3,    0x24,
      0xa,  0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,  0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,  0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,  0x3,    0x3,    0x3,    0x3,    0x7,    0x3,    0x35,   0xa,
      0x3,  0xc,    0x3,    0xe,    0x3,    0x38,   0xb,    0x3,    0x3,
      0x4,  0x3,    0x4,    0x5,    0x4,    0x3c,   0xa,    0x4,    0x3,
      0x5,  0x3,    0x5,    0x3,    0x6,    0x3,    0x6,    0x3,    0x6,
      0x3,  0x6,    0x3,    0x6,    0x3,    0x6,    0x3,    0x6,    0x3,
      0x6,  0x3,    0x7,    0x3,    0x7,    0x3,    0x7,    0x3,    0x7,
      0x3,  0x7,    0x3,    0x7,    0x3,    0x7,    0x5,    0x7,    0x4f,
      0xa,  0x7,    0x3,    0x7,    0x3,    0x7,    0x3,    0x7,    0x3,
      0x7,  0x3,    0x7,    0x3,    0x7,    0x7,    0x7,    0x57,   0xa,
      0x7,  0xc,    0x7,    0xe,    0x7,    0x5a,   0xb,    0x7,    0x3,
      0x8,  0x3,    0x8,    0x5,    0x8,    0x5e,   0xa,    0x8,    0x3,
      0x9,  0x3,    0x9,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,
      0x3,  0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xb,    0x3,
      0xb,  0x3,    0xc,    0x3,    0xc,    0x3,    0xc,    0x2,    0x4,
      0x4,  0xc,    0xd,    0x2,    0x4,    0x6,    0x8,    0xa,    0xc,
      0xe,  0x10,   0x12,   0x14,   0x16,   0x2,    0x6,    0x3,    0x2,
      0x10, 0x13,   0x3,    0x2,    0x17,   0x18,   0x3,    0x2,    0x15,
      0x16, 0x3,    0x2,    0x19,   0x1c,   0x2,    0x6d,   0x2,    0x18,
      0x3,  0x2,    0x2,    0x2,    0x4,    0x23,   0x3,    0x2,    0x2,
      0x2,  0x6,    0x3b,   0x3,    0x2,    0x2,    0x2,    0x8,    0x3d,
      0x3,  0x2,    0x2,    0x2,    0xa,    0x3f,   0x3,    0x2,    0x2,
      0x2,  0xc,    0x4e,   0x3,    0x2,    0x2,    0x2,    0xe,    0x5d,
      0x3,  0x2,    0x2,    0x2,    0x10,   0x5f,   0x3,    0x2,    0x2,
      0x2,  0x12,   0x61,   0x3,    0x2,    0x2,    0x2,    0x14,   0x67,
      0x3,  0x2,    0x2,    0x2,    0x16,   0x69,   0x3,    0x2,    0x2,
      0x2,  0x18,   0x19,   0x5,    0xc,    0x7,    0x2,    0x19,   0x1a,
      0x7,  0x2,    0x2,    0x3,    0x1a,   0x3,    0x3,    0x2,    0x2,
      0x2,  0x1b,   0x1c,   0x8,    0x3,    0x1,    0x2,    0x1c,   0x1d,
      0x7,  0x22,   0x2,    0x2,    0x1d,   0x24,   0x5,    0x4,    0x3,
      0xa,  0x1e,   0x24,   0x5,    0x6,    0x4,    0x2,    0x1f,   0x20,
      0x7,  0xc,    0x2,    0x2,    0x20,   0x21,   0x5,    0x4,    0x3,
      0x2,  0x21,   0x22,   0x7,    0xd,    0x2,    0x2,    0x22,   0x24,
      0x3,  0x2,    0x2,    0x2,    0x23,   0x1b,   0x3,    0x2,    0x2,
      0x2,  0x23,   0x1e,   0x3,    0x2,    0x2,    0x2,    0x23,   0x1f,
      0x3,  0x2,    0x2,    0x2,    0x24,   0x36,   0x3,    0x2,    0x2,
      0x2,  0x25,   0x26,   0xc,    0x9,    0x2,    0x2,    0x26,   0x27,
      0x7,  0x23,   0x2,    0x2,    0x27,   0x35,   0x5,    0x4,    0x3,
      0xa,  0x28,   0x29,   0xc,    0x8,    0x2,    0x2,    0x29,   0x2a,
      0x7,  0x24,   0x2,    0x2,    0x2a,   0x35,   0x5,    0x4,    0x3,
      0x9,  0x2b,   0x2c,   0xc,    0x7,    0x2,    0x2,    0x2c,   0x2d,
      0x7,  0x1f,   0x2,    0x2,    0x2d,   0x35,   0x5,    0x4,    0x3,
      0x8,  0x2e,   0x2f,   0xc,    0x6,    0x2,    0x2,    0x2f,   0x30,
      0x7,  0x21,   0x2,    0x2,    0x30,   0x35,   0x5,    0x4,    0x3,
      0x7,  0x31,   0x32,   0xc,    0x5,    0x2,    0x2,    0x32,   0x33,
      0x7,  0x20,   0x2,    0x2,    0x33,   0x35,   0x5,    0x4,    0x3,
      0x6,  0x34,   0x25,   0x3,    0x2,    0x2,    0x2,    0x34,   0x28,
      0x3,  0x2,    0x2,    0x2,    0x34,   0x2b,   0x3,    0x2,    0x2,
      0x2,  0x34,   0x2e,   0x3,    0x2,    0x2,    0x2,    0x34,   0x31,
      0x3,  0x2,    0x2,    0x2,    0x35,   0x38,   0x3,    0x2,    0x2,
      0x2,  0x36,   0x34,   0x3,    0x2,    0x2,    0x2,    0x36,   0x37,
      0x3,  0x2,    0x2,    0x2,    0x37,   0x5,    0x3,    0x2,    0x2,
      0x2,  0x38,   0x36,   0x3,    0x2,    0x2,    0x2,    0x39,   0x3c,
      0x5,  0x8,    0x5,    0x2,    0x3a,   0x3c,   0x5,    0xa,    0x6,
      0x2,  0x3b,   0x39,   0x3,    0x2,    0x2,    0x2,    0x3b,   0x3a,
      0x3,  0x2,    0x2,    0x2,    0x3c,   0x7,    0x3,    0x2,    0x2,
      0x2,  0x3d,   0x3e,   0x9,    0x2,    0x2,    0x2,    0x3e,   0x9,
      0x3,  0x2,    0x2,    0x2,    0x3f,   0x40,   0x7,    0x1b,   0x2,
      0x2,  0x40,   0x41,   0x5,    0x14,   0xb,    0x2,    0x41,   0x42,
      0x7,  0x3,    0x2,    0x2,    0x42,   0x43,   0x7,    0x7,    0x2,
      0x2,  0x43,   0x44,   0x7,    0x4,    0x2,    0x2,    0x44,   0x45,
      0x7,  0x10,   0x2,    0x2,    0x45,   0x46,   0x7,    0x5,    0x2,
      0x2,  0x46,   0xb,    0x3,    0x2,    0x2,    0x2,    0x47,   0x48,
      0x8,  0x7,    0x1,    0x2,    0x48,   0x4f,   0x5,    0xe,    0x8,
      0x2,  0x49,   0x4f,   0x5,    0x4,    0x3,    0x2,    0x4a,   0x4b,
      0x7,  0xc,    0x2,    0x2,    0x4b,   0x4c,   0x5,    0xc,    0x7,
      0x2,  0x4c,   0x4d,   0x7,    0xd,    0x2,    0x2,    0x4d,   0x4f,
      0x3,  0x2,    0x2,    0x2,    0x4e,   0x47,   0x3,    0x2,    0x2,
      0x2,  0x4e,   0x49,   0x3,    0x2,    0x2,    0x2,    0x4e,   0x4a,
      0x3,  0x2,    0x2,    0x2,    0x4f,   0x58,   0x3,    0x2,    0x2,
      0x2,  0x50,   0x51,   0xc,    0x7,    0x2,    0x2,    0x51,   0x52,
      0x9,  0x3,    0x2,    0x2,    0x52,   0x57,   0x5,    0xc,    0x7,
      0x8,  0x53,   0x54,   0xc,    0x6,    0x2,    0x2,    0x54,   0x55,
      0x9,  0x4,    0x2,    0x2,    0x55,   0x57,   0x5,    0xc,    0x7,
      0x7,  0x56,   0x50,   0x3,    0x2,    0x2,    0x2,    0x56,   0x53,
      0x3,  0x2,    0x2,    0x2,    0x57,   0x5a,   0x3,    0x2,    0x2,
      0x2,  0x58,   0x56,   0x3,    0x2,    0x2,    0x2,    0x58,   0x59,
      0x3,  0x2,    0x2,    0x2,    0x59,   0xd,    0x3,    0x2,    0x2,
      0x2,  0x5a,   0x58,   0x3,    0x2,    0x2,    0x2,    0x5b,   0x5e,
      0x5,  0x10,   0x9,    0x2,    0x5c,   0x5e,   0x5,    0x12,   0xa,
      0x2,  0x5d,   0x5b,   0x3,    0x2,    0x2,    0x2,    0x5d,   0x5c,
      0x3,  0x2,    0x2,    0x2,    0x5e,   0xf,    0x3,    0x2,    0x2,
      0x2,  0x5f,   0x60,   0x7,    0x10,   0x2,    0x2,    0x60,   0x11,
      0x3,  0x2,    0x2,    0x2,    0x61,   0x62,   0x7,    0x1b,   0x2,
      0x2,  0x62,   0x63,   0x5,    0x14,   0xb,    0x2,    0x63,   0x64,
      0x7,  0x6,    0x2,    0x2,    0x64,   0x65,   0x7,    0x10,   0x2,
      0x2,  0x65,   0x66,   0x7,    0x5,    0x2,    0x2,    0x66,   0x13,
      0x3,  0x2,    0x2,    0x2,    0x67,   0x68,   0x7,    0xe,    0x2,
      0x2,  0x68,   0x15,   0x3,    0x2,    0x2,    0x2,    0x69,   0x6a,
      0x9,  0x5,    0x2,    0x2,    0x6a,   0x17,   0x3,    0x2,    0x2,
      0x2,  0xa,    0x23,   0x34,   0x36,   0x3b,   0x4e,   0x56,   0x58,
      0x5d,
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

metricParser::Initializer metricParser::_init;
