
#include <string>
// Forward declaration
bool isUnary(const std::string& token);
bool isSharedOperator(const std::string& token);
bool canUseSharedOperator(const std::string& unaryOp, const std::string& sharedOp);
bool canTakeThisNot(const std::string& unaryOp, const std::string& ph);


// Generated from temporal.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "temporalListener.h"


/**
 * This class provides an empty implementation of temporalListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  temporalBaseListener : public temporalListener {
public:

  virtual void enterFormula(temporalParser::FormulaContext * /*ctx*/) override { }
  virtual void exitFormula(temporalParser::FormulaContext * /*ctx*/) override { }

  virtual void enterSva_assert(temporalParser::Sva_assertContext * /*ctx*/) override { }
  virtual void exitSva_assert(temporalParser::Sva_assertContext * /*ctx*/) override { }

  virtual void enterImplication(temporalParser::ImplicationContext * /*ctx*/) override { }
  virtual void exitImplication(temporalParser::ImplicationContext * /*ctx*/) override { }

  virtual void enterSere(temporalParser::SereContext * /*ctx*/) override { }
  virtual void exitSere(temporalParser::SereContext * /*ctx*/) override { }

  virtual void enterBooleanLayer(temporalParser::BooleanLayerContext * /*ctx*/) override { }
  virtual void exitBooleanLayer(temporalParser::BooleanLayerContext * /*ctx*/) override { }

  virtual void enterTformula(temporalParser::TformulaContext * /*ctx*/) override { }
  virtual void exitTformula(temporalParser::TformulaContext * /*ctx*/) override { }

  virtual void enterDt_next(temporalParser::Dt_nextContext * /*ctx*/) override { }
  virtual void exitDt_next(temporalParser::Dt_nextContext * /*ctx*/) override { }

  virtual void enterDt_next_and(temporalParser::Dt_next_andContext * /*ctx*/) override { }
  virtual void exitDt_next_and(temporalParser::Dt_next_andContext * /*ctx*/) override { }

  virtual void enterDt_ncreps(temporalParser::Dt_ncrepsContext * /*ctx*/) override { }
  virtual void exitDt_ncreps(temporalParser::Dt_ncrepsContext * /*ctx*/) override { }

  virtual void enterStartBoolean(temporalParser::StartBooleanContext * /*ctx*/) override { }
  virtual void exitStartBoolean(temporalParser::StartBooleanContext * /*ctx*/) override { }

  virtual void enterStartInt(temporalParser::StartIntContext * /*ctx*/) override { }
  virtual void exitStartInt(temporalParser::StartIntContext * /*ctx*/) override { }

  virtual void enterStartFloat(temporalParser::StartFloatContext * /*ctx*/) override { }
  virtual void exitStartFloat(temporalParser::StartFloatContext * /*ctx*/) override { }

  virtual void enterBoolean(temporalParser::BooleanContext * /*ctx*/) override { }
  virtual void exitBoolean(temporalParser::BooleanContext * /*ctx*/) override { }

  virtual void enterBooleanAtom(temporalParser::BooleanAtomContext * /*ctx*/) override { }
  virtual void exitBooleanAtom(temporalParser::BooleanAtomContext * /*ctx*/) override { }

  virtual void enterNumeric(temporalParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(temporalParser::NumericContext * /*ctx*/) override { }

  virtual void enterRange(temporalParser::RangeContext * /*ctx*/) override { }
  virtual void exitRange(temporalParser::RangeContext * /*ctx*/) override { }

  virtual void enterIntAtom(temporalParser::IntAtomContext * /*ctx*/) override { }
  virtual void exitIntAtom(temporalParser::IntAtomContext * /*ctx*/) override { }

  virtual void enterInt_constant(temporalParser::Int_constantContext * /*ctx*/) override { }
  virtual void exitInt_constant(temporalParser::Int_constantContext * /*ctx*/) override { }

  virtual void enterFloatAtom(temporalParser::FloatAtomContext * /*ctx*/) override { }
  virtual void exitFloatAtom(temporalParser::FloatAtomContext * /*ctx*/) override { }

  virtual void enterRelop(temporalParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(temporalParser::RelopContext * /*ctx*/) override { }

  virtual void enterCls_op(temporalParser::Cls_opContext * /*ctx*/) override { }
  virtual void exitCls_op(temporalParser::Cls_opContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

