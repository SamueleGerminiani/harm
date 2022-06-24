#include "classes/temporal/PastOperator.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

template <>
void PastOperator<NumericExpression>::acceptVisitor(ExpVisitor &vis) {
    vis.visit(*this);
}

template <>
void PastOperator<LogicExpression>::acceptVisitor(ExpVisitor &vis) {
    vis.visit(*this);
}

template <> void PastOperator<Proposition>::acceptVisitor(ExpVisitor &vis) {
    vis.visit(*this);
}

template <> Numeric PastOperator<NumericExpression>::evaluate(size_t time) {
    if (time < _offset) {
        return _e->evaluate(0);
    } else {
        return _e->evaluate(time - _offset);
    }
}

template <> Logic PastOperator<LogicExpression>::evaluate(size_t time) {
    if (time < _offset) {
        return _e->evaluate(0);
    } else {
        return _e->evaluate(time - _offset);
    }
}

template <> bool PastOperator<Proposition>::evaluate(size_t time) {
    if (time < _offset) {
        return _e->evaluate(0);
    } else {
        return _e->evaluate(time - _offset);
    }
}

} // namespace oden
