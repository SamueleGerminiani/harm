#pragma once

#include "PropertyQualifier.hh"
#include <unordered_map>

namespace harm {
struct FunctionParameter {
  FunctionParameter(double z, double k) : _z(z), _k(k) {
    // not todo
  }
  FunctionParameter() {}

  double _z;
  double _k;
};

class Qualifier : public PropertyQualifier {

public:
  explicit Qualifier();

  ~Qualifier() override {}

  virtual void qualify(Context &context, Trace *trace) override;

private:
  Trace *parseFaultyTrace(const std::string &ftStr);

  double evaluate(Assertion &a, Metric &m);
  double scoreFunction(double x, FunctionParameter &fp);
  void printAssertions(Context &context, std::vector<Assertion *> &assertions,
                       Trace *trace);
  void faultBasedQualification(std::vector<Assertion *> selected,
                               Trace *trace);
  void fbqUsingFaultyTraces(std::vector<Assertion *> &selected);
  void fbqUsingFaultOnTraceMode(std::vector<Assertion *> &selected,
                                Trace *trace, size_t &nFaults);
  void dumpAssToFile(Context &context, Trace *trace,
                     std::vector<Assertion *> &assertions);
  std::unordered_map<std::string, double>
  gatherMaxValuesForMetrics(Context &context,
                            std::vector<Assertion *> &assertions);

  std::vector<Assertion *> rankAssertions(Context &context, Trace *trace);
  void sortAssertions(Context &context, Trace *trace, size_t currParamIndex,
                      std::vector<Assertion *> &assertions);

  void sortAssertions(Context &context, Trace *trace,
                      std::vector<Assertion *> &assertions,
                      size_t currParamIndex = 19);
  void loadParams();
  std::vector<size_t> getCoverageSet();
  size_t _traceLength;
  std::unordered_map<size_t, FunctionParameter> _functionParams;
  size_t _maxParamIndex = 0;
  std::vector<Assertion *> extractUniqueAssertions(Context &context);
  std::vector<Assertion *> extractUniqueAssertionsFast(Context &context);
  std::unordered_map<size_t, std::vector<size_t>> _aToF;
  std::unordered_map<size_t, std::vector<size_t>> _fToA;
  std::unordered_map<size_t, std::string> _fToVar;
};

} // namespace harm
