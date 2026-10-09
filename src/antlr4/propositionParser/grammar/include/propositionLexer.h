
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
    RROUND = 18, INSIDE = 19, FUNCTION = 20, SINTEGER = 21, UINTEGER = 22, 
    FLOAT = 23, GCC_BINARY = 24, HEX = 25, VERILOG_BASED = 26, FILL_LITERAL = 27, 
    SINGLE_QUOTE = 28, PLUS = 29, MINUS = 30, TIMES = 31, DIV = 32, GT = 33, 
    GE = 34, LT = 35, LE = 36, EQ = 37, NEQ = 38, CASE_EQ = 39, CASE_NEQ = 40, 
    QUESTION = 41, BAND = 42, BOR = 43, BXOR = 44, NEG = 45, LSHIFT = 46, 
    RSHIFT = 47, AND = 48, OR = 49, NOT = 50, COL = 51, DCOL = 52, DOLLAR = 53, 
    RANGE = 54, CLS_TYPE = 55, WS = 56
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

