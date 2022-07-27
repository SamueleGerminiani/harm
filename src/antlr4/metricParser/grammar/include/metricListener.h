
// Generated from metric.g4 by ANTLR 4.9.2

#pragma once

#include "antlr4-runtime.h"
#include "metricParser.h"

/**
 * This interface defines an abstract listener for a parse tree produced by metricParser.
 */
class metricListener : public antlr4::tree::ParseTreeListener {
public:
  virtual void enterFile(metricParser::FileContext *ctx) = 0;
  virtual void exitFile(metricParser::FileContext *ctx) = 0;

  virtual void enterLogic(metricParser::LogicContext *ctx) = 0;
  virtual void exitLogic(metricParser::LogicContext *ctx) = 0;

  virtual void enterLogicAtom(metricParser::LogicAtomContext *ctx) = 0;
  virtual void exitLogicAtom(metricParser::LogicAtomContext *ctx) = 0;

  virtual void enterLogicConstant(metricParser::LogicConstantContext *ctx) = 0;
  virtual void exitLogicConstant(metricParser::LogicConstantContext *ctx) = 0;

  virtual void enterLogicVariable(metricParser::LogicVariableContext *ctx) = 0;
  virtual void exitLogicVariable(metricParser::LogicVariableContext *ctx) = 0;

  virtual void enterNumeric(metricParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(metricParser::NumericContext *ctx) = 0;

  virtual void enterNumericAtom(metricParser::NumericAtomContext *ctx) = 0;
  virtual void exitNumericAtom(metricParser::NumericAtomContext *ctx) = 0;

  virtual void
  enterNumericConstant(metricParser::NumericConstantContext *ctx) = 0;
  virtual void
  exitNumericConstant(metricParser::NumericConstantContext *ctx) = 0;

  virtual void
  enterNumericVariable(metricParser::NumericVariableContext *ctx) = 0;
  virtual void
  exitNumericVariable(metricParser::NumericVariableContext *ctx) = 0;

  virtual void enterVariable(metricParser::VariableContext *ctx) = 0;
  virtual void exitVariable(metricParser::VariableContext *ctx) = 0;

  virtual void enterRelop(metricParser::RelopContext *ctx) = 0;
  virtual void exitRelop(metricParser::RelopContext *ctx) = 0;
};
