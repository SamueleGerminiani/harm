
// Generated from varDeclaration.g4 by ANTLR 4.12.0

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

  virtual void enterBoolean(varDeclarationParser::BooleanContext * /*ctx*/) override { }
  virtual void exitBoolean(varDeclarationParser::BooleanContext * /*ctx*/) override { }

  virtual void enterBooleanAtom(varDeclarationParser::BooleanAtomContext * /*ctx*/) override { }
  virtual void exitBooleanAtom(varDeclarationParser::BooleanAtomContext * /*ctx*/) override { }

  virtual void enterLogic(varDeclarationParser::LogicContext * /*ctx*/) override { }
  virtual void exitLogic(varDeclarationParser::LogicContext * /*ctx*/) override { }

  virtual void enterBitSelect(varDeclarationParser::BitSelectContext * /*ctx*/) override { }
  virtual void exitBitSelect(varDeclarationParser::BitSelectContext * /*ctx*/) override { }

  virtual void enterLogicAtom(varDeclarationParser::LogicAtomContext * /*ctx*/) override { }
  virtual void exitLogicAtom(varDeclarationParser::LogicAtomContext * /*ctx*/) override { }

  virtual void enterNumeric(varDeclarationParser::NumericContext * /*ctx*/) override { }
  virtual void exitNumeric(varDeclarationParser::NumericContext * /*ctx*/) override { }

  virtual void enterNumericAtom(varDeclarationParser::NumericAtomContext * /*ctx*/) override { }
  virtual void exitNumericAtom(varDeclarationParser::NumericAtomContext * /*ctx*/) override { }

  virtual void enterRelop(varDeclarationParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(varDeclarationParser::RelopContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

