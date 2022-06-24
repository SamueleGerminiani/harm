
// Generated from temporalSVA.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "temporalSVAParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by temporalSVAParser.
 */
class  temporalSVAListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFile(temporalSVAParser::FileContext *ctx) = 0;
  virtual void exitFile(temporalSVAParser::FileContext *ctx) = 0;

  virtual void enterFormula(temporalSVAParser::FormulaContext *ctx) = 0;
  virtual void exitFormula(temporalSVAParser::FormulaContext *ctx) = 0;

  virtual void enterSere(temporalSVAParser::SereContext *ctx) = 0;
  virtual void exitSere(temporalSVAParser::SereContext *ctx) = 0;

  virtual void enterTformula(temporalSVAParser::TformulaContext *ctx) = 0;
  virtual void exitTformula(temporalSVAParser::TformulaContext *ctx) = 0;

  virtual void enterPlaceholder(temporalSVAParser::PlaceholderContext *ctx) = 0;
  virtual void exitPlaceholder(temporalSVAParser::PlaceholderContext *ctx) = 0;

  virtual void enterBdt_next(temporalSVAParser::Bdt_nextContext *ctx) = 0;
  virtual void exitBdt_next(temporalSVAParser::Bdt_nextContext *ctx) = 0;

  virtual void enterBdt_next_and(temporalSVAParser::Bdt_next_andContext *ctx) = 0;
  virtual void exitBdt_next_and(temporalSVAParser::Bdt_next_andContext *ctx) = 0;

  virtual void enterBdt_NCReps(temporalSVAParser::Bdt_NCRepsContext *ctx) = 0;
  virtual void exitBdt_NCReps(temporalSVAParser::Bdt_NCRepsContext *ctx) = 0;

  virtual void enterBoolean(temporalSVAParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(temporalSVAParser::BooleanContext *ctx) = 0;

  virtual void enterBooleanAtom(temporalSVAParser::BooleanAtomContext *ctx) = 0;
  virtual void exitBooleanAtom(temporalSVAParser::BooleanAtomContext *ctx) = 0;

  virtual void enterBooleanConstant(temporalSVAParser::BooleanConstantContext *ctx) = 0;
  virtual void exitBooleanConstant(temporalSVAParser::BooleanConstantContext *ctx) = 0;

  virtual void enterBooleanVariable(temporalSVAParser::BooleanVariableContext *ctx) = 0;
  virtual void exitBooleanVariable(temporalSVAParser::BooleanVariableContext *ctx) = 0;

  virtual void enterLogic(temporalSVAParser::LogicContext *ctx) = 0;
  virtual void exitLogic(temporalSVAParser::LogicContext *ctx) = 0;

  virtual void enterLogicAtom(temporalSVAParser::LogicAtomContext *ctx) = 0;
  virtual void exitLogicAtom(temporalSVAParser::LogicAtomContext *ctx) = 0;

  virtual void enterLogicConstant(temporalSVAParser::LogicConstantContext *ctx) = 0;
  virtual void exitLogicConstant(temporalSVAParser::LogicConstantContext *ctx) = 0;

  virtual void enterLogicVariable(temporalSVAParser::LogicVariableContext *ctx) = 0;
  virtual void exitLogicVariable(temporalSVAParser::LogicVariableContext *ctx) = 0;

  virtual void enterNumeric(temporalSVAParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(temporalSVAParser::NumericContext *ctx) = 0;

  virtual void enterNumericAtom(temporalSVAParser::NumericAtomContext *ctx) = 0;
  virtual void exitNumericAtom(temporalSVAParser::NumericAtomContext *ctx) = 0;

  virtual void enterNumericConstant(temporalSVAParser::NumericConstantContext *ctx) = 0;
  virtual void exitNumericConstant(temporalSVAParser::NumericConstantContext *ctx) = 0;

  virtual void enterNumericVariable(temporalSVAParser::NumericVariableContext *ctx) = 0;
  virtual void exitNumericVariable(temporalSVAParser::NumericVariableContext *ctx) = 0;

  virtual void enterVariable(temporalSVAParser::VariableContext *ctx) = 0;
  virtual void exitVariable(temporalSVAParser::VariableContext *ctx) = 0;

  virtual void enterRelop(temporalSVAParser::RelopContext *ctx) = 0;
  virtual void exitRelop(temporalSVAParser::RelopContext *ctx) = 0;


};

