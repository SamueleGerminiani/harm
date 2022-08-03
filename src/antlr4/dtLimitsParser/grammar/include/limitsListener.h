
// Generated from limits.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "limitsParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by limitsParser.
 */
class  limitsListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFile(limitsParser::FileContext *ctx) = 0;
  virtual void exitFile(limitsParser::FileContext *ctx) = 0;

  virtual void enterParameter(limitsParser::ParameterContext *ctx) = 0;
  virtual void exitParameter(limitsParser::ParameterContext *ctx) = 0;

  virtual void enterAtom(limitsParser::AtomContext *ctx) = 0;
  virtual void exitAtom(limitsParser::AtomContext *ctx) = 0;

  virtual void enterDep(limitsParser::DepContext *ctx) = 0;
  virtual void exitDep(limitsParser::DepContext *ctx) = 0;

  virtual void enterWidth(limitsParser::WidthContext *ctx) = 0;
  virtual void exitWidth(limitsParser::WidthContext *ctx) = 0;

  virtual void enterAll(limitsParser::AllContext *ctx) = 0;
  virtual void exitAll(limitsParser::AllContext *ctx) = 0;

  virtual void enterOffset(limitsParser::OffsetContext *ctx) = 0;
  virtual void exitOffset(limitsParser::OffsetContext *ctx) = 0;

  virtual void enterNegated(limitsParser::NegatedContext *ctx) = 0;
  virtual void exitNegated(limitsParser::NegatedContext *ctx) = 0;

  virtual void enterEffort(limitsParser::EffortContext *ctx) = 0;
  virtual void exitEffort(limitsParser::EffortContext *ctx) = 0;

  virtual void enterStrategy(limitsParser::StrategyContext *ctx) = 0;
  virtual void exitStrategy(limitsParser::StrategyContext *ctx) = 0;


};

