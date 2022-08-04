#pragma once

#include "PropertyQualifier.hh"
#include <unordered_map>

namespace harm {

/*! \class Qualifier
    \brief used to rank the assertions
*/
class Qualifier : public PropertyQualifier {

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

public:
  explicit Qualifier();

  ~Qualifier() override {}

  /** \brief rank the assertions in the given context (print or dump the result), return the ranked assertions
   */
  virtual std::vector<Assertion *> qualify(Context &context, Trace *trace) override;

private:
  /** \brief parse a trace containing a fault
   */
  Trace *parseFaultyTrace(const std::string &ftStr);

  /** \brief evaluate the given metric on the given assertion
   */
  double evaluate(Assertion &a, Metric &m);
  /** \brief evalute the "calibrate" funtion for value x
   */
  double scoreFunction(double x, FunctionParameter &fp);
  void printAssertions(Context &context, std::vector<Assertion *> &assertions,
                       Trace *trace);
  /** \brief find fault coverage
   */
  void faultBasedQualification(std::vector<Assertion *> selected, Trace *trace);
  void fbqUsingFaultyTraces(std::vector<Assertion *> &selected);
  /** \brief faults are inserted direclty on the trace
   */
  void fbqUsingFaultOnTraceMode(std::vector<Assertion *> &selected,
                                Trace *trace, size_t &nFaults);
  void dumpAssToFile(Context &context, Trace *trace,
                     std::vector<Assertion *> &assertions);

  /** \brief for each sorting metric, gather the max values reached by any of the input assertions
   */
  std::unordered_map<std::string, double>
  gatherMaxValuesForMetrics(Context &context,
                            std::vector<Assertion *> &assertions);

  std::vector<Assertion *> rankAssertions(Context &context, Trace *trace);
  /** \brief sort the input assertions according to their finalScore
   */
  void sortAssertions(Context &context, Trace *trace, size_t currParamIndex,
                      std::vector<Assertion *> &assertions);

  /** \brief sort the input assertions according to their finalScore, interactive version
   *  \param currParamIndex configure the calibrate function, default is (0.1 - 0.9, that is, 19) 
   */
  void sortAssertions(Context &context, Trace *trace,
                      std::vector<Assertion *> &assertions,
                      size_t currParamIndex = 19);

  /** \brief load the parameters for the interactive ranking with several 'calibration' functions
   */
  void loadParams();
  
  /** \brief run the sat solver to find the minimum number of assertions covering the maximum number of faults
   */
  std::vector<size_t> getCoverageSet();

  /** \brief filter redundant assertions
   */
  std::vector<Assertion *> extractUniqueAssertions(Context &context);
  /** \brief filter redundant assertions, quikly allbeit less precisely
   */
  std::vector<Assertion *> extractUniqueAssertionsFast(Context &context);

  size_t _traceLength;
  std::unordered_map<size_t, FunctionParameter> _functionParams;
  /** \brief filter redundant assertions, quikly allbeit less precisely
   */
  /** \brief max value to calibrate the function in the ranking
   * values go from 1 (range is 0.1-10) to 90 (range is 0.9-1)
   */
  size_t _maxParamIndex = 0;
  ///maps the assertion to the faults they cover
  std::unordered_map<size_t, std::vector<size_t>> _aToF;
  ///maps covered faults to the assertion covering them
  std::unordered_map<size_t, std::vector<size_t>> _fToA;
  ///used in fault-on-trace mode to keep the relation between a fault and corresponding bit a variable
  std::unordered_map<size_t, std::string> _fToVar;
};

} // namespace harm
