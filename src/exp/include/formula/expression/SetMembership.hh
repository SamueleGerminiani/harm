#pragma once

#include <stddef.h>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

#include "formula/atom/Atom.hh"

namespace expression {
class ExpVisitor;
namespace ope {
enum ope : int;
} // namespace ope

/// @brief SetMembership declaration.
/// This class represents the set membership operator
template <typename T> class SetMembership : public Proposition {

public:
  SetMembership(
      GenericPtr<T> e, const std::vector<GenericPtr<T>> &set,
      const std::vector<std::pair<GenericPtr<T>, GenericPtr<T>>>
          &ranges);

  SetMembership(const SetMembership &other);

  virtual ~SetMembership();

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis GenericPtr<T>he visitor.
  void acceptVisitor(ExpVisitor &vis) override;

  /// @brief Returns if the input constant is equal to the maximum value assumable by the expression
  bool isRangeConstantMax(const GenericPtr<T> &maxConstant);

  /// @brief Returns if the input constant is equal to the minimum value assumable by the expression
  bool isRangeConstantMin(const GenericPtr<T> &minConstant);

  /// @brief Return the expression of the next operator
  /// @return A reference to the expression.
  GenericPtr<T> &getItem();

  /// @brief Return the set of the operator
  std::vector<GenericPtr<T>> getSet();

  /// @brief Return the ranges of the operator
  std::vector<std::pair<GenericPtr<T>, GenericPtr<T>>> getRanges();

  SetMembership &operator=(const SetMembership &other) = delete;

  /// @brief Return the operator of the expression
  ope::ope getOperator() override;

  /// @brief Return the string representation of the sets and ranges
  std::string valuesToString();

private:
  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  /// @brief GenericPtr<T>he expression to be checked if it is in the set
  GenericPtr<T> _e;

  /// @brief GenericPtr<T>he set of the operator
  std::vector<GenericPtr<T>> _set;
  /// @brief GenericPtr<T>he ranges of the operator
  std::vector<std::pair<GenericPtr<T>, GenericPtr<T>>> _ranges;
  /// @brief Propositional representations of the constraints imposed by the ranges and set
  std::vector<PropositionPtr> _conditions;

  using Proposition::directEvaluate;
  using Proposition::disableCache;
};

using IntSetMembership = SetMembership<IntExpression>;
using FloatSetMembership = SetMembership<FloatExpression>;
using LogicSetMembership = SetMembership<LogicExpression>;

//smart pointer alias
using IntSetMembershipPtr = std::shared_ptr<IntSetMembership>;
using FloatSetMembershipPtr = std::shared_ptr<FloatSetMembership>;
using LogicSetMembershipPtr = std::shared_ptr<LogicSetMembership>;

} // namespace expression

#include "SetMembership.i.hh"
