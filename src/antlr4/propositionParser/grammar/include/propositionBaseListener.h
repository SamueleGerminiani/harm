
// Generated from proposition.g4 by ANTLR 4.10.1

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

  virtual void enterStartBoolean(propositionParser::StartBooleanContext * /*ctx*/) override { }
  virtual void exitStartBoolean(propositionParser::StartBooleanContext * /*ctx*/) override { }

  virtual void enterStartInt(propositionParser::StartIntContext * /*ctx*/) override { }
  virtual void exitStartInt(propositionParser::StartIntContext * /*ctx*/) override { }

  virtual void enterStartLogic(propositionParser::StartLogicContext * /*ctx*/) override { }
  virtual void exitStartLogic(propositionParser::StartLogicContext * /*ctx*/) override { }

  virtual void enterStartFloat(propositionParser::StartFloatContext * /*ctx*/) override { }
  virtual void exitStartFloat(propositionParser::StartFloatContext * /*ctx*/) override { }

  virtual void enterStartString(propositionParser::StartStringContext * /*ctx*/) override { }
  virtual void exitStartString(propositionParser::StartStringContext * /*ctx*/) override { }

  virtual void enterBoolean(propositionParser::BooleanContext * /*ctx*/) override { }
  virtual void exitBoolean(propositionParser::BooleanContext * /*ctx*/) override { }

  virtual void enterBooleanAtom(propositionParser::BooleanAtomContext * /*ctx*/) override { }
  virtual void exitBooleanAtom(propositionParser::BooleanAtomContext * /*ctx*/) override { }

  virtual void enterNumeric(propositionParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(propositionParser::NumericContext * /*ctx*/) override { }

  virtual void enterRange(propositionParser::RangeContext * /*ctx*/) override { }
  virtual void exitRange(propositionParser::RangeContext * /*ctx*/) override { }

  virtual void enterSm_range(propositionParser::Sm_rangeContext * /*ctx*/) override { }
  virtual void exitSm_range(propositionParser::Sm_rangeContext * /*ctx*/) override { }

  virtual void enterMin_dollar(propositionParser::Min_dollarContext * /*ctx*/) override { }
  virtual void exitMin_dollar(propositionParser::Min_dollarContext * /*ctx*/) override { }

  virtual void enterMax_dollar(propositionParser::Max_dollarContext * /*ctx*/) override { }
  virtual void exitMax_dollar(propositionParser::Max_dollarContext * /*ctx*/) override { }

  virtual void enterSm_constant(propositionParser::Sm_constantContext * /*ctx*/) override { }
  virtual void exitSm_constant(propositionParser::Sm_constantContext * /*ctx*/) override { }

  virtual void enterIntAtom(propositionParser::IntAtomContext * /*ctx*/) override { }
  virtual void exitIntAtom(propositionParser::IntAtomContext * /*ctx*/) override { }

  virtual void enterInt_constant(propositionParser::Int_constantContext * /*ctx*/) override { }
  virtual void exitInt_constant(propositionParser::Int_constantContext * /*ctx*/) override { }

  virtual void enterLogicAtom(propositionParser::LogicAtomContext * /*ctx*/) override { }
  virtual void exitLogicAtom(propositionParser::LogicAtomContext * /*ctx*/) override { }

  virtual void enterLogic_constant(propositionParser::Logic_constantContext * /*ctx*/) override { }
  virtual void exitLogic_constant(propositionParser::Logic_constantContext * /*ctx*/) override { }

  virtual void enterFloatAtom(propositionParser::FloatAtomContext * /*ctx*/) override { }
  virtual void exitFloatAtom(propositionParser::FloatAtomContext * /*ctx*/) override { }

  virtual void enterString(propositionParser::StringContext * /*ctx*/) override { }
  virtual void exitString(propositionParser::StringContext * /*ctx*/) override { }

  virtual void enterStringAtom(propositionParser::StringAtomContext * /*ctx*/) override { }
  virtual void exitStringAtom(propositionParser::StringAtomContext * /*ctx*/) override { }

  virtual void enterNonTemporalFunction(propositionParser::NonTemporalFunctionContext * /*ctx*/) override { }
  virtual void exitNonTemporalFunction(propositionParser::NonTemporalFunctionContext * /*ctx*/) override { }

  virtual void enterPfunc_arg(propositionParser::Pfunc_argContext * /*ctx*/) override { }
  virtual void exitPfunc_arg(propositionParser::Pfunc_argContext * /*ctx*/) override { }

  virtual void enterRelop(propositionParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(propositionParser::RelopContext * /*ctx*/) override { }

  virtual void enterCls_op(propositionParser::Cls_opContext * /*ctx*/) override { }
  virtual void exitCls_op(propositionParser::Cls_opContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

