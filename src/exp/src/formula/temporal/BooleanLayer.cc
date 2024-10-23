#include "formula/temporal/BooleanLayer.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

void BooleanLayerPermutationPlaceholder::acceptVisitor(
    ExpVisitor &vis) {
  vis.visit(*this);
}
void BooleanLayerDTPlaceholder::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
void BooleanLayerInst::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

void BooleanLayerNot::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
}; // namespace expression
