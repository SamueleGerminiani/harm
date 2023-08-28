
// Generated from spot.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  spotLexer : public antlr4::Lexer {
public:
  enum {
    PLACEHOLDER = 1, DT_AND = 2, DT_NEXT = 3, DT_NEXT_AND = 4, DT_NCREPS = 5, 
    SEP = 6, FUNCTION = 7, EVENTUALLY = 8, ALWAYS = 9, NEXT = 10, UNTIL = 11, 
    RELEASE = 12, DOTS = 13, IMPL = 14, IMPLO = 15, IFF = 16, XOR = 17, 
    SEREIMPL = 18, SEREIMPLO = 19, ASS = 20, DELAY = 21, SCOL = 22, COL = 23, 
    DOLLAR = 24, BOOLEAN_CONSTANT = 25, BOOLEAN_VARIABLE = 26, LOGIC_VARIABLE = 27, 
    CONST_SUFFIX = 28, NUMERIC_CONSTANT = 29, NUMERIC_VARIABLE = 30, LCURLY = 31, 
    RCURLY = 32, LSQUARED = 33, RSQUARED = 34, LROUND = 35, RROUND = 36, 
    SINTEGER = 37, UINTEGER = 38, FLOAT = 39, VERILOG_BINARY = 40, GCC_BINARY = 41, 
    HEX = 42, PLUS = 43, MINUS = 44, TIMES = 45, DIV = 46, GT = 47, GE = 48, 
    LT = 49, LE = 50, EQ = 51, NEQ = 52, BAND = 53, BOR = 54, BXOR = 55, 
    NEG = 56, LSHIFT = 57, RSHIFT = 58, AND = 59, OR = 60, NOT = 61, WS = 62
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

