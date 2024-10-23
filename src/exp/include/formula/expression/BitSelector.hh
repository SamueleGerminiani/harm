#pragma once

#include <stddef.h>
#include <type_traits>

#include "Int.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class ExpVisitor;
} // namespace expression

namespace expression {

/// @brief BitSelector declaration.
/// This class represents the bit selector operator
template <typename ET, typename RT> class BitSelector : public RT {

public:
  BitSelector(const GenericPtr<ET> &e, size_t lower_bound,
              size_t upper_bound);

  using ReturnType = UInt;
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

private:
  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  GenericPtr<ET> _e;
  size_t _lower_bound;
  size_t _upper_bound;

  using RT::directEvaluate;
  using RT::disableCache;
};
using IntBitSelector = BitSelector<IntExpression, IntExpression>;

} // namespace expression

#include "BitSelector.i.hh"
