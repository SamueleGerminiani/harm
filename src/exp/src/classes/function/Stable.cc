#include "classes/function/Stable.hh"

namespace expression {


template <> bool Stable<NumericExpression>::evaluate(size_t time) {
  return time == 0 ? false
                   : _operand->evaluate(time) == _operand->evaluate(time - 1);
}

template <> bool Stable<LogicExpression>::evaluate(size_t time) {
  return time == 0 ? false
                   : _operand->evaluate(time) == _operand->evaluate(time - 1);
}

template <> bool Stable<Proposition>::evaluate(size_t time) {
  return time == 0 ? false
                   : _operand->evaluate(time) == _operand->evaluate(time - 1);
}

} // namespace expression
