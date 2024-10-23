#include "dkm.hpp"
#include "message.hh"
#include "misc.hh"
#include "utils.hh"
#include <algorithm>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
/// \brief Find the contiguous subsequences in the input list
template <typename T>
std::vector<std::tuple<T, T, size_t>>
findContiguousSubsequences(const std::vector<T> &inputList) {
  std::vector<std::tuple<T, T, size_t>> subsequences;
  std::vector<T> sortedList = inputList;
  std::sort(sortedList.begin(), sortedList.end());

  size_t i = 0;

  while (i < sortedList.size()) {
    //start of a sequence
    T minVal = sortedList[i];
    T maxVal = sortedList[i];
    size_t numElements = 1;

    while (i + 1 < sortedList.size() &&
           //retrieve the rest of the elements of the sequence
           (sortedList[i] + 1 == sortedList[i + 1] ||
            sortedList[i] == sortedList[i + 1])) {
      i++;

      //take care of repeated elements
      if (sortedList[i] != sortedList[i - 1]) {
        numElements++;
      }
      maxVal = sortedList[i];
    }

    subsequences.emplace_back(minVal, maxVal, numElements);
    i++;
  }

  return subsequences;
}
/// \brief Find subsequences of single elements in the input list
template <typename T>
std::vector<std::tuple<T, T, size_t>>
findSingleElements(const std::vector<T> &inputList) {

  std::vector<std::tuple<T, T, size_t>> singleElements;
  std::unordered_map<T, size_t> elementToFrequency;

  for (auto &val : inputList) {
    elementToFrequency[val]++;
  }

  for (auto &[elements, frequency] : elementToFrequency) {
    singleElements.emplace_back(elements, elements, frequency);
  }

  return singleElements;
}

template <typename T>
std::vector<std::pair<T, T>>
contiguousClustering(const std::vector<T> &elements, size_t max,
                     bool dontGenerateRanges = false) {
  std::vector<std::pair<T, T>> ret;

  std::vector<std::tuple<T, T, size_t>> subsequences =
      dontGenerateRanges ? findSingleElements(elements)
                         : findContiguousSubsequences(elements);

  // Sort subsequences by frequency in the range
  std::sort(subsequences.begin(), subsequences.end(),
            [](const std::tuple<T, T, size_t> &a,
               const std::tuple<T, T, size_t> &b) {
              return std::get<2>(a) > std::get<2>(b);
            });

  //keep only the max most frequent subsequences
  if (subsequences.size() > max) {
    subsequences.erase(subsequences.begin() + max,
                       subsequences.end());
  }

  //prepare the output
  for (auto &subsequence : subsequences) {
    ret.emplace_back(std::get<0>(subsequence),
                     std::get<1>(subsequence));
  }

  return ret;
}
