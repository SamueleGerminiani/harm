#include <stddef.h>
#include <utility>

#include "Int.hh"
#include "formula/atom/Atom.hh"
#include "formula/expression/BitSelector.hh"
#include "misc.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

//Int
template <>
void BitSelector<IntExpression, IntExpression>::acceptVisitor(
    ExpVisitor &vis) {
  vis.visit(*this);
}

template <>
void BitSelector<IntExpression, IntExpression>::initEvaluate() {
  directEvaluate = [this](int time) {
    return extractBits(_e->evaluate(time), _lower_bound,
                       _upper_bound);
  };
  disableCache();
}

} // namespace expression
