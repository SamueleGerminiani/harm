
// Generated from spot.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  spotLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, DT_AND = 10, SEP = 11, EVENTUALLY = 12, ALWAYS = 13, 
    NEXT = 14, UNTIL = 15, RELEASE = 16, DOTS = 17, IMPL = 18, IMPL2 = 19, 
    IFF = 20, XOR = 21, BIND1 = 22, BIND2 = 23, SEREIMPL1 = 24, SEREIMPL2 = 25, 
    ASS = 26, DELAY = 27, SCOL = 28, COL = 29, FIRST_MATCH = 30, SIGN = 31, 
    CONST_SUFFIX = 32, LGPAREN = 33, RGPAREN = 34, LCPAREN = 35, RCPAREN = 36, 
    LPAREN = 37, RPAREN = 38, VARIABLE = 39, NUMERIC = 40, VERILOG_BINARY = 41, 
    GCC_BINARY = 42, HEX = 43, BOOLEAN = 44, PLUS = 45, MINUS = 46, TIMES = 47, 
    DIV = 48, GT = 49, GE = 50, LT = 51, LE = 52, EQ = 53, NEQ = 54, BAND = 55, 
    BOR = 56, BXOR = 57, NEG = 58, LSHIFT = 59, RSHIFT = 60, AND = 61, OR = 62, 
    NOT = 63, WS = 64
  };

  explicit spotLexer(antlr4::CharStream *input);

  ~spotLexer() override;


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

