#pragma once

#include <stddef.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "PropertyQualifier.hh"

class SetCovTest_randSetCov_Test;

namespace harm {
class Assertion;
using AssertionPtr = std::shared_ptr<Assertion>;
class Context;
class Metric;
using MetricPtr = std::shared_ptr<Metric>;
class Trace;

/*! \class Qualifier
    \brief used to rank the assertions
*/
class Qualifier : public PropertyQualifier {

public:
  explicit Qualifier();

  ~Qualifier() override {}

  void init();

  /** \brief rank the assertions in the given context (print or dump the result), return the ranked assertions
   */
  virtual std::vector<harm::AssertionPtr>
  qualify(Context &context, const harm::TracePtr &trace) override;

private:
  /** remove assertions of the form G(a -> a)
   */
  std::vector<AssertionPtr>
  patchDiscardAssertions(std::vector<AssertionPtr> &inAssertions,
                         TracePtr trace);

  /** \brief parse a trace containing a fault
   */
  harm::TracePtr parseFaultyTrace(const std::string &ftStr);

  void printAssertions(Context &context,
                       std::vector<harm::AssertionPtr> &assertions,
                       const harm::TracePtr &trace);
  /** \brief find fault coverage
   */
  void
  faultBasedQualification(std::vector<harm::AssertionPtr> selected,
                          const harm::TracePtr &trace);

  void fbqUsingFaultyTraces(
      const std::vector<harm::AssertionPtr> &selected,
      const harm::TracePtr &originalTrace);

  void dumpAssToFile(Context &context, const harm::TracePtr &trace,
                     std::vector<harm::AssertionPtr> &assertions);

  /** \brief for each sorting metric, gather the max values reached by any of the input assertions
   */
  std::unordered_map<std::string, double> getMaxValuesForSortMetrics(
      std::vector<MetricPtr> &metrics,
      std::vector<harm::AssertionPtr> &assertions);

  /** \brief for each filtering metric, gather the max values reached by any of the input assertions
   */
  std::unordered_map<std::string, double>
  getMaxValuesForFilterMetrics(
      std::vector<std::pair<MetricPtr, double>> &metrics,
      std::vector<harm::AssertionPtr> &assertions);

  /** \brief rank the assertions in the given context using sorting metrics
   */
  std::vector<harm::AssertionPtr>
  rankAssertions(const std::vector<harm::AssertionPtr> &assertions,
                 std::vector<MetricPtr> &sort);

  /** \brief cluster assertios by use
   */
  std::vector<std::pair<size_t, std::vector<harm::AssertionPtr>>>
  clusterAssertions(const std::vector<harm::AssertionPtr> &assertions,
                    const harm::TracePtr &trace);

  /** \brief remove all assertion with a finalScore lower than the given threshold
   */
  void filterAssertionsWithFrank(
      std::vector<harm::AssertionPtr> &assertions);

  /** \brief filter redundant assertions
   */
  void filterRedundantAssertions(
      std::vector<harm::AssertionPtr> &assertions);

  /** \brief filter the input assertions using the 'filter' metrics
   */
  void filterAssertionsWithMetrics(
      std::vector<harm::AssertionPtr> &assertions,
      std::vector<std::pair<MetricPtr, double>> &metrics);

  /** \brief sort the input assertions according to their finalScore
   */
  void sortAssertionsWithMetrics(
      std::vector<MetricPtr> &metrics,
      std::vector<harm::AssertionPtr> &assertions,
      size_t currParamIndex = 19);

  /** \brief run the sat solver to find the minimum number of assertions covering the maximum number of faults
   */
  std::vector<size_t> getCoverageSet();

  /** \brief filter redundant assertions, quikly allbeit less precisely
   */
  std::vector<harm::AssertionPtr> extractUniqueAssertionsFast(
      const std::vector<harm::AssertionPtr> &inAssertions);

  /** \brief filter redundant assertions
   */
  std::vector<harm::AssertionPtr> extractUniqueAssertions(
      const std::vector<harm::AssertionPtr> &inAssertions);

  void fillAssertionsWithFaultCoverage(
      const std::vector<harm::AssertionPtr> &assertions,
      const harm::TracePtr &trace);

  bool
  requiresFaultCoverage(const std::vector<harm::MetricPtr> &metrics);
  bool requiresFaultCoverage(
      const std::vector<std::pair<harm::MetricPtr, double>> &metrics);

  ///keeps the the assertions covering the maximum numbers of faults: id to assertion
  std::vector<AssertionPtr> _minCoveringAssertions;

  ///keeps track of the original assertions before filtering or sorting
  std::vector<AssertionPtr> _originalAssertions;

  /** \brief max value to calibrate the function in the ranking
   * values go from 1 (range is 0.1-10) to 90 (range is 0.9-1)
   */
  size_t _maxParamIndex = 90;
  ///maps the assertion to the faults they cover
  std::unordered_map<size_t, std::vector<size_t>> _aidToF;
  ///maps covered faults to the assertion covering them
  std::unordered_map<size_t, std::vector<size_t>> _fToAid;

  friend SetCovTest_randSetCov_Test;
};

} // namespace harm
