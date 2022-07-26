#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <unordered_set>

#include "expUtils/VarType.hh"
#include "Logic.hh"

namespace expression {

// Forwards declaration of base class Visitor
class ExpVisitor;

/// @brief An Atom can represent either a Variable or a Constant.
/// It only provides the base methods evaluate and visit.
template <typename T> class Atom {
public:
  /// @brief Destructor.
  virtual ~Atom() = default;

  /// @brief Returns the value of the atom in the given simulation time
  /// @param time The simulation time
  /// @return The value of the atom
  virtual T evaluate(size_t time) = 0;

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  virtual void acceptVisitor(ExpVisitor &vis) = 0;

  /// @brief Returns the largest simulation time that can be provided to
  /// the method evaluate.
  virtual size_t getMaxTime();

  void setType(VarType type, size_t size);

  std::pair<VarType, size_t> getType();

protected:
  /// @brief Constructor of an Atom
  /// @param max_time the largest simulation time that can be provided to
  /// the method evaluate.
  Atom(VarType type = VarType::Bool, size_t size = 1, size_t max_time = 0);

  VarType _type;
  size_t _size;
  size_t _max_time;
};

using Numeric = double;

using NumericExpression = Atom<Numeric>;
using LogicExpression = Atom<ULogic>;
using Proposition = Atom<bool>;


} // namespace expression

#include "Atom.i.hh"
