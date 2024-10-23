#pragma once
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using EvaluatorClusterElement =
    std::pair<std::string, std::unordered_set<std::string>>;

template <typename T> class Hierarchical {
  using Cluster = std::vector<T>;
  using Level = std::vector<Cluster>;

public:
  Hierarchical(const std::vector<T> objects,
               float (*similarity)(const Cluster &, const Cluster &),
               float minSimilarity = 0.f,
               std::string (*printObject)(const T &) = nullptr);

  ~Hierarchical();
  const Level &getTopLevel();
  const Level &getLevel(size_t l);
  size_t getNumLevels();
  size_t getNumClusters();
  const Level &getLevelWithAtleastClusterSize(size_t n);

  template <typename F>
  friend std::ostream &operator<<(std::ostream &o, Hierarchical<F> &h);

private:
  void execute();

  float (*_similarity)(const Cluster &, const Cluster &);
  std::vector<Level> _levels;
  float **_distMatrix;
  float _minSimilarity;
  std::string (*_printObject)(const T &);
};

#include "Hierarchical.i.hh"
