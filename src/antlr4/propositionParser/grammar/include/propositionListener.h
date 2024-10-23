
// Generated from proposition.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "propositionParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by propositionParser.
 */
class  propositionListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStartBoolean(propositionParser::StartBooleanContext *ctx) = 0;
  virtual void exitStartBoolean(propositionParser::StartBooleanContext *ctx) = 0;

  virtual void enterStartInt(propositionParser::StartIntContext *ctx) = 0;
  virtual void exitStartInt(propositionParser::StartIntContext *ctx) = 0;

  virtual void enterStartFloat(propositionParser::StartFloatContext *ctx) = 0;
  virtual void exitStartFloat(propositionParser::StartFloatContext *ctx) = 0;

  virtual void enterBoolean(propositionParser::BooleanContext *ctx) = 0;
  virtual void exitBoolean(propositionParser::BooleanContext *ctx) = 0;

  virtual void enterBooleanAtom(propositionParser::BooleanAtomContext *ctx) = 0;
  virtual void exitBooleanAtom(propositionParser::BooleanAtomContext *ctx) = 0;

  virtual void enterNumeric(propositionParser::NumericContext *ctx) = 0;
  virtual void exitNumeric(propositionParser::NumericContext *ctx) = 0;

  virtual void enterRange(propositionParser::RangeContext *ctx) = 0;
  virtual void exitRange(propositionParser::RangeContext *ctx) = 0;

  virtual void enterIntAtom(propositionParser::IntAtomContext *ctx) = 0;
  virtual void exitIntAtom(propositionParser::IntAtomContext *ctx) = 0;

  virtual void enterInt_constant(propositionParser::Int_constantContext *ctx) = 0;
  virtual void exitInt_constant(propositionParser::Int_constantContext *ctx) = 0;

  virtual void enterFloatAtom(propositionParser::FloatAtomContext *ctx) = 0;
  virtual void exitFloatAtom(propositionParser::FloatAtomContext *ctx) = 0;

  virtual void enterRelop(propositionParser::RelopContext *ctx) = 0;
  virtual void exitRelop(propositionParser::RelopContext *ctx) = 0;

  virtual void enterCls_op(propositionParser::Cls_opContext *ctx) = 0;
  virtual void exitCls_op(propositionParser::Cls_opContext *ctx) = 0;


};

