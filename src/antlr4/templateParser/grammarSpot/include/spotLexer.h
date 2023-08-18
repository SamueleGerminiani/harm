
// Generated from spot.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  spotLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, DT_AND = 10, SEP = 11, FUNCTION = 12, EVENTUALLY = 13, 
    ALWAYS = 14, NEXT = 15, UNTIL = 16, RELEASE = 17, DOTS = 18, IMPL = 19, 
    IMPL2 = 20, IFF = 21, XOR = 22, BIND1 = 23, BIND2 = 24, SEREIMPL1 = 25, 
    SEREIMPL2 = 26, ASS = 27, DELAY = 28, SCOL = 29, COL = 30, FIRST_MATCH = 31, 
    SIGN = 32, CONST_SUFFIX = 33, LGPAREN = 34, RGPAREN = 35, LCPAREN = 36, 
    RCPAREN = 37, LPAREN = 38, RPAREN = 39, VARIABLE = 40, NUMERIC = 41, 
    VERILOG_BINARY = 42, GCC_BINARY = 43, HEX = 44, BOOLEAN = 45, PLUS = 46, 
    MINUS = 47, TIMES = 48, DIV = 49, GT = 50, GE = 51, LT = 52, LE = 53, 
    EQ = 54, NEQ = 55, BAND = 56, BOR = 57, BXOR = 58, NEG = 59, LSHIFT = 60, 
    RSHIFT = 61, AND = 62, OR = 63, NOT = 64, WS = 65
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

