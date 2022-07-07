#pragma once

#include "Atom.hh"

namespace expression {

/// @brief Constant declaration.
/// This class represents a constant value.
template <typename T> class Constant : public Atom<T> {

  public:
    /// @brief Constructor.
    /// @param value a constant value.
    /// @param max_time the largest simulation time that can be provided to
    /// the method evaluate.
    explicit Constant(T value,VarType type,size_t size, size_t max_time);


    /// @brief Destructor.
    ~Constant() = default;

    /// @brief Returns the value of the constant in the given simulation time
    /// @param time The simulation time
    /// @return A value constant value
    T evaluate(size_t time) override;


    /// @brief Accepts a visitor to visit the current object.
    /// @param vis The visitor.
    void acceptVisitor(ExpVisitor &vis) override;

    void set(T value){_value=value;}

  private:
    ///  @brief Stores the constant value
    T _value;
};

using NumericConstant = Constant<Numeric>;
using LogicConstant   = Constant<Logic>;
using BooleanConstant = Constant<bool>;

} // namespace oden

#include "Constant.i.hh"
