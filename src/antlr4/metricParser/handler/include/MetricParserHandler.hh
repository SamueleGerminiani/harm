#pragma once

#include "Trace.hh"
#include "metricBaseListener.h"
#include "Metric.hh"

#include <cmath>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

namespace hparser{

class MetricParserHandler : public metricBaseListener {

public:
  explicit MetricParserHandler(harm::Trace * trace);

  ~MetricParserHandler() override = default;

  harm::Metric* getMetric();
  void addErrorMessage(const std::string &msg);

private:
  std::string printErrorMessage();
  bool _abort;
  std::vector<std::string> _errorMessages;

  std::stack<expression::LogicExpression *> _logicExpressions;
  std::stack<expression::NumericExpression *> _numericExpressions;
  harm::Trace * _trace;
  size_t logicStack = 0;
  size_t numeriStack = 0;
  harm::Metric* _metric;


  void enterFile(metricParser::FileContext *ctx) override;
  void exitFile(metricParser::FileContext *ctx) override;

  virtual void exitLogic(metricParser::LogicContext *ctx) override;
  virtual void exitNumeric(metricParser::NumericContext *ctx) override;
  virtual void enterLogicVariable(metricParser::LogicVariableContext *ctx) override;
  virtual void enterNumericVariable(metricParser::NumericVariableContext *ctx) override;

  virtual void enterLogicConstant(metricParser::LogicConstantContext *ctx) override;
  virtual void enterNumericConstant(metricParser::NumericConstantContext *ctx) override;


  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;
};
}
