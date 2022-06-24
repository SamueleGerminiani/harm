
// Generated from varDeclaration.g4 by ANTLR 4.7.2

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

  virtual void enterName(varDeclarationParser::NameContext * /*ctx*/) override { }
  virtual void exitName(varDeclarationParser::NameContext * /*ctx*/) override { }

  virtual void enterVartype(varDeclarationParser::VartypeContext * /*ctx*/) override { }
  virtual void exitVartype(varDeclarationParser::VartypeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

