#pragma once

#include <map>
#include <string>

#include "formula/atom/Atom.hh"

namespace expression {
namespace smt {

/// result of an equivalence query: Unknown (timeout, unsupported) must be treated as "not proved"
enum class Equivalence { Equivalent, NotEquivalent, Unknown };

/// @brief true if HARM was built with Z3 (HARM_WITH_Z3)
bool available();

/// @brief Decide whether two propositions are equivalent under HARM's semantics (D-003, D-011):
/// for every value of the variables, x and z included, they evaluate to the same truth value.
/// Constructs that are not encoded exactly are free atoms (sound, incomplete).
/// a counterexample: logic variable name -> 4-valued value (MSB first), bool/int variable name ->
/// "0"/"1" or decimal value
using Counterexample = std::map<std::string, std::string>;

Equivalence checkEquivalence(const PropositionPtr &p1,
                             const PropositionPtr &p2,
                             unsigned timeoutMs = 1000,
                             Counterexample *cex = nullptr);

} // namespace smt
} // namespace expression
