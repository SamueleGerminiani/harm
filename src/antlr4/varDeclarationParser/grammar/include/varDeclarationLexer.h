
// Generated from varDeclaration.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  varDeclarationLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, Name = 2, VARTYPE = 3, WS = 4, BOOLEAN_CONSTANT = 5, BOOLEAN_VARIABLE = 6, 
    INT_VARIABLE = 7, CONST_SUFFIX = 8, LOGIC_VARIABLE = 9, BIT_VARIABLE = 10, 
    FLOAT_CONSTANT = 11, FLOAT_VARIABLE = 12, SUBSTR = 13, STRING_CONSTANT = 14, 
    STRING_VARIABLE = 15, LCURLY = 16, RCURLY = 17, LSQUARED = 18, RSQUARED = 19, 
    LROUND = 20, RROUND = 21, INSIDE = 22, SIGN_CAST = 23, FUNCTION = 24, 
    UINTEGER = 25, FLOAT = 26, GCC_BINARY = 27, HEX = 28, VERILOG_BASED = 29, 
    FILL_LITERAL = 30, SINGLE_QUOTE = 31, PLUS = 32, MINUS = 33, TIMES = 34, 
    DIV = 35, GT = 36, GE = 37, LT = 38, LE = 39, EQ = 40, NEQ = 41, CASE_EQ = 42, 
    CASE_NEQ = 43, QUESTION = 44, BAND = 45, BOR = 46, BXOR = 47, NEG = 48, 
    ALSHIFT = 49, ARSHIFT = 50, LSHIFT = 51, RSHIFT = 52, AND = 53, OR = 54, 
    NOT = 55, COL = 56, DCOL = 57, DOLLAR = 58, RANGE = 59, CLS_TYPE = 60
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

