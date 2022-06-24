#pragma once

#include "classes/atom/Atom.hh"
#include "classes/atom/Constant.hh"

namespace expression {

/// @brief TypeCast declaration.
/// This class represents the bit selector operator
template <typename ET,typename RT> class TypeCast : public RT {


  public:
    TypeCast(ET *e);

    using ReturnType = typename std::conditional<
        std::is_same<RT, NumericExpression>::value, Numeric,
        typename std::conditional<std::is_same<RT, LogicExpression>::value,
                                  Logic, bool>::type>::type;
    /// @brief Copy constructor.
    TypeCast(const TypeCast &other) = delete;

    /// @brief Destructor.
    virtual ~TypeCast();

    /// @brief Evaluate the expression in a given simulation time.
    /// @param time The simulation time
    /// @return The value of the expression
    ReturnType evaluate(size_t time) override;

    /// @brief Accepts a visitor to visit the current object.
    /// @param vis The visitor.
    void acceptVisitor(ExpVisitor &vis) override;

    /// @brief Return the expression of the next operator
    /// @return A reference to the expression.
    ET &getItem();

    void popItem();

    /// @brief Assing operator
    TypeCast &operator=(const TypeCast &other) = delete;

  private:
    ET *_e;
};

using LogicToNumeric = TypeCast<LogicExpression, NumericExpression>;
using LogicToBool = TypeCast<LogicExpression, Proposition>;
using NumericToBool = TypeCast<NumericExpression, Proposition>;

} 

#include "TypeCast.i.hh"
