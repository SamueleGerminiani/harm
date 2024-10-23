
#pragma once

#include <unordered_map>
#include <utility>
#include <vector>

#include "formula/atom/Atom.hh"

namespace expression {
class NumericExpression;
using NumericExpressionPtr = std::shared_ptr<NumericExpression>;
} // namespace expression

namespace harm {

class TemplateImplication;
using TemplateImplicationPtr = std::shared_ptr<TemplateImplication>;
class Assertion;
using AssertionPtr = std::shared_ptr<Assertion>;
class Metric;
using MetricPtr = std::shared_ptr<Metric>;
enum class Location;

/*! \class Context
    \brief Class representing a set of props, numerics, templates, metrics and assertions
*/
class Context {

public:
  Context() = default;
  ~Context();
  //delete all other constructors
  Context(const Context &) = delete;
  Context &operator=(const Context &) = delete;

  Context(const std::string &name);

  std::string _name;

  //domains
  std::unordered_map<int, std::vector<expression::PropositionPtr>>
      _domainIdToProps;
  std::unordered_map<int,
                     std::vector<expression::NumericExpressionPtr>>
      _domainIdToNumerics;

  std::vector<TemplateImplicationPtr> _templates;

  std::vector<expression::NumericExpressionPtr> _numerics;

  //this is filled by the miner
  std::vector<AssertionPtr> _assertions;

  ///sorting metrics
  std::vector<MetricPtr> _sort;
  ///filtering metrics
  std::vector<std::pair<MetricPtr, double>> _filter;
};
//using shared pointer for the context
using ContextPtr = std::shared_ptr<Context>;
} // namespace harm
