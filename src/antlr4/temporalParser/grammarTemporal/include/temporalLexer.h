
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
    RROUND = 39, INSIDE = 40, FUNCTION = 41, SINTEGER = 42, UINTEGER = 43, 
    FLOAT = 44, GCC_BINARY = 45, HEX = 46, VERILOG_BINARY = 47, FVL = 48, 
    SINGLE_QUOTE = 49, PLUS = 50, MINUS = 51, TIMES = 52, DIV = 53, GT = 54, 
    GE = 55, LT = 56, LE = 57, EQ = 58, NEQ = 59, BAND = 60, BOR = 61, BXOR = 62, 
    NEG = 63, LSHIFT = 64, RSHIFT = 65, AND = 66, OR = 67, NOT = 68, COL = 69, 
    DCOL = 70, DOLLAR = 71, RANGE = 72, CLS_TYPE = 73, WS = 74
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

