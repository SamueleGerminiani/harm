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

#define dumpVacAss 0
#define enPB 1
using namespace std;

namespace harm {

/// @brief Ateam property miner declaration.
/// This class mines temporal assertions by using assertion templates
class TLMiner : public PropertyMiner {

public:
  explicit TLMiner();

  /// @brief Copy constructor.
  /// @param other The TLMiner to be copied.
  TLMiner(const TLMiner &other) = delete;

  /// @brief Assignment operator
  /// @param other The TLMiner to be copied.
  TLMiner &operator=(const TLMiner &other) = delete;

  /// @brief Destructor.
  ~TLMiner() override;

  /// @brief mineProperties.
  /// @param context The context of influence
  /// @param traceRepository The trace repository used by the miner
  void mineProperties(Context &context, Trace *traceRepository) override;

  void l3Handler(Context &context, size_t nThread);
  void l2Handler(Template *t, size_t l3InstId,
                 std::unordered_map<size_t, Semaphore *> &l3Instances,
                 Semaphore &l3avThreads, std::mutex &spotStupidity,
                 std::mutex &l3InstancesGuard, std::unordered_map<size_t, size_t>  &l3InstToNumThreads);
  void l1Handler(Template *t, size_t l2InstId, size_t l3InstId,
                 Semaphore *l2avThreads,
                 std::unordered_map<size_t, size_t> &l2Instances,
                 std::mutex &l2InstancesGuard);

  void clear();

private:
  std::vector<Proposition *> _propsCon;
  std::vector<Proposition *> _propsAnt;
  std::vector<Proposition *> _propsAntCon;
  std::vector<Proposition *> _propsDT;
  std::vector<CachedAllNumeric *> _numerics;
  // @brief trace length
  size_t _traceLength;
  std::vector<std::vector<Assertion*>> _collectedAssertions;
  std::mutex _collectedAssertionsGuard;
  progresscpp::ParallelProgressBar _progressBar;
#if dumpVacAss
  std::mutex vacLock;
#endif
  };

} // namespace harm
