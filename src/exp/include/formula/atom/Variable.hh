#pragma once

#include "Atom.hh"
#include "Int.hh"

#include <climits>
#include <string>

namespace expression {

/// @brief This class represents a Int variable.
class IntVariable : public Atom<UInt> {
public:
  /// @brief Constructor for Int.
  /// @param v A pointer to the variable's values.
  /// @param size The size of the int value.
  /// @param name the name of the variable.
  /// @param max_time the largest simulation time that can be provided to
  /// the method evaluate.
  IntVariable(UInt *v, const std::string &name, ExpType type,
              size_t size, size_t max_time);

  IntVariable(const IntVariable &other);

  IntVariable &operator=(const IntVariable &other) = delete;

  ~IntVariable() override = default;

  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  /// @brief Sets the value of the variable in a given simulation time.
  /// @param time The simulation time.
  /// @param value The value set for the variable.
  void assign(size_t time, UInt value);

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  void acceptVisitor(ExpVisitor &vis) override;

  std::string getName() { return _name; }
  // declare friend class to allow it access private variables
  friend class TraceChangerVisitor;

private:
  /// A pointer to variable's values
  // This pointer must not be deallocated as values are stored in a Trace!
  UInt *_v;

  std::string _name;

  /// mask to get a Int value from a UInt value.
  UInt _mask;

  /// number of values stored in UInt.
  size_t _valuesInside;

  ///number of bits in UInt
  const size_t _val4Int = sizeof(expression::UInt) * CHAR_BIT;

  using Atom<UInt>::directEvaluate;
  using Atom<UInt>::disableCache;
};

/// @brief This class represents a Float variable.
class FloatVariable : public Atom<Float> {
public:
  /// @brief Constructor for Float.
  /// @param v A pointer to the variable's values
  /// @param name the name of the variable
  /// @param max_time the largest simulation time that can be provided to
  /// the method evaluate.
  FloatVariable(Float *v, const std::string &name, ExpType type,
                size_t size, size_t max_time);

  FloatVariable(const FloatVariable &other);

  FloatVariable &operator=(const FloatVariable &other) = delete;

  ~FloatVariable() override = default;

  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  /// @brief Sets the value of the variable in a given simulation time.
  /// @param time The simulation time.
  /// @param value The value set for the variable.
  void assign(size_t time, Float value);

  /// @brief Assignment operator.
  /// @param other The other variable to be copied.

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  void acceptVisitor(ExpVisitor &vis) override;

  std::string getName() { return _name; }
  // declare friend class to allow it access private variables
  friend class TraceChangerVisitor;

private:
  /// A pointer to variable's values
  // This pointer must not be deallocated as values are stored in a Trace!
  Float *_v;
  /// @brief name of the variable
  std::string _name;

  using Atom<Float>::directEvaluate;
  using Atom<Float>::disableCache;
};

/// @brief This class represents a bool variable.
class BooleanVariable : public Atom<bool> {

public:
  /// @brief Constructor.
  /// @param v Pointer to variable's values
  /// @param name The name of the variable
  /// @param max_time the largest simulation time that can be provided to
  /// the method evaluate.
  BooleanVariable(unsigned int *v, const std::string &name,
                  size_t max_time);

  BooleanVariable(const BooleanVariable &other);
  BooleanVariable &operator=(const BooleanVariable &other) = delete;

  ~BooleanVariable() override = default;

  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  /// @brief Sets the value of the variable in a given simulation time
  /// @param time The simulation time
  /// @param value The value set for the variable
  void assign(size_t time, bool value);

  /// @brief Assignment operator
  /// @param other The other variable to be copied.

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  void acceptVisitor(ExpVisitor &vis) override;
  std::string getName() { return _name; }

  // declare friend class to allow it access private variables
  friend class TraceChangerVisitor;

private:
  /// A pointer to variable's values
  // This pointer must not be deallocated as values are stored in a Trace!
  unsigned int *_v;
  /// @brief name of the variable
  std::string _name;

  using Atom<bool>::directEvaluate;
  using Atom<bool>::disableCache;
};

//smart pointer alias
using IntVariablePtr = std::shared_ptr<IntVariable>;
using FloatVariablePtr = std::shared_ptr<FloatVariable>;
using BooleanVariablePtr = std::shared_ptr<BooleanVariable>;

template <typename T> bool isVariable(const GenericPtr<T> &exp) {
  if constexpr (std::is_same_v<T, Proposition>) {
    return std::dynamic_pointer_cast<BooleanVariable>(exp) != nullptr;
  } else if constexpr (std::is_same_v<T, FloatExpression>) {
    return std::dynamic_pointer_cast<FloatVariable>(exp) != nullptr;
  } else if constexpr (std::is_same_v<T, IntExpression>) {
    return std::dynamic_pointer_cast<IntVariable>(exp) != nullptr;
  } else {
    return false;
  }
}

} // namespace expression
