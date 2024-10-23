#pragma once

namespace harm {
/** @enum ClsOp
 *  @brief Operator for a numeric expression (clustering): 
 *  Range: l <= numeric <= r;
 *  E: numeric == r;
 *  GE: numeric >= r;
 *  LE: numeric <= r.
 */
enum class ClsOp { Range = 0, E, GE, LE };
enum class ClsType {
  Kmeans,
  Contiguous,
  Kmeans_UseAllIVsInDT,
  Contiguous_UseAllIVsInDT
};

inline bool isKmeans(ClsType type) {
  return type == ClsType::Kmeans ||
         type == ClsType::Kmeans_UseAllIVsInDT;
}
inline bool isContiguous(ClsType type) {
  return type == ClsType::Contiguous ||
         type == ClsType::Contiguous_UseAllIVsInDT;
}
} // namespace harm
