
// Generated from proposition.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  propositionLexer : public antlr4::Lexer {
public:
  enum {
    BOOLEAN_CONSTANT = 1, BOOLEAN_VARIABLE = 2, INT_VARIABLE = 3, CONST_SUFFIX = 4, 
    FLOAT_CONSTANT = 5, FLOAT_VARIABLE = 6, LCURLY = 7, RCURLY = 8, LSQUARED = 9, 
    RSQUARED = 10, LROUND = 11, RROUND = 12, INSIDE = 13, FUNCTION = 14, 
    SINTEGER = 15, UINTEGER = 16, FLOAT = 17, GCC_BINARY = 18, HEX = 19, 
    VERILOG_BINARY = 20, FVL = 21, SINGLE_QUOTE = 22, PLUS = 23, MINUS = 24, 
    TIMES = 25, DIV = 26, GT = 27, GE = 28, LT = 29, LE = 30, EQ = 31, NEQ = 32, 
    BAND = 33, BOR = 34, BXOR = 35, NEG = 36, LSHIFT = 37, RSHIFT = 38, 
    AND = 39, OR = 40, NOT = 41, COL = 42, DCOL = 43, DOLLAR = 44, RANGE = 45, 
    CLS_TYPE = 46, WS = 47
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

