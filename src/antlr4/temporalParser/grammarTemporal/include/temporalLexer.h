
// Generated from temporal.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  temporalLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    PLACEHOLDER = 8, DT_AND = 9, EVENTUALLY = 10, ALWAYS = 11, NEXT = 12, 
    UNTIL = 13, RELEASE = 14, DOTS = 15, IMPL = 16, IMPLO = 17, IFF = 18, 
    SEREIMPL = 19, SEREIMPLO = 20, ASS = 21, DELAY = 22, SCOL = 23, FIRST_MATCH = 24, 
    TNOT = 25, TAND = 26, INTERSECT = 27, TOR = 28, BOOLEAN_CONSTANT = 29, 
    BOOLEAN_VARIABLE = 30, INT_VARIABLE = 31, CONST_SUFFIX = 32, LOGIC_VARIABLE = 33, 
    FLOAT_CONSTANT = 34, FLOAT_VARIABLE = 35, SUBSTR = 36, STRING_CONSTANT = 37, 
    STRING_VARIABLE = 38, LCURLY = 39, RCURLY = 40, LSQUARED = 41, RSQUARED = 42, 
    LROUND = 43, RROUND = 44, INSIDE = 45, FUNCTION = 46, SINTEGER = 47, 
    UINTEGER = 48, FLOAT = 49, GCC_BINARY = 50, HEX = 51, VERILOG_BINARY = 52, 
    FVL = 53, SINGLE_QUOTE = 54, PLUS = 55, MINUS = 56, TIMES = 57, DIV = 58, 
    GT = 59, GE = 60, LT = 61, LE = 62, EQ = 63, NEQ = 64, BAND = 65, BOR = 66, 
    BXOR = 67, NEG = 68, LSHIFT = 69, RSHIFT = 70, AND = 71, OR = 72, NOT = 73, 
    COL = 74, DCOL = 75, DOLLAR = 76, RANGE = 77, CLS_TYPE = 78, WS = 79
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

