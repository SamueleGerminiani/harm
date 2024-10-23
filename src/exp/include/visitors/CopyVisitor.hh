#pragma once

#include "formula/atom/Atom.hh"
#include "formula/temporal/TemporalExpression.hh"
#include "visitors/ExpVisitor.hh"
#include "visitors/visitorExpList.hh"

namespace expression {

/// @brief CopyVisitor generates a copy of a proposition
class CopyVisitor : public ExpVisitor {
public:
  CopyVisitor(bool removePlaceholders = false);

  CopyVisitor(const CopyVisitor &other) = delete;

  CopyVisitor &operator=(const CopyVisitor &other) = delete;

  ~CopyVisitor() override;

  /// @brief Returns the generated copy of the visited proposition
  PropositionPtr getProposition();
  /// @brief Returns the generated copy of the visited int expression
  IntExpressionPtr getInt();
  /// @brief Returns the generated copy of the visited float expression
  FloatExpressionPtr getFloat();
  /// @brief Returns the generated copy of the visited numeric expression
  NumericExpressionPtr getNum();
  /// @brief Returns the generated copy of the visited temporal expression
  TemporalExpressionPtr getTemporal();

  // list of methods to override
  VISITOR_EXP_LIST(, visitor_override);

private:
  //stacks of expressions
  PropositionPtr _proposition = nullptr;
  FloatExpressionPtr _float = nullptr;
  IntExpressionPtr _int = nullptr;
  TemporalExpressionPtr _temporal = nullptr;

  /// @brief keeps track of booleal layer expression, to avoid creating redundant expressions
  std::unordered_map<std::string, TemporalExpressionPtr>
      _tokenToTempExp;

  /// @brief if true, the visitor will remove placeholders from the copy
  bool _removePlaceholders = false;

  /// @brief resets the stacks of expressions
  void reset();
};

} // namespace expression
