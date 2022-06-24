
// Generated from proposition.g4 by ANTLR 4.9.2


#include "propositionListener.h"

#include "propositionParser.h"


using namespace antlrcpp;
using namespace antlr4;

propositionParser::propositionParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

propositionParser::~propositionParser() {
  delete _interpreter;
}

std::string propositionParser::getGrammarFileName() const {
  return "proposition.g4";
}

const std::vector<std::string>& propositionParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& propositionParser::getVocabulary() const {
  return _vocabulary;
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
    setState(32);
    boolean(0);
    setState(33);
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

tree::TerminalNode* propositionParser::BooleanContext::LPAREN() {
  return getToken(propositionParser::LPAREN, 0);
}

tree::TerminalNode* propositionParser::BooleanContext::RPAREN() {
  return getToken(propositionParser::RPAREN, 0);
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
    setState(69);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(36);
      match(propositionParser::NOT);
      setState(37);
      boolean(15);
      break;
    }

    case 2: {
      setState(38);
      logic(0);
      setState(39);
      relop();
      setState(40);
      logic(0);
      break;
    }

    case 3: {
      setState(42);
      numeric(0);
      setState(43);
      relop();
      setState(44);
      numeric(0);
      break;
    }

    case 4: {
      setState(46);
      logic(0);
      setState(47);
      match(propositionParser::EQ);
      setState(48);
      logic(0);
      break;
    }

    case 5: {
      setState(50);
      numeric(0);
      setState(51);
      match(propositionParser::EQ);
      setState(52);
      numeric(0);
      break;
    }

    case 6: {
      setState(54);
      logic(0);
      setState(55);
      match(propositionParser::NEQ);
      setState(56);
      logic(0);
      break;
    }

    case 7: {
      setState(58);
      numeric(0);
      setState(59);
      match(propositionParser::NEQ);
      setState(60);
      numeric(0);
      break;
    }

    case 8: {
      setState(62);
      booleanAtom();
      break;
    }

    case 9: {
      setState(63);
      logic(0);
      break;
    }

    case 10: {
      setState(64);
      numeric(0);
      break;
    }

    case 11: {
      setState(65);
      match(propositionParser::LPAREN);
      setState(66);
      boolean(0);
      setState(67);
      match(propositionParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(85);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(83);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(71);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(72);
          match(propositionParser::EQ);
          setState(73);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(74);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(75);
          match(propositionParser::NEQ);
          setState(76);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(77);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(78);
          dynamic_cast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::AND);
          setState(79);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(80);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(81);
          dynamic_cast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::OR);
          setState(82);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(87);
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

propositionParser::BooleanConstantContext* propositionParser::BooleanAtomContext::booleanConstant() {
  return getRuleContext<propositionParser::BooleanConstantContext>(0);
}

propositionParser::BooleanVariableContext* propositionParser::BooleanAtomContext::booleanVariable() {
  return getRuleContext<propositionParser::BooleanVariableContext>(0);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(90);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::BOOLEAN: {
        enterOuterAlt(_localctx, 1);
        setState(88);
        booleanConstant();
        break;
      }

      case propositionParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(89);
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

propositionParser::BooleanConstantContext::BooleanConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::BooleanConstantContext::BOOLEAN() {
  return getToken(propositionParser::BOOLEAN, 0);
}


size_t propositionParser::BooleanConstantContext::getRuleIndex() const {
  return propositionParser::RuleBooleanConstant;
}

void propositionParser::BooleanConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanConstant(this);
}

void propositionParser::BooleanConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanConstant(this);
}

propositionParser::BooleanConstantContext* propositionParser::booleanConstant() {
  BooleanConstantContext *_localctx = _tracker.createInstance<BooleanConstantContext>(_ctx, getState());
  enterRule(_localctx, 6, propositionParser::RuleBooleanConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    match(propositionParser::BOOLEAN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanVariableContext ------------------------------------------------------------------

propositionParser::BooleanVariableContext::BooleanVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::BooleanVariableContext::LT() {
  return getToken(propositionParser::LT, 0);
}

propositionParser::VariableContext* propositionParser::BooleanVariableContext::variable() {
  return getRuleContext<propositionParser::VariableContext>(0);
}


size_t propositionParser::BooleanVariableContext::getRuleIndex() const {
  return propositionParser::RuleBooleanVariable;
}

void propositionParser::BooleanVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanVariable(this);
}

void propositionParser::BooleanVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanVariable(this);
}

propositionParser::BooleanVariableContext* propositionParser::booleanVariable() {
  BooleanVariableContext *_localctx = _tracker.createInstance<BooleanVariableContext>(_ctx, getState());
  enterRule(_localctx, 8, propositionParser::RuleBooleanVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    match(propositionParser::LT);
    setState(95);
    variable();
    setState(96);
    match(propositionParser::T__0);
   
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

tree::TerminalNode* propositionParser::LogicContext::LPAREN() {
  return getToken(propositionParser::LPAREN, 0);
}

tree::TerminalNode* propositionParser::LogicContext::RPAREN() {
  return getToken(propositionParser::RPAREN, 0);
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
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, propositionParser::RuleLogic, precedence);

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
    setState(106);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::NEG: {
        setState(99);
        match(propositionParser::NEG);
        setState(100);
        logic(11);
        break;
      }

      case propositionParser::NUMERIC:
      case propositionParser::VERILOG_BINARY:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::LT: {
        setState(101);
        logicAtom();
        break;
      }

      case propositionParser::LPAREN: {
        setState(102);
        match(propositionParser::LPAREN);
        setState(103);
        logic(0);
        setState(104);
        match(propositionParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(133);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(131);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(108);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(109);
          dynamic_cast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::TIMES

          || _la == propositionParser::DIV)) {
            dynamic_cast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(110);
          logic(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(111);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(112);
          dynamic_cast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::PLUS

          || _la == propositionParser::MINUS)) {
            dynamic_cast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(113);
          logic(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(114);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(115);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(propositionParser::LSHIFT);
          setState(116);
          logic(8);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(117);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(118);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(propositionParser::RSHIFT);
          setState(119);
          logic(7);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(120);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(121);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(propositionParser::BAND);
          setState(122);
          logic(6);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(123);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(124);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(propositionParser::BXOR);
          setState(125);
          logic(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(126);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(127);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(propositionParser::BOR);
          setState(128);
          logic(4);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(129);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(130);
          bitSelect();
          break;
        }

        default:
          break;
        } 
      }
      setState(135);
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

//----------------- BitSelectContext ------------------------------------------------------------------

propositionParser::BitSelectContext::BitSelectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::BitSelectContext::LCPAREN() {
  return getToken(propositionParser::LCPAREN, 0);
}

std::vector<tree::TerminalNode *> propositionParser::BitSelectContext::NUMERIC() {
  return getTokens(propositionParser::NUMERIC);
}

tree::TerminalNode* propositionParser::BitSelectContext::NUMERIC(size_t i) {
  return getToken(propositionParser::NUMERIC, i);
}

tree::TerminalNode* propositionParser::BitSelectContext::RCPAREN() {
  return getToken(propositionParser::RCPAREN, 0);
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
  enterRule(_localctx, 12, propositionParser::RuleBitSelect);
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
    match(propositionParser::LCPAREN);
    setState(137);
    match(propositionParser::NUMERIC);
    setState(140);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == propositionParser::T__1) {
      setState(138);
      match(propositionParser::T__1);
      setState(139);
      match(propositionParser::NUMERIC);
    }
    setState(142);
    match(propositionParser::RCPAREN);
   
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

propositionParser::LogicConstantContext* propositionParser::LogicAtomContext::logicConstant() {
  return getRuleContext<propositionParser::LogicConstantContext>(0);
}

propositionParser::LogicVariableContext* propositionParser::LogicAtomContext::logicVariable() {
  return getRuleContext<propositionParser::LogicVariableContext>(0);
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
  enterRule(_localctx, 14, propositionParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(146);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::NUMERIC:
      case propositionParser::VERILOG_BINARY:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(144);
        logicConstant();
        break;
      }

      case propositionParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(145);
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

propositionParser::LogicConstantContext::LogicConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::LogicConstantContext::VERILOG_BINARY() {
  return getToken(propositionParser::VERILOG_BINARY, 0);
}

tree::TerminalNode* propositionParser::LogicConstantContext::GCC_BINARY() {
  return getToken(propositionParser::GCC_BINARY, 0);
}

tree::TerminalNode* propositionParser::LogicConstantContext::NUMERIC() {
  return getToken(propositionParser::NUMERIC, 0);
}

tree::TerminalNode* propositionParser::LogicConstantContext::HEX() {
  return getToken(propositionParser::HEX, 0);
}


size_t propositionParser::LogicConstantContext::getRuleIndex() const {
  return propositionParser::RuleLogicConstant;
}

void propositionParser::LogicConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicConstant(this);
}

void propositionParser::LogicConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicConstant(this);
}

propositionParser::LogicConstantContext* propositionParser::logicConstant() {
  LogicConstantContext *_localctx = _tracker.createInstance<LogicConstantContext>(_ctx, getState());
  enterRule(_localctx, 16, propositionParser::RuleLogicConstant);
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
    setState(148);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << propositionParser::NUMERIC)
      | (1ULL << propositionParser::VERILOG_BINARY)
      | (1ULL << propositionParser::GCC_BINARY)
      | (1ULL << propositionParser::HEX))) != 0))) {
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

propositionParser::LogicVariableContext::LogicVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::LogicVariableContext::LT() {
  return getToken(propositionParser::LT, 0);
}

propositionParser::VariableContext* propositionParser::LogicVariableContext::variable() {
  return getRuleContext<propositionParser::VariableContext>(0);
}

tree::TerminalNode* propositionParser::LogicVariableContext::SIGN() {
  return getToken(propositionParser::SIGN, 0);
}

tree::TerminalNode* propositionParser::LogicVariableContext::NUMERIC() {
  return getToken(propositionParser::NUMERIC, 0);
}


size_t propositionParser::LogicVariableContext::getRuleIndex() const {
  return propositionParser::RuleLogicVariable;
}

void propositionParser::LogicVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicVariable(this);
}

void propositionParser::LogicVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicVariable(this);
}

propositionParser::LogicVariableContext* propositionParser::logicVariable() {
  LogicVariableContext *_localctx = _tracker.createInstance<LogicVariableContext>(_ctx, getState());
  enterRule(_localctx, 18, propositionParser::RuleLogicVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150);
    match(propositionParser::LT);
    setState(151);
    variable();
    setState(152);
    match(propositionParser::T__2);
    setState(153);
    match(propositionParser::SIGN);
    setState(154);
    match(propositionParser::T__3);
    setState(155);
    match(propositionParser::NUMERIC);
    setState(156);
    match(propositionParser::T__4);
   
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

tree::TerminalNode* propositionParser::NumericContext::LPAREN() {
  return getToken(propositionParser::LPAREN, 0);
}

std::vector<propositionParser::NumericContext *> propositionParser::NumericContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext* propositionParser::NumericContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
}

tree::TerminalNode* propositionParser::NumericContext::RPAREN() {
  return getToken(propositionParser::RPAREN, 0);
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
  size_t startState = 20;
  enterRecursionRule(_localctx, 20, propositionParser::RuleNumeric, precedence);

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
    setState(165);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(159);
      numericAtom();
      break;
    }

    case 2: {
      setState(160);
      logic(0);
      break;
    }

    case 3: {
      setState(161);
      match(propositionParser::LPAREN);
      setState(162);
      numeric(0);
      setState(163);
      match(propositionParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(175);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(173);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(167);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(168);
          dynamic_cast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::TIMES

          || _la == propositionParser::DIV)) {
            dynamic_cast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(169);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(170);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(171);
          dynamic_cast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::PLUS

          || _la == propositionParser::MINUS)) {
            dynamic_cast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(172);
          numeric(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(177);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
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

propositionParser::NumericConstantContext* propositionParser::NumericAtomContext::numericConstant() {
  return getRuleContext<propositionParser::NumericConstantContext>(0);
}

propositionParser::NumericVariableContext* propositionParser::NumericAtomContext::numericVariable() {
  return getRuleContext<propositionParser::NumericVariableContext>(0);
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
  enterRule(_localctx, 22, propositionParser::RuleNumericAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(180);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::NUMERIC: {
        enterOuterAlt(_localctx, 1);
        setState(178);
        numericConstant();
        break;
      }

      case propositionParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(179);
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

propositionParser::NumericConstantContext::NumericConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::NumericConstantContext::NUMERIC() {
  return getToken(propositionParser::NUMERIC, 0);
}


size_t propositionParser::NumericConstantContext::getRuleIndex() const {
  return propositionParser::RuleNumericConstant;
}

void propositionParser::NumericConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericConstant(this);
}

void propositionParser::NumericConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericConstant(this);
}

propositionParser::NumericConstantContext* propositionParser::numericConstant() {
  NumericConstantContext *_localctx = _tracker.createInstance<NumericConstantContext>(_ctx, getState());
  enterRule(_localctx, 24, propositionParser::RuleNumericConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    match(propositionParser::NUMERIC);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericVariableContext ------------------------------------------------------------------

propositionParser::NumericVariableContext::NumericVariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::NumericVariableContext::LT() {
  return getToken(propositionParser::LT, 0);
}

propositionParser::VariableContext* propositionParser::NumericVariableContext::variable() {
  return getRuleContext<propositionParser::VariableContext>(0);
}

tree::TerminalNode* propositionParser::NumericVariableContext::NUMERIC() {
  return getToken(propositionParser::NUMERIC, 0);
}


size_t propositionParser::NumericVariableContext::getRuleIndex() const {
  return propositionParser::RuleNumericVariable;
}

void propositionParser::NumericVariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericVariable(this);
}

void propositionParser::NumericVariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericVariable(this);
}

propositionParser::NumericVariableContext* propositionParser::numericVariable() {
  NumericVariableContext *_localctx = _tracker.createInstance<NumericVariableContext>(_ctx, getState());
  enterRule(_localctx, 26, propositionParser::RuleNumericVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    match(propositionParser::LT);
    setState(185);
    variable();
    setState(186);
    match(propositionParser::T__5);
    setState(187);
    match(propositionParser::NUMERIC);
    setState(188);
    match(propositionParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

propositionParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* propositionParser::VariableContext::VARIABLE() {
  return getToken(propositionParser::VARIABLE, 0);
}


size_t propositionParser::VariableContext::getRuleIndex() const {
  return propositionParser::RuleVariable;
}

void propositionParser::VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void propositionParser::VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

propositionParser::VariableContext* propositionParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 28, propositionParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    match(propositionParser::VARIABLE);
   
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
  enterRule(_localctx, 30, propositionParser::RuleRelop);
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

bool propositionParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return booleanSempred(dynamic_cast<BooleanContext *>(context), predicateIndex);
    case 5: return logicSempred(dynamic_cast<LogicContext *>(context), predicateIndex);
    case 10: return numericSempred(dynamic_cast<NumericContext *>(context), predicateIndex);

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

// Static vars and initialization.
std::vector<dfa::DFA> propositionParser::_decisionToDFA;
atn::PredictionContextCache propositionParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN propositionParser::_atn;
std::vector<uint16_t> propositionParser::_serializedATN;

std::vector<std::string> propositionParser::_ruleNames = {
  "file", "boolean", "booleanAtom", "booleanConstant", "booleanVariable", 
  "logic", "bitSelect", "logicAtom", "logicConstant", "logicVariable", "numeric", 
  "numericAtom", "numericConstant", "numericVariable", "variable", "relop"
};

std::vector<std::string> propositionParser::_literalNames = {
  "", "',bool>'", "':'", "',logic('", "','", "')>'", "',numeric('", "", 
  "'{'", "'}'", "'['", "']'", "'('", "')'", "", "", "", "", "", "", "'+'", 
  "'-'", "'*'", "'/'", "'>'", "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", 
  "'|'", "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'"
};

std::vector<std::string> propositionParser::_symbolicNames = {
  "", "", "", "", "", "", "", "SIGN", "LGPAREN", "RGPAREN", "LCPAREN", "RCPAREN", 
  "LPAREN", "RPAREN", "VARIABLE", "NUMERIC", "VERILOG_BINARY", "GCC_BINARY", 
  "HEX", "BOOLEAN", "PLUS", "MINUS", "TIMES", "DIV", "GT", "GE", "LT", "LE", 
  "EQ", "NEQ", "BAND", "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", 
  "OR", "NOT", "WS"
};

dfa::Vocabulary propositionParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> propositionParser::_tokenNames;

propositionParser::Initializer::Initializer() {
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
       0x3, 0x29, 0xc5, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 
       0x48, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x7, 0x3, 0x56, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x59, 0xb, 0x3, 
       0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x5d, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 
       0x6d, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x86, 
       0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x89, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 
       0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x8f, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 
       0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x95, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 
       0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
       0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
       0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0xa8, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 
       0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0xb0, 0xa, 0xc, 
       0xc, 0xc, 0xe, 0xc, 0xb3, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 
       0xb7, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 
       0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 
       0x11, 0x3, 0x11, 0x2, 0x5, 0x4, 0xc, 0x16, 0x12, 0x2, 0x4, 0x6, 0x8, 
       0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 
       0x2, 0x6, 0x3, 0x2, 0x18, 0x19, 0x3, 0x2, 0x16, 0x17, 0x3, 0x2, 0x11, 
       0x14, 0x3, 0x2, 0x1a, 0x1d, 0x2, 0xd4, 0x2, 0x22, 0x3, 0x2, 0x2, 
       0x2, 0x4, 0x47, 0x3, 0x2, 0x2, 0x2, 0x6, 0x5c, 0x3, 0x2, 0x2, 0x2, 
       0x8, 0x5e, 0x3, 0x2, 0x2, 0x2, 0xa, 0x60, 0x3, 0x2, 0x2, 0x2, 0xc, 
       0x6c, 0x3, 0x2, 0x2, 0x2, 0xe, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x10, 0x94, 
       0x3, 0x2, 0x2, 0x2, 0x12, 0x96, 0x3, 0x2, 0x2, 0x2, 0x14, 0x98, 0x3, 
       0x2, 0x2, 0x2, 0x16, 0xa7, 0x3, 0x2, 0x2, 0x2, 0x18, 0xb6, 0x3, 0x2, 
       0x2, 0x2, 0x1a, 0xb8, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xba, 0x3, 0x2, 0x2, 
       0x2, 0x1e, 0xc0, 0x3, 0x2, 0x2, 0x2, 0x20, 0xc2, 0x3, 0x2, 0x2, 0x2, 
       0x22, 0x23, 0x5, 0x4, 0x3, 0x2, 0x23, 0x24, 0x7, 0x2, 0x2, 0x3, 0x24, 
       0x3, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x8, 0x3, 0x1, 0x2, 0x26, 0x27, 
       0x7, 0x28, 0x2, 0x2, 0x27, 0x48, 0x5, 0x4, 0x3, 0x11, 0x28, 0x29, 
       0x5, 0xc, 0x7, 0x2, 0x29, 0x2a, 0x5, 0x20, 0x11, 0x2, 0x2a, 0x2b, 
       0x5, 0xc, 0x7, 0x2, 0x2b, 0x48, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x5, 
       0x16, 0xc, 0x2, 0x2d, 0x2e, 0x5, 0x20, 0x11, 0x2, 0x2e, 0x2f, 0x5, 
       0x16, 0xc, 0x2, 0x2f, 0x48, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x5, 
       0xc, 0x7, 0x2, 0x31, 0x32, 0x7, 0x1e, 0x2, 0x2, 0x32, 0x33, 0x5, 
       0xc, 0x7, 0x2, 0x33, 0x48, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x5, 0x16, 
       0xc, 0x2, 0x35, 0x36, 0x7, 0x1e, 0x2, 0x2, 0x36, 0x37, 0x5, 0x16, 
       0xc, 0x2, 0x37, 0x48, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x5, 0xc, 0x7, 
       0x2, 0x39, 0x3a, 0x7, 0x1f, 0x2, 0x2, 0x3a, 0x3b, 0x5, 0xc, 0x7, 
       0x2, 0x3b, 0x48, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x5, 0x16, 0xc, 
       0x2, 0x3d, 0x3e, 0x7, 0x1f, 0x2, 0x2, 0x3e, 0x3f, 0x5, 0x16, 0xc, 
       0x2, 0x3f, 0x48, 0x3, 0x2, 0x2, 0x2, 0x40, 0x48, 0x5, 0x6, 0x4, 0x2, 
       0x41, 0x48, 0x5, 0xc, 0x7, 0x2, 0x42, 0x48, 0x5, 0x16, 0xc, 0x2, 
       0x43, 0x44, 0x7, 0xe, 0x2, 0x2, 0x44, 0x45, 0x5, 0x4, 0x3, 0x2, 0x45, 
       0x46, 0x7, 0xf, 0x2, 0x2, 0x46, 0x48, 0x3, 0x2, 0x2, 0x2, 0x47, 0x25, 
       0x3, 0x2, 0x2, 0x2, 0x47, 0x28, 0x3, 0x2, 0x2, 0x2, 0x47, 0x2c, 0x3, 
       0x2, 0x2, 0x2, 0x47, 0x30, 0x3, 0x2, 0x2, 0x2, 0x47, 0x34, 0x3, 0x2, 
       0x2, 0x2, 0x47, 0x38, 0x3, 0x2, 0x2, 0x2, 0x47, 0x3c, 0x3, 0x2, 0x2, 
       0x2, 0x47, 0x40, 0x3, 0x2, 0x2, 0x2, 0x47, 0x41, 0x3, 0x2, 0x2, 0x2, 
       0x47, 0x42, 0x3, 0x2, 0x2, 0x2, 0x47, 0x43, 0x3, 0x2, 0x2, 0x2, 0x48, 
       0x57, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0xc, 0xc, 0x2, 0x2, 0x4a, 0x4b, 
       0x7, 0x1e, 0x2, 0x2, 0x4b, 0x56, 0x5, 0x4, 0x3, 0xd, 0x4c, 0x4d, 
       0xc, 0x9, 0x2, 0x2, 0x4d, 0x4e, 0x7, 0x1f, 0x2, 0x2, 0x4e, 0x56, 
       0x5, 0x4, 0x3, 0xa, 0x4f, 0x50, 0xc, 0x8, 0x2, 0x2, 0x50, 0x51, 0x7, 
       0x26, 0x2, 0x2, 0x51, 0x56, 0x5, 0x4, 0x3, 0x9, 0x52, 0x53, 0xc, 
       0x7, 0x2, 0x2, 0x53, 0x54, 0x7, 0x27, 0x2, 0x2, 0x54, 0x56, 0x5, 
       0x4, 0x3, 0x8, 0x55, 0x49, 0x3, 0x2, 0x2, 0x2, 0x55, 0x4c, 0x3, 0x2, 
       0x2, 0x2, 0x55, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x55, 0x52, 0x3, 0x2, 0x2, 
       0x2, 0x56, 0x59, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 0x3, 0x2, 0x2, 0x2, 
       0x57, 0x58, 0x3, 0x2, 0x2, 0x2, 0x58, 0x5, 0x3, 0x2, 0x2, 0x2, 0x59, 
       0x57, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5d, 0x5, 0x8, 0x5, 0x2, 0x5b, 0x5d, 
       0x5, 0xa, 0x6, 0x2, 0x5c, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5b, 0x3, 
       0x2, 0x2, 0x2, 0x5d, 0x7, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x7, 0x15, 
       0x2, 0x2, 0x5f, 0x9, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x7, 0x1c, 0x2, 
       0x2, 0x61, 0x62, 0x5, 0x1e, 0x10, 0x2, 0x62, 0x63, 0x7, 0x3, 0x2, 
       0x2, 0x63, 0xb, 0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 0x8, 0x7, 0x1, 0x2, 
       0x65, 0x66, 0x7, 0x23, 0x2, 0x2, 0x66, 0x6d, 0x5, 0xc, 0x7, 0xd, 
       0x67, 0x6d, 0x5, 0x10, 0x9, 0x2, 0x68, 0x69, 0x7, 0xe, 0x2, 0x2, 
       0x69, 0x6a, 0x5, 0xc, 0x7, 0x2, 0x6a, 0x6b, 0x7, 0xf, 0x2, 0x2, 0x6b, 
       0x6d, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x64, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x67, 
       0x3, 0x2, 0x2, 0x2, 0x6c, 0x68, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x87, 0x3, 
       0x2, 0x2, 0x2, 0x6e, 0x6f, 0xc, 0xb, 0x2, 0x2, 0x6f, 0x70, 0x9, 0x2, 
       0x2, 0x2, 0x70, 0x86, 0x5, 0xc, 0x7, 0xc, 0x71, 0x72, 0xc, 0xa, 0x2, 
       0x2, 0x72, 0x73, 0x9, 0x3, 0x2, 0x2, 0x73, 0x86, 0x5, 0xc, 0x7, 0xb, 
       0x74, 0x75, 0xc, 0x9, 0x2, 0x2, 0x75, 0x76, 0x7, 0x24, 0x2, 0x2, 
       0x76, 0x86, 0x5, 0xc, 0x7, 0xa, 0x77, 0x78, 0xc, 0x8, 0x2, 0x2, 0x78, 
       0x79, 0x7, 0x25, 0x2, 0x2, 0x79, 0x86, 0x5, 0xc, 0x7, 0x9, 0x7a, 
       0x7b, 0xc, 0x7, 0x2, 0x2, 0x7b, 0x7c, 0x7, 0x20, 0x2, 0x2, 0x7c, 
       0x86, 0x5, 0xc, 0x7, 0x8, 0x7d, 0x7e, 0xc, 0x6, 0x2, 0x2, 0x7e, 0x7f, 
       0x7, 0x22, 0x2, 0x2, 0x7f, 0x86, 0x5, 0xc, 0x7, 0x7, 0x80, 0x81, 
       0xc, 0x5, 0x2, 0x2, 0x81, 0x82, 0x7, 0x21, 0x2, 0x2, 0x82, 0x86, 
       0x5, 0xc, 0x7, 0x6, 0x83, 0x84, 0xc, 0xc, 0x2, 0x2, 0x84, 0x86, 0x5, 
       0xe, 0x8, 0x2, 0x85, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x85, 0x71, 0x3, 0x2, 
       0x2, 0x2, 0x85, 0x74, 0x3, 0x2, 0x2, 0x2, 0x85, 0x77, 0x3, 0x2, 0x2, 
       0x2, 0x85, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x85, 0x7d, 0x3, 0x2, 0x2, 0x2, 
       0x85, 0x80, 0x3, 0x2, 0x2, 0x2, 0x85, 0x83, 0x3, 0x2, 0x2, 0x2, 0x86, 
       0x89, 0x3, 0x2, 0x2, 0x2, 0x87, 0x85, 0x3, 0x2, 0x2, 0x2, 0x87, 0x88, 
       0x3, 0x2, 0x2, 0x2, 0x88, 0xd, 0x3, 0x2, 0x2, 0x2, 0x89, 0x87, 0x3, 
       0x2, 0x2, 0x2, 0x8a, 0x8b, 0x7, 0xc, 0x2, 0x2, 0x8b, 0x8e, 0x7, 0x11, 
       0x2, 0x2, 0x8c, 0x8d, 0x7, 0x4, 0x2, 0x2, 0x8d, 0x8f, 0x7, 0x11, 
       0x2, 0x2, 0x8e, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x3, 0x2, 0x2, 
       0x2, 0x8f, 0x90, 0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x7, 0xd, 0x2, 0x2, 
       0x91, 0xf, 0x3, 0x2, 0x2, 0x2, 0x92, 0x95, 0x5, 0x12, 0xa, 0x2, 0x93, 
       0x95, 0x5, 0x14, 0xb, 0x2, 0x94, 0x92, 0x3, 0x2, 0x2, 0x2, 0x94, 
       0x93, 0x3, 0x2, 0x2, 0x2, 0x95, 0x11, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 
       0x9, 0x4, 0x2, 0x2, 0x97, 0x13, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x7, 
       0x1c, 0x2, 0x2, 0x99, 0x9a, 0x5, 0x1e, 0x10, 0x2, 0x9a, 0x9b, 0x7, 
       0x5, 0x2, 0x2, 0x9b, 0x9c, 0x7, 0x9, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0x6, 
       0x2, 0x2, 0x9d, 0x9e, 0x7, 0x11, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x7, 
       0x2, 0x2, 0x9f, 0x15, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x8, 0xc, 0x1, 
       0x2, 0xa1, 0xa8, 0x5, 0x18, 0xd, 0x2, 0xa2, 0xa8, 0x5, 0xc, 0x7, 
       0x2, 0xa3, 0xa4, 0x7, 0xe, 0x2, 0x2, 0xa4, 0xa5, 0x5, 0x16, 0xc, 
       0x2, 0xa5, 0xa6, 0x7, 0xf, 0x2, 0x2, 0xa6, 0xa8, 0x3, 0x2, 0x2, 0x2, 
       0xa7, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa7, 
       0xa3, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xaa, 
       0xc, 0x7, 0x2, 0x2, 0xaa, 0xab, 0x9, 0x2, 0x2, 0x2, 0xab, 0xb0, 0x5, 
       0x16, 0xc, 0x8, 0xac, 0xad, 0xc, 0x6, 0x2, 0x2, 0xad, 0xae, 0x9, 
       0x3, 0x2, 0x2, 0xae, 0xb0, 0x5, 0x16, 0xc, 0x7, 0xaf, 0xa9, 0x3, 
       0x2, 0x2, 0x2, 0xaf, 0xac, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb3, 0x3, 0x2, 
       0x2, 0x2, 0xb1, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb2, 0x3, 0x2, 0x2, 
       0x2, 0xb2, 0x17, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb1, 0x3, 0x2, 0x2, 0x2, 
       0xb4, 0xb7, 0x5, 0x1a, 0xe, 0x2, 0xb5, 0xb7, 0x5, 0x1c, 0xf, 0x2, 
       0xb6, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb7, 
       0x19, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb9, 0x7, 0x11, 0x2, 0x2, 0xb9, 
       0x1b, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 0x7, 0x1c, 0x2, 0x2, 0xbb, 
       0xbc, 0x5, 0x1e, 0x10, 0x2, 0xbc, 0xbd, 0x7, 0x8, 0x2, 0x2, 0xbd, 
       0xbe, 0x7, 0x11, 0x2, 0x2, 0xbe, 0xbf, 0x7, 0x7, 0x2, 0x2, 0xbf, 
       0x1d, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xc1, 0x7, 0x10, 0x2, 0x2, 0xc1, 
       0x1f, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc3, 0x9, 0x5, 0x2, 0x2, 0xc3, 0x21, 
       0x3, 0x2, 0x2, 0x2, 0xf, 0x47, 0x55, 0x57, 0x5c, 0x6c, 0x85, 0x87, 
       0x8e, 0x94, 0xa7, 0xaf, 0xb1, 0xb6, 
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

propositionParser::Initializer propositionParser::_init;
