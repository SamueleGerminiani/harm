
// Generated from varDeclaration.g4 by ANTLR 4.10.1


#include "varDeclarationListener.h"

#include "varDeclarationParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct VarDeclarationParserStaticData final {
  VarDeclarationParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  VarDeclarationParserStaticData(const VarDeclarationParserStaticData&) = delete;
  VarDeclarationParserStaticData(VarDeclarationParserStaticData&&) = delete;
  VarDeclarationParserStaticData& operator=(const VarDeclarationParserStaticData&) = delete;
  VarDeclarationParserStaticData& operator=(VarDeclarationParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag vardeclarationParserOnceFlag;
VarDeclarationParserStaticData *vardeclarationParserStaticData = nullptr;

void vardeclarationParserInitialize() {
  assert(vardeclarationParserStaticData == nullptr);
  auto staticData = std::make_unique<VarDeclarationParserStaticData>(
    std::vector<std::string>{
      "file", "varDec", "name", "vartype"
    },
    std::vector<std::string>{
      "", "'['", "':'", "']'"
    },
    std::vector<std::string>{
      "", "", "", "", "VARTYPE", "NAME", "NUMERIC", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,7,26,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,1,0,1,0,1,0,1,1,1,1,1,1,1,1,
  	1,1,1,1,3,1,18,8,1,1,1,1,1,1,2,1,2,1,3,1,3,1,3,0,0,4,0,2,4,6,0,0,22,0,
  	8,1,0,0,0,2,11,1,0,0,0,4,21,1,0,0,0,6,23,1,0,0,0,8,9,3,2,1,0,9,10,5,0,
  	0,1,10,1,1,0,0,0,11,17,3,6,3,0,12,13,5,1,0,0,13,14,5,6,0,0,14,15,5,2,
  	0,0,15,16,5,6,0,0,16,18,5,3,0,0,17,12,1,0,0,0,17,18,1,0,0,0,18,19,1,0,
  	0,0,19,20,3,4,2,0,20,3,1,0,0,0,21,22,5,5,0,0,22,5,1,0,0,0,23,24,5,4,0,
  	0,24,7,1,0,0,0,1,17
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  vardeclarationParserStaticData = staticData.release();
}

}

varDeclarationParser::varDeclarationParser(TokenStream *input) : varDeclarationParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

varDeclarationParser::varDeclarationParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  varDeclarationParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *vardeclarationParserStaticData->atn, vardeclarationParserStaticData->decisionToDFA, vardeclarationParserStaticData->sharedContextCache, options);
}

varDeclarationParser::~varDeclarationParser() {
  delete _interpreter;
}

const atn::ATN& varDeclarationParser::getATN() const {
  return *vardeclarationParserStaticData->atn;
}

std::string varDeclarationParser::getGrammarFileName() const {
  return "varDeclaration.g4";
}

const std::vector<std::string>& varDeclarationParser::getRuleNames() const {
  return vardeclarationParserStaticData->ruleNames;
}

const dfa::Vocabulary& varDeclarationParser::getVocabulary() const {
  return vardeclarationParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView varDeclarationParser::getSerializedATN() const {
  return vardeclarationParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

varDeclarationParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::VarDecContext* varDeclarationParser::FileContext::varDec() {
  return getRuleContext<varDeclarationParser::VarDecContext>(0);
}

tree::TerminalNode* varDeclarationParser::FileContext::EOF() {
  return getToken(varDeclarationParser::EOF, 0);
}


size_t varDeclarationParser::FileContext::getRuleIndex() const {
  return varDeclarationParser::RuleFile;
}

void varDeclarationParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void varDeclarationParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

varDeclarationParser::FileContext* varDeclarationParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, varDeclarationParser::RuleFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(8);
    varDec();
    setState(9);
    match(varDeclarationParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDecContext ------------------------------------------------------------------

varDeclarationParser::VarDecContext::VarDecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::VartypeContext* varDeclarationParser::VarDecContext::vartype() {
  return getRuleContext<varDeclarationParser::VartypeContext>(0);
}

varDeclarationParser::NameContext* varDeclarationParser::VarDecContext::name() {
  return getRuleContext<varDeclarationParser::NameContext>(0);
}

std::vector<tree::TerminalNode *> varDeclarationParser::VarDecContext::NUMERIC() {
  return getTokens(varDeclarationParser::NUMERIC);
}

tree::TerminalNode* varDeclarationParser::VarDecContext::NUMERIC(size_t i) {
  return getToken(varDeclarationParser::NUMERIC, i);
}


size_t varDeclarationParser::VarDecContext::getRuleIndex() const {
  return varDeclarationParser::RuleVarDec;
}

void varDeclarationParser::VarDecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDec(this);
}

void varDeclarationParser::VarDecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDec(this);
}

varDeclarationParser::VarDecContext* varDeclarationParser::varDec() {
  VarDecContext *_localctx = _tracker.createInstance<VarDecContext>(_ctx, getState());
  enterRule(_localctx, 2, varDeclarationParser::RuleVarDec);
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
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameContext ------------------------------------------------------------------

varDeclarationParser::NameContext::NameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::NameContext::NAME() {
  return getToken(varDeclarationParser::NAME, 0);
}


size_t varDeclarationParser::NameContext::getRuleIndex() const {
  return varDeclarationParser::RuleName;
}

void varDeclarationParser::NameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterName(this);
}

void varDeclarationParser::NameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitName(this);
}

varDeclarationParser::NameContext* varDeclarationParser::name() {
  NameContext *_localctx = _tracker.createInstance<NameContext>(_ctx, getState());
  enterRule(_localctx, 4, varDeclarationParser::RuleName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(21);
    match(varDeclarationParser::NAME);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VartypeContext ------------------------------------------------------------------

varDeclarationParser::VartypeContext::VartypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::VartypeContext::VARTYPE() {
  return getToken(varDeclarationParser::VARTYPE, 0);
}


size_t varDeclarationParser::VartypeContext::getRuleIndex() const {
  return varDeclarationParser::RuleVartype;
}

void varDeclarationParser::VartypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVartype(this);
}

void varDeclarationParser::VartypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVartype(this);
}

varDeclarationParser::VartypeContext* varDeclarationParser::vartype() {
  VartypeContext *_localctx = _tracker.createInstance<VartypeContext>(_ctx, getState());
  enterRule(_localctx, 6, varDeclarationParser::RuleVartype);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(23);
    match(varDeclarationParser::VARTYPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void varDeclarationParser::initialize() {
  std::call_once(vardeclarationParserOnceFlag, vardeclarationParserInitialize);
}
