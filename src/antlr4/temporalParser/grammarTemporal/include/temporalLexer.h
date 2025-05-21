
// Generated from temporal.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  temporalLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, PLACEHOLDER = 7, 
    DT_AND = 8, EVENTUALLY = 9, ALWAYS = 10, NEXT = 11, UNTIL = 12, RELEASE = 13, 
    DOTS = 14, IMPL = 15, IMPLO = 16, IFF = 17, SEREIMPL = 18, SEREIMPLO = 19, 
    ASS = 20, DELAY = 21, SCOL = 22, FIRST_MATCH = 23, TNOT = 24, TAND = 25, 
    INTERSECT = 26, TOR = 27, BOOLEAN_CONSTANT = 28, BOOLEAN_VARIABLE = 29, 
    INT_VARIABLE = 30, CONST_SUFFIX = 31, FLOAT_CONSTANT = 32, FLOAT_VARIABLE = 33, 
    LCURLY = 34, RCURLY = 35, LSQUARED = 36, RSQUARED = 37, LROUND = 38, 
    RROUND = 39, SINTEGER = 40, UINTEGER = 41, FLOAT = 42, GCC_BINARY = 43, 
    HEX = 44, VERILOG_BINARY = 45, FVL = 46, SINGLE_QUOTE = 47, PLUS = 48, 
    MINUS = 49, TIMES = 50, DIV = 51, GT = 52, GE = 53, LT = 54, LE = 55, 
    EQ = 56, NEQ = 57, BAND = 58, BOR = 59, BXOR = 60, NEG = 61, LSHIFT = 62, 
    RSHIFT = 63, AND = 64, OR = 65, NOT = 66, COL = 67, DCOL = 68, DOLLAR = 69, 
    RANGE = 70, CLS_TYPE = 71, WS = 72
  };

  explicit temporalLexer(antlr4::CharStream *input);

  ~temporalLexer() override;


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

