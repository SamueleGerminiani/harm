
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

  virtual void enterNonTemporalExp(spotParser::NonTemporalExpContext *ctx) = 0;
  virtual void exitNonTemporalExp(spotParser::NonTemporalExpContext *ctx) = 0;

  virtual void enterBoolean(spotParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(spotParser::BooleanContext *ctx) = 0;

  virtual void enterBooleanAtom(spotParser::BooleanAtomContext *ctx) = 0;
  virtual void exitBooleanAtom(spotParser::BooleanAtomContext *ctx) = 0;

  virtual void enterLogic(spotParser::LogicContext *ctx) = 0;
  virtual void exitLogic(spotParser::LogicContext *ctx) = 0;

  virtual void enterBitSelect(spotParser::BitSelectContext *ctx) = 0;
  virtual void exitBitSelect(spotParser::BitSelectContext *ctx) = 0;

  virtual void enterLogicAtom(spotParser::LogicAtomContext *ctx) = 0;
  virtual void exitLogicAtom(spotParser::LogicAtomContext *ctx) = 0;

  virtual void enterLogic_constant(spotParser::Logic_constantContext *ctx) = 0;
  virtual void exitLogic_constant(spotParser::Logic_constantContext *ctx) = 0;

  virtual void enterNumeric(spotParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(spotParser::NumericContext *ctx) = 0;

  virtual void enterNumericAtom(spotParser::NumericAtomContext *ctx) = 0;
  virtual void exitNumericAtom(spotParser::NumericAtomContext *ctx) = 0;

  virtual void enterRelop(spotParser::RelopContext *ctx) = 0;
  virtual void exitRelop(spotParser::RelopContext *ctx) = 0;


};

