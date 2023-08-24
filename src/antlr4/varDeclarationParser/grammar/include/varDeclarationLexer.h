
// Generated from varDeclaration.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  varDeclarationLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, Name = 2, VARTYPE = 3, WS = 4, BOOLEAN_CONSTANT = 5, BOOLEAN_VARIABLE = 6, 
    LOGIC_CONSTANT = 7, LOGIC_VARIABLE = 8, SIGN = 9, CONST_SUFFIX = 10, 
    NUMERIC_CONSTANT = 11, NUMERIC_VARIABLE = 12, LGPAREN = 13, RGPAREN = 14, 
    LCPAREN = 15, RCPAREN = 16, LPAREN = 17, RPAREN = 18, NUMERIC = 19, 
    VERILOG_BINARY = 20, GCC_BINARY = 21, HEX = 22, PLUS = 23, MINUS = 24, 
    TIMES = 25, DIV = 26, GT = 27, GE = 28, LT = 29, LE = 30, EQ = 31, NEQ = 32, 
    BAND = 33, BOR = 34, BXOR = 35, NEG = 36, LSHIFT = 37, RSHIFT = 38, 
    AND = 39, OR = 40, NOT = 41
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

