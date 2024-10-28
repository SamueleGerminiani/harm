#pragma once

#include <stddef.h>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"

namespace expression {
class FloatVariable;
enum class ExpType;
} // namespace expression

namespace harm {
class Assertion;
class Trace;
using TracePtr = std::shared_ptr<Trace>;
class Metric;
///shared pointer to Metric
using MetricPtr = std::shared_ptr<Metric>;

/*! \class Metric
    \brief Class representing an index used to rank the assertions
*/
class Metric {
public:
  /*! \struct FunctionParameter
    \brief used to keep the parameters of the "calibration" function f(x) = 1/(1 + e^(z - kx))^2

*/
  struct FunctionParameter {
    FunctionParameter(double z, double k) : _z(z), _k(k) {
      // not todo
    }
    FunctionParameter() {}

    double _z;
    double _k;
  };

  Metric() = default;

  /** \brief Assign a variable called 'name' in the metric with 'value' (float)
   */

  static harm::MetricPtr parseMetric(const std::string &name,
                                     std::string formula);
  static double evaluateMetric(harm::Assertion &a, Metric &m);

  /** \brief Evaluate the metric with the current values of variables
   */
  double evaluate();

  ~Metric();

  ///Return true if the metric contains the assertion feature
  bool contains(std::string assertionFeature) const;

  ///name of the metric
  std::string _name;

  ///contains the parameters of the function f(x) = 1/(1 + e^(z - kx))^2
  static std::unordered_map<size_t, FunctionParameter> functionParams;

private:
  void assign(const std::string &name, double value);
  ///map assertion feature to Value (integer)
  std::unordered_map<std::string, expression::FloatVariablePtr>
      _nameToFloatVarInMetric;

  ///numeric epression (the actual metric)
  expression::FloatExpressionPtr _exp;
  ///list of assertion features used in the metric
  std::vector<std::string> _vars;

  static std::vector<
      std::tuple<std::string, expression::ExpType, size_t>>
      availableFeatures;

  TracePtr _oneValTrace;
};

} // namespace harm
