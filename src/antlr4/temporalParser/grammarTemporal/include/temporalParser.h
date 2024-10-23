
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
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, PLACEHOLDER = 7, 
    DT_AND = 8, EVENTUALLY = 9, ALWAYS = 10, NEXT = 11, UNTIL = 12, RELEASE = 13, 
    DOTS = 14, IMPL = 15, IMPLO = 16, IFF = 17, SEREIMPL = 18, SEREIMPLO = 19, 
    ASS = 20, DELAY = 21, SCOL = 22, FIRST_MATCH = 23, TNOT = 24, TAND = 25, 
    INTERSECT = 26, TOR = 27, BOOLEAN_CONSTANT = 28, BOOLEAN_VARIABLE = 29, 
    INT_VARIABLE = 30, CONST_SUFFIX = 31, FLOAT_CONSTANT = 32, FLOAT_VARIABLE = 33, 
    LCURLY = 34, RCURLY = 35, LSQUARED = 36, RSQUARED = 37, LROUND = 38, 
    RROUND = 39, INSIDE = 40, FUNCTION = 41, SINTEGER = 42, UINTEGER = 43, 
    FLOAT = 44, GCC_BINARY = 45, HEX = 46, VERILOG_BINARY = 47, FVL = 48, 
    SINGLE_QUOTE = 49, PLUS = 50, MINUS = 51, TIMES = 52, DIV = 53, GT = 54, 
    GE = 55, LT = 56, LE = 57, EQ = 58, NEQ = 59, BAND = 60, BOR = 61, BXOR = 62, 
    NEG = 63, LSHIFT = 64, RSHIFT = 65, AND = 66, OR = 67, NOT = 68, COL = 69, 
    DCOL = 70, DOLLAR = 71, RANGE = 72, CLS_TYPE = 73, WS = 74
  };

  enum {
    RuleFormula = 0, RuleSva_assert = 1, RuleImplication = 2, RuleSere = 3, 
    RuleBooleanLayer = 4, RuleTformula = 5, RuleDt_next = 6, RuleDt_next_and = 7, 
    RuleDt_ncreps = 8, RuleStartBoolean = 9, RuleStartInt = 10, RuleStartFloat = 11, 
    RuleBoolean = 12, RuleBooleanAtom = 13, RuleNumeric = 14, RuleRange = 15, 
    RuleIntAtom = 16, RuleInt_constant = 17, RuleFloatAtom = 18, RuleRelop = 19, 
    RuleCls_op = 20
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
  class Dt_nextContext;
  class Dt_next_andContext;
  class Dt_ncrepsContext;
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

  bool sereSempred(SereContext *_localctx, size_t predicateIndex);
  bool tformulaSempred(TformulaContext *_localctx, size_t predicateIndex);
  bool booleanSempred(BooleanContext *_localctx, size_t predicateIndex);
  bool numericSempred(NumericContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

