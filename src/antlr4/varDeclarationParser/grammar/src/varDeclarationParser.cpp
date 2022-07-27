
// Generated from varDeclaration.g4 by ANTLR 4.7.2

#include "varDeclarationListener.h"

#include "varDeclarationParser.h"

using namespace antlrcpp;
using namespace antlr4;

varDeclarationParser::varDeclarationParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA,
                                             _sharedContextCache);
}

varDeclarationParser::~varDeclarationParser() { delete _interpreter; }

std::string varDeclarationParser::getGrammarFileName() const {
  return "varDeclaration.g4";
}

const std::vector<std::string> &varDeclarationParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary &varDeclarationParser::getVocabulary() const {
  return _vocabulary;
}

//----------------- FileContext ------------------------------------------------------------------

varDeclarationParser::FileContext::FileContext(ParserRuleContext *parent,
                                               size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

varDeclarationParser::VarDecContext *
varDeclarationParser::FileContext::varDec() {
  return getRuleContext<varDeclarationParser::VarDecContext>(0);
}

tree::TerminalNode *varDeclarationParser::FileContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
}

size_t varDeclarationParser::FileContext::getRuleIndex() const {
  return varDeclarationParser::RuleFile;
}

void varDeclarationParser::FileContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void varDeclarationParser::FileContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

varDeclarationParser::FileContext *varDeclarationParser::file() {
  FileContext *_localctx =
      _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, varDeclarationParser::RuleFile);

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(8);
    varDec();
    setState(9);
    match(varDeclarationParser::EOF);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDecContext ------------------------------------------------------------------

varDeclarationParser::VarDecContext::VarDecContext(ParserRuleContext *parent,
                                                   size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

varDeclarationParser::VartypeContext *
varDeclarationParser::VarDecContext::vartype() {
  return getRuleContext<varDeclarationParser::VartypeContext>(0);
}

varDeclarationParser::NameContext *varDeclarationParser::VarDecContext::name() {
  return getRuleContext<varDeclarationParser::NameContext>(0);
}

std::vector<tree::TerminalNode *>
varDeclarationParser::VarDecContext::NUMERIC() {
  return getTokens(varDeclarationParser::NUMERIC);
}

tree::TerminalNode *varDeclarationParser::VarDecContext::NUMERIC(size_t i) {
  return getToken(varDeclarationParser::NUMERIC, i);
}

size_t varDeclarationParser::VarDecContext::getRuleIndex() const {
  return varDeclarationParser::RuleVarDec;
}

void varDeclarationParser::VarDecContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDec(this);
}

void varDeclarationParser::VarDecContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDec(this);
}

varDeclarationParser::VarDecContext *varDeclarationParser::varDec() {
  VarDecContext *_localctx =
      _tracker.createInstance<VarDecContext>(_ctx, getState());
  enterRule(_localctx, 2, varDeclarationParser::RuleVarDec);
  size_t _la = 0;

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(11);
    vartype();
    setState(17);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::T__0) {
      setState(12);
      match(varDeclarationParser::T__0);
      setState(13);
      match(varDeclarationParser::NUMERIC);
      setState(14);
      match(varDeclarationParser::T__1);
      setState(15);
      match(varDeclarationParser::NUMERIC);
      setState(16);
      match(varDeclarationParser::T__2);
    }
    setState(19);
    name();

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameContext ------------------------------------------------------------------

varDeclarationParser::NameContext::NameContext(ParserRuleContext *parent,
                                               size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *varDeclarationParser::NameContext::NAME() {
  return getToken(varDeclarationParser::NAME, 0);
}

size_t varDeclarationParser::NameContext::getRuleIndex() const {
  return varDeclarationParser::RuleName;
}

void varDeclarationParser::NameContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterName(this);
}

void varDeclarationParser::NameContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitName(this);
}

varDeclarationParser::NameContext *varDeclarationParser::name() {
  NameContext *_localctx =
      _tracker.createInstance<NameContext>(_ctx, getState());
  enterRule(_localctx, 4, varDeclarationParser::RuleName);

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(21);
    match(varDeclarationParser::NAME);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VartypeContext ------------------------------------------------------------------

varDeclarationParser::VartypeContext::VartypeContext(ParserRuleContext *parent,
                                                     size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *varDeclarationParser::VartypeContext::VARTYPE() {
  return getToken(varDeclarationParser::VARTYPE, 0);
}

size_t varDeclarationParser::VartypeContext::getRuleIndex() const {
  return varDeclarationParser::RuleVartype;
}

void varDeclarationParser::VartypeContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVartype(this);
}

void varDeclarationParser::VartypeContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVartype(this);
}

varDeclarationParser::VartypeContext *varDeclarationParser::vartype() {
  VartypeContext *_localctx =
      _tracker.createInstance<VartypeContext>(_ctx, getState());
  enterRule(_localctx, 6, varDeclarationParser::RuleVartype);

  auto onExit = finally([=] { exitRule(); });
  try {
    enterOuterAlt(_localctx, 1);
    setState(23);
    match(varDeclarationParser::VARTYPE);

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> varDeclarationParser::_decisionToDFA;
atn::PredictionContextCache varDeclarationParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN varDeclarationParser::_atn;
std::vector<uint16_t> varDeclarationParser::_serializedATN;

std::vector<std::string> varDeclarationParser::_ruleNames = {"file", "varDec",
                                                             "name", "vartype"};

std::vector<std::string> varDeclarationParser::_literalNames = {"", "'['",
                                                                "':'", "']'"};

std::vector<std::string> varDeclarationParser::_symbolicNames = {
    "", "", "", "", "VARTYPE", "NAME", "NUMERIC", "WS"};

dfa::Vocabulary varDeclarationParser::_vocabulary(_literalNames,
                                                  _symbolicNames);

std::vector<std::string> varDeclarationParser::_tokenNames;

varDeclarationParser::Initializer::Initializer() {
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

  _serializedATN = {
      0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964,
      0x3, 0x9,    0x1c,   0x4,    0x2,    0x9,    0x2,    0x4,    0x3,
      0x9, 0x3,    0x4,    0x4,    0x9,    0x4,    0x4,    0x5,    0x9,
      0x5, 0x3,    0x2,    0x3,    0x2,    0x3,    0x2,    0x3,    0x3,
      0x3, 0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,    0x3,
      0x3, 0x5,    0x3,    0x14,   0xa,    0x3,    0x3,    0x3,    0x3,
      0x3, 0x3,    0x4,    0x3,    0x4,    0x3,    0x5,    0x3,    0x5,
      0x3, 0x5,    0x2,    0x2,    0x6,    0x2,    0x4,    0x6,    0x8,
      0x2, 0x2,    0x2,    0x18,   0x2,    0xa,    0x3,    0x2,    0x2,
      0x2, 0x4,    0xd,    0x3,    0x2,    0x2,    0x2,    0x6,    0x17,
      0x3, 0x2,    0x2,    0x2,    0x8,    0x19,   0x3,    0x2,    0x2,
      0x2, 0xa,    0xb,    0x5,    0x4,    0x3,    0x2,    0xb,    0xc,
      0x7, 0x2,    0x2,    0x3,    0xc,    0x3,    0x3,    0x2,    0x2,
      0x2, 0xd,    0x13,   0x5,    0x8,    0x5,    0x2,    0xe,    0xf,
      0x7, 0x3,    0x2,    0x2,    0xf,    0x10,   0x7,    0x8,    0x2,
      0x2, 0x10,   0x11,   0x7,    0x4,    0x2,    0x2,    0x11,   0x12,
      0x7, 0x8,    0x2,    0x2,    0x12,   0x14,   0x7,    0x5,    0x2,
      0x2, 0x13,   0xe,    0x3,    0x2,    0x2,    0x2,    0x13,   0x14,
      0x3, 0x2,    0x2,    0x2,    0x14,   0x15,   0x3,    0x2,    0x2,
      0x2, 0x15,   0x16,   0x5,    0x6,    0x4,    0x2,    0x16,   0x5,
      0x3, 0x2,    0x2,    0x2,    0x17,   0x18,   0x7,    0x7,    0x2,
      0x2, 0x18,   0x7,    0x3,    0x2,    0x2,    0x2,    0x19,   0x1a,
      0x7, 0x6,    0x2,    0x2,    0x1a,   0x9,    0x3,    0x2,    0x2,
      0x2, 0x3,    0x13,
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) {
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

varDeclarationParser::Initializer varDeclarationParser::_init;
