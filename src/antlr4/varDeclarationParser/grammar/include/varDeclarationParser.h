
// Generated from varDeclaration.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  varDeclarationParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, Name = 2, VARTYPE = 3, WS = 4, BOOLEAN_CONSTANT = 5, BOOLEAN_VARIABLE = 6, 
    INT_VARIABLE = 7, CONST_SUFFIX = 8, LOGIC_VARIABLE = 9, BIT_VARIABLE = 10, 
    FLOAT_CONSTANT = 11, FLOAT_VARIABLE = 12, SUBSTR = 13, STRING_CONSTANT = 14, 
    STRING_VARIABLE = 15, LCURLY = 16, RCURLY = 17, LSQUARED = 18, RSQUARED = 19, 
    LROUND = 20, RROUND = 21, INSIDE = 22, FUNCTION = 23, UINTEGER = 24, 
    FLOAT = 25, GCC_BINARY = 26, HEX = 27, VERILOG_BASED = 28, FILL_LITERAL = 29, 
    SINGLE_QUOTE = 30, PLUS = 31, MINUS = 32, TIMES = 33, DIV = 34, GT = 35, 
    GE = 36, LT = 37, LE = 38, EQ = 39, NEQ = 40, CASE_EQ = 41, CASE_NEQ = 42, 
    QUESTION = 43, BAND = 44, BOR = 45, BXOR = 46, NEG = 47, ALSHIFT = 48, 
    ARSHIFT = 49, LSHIFT = 50, RSHIFT = 51, AND = 52, OR = 53, NOT = 54, 
    COL = 55, DCOL = 56, DOLLAR = 57, RANGE = 58, CLS_TYPE = 59
  };

  enum {
    RuleFile = 0, RuleVarDec = 1, RuleStartBoolean = 2, RuleStartInt = 3, 
    RuleStartLogic = 4, RuleStartFloat = 5, RuleStartString = 6, RuleBooleanTernary = 7, 
    RuleNumericTernary = 8, RuleBoolean = 9, RuleBooleanAtom = 10, RuleNumeric = 11, 
    RuleConcatenation = 12, RuleConcatItem = 13, RuleRange = 14, RuleSm_range = 15, 
    RuleMin_dollar = 16, RuleMax_dollar = 17, RuleSm_constant = 18, RuleIntAtom = 19, 
    RuleInt_constant = 20, RuleLogicAtom = 21, RuleLogic_constant = 22, 
    RuleFloatAtom = 23, RuleString = 24, RuleStringAtom = 25, RuleNonTemporalFunction = 26, 
    RulePfunc_arg = 27, RuleRelop = 28, RuleCls_op = 29
  };

  explicit varDeclarationParser(antlr4::TokenStream *input);

  varDeclarationParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~varDeclarationParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class FileContext;
  class VarDecContext;
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

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarDecContext *varDec();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FileContext* file();

  class  VarDecContext : public antlr4::ParserRuleContext {
  public:
    VarDecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARTYPE();
    antlr4::tree::TerminalNode *Name();
    RangeContext *range();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarDecContext* varDec();

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
    antlr4::Token *eqop = nullptr;
    antlr4::Token *booleanop = nullptr;
    BooleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BooleanAtomContext *booleanAtom();
    NonTemporalFunctionContext *nonTemporalFunction();
    std::vector<StringContext *> string();
    StringContext* string(size_t i);
    RelopContext *relop();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *LROUND();
    std::vector<BooleanContext *> boolean();
    BooleanContext* boolean(size_t i);
    antlr4::tree::TerminalNode *RROUND();
    NumericContext *numeric();
    BooleanTernaryContext *booleanTernary();
    antlr4::tree::TerminalNode *NOT();
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
    antlr4::Token *unop = nullptr;
    antlr4::Token *artop = nullptr;
    antlr4::Token *logop = nullptr;
    antlr4::Token *eqop = nullptr;
    NumericContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NumericContext *> numeric();
    NumericContext* numeric(size_t i);
    antlr4::tree::TerminalNode *NEG();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *PLUS();
    NonTemporalFunctionContext *nonTemporalFunction();
    IntAtomContext *intAtom();
    LogicAtomContext *logicAtom();
    FloatAtomContext *floatAtom();
    ConcatenationContext *concatenation();
    antlr4::tree::TerminalNode *LROUND();
    antlr4::tree::TerminalNode *RROUND();
    NumericTernaryContext *numericTernary();
    BooleanContext *boolean();
    antlr4::tree::TerminalNode *TIMES();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *LSHIFT();
    antlr4::tree::TerminalNode *RSHIFT();
    antlr4::tree::TerminalNode *ALSHIFT();
    antlr4::tree::TerminalNode *ARSHIFT();
    RelopContext *relop();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *CASE_EQ();
    antlr4::tree::TerminalNode *CASE_NEQ();
    antlr4::tree::TerminalNode *BAND();
    antlr4::tree::TerminalNode *BXOR();
    antlr4::tree::TerminalNode *BOR();
    RangeContext *range();
    antlr4::tree::TerminalNode *INSIDE();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    std::vector<Sm_constantContext *> sm_constant();
    Sm_constantContext* sm_constant(size_t i);
    std::vector<Sm_rangeContext *> sm_range();
    Sm_rangeContext* sm_range(size_t i);

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
    std::vector<antlr4::tree::TerminalNode *> UINTEGER();
    antlr4::tree::TerminalNode* UINTEGER(size_t i);
    antlr4::tree::TerminalNode *RSQUARED();
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
    antlr4::tree::TerminalNode *UINTEGER();
    antlr4::tree::TerminalNode *CONST_SUFFIX();
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

