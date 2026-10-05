#pragma once

#include <string>
#include <vector>

#include "formula/temporal/TemporalExpression.hh"

namespace harm {
class Assertion;
using AssertionPtr = std::shared_ptr<Assertion>;

/// relation between two assertions (H3, D-004)
enum class Implication { Equivalent, AImpliesB, BImpliesA, None, Skipped };
std::string toString(Implication i);

/// @brief The logical relation between two temporal formulas: atoms are the maximal non-boolean
/// subexpressions, merged when proved equivalent with Z3 (H2); the formulas are compared with
/// Spot. Skipped unless both are syntactic safety formulas (D-004).
Implication implicationBetween(const expression::TemporalExpressionPtr &a,
                               const expression::TemporalExpressionPtr &b,
                               unsigned z3TimeoutMs = 1000);

} // namespace harm
