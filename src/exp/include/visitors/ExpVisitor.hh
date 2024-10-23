#pragma once

#include "formula/atom/Constant.hh"          // IWYU pragma: keep
#include "formula/atom/Variable.hh"          // IWYU pragma: keep
#include "formula/expression/BitSelector.hh" // IWYU pragma: keep
#include "formula/expression/GenericExpression.hh" // IWYU pragma: keep
#include "formula/expression/TypeCast.hh"   // IWYU pragma: keep
#include "formula/temporal/BooleanLayer.hh" // IWYU pragma: keep
#include "formula/temporal/Property.hh"     // IWYU pragma: keep
#include "formula/temporal/Sere.hh"         // IWYU pragma: keep

#include "visitorExpList.hh"

namespace expression {

/// @brief ExpVisitor defines the base visitor to visit expressions
class ExpVisitor {

public:
  virtual ~ExpVisitor() = default;

  VISITOR_EXP_LIST(visitor_virtual, );

protected:
  ExpVisitor() = default;
};

} // namespace expression
