
// Generated from proposition.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  propositionLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, SIGN = 7, 
    CONST_SUFFIX = 8, LGPAREN = 9, RGPAREN = 10, LCPAREN = 11, RCPAREN = 12, 
    LPAREN = 13, RPAREN = 14, VARIABLE = 15, NUMERIC = 16, VERILOG_BINARY = 17, 
    GCC_BINARY = 18, HEX = 19, BOOLEAN = 20, PLUS = 21, MINUS = 22, TIMES = 23, 
    DIV = 24, GT = 25, GE = 26, LT = 27, LE = 28, EQ = 29, NEQ = 30, BAND = 31, 
    BOR = 32, BXOR = 33, NEG = 34, LSHIFT = 35, RSHIFT = 36, AND = 37, OR = 38, 
    NOT = 39, WS = 40
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

