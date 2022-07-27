
// Generated from metric.g4 by ANTLR 4.9.2

#pragma once

#include "antlr4-runtime.h"

class metricLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1,
    T__1 = 2,
    T__2 = 3,
    T__3 = 4,
    SIGN = 5,
    LGPAREN = 6,
    RGPAREN = 7,
    LCPAREN = 8,
    RCPAREN = 9,
    LPAREN = 10,
    RPAREN = 11,
    VARIABLE = 12,
    INDEX = 13,
    NUMERIC = 14,
    VERILOG_BINARY = 15,
    GCC_BINARY = 16,
    HEX = 17,
    BOOLEAN = 18,
    PLUS = 19,
    MINUS = 20,
    TIMES = 21,
    DIV = 22,
    GT = 23,
    GE = 24,
    LT = 25,
    LE = 26,
    EQ = 27,
    NEQ = 28,
    BAND = 29,
    BOR = 30,
    BXOR = 31,
    NEG = 32,
    LSHIFT = 33,
    RSHIFT = 34,
    AND = 35,
    OR = 36,
    NOT = 37,
    WS = 38
  };

  explicit metricLexer(antlr4::CharStream *input);
  ~metricLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string> &getRuleNames() const override;

  virtual const std::vector<std::string> &getChannelNames() const override;
  virtual const std::vector<std::string> &getModeNames() const override;
  virtual const std::vector<std::string> &
  getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary &getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN &getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};
