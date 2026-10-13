#include "formula/expression/SignCast.hh"
#include "Logic.hh"
#include "expUtils/ExpType.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

// H25 (D-039): an integer is held in 64 bits, extended from its width by its type's sign (D-035): the cast
// re-extends its low bits with the new sign
template <> void IntSignCast::initEvaluate() {
  directEvaluate = [this](size_t time) {
    const size_t w = std::min<size_t>(this->_size, 64);
    UInt v = _e->evaluate(time);
    if (w >= 64) {
      return v;
    }
    v &= (UInt(1) << w) - 1;
    if (_toSigned && ((v >> (w - 1)) & 1)) {
      v |= ~((UInt(1) << w) - 1); // as a signed integer of width w, held in 64 bits
    }
    return v;
  };
  disableCache();
}

template <> void LogicSignCast::initEvaluate() {
  directEvaluate = [this](size_t time) {
    Logic l = _e->evaluate(time);
    l._isSigned = _toSigned;
    return l;
  };
  disableCache();
}

template <>
IntSignCast::SignCast(IntExpressionPtr e, bool toSigned)
    : IntExpression(toSigned ? ExpType::SInt : ExpType::UInt,
                    e->getType().second, e->getMaxTime()),
      _e(e), _toSigned(toSigned) {
  initEvaluate();
}

template <>
LogicSignCast::SignCast(LogicExpressionPtr e, bool toSigned)
    : LogicExpression(toSigned ? ExpType::SLogic : ExpType::ULogic,
                      e->getType().second, e->getMaxTime()),
      _e(e), _toSigned(toSigned) {
  initEvaluate();
}

template <> void IntSignCast::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void LogicSignCast::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

} // namespace expression
