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

/// assertions spanning more cycles than this are never reduced (their automata are exponential)
constexpr int maxImplicationDepth = 10;

/// H3b (D-025): facts between atoms (p => q, p => !q), proved with Z3 under HARM's semantics,
/// given as premises to both checks. Off by default; at most maxQueries Z3 queries per reduction
struct AtomPremises {
  bool enabled = false;
  size_t maxQueries = 2000;
};

/// @brief The logical relation between two temporal formulas: atoms are the maximal non-boolean
/// subexpressions, merged when proved equivalent with Z3 (H2). A implies B only if it does both
/// over infinite words (Spot) and on every finite trace as HARM evaluates it (D-004 as amended).
/// Skipped unless both are syntactic safety formulas G(antecedent -> consequent) with a
/// fixed-length antecedent, spanning at most maxImplicationDepth cycles.
Implication implicationBetween(const expression::TemporalExpressionPtr &a,
                               const expression::TemporalExpressionPtr &b,
                               unsigned z3TimeoutMs = 1000,
                               const AtomPremises &premises = AtomPremises());

/// a dropped assertion and the kept assertions it is related to
struct ImplicationRecord {
  AssertionPtr dropped;
  std::vector<AssertionPtr> kept;
  /// "equivalent", "implied" (a kept assertion implies it) or "implies" (it implies a kept one)
  std::string relation;
  /// the facts between atoms the claim needed (H3b), as "p -> q" texts; empty without premises
  std::vector<std::string> premises;
};

/// @brief --reduce implies (D-004, D-008): drop assertions related by implication to kept ones.
/// keep = "stronger" (default), "weaker" or "ranked" (by _finalScore, best first). The order of
/// the kept assertions is the input order.
std::vector<AssertionPtr>
reduceByImplication(const std::vector<AssertionPtr> &assertions,
                    const std::string &keep,
                    std::vector<ImplicationRecord> *records = nullptr,
                    unsigned z3TimeoutMs = 1000,
                    size_t *pairsChecked = nullptr,
                    const AtomPremises &premises = AtomPremises());

} // namespace harm
