#include "formula/atom/Constant.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

template <> void Constant<bool>::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

template <> void Constant<Float>::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

template <> void Constant<UInt>::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

} // namespace expression
