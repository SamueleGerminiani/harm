
// Generated from proposition.g4 by ANTLR 4.10.1

#include "propositionListener.h"

#include "propositionParser.h"

using namespace antlrcpp;

using namespace antlr4;

namespace {

struct PropositionParserStaticData final {
  PropositionParserStaticData(std::vector<std::string> ruleNames,
                              std::vector<std::string> literalNames,
                              std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PropositionParserStaticData(const PropositionParserStaticData &) = delete;
  PropositionParserStaticData(PropositionParserStaticData &&) = delete;
  PropositionParserStaticData &
  operator=(const PropositionParserStaticData &) = delete;
  PropositionParserStaticData &
  operator=(PropositionParserStaticData &&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag propositionParserOnceFlag;
PropositionParserStaticData *propositionParserStaticData = nullptr;

void propositionParserInitialize() {
  assert(propositionParserStaticData == nullptr);
  auto staticData = std::make_unique<PropositionParserStaticData>(
      std::vector<std::string>{
          "file", "boolean", "booleanAtom", "booleanConstant",
          "booleanVariable", "logic", "bitSelect", "logicAtom", "logicConstant",
          "logicVariable", "numeric", "numericAtom", "numericConstant",
          "numericVariable", "variable", "relop"},
      std::vector<std::string>{"",
                               "',bool>'",
                               "':'",
                               "',logic('",
                               "','",
                               "')>'",
                               "',numeric('",
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
                               "'!'"},
      std::vector<std::string>{"",
                               "",
                               "",
                               "",
                               "",
                               "",
                               "",
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
                               "WS"});
  static const int32_t serializedATNSegment[] = {
      4,   1,   39,  195, 2,   0,   7,   0,   2,   1,   7,   1,   2,   2,   7,
      2,   2,   3,   7,   3,   2,   4,   7,   4,   2,   5,   7,   5,   2,   6,
      7,   6,   2,   7,   7,   7,   2,   8,   7,   8,   2,   9,   7,   9,   2,
      10,  7,   10,  2,   11,  7,   11,  2,   12,  7,   12,  2,   13,  7,   13,
      2,   14,  7,   14,  2,   15,  7,   15,  1,   0,   1,   0,   1,   0,   1,
      1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      1,   1,   1,   1,   1,   1,   1,   3,   1,   70,  8,   1,   1,   1,   1,
      1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
      1,   1,   1,   1,   1,   1,   5,   1,   84,  8,   1,   10,  1,   12,  1,
      87,  9,   1,   1,   2,   1,   2,   3,   2,   91,  8,   2,   1,   3,   1,
      3,   1,   4,   1,   4,   1,   4,   1,   4,   1,   5,   1,   5,   1,   5,
      1,   5,   1,   5,   1,   5,   1,   5,   1,   5,   3,   5,   107, 8,   5,
      1,   5,   1,   5,   1,   5,   1,   5,   1,   5,   1,   5,   1,   5,   1,
      5,   1,   5,   1,   5,   1,   5,   1,   5,   1,   5,   1,   5,   1,   5,
      1,   5,   1,   5,   1,   5,   1,   5,   1,   5,   1,   5,   1,   5,   1,
      5,   5,   5,   132, 8,   5,   10,  5,   12,  5,   135, 9,   5,   1,   6,
      1,   6,   1,   6,   1,   6,   3,   6,   141, 8,   6,   1,   6,   1,   6,
      1,   7,   1,   7,   3,   7,   147, 8,   7,   1,   8,   1,   8,   1,   9,
      1,   9,   1,   9,   1,   9,   1,   9,   1,   9,   1,   9,   1,   9,   1,
      10,  1,   10,  1,   10,  1,   10,  1,   10,  1,   10,  1,   10,  3,   10,
      166, 8,   10,  1,   10,  1,   10,  1,   10,  1,   10,  1,   10,  1,   10,
      5,   10,  174, 8,   10,  10,  10,  12,  10,  177, 9,   10,  1,   11,  1,
      11,  3,   11,  181, 8,   11,  1,   12,  1,   12,  1,   13,  1,   13,  1,
      13,  1,   13,  1,   13,  1,   13,  1,   14,  1,   14,  1,   15,  1,   15,
      1,   15,  0,   3,   2,   10,  20,  16,  0,   2,   4,   6,   8,   10,  12,
      14,  16,  18,  20,  22,  24,  26,  28,  30,  0,   4,   1,   0,   22,  23,
      1,   0,   20,  21,  1,   0,   15,  18,  1,   0,   24,  27,  210, 0,   32,
      1,   0,   0,   0,   2,   69,  1,   0,   0,   0,   4,   90,  1,   0,   0,
      0,   6,   92,  1,   0,   0,   0,   8,   94,  1,   0,   0,   0,   10,  106,
      1,   0,   0,   0,   12,  136, 1,   0,   0,   0,   14,  146, 1,   0,   0,
      0,   16,  148, 1,   0,   0,   0,   18,  150, 1,   0,   0,   0,   20,  165,
      1,   0,   0,   0,   22,  180, 1,   0,   0,   0,   24,  182, 1,   0,   0,
      0,   26,  184, 1,   0,   0,   0,   28,  190, 1,   0,   0,   0,   30,  192,
      1,   0,   0,   0,   32,  33,  3,   2,   1,   0,   33,  34,  5,   0,   0,
      1,   34,  1,   1,   0,   0,   0,   35,  36,  6,   1,   -1,  0,   36,  37,
      5,   38,  0,   0,   37,  70,  3,   2,   1,   15,  38,  39,  3,   10,  5,
      0,   39,  40,  3,   30,  15,  0,   40,  41,  3,   10,  5,   0,   41,  70,
      1,   0,   0,   0,   42,  43,  3,   20,  10,  0,   43,  44,  3,   30,  15,
      0,   44,  45,  3,   20,  10,  0,   45,  70,  1,   0,   0,   0,   46,  47,
      3,   10,  5,   0,   47,  48,  5,   28,  0,   0,   48,  49,  3,   10,  5,
      0,   49,  70,  1,   0,   0,   0,   50,  51,  3,   20,  10,  0,   51,  52,
      5,   28,  0,   0,   52,  53,  3,   20,  10,  0,   53,  70,  1,   0,   0,
      0,   54,  55,  3,   10,  5,   0,   55,  56,  5,   29,  0,   0,   56,  57,
      3,   10,  5,   0,   57,  70,  1,   0,   0,   0,   58,  59,  3,   20,  10,
      0,   59,  60,  5,   29,  0,   0,   60,  61,  3,   20,  10,  0,   61,  70,
      1,   0,   0,   0,   62,  70,  3,   4,   2,   0,   63,  70,  3,   10,  5,
      0,   64,  70,  3,   20,  10,  0,   65,  66,  5,   12,  0,   0,   66,  67,
      3,   2,   1,   0,   67,  68,  5,   13,  0,   0,   68,  70,  1,   0,   0,
      0,   69,  35,  1,   0,   0,   0,   69,  38,  1,   0,   0,   0,   69,  42,
      1,   0,   0,   0,   69,  46,  1,   0,   0,   0,   69,  50,  1,   0,   0,
      0,   69,  54,  1,   0,   0,   0,   69,  58,  1,   0,   0,   0,   69,  62,
      1,   0,   0,   0,   69,  63,  1,   0,   0,   0,   69,  64,  1,   0,   0,
      0,   69,  65,  1,   0,   0,   0,   70,  85,  1,   0,   0,   0,   71,  72,
      10,  10,  0,   0,   72,  73,  5,   28,  0,   0,   73,  84,  3,   2,   1,
      11,  74,  75,  10,  7,   0,   0,   75,  76,  5,   29,  0,   0,   76,  84,
      3,   2,   1,   8,   77,  78,  10,  6,   0,   0,   78,  79,  5,   36,  0,
      0,   79,  84,  3,   2,   1,   7,   80,  81,  10,  5,   0,   0,   81,  82,
      5,   37,  0,   0,   82,  84,  3,   2,   1,   6,   83,  71,  1,   0,   0,
      0,   83,  74,  1,   0,   0,   0,   83,  77,  1,   0,   0,   0,   83,  80,
      1,   0,   0,   0,   84,  87,  1,   0,   0,   0,   85,  83,  1,   0,   0,
      0,   85,  86,  1,   0,   0,   0,   86,  3,   1,   0,   0,   0,   87,  85,
      1,   0,   0,   0,   88,  91,  3,   6,   3,   0,   89,  91,  3,   8,   4,
      0,   90,  88,  1,   0,   0,   0,   90,  89,  1,   0,   0,   0,   91,  5,
      1,   0,   0,   0,   92,  93,  5,   19,  0,   0,   93,  7,   1,   0,   0,
      0,   94,  95,  5,   26,  0,   0,   95,  96,  3,   28,  14,  0,   96,  97,
      5,   1,   0,   0,   97,  9,   1,   0,   0,   0,   98,  99,  6,   5,   -1,
      0,   99,  100, 5,   33,  0,   0,   100, 107, 3,   10,  5,   11,  101, 107,
      3,   14,  7,   0,   102, 103, 5,   12,  0,   0,   103, 104, 3,   10,  5,
      0,   104, 105, 5,   13,  0,   0,   105, 107, 1,   0,   0,   0,   106, 98,
      1,   0,   0,   0,   106, 101, 1,   0,   0,   0,   106, 102, 1,   0,   0,
      0,   107, 133, 1,   0,   0,   0,   108, 109, 10,  9,   0,   0,   109, 110,
      7,   0,   0,   0,   110, 132, 3,   10,  5,   10,  111, 112, 10,  8,   0,
      0,   112, 113, 7,   1,   0,   0,   113, 132, 3,   10,  5,   9,   114, 115,
      10,  7,   0,   0,   115, 116, 5,   34,  0,   0,   116, 132, 3,   10,  5,
      8,   117, 118, 10,  6,   0,   0,   118, 119, 5,   35,  0,   0,   119, 132,
      3,   10,  5,   7,   120, 121, 10,  5,   0,   0,   121, 122, 5,   30,  0,
      0,   122, 132, 3,   10,  5,   6,   123, 124, 10,  4,   0,   0,   124, 125,
      5,   32,  0,   0,   125, 132, 3,   10,  5,   5,   126, 127, 10,  3,   0,
      0,   127, 128, 5,   31,  0,   0,   128, 132, 3,   10,  5,   4,   129, 130,
      10,  10,  0,   0,   130, 132, 3,   12,  6,   0,   131, 108, 1,   0,   0,
      0,   131, 111, 1,   0,   0,   0,   131, 114, 1,   0,   0,   0,   131, 117,
      1,   0,   0,   0,   131, 120, 1,   0,   0,   0,   131, 123, 1,   0,   0,
      0,   131, 126, 1,   0,   0,   0,   131, 129, 1,   0,   0,   0,   132, 135,
      1,   0,   0,   0,   133, 131, 1,   0,   0,   0,   133, 134, 1,   0,   0,
      0,   134, 11,  1,   0,   0,   0,   135, 133, 1,   0,   0,   0,   136, 137,
      5,   10,  0,   0,   137, 140, 5,   15,  0,   0,   138, 139, 5,   2,   0,
      0,   139, 141, 5,   15,  0,   0,   140, 138, 1,   0,   0,   0,   140, 141,
      1,   0,   0,   0,   141, 142, 1,   0,   0,   0,   142, 143, 5,   11,  0,
      0,   143, 13,  1,   0,   0,   0,   144, 147, 3,   16,  8,   0,   145, 147,
      3,   18,  9,   0,   146, 144, 1,   0,   0,   0,   146, 145, 1,   0,   0,
      0,   147, 15,  1,   0,   0,   0,   148, 149, 7,   2,   0,   0,   149, 17,
      1,   0,   0,   0,   150, 151, 5,   26,  0,   0,   151, 152, 3,   28,  14,
      0,   152, 153, 5,   3,   0,   0,   153, 154, 5,   7,   0,   0,   154, 155,
      5,   4,   0,   0,   155, 156, 5,   15,  0,   0,   156, 157, 5,   5,   0,
      0,   157, 19,  1,   0,   0,   0,   158, 159, 6,   10,  -1,  0,   159, 166,
      3,   22,  11,  0,   160, 166, 3,   10,  5,   0,   161, 162, 5,   12,  0,
      0,   162, 163, 3,   20,  10,  0,   163, 164, 5,   13,  0,   0,   164, 166,
      1,   0,   0,   0,   165, 158, 1,   0,   0,   0,   165, 160, 1,   0,   0,
      0,   165, 161, 1,   0,   0,   0,   166, 175, 1,   0,   0,   0,   167, 168,
      10,  5,   0,   0,   168, 169, 7,   0,   0,   0,   169, 174, 3,   20,  10,
      6,   170, 171, 10,  4,   0,   0,   171, 172, 7,   1,   0,   0,   172, 174,
      3,   20,  10,  5,   173, 167, 1,   0,   0,   0,   173, 170, 1,   0,   0,
      0,   174, 177, 1,   0,   0,   0,   175, 173, 1,   0,   0,   0,   175, 176,
      1,   0,   0,   0,   176, 21,  1,   0,   0,   0,   177, 175, 1,   0,   0,
      0,   178, 181, 3,   24,  12,  0,   179, 181, 3,   26,  13,  0,   180, 178,
      1,   0,   0,   0,   180, 179, 1,   0,   0,   0,   181, 23,  1,   0,   0,
      0,   182, 183, 5,   15,  0,   0,   183, 25,  1,   0,   0,   0,   184, 185,
      5,   26,  0,   0,   185, 186, 3,   28,  14,  0,   186, 187, 5,   6,   0,
      0,   187, 188, 5,   15,  0,   0,   188, 189, 5,   5,   0,   0,   189, 27,
      1,   0,   0,   0,   190, 191, 5,   14,  0,   0,   191, 29,  1,   0,   0,
      0,   192, 193, 7,   3,   0,   0,   193, 31,  1,   0,   0,   0,   13,  69,
      83,  85,  90,  106, 131, 133, 140, 146, 165, 173, 175, 180};
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
  propositionParserStaticData = staticData.release();
}

} // namespace

propositionParser::propositionParser(TokenStream *input)
    : propositionParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

propositionParser::propositionParser(
    TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options)
    : Parser(input) {
  propositionParser::initialize();
  _interpreter = new atn::ParserATNSimulator(
      this, *propositionParserStaticData->atn,
      propositionParserStaticData->decisionToDFA,
      propositionParserStaticData->sharedContextCache, options);
}

propositionParser::~propositionParser() { delete _interpreter; }

const atn::ATN &propositionParser::getATN() const {
  return *propositionParserStaticData->atn;
}

std::string propositionParser::getGrammarFileName() const {
  return "proposition.g4";
}

const std::vector<std::string> &propositionParser::getRuleNames() const {
  return propositionParserStaticData->ruleNames;
}

const dfa::Vocabulary &propositionParser::getVocabulary() const {
  return propositionParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView propositionParser::getSerializedATN() const {
  return propositionParserStaticData->serializedATN;
}

//----------------- FileContext ------------------------------------------------------------------

propositionParser::FileContext::FileContext(ParserRuleContext *parent,
                                            size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

propositionParser::BooleanContext *propositionParser::FileContext::boolean() {
  return getRuleContext<propositionParser::BooleanContext>(0);
}

tree::TerminalNode *propositionParser::FileContext::EOF() {
  return getToken(propositionParser::EOF, 0);
}

size_t propositionParser::FileContext::getRuleIndex() const {
  return propositionParser::RuleFile;
}

void propositionParser::FileContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void propositionParser::FileContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

propositionParser::FileContext *propositionParser::file() {
  FileContext *_localctx =
      _tracker.createInstance<FileContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

propositionParser::BooleanContext::BooleanContext(ParserRuleContext *parent,
                                                  size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::BooleanContext::NOT() {
  return getToken(propositionParser::NOT, 0);
}

std::vector<propositionParser::BooleanContext *>
propositionParser::BooleanContext::boolean() {
  return getRuleContexts<propositionParser::BooleanContext>();
}

propositionParser::BooleanContext *
propositionParser::BooleanContext::boolean(size_t i) {
  return getRuleContext<propositionParser::BooleanContext>(i);
}

std::vector<propositionParser::LogicContext *>
propositionParser::BooleanContext::logic() {
  return getRuleContexts<propositionParser::LogicContext>();
}

propositionParser::LogicContext *
propositionParser::BooleanContext::logic(size_t i) {
  return getRuleContext<propositionParser::LogicContext>(i);
}

propositionParser::RelopContext *propositionParser::BooleanContext::relop() {
  return getRuleContext<propositionParser::RelopContext>(0);
}

std::vector<propositionParser::NumericContext *>
propositionParser::BooleanContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext *
propositionParser::BooleanContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
}

tree::TerminalNode *propositionParser::BooleanContext::EQ() {
  return getToken(propositionParser::EQ, 0);
}

tree::TerminalNode *propositionParser::BooleanContext::NEQ() {
  return getToken(propositionParser::NEQ, 0);
}

propositionParser::BooleanAtomContext *
propositionParser::BooleanContext::booleanAtom() {
  return getRuleContext<propositionParser::BooleanAtomContext>(0);
}

tree::TerminalNode *propositionParser::BooleanContext::LPAREN() {
  return getToken(propositionParser::LPAREN, 0);
}

tree::TerminalNode *propositionParser::BooleanContext::RPAREN() {
  return getToken(propositionParser::RPAREN, 0);
}

tree::TerminalNode *propositionParser::BooleanContext::AND() {
  return getToken(propositionParser::AND, 0);
}

tree::TerminalNode *propositionParser::BooleanContext::OR() {
  return getToken(propositionParser::OR, 0);
}

size_t propositionParser::BooleanContext::getRuleIndex() const {
  return propositionParser::RuleBoolean;
}

void propositionParser::BooleanContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolean(this);
}

void propositionParser::BooleanContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolean(this);
}

propositionParser::BooleanContext *propositionParser::boolean() {
  return boolean(0);
}

propositionParser::BooleanContext *propositionParser::boolean(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  propositionParser::BooleanContext *_localctx =
      _tracker.createInstance<BooleanContext>(_ctx, parentState);
  propositionParser::BooleanContext *previousContext = _localctx;
  (void)
      previousContext; // Silence compiler, in case the context is not used by generated code.
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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 0, _ctx)) {
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
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2,
                                                                     _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(83);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 1, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(71);

          if (!(precpred(_ctx, 10)))
            throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(72);
          match(propositionParser::EQ);
          setState(73);
          boolean(11);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(74);

          if (!(precpred(_ctx, 7)))
            throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(75);
          match(propositionParser::NEQ);
          setState(76);
          boolean(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(77);

          if (!(precpred(_ctx, 6)))
            throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(78);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop =
              match(propositionParser::AND);
          setState(79);
          boolean(7);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<BooleanContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleBoolean);
          setState(80);

          if (!(precpred(_ctx, 5)))
            throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(81);
          antlrcpp::downCast<BooleanContext *>(_localctx)->booleanop =
              match(propositionParser::OR);
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

//----------------- BooleanAtomContext ------------------------------------------------------------------

propositionParser::BooleanAtomContext::BooleanAtomContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

propositionParser::BooleanConstantContext *
propositionParser::BooleanAtomContext::booleanConstant() {
  return getRuleContext<propositionParser::BooleanConstantContext>(0);
}

propositionParser::BooleanVariableContext *
propositionParser::BooleanAtomContext::booleanVariable() {
  return getRuleContext<propositionParser::BooleanVariableContext>(0);
}

size_t propositionParser::BooleanAtomContext::getRuleIndex() const {
  return propositionParser::RuleBooleanAtom;
}

void propositionParser::BooleanAtomContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanAtom(this);
}

void propositionParser::BooleanAtomContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanAtom(this);
}

propositionParser::BooleanAtomContext *propositionParser::booleanAtom() {
  BooleanAtomContext *_localctx =
      _tracker.createInstance<BooleanAtomContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanConstantContext ------------------------------------------------------------------

propositionParser::BooleanConstantContext::BooleanConstantContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::BooleanConstantContext::BOOLEAN() {
  return getToken(propositionParser::BOOLEAN, 0);
}

size_t propositionParser::BooleanConstantContext::getRuleIndex() const {
  return propositionParser::RuleBooleanConstant;
}

void propositionParser::BooleanConstantContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanConstant(this);
}

void propositionParser::BooleanConstantContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanConstant(this);
}

propositionParser::BooleanConstantContext *
propositionParser::booleanConstant() {
  BooleanConstantContext *_localctx =
      _tracker.createInstance<BooleanConstantContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanVariableContext ------------------------------------------------------------------

propositionParser::BooleanVariableContext::BooleanVariableContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::BooleanVariableContext::LT() {
  return getToken(propositionParser::LT, 0);
}

propositionParser::VariableContext *
propositionParser::BooleanVariableContext::variable() {
  return getRuleContext<propositionParser::VariableContext>(0);
}

size_t propositionParser::BooleanVariableContext::getRuleIndex() const {
  return propositionParser::RuleBooleanVariable;
}

void propositionParser::BooleanVariableContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanVariable(this);
}

void propositionParser::BooleanVariableContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanVariable(this);
}

propositionParser::BooleanVariableContext *
propositionParser::booleanVariable() {
  BooleanVariableContext *_localctx =
      _tracker.createInstance<BooleanVariableContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicContext ------------------------------------------------------------------

propositionParser::LogicContext::LogicContext(ParserRuleContext *parent,
                                              size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::LogicContext::NEG() {
  return getToken(propositionParser::NEG, 0);
}

std::vector<propositionParser::LogicContext *>
propositionParser::LogicContext::logic() {
  return getRuleContexts<propositionParser::LogicContext>();
}

propositionParser::LogicContext *
propositionParser::LogicContext::logic(size_t i) {
  return getRuleContext<propositionParser::LogicContext>(i);
}

propositionParser::LogicAtomContext *
propositionParser::LogicContext::logicAtom() {
  return getRuleContext<propositionParser::LogicAtomContext>(0);
}

tree::TerminalNode *propositionParser::LogicContext::LPAREN() {
  return getToken(propositionParser::LPAREN, 0);
}

tree::TerminalNode *propositionParser::LogicContext::RPAREN() {
  return getToken(propositionParser::RPAREN, 0);
}

tree::TerminalNode *propositionParser::LogicContext::TIMES() {
  return getToken(propositionParser::TIMES, 0);
}

tree::TerminalNode *propositionParser::LogicContext::DIV() {
  return getToken(propositionParser::DIV, 0);
}

tree::TerminalNode *propositionParser::LogicContext::PLUS() {
  return getToken(propositionParser::PLUS, 0);
}

tree::TerminalNode *propositionParser::LogicContext::MINUS() {
  return getToken(propositionParser::MINUS, 0);
}

tree::TerminalNode *propositionParser::LogicContext::LSHIFT() {
  return getToken(propositionParser::LSHIFT, 0);
}

tree::TerminalNode *propositionParser::LogicContext::RSHIFT() {
  return getToken(propositionParser::RSHIFT, 0);
}

tree::TerminalNode *propositionParser::LogicContext::BAND() {
  return getToken(propositionParser::BAND, 0);
}

tree::TerminalNode *propositionParser::LogicContext::BXOR() {
  return getToken(propositionParser::BXOR, 0);
}

tree::TerminalNode *propositionParser::LogicContext::BOR() {
  return getToken(propositionParser::BOR, 0);
}

propositionParser::BitSelectContext *
propositionParser::LogicContext::bitSelect() {
  return getRuleContext<propositionParser::BitSelectContext>(0);
}

size_t propositionParser::LogicContext::getRuleIndex() const {
  return propositionParser::RuleLogic;
}

void propositionParser::LogicContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogic(this);
}

void propositionParser::LogicContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogic(this);
}

propositionParser::LogicContext *propositionParser::logic() { return logic(0); }

propositionParser::LogicContext *propositionParser::logic(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  propositionParser::LogicContext *_localctx =
      _tracker.createInstance<LogicContext>(_ctx, parentState);
  propositionParser::LogicContext *previousContext = _localctx;
  (void)
      previousContext; // Silence compiler, in case the context is not used by generated code.
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
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6,
                                                                     _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(131);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 5, _ctx)) {
        case 1: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(108);

          if (!(precpred(_ctx, 9)))
            throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(109);
          antlrcpp::downCast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::TIMES

                || _la == propositionParser::DIV)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->artop =
                _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(110);
          logic(10);
          break;
        }

        case 2: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(111);

          if (!(precpred(_ctx, 8)))
            throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(112);
          antlrcpp::downCast<LogicContext *>(_localctx)->artop = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::PLUS

                || _la == propositionParser::MINUS)) {
            antlrcpp::downCast<LogicContext *>(_localctx)->artop =
                _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(113);
          logic(9);
          break;
        }

        case 3: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(114);

          if (!(precpred(_ctx, 7)))
            throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(115);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop =
              match(propositionParser::LSHIFT);
          setState(116);
          logic(8);
          break;
        }

        case 4: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(117);

          if (!(precpred(_ctx, 6)))
            throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(118);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop =
              match(propositionParser::RSHIFT);
          setState(119);
          logic(7);
          break;
        }

        case 5: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(120);

          if (!(precpred(_ctx, 5)))
            throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(121);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop =
              match(propositionParser::BAND);
          setState(122);
          logic(6);
          break;
        }

        case 6: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(123);

          if (!(precpred(_ctx, 4)))
            throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(124);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop =
              match(propositionParser::BXOR);
          setState(125);
          logic(5);
          break;
        }

        case 7: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(126);

          if (!(precpred(_ctx, 3)))
            throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(127);
          antlrcpp::downCast<LogicContext *>(_localctx)->logop =
              match(propositionParser::BOR);
          setState(128);
          logic(4);
          break;
        }

        case 8: {
          _localctx =
              _tracker.createInstance<LogicContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleLogic);
          setState(129);

          if (!(precpred(_ctx, 10)))
            throw FailedPredicateException(this, "precpred(_ctx, 10)");
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

//----------------- BitSelectContext ------------------------------------------------------------------

propositionParser::BitSelectContext::BitSelectContext(ParserRuleContext *parent,
                                                      size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::BitSelectContext::LCPAREN() {
  return getToken(propositionParser::LCPAREN, 0);
}

std::vector<tree::TerminalNode *>
propositionParser::BitSelectContext::NUMERIC() {
  return getTokens(propositionParser::NUMERIC);
}

tree::TerminalNode *propositionParser::BitSelectContext::NUMERIC(size_t i) {
  return getToken(propositionParser::NUMERIC, i);
}

tree::TerminalNode *propositionParser::BitSelectContext::RCPAREN() {
  return getToken(propositionParser::RCPAREN, 0);
}

size_t propositionParser::BitSelectContext::getRuleIndex() const {
  return propositionParser::RuleBitSelect;
}

void propositionParser::BitSelectContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBitSelect(this);
}

void propositionParser::BitSelectContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBitSelect(this);
}

propositionParser::BitSelectContext *propositionParser::bitSelect() {
  BitSelectContext *_localctx =
      _tracker.createInstance<BitSelectContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicAtomContext ------------------------------------------------------------------

propositionParser::LogicAtomContext::LogicAtomContext(ParserRuleContext *parent,
                                                      size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

propositionParser::LogicConstantContext *
propositionParser::LogicAtomContext::logicConstant() {
  return getRuleContext<propositionParser::LogicConstantContext>(0);
}

propositionParser::LogicVariableContext *
propositionParser::LogicAtomContext::logicVariable() {
  return getRuleContext<propositionParser::LogicVariableContext>(0);
}

size_t propositionParser::LogicAtomContext::getRuleIndex() const {
  return propositionParser::RuleLogicAtom;
}

void propositionParser::LogicAtomContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicAtom(this);
}

void propositionParser::LogicAtomContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicAtom(this);
}

propositionParser::LogicAtomContext *propositionParser::logicAtom() {
  LogicAtomContext *_localctx =
      _tracker.createInstance<LogicAtomContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicConstantContext ------------------------------------------------------------------

propositionParser::LogicConstantContext::LogicConstantContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::LogicConstantContext::VERILOG_BINARY() {
  return getToken(propositionParser::VERILOG_BINARY, 0);
}

tree::TerminalNode *propositionParser::LogicConstantContext::GCC_BINARY() {
  return getToken(propositionParser::GCC_BINARY, 0);
}

tree::TerminalNode *propositionParser::LogicConstantContext::NUMERIC() {
  return getToken(propositionParser::NUMERIC, 0);
}

tree::TerminalNode *propositionParser::LogicConstantContext::HEX() {
  return getToken(propositionParser::HEX, 0);
}

size_t propositionParser::LogicConstantContext::getRuleIndex() const {
  return propositionParser::RuleLogicConstant;
}

void propositionParser::LogicConstantContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicConstant(this);
}

void propositionParser::LogicConstantContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicConstant(this);
}

propositionParser::LogicConstantContext *propositionParser::logicConstant() {
  LogicConstantContext *_localctx =
      _tracker.createInstance<LogicConstantContext>(_ctx, getState());
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
    if (!((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) & ((1ULL << propositionParser::NUMERIC) |
                             (1ULL << propositionParser::VERILOG_BINARY) |
                             (1ULL << propositionParser::GCC_BINARY) |
                             (1ULL << propositionParser::HEX))) != 0))) {
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

propositionParser::LogicVariableContext::LogicVariableContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::LogicVariableContext::LT() {
  return getToken(propositionParser::LT, 0);
}

propositionParser::VariableContext *
propositionParser::LogicVariableContext::variable() {
  return getRuleContext<propositionParser::VariableContext>(0);
}

tree::TerminalNode *propositionParser::LogicVariableContext::SIGN() {
  return getToken(propositionParser::SIGN, 0);
}

tree::TerminalNode *propositionParser::LogicVariableContext::NUMERIC() {
  return getToken(propositionParser::NUMERIC, 0);
}

size_t propositionParser::LogicVariableContext::getRuleIndex() const {
  return propositionParser::RuleLogicVariable;
}

void propositionParser::LogicVariableContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicVariable(this);
}

void propositionParser::LogicVariableContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicVariable(this);
}

propositionParser::LogicVariableContext *propositionParser::logicVariable() {
  LogicVariableContext *_localctx =
      _tracker.createInstance<LogicVariableContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericContext ------------------------------------------------------------------

propositionParser::NumericContext::NumericContext(ParserRuleContext *parent,
                                                  size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

propositionParser::NumericAtomContext *
propositionParser::NumericContext::numericAtom() {
  return getRuleContext<propositionParser::NumericAtomContext>(0);
}

propositionParser::LogicContext *propositionParser::NumericContext::logic() {
  return getRuleContext<propositionParser::LogicContext>(0);
}

tree::TerminalNode *propositionParser::NumericContext::LPAREN() {
  return getToken(propositionParser::LPAREN, 0);
}

std::vector<propositionParser::NumericContext *>
propositionParser::NumericContext::numeric() {
  return getRuleContexts<propositionParser::NumericContext>();
}

propositionParser::NumericContext *
propositionParser::NumericContext::numeric(size_t i) {
  return getRuleContext<propositionParser::NumericContext>(i);
}

tree::TerminalNode *propositionParser::NumericContext::RPAREN() {
  return getToken(propositionParser::RPAREN, 0);
}

tree::TerminalNode *propositionParser::NumericContext::TIMES() {
  return getToken(propositionParser::TIMES, 0);
}

tree::TerminalNode *propositionParser::NumericContext::DIV() {
  return getToken(propositionParser::DIV, 0);
}

tree::TerminalNode *propositionParser::NumericContext::PLUS() {
  return getToken(propositionParser::PLUS, 0);
}

tree::TerminalNode *propositionParser::NumericContext::MINUS() {
  return getToken(propositionParser::MINUS, 0);
}

size_t propositionParser::NumericContext::getRuleIndex() const {
  return propositionParser::RuleNumeric;
}

void propositionParser::NumericContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumeric(this);
}

void propositionParser::NumericContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumeric(this);
}

propositionParser::NumericContext *propositionParser::numeric() {
  return numeric(0);
}

propositionParser::NumericContext *propositionParser::numeric(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  propositionParser::NumericContext *_localctx =
      _tracker.createInstance<NumericContext>(_ctx, parentState);
  propositionParser::NumericContext *previousContext = _localctx;
  (void)
      previousContext; // Silence compiler, in case the context is not used by generated code.
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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 9, _ctx)) {
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
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11,
                                                                     _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(173);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 10, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(167);

          if (!(precpred(_ctx, 5)))
            throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(168);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop =
              _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::TIMES

                || _la == propositionParser::DIV)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop =
                _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(169);
          numeric(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<NumericContext>(parentContext,
                                                              parentState);
          pushNewRecursionContext(_localctx, startState, RuleNumeric);
          setState(170);

          if (!(precpred(_ctx, 4)))
            throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(171);
          antlrcpp::downCast<NumericContext *>(_localctx)->artop =
              _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == propositionParser::PLUS

                || _la == propositionParser::MINUS)) {
            antlrcpp::downCast<NumericContext *>(_localctx)->artop =
                _errHandler->recoverInline(this);
          } else {
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
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 11, _ctx);
    }
  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- NumericAtomContext ------------------------------------------------------------------

propositionParser::NumericAtomContext::NumericAtomContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

propositionParser::NumericConstantContext *
propositionParser::NumericAtomContext::numericConstant() {
  return getRuleContext<propositionParser::NumericConstantContext>(0);
}

propositionParser::NumericVariableContext *
propositionParser::NumericAtomContext::numericVariable() {
  return getRuleContext<propositionParser::NumericVariableContext>(0);
}

size_t propositionParser::NumericAtomContext::getRuleIndex() const {
  return propositionParser::RuleNumericAtom;
}

void propositionParser::NumericAtomContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericAtom(this);
}

void propositionParser::NumericAtomContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericAtom(this);
}

propositionParser::NumericAtomContext *propositionParser::numericAtom() {
  NumericAtomContext *_localctx =
      _tracker.createInstance<NumericAtomContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericConstantContext ------------------------------------------------------------------

propositionParser::NumericConstantContext::NumericConstantContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::NumericConstantContext::NUMERIC() {
  return getToken(propositionParser::NUMERIC, 0);
}

size_t propositionParser::NumericConstantContext::getRuleIndex() const {
  return propositionParser::RuleNumericConstant;
}

void propositionParser::NumericConstantContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericConstant(this);
}

void propositionParser::NumericConstantContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericConstant(this);
}

propositionParser::NumericConstantContext *
propositionParser::numericConstant() {
  NumericConstantContext *_localctx =
      _tracker.createInstance<NumericConstantContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericVariableContext ------------------------------------------------------------------

propositionParser::NumericVariableContext::NumericVariableContext(
    ParserRuleContext *parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::NumericVariableContext::LT() {
  return getToken(propositionParser::LT, 0);
}

propositionParser::VariableContext *
propositionParser::NumericVariableContext::variable() {
  return getRuleContext<propositionParser::VariableContext>(0);
}

tree::TerminalNode *propositionParser::NumericVariableContext::NUMERIC() {
  return getToken(propositionParser::NUMERIC, 0);
}

size_t propositionParser::NumericVariableContext::getRuleIndex() const {
  return propositionParser::RuleNumericVariable;
}

void propositionParser::NumericVariableContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericVariable(this);
}

void propositionParser::NumericVariableContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericVariable(this);
}

propositionParser::NumericVariableContext *
propositionParser::numericVariable() {
  NumericVariableContext *_localctx =
      _tracker.createInstance<NumericVariableContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

propositionParser::VariableContext::VariableContext(ParserRuleContext *parent,
                                                    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::VariableContext::VARIABLE() {
  return getToken(propositionParser::VARIABLE, 0);
}

size_t propositionParser::VariableContext::getRuleIndex() const {
  return propositionParser::RuleVariable;
}

void propositionParser::VariableContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void propositionParser::VariableContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

propositionParser::VariableContext *propositionParser::variable() {
  VariableContext *_localctx =
      _tracker.createInstance<VariableContext>(_ctx, getState());
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

  } catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelopContext ------------------------------------------------------------------

propositionParser::RelopContext::RelopContext(ParserRuleContext *parent,
                                              size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode *propositionParser::RelopContext::GT() {
  return getToken(propositionParser::GT, 0);
}

tree::TerminalNode *propositionParser::RelopContext::GE() {
  return getToken(propositionParser::GE, 0);
}

tree::TerminalNode *propositionParser::RelopContext::LT() {
  return getToken(propositionParser::LT, 0);
}

tree::TerminalNode *propositionParser::RelopContext::LE() {
  return getToken(propositionParser::LE, 0);
}

size_t propositionParser::RelopContext::getRuleIndex() const {
  return propositionParser::RuleRelop;
}

void propositionParser::RelopContext::enterRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void propositionParser::RelopContext::exitRule(
    tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<propositionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}

propositionParser::RelopContext *propositionParser::relop() {
  RelopContext *_localctx =
      _tracker.createInstance<RelopContext>(_ctx, getState());
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
    if (!((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) &
            ((1ULL << propositionParser::GT) | (1ULL << propositionParser::GE) |
             (1ULL << propositionParser::LT) |
             (1ULL << propositionParser::LE))) != 0))) {
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

bool propositionParser::sempred(RuleContext *context, size_t ruleIndex,
                                size_t predicateIndex) {
  switch (ruleIndex) {
  case 1:
    return booleanSempred(antlrcpp::downCast<BooleanContext *>(context),
                          predicateIndex);
  case 5:
    return logicSempred(antlrcpp::downCast<LogicContext *>(context),
                        predicateIndex);
  case 10:
    return numericSempred(antlrcpp::downCast<NumericContext *>(context),
                          predicateIndex);

  default:
    break;
  }
  return true;
}

bool propositionParser::booleanSempred(BooleanContext *_localctx,
                                       size_t predicateIndex) {
  switch (predicateIndex) {
  case 0:
    return precpred(_ctx, 10);
  case 1:
    return precpred(_ctx, 7);
  case 2:
    return precpred(_ctx, 6);
  case 3:
    return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

bool propositionParser::logicSempred(LogicContext *_localctx,
                                     size_t predicateIndex) {
  switch (predicateIndex) {
  case 4:
    return precpred(_ctx, 9);
  case 5:
    return precpred(_ctx, 8);
  case 6:
    return precpred(_ctx, 7);
  case 7:
    return precpred(_ctx, 6);
  case 8:
    return precpred(_ctx, 5);
  case 9:
    return precpred(_ctx, 4);
  case 10:
    return precpred(_ctx, 3);
  case 11:
    return precpred(_ctx, 10);

  default:
    break;
  }
  return true;
}

bool propositionParser::numericSempred(NumericContext *_localctx,
                                       size_t predicateIndex) {
  switch (predicateIndex) {
  case 12:
    return precpred(_ctx, 5);
  case 13:
    return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void propositionParser::initialize() {
  std::call_once(propositionParserOnceFlag, propositionParserInitialize);
}
