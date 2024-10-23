#pragma once

#include <stddef.h>
#include <type_traits>

#include "Float.hh"
#include "Int.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class ExpVisitor;

/// @brief This class represents an inmplicit type cast
template <typename ET, typename RT> class TypeCast : public RT {

public:
  TypeCast(GenericPtr<ET> e);

  using ReturnType = typename std::conditional<
      std::is_same<RT, FloatExpression>::value, Float,
      typename std::conditional<
          std::is_same<RT, IntExpression>::value, UInt,
          bool>::type>::type;

  TypeCast(const TypeCast &other) = delete;

  virtual ~TypeCast();

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  void acceptVisitor(ExpVisitor &vis) override;

  /// @brief Return the expression of the next operator
  /// @return A reference to the expression.
  GenericPtr<ET> &getItem();

  void popItem();

  /// @brief Assing operator
  TypeCast &operator=(const TypeCast &other) = delete;

private:
  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  /// @brief The expression to cast
  GenericPtr<ET> _e;

  using RT::directEvaluate;
  using RT::disableCache;
};

using IntToFloat = TypeCast<IntExpression, FloatExpression>;
using IntToBool = TypeCast<IntExpression, Proposition>;

using FloatToBool = TypeCast<FloatExpression, Proposition>;
using FloatToInt = TypeCast<FloatExpression, IntExpression>;

using IntToFloatPtr = std::shared_ptr<IntToFloat>;
using IntToBoolPtr = std::shared_ptr<IntToBool>;

using FloatToBoolPtr = std::shared_ptr<FloatToBool>;
using FloatToIntPtr = std::shared_ptr<FloatToInt>;

/// @brief Check if an expression is a of type TypeCast
template <typename T> bool isTypeCast(GenericPtr<T> exp) {
  if constexpr (std::is_same_v<T, FloatExpression>) {
    return std::dynamic_pointer_cast<IntToFloat>(exp) != nullptr;
  } else if constexpr (std::is_same_v<T, IntExpression>) {
    return std::dynamic_pointer_cast<FloatToInt>(exp) != nullptr;
  } else if constexpr (std::is_same_v<T, Proposition>) {
    return std::dynamic_pointer_cast<IntToBool>(exp) != nullptr ||
           std::dynamic_pointer_cast<FloatToBool>(exp) != nullptr;
  }
  return false;
}

} // namespace expression

#include "TypeCast.i.hh"
