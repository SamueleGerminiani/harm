
// Generated from temporalSVA.g4 by ANTLR 4.9.2


#include "temporalSVAListener.h"

#include "temporalSVAParser.h"


using namespace antlrcpp;
using namespace antlr4;

temporalSVAParser::temporalSVAParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

temporalSVAParser::~temporalSVAParser() {
  delete _interpreter;
}

std::string temporalSVAParser::getGrammarFileName() const {
  return "temporalSVA.g4";
}

const std::vector<std::string>& temporalSVAParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& temporalSVAParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- FileContext ------------------------------------------------------------------

temporalSVAParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::FileContext::ALWAYS() {
  return getToken(temporalSVAParser::ALWAYS, 0);
}

temporalSVAParser::FormulaContext* temporalSVAParser::FileContext::formula() {
  return getRuleContext<temporalSVAParser::FormulaContext>(0);
}

tree::TerminalNode* temporalSVAParser::FileContext::EOF() {
  return getToken(temporalSVAParser::EOF, 0);
}

tree::TerminalNode* temporalSVAParser::FileContext::LPAREN() {
  return getToken(temporalSVAParser::LPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::FileContext::RPAREN() {
  return getToken(temporalSVAParser::RPAREN, 0);
}


size_t temporalSVAParser::FileContext::getRuleIndex() const {
  return temporalSVAParser::RuleFile;
}

void temporalSVAParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void temporalSVAParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

temporalSVAParser::FileContext* temporalSVAParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, temporalSVAParser::RuleFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(54);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(44);
      match(temporalSVAParser::ALWAYS);
      setState(45);
      formula();
      setState(46);
      match(temporalSVAParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(48);
      match(temporalSVAParser::ALWAYS);
      setState(49);
      match(temporalSVAParser::LPAREN);
      setState(50);
      formula();
      setState(51);
      match(temporalSVAParser::RPAREN);
      setState(52);
      match(temporalSVAParser::EOF);
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

temporalSVAParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<temporalSVAParser::TformulaContext *> temporalSVAParser::FormulaContext::tformula() {
  return getRuleContexts<temporalSVAParser::TformulaContext>();
}

temporalSVAParser::TformulaContext* temporalSVAParser::FormulaContext::tformula(size_t i) {
  return getRuleContext<temporalSVAParser::TformulaContext>(i);
}

tree::TerminalNode* temporalSVAParser::FormulaContext::IMPL() {
  return getToken(temporalSVAParser::IMPL, 0);
}

tree::TerminalNode* temporalSVAParser::FormulaContext::IMPL2() {
  return getToken(temporalSVAParser::IMPL2, 0);
}

tree::TerminalNode* temporalSVAParser::FormulaContext::LGPAREN() {
  return getToken(temporalSVAParser::LGPAREN, 0);
}

temporalSVAParser::SereContext* temporalSVAParser::FormulaContext::sere() {
  return getRuleContext<temporalSVAParser::SereContext>(0);
}

tree::TerminalNode* temporalSVAParser::FormulaContext::RGPAREN() {
  return getToken(temporalSVAParser::RGPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::FormulaContext::LCPAREN() {
  return getToken(temporalSVAParser::LCPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::FormulaContext::RCPAREN() {
  return getToken(temporalSVAParser::RCPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::FormulaContext::BIND1() {
  return getToken(temporalSVAParser::BIND1, 0);
}

tree::TerminalNode* temporalSVAParser::FormulaContext::BIND2() {
  return getToken(temporalSVAParser::BIND2, 0);
}


size_t temporalSVAParser::FormulaContext::getRuleIndex() const {
  return temporalSVAParser::RuleFormula;
}

void temporalSVAParser::FormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormula(this);
}

void temporalSVAParser::FormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormula(this);
}

temporalSVAParser::FormulaContext* temporalSVAParser::formula() {
  FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, getState());
  enterRule(_localctx, 2, temporalSVAParser::RuleFormula);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(92);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(56);
      tformula(0);
      setState(57);
      match(temporalSVAParser::IMPL);
      setState(58);
      tformula(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(60);
      tformula(0);
      setState(61);
      match(temporalSVAParser::IMPL2);
      setState(62);
      tformula(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(64);
      match(temporalSVAParser::LGPAREN);
      setState(65);
      sere(0);
      setState(66);
      match(temporalSVAParser::RGPAREN);
      setState(67);
      match(temporalSVAParser::LCPAREN);
      setState(68);
      match(temporalSVAParser::RCPAREN);
      setState(69);
      match(temporalSVAParser::IMPL);
      setState(70);
      tformula(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(72);
      match(temporalSVAParser::LGPAREN);
      setState(73);
      sere(0);
      setState(74);
      match(temporalSVAParser::RGPAREN);
      setState(75);
      match(temporalSVAParser::LCPAREN);
      setState(76);
      match(temporalSVAParser::RCPAREN);
      setState(77);
      match(temporalSVAParser::IMPL2);
      setState(78);
      tformula(0);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(80);
      match(temporalSVAParser::LGPAREN);
      setState(81);
      sere(0);
      setState(82);
      match(temporalSVAParser::RGPAREN);
      setState(83);
      match(temporalSVAParser::BIND1);
      setState(84);
      tformula(0);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(86);
      match(temporalSVAParser::LGPAREN);
      setState(87);
      sere(0);
      setState(88);
      match(temporalSVAParser::RGPAREN);
      setState(89);
      match(temporalSVAParser::BIND2);
      setState(90);
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

temporalSVAParser::SereContext::SereContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalSVAParser::BooleanContext* temporalSVAParser::SereContext::boolean() {
  return getRuleContext<temporalSVAParser::BooleanContext>(0);
}

temporalSVAParser::PlaceholderContext* temporalSVAParser::SereContext::placeholder() {
  return getRuleContext<temporalSVAParser::PlaceholderContext>(0);
}

tree::TerminalNode* temporalSVAParser::SereContext::NOT() {
  return getToken(temporalSVAParser::NOT, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::BDT_AND() {
  return getToken(temporalSVAParser::BDT_AND, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::LPAREN() {
  return getToken(temporalSVAParser::LPAREN, 0);
}

std::vector<temporalSVAParser::SereContext *> temporalSVAParser::SereContext::sere() {
  return getRuleContexts<temporalSVAParser::SereContext>();
}

temporalSVAParser::SereContext* temporalSVAParser::SereContext::sere(size_t i) {
  return getRuleContext<temporalSVAParser::SereContext>(i);
}

tree::TerminalNode* temporalSVAParser::SereContext::RPAREN() {
  return getToken(temporalSVAParser::RPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::LGPAREN() {
  return getToken(temporalSVAParser::LGPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::RGPAREN() {
  return getToken(temporalSVAParser::RGPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::DELAY() {
  return getToken(temporalSVAParser::DELAY, 0);
}

std::vector<tree::TerminalNode *> temporalSVAParser::SereContext::NUMERIC() {
  return getTokens(temporalSVAParser::NUMERIC);
}

tree::TerminalNode* temporalSVAParser::SereContext::NUMERIC(size_t i) {
  return getToken(temporalSVAParser::NUMERIC, i);
}

tree::TerminalNode* temporalSVAParser::SereContext::LCPAREN() {
  return getToken(temporalSVAParser::LCPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::DOTS() {
  return getToken(temporalSVAParser::DOTS, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::RCPAREN() {
  return getToken(temporalSVAParser::RCPAREN, 0);
}

temporalSVAParser::Bdt_nextContext* temporalSVAParser::SereContext::bdt_next() {
  return getRuleContext<temporalSVAParser::Bdt_nextContext>(0);
}

temporalSVAParser::Bdt_next_andContext* temporalSVAParser::SereContext::bdt_next_and() {
  return getRuleContext<temporalSVAParser::Bdt_next_andContext>(0);
}

temporalSVAParser::Bdt_NCRepsContext* temporalSVAParser::SereContext::bdt_NCReps() {
  return getRuleContext<temporalSVAParser::Bdt_NCRepsContext>(0);
}

tree::TerminalNode* temporalSVAParser::SereContext::BOR() {
  return getToken(temporalSVAParser::BOR, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::BAND() {
  return getToken(temporalSVAParser::BAND, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::AND() {
  return getToken(temporalSVAParser::AND, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::SCOL() {
  return getToken(temporalSVAParser::SCOL, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::COL() {
  return getToken(temporalSVAParser::COL, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::TIMES() {
  return getToken(temporalSVAParser::TIMES, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::PLUS() {
  return getToken(temporalSVAParser::PLUS, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::ASS() {
  return getToken(temporalSVAParser::ASS, 0);
}

tree::TerminalNode* temporalSVAParser::SereContext::IMPL() {
  return getToken(temporalSVAParser::IMPL, 0);
}


size_t temporalSVAParser::SereContext::getRuleIndex() const {
  return temporalSVAParser::RuleSere;
}

void temporalSVAParser::SereContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSere(this);
}

void temporalSVAParser::SereContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSere(this);
}


temporalSVAParser::SereContext* temporalSVAParser::sere() {
   return sere(0);
}

temporalSVAParser::SereContext* temporalSVAParser::sere(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  temporalSVAParser::SereContext *_localctx = _tracker.createInstance<SereContext>(_ctx, parentState);
  temporalSVAParser::SereContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, temporalSVAParser::RuleSere, precedence);

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
    setState(127);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(95);
      boolean(0);
      break;
    }

    case 2: {
      setState(97);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalSVAParser::NOT) {
        setState(96);
        match(temporalSVAParser::NOT);
      }
      setState(99);
      placeholder();
      break;
    }

    case 3: {
      setState(100);
      match(temporalSVAParser::BDT_AND);
      break;
    }

    case 4: {
      setState(101);
      match(temporalSVAParser::LPAREN);
      setState(102);
      sere(0);
      setState(103);
      match(temporalSVAParser::RPAREN);
      break;
    }

    case 5: {
      setState(105);
      match(temporalSVAParser::LGPAREN);
      setState(106);
      sere(0);
      setState(107);
      match(temporalSVAParser::RGPAREN);
      break;
    }

    case 6: {
      setState(109);
      match(temporalSVAParser::DELAY);
      setState(111);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalSVAParser::LCPAREN) {
        setState(110);
        match(temporalSVAParser::LCPAREN);
      }
      setState(113);
      match(temporalSVAParser::NUMERIC);
      setState(115);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalSVAParser::DOTS) {
        setState(114);
        match(temporalSVAParser::DOTS);
      }
      setState(118);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(117);
        match(temporalSVAParser::NUMERIC);
        break;
      }

      default:
        break;
      }
      setState(121);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == temporalSVAParser::RCPAREN) {
        setState(120);
        match(temporalSVAParser::RCPAREN);
      }
      setState(123);
      sere(5);
      break;
    }

    case 7: {
      setState(124);
      bdt_next();
      break;
    }

    case 8: {
      setState(125);
      bdt_next_and();
      break;
    }

    case 9: {
      setState(126);
      bdt_NCReps();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(203);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(201);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(129);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(130);
          match(temporalSVAParser::BOR);
          setState(131);
          sere(15);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(132);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(133);
          match(temporalSVAParser::BAND);
          setState(134);
          sere(14);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(135);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(136);
          match(temporalSVAParser::AND);
          setState(137);
          sere(13);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(138);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(139);
          match(temporalSVAParser::SCOL);
          setState(140);
          sere(12);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(141);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(142);
          match(temporalSVAParser::COL);
          setState(143);
          sere(11);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(144);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(145);
          match(temporalSVAParser::DELAY);
          setState(147);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalSVAParser::LCPAREN) {
            setState(146);
            match(temporalSVAParser::LCPAREN);
          }
          setState(150);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
          case 1: {
            setState(149);
            match(temporalSVAParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(153);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalSVAParser::DOTS) {
            setState(152);
            match(temporalSVAParser::DOTS);
          }
          setState(156);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
          case 1: {
            setState(155);
            match(temporalSVAParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(159);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalSVAParser::RCPAREN) {
            setState(158);
            match(temporalSVAParser::RCPAREN);
          }
          setState(161);
          sere(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(162);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(163);
          match(temporalSVAParser::LCPAREN);
          setState(164);
          match(temporalSVAParser::TIMES);
          setState(166);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
          case 1: {
            setState(165);
            match(temporalSVAParser::NUMERIC);
            break;
          }

          default:
            break;
          }
          setState(169);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalSVAParser::DOTS) {
            setState(168);
            match(temporalSVAParser::DOTS);
          }
          setState(172);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalSVAParser::NUMERIC) {
            setState(171);
            match(temporalSVAParser::NUMERIC);
          }
          setState(174);
          match(temporalSVAParser::RCPAREN);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(175);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(176);
          match(temporalSVAParser::LCPAREN);
          setState(177);
          match(temporalSVAParser::PLUS);
          setState(178);
          match(temporalSVAParser::RCPAREN);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(179);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(180);
          match(temporalSVAParser::LCPAREN);
          setState(181);
          match(temporalSVAParser::ASS);
          setState(182);
          match(temporalSVAParser::NUMERIC);
          setState(184);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalSVAParser::DOTS) {
            setState(183);
            match(temporalSVAParser::DOTS);
          }
          setState(187);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalSVAParser::NUMERIC) {
            setState(186);
            match(temporalSVAParser::NUMERIC);
          }
          setState(189);
          match(temporalSVAParser::RCPAREN);
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<SereContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleSere);
          setState(190);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(191);
          match(temporalSVAParser::LCPAREN);
          setState(192);
          match(temporalSVAParser::IMPL);
          setState(193);
          match(temporalSVAParser::NUMERIC);
          setState(195);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalSVAParser::DOTS) {
            setState(194);
            match(temporalSVAParser::DOTS);
          }
          setState(198);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == temporalSVAParser::NUMERIC) {
            setState(197);
            match(temporalSVAParser::NUMERIC);
          }
          setState(200);
          match(temporalSVAParser::RCPAREN);
          break;
        }

        default:
          break;
        } 
      }
      setState(205);
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

//----------------- TformulaContext ------------------------------------------------------------------

temporalSVAParser::TformulaContext::TformulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalSVAParser::BooleanContext* temporalSVAParser::TformulaContext::boolean() {
  return getRuleContext<temporalSVAParser::BooleanContext>(0);
}

temporalSVAParser::PlaceholderContext* temporalSVAParser::TformulaContext::placeholder() {
  return getRuleContext<temporalSVAParser::PlaceholderContext>(0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::BDT_AND() {
  return getToken(temporalSVAParser::BDT_AND, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::LPAREN() {
  return getToken(temporalSVAParser::LPAREN, 0);
}

std::vector<temporalSVAParser::TformulaContext *> temporalSVAParser::TformulaContext::tformula() {
  return getRuleContexts<temporalSVAParser::TformulaContext>();
}

temporalSVAParser::TformulaContext* temporalSVAParser::TformulaContext::tformula(size_t i) {
  return getRuleContext<temporalSVAParser::TformulaContext>(i);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::RPAREN() {
  return getToken(temporalSVAParser::RPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::NOT() {
  return getToken(temporalSVAParser::NOT, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::NEXT() {
  return getToken(temporalSVAParser::NEXT, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::LCPAREN() {
  return getToken(temporalSVAParser::LCPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::NUMERIC() {
  return getToken(temporalSVAParser::NUMERIC, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::RCPAREN() {
  return getToken(temporalSVAParser::RCPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::LGPAREN() {
  return getToken(temporalSVAParser::LGPAREN, 0);
}

temporalSVAParser::SereContext* temporalSVAParser::TformulaContext::sere() {
  return getRuleContext<temporalSVAParser::SereContext>(0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::RGPAREN() {
  return getToken(temporalSVAParser::RGPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::AND() {
  return getToken(temporalSVAParser::AND, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::OR() {
  return getToken(temporalSVAParser::OR, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::XOR() {
  return getToken(temporalSVAParser::XOR, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::UNTIL() {
  return getToken(temporalSVAParser::UNTIL, 0);
}

tree::TerminalNode* temporalSVAParser::TformulaContext::RELEASE() {
  return getToken(temporalSVAParser::RELEASE, 0);
}


size_t temporalSVAParser::TformulaContext::getRuleIndex() const {
  return temporalSVAParser::RuleTformula;
}

void temporalSVAParser::TformulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTformula(this);
}

void temporalSVAParser::TformulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTformula(this);
}


temporalSVAParser::TformulaContext* temporalSVAParser::tformula() {
   return tformula(0);
}

temporalSVAParser::TformulaContext* temporalSVAParser::tformula(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  temporalSVAParser::TformulaContext *_localctx = _tracker.createInstance<TformulaContext>(_ctx, parentState);
  temporalSVAParser::TformulaContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, temporalSVAParser::RuleTformula, precedence);

    

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
    setState(227);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(207);
      boolean(0);
      break;
    }

    case 2: {
      setState(208);
      placeholder();
      break;
    }

    case 3: {
      setState(209);
      match(temporalSVAParser::BDT_AND);
      break;
    }

    case 4: {
      setState(210);
      match(temporalSVAParser::LPAREN);
      setState(211);
      tformula(0);
      setState(212);
      match(temporalSVAParser::RPAREN);
      break;
    }

    case 5: {
      setState(214);
      match(temporalSVAParser::NOT);
      setState(215);
      tformula(9);
      break;
    }

    case 6: {
      setState(216);
      match(temporalSVAParser::NEXT);
      setState(217);
      match(temporalSVAParser::LCPAREN);
      setState(218);
      match(temporalSVAParser::NUMERIC);
      setState(219);
      match(temporalSVAParser::RCPAREN);
      setState(220);
      tformula(3);
      break;
    }

    case 7: {
      setState(221);
      match(temporalSVAParser::NEXT);
      setState(222);
      tformula(2);
      break;
    }

    case 8: {
      setState(223);
      match(temporalSVAParser::LGPAREN);
      setState(224);
      sere(0);
      setState(225);
      match(temporalSVAParser::RGPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(246);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(244);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(229);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(230);
          match(temporalSVAParser::AND);
          setState(231);
          tformula(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(232);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(233);
          match(temporalSVAParser::OR);
          setState(234);
          tformula(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(235);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(236);
          match(temporalSVAParser::XOR);
          setState(237);
          tformula(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(238);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(239);
          match(temporalSVAParser::UNTIL);
          setState(240);
          tformula(6);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<TformulaContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTformula);
          setState(241);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(242);
          match(temporalSVAParser::RELEASE);
          setState(243);
          tformula(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(248);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PlaceholderContext ------------------------------------------------------------------

temporalSVAParser::PlaceholderContext::PlaceholderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::PlaceholderContext::NUMERIC() {
  return getToken(temporalSVAParser::NUMERIC, 0);
}


size_t temporalSVAParser::PlaceholderContext::getRuleIndex() const {
  return temporalSVAParser::RulePlaceholder;
}

void temporalSVAParser::PlaceholderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlaceholder(this);
}

void temporalSVAParser::PlaceholderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlaceholder(this);
}

temporalSVAParser::PlaceholderContext* temporalSVAParser::placeholder() {
  PlaceholderContext *_localctx = _tracker.createInstance<PlaceholderContext>(_ctx, getState());
  enterRule(_localctx, 8, temporalSVAParser::RulePlaceholder);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(249);
    match(temporalSVAParser::T__0);
    setState(250);
    match(temporalSVAParser::NUMERIC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bdt_nextContext ------------------------------------------------------------------

temporalSVAParser::Bdt_nextContext::Bdt_nextContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::Bdt_nextContext::NUMERIC() {
  return getToken(temporalSVAParser::NUMERIC, 0);
}

tree::TerminalNode* temporalSVAParser::Bdt_nextContext::DOTS() {
  return getToken(temporalSVAParser::DOTS, 0);
}


size_t temporalSVAParser::Bdt_nextContext::getRuleIndex() const {
  return temporalSVAParser::RuleBdt_next;
}

void temporalSVAParser::Bdt_nextContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBdt_next(this);
}

void temporalSVAParser::Bdt_nextContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBdt_next(this);
}

temporalSVAParser::Bdt_nextContext* temporalSVAParser::bdt_next() {
  Bdt_nextContext *_localctx = _tracker.createInstance<Bdt_nextContext>(_ctx, getState());
  enterRule(_localctx, 10, temporalSVAParser::RuleBdt_next);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
    match(temporalSVAParser::T__1);
    setState(253);
    match(temporalSVAParser::NUMERIC);
    setState(254);
    match(temporalSVAParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bdt_next_andContext ------------------------------------------------------------------

temporalSVAParser::Bdt_next_andContext::Bdt_next_andContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::Bdt_next_andContext::NUMERIC() {
  return getToken(temporalSVAParser::NUMERIC, 0);
}

tree::TerminalNode* temporalSVAParser::Bdt_next_andContext::BAND() {
  return getToken(temporalSVAParser::BAND, 0);
}

tree::TerminalNode* temporalSVAParser::Bdt_next_andContext::DOTS() {
  return getToken(temporalSVAParser::DOTS, 0);
}


size_t temporalSVAParser::Bdt_next_andContext::getRuleIndex() const {
  return temporalSVAParser::RuleBdt_next_and;
}

void temporalSVAParser::Bdt_next_andContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBdt_next_and(this);
}

void temporalSVAParser::Bdt_next_andContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBdt_next_and(this);
}

temporalSVAParser::Bdt_next_andContext* temporalSVAParser::bdt_next_and() {
  Bdt_next_andContext *_localctx = _tracker.createInstance<Bdt_next_andContext>(_ctx, getState());
  enterRule(_localctx, 12, temporalSVAParser::RuleBdt_next_and);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(256);
    match(temporalSVAParser::T__2);
    setState(257);
    match(temporalSVAParser::NUMERIC);
    setState(258);
    match(temporalSVAParser::BAND);
    setState(259);
    match(temporalSVAParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bdt_NCRepsContext ------------------------------------------------------------------

temporalSVAParser::Bdt_NCRepsContext::Bdt_NCRepsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::Bdt_NCRepsContext::NUMERIC() {
  return getToken(temporalSVAParser::NUMERIC, 0);
}

tree::TerminalNode* temporalSVAParser::Bdt_NCRepsContext::RCPAREN() {
  return getToken(temporalSVAParser::RCPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::Bdt_NCRepsContext::SEP() {
  return getToken(temporalSVAParser::SEP, 0);
}

tree::TerminalNode* temporalSVAParser::Bdt_NCRepsContext::DOTS() {
  return getToken(temporalSVAParser::DOTS, 0);
}


size_t temporalSVAParser::Bdt_NCRepsContext::getRuleIndex() const {
  return temporalSVAParser::RuleBdt_NCReps;
}

void temporalSVAParser::Bdt_NCRepsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBdt_NCReps(this);
}

void temporalSVAParser::Bdt_NCRepsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBdt_NCReps(this);
}

temporalSVAParser::Bdt_NCRepsContext* temporalSVAParser::bdt_NCReps() {
  Bdt_NCRepsContext *_localctx = _tracker.createInstance<Bdt_NCRepsContext>(_ctx, getState());
  enterRule(_localctx, 14, temporalSVAParser::RuleBdt_NCReps);

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
    match(temporalSVAParser::T__3);
    setState(262);
    match(temporalSVAParser::NUMERIC);
    setState(263);
    match(temporalSVAParser::RCPAREN);
    setState(264);
    match(temporalSVAParser::SEP);
    setState(265);
    match(temporalSVAParser::DOTS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

temporalSVAParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::BooleanContext::NOT() {
  return getToken(temporalSVAParser::NOT, 0);
}

std::vector<temporalSVAParser::BooleanContext *> temporalSVAParser::BooleanContext::boolean() {
  return getRuleContexts<temporalSVAParser::BooleanContext>();
}

temporalSVAParser::BooleanContext* temporalSVAParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<temporalSVAParser::BooleanContext>(i);
}

std::vector<temporalSVAParser::LogicContext *> temporalSVAParser::BooleanContext::logic() {
  return getRuleContexts<temporalSVAParser::LogicContext>();
}

temporalSVAParser::LogicContext* temporalSVAParser::BooleanContext::logic(size_t i) {
  return getRuleContext<temporalSVAParser::LogicContext>(i);
}

temporalSVAParser::RelopContext* temporalSVAParser::BooleanContext::relop() {
  return getRuleContext<temporalSVAParser::RelopContext>(0);
}

std::vector<temporalSVAParser::NumericContext *> temporalSVAParser::BooleanContext::numeric() {
  return getRuleContexts<temporalSVAParser::NumericContext>();
}

temporalSVAParser::NumericContext* temporalSVAParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<temporalSVAParser::NumericContext>(i);
}

tree::TerminalNode* temporalSVAParser::BooleanContext::EQ() {
  return getToken(temporalSVAParser::EQ, 0);
}

tree::TerminalNode* temporalSVAParser::BooleanContext::NEQ() {
  return getToken(temporalSVAParser::NEQ, 0);
}

temporalSVAParser::BooleanAtomContext* temporalSVAParser::BooleanContext::booleanAtom() {
  return getRuleContext<temporalSVAParser::BooleanAtomContext>(0);
}

tree::TerminalNode* temporalSVAParser::BooleanContext::LPAREN() {
  return getToken(temporalSVAParser::LPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::BooleanContext::RPAREN() {
  return getToken(temporalSVAParser::RPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::BooleanContext::AND() {
  return getToken(temporalSVAParser::AND, 0);
}

tree::TerminalNode* temporalSVAParser::BooleanContext::OR() {
  return getToken(temporalSVAParser::OR, 0);
}


size_t temporalSVAParser::BooleanContext::getRuleIndex() const {
  return temporalSVAParser::RuleBoolean;
}

void temporalSVAParser::BooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolean(this);
}

void temporalSVAParser::BooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolean(this);
}


temporalSVAParser::BooleanContext* temporalSVAParser::boolean() {
   return boolean(0);
}

temporalSVAParser::BooleanContext* temporalSVAParser::boolean(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  temporalSVAParser::BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, parentState);
  temporalSVAParser::BooleanContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, temporalSVAParser::RuleBoolean, precedence);

    

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
    setState(301);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      setState(268);
      match(temporalSVAParser::NOT);
      setState(269);
      boolean(15);
      break;
    }

    case 2: {
      setState(270);
      logic(0);
      setState(271);
      relop();
      setState(272);
      logic(0);
      break;
    }

    case 3: {
      setState(274);
      numeric(0);
      setState(275);
      relop();
      setState(276);
      numeric(0);
      break;
    }

    case 4: {
      setState(278);
      logic(0);
      setState(279);
      match(temporalSVAParser::EQ);
      setState(280);
      logic(0);
      break;
    }

    case 5: {
      setState(282);
      numeric(0);
      setState(283);
      match(temporalSVAParser::EQ);
      setState(284);
      numeric(0);
      break;
    }

    case 6: {
      setState(286);
      logic(0);
      setState(287);
      match(temporalSVAParser::NEQ);
      setState(288);
      logic(0);
      break;
    }

    case 7: {
      setState(290);
      numeric(0);
      setState(291);
      match(temporalSVAParser::NEQ);
      setState(292);
      numeric(0);
      break;
    }

    case 8: {
      setState(294);
      booleanAtom();
      break;
    }

    case 9: {
      setState(295);
      logic(0);
      break;
    }

    case 10: {
      setState(296);
      numeric(0);
      break;
    }

    case 11: {
      setState(297);
      match(temporalSVAParser::LPAREN);
      setState(298);
      boolean(0);
      setState(299);
      match(temporalSVAParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(317);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(315);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(303);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(304);
          match(temporalSVAParser::EQ);
          setState(305);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(306);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(307);
          match(temporalSVAParser::NEQ);
          setState(308);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(309);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(310);
          dynamic_cast<BooleanContext *>(_localctx)->booleanop = match(temporalSVAParser::AND);
          setState(311);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(312);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(313);
          dynamic_cast<BooleanContext *>(_localctx)->booleanop = match(temporalSVAParser::OR);
          setState(314);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(319);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
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

temporalSVAParser::BooleanAtomContext::BooleanAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalSVAParser::BooleanConstantContext* temporalSVAParser::BooleanAtomContext::booleanConstant() {
  return getRuleContext<temporalSVAParser::BooleanConstantContext>(0);
}

temporalSVAParser::BooleanVariableContext* temporalSVAParser::BooleanAtomContext::booleanVariable() {
  return getRuleContext<temporalSVAParser::BooleanVariableContext>(0);
}


size_t temporalSVAParser::BooleanAtomContext::getRuleIndex() const {
  return temporalSVAParser::RuleBooleanAtom;
}

void temporalSVAParser::BooleanAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanAtom(this);
}

void temporalSVAParser::BooleanAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanAtom(this);
}

temporalSVAParser::BooleanAtomContext* temporalSVAParser::booleanAtom() {
  BooleanAtomContext *_localctx = _tracker.createInstance<BooleanAtomContext>(_ctx, getState());
  enterRule(_localctx, 18, temporalSVAParser::RuleBooleanAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(322);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalSVAParser::BOOLEAN: {
        enterOuterAlt(_localctx, 1);
        setState(320);
        booleanConstant();
        break;
      }

      case temporalSVAParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(321);
        booleanVariable();
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

//----------------- BooleanConstantContext ------------------------------------------------------------------

temporalSVAParser::BooleanConstantContext::BooleanConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::BooleanConstantContext::BOOLEAN() {
  return getToken(temporalSVAParser::BOOLEAN, 0);
}


size_t temporalSVAParser::BooleanConstantContext::getRuleIndex() const {
  return temporalSVAParser::RuleBooleanConstant;
}

void temporalSVAParser::BooleanConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanConstant(this);
}

void temporalSVAParser::BooleanConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanConstant(this);
}

temporalSVAParser::BooleanConstantContext* temporalSVAParser::booleanConstant() {
  BooleanConstantContext *_localctx = _tracker.createInstance<BooleanConstantContext>(_ctx, getState());
  enterRule(_localctx, 20, temporalSVAParser::RuleBooleanConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(324);
    match(temporalSVAParser::BOOLEAN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanVariableContext ------------------------------------------------------------------

temporalSVAParser::BooleanVariableContext::BooleanVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::BooleanVariableContext::LT() {
  return getToken(temporalSVAParser::LT, 0);
}

temporalSVAParser::VariableContext* temporalSVAParser::BooleanVariableContext::variable() {
  return getRuleContext<temporalSVAParser::VariableContext>(0);
}


size_t temporalSVAParser::BooleanVariableContext::getRuleIndex() const {
  return temporalSVAParser::RuleBooleanVariable;
}

void temporalSVAParser::BooleanVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanVariable(this);
}

void temporalSVAParser::BooleanVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanVariable(this);
}

temporalSVAParser::BooleanVariableContext* temporalSVAParser::booleanVariable() {
  BooleanVariableContext *_localctx = _tracker.createInstance<BooleanVariableContext>(_ctx, getState());
  enterRule(_localctx, 22, temporalSVAParser::RuleBooleanVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(326);
    match(temporalSVAParser::LT);
    setState(327);
    variable();
    setState(328);
    match(temporalSVAParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicContext ------------------------------------------------------------------

temporalSVAParser::LogicContext::LogicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::LogicContext::NEG() {
  return getToken(temporalSVAParser::NEG, 0);
}

std::vector<temporalSVAParser::LogicContext *> temporalSVAParser::LogicContext::logic() {
  return getRuleContexts<temporalSVAParser::LogicContext>();
}

temporalSVAParser::LogicContext* temporalSVAParser::LogicContext::logic(size_t i) {
  return getRuleContext<temporalSVAParser::LogicContext>(i);
}

temporalSVAParser::LogicAtomContext* temporalSVAParser::LogicContext::logicAtom() {
  return getRuleContext<temporalSVAParser::LogicAtomContext>(0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::LPAREN() {
  return getToken(temporalSVAParser::LPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::RPAREN() {
  return getToken(temporalSVAParser::RPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::TIMES() {
  return getToken(temporalSVAParser::TIMES, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::DIV() {
  return getToken(temporalSVAParser::DIV, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::PLUS() {
  return getToken(temporalSVAParser::PLUS, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::MINUS() {
  return getToken(temporalSVAParser::MINUS, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::LSHIFT() {
  return getToken(temporalSVAParser::LSHIFT, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::RSHIFT() {
  return getToken(temporalSVAParser::RSHIFT, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::BAND() {
  return getToken(temporalSVAParser::BAND, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::BXOR() {
  return getToken(temporalSVAParser::BXOR, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::BOR() {
  return getToken(temporalSVAParser::BOR, 0);
}

tree::TerminalNode* temporalSVAParser::LogicContext::INDEX() {
  return getToken(temporalSVAParser::INDEX, 0);
}


size_t temporalSVAParser::LogicContext::getRuleIndex() const {
  return temporalSVAParser::RuleLogic;
}

void temporalSVAParser::LogicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic(this);
}

void temporalSVAParser::LogicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic(this);
}


temporalSVAParser::LogicContext* temporalSVAParser::logic() {
   return logic(0);
}

temporalSVAParser::LogicContext* temporalSVAParser::logic(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  temporalSVAParser::LogicContext *_localctx = _tracker.createInstance<LogicContext>(_ctx, parentState);
  temporalSVAParser::LogicContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, temporalSVAParser::RuleLogic, precedence);

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
    setState(338);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalSVAParser::NEG: {
        setState(331);
        match(temporalSVAParser::NEG);
        setState(332);
        logic(11);
        break;
      }

      case temporalSVAParser::NUMERIC:
      case temporalSVAParser::VERILOG_BINARY:
      case temporalSVAParser::GCC_BINARY:
      case temporalSVAParser::HEX:
      case temporalSVAParser::LT: {
        setState(333);
        logicAtom();
        break;
      }

      case temporalSVAParser::LPAREN: {
        setState(334);
        match(temporalSVAParser::LPAREN);
        setState(335);
        logic(0);
        setState(336);
        match(temporalSVAParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(365);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(363);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(340);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(341);
          dynamic_cast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == temporalSVAParser::TIMES

          || _la == temporalSVAParser::DIV)) {
            dynamic_cast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(342);
          logic(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(343);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(344);
          dynamic_cast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == temporalSVAParser::PLUS

          || _la == temporalSVAParser::MINUS)) {
            dynamic_cast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(345);
          logic(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(346);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(347);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(temporalSVAParser::LSHIFT);
          setState(348);
          logic(8);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(349);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(350);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(temporalSVAParser::RSHIFT);
          setState(351);
          logic(7);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(352);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(353);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(temporalSVAParser::BAND);
          setState(354);
          logic(6);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(355);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(356);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(temporalSVAParser::BXOR);
          setState(357);
          logic(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(358);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(359);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(temporalSVAParser::BOR);
          setState(360);
          logic(4);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(361);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(362);
          match(temporalSVAParser::INDEX);
          break;
        }

        default:
          break;
        } 
      }
      setState(367);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
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

temporalSVAParser::LogicAtomContext::LogicAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalSVAParser::LogicConstantContext* temporalSVAParser::LogicAtomContext::logicConstant() {
  return getRuleContext<temporalSVAParser::LogicConstantContext>(0);
}

temporalSVAParser::LogicVariableContext* temporalSVAParser::LogicAtomContext::logicVariable() {
  return getRuleContext<temporalSVAParser::LogicVariableContext>(0);
}


size_t temporalSVAParser::LogicAtomContext::getRuleIndex() const {
  return temporalSVAParser::RuleLogicAtom;
}

void temporalSVAParser::LogicAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicAtom(this);
}

void temporalSVAParser::LogicAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicAtom(this);
}

temporalSVAParser::LogicAtomContext* temporalSVAParser::logicAtom() {
  LogicAtomContext *_localctx = _tracker.createInstance<LogicAtomContext>(_ctx, getState());
  enterRule(_localctx, 26, temporalSVAParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(370);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalSVAParser::NUMERIC:
      case temporalSVAParser::VERILOG_BINARY:
      case temporalSVAParser::GCC_BINARY:
      case temporalSVAParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(368);
        logicConstant();
        break;
      }

      case temporalSVAParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(369);
        logicVariable();
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

//----------------- LogicConstantContext ------------------------------------------------------------------

temporalSVAParser::LogicConstantContext::LogicConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::LogicConstantContext::VERILOG_BINARY() {
  return getToken(temporalSVAParser::VERILOG_BINARY, 0);
}

tree::TerminalNode* temporalSVAParser::LogicConstantContext::GCC_BINARY() {
  return getToken(temporalSVAParser::GCC_BINARY, 0);
}

tree::TerminalNode* temporalSVAParser::LogicConstantContext::NUMERIC() {
  return getToken(temporalSVAParser::NUMERIC, 0);
}

tree::TerminalNode* temporalSVAParser::LogicConstantContext::HEX() {
  return getToken(temporalSVAParser::HEX, 0);
}


size_t temporalSVAParser::LogicConstantContext::getRuleIndex() const {
  return temporalSVAParser::RuleLogicConstant;
}

void temporalSVAParser::LogicConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicConstant(this);
}

void temporalSVAParser::LogicConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicConstant(this);
}

temporalSVAParser::LogicConstantContext* temporalSVAParser::logicConstant() {
  LogicConstantContext *_localctx = _tracker.createInstance<LogicConstantContext>(_ctx, getState());
  enterRule(_localctx, 28, temporalSVAParser::RuleLogicConstant);
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
    setState(372);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << temporalSVAParser::NUMERIC)
      | (1ULL << temporalSVAParser::VERILOG_BINARY)
      | (1ULL << temporalSVAParser::GCC_BINARY)
      | (1ULL << temporalSVAParser::HEX))) != 0))) {
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

//----------------- LogicVariableContext ------------------------------------------------------------------

temporalSVAParser::LogicVariableContext::LogicVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::LogicVariableContext::LT() {
  return getToken(temporalSVAParser::LT, 0);
}

temporalSVAParser::VariableContext* temporalSVAParser::LogicVariableContext::variable() {
  return getRuleContext<temporalSVAParser::VariableContext>(0);
}

tree::TerminalNode* temporalSVAParser::LogicVariableContext::SIGN() {
  return getToken(temporalSVAParser::SIGN, 0);
}

tree::TerminalNode* temporalSVAParser::LogicVariableContext::NUMERIC() {
  return getToken(temporalSVAParser::NUMERIC, 0);
}


size_t temporalSVAParser::LogicVariableContext::getRuleIndex() const {
  return temporalSVAParser::RuleLogicVariable;
}

void temporalSVAParser::LogicVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicVariable(this);
}

void temporalSVAParser::LogicVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicVariable(this);
}

temporalSVAParser::LogicVariableContext* temporalSVAParser::logicVariable() {
  LogicVariableContext *_localctx = _tracker.createInstance<LogicVariableContext>(_ctx, getState());
  enterRule(_localctx, 30, temporalSVAParser::RuleLogicVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(374);
    match(temporalSVAParser::LT);
    setState(375);
    variable();
    setState(376);
    match(temporalSVAParser::T__5);
    setState(377);
    match(temporalSVAParser::SIGN);
    setState(378);
    match(temporalSVAParser::T__6);
    setState(379);
    match(temporalSVAParser::NUMERIC);
    setState(380);
    match(temporalSVAParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericContext ------------------------------------------------------------------

temporalSVAParser::NumericContext::NumericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalSVAParser::NumericAtomContext* temporalSVAParser::NumericContext::numericAtom() {
  return getRuleContext<temporalSVAParser::NumericAtomContext>(0);
}

temporalSVAParser::LogicContext* temporalSVAParser::NumericContext::logic() {
  return getRuleContext<temporalSVAParser::LogicContext>(0);
}

tree::TerminalNode* temporalSVAParser::NumericContext::LPAREN() {
  return getToken(temporalSVAParser::LPAREN, 0);
}

std::vector<temporalSVAParser::NumericContext *> temporalSVAParser::NumericContext::numeric() {
  return getRuleContexts<temporalSVAParser::NumericContext>();
}

temporalSVAParser::NumericContext* temporalSVAParser::NumericContext::numeric(size_t i) {
  return getRuleContext<temporalSVAParser::NumericContext>(i);
}

tree::TerminalNode* temporalSVAParser::NumericContext::RPAREN() {
  return getToken(temporalSVAParser::RPAREN, 0);
}

tree::TerminalNode* temporalSVAParser::NumericContext::TIMES() {
  return getToken(temporalSVAParser::TIMES, 0);
}

tree::TerminalNode* temporalSVAParser::NumericContext::DIV() {
  return getToken(temporalSVAParser::DIV, 0);
}

tree::TerminalNode* temporalSVAParser::NumericContext::PLUS() {
  return getToken(temporalSVAParser::PLUS, 0);
}

tree::TerminalNode* temporalSVAParser::NumericContext::MINUS() {
  return getToken(temporalSVAParser::MINUS, 0);
}


size_t temporalSVAParser::NumericContext::getRuleIndex() const {
  return temporalSVAParser::RuleNumeric;
}

void temporalSVAParser::NumericContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void temporalSVAParser::NumericContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}


temporalSVAParser::NumericContext* temporalSVAParser::numeric() {
   return numeric(0);
}

temporalSVAParser::NumericContext* temporalSVAParser::numeric(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  temporalSVAParser::NumericContext *_localctx = _tracker.createInstance<NumericContext>(_ctx, parentState);
  temporalSVAParser::NumericContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 32;
  enterRecursionRule(_localctx, 32, temporalSVAParser::RuleNumeric, precedence);

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
    setState(389);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      setState(383);
      numericAtom();
      break;
    }

    case 2: {
      setState(384);
      logic(0);
      break;
    }

    case 3: {
      setState(385);
      match(temporalSVAParser::LPAREN);
      setState(386);
      numeric(0);
      setState(387);
      match(temporalSVAParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(399);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(397);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(391);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(392);
          dynamic_cast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == temporalSVAParser::TIMES

          || _la == temporalSVAParser::DIV)) {
            dynamic_cast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(393);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(394);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(395);
          dynamic_cast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == temporalSVAParser::PLUS

          || _la == temporalSVAParser::MINUS)) {
            dynamic_cast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(396);
          numeric(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(401);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
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

temporalSVAParser::NumericAtomContext::NumericAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

temporalSVAParser::NumericConstantContext* temporalSVAParser::NumericAtomContext::numericConstant() {
  return getRuleContext<temporalSVAParser::NumericConstantContext>(0);
}

temporalSVAParser::NumericVariableContext* temporalSVAParser::NumericAtomContext::numericVariable() {
  return getRuleContext<temporalSVAParser::NumericVariableContext>(0);
}


size_t temporalSVAParser::NumericAtomContext::getRuleIndex() const {
  return temporalSVAParser::RuleNumericAtom;
}

void temporalSVAParser::NumericAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericAtom(this);
}

void temporalSVAParser::NumericAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericAtom(this);
}

temporalSVAParser::NumericAtomContext* temporalSVAParser::numericAtom() {
  NumericAtomContext *_localctx = _tracker.createInstance<NumericAtomContext>(_ctx, getState());
  enterRule(_localctx, 34, temporalSVAParser::RuleNumericAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(404);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case temporalSVAParser::NUMERIC: {
        enterOuterAlt(_localctx, 1);
        setState(402);
        numericConstant();
        break;
      }

      case temporalSVAParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(403);
        numericVariable();
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

//----------------- NumericConstantContext ------------------------------------------------------------------

temporalSVAParser::NumericConstantContext::NumericConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::NumericConstantContext::NUMERIC() {
  return getToken(temporalSVAParser::NUMERIC, 0);
}


size_t temporalSVAParser::NumericConstantContext::getRuleIndex() const {
  return temporalSVAParser::RuleNumericConstant;
}

void temporalSVAParser::NumericConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericConstant(this);
}

void temporalSVAParser::NumericConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericConstant(this);
}

temporalSVAParser::NumericConstantContext* temporalSVAParser::numericConstant() {
  NumericConstantContext *_localctx = _tracker.createInstance<NumericConstantContext>(_ctx, getState());
  enterRule(_localctx, 36, temporalSVAParser::RuleNumericConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(406);
    match(temporalSVAParser::NUMERIC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericVariableContext ------------------------------------------------------------------

temporalSVAParser::NumericVariableContext::NumericVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::NumericVariableContext::LT() {
  return getToken(temporalSVAParser::LT, 0);
}

temporalSVAParser::VariableContext* temporalSVAParser::NumericVariableContext::variable() {
  return getRuleContext<temporalSVAParser::VariableContext>(0);
}

tree::TerminalNode* temporalSVAParser::NumericVariableContext::NUMERIC() {
  return getToken(temporalSVAParser::NUMERIC, 0);
}


size_t temporalSVAParser::NumericVariableContext::getRuleIndex() const {
  return temporalSVAParser::RuleNumericVariable;
}

void temporalSVAParser::NumericVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericVariable(this);
}

void temporalSVAParser::NumericVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericVariable(this);
}

temporalSVAParser::NumericVariableContext* temporalSVAParser::numericVariable() {
  NumericVariableContext *_localctx = _tracker.createInstance<NumericVariableContext>(_ctx, getState());
  enterRule(_localctx, 38, temporalSVAParser::RuleNumericVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(408);
    match(temporalSVAParser::LT);
    setState(409);
    variable();
    setState(410);
    match(temporalSVAParser::T__8);
    setState(411);
    match(temporalSVAParser::NUMERIC);
    setState(412);
    match(temporalSVAParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

temporalSVAParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::VariableContext::VARIABLE() {
  return getToken(temporalSVAParser::VARIABLE, 0);
}


size_t temporalSVAParser::VariableContext::getRuleIndex() const {
  return temporalSVAParser::RuleVariable;
}

void temporalSVAParser::VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void temporalSVAParser::VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

temporalSVAParser::VariableContext* temporalSVAParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 40, temporalSVAParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(414);
    match(temporalSVAParser::VARIABLE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelopContext ------------------------------------------------------------------

temporalSVAParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* temporalSVAParser::RelopContext::GT() {
  return getToken(temporalSVAParser::GT, 0);
}

tree::TerminalNode* temporalSVAParser::RelopContext::GE() {
  return getToken(temporalSVAParser::GE, 0);
}

tree::TerminalNode* temporalSVAParser::RelopContext::LT() {
  return getToken(temporalSVAParser::LT, 0);
}

tree::TerminalNode* temporalSVAParser::RelopContext::LE() {
  return getToken(temporalSVAParser::LE, 0);
}


size_t temporalSVAParser::RelopContext::getRuleIndex() const {
  return temporalSVAParser::RuleRelop;
}

void temporalSVAParser::RelopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void temporalSVAParser::RelopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<temporalSVAListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}

temporalSVAParser::RelopContext* temporalSVAParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 42, temporalSVAParser::RuleRelop);
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
    setState(416);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << temporalSVAParser::GT)
      | (1ULL << temporalSVAParser::GE)
      | (1ULL << temporalSVAParser::LT)
      | (1ULL << temporalSVAParser::LE))) != 0))) {
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

bool temporalSVAParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return sereSempred(dynamic_cast<SereContext *>(context), predicateIndex);
    case 3: return tformulaSempred(dynamic_cast<TformulaContext *>(context), predicateIndex);
    case 8: return booleanSempred(dynamic_cast<BooleanContext *>(context), predicateIndex);
    case 12: return logicSempred(dynamic_cast<LogicContext *>(context), predicateIndex);
    case 16: return numericSempred(dynamic_cast<NumericContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool temporalSVAParser::sereSempred(SereContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 14);
    case 1: return precpred(_ctx, 13);
    case 2: return precpred(_ctx, 12);
    case 3: return precpred(_ctx, 11);
    case 4: return precpred(_ctx, 10);
    case 5: return precpred(_ctx, 4);
    case 6: return precpred(_ctx, 9);
    case 7: return precpred(_ctx, 8);
    case 8: return precpred(_ctx, 7);
    case 9: return precpred(_ctx, 6);

  default:
    break;
  }
  return true;
}

bool temporalSVAParser::tformulaSempred(TformulaContext *_localctx, size_t predicateIndex) {
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

bool temporalSVAParser::booleanSempred(BooleanContext *_localctx, size_t predicateIndex) {
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

bool temporalSVAParser::logicSempred(LogicContext *_localctx, size_t predicateIndex) {
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

bool temporalSVAParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 27: return precpred(_ctx, 5);
    case 28: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> temporalSVAParser::_decisionToDFA;
atn::PredictionContextCache temporalSVAParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN temporalSVAParser::_atn;
std::vector<uint16_t> temporalSVAParser::_serializedATN;

std::vector<std::string> temporalSVAParser::_ruleNames = {
  "file", "formula", "sere", "tformula", "placeholder", "bdt_next", "bdt_next_and", 
  "bdt_NCReps", "boolean", "booleanAtom", "booleanConstant", "booleanVariable", 
  "logic", "logicAtom", "logicConstant", "logicVariable", "numeric", "numericAtom", 
  "numericConstant", "numericVariable", "variable", "relop"
};

std::vector<std::string> temporalSVAParser::_literalNames = {
  "", "'P'", "'..##'", "'..#'", "'..[->'", "',bool>'", "',logic('", "','", 
  "')>'", "',numeric('", "'..&&..'", "", "'eventually'", "'always'", "'nexttime'", 
  "'until'", "'release'", "'..'", "'|->'", "'|=>'", "'iff'", "'xor'", "'[]->'", 
  "'[]=>'", "'='", "'##'", "';'", "':'", "'first_match'", "", "'{'", "'}'", 
  "'['", "']'", "'('", "')'", "", "", "", "", "", "", "", "'+'", "'-'", 
  "'*'", "'/'", "'>'", "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", "'|'", 
  "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'"
};

std::vector<std::string> temporalSVAParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "BDT_AND", "SEP", "EVENTUALLY", 
  "ALWAYS", "NEXT", "UNTIL", "RELEASE", "DOTS", "IMPL", "IMPL2", "IFF", 
  "XOR", "BIND1", "BIND2", "ASS", "DELAY", "SCOL", "COL", "FIRST_MATCH", 
  "SIGN", "LGPAREN", "RGPAREN", "LCPAREN", "RCPAREN", "LPAREN", "RPAREN", 
  "VARIABLE", "INDEX", "NUMERIC", "VERILOG_BINARY", "GCC_BINARY", "HEX", 
  "BOOLEAN", "PLUS", "MINUS", "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", 
  "NEQ", "BAND", "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", "OR", 
  "NOT", "WS"
};

dfa::Vocabulary temporalSVAParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> temporalSVAParser::_tokenNames;

temporalSVAParser::Initializer::Initializer() {
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
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x40, 0x1a5, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x4, 0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 
       0x9, 0x14, 0x4, 0x15, 0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 
       0x9, 0x17, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
       0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x39, 0xa, 
       0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x5f, 0xa, 0x3, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x64, 0xa, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x72, 0xa, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x76, 0xa, 0x4, 0x3, 0x4, 0x5, 
       0x4, 0x79, 0xa, 0x4, 0x3, 0x4, 0x5, 0x4, 0x7c, 0xa, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x82, 0xa, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x96, 0xa, 0x4, 
       0x3, 0x4, 0x5, 0x4, 0x99, 0xa, 0x4, 0x3, 0x4, 0x5, 0x4, 0x9c, 0xa, 
       0x4, 0x3, 0x4, 0x5, 0x4, 0x9f, 0xa, 0x4, 0x3, 0x4, 0x5, 0x4, 0xa2, 
       0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 
       0x4, 0xa9, 0xa, 0x4, 0x3, 0x4, 0x5, 0x4, 0xac, 0xa, 0x4, 0x3, 0x4, 
       0x5, 0x4, 0xaf, 0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 
       0x4, 0xbb, 0xa, 0x4, 0x3, 0x4, 0x5, 0x4, 0xbe, 0xa, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0xc6, 
       0xa, 0x4, 0x3, 0x4, 0x5, 0x4, 0xc9, 0xa, 0x4, 0x3, 0x4, 0x7, 0x4, 
       0xcc, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0xcf, 0xb, 0x4, 0x3, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x5, 0x5, 0xe6, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0xf7, 0xa, 
       0x5, 0xc, 0x5, 0xe, 0x5, 0xfa, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
       0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 
       0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
       0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
       0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
       0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
       0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
       0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
       0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x130, 0xa, 0xa, 
       0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
       0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 
       0x13e, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x141, 0xb, 0xa, 0x3, 0xb, 0x3, 
       0xb, 0x5, 0xb, 0x145, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 
       0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
       0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x155, 0xa, 0xe, 
       0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
       0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
       0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
       0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0x16e, 0xa, 0xe, 0xc, 
       0xe, 0xe, 0xe, 0x171, 0xb, 0xe, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x175, 
       0xa, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
       0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 
       0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
       0x5, 0x12, 0x188, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
       0x12, 0x3, 0x12, 0x3, 0x12, 0x7, 0x12, 0x190, 0xa, 0x12, 0xc, 0x12, 
       0xe, 0x12, 0x193, 0xb, 0x12, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x197, 
       0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
       0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 
       0x3, 0x17, 0x3, 0x17, 0x2, 0x7, 0x6, 0x8, 0x12, 0x1a, 0x22, 0x18, 
       0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
       0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2, 
       0x6, 0x3, 0x2, 0x2f, 0x30, 0x3, 0x2, 0x2d, 0x2e, 0x3, 0x2, 0x28, 
       0x2b, 0x3, 0x2, 0x31, 0x34, 0x2, 0x1e2, 0x2, 0x38, 0x3, 0x2, 0x2, 
       0x2, 0x4, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x6, 0x81, 0x3, 0x2, 0x2, 0x2, 
       0x8, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xa, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xc, 
       0xfe, 0x3, 0x2, 0x2, 0x2, 0xe, 0x102, 0x3, 0x2, 0x2, 0x2, 0x10, 0x107, 
       0x3, 0x2, 0x2, 0x2, 0x12, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x14, 0x144, 
       0x3, 0x2, 0x2, 0x2, 0x16, 0x146, 0x3, 0x2, 0x2, 0x2, 0x18, 0x148, 
       0x3, 0x2, 0x2, 0x2, 0x1a, 0x154, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x174, 
       0x3, 0x2, 0x2, 0x2, 0x1e, 0x176, 0x3, 0x2, 0x2, 0x2, 0x20, 0x178, 
       0x3, 0x2, 0x2, 0x2, 0x22, 0x187, 0x3, 0x2, 0x2, 0x2, 0x24, 0x196, 
       0x3, 0x2, 0x2, 0x2, 0x26, 0x198, 0x3, 0x2, 0x2, 0x2, 0x28, 0x19a, 
       0x3, 0x2, 0x2, 0x2, 0x2a, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x1a2, 
       0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x7, 0xf, 0x2, 0x2, 0x2f, 0x30, 0x5, 
       0x4, 0x3, 0x2, 0x30, 0x31, 0x7, 0x2, 0x2, 0x3, 0x31, 0x39, 0x3, 0x2, 
       0x2, 0x2, 0x32, 0x33, 0x7, 0xf, 0x2, 0x2, 0x33, 0x34, 0x7, 0x24, 
       0x2, 0x2, 0x34, 0x35, 0x5, 0x4, 0x3, 0x2, 0x35, 0x36, 0x7, 0x25, 
       0x2, 0x2, 0x36, 0x37, 0x7, 0x2, 0x2, 0x3, 0x37, 0x39, 0x3, 0x2, 0x2, 
       0x2, 0x38, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x38, 0x32, 0x3, 0x2, 0x2, 0x2, 
       0x39, 0x3, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x5, 0x8, 0x5, 0x2, 0x3b, 
       0x3c, 0x7, 0x14, 0x2, 0x2, 0x3c, 0x3d, 0x5, 0x8, 0x5, 0x2, 0x3d, 
       0x5f, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 0x5, 0x8, 0x5, 0x2, 0x3f, 0x40, 
       0x7, 0x15, 0x2, 0x2, 0x40, 0x41, 0x5, 0x8, 0x5, 0x2, 0x41, 0x5f, 
       0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x7, 0x20, 0x2, 0x2, 0x43, 0x44, 
       0x5, 0x6, 0x4, 0x2, 0x44, 0x45, 0x7, 0x21, 0x2, 0x2, 0x45, 0x46, 
       0x7, 0x22, 0x2, 0x2, 0x46, 0x47, 0x7, 0x23, 0x2, 0x2, 0x47, 0x48, 
       0x7, 0x14, 0x2, 0x2, 0x48, 0x49, 0x5, 0x8, 0x5, 0x2, 0x49, 0x5f, 
       0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0x20, 0x2, 0x2, 0x4b, 0x4c, 
       0x5, 0x6, 0x4, 0x2, 0x4c, 0x4d, 0x7, 0x21, 0x2, 0x2, 0x4d, 0x4e, 
       0x7, 0x22, 0x2, 0x2, 0x4e, 0x4f, 0x7, 0x23, 0x2, 0x2, 0x4f, 0x50, 
       0x7, 0x15, 0x2, 0x2, 0x50, 0x51, 0x5, 0x8, 0x5, 0x2, 0x51, 0x5f, 
       0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x7, 0x20, 0x2, 0x2, 0x53, 0x54, 
       0x5, 0x6, 0x4, 0x2, 0x54, 0x55, 0x7, 0x21, 0x2, 0x2, 0x55, 0x56, 
       0x7, 0x18, 0x2, 0x2, 0x56, 0x57, 0x5, 0x8, 0x5, 0x2, 0x57, 0x5f, 
       0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x7, 0x20, 0x2, 0x2, 0x59, 0x5a, 
       0x5, 0x6, 0x4, 0x2, 0x5a, 0x5b, 0x7, 0x21, 0x2, 0x2, 0x5b, 0x5c, 
       0x7, 0x19, 0x2, 0x2, 0x5c, 0x5d, 0x5, 0x8, 0x5, 0x2, 0x5d, 0x5f, 
       0x3, 0x2, 0x2, 0x2, 0x5e, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x3e, 0x3, 
       0x2, 0x2, 0x2, 0x5e, 0x42, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x4a, 0x3, 0x2, 
       0x2, 0x2, 0x5e, 0x52, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x58, 0x3, 0x2, 0x2, 
       0x2, 0x5f, 0x5, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x8, 0x4, 0x1, 0x2, 
       0x61, 0x82, 0x5, 0x12, 0xa, 0x2, 0x62, 0x64, 0x7, 0x3f, 0x2, 0x2, 
       0x63, 0x62, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 
       0x65, 0x3, 0x2, 0x2, 0x2, 0x65, 0x82, 0x5, 0xa, 0x6, 0x2, 0x66, 0x82, 
       0x7, 0xc, 0x2, 0x2, 0x67, 0x68, 0x7, 0x24, 0x2, 0x2, 0x68, 0x69, 
       0x5, 0x6, 0x4, 0x2, 0x69, 0x6a, 0x7, 0x25, 0x2, 0x2, 0x6a, 0x82, 
       0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x7, 0x20, 0x2, 0x2, 0x6c, 0x6d, 
       0x5, 0x6, 0x4, 0x2, 0x6d, 0x6e, 0x7, 0x21, 0x2, 0x2, 0x6e, 0x82, 
       0x3, 0x2, 0x2, 0x2, 0x6f, 0x71, 0x7, 0x1b, 0x2, 0x2, 0x70, 0x72, 
       0x7, 0x22, 0x2, 0x2, 0x71, 0x70, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 
       0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x3, 0x2, 0x2, 0x2, 0x73, 0x75, 0x7, 
       0x28, 0x2, 0x2, 0x74, 0x76, 0x7, 0x13, 0x2, 0x2, 0x75, 0x74, 0x3, 
       0x2, 0x2, 0x2, 0x75, 0x76, 0x3, 0x2, 0x2, 0x2, 0x76, 0x78, 0x3, 0x2, 
       0x2, 0x2, 0x77, 0x79, 0x7, 0x28, 0x2, 0x2, 0x78, 0x77, 0x3, 0x2, 
       0x2, 0x2, 0x78, 0x79, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7b, 0x3, 0x2, 0x2, 
       0x2, 0x7a, 0x7c, 0x7, 0x23, 0x2, 0x2, 0x7b, 0x7a, 0x3, 0x2, 0x2, 
       0x2, 0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x3, 0x2, 0x2, 0x2, 
       0x7d, 0x82, 0x5, 0x6, 0x4, 0x7, 0x7e, 0x82, 0x5, 0xc, 0x7, 0x2, 0x7f, 
       0x82, 0x5, 0xe, 0x8, 0x2, 0x80, 0x82, 0x5, 0x10, 0x9, 0x2, 0x81, 
       0x60, 0x3, 0x2, 0x2, 0x2, 0x81, 0x63, 0x3, 0x2, 0x2, 0x2, 0x81, 0x66, 
       0x3, 0x2, 0x2, 0x2, 0x81, 0x67, 0x3, 0x2, 0x2, 0x2, 0x81, 0x6b, 0x3, 
       0x2, 0x2, 0x2, 0x81, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x81, 0x7e, 0x3, 0x2, 
       0x2, 0x2, 0x81, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x81, 0x80, 0x3, 0x2, 0x2, 
       0x2, 0x82, 0xcd, 0x3, 0x2, 0x2, 0x2, 0x83, 0x84, 0xc, 0x10, 0x2, 
       0x2, 0x84, 0x85, 0x7, 0x38, 0x2, 0x2, 0x85, 0xcc, 0x5, 0x6, 0x4, 
       0x11, 0x86, 0x87, 0xc, 0xf, 0x2, 0x2, 0x87, 0x88, 0x7, 0x37, 0x2, 
       0x2, 0x88, 0xcc, 0x5, 0x6, 0x4, 0x10, 0x89, 0x8a, 0xc, 0xe, 0x2, 
       0x2, 0x8a, 0x8b, 0x7, 0x3d, 0x2, 0x2, 0x8b, 0xcc, 0x5, 0x6, 0x4, 
       0xf, 0x8c, 0x8d, 0xc, 0xd, 0x2, 0x2, 0x8d, 0x8e, 0x7, 0x1c, 0x2, 
       0x2, 0x8e, 0xcc, 0x5, 0x6, 0x4, 0xe, 0x8f, 0x90, 0xc, 0xc, 0x2, 0x2, 
       0x90, 0x91, 0x7, 0x1d, 0x2, 0x2, 0x91, 0xcc, 0x5, 0x6, 0x4, 0xd, 
       0x92, 0x93, 0xc, 0x6, 0x2, 0x2, 0x93, 0x95, 0x7, 0x1b, 0x2, 0x2, 
       0x94, 0x96, 0x7, 0x22, 0x2, 0x2, 0x95, 0x94, 0x3, 0x2, 0x2, 0x2, 
       0x95, 0x96, 0x3, 0x2, 0x2, 0x2, 0x96, 0x98, 0x3, 0x2, 0x2, 0x2, 0x97, 
       0x99, 0x7, 0x28, 0x2, 0x2, 0x98, 0x97, 0x3, 0x2, 0x2, 0x2, 0x98, 
       0x99, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9c, 
       0x7, 0x13, 0x2, 0x2, 0x9b, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9c, 
       0x3, 0x2, 0x2, 0x2, 0x9c, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9f, 0x7, 
       0x28, 0x2, 0x2, 0x9e, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x3, 
       0x2, 0x2, 0x2, 0x9f, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa2, 0x7, 0x23, 
       0x2, 0x2, 0xa1, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 0x3, 0x2, 0x2, 
       0x2, 0xa2, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xcc, 0x5, 0x6, 0x4, 0x7, 
       0xa4, 0xa5, 0xc, 0xb, 0x2, 0x2, 0xa5, 0xa6, 0x7, 0x22, 0x2, 0x2, 
       0xa6, 0xa8, 0x7, 0x2f, 0x2, 0x2, 0xa7, 0xa9, 0x7, 0x28, 0x2, 0x2, 
       0xa8, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xa9, 
       0xab, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xac, 0x7, 0x13, 0x2, 0x2, 0xab, 
       0xaa, 0x3, 0x2, 0x2, 0x2, 0xab, 0xac, 0x3, 0x2, 0x2, 0x2, 0xac, 0xae, 
       0x3, 0x2, 0x2, 0x2, 0xad, 0xaf, 0x7, 0x28, 0x2, 0x2, 0xae, 0xad, 
       0x3, 0x2, 0x2, 0x2, 0xae, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xb0, 0x3, 
       0x2, 0x2, 0x2, 0xb0, 0xcc, 0x7, 0x23, 0x2, 0x2, 0xb1, 0xb2, 0xc, 
       0xa, 0x2, 0x2, 0xb2, 0xb3, 0x7, 0x22, 0x2, 0x2, 0xb3, 0xb4, 0x7, 
       0x2d, 0x2, 0x2, 0xb4, 0xcc, 0x7, 0x23, 0x2, 0x2, 0xb5, 0xb6, 0xc, 
       0x9, 0x2, 0x2, 0xb6, 0xb7, 0x7, 0x22, 0x2, 0x2, 0xb7, 0xb8, 0x7, 
       0x1a, 0x2, 0x2, 0xb8, 0xba, 0x7, 0x28, 0x2, 0x2, 0xb9, 0xbb, 0x7, 
       0x13, 0x2, 0x2, 0xba, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 0x3, 
       0x2, 0x2, 0x2, 0xbb, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbe, 0x7, 0x28, 
       0x2, 0x2, 0xbd, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 0x3, 0x2, 0x2, 
       0x2, 0xbe, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xcc, 0x7, 0x23, 0x2, 
       0x2, 0xc0, 0xc1, 0xc, 0x8, 0x2, 0x2, 0xc1, 0xc2, 0x7, 0x22, 0x2, 
       0x2, 0xc2, 0xc3, 0x7, 0x14, 0x2, 0x2, 0xc3, 0xc5, 0x7, 0x28, 0x2, 
       0x2, 0xc4, 0xc6, 0x7, 0x13, 0x2, 0x2, 0xc5, 0xc4, 0x3, 0x2, 0x2, 
       0x2, 0xc5, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc8, 0x3, 0x2, 0x2, 0x2, 
       0xc7, 0xc9, 0x7, 0x28, 0x2, 0x2, 0xc8, 0xc7, 0x3, 0x2, 0x2, 0x2, 
       0xc8, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xca, 0x3, 0x2, 0x2, 0x2, 0xca, 
       0xcc, 0x7, 0x23, 0x2, 0x2, 0xcb, 0x83, 0x3, 0x2, 0x2, 0x2, 0xcb, 
       0x86, 0x3, 0x2, 0x2, 0x2, 0xcb, 0x89, 0x3, 0x2, 0x2, 0x2, 0xcb, 0x8c, 
       0x3, 0x2, 0x2, 0x2, 0xcb, 0x8f, 0x3, 0x2, 0x2, 0x2, 0xcb, 0x92, 0x3, 
       0x2, 0x2, 0x2, 0xcb, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xb1, 0x3, 0x2, 
       0x2, 0x2, 0xcb, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xc0, 0x3, 0x2, 0x2, 
       0x2, 0xcc, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xcb, 0x3, 0x2, 0x2, 0x2, 
       0xcd, 0xce, 0x3, 0x2, 0x2, 0x2, 0xce, 0x7, 0x3, 0x2, 0x2, 0x2, 0xcf, 
       0xcd, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xd1, 0x8, 0x5, 0x1, 0x2, 0xd1, 0xe6, 
       0x5, 0x12, 0xa, 0x2, 0xd2, 0xe6, 0x5, 0xa, 0x6, 0x2, 0xd3, 0xe6, 
       0x7, 0xc, 0x2, 0x2, 0xd4, 0xd5, 0x7, 0x24, 0x2, 0x2, 0xd5, 0xd6, 
       0x5, 0x8, 0x5, 0x2, 0xd6, 0xd7, 0x7, 0x25, 0x2, 0x2, 0xd7, 0xe6, 
       0x3, 0x2, 0x2, 0x2, 0xd8, 0xd9, 0x7, 0x3f, 0x2, 0x2, 0xd9, 0xe6, 
       0x5, 0x8, 0x5, 0xb, 0xda, 0xdb, 0x7, 0x10, 0x2, 0x2, 0xdb, 0xdc, 
       0x7, 0x22, 0x2, 0x2, 0xdc, 0xdd, 0x7, 0x28, 0x2, 0x2, 0xdd, 0xde, 
       0x7, 0x23, 0x2, 0x2, 0xde, 0xe6, 0x5, 0x8, 0x5, 0x5, 0xdf, 0xe0, 
       0x7, 0x10, 0x2, 0x2, 0xe0, 0xe6, 0x5, 0x8, 0x5, 0x4, 0xe1, 0xe2, 
       0x7, 0x20, 0x2, 0x2, 0xe2, 0xe3, 0x5, 0x6, 0x4, 0x2, 0xe3, 0xe4, 
       0x7, 0x21, 0x2, 0x2, 0xe4, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xd0, 
       0x3, 0x2, 0x2, 0x2, 0xe5, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xd3, 0x3, 
       0x2, 0x2, 0x2, 0xe5, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xd8, 0x3, 0x2, 
       0x2, 0x2, 0xe5, 0xda, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xdf, 0x3, 0x2, 0x2, 
       0x2, 0xe5, 0xe1, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xf8, 0x3, 0x2, 0x2, 0x2, 
       0xe7, 0xe8, 0xc, 0xa, 0x2, 0x2, 0xe8, 0xe9, 0x7, 0x3d, 0x2, 0x2, 
       0xe9, 0xf7, 0x5, 0x8, 0x5, 0xb, 0xea, 0xeb, 0xc, 0x9, 0x2, 0x2, 0xeb, 
       0xec, 0x7, 0x3e, 0x2, 0x2, 0xec, 0xf7, 0x5, 0x8, 0x5, 0xa, 0xed, 
       0xee, 0xc, 0x8, 0x2, 0x2, 0xee, 0xef, 0x7, 0x17, 0x2, 0x2, 0xef, 
       0xf7, 0x5, 0x8, 0x5, 0x9, 0xf0, 0xf1, 0xc, 0x7, 0x2, 0x2, 0xf1, 0xf2, 
       0x7, 0x11, 0x2, 0x2, 0xf2, 0xf7, 0x5, 0x8, 0x5, 0x8, 0xf3, 0xf4, 
       0xc, 0x6, 0x2, 0x2, 0xf4, 0xf5, 0x7, 0x12, 0x2, 0x2, 0xf5, 0xf7, 
       0x5, 0x8, 0x5, 0x7, 0xf6, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xea, 0x3, 
       0x2, 0x2, 0x2, 0xf6, 0xed, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf0, 0x3, 0x2, 
       0x2, 0x2, 0xf6, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xfa, 0x3, 0x2, 0x2, 
       0x2, 0xf8, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf9, 0x3, 0x2, 0x2, 0x2, 
       0xf9, 0x9, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xfb, 
       0xfc, 0x7, 0x3, 0x2, 0x2, 0xfc, 0xfd, 0x7, 0x28, 0x2, 0x2, 0xfd, 
       0xb, 0x3, 0x2, 0x2, 0x2, 0xfe, 0xff, 0x7, 0x4, 0x2, 0x2, 0xff, 0x100, 
       0x7, 0x28, 0x2, 0x2, 0x100, 0x101, 0x7, 0x13, 0x2, 0x2, 0x101, 0xd, 
       0x3, 0x2, 0x2, 0x2, 0x102, 0x103, 0x7, 0x5, 0x2, 0x2, 0x103, 0x104, 
       0x7, 0x28, 0x2, 0x2, 0x104, 0x105, 0x7, 0x37, 0x2, 0x2, 0x105, 0x106, 
       0x7, 0x13, 0x2, 0x2, 0x106, 0xf, 0x3, 0x2, 0x2, 0x2, 0x107, 0x108, 
       0x7, 0x6, 0x2, 0x2, 0x108, 0x109, 0x7, 0x28, 0x2, 0x2, 0x109, 0x10a, 
       0x7, 0x23, 0x2, 0x2, 0x10a, 0x10b, 0x7, 0xd, 0x2, 0x2, 0x10b, 0x10c, 
       0x7, 0x13, 0x2, 0x2, 0x10c, 0x11, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10e, 
       0x8, 0xa, 0x1, 0x2, 0x10e, 0x10f, 0x7, 0x3f, 0x2, 0x2, 0x10f, 0x130, 
       0x5, 0x12, 0xa, 0x11, 0x110, 0x111, 0x5, 0x1a, 0xe, 0x2, 0x111, 0x112, 
       0x5, 0x2c, 0x17, 0x2, 0x112, 0x113, 0x5, 0x1a, 0xe, 0x2, 0x113, 0x130, 
       0x3, 0x2, 0x2, 0x2, 0x114, 0x115, 0x5, 0x22, 0x12, 0x2, 0x115, 0x116, 
       0x5, 0x2c, 0x17, 0x2, 0x116, 0x117, 0x5, 0x22, 0x12, 0x2, 0x117, 
       0x130, 0x3, 0x2, 0x2, 0x2, 0x118, 0x119, 0x5, 0x1a, 0xe, 0x2, 0x119, 
       0x11a, 0x7, 0x35, 0x2, 0x2, 0x11a, 0x11b, 0x5, 0x1a, 0xe, 0x2, 0x11b, 
       0x130, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x11d, 0x5, 0x22, 0x12, 0x2, 0x11d, 
       0x11e, 0x7, 0x35, 0x2, 0x2, 0x11e, 0x11f, 0x5, 0x22, 0x12, 0x2, 0x11f, 
       0x130, 0x3, 0x2, 0x2, 0x2, 0x120, 0x121, 0x5, 0x1a, 0xe, 0x2, 0x121, 
       0x122, 0x7, 0x36, 0x2, 0x2, 0x122, 0x123, 0x5, 0x1a, 0xe, 0x2, 0x123, 
       0x130, 0x3, 0x2, 0x2, 0x2, 0x124, 0x125, 0x5, 0x22, 0x12, 0x2, 0x125, 
       0x126, 0x7, 0x36, 0x2, 0x2, 0x126, 0x127, 0x5, 0x22, 0x12, 0x2, 0x127, 
       0x130, 0x3, 0x2, 0x2, 0x2, 0x128, 0x130, 0x5, 0x14, 0xb, 0x2, 0x129, 
       0x130, 0x5, 0x1a, 0xe, 0x2, 0x12a, 0x130, 0x5, 0x22, 0x12, 0x2, 0x12b, 
       0x12c, 0x7, 0x24, 0x2, 0x2, 0x12c, 0x12d, 0x5, 0x12, 0xa, 0x2, 0x12d, 
       0x12e, 0x7, 0x25, 0x2, 0x2, 0x12e, 0x130, 0x3, 0x2, 0x2, 0x2, 0x12f, 
       0x10d, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x110, 0x3, 0x2, 0x2, 0x2, 0x12f, 
       0x114, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x118, 0x3, 0x2, 0x2, 0x2, 0x12f, 
       0x11c, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x120, 0x3, 0x2, 0x2, 0x2, 0x12f, 
       0x124, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x128, 0x3, 0x2, 0x2, 0x2, 0x12f, 
       0x129, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12f, 
       0x12b, 0x3, 0x2, 0x2, 0x2, 0x130, 0x13f, 0x3, 0x2, 0x2, 0x2, 0x131, 
       0x132, 0xc, 0xc, 0x2, 0x2, 0x132, 0x133, 0x7, 0x35, 0x2, 0x2, 0x133, 
       0x13e, 0x5, 0x12, 0xa, 0xd, 0x134, 0x135, 0xc, 0x9, 0x2, 0x2, 0x135, 
       0x136, 0x7, 0x36, 0x2, 0x2, 0x136, 0x13e, 0x5, 0x12, 0xa, 0xa, 0x137, 
       0x138, 0xc, 0x8, 0x2, 0x2, 0x138, 0x139, 0x7, 0x3d, 0x2, 0x2, 0x139, 
       0x13e, 0x5, 0x12, 0xa, 0x9, 0x13a, 0x13b, 0xc, 0x7, 0x2, 0x2, 0x13b, 
       0x13c, 0x7, 0x3e, 0x2, 0x2, 0x13c, 0x13e, 0x5, 0x12, 0xa, 0x8, 0x13d, 
       0x131, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x134, 0x3, 0x2, 0x2, 0x2, 0x13d, 
       0x137, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x13e, 
       0x141, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13f, 
       0x140, 0x3, 0x2, 0x2, 0x2, 0x140, 0x13, 0x3, 0x2, 0x2, 0x2, 0x141, 
       0x13f, 0x3, 0x2, 0x2, 0x2, 0x142, 0x145, 0x5, 0x16, 0xc, 0x2, 0x143, 
       0x145, 0x5, 0x18, 0xd, 0x2, 0x144, 0x142, 0x3, 0x2, 0x2, 0x2, 0x144, 
       0x143, 0x3, 0x2, 0x2, 0x2, 0x145, 0x15, 0x3, 0x2, 0x2, 0x2, 0x146, 
       0x147, 0x7, 0x2c, 0x2, 0x2, 0x147, 0x17, 0x3, 0x2, 0x2, 0x2, 0x148, 
       0x149, 0x7, 0x33, 0x2, 0x2, 0x149, 0x14a, 0x5, 0x2a, 0x16, 0x2, 0x14a, 
       0x14b, 0x7, 0x7, 0x2, 0x2, 0x14b, 0x19, 0x3, 0x2, 0x2, 0x2, 0x14c, 
       0x14d, 0x8, 0xe, 0x1, 0x2, 0x14d, 0x14e, 0x7, 0x3a, 0x2, 0x2, 0x14e, 
       0x155, 0x5, 0x1a, 0xe, 0xd, 0x14f, 0x155, 0x5, 0x1c, 0xf, 0x2, 0x150, 
       0x151, 0x7, 0x24, 0x2, 0x2, 0x151, 0x152, 0x5, 0x1a, 0xe, 0x2, 0x152, 
       0x153, 0x7, 0x25, 0x2, 0x2, 0x153, 0x155, 0x3, 0x2, 0x2, 0x2, 0x154, 
       0x14c, 0x3, 0x2, 0x2, 0x2, 0x154, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x154, 
       0x150, 0x3, 0x2, 0x2, 0x2, 0x155, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x156, 
       0x157, 0xc, 0xb, 0x2, 0x2, 0x157, 0x158, 0x9, 0x2, 0x2, 0x2, 0x158, 
       0x16e, 0x5, 0x1a, 0xe, 0xc, 0x159, 0x15a, 0xc, 0xa, 0x2, 0x2, 0x15a, 
       0x15b, 0x9, 0x3, 0x2, 0x2, 0x15b, 0x16e, 0x5, 0x1a, 0xe, 0xb, 0x15c, 
       0x15d, 0xc, 0x9, 0x2, 0x2, 0x15d, 0x15e, 0x7, 0x3b, 0x2, 0x2, 0x15e, 
       0x16e, 0x5, 0x1a, 0xe, 0xa, 0x15f, 0x160, 0xc, 0x8, 0x2, 0x2, 0x160, 
       0x161, 0x7, 0x3c, 0x2, 0x2, 0x161, 0x16e, 0x5, 0x1a, 0xe, 0x9, 0x162, 
       0x163, 0xc, 0x7, 0x2, 0x2, 0x163, 0x164, 0x7, 0x37, 0x2, 0x2, 0x164, 
       0x16e, 0x5, 0x1a, 0xe, 0x8, 0x165, 0x166, 0xc, 0x6, 0x2, 0x2, 0x166, 
       0x167, 0x7, 0x39, 0x2, 0x2, 0x167, 0x16e, 0x5, 0x1a, 0xe, 0x7, 0x168, 
       0x169, 0xc, 0x5, 0x2, 0x2, 0x169, 0x16a, 0x7, 0x38, 0x2, 0x2, 0x16a, 
       0x16e, 0x5, 0x1a, 0xe, 0x6, 0x16b, 0x16c, 0xc, 0xc, 0x2, 0x2, 0x16c, 
       0x16e, 0x7, 0x27, 0x2, 0x2, 0x16d, 0x156, 0x3, 0x2, 0x2, 0x2, 0x16d, 
       0x159, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x16d, 
       0x15f, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x162, 0x3, 0x2, 0x2, 0x2, 0x16d, 
       0x165, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x168, 0x3, 0x2, 0x2, 0x2, 0x16d, 
       0x16b, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x171, 0x3, 0x2, 0x2, 0x2, 0x16f, 
       0x16d, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x170, 0x3, 0x2, 0x2, 0x2, 0x170, 
       0x1b, 0x3, 0x2, 0x2, 0x2, 0x171, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x172, 
       0x175, 0x5, 0x1e, 0x10, 0x2, 0x173, 0x175, 0x5, 0x20, 0x11, 0x2, 
       0x174, 0x172, 0x3, 0x2, 0x2, 0x2, 0x174, 0x173, 0x3, 0x2, 0x2, 0x2, 
       0x175, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x176, 0x177, 0x9, 0x4, 0x2, 0x2, 
       0x177, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x178, 0x179, 0x7, 0x33, 0x2, 0x2, 
       0x179, 0x17a, 0x5, 0x2a, 0x16, 0x2, 0x17a, 0x17b, 0x7, 0x8, 0x2, 
       0x2, 0x17b, 0x17c, 0x7, 0x1f, 0x2, 0x2, 0x17c, 0x17d, 0x7, 0x9, 0x2, 
       0x2, 0x17d, 0x17e, 0x7, 0x28, 0x2, 0x2, 0x17e, 0x17f, 0x7, 0xa, 0x2, 
       0x2, 0x17f, 0x21, 0x3, 0x2, 0x2, 0x2, 0x180, 0x181, 0x8, 0x12, 0x1, 
       0x2, 0x181, 0x188, 0x5, 0x24, 0x13, 0x2, 0x182, 0x188, 0x5, 0x1a, 
       0xe, 0x2, 0x183, 0x184, 0x7, 0x24, 0x2, 0x2, 0x184, 0x185, 0x5, 0x22, 
       0x12, 0x2, 0x185, 0x186, 0x7, 0x25, 0x2, 0x2, 0x186, 0x188, 0x3, 
       0x2, 0x2, 0x2, 0x187, 0x180, 0x3, 0x2, 0x2, 0x2, 0x187, 0x182, 0x3, 
       0x2, 0x2, 0x2, 0x187, 0x183, 0x3, 0x2, 0x2, 0x2, 0x188, 0x191, 0x3, 
       0x2, 0x2, 0x2, 0x189, 0x18a, 0xc, 0x7, 0x2, 0x2, 0x18a, 0x18b, 0x9, 
       0x2, 0x2, 0x2, 0x18b, 0x190, 0x5, 0x22, 0x12, 0x8, 0x18c, 0x18d, 
       0xc, 0x6, 0x2, 0x2, 0x18d, 0x18e, 0x9, 0x3, 0x2, 0x2, 0x18e, 0x190, 
       0x5, 0x22, 0x12, 0x7, 0x18f, 0x189, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x18c, 
       0x3, 0x2, 0x2, 0x2, 0x190, 0x193, 0x3, 0x2, 0x2, 0x2, 0x191, 0x18f, 
       0x3, 0x2, 0x2, 0x2, 0x191, 0x192, 0x3, 0x2, 0x2, 0x2, 0x192, 0x23, 
       0x3, 0x2, 0x2, 0x2, 0x193, 0x191, 0x3, 0x2, 0x2, 0x2, 0x194, 0x197, 
       0x5, 0x26, 0x14, 0x2, 0x195, 0x197, 0x5, 0x28, 0x15, 0x2, 0x196, 
       0x194, 0x3, 0x2, 0x2, 0x2, 0x196, 0x195, 0x3, 0x2, 0x2, 0x2, 0x197, 
       0x25, 0x3, 0x2, 0x2, 0x2, 0x198, 0x199, 0x7, 0x28, 0x2, 0x2, 0x199, 
       0x27, 0x3, 0x2, 0x2, 0x2, 0x19a, 0x19b, 0x7, 0x33, 0x2, 0x2, 0x19b, 
       0x19c, 0x5, 0x2a, 0x16, 0x2, 0x19c, 0x19d, 0x7, 0xb, 0x2, 0x2, 0x19d, 
       0x19e, 0x7, 0x28, 0x2, 0x2, 0x19e, 0x19f, 0x7, 0xa, 0x2, 0x2, 0x19f, 
       0x29, 0x3, 0x2, 0x2, 0x2, 0x1a0, 0x1a1, 0x7, 0x26, 0x2, 0x2, 0x1a1, 
       0x2b, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x1a3, 0x9, 0x5, 0x2, 0x2, 0x1a3, 
       0x2d, 0x3, 0x2, 0x2, 0x2, 0x27, 0x38, 0x5e, 0x63, 0x71, 0x75, 0x78, 
       0x7b, 0x81, 0x95, 0x98, 0x9b, 0x9e, 0xa1, 0xa8, 0xab, 0xae, 0xba, 
       0xbd, 0xc5, 0xc8, 0xcb, 0xcd, 0xe5, 0xf6, 0xf8, 0x12f, 0x13d, 0x13f, 
       0x144, 0x154, 0x16d, 0x16f, 0x174, 0x187, 0x18f, 0x191, 0x196, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

temporalSVAParser::Initializer temporalSVAParser::_init;
