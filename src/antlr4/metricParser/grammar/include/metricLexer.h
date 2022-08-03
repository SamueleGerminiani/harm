
// Generated from metric.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  metricLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, SIGN = 5, LGPAREN = 6, RGPAREN = 7, 
    LCPAREN = 8, RCPAREN = 9, LPAREN = 10, RPAREN = 11, VARIABLE = 12, INDEX = 13, 
    NUMERIC = 14, VERILOG_BINARY = 15, GCC_BINARY = 16, HEX = 17, BOOLEAN = 18, 
    PLUS = 19, MINUS = 20, TIMES = 21, DIV = 22, GT = 23, GE = 24, LT = 25, 
    LE = 26, EQ = 27, NEQ = 28, BAND = 29, BOR = 30, BXOR = 31, NEG = 32, 
    LSHIFT = 33, RSHIFT = 34, AND = 35, OR = 36, NOT = 37, WS = 38
  };

  explicit metricLexer(antlr4::CharStream *input);

  ~metricLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

