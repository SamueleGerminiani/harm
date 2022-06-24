
#pragma once
#include <algorithm>
#include <unordered_map>
#include <vector>

template <typename T>
std::vector<std::pair<T, T>>
toRanges(std::unordered_map<size_t, std::vector<T>> &labelToValues);

template <typename T>
std::vector<std::pair<T, T>>
toRanges(std::unordered_map<size_t, std::vector<T>> &labelToValues) {
  std::vector<std::pair<T, T>> ranges;

  for (auto &l_vv : labelToValues) {
    std::vector<T> values;
    for (auto &v : l_vv.second) {
      values.push_back(v);
    }
    if (values.empty())
      continue;

    std::sort(values.begin(), values.end());
    if (values.size() > 1) {
      ranges.emplace_back(std::make_pair(values.front(), values.back()));
    } else {
      ranges.emplace_back(std::make_pair(values.back(), values.back()));
    }
  }
  return ranges;
}
