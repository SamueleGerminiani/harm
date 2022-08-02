#pragma once

#include "exp.hh"

#include <unordered_map>

namespace harm {

/*! \class Metric
    \brief Class representing an index used to rank the assertions
*/
class Metric {
public:
  Metric() {}

  /** \brief Assign a variable called 'name' in the metric with 'value' (integer)
   */
  void assign(std::string name, size_t value) {
    _nameToLogicVarInMetric.at(name)->set(value);
  }
  /** \brief Assign a variable called 'name' in the metric with 'value' (float)
   */
  void assign(std::string name, double value) {
    _nameToNumericVarInMetric.at(name)->set(value);
  }
  /** \brief Evaluate the metric with the current values of variables
   */
  double evaluate() { return _exp->evaluate(0); }

  ~Metric() { delete _exp; }
  ///map assertion feature to Value (integer)
  std::unordered_map<std::string, expression::NumericConstant *>
      _nameToNumericVarInMetric;

  ///map assertion feature to Value (float)
  std::unordered_map<std::string, expression::LogicConstant *>
      _nameToLogicVarInMetric;
  ///numeric epression (the actual metric)
  expression::NumericExpression *_exp;
  ///list of assertion features used in the metric
  std::vector<std::string> _vars;
  ///name of the metric
  std::string _name;
};
} // namespace harm
