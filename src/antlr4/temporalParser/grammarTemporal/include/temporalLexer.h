
// Generated from temporal.g4 by ANTLR 4.13.2

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
    BIT_VARIABLE = 34, FLOAT_CONSTANT = 35, FLOAT_VARIABLE = 36, SUBSTR = 37, 
    STRING_CONSTANT = 38, STRING_VARIABLE = 39, LCURLY = 40, RCURLY = 41, 
    LSQUARED = 42, RSQUARED = 43, LROUND = 44, RROUND = 45, INSIDE = 46, 
    FUNCTION = 47, SINTEGER = 48, UINTEGER = 49, FLOAT = 50, GCC_BINARY = 51, 
    HEX = 52, VERILOG_BASED = 53, FILL_LITERAL = 54, SINGLE_QUOTE = 55, 
    PLUS = 56, MINUS = 57, TIMES = 58, DIV = 59, GT = 60, GE = 61, LT = 62, 
    LE = 63, EQ = 64, NEQ = 65, CASE_EQ = 66, CASE_NEQ = 67, QUESTION = 68, 
    BAND = 69, BOR = 70, BXOR = 71, NEG = 72, LSHIFT = 73, RSHIFT = 74, 
    AND = 75, OR = 76, NOT = 77, COL = 78, DCOL = 79, DOLLAR = 80, RANGE = 81, 
    CLS_TYPE = 82, WS = 83
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

