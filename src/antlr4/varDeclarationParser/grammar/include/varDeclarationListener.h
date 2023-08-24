
// Generated from varDeclaration.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "varDeclarationParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by varDeclarationParser.
 */
class  varDeclarationListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFile(varDeclarationParser::FileContext *ctx) = 0;
  virtual void exitFile(varDeclarationParser::FileContext *ctx) = 0;

  virtual void enterVarDec(varDeclarationParser::VarDecContext *ctx) = 0;
  virtual void exitVarDec(varDeclarationParser::VarDecContext *ctx) = 0;

  virtual void enterBoolean(varDeclarationParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(varDeclarationParser::BooleanContext *ctx) = 0;

  virtual void enterBooleanAtom(varDeclarationParser::BooleanAtomContext *ctx) = 0;
  virtual void exitBooleanAtom(varDeclarationParser::BooleanAtomContext *ctx) = 0;

  virtual void enterLogic(varDeclarationParser::LogicContext *ctx) = 0;
  virtual void exitLogic(varDeclarationParser::LogicContext *ctx) = 0;

  virtual void enterBitSelect(varDeclarationParser::BitSelectContext *ctx) = 0;
  virtual void exitBitSelect(varDeclarationParser::BitSelectContext *ctx) = 0;

  virtual void enterLogicAtom(varDeclarationParser::LogicAtomContext *ctx) = 0;
  virtual void exitLogicAtom(varDeclarationParser::LogicAtomContext *ctx) = 0;

  virtual void enterNumeric(varDeclarationParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(varDeclarationParser::NumericContext *ctx) = 0;

  virtual void enterNumericAtom(varDeclarationParser::NumericAtomContext *ctx) = 0;
  virtual void exitNumericAtom(varDeclarationParser::NumericAtomContext *ctx) = 0;

  virtual void enterRelop(varDeclarationParser::RelopContext *ctx) = 0;
  virtual void exitRelop(varDeclarationParser::RelopContext *ctx) = 0;


};

