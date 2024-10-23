#include "set_cover.hpp"

#include <boost/range/irange.hpp>
#include <iostream>
#include <iterator>
#include <vector>

std::vector<int>
findMinSetCover(std::vector<std::vector<int>> &set_to_elements) {

  std::vector<int> ret;

  std::vector<int> costs(set_to_elements.size(), 1);
  boost::integer_range<int> sets =
      boost::irange(0, (int)set_to_elements.size());
  std::vector<int> result;
  auto element_index = [](int el) { return el; };
  auto cost = paal::greedy::set_cover(
      sets, [&](int set) { return costs[set]; },
      [&](int set) { return set_to_elements[set]; },
      back_inserter(result), element_index);

  for (auto el : result) {
    ret.push_back(el);
  }
  return ret;
}
