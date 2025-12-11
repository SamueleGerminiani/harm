
// Generated from proposition.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "propositionParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by propositionParser.
 */
class  propositionListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStartBoolean(propositionParser::StartBooleanContext *ctx) = 0;
  virtual void exitStartBoolean(propositionParser::StartBooleanContext *ctx) = 0;

  virtual void enterStartInt(propositionParser::StartIntContext *ctx) = 0;
  virtual void exitStartInt(propositionParser::StartIntContext *ctx) = 0;

  virtual void enterStartLogic(propositionParser::StartLogicContext *ctx) = 0;
  virtual void exitStartLogic(propositionParser::StartLogicContext *ctx) = 0;

  virtual void enterStartFloat(propositionParser::StartFloatContext *ctx) = 0;
  virtual void exitStartFloat(propositionParser::StartFloatContext *ctx) = 0;

  virtual void enterStartString(propositionParser::StartStringContext *ctx) = 0;
  virtual void exitStartString(propositionParser::StartStringContext *ctx) = 0;

  virtual void enterBoolean(propositionParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(propositionParser::BooleanContext *ctx) = 0;

  virtual void enterBooleanAtom(propositionParser::BooleanAtomContext *ctx) = 0;
  virtual void exitBooleanAtom(propositionParser::BooleanAtomContext *ctx) = 0;

  virtual void enterNumeric(propositionParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(propositionParser::NumericContext *ctx) = 0;

  virtual void enterRange(propositionParser::RangeContext *ctx) = 0;
  virtual void exitRange(propositionParser::RangeContext *ctx) = 0;

  virtual void enterSm_range(propositionParser::Sm_rangeContext *ctx) = 0;
  virtual void exitSm_range(propositionParser::Sm_rangeContext *ctx) = 0;

  virtual void enterMin_dollar(propositionParser::Min_dollarContext *ctx) = 0;
  virtual void exitMin_dollar(propositionParser::Min_dollarContext *ctx) = 0;

  virtual void enterMax_dollar(propositionParser::Max_dollarContext *ctx) = 0;
  virtual void exitMax_dollar(propositionParser::Max_dollarContext *ctx) = 0;

  virtual void enterSm_constant(propositionParser::Sm_constantContext *ctx) = 0;
  virtual void exitSm_constant(propositionParser::Sm_constantContext *ctx) = 0;

  virtual void enterIntAtom(propositionParser::IntAtomContext *ctx) = 0;
  virtual void exitIntAtom(propositionParser::IntAtomContext *ctx) = 0;

  virtual void enterInt_constant(propositionParser::Int_constantContext *ctx) = 0;
  virtual void exitInt_constant(propositionParser::Int_constantContext *ctx) = 0;

  virtual void enterLogicAtom(propositionParser::LogicAtomContext *ctx) = 0;
  virtual void exitLogicAtom(propositionParser::LogicAtomContext *ctx) = 0;

  virtual void enterLogic_constant(propositionParser::Logic_constantContext *ctx) = 0;
  virtual void exitLogic_constant(propositionParser::Logic_constantContext *ctx) = 0;

  virtual void enterFloatAtom(propositionParser::FloatAtomContext *ctx) = 0;
  virtual void exitFloatAtom(propositionParser::FloatAtomContext *ctx) = 0;

  virtual void enterString(propositionParser::StringContext *ctx) = 0;
  virtual void exitString(propositionParser::StringContext *ctx) = 0;

  virtual void enterStringAtom(propositionParser::StringAtomContext *ctx) = 0;
  virtual void exitStringAtom(propositionParser::StringAtomContext *ctx) = 0;

  virtual void enterNonTemporalFunction(propositionParser::NonTemporalFunctionContext *ctx) = 0;
  virtual void exitNonTemporalFunction(propositionParser::NonTemporalFunctionContext *ctx) = 0;

  virtual void enterPfunc_arg(propositionParser::Pfunc_argContext *ctx) = 0;
  virtual void exitPfunc_arg(propositionParser::Pfunc_argContext *ctx) = 0;

  virtual void enterRelop(propositionParser::RelopContext *ctx) = 0;
  virtual void exitRelop(propositionParser::RelopContext *ctx) = 0;

  virtual void enterCls_op(propositionParser::Cls_opContext *ctx) = 0;
  virtual void exitCls_op(propositionParser::Cls_opContext *ctx) = 0;


};

