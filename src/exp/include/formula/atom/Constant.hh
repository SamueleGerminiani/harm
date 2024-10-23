#pragma once

#include <stddef.h>
#include <string>

#include "Atom.hh"
#include "Float.hh"
#include "Int.hh"
#include "Limits.hh"
#include "PointerUtils.hh"

namespace expression {
class ExpVisitor;
enum class ExpType;

/// @brief Constant declaration.
/// This class represents a constant value.
template <typename T> class Constant : public Atom<T> {

public:
  /// @brief Constructor.
  explicit Constant(T value, ExpType type, size_t size,
                    size_t max_time);

  Constant(const Constant &other);

  /// @brief Destructor.
  ~Constant() = default;

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  void acceptVisitor(ExpVisitor &vis) override;

  /// @brief sets the value of the constant
  void set(T value);

private:
  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  ///  @brief the stored the constant value
  T _value;

  using Atom<T>::directEvaluate;
  using Atom<T>::disableCache;
  using Atom<T>::_max_time;
  using Atom<T>::_type;
  using Atom<T>::_size;
};

using FloatConstant = Constant<Float>;
using IntConstant = Constant<UInt>;
using BooleanConstant = Constant<bool>;

//smart pointer alias
using FloatConstantPtr = std::shared_ptr<FloatConstant>;
using IntConstantPtr = std::shared_ptr<IntConstant>;
using BooleanConstantPtr = std::shared_ptr<BooleanConstant>;

/// @brief Returns true if the given expression is a constant.
template <typename T> bool isConstant(const GenericPtr<T> &exp) {
  if constexpr (std::is_same_v<T, Proposition>) {
    return std::dynamic_pointer_cast<BooleanConstant>(exp) != nullptr;
  } else if constexpr (std::is_same_v<T, FloatExpression>) {
    return std::dynamic_pointer_cast<FloatConstant>(exp) != nullptr;
  } else if constexpr (std::is_same_v<T, IntExpression>) {
    return std::dynamic_pointer_cast<IntConstant>(exp) != nullptr;
  }
  return false;
}

/// @brief Returns the maximum value of the given type.
template <typename T>
GenericPtr<T> makeMaxConstant(const std::pair<ExpType, size_t> &type,
                              size_t max_time) {

  if constexpr (std::is_same_v<T, FloatExpression>) {
    return generatePtr<FloatConstant>(
        max<Float>(type.second), type.first, type.second, max_time);
  } else if constexpr (std::is_same_v<T, IntExpression>) {
    if (isSigned(type.first)) {
      return generatePtr<IntConstant>(
          max<SInt>(type.second), type.first, type.second, max_time);
    } else {
      return generatePtr<IntConstant>(
          max<UInt>(type.second), type.first, type.second, max_time);
    }
  } else if constexpr (std::is_same_v<T, Proposition>) {
    return generatePtr<BooleanConstant>(
        max<bool>(type.second), type.first, type.second, max_time);
  }

  messageError("makeMaxConstant not implemented for this type");
}

/// @brief Returns the minimum value of the given type.
template <typename T>
GenericPtr<T> makeMinConstant(const std::pair<ExpType, size_t> &type,
                              size_t max_time) {

  if constexpr (std::is_same_v<T, FloatExpression>) {
    return generatePtr<FloatConstant>(
        min<Float>(type.second), type.first, type.second, max_time);
  } else if constexpr (std::is_same_v<T, IntExpression>) {
    if (isSigned(type.first)) {
      return generatePtr<IntConstant>(
          min<SInt>(type.second), type.first, type.second, max_time);
    } else {
      return generatePtr<IntConstant>(
          min<UInt>(type.second), type.first, type.second, max_time);
    }
  } else if constexpr (std::is_same_v<T, Proposition>) {
    return generatePtr<BooleanConstant>(
        min<bool>(type.second), type.first, type.second, max_time);
  }

  messageError("makeMinConstant not implemented for this type");
}

} // namespace expression

#include "Constant.i.hh"
