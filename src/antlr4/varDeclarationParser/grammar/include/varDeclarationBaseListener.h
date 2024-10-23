
// Generated from varDeclaration.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "varDeclarationListener.h"


/**
 * This class provides an empty implementation of varDeclarationListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  varDeclarationBaseListener : public varDeclarationListener {
public:

  virtual void enterFile(varDeclarationParser::FileContext * /*ctx*/) override { }
  virtual void exitFile(varDeclarationParser::FileContext * /*ctx*/) override { }

  virtual void enterVarDec(varDeclarationParser::VarDecContext * /*ctx*/) override { }
  virtual void exitVarDec(varDeclarationParser::VarDecContext * /*ctx*/) override { }

  virtual void enterStartBoolean(varDeclarationParser::StartBooleanContext * /*ctx*/) override { }
  virtual void exitStartBoolean(varDeclarationParser::StartBooleanContext * /*ctx*/) override { }

  virtual void enterStartInt(varDeclarationParser::StartIntContext * /*ctx*/) override { }
  virtual void exitStartInt(varDeclarationParser::StartIntContext * /*ctx*/) override { }

  virtual void enterStartLogic(varDeclarationParser::StartLogicContext * /*ctx*/) override { }
  virtual void exitStartLogic(varDeclarationParser::StartLogicContext * /*ctx*/) override { }

  virtual void enterStartFloat(varDeclarationParser::StartFloatContext * /*ctx*/) override { }
  virtual void exitStartFloat(varDeclarationParser::StartFloatContext * /*ctx*/) override { }

  virtual void enterStartString(varDeclarationParser::StartStringContext * /*ctx*/) override { }
  virtual void exitStartString(varDeclarationParser::StartStringContext * /*ctx*/) override { }

  virtual void enterBoolean(varDeclarationParser::BooleanContext * /*ctx*/) override { }
  virtual void exitBoolean(varDeclarationParser::BooleanContext * /*ctx*/) override { }

  virtual void enterBooleanAtom(varDeclarationParser::BooleanAtomContext * /*ctx*/) override { }
  virtual void exitBooleanAtom(varDeclarationParser::BooleanAtomContext * /*ctx*/) override { }

  virtual void enterNumeric(varDeclarationParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(varDeclarationParser::NumericContext * /*ctx*/) override { }

  virtual void enterRange(varDeclarationParser::RangeContext * /*ctx*/) override { }
  virtual void exitRange(varDeclarationParser::RangeContext * /*ctx*/) override { }

  virtual void enterSm_range(varDeclarationParser::Sm_rangeContext * /*ctx*/) override { }
  virtual void exitSm_range(varDeclarationParser::Sm_rangeContext * /*ctx*/) override { }

  virtual void enterMin_dollar(varDeclarationParser::Min_dollarContext * /*ctx*/) override { }
  virtual void exitMin_dollar(varDeclarationParser::Min_dollarContext * /*ctx*/) override { }

  virtual void enterMax_dollar(varDeclarationParser::Max_dollarContext * /*ctx*/) override { }
  virtual void exitMax_dollar(varDeclarationParser::Max_dollarContext * /*ctx*/) override { }

  virtual void enterSm_constant(varDeclarationParser::Sm_constantContext * /*ctx*/) override { }
  virtual void exitSm_constant(varDeclarationParser::Sm_constantContext * /*ctx*/) override { }

  virtual void enterIntAtom(varDeclarationParser::IntAtomContext * /*ctx*/) override { }
  virtual void exitIntAtom(varDeclarationParser::IntAtomContext * /*ctx*/) override { }

  virtual void enterInt_constant(varDeclarationParser::Int_constantContext * /*ctx*/) override { }
  virtual void exitInt_constant(varDeclarationParser::Int_constantContext * /*ctx*/) override { }

  virtual void enterLogicAtom(varDeclarationParser::LogicAtomContext * /*ctx*/) override { }
  virtual void exitLogicAtom(varDeclarationParser::LogicAtomContext * /*ctx*/) override { }

  virtual void enterLogic_constant(varDeclarationParser::Logic_constantContext * /*ctx*/) override { }
  virtual void exitLogic_constant(varDeclarationParser::Logic_constantContext * /*ctx*/) override { }

  virtual void enterFloatAtom(varDeclarationParser::FloatAtomContext * /*ctx*/) override { }
  virtual void exitFloatAtom(varDeclarationParser::FloatAtomContext * /*ctx*/) override { }

  virtual void enterString(varDeclarationParser::StringContext * /*ctx*/) override { }
  virtual void exitString(varDeclarationParser::StringContext * /*ctx*/) override { }

  virtual void enterStringAtom(varDeclarationParser::StringAtomContext * /*ctx*/) override { }
  virtual void exitStringAtom(varDeclarationParser::StringAtomContext * /*ctx*/) override { }

  virtual void enterNonTemporalFunction(varDeclarationParser::NonTemporalFunctionContext * /*ctx*/) override { }
  virtual void exitNonTemporalFunction(varDeclarationParser::NonTemporalFunctionContext * /*ctx*/) override { }

  virtual void enterPfunc_arg(varDeclarationParser::Pfunc_argContext * /*ctx*/) override { }
  virtual void exitPfunc_arg(varDeclarationParser::Pfunc_argContext * /*ctx*/) override { }

  virtual void enterRelop(varDeclarationParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(varDeclarationParser::RelopContext * /*ctx*/) override { }

  virtual void enterCls_op(varDeclarationParser::Cls_opContext * /*ctx*/) override { }
  virtual void exitCls_op(varDeclarationParser::Cls_opContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

