#pragma once

#include <stack>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "DTLimits.hh"
#include "formula/atom/Atom.hh"
#include "temporalBaseListener.h"
#include "temporalParser.h"

namespace antlr4 {
namespace tree {
class ErrorNode;
} // namespace tree
} // namespace antlr4
namespace expression {

class TemporalExpression;
using TemporalExpressionPtr = std::shared_ptr<TemporalExpression>;
} // namespace expression

namespace harm {
class Trace;
using TracePtr = std::shared_ptr<Trace>;
} // namespace harm
namespace hparser {

class TemporalParserHandler : public temporalBaseListener {

public:
  explicit TemporalParserHandler(const harm::TracePtr &trace);

  ~TemporalParserHandler() override = default;

  std::unordered_map<std::string, std::unordered_set<int>>
  getPhToIdsDomain();

  void addErrorMessage(const std::string &msg);

  bool _useCache = 1;

  expression::TemporalExpressionPtr getTemporalExpression();
  harm::DTOParam getDTOParam();

private:
  std::string printErrorMessage();

  void exitFormula(temporalParser::FormulaContext *ctx) override;
  virtual void
  exitImplication(temporalParser::ImplicationContext *ctx) override;
  virtual void visitErrorNode(antlr4::tree::ErrorNode *node) override;
  virtual void
  exitTformula(temporalParser::TformulaContext *ctx) override;
  virtual void exitSere(temporalParser::SereContext *ctx) override;
  virtual void enterBooleanLayer(
      temporalParser::BooleanLayerContext *ctx) override;

  std::string handleNewPP(const std::string &ph);
  std::string handleNewInst(const std::string &prop);

  std::stack<expression::TemporalExpressionPtr> _tsubFormulas;

  /// map from placeholder to the their domain
  std::unordered_map<std::string, std::unordered_set<int>>
      _phToIdsDomain;
  harm::TracePtr _trace;
  /// the parsed formula
  expression::TemporalExpressionPtr _temporalExpression;
  /// map from placeholder to the corresponding placeholder proposition
  std::unordered_map<std::string, expression::PropositionPtrPtr>
      _phToPP;
  /// map from proposition to the corresponding instance proposition
  std::unordered_map<std::string, expression::PropositionPtr>
      _instToPP;

  /// map from the string representation of a instance proposition to the temporal name
  std::unordered_map<std::string, std::string> _propStrToInst;

  ///keeps track of the number of DT operators
  size_t dtCount = 0;
  ///keeps track of the number of instance propositions
  size_t instCount = 0;

  harm::DTOParam _dto_param;

  ///contains the error messages to be issued on failure
  std::vector<std::string> _errorMessages;
};

} // namespace hparser
