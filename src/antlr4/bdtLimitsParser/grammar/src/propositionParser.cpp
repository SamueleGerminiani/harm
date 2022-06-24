
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
    setState(30);
    boolean(0);
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
    setState(67);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(34);
      match(propositionParser::NOT);
      setState(35);
      boolean(15);
      break;
    }

    case 2: {
      setState(36);
      logic(0);
      setState(37);
      relop();
      setState(38);
      logic(0);
      break;
    }

    case 3: {
      setState(40);
      numeric(0);
      setState(41);
      relop();
      setState(42);
      numeric(0);
      break;
    }

    case 4: {
      setState(44);
      logic(0);
      setState(45);
      match(propositionParser::EQ);
      setState(46);
      logic(0);
      break;
    }

    case 5: {
      setState(48);
      numeric(0);
      setState(49);
      match(propositionParser::EQ);
      setState(50);
      numeric(0);
      break;
    }

    case 6: {
      setState(52);
      logic(0);
      setState(53);
      match(propositionParser::NEQ);
      setState(54);
      logic(0);
      break;
    }

    case 7: {
      setState(56);
      numeric(0);
      setState(57);
      match(propositionParser::NEQ);
      setState(58);
      numeric(0);
      break;
    }

    case 8: {
      setState(60);
      booleanAtom();
      break;
    }

    case 9: {
      setState(61);
      logic(0);
      break;
    }

    case 10: {
      setState(62);
      numeric(0);
      break;
    }

    case 11: {
      setState(63);
      match(propositionParser::LPAREN);
      setState(64);
      boolean(0);
      setState(65);
      match(propositionParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(83);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(81);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(69);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(70);
          match(propositionParser::EQ);
          setState(71);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(72);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(73);
          match(propositionParser::NEQ);
          setState(74);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(75);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(76);
          dynamic_cast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::AND);
          setState(77);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(78);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(79);
          dynamic_cast<BooleanContext *>(_localctx)->booleanop = match(propositionParser::OR);
          setState(80);
          boolean(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(85);
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
    setState(88);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::BOOLEAN: {
        enterOuterAlt(_localctx, 1);
        setState(86);
        booleanConstant();
        break;
      }

      case propositionParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(87);
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
    setState(90);
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
    setState(92);
    match(propositionParser::LT);
    setState(93);
    variable();
    setState(94);
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
    setState(104);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::NEG: {
        setState(97);
        match(propositionParser::NEG);
        setState(98);
        logic(10);
        break;
      }

      case propositionParser::NUMERIC:
      case propositionParser::VERILOG_BINARY:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX:
      case propositionParser::LT: {
        setState(99);
        logicAtom();
        break;
      }

      case propositionParser::LPAREN: {
        setState(100);
        match(propositionParser::LPAREN);
        setState(101);
        logic(0);
        setState(102);
        match(propositionParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(129);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(127);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(106);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(107);
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
          setState(108);
          logic(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(109);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(110);
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
          setState(111);
          logic(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(112);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(113);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(propositionParser::LSHIFT);
          setState(114);
          logic(8);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(115);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(116);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(propositionParser::RSHIFT);
          setState(117);
          logic(7);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(118);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(119);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(propositionParser::BAND);
          setState(120);
          logic(6);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(121);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(122);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(propositionParser::BXOR);
          setState(123);
          logic(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(124);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(125);
          dynamic_cast<LogicContext *>(_localctx)->logop = match(propositionParser::BOR);
          setState(126);
          logic(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(131);
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
  enterRule(_localctx, 12, propositionParser::RuleLogicAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(134);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::NUMERIC:
      case propositionParser::VERILOG_BINARY:
      case propositionParser::GCC_BINARY:
      case propositionParser::HEX: {
        enterOuterAlt(_localctx, 1);
        setState(132);
        logicConstant();
        break;
      }

      case propositionParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(133);
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
  enterRule(_localctx, 14, propositionParser::RuleLogicConstant);
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
  enterRule(_localctx, 16, propositionParser::RuleLogicVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    match(propositionParser::LT);
    setState(139);
    variable();
    setState(140);
    match(propositionParser::T__1);
    setState(141);
    match(propositionParser::SIGN);
    setState(142);
    match(propositionParser::T__2);
    setState(143);
    match(propositionParser::NUMERIC);
    setState(144);
    match(propositionParser::T__3);
   
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
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, propositionParser::RuleNumeric, precedence);

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
    setState(153);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(147);
      numericAtom();
      break;
    }

    case 2: {
      setState(148);
      logic(0);
      break;
    }

    case 3: {
      setState(149);
      match(propositionParser::LPAREN);
      setState(150);
      numeric(0);
      setState(151);
      match(propositionParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(163);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(161);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(155);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(156);
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
          setState(157);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(158);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(159);
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
          setState(160);
          numeric(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(165);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
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
  enterRule(_localctx, 20, propositionParser::RuleNumericAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(168);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case propositionParser::NUMERIC: {
        enterOuterAlt(_localctx, 1);
        setState(166);
        numericConstant();
        break;
      }

      case propositionParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(167);
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
  enterRule(_localctx, 22, propositionParser::RuleNumericConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
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
  enterRule(_localctx, 24, propositionParser::RuleNumericVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(172);
    match(propositionParser::LT);
    setState(173);
    variable();
    setState(174);
    match(propositionParser::T__4);
    setState(175);
    match(propositionParser::NUMERIC);
    setState(176);
    match(propositionParser::T__3);
   
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
  enterRule(_localctx, 26, propositionParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(178);
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
  enterRule(_localctx, 28, propositionParser::RuleRelop);
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
    setState(180);
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
    case 9: return numericSempred(dynamic_cast<NumericContext *>(context), predicateIndex);

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

  default:
    break;
  }
  return true;
}

bool propositionParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 11: return precpred(_ctx, 5);
    case 12: return precpred(_ctx, 4);

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
  "logic", "logicAtom", "logicConstant", "logicVariable", "numeric", "numericAtom", 
  "numericConstant", "numericVariable", "variable", "relop"
};

std::vector<std::string> propositionParser::_literalNames = {
  "", "',bool>'", "',logic('", "','", "')>'", "',numeric('", "", "'{'", 
  "'}'", "'['", "']'", "'('", "')'", "", "", "", "", "", "", "", "'+'", 
  "'-'", "'*'", "'/'", "'>'", "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", 
  "'|'", "'^'", "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'"
};

std::vector<std::string> propositionParser::_symbolicNames = {
  "", "", "", "", "", "", "SIGN", "LGPAREN", "RGPAREN", "LCPAREN", "RCPAREN", 
  "LPAREN", "RPAREN", "VARIABLE", "INDEX", "NUMERIC", "VERILOG_BINARY", 
  "GCC_BINARY", "HEX", "BOOLEAN", "PLUS", "MINUS", "TIMES", "DIV", "GT", 
  "GE", "LT", "LE", "EQ", "NEQ", "BAND", "BOR", "BXOR", "NEG", "LSHIFT", 
  "RSHIFT", "AND", "OR", "NOT", "WS"
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
       0x3, 0x29, 0xb9, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x3, 0x2, 
       0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x46, 0xa, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x54, 
       0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x57, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 
       0x5, 0x4, 0x5b, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 
       0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x6b, 0xa, 0x7, 0x3, 
       0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x7, 0x7, 0x82, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x85, 0xb, 
       0x7, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x89, 0xa, 0x8, 0x3, 0x9, 0x3, 
       0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
       0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
       0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x9c, 0xa, 0xb, 0x3, 0xb, 0x3, 
       0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0xa4, 0xa, 
       0xb, 0xc, 0xb, 0xe, 0xb, 0xa7, 0xb, 0xb, 0x3, 0xc, 0x3, 0xc, 0x5, 
       0xc, 0xab, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 
       0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 
       0x3, 0x10, 0x3, 0x10, 0x2, 0x5, 0x4, 0xc, 0x14, 0x11, 0x2, 0x4, 0x6, 
       0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 
       0x2, 0x6, 0x3, 0x2, 0x18, 0x19, 0x3, 0x2, 0x16, 0x17, 0x3, 0x2, 0x11, 
       0x14, 0x3, 0x2, 0x1a, 0x1d, 0x2, 0xc7, 0x2, 0x20, 0x3, 0x2, 0x2, 
       0x2, 0x4, 0x45, 0x3, 0x2, 0x2, 0x2, 0x6, 0x5a, 0x3, 0x2, 0x2, 0x2, 
       0x8, 0x5c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x5e, 0x3, 0x2, 0x2, 0x2, 0xc, 
       0x6a, 0x3, 0x2, 0x2, 0x2, 0xe, 0x88, 0x3, 0x2, 0x2, 0x2, 0x10, 0x8a, 
       0x3, 0x2, 0x2, 0x2, 0x12, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x14, 0x9b, 0x3, 
       0x2, 0x2, 0x2, 0x16, 0xaa, 0x3, 0x2, 0x2, 0x2, 0x18, 0xac, 0x3, 0x2, 
       0x2, 0x2, 0x1a, 0xae, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xb4, 0x3, 0x2, 0x2, 
       0x2, 0x1e, 0xb6, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x5, 0x4, 0x3, 0x2, 
       0x21, 0x22, 0x7, 0x2, 0x2, 0x3, 0x22, 0x3, 0x3, 0x2, 0x2, 0x2, 0x23, 
       0x24, 0x8, 0x3, 0x1, 0x2, 0x24, 0x25, 0x7, 0x28, 0x2, 0x2, 0x25, 
       0x46, 0x5, 0x4, 0x3, 0x11, 0x26, 0x27, 0x5, 0xc, 0x7, 0x2, 0x27, 
       0x28, 0x5, 0x1e, 0x10, 0x2, 0x28, 0x29, 0x5, 0xc, 0x7, 0x2, 0x29, 
       0x46, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0x5, 0x14, 0xb, 0x2, 0x2b, 
       0x2c, 0x5, 0x1e, 0x10, 0x2, 0x2c, 0x2d, 0x5, 0x14, 0xb, 0x2, 0x2d, 
       0x46, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x5, 0xc, 0x7, 0x2, 0x2f, 0x30, 
       0x7, 0x1e, 0x2, 0x2, 0x30, 0x31, 0x5, 0xc, 0x7, 0x2, 0x31, 0x46, 
       0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x5, 0x14, 0xb, 0x2, 0x33, 0x34, 
       0x7, 0x1e, 0x2, 0x2, 0x34, 0x35, 0x5, 0x14, 0xb, 0x2, 0x35, 0x46, 
       0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x5, 0xc, 0x7, 0x2, 0x37, 0x38, 0x7, 
       0x1f, 0x2, 0x2, 0x38, 0x39, 0x5, 0xc, 0x7, 0x2, 0x39, 0x46, 0x3, 
       0x2, 0x2, 0x2, 0x3a, 0x3b, 0x5, 0x14, 0xb, 0x2, 0x3b, 0x3c, 0x7, 
       0x1f, 0x2, 0x2, 0x3c, 0x3d, 0x5, 0x14, 0xb, 0x2, 0x3d, 0x46, 0x3, 
       0x2, 0x2, 0x2, 0x3e, 0x46, 0x5, 0x6, 0x4, 0x2, 0x3f, 0x46, 0x5, 0xc, 
       0x7, 0x2, 0x40, 0x46, 0x5, 0x14, 0xb, 0x2, 0x41, 0x42, 0x7, 0xd, 
       0x2, 0x2, 0x42, 0x43, 0x5, 0x4, 0x3, 0x2, 0x43, 0x44, 0x7, 0xe, 0x2, 
       0x2, 0x44, 0x46, 0x3, 0x2, 0x2, 0x2, 0x45, 0x23, 0x3, 0x2, 0x2, 0x2, 
       0x45, 0x26, 0x3, 0x2, 0x2, 0x2, 0x45, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x45, 
       0x2e, 0x3, 0x2, 0x2, 0x2, 0x45, 0x32, 0x3, 0x2, 0x2, 0x2, 0x45, 0x36, 
       0x3, 0x2, 0x2, 0x2, 0x45, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x45, 0x3e, 0x3, 
       0x2, 0x2, 0x2, 0x45, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x45, 0x40, 0x3, 0x2, 
       0x2, 0x2, 0x45, 0x41, 0x3, 0x2, 0x2, 0x2, 0x46, 0x55, 0x3, 0x2, 0x2, 
       0x2, 0x47, 0x48, 0xc, 0xc, 0x2, 0x2, 0x48, 0x49, 0x7, 0x1e, 0x2, 
       0x2, 0x49, 0x54, 0x5, 0x4, 0x3, 0xd, 0x4a, 0x4b, 0xc, 0x9, 0x2, 0x2, 
       0x4b, 0x4c, 0x7, 0x1f, 0x2, 0x2, 0x4c, 0x54, 0x5, 0x4, 0x3, 0xa, 
       0x4d, 0x4e, 0xc, 0x8, 0x2, 0x2, 0x4e, 0x4f, 0x7, 0x26, 0x2, 0x2, 
       0x4f, 0x54, 0x5, 0x4, 0x3, 0x9, 0x50, 0x51, 0xc, 0x7, 0x2, 0x2, 0x51, 
       0x52, 0x7, 0x27, 0x2, 0x2, 0x52, 0x54, 0x5, 0x4, 0x3, 0x8, 0x53, 
       0x47, 0x3, 0x2, 0x2, 0x2, 0x53, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x53, 0x4d, 
       0x3, 0x2, 0x2, 0x2, 0x53, 0x50, 0x3, 0x2, 0x2, 0x2, 0x54, 0x57, 0x3, 
       0x2, 0x2, 0x2, 0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x3, 0x2, 
       0x2, 0x2, 0x56, 0x5, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 0x3, 0x2, 0x2, 
       0x2, 0x58, 0x5b, 0x5, 0x8, 0x5, 0x2, 0x59, 0x5b, 0x5, 0xa, 0x6, 0x2, 
       0x5a, 0x58, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5b, 
       0x7, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x7, 0x15, 0x2, 0x2, 0x5d, 0x9, 
       0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x7, 0x1c, 0x2, 0x2, 0x5f, 0x60, 
       0x5, 0x1c, 0xf, 0x2, 0x60, 0x61, 0x7, 0x3, 0x2, 0x2, 0x61, 0xb, 0x3, 
       0x2, 0x2, 0x2, 0x62, 0x63, 0x8, 0x7, 0x1, 0x2, 0x63, 0x64, 0x7, 0x23, 
       0x2, 0x2, 0x64, 0x6b, 0x5, 0xc, 0x7, 0xc, 0x65, 0x6b, 0x5, 0xe, 0x8, 
       0x2, 0x66, 0x67, 0x7, 0xd, 0x2, 0x2, 0x67, 0x68, 0x5, 0xc, 0x7, 0x2, 
       0x68, 0x69, 0x7, 0xe, 0x2, 0x2, 0x69, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6a, 
       0x62, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x65, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x66, 
       0x3, 0x2, 0x2, 0x2, 0x6b, 0x83, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0xc, 
       0xb, 0x2, 0x2, 0x6d, 0x6e, 0x9, 0x2, 0x2, 0x2, 0x6e, 0x82, 0x5, 0xc, 
       0x7, 0xc, 0x6f, 0x70, 0xc, 0xa, 0x2, 0x2, 0x70, 0x71, 0x9, 0x3, 0x2, 
       0x2, 0x71, 0x82, 0x5, 0xc, 0x7, 0xb, 0x72, 0x73, 0xc, 0x9, 0x2, 0x2, 
       0x73, 0x74, 0x7, 0x24, 0x2, 0x2, 0x74, 0x82, 0x5, 0xc, 0x7, 0xa, 
       0x75, 0x76, 0xc, 0x8, 0x2, 0x2, 0x76, 0x77, 0x7, 0x25, 0x2, 0x2, 
       0x77, 0x82, 0x5, 0xc, 0x7, 0x9, 0x78, 0x79, 0xc, 0x7, 0x2, 0x2, 0x79, 
       0x7a, 0x7, 0x20, 0x2, 0x2, 0x7a, 0x82, 0x5, 0xc, 0x7, 0x8, 0x7b, 
       0x7c, 0xc, 0x6, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0x22, 0x2, 0x2, 0x7d, 
       0x82, 0x5, 0xc, 0x7, 0x7, 0x7e, 0x7f, 0xc, 0x5, 0x2, 0x2, 0x7f, 0x80, 
       0x7, 0x21, 0x2, 0x2, 0x80, 0x82, 0x5, 0xc, 0x7, 0x6, 0x81, 0x6c, 
       0x3, 0x2, 0x2, 0x2, 0x81, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x81, 0x72, 0x3, 
       0x2, 0x2, 0x2, 0x81, 0x75, 0x3, 0x2, 0x2, 0x2, 0x81, 0x78, 0x3, 0x2, 
       0x2, 0x2, 0x81, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x81, 0x7e, 0x3, 0x2, 0x2, 
       0x2, 0x82, 0x85, 0x3, 0x2, 0x2, 0x2, 0x83, 0x81, 0x3, 0x2, 0x2, 0x2, 
       0x83, 0x84, 0x3, 0x2, 0x2, 0x2, 0x84, 0xd, 0x3, 0x2, 0x2, 0x2, 0x85, 
       0x83, 0x3, 0x2, 0x2, 0x2, 0x86, 0x89, 0x5, 0x10, 0x9, 0x2, 0x87, 
       0x89, 0x5, 0x12, 0xa, 0x2, 0x88, 0x86, 0x3, 0x2, 0x2, 0x2, 0x88, 
       0x87, 0x3, 0x2, 0x2, 0x2, 0x89, 0xf, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8b, 
       0x9, 0x4, 0x2, 0x2, 0x8b, 0x11, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x7, 
       0x1c, 0x2, 0x2, 0x8d, 0x8e, 0x5, 0x1c, 0xf, 0x2, 0x8e, 0x8f, 0x7, 
       0x4, 0x2, 0x2, 0x8f, 0x90, 0x7, 0x8, 0x2, 0x2, 0x90, 0x91, 0x7, 0x5, 
       0x2, 0x2, 0x91, 0x92, 0x7, 0x11, 0x2, 0x2, 0x92, 0x93, 0x7, 0x6, 
       0x2, 0x2, 0x93, 0x13, 0x3, 0x2, 0x2, 0x2, 0x94, 0x95, 0x8, 0xb, 0x1, 
       0x2, 0x95, 0x9c, 0x5, 0x16, 0xc, 0x2, 0x96, 0x9c, 0x5, 0xc, 0x7, 
       0x2, 0x97, 0x98, 0x7, 0xd, 0x2, 0x2, 0x98, 0x99, 0x5, 0x14, 0xb, 
       0x2, 0x99, 0x9a, 0x7, 0xe, 0x2, 0x2, 0x9a, 0x9c, 0x3, 0x2, 0x2, 0x2, 
       0x9b, 0x94, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x96, 0x3, 0x2, 0x2, 0x2, 0x9b, 
       0x97, 0x3, 0x2, 0x2, 0x2, 0x9c, 0xa5, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 
       0xc, 0x7, 0x2, 0x2, 0x9e, 0x9f, 0x9, 0x2, 0x2, 0x2, 0x9f, 0xa4, 0x5, 
       0x14, 0xb, 0x8, 0xa0, 0xa1, 0xc, 0x6, 0x2, 0x2, 0xa1, 0xa2, 0x9, 
       0x3, 0x2, 0x2, 0xa2, 0xa4, 0x5, 0x14, 0xb, 0x7, 0xa3, 0x9d, 0x3, 
       0x2, 0x2, 0x2, 0xa3, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa7, 0x3, 0x2, 
       0x2, 0x2, 0xa5, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa6, 0x3, 0x2, 0x2, 
       0x2, 0xa6, 0x15, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa5, 0x3, 0x2, 0x2, 0x2, 
       0xa8, 0xab, 0x5, 0x18, 0xd, 0x2, 0xa9, 0xab, 0x5, 0x1a, 0xe, 0x2, 
       0xaa, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xab, 
       0x17, 0x3, 0x2, 0x2, 0x2, 0xac, 0xad, 0x7, 0x11, 0x2, 0x2, 0xad, 
       0x19, 0x3, 0x2, 0x2, 0x2, 0xae, 0xaf, 0x7, 0x1c, 0x2, 0x2, 0xaf, 
       0xb0, 0x5, 0x1c, 0xf, 0x2, 0xb0, 0xb1, 0x7, 0x7, 0x2, 0x2, 0xb1, 
       0xb2, 0x7, 0x11, 0x2, 0x2, 0xb2, 0xb3, 0x7, 0x6, 0x2, 0x2, 0xb3, 
       0x1b, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xb5, 0x7, 0xf, 0x2, 0x2, 0xb5, 0x1d, 
       0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x9, 0x5, 0x2, 0x2, 0xb7, 0x1f, 0x3, 
       0x2, 0x2, 0x2, 0xe, 0x45, 0x53, 0x55, 0x5a, 0x6a, 0x81, 0x83, 0x88, 
       0x9b, 0xa3, 0xa5, 0xaa, 
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
