
// Generated from spot.g4 by ANTLR 4.9.2

#include "spotListener.h"

#include "spotParser.h"

using namespace antlrcpp;
using namespace antlr4;

spotParser::spotParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA,
                                             _sharedContextCache);
}

spotParser::~spotParser() { delete _interpreter; }

std::string spotParser::getGrammarFileName() const { return "spot.g4"; }

const std::vector<std::string> &spotParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary &spotParser::getVocabulary() const { return _vocabulary; }

//----------------- FileContext ------------------------------------------------------------------

spotParser::FileContext::FileContext(ParserRuleContext *parent,
                                     size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::FileContext::ALWAYS() {
  return getToken(spotParser::ALWAYS, 0);
}

spotParser::FormulaContext *spotParser::FileContext::formula() {
  return getRuleContext<spotParser::FormulaContext>(0);
}

tree::TerminalNode *spotParser::FileContext::EOF() {
  return getToken(spotParser::EOF, 0);
}

tree::TerminalNode *spotParser::FileContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

tree::TerminalNode *spotParser::FileContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
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

spotParser::FileContext *spotParser::file() {
  FileContext *_localctx =
      _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, spotParser::RuleFile);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(46);
      match(spotParser::ALWAYS);
      setState(47);
      formula();
      setState(48);
      match(spotParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(50);
      match(spotParser::ALWAYS);
      setState(51);
      match(spotParser::LPAREN);
      setState(52);
      formula();
      setState(53);
      match(spotParser::RPAREN);
      setState(54);
      match(spotParser::EOF);
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

//----------------- FormulaContext ------------------------------------------------------------------

spotParser::FormulaContext::FormulaContext(ParserRuleContext *parent,
                                           size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<spotParser::TformulaContext *>
spotParser::FormulaContext::tformula() {
  return getRuleContexts<spotParser::TformulaContext>();
}

spotParser::TformulaContext *spotParser::FormulaContext::tformula(size_t i) {
  return getRuleContext<spotParser::TformulaContext>(i);
}

tree::TerminalNode *spotParser::FormulaContext::IMPL() {
  return getToken(spotParser::IMPL, 0);
}

tree::TerminalNode *spotParser::FormulaContext::IMPL2() {
  return getToken(spotParser::IMPL2, 0);
}

tree::TerminalNode *spotParser::FormulaContext::LGPAREN() {
  return getToken(spotParser::LGPAREN, 0);
}

spotParser::SereContext *spotParser::FormulaContext::sere() {
  return getRuleContext<spotParser::SereContext>(0);
}

tree::TerminalNode *spotParser::FormulaContext::RGPAREN() {
  return getToken(spotParser::RGPAREN, 0);
}

tree::TerminalNode *spotParser::FormulaContext::LCPAREN() {
  return getToken(spotParser::LCPAREN, 0);
}

tree::TerminalNode *spotParser::FormulaContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

tree::TerminalNode *spotParser::FormulaContext::BIND1() {
  return getToken(spotParser::BIND1, 0);
}

tree::TerminalNode *spotParser::FormulaContext::BIND2() {
  return getToken(spotParser::BIND2, 0);
}

tree::TerminalNode *spotParser::FormulaContext::SEREIMPL1() {
  return getToken(spotParser::SEREIMPL1, 0);
}

tree::TerminalNode *spotParser::FormulaContext::SEREIMPL2() {
  return getToken(spotParser::SEREIMPL2, 0);
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

spotParser::FormulaContext *spotParser::formula() {
  FormulaContext *_localctx =
      _tracker.createInstance<FormulaContext>(_ctx, getState());
  enterRule(_localctx, 2, spotParser::RuleFormula);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(106);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(58);
      tformula(0);
      setState(59);
      match(spotParser::IMPL);
      setState(60);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(62);
      tformula(0);
      setState(63);
      match(spotParser::IMPL2);
      setState(64);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(66);
      match(spotParser::LGPAREN);
      setState(67);
      sere(0);
      setState(68);
      match(spotParser::RGPAREN);
      setState(69);
      match(spotParser::LCPAREN);
      setState(70);
      match(spotParser::RCPAREN);
      setState(71);
      match(spotParser::IMPL);
      setState(72);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(74);
      match(spotParser::LGPAREN);
      setState(75);
      sere(0);
      setState(76);
      match(spotParser::RGPAREN);
      setState(77);
      match(spotParser::LCPAREN);
      setState(78);
      match(spotParser::RCPAREN);
      setState(79);
      match(spotParser::IMPL2);
      setState(80);
      tformula(0);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(82);
      match(spotParser::LGPAREN);
      setState(83);
      sere(0);
      setState(84);
      match(spotParser::RGPAREN);
      setState(85);
      match(spotParser::BIND1);
      setState(86);
      tformula(0);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(88);
      match(spotParser::LGPAREN);
      setState(89);
      sere(0);
      setState(90);
      match(spotParser::RGPAREN);
      setState(91);
      match(spotParser::BIND2);
      setState(92);
      tformula(0);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(94);
      match(spotParser::LGPAREN);
      setState(95);
      sere(0);
      setState(96);
      match(spotParser::RGPAREN);
      setState(97);
      match(spotParser::SEREIMPL1);
      setState(98);
      tformula(0);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(100);
      match(spotParser::LGPAREN);
      setState(101);
      sere(0);
      setState(102);
      match(spotParser::RGPAREN);
      setState(103);
      match(spotParser::SEREIMPL2);
      setState(104);
      tformula(0);
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

//----------------- SereContext ------------------------------------------------------------------

spotParser::SereContext::SereContext(ParserRuleContext *parent,
                                     size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

spotParser::BooleanContext *spotParser::SereContext::boolean() {
  return getRuleContext<spotParser::BooleanContext>(0);
}

spotParser::PlaceholderContext *spotParser::SereContext::placeholder() {
  return getRuleContext<spotParser::PlaceholderContext>(0);
}

tree::TerminalNode *spotParser::SereContext::NOT() {
  return getToken(spotParser::NOT, 0);
}

tree::TerminalNode *spotParser::SereContext::DT_AND() {
  return getToken(spotParser::DT_AND, 0);
}

tree::TerminalNode *spotParser::SereContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

std::vector<spotParser::SereContext *> spotParser::SereContext::sere() {
  return getRuleContexts<spotParser::SereContext>();
}

spotParser::SereContext *spotParser::SereContext::sere(size_t i) {
  return getRuleContext<spotParser::SereContext>(i);
}

tree::TerminalNode *spotParser::SereContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode *spotParser::SereContext::LGPAREN() {
  return getToken(spotParser::LGPAREN, 0);
}

tree::TerminalNode *spotParser::SereContext::RGPAREN() {
  return getToken(spotParser::RGPAREN, 0);
}

tree::TerminalNode *spotParser::SereContext::DELAY() {
  return getToken(spotParser::DELAY, 0);
}

std::vector<tree::TerminalNode *> spotParser::SereContext::NUMERIC() {
  return getTokens(spotParser::NUMERIC);
}

tree::TerminalNode *spotParser::SereContext::NUMERIC(size_t i) {
  return getToken(spotParser::NUMERIC, i);
}

tree::TerminalNode *spotParser::SereContext::LCPAREN() {
  return getToken(spotParser::LCPAREN, 0);
}

tree::TerminalNode *spotParser::SereContext::DOTS() {
  return getToken(spotParser::DOTS, 0);
}

tree::TerminalNode *spotParser::SereContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

spotParser::Dt_nextContext *spotParser::SereContext::dt_next() {
  return getRuleContext<spotParser::Dt_nextContext>(0);
}

spotParser::Dt_next_andContext *spotParser::SereContext::dt_next_and() {
  return getRuleContext<spotParser::Dt_next_andContext>(0);
}

spotParser::Dt_NCRepsContext *spotParser::SereContext::dt_NCReps() {
  return getRuleContext<spotParser::Dt_NCRepsContext>(0);
}

tree::TerminalNode *spotParser::SereContext::BOR() {
  return getToken(spotParser::BOR, 0);
}

tree::TerminalNode *spotParser::SereContext::BAND() {
  return getToken(spotParser::BAND, 0);
}

tree::TerminalNode *spotParser::SereContext::AND() {
  return getToken(spotParser::AND, 0);
}

tree::TerminalNode *spotParser::SereContext::SCOL() {
  return getToken(spotParser::SCOL, 0);
}

tree::TerminalNode *spotParser::SereContext::COL() {
  return getToken(spotParser::COL, 0);
}

tree::TerminalNode *spotParser::SereContext::TIMES() {
  return getToken(spotParser::TIMES, 0);
}

tree::TerminalNode *spotParser::SereContext::PLUS() {
  return getToken(spotParser::PLUS, 0);
}

tree::TerminalNode *spotParser::SereContext::ASS() {
  return getToken(spotParser::ASS, 0);
}

tree::TerminalNode *spotParser::SereContext::IMPL() {
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

spotParser::SereContext *spotParser::sere() { return sere(0); }

spotParser::SereContext *spotParser::sere(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  spotParser::SereContext *_localctx =
      _tracker.createInstance<SereContext>(_ctx, parentState);
  spotParser::SereContext *previousContext = _localctx;
  (void)
      previousContext; // Silence compiler, in case the context is not used by generated code.
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
    setState(141);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 7, _ctx)) {
    case 1: {
      setState(109);
      boolean(0);
      break;
    }

    case 2: {
      setState(111);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::NOT) {
        setState(110);
        match(spotParser::NOT);
      }
      setState(113);
      placeholder();
      break;
    }

    case 3: {
      setState(114);
      match(spotParser::DT_AND);
      break;
    }

    case 4: {
      setState(115);
      match(spotParser::LPAREN);
      setState(116);
      sere(0);
      setState(117);
      match(spotParser::RPAREN);
      break;
    }

    case 5: {
      setState(119);
      match(spotParser::LGPAREN);
      setState(120);
      sere(0);
      setState(121);
      match(spotParser::RGPAREN);
      break;
    }

    case 6: {
      setState(123);
      match(spotParser::DELAY);
      setState(125);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::LCPAREN) {
        setState(124);
        match(spotParser::LCPAREN);
      }
      setState(127);
      match(spotParser::NUMERIC);
      setState(129);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::DOTS) {
        setState(128);
        match(spotParser::DOTS);
      }
      setState(132);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 5, _ctx)) {
      case 1: {
        setState(131);
        match(spotParser::NUMERIC);
        break;
      }

      default:
        break;
      }
      setState(135);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == spotParser::RCPAREN) {
        setState(134);
        match(spotParser::RCPAREN);
      }
      setState(137);
      sere(5);
      break;
    }

    case 7: {
      setState(138);
      dt_next();
      break;
    }

    case 8: {
      setState(139);
      dt_next_and();
      break;
    }

    case 9: {
      setState(140);
      dt_NCReps();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(217);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21,
                                                                     _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(215);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 20, _ctx)) {
        case 1: {
          _localctx =
              _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(143);

          if (!(precpred(_ctx, 14)))
            throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(144);
          match(spotParser::BOR);
          setState(145);
          sere(15);
          break;
        }

        case 2: {
          _localctx =
              _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(146);

          if (!(precpred(_ctx, 13)))
            throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(147);
          match(spotParser::BAND);
          setState(148);
          sere(14);
          break;
        }

        case 3: {
          _localctx =
              _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(149);

          if (!(precpred(_ctx, 12)))
            throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(150);
          match(spotParser::AND);
          setState(151);
          sere(13);
          break;
        }

        case 4: {
          _localctx =
              _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(152);

          if (!(precpred(_ctx, 11)))
            throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(153);
          match(spotParser::SCOL);
          setState(154);
          sere(12);
          break;
        }

        case 5: {
          _localctx =
              _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(155);

          if (!(precpred(_ctx, 10)))
            throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(156);
          match(spotParser::COL);
          setState(157);
          sere(11);
          break;
        }

        case 6: {
          _localctx =
              _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(158);

          if (!(precpred(_ctx, 4)))
            throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(159);
          match(spotParser::DELAY);
          setState(161);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::LCPAREN) {
            setState(160);
            match(spotParser::LCPAREN);
          }
          setState(164);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
              _input, 9, _ctx)) {
          case 1: {
            setState(163);
            match(spotParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(167);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(166);
            match(spotParser::DOTS);
          }
          setState(170);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
              _input, 11, _ctx)) {
          case 1: {
            setState(169);
            match(spotParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(173);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::RCPAREN) {
            setState(172);
            match(spotParser::RCPAREN);
          }
          setState(175);
          sere(5);
          break;
        }

        case 7: {
          _localctx =
              _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(176);

          if (!(precpred(_ctx, 9)))
            throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(177);
          match(spotParser::LCPAREN);
          setState(178);
          match(spotParser::TIMES);
          setState(180);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
              _input, 13, _ctx)) {
          case 1: {
            setState(179);
            match(spotParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(183);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(182);
            match(spotParser::DOTS);
          }
          setState(186);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::NUMERIC) {
            setState(185);
            match(spotParser::NUMERIC);
          }
          setState(188);
          match(spotParser::RCPAREN);
          break;
        }

        case 8: {
          _localctx =
              _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(189);

          if (!(precpred(_ctx, 8)))
            throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(190);
          match(spotParser::LCPAREN);
          setState(191);
          match(spotParser::PLUS);
          setState(192);
          match(spotParser::RCPAREN);
          break;
        }

        case 9: {
          _localctx =
              _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(193);

          if (!(precpred(_ctx, 7)))
            throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(194);
          match(spotParser::LCPAREN);
          setState(195);
          match(spotParser::ASS);
          setState(196);
          match(spotParser::NUMERIC);
          setState(198);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(197);
            match(spotParser::DOTS);
          }
          setState(201);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::NUMERIC) {
            setState(200);
            match(spotParser::NUMERIC);
          }
          setState(203);
          match(spotParser::RCPAREN);
          break;
        }

        case 10: {
          _localctx =
              _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(204);

          if (!(precpred(_ctx, 6)))
            throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(205);
          match(spotParser::LCPAREN);
          setState(206);
          match(spotParser::IMPL);
          setState(207);
          match(spotParser::NUMERIC);
          setState(209);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::DOTS) {
            setState(208);
            match(spotParser::DOTS);
          }
          setState(212);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == spotParser::NUMERIC) {
            setState(211);
            match(spotParser::NUMERIC);
          }
          setState(214);
          match(spotParser::RCPAREN);
          break;
        }

        default:
          break;
        }
      }
      setState(219);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 21, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TformulaContext ------------------------------------------------------------------

spotParser::TformulaContext::TformulaContext(ParserRuleContext *parent,
                                             size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

spotParser::BooleanContext *spotParser::TformulaContext::boolean() {
  return getRuleContext<spotParser::BooleanContext>(0);
}

spotParser::PlaceholderContext *spotParser::TformulaContext::placeholder() {
  return getRuleContext<spotParser::PlaceholderContext>(0);
}

tree::TerminalNode *spotParser::TformulaContext::DT_AND() {
  return getToken(spotParser::DT_AND, 0);
}

tree::TerminalNode *spotParser::TformulaContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

std::vector<spotParser::TformulaContext *>
spotParser::TformulaContext::tformula() {
  return getRuleContexts<spotParser::TformulaContext>();
}

spotParser::TformulaContext *spotParser::TformulaContext::tformula(size_t i) {
  return getRuleContext<spotParser::TformulaContext>(i);
}

tree::TerminalNode *spotParser::TformulaContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode *spotParser::TformulaContext::NOT() {
  return getToken(spotParser::NOT, 0);
}

tree::TerminalNode *spotParser::TformulaContext::NEXT() {
  return getToken(spotParser::NEXT, 0);
}

tree::TerminalNode *spotParser::TformulaContext::LCPAREN() {
  return getToken(spotParser::LCPAREN, 0);
}

tree::TerminalNode *spotParser::TformulaContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

tree::TerminalNode *spotParser::TformulaContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

tree::TerminalNode *spotParser::TformulaContext::LGPAREN() {
  return getToken(spotParser::LGPAREN, 0);
}

spotParser::SereContext *spotParser::TformulaContext::sere() {
  return getRuleContext<spotParser::SereContext>(0);
}

tree::TerminalNode *spotParser::TformulaContext::RGPAREN() {
  return getToken(spotParser::RGPAREN, 0);
}

tree::TerminalNode *spotParser::TformulaContext::AND() {
  return getToken(spotParser::AND, 0);
}

tree::TerminalNode *spotParser::TformulaContext::OR() {
  return getToken(spotParser::OR, 0);
}

tree::TerminalNode *spotParser::TformulaContext::XOR() {
  return getToken(spotParser::XOR, 0);
}

tree::TerminalNode *spotParser::TformulaContext::UNTIL() {
  return getToken(spotParser::UNTIL, 0);
}

tree::TerminalNode *spotParser::TformulaContext::RELEASE() {
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

spotParser::TformulaContext *spotParser::tformula() { return tformula(0); }

spotParser::TformulaContext *spotParser::tformula(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  spotParser::TformulaContext *_localctx =
      _tracker.createInstance<TformulaContext>(_ctx, parentState);
  spotParser::TformulaContext *previousContext = _localctx;
  (void)
      previousContext; // Silence compiler, in case the context is not used by generated code.
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
    setState(241);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 22, _ctx)) {
    case 1: {
      setState(221);
      boolean(0);
      break;
    }

    case 2: {
      setState(222);
      placeholder();
      break;
    }

    case 3: {
      setState(223);
      match(spotParser::DT_AND);
      break;
    }

    case 4: {
      setState(224);
      match(spotParser::LPAREN);
      setState(225);
      tformula(0);
      setState(226);
      match(spotParser::RPAREN);
      break;
    }

    case 5: {
      setState(228);
      match(spotParser::NOT);
      setState(229);
      tformula(9);
      break;
    }

    case 6: {
      setState(230);
      match(spotParser::NEXT);
      setState(231);
      match(spotParser::LCPAREN);
      setState(232);
      match(spotParser::NUMERIC);
      setState(233);
      match(spotParser::RCPAREN);
      setState(234);
      tformula(3);
      break;
    }

    case 7: {
      setState(235);
      match(spotParser::NEXT);
      setState(236);
      tformula(2);
      break;
    }

    case 8: {
      setState(237);
      match(spotParser::LGPAREN);
      setState(238);
      sere(0);
      setState(239);
      match(spotParser::RGPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(260);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24,
                                                                     _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(258);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 23, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext,
                                                               parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(243);

          if (!(precpred(_ctx, 8)))
            throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(244);
          match(spotParser::AND);
          setState(245);
          tformula(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext,
                                                               parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(246);

          if (!(precpred(_ctx, 7)))
            throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(247);
          match(spotParser::OR);
          setState(248);
          tformula(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext,
                                                               parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(249);

          if (!(precpred(_ctx, 6)))
            throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(250);
          match(spotParser::XOR);
          setState(251);
          tformula(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext,
                                                               parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(252);

          if (!(precpred(_ctx, 5)))
            throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(253);
          match(spotParser::UNTIL);
          setState(254);
          tformula(6);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext,
                                                               parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(255);

          if (!(precpred(_ctx, 4)))
            throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(256);
          match(spotParser::RELEASE);
          setState(257);
          tformula(5);
          break;
        }

        default:
          break;
        }
      }
      setState(262);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 24, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PlaceholderContext ------------------------------------------------------------------

spotParser::PlaceholderContext::PlaceholderContext(ParserRuleContext *parent,
                                                   size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::PlaceholderContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

size_t spotParser::PlaceholderContext::getRuleIndex() const {
  return spotParser::RulePlaceholder;
}

void spotParser::PlaceholderContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlaceholder(this);
}

void spotParser::PlaceholderContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlaceholder(this);
}

spotParser::PlaceholderContext *spotParser::placeholder() {
  PlaceholderContext *_localctx =
      _tracker.createInstance<PlaceholderContext>(_ctx, getState());
  enterRule(_localctx, 8, spotParser::RulePlaceholder);

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
    match(spotParser::T__0);
    setState(264);
    match(spotParser::NUMERIC);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_nextContext ------------------------------------------------------------------

spotParser::Dt_nextContext::Dt_nextContext(ParserRuleContext *parent,
                                           size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::Dt_nextContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

tree::TerminalNode *spotParser::Dt_nextContext::DOTS() {
  return getToken(spotParser::DOTS, 0);
}

size_t spotParser::Dt_nextContext::getRuleIndex() const {
  return spotParser::RuleDt_next;
}

void spotParser::Dt_nextContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_next(this);
}

void spotParser::Dt_nextContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_next(this);
}

spotParser::Dt_nextContext *spotParser::dt_next() {
  Dt_nextContext *_localctx =
      _tracker.createInstance<Dt_nextContext>(_ctx, getState());
  enterRule(_localctx, 10, spotParser::RuleDt_next);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(266);
    match(spotParser::T__1);
    setState(267);
    match(spotParser::NUMERIC);
    setState(268);
    match(spotParser::DOTS);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_next_andContext ------------------------------------------------------------------

spotParser::Dt_next_andContext::Dt_next_andContext(ParserRuleContext *parent,
                                                   size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::Dt_next_andContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

tree::TerminalNode *spotParser::Dt_next_andContext::BAND() {
  return getToken(spotParser::BAND, 0);
}

tree::TerminalNode *spotParser::Dt_next_andContext::DOTS() {
  return getToken(spotParser::DOTS, 0);
}

size_t spotParser::Dt_next_andContext::getRuleIndex() const {
  return spotParser::RuleDt_next_and;
}

void spotParser::Dt_next_andContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_next_and(this);
}

void spotParser::Dt_next_andContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_next_and(this);
}

spotParser::Dt_next_andContext *spotParser::dt_next_and() {
  Dt_next_andContext *_localctx =
      _tracker.createInstance<Dt_next_andContext>(_ctx, getState());
  enterRule(_localctx, 12, spotParser::RuleDt_next_and);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(270);
    match(spotParser::T__2);
    setState(271);
    match(spotParser::NUMERIC);
    setState(272);
    match(spotParser::BAND);
    setState(273);
    match(spotParser::DOTS);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Dt_NCRepsContext ------------------------------------------------------------------

spotParser::Dt_NCRepsContext::Dt_NCRepsContext(ParserRuleContext *parent,
                                               size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::Dt_NCRepsContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

tree::TerminalNode *spotParser::Dt_NCRepsContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

tree::TerminalNode *spotParser::Dt_NCRepsContext::SEP() {
  return getToken(spotParser::SEP, 0);
}

tree::TerminalNode *spotParser::Dt_NCRepsContext::DOTS() {
  return getToken(spotParser::DOTS, 0);
}

size_t spotParser::Dt_NCRepsContext::getRuleIndex() const {
  return spotParser::RuleDt_NCReps;
}

void spotParser::Dt_NCRepsContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDt_NCReps(this);
}

void spotParser::Dt_NCRepsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDt_NCReps(this);
}

spotParser::Dt_NCRepsContext *spotParser::dt_NCReps() {
  Dt_NCRepsContext *_localctx =
      _tracker.createInstance<Dt_NCRepsContext>(_ctx, getState());
  enterRule(_localctx, 14, spotParser::RuleDt_NCReps);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(275);
    match(spotParser::T__3);
    setState(276);
    match(spotParser::NUMERIC);
    setState(277);
    match(spotParser::RCPAREN);
    setState(278);
    match(spotParser::SEP);
    setState(279);
    match(spotParser::DOTS);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

spotParser::BooleanContext::BooleanContext(ParserRuleContext *parent,
                                           size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::BooleanContext::NOT() {
  return getToken(spotParser::NOT, 0);
}

std::vector<spotParser::BooleanContext *>
spotParser::BooleanContext::boolean() {
  return getRuleContexts<spotParser::BooleanContext>();
}

spotParser::BooleanContext *spotParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<spotParser::BooleanContext>(i);
}

std::vector<spotParser::LogicContext *> spotParser::BooleanContext::logic() {
  return getRuleContexts<spotParser::LogicContext>();
}

spotParser::LogicContext *spotParser::BooleanContext::logic(size_t i) {
  return getRuleContext<spotParser::LogicContext>(i);
}

spotParser::RelopContext *spotParser::BooleanContext::relop() {
  return getRuleContext<spotParser::RelopContext>(0);
}

std::vector<spotParser::NumericContext *>
spotParser::BooleanContext::numeric() {
  return getRuleContexts<spotParser::NumericContext>();
}

spotParser::NumericContext *spotParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<spotParser::NumericContext>(i);
}

tree::TerminalNode *spotParser::BooleanContext::EQ() {
  return getToken(spotParser::EQ, 0);
}

tree::TerminalNode *spotParser::BooleanContext::NEQ() {
  return getToken(spotParser::NEQ, 0);
}

spotParser::BooleanAtomContext *spotParser::BooleanContext::booleanAtom() {
  return getRuleContext<spotParser::BooleanAtomContext>(0);
}

tree::TerminalNode *spotParser::BooleanContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

tree::TerminalNode *spotParser::BooleanContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode *spotParser::BooleanContext::AND() {
  return getToken(spotParser::AND, 0);
}

tree::TerminalNode *spotParser::BooleanContext::OR() {
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

spotParser::BooleanContext *spotParser::boolean() { return boolean(0); }

spotParser::BooleanContext *spotParser::boolean(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  spotParser::BooleanContext *_localctx =
      _tracker.createInstance<BooleanContext>(_ctx, parentState);
  spotParser::BooleanContext *previousContext = _localctx;
  (void)
      previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, spotParser::RuleBoolean, precedence);

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
    setState(315);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 25, _ctx)) {
    case 1: {
      setState(282);
      match(spotParser::NOT);
      setState(283);
      boolean(15);
      break;
    }

    case 2: {
      setState(284);
      logic(0);
      setState(285);
      relop();
      setState(286);
      logic(0);
      break;
    }

    case 3: {
      setState(288);
      numeric(0);
      setState(289);
      relop();
      setState(290);
      numeric(0);
      break;
    }

    case 4: {
      setState(292);
      logic(0);
      setState(293);
      match(spotParser::EQ);
      setState(294);
      logic(0);
      break;
    }

    case 5: {
      setState(296);
      numeric(0);
      setState(297);
      match(spotParser::EQ);
      setState(298);
      numeric(0);
      break;
    }

    case 6: {
      setState(300);
      logic(0);
      setState(301);
      match(spotParser::NEQ);
      setState(302);
      logic(0);
      break;
    }

    case 7: {
      setState(304);
      numeric(0);
      setState(305);
      match(spotParser::NEQ);
      setState(306);
      numeric(0);
      break;
    }

    case 8: {
      setState(308);
      booleanAtom();
      break;
    }

    case 9: {
      setState(309);
      logic(0);
      break;
    }

    case 10: {
      setState(310);
      numeric(0);
      break;
    }

    case 11: {
      setState(311);
      match(spotParser::LPAREN);
      setState(312);
      boolean(0);
      setState(313);
      match(spotParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(331);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27,
                                                                     _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(329);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 26, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(317);

          if (!(precpred(_ctx, 10)))
            throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(318);
          match(spotParser::EQ);
          setState(319);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(320);

          if (!(precpred(_ctx, 7)))
            throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(321);
          match(spotParser::NEQ);
          setState(322);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(323);

          if (!(precpred(_ctx, 6)))
            throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(324);
          dynamic_cast<BooleanContext *>(_localctx)->booleanop =
              match(spotParser::AND);
          setState(325);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(326);

          if (!(precpred(_ctx, 5)))
            throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(327);
          dynamic_cast<BooleanContext *>(_localctx)->booleanop =
              match(spotParser::OR);
          setState(328);
          boolean(6);
          break;
        }

        default:
          break;
        }
      }
      setState(333);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 27, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- BooleanAtomContext ------------------------------------------------------------------

spotParser::BooleanAtomContext::BooleanAtomContext(ParserRuleContext *parent,
                                                   size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

spotParser::BooleanConstantContext *
spotParser::BooleanAtomContext::booleanConstant() {
  return getRuleContext<spotParser::BooleanConstantContext>(0);
}

spotParser::BooleanVariableContext *
spotParser::BooleanAtomContext::booleanVariable() {
  return getRuleContext<spotParser::BooleanVariableContext>(0);
}

size_t spotParser::BooleanAtomContext::getRuleIndex() const {
  return spotParser::RuleBooleanAtom;
}

void spotParser::BooleanAtomContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanAtom(this);
}

void spotParser::BooleanAtomContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanAtom(this);
}

spotParser::BooleanAtomContext *spotParser::booleanAtom() {
  BooleanAtomContext *_localctx =
      _tracker.createInstance<BooleanAtomContext>(_ctx, getState());
  enterRule(_localctx, 18, spotParser::RuleBooleanAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(336);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case spotParser::BOOLEAN: {
      enterOuterAlt(_localctx, 1);
      setState(334);
      booleanConstant();
      break;
    }

    case spotParser::LT: {
      enterOuterAlt(_localctx, 2);
      setState(335);
      booleanVariable();
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

//----------------- BooleanConstantContext ------------------------------------------------------------------

spotParser::BooleanConstantContext::BooleanConstantContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::BooleanConstantContext::BOOLEAN() {
  return getToken(spotParser::BOOLEAN, 0);
}

size_t spotParser::BooleanConstantContext::getRuleIndex() const {
  return spotParser::RuleBooleanConstant;
}

void spotParser::BooleanConstantContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanConstant(this);
}

void spotParser::BooleanConstantContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanConstant(this);
}

spotParser::BooleanConstantContext *spotParser::booleanConstant() {
  BooleanConstantContext *_localctx =
      _tracker.createInstance<BooleanConstantContext>(_ctx, getState());
  enterRule(_localctx, 20, spotParser::RuleBooleanConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(338);
    match(spotParser::BOOLEAN);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanVariableContext ------------------------------------------------------------------

spotParser::BooleanVariableContext::BooleanVariableContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::BooleanVariableContext::LT() {
  return getToken(spotParser::LT, 0);
}

spotParser::VariableContext *spotParser::BooleanVariableContext::variable() {
  return getRuleContext<spotParser::VariableContext>(0);
}

size_t spotParser::BooleanVariableContext::getRuleIndex() const {
  return spotParser::RuleBooleanVariable;
}

void spotParser::BooleanVariableContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanVariable(this);
}

void spotParser::BooleanVariableContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanVariable(this);
}

spotParser::BooleanVariableContext *spotParser::booleanVariable() {
  BooleanVariableContext *_localctx =
      _tracker.createInstance<BooleanVariableContext>(_ctx, getState());
  enterRule(_localctx, 22, spotParser::RuleBooleanVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(340);
    match(spotParser::LT);
    setState(341);
    variable();
    setState(342);
    match(spotParser::T__4);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicContext ------------------------------------------------------------------

spotParser::LogicContext::LogicContext(ParserRuleContext *parent,
                                       size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::LogicContext::NEG() {
  return getToken(spotParser::NEG, 0);
}

std::vector<spotParser::LogicContext *> spotParser::LogicContext::logic() {
  return getRuleContexts<spotParser::LogicContext>();
}

spotParser::LogicContext *spotParser::LogicContext::logic(size_t i) {
  return getRuleContext<spotParser::LogicContext>(i);
}

spotParser::LogicAtomContext *spotParser::LogicContext::logicAtom() {
  return getRuleContext<spotParser::LogicAtomContext>(0);
}

tree::TerminalNode *spotParser::LogicContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

tree::TerminalNode *spotParser::LogicContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode *spotParser::LogicContext::TIMES() {
  return getToken(spotParser::TIMES, 0);
}

tree::TerminalNode *spotParser::LogicContext::DIV() {
  return getToken(spotParser::DIV, 0);
}

tree::TerminalNode *spotParser::LogicContext::PLUS() {
  return getToken(spotParser::PLUS, 0);
}

tree::TerminalNode *spotParser::LogicContext::MINUS() {
  return getToken(spotParser::MINUS, 0);
}

tree::TerminalNode *spotParser::LogicContext::LSHIFT() {
  return getToken(spotParser::LSHIFT, 0);
}

tree::TerminalNode *spotParser::LogicContext::RSHIFT() {
  return getToken(spotParser::RSHIFT, 0);
}

tree::TerminalNode *spotParser::LogicContext::BAND() {
  return getToken(spotParser::BAND, 0);
}

tree::TerminalNode *spotParser::LogicContext::BXOR() {
  return getToken(spotParser::BXOR, 0);
}

tree::TerminalNode *spotParser::LogicContext::BOR() {
  return getToken(spotParser::BOR, 0);
}

spotParser::BitSelectContext *spotParser::LogicContext::bitSelect() {
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

spotParser::LogicContext *spotParser::logic() { return logic(0); }

spotParser::LogicContext *spotParser::logic(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  spotParser::LogicContext *_localctx =
      _tracker.createInstance<LogicContext>(_ctx, parentState);
  spotParser::LogicContext *previousContext = _localctx;
  (void)
      previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, spotParser::RuleLogic, precedence);

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
    setState(352);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case spotParser::NEG: {
      setState(345);
      match(spotParser::NEG);
      setState(346);
      logic(11);
      break;
    }

    case spotParser::NUMERIC:
    case spotParser::VERILOG_BINARY:
    case spotParser::GCC_BINARY:
    case spotParser::HEX:
    case spotParser::LT: {
      setState(347);
      logicAtom();
      break;
    }

    case spotParser::LPAREN: {
      setState(348);
      match(spotParser::LPAREN);
      setState(349);
      logic(0);
      setState(350);
      match(spotParser::RPAREN);
      break;
    }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(379);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31,
                                                                     _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(377);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 30, _ctx)) {
        case 1: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(354);

          if (!(precpred(_ctx, 9)))
            throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(355);
          dynamic_cast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == spotParser::TIMES

                || _la == spotParser::DIV)) {
            dynamic_cast<LogicContext *>(_localctx)->artop =
                _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(356);
          logic(10);
          break;
        }

        case 2: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(357);

          if (!(precpred(_ctx, 8)))
            throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(358);
          dynamic_cast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == spotParser::PLUS

                || _la == spotParser::MINUS)) {
            dynamic_cast<LogicContext *>(_localctx)->artop =
                _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(359);
          logic(9);
          break;
        }

        case 3: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(360);

          if (!(precpred(_ctx, 7)))
            throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(361);
          dynamic_cast<LogicContext *>(_localctx)->logop =
              match(spotParser::LSHIFT);
          setState(362);
          logic(8);
          break;
        }

        case 4: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(363);

          if (!(precpred(_ctx, 6)))
            throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(364);
          dynamic_cast<LogicContext *>(_localctx)->logop =
              match(spotParser::RSHIFT);
          setState(365);
          logic(7);
          break;
        }

        case 5: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(366);

          if (!(precpred(_ctx, 5)))
            throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(367);
          dynamic_cast<LogicContext *>(_localctx)->logop =
              match(spotParser::BAND);
          setState(368);
          logic(6);
          break;
        }

        case 6: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(369);

          if (!(precpred(_ctx, 4)))
            throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(370);
          dynamic_cast<LogicContext *>(_localctx)->logop =
              match(spotParser::BXOR);
          setState(371);
          logic(5);
          break;
        }

        case 7: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(372);

          if (!(precpred(_ctx, 3)))
            throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(373);
          dynamic_cast<LogicContext *>(_localctx)->logop =
              match(spotParser::BOR);
          setState(374);
          logic(4);
          break;
        }

        case 8: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(375);

          if (!(precpred(_ctx, 10)))
            throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(376);
          bitSelect();
          break;
        }

        default:
          break;
        }
      }
      setState(381);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 31, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- BitSelectContext ------------------------------------------------------------------

spotParser::BitSelectContext::BitSelectContext(ParserRuleContext *parent,
                                               size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::BitSelectContext::LCPAREN() {
  return getToken(spotParser::LCPAREN, 0);
}

std::vector<tree::TerminalNode *> spotParser::BitSelectContext::NUMERIC() {
  return getTokens(spotParser::NUMERIC);
}

tree::TerminalNode *spotParser::BitSelectContext::NUMERIC(size_t i) {
  return getToken(spotParser::NUMERIC, i);
}

tree::TerminalNode *spotParser::BitSelectContext::RCPAREN() {
  return getToken(spotParser::RCPAREN, 0);
}

tree::TerminalNode *spotParser::BitSelectContext::COL() {
  return getToken(spotParser::COL, 0);
}

size_t spotParser::BitSelectContext::getRuleIndex() const {
  return spotParser::RuleBitSelect;
}

void spotParser::BitSelectContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitSelect(this);
}

void spotParser::BitSelectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitSelect(this);
}

spotParser::BitSelectContext *spotParser::bitSelect() {
  BitSelectContext *_localctx =
      _tracker.createInstance<BitSelectContext>(_ctx, getState());
  enterRule(_localctx, 26, spotParser::RuleBitSelect);
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
    match(spotParser::LCPAREN);
    setState(383);
    match(spotParser::NUMERIC);
    setState(386);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == spotParser::COL) {
      setState(384);
      match(spotParser::COL);
      setState(385);
      match(spotParser::NUMERIC);
    }
    setState(388);
    match(spotParser::RCPAREN);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicAtomContext ------------------------------------------------------------------

spotParser::LogicAtomContext::LogicAtomContext(ParserRuleContext *parent,
                                               size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

spotParser::LogicConstantContext *
spotParser::LogicAtomContext::logicConstant() {
  return getRuleContext<spotParser::LogicConstantContext>(0);
}

spotParser::LogicVariableContext *
spotParser::LogicAtomContext::logicVariable() {
  return getRuleContext<spotParser::LogicVariableContext>(0);
}

size_t spotParser::LogicAtomContext::getRuleIndex() const {
  return spotParser::RuleLogicAtom;
}

void spotParser::LogicAtomContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicAtom(this);
}

void spotParser::LogicAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicAtom(this);
}

spotParser::LogicAtomContext *spotParser::logicAtom() {
  LogicAtomContext *_localctx =
      _tracker.createInstance<LogicAtomContext>(_ctx, getState());
  enterRule(_localctx, 28, spotParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(392);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case spotParser::NUMERIC:
    case spotParser::VERILOG_BINARY:
    case spotParser::GCC_BINARY:
    case spotParser::HEX: {
      enterOuterAlt(_localctx, 1);
      setState(390);
      logicConstant();
      break;
    }

    case spotParser::LT: {
      enterOuterAlt(_localctx, 2);
      setState(391);
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

spotParser::LogicConstantContext::LogicConstantContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::LogicConstantContext::VERILOG_BINARY() {
  return getToken(spotParser::VERILOG_BINARY, 0);
}

tree::TerminalNode *spotParser::LogicConstantContext::GCC_BINARY() {
  return getToken(spotParser::GCC_BINARY, 0);
}

tree::TerminalNode *spotParser::LogicConstantContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

tree::TerminalNode *spotParser::LogicConstantContext::HEX() {
  return getToken(spotParser::HEX, 0);
}

size_t spotParser::LogicConstantContext::getRuleIndex() const {
  return spotParser::RuleLogicConstant;
}

void spotParser::LogicConstantContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicConstant(this);
}

void spotParser::LogicConstantContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicConstant(this);
}

spotParser::LogicConstantContext *spotParser::logicConstant() {
  LogicConstantContext *_localctx =
      _tracker.createInstance<LogicConstantContext>(_ctx, getState());
  enterRule(_localctx, 30, spotParser::RuleLogicConstant);
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
    setState(394);
    _la = _input->LA(1);
    if (!((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) & ((1ULL << spotParser::NUMERIC) |
                             (1ULL << spotParser::VERILOG_BINARY) |
                             (1ULL << spotParser::GCC_BINARY) |
                             (1ULL << spotParser::HEX))) != 0))) {
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

spotParser::LogicVariableContext::LogicVariableContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::LogicVariableContext::LT() {
  return getToken(spotParser::LT, 0);
}

spotParser::VariableContext *spotParser::LogicVariableContext::variable() {
  return getRuleContext<spotParser::VariableContext>(0);
}

tree::TerminalNode *spotParser::LogicVariableContext::SIGN() {
  return getToken(spotParser::SIGN, 0);
}

tree::TerminalNode *spotParser::LogicVariableContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

size_t spotParser::LogicVariableContext::getRuleIndex() const {
  return spotParser::RuleLogicVariable;
}

void spotParser::LogicVariableContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicVariable(this);
}

void spotParser::LogicVariableContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicVariable(this);
}

spotParser::LogicVariableContext *spotParser::logicVariable() {
  LogicVariableContext *_localctx =
      _tracker.createInstance<LogicVariableContext>(_ctx, getState());
  enterRule(_localctx, 32, spotParser::RuleLogicVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(396);
    match(spotParser::LT);
    setState(397);
    variable();
    setState(398);
    match(spotParser::T__5);
    setState(399);
    match(spotParser::SIGN);
    setState(400);
    match(spotParser::T__6);
    setState(401);
    match(spotParser::NUMERIC);
    setState(402);
    match(spotParser::T__7);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericContext ------------------------------------------------------------------

spotParser::NumericContext::NumericContext(ParserRuleContext *parent,
                                           size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

spotParser::NumericAtomContext *spotParser::NumericContext::numericAtom() {
  return getRuleContext<spotParser::NumericAtomContext>(0);
}

spotParser::LogicContext *spotParser::NumericContext::logic() {
  return getRuleContext<spotParser::LogicContext>(0);
}

tree::TerminalNode *spotParser::NumericContext::LPAREN() {
  return getToken(spotParser::LPAREN, 0);
}

std::vector<spotParser::NumericContext *>
spotParser::NumericContext::numeric() {
  return getRuleContexts<spotParser::NumericContext>();
}

spotParser::NumericContext *spotParser::NumericContext::numeric(size_t i) {
  return getRuleContext<spotParser::NumericContext>(i);
}

tree::TerminalNode *spotParser::NumericContext::RPAREN() {
  return getToken(spotParser::RPAREN, 0);
}

tree::TerminalNode *spotParser::NumericContext::TIMES() {
  return getToken(spotParser::TIMES, 0);
}

tree::TerminalNode *spotParser::NumericContext::DIV() {
  return getToken(spotParser::DIV, 0);
}

tree::TerminalNode *spotParser::NumericContext::PLUS() {
  return getToken(spotParser::PLUS, 0);
}

tree::TerminalNode *spotParser::NumericContext::MINUS() {
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

spotParser::NumericContext *spotParser::numeric() { return numeric(0); }

spotParser::NumericContext *spotParser::numeric(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  spotParser::NumericContext *_localctx =
      _tracker.createInstance<NumericContext>(_ctx, parentState);
  spotParser::NumericContext *previousContext = _localctx;
  (void)
      previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, spotParser::RuleNumeric, precedence);

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
    setState(411);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 34, _ctx)) {
    case 1: {
      setState(405);
      numericAtom();
      break;
    }

    case 2: {
      setState(406);
      logic(0);
      break;
    }

    case 3: {
      setState(407);
      match(spotParser::LPAREN);
      setState(408);
      numeric(0);
      setState(409);
      match(spotParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(421);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36,
                                                                     _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(419);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 35, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(413);

          if (!(precpred(_ctx, 5)))
            throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(414);
          dynamic_cast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == spotParser::TIMES

                || _la == spotParser::DIV)) {
            dynamic_cast<NumericContext *>(_localctx)->artop =
                _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(415);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(416);

          if (!(precpred(_ctx, 4)))
            throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(417);
          dynamic_cast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == spotParser::PLUS

                || _la == spotParser::MINUS)) {
            dynamic_cast<NumericContext *>(_localctx)->artop =
                _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(418);
          numeric(5);
          break;
        }

        default:
          break;
        }
      }
      setState(423);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 36, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- NumericAtomContext ------------------------------------------------------------------

spotParser::NumericAtomContext::NumericAtomContext(ParserRuleContext *parent,
                                                   size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

spotParser::NumericConstantContext *
spotParser::NumericAtomContext::numericConstant() {
  return getRuleContext<spotParser::NumericConstantContext>(0);
}

spotParser::NumericVariableContext *
spotParser::NumericAtomContext::numericVariable() {
  return getRuleContext<spotParser::NumericVariableContext>(0);
}

size_t spotParser::NumericAtomContext::getRuleIndex() const {
  return spotParser::RuleNumericAtom;
}

void spotParser::NumericAtomContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericAtom(this);
}

void spotParser::NumericAtomContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericAtom(this);
}

spotParser::NumericAtomContext *spotParser::numericAtom() {
  NumericAtomContext *_localctx =
      _tracker.createInstance<NumericAtomContext>(_ctx, getState());
  enterRule(_localctx, 36, spotParser::RuleNumericAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(426);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
    case spotParser::NUMERIC: {
      enterOuterAlt(_localctx, 1);
      setState(424);
      numericConstant();
      break;
    }

    case spotParser::LT: {
      enterOuterAlt(_localctx, 2);
      setState(425);
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

spotParser::NumericConstantContext::NumericConstantContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::NumericConstantContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

size_t spotParser::NumericConstantContext::getRuleIndex() const {
  return spotParser::RuleNumericConstant;
}

void spotParser::NumericConstantContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericConstant(this);
}

void spotParser::NumericConstantContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericConstant(this);
}

spotParser::NumericConstantContext *spotParser::numericConstant() {
  NumericConstantContext *_localctx =
      _tracker.createInstance<NumericConstantContext>(_ctx, getState());
  enterRule(_localctx, 38, spotParser::RuleNumericConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(428);
    match(spotParser::NUMERIC);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericVariableContext ------------------------------------------------------------------

spotParser::NumericVariableContext::NumericVariableContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::NumericVariableContext::LT() {
  return getToken(spotParser::LT, 0);
}

spotParser::VariableContext *spotParser::NumericVariableContext::variable() {
  return getRuleContext<spotParser::VariableContext>(0);
}

tree::TerminalNode *spotParser::NumericVariableContext::NUMERIC() {
  return getToken(spotParser::NUMERIC, 0);
}

size_t spotParser::NumericVariableContext::getRuleIndex() const {
  return spotParser::RuleNumericVariable;
}

void spotParser::NumericVariableContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericVariable(this);
}

void spotParser::NumericVariableContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericVariable(this);
}

spotParser::NumericVariableContext *spotParser::numericVariable() {
  NumericVariableContext *_localctx =
      _tracker.createInstance<NumericVariableContext>(_ctx, getState());
  enterRule(_localctx, 40, spotParser::RuleNumericVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(430);
    match(spotParser::LT);
    setState(431);
    variable();
    setState(432);
    match(spotParser::T__8);
    setState(433);
    match(spotParser::NUMERIC);
    setState(434);
    match(spotParser::T__7);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

spotParser::VariableContext::VariableContext(ParserRuleContext *parent,
                                             size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::VariableContext::VARIABLE() {
  return getToken(spotParser::VARIABLE, 0);
}

size_t spotParser::VariableContext::getRuleIndex() const {
  return spotParser::RuleVariable;
}

void spotParser::VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void spotParser::VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<spotListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

spotParser::VariableContext *spotParser::variable() {
  VariableContext *_localctx =
      _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 42, spotParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436);
    match(spotParser::VARIABLE);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelopContext ------------------------------------------------------------------

spotParser::RelopContext::RelopContext(ParserRuleContext *parent,
                                       size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *spotParser::RelopContext::GT() {
  return getToken(spotParser::GT, 0);
}

tree::TerminalNode *spotParser::RelopContext::GE() {
  return getToken(spotParser::GE, 0);
}

tree::TerminalNode *spotParser::RelopContext::LT() {
  return getToken(spotParser::LT, 0);
}

tree::TerminalNode *spotParser::RelopContext::LE() {
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

spotParser::RelopContext *spotParser::relop() {
  RelopContext *_localctx =
      _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 44, spotParser::RuleRelop);
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
    setState(438);
    _la = _input->LA(1);
    if (!((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) &
            ((1ULL << spotParser::GT) | (1ULL << spotParser::GE) |
             (1ULL << spotParser::LT) | (1ULL << spotParser::LE))) != 0))) {
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

bool spotParser::sempred(RuleContext *context, size_t ruleIndex,
                         size_t predicateIndex) {
  switch (ruleIndex) {
  case 2:
    return sereSempred(dynamic_cast<SereContext *>(context), predicateIndex);
  case 3:
    return tformulaSempred(dynamic_cast<TformulaContext *>(context),
                           predicateIndex);
  case 8:
    return booleanSempred(dynamic_cast<BooleanContext *>(context),
                          predicateIndex);
  case 12:
    return logicSempred(dynamic_cast<LogicContext *>(context), predicateIndex);
  case 17:
    return numericSempred(dynamic_cast<NumericContext *>(context),
                          predicateIndex);

  default:
    break;
  }
  return true;
}

bool spotParser::sereSempred(SereContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
  case 0:
    return precpred(_ctx, 14);
  case 1:
    return precpred(_ctx, 13);
  case 2:
    return precpred(_ctx, 12);
  case 3:
    return precpred(_ctx, 11);
  case 4:
    return precpred(_ctx, 10);
  case 5:
    return precpred(_ctx, 4);
  case 6:
    return precpred(_ctx, 9);
  case 7:
    return precpred(_ctx, 8);
  case 8:
    return precpred(_ctx, 7);
  case 9:
    return precpred(_ctx, 6);

  default:
    break;
  }
  return true;
}

bool spotParser::tformulaSempred(TformulaContext *_localctx,
                                 size_t predicateIndex) {
  switch (predicateIndex) {
  case 10:
    return precpred(_ctx, 8);
  case 11:
    return precpred(_ctx, 7);
  case 12:
    return precpred(_ctx, 6);
  case 13:
    return precpred(_ctx, 5);
  case 14:
    return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

bool spotParser::booleanSempred(BooleanContext *_localctx,
                                size_t predicateIndex) {
  switch (predicateIndex) {
  case 15:
    return precpred(_ctx, 10);
  case 16:
    return precpred(_ctx, 7);
  case 17:
    return precpred(_ctx, 6);
  case 18:
    return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

bool spotParser::logicSempred(LogicContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
  case 19:
    return precpred(_ctx, 9);
  case 20:
    return precpred(_ctx, 8);
  case 21:
    return precpred(_ctx, 7);
  case 22:
    return precpred(_ctx, 6);
  case 23:
    return precpred(_ctx, 5);
  case 24:
    return precpred(_ctx, 4);
  case 25:
    return precpred(_ctx, 3);
  case 26:
    return precpred(_ctx, 10);

  default:
    break;
  }
  return true;
}

bool spotParser::numericSempred(NumericContext *_localctx,
                                size_t predicateIndex) {
  switch (predicateIndex) {
  case 27:
    return precpred(_ctx, 5);
  case 28:
    return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> spotParser::_decisionToDFA;
atn::PredictionContextCache spotParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN spotParser::_atn;
std::vector<uint16_t> spotParser::_serializedATN;

std::vector<std::string> spotParser::_ruleNames = {"file",
                                                   "formula",
                                                   "sere",
                                                   "tformula",
                                                   "placeholder",
                                                   "dt_next",
                                                   "dt_next_and",
                                                   "dt_NCReps",
                                                   "boolean",
                                                   "booleanAtom",
                                                   "booleanConstant",
                                                   "booleanVariable",
                                                   "logic",
                                                   "bitSelect",
                                                   "logicAtom",
                                                   "logicConstant",
                                                   "logicVariable",
                                                   "numeric",
                                                   "numericAtom",
                                                   "numericConstant",
                                                   "numericVariable",
                                                   "variable",
                                                   "relop"};

std::vector<std::string> spotParser::_literalNames = {"",
                                                      "'P'",
                                                      "'..##'",
                                                      "'..#'",
                                                      "'..[->'",
                                                      "',bool>'",
                                                      "',logic('",
                                                      "','",
                                                      "')>'",
                                                      "',numeric('",
                                                      "'..&&..'",
                                                      "",
                                                      "'F'",
                                                      "'G'",
                                                      "'X'",
                                                      "'U'",
                                                      "'R'",
                                                      "'..'",
                                                      "'->'",
                                                      "'=>'",
                                                      "'<->'",
                                                      "'xor'",
                                                      "'[]->'",
                                                      "'[]=>'",
                                                      "'|->'",
                                                      "'|=>'",
                                                      "'='",
                                                      "'##'",
                                                      "';'",
                                                      "':'",
                                                      "'first_match'",
                                                      "",
                                                      "'{'",
                                                      "'}'",
                                                      "'['",
                                                      "']'",
                                                      "'('",
                                                      "')'",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "",
                                                      "'+'",
                                                      "'-'",
                                                      "'*'",
                                                      "'/'",
                                                      "'>'",
                                                      "'>='",
                                                      "'<'",
                                                      "'<='",
                                                      "'=='",
                                                      "'!='",
                                                      "'&'",
                                                      "'|'",
                                                      "'^'",
                                                      "'~'",
                                                      "'<<'",
                                                      "'>>'",
                                                      "'&&'",
                                                      "'||'",
                                                      "'!'"};

std::vector<std::string> spotParser::_symbolicNames = {"",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "",
                                                       "DT_AND",
                                                       "SEP",
                                                       "EVENTUALLY",
                                                       "ALWAYS",
                                                       "NEXT",
                                                       "UNTIL",
                                                       "RELEASE",
                                                       "DOTS",
                                                       "IMPL",
                                                       "IMPL2",
                                                       "IFF",
                                                       "XOR",
                                                       "BIND1",
                                                       "BIND2",
                                                       "SEREIMPL1",
                                                       "SEREIMPL2",
                                                       "ASS",
                                                       "DELAY",
                                                       "SCOL",
                                                       "COL",
                                                       "FIRST_MATCH",
                                                       "SIGN",
                                                       "LGPAREN",
                                                       "RGPAREN",
                                                       "LCPAREN",
                                                       "RCPAREN",
                                                       "LPAREN",
                                                       "RPAREN",
                                                       "VARIABLE",
                                                       "NUMERIC",
                                                       "VERILOG_BINARY",
                                                       "GCC_BINARY",
                                                       "HEX",
                                                       "BOOLEAN",
                                                       "PLUS",
                                                       "MINUS",
                                                       "TIMES",
                                                       "DIV",
                                                       "GT",
                                                       "GE",
                                                       "LT",
                                                       "LE",
                                                       "EQ",
                                                       "NEQ",
                                                       "BAND",
                                                       "BOR",
                                                       "BXOR",
                                                       "NEG",
                                                       "LSHIFT",
                                                       "RSHIFT",
                                                       "AND",
                                                       "OR",
                                                       "NOT",
                                                       "WS"};

dfa::Vocabulary spotParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> spotParser::_tokenNames;

spotParser::Initializer::Initializer() {
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
      0x3,   0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964,
      0x3,   0x41,   0x1bb,  0x4,    0x2,    0x9,    0x2,    0x4,    0x3,
      0x9,   0x3,    0x4,    0x4,    0x9,    0x4,    0x4,    0x5,    0x9,
      0x5,   0x4,    0x6,    0x9,    0x6,    0x4,    0x7,    0x9,    0x7,
      0x4,   0x8,    0x9,    0x8,    0x4,    0x9,    0x9,    0x9,    0x4,
      0xa,   0x9,    0xa,    0x4,    0xb,    0x9,    0xb,    0x4,    0xc,
      0x9,   0xc,    0x4,    0xd,    0x9,    0xd,    0x4,    0xe,    0x9,
      0xe,   0x4,    0xf,    0x9,    0xf,    0x4,    0x10,   0x9,    0x10,
      0x4,   0x11,   0x9,    0x11,   0x4,    0x12,   0x9,    0x12,   0x4,
      0x13,  0x9,    0x13,   0x4,    0x14,   0x9,    0x14,   0x4,    0x15,
      0x9,   0x15,   0x4,    0x16,   0x9,    0x16,   0x4,    0x17,   0x9,
      0x17,  0x4,    0x18,   0x9,    0x18,   0x3,    0x2,    0x3,    0x2,
      0x3,   0x2,    0x3,    0x2,    0x3,    0x2,    0x3,    0x2,    0x3,
      0x2,   0x3,    0x2,    0x3,    0x2,    0x3,    0x2,    0x5,    0x2,
      0x3b,  0xa,    0x2,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3,   0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x5,   0x3,    0x6d,   0xa,    0x3,    0x3,    0x4,    0x3,    0x4,
      0x3,   0x4,    0x5,    0x4,    0x72,   0xa,    0x4,    0x3,    0x4,
      0x3,   0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,
      0x4,   0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,
      0x3,   0x4,    0x3,    0x4,    0x5,    0x4,    0x80,   0xa,    0x4,
      0x3,   0x4,    0x3,    0x4,    0x5,    0x4,    0x84,   0xa,    0x4,
      0x3,   0x4,    0x5,    0x4,    0x87,   0xa,    0x4,    0x3,    0x4,
      0x5,   0x4,    0x8a,   0xa,    0x4,    0x3,    0x4,    0x3,    0x4,
      0x3,   0x4,    0x3,    0x4,    0x5,    0x4,    0x90,   0xa,    0x4,
      0x3,   0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,
      0x4,   0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,
      0x3,   0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,
      0x4,   0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,
      0x5,   0x4,    0xa4,   0xa,    0x4,    0x3,    0x4,    0x5,    0x4,
      0xa7,  0xa,    0x4,    0x3,    0x4,    0x5,    0x4,    0xaa,   0xa,
      0x4,   0x3,    0x4,    0x5,    0x4,    0xad,   0xa,    0x4,    0x3,
      0x4,   0x5,    0x4,    0xb0,   0xa,    0x4,    0x3,    0x4,    0x3,
      0x4,   0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x5,    0x4,
      0xb7,  0xa,    0x4,    0x3,    0x4,    0x5,    0x4,    0xba,   0xa,
      0x4,   0x3,    0x4,    0x5,    0x4,    0xbd,   0xa,    0x4,    0x3,
      0x4,   0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,
      0x3,   0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,
      0x4,   0x5,    0x4,    0xc9,   0xa,    0x4,    0x3,    0x4,    0x5,
      0x4,   0xcc,   0xa,    0x4,    0x3,    0x4,    0x3,    0x4,    0x3,
      0x4,   0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x5,    0x4,
      0xd4,  0xa,    0x4,    0x3,    0x4,    0x5,    0x4,    0xd7,   0xa,
      0x4,   0x3,    0x4,    0x7,    0x4,    0xda,   0xa,    0x4,    0xc,
      0x4,   0xe,    0x4,    0xdd,   0xb,    0x4,    0x3,    0x5,    0x3,
      0x5,   0x3,    0x5,    0x3,    0x5,    0x3,    0x5,    0x3,    0x5,
      0x3,   0x5,    0x3,    0x5,    0x3,    0x5,    0x3,    0x5,    0x3,
      0x5,   0x3,    0x5,    0x3,    0x5,    0x3,    0x5,    0x3,    0x5,
      0x3,   0x5,    0x3,    0x5,    0x3,    0x5,    0x3,    0x5,    0x3,
      0x5,   0x3,    0x5,    0x5,    0x5,    0xf4,   0xa,    0x5,    0x3,
      0x5,   0x3,    0x5,    0x3,    0x5,    0x3,    0x5,    0x3,    0x5,
      0x3,   0x5,    0x3,    0x5,    0x3,    0x5,    0x3,    0x5,    0x3,
      0x5,   0x3,    0x5,    0x3,    0x5,    0x3,    0x5,    0x3,    0x5,
      0x3,   0x5,    0x7,    0x5,    0x105,  0xa,    0x5,    0xc,    0x5,
      0xe,   0x5,    0x108,  0xb,    0x5,    0x3,    0x6,    0x3,    0x6,
      0x3,   0x6,    0x3,    0x7,    0x3,    0x7,    0x3,    0x7,    0x3,
      0x7,   0x3,    0x8,    0x3,    0x8,    0x3,    0x8,    0x3,    0x8,
      0x3,   0x8,    0x3,    0x9,    0x3,    0x9,    0x3,    0x9,    0x3,
      0x9,   0x3,    0x9,    0x3,    0x9,    0x3,    0xa,    0x3,    0xa,
      0x3,   0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,
      0xa,   0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,
      0x3,   0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,
      0xa,   0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,
      0x3,   0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,
      0xa,   0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,
      0x3,   0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,
      0xa,   0x5,    0xa,    0x13e,  0xa,    0xa,    0x3,    0xa,    0x3,
      0xa,   0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,
      0x3,   0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,
      0xa,   0x3,    0xa,    0x7,    0xa,    0x14c,  0xa,    0xa,    0xc,
      0xa,   0xe,    0xa,    0x14f,  0xb,    0xa,    0x3,    0xb,    0x3,
      0xb,   0x5,    0xb,    0x153,  0xa,    0xb,    0x3,    0xc,    0x3,
      0xc,   0x3,    0xd,    0x3,    0xd,    0x3,    0xd,    0x3,    0xd,
      0x3,   0xe,    0x3,    0xe,    0x3,    0xe,    0x3,    0xe,    0x3,
      0xe,   0x3,    0xe,    0x3,    0xe,    0x3,    0xe,    0x5,    0xe,
      0x163, 0xa,    0xe,    0x3,    0xe,    0x3,    0xe,    0x3,    0xe,
      0x3,   0xe,    0x3,    0xe,    0x3,    0xe,    0x3,    0xe,    0x3,
      0xe,   0x3,    0xe,    0x3,    0xe,    0x3,    0xe,    0x3,    0xe,
      0x3,   0xe,    0x3,    0xe,    0x3,    0xe,    0x3,    0xe,    0x3,
      0xe,   0x3,    0xe,    0x3,    0xe,    0x3,    0xe,    0x3,    0xe,
      0x3,   0xe,    0x3,    0xe,    0x7,    0xe,    0x17c,  0xa,    0xe,
      0xc,   0xe,    0xe,    0xe,    0x17f,  0xb,    0xe,    0x3,    0xf,
      0x3,   0xf,    0x3,    0xf,    0x3,    0xf,    0x5,    0xf,    0x185,
      0xa,   0xf,    0x3,    0xf,    0x3,    0xf,    0x3,    0x10,   0x3,
      0x10,  0x5,    0x10,   0x18b,  0xa,    0x10,   0x3,    0x11,   0x3,
      0x11,  0x3,    0x12,   0x3,    0x12,   0x3,    0x12,   0x3,    0x12,
      0x3,   0x12,   0x3,    0x12,   0x3,    0x12,   0x3,    0x12,   0x3,
      0x13,  0x3,    0x13,   0x3,    0x13,   0x3,    0x13,   0x3,    0x13,
      0x3,   0x13,   0x3,    0x13,   0x5,    0x13,   0x19e,  0xa,    0x13,
      0x3,   0x13,   0x3,    0x13,   0x3,    0x13,   0x3,    0x13,   0x3,
      0x13,  0x3,    0x13,   0x7,    0x13,   0x1a6,  0xa,    0x13,   0xc,
      0x13,  0xe,    0x13,   0x1a9,  0xb,    0x13,   0x3,    0x14,   0x3,
      0x14,  0x5,    0x14,   0x1ad,  0xa,    0x14,   0x3,    0x15,   0x3,
      0x15,  0x3,    0x16,   0x3,    0x16,   0x3,    0x16,   0x3,    0x16,
      0x3,   0x16,   0x3,    0x16,   0x3,    0x17,   0x3,    0x17,   0x3,
      0x18,  0x3,    0x18,   0x3,    0x18,   0x2,    0x7,    0x6,    0x8,
      0x12,  0x1a,   0x24,   0x19,   0x2,    0x4,    0x6,    0x8,    0xa,
      0xc,   0xe,    0x10,   0x12,   0x14,   0x16,   0x18,   0x1a,   0x1c,
      0x1e,  0x20,   0x22,   0x24,   0x26,   0x28,   0x2a,   0x2c,   0x2e,
      0x2,   0x6,    0x3,    0x2,    0x30,   0x31,   0x3,    0x2,    0x2e,
      0x2f,  0x3,    0x2,    0x29,   0x2c,   0x3,    0x2,    0x32,   0x35,
      0x2,   0x1fa,  0x2,    0x3a,   0x3,    0x2,    0x2,    0x2,    0x4,
      0x6c,  0x3,    0x2,    0x2,    0x2,    0x6,    0x8f,   0x3,    0x2,
      0x2,   0x2,    0x8,    0xf3,   0x3,    0x2,    0x2,    0x2,    0xa,
      0x109, 0x3,    0x2,    0x2,    0x2,    0xc,    0x10c,  0x3,    0x2,
      0x2,   0x2,    0xe,    0x110,  0x3,    0x2,    0x2,    0x2,    0x10,
      0x115, 0x3,    0x2,    0x2,    0x2,    0x12,   0x13d,  0x3,    0x2,
      0x2,   0x2,    0x14,   0x152,  0x3,    0x2,    0x2,    0x2,    0x16,
      0x154, 0x3,    0x2,    0x2,    0x2,    0x18,   0x156,  0x3,    0x2,
      0x2,   0x2,    0x1a,   0x162,  0x3,    0x2,    0x2,    0x2,    0x1c,
      0x180, 0x3,    0x2,    0x2,    0x2,    0x1e,   0x18a,  0x3,    0x2,
      0x2,   0x2,    0x20,   0x18c,  0x3,    0x2,    0x2,    0x2,    0x22,
      0x18e, 0x3,    0x2,    0x2,    0x2,    0x24,   0x19d,  0x3,    0x2,
      0x2,   0x2,    0x26,   0x1ac,  0x3,    0x2,    0x2,    0x2,    0x28,
      0x1ae, 0x3,    0x2,    0x2,    0x2,    0x2a,   0x1b0,  0x3,    0x2,
      0x2,   0x2,    0x2c,   0x1b6,  0x3,    0x2,    0x2,    0x2,    0x2e,
      0x1b8, 0x3,    0x2,    0x2,    0x2,    0x30,   0x31,   0x7,    0xf,
      0x2,   0x2,    0x31,   0x32,   0x5,    0x4,    0x3,    0x2,    0x32,
      0x33,  0x7,    0x2,    0x2,    0x3,    0x33,   0x3b,   0x3,    0x2,
      0x2,   0x2,    0x34,   0x35,   0x7,    0xf,    0x2,    0x2,    0x35,
      0x36,  0x7,    0x26,   0x2,    0x2,    0x36,   0x37,   0x5,    0x4,
      0x3,   0x2,    0x37,   0x38,   0x7,    0x27,   0x2,    0x2,    0x38,
      0x39,  0x7,    0x2,    0x2,    0x3,    0x39,   0x3b,   0x3,    0x2,
      0x2,   0x2,    0x3a,   0x30,   0x3,    0x2,    0x2,    0x2,    0x3a,
      0x34,  0x3,    0x2,    0x2,    0x2,    0x3b,   0x3,    0x3,    0x2,
      0x2,   0x2,    0x3c,   0x3d,   0x5,    0x8,    0x5,    0x2,    0x3d,
      0x3e,  0x7,    0x14,   0x2,    0x2,    0x3e,   0x3f,   0x5,    0x8,
      0x5,   0x2,    0x3f,   0x6d,   0x3,    0x2,    0x2,    0x2,    0x40,
      0x41,  0x5,    0x8,    0x5,    0x2,    0x41,   0x42,   0x7,    0x15,
      0x2,   0x2,    0x42,   0x43,   0x5,    0x8,    0x5,    0x2,    0x43,
      0x6d,  0x3,    0x2,    0x2,    0x2,    0x44,   0x45,   0x7,    0x22,
      0x2,   0x2,    0x45,   0x46,   0x5,    0x6,    0x4,    0x2,    0x46,
      0x47,  0x7,    0x23,   0x2,    0x2,    0x47,   0x48,   0x7,    0x24,
      0x2,   0x2,    0x48,   0x49,   0x7,    0x25,   0x2,    0x2,    0x49,
      0x4a,  0x7,    0x14,   0x2,    0x2,    0x4a,   0x4b,   0x5,    0x8,
      0x5,   0x2,    0x4b,   0x6d,   0x3,    0x2,    0x2,    0x2,    0x4c,
      0x4d,  0x7,    0x22,   0x2,    0x2,    0x4d,   0x4e,   0x5,    0x6,
      0x4,   0x2,    0x4e,   0x4f,   0x7,    0x23,   0x2,    0x2,    0x4f,
      0x50,  0x7,    0x24,   0x2,    0x2,    0x50,   0x51,   0x7,    0x25,
      0x2,   0x2,    0x51,   0x52,   0x7,    0x15,   0x2,    0x2,    0x52,
      0x53,  0x5,    0x8,    0x5,    0x2,    0x53,   0x6d,   0x3,    0x2,
      0x2,   0x2,    0x54,   0x55,   0x7,    0x22,   0x2,    0x2,    0x55,
      0x56,  0x5,    0x6,    0x4,    0x2,    0x56,   0x57,   0x7,    0x23,
      0x2,   0x2,    0x57,   0x58,   0x7,    0x18,   0x2,    0x2,    0x58,
      0x59,  0x5,    0x8,    0x5,    0x2,    0x59,   0x6d,   0x3,    0x2,
      0x2,   0x2,    0x5a,   0x5b,   0x7,    0x22,   0x2,    0x2,    0x5b,
      0x5c,  0x5,    0x6,    0x4,    0x2,    0x5c,   0x5d,   0x7,    0x23,
      0x2,   0x2,    0x5d,   0x5e,   0x7,    0x19,   0x2,    0x2,    0x5e,
      0x5f,  0x5,    0x8,    0x5,    0x2,    0x5f,   0x6d,   0x3,    0x2,
      0x2,   0x2,    0x60,   0x61,   0x7,    0x22,   0x2,    0x2,    0x61,
      0x62,  0x5,    0x6,    0x4,    0x2,    0x62,   0x63,   0x7,    0x23,
      0x2,   0x2,    0x63,   0x64,   0x7,    0x1a,   0x2,    0x2,    0x64,
      0x65,  0x5,    0x8,    0x5,    0x2,    0x65,   0x6d,   0x3,    0x2,
      0x2,   0x2,    0x66,   0x67,   0x7,    0x22,   0x2,    0x2,    0x67,
      0x68,  0x5,    0x6,    0x4,    0x2,    0x68,   0x69,   0x7,    0x23,
      0x2,   0x2,    0x69,   0x6a,   0x7,    0x1b,   0x2,    0x2,    0x6a,
      0x6b,  0x5,    0x8,    0x5,    0x2,    0x6b,   0x6d,   0x3,    0x2,
      0x2,   0x2,    0x6c,   0x3c,   0x3,    0x2,    0x2,    0x2,    0x6c,
      0x40,  0x3,    0x2,    0x2,    0x2,    0x6c,   0x44,   0x3,    0x2,
      0x2,   0x2,    0x6c,   0x4c,   0x3,    0x2,    0x2,    0x2,    0x6c,
      0x54,  0x3,    0x2,    0x2,    0x2,    0x6c,   0x5a,   0x3,    0x2,
      0x2,   0x2,    0x6c,   0x60,   0x3,    0x2,    0x2,    0x2,    0x6c,
      0x66,  0x3,    0x2,    0x2,    0x2,    0x6d,   0x5,    0x3,    0x2,
      0x2,   0x2,    0x6e,   0x6f,   0x8,    0x4,    0x1,    0x2,    0x6f,
      0x90,  0x5,    0x12,   0xa,    0x2,    0x70,   0x72,   0x7,    0x40,
      0x2,   0x2,    0x71,   0x70,   0x3,    0x2,    0x2,    0x2,    0x71,
      0x72,  0x3,    0x2,    0x2,    0x2,    0x72,   0x73,   0x3,    0x2,
      0x2,   0x2,    0x73,   0x90,   0x5,    0xa,    0x6,    0x2,    0x74,
      0x90,  0x7,    0xc,    0x2,    0x2,    0x75,   0x76,   0x7,    0x26,
      0x2,   0x2,    0x76,   0x77,   0x5,    0x6,    0x4,    0x2,    0x77,
      0x78,  0x7,    0x27,   0x2,    0x2,    0x78,   0x90,   0x3,    0x2,
      0x2,   0x2,    0x79,   0x7a,   0x7,    0x22,   0x2,    0x2,    0x7a,
      0x7b,  0x5,    0x6,    0x4,    0x2,    0x7b,   0x7c,   0x7,    0x23,
      0x2,   0x2,    0x7c,   0x90,   0x3,    0x2,    0x2,    0x2,    0x7d,
      0x7f,  0x7,    0x1d,   0x2,    0x2,    0x7e,   0x80,   0x7,    0x24,
      0x2,   0x2,    0x7f,   0x7e,   0x3,    0x2,    0x2,    0x2,    0x7f,
      0x80,  0x3,    0x2,    0x2,    0x2,    0x80,   0x81,   0x3,    0x2,
      0x2,   0x2,    0x81,   0x83,   0x7,    0x29,   0x2,    0x2,    0x82,
      0x84,  0x7,    0x13,   0x2,    0x2,    0x83,   0x82,   0x3,    0x2,
      0x2,   0x2,    0x83,   0x84,   0x3,    0x2,    0x2,    0x2,    0x84,
      0x86,  0x3,    0x2,    0x2,    0x2,    0x85,   0x87,   0x7,    0x29,
      0x2,   0x2,    0x86,   0x85,   0x3,    0x2,    0x2,    0x2,    0x86,
      0x87,  0x3,    0x2,    0x2,    0x2,    0x87,   0x89,   0x3,    0x2,
      0x2,   0x2,    0x88,   0x8a,   0x7,    0x25,   0x2,    0x2,    0x89,
      0x88,  0x3,    0x2,    0x2,    0x2,    0x89,   0x8a,   0x3,    0x2,
      0x2,   0x2,    0x8a,   0x8b,   0x3,    0x2,    0x2,    0x2,    0x8b,
      0x90,  0x5,    0x6,    0x4,    0x7,    0x8c,   0x90,   0x5,    0xc,
      0x7,   0x2,    0x8d,   0x90,   0x5,    0xe,    0x8,    0x2,    0x8e,
      0x90,  0x5,    0x10,   0x9,    0x2,    0x8f,   0x6e,   0x3,    0x2,
      0x2,   0x2,    0x8f,   0x71,   0x3,    0x2,    0x2,    0x2,    0x8f,
      0x74,  0x3,    0x2,    0x2,    0x2,    0x8f,   0x75,   0x3,    0x2,
      0x2,   0x2,    0x8f,   0x79,   0x3,    0x2,    0x2,    0x2,    0x8f,
      0x7d,  0x3,    0x2,    0x2,    0x2,    0x8f,   0x8c,   0x3,    0x2,
      0x2,   0x2,    0x8f,   0x8d,   0x3,    0x2,    0x2,    0x2,    0x8f,
      0x8e,  0x3,    0x2,    0x2,    0x2,    0x90,   0xdb,   0x3,    0x2,
      0x2,   0x2,    0x91,   0x92,   0xc,    0x10,   0x2,    0x2,    0x92,
      0x93,  0x7,    0x39,   0x2,    0x2,    0x93,   0xda,   0x5,    0x6,
      0x4,   0x11,   0x94,   0x95,   0xc,    0xf,    0x2,    0x2,    0x95,
      0x96,  0x7,    0x38,   0x2,    0x2,    0x96,   0xda,   0x5,    0x6,
      0x4,   0x10,   0x97,   0x98,   0xc,    0xe,    0x2,    0x2,    0x98,
      0x99,  0x7,    0x3e,   0x2,    0x2,    0x99,   0xda,   0x5,    0x6,
      0x4,   0xf,    0x9a,   0x9b,   0xc,    0xd,    0x2,    0x2,    0x9b,
      0x9c,  0x7,    0x1e,   0x2,    0x2,    0x9c,   0xda,   0x5,    0x6,
      0x4,   0xe,    0x9d,   0x9e,   0xc,    0xc,    0x2,    0x2,    0x9e,
      0x9f,  0x7,    0x1f,   0x2,    0x2,    0x9f,   0xda,   0x5,    0x6,
      0x4,   0xd,    0xa0,   0xa1,   0xc,    0x6,    0x2,    0x2,    0xa1,
      0xa3,  0x7,    0x1d,   0x2,    0x2,    0xa2,   0xa4,   0x7,    0x24,
      0x2,   0x2,    0xa3,   0xa2,   0x3,    0x2,    0x2,    0x2,    0xa3,
      0xa4,  0x3,    0x2,    0x2,    0x2,    0xa4,   0xa6,   0x3,    0x2,
      0x2,   0x2,    0xa5,   0xa7,   0x7,    0x29,   0x2,    0x2,    0xa6,
      0xa5,  0x3,    0x2,    0x2,    0x2,    0xa6,   0xa7,   0x3,    0x2,
      0x2,   0x2,    0xa7,   0xa9,   0x3,    0x2,    0x2,    0x2,    0xa8,
      0xaa,  0x7,    0x13,   0x2,    0x2,    0xa9,   0xa8,   0x3,    0x2,
      0x2,   0x2,    0xa9,   0xaa,   0x3,    0x2,    0x2,    0x2,    0xaa,
      0xac,  0x3,    0x2,    0x2,    0x2,    0xab,   0xad,   0x7,    0x29,
      0x2,   0x2,    0xac,   0xab,   0x3,    0x2,    0x2,    0x2,    0xac,
      0xad,  0x3,    0x2,    0x2,    0x2,    0xad,   0xaf,   0x3,    0x2,
      0x2,   0x2,    0xae,   0xb0,   0x7,    0x25,   0x2,    0x2,    0xaf,
      0xae,  0x3,    0x2,    0x2,    0x2,    0xaf,   0xb0,   0x3,    0x2,
      0x2,   0x2,    0xb0,   0xb1,   0x3,    0x2,    0x2,    0x2,    0xb1,
      0xda,  0x5,    0x6,    0x4,    0x7,    0xb2,   0xb3,   0xc,    0xb,
      0x2,   0x2,    0xb3,   0xb4,   0x7,    0x24,   0x2,    0x2,    0xb4,
      0xb6,  0x7,    0x30,   0x2,    0x2,    0xb5,   0xb7,   0x7,    0x29,
      0x2,   0x2,    0xb6,   0xb5,   0x3,    0x2,    0x2,    0x2,    0xb6,
      0xb7,  0x3,    0x2,    0x2,    0x2,    0xb7,   0xb9,   0x3,    0x2,
      0x2,   0x2,    0xb8,   0xba,   0x7,    0x13,   0x2,    0x2,    0xb9,
      0xb8,  0x3,    0x2,    0x2,    0x2,    0xb9,   0xba,   0x3,    0x2,
      0x2,   0x2,    0xba,   0xbc,   0x3,    0x2,    0x2,    0x2,    0xbb,
      0xbd,  0x7,    0x29,   0x2,    0x2,    0xbc,   0xbb,   0x3,    0x2,
      0x2,   0x2,    0xbc,   0xbd,   0x3,    0x2,    0x2,    0x2,    0xbd,
      0xbe,  0x3,    0x2,    0x2,    0x2,    0xbe,   0xda,   0x7,    0x25,
      0x2,   0x2,    0xbf,   0xc0,   0xc,    0xa,    0x2,    0x2,    0xc0,
      0xc1,  0x7,    0x24,   0x2,    0x2,    0xc1,   0xc2,   0x7,    0x2e,
      0x2,   0x2,    0xc2,   0xda,   0x7,    0x25,   0x2,    0x2,    0xc3,
      0xc4,  0xc,    0x9,    0x2,    0x2,    0xc4,   0xc5,   0x7,    0x24,
      0x2,   0x2,    0xc5,   0xc6,   0x7,    0x1c,   0x2,    0x2,    0xc6,
      0xc8,  0x7,    0x29,   0x2,    0x2,    0xc7,   0xc9,   0x7,    0x13,
      0x2,   0x2,    0xc8,   0xc7,   0x3,    0x2,    0x2,    0x2,    0xc8,
      0xc9,  0x3,    0x2,    0x2,    0x2,    0xc9,   0xcb,   0x3,    0x2,
      0x2,   0x2,    0xca,   0xcc,   0x7,    0x29,   0x2,    0x2,    0xcb,
      0xca,  0x3,    0x2,    0x2,    0x2,    0xcb,   0xcc,   0x3,    0x2,
      0x2,   0x2,    0xcc,   0xcd,   0x3,    0x2,    0x2,    0x2,    0xcd,
      0xda,  0x7,    0x25,   0x2,    0x2,    0xce,   0xcf,   0xc,    0x8,
      0x2,   0x2,    0xcf,   0xd0,   0x7,    0x24,   0x2,    0x2,    0xd0,
      0xd1,  0x7,    0x14,   0x2,    0x2,    0xd1,   0xd3,   0x7,    0x29,
      0x2,   0x2,    0xd2,   0xd4,   0x7,    0x13,   0x2,    0x2,    0xd3,
      0xd2,  0x3,    0x2,    0x2,    0x2,    0xd3,   0xd4,   0x3,    0x2,
      0x2,   0x2,    0xd4,   0xd6,   0x3,    0x2,    0x2,    0x2,    0xd5,
      0xd7,  0x7,    0x29,   0x2,    0x2,    0xd6,   0xd5,   0x3,    0x2,
      0x2,   0x2,    0xd6,   0xd7,   0x3,    0x2,    0x2,    0x2,    0xd7,
      0xd8,  0x3,    0x2,    0x2,    0x2,    0xd8,   0xda,   0x7,    0x25,
      0x2,   0x2,    0xd9,   0x91,   0x3,    0x2,    0x2,    0x2,    0xd9,
      0x94,  0x3,    0x2,    0x2,    0x2,    0xd9,   0x97,   0x3,    0x2,
      0x2,   0x2,    0xd9,   0x9a,   0x3,    0x2,    0x2,    0x2,    0xd9,
      0x9d,  0x3,    0x2,    0x2,    0x2,    0xd9,   0xa0,   0x3,    0x2,
      0x2,   0x2,    0xd9,   0xb2,   0x3,    0x2,    0x2,    0x2,    0xd9,
      0xbf,  0x3,    0x2,    0x2,    0x2,    0xd9,   0xc3,   0x3,    0x2,
      0x2,   0x2,    0xd9,   0xce,   0x3,    0x2,    0x2,    0x2,    0xda,
      0xdd,  0x3,    0x2,    0x2,    0x2,    0xdb,   0xd9,   0x3,    0x2,
      0x2,   0x2,    0xdb,   0xdc,   0x3,    0x2,    0x2,    0x2,    0xdc,
      0x7,   0x3,    0x2,    0x2,    0x2,    0xdd,   0xdb,   0x3,    0x2,
      0x2,   0x2,    0xde,   0xdf,   0x8,    0x5,    0x1,    0x2,    0xdf,
      0xf4,  0x5,    0x12,   0xa,    0x2,    0xe0,   0xf4,   0x5,    0xa,
      0x6,   0x2,    0xe1,   0xf4,   0x7,    0xc,    0x2,    0x2,    0xe2,
      0xe3,  0x7,    0x26,   0x2,    0x2,    0xe3,   0xe4,   0x5,    0x8,
      0x5,   0x2,    0xe4,   0xe5,   0x7,    0x27,   0x2,    0x2,    0xe5,
      0xf4,  0x3,    0x2,    0x2,    0x2,    0xe6,   0xe7,   0x7,    0x40,
      0x2,   0x2,    0xe7,   0xf4,   0x5,    0x8,    0x5,    0xb,    0xe8,
      0xe9,  0x7,    0x10,   0x2,    0x2,    0xe9,   0xea,   0x7,    0x24,
      0x2,   0x2,    0xea,   0xeb,   0x7,    0x29,   0x2,    0x2,    0xeb,
      0xec,  0x7,    0x25,   0x2,    0x2,    0xec,   0xf4,   0x5,    0x8,
      0x5,   0x5,    0xed,   0xee,   0x7,    0x10,   0x2,    0x2,    0xee,
      0xf4,  0x5,    0x8,    0x5,    0x4,    0xef,   0xf0,   0x7,    0x22,
      0x2,   0x2,    0xf0,   0xf1,   0x5,    0x6,    0x4,    0x2,    0xf1,
      0xf2,  0x7,    0x23,   0x2,    0x2,    0xf2,   0xf4,   0x3,    0x2,
      0x2,   0x2,    0xf3,   0xde,   0x3,    0x2,    0x2,    0x2,    0xf3,
      0xe0,  0x3,    0x2,    0x2,    0x2,    0xf3,   0xe1,   0x3,    0x2,
      0x2,   0x2,    0xf3,   0xe2,   0x3,    0x2,    0x2,    0x2,    0xf3,
      0xe6,  0x3,    0x2,    0x2,    0x2,    0xf3,   0xe8,   0x3,    0x2,
      0x2,   0x2,    0xf3,   0xed,   0x3,    0x2,    0x2,    0x2,    0xf3,
      0xef,  0x3,    0x2,    0x2,    0x2,    0xf4,   0x106,  0x3,    0x2,
      0x2,   0x2,    0xf5,   0xf6,   0xc,    0xa,    0x2,    0x2,    0xf6,
      0xf7,  0x7,    0x3e,   0x2,    0x2,    0xf7,   0x105,  0x5,    0x8,
      0x5,   0xb,    0xf8,   0xf9,   0xc,    0x9,    0x2,    0x2,    0xf9,
      0xfa,  0x7,    0x3f,   0x2,    0x2,    0xfa,   0x105,  0x5,    0x8,
      0x5,   0xa,    0xfb,   0xfc,   0xc,    0x8,    0x2,    0x2,    0xfc,
      0xfd,  0x7,    0x17,   0x2,    0x2,    0xfd,   0x105,  0x5,    0x8,
      0x5,   0x9,    0xfe,   0xff,   0xc,    0x7,    0x2,    0x2,    0xff,
      0x100, 0x7,    0x11,   0x2,    0x2,    0x100,  0x105,  0x5,    0x8,
      0x5,   0x8,    0x101,  0x102,  0xc,    0x6,    0x2,    0x2,    0x102,
      0x103, 0x7,    0x12,   0x2,    0x2,    0x103,  0x105,  0x5,    0x8,
      0x5,   0x7,    0x104,  0xf5,   0x3,    0x2,    0x2,    0x2,    0x104,
      0xf8,  0x3,    0x2,    0x2,    0x2,    0x104,  0xfb,   0x3,    0x2,
      0x2,   0x2,    0x104,  0xfe,   0x3,    0x2,    0x2,    0x2,    0x104,
      0x101, 0x3,    0x2,    0x2,    0x2,    0x105,  0x108,  0x3,    0x2,
      0x2,   0x2,    0x106,  0x104,  0x3,    0x2,    0x2,    0x2,    0x106,
      0x107, 0x3,    0x2,    0x2,    0x2,    0x107,  0x9,    0x3,    0x2,
      0x2,   0x2,    0x108,  0x106,  0x3,    0x2,    0x2,    0x2,    0x109,
      0x10a, 0x7,    0x3,    0x2,    0x2,    0x10a,  0x10b,  0x7,    0x29,
      0x2,   0x2,    0x10b,  0xb,    0x3,    0x2,    0x2,    0x2,    0x10c,
      0x10d, 0x7,    0x4,    0x2,    0x2,    0x10d,  0x10e,  0x7,    0x29,
      0x2,   0x2,    0x10e,  0x10f,  0x7,    0x13,   0x2,    0x2,    0x10f,
      0xd,   0x3,    0x2,    0x2,    0x2,    0x110,  0x111,  0x7,    0x5,
      0x2,   0x2,    0x111,  0x112,  0x7,    0x29,   0x2,    0x2,    0x112,
      0x113, 0x7,    0x38,   0x2,    0x2,    0x113,  0x114,  0x7,    0x13,
      0x2,   0x2,    0x114,  0xf,    0x3,    0x2,    0x2,    0x2,    0x115,
      0x116, 0x7,    0x6,    0x2,    0x2,    0x116,  0x117,  0x7,    0x29,
      0x2,   0x2,    0x117,  0x118,  0x7,    0x25,   0x2,    0x2,    0x118,
      0x119, 0x7,    0xd,    0x2,    0x2,    0x119,  0x11a,  0x7,    0x13,
      0x2,   0x2,    0x11a,  0x11,   0x3,    0x2,    0x2,    0x2,    0x11b,
      0x11c, 0x8,    0xa,    0x1,    0x2,    0x11c,  0x11d,  0x7,    0x40,
      0x2,   0x2,    0x11d,  0x13e,  0x5,    0x12,   0xa,    0x11,   0x11e,
      0x11f, 0x5,    0x1a,   0xe,    0x2,    0x11f,  0x120,  0x5,    0x2e,
      0x18,  0x2,    0x120,  0x121,  0x5,    0x1a,   0xe,    0x2,    0x121,
      0x13e, 0x3,    0x2,    0x2,    0x2,    0x122,  0x123,  0x5,    0x24,
      0x13,  0x2,    0x123,  0x124,  0x5,    0x2e,   0x18,   0x2,    0x124,
      0x125, 0x5,    0x24,   0x13,   0x2,    0x125,  0x13e,  0x3,    0x2,
      0x2,   0x2,    0x126,  0x127,  0x5,    0x1a,   0xe,    0x2,    0x127,
      0x128, 0x7,    0x36,   0x2,    0x2,    0x128,  0x129,  0x5,    0x1a,
      0xe,   0x2,    0x129,  0x13e,  0x3,    0x2,    0x2,    0x2,    0x12a,
      0x12b, 0x5,    0x24,   0x13,   0x2,    0x12b,  0x12c,  0x7,    0x36,
      0x2,   0x2,    0x12c,  0x12d,  0x5,    0x24,   0x13,   0x2,    0x12d,
      0x13e, 0x3,    0x2,    0x2,    0x2,    0x12e,  0x12f,  0x5,    0x1a,
      0xe,   0x2,    0x12f,  0x130,  0x7,    0x37,   0x2,    0x2,    0x130,
      0x131, 0x5,    0x1a,   0xe,    0x2,    0x131,  0x13e,  0x3,    0x2,
      0x2,   0x2,    0x132,  0x133,  0x5,    0x24,   0x13,   0x2,    0x133,
      0x134, 0x7,    0x37,   0x2,    0x2,    0x134,  0x135,  0x5,    0x24,
      0x13,  0x2,    0x135,  0x13e,  0x3,    0x2,    0x2,    0x2,    0x136,
      0x13e, 0x5,    0x14,   0xb,    0x2,    0x137,  0x13e,  0x5,    0x1a,
      0xe,   0x2,    0x138,  0x13e,  0x5,    0x24,   0x13,   0x2,    0x139,
      0x13a, 0x7,    0x26,   0x2,    0x2,    0x13a,  0x13b,  0x5,    0x12,
      0xa,   0x2,    0x13b,  0x13c,  0x7,    0x27,   0x2,    0x2,    0x13c,
      0x13e, 0x3,    0x2,    0x2,    0x2,    0x13d,  0x11b,  0x3,    0x2,
      0x2,   0x2,    0x13d,  0x11e,  0x3,    0x2,    0x2,    0x2,    0x13d,
      0x122, 0x3,    0x2,    0x2,    0x2,    0x13d,  0x126,  0x3,    0x2,
      0x2,   0x2,    0x13d,  0x12a,  0x3,    0x2,    0x2,    0x2,    0x13d,
      0x12e, 0x3,    0x2,    0x2,    0x2,    0x13d,  0x132,  0x3,    0x2,
      0x2,   0x2,    0x13d,  0x136,  0x3,    0x2,    0x2,    0x2,    0x13d,
      0x137, 0x3,    0x2,    0x2,    0x2,    0x13d,  0x138,  0x3,    0x2,
      0x2,   0x2,    0x13d,  0x139,  0x3,    0x2,    0x2,    0x2,    0x13e,
      0x14d, 0x3,    0x2,    0x2,    0x2,    0x13f,  0x140,  0xc,    0xc,
      0x2,   0x2,    0x140,  0x141,  0x7,    0x36,   0x2,    0x2,    0x141,
      0x14c, 0x5,    0x12,   0xa,    0xd,    0x142,  0x143,  0xc,    0x9,
      0x2,   0x2,    0x143,  0x144,  0x7,    0x37,   0x2,    0x2,    0x144,
      0x14c, 0x5,    0x12,   0xa,    0xa,    0x145,  0x146,  0xc,    0x8,
      0x2,   0x2,    0x146,  0x147,  0x7,    0x3e,   0x2,    0x2,    0x147,
      0x14c, 0x5,    0x12,   0xa,    0x9,    0x148,  0x149,  0xc,    0x7,
      0x2,   0x2,    0x149,  0x14a,  0x7,    0x3f,   0x2,    0x2,    0x14a,
      0x14c, 0x5,    0x12,   0xa,    0x8,    0x14b,  0x13f,  0x3,    0x2,
      0x2,   0x2,    0x14b,  0x142,  0x3,    0x2,    0x2,    0x2,    0x14b,
      0x145, 0x3,    0x2,    0x2,    0x2,    0x14b,  0x148,  0x3,    0x2,
      0x2,   0x2,    0x14c,  0x14f,  0x3,    0x2,    0x2,    0x2,    0x14d,
      0x14b, 0x3,    0x2,    0x2,    0x2,    0x14d,  0x14e,  0x3,    0x2,
      0x2,   0x2,    0x14e,  0x13,   0x3,    0x2,    0x2,    0x2,    0x14f,
      0x14d, 0x3,    0x2,    0x2,    0x2,    0x150,  0x153,  0x5,    0x16,
      0xc,   0x2,    0x151,  0x153,  0x5,    0x18,   0xd,    0x2,    0x152,
      0x150, 0x3,    0x2,    0x2,    0x2,    0x152,  0x151,  0x3,    0x2,
      0x2,   0x2,    0x153,  0x15,   0x3,    0x2,    0x2,    0x2,    0x154,
      0x155, 0x7,    0x2d,   0x2,    0x2,    0x155,  0x17,   0x3,    0x2,
      0x2,   0x2,    0x156,  0x157,  0x7,    0x34,   0x2,    0x2,    0x157,
      0x158, 0x5,    0x2c,   0x17,   0x2,    0x158,  0x159,  0x7,    0x7,
      0x2,   0x2,    0x159,  0x19,   0x3,    0x2,    0x2,    0x2,    0x15a,
      0x15b, 0x8,    0xe,    0x1,    0x2,    0x15b,  0x15c,  0x7,    0x3b,
      0x2,   0x2,    0x15c,  0x163,  0x5,    0x1a,   0xe,    0xd,    0x15d,
      0x163, 0x5,    0x1e,   0x10,   0x2,    0x15e,  0x15f,  0x7,    0x26,
      0x2,   0x2,    0x15f,  0x160,  0x5,    0x1a,   0xe,    0x2,    0x160,
      0x161, 0x7,    0x27,   0x2,    0x2,    0x161,  0x163,  0x3,    0x2,
      0x2,   0x2,    0x162,  0x15a,  0x3,    0x2,    0x2,    0x2,    0x162,
      0x15d, 0x3,    0x2,    0x2,    0x2,    0x162,  0x15e,  0x3,    0x2,
      0x2,   0x2,    0x163,  0x17d,  0x3,    0x2,    0x2,    0x2,    0x164,
      0x165, 0xc,    0xb,    0x2,    0x2,    0x165,  0x166,  0x9,    0x2,
      0x2,   0x2,    0x166,  0x17c,  0x5,    0x1a,   0xe,    0xc,    0x167,
      0x168, 0xc,    0xa,    0x2,    0x2,    0x168,  0x169,  0x9,    0x3,
      0x2,   0x2,    0x169,  0x17c,  0x5,    0x1a,   0xe,    0xb,    0x16a,
      0x16b, 0xc,    0x9,    0x2,    0x2,    0x16b,  0x16c,  0x7,    0x3c,
      0x2,   0x2,    0x16c,  0x17c,  0x5,    0x1a,   0xe,    0xa,    0x16d,
      0x16e, 0xc,    0x8,    0x2,    0x2,    0x16e,  0x16f,  0x7,    0x3d,
      0x2,   0x2,    0x16f,  0x17c,  0x5,    0x1a,   0xe,    0x9,    0x170,
      0x171, 0xc,    0x7,    0x2,    0x2,    0x171,  0x172,  0x7,    0x38,
      0x2,   0x2,    0x172,  0x17c,  0x5,    0x1a,   0xe,    0x8,    0x173,
      0x174, 0xc,    0x6,    0x2,    0x2,    0x174,  0x175,  0x7,    0x3a,
      0x2,   0x2,    0x175,  0x17c,  0x5,    0x1a,   0xe,    0x7,    0x176,
      0x177, 0xc,    0x5,    0x2,    0x2,    0x177,  0x178,  0x7,    0x39,
      0x2,   0x2,    0x178,  0x17c,  0x5,    0x1a,   0xe,    0x6,    0x179,
      0x17a, 0xc,    0xc,    0x2,    0x2,    0x17a,  0x17c,  0x5,    0x1c,
      0xf,   0x2,    0x17b,  0x164,  0x3,    0x2,    0x2,    0x2,    0x17b,
      0x167, 0x3,    0x2,    0x2,    0x2,    0x17b,  0x16a,  0x3,    0x2,
      0x2,   0x2,    0x17b,  0x16d,  0x3,    0x2,    0x2,    0x2,    0x17b,
      0x170, 0x3,    0x2,    0x2,    0x2,    0x17b,  0x173,  0x3,    0x2,
      0x2,   0x2,    0x17b,  0x176,  0x3,    0x2,    0x2,    0x2,    0x17b,
      0x179, 0x3,    0x2,    0x2,    0x2,    0x17c,  0x17f,  0x3,    0x2,
      0x2,   0x2,    0x17d,  0x17b,  0x3,    0x2,    0x2,    0x2,    0x17d,
      0x17e, 0x3,    0x2,    0x2,    0x2,    0x17e,  0x1b,   0x3,    0x2,
      0x2,   0x2,    0x17f,  0x17d,  0x3,    0x2,    0x2,    0x2,    0x180,
      0x181, 0x7,    0x24,   0x2,    0x2,    0x181,  0x184,  0x7,    0x29,
      0x2,   0x2,    0x182,  0x183,  0x7,    0x1f,   0x2,    0x2,    0x183,
      0x185, 0x7,    0x29,   0x2,    0x2,    0x184,  0x182,  0x3,    0x2,
      0x2,   0x2,    0x184,  0x185,  0x3,    0x2,    0x2,    0x2,    0x185,
      0x186, 0x3,    0x2,    0x2,    0x2,    0x186,  0x187,  0x7,    0x25,
      0x2,   0x2,    0x187,  0x1d,   0x3,    0x2,    0x2,    0x2,    0x188,
      0x18b, 0x5,    0x20,   0x11,   0x2,    0x189,  0x18b,  0x5,    0x22,
      0x12,  0x2,    0x18a,  0x188,  0x3,    0x2,    0x2,    0x2,    0x18a,
      0x189, 0x3,    0x2,    0x2,    0x2,    0x18b,  0x1f,   0x3,    0x2,
      0x2,   0x2,    0x18c,  0x18d,  0x9,    0x4,    0x2,    0x2,    0x18d,
      0x21,  0x3,    0x2,    0x2,    0x2,    0x18e,  0x18f,  0x7,    0x34,
      0x2,   0x2,    0x18f,  0x190,  0x5,    0x2c,   0x17,   0x2,    0x190,
      0x191, 0x7,    0x8,    0x2,    0x2,    0x191,  0x192,  0x7,    0x21,
      0x2,   0x2,    0x192,  0x193,  0x7,    0x9,    0x2,    0x2,    0x193,
      0x194, 0x7,    0x29,   0x2,    0x2,    0x194,  0x195,  0x7,    0xa,
      0x2,   0x2,    0x195,  0x23,   0x3,    0x2,    0x2,    0x2,    0x196,
      0x197, 0x8,    0x13,   0x1,    0x2,    0x197,  0x19e,  0x5,    0x26,
      0x14,  0x2,    0x198,  0x19e,  0x5,    0x1a,   0xe,    0x2,    0x199,
      0x19a, 0x7,    0x26,   0x2,    0x2,    0x19a,  0x19b,  0x5,    0x24,
      0x13,  0x2,    0x19b,  0x19c,  0x7,    0x27,   0x2,    0x2,    0x19c,
      0x19e, 0x3,    0x2,    0x2,    0x2,    0x19d,  0x196,  0x3,    0x2,
      0x2,   0x2,    0x19d,  0x198,  0x3,    0x2,    0x2,    0x2,    0x19d,
      0x199, 0x3,    0x2,    0x2,    0x2,    0x19e,  0x1a7,  0x3,    0x2,
      0x2,   0x2,    0x19f,  0x1a0,  0xc,    0x7,    0x2,    0x2,    0x1a0,
      0x1a1, 0x9,    0x2,    0x2,    0x2,    0x1a1,  0x1a6,  0x5,    0x24,
      0x13,  0x8,    0x1a2,  0x1a3,  0xc,    0x6,    0x2,    0x2,    0x1a3,
      0x1a4, 0x9,    0x3,    0x2,    0x2,    0x1a4,  0x1a6,  0x5,    0x24,
      0x13,  0x7,    0x1a5,  0x19f,  0x3,    0x2,    0x2,    0x2,    0x1a5,
      0x1a2, 0x3,    0x2,    0x2,    0x2,    0x1a6,  0x1a9,  0x3,    0x2,
      0x2,   0x2,    0x1a7,  0x1a5,  0x3,    0x2,    0x2,    0x2,    0x1a7,
      0x1a8, 0x3,    0x2,    0x2,    0x2,    0x1a8,  0x25,   0x3,    0x2,
      0x2,   0x2,    0x1a9,  0x1a7,  0x3,    0x2,    0x2,    0x2,    0x1aa,
      0x1ad, 0x5,    0x28,   0x15,   0x2,    0x1ab,  0x1ad,  0x5,    0x2a,
      0x16,  0x2,    0x1ac,  0x1aa,  0x3,    0x2,    0x2,    0x2,    0x1ac,
      0x1ab, 0x3,    0x2,    0x2,    0x2,    0x1ad,  0x27,   0x3,    0x2,
      0x2,   0x2,    0x1ae,  0x1af,  0x7,    0x29,   0x2,    0x2,    0x1af,
      0x29,  0x3,    0x2,    0x2,    0x2,    0x1b0,  0x1b1,  0x7,    0x34,
      0x2,   0x2,    0x1b1,  0x1b2,  0x5,    0x2c,   0x17,   0x2,    0x1b2,
      0x1b3, 0x7,    0xb,    0x2,    0x2,    0x1b3,  0x1b4,  0x7,    0x29,
      0x2,   0x2,    0x1b4,  0x1b5,  0x7,    0xa,    0x2,    0x2,    0x1b5,
      0x2b,  0x3,    0x2,    0x2,    0x2,    0x1b6,  0x1b7,  0x7,    0x28,
      0x2,   0x2,    0x1b7,  0x2d,   0x3,    0x2,    0x2,    0x2,    0x1b8,
      0x1b9, 0x9,    0x5,    0x2,    0x2,    0x1b9,  0x2f,   0x3,    0x2,
      0x2,   0x2,    0x28,   0x3a,   0x6c,   0x71,   0x7f,   0x83,   0x86,
      0x89,  0x8f,   0xa3,   0xa6,   0xa9,   0xac,   0xaf,   0xb6,   0xb9,
      0xbc,  0xc8,   0xcb,   0xd3,   0xd6,   0xd9,   0xdb,   0xf3,   0x104,
      0x106, 0x13d,  0x14b,  0x14d,  0x152,  0x162,  0x17b,  0x17d,  0x184,
      0x18a, 0x19d,  0x1a5,  0x1a7,  0x1ac,
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

spotParser::Initializer spotParser::_init;
