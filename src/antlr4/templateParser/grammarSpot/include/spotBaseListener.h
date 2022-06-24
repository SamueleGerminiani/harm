
// Generated from spot.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "spotListener.h"


/**
 * This class provides an empty implementation of spotListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  spotBaseListener : public spotListener {
public:

  virtual void enterFile(spotParser::FileContext * /*ctx*/) override { }
  virtual void exitFile(spotParser::FileContext * /*ctx*/) override { }

  virtual void enterFormula(spotParser::FormulaContext * /*ctx*/) override { }
  virtual void exitFormula(spotParser::FormulaContext * /*ctx*/) override { }

  virtual void enterSere(spotParser::SereContext * /*ctx*/) override { }
  virtual void exitSere(spotParser::SereContext * /*ctx*/) override { }

  virtual void enterTformula(spotParser::TformulaContext * /*ctx*/) override { }
  virtual void exitTformula(spotParser::TformulaContext * /*ctx*/) override { }

  virtual void enterPlaceholder(spotParser::PlaceholderContext * /*ctx*/) override { }
  virtual void exitPlaceholder(spotParser::PlaceholderContext * /*ctx*/) override { }

  virtual void enterBdt_next(spotParser::Bdt_nextContext * /*ctx*/) override { }
  virtual void exitBdt_next(spotParser::Bdt_nextContext * /*ctx*/) override { }

  virtual void enterBdt_next_and(spotParser::Bdt_next_andContext * /*ctx*/) override { }
  virtual void exitBdt_next_and(spotParser::Bdt_next_andContext * /*ctx*/) override { }

  virtual void enterBdt_NCReps(spotParser::Bdt_NCRepsContext * /*ctx*/) override { }
  virtual void exitBdt_NCReps(spotParser::Bdt_NCRepsContext * /*ctx*/) override { }

  virtual void enterBoolean(spotParser::BooleanContext * /*ctx*/) override { }
  virtual void exitBoolean(spotParser::BooleanContext * /*ctx*/) override { }

  virtual void enterBooleanAtom(spotParser::BooleanAtomContext * /*ctx*/) override { }
  virtual void exitBooleanAtom(spotParser::BooleanAtomContext * /*ctx*/) override { }

  virtual void enterBooleanConstant(spotParser::BooleanConstantContext * /*ctx*/) override { }
  virtual void exitBooleanConstant(spotParser::BooleanConstantContext * /*ctx*/) override { }

  virtual void enterBooleanVariable(spotParser::BooleanVariableContext * /*ctx*/) override { }
  virtual void exitBooleanVariable(spotParser::BooleanVariableContext * /*ctx*/) override { }

  virtual void enterLogic(spotParser::LogicContext * /*ctx*/) override { }
  virtual void exitLogic(spotParser::LogicContext * /*ctx*/) override { }

  virtual void enterBitSelect(spotParser::BitSelectContext * /*ctx*/) override { }
  virtual void exitBitSelect(spotParser::BitSelectContext * /*ctx*/) override { }

  virtual void enterLogicAtom(spotParser::LogicAtomContext * /*ctx*/) override { }
  virtual void exitLogicAtom(spotParser::LogicAtomContext * /*ctx*/) override { }

  virtual void enterLogicConstant(spotParser::LogicConstantContext * /*ctx*/) override { }
  virtual void exitLogicConstant(spotParser::LogicConstantContext * /*ctx*/) override { }

  virtual void enterLogicVariable(spotParser::LogicVariableContext * /*ctx*/) override { }
  virtual void exitLogicVariable(spotParser::LogicVariableContext * /*ctx*/) override { }

  virtual void enterNumeric(spotParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(spotParser::NumericContext * /*ctx*/) override { }

  virtual void enterNumericAtom(spotParser::NumericAtomContext * /*ctx*/) override { }
  virtual void exitNumericAtom(spotParser::NumericAtomContext * /*ctx*/) override { }

  virtual void enterNumericConstant(spotParser::NumericConstantContext * /*ctx*/) override { }
  virtual void exitNumericConstant(spotParser::NumericConstantContext * /*ctx*/) override { }

  virtual void enterNumericVariable(spotParser::NumericVariableContext * /*ctx*/) override { }
  virtual void exitNumericVariable(spotParser::NumericVariableContext * /*ctx*/) override { }

  virtual void enterVariable(spotParser::VariableContext * /*ctx*/) override { }
  virtual void exitVariable(spotParser::VariableContext * /*ctx*/) override { }

  virtual void enterRelop(spotParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(spotParser::RelopContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

