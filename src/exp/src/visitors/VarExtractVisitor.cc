#include "visitors/VarExtractVisitor.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Constant.hh"
#include "formula/atom/Variable.hh"
#include "formula/expression/BitSelector.hh"
#include "formula/expression/GenericExpression.hh"
#include "formula/expression/TypeCast.hh"

#define VARIABLE(LEAF)                                               \
  void VarExtractVisitor::visit(LEAF &o) {                           \
    _varNameToType.emplace_back(o.getName(), o.getType());           \
  }

namespace expression {

VarExtractVisitor::VarExtractVisitor() : ExpVisitor() {}

// proposition
VARIABLE(BooleanVariable)
VARIABLE(FloatVariable)
VARIABLE(IntVariable)

std::vector<std::pair<std::string, VarType>>
VarExtractVisitor::get_vars() {
  auto res = _varNameToType;
  _varNameToType.clear();
  return res;
}
} // namespace expression
