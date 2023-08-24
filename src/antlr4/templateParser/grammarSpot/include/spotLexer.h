
// Generated from spot.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  spotLexer : public antlr4::Lexer {
public:
  enum {
    PLACEHOLDER = 1, DT_AND = 2, DT_NEXT = 3, DT_NEXT_AND = 4, DT_NCREPS = 5, 
    SEP = 6, FUNCTION = 7, EVENTUALLY = 8, ALWAYS = 9, NEXT = 10, UNTIL = 11, 
    RELEASE = 12, DOTS = 13, IMPL = 14, IMPL2 = 15, IFF = 16, XOR = 17, 
    BIND1 = 18, BIND2 = 19, SEREIMPL1 = 20, SEREIMPL2 = 21, ASS = 22, DELAY = 23, 
    SCOL = 24, COL = 25, FIRST_MATCH = 26, BOOLEAN_CONSTANT = 27, BOOLEAN_VARIABLE = 28, 
    LOGIC_CONSTANT = 29, LOGIC_VARIABLE = 30, SIGN = 31, CONST_SUFFIX = 32, 
    NUMERIC_CONSTANT = 33, NUMERIC_VARIABLE = 34, LGPAREN = 35, RGPAREN = 36, 
    LCPAREN = 37, RCPAREN = 38, LPAREN = 39, RPAREN = 40, NUMERIC = 41, 
    VERILOG_BINARY = 42, GCC_BINARY = 43, HEX = 44, PLUS = 45, MINUS = 46, 
    TIMES = 47, DIV = 48, GT = 49, GE = 50, LT = 51, LE = 52, EQ = 53, NEQ = 54, 
    BAND = 55, BOR = 56, BXOR = 57, NEG = 58, LSHIFT = 59, RSHIFT = 60, 
    AND = 61, OR = 62, NOT = 63, WS = 64
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

