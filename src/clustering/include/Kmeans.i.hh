
#include "dkm.hpp"
#include "utils.hh"
#include <algorithm>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename T>
std::vector<std::pair<T, T>> kmeans(std::vector<T> elements, size_t k) {
  // store data in the correct format
  std::vector<std::array<T, 1>> data;
  for (size_t i = 0; i < elements.size(); i++) {
    data.push_back(std::array<T, 1>({(T)(elements[i])}));
  }

  std::vector<std::pair<T, T>> ranges;
  double prevSD = DBL_MAX;

  // generate the clusters
  auto cluster_data = dkm::kmeans_lloyd(data, k);

  // group the clusters by label
  std::unordered_map<size_t, std::vector<T>> labelToValues;
  for (size_t j = 0; j < std::get<1>(cluster_data).size(); j++) {
    auto label = std::get<1>(cluster_data)[j];
    labelToValues[label].push_back(data[j][0]);
  }

  // translate the customers into ranges [min, max]
  auto rr = toRanges<T>(labelToValues);
  // add the ranges to the final list
  ranges.insert(ranges.end(), rr.begin(), rr.end());

  return ranges;
}

template <typename T>
std::vector<std::pair<T, T>> kmeansElbow(std::vector<T> elements, size_t max,
                                         double SDmin_red, bool keepOnlyBest) {
  // store data in the correct format
  std::vector<std::array<T, 1>> data;
  for (size_t i = 0; i < elements.size(); i++) {
    data.push_back(std::array<T, 1>({(T)(elements[i])}));
  }

  std::vector<std::pair<T, T>> ranges;
  double prevSD = DBL_MAX;
  for (size_t i = 1; i <= max && i <= elements.size(); i++) {
    // generate the clusters
    auto cluster_data = dkm::kmeans_lloyd(data, i, 100);

    // group the clusters by label
    std::unordered_map<size_t, std::vector<T>> labelToValues;
    for (size_t j = 0; j < std::get<1>(cluster_data).size(); j++) {
      auto label = std::get<1>(cluster_data)[j];
      labelToValues[label].push_back(data[j][0]);
    }

    // compute the standard deviation
    double totSD = 0.f;
    auto means = std::get<0>(cluster_data);
    for (size_t k = 0; k < means.size(); k++) {
      double mean = means[k][0];
      double currSD = 0.f;
      for (auto &v : labelToValues[k]) {
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
    // translate the customers into ranges [min, max]
    auto rr = toRanges<T>(labelToValues);
    // add the ranges to the final list
    if (keepOnlyBest) {
      ranges.clear();
    }
    ranges.insert(ranges.end(), rr.begin(), rr.end());
    prevSD = totSD;

  }

  // remove redundant ranges
  std::set<std::pair<T, T>> uniqueRanges;
  for (auto &lr : ranges) {
    uniqueRanges.insert(lr);
  }

  std::vector<std::pair<T, T>> ret;

  //translate the ranges into the output format
  for (auto &lr : uniqueRanges) {
    ret.push_back(lr);
  }
  std::sort(ret.begin(), ret.end(),
            [](const std::pair<T, T> &e1, const std::pair<T, T> &e2) {
              return e1.second <= e2.first;
            });

  return ret;
}

