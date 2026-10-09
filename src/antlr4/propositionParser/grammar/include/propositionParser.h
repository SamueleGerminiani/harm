
// Generated from proposition.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  propositionParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, BOOLEAN_CONSTANT = 2, BOOLEAN_VARIABLE = 3, INT_VARIABLE = 4, 
    CONST_SUFFIX = 5, LOGIC_VARIABLE = 6, BIT_VARIABLE = 7, FLOAT_CONSTANT = 8, 
    FLOAT_VARIABLE = 9, SUBSTR = 10, STRING_CONSTANT = 11, STRING_VARIABLE = 12, 
    LCURLY = 13, RCURLY = 14, LSQUARED = 15, RSQUARED = 16, LROUND = 17, 
    RROUND = 18, INSIDE = 19, FUNCTION = 20, SINTEGER = 21, UINTEGER = 22, 
    FLOAT = 23, GCC_BINARY = 24, HEX = 25, VERILOG_BASED = 26, FILL_LITERAL = 27, 
    SINGLE_QUOTE = 28, PLUS = 29, MINUS = 30, TIMES = 31, DIV = 32, GT = 33, 
    GE = 34, LT = 35, LE = 36, EQ = 37, NEQ = 38, CASE_EQ = 39, CASE_NEQ = 40, 
    QUESTION = 41, BAND = 42, BOR = 43, BXOR = 44, NEG = 45, LSHIFT = 46, 
    RSHIFT = 47, AND = 48, OR = 49, NOT = 50, COL = 51, DCOL = 52, DOLLAR = 53, 
    RANGE = 54, CLS_TYPE = 55, WS = 56
  };

  enum {
    RuleStartBoolean = 0, RuleStartInt = 1, RuleStartLogic = 2, RuleStartFloat = 3, 
    RuleStartString = 4, RuleBooleanTernary = 5, RuleNumericTernary = 6, 
    RuleBoolean = 7, RuleBooleanAtom = 8, RuleNumeric = 9, RuleConcatenation = 10, 
    RuleConcatItem = 11, RuleRange = 12, RuleSm_range = 13, RuleMin_dollar = 14, 
    RuleMax_dollar = 15, RuleSm_constant = 16, RuleIntAtom = 17, RuleInt_constant = 18, 
    RuleLogicAtom = 19, RuleLogic_constant = 20, RuleFloatAtom = 21, RuleString = 22, 
    RuleStringAtom = 23, RuleNonTemporalFunction = 24, RulePfunc_arg = 25, 
    RuleRelop = 26, RuleCls_op = 27
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
  class StartLogicContext;
  class StartFloatContext;
  class StartStringContext;
  class BooleanTernaryContext;
  class NumericTernaryContext;
  class BooleanContext;
  class BooleanAtomContext;
  class NumericContext;
  class ConcatenationContext;
  class ConcatItemContext;
  class RangeContext;
  class Sm_rangeContext;
  class Min_dollarContext;
  class Max_dollarContext;
  class Sm_constantContext;
  class IntAtomContext;
  class Int_constantContext;
  class LogicAtomContext;
  class Logic_constantContext;
  class FloatAtomContext;
  class StringContext;
  class StringAtomContext;
  class NonTemporalFunctionContext;
  class Pfunc_argContext;
  class RelopContext;
  class Cls_opContext; 

  class  StartBooleanContext : public antlr4::ParserRuleContext {
  public:
    StartBooleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    BooleanContext *boolean();
    BooleanTernaryContext *booleanTernary();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartBooleanContext* startBoolean();

  class  StartIntContext : public antlr4::ParserRuleContext {
  public:
    StartIntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    NumericContext *numeric();
    NumericTernaryContext *numericTernary();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartIntContext* startInt();

  class  StartLogicContext : public antlr4::ParserRuleContext {
  public:
    StartLogicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    NumericContext *numeric();
    NumericTernaryContext *numericTernary();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartLogicContext* startLogic();

  class  StartFloatContext : public antlr4::ParserRuleContext {
  public:
    StartFloatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    NumericContext *numeric();
    NumericTernaryContext *numericTernary();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartFloatContext* startFloat();

  class  StartStringContext : public antlr4::ParserRuleContext {
  public:
    StartStringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringContext *string();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartStringContext* startString();

  class  BooleanTernaryContext : public antlr4::ParserRuleContext {
  public:
    BooleanTernaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BooleanContext *> boolean();
    BooleanContext* boolean(size_t i);
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *COL();
    std::vector<BooleanTernaryContext *> booleanTernary();
    BooleanTernaryContext* booleanTernary(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BooleanTernaryContext* booleanTernary();

  class  NumericTernaryContext : public antlr4::ParserRuleContext {
  public:
    NumericTernaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BooleanContext *boolean();
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *COL();
    std::vector<NumericContext *> numeric();
    NumericContext* numeric(size_t i);
    std::vector<NumericTernaryContext *> numericTernary();
    NumericTernaryContext* numericTernary(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericTernaryContext* numericTernary();

  class  BooleanContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *booleanop = nullptr;
    BooleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOT();
    std::vector<BooleanContext *> boolean();
    BooleanContext* boolean(size_t i);
    NonTemporalFunctionContext *nonTemporalFunction();
    std::vector<NumericContext *> numeric();
    NumericContext* numeric(size_t i);
    antlr4::tree::TerminalNode *INSIDE();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    std::vector<Sm_constantContext *> sm_constant();
    Sm_constantContext* sm_constant(size_t i);
    std::vector<Sm_rangeContext *> sm_range();
    Sm_rangeContext* sm_range(size_t i);
    RelopContext *relop();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *CASE_EQ();
    antlr4::tree::TerminalNode *CASE_NEQ();
    std::vector<StringContext *> string();
    StringContext* string(size_t i);
    BooleanAtomContext *booleanAtom();
    antlr4::tree::TerminalNode *LROUND();
    antlr4::tree::TerminalNode *RROUND();
    BooleanTernaryContext *booleanTernary();
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
    NonTemporalFunctionContext *nonTemporalFunction();
    IntAtomContext *intAtom();
    LogicAtomContext *logicAtom();
    FloatAtomContext *floatAtom();
    ConcatenationContext *concatenation();
    antlr4::tree::TerminalNode *LROUND();
    antlr4::tree::TerminalNode *RROUND();
    NumericTernaryContext *numericTernary();
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
  class  ConcatenationContext : public antlr4::ParserRuleContext {
  public:
    ConcatenationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> LCURLY();
    antlr4::tree::TerminalNode* LCURLY(size_t i);
    std::vector<ConcatItemContext *> concatItem();
    ConcatItemContext* concatItem(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RCURLY();
    antlr4::tree::TerminalNode* RCURLY(size_t i);
    antlr4::tree::TerminalNode *UINTEGER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConcatenationContext* concatenation();

  class  ConcatItemContext : public antlr4::ParserRuleContext {
  public:
    ConcatItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericContext *numeric();
    BooleanAtomContext *booleanAtom();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConcatItemContext* concatItem();

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

  class  Sm_rangeContext : public antlr4::ParserRuleContext {
  public:
    Sm_rangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LSQUARED();
    antlr4::tree::TerminalNode *COL();
    antlr4::tree::TerminalNode *RSQUARED();
    std::vector<NumericContext *> numeric();
    NumericContext* numeric(size_t i);
    Min_dollarContext *min_dollar();
    Max_dollarContext *max_dollar();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Sm_rangeContext* sm_range();

  class  Min_dollarContext : public antlr4::ParserRuleContext {
  public:
    Min_dollarContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOLLAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Min_dollarContext* min_dollar();

  class  Max_dollarContext : public antlr4::ParserRuleContext {
  public:
    Max_dollarContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOLLAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Max_dollarContext* max_dollar();

  class  Sm_constantContext : public antlr4::ParserRuleContext {
  public:
    Sm_constantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericContext *numeric();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Sm_constantContext* sm_constant();

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
    antlr4::tree::TerminalNode *HEX();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Int_constantContext* int_constant();

  class  LogicAtomContext : public antlr4::ParserRuleContext {
  public:
    LogicAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Logic_constantContext *logic_constant();
    Int_constantContext *int_constant();
    antlr4::tree::TerminalNode *LOGIC_VARIABLE();
    antlr4::tree::TerminalNode *BIT_VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicAtomContext* logicAtom();

  class  Logic_constantContext : public antlr4::ParserRuleContext {
  public:
    Logic_constantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VERILOG_BASED();
    antlr4::tree::TerminalNode *UINTEGER();
    antlr4::tree::TerminalNode *FILL_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Logic_constantContext* logic_constant();

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

  class  StringContext : public antlr4::ParserRuleContext {
  public:
    StringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringAtomContext *stringAtom();
    antlr4::tree::TerminalNode *LROUND();
    std::vector<StringContext *> string();
    StringContext* string(size_t i);
    antlr4::tree::TerminalNode *RROUND();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *SUBSTR();
    std::vector<antlr4::tree::TerminalNode *> UINTEGER();
    antlr4::tree::TerminalNode* UINTEGER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StringContext* string();
  StringContext* string(int precedence);
  class  StringAtomContext : public antlr4::ParserRuleContext {
  public:
    StringAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_CONSTANT();
    antlr4::tree::TerminalNode *STRING_VARIABLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StringAtomContext* stringAtom();

  class  NonTemporalFunctionContext : public antlr4::ParserRuleContext {
  public:
    NonTemporalFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNCTION();
    antlr4::tree::TerminalNode *LROUND();
    std::vector<Pfunc_argContext *> pfunc_arg();
    Pfunc_argContext* pfunc_arg(size_t i);
    antlr4::tree::TerminalNode *RROUND();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NonTemporalFunctionContext* nonTemporalFunction();

  class  Pfunc_argContext : public antlr4::ParserRuleContext {
  public:
    Pfunc_argContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericContext *numeric();
    BooleanContext *boolean();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Pfunc_argContext* pfunc_arg();

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
  bool stringSempred(StringContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

