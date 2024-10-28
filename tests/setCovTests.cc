#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

#include "Qualifier.hh"
#include "message.hh"
#include "misc.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;

std::vector<size_t> makeRandomSet(size_t maxSize, size_t maxValue) {
  std::vector<size_t> result;
  size_t size = rand() % (maxSize + 1);
  for (size_t i = 0; i < size; ++i) {
    result.push_back(rand() % maxValue);
  }
  return result;
}

TEST(SetCovTest, randSetCov) {

  Qualifier q;
  size_t maxFaults = 1000;
  size_t assMaxCov = 10;
  size_t nAss = 10000;

  for (size_t i = 0; i < nAss; i++) {
    q._aidToF[i] = makeRandomSet(assMaxCov, maxFaults);
  }
  for (auto &[aId, faults] : q._aidToF) {
    for (auto f : faults) {
      q._fToAid[f].push_back(aId);
    }
  }
  std::unordered_set<size_t> coveredFaults;
  dirtyTimerMicroseconds("1", 1);
  auto selectesAss = q.getCoverageSet();
  std::sort(selectesAss.begin(), selectesAss.end());
  messageErrorIf(selectesAss.empty(), "No sets selected");
  for (auto a : selectesAss) {
    coveredFaults.insert(q._aidToF[a].begin(), q._aidToF[a].end());
  }
  for (auto &[a, ff] : q._aidToF) {
    for (auto f : ff) {
      messageErrorIf(!coveredFaults.count(f),
                     "Fault " + std::to_string(f) + " not selected");
    }
  }

  //std::cout << "SC solution selected " << selectesAss.size() << " assetions, instead of " << nAss << "\n";
}
