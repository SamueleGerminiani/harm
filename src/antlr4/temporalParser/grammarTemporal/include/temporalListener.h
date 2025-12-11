
#include <string>
// Forward declaration
bool isUnary(const std::string& token);
bool isSharedOperator(const std::string& token);
bool canUseSharedOperator(const std::string& unaryOp, const std::string& sharedOp);
bool canTakeThisNot(const std::string& unaryOp, const std::string& ph);


// Generated from temporal.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "temporalParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by temporalParser.
 */
class  temporalListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFormula(temporalParser::FormulaContext *ctx) = 0;
  virtual void exitFormula(temporalParser::FormulaContext *ctx) = 0;

  virtual void enterSva_assert(temporalParser::Sva_assertContext *ctx) = 0;
  virtual void exitSva_assert(temporalParser::Sva_assertContext *ctx) = 0;

  virtual void enterImplication(temporalParser::ImplicationContext *ctx) = 0;
  virtual void exitImplication(temporalParser::ImplicationContext *ctx) = 0;

  virtual void enterSere(temporalParser::SereContext *ctx) = 0;
  virtual void exitSere(temporalParser::SereContext *ctx) = 0;

  virtual void enterBooleanLayer(temporalParser::BooleanLayerContext *ctx) = 0;
  virtual void exitBooleanLayer(temporalParser::BooleanLayerContext *ctx) = 0;

  virtual void enterTformula(temporalParser::TformulaContext *ctx) = 0;
  virtual void exitTformula(temporalParser::TformulaContext *ctx) = 0;

  virtual void enterTemporalFunction(temporalParser::TemporalFunctionContext *ctx) = 0;
  virtual void exitTemporalFunction(temporalParser::TemporalFunctionContext *ctx) = 0;

  virtual void enterTfunc_arg(temporalParser::Tfunc_argContext *ctx) = 0;
  virtual void exitTfunc_arg(temporalParser::Tfunc_argContext *ctx) = 0;

  virtual void enterPlaceholder_domain(temporalParser::Placeholder_domainContext *ctx) = 0;
  virtual void exitPlaceholder_domain(temporalParser::Placeholder_domainContext *ctx) = 0;

  virtual void enterDt_next(temporalParser::Dt_nextContext *ctx) = 0;
  virtual void exitDt_next(temporalParser::Dt_nextContext *ctx) = 0;

  virtual void enterDt_next_and(temporalParser::Dt_next_andContext *ctx) = 0;
  virtual void exitDt_next_and(temporalParser::Dt_next_andContext *ctx) = 0;

  virtual void enterDt_ncreps(temporalParser::Dt_ncrepsContext *ctx) = 0;
  virtual void exitDt_ncreps(temporalParser::Dt_ncrepsContext *ctx) = 0;

  virtual void enterStartBoolean(temporalParser::StartBooleanContext *ctx) = 0;
  virtual void exitStartBoolean(temporalParser::StartBooleanContext *ctx) = 0;

  virtual void enterStartInt(temporalParser::StartIntContext *ctx) = 0;
  virtual void exitStartInt(temporalParser::StartIntContext *ctx) = 0;

  virtual void enterStartLogic(temporalParser::StartLogicContext *ctx) = 0;
  virtual void exitStartLogic(temporalParser::StartLogicContext *ctx) = 0;

  virtual void enterStartFloat(temporalParser::StartFloatContext *ctx) = 0;
  virtual void exitStartFloat(temporalParser::StartFloatContext *ctx) = 0;

  virtual void enterStartString(temporalParser::StartStringContext *ctx) = 0;
  virtual void exitStartString(temporalParser::StartStringContext *ctx) = 0;

  virtual void enterBoolean(temporalParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(temporalParser::BooleanContext *ctx) = 0;

  virtual void enterBooleanAtom(temporalParser::BooleanAtomContext *ctx) = 0;
  virtual void exitBooleanAtom(temporalParser::BooleanAtomContext *ctx) = 0;

  virtual void enterNumeric(temporalParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(temporalParser::NumericContext *ctx) = 0;

  virtual void enterRange(temporalParser::RangeContext *ctx) = 0;
  virtual void exitRange(temporalParser::RangeContext *ctx) = 0;

  virtual void enterSm_range(temporalParser::Sm_rangeContext *ctx) = 0;
  virtual void exitSm_range(temporalParser::Sm_rangeContext *ctx) = 0;

  virtual void enterMin_dollar(temporalParser::Min_dollarContext *ctx) = 0;
  virtual void exitMin_dollar(temporalParser::Min_dollarContext *ctx) = 0;

  virtual void enterMax_dollar(temporalParser::Max_dollarContext *ctx) = 0;
  virtual void exitMax_dollar(temporalParser::Max_dollarContext *ctx) = 0;

  virtual void enterSm_constant(temporalParser::Sm_constantContext *ctx) = 0;
  virtual void exitSm_constant(temporalParser::Sm_constantContext *ctx) = 0;

  virtual void enterIntAtom(temporalParser::IntAtomContext *ctx) = 0;
  virtual void exitIntAtom(temporalParser::IntAtomContext *ctx) = 0;

  virtual void enterInt_constant(temporalParser::Int_constantContext *ctx) = 0;
  virtual void exitInt_constant(temporalParser::Int_constantContext *ctx) = 0;

  virtual void enterLogicAtom(temporalParser::LogicAtomContext *ctx) = 0;
  virtual void exitLogicAtom(temporalParser::LogicAtomContext *ctx) = 0;

  virtual void enterLogic_constant(temporalParser::Logic_constantContext *ctx) = 0;
  virtual void exitLogic_constant(temporalParser::Logic_constantContext *ctx) = 0;

  virtual void enterFloatAtom(temporalParser::FloatAtomContext *ctx) = 0;
  virtual void exitFloatAtom(temporalParser::FloatAtomContext *ctx) = 0;

  virtual void enterString(temporalParser::StringContext *ctx) = 0;
  virtual void exitString(temporalParser::StringContext *ctx) = 0;

  virtual void enterStringAtom(temporalParser::StringAtomContext *ctx) = 0;
  virtual void exitStringAtom(temporalParser::StringAtomContext *ctx) = 0;

  virtual void enterNonTemporalFunction(temporalParser::NonTemporalFunctionContext *ctx) = 0;
  virtual void exitNonTemporalFunction(temporalParser::NonTemporalFunctionContext *ctx) = 0;

  virtual void enterPfunc_arg(temporalParser::Pfunc_argContext *ctx) = 0;
  virtual void exitPfunc_arg(temporalParser::Pfunc_argContext *ctx) = 0;

  virtual void enterRelop(temporalParser::RelopContext *ctx) = 0;
  virtual void exitRelop(temporalParser::RelopContext *ctx) = 0;

  virtual void enterCls_op(temporalParser::Cls_opContext *ctx) = 0;
  virtual void exitCls_op(temporalParser::Cls_opContext *ctx) = 0;


};

