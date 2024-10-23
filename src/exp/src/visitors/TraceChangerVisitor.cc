#include <vector>

#include "Trace.hh"
#include "formula/atom/Variable.hh"
#include "visitors/TraceChangerVisitor.hh"

namespace expression {

TraceChangerVisitor::TraceChangerVisitor(
    const harm::TracePtr &newTrace)
    : ExpVisitor(), _newTrace(newTrace) {}

void TraceChangerVisitor::visit(BooleanVariable &o) {
  o._v = _newTrace->getBooleanVariableValues(o._name);
}
void TraceChangerVisitor::visit(IntVariable &o) {
  o._v = _newTrace->getIntVariableValues(o._name);
}
void TraceChangerVisitor::visit(FloatVariable &o) {
  o._v = _newTrace->getFloatVariableValues(o._name);
}

} // namespace expression
