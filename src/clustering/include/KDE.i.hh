
#include "utils.hh"
#include <algorithm>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
#define samplesPerIV 100

template <typename T> double default_bandwidth(std::map<T, double> ivTosup) {
  double sum_x = 0.f;
  double sum_x2 = 0.f;
  size_t count = 0;
  for (auto &e : ivTosup) {
    sum_x += e.first * e.second;
    sum_x2 += e.first * e.first * e.second;
    count += e.second;
  }

  double x = sum_x / count;
  double x2 = sum_x2 / count;
  double sigma = sqrt(x2 - (x * x));
  return sigma * (pow((3.0 * count / 4.0), (-1.0 / 5.0)));
}
inline double epanechnikov_kernel(double x, double m, double s) {
  double z = (x - m) / s;
  if (fabs(z) > 1.0) {
    return (0.0);
  }
  return 0.75 * (1.0 - (z * z)) / s;
}

inline double gauss_kernel(double x, double m, double s) {
  double z = (x - m) / s;
  return exp(-0.5 * z * z) / (s * sqrt(2.0 * M_PI));
}

enum Kernel { Gaus, Epan };

template <typename T>
double computeKDE(const std::map<T, double> &ivTosup, double iv, double sample,
                  Kernel kernel, double bw) {
  double ret = 0.f;

  auto itr = ivTosup.find(iv);
  auto itl = itr;
  // right side
  for (; itr != ivTosup.end(); itr++) {
    ret += (Kernel::Epan ? epanechnikov_kernel(sample, itr->first, bw)
                         : gauss_kernel(sample, itr->first, bw)) *
           itr->second;
  }

  // left side
  if (itl != ivTosup.begin()) {
    itl--;
    for (;; itl--) {
      ret += (Kernel::Epan ? epanechnikov_kernel(sample, itl->first, bw)
                           : gauss_kernel(sample, itl->first, bw)) *
             itl->second;
      if (itl == ivTosup.begin()) {
        break;
      }
    }
  }

  return ret;
}
inline bool isMin(std::vector<std::pair<double, double>> &xy, size_t candidate,
                  size_t windowSize) {
  for (size_t i = candidate; i <= candidate + windowSize / 2 && i < xy.size();
       i++) {
    if (xy[candidate].second > xy[i].second) {
      return false;
    }
  }
  for (int i = candidate; i >= (int)candidate - (int)windowSize / 2 && i >= 0;
       i--) {
    if (xy[candidate].second > xy[i].second) {
      return false;
    }
  }
  return true;
}
template <typename T>
void generateHistogram(const std::map<T, double> &ivTosup,
                       std::map<double, T> &xToIV,
                       std::vector<std::pair<double, double>> &xy) {

  double bw = default_bandwidth(ivTosup);
  // this sets the precision of the final histogram
  size_t nSamples = ivTosup.size() * samplesPerIV;
  Kernel kernel = Kernel::Epan;

  std::vector<T> listOfIV;
  for (auto &vs : ivTosup) {
    listOfIV.push_back(vs.first);
  }

  size_t indexIV = 0;
  for (size_t i = 0; i < listOfIV.size() - 1; i++) {
    double x = listOfIV[i];
    double inc_x =
        ((double)listOfIV[i + 1] - (double)listOfIV[i]) / (double)samplesPerIV;
    for (size_t j = 0; j < samplesPerIV; j++) {
      if (x <= ((double)(listOfIV[i] + listOfIV[i + 1])) / 2.f) {
        xToIV[x] = listOfIV[i];
      } else {
        xToIV[x] = listOfIV[i + 1];
      }
      x += inc_x;
    }
  }

  // compute KDE for each sample
  for (auto &[x, IV] : xToIV) {
    xy.emplace_back(x, computeKDE(ivTosup, IV, x, kernel, bw));
  }
  // insert to absolute minimum at the begining and ending of the histogram
  xy.front().second = DBL_MIN;
  xy.back().second = DBL_MIN;
}
template <typename T>
void generateClusters(
    const std::map<double, T> &xToIV,
    std::vector<std::pair<double, double>> &xy, size_t minWindow,
    std::vector<std::pair<std::pair<T, T>, std::vector<T>>> &clusters) {

  // contains the values of a cluster
  std::vector<T> values;
  // last cluster left bound
  T last = xToIV.at(xy[0].first);
  // generate the clusters
  for (size_t i = 1; i < xy.size(); i++) {
    values.push_back(xToIV.at(xy[i].first));
    if (isMin(xy, i, 2 + minWindow) || i == xy.size() - 1) {
      // found a new cluster
      clusters.emplace_back(std::make_pair(last, xToIV.at(xy[i].first)),
                            values);
      last = xToIV.at(xy[i].first);
      values.clear();
    }
  }
}
template <typename T>
std::vector<std::pair<std::pair<T, T>, std::vector<T>>>
getClustersKDE_ReuseHistogram(const std::map<T, double> &ivTosup,
                              std::map<double, T> &xToIV,
                              std::vector<std::pair<double, double>> &xy,
                              size_t minWindow) {
  //<cluster(L,R), valuesInCluster>
  std::vector<std::pair<std::pair<T, T>, std::vector<T>>> ret;

  if (ivTosup.size() == 0) {
    // no clusters
    return ret;
  } else if (ivTosup.size() == 1) {
    // only one cluster with one element
    ret.emplace_back(
        std::make_pair(ivTosup.begin()->first, ivTosup.begin()->first),
        std::vector<T>({ivTosup.begin()->first}));
    return ret;
  }

  // reuse the old values of xToIV and xy (if possible)
  if (xToIV.empty() && xy.empty()) {
    generateHistogram(ivTosup, xToIV, xy);
  }
  generateClusters(xToIV, xy, minWindow, ret);

  return ret;
}

template <typename T>
std::vector<std::pair<std::pair<T, T>, std::vector<T>>>
getClustersKDE(const std::map<T, double> &ivTosup, size_t minWindow) {

  //<cluster(L,R), valuesInCluster>
  std::vector<std::pair<std::pair<T, T>, std::vector<T>>> ret;

  if (ivTosup.size() == 0) {
    // no cluster
    return ret;
  } else if (ivTosup.size() == 1) {
    // only one cluster with one element
    ret.emplace_back(
        std::make_pair(ivTosup.begin()->first, ivTosup.begin()->first),
        std::vector<T>({ivTosup.begin()->first}));
    return ret;
  }

  std::map<double, T> xToIV;
  std::vector<std::pair<double, double>> xy;
  generateHistogram(ivTosup, xToIV, xy);
  generateClusters(xToIV, xy, minWindow, ret);
  return ret;
}

template <typename T>
std::vector<std::pair<T, T>> kdeElbow(std::vector<T> elements, size_t max,
                                      double SDmin_red, bool keepOnlyBest) {

  std::map<T, double> ivTosup;
  for (auto i : elements) {
    ivTosup[i]++;
  }

  //  debug
  //  for (auto i : ivTosup) {
  //    std::cout << i.first << " ";
  //  }
  //  std::cout <<  "\n";

  // store data in the correct format
  std::vector<std::pair<T, T>> ranges;
  double prevSD = DBL_MAX;
  // the inital window covers all values (only one cluster)
  size_t minWindow = ivTosup.size() * samplesPerIV;
  size_t prevRangeSize = 0;

  //[L,R] --> values in cluster
  std::vector<std::pair<std::pair<T, T>, std::vector<T>>> cluster_data;
  // map sample to original value
  std::map<double, T> xToIV;
  // final histogram data
  std::vector<std::pair<double, double>> xy;

  for (size_t i = 1; i <= max && i <= elements.size() && minWindow >= 2; i++) {
    // double div = 100.f;
    double div = 2.f;
    // found a local soulution
    // bool foundLocalSol = 0;
    // how many iterations before terminating on a local solution
    // size_t maxTries = 5;
    // keep going until the reduction of the minWindow lets us find one more
    // cluster
    while (1) {
      // debug
      // std::cout << "div " << div << "\n";
      // std::cout << "minWindow " << minWindow << "\n";
      // std::cout << "size " << cluster_data.size() << "\n";
      // std::cout << "target " << prevRangeSize + 1 << "\n";
      // std::cout << "maxTries " << maxTries << "\n";

      cluster_data =
          getClustersKDE_ReuseHistogram(ivTosup, xToIV, xy, minWindow);

      // if (cluster_data.size() > prevRangeSize) {
      //  foundLocalSol = 1;
      //  minWindow = minWindow * div;
      //  div = div / 2.f + 1.f;
      //}

      minWindow = minWindow / div;
      // if (foundLocalSol) {
      //  maxTries--;
      //}

      // if (prevRangeSize == cluster_data.size() - 1 || minWindow <= 2 ||
      //    maxTries == 0) {
      //  break;
      //}
      if (cluster_data.size() > prevRangeSize || minWindow <= 2) {
        break;
      }
    }

    prevRangeSize = cluster_data.size();

    // group the clusters by label
    std::unordered_map<size_t, std::vector<T>> labelToValues;
    for (size_t j = 0; j < cluster_data.size(); j++) {
      std::vector<T> cls;
      // add multiple occourences of the same value
      for (auto v : cluster_data[j].second) {
        for (size_t i = 0; i < ivTosup.at(v); i++) {
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
      for (auto &v : cl) {
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
