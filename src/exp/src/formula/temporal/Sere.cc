#include "formula/temporal/Sere.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

//generic property
#define G_VISITOR_CALL(Type)                                         \
  template <> void Type::acceptVisitor(ExpVisitor &vis) {            \
    vis.visit(*this);                                                \
  }

//specific property
#define S_VISITOR_CALL(Type)                                         \
  void Type::acceptVisitor(ExpVisitor &vis) { vis.visit(*this); }

//specific property, window-based
#define WB_VISITOR_CALL(Type)                                        \
  template <> void Type::acceptVisitor(ExpVisitor &vis) {            \
    vis.visit(*this);                                                \
  }

G_VISITOR_CALL(SereAnd);
G_VISITOR_CALL(SereOr);
G_VISITOR_CALL(SereIntersect);
G_VISITOR_CALL(SereFirstMatch);

S_VISITOR_CALL(SereConcat);
S_VISITOR_CALL(SerePlus);

WB_VISITOR_CALL(SereDelay);
WB_VISITOR_CALL(SereConsecutiveRep);
WB_VISITOR_CALL(SereGoto);
WB_VISITOR_CALL(SereNonConsecutiveRep);

} // namespace expression
