#pragma once

#define visitor_virtual virtual
#define visitor_override override

#define VISITOR_EXP_LIST(VIRTUAL, OVVERIDE)                          \
  VIRTUAL void visit(BooleanConstant &o) OVVERIDE;                   \
  VIRTUAL void visit(BooleanVariable &o) OVVERIDE;                   \
  VIRTUAL void visit(PropositionAnd &o) OVVERIDE;                    \
  VIRTUAL void visit(PropositionOr &o) OVVERIDE;                     \
  VIRTUAL void visit(PropositionXor &o) OVVERIDE;                    \
  VIRTUAL void visit(PropositionEq &o) OVVERIDE;                     \
  VIRTUAL void visit(PropositionNeq &o) OVVERIDE;                    \
  VIRTUAL void visit(PropositionNot &o) OVVERIDE;                    \
  VIRTUAL void visit(FloatConstant &o) OVVERIDE;                     \
  VIRTUAL void visit(FloatVariable &o) OVVERIDE;                     \
  VIRTUAL void visit(FloatSum &o) OVVERIDE;                          \
  VIRTUAL void visit(FloatSub &o) OVVERIDE;                          \
  VIRTUAL void visit(FloatMul &o) OVVERIDE;                          \
  VIRTUAL void visit(FloatDiv &o) OVVERIDE;                          \
  VIRTUAL void visit(FloatEq &o) OVVERIDE;                           \
  VIRTUAL void visit(FloatNeq &o) OVVERIDE;                          \
  VIRTUAL void visit(FloatGreater &o) OVVERIDE;                      \
  VIRTUAL void visit(FloatGreaterEq &o) OVVERIDE;                    \
  VIRTUAL void visit(FloatLess &o) OVVERIDE;                         \
  VIRTUAL void visit(FloatLessEq &o) OVVERIDE;                       \
  VIRTUAL void visit(FloatToBool &o) OVVERIDE;                       \
  VIRTUAL void visit(FloatToInt &o) OVVERIDE;                        \
  VIRTUAL void visit(IntConstant &o) OVVERIDE;                       \
  VIRTUAL void visit(IntVariable &o) OVVERIDE;                       \
  VIRTUAL void visit(IntSum &o) OVVERIDE;                            \
  VIRTUAL void visit(IntSub &o) OVVERIDE;                            \
  VIRTUAL void visit(IntMul &o) OVVERIDE;                            \
  VIRTUAL void visit(IntDiv &o) OVVERIDE;                            \
  VIRTUAL void visit(IntBAnd &o) OVVERIDE;                           \
  VIRTUAL void visit(IntBOr &o) OVVERIDE;                            \
  VIRTUAL void visit(IntBXor &o) OVVERIDE;                           \
  VIRTUAL void visit(IntNot &o) OVVERIDE;                            \
  VIRTUAL void visit(IntEq &o) OVVERIDE;                             \
  VIRTUAL void visit(IntNeq &o) OVVERIDE;                            \
  VIRTUAL void visit(IntGreater &o) OVVERIDE;                        \
  VIRTUAL void visit(IntGreaterEq &o) OVVERIDE;                      \
  VIRTUAL void visit(IntLess &o) OVVERIDE;                           \
  VIRTUAL void visit(IntLessEq &o) OVVERIDE;                         \
  VIRTUAL void visit(IntBitSelector &o) OVVERIDE;                    \
  VIRTUAL void visit(IntToBool &o) OVVERIDE;                         \
  VIRTUAL void visit(IntToFloat &o) OVVERIDE;                        \
  VIRTUAL void visit(IntLShift &o) OVVERIDE;                         \
  VIRTUAL void visit(IntRShift &o) OVVERIDE;                         \
  VIRTUAL void visit(BooleanLayerPermutationPlaceholder &o)          \
      OVVERIDE;                                                      \
  VIRTUAL void visit(BooleanLayerNot &o) OVVERIDE;                   \
  VIRTUAL void visit(BooleanLayerDTPlaceholder &o) OVVERIDE;         \
  VIRTUAL void visit(BooleanLayerInst &o) OVVERIDE;                  \
  VIRTUAL void visit(PropertyAlways &o) OVVERIDE;                    \
  VIRTUAL void visit(PropertyNext &o) OVVERIDE;                      \
  VIRTUAL void visit(PropertyEventually &o) OVVERIDE;                \
  VIRTUAL void visit(PropertyUntil &o) OVVERIDE;                     \
  VIRTUAL void visit(PropertyRelease &o) OVVERIDE;                   \
  VIRTUAL void visit(PropertyAnd &o) OVVERIDE;                       \
  VIRTUAL void visit(PropertyOr &o) OVVERIDE;                        \
  VIRTUAL void visit(PropertyNot &o) OVVERIDE;                       \
  VIRTUAL void visit(PropertyImplication &o) OVVERIDE;               \
  VIRTUAL void visit(SereConcat &o) OVVERIDE;                        \
  VIRTUAL void visit(SereAnd &o) OVVERIDE;                           \
  VIRTUAL void visit(SereOr &o) OVVERIDE;                            \
  VIRTUAL void visit(SereIntersect &o) OVVERIDE;                     \
  VIRTUAL void visit(SereFirstMatch &o) OVVERIDE;                    \
  VIRTUAL void visit(SereDelay &o) OVVERIDE;                         \
  VIRTUAL void visit(SereConsecutiveRep &o) OVVERIDE;                \
  VIRTUAL void visit(SerePlus &o) OVVERIDE;                          \
  VIRTUAL void visit(SereGoto &o) OVVERIDE;                          \
  VIRTUAL void visit(SereNonConsecutiveRep &o) OVVERIDE;
