#pragma once
#include <string>
#include <unordered_set>
namespace dea {

struct Individual {
public:
  Individual() = default;
  Individual(const std::unordered_set<std::string> &_genes,
             const std::pair<size_t, size_t> &objective,
             const size_t &rank)
      : _genes(_genes), _objective(objective), _rank(rank) {
    //not todo
  }
  Individual(const std::unordered_set<std::string> &_genes)
      : _genes(_genes) {
    //not todo
  }

public:
  std::unordered_set<std::string> _genes;
  std::pair<size_t, size_t> _objective;
  size_t _rank = 0;
};
} // namespace dea
