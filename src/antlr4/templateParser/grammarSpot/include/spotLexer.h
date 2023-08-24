
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
    BOOLEAN_CONSTANT = 24, BOOLEAN_VARIABLE = 25, LOGIC_VARIABLE = 26, CONST_SUFFIX = 27, 
    NUMERIC_CONSTANT = 28, NUMERIC_VARIABLE = 29, LCURLY = 30, RCURLY = 31, 
    LSQUARED = 32, RSQUARED = 33, LROUND = 34, RROUND = 35, SINTEGER = 36, 
    UINTEGER = 37, FLOAT = 38, VERILOG_BINARY = 39, GCC_BINARY = 40, HEX = 41, 
    PLUS = 42, MINUS = 43, TIMES = 44, DIV = 45, GT = 46, GE = 47, LT = 48, 
    LE = 49, EQ = 50, NEQ = 51, BAND = 52, BOR = 53, BXOR = 54, NEG = 55, 
    LSHIFT = 56, RSHIFT = 57, AND = 58, OR = 59, NOT = 60, WS = 61
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

