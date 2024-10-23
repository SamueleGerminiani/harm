#pragma once

#include "visitors/ExpVisitor.hh"
#include "visitors/visitorExpList.hh"

namespace harm {
class Trace;
}

namespace expression {

/// @brief TraceChangerVisitor changes the trace of the given expression to the new one.
class TraceChangerVisitor : public ExpVisitor {
public:
  TraceChangerVisitor(const harm::TracePtr &newTrace);

  ~TraceChangerVisitor() override = default;

  void visit(BooleanVariable &o) override;
  void visit(FloatVariable &o) override;
  void visit(IntVariable &o) override;

protected:
  harm::TracePtr _newTrace;
};

} // namespace expression
