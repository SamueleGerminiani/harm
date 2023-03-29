#include "visitors/TraceChangerVisitor.hh"
#include "Trace.hh"
#include "classes/expression/BitSelector.hh"
#include "expUtils/expUtils.hh"

//------------------------------------------------------------------------------

#define CONSTANT(LEAF)                                                         \
  void TraceChangerVisitor::visit(LEAF &o) {}
#define BOOLEAN_CONSTANT(LEAF)                                                 \
  void TraceChangerVisitor::visit(LEAF &o) {}

#define EXPRESSION(NODE)                                                       \
  void TraceChangerVisitor::visit(expression::NODE &o) {                       \
    auto &items = o.getItems();                                                \
                                                                               \
    if (!items.empty()) {                                                      \
      auto iterStop = items.end();                                             \
      auto iter = items.begin();                                               \
                                                                               \
      for (; iter != iterStop; ++iter) {                                       \
        if (dynamic_cast<expression::NODE *>(*iter) != nullptr) {              \
          (*iter)->acceptVisitor(*this);                                       \
        } else {                                                               \
          (*iter)->acceptVisitor(*this);                                       \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }

#define TYPE_CAST(NODE)                                                        \
  void TraceChangerVisitor::visit(expression::NODE &o) {                       \
    o.getItem().acceptVisitor(*this);                                          \
  }

#define EXPRESSION_LOGIC_BIT_SELECTION(NODE)                                   \
  void TraceChangerVisitor::visit(expression::NODE &o) {                       \
    if (o.getLowerBound() == o.getUpperBound()) {                              \
      o.getItem().acceptVisitor(*this);                                        \
    } else {                                                                   \
      o.getItem().acceptVisitor(*this);                                        \
    }                                                                          \
  }

#define EXPRESSION_NEXT(NODE)                                                  \
  void TraceChangerVisitor::visit(expression::NODE &o) {                       \
    o.getItem().acceptVisitor(*this);                                          \
  }
#define EXPRESSION_PAST(NODE)                                                  \
  void TraceChangerVisitor::visit(expression::NODE &o) {                       \
    o.getItem().acceptVisitor(*this);                                          \
  }
//------------------------------------------------------------------------------

namespace expression {

TraceChangerVisitor::TraceChangerVisitor(harm::Trace *newTrace)
    : ExpVisitor(),_newTrace(newTrace) {}

void TraceChangerVisitor::visit(BooleanVariable &o) {
  o._v = _newTrace->getBooleanVariableValues(o._name);
}
void TraceChangerVisitor::visit(LogicVariable &o) {
  o._v = _newTrace->getLogicVariableValues(o._name);
}
void TraceChangerVisitor::visit(NumericVariable &o) {
  o._v = _newTrace->getNumericVariableValues(o._name);
}
// proposition
BOOLEAN_CONSTANT(BooleanConstant)
EXPRESSION(PropositionOr)
EXPRESSION(PropositionAnd)
EXPRESSION(PropositionXor)
EXPRESSION(PropositionEq)
EXPRESSION(PropositionNeq)
EXPRESSION_PAST(PropositionPast)

void TraceChangerVisitor::visit(expression::PropositionNot &o) {
  o.getItems()[0]->acceptVisitor(*this);
}

void TraceChangerVisitor::visit(expression::LogicNot &o) {
  o.getItems()[0]->acceptVisitor(*this);
}
void TraceChangerVisitor::visit(expression::LogicBitSelector &o) {
  o.getItem().acceptVisitor(*this);
}

// numeric
CONSTANT(NumericConstant)
EXPRESSION(NumericSum)
EXPRESSION(NumericSub)
EXPRESSION(NumericMul)
EXPRESSION(NumericDiv)
EXPRESSION(NumericEq)
EXPRESSION(NumericNeq)
EXPRESSION(NumericGreater)
EXPRESSION(NumericGreaterEq)
EXPRESSION(NumericLess)
EXPRESSION(NumericLessEq)
EXPRESSION_PAST(NumericPast)
TYPE_CAST(NumericToBool)

// logic
CONSTANT(LogicConstant)
EXPRESSION(LogicSum)
EXPRESSION(LogicSub)
EXPRESSION(LogicMul)
EXPRESSION(LogicDiv)
EXPRESSION(LogicBAnd)
EXPRESSION(LogicBOr)
EXPRESSION(LogicBXor)
EXPRESSION(LogicEq)
EXPRESSION(LogicNeq)
EXPRESSION(LogicGreater)
EXPRESSION(LogicGreaterEq)
EXPRESSION(LogicLess)
EXPRESSION(LogicLessEq)
EXPRESSION_PAST(LogicPast)
TYPE_CAST(LogicToNumeric)
TYPE_CAST(LogicToBool)
EXPRESSION(LogicLShift)
EXPRESSION(LogicRShift)

} // namespace expression
