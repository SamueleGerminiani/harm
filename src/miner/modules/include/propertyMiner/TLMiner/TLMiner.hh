#pragma once

#include <fstream>
#include <mutex>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "DTOperator.hh"
#include "ProgressBar.hpp"
#include "PropertyMiner.hh"
#include "Semaphore.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class NumericExpression;
using NumericExpressionPtr = std::shared_ptr<NumericExpression>;
} // namespace expression
namespace harm {
class Assertion;
using AssertionPtr = std::shared_ptr<Assertion>;
class Context;
using ContextPtr = std::shared_ptr<Context>;
class TemplateImplication;
using TemplateImplicationPtr = std::shared_ptr<TemplateImplication>;
class Trace;
enum class Location;
} // namespace harm

namespace harm {

/*! \class TLMiner
    \brief implements the three-level assertion miner
*/
class TLMiner : public PropertyMiner {

public:
  explicit TLMiner();

  TLMiner(const TLMiner &other) = delete;

  TLMiner &operator=(const TLMiner &other) = delete;

  ~TLMiner() override;

  /// @brief the context is filled with mined assertions
  void mineProperties(const ContextPtr &context,
                      const harm::TracePtr &trace) override;

private:
  /// @brief implements level 3 of parallelization (Template)
  void l3Handler(size_t nThread);
  /// @brief implements level 2 of parallelization (Permutation)
  void
  l2Handler(const TemplateImplicationPtr &t, size_t l3InstId,
            std::unordered_map<size_t, Semaphore *> &l3Instances,
            Semaphore &l3avThreads, std::mutex &l3InstancesGuard,
            std::unordered_map<size_t, size_t> &l3InstToNumThreads);
  /// @brief implements level 1 of parallelization (Evaluation function)
  void l1Handler(const TemplateImplicationPtr &t, size_t l2InstId,
                 size_t l3InstId, Semaphore *l2avThreads,
                 std::unordered_map<size_t, size_t> &l2Instances,
                 std::mutex &l2InstancesGuard);

  /// @brief clears the utility vars and the gathered assertions
  void clear();

  void dumpVac(const std::string &assStr);

  /// @brief collects the assertions mined using DT operators
  void handleDTSolutions(const TemplateImplicationPtr &t,
                         std::vector<DTSolution> &solutions,
                         std::vector<harm::AssertionPtr> &assp,
                         bool isOffset);

  std::vector<std::vector<harm::AssertionPtr>> _collectedAssertions;
  std::mutex _collectedAssertionsGuard;
  ContextPtr _context = nullptr;
  progresscpp::ParallelProgressBar _progressBar;

  //debug
  std::mutex _vacLock;
  std::ofstream _vacFile;
  size_t _nVacAss = 0;
};

} // namespace harm
