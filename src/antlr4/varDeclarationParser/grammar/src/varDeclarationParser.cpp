
// Generated from varDeclaration.g4 by ANTLR 4.12.0


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

::antlr4::internal::OnceFlag vardeclarationParserOnceFlag;
VarDeclarationParserStaticData *vardeclarationParserStaticData = nullptr;

void vardeclarationParserInitialize() {
  assert(vardeclarationParserStaticData == nullptr);
  auto staticData = std::make_unique<VarDeclarationParserStaticData>(
    std::vector<std::string>{
      "file", "varDec", "boolean", "booleanAtom", "logic", "bitSelect", 
      "logicAtom", "numeric", "numericAtom", "relop"
    },
    std::vector<std::string>{
      "", "':'", "", "", "", "", "", "", "", "", "", "", "", "'{'", "'}'", 
      "'['", "']'", "'('", "')'", "", "", "", "", "'+'", "'-'", "'*'", "'/'", 
      "'>'", "'>='", "'<'", "'<='", "'=='", "'!='", "'&'", "'|'", "'^'", 
      "'~'", "'<<'", "'>>'", "'&&'", "'||'", "'!'"
    },
    std::vector<std::string>{
      "", "", "Name", "VARTYPE", "WS", "BOOLEAN_CONSTANT", "BOOLEAN_VARIABLE", 
      "LOGIC_CONSTANT", "LOGIC_VARIABLE", "SIGN", "CONST_SUFFIX", "NUMERIC_CONSTANT", 
      "NUMERIC_VARIABLE", "LGPAREN", "RGPAREN", "LCPAREN", "RCPAREN", "LPAREN", 
      "RPAREN", "NUMERIC", "VERILOG_BINARY", "GCC_BINARY", "HEX", "PLUS", 
      "MINUS", "TIMES", "DIV", "GT", "GE", "LT", "LE", "EQ", "NEQ", "BAND", 
      "BOR", "BXOR", "NEG", "LSHIFT", "RSHIFT", "AND", "OR", "NOT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,41,161,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,3,1,30,8,1,
  	1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,3,2,68,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,5,2,82,
  	8,2,10,2,12,2,85,9,2,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,97,8,
  	4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,4,1,4,1,4,1,4,1,4,1,4,5,4,122,8,4,10,4,12,4,125,9,4,1,5,1,5,1,5,1,5,
  	3,5,131,8,5,1,5,1,5,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,144,8,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,5,7,152,8,7,10,7,12,7,155,9,7,1,8,1,8,1,9,1,9,1,
  	9,0,3,4,8,14,10,0,2,4,6,8,10,12,14,16,18,0,6,1,0,5,6,1,0,25,26,1,0,23,
  	24,1,0,7,8,1,0,11,12,1,0,27,30,180,0,20,1,0,0,0,2,23,1,0,0,0,4,67,1,0,
  	0,0,6,86,1,0,0,0,8,96,1,0,0,0,10,126,1,0,0,0,12,134,1,0,0,0,14,143,1,
  	0,0,0,16,156,1,0,0,0,18,158,1,0,0,0,20,21,3,2,1,0,21,22,5,0,0,1,22,1,
  	1,0,0,0,23,29,5,3,0,0,24,25,5,15,0,0,25,26,5,7,0,0,26,27,5,1,0,0,27,28,
  	5,7,0,0,28,30,5,16,0,0,29,24,1,0,0,0,29,30,1,0,0,0,30,31,1,0,0,0,31,32,
  	5,2,0,0,32,3,1,0,0,0,33,34,6,2,-1,0,34,35,5,41,0,0,35,68,3,4,2,15,36,
  	37,3,8,4,0,37,38,3,18,9,0,38,39,3,8,4,0,39,68,1,0,0,0,40,41,3,14,7,0,
  	41,42,3,18,9,0,42,43,3,14,7,0,43,68,1,0,0,0,44,45,3,8,4,0,45,46,5,31,
  	0,0,46,47,3,8,4,0,47,68,1,0,0,0,48,49,3,14,7,0,49,50,5,31,0,0,50,51,3,
  	14,7,0,51,68,1,0,0,0,52,53,3,8,4,0,53,54,5,32,0,0,54,55,3,8,4,0,55,68,
  	1,0,0,0,56,57,3,14,7,0,57,58,5,32,0,0,58,59,3,14,7,0,59,68,1,0,0,0,60,
  	68,3,6,3,0,61,68,3,8,4,0,62,68,3,14,7,0,63,64,5,17,0,0,64,65,3,4,2,0,
  	65,66,5,18,0,0,66,68,1,0,0,0,67,33,1,0,0,0,67,36,1,0,0,0,67,40,1,0,0,
  	0,67,44,1,0,0,0,67,48,1,0,0,0,67,52,1,0,0,0,67,56,1,0,0,0,67,60,1,0,0,
  	0,67,61,1,0,0,0,67,62,1,0,0,0,67,63,1,0,0,0,68,83,1,0,0,0,69,70,10,10,
  	0,0,70,71,5,31,0,0,71,82,3,4,2,11,72,73,10,7,0,0,73,74,5,32,0,0,74,82,
  	3,4,2,8,75,76,10,6,0,0,76,77,5,39,0,0,77,82,3,4,2,7,78,79,10,5,0,0,79,
  	80,5,40,0,0,80,82,3,4,2,6,81,69,1,0,0,0,81,72,1,0,0,0,81,75,1,0,0,0,81,
  	78,1,0,0,0,82,85,1,0,0,0,83,81,1,0,0,0,83,84,1,0,0,0,84,5,1,0,0,0,85,
  	83,1,0,0,0,86,87,7,0,0,0,87,7,1,0,0,0,88,89,6,4,-1,0,89,90,5,36,0,0,90,
  	97,3,8,4,11,91,97,3,12,6,0,92,93,5,17,0,0,93,94,3,8,4,0,94,95,5,18,0,
  	0,95,97,1,0,0,0,96,88,1,0,0,0,96,91,1,0,0,0,96,92,1,0,0,0,97,123,1,0,
  	0,0,98,99,10,9,0,0,99,100,7,1,0,0,100,122,3,8,4,10,101,102,10,8,0,0,102,
  	103,7,2,0,0,103,122,3,8,4,9,104,105,10,7,0,0,105,106,5,37,0,0,106,122,
  	3,8,4,8,107,108,10,6,0,0,108,109,5,38,0,0,109,122,3,8,4,7,110,111,10,
  	5,0,0,111,112,5,33,0,0,112,122,3,8,4,6,113,114,10,4,0,0,114,115,5,35,
  	0,0,115,122,3,8,4,5,116,117,10,3,0,0,117,118,5,34,0,0,118,122,3,8,4,4,
  	119,120,10,10,0,0,120,122,3,10,5,0,121,98,1,0,0,0,121,101,1,0,0,0,121,
  	104,1,0,0,0,121,107,1,0,0,0,121,110,1,0,0,0,121,113,1,0,0,0,121,116,1,
  	0,0,0,121,119,1,0,0,0,122,125,1,0,0,0,123,121,1,0,0,0,123,124,1,0,0,0,
  	124,9,1,0,0,0,125,123,1,0,0,0,126,127,5,15,0,0,127,130,5,19,0,0,128,129,
  	5,1,0,0,129,131,5,19,0,0,130,128,1,0,0,0,130,131,1,0,0,0,131,132,1,0,
  	0,0,132,133,5,16,0,0,133,11,1,0,0,0,134,135,7,3,0,0,135,13,1,0,0,0,136,
  	137,6,7,-1,0,137,144,3,16,8,0,138,144,3,8,4,0,139,140,5,17,0,0,140,141,
  	3,14,7,0,141,142,5,18,0,0,142,144,1,0,0,0,143,136,1,0,0,0,143,138,1,0,
  	0,0,143,139,1,0,0,0,144,153,1,0,0,0,145,146,10,5,0,0,146,147,7,1,0,0,
  	147,152,3,14,7,6,148,149,10,4,0,0,149,150,7,2,0,0,150,152,3,14,7,5,151,
  	145,1,0,0,0,151,148,1,0,0,0,152,155,1,0,0,0,153,151,1,0,0,0,153,154,1,
  	0,0,0,154,15,1,0,0,0,155,153,1,0,0,0,156,157,7,4,0,0,157,17,1,0,0,0,158,
  	159,7,5,0,0,159,19,1,0,0,0,11,29,67,81,83,96,121,123,130,143,151,153
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
    setState(20);
    varDec();
    setState(21);
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

tree::TerminalNode* varDeclarationParser::VarDecContext::VARTYPE() {
  return getToken(varDeclarationParser::VARTYPE, 0);
}

tree::TerminalNode* varDeclarationParser::VarDecContext::Name() {
  return getToken(varDeclarationParser::Name, 0);
}

tree::TerminalNode* varDeclarationParser::VarDecContext::LCPAREN() {
  return getToken(varDeclarationParser::LCPAREN, 0);
}

std::vector<tree::TerminalNode *> varDeclarationParser::VarDecContext::LOGIC_CONSTANT() {
  return getTokens(varDeclarationParser::LOGIC_CONSTANT);
}

tree::TerminalNode* varDeclarationParser::VarDecContext::LOGIC_CONSTANT(size_t i) {
  return getToken(varDeclarationParser::LOGIC_CONSTANT, i);
}

tree::TerminalNode* varDeclarationParser::VarDecContext::RCPAREN() {
  return getToken(varDeclarationParser::RCPAREN, 0);
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
    setState(23);
    match(varDeclarationParser::VARTYPE);
    setState(29);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::LCPAREN) {
      setState(24);
      match(varDeclarationParser::LCPAREN);
      setState(25);
      match(varDeclarationParser::LOGIC_CONSTANT);
      setState(26);
      match(varDeclarationParser::T__0);
      setState(27);
      match(varDeclarationParser::LOGIC_CONSTANT);
      setState(28);
      match(varDeclarationParser::RCPAREN);
    }
    setState(31);
    match(varDeclarationParser::Name);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

varDeclarationParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::BooleanContext::NOT() {
  return getToken(varDeclarationParser::NOT, 0);
}

std::vector<varDeclarationParser::BooleanContext *> varDeclarationParser::BooleanContext::boolean() {
  return getRuleContexts<varDeclarationParser::BooleanContext>();
}

varDeclarationParser::BooleanContext* varDeclarationParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<varDeclarationParser::BooleanContext>(i);
}

std::vector<varDeclarationParser::LogicContext *> varDeclarationParser::BooleanContext::logic() {
  return getRuleContexts<varDeclarationParser::LogicContext>();
}

varDeclarationParser::LogicContext* varDeclarationParser::BooleanContext::logic(size_t i) {
  return getRuleContext<varDeclarationParser::LogicContext>(i);
}

varDeclarationParser::RelopContext* varDeclarationParser::BooleanContext::relop() {
  return getRuleContext<varDeclarationParser::RelopContext>(0);
}

std::vector<varDeclarationParser::NumericContext *> varDeclarationParser::BooleanContext::numeric() {
  return getRuleContexts<varDeclarationParser::NumericContext>();
}

varDeclarationParser::NumericContext* varDeclarationParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<varDeclarationParser::NumericContext>(i);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::EQ() {
  return getToken(varDeclarationParser::EQ, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::NEQ() {
  return getToken(varDeclarationParser::NEQ, 0);
}

varDeclarationParser::BooleanAtomContext* varDeclarationParser::BooleanContext::booleanAtom() {
  return getRuleContext<varDeclarationParser::BooleanAtomContext>(0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::LPAREN() {
  return getToken(varDeclarationParser::LPAREN, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::RPAREN() {
  return getToken(varDeclarationParser::RPAREN, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::AND() {
  return getToken(varDeclarationParser::AND, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanContext::OR() {
  return getToken(varDeclarationParser::OR, 0);
}


size_t varDeclarationParser::BooleanContext::getRuleIndex() const {
  return varDeclarationParser::RuleBoolean;
}

void varDeclarationParser::BooleanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolean(this);
}

void varDeclarationParser::BooleanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolean(this);
}


varDeclarationParser::BooleanContext* varDeclarationParser::boolean() {
   return boolean(0);
}

varDeclarationParser::BooleanContext* varDeclarationParser::boolean(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  varDeclarationParser::BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, parentState);
  varDeclarationParser::BooleanContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, varDeclarationParser::RuleBoolean, precedence);

    

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(34);
      match(varDeclarationParser::NOT);
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
      match(varDeclarationParser::EQ);
      setState(46);
      logic(0);
      break;
    }

    case 5: {
      setState(48);
      numeric(0);
      setState(49);
      match(varDeclarationParser::EQ);
      setState(50);
      numeric(0);
      break;
    }

    case 6: {
      setState(52);
      logic(0);
      setState(53);
      match(varDeclarationParser::NEQ);
      setState(54);
      logic(0);
      break;
    }

    case 7: {
      setState(56);
      numeric(0);
      setState(57);
      match(varDeclarationParser::NEQ);
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
      match(varDeclarationParser::LPAREN);
      setState(64);
      boolean(0);
      setState(65);
      match(varDeclarationParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(83);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(81);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(69);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(70);
          match(varDeclarationParser::EQ);
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
          match(varDeclarationParser::NEQ);
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
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(varDeclarationParser::AND);
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
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop = match(varDeclarationParser::OR);
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
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
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

varDeclarationParser::BooleanAtomContext::BooleanAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::BooleanAtomContext::BOOLEAN_CONSTANT() {
  return getToken(varDeclarationParser::BOOLEAN_CONSTANT, 0);
}

tree::TerminalNode* varDeclarationParser::BooleanAtomContext::BOOLEAN_VARIABLE() {
  return getToken(varDeclarationParser::BOOLEAN_VARIABLE, 0);
}


size_t varDeclarationParser::BooleanAtomContext::getRuleIndex() const {
  return varDeclarationParser::RuleBooleanAtom;
}

void varDeclarationParser::BooleanAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanAtom(this);
}

void varDeclarationParser::BooleanAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanAtom(this);
}

varDeclarationParser::BooleanAtomContext* varDeclarationParser::booleanAtom() {
  BooleanAtomContext *_localctx = _tracker.createInstance<BooleanAtomContext>(_ctx, getState());
  enterRule(_localctx, 6, varDeclarationParser::RuleBooleanAtom);
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
    setState(86);
    _la = _input->LA(1);
    if (!(_la == varDeclarationParser::BOOLEAN_CONSTANT

    || _la == varDeclarationParser::BOOLEAN_VARIABLE)) {
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

varDeclarationParser::LogicContext::LogicContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::LogicContext::NEG() {
  return getToken(varDeclarationParser::NEG, 0);
}

std::vector<varDeclarationParser::LogicContext *> varDeclarationParser::LogicContext::logic() {
  return getRuleContexts<varDeclarationParser::LogicContext>();
}

varDeclarationParser::LogicContext* varDeclarationParser::LogicContext::logic(size_t i) {
  return getRuleContext<varDeclarationParser::LogicContext>(i);
}

varDeclarationParser::LogicAtomContext* varDeclarationParser::LogicContext::logicAtom() {
  return getRuleContext<varDeclarationParser::LogicAtomContext>(0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::LPAREN() {
  return getToken(varDeclarationParser::LPAREN, 0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::RPAREN() {
  return getToken(varDeclarationParser::RPAREN, 0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::TIMES() {
  return getToken(varDeclarationParser::TIMES, 0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::DIV() {
  return getToken(varDeclarationParser::DIV, 0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::PLUS() {
  return getToken(varDeclarationParser::PLUS, 0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::MINUS() {
  return getToken(varDeclarationParser::MINUS, 0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::LSHIFT() {
  return getToken(varDeclarationParser::LSHIFT, 0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::RSHIFT() {
  return getToken(varDeclarationParser::RSHIFT, 0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::BAND() {
  return getToken(varDeclarationParser::BAND, 0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::BXOR() {
  return getToken(varDeclarationParser::BXOR, 0);
}

tree::TerminalNode* varDeclarationParser::LogicContext::BOR() {
  return getToken(varDeclarationParser::BOR, 0);
}

varDeclarationParser::BitSelectContext* varDeclarationParser::LogicContext::bitSelect() {
  return getRuleContext<varDeclarationParser::BitSelectContext>(0);
}


size_t varDeclarationParser::LogicContext::getRuleIndex() const {
  return varDeclarationParser::RuleLogic;
}

void varDeclarationParser::LogicContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic(this);
}

void varDeclarationParser::LogicContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic(this);
}


varDeclarationParser::LogicContext* varDeclarationParser::logic() {
   return logic(0);
}

varDeclarationParser::LogicContext* varDeclarationParser::logic(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  varDeclarationParser::LogicContext *_localctx = _tracker.createInstance<LogicContext>(_ctx, parentState);
  varDeclarationParser::LogicContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, varDeclarationParser::RuleLogic, precedence);

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
    setState(96);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case varDeclarationParser::NEG: {
        setState(89);
        match(varDeclarationParser::NEG);
        setState(90);
        logic(11);
        break;
      }

      case varDeclarationParser::LOGIC_CONSTANT:
      case varDeclarationParser::LOGIC_VARIABLE: {
        setState(91);
        logicAtom();
        break;
      }

      case varDeclarationParser::LPAREN: {
        setState(92);
        match(varDeclarationParser::LPAREN);
        setState(93);
        logic(0);
        setState(94);
        match(varDeclarationParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(123);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(121);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(98);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(99);
          antlrcpp::downCast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == varDeclarationParser::TIMES

          || _la == varDeclarationParser::DIV)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(100);
          logic(10);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(101);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(102);
          antlrcpp::downCast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == varDeclarationParser::PLUS

          || _la == varDeclarationParser::MINUS)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(103);
          logic(9);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(104);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(105);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(varDeclarationParser::LSHIFT);
          setState(106);
          logic(8);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(107);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(108);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(varDeclarationParser::RSHIFT);
          setState(109);
          logic(7);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(110);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(111);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(varDeclarationParser::BAND);
          setState(112);
          logic(6);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(113);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(114);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(varDeclarationParser::BXOR);
          setState(115);
          logic(5);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(116);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(117);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop = match(varDeclarationParser::BOR);
          setState(118);
          logic(4);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(119);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(120);
          bitSelect();
          break;
        }

        default:
          break;
        } 
      }
      setState(125);
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

varDeclarationParser::BitSelectContext::BitSelectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::BitSelectContext::LCPAREN() {
  return getToken(varDeclarationParser::LCPAREN, 0);
}

std::vector<tree::TerminalNode *> varDeclarationParser::BitSelectContext::NUMERIC() {
  return getTokens(varDeclarationParser::NUMERIC);
}

tree::TerminalNode* varDeclarationParser::BitSelectContext::NUMERIC(size_t i) {
  return getToken(varDeclarationParser::NUMERIC, i);
}

tree::TerminalNode* varDeclarationParser::BitSelectContext::RCPAREN() {
  return getToken(varDeclarationParser::RCPAREN, 0);
}


size_t varDeclarationParser::BitSelectContext::getRuleIndex() const {
  return varDeclarationParser::RuleBitSelect;
}

void varDeclarationParser::BitSelectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitSelect(this);
}

void varDeclarationParser::BitSelectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitSelect(this);
}

varDeclarationParser::BitSelectContext* varDeclarationParser::bitSelect() {
  BitSelectContext *_localctx = _tracker.createInstance<BitSelectContext>(_ctx, getState());
  enterRule(_localctx, 10, varDeclarationParser::RuleBitSelect);
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
    setState(126);
    match(varDeclarationParser::LCPAREN);
    setState(127);
    match(varDeclarationParser::NUMERIC);
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == varDeclarationParser::T__0) {
      setState(128);
      match(varDeclarationParser::T__0);
      setState(129);
      match(varDeclarationParser::NUMERIC);
    }
    setState(132);
    match(varDeclarationParser::RCPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicAtomContext ------------------------------------------------------------------

varDeclarationParser::LogicAtomContext::LogicAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::LogicAtomContext::LOGIC_CONSTANT() {
  return getToken(varDeclarationParser::LOGIC_CONSTANT, 0);
}

tree::TerminalNode* varDeclarationParser::LogicAtomContext::LOGIC_VARIABLE() {
  return getToken(varDeclarationParser::LOGIC_VARIABLE, 0);
}


size_t varDeclarationParser::LogicAtomContext::getRuleIndex() const {
  return varDeclarationParser::RuleLogicAtom;
}

void varDeclarationParser::LogicAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicAtom(this);
}

void varDeclarationParser::LogicAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicAtom(this);
}

varDeclarationParser::LogicAtomContext* varDeclarationParser::logicAtom() {
  LogicAtomContext *_localctx = _tracker.createInstance<LogicAtomContext>(_ctx, getState());
  enterRule(_localctx, 12, varDeclarationParser::RuleLogicAtom);
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
    setState(134);
    _la = _input->LA(1);
    if (!(_la == varDeclarationParser::LOGIC_CONSTANT

    || _la == varDeclarationParser::LOGIC_VARIABLE)) {
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

//----------------- NumericContext ------------------------------------------------------------------

varDeclarationParser::NumericContext::NumericContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

varDeclarationParser::NumericAtomContext* varDeclarationParser::NumericContext::numericAtom() {
  return getRuleContext<varDeclarationParser::NumericAtomContext>(0);
}

varDeclarationParser::LogicContext* varDeclarationParser::NumericContext::logic() {
  return getRuleContext<varDeclarationParser::LogicContext>(0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::LPAREN() {
  return getToken(varDeclarationParser::LPAREN, 0);
}

std::vector<varDeclarationParser::NumericContext *> varDeclarationParser::NumericContext::numeric() {
  return getRuleContexts<varDeclarationParser::NumericContext>();
}

varDeclarationParser::NumericContext* varDeclarationParser::NumericContext::numeric(size_t i) {
  return getRuleContext<varDeclarationParser::NumericContext>(i);
}

tree::TerminalNode* varDeclarationParser::NumericContext::RPAREN() {
  return getToken(varDeclarationParser::RPAREN, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::TIMES() {
  return getToken(varDeclarationParser::TIMES, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::DIV() {
  return getToken(varDeclarationParser::DIV, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::PLUS() {
  return getToken(varDeclarationParser::PLUS, 0);
}

tree::TerminalNode* varDeclarationParser::NumericContext::MINUS() {
  return getToken(varDeclarationParser::MINUS, 0);
}


size_t varDeclarationParser::NumericContext::getRuleIndex() const {
  return varDeclarationParser::RuleNumeric;
}

void varDeclarationParser::NumericContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void varDeclarationParser::NumericContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}


varDeclarationParser::NumericContext* varDeclarationParser::numeric() {
   return numeric(0);
}

varDeclarationParser::NumericContext* varDeclarationParser::numeric(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  varDeclarationParser::NumericContext *_localctx = _tracker.createInstance<NumericContext>(_ctx, parentState);
  varDeclarationParser::NumericContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, varDeclarationParser::RuleNumeric, precedence);

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
    setState(143);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(137);
      numericAtom();
      break;
    }

    case 2: {
      setState(138);
      logic(0);
      break;
    }

    case 3: {
      setState(139);
      match(varDeclarationParser::LPAREN);
      setState(140);
      numeric(0);
      setState(141);
      match(varDeclarationParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(153);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(151);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(145);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(146);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == varDeclarationParser::TIMES

          || _la == varDeclarationParser::DIV)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(147);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(148);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(149);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == varDeclarationParser::PLUS

          || _la == varDeclarationParser::MINUS)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(150);
          numeric(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(155);
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

varDeclarationParser::NumericAtomContext::NumericAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::NumericAtomContext::NUMERIC_CONSTANT() {
  return getToken(varDeclarationParser::NUMERIC_CONSTANT, 0);
}

tree::TerminalNode* varDeclarationParser::NumericAtomContext::NUMERIC_VARIABLE() {
  return getToken(varDeclarationParser::NUMERIC_VARIABLE, 0);
}


size_t varDeclarationParser::NumericAtomContext::getRuleIndex() const {
  return varDeclarationParser::RuleNumericAtom;
}

void varDeclarationParser::NumericAtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericAtom(this);
}

void varDeclarationParser::NumericAtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericAtom(this);
}

varDeclarationParser::NumericAtomContext* varDeclarationParser::numericAtom() {
  NumericAtomContext *_localctx = _tracker.createInstance<NumericAtomContext>(_ctx, getState());
  enterRule(_localctx, 16, varDeclarationParser::RuleNumericAtom);
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
    setState(156);
    _la = _input->LA(1);
    if (!(_la == varDeclarationParser::NUMERIC_CONSTANT

    || _la == varDeclarationParser::NUMERIC_VARIABLE)) {
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

varDeclarationParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* varDeclarationParser::RelopContext::GT() {
  return getToken(varDeclarationParser::GT, 0);
}

tree::TerminalNode* varDeclarationParser::RelopContext::GE() {
  return getToken(varDeclarationParser::GE, 0);
}

tree::TerminalNode* varDeclarationParser::RelopContext::LT() {
  return getToken(varDeclarationParser::LT, 0);
}

tree::TerminalNode* varDeclarationParser::RelopContext::LE() {
  return getToken(varDeclarationParser::LE, 0);
}


size_t varDeclarationParser::RelopContext::getRuleIndex() const {
  return varDeclarationParser::RuleRelop;
}

void varDeclarationParser::RelopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void varDeclarationParser::RelopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<varDeclarationListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}

varDeclarationParser::RelopContext* varDeclarationParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 18, varDeclarationParser::RuleRelop);
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
    setState(158);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2013265920) != 0))) {
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

bool varDeclarationParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return booleanSempred(antlrcpp::downCast<BooleanContext *>(context), predicateIndex);
    case 4: return logicSempred(antlrcpp::downCast<LogicContext *>(context), predicateIndex);
    case 7: return numericSempred(antlrcpp::downCast<NumericContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool varDeclarationParser::booleanSempred(BooleanContext *_localctx, size_t predicateIndex) {
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

bool varDeclarationParser::logicSempred(LogicContext *_localctx, size_t predicateIndex) {
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

bool varDeclarationParser::numericSempred(NumericContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 12: return precpred(_ctx, 5);
    case 13: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void varDeclarationParser::initialize() {
  ::antlr4::internal::call_once(vardeclarationParserOnceFlag, vardeclarationParserInitialize);
}
