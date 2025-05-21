
// Generated from proposition.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  propositionLexer : public antlr4::Lexer {
public:
  enum {
    BOOLEAN_CONSTANT = 1, BOOLEAN_VARIABLE = 2, INT_VARIABLE = 3, CONST_SUFFIX = 4, 
    FLOAT_CONSTANT = 5, FLOAT_VARIABLE = 6, LCURLY = 7, RCURLY = 8, LSQUARED = 9, 
    RSQUARED = 10, LROUND = 11, RROUND = 12, SINTEGER = 13, UINTEGER = 14, 
    FLOAT = 15, GCC_BINARY = 16, HEX = 17, VERILOG_BINARY = 18, FVL = 19, 
    SINGLE_QUOTE = 20, PLUS = 21, MINUS = 22, TIMES = 23, DIV = 24, GT = 25, 
    GE = 26, LT = 27, LE = 28, EQ = 29, NEQ = 30, BAND = 31, BOR = 32, BXOR = 33, 
    NEG = 34, LSHIFT = 35, RSHIFT = 36, AND = 37, OR = 38, NOT = 39, COL = 40, 
    DCOL = 41, DOLLAR = 42, RANGE = 43, CLS_TYPE = 44, WS = 45
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

