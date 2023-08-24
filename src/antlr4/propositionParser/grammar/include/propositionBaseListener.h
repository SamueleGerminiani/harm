
// Generated from proposition.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "propositionListener.h"


/**
 * This class provides an empty implementation of propositionListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  propositionBaseListener : public propositionListener {
public:

  virtual void enterFile(propositionParser::FileContext * /*ctx*/) override { }
  virtual void exitFile(propositionParser::FileContext * /*ctx*/) override { }

  virtual void enterBoolean(propositionParser::BooleanContext * /*ctx*/) override { }
  virtual void exitBoolean(propositionParser::BooleanContext * /*ctx*/) override { }

  virtual void enterBooleanAtom(propositionParser::BooleanAtomContext * /*ctx*/) override { }
  virtual void exitBooleanAtom(propositionParser::BooleanAtomContext * /*ctx*/) override { }

  virtual void enterLogic(propositionParser::LogicContext * /*ctx*/) override { }
  virtual void exitLogic(propositionParser::LogicContext * /*ctx*/) override { }

  virtual void enterBitSelect(propositionParser::BitSelectContext * /*ctx*/) override { }
  virtual void exitBitSelect(propositionParser::BitSelectContext * /*ctx*/) override { }

  virtual void enterLogicAtom(propositionParser::LogicAtomContext * /*ctx*/) override { }
  virtual void exitLogicAtom(propositionParser::LogicAtomContext * /*ctx*/) override { }

  virtual void enterNumeric(propositionParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(propositionParser::NumericContext * /*ctx*/) override { }

  virtual void enterNumericAtom(propositionParser::NumericAtomContext * /*ctx*/) override { }
  virtual void exitNumericAtom(propositionParser::NumericAtomContext * /*ctx*/) override { }

  virtual void enterRelop(propositionParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(propositionParser::RelopContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

