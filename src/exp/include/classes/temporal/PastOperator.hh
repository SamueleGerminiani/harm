#pragma once


#include "classes/atom/Atom.hh"

namespace expression {

/// @brief PastOperator declaration.
/// This class represents the temporal operator Next
template <typename ET> class PastOperator : public ET {

    using ReturnType = typename std::conditional<
        std::is_same<ET, NumericExpression>::value, Numeric,
        typename std::conditional<std::is_same<ET, LogicExpression>::value,
                                  Logic, bool>::type>::type;

  public:
    /// @brief Given an expression e, and a temporal offset t, the constructor
    /// defines the new expression X[offset](p)
    /// @param e An expression
    /// @param offset A temporal offset
    PastOperator(ET *e, size_t offset);

    /// @brief Copy constructor.
    PastOperator(const PastOperator &other) = delete;

    /// @brief Destructor.
    virtual ~PastOperator();

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

    /// @brief Assing operator
    PastOperator &operator=(const PastOperator &other) = delete;

    /// @brief Return the temporal offset of the Next operator
    /// @return temporal offset
    size_t getOffset();

  private:
    // The evaluated expression at time t + offset
    ET *_e;
    // The temporal offset
    size_t _offset;
};

using NumericPast     = PastOperator<NumericExpression>;
using LogicPast       = PastOperator<LogicExpression>;
using PropositionPast = PastOperator<Proposition>;

} // namespace oden

#include "PastOperator.i.hh"
