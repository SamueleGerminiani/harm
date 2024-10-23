#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <type_traits>
#include <unordered_set>

#include "Float.hh"
#include "Int.hh"
#include "expUtils/ExpType.hh"
#include "expUtils/ope.hh"

namespace expression {

// Forwards declaration of base class Visitor
class ExpVisitor;

/// @brief An Atom is the base class for all the propositional expressions
template <typename T> class Atom {
public:
  /// @brief Destructor.
  virtual ~Atom();

  virtual void initEvaluate() = 0;

  /// @brief enables evaluation using cached values
  void enableCache();
  /// @brief disables evaluation using cached values
  void disableCache();
  /// @brief Returns true if the cache is enabled
  bool isCacheEnabled();

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  virtual void acceptVisitor(ExpVisitor &vis) = 0;

  /// @brief Returns the largest simulation time that can be provided to
  /// the method evaluate.
  size_t getMaxTime();

  /// @brief Returns the type of the expression
  std::pair<ExpType, size_t> getType();

  /// @brief Returns the operator of the expression
  /// Not all derived classes will have an operator, hence this method has a default implementation that returns NoOp
  virtual ope::ope getOperator();

  /// @brief The current evaluation function, direct or cached
  std::function<T(size_t)> evaluate = nullptr;

private:
  /// @brief fills the cache with the values of the atom (using the evaluate function)
  void fillCache();

  /// @brief The cache
  T *_cache = nullptr;

protected:
  /// @brief Constructor of an Atom
  /// @param max_time the largest simulation time that can be provided to
  /// the method evaluate.
  Atom(ExpType type = ExpType::Bool, size_t size = 1,
       size_t max_time = 0);

  /// @brief this function is used to evaluate the expression directly without using the cache
  std::function<T(size_t)> directEvaluate = nullptr;

  /// @brief The type of the expression
  ExpType _type;
  /// @brief The number of bits used to represent the expression
  size_t _size;
  /// @brief The largest simulation time that can be provided to
  size_t _max_time;
};

using FloatExpression = Atom<Float>;
using IntExpression = Atom<UInt>;
using Proposition = Atom<bool>;

//smart pointer aliases
using PropositionPtr = std::shared_ptr<Proposition>;
using PropositionPtrPtr = std::shared_ptr<PropositionPtr>;
using FloatExpressionPtr = std::shared_ptr<FloatExpression>;
using IntExpressionPtr = std::shared_ptr<IntExpression>;
template <typename T> using GenericPtr = std::shared_ptr<T>;
template <typename T>
using GenericPtrPtr = std::shared_ptr<GenericPtr<T>>;

} // namespace expression

#include "Atom.i.hh"
