
// Generated from metric.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "metricListener.h"


/**
 * This class provides an empty implementation of metricListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  metricBaseListener : public metricListener {
public:

  virtual void enterFile(metricParser::FileContext * /*ctx*/) override { }
  virtual void exitFile(metricParser::FileContext * /*ctx*/) override { }

  virtual void enterLogic(metricParser::LogicContext * /*ctx*/) override { }
  virtual void exitLogic(metricParser::LogicContext * /*ctx*/) override { }

  virtual void enterLogicAtom(metricParser::LogicAtomContext * /*ctx*/) override { }
  virtual void exitLogicAtom(metricParser::LogicAtomContext * /*ctx*/) override { }

  virtual void enterLogicConstant(metricParser::LogicConstantContext * /*ctx*/) override { }
  virtual void exitLogicConstant(metricParser::LogicConstantContext * /*ctx*/) override { }

  virtual void enterLogicVariable(metricParser::LogicVariableContext * /*ctx*/) override { }
  virtual void exitLogicVariable(metricParser::LogicVariableContext * /*ctx*/) override { }

  virtual void enterNumeric(metricParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(metricParser::NumericContext * /*ctx*/) override { }

  virtual void enterNumericAtom(metricParser::NumericAtomContext * /*ctx*/) override { }
  virtual void exitNumericAtom(metricParser::NumericAtomContext * /*ctx*/) override { }

  virtual void enterNumericConstant(metricParser::NumericConstantContext * /*ctx*/) override { }
  virtual void exitNumericConstant(metricParser::NumericConstantContext * /*ctx*/) override { }

  virtual void enterNumericVariable(metricParser::NumericVariableContext * /*ctx*/) override { }
  virtual void exitNumericVariable(metricParser::NumericVariableContext * /*ctx*/) override { }

  virtual void enterVariable(metricParser::VariableContext * /*ctx*/) override { }
  virtual void exitVariable(metricParser::VariableContext * /*ctx*/) override { }

  virtual void enterRelop(metricParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(metricParser::RelopContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

