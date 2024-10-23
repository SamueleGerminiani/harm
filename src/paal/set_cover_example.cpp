/**
 * @file set_cover_example.cpp
 * @brief
 * @author Piotr Smulewicz
 * @version 1.0
 * @date 2014-02-17
 */
//! [Set Cover Example]
#include <iostream>
#include <iterator>
#include <vector>

#include "set_cover/set_cover_wrapper.hh"

std::vector<int> makeRandomSet(int maxSize, int maxValue) {
  std::vector<int> result;
  size_t size = rand() % (maxSize + 1);
  for (int i = 0; i < size; ++i) {
    result.push_back(rand() % maxValue);
  }
  return result;
}

int main() {
  std::vector<std::vector<int>> set_to_elements;
  int n = 1000;
  size_t maxSize = n;
  size_t maxValue = 10000;
  for (size_t i = 0; i < n; i++) {
    set_to_elements.push_back(makeRandomSet(maxSize, maxValue));
  }

  //  std::vector<int> costs(n, 1);
  //  boost::integer_range<int> sets = boost::irange(0, n);
  //  std::vector<int> result;
  //  auto element_index = [](int el) { return el; };
  //  auto cost = paal::greedy::set_cover(
  //      sets, [&](int set) { return costs[set]; },
  //      [&](int set) { return set_to_elements[set]; }, back_inserter(result),
  //      element_index);
  //  std::cout << "Cost: " << cost << std::endl;
  //  std::sort(result.begin(), result.end());
  auto result = findMinSetCover(set_to_elements);
  for (auto el : result) {
    std::cout << el << " ";
  }
  std::cout << "\n";
}
//! [Set Cover Example]
