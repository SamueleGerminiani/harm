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

template <typename T>
std::vector<std::pair<T, T>>
hcElbowHarm(std::vector<T> elements, size_t max = 20, double SDmin_red = 0.1f,
            bool keepOnlyBest = false);

std::vector<std::vector<EvaluatorClusterElement>> hcElbowEvaluator( std::unordered_map<std::string, std::unordered_set<std::string>> elements);

#include "Hierarchical.i.hh"
