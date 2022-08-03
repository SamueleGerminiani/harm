
// Generated from sva.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  temporalSVALexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, DT_AND = 10, SEP = 11, EVENTUALLY = 12, ALWAYS = 13, 
    NEXT = 14, UNTIL = 15, RELEASE = 16, DOTS = 17, IMPL = 18, IMPL2 = 19, 
    IFF = 20, XOR = 21, BIND1 = 22, BIND2 = 23, ASS = 24, DELAY = 25, SCOL = 26, 
    COL = 27, FIRST_MATCH = 28, SIGN = 29, LGPAREN = 30, RGPAREN = 31, LCPAREN = 32, 
    RCPAREN = 33, LPAREN = 34, RPAREN = 35, VARIABLE = 36, NUMERIC = 37, 
    VERILOG_BINARY = 38, GCC_BINARY = 39, HEX = 40, BOOLEAN = 41, PLUS = 42, 
    MINUS = 43, TIMES = 44, DIV = 45, GT = 46, GE = 47, LT = 48, LE = 49, 
    EQ = 50, NEQ = 51, BAND = 52, BOR = 53, BXOR = 54, NEG = 55, LSHIFT = 56, 
    RSHIFT = 57, AND = 58, OR = 59, NOT = 60, WS = 61
  };

  explicit temporalSVALexer(antlr4::CharStream *input);

  ~temporalSVALexer() override;


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

