#include <algorithm>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <map>
#include <set>
#include <stdint.h>
#include <stdlib.h>
#include <utility>
#include <vector>

#include "CSVtraceReader.hh"
#include "ClsOp.hh"
#include "Contiguous.hh" // IWYU pragma: keep
#include "Float.hh"
#include "Kmeans.hh" // IWYU pragma: keep
#include "Logic.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "expUtils/ExpType.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/NumericExpression.hh"
#include "formula/atom/Variable.hh"
#include "message.hh"
#include "minerUtils.hh"
#include "propositionParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

template <typename T>
std::vector<T> generateClusters(size_t nClusters, size_t nPoints) {

  std::vector<T> randVector;
  size_t clusterID = 0;
  for (size_t i = 0; i < nPoints; i++) {
    randVector.push_back((T)(rand() % 100 + clusterID * 100000));
    clusterID = ++clusterID % nClusters;
  }

  for (size_t i = 0; i < nPoints; i++) {
    randVector.push_back((T)(rand() % 100 + clusterID * 10));
    clusterID = ++clusterID % nClusters;
  }

  for (size_t i = 0; i < nPoints; i++) {
    randVector.push_back((T)(rand() % 100 + clusterID * 100000) * -1);
    clusterID = ++clusterID % nClusters;
  }

  return randVector;
}

template <typename T1, typename T2>
void compareKmeans(size_t n, size_t nClusters) {

  std::vector<T1> randVector1 = generateClusters<T1>(nClusters, n);

  std::sort(randVector1.begin(), randVector1.end());

  std::vector<std::pair<T1, T1>> clusters1;
  clusters1 = kmeansElbow<T1>(randVector1, nClusters * 2, 0.001, 1);

  //debug
  //print clusters
  //for (auto i : clusters1) {
  //  std::cout << i.first << " " << i.second << std::endl;
  //}

  std::vector<T2> randVector2;
  for (auto i : randVector1) {
    randVector2.push_back((T2)i);
  }

  std::vector<std::pair<T2, T2>> clusters2;
  clusters2 = kmeansElbow<T2>(randVector2, nClusters * 2, 0.001, 1);

  messageErrorIf(clusters1.size() != clusters2.size(),
                 "Different sizes of clusters");

  messageErrorIf(clusters1.empty() || clusters2.empty(),
                 "Empty clusters, something went wrong");

  for (size_t i = 0; i < clusters1.size(); i++) {
    ASSERT_EQ(clusters1[i].first, clusters2[i].first);
    ASSERT_EQ(clusters1[i].second, clusters2[i].second);
  }
}

template <typename T1, typename T2>
void compareContiguous(size_t n, size_t nClusters) {

  std::vector<T1> randVector1 = generateClusters<T1>(nClusters, n);

  std::sort(randVector1.begin(), randVector1.end());

  std::vector<std::pair<T1, T1>> clusters1;
  clusters1 = contiguousClustering<T1>(randVector1, nClusters);

  std::vector<T2> randVector2;
  for (auto i : randVector1) {
    randVector2.push_back((T2)i);
  }

  std::vector<std::pair<T2, T2>> clusters2;
  clusters2 = contiguousClustering<T2>(randVector2, nClusters);

  messageErrorIf(clusters1.size() != clusters2.size(),
                 "Different sizes of clusters");

  messageErrorIf(clusters1.empty() || clusters2.empty(),
                 "Empty clusters, something went wrong");

  for (size_t i = 0; i < clusters1.size(); i++) {
    ASSERT_EQ(clusters1[i].first, clusters2[i].first);
    ASSERT_EQ(clusters1[i].second, clusters2[i].second);
  }
}

TEST(ClsTest, compareIntAndLogicKmeans) {

  srand(0);
  compareKmeans<int64_t, SLogic>(1'000, 10);
}

TEST(ClsTest, compareIntAndLogicSequenced) {

  srand(0);
  compareContiguous<int64_t, SLogic>(1'000, 10);
}

TEST(ClsTest, contiguousSingleVsRange) {
  srand(0);

  std::vector<int64_t> values = std::vector<int64_t>{1, 2, 3, 7, 8};
  std::vector<size_t> ivs(values.size());
  std::iota(ivs.begin(), ivs.end(), 0);
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::SInt, 64);
  const TracePtr &trace = generatePtr<Trace>(vars, values.size());
  auto v1 = trace->getIntVariable("v1");
  for (size_t i = 0; i < values.size(); i++) {
    v1->assign(i, values[i]);
  }
  auto nn =
      generatePtr<NumericExpression>(trace->getIntVariable("v1"));
  auto cc = ClusteringConfig();
  cc._clusteringType.insert(ClsType::Contiguous);
  cc._maxClusters = 10000;

  //E
  cc._clsOps.insert(ClsOp::E);
  nn->_clsConfig = cc;

  auto props = genPropsThroughClustering(ivs, nn, false);
  messageErrorIf(props.empty(), "Wrong number of props");
  std::sort(props.begin(), props.end(),
            [](PropositionPtr a, PropositionPtr b) {
              return prop2String(a) < prop2String(b);
            });
  for (size_t i = 0; i < props.size(); i++) {
    auto p = props[i];
    auto v = values[i];
    //EXPECT_EQ(prop2String(p), "v1 inside {" + std::to_string(v) + "} ");
    EXPECT_EQ(prop2String(p), "v1 == " + std::to_string(v));
  }

  //Range
  cc._clsOps.clear();
  cc._clsOps.insert(ClsOp::Range);
  nn->_clsConfig = cc;

  props = genPropsThroughClustering(ivs, nn, false);
  messageErrorIf(props.empty(), "Wrong number of props");
  std::sort(props.begin(), props.end(),
            [](PropositionPtr a, PropositionPtr b) {
              return prop2String(a) < prop2String(b);
            });

  EXPECT_EQ(prop2String(props[0]),
            "v1 inside {[" + std::to_string(values[0]) + ":" +
                std::to_string(values[2]) + "]} ");
  EXPECT_EQ(prop2String(props[1]),
            "v1 inside {[" + std::to_string(values[3]) + ":" +
                std::to_string(values[4]) + "]} ");

  //E + Range
  cc._clsOps.clear();
  cc._clsOps.insert(ClsOp::Range);
  cc._clsOps.insert(ClsOp::E);
  nn->_clsConfig = cc;

  props = genPropsThroughClustering(ivs, nn, false);
  messageErrorIf(props.empty(), "Wrong number of props");
  std::sort(props.begin(), props.end(),
            [](PropositionPtr a, PropositionPtr b) {
              return prop2String(a) < prop2String(b);
            });

  EXPECT_EQ(prop2String(props[0]),
            "v1 inside {[" + std::to_string(values[0]) + ":" +
                std::to_string(values[2]) + "]} ");
  EXPECT_EQ(prop2String(props[1]),
            "v1 inside {[" + std::to_string(values[3]) + ":" +
                std::to_string(values[4]) + "]} ");
}
