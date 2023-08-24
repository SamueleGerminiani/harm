
// Generated from spot.g4 by ANTLR 4.12.0

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

  virtual void enterNonTemporalExp(spotParser::NonTemporalExpContext * /*ctx*/) override { }
  virtual void exitNonTemporalExp(spotParser::NonTemporalExpContext * /*ctx*/) override { }

  virtual void enterBoolean(spotParser::BooleanContext * /*ctx*/) override { }
  virtual void exitBoolean(spotParser::BooleanContext * /*ctx*/) override { }

  virtual void enterBooleanAtom(spotParser::BooleanAtomContext * /*ctx*/) override { }
  virtual void exitBooleanAtom(spotParser::BooleanAtomContext * /*ctx*/) override { }

  virtual void enterLogic(spotParser::LogicContext * /*ctx*/) override { }
  virtual void exitLogic(spotParser::LogicContext * /*ctx*/) override { }

  virtual void enterBitSelect(spotParser::BitSelectContext * /*ctx*/) override { }
  virtual void exitBitSelect(spotParser::BitSelectContext * /*ctx*/) override { }

  virtual void enterLogicAtom(spotParser::LogicAtomContext * /*ctx*/) override { }
  virtual void exitLogicAtom(spotParser::LogicAtomContext * /*ctx*/) override { }

  virtual void enterLogic_constant(spotParser::Logic_constantContext * /*ctx*/) override { }
  virtual void exitLogic_constant(spotParser::Logic_constantContext * /*ctx*/) override { }

  virtual void enterNumeric(spotParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(spotParser::NumericContext * /*ctx*/) override { }

  virtual void enterNumericAtom(spotParser::NumericAtomContext * /*ctx*/) override { }
  virtual void exitNumericAtom(spotParser::NumericAtomContext * /*ctx*/) override { }

  virtual void enterRelop(spotParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(spotParser::RelopContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

