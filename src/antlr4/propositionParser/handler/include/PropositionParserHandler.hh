
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

  void enterBooleanAtom(propositionParser::BooleanAtomContext *ctx) override;
  virtual void
  enterLogicAtom(propositionParser::LogicAtomContext *ctx) override;
  void enterLogic_constant(propositionParser::Logic_constantContext *ctx) override;
  virtual void enterNumericAtom(propositionParser::NumericAtomContext *ctx) override;

  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;
};
} // namespace hparser
