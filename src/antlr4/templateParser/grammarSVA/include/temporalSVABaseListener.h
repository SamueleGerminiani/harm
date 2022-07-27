
// Generated from temporalSVA.g4 by ANTLR 4.9.2

#pragma once

#include "antlr4-runtime.h"
#include "temporalSVAListener.h"

/**
 * This class provides an empty implementation of temporalSVAListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class temporalSVABaseListener : public temporalSVAListener {
public:
  virtual void enterFile(temporalSVAParser::FileContext * /*ctx*/) override {}
  virtual void exitFile(temporalSVAParser::FileContext * /*ctx*/) override {}

  virtual void
  enterFormula(temporalSVAParser::FormulaContext * /*ctx*/) override {}
  virtual void
  exitFormula(temporalSVAParser::FormulaContext * /*ctx*/) override {}

  virtual void enterSere(temporalSVAParser::SereContext * /*ctx*/) override {}
  virtual void exitSere(temporalSVAParser::SereContext * /*ctx*/) override {}

  virtual void
  enterTformula(temporalSVAParser::TformulaContext * /*ctx*/) override {}
  virtual void
  exitTformula(temporalSVAParser::TformulaContext * /*ctx*/) override {}

  virtual void
  enterPlaceholder(temporalSVAParser::PlaceholderContext * /*ctx*/) override {}
  virtual void
  exitPlaceholder(temporalSVAParser::PlaceholderContext * /*ctx*/) override {}

  virtual void
  enterDt_next(temporalSVAParser::Dt_nextContext * /*ctx*/) override {}
  virtual void
  exitDt_next(temporalSVAParser::Dt_nextContext * /*ctx*/) override {}

  virtual void
  enterDt_next_and(temporalSVAParser::Dt_next_andContext * /*ctx*/) override {}
  virtual void
  exitDt_next_and(temporalSVAParser::Dt_next_andContext * /*ctx*/) override {}

  virtual void
  enterDt_NCReps(temporalSVAParser::Dt_NCRepsContext * /*ctx*/) override {}
  virtual void
  exitDt_NCReps(temporalSVAParser::Dt_NCRepsContext * /*ctx*/) override {}

  virtual void
  enterBoolean(temporalSVAParser::BooleanContext * /*ctx*/) override {}
  virtual void
  exitBoolean(temporalSVAParser::BooleanContext * /*ctx*/) override {}

  virtual void
  enterBooleanAtom(temporalSVAParser::BooleanAtomContext * /*ctx*/) override {}
  virtual void
  exitBooleanAtom(temporalSVAParser::BooleanAtomContext * /*ctx*/) override {}

  virtual void enterBooleanConstant(
      temporalSVAParser::BooleanConstantContext * /*ctx*/) override {}
  virtual void exitBooleanConstant(
      temporalSVAParser::BooleanConstantContext * /*ctx*/) override {}

  virtual void enterBooleanVariable(
      temporalSVAParser::BooleanVariableContext * /*ctx*/) override {}
  virtual void exitBooleanVariable(
      temporalSVAParser::BooleanVariableContext * /*ctx*/) override {}

  virtual void enterLogic(temporalSVAParser::LogicContext * /*ctx*/) override {}
  virtual void exitLogic(temporalSVAParser::LogicContext * /*ctx*/) override {}

  virtual void
  enterLogicAtom(temporalSVAParser::LogicAtomContext * /*ctx*/) override {}
  virtual void
  exitLogicAtom(temporalSVAParser::LogicAtomContext * /*ctx*/) override {}

  virtual void enterLogicConstant(
      temporalSVAParser::LogicConstantContext * /*ctx*/) override {}
  virtual void exitLogicConstant(
      temporalSVAParser::LogicConstantContext * /*ctx*/) override {}

  virtual void enterLogicVariable(
      temporalSVAParser::LogicVariableContext * /*ctx*/) override {}
  virtual void exitLogicVariable(
      temporalSVAParser::LogicVariableContext * /*ctx*/) override {}

  virtual void
  enterNumeric(temporalSVAParser::NumericContext * /*ctx*/) override {}
  virtual void
  exitNumeric(temporalSVAParser::NumericContext * /*ctx*/) override {}

  virtual void
  enterNumericAtom(temporalSVAParser::NumericAtomContext * /*ctx*/) override {}
  virtual void
  exitNumericAtom(temporalSVAParser::NumericAtomContext * /*ctx*/) override {}

  virtual void enterNumericConstant(
      temporalSVAParser::NumericConstantContext * /*ctx*/) override {}
  virtual void exitNumericConstant(
      temporalSVAParser::NumericConstantContext * /*ctx*/) override {}

  virtual void enterNumericVariable(
      temporalSVAParser::NumericVariableContext * /*ctx*/) override {}
  virtual void exitNumericVariable(
      temporalSVAParser::NumericVariableContext * /*ctx*/) override {}

  virtual void
  enterVariable(temporalSVAParser::VariableContext * /*ctx*/) override {}
  virtual void
  exitVariable(temporalSVAParser::VariableContext * /*ctx*/) override {}

  virtual void enterRelop(temporalSVAParser::RelopContext * /*ctx*/) override {}
  virtual void exitRelop(temporalSVAParser::RelopContext * /*ctx*/) override {}

  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override {}
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override {}
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override {}
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override {}
};
