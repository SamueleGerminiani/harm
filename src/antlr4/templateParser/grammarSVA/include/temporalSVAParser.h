
// Generated from temporalSVA.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  temporalSVAParser : public antlr4::Parser {
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

  enum {
    RuleFile = 0, RuleFormula = 1, RuleSere = 2, RuleTformula = 3, RulePlaceholder = 4, 
    RuleBdt_next = 5, RuleBdt_next_and = 6, RuleBdt_NCReps = 7, RuleBoolean = 8, 
    RuleBooleanAtom = 9, RuleBooleanConstant = 10, RuleBooleanVariable = 11, 
    RuleLogic = 12, RuleLogicAtom = 13, RuleLogicConstant = 14, RuleLogicVariable = 15, 
    RuleNumeric = 16, RuleNumericAtom = 17, RuleNumericConstant = 18, RuleNumericVariable = 19, 
    RuleVariable = 20, RuleRelop = 21
  };

  explicit temporalSVAParser(antlr4::TokenStream *input);
  ~temporalSVAParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class FileContext;
  class FormulaContext;
  class SereContext;
  class TformulaContext;
  class PlaceholderContext;
  class Bdt_nextContext;
  class Bdt_next_andContext;
  class Bdt_NCRepsContext;
  class BooleanContext;
  class BooleanAtomContext;
  class BooleanConstantContext;
  class BooleanVariableContext;
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

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ALWAYS();
    FormulaContext *formula();
    antlr4::tree::TerminalNode *EOF();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FileContext* file();

  class  FormulaContext : public antlr4::ParserRuleContext {
  public:
    FormulaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TformulaContext *> tformula();
    TformulaContext* tformula(size_t i);
    antlr4::tree::TerminalNode *IMPL();
    antlr4::tree::TerminalNode *IMPL2();
    antlr4::tree::TerminalNode *LGPAREN();
    SereContext *sere();
    antlr4::tree::TerminalNode *RGPAREN();
    antlr4::tree::TerminalNode *LCPAREN();
    antlr4::tree::TerminalNode *RCPAREN();
    antlr4::tree::TerminalNode *BIND1();
    antlr4::tree::TerminalNode *BIND2();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FormulaContext* formula();

  class  SereContext : public antlr4::ParserRuleContext {
  public:
    SereContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BooleanContext *boolean();
    PlaceholderContext *placeholder();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *BDT_AND();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<SereContext *> sere();
    SereContext* sere(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *LGPAREN();
    antlr4::tree::TerminalNode *RGPAREN();
    antlr4::tree::TerminalNode *DELAY();
    std::vector<antlr4::tree::TerminalNode *> NUMERIC();
    antlr4::tree::TerminalNode* NUMERIC(size_t i);
    antlr4::tree::TerminalNode *LCPAREN();
    antlr4::tree::TerminalNode *DOTS();
    antlr4::tree::TerminalNode *RCPAREN();
    Bdt_nextContext *bdt_next();
    Bdt_next_andContext *bdt_next_and();
    Bdt_NCRepsContext *bdt_NCReps();
    antlr4::tree::TerminalNode *BOR();
    antlr4::tree::TerminalNode *BAND();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *SCOL();
    antlr4::tree::TerminalNode *COL();
    antlr4::tree::TerminalNode *TIMES();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *ASS();
    antlr4::tree::TerminalNode *IMPL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SereContext* sere();
  SereContext* sere(int precedence);
  class  TformulaContext : public antlr4::ParserRuleContext {
  public:
    TformulaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BooleanContext *boolean();
    PlaceholderContext *placeholder();
    antlr4::tree::TerminalNode *BDT_AND();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<TformulaContext *> tformula();
    TformulaContext* tformula(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *NEXT();
    antlr4::tree::TerminalNode *LCPAREN();
    antlr4::tree::TerminalNode *NUMERIC();
    antlr4::tree::TerminalNode *RCPAREN();
    antlr4::tree::TerminalNode *LGPAREN();
    SereContext *sere();
    antlr4::tree::TerminalNode *RGPAREN();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *XOR();
    antlr4::tree::TerminalNode *UNTIL();
    antlr4::tree::TerminalNode *RELEASE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TformulaContext* tformula();
  TformulaContext* tformula(int precedence);
  class  PlaceholderContext : public antlr4::ParserRuleContext {
  public:
    PlaceholderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMERIC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PlaceholderContext* placeholder();

  class  Bdt_nextContext : public antlr4::ParserRuleContext {
  public:
    Bdt_nextContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMERIC();
    antlr4::tree::TerminalNode *DOTS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Bdt_nextContext* bdt_next();

  class  Bdt_next_andContext : public antlr4::ParserRuleContext {
  public:
    Bdt_next_andContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMERIC();
    antlr4::tree::TerminalNode *BAND();
    antlr4::tree::TerminalNode *DOTS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Bdt_next_andContext* bdt_next_and();

  class  Bdt_NCRepsContext : public antlr4::ParserRuleContext {
  public:
    Bdt_NCRepsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMERIC();
    antlr4::tree::TerminalNode *RCPAREN();
    antlr4::tree::TerminalNode *SEP();
    antlr4::tree::TerminalNode *DOTS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Bdt_NCRepsContext* bdt_NCReps();

  class  BooleanContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *booleanop = nullptr;
    BooleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOT();
    std::vector<BooleanContext *> boolean();
    BooleanContext* boolean(size_t i);
    std::vector<LogicContext *> logic();
    LogicContext* logic(size_t i);
    RelopContext *relop();
    std::vector<NumericContext *> numeric();
    NumericContext* numeric(size_t i);
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    BooleanAtomContext *booleanAtom();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *OR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BooleanContext* boolean();
  BooleanContext* boolean(int precedence);
  class  BooleanAtomContext : public antlr4::ParserRuleContext {
  public:
    BooleanAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BooleanConstantContext *booleanConstant();
    BooleanVariableContext *booleanVariable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BooleanAtomContext* booleanAtom();

  class  BooleanConstantContext : public antlr4::ParserRuleContext {
  public:
    BooleanConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BOOLEAN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BooleanConstantContext* booleanConstant();

  class  BooleanVariableContext : public antlr4::ParserRuleContext {
  public:
    BooleanVariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    VariableContext *variable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BooleanVariableContext* booleanVariable();

  class  LogicContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *artop = nullptr;
    antlr4::Token *logop = nullptr;
    LogicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEG();
    std::vector<LogicContext *> logic();
    LogicContext* logic(size_t i);
    LogicAtomContext *logicAtom();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *TIMES();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *LSHIFT();
    antlr4::tree::TerminalNode *RSHIFT();
    antlr4::tree::TerminalNode *BAND();
    antlr4::tree::TerminalNode *BXOR();
    antlr4::tree::TerminalNode *BOR();
    antlr4::tree::TerminalNode *INDEX();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicContext* logic();
  LogicContext* logic(int precedence);
  class  LogicAtomContext : public antlr4::ParserRuleContext {
  public:
    LogicAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogicConstantContext *logicConstant();
    LogicVariableContext *logicVariable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicAtomContext* logicAtom();

  class  LogicConstantContext : public antlr4::ParserRuleContext {
  public:
    LogicConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VERILOG_BINARY();
    antlr4::tree::TerminalNode *GCC_BINARY();
    antlr4::tree::TerminalNode *NUMERIC();
    antlr4::tree::TerminalNode *HEX();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicConstantContext* logicConstant();

  class  LogicVariableContext : public antlr4::ParserRuleContext {
  public:
    LogicVariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    VariableContext *variable();
    antlr4::tree::TerminalNode *SIGN();
    antlr4::tree::TerminalNode *NUMERIC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicVariableContext* logicVariable();

  class  NumericContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *artop = nullptr;
    NumericContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericAtomContext *numericAtom();
    LogicContext *logic();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<NumericContext *> numeric();
    NumericContext* numeric(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *TIMES();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericContext* numeric();
  NumericContext* numeric(int precedence);
  class  NumericAtomContext : public antlr4::ParserRuleContext {
  public:
    NumericAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericConstantContext *numericConstant();
    NumericVariableContext *numericVariable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericAtomContext* numericAtom();

  class  NumericConstantContext : public antlr4::ParserRuleContext {
  public:
    NumericConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMERIC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericConstantContext* numericConstant();

  class  NumericVariableContext : public antlr4::ParserRuleContext {
  public:
    NumericVariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    VariableContext *variable();
    antlr4::tree::TerminalNode *NUMERIC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericVariableContext* numericVariable();

  class  VariableContext : public antlr4::ParserRuleContext {
  public:
    VariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableContext* variable();

  class  RelopContext : public antlr4::ParserRuleContext {
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

  RelopContext* relop();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool sereSempred(SereContext *_localctx, size_t predicateIndex);
  bool tformulaSempred(TformulaContext *_localctx, size_t predicateIndex);
  bool booleanSempred(BooleanContext *_localctx, size_t predicateIndex);
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

