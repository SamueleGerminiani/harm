
// Generated from proposition.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  propositionLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, BOOLEAN_CONSTANT = 2, BOOLEAN_VARIABLE = 3, INT_VARIABLE = 4, 
    CONST_SUFFIX = 5, LOGIC_VARIABLE = 6, FLOAT_CONSTANT = 7, FLOAT_VARIABLE = 8, 
    SUBSTR = 9, STRING_CONSTANT = 10, STRING_VARIABLE = 11, LCURLY = 12, 
    RCURLY = 13, LSQUARED = 14, RSQUARED = 15, LROUND = 16, RROUND = 17, 
    INSIDE = 18, FUNCTION = 19, SINTEGER = 20, UINTEGER = 21, FLOAT = 22, 
    GCC_BINARY = 23, HEX = 24, VERILOG_BASED = 25, FILL_LITERAL = 26, SINGLE_QUOTE = 27, 
    PLUS = 28, MINUS = 29, TIMES = 30, DIV = 31, GT = 32, GE = 33, LT = 34, 
    LE = 35, EQ = 36, NEQ = 37, CASE_EQ = 38, CASE_NEQ = 39, QUESTION = 40, 
    BAND = 41, BOR = 42, BXOR = 43, NEG = 44, LSHIFT = 45, RSHIFT = 46, 
    AND = 47, OR = 48, NOT = 49, COL = 50, DCOL = 51, DOLLAR = 52, RANGE = 53, 
    CLS_TYPE = 54, WS = 55
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

