
#pragma once

#include "Hierarchical.hh"
#include "utils.hh"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <limits.h>
#include <map>
#include <message.hh>
#include <numeric>
#include <set>
#include <string>

using EvaluatorClusterElement =
    std::pair<std::string, std::unordered_set<std::string>>;

template <typename T>
Hierarchical<T>::Hierarchical(const std::vector<T> objects,
                              float (*similarity)(const Cluster &,
                                                  const Cluster &),
                              float minSimilarity,
                              std::string (*printObject)(const T &))
    : _similarity(similarity), _minSimilarity(minSimilarity),
      _printObject(printObject) {
  assert(minSimilarity <= 1.f && minSimilarity >= 0.f);
  // generate level 0 where all clusters are of size 1 (one for each object)
  Level l0;
  for (const T &e : objects) {
    l0.push_back(Cluster({e}));
  }
  _levels.push_back(l0);

  _distMatrix = new float *[_levels[0].size()];
  for (size_t i = 0; i < l0.size(); i++) {
    _distMatrix[i] = new float[_levels[0].size()];
    // init
    for (size_t j = 0; j < _levels[0].size(); j++) {
      _distMatrix[i][j] = 0.f;
    }
  }

  // perform clustering
  execute();
}

template <typename T> Hierarchical<T>::~Hierarchical() {
  for (size_t i = 0; i < _levels[0].size(); i++) {
    delete[] _distMatrix[i];
  }
  delete _distMatrix;
}

template <typename T>
const typename Hierarchical<T>::Level &
Hierarchical<T>::getTopLevel() {
  return _levels.back();
}
template <typename T>
const typename Hierarchical<T>::Level &
Hierarchical<T>::getLevelWithAtleastClusterSize(size_t n) {
  for (const auto &level : _levels) {
    for (const auto &cluster : level) {
      if (cluster.size() < n) {
        goto nextLevel;
      }
    }
    return level;

  nextLevel:;
  }
  // if we don't find a suitable level
  return getTopLevel();
}

template <typename T>
const typename Hierarchical<T>::Level &
Hierarchical<T>::getLevel(size_t l) {
  return _levels[l];
}

template <typename T> void Hierarchical<T>::execute() {
  std::unordered_set<size_t> deletedRows;
  std::unordered_set<size_t> deletedCols;

  // compute distance matrix
  size_t currentLevel = 0;
  auto &l0 = _levels[currentLevel];
  const size_t matrixSize = _levels[currentLevel].size();
  for (size_t i = 0; i < matrixSize; i++) {
    for (size_t j = 0; j < matrixSize; ++j) {
      if (i == j) {
        _distMatrix[i][j] = 0.f;
        continue;
      }
      _distMatrix[i][j] = _similarity(l0[i], l0[j]);
    }
  }
  /*
   * DEBUG - print dist matrix
  for (size_t i = 0; i < matrixSize; i++) {
    for (size_t j = 0; j < matrixSize; ++j) {
      if (deletedCols.count(j) || deletedRows.count(i)) {
        continue;
      }
      std::cout << std::setprecision(1) << _distMatrix[i][j] << "  ";
    }
    std::cout << "\n";
  }
  */

  while (deletedRows.size() < matrixSize - 1) {

    currentLevel = _levels.size() - 1;
    // find max
    size_t maxi = (1ULL << 63ULL);
    size_t maxj = (1ULL << 63ULL);
    float max = -1.f;
    for (size_t i = 0; i < matrixSize; i++) {
      for (size_t j = 0; j < matrixSize; j++) {
        if (i == j || deletedCols.count(j) || deletedRows.count(i)) {
          continue;
        }
        if (_distMatrix[i][j] > max) {
          max = _distMatrix[i][j];
          maxi = i;
          maxj = j;
        }
      }
    }

    if ((max <= _minSimilarity)) {
      break;
    }

    // copy the current level
    auto l = _levels[currentLevel];
    // merge clusters

    // DEBUG
    assert(l[maxj].size() > 0);
    for (const auto &i_obj : l[maxi]) {
      l[maxj].push_back(i_obj);
    }
    l[maxi].clear();
    _levels.push_back(l);

    // delete cols & rows
    deletedRows.insert({maxi});
    deletedCols.insert({maxi});
    // recompute scores for new cluster
    // row
    for (size_t j = 0; j < matrixSize; j++) {
      if (j == maxj || deletedCols.count(j)) {
        _distMatrix[maxj][j] = 0.f;
        continue;
      }
      _distMatrix[maxj][j] = _similarity(l[j], l[maxj]);
    }
    // col
    for (size_t i = 0; i < matrixSize; i++) {
      if (i == maxj || deletedRows.count(i)) {
        _distMatrix[i][maxj] = 0.f;
        continue;
      }
      _distMatrix[i][maxj] = _similarity(l[i], l[maxj]);
    }
    /*
     * DEBUG - print dist matrix
    for (size_t i = 0; i < matrixSize; i++) {
      for (size_t j = 0; j < matrixSize; ++j) {
        if (deletedCols.count(j) || deletedRows.count(i)) {
          continue;
        }
        std::cout << std::setprecision(5) << _distMatrix[i][j] << "  ";
      }
      std::cout << "\n";
    }
    */
  }
  // remove levels of empty clusters
  for (auto &l : _levels) {
    l.erase(std::remove_if(begin(l), end(l),
                           [](Cluster &c1) { return c1.empty(); }),
            end(l));
  }
}

template <typename T> size_t Hierarchical<T>::getNumLevels() {
  return _levels.size();
}
template <typename T> size_t Hierarchical<T>::getNumClusters() {
  size_t count = 0;
  for (const auto &level : _levels) {
    for (const auto &cluster : level) {
      count += cluster.size();
    }
  }
  return count;
}

template <typename F>
std::ostream &operator<<(std::ostream &o, Hierarchical<F> &h) {
  assert(h._printObject != nullptr);
  size_t levelID = 0;
  for (const auto &level : h._levels) {
    o << "Level " << levelID << "=======================\n";
    size_t clusterID = 0;
    for (const auto &cluster : level) {
      o << "Cluster " << clusterID << "-----------------------\n";
      for (const auto &obj : cluster) {
        o << h._printObject(obj) << " ";
      }
      clusterID++;
      o << "\n";
    }
    levelID++;
  }
  return o;
}

inline std::string
printObjectEvaluator(const EvaluatorClusterElement &obj) {
  std::string ret = "";
  ret += obj.first;
  return ret;
}


float inline similarityOverlapping(
    const std::vector<EvaluatorClusterElement> &e1,
    const std::vector<EvaluatorClusterElement> &e2) {

  std::unordered_map<std::string, size_t> instToNElements;
  size_t nClusters = e1.size() + e2.size();

  for (auto &[id, instances] : e1) {
    for (auto inst : instances) {
      //init
      if (!instToNElements.count(inst)) {
        instToNElements[inst] = 0;
      }
      instToNElements.at(inst)++;
    }
  }

  for (auto &[id, instances] : e2) {
    for (auto inst : instances) {
      if (!instToNElements.count(inst)) {
        instToNElements[inst] = 0;
      }
      instToNElements.at(inst)++;
    }
  }

  size_t notOverlappingScore = 0;
  for (auto &[inst, n] : instToNElements) {
    //if nCluster - n == 0 then the instance is contained in all clusters (best case)
    notOverlappingScore += nClusters - n;
  }

  //(instToNElements.size()*(nClusters-1) is the worst case where all instances are
  //non-overlapping
  messageErrorIf(nClusters < 2,
                 "nClusters == " + std::to_string(nClusters));
  messageErrorIf(instToNElements.size() == 0,
                 "instToNElements.size() == 0");

  return 1.f - (double)notOverlappingScore /
                   (instToNElements.size() * (nClusters - 1));
}

using EvaluatorClusterElement =
    std::pair<std::string, std::unordered_set<std::string>>;

inline size_t getNUniqueElementsOverlapping(
    std::vector<EvaluatorClusterElement> &c) {

  std::unordered_set<std::string> uniqueInstances;

  for (auto &[id, instances] : c) {
    for (auto &inst : instances) {
      uniqueInstances.insert(inst);
    }
  }

  return uniqueInstances.size();
}

inline size_t getNUniqueElementsOverlapping(
    std::vector<std::vector<EvaluatorClusterElement>>
        &listOfClusters) {

  std::unordered_set<std::string> uniqueInstances;

  for (auto &c : listOfClusters) {
    for (auto &[id, instances] : c) {
      for (auto &inst : instances) {
        uniqueInstances.insert(inst);
      }
    }
  }

  return uniqueInstances.size();
}

inline double getScoreOverlapping(
    std::vector<std::vector<EvaluatorClusterElement>> &level,
    size_t maxElements) {

  double meanClScore = 0.f;

  for (auto cl : level) {

    std::unordered_set<std::string> uniqueElements;

    size_t sumInstances = 0;
    for (auto &[id, instances] : cl) {
      for (auto inst : instances) {
        uniqueElements.insert(inst);
      }
      sumInstances += instances.size();
    }

    meanClScore +=
        ((double)uniqueElements.size() / (double)sumInstances);
  }

  meanClScore /= level.size();

  double finalScore = 0.f;

  finalScore = (1.f - meanClScore);
    //* ((1.f - (double)level.size() / maxElements));

  return finalScore;
}

inline std::vector<std::vector<EvaluatorClusterElement>>
hcElbowOverlapping(
    std::unordered_map<std::string, std::unordered_set<std::string>>
        elements) {

  std::vector<std::vector<EvaluatorClusterElement>> ret;
  std::vector<EvaluatorClusterElement> arrangedElements;
  std::vector<EvaluatorClusterElement> zeroInstancesCluster;

  for (auto &[id, instances] : elements) {
    if (!instances.empty()) {
      arrangedElements.emplace_back(id, instances);
    } else {
      zeroInstancesCluster.emplace_back(id, elements.at(id));
    }
  }

  //perform hc
  Hierarchical<EvaluatorClusterElement> cls(
      arrangedElements, &similarityOverlapping, 0.f,
      &printObjectEvaluator);

  //  debug -- print levels
  //  std::cout << cls << "\n";

  //  double prevMean = DBL_MAX;

  double maxScore = 0;
  int maxIndex = 0;

  for (size_t i = 0; i < cls.getNumLevels(); i++) {
    //set of clusters at level i
    auto level = cls.getLevel(i);

    double thisLevelScore =
        getScoreOverlapping(level, elements.size());

    if (thisLevelScore > maxScore) {
      maxScore = thisLevelScore;
      maxIndex = i;
    }
    std::cout << thisLevelScore << "\n";

    //std::cout << "Mean:" << mean << "\n";
    //std::cout << "prevMean:" << prevMean << "\n";
    //std::cout << "SDmax_red:" << SDmax_red << "\n";
    //std::cout << "Reduction:"
    //          << std::abs((double)prevMean - (double)mean) / (double)prevMean
    //          << "\n";

    // continue only if the mean reduction is above the
    // defined threshold
    //    if (std::abs((double)prevMean - (double)mean) / (double)prevMean <
    //        SDmax_red) {
    //      std::cout << "Saving level:" << i - 1 << "\n";
    //      for (auto cl : cls.getLevel(i - 1)) {
    //        ret.push_back(cl);
    //      }
    //      return ret;
    //    }
    //
    //    prevMean = mean;
    //  }
    //  std::cout << "Saving top level"<< "\n";
    //  for (auto cl : cls.getTopLevel()) {
    //    ret.push_back(cl);
  }

  //std::cout << "Level " << maxIndex << "\n";
  //std::cout << "MinScore " << maxScore << "\n";
  //std::cout << "-------------------------------"
  //          << "\n";

  for (auto cl : cls.getLevel(maxIndex)) {
    ret.push_back(cl);
  }

  //ret.push_back(zeroInstancesCluster);

  std::sort(begin(ret), end(ret),
            [](std::vector<EvaluatorClusterElement> &c1,
               std::vector<EvaluatorClusterElement> &c2) {
              return getNUniqueElementsOverlapping(c1) <
                     getNUniqueElementsOverlapping(c2);
            });

  //debug - print sorted clusters
  //  for (size_t i = 0; i < ret.size(); i++) {

  //   auto cls = ret[i];

  //    std::cout << "Score: " << getNUniqueElementsOverlapping(cls) << "\n";

  //for (auto inst : cls) {
  //  std::cout << inst.first << " ";
  //}

  //std::cout << "\n---------------------------------"
  //          << "\n";
  //std::cout << i << ":" << cls.size() << "\n";
  //}

  return ret;
}
