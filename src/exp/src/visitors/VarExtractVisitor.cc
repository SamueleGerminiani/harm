#include "visitors/VarExtractVisitor.hh"
#include "classes/expression/BitSelector.hh"
#include "expUtils/expUtils.hh"

//------------------------------------------------------------------------------
#define VARIABLE(LEAF)                                                         \
  void VarExtractVisitor::visit(LEAF &o) {                                     \
    _vars.emplace_back(o.getName(), _currDepth);                               \
  }

#define CONSTANT(LEAF)                                                         \
  void VarExtractVisitor::visit(LEAF &o) {}
#define BOOLEAN_CONSTANT(LEAF)                                                 \
  void VarExtractVisitor::visit(LEAF &o) {}

#define EXPRESSION(NODE)                                                       \
  void VarExtractVisitor::visit(expression::NODE &o) {                         \
    auto &items = o.getItems();                                                \
                                                                               \
    _currDepth++;                                                              \
    if (!items.empty()) {                                                      \
      auto iterStop = items.end();                                             \
      auto iter = items.begin();                                               \
                                                                               \
      for (; iter != iterStop; ++iter) {                                       \
        if (dynamic_cast<expression::NODE *>(*iter) != nullptr) {              \
          _currDepth--;                                                        \
          (*iter)->acceptVisitor(*this);                                       \
          _currDepth++;                                                        \
        } else {                                                               \
          (*iter)->acceptVisitor(*this);                                       \
        }                                                                      \
      }                                                                        \
    }                                                                          \
    _currDepth--;                                                              \
  }

#define TYPE_CAST(NODE)                                                        \
  void VarExtractVisitor::visit(expression::NODE &o) {                         \
    _currDepth++;                                                              \
    o.getItem().acceptVisitor(*this);                                          \
    _currDepth--;                                                              \
  }

#define EXPRESSION_LOGIC_BIT_SELECTION(NODE)                                   \
  void VarExtractVisitor::visit(expression::NODE &o) {                         \
    _currDepth++;                                                              \
    if (o.getLowerBound() == o.getUpperBound()) {                              \
      o.getItem().acceptVisitor(*this);                                        \
    } else {                                                                   \
      o.getItem().acceptVisitor(*this);                                        \
    }                                                                          \
    _currDepth--;                                                              \
  }

#define EXPRESSION_NEXT(NODE)                                                  \
  void VarExtractVisitor::visit(expression::NODE &o) {                         \
    _currDepth++;                                                              \
    o.getItem().acceptVisitor(*this);                                          \
    _currDepth--;                                                              \
  }
#define EXPRESSION_PAST(NODE)                                                  \
  void VarExtractVisitor::visit(expression::NODE &o) {                         \
    _currDepth++;                                                              \
    o.getItem().acceptVisitor(*this);                                          \
    _currDepth--;                                                              \
  }
//------------------------------------------------------------------------------

namespace expression {

VarExtractVisitor::VarExtractVisitor(bool keepIndex) : ExpVisitor(), _keepIndex(keepIndex) {}

// proposition
VARIABLE(BooleanVariable)
BOOLEAN_CONSTANT(BooleanConstant)
EXPRESSION(PropositionOr)
EXPRESSION(PropositionAnd)
EXPRESSION(PropositionXor)
EXPRESSION(PropositionEq)
EXPRESSION(PropositionNeq)
EXPRESSION_PAST(PropositionPast)

std::vector<std::pair<std::string, size_t>> VarExtractVisitor::get_vars() {
  return _vars;
}

void VarExtractVisitor::visit(expression::PropositionNot &o) {
  _currDepth++;
  o.getItems()[0]->acceptVisitor(*this);
  _currDepth--;
}

void VarExtractVisitor::visit(expression::LogicNot &o) {
  _currDepth++;
  o.getItems()[0]->acceptVisitor(*this);
  _currDepth--;
}
void VarExtractVisitor::visit(expression::LogicBitSelector &o) {
  _currDepth++;
  //keep the index in the variable
  if (_keepIndex && dynamic_cast<LogicVariable *>(&o.getItem()) != nullptr) {
    _vars.emplace_back(log2String(o),_currDepth);
  } else {
    o.getItem().acceptVisitor(*this);
  }
  _currDepth--;
}

// numeric
VARIABLE(NumericVariable)
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
VARIABLE(LogicVariable)
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
