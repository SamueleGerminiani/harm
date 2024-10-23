#include "formula/temporal/Property.hh"
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

G_VISITOR_CALL(PropertyAlways);
G_VISITOR_CALL(PropertyEventually);
G_VISITOR_CALL(PropertyUntil);
G_VISITOR_CALL(PropertyRelease);
G_VISITOR_CALL(PropertyAnd);
G_VISITOR_CALL(PropertyOr);
G_VISITOR_CALL(PropertyNot);

S_VISITOR_CALL(PropertyNext);
S_VISITOR_CALL(PropertyImplication);
} // namespace expression
