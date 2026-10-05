#pragma once

#include <stddef.h>

#include <algorithm>
#include <utility>

#include "Logic.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class ExpVisitor;
} // namespace expression

namespace expression {

/// @brief Ternary declaration.
/// This class represents the conditional operator 'cond ? a : b' (SystemVerilog '?:'). The
/// condition is a proposition (2-valued in HARM); both branches have the type of the result.
template <typename ET> class Ternary : public ET {

public:
  /// @param type the type of the result (the common type of the branches)
  Ternary(const PropositionPtr &cond, const GenericPtr<ET> &whenTrue,
          const GenericPtr<ET> &whenFalse,
          std::pair<ExpType, size_t> type);

  /// @brief the result has the type of 'whenTrue'
  Ternary(const PropositionPtr &cond, const GenericPtr<ET> &whenTrue,
          const GenericPtr<ET> &whenFalse)
      : Ternary(cond, whenTrue, whenFalse, whenTrue->getType()) {}

  Ternary(const Ternary &other) = delete;
  Ternary &operator=(const Ternary &other) = delete;

  virtual ~Ternary() = default;

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  void acceptVisitor(ExpVisitor &vis) override;

  ope::ope getOperator() override { return ope::ope::Ternary; }

  PropositionPtr &getCondition() { return _cond; }
  GenericPtr<ET> &getWhenTrue() { return _whenTrue; }
  GenericPtr<ET> &getWhenFalse() { return _whenFalse; }

private:
  /// @brief Initialize the evaluation function, this method must me called in the constructor.
  void initEvaluate() override;

  PropositionPtr _cond;
  GenericPtr<ET> _whenTrue;
  GenericPtr<ET> _whenFalse;

  using ET::directEvaluate;
  using ET::disableCache;
};

using PropositionTernary = Ternary<Proposition>;
using IntTernary = Ternary<IntExpression>;
using LogicTernary = Ternary<LogicExpression>;
using FloatTernary = Ternary<FloatExpression>;

using PropositionTernaryPtr = std::shared_ptr<PropositionTernary>;
using IntTernaryPtr = std::shared_ptr<IntTernary>;
using LogicTernaryPtr = std::shared_ptr<LogicTernary>;
using FloatTernaryPtr = std::shared_ptr<FloatTernary>;

template <typename ET>
Ternary<ET>::Ternary(const PropositionPtr &cond,
                     const GenericPtr<ET> &whenTrue,
                     const GenericPtr<ET> &whenFalse,
                     std::pair<ExpType, size_t> type)
    : ET(type.first, type.second,
         std::min(cond->getMaxTime(),
                  std::min(whenTrue->getMaxTime(),
                           whenFalse->getMaxTime()))),
      _cond(cond), _whenTrue(whenTrue), _whenFalse(whenFalse) {
  initEvaluate();
}

template <typename ET> void Ternary<ET>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    return _cond->evaluate(time) ? _whenTrue->evaluate(time)
                                 : _whenFalse->evaluate(time);
  };
  disableCache();
}

/// logic branches may be narrower than the result: extend them (as SystemVerilog does)
template <> inline void Ternary<LogicExpression>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    Logic v = _cond->evaluate(time) ? _whenTrue->evaluate(time)
                                    : _whenFalse->evaluate(time);
    auto type = this->getType();
    return v._size == type.second
               ? v
               : resize(v, type.second, isSigned(type.first));
  };
  disableCache();
}

} // namespace expression
