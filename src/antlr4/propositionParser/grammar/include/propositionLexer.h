
// Generated from proposition.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  propositionLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, BOOLEAN_CONSTANT = 2, BOOLEAN_VARIABLE = 3, INT_VARIABLE = 4, 
    CONST_SUFFIX = 5, LOGIC_VARIABLE = 6, BIT_VARIABLE = 7, FLOAT_CONSTANT = 8, 
    FLOAT_VARIABLE = 9, SUBSTR = 10, STRING_CONSTANT = 11, STRING_VARIABLE = 12, 
    LCURLY = 13, RCURLY = 14, LSQUARED = 15, RSQUARED = 16, LROUND = 17, 
    RROUND = 18, INSIDE = 19, FUNCTION = 20, UINTEGER = 21, FLOAT = 22, 
    GCC_BINARY = 23, HEX = 24, VERILOG_BASED = 25, FILL_LITERAL = 26, SINGLE_QUOTE = 27, 
    PLUS = 28, MINUS = 29, TIMES = 30, DIV = 31, GT = 32, GE = 33, LT = 34, 
    LE = 35, EQ = 36, NEQ = 37, CASE_EQ = 38, CASE_NEQ = 39, QUESTION = 40, 
    BAND = 41, BOR = 42, BXOR = 43, NEG = 44, ALSHIFT = 45, ARSHIFT = 46, 
    LSHIFT = 47, RSHIFT = 48, AND = 49, OR = 50, NOT = 51, COL = 52, DCOL = 53, 
    DOLLAR = 54, RANGE = 55, CLS_TYPE = 56, WS = 57
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

