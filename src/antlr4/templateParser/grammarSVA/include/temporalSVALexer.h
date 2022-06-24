
// Generated from temporalSVA.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  temporalSVALexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, BDT_AND = 10, SEP = 11, EVENTUALLY = 12, ALWAYS = 13, 
    NEXT = 14, UNTIL = 15, RELEASE = 16, DOTS = 17, IMPL = 18, IMPL2 = 19, 
    IFF = 20, XOR = 21, BIND1 = 22, BIND2 = 23, ASS = 24, DELAY = 25, SCOL = 26, 
    COL = 27, FIRST_MATCH = 28, SIGN = 29, LGPAREN = 30, RGPAREN = 31, LCPAREN = 32, 
    RCPAREN = 33, LPAREN = 34, RPAREN = 35, VARIABLE = 36, INDEX = 37, NUMERIC = 38, 
    VERILOG_BINARY = 39, GCC_BINARY = 40, HEX = 41, BOOLEAN = 42, PLUS = 43, 
    MINUS = 44, TIMES = 45, DIV = 46, GT = 47, GE = 48, LT = 49, LE = 50, 
    EQ = 51, NEQ = 52, BAND = 53, BOR = 54, BXOR = 55, NEG = 56, LSHIFT = 57, 
    RSHIFT = 58, AND = 59, OR = 60, NOT = 61, WS = 62
  };

  explicit temporalSVALexer(antlr4::CharStream *input);
  ~temporalSVALexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

