#include <memory>
#include <utility>

#include "Logic.hh"
#include "expUtils/ExpType.hh"
#include "formula/expression/TypeCast.hh"
#include "message.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

//------------------init evaluate------------------

template <> void IntToBool::initEvaluate() {
  directEvaluate = [this](size_t time) { return _e->evaluate(time); };
  disableCache();
}

template <> void IntToLogic::initEvaluate() {
  // D-035: the integer extended from its own width to the cast's (a context may widen the cast):
  // sign-extended when both are signed, zero-extended otherwise (IEEE 1800-2017 11.8.2)
  directEvaluate = [this](size_t time) {
    UInt raw = _e->evaluate(time);
    const size_t w = std::min<size_t>(_e->getType().second, 64);
    const bool sx = isSigned(this->_type) && isSigned(_e->getType().first);
    ULogic v;
    if (w >= 64) {
      v = sx && (SInt)raw < 0 ? ~((ULogic)~raw) : (ULogic)raw;
    } else if (sx && ((raw >> (w - 1)) & 1)) {
      ULogic m = (ULogic(1) << w) - 1;
      v = ~ULogic(0) & ~m | ((ULogic)raw & m); // the sign bit repeated above the own width
    } else {
      v = (ULogic)(raw & ((UInt(1) << w) - 1));
    }
    if (this->_size < sizeOfLogic() * 8) {
      v &= (ULogic(1) << this->_size) - 1;
    }
    return Logic(this->_size, isSigned(this->_type), v, 0, 0);
  };
  disableCache();
}

template <> void IntToFloat::initEvaluate() {
  directEvaluate = [this](size_t time) {
    return _e->getType().first == ExpType::SInt
               ? (Float)(SInt)_e->evaluate(time)
               : (Float)(UInt)_e->evaluate(time);
  };
  disableCache();
}
template <> void FloatToBool::initEvaluate() {
  directEvaluate = [this](size_t time) { return _e->evaluate(time); };
  disableCache();
}

template <> void FloatToInt::initEvaluate() {
  // D-035: a float becomes a signed integer (truncated towards zero), as the cast's type says
  directEvaluate = [this](size_t time) {
    return (UInt)(SInt)_e->evaluate(time);
  };
  disableCache();
}

template <> void FloatToLogic::initEvaluate() {
  directEvaluate = [this](size_t time) {
    return Logic(64, 1, (ULogic)(SLogic)_e->evaluate(time), 0, 0);
  };
  disableCache();
}

template <> void LogicToFloat::initEvaluate() {
  directEvaluate = [this](size_t time) {
    return _e->getType().first == ExpType::SLogic
               ? (Float)_e->evaluate(time).getSignedValue()
               : (Float)_e->evaluate(time).getUnsignedValue();
  };
  disableCache();
}

template <> void LogicToBool::initEvaluate() {
  directEvaluate = [this](size_t time) {
    return _e->evaluate(time).getUnsignedValue() != (ULogic)0;
  };
  disableCache();
}

template <> void LogicToInt::initEvaluate() {
  directEvaluate = [this](size_t time) {
    // D-035: the sign of the logic operand (its type is SLogic or ULogic, never SInt)
    return isSigned(_e->getType().first)
               ? (UInt)(SInt)_e->evaluate(time).getSignedValue()
               : (UInt)_e->evaluate(time).getUnsignedValue();
  };
  disableCache();
}

template <> void BoolToLogic::initEvaluate() {
  directEvaluate = [this](size_t time) {
    return Logic(1, false, (ULogic)(_e->evaluate(time) ? 1 : 0), 0, 0);
  };
  disableCache();
}

//-----constructors-----

//int
template <>
IntToFloat::TypeCast(IntExpressionPtr e)
    : FloatExpression(ExpType::Float, 64, e->getMaxTime()), _e(e) {

  initEvaluate();
}
template <>
IntToBool::TypeCast(IntExpressionPtr e)
    : Proposition(ExpType::Bool, 1, e->getMaxTime()), _e(e) {

  initEvaluate();
}

template <>
IntToLogic::TypeCast(IntExpressionPtr e)
    : LogicExpression(isSigned(e->getType().first) ? ExpType::SLogic
                                                   : ExpType::ULogic,
                      e->getType().second, e->getMaxTime()),
      _e(e) {

  initEvaluate();
}

//logic
template <>
LogicToInt::TypeCast(LogicExpressionPtr e)
    : IntExpression(isSigned(e->getType().first) ? ExpType::SInt
                                                 : ExpType::UInt,
                    e->getType().second, e->getMaxTime()),
      _e(e) {
  messageErrorIf(
      e->getType().second > 64,
      "LogicToInt: LogicExpression size is greater than 64 bits");

  initEvaluate();
}

template <>
LogicToFloat::TypeCast(LogicExpressionPtr e)
    : FloatExpression(ExpType::Float, 64, e->getMaxTime()), _e(e) {
  messageWarningIf(
      e->getType().second > 64,
      "LogicToFloat : LogicExpression size is greater than 64 bits");

  initEvaluate();
}
template <>
LogicToBool::TypeCast(LogicExpressionPtr e)
    : Proposition(ExpType::Bool, 1, e->getMaxTime()), _e(e) {

  initEvaluate();
}

//float
template <>
FloatToBool::TypeCast(FloatExpressionPtr e)
    : Proposition(ExpType::Bool, 1, e->getMaxTime()), _e(e) {

  initEvaluate();
}

template <>
FloatToInt::TypeCast(FloatExpressionPtr e)
    : IntExpression(ExpType::SInt, 64, e->getMaxTime()), _e(e) {

  initEvaluate();
}

template <>
FloatToLogic::TypeCast(FloatExpressionPtr e)
    : LogicExpression(ExpType::SLogic, 64, e->getMaxTime()), _e(e) {

  initEvaluate();
}

//bool
template <>
BoolToLogic::TypeCast(PropositionPtr e)
    : LogicExpression(ExpType::ULogic, 1, e->getMaxTime()), _e(e) {

  initEvaluate();
}

//------------------acceptVisitor------------------
template <> void IntToFloat::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void IntToBool::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void IntToLogic::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void LogicToFloat::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void LogicToBool::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void LogicToInt::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void FloatToBool::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void FloatToInt::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void FloatToLogic::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void BoolToLogic::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

} // namespace expression
