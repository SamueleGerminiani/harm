#include <vector>

#include "Logic.hh"
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
void TraceChangerVisitor::visit(LogicVariable &o) {
  ULogic **values = _newTrace->getLogicVariableValues(o._name);
  o._v[0] = values[0];
  o._v[1] = values[1];
  o._v[2] = values[2];
}
void TraceChangerVisitor::visit(FloatVariable &o) {
  o._v = _newTrace->getFloatVariableValues(o._name);
}
void TraceChangerVisitor::visit(StringVariable &o) {
  o._v = _newTrace->getStringVariableValues(o._name);
}

} // namespace expression
