
// Generated from proposition.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  propositionParser : public antlr4::Parser {
public:
  enum {
    BOOLEAN_CONSTANT = 1, BOOLEAN_VARIABLE = 2, INT_VARIABLE = 3, CONST_SUFFIX = 4, 
    FLOAT_CONSTANT = 5, FLOAT_VARIABLE = 6, LCURLY = 7, RCURLY = 8, LSQUARED = 9, 
    RSQUARED = 10, LROUND = 11, RROUND = 12, SINTEGER = 13, UINTEGER = 14, 
    FLOAT = 15, GCC_BINARY = 16, HEX = 17, VERILOG_BINARY = 18, FVL = 19, 
    SINGLE_QUOTE = 20, PLUS = 21, MINUS = 22, TIMES = 23, DIV = 24, GT = 25, 
    GE = 26, LT = 27, LE = 28, EQ = 29, NEQ = 30, BAND = 31, BOR = 32, BXOR = 33, 
    NEG = 34, LSHIFT = 35, RSHIFT = 36, AND = 37, OR = 38, NOT = 39, COL = 40, 
    DCOL = 41, DOLLAR = 42, RANGE = 43, CLS_TYPE = 44, WS = 45
  };

  enum {
    RuleStartBoolean = 0, RuleStartInt = 1, RuleStartFloat = 2, RuleBoolean = 3, 
    RuleBooleanAtom = 4, RuleNumeric = 5, RuleRange = 6, RuleIntAtom = 7, 
    RuleInt_constant = 8, RuleFloatAtom = 9, RuleRelop = 10, RuleCls_op = 11
  };

  explicit propositionParser(antlr4::TokenStream *input);

  propositionParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~propositionParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class StartBooleanContext;
  class StartIntContext;
  class StartFloatContext;
  class BooleanContext;
  class BooleanAtomContext;
  class NumericContext;
  class RangeContext;
  class IntAtomContext;
  class Int_constantContext;
  class FloatAtomContext;
  class RelopContext;
  class Cls_opContext; 

  class  StartBooleanContext : public antlr4::ParserRuleContext {
  public:
    StartBooleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BooleanContext *boolean();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartBooleanContext* startBoolean();

  class  StartIntContext : public antlr4::ParserRuleContext {
  public:
    StartIntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericContext *numeric();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartIntContext* startInt();

  class  StartFloatContext : public antlr4::ParserRuleContext {
  public:
    StartFloatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericContext *numeric();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartFloatContext* startFloat();

  class  BooleanContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *booleanop = nullptr;
    BooleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOT();
    std::vector<BooleanContext *> boolean();
    BooleanContext* boolean(size_t i);
    std::vector<NumericContext *> numeric();
    NumericContext* numeric(size_t i);
    RelopContext *relop();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    BooleanAtomContext *booleanAtom();
    antlr4::tree::TerminalNode *LROUND();
    antlr4::tree::TerminalNode *RROUND();
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
    antlr4::tree::TerminalNode *BOOLEAN_CONSTANT();
    antlr4::tree::TerminalNode *BOOLEAN_VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BooleanAtomContext* booleanAtom();

  class  NumericContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *artop = nullptr;
    antlr4::Token *logop = nullptr;
    NumericContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEG();
    std::vector<NumericContext *> numeric();
    NumericContext* numeric(size_t i);
    IntAtomContext *intAtom();
    FloatAtomContext *floatAtom();
    antlr4::tree::TerminalNode *LROUND();
    antlr4::tree::TerminalNode *RROUND();
    antlr4::tree::TerminalNode *TIMES();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *LSHIFT();
    antlr4::tree::TerminalNode *RSHIFT();
    antlr4::tree::TerminalNode *BAND();
    antlr4::tree::TerminalNode *BXOR();
    antlr4::tree::TerminalNode *BOR();
    RangeContext *range();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericContext* numeric();
  NumericContext* numeric(int precedence);
  class  RangeContext : public antlr4::ParserRuleContext {
  public:
    RangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LSQUARED();
    antlr4::tree::TerminalNode *RSQUARED();
    std::vector<antlr4::tree::TerminalNode *> SINTEGER();
    antlr4::tree::TerminalNode* SINTEGER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> UINTEGER();
    antlr4::tree::TerminalNode* UINTEGER(size_t i);
    antlr4::tree::TerminalNode *COL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RangeContext* range();

  class  IntAtomContext : public antlr4::ParserRuleContext {
  public:
    IntAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Int_constantContext *int_constant();
    antlr4::tree::TerminalNode *INT_VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IntAtomContext* intAtom();

  class  Int_constantContext : public antlr4::ParserRuleContext {
  public:
    Int_constantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GCC_BINARY();
    antlr4::tree::TerminalNode *SINTEGER();
    antlr4::tree::TerminalNode *CONST_SUFFIX();
    antlr4::tree::TerminalNode *UINTEGER();
    antlr4::tree::TerminalNode *VERILOG_BINARY();
    antlr4::tree::TerminalNode *HEX();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Int_constantContext* int_constant();

  class  FloatAtomContext : public antlr4::ParserRuleContext {
  public:
    FloatAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLOAT_CONSTANT();
    antlr4::tree::TerminalNode *FLOAT_VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FloatAtomContext* floatAtom();

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

  class  Cls_opContext : public antlr4::ParserRuleContext {
  public:
    Cls_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RANGE();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *EQ();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Cls_opContext* cls_op();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool booleanSempred(BooleanContext *_localctx, size_t predicateIndex);
  bool numericSempred(NumericContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

