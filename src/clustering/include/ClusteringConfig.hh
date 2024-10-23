#pragma once
#include <stddef.h>
#include <string>
#include <unordered_set>
#include <vector>

namespace harm {
enum class ClsOp;
enum class ClsType;
} // namespace harm

namespace harm {
struct ClusteringConfig {

  std::unordered_set<harm::ClsType> _clusteringType;
  double _minWCSS = 1.0f;
  size_t _maxClusters = 100;
  std::unordered_set<harm::ClsOp> _clsOps;
  std::unordered_set<std::string> _excluded;
};
} // namespace harm
