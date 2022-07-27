
// Generated from limits.g4 by ANTLR 4.9.2

#pragma once

#include "antlr4-runtime.h"
#include "limitsListener.h"

/**
 * This class provides an empty implementation of limitsListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class limitsBaseListener : public limitsListener {
public:
  virtual void enterFile(limitsParser::FileContext * /*ctx*/) override {}
  virtual void exitFile(limitsParser::FileContext * /*ctx*/) override {}

  virtual void
  enterParameter(limitsParser::ParameterContext * /*ctx*/) override {}
  virtual void
  exitParameter(limitsParser::ParameterContext * /*ctx*/) override {}

  virtual void enterAtom(limitsParser::AtomContext * /*ctx*/) override {}
  virtual void exitAtom(limitsParser::AtomContext * /*ctx*/) override {}

  virtual void enterDep(limitsParser::DepContext * /*ctx*/) override {}
  virtual void exitDep(limitsParser::DepContext * /*ctx*/) override {}

  virtual void enterWidth(limitsParser::WidthContext * /*ctx*/) override {}
  virtual void exitWidth(limitsParser::WidthContext * /*ctx*/) override {}

  virtual void enterAll(limitsParser::AllContext * /*ctx*/) override {}
  virtual void exitAll(limitsParser::AllContext * /*ctx*/) override {}

  virtual void enterOffset(limitsParser::OffsetContext * /*ctx*/) override {}
  virtual void exitOffset(limitsParser::OffsetContext * /*ctx*/) override {}

  virtual void enterNegated(limitsParser::NegatedContext * /*ctx*/) override {}
  virtual void exitNegated(limitsParser::NegatedContext * /*ctx*/) override {}

  virtual void enterEffort(limitsParser::EffortContext * /*ctx*/) override {}
  virtual void exitEffort(limitsParser::EffortContext * /*ctx*/) override {}

  virtual void enterStrategy(limitsParser::StrategyContext * /*ctx*/) override {
  }
  virtual void exitStrategy(limitsParser::StrategyContext * /*ctx*/) override {}

  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override {}
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override {}
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override {}
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override {}
};
