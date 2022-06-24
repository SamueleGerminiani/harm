
#pragma once
#include "z3++.h"
#include "z3.h"

#include "visitors/ExpToZ3Visitor.hh"

#include <bitset>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace z3 {
struct VarValue {
  VarValue() {}
  VarValue(uint64_t value) : uVal(value) {}
  VarValue(int64_t value) : sVal(value) {}
  VarValue(int64_t value, std::string name) : sVal(value), namedValue(name) {}
  VarValue(bool value) : bVal(value) {}
  VarValue(double value) : dVal(value) {}
  VarValue(float value) : dVal(value) {}
  uint64_t uVal;
  int64_t sVal;
  bool bVal;
  double dVal;
  std::string namedValue = "";
};

using VarName = std::string;
using TypeValue = std::pair<expression::VarType, VarValue>;
using Assignment = std::pair<VarName, TypeValue>;
using TestCase = std::vector<Assignment>;
std::ostream &operator<<(std::ostream &o, const TestCase &tc);

union intToFloat {
  uint32_t i;
  float f;
};
union intToDouble {
  uint64_t i;
  double d;
};

inline bool operator==(TypeValue e1, TypeValue e2) {

  messageErrorIf(
      e1.first != e2.first,
      "== on variables with different types: " + std::to_string((int)e1.first) +
          " vs " + std::to_string((int)e2.first));

  switch (e1.first) {
  case expression::VarType::Bool:
    return e1.second.bVal == e2.second.bVal;
    break;
  case expression::VarType::ULogic:
    return e1.second.uVal == e2.second.uVal;
    break;
  case expression::VarType::SLogic:
    return e1.second.sVal == e2.second.sVal;
    break;
  case expression::VarType::Numeric:
    return e1.second.dVal == e2.second.dVal;
    break;
  default:
    return 0;
  }

  return false;
}
inline std::ostream &operator<<(std::ostream &os, const TypeValue e1) {

  switch (e1.first) {
  case expression::VarType::Bool:
    os << e1.second.bVal;
    break;
  case expression::VarType::ULogic:
    os << e1.second.uVal;
    break;
  case expression::VarType::SLogic:
    os << e1.second.sVal;
    break;
  case expression::VarType::Numeric:
    os << e1.second.dVal;
    break;
  default:
    return os;
  }

  return os;
}

class Z3TestCaseGenerator {
public:
  Z3TestCaseGenerator() = default;

  std::vector<TestCase> generateTestCase(
      expression::Proposition &p, size_t n = 1,
      const std::vector<TestCase> &alreadyGen = std::vector<TestCase>());

  expr propToz3Expr(expression::Proposition &p);
  std::vector<expr> propToz3Expr(std::vector<expression::Proposition *> &ps);
  std::vector<expr>
  propToz3Expr(std::vector<std::shared_ptr<expression::Proposition>> &ps);
  z3::context *getContext();

private:
  z3::expr negateTestCases(const std::vector<TestCase> &tcs, context &c);
  expression::ExpToZ3Visitor _converter;
};
inline std::string valueToString(Assignment &ass) {
  if (ass.second.second.namedValue != "") {
    return ass.second.second.namedValue;
  }
  std::stringstream ss;
  switch (ass.second.first) {
  case expression::VarType::Bool:
    return std::to_string(ass.second.second.bVal);
    break;
  case expression::VarType::ULogic:
    return std::to_string(ass.second.second.uVal);
    break;
  case expression::VarType::SLogic:
    return std::to_string(ass.second.second.sVal);
    break;
  case expression::VarType::Numeric:
    ss << std::setprecision(12) << ass.second.second.dVal;
    return ss.str();
    break;
  default:
    return "Uknown";
  }
  return "Uknown";
}

} // namespace z3
