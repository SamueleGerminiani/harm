
// Generated from varDeclaration.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "varDeclarationParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by varDeclarationParser.
 */
class  varDeclarationListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFile(varDeclarationParser::FileContext *ctx) = 0;
  virtual void exitFile(varDeclarationParser::FileContext *ctx) = 0;

  virtual void enterVarDec(varDeclarationParser::VarDecContext *ctx) = 0;
  virtual void exitVarDec(varDeclarationParser::VarDecContext *ctx) = 0;

  virtual void enterStartBoolean(varDeclarationParser::StartBooleanContext *ctx) = 0;
  virtual void exitStartBoolean(varDeclarationParser::StartBooleanContext *ctx) = 0;

  virtual void enterStartInt(varDeclarationParser::StartIntContext *ctx) = 0;
  virtual void exitStartInt(varDeclarationParser::StartIntContext *ctx) = 0;

  virtual void enterStartLogic(varDeclarationParser::StartLogicContext *ctx) = 0;
  virtual void exitStartLogic(varDeclarationParser::StartLogicContext *ctx) = 0;

  virtual void enterStartFloat(varDeclarationParser::StartFloatContext *ctx) = 0;
  virtual void exitStartFloat(varDeclarationParser::StartFloatContext *ctx) = 0;

  virtual void enterStartString(varDeclarationParser::StartStringContext *ctx) = 0;
  virtual void exitStartString(varDeclarationParser::StartStringContext *ctx) = 0;

  virtual void enterBoolean(varDeclarationParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(varDeclarationParser::BooleanContext *ctx) = 0;

  virtual void enterBooleanAtom(varDeclarationParser::BooleanAtomContext *ctx) = 0;
  virtual void exitBooleanAtom(varDeclarationParser::BooleanAtomContext *ctx) = 0;

  virtual void enterNumeric(varDeclarationParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(varDeclarationParser::NumericContext *ctx) = 0;

  virtual void enterRange(varDeclarationParser::RangeContext *ctx) = 0;
  virtual void exitRange(varDeclarationParser::RangeContext *ctx) = 0;

  virtual void enterSm_range(varDeclarationParser::Sm_rangeContext *ctx) = 0;
  virtual void exitSm_range(varDeclarationParser::Sm_rangeContext *ctx) = 0;

  virtual void enterMin_dollar(varDeclarationParser::Min_dollarContext *ctx) = 0;
  virtual void exitMin_dollar(varDeclarationParser::Min_dollarContext *ctx) = 0;

  virtual void enterMax_dollar(varDeclarationParser::Max_dollarContext *ctx) = 0;
  virtual void exitMax_dollar(varDeclarationParser::Max_dollarContext *ctx) = 0;

  virtual void enterSm_constant(varDeclarationParser::Sm_constantContext *ctx) = 0;
  virtual void exitSm_constant(varDeclarationParser::Sm_constantContext *ctx) = 0;

  virtual void enterIntAtom(varDeclarationParser::IntAtomContext *ctx) = 0;
  virtual void exitIntAtom(varDeclarationParser::IntAtomContext *ctx) = 0;

  virtual void enterInt_constant(varDeclarationParser::Int_constantContext *ctx) = 0;
  virtual void exitInt_constant(varDeclarationParser::Int_constantContext *ctx) = 0;

  virtual void enterLogicAtom(varDeclarationParser::LogicAtomContext *ctx) = 0;
  virtual void exitLogicAtom(varDeclarationParser::LogicAtomContext *ctx) = 0;

  virtual void enterLogic_constant(varDeclarationParser::Logic_constantContext *ctx) = 0;
  virtual void exitLogic_constant(varDeclarationParser::Logic_constantContext *ctx) = 0;

  virtual void enterFloatAtom(varDeclarationParser::FloatAtomContext *ctx) = 0;
  virtual void exitFloatAtom(varDeclarationParser::FloatAtomContext *ctx) = 0;

  virtual void enterString(varDeclarationParser::StringContext *ctx) = 0;
  virtual void exitString(varDeclarationParser::StringContext *ctx) = 0;

  virtual void enterStringAtom(varDeclarationParser::StringAtomContext *ctx) = 0;
  virtual void exitStringAtom(varDeclarationParser::StringAtomContext *ctx) = 0;

  virtual void enterNonTemporalFunction(varDeclarationParser::NonTemporalFunctionContext *ctx) = 0;
  virtual void exitNonTemporalFunction(varDeclarationParser::NonTemporalFunctionContext *ctx) = 0;

  virtual void enterPfunc_arg(varDeclarationParser::Pfunc_argContext *ctx) = 0;
  virtual void exitPfunc_arg(varDeclarationParser::Pfunc_argContext *ctx) = 0;

  virtual void enterRelop(varDeclarationParser::RelopContext *ctx) = 0;
  virtual void exitRelop(varDeclarationParser::RelopContext *ctx) = 0;

  virtual void enterCls_op(varDeclarationParser::Cls_opContext *ctx) = 0;
  virtual void exitCls_op(varDeclarationParser::Cls_opContext *ctx) = 0;


};

