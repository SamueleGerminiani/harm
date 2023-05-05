
// Generated from spot.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "spotParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by spotParser.
 */
class  spotListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFile(spotParser::FileContext *ctx) = 0;
  virtual void exitFile(spotParser::FileContext *ctx) = 0;

  virtual void enterFormula(spotParser::FormulaContext *ctx) = 0;
  virtual void exitFormula(spotParser::FormulaContext *ctx) = 0;

  virtual void enterSere(spotParser::SereContext *ctx) = 0;
  virtual void exitSere(spotParser::SereContext *ctx) = 0;

  virtual void enterTformula(spotParser::TformulaContext *ctx) = 0;
  virtual void exitTformula(spotParser::TformulaContext *ctx) = 0;

  virtual void enterPlaceholder(spotParser::PlaceholderContext *ctx) = 0;
  virtual void exitPlaceholder(spotParser::PlaceholderContext *ctx) = 0;

  virtual void enterDt_next(spotParser::Dt_nextContext *ctx) = 0;
  virtual void exitDt_next(spotParser::Dt_nextContext *ctx) = 0;

  virtual void enterDt_next_and(spotParser::Dt_next_andContext *ctx) = 0;
  virtual void exitDt_next_and(spotParser::Dt_next_andContext *ctx) = 0;

  virtual void enterDt_NCReps(spotParser::Dt_NCRepsContext *ctx) = 0;
  virtual void exitDt_NCReps(spotParser::Dt_NCRepsContext *ctx) = 0;

  virtual void enterBoolean(spotParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(spotParser::BooleanContext *ctx) = 0;

  virtual void enterBooleanAtom(spotParser::BooleanAtomContext *ctx) = 0;
  virtual void exitBooleanAtom(spotParser::BooleanAtomContext *ctx) = 0;

  virtual void enterBooleanConstant(spotParser::BooleanConstantContext *ctx) = 0;
  virtual void exitBooleanConstant(spotParser::BooleanConstantContext *ctx) = 0;

  virtual void enterBooleanVariable(spotParser::BooleanVariableContext *ctx) = 0;
  virtual void exitBooleanVariable(spotParser::BooleanVariableContext *ctx) = 0;

  virtual void enterLogic(spotParser::LogicContext *ctx) = 0;
  virtual void exitLogic(spotParser::LogicContext *ctx) = 0;

  virtual void enterBitSelect(spotParser::BitSelectContext *ctx) = 0;
  virtual void exitBitSelect(spotParser::BitSelectContext *ctx) = 0;

  virtual void enterLogicAtom(spotParser::LogicAtomContext *ctx) = 0;
  virtual void exitLogicAtom(spotParser::LogicAtomContext *ctx) = 0;

  virtual void enterLogicConstant(spotParser::LogicConstantContext *ctx) = 0;
  virtual void exitLogicConstant(spotParser::LogicConstantContext *ctx) = 0;

  virtual void enterLogicVariable(spotParser::LogicVariableContext *ctx) = 0;
  virtual void exitLogicVariable(spotParser::LogicVariableContext *ctx) = 0;

  virtual void enterNumeric(spotParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(spotParser::NumericContext *ctx) = 0;

  virtual void enterNumericAtom(spotParser::NumericAtomContext *ctx) = 0;
  virtual void exitNumericAtom(spotParser::NumericAtomContext *ctx) = 0;

  virtual void enterNumericConstant(spotParser::NumericConstantContext *ctx) = 0;
  virtual void exitNumericConstant(spotParser::NumericConstantContext *ctx) = 0;

  virtual void enterNumericVariable(spotParser::NumericVariableContext *ctx) = 0;
  virtual void exitNumericVariable(spotParser::NumericVariableContext *ctx) = 0;

  virtual void enterVariable(spotParser::VariableContext *ctx) = 0;
  virtual void exitVariable(spotParser::VariableContext *ctx) = 0;

  virtual void enterRelop(spotParser::RelopContext *ctx) = 0;
  virtual void exitRelop(spotParser::RelopContext *ctx) = 0;


};

