#include "visitors/ExpVisitor.hh"
#include "classes/atom/Atom.hh"

namespace expression {

template <>
void BitSelector<LogicExpression, LogicExpression>::acceptVisitor(
  ExpVisitor &vis) {
  vis.visit(*this);
}

template <>
Logic BitSelector<LogicExpression, LogicExpression>::evaluate(size_t time) {
  return 
    (static_cast<uint64_t>(((1 << (_upper_bound - _lower_bound + 1)) - 1) << _lower_bound) &
     _e->evaluate(time));
}

template <>
bool BitSelector<LogicExpression, Proposition>::evaluate(size_t time) {
//  messageErrorIf(_upper_bound != _lower_bound, "Single bit selector index error");

  return static_cast<uint64_t>(((1 << (_upper_bound - _lower_bound + 1)) - 1)
                               << _lower_bound) &
         _e->evaluate(time);
}

} // namespace oden
