#include "formula/expression/Ternary.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

template <> void Ternary<Proposition>::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void Ternary<IntExpression>::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <>
void Ternary<LogicExpression>::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <>
void Ternary<FloatExpression>::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

} // namespace expression
