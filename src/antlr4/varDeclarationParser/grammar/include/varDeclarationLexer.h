
// Generated from varDeclaration.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  varDeclarationLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, Name = 2, VARTYPE = 3, WS = 4, BOOLEAN_CONSTANT = 5, BOOLEAN_VARIABLE = 6, 
    INT_VARIABLE = 7, CONST_SUFFIX = 8, LOGIC_VARIABLE = 9, FLOAT_CONSTANT = 10, 
    FLOAT_VARIABLE = 11, SUBSTR = 12, STRING_CONSTANT = 13, STRING_VARIABLE = 14, 
    LCURLY = 15, RCURLY = 16, LSQUARED = 17, RSQUARED = 18, LROUND = 19, 
    RROUND = 20, INSIDE = 21, FUNCTION = 22, SINTEGER = 23, UINTEGER = 24, 
    FLOAT = 25, GCC_BINARY = 26, HEX = 27, VERILOG_BASED = 28, FILL_LITERAL = 29, 
    SINGLE_QUOTE = 30, PLUS = 31, MINUS = 32, TIMES = 33, DIV = 34, GT = 35, 
    GE = 36, LT = 37, LE = 38, EQ = 39, NEQ = 40, CASE_EQ = 41, CASE_NEQ = 42, 
    QUESTION = 43, BAND = 44, BOR = 45, BXOR = 46, NEG = 47, LSHIFT = 48, 
    RSHIFT = 49, AND = 50, OR = 51, NOT = 52, COL = 53, DCOL = 54, DOLLAR = 55, 
    RANGE = 56, CLS_TYPE = 57
  };

  explicit varDeclarationLexer(antlr4::CharStream *input);

  ~varDeclarationLexer() override;


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

