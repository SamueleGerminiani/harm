
// Generated from sva.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "svaParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by svaParser.
 */
class  svaListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFile(svaParser::FileContext *ctx) = 0;
  virtual void exitFile(svaParser::FileContext *ctx) = 0;

  virtual void enterFormula(svaParser::FormulaContext *ctx) = 0;
  virtual void exitFormula(svaParser::FormulaContext *ctx) = 0;

  virtual void enterSere(svaParser::SereContext *ctx) = 0;
  virtual void exitSere(svaParser::SereContext *ctx) = 0;

  virtual void enterTformula(svaParser::TformulaContext *ctx) = 0;
  virtual void exitTformula(svaParser::TformulaContext *ctx) = 0;

  virtual void enterPlaceholder(svaParser::PlaceholderContext *ctx) = 0;
  virtual void exitPlaceholder(svaParser::PlaceholderContext *ctx) = 0;

  virtual void enterDt_next(svaParser::Dt_nextContext *ctx) = 0;
  virtual void exitDt_next(svaParser::Dt_nextContext *ctx) = 0;

  virtual void enterDt_next_and(svaParser::Dt_next_andContext *ctx) = 0;
  virtual void exitDt_next_and(svaParser::Dt_next_andContext *ctx) = 0;

  virtual void enterDt_NCReps(svaParser::Dt_NCRepsContext *ctx) = 0;
  virtual void exitDt_NCReps(svaParser::Dt_NCRepsContext *ctx) = 0;

  virtual void enterBoolean(svaParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(svaParser::BooleanContext *ctx) = 0;

  virtual void enterBooleanAtom(svaParser::BooleanAtomContext *ctx) = 0;
  virtual void exitBooleanAtom(svaParser::BooleanAtomContext *ctx) = 0;

  virtual void enterBooleanConstant(svaParser::BooleanConstantContext *ctx) = 0;
  virtual void exitBooleanConstant(svaParser::BooleanConstantContext *ctx) = 0;

  virtual void enterBooleanVariable(svaParser::BooleanVariableContext *ctx) = 0;
  virtual void exitBooleanVariable(svaParser::BooleanVariableContext *ctx) = 0;

  virtual void enterLogic(svaParser::LogicContext *ctx) = 0;
  virtual void exitLogic(svaParser::LogicContext *ctx) = 0;

  virtual void enterBitSelect(svaParser::BitSelectContext *ctx) = 0;
  virtual void exitBitSelect(svaParser::BitSelectContext *ctx) = 0;

  virtual void enterLogicAtom(svaParser::LogicAtomContext *ctx) = 0;
  virtual void exitLogicAtom(svaParser::LogicAtomContext *ctx) = 0;

  virtual void enterLogicConstant(svaParser::LogicConstantContext *ctx) = 0;
  virtual void exitLogicConstant(svaParser::LogicConstantContext *ctx) = 0;

  virtual void enterLogicVariable(svaParser::LogicVariableContext *ctx) = 0;
  virtual void exitLogicVariable(svaParser::LogicVariableContext *ctx) = 0;

  virtual void enterNumeric(svaParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(svaParser::NumericContext *ctx) = 0;

  virtual void enterNumericAtom(svaParser::NumericAtomContext *ctx) = 0;
  virtual void exitNumericAtom(svaParser::NumericAtomContext *ctx) = 0;

  virtual void enterNumericConstant(svaParser::NumericConstantContext *ctx) = 0;
  virtual void exitNumericConstant(svaParser::NumericConstantContext *ctx) = 0;

  virtual void enterNumericVariable(svaParser::NumericVariableContext *ctx) = 0;
  virtual void exitNumericVariable(svaParser::NumericVariableContext *ctx) = 0;

  virtual void enterVariable(svaParser::VariableContext *ctx) = 0;
  virtual void exitVariable(svaParser::VariableContext *ctx) = 0;

  virtual void enterRelop(svaParser::RelopContext *ctx) = 0;
  virtual void exitRelop(svaParser::RelopContext *ctx) = 0;


};

