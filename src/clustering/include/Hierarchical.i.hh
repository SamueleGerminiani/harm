
#pragma one

#include "Hierarchical.hh"
#include "utils.hh"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <map>
#include <numeric>
#include <set>

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
const typename Hierarchical<T>::Level &Hierarchical<T>::getTopLevel() {
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
const typename Hierarchical<T>::Level &Hierarchical<T>::getLevel(size_t l) {
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

template <typename T> std::string printObject(const std::pair<T, double> &obj) {
  std::string ret = "";
  ret += std::to_string(obj.first);
  return ret;
}
template <typename T>
float similarity(const std::vector<std::pair<T, double>> &e1,
                 const std::vector<std::pair<T, double>> &e2) {
  double s1 = 0.f;
  double s2 = 0.f;

  double weigths = 0.f;
  double sum = 0.f;
  for (auto &e : e1) {
    weigths += e.second;
    sum += e.first * e.second;
  }
  s1 = sum / weigths;

  weigths = 0.f;
  sum = 0.f;
  for (auto &e : e2) {
    weigths += e.second;
    sum += e.first * e.second;
  }
  s2 = sum / weigths;

  return std::abs(s1 - s2) == 0 ? DBL_MAX : 1.f / std::abs(s1 - s2);
}
template <typename T>
std::vector<std::pair<T, T>> hcElbow(std::vector<T> elements, size_t max,
                                     double SDmin_red, bool keepOnlyBest) {

  std::map<T, double> ivTosup;
  for (auto i : elements) {
    ivTosup[i]++;
  }
  //convert the values to the correct data format
  std::vector<std::pair<T, double>> uniqValWithSupport;
  for (auto &[v, sup] : ivTosup) {
    uniqValWithSupport.emplace_back(v, sup);
  }

  //perform hc
  Hierarchical<std::pair<T, double>> cls(uniqValWithSupport, &similarity<T>,
                                         0.f, &printObject<T>);

  std::vector<std::pair<T, T>> ranges;
  double prevSD = DBL_MAX;

  for (size_t i = 0; i < cls.getNumLevels() && i <= max; i++) {
      //set of clusters at level i
    auto level = cls.getLevel(cls.getNumLevels() - i - 1);

    // group the clusters by label
    std::unordered_map<size_t, std::vector<T>> labelToValues;
    for (size_t j = 0; j < level.size(); j++) {
      std::vector<T> cls;
      // add multiple occourences of the same value
      for (auto &[v, s] : level[j]) {
        for (size_t i = 0; i < s; i++) {
          cls.push_back(v);
        }
      }
      // add the cluster
      labelToValues[j] = cls;
    }

    // compute the standard deviation
    double totSD = 0.f;
    for (auto &[l, cl] : labelToValues) {
      double mean =
          (double)std::accumulate(begin(cl), end(cl), 0.f) / cl.size();
      double currSD = 0.f;
      for (auto v : cl) {
        currSD += std::pow(mean - (double)v, 2);
      }
      currSD = std::sqrt(currSD / (double)elements.size());
      totSD += currSD;
    }

    // continue only if the standard deviation reduction is above the
    // defined threshold
    if (std::abs((double)prevSD - (double)totSD) / (double)prevSD < SDmin_red) {
      break;
    }
    prevSD = totSD;
    // translate the clusters into ranges [min, max]
    auto rr = toRanges<T>(labelToValues);
    // add the ranges to the final list
    if (keepOnlyBest) {
      ranges.clear();
    }
    ranges.insert(ranges.end(), rr.begin(), rr.end());
  }

  // remove redundant ranges
  std::set<std::pair<T, T>> uniqueRanges;
  for (auto &lr : ranges) {
    uniqueRanges.insert(lr);
  }

  //	translate the ranges into the output format
  std::vector<std::pair<T, T>> ret;
  for (auto &lr : uniqueRanges) {
    ret.push_back(lr);
  }
  std::sort(ret.begin(), ret.end(),
            [](const std::pair<T, T> &e1, const std::pair<T, T> &e2) {
              return e1.second <= e2.first;
            });

  return ret;
}
