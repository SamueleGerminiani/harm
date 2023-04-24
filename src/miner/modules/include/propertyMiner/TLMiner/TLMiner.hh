#pragma once

#include "AntecedentGenerator.hh"
#include "ProgressBar.hpp"
#include "PropertyMiner.hh"
#include "Semaphore.hh"
#include "visitors/visitors.hh"
#include <map>
#include <mutex>
#include <set>
#include <unordered_set>
#include <vector>
#include <fstream>

#define enPB 1
using namespace std;

namespace harm {

/*! \class TLMiner
    \brief implements the logic of the harm assertion miner
*/
class TLMiner : public PropertyMiner {

public:
  explicit TLMiner();

  TLMiner(const TLMiner &other) = delete;

  TLMiner &operator=(const TLMiner &other) = delete;

  ~TLMiner() override;

  /// @brief the context is filled with mined assertions
  void mineProperties(Context &context, Trace *trace) override;

  /// @brief implements level 3 of parallelization (Template)
  void l3Handler(Context &context, size_t nThread);
  /// @brief implements level 2 of parallelization (Permutation)
  void l2Handler(Template *t, size_t l3InstId,
                 std::unordered_map<size_t, Semaphore *> &l3Instances,
                 Semaphore &l3avThreads, std::mutex &spotStupidity,
                 std::mutex &l3InstancesGuard, std::unordered_map<size_t, size_t>  &l3InstToNumThreads);
  /// @brief implements level 1 of parallelization (Evaluation function)
  void l1Handler(Template *t, size_t l2InstId, size_t l3InstId,
                 Semaphore *l2avThreads,
                 std::unordered_map<size_t, size_t> &l2Instances,
                 std::mutex &l2InstancesGuard);

  /// @brief clears the utility vars and the gathered assertions
  void clear();

private:
  std::vector<Proposition *> _propsCon;
  std::vector<Proposition *> _propsAnt;
  std::vector<Proposition *> _propsAntCon;
  std::vector<Proposition *> _propsDT;
  std::vector<CachedAllNumeric *> _numerics;

  size_t _traceLength;
  std::vector<std::vector<Assertion*>> _collectedAssertions;
  std::mutex _collectedAssertionsGuard;
  progresscpp::ParallelProgressBar _progressBar;
  //debug
  std::mutex _vacLock;
  std::ofstream _vacFile;
  size_t _nVacAss=0;
  };

} // namespace harm
