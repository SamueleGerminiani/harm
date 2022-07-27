
// Generated from metric.g4 by ANTLR 4.9.2

#pragma once

#include "antlr4-runtime.h"

class metricParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1,
    T__1 = 2,
    T__2 = 3,
    T__3 = 4,
    SIGN = 5,
    LGPAREN = 6,
    RGPAREN = 7,
    LCPAREN = 8,
    RCPAREN = 9,
    LPAREN = 10,
    RPAREN = 11,
    VARIABLE = 12,
    INDEX = 13,
    NUMERIC = 14,
    VERILOG_BINARY = 15,
    GCC_BINARY = 16,
    HEX = 17,
    BOOLEAN = 18,
    PLUS = 19,
    MINUS = 20,
    TIMES = 21,
    DIV = 22,
    GT = 23,
    GE = 24,
    LT = 25,
    LE = 26,
    EQ = 27,
    NEQ = 28,
    BAND = 29,
    BOR = 30,
    BXOR = 31,
    NEG = 32,
    LSHIFT = 33,
    RSHIFT = 34,
    AND = 35,
    OR = 36,
    NOT = 37,
    WS = 38
  };

  enum {
    RuleFile = 0,
    RuleLogic = 1,
    RuleLogicAtom = 2,
    RuleLogicConstant = 3,
    RuleLogicVariable = 4,
    RuleNumeric = 5,
    RuleNumericAtom = 6,
    RuleNumericConstant = 7,
    RuleNumericVariable = 8,
    RuleVariable = 9,
    RuleRelop = 10
  };

  explicit metricParser(antlr4::TokenStream *input);
  ~metricParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN &getATN() const override { return _atn; };
  virtual const std::vector<std::string> &getTokenNames() const override {
    return _tokenNames;
  }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string> &getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary &getVocabulary() const override;

  class FileContext;
  class LogicContext;
  class LogicAtomContext;
  class LogicConstantContext;
  class LogicVariableContext;
  class NumericContext;
  class NumericAtomContext;
  class NumericConstantContext;
  class NumericVariableContext;
  class VariableContext;
  class RelopContext;

  class FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericContext *numeric();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  FileContext *file();

  class LogicContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *logop = nullptr;
    LogicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEG();
    std::vector<LogicContext *> logic();
    LogicContext *logic(size_t i);
    LogicAtomContext *logicAtom();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *LSHIFT();
    antlr4::tree::TerminalNode *RSHIFT();
    antlr4::tree::TerminalNode *BAND();
    antlr4::tree::TerminalNode *BXOR();
    antlr4::tree::TerminalNode *BOR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  LogicContext *logic();
  LogicContext *logic(int precedence);
  class LogicAtomContext : public antlr4::ParserRuleContext {
  public:
    LogicAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogicConstantContext *logicConstant();
    LogicVariableContext *logicVariable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  LogicAtomContext *logicAtom();

  class LogicConstantContext : public antlr4::ParserRuleContext {
  public:
    LogicConstantContext(antlr4::ParserRuleContext *parent,
                         size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VERILOG_BINARY();
    antlr4::tree::TerminalNode *GCC_BINARY();
    antlr4::tree::TerminalNode *NUMERIC();
    antlr4::tree::TerminalNode *HEX();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  LogicConstantContext *logicConstant();

  class LogicVariableContext : public antlr4::ParserRuleContext {
  public:
    LogicVariableContext(antlr4::ParserRuleContext *parent,
                         size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    VariableContext *variable();
    antlr4::tree::TerminalNode *SIGN();
    antlr4::tree::TerminalNode *NUMERIC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  LogicVariableContext *logicVariable();

  class NumericContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *artop = nullptr;
    NumericContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericAtomContext *numericAtom();
    LogicContext *logic();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<NumericContext *> numeric();
    NumericContext *numeric(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *TIMES();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  NumericContext *numeric();
  NumericContext *numeric(int precedence);
  class NumericAtomContext : public antlr4::ParserRuleContext {
  public:
    NumericAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericConstantContext *numericConstant();
    NumericVariableContext *numericVariable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  NumericAtomContext *numericAtom();

  class NumericConstantContext : public antlr4::ParserRuleContext {
  public:
    NumericConstantContext(antlr4::ParserRuleContext *parent,
                           size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMERIC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  NumericConstantContext *numericConstant();

  class NumericVariableContext : public antlr4::ParserRuleContext {
  public:
    NumericVariableContext(antlr4::ParserRuleContext *parent,
                           size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    VariableContext *variable();
    antlr4::tree::TerminalNode *NUMERIC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  NumericVariableContext *numericVariable();

  class VariableContext : public antlr4::ParserRuleContext {
  public:
    VariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  VariableContext *variable();

  class RelopContext : public antlr4::ParserRuleContext {
  public:
    RelopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *LE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  RelopContext *relop();

  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex,
                       size_t predicateIndex) override;
  bool logicSempred(LogicContext *_localctx, size_t predicateIndex);
  bool numericSempred(NumericContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};
