#include <vector>

#include "formula/atom/Atom.hh"
#include "formula/atom/Constant.hh"
#include "formula/expression/BitSelector.hh"
#include "formula/expression/GenericExpression.hh"
#include "formula/expression/SetMembership.hh"
#include "formula/expression/Substring.hh"
#include "formula/expression/TypeCast.hh"
#include "formula/function/SVAfunction.hh"
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
UNARY_FUNCTION(PropositionFell)
UNARY_FUNCTION(PropositionPast)
UNARY_FUNCTION(PropositionStable)
UNARY_FUNCTION(PropositionRose)

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
EXP_OPE_UNARY(FloatToLogic)
EXP_OPE_UNARY(FloatSetMembership)
UNARY_FUNCTION(FloatPast)
UNARY_FUNCTION(FloatStable)

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
EXP_OPE_UNARY(IntSetMembership)
EXP_OPE_UNARY(IntToFloat)
EXP_OPE_UNARY(IntToBool)
EXP_OPE_UNARY(IntToLogic)
UNARY_FUNCTION(IntStable)
UNARY_FUNCTION(IntRose)
UNARY_FUNCTION(IntFell)
UNARY_FUNCTION(IntPast)

//logic
LEAF_NODE(LogicConstant)
LEAF_NODE(LogicVariable)
EXP_OPE(LogicSum)
EXP_OPE(LogicSub)
EXP_OPE(LogicMul)
EXP_OPE(LogicDiv)
EXP_OPE(LogicBAnd)
EXP_OPE(LogicBOr)
EXP_OPE(LogicBXor)
EXP_OPE(LogicEq)
EXP_OPE(LogicNeq)
EXP_OPE(LogicGreater)
EXP_OPE(LogicGreaterEq)
EXP_OPE(LogicLess)
EXP_OPE(LogicLessEq)
EXP_OPE(LogicNot)
EXP_OPE(LogicLShift)
EXP_OPE(LogicRShift)
EXP_OPE_UNARY(LogicBitSelector)
EXP_OPE_UNARY(LogicSetMembership)
EXP_OPE_UNARY(LogicToFloat)
EXP_OPE_UNARY(LogicToBool)
EXP_OPE_UNARY(LogicToInt)
UNARY_FUNCTION(LogicStable)
UNARY_FUNCTION(LogicRose)
UNARY_FUNCTION(LogicFell)
UNARY_FUNCTION(LogicPast)

//string
LEAF_NODE(StringConstant)
LEAF_NODE(StringVariable)
EXP_OPE(StringConcat)
EXP_OPE(StringEq)
EXP_OPE(StringNeq)
EXP_OPE(StringGreater)
EXP_OPE(StringGreaterEq)
EXP_OPE(StringLess)
EXP_OPE(StringLessEq)
EXP_OPE_UNARY(Substring)

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
void ExpVisitor::visit(BooleanLayerFunction &o) {
  o.getFunction()->acceptVisitor(*this);
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
