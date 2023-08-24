
// Generated from proposition.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "propositionParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by propositionParser.
 */
class  propositionListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFile(propositionParser::FileContext *ctx) = 0;
  virtual void exitFile(propositionParser::FileContext *ctx) = 0;

  virtual void enterBoolean(propositionParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(propositionParser::BooleanContext *ctx) = 0;

  virtual void enterBooleanAtom(propositionParser::BooleanAtomContext *ctx) = 0;
  virtual void exitBooleanAtom(propositionParser::BooleanAtomContext *ctx) = 0;

  virtual void enterLogic(propositionParser::LogicContext *ctx) = 0;
  virtual void exitLogic(propositionParser::LogicContext *ctx) = 0;

  virtual void enterBitSelect(propositionParser::BitSelectContext *ctx) = 0;
  virtual void exitBitSelect(propositionParser::BitSelectContext *ctx) = 0;

  virtual void enterLogicAtom(propositionParser::LogicAtomContext *ctx) = 0;
  virtual void exitLogicAtom(propositionParser::LogicAtomContext *ctx) = 0;

  virtual void enterLogic_constant(propositionParser::Logic_constantContext *ctx) = 0;
  virtual void exitLogic_constant(propositionParser::Logic_constantContext *ctx) = 0;

  virtual void enterNumeric(propositionParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(propositionParser::NumericContext *ctx) = 0;

  virtual void enterNumericAtom(propositionParser::NumericAtomContext *ctx) = 0;
  virtual void exitNumericAtom(propositionParser::NumericAtomContext *ctx) = 0;

  virtual void enterRelop(propositionParser::RelopContext *ctx) = 0;
  virtual void exitRelop(propositionParser::RelopContext *ctx) = 0;


};

