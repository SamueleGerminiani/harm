#pragma once

#include <stddef.h>
#include <type_traits>

#include "Int.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class ExpVisitor;
class Logic;
} // namespace expression

namespace expression {

/// @brief BitSelector declaration.
/// This class represents the bit selector operator
template <typename ET, typename RT> class BitSelector : public RT {

public:
  BitSelector(const GenericPtr<ET> &e, size_t lower_bound,
              size_t upper_bound);

  using ReturnType = typename std::conditional<
      std::is_same<RT, IntExpression>::value, UInt, Logic>::type;
  BitSelector(const BitSelector &other) = delete;

  virtual ~BitSelector();

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  void acceptVisitor(ExpVisitor &vis) override;

  /// @brief Return the expression of the next operator
  /// @return A reference to the expression.
  GenericPtr<ET> &getItem();

  /// @brief Assing operator
  BitSelector &operator=(const BitSelector &other) = delete;

  size_t getLowerBound();
  size_t getUpperBound();

  /// @brief The indices as written in the source ([left:right], SystemVerilog indices of a
  /// variable with a declared range, D-028), printed instead of the bit positions; -1 if none
  void setSourceIndices(long left, long right);
  long getSourceLeft();
  long getSourceRight();

private:
  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  GenericPtr<ET> _e;
  size_t _lower_bound;
  size_t _upper_bound;
  long _source_left = -1;
  long _source_right = -1;

  using RT::directEvaluate;
  using RT::disableCache;
};
using IntBitSelector = BitSelector<IntExpression, IntExpression>;
using LogicBitSelector =
    BitSelector<LogicExpression, LogicExpression>;

} // namespace expression

#include "BitSelector.i.hh"
