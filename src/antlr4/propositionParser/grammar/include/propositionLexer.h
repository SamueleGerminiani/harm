
// Generated from proposition.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  propositionLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, BOOLEAN_CONSTANT = 2, BOOLEAN_VARIABLE = 3, LOGIC_CONSTANT = 4, 
    LOGIC_VARIABLE = 5, SIGN = 6, CONST_SUFFIX = 7, NUMERIC_CONSTANT = 8, 
    NUMERIC_VARIABLE = 9, LGPAREN = 10, RGPAREN = 11, LCPAREN = 12, RCPAREN = 13, 
    LPAREN = 14, RPAREN = 15, NUMERIC = 16, VERILOG_BINARY = 17, GCC_BINARY = 18, 
    HEX = 19, PLUS = 20, MINUS = 21, TIMES = 22, DIV = 23, GT = 24, GE = 25, 
    LT = 26, LE = 27, EQ = 28, NEQ = 29, BAND = 30, BOR = 31, BXOR = 32, 
    NEG = 33, LSHIFT = 34, RSHIFT = 35, AND = 36, OR = 37, NOT = 38, WS = 39
  };

  explicit propositionLexer(antlr4::CharStream *input);

  ~propositionLexer() override;


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

