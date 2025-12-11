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
  directEvaluate = [this](size_t time) {
    return Logic(this->_size, isSigned(this->_type),
                 (ULogic)_e->evaluate(time), 0, 0);
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
  directEvaluate = [this](size_t time) {
    return _e->getType().first == ExpType::SInt
               ? (SInt)_e->evaluate(time)
               : (UInt)_e->evaluate(time);
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
    return _e->getType().first == ExpType::SInt
               ? (SInt)_e->evaluate(time).getSignedValue()
               : (UInt)_e->evaluate(time).getUnsignedValue();
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

} // namespace expression
