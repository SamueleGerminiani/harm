
#pragma once
#include <algorithm>
#include <map>
#include <vector>

template <typename T>
std::vector<std::tuple<T, T, size_t>>
toRanges(std::map<size_t, std::vector<T>> &labelToValues) {

  std::vector<std::tuple<T, T, size_t>> ranges;

  for (auto &[l, vv] : labelToValues) {
    //FIXME: do we still need this?
    if (vv.empty())
      continue;

    auto [min, max] = std::minmax_element(vv.begin(), vv.end());

    ranges.emplace_back(*min, *max, vv.size());
  }
  return ranges;
}
