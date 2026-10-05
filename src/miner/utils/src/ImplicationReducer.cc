#include "ImplicationReducer.hh"

namespace harm {

std::string toString(Implication i) {
  switch (i) {
  case Implication::Equivalent:
    return "EQUIVALENT";
  case Implication::AImpliesB:
    return "A_IMPLIES_B";
  case Implication::BImpliesA:
    return "B_IMPLIES_A";
  case Implication::None:
    return "NONE";
  case Implication::Skipped:
    return "SKIPPED";
  }
  return "?";
}

//H3: not implemented yet (stub so that the acceptance tests compile and fail)
Implication implicationBetween(const expression::TemporalExpressionPtr &,
                               const expression::TemporalExpressionPtr &,
                               unsigned) {
  return Implication::None;
}

} // namespace harm
