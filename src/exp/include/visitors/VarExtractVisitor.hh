#pragma once
#include <stddef.h>
#include <string>
#include <utility>
#include <vector>

#include "visitors/ExpVisitor.hh"

namespace expression {
enum class ExpType;

using VarType = std::pair<ExpType, size_t>;

/// @brief This class extracts all the variables from an expression.
class VarExtractVisitor : public ExpVisitor {
public:
  VarExtractVisitor();
  ~VarExtractVisitor() override = default;

  /// @brief returns the extracted variables.
  std::vector<std::pair<std::string, VarType>> get_vars();

  void visit(BooleanVariable &o) override;
  void visit(FloatVariable &o) override;
  void visit(IntVariable &o) override;

protected:
  /// @brief list of extracted variables
  std::vector<std::pair<std::string, VarType>> _varNameToType;
};

} // namespace expression
