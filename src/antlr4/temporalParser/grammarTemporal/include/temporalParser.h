
#include <string>
// Forward declaration
bool isUnary(const std::string& token);
bool isSharedOperator(const std::string& token);
bool canUseSharedOperator(const std::string& unaryOp, const std::string& sharedOp);
bool canTakeThisNot(const std::string& unaryOp, const std::string& ph);


// Generated from temporal.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  temporalParser : public antlr4::Parser {
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

  enum {
    RuleFormula = 0, RuleSva_assert = 1, RuleImplication = 2, RuleSere = 3, 
    RuleBooleanLayer = 4, RuleTformula = 5, RuleTemporalFunction = 6, RuleTfunc_arg = 7, 
    RulePlaceholder_domain = 8, RuleDt_next = 9, RuleDt_next_and = 10, RuleDt_ncreps = 11, 
    RuleStartBoolean = 12, RuleStartInt = 13, RuleStartLogic = 14, RuleStartFloat = 15, 
    RuleStartString = 16, RuleBoolean = 17, RuleBooleanAtom = 18, RuleNumeric = 19, 
    RuleRange = 20, RuleSm_range = 21, RuleMin_dollar = 22, RuleMax_dollar = 23, 
    RuleSm_constant = 24, RuleIntAtom = 25, RuleInt_constant = 26, RuleLogicAtom = 27, 
    RuleLogic_constant = 28, RuleFloatAtom = 29, RuleString = 30, RuleStringAtom = 31, 
    RuleNonTemporalFunction = 32, RulePfunc_arg = 33, RuleRelop = 34, RuleCls_op = 35
  };

  explicit temporalParser(antlr4::TokenStream *input);

  temporalParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~temporalParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  // Definition
  bool isUnary(const std::string& token){
  return token=="X" || token=="nexttime" || token=="F" || token=="eventually" || token=="!" || token=="not";
  }
  bool isSharedOperator(const std::string& token){
  return token=="and" || token=="&&" || token=="or" || token=="||" || token=="|";
  }
  bool canUseSharedOperator(const std::string& unaryOp, const std::string& sharedOp){
  return !(isSharedOperator(sharedOp) && isUnary(unaryOp));
  }

  bool canTakeThisNot(const std::string& unaryOp, const std::string& ph){
  return !(unaryOp=="!" && ph[0]=='P');
  }



  class FormulaContext;
  class Sva_assertContext;
  class ImplicationContext;
  class SereContext;
  class BooleanLayerContext;
  class TformulaContext;
  class TemporalFunctionContext;
  class Tfunc_argContext;
  class Placeholder_domainContext;
  class Dt_nextContext;
  class Dt_next_andContext;
  class Dt_ncrepsContext;
  class StartBooleanContext;
  class StartIntContext;
  class StartLogicContext;
  class StartFloatContext;
  class StartStringContext;
  class BooleanContext;
  class BooleanAtomContext;
  class NumericContext;
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

  class  FormulaContext : public antlr4::ParserRuleContext {
  public:
    FormulaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ALWAYS();
    antlr4::tree::TerminalNode *LROUND();
    ImplicationContext *implication();
    antlr4::tree::TerminalNode *RROUND();
    antlr4::tree::TerminalNode *EOF();
    Sva_assertContext *sva_assert();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FormulaContext* formula();

  class  Sva_assertContext : public antlr4::ParserRuleContext {
  public:
    Sva_assertContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LROUND();
    Sva_assertContext *sva_assert();
    antlr4::tree::TerminalNode *RROUND();
    BooleanContext *boolean();
    ImplicationContext *implication();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Sva_assertContext* sva_assert();

  class  ImplicationContext : public antlr4::ParserRuleContext {
  public:
    ImplicationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TformulaContext *> tformula();
    TformulaContext* tformula(size_t i);
    antlr4::tree::TerminalNode *IMPL();
    antlr4::tree::TerminalNode *IMPLO();
    SereContext *sere();
    antlr4::tree::TerminalNode *SEREIMPL();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    antlr4::tree::TerminalNode *SEREIMPLO();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImplicationContext* implication();

  class  SereContext : public antlr4::ParserRuleContext {
  public:
    SereContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FIRST_MATCH();
    antlr4::tree::TerminalNode *LROUND();
    std::vector<SereContext *> sere();
    SereContext* sere(size_t i);
    antlr4::tree::TerminalNode *RROUND();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    BooleanLayerContext *booleanLayer();
    antlr4::tree::TerminalNode *LSQUARED();
    antlr4::tree::TerminalNode *ASS();
    antlr4::tree::TerminalNode *RSQUARED();
    std::vector<antlr4::tree::TerminalNode *> UINTEGER();
    antlr4::tree::TerminalNode* UINTEGER(size_t i);
    antlr4::tree::TerminalNode *DOTS();
    antlr4::tree::TerminalNode *COL();
    antlr4::tree::TerminalNode *DOLLAR();
    antlr4::tree::TerminalNode *IMPLO();
    Dt_ncrepsContext *dt_ncreps();
    Placeholder_domainContext *placeholder_domain();
    antlr4::tree::TerminalNode *DT_AND();
    antlr4::tree::TerminalNode *DELAY();
    Dt_nextContext *dt_next();
    Dt_next_andContext *dt_next_and();
    antlr4::tree::TerminalNode *BAND();
    antlr4::tree::TerminalNode *TAND();
    antlr4::tree::TerminalNode *INTERSECT();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *TOR();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *BOR();
    antlr4::tree::TerminalNode *SCOL();
    antlr4::tree::TerminalNode *TIMES();
    antlr4::tree::TerminalNode *PLUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SereContext* sere();
  SereContext* sere(int precedence);
  class  BooleanLayerContext : public antlr4::ParserRuleContext {
  public:
    BooleanLayerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LROUND();
    BooleanLayerContext *booleanLayer();
    antlr4::tree::TerminalNode *RROUND();
    BooleanContext *boolean();
    antlr4::tree::TerminalNode *PLACEHOLDER();
    antlr4::tree::TerminalNode *NOT();
    Placeholder_domainContext *placeholder_domain();
    TemporalFunctionContext *temporalFunction();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BooleanLayerContext* booleanLayer();

  class  TformulaContext : public antlr4::ParserRuleContext {
  public:
    TformulaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LROUND();
    std::vector<TformulaContext *> tformula();
    TformulaContext* tformula(size_t i);
    antlr4::tree::TerminalNode *RROUND();
    SereContext *sere();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    antlr4::tree::TerminalNode *TNOT();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *NEXT();
    antlr4::tree::TerminalNode *LSQUARED();
    antlr4::tree::TerminalNode *UINTEGER();
    antlr4::tree::TerminalNode *RSQUARED();
    antlr4::tree::TerminalNode *EVENTUALLY();
    antlr4::tree::TerminalNode *DT_AND();
    Placeholder_domainContext *placeholder_domain();
    BooleanLayerContext *booleanLayer();
    antlr4::tree::TerminalNode *UNTIL();
    antlr4::tree::TerminalNode *RELEASE();
    antlr4::tree::TerminalNode *TAND();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *TOR();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *BOR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TformulaContext* tformula();
  TformulaContext* tformula(int precedence);
  class  TemporalFunctionContext : public antlr4::ParserRuleContext {
  public:
    TemporalFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LROUND();
    TemporalFunctionContext *temporalFunction();
    antlr4::tree::TerminalNode *RROUND();
    antlr4::tree::TerminalNode *FUNCTION();
    std::vector<Tfunc_argContext *> tfunc_arg();
    Tfunc_argContext* tfunc_arg(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TemporalFunctionContext* temporalFunction();

  class  Tfunc_argContext : public antlr4::ParserRuleContext {
  public:
    Tfunc_argContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLACEHOLDER();
    antlr4::tree::TerminalNode *LROUND();
    Placeholder_domainContext *placeholder_domain();
    antlr4::tree::TerminalNode *RROUND();
    antlr4::tree::TerminalNode *UINTEGER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Tfunc_argContext* tfunc_arg();

  class  Placeholder_domainContext : public antlr4::ParserRuleContext {
  public:
    Placeholder_domainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> UINTEGER();
    antlr4::tree::TerminalNode* UINTEGER(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Placeholder_domainContext* placeholder_domain();

  class  Dt_nextContext : public antlr4::ParserRuleContext {
  public:
    Dt_nextContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UINTEGER();
    antlr4::tree::TerminalNode *DOTS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Dt_nextContext* dt_next();

  class  Dt_next_andContext : public antlr4::ParserRuleContext {
  public:
    Dt_next_andContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UINTEGER();
    antlr4::tree::TerminalNode *BAND();
    antlr4::tree::TerminalNode *DOTS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Dt_next_andContext* dt_next_and();

  class  Dt_ncrepsContext : public antlr4::ParserRuleContext {
  public:
    Dt_ncrepsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UINTEGER();
    antlr4::tree::TerminalNode *DOTS();
    antlr4::tree::TerminalNode *IMPLO();
    antlr4::tree::TerminalNode *ASS();
    antlr4::tree::TerminalNode *COL();
    antlr4::tree::TerminalNode *SCOL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Dt_ncrepsContext* dt_ncreps();

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

  class  StartLogicContext : public antlr4::ParserRuleContext {
  public:
    StartLogicContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericContext *numeric();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StartLogicContext* startLogic();

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
    std::vector<StringContext *> string();
    StringContext* string(size_t i);
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
    NonTemporalFunctionContext *nonTemporalFunction();
    IntAtomContext *intAtom();
    LogicAtomContext *logicAtom();
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

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogicAtomContext* logicAtom();

  class  Logic_constantContext : public antlr4::ParserRuleContext {
  public:
    Logic_constantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VERILOG_BINARY();
    antlr4::tree::TerminalNode *UINTEGER();

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

  bool sereSempred(SereContext *_localctx, size_t predicateIndex);
  bool tformulaSempred(TformulaContext *_localctx, size_t predicateIndex);
  bool booleanSempred(BooleanContext *_localctx, size_t predicateIndex);
  bool numericSempred(NumericContext *_localctx, size_t predicateIndex);
  bool stringSempred(StringContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

