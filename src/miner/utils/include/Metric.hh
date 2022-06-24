#pragma once

#include "exp.hh"

#include <unordered_map>

namespace harm {

class Metric {
public:
  Metric() {}

  void assign(std::string name, size_t value) {
    _nameToLogicVarInMetric.at(name)->set(value);
  }
  void assign(std::string name, double value) {
    _nameToNumericVarInMetric.at(name)->set(value);
  }
  double evaluate() { return _exp->evaluate(0); }

  ~Metric() { delete _exp; }
  std::unordered_map<std::string, expression::NumericConstant *> _nameToNumericVarInMetric;
  std::unordered_map<std::string, expression::LogicConstant *> _nameToLogicVarInMetric;
  std::vector<std::string> _vars;
  expression::NumericExpression *_exp;
  std::string _name;
};
} // namespace harm
