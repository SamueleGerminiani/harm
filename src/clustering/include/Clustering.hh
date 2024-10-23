#pragma once
#include "Int.hh"
#include "exp.hh"
#include <vector>
namespace expression {
class NumericExpression;
using NumericExpressionPtr = std::shared_ptr<NumericExpression>;
} // namespace expression

namespace harm {

/**
 * @brief Run clustering algorithm on a numeric expression.
 *
 * @param ivs The indices the time units to cluster on.
 * @param cn The numeric expression to cluster on.
 * @return A vector of propositions, each of which represents a cluster.
 */
template <typename T>
std::vector<expression::PropositionPtr>
runClustering(const std::vector<size_t> &ivs,
              const expression::NumericExpressionPtr &cn,
              bool inDTAlgo = false);

template <typename Original, typename Signed>
std::vector<Signed>
gatherElements(const std::vector<size_t> &ivs,
               const expression::NumericExpressionPtr &cn);

} // namespace harm
