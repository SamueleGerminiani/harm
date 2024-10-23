#include <memory>
#include <utility>

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

//------------------acceptVisitor------------------
template <> void IntToFloat::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void IntToBool::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void FloatToBool::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void FloatToInt::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

} // namespace expression
