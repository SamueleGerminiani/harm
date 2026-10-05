#include "expUtils/smtEquivalence.hh"

namespace expression {
namespace smt {

//H2: not implemented yet (stub so that the acceptance tests compile and fail)
bool available() { return false; }

Equivalence checkEquivalence(const PropositionPtr &, const PropositionPtr &,
                             unsigned) {
  return Equivalence::Unknown;
}

} // namespace smt
} // namespace expression
