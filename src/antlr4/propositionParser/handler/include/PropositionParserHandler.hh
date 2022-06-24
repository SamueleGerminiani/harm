
#pragma once

#include "Trace.hh"
#include "exp.hh"
#include "propositionBaseListener.h"

#include <cmath>
#include <stack>
#include <string>

namespace hparser {

class PropositionParserHandler : public propositionBaseListener {

public:
  explicit PropositionParserHandler(harm::Trace *trace);

  ~PropositionParserHandler() override = default;

  expression::Proposition *getProposition();
  void addErrorMessage(const std::string &msg);

private:
  std::string printErrorMessage();

  bool _abort;

  std::stack<expression::Proposition *> _proposition;
  std::stack<expression::LogicExpression *> _logicExpressions;
  std::stack<expression::NumericExpression *> _numericExpressions;
  harm::Trace *_trace;
  size_t boolStack = 0;
  size_t logicStack = 0;
  size_t numeriStack = 0;
  std::vector<std::string> _errorMessages;

  void enterFile(propositionParser::FileContext *ctx) override;
  void exitFile(propositionParser::FileContext *ctx) override;

  void exitBoolean(propositionParser::BooleanContext *ctx) override;
  virtual void exitLogic(propositionParser::LogicContext *ctx) override;
  virtual void exitNumeric(propositionParser::NumericContext *ctx) override;
  void
  enterBooleanVariable(propositionParser::BooleanVariableContext *ctx) override;
  virtual void
  enterLogicVariable(propositionParser::LogicVariableContext *ctx) override;
  virtual void
  enterNumericVariable(propositionParser::NumericVariableContext *ctx) override;

  virtual void
  enterBooleanConstant(propositionParser::BooleanConstantContext *ctx) override;
  virtual void
  enterLogicConstant(propositionParser::LogicConstantContext *ctx) override;
  virtual void
  enterNumericConstant(propositionParser::NumericConstantContext *ctx) override;

  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;
};
} // namespace hparser
