
// Generated from varDeclaration.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "varDeclarationParser.h"

/**
 * This interface defines an abstract listener for a parse tree produced by varDeclarationParser.
 */
class varDeclarationListener : public antlr4::tree::ParseTreeListener {
public:
  virtual void enterFile(varDeclarationParser::FileContext *ctx) = 0;
  virtual void exitFile(varDeclarationParser::FileContext *ctx) = 0;

  virtual void enterVarDec(varDeclarationParser::VarDecContext *ctx) = 0;
  virtual void exitVarDec(varDeclarationParser::VarDecContext *ctx) = 0;

  virtual void enterName(varDeclarationParser::NameContext *ctx) = 0;
  virtual void exitName(varDeclarationParser::NameContext *ctx) = 0;

  virtual void enterVartype(varDeclarationParser::VartypeContext *ctx) = 0;
  virtual void exitVartype(varDeclarationParser::VartypeContext *ctx) = 0;
};
