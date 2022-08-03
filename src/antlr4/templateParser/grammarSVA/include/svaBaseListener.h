
// Generated from sva.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "svaListener.h"


/**
 * This class provides an empty implementation of svaListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  svaBaseListener : public svaListener {
public:

  virtual void enterFile(svaParser::FileContext * /*ctx*/) override { }
  virtual void exitFile(svaParser::FileContext * /*ctx*/) override { }

  virtual void enterFormula(svaParser::FormulaContext * /*ctx*/) override { }
  virtual void exitFormula(svaParser::FormulaContext * /*ctx*/) override { }

  virtual void enterSere(svaParser::SereContext * /*ctx*/) override { }
  virtual void exitSere(svaParser::SereContext * /*ctx*/) override { }

  virtual void enterTformula(svaParser::TformulaContext * /*ctx*/) override { }
  virtual void exitTformula(svaParser::TformulaContext * /*ctx*/) override { }

  virtual void enterPlaceholder(svaParser::PlaceholderContext * /*ctx*/) override { }
  virtual void exitPlaceholder(svaParser::PlaceholderContext * /*ctx*/) override { }

  virtual void enterDt_next(svaParser::Dt_nextContext * /*ctx*/) override { }
  virtual void exitDt_next(svaParser::Dt_nextContext * /*ctx*/) override { }

  virtual void enterDt_next_and(svaParser::Dt_next_andContext * /*ctx*/) override { }
  virtual void exitDt_next_and(svaParser::Dt_next_andContext * /*ctx*/) override { }

  virtual void enterDt_NCReps(svaParser::Dt_NCRepsContext * /*ctx*/) override { }
  virtual void exitDt_NCReps(svaParser::Dt_NCRepsContext * /*ctx*/) override { }

  virtual void enterBoolean(svaParser::BooleanContext * /*ctx*/) override { }
  virtual void exitBoolean(svaParser::BooleanContext * /*ctx*/) override { }

  virtual void enterBooleanAtom(svaParser::BooleanAtomContext * /*ctx*/) override { }
  virtual void exitBooleanAtom(svaParser::BooleanAtomContext * /*ctx*/) override { }

  virtual void enterBooleanConstant(svaParser::BooleanConstantContext * /*ctx*/) override { }
  virtual void exitBooleanConstant(svaParser::BooleanConstantContext * /*ctx*/) override { }

  virtual void enterBooleanVariable(svaParser::BooleanVariableContext * /*ctx*/) override { }
  virtual void exitBooleanVariable(svaParser::BooleanVariableContext * /*ctx*/) override { }

  virtual void enterLogic(svaParser::LogicContext * /*ctx*/) override { }
  virtual void exitLogic(svaParser::LogicContext * /*ctx*/) override { }

  virtual void enterBitSelect(svaParser::BitSelectContext * /*ctx*/) override { }
  virtual void exitBitSelect(svaParser::BitSelectContext * /*ctx*/) override { }

  virtual void enterLogicAtom(svaParser::LogicAtomContext * /*ctx*/) override { }
  virtual void exitLogicAtom(svaParser::LogicAtomContext * /*ctx*/) override { }

  virtual void enterLogicConstant(svaParser::LogicConstantContext * /*ctx*/) override { }
  virtual void exitLogicConstant(svaParser::LogicConstantContext * /*ctx*/) override { }

  virtual void enterLogicVariable(svaParser::LogicVariableContext * /*ctx*/) override { }
  virtual void exitLogicVariable(svaParser::LogicVariableContext * /*ctx*/) override { }

  virtual void enterNumeric(svaParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(svaParser::NumericContext * /*ctx*/) override { }

  virtual void enterNumericAtom(svaParser::NumericAtomContext * /*ctx*/) override { }
  virtual void exitNumericAtom(svaParser::NumericAtomContext * /*ctx*/) override { }

  virtual void enterNumericConstant(svaParser::NumericConstantContext * /*ctx*/) override { }
  virtual void exitNumericConstant(svaParser::NumericConstantContext * /*ctx*/) override { }

  virtual void enterNumericVariable(svaParser::NumericVariableContext * /*ctx*/) override { }
  virtual void exitNumericVariable(svaParser::NumericVariableContext * /*ctx*/) override { }

  virtual void enterVariable(svaParser::VariableContext * /*ctx*/) override { }
  virtual void exitVariable(svaParser::VariableContext * /*ctx*/) override { }

  virtual void enterRelop(svaParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(svaParser::RelopContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

