#include <vector>

#include "formula/atom/Atom.hh"
#include "formula/atom/Constant.hh"
#include "formula/expression/BitSelector.hh"
#include "formula/expression/GenericExpression.hh"
#include "formula/expression/TypeCast.hh"
#include "formula/temporal/BooleanLayer.hh"
#include "formula/temporal/Property.hh"
#include "formula/temporal/Sere.hh"
#include "visitors/ExpVisitor.hh"

//------------------------------------------------------------------------------
#define LEAF_NODE(LEAF)                                              \
  void ExpVisitor::visit(LEAF &) {}

#define EXP_OPE(NODE)                                                \
  void ExpVisitor::visit(NODE &o) {                                  \
    auto &propositions = o.getItems();                               \
    for (const auto &prop : propositions)                            \
      prop->acceptVisitor(*this);                                    \
  }

#define EXP_OPE_UNARY(NODE)                                          \
  void ExpVisitor::visit(NODE &o) {                                  \
    o.getItem()->acceptVisitor(*this);                               \
  }

#define UNARY_FUNCTION(TYPE)                                         \
  void ExpVisitor::visit(TYPE &o) {                                  \
    if (o.isTemporal()) {                                            \
      (*o.getPlaceholderPointer())->acceptVisitor(*this);            \
    } else {                                                         \
      o.getOperand()->acceptVisitor(*this);                          \
    }                                                                \
  }
//------------------------------------------------------------------------------

namespace expression {

// proposition
LEAF_NODE(BooleanConstant)
LEAF_NODE(BooleanVariable)
EXP_OPE(PropositionAnd)
EXP_OPE(PropositionOr)
EXP_OPE(PropositionXor)
EXP_OPE(PropositionEq)
EXP_OPE(PropositionNeq)
EXP_OPE(PropositionNot)

// float
LEAF_NODE(FloatConstant)
LEAF_NODE(FloatVariable)
EXP_OPE(FloatSum)
EXP_OPE(FloatSub)
EXP_OPE(FloatMul)
EXP_OPE(FloatDiv)
EXP_OPE(FloatEq)
EXP_OPE(FloatNeq)
EXP_OPE(FloatGreater)
EXP_OPE(FloatGreaterEq)
EXP_OPE(FloatLess)
EXP_OPE(FloatLessEq)
EXP_OPE_UNARY(FloatToBool)
EXP_OPE_UNARY(FloatToInt)

// int
LEAF_NODE(IntConstant)
LEAF_NODE(IntVariable)
EXP_OPE(IntSum)
EXP_OPE(IntSub)
EXP_OPE(IntMul)
EXP_OPE(IntDiv)
EXP_OPE(IntBAnd)
EXP_OPE(IntBOr)
EXP_OPE(IntBXor)
EXP_OPE(IntEq)
EXP_OPE(IntNeq)
EXP_OPE(IntGreater)
EXP_OPE(IntGreaterEq)
EXP_OPE(IntLess)
EXP_OPE(IntLessEq)
EXP_OPE(IntNot)
EXP_OPE(IntLShift)
EXP_OPE(IntRShift)
EXP_OPE_UNARY(IntBitSelector)
EXP_OPE_UNARY(IntToFloat)
EXP_OPE_UNARY(IntToBool)

//temporal
void ExpVisitor::visit(BooleanLayerInst &o) {
  o.getProposition()->acceptVisitor(*this);
}
void ExpVisitor::visit(BooleanLayerPermutationPlaceholder &o) {
  if (o.getPlaceholderPointer() != nullptr &&
      (*o.getPlaceholderPointer()) != nullptr)
    (*o.getPlaceholderPointer())->acceptVisitor(*this);
}
void ExpVisitor::visit(BooleanLayerDTPlaceholder &o) {
  if (o.getPlaceholderPointer() != nullptr &&
      (*o.getPlaceholderPointer()) != nullptr)
    (*o.getPlaceholderPointer())->acceptVisitor(*this);
}
void ExpVisitor::visit(BooleanLayerNot &o) {
  o.getBL()->acceptVisitor(*this);
}

EXP_OPE(PropertyAlways)
EXP_OPE(PropertyEventually)
EXP_OPE(PropertyUntil)
EXP_OPE(PropertyRelease)
EXP_OPE(PropertyAnd)
EXP_OPE(PropertyOr)
EXP_OPE(PropertyNot)
EXP_OPE(PropertyNext)
EXP_OPE(PropertyImplication)
EXP_OPE(SereAnd)
EXP_OPE(SereOr)
EXP_OPE(SereConcat)
EXP_OPE(SereIntersect)
EXP_OPE(SereFirstMatch)
EXP_OPE(SereDelay)
EXP_OPE(SereConsecutiveRep)
EXP_OPE(SerePlus)
EXP_OPE(SereGoto)
EXP_OPE(SereNonConsecutiveRep)

} // namespace expression
