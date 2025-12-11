#include "formula/expression/SetMembership.hh"
#include "expUtils/ope.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {
template <> void IntSetMembership::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

//Logic
template <> void LogicSetMembership::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
template <> void FloatSetMembership::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

template <> ope::ope IntSetMembership::getOperator() {
  return ope::ope::IntSetMembership;
}
template <> ope::ope LogicSetMembership::getOperator() {
  return ope::ope::LogicSetMembership;
}
template <> ope::ope FloatSetMembership::getOperator() {
  return ope::ope::FloatSetMembership;
}

template <>
SetMembership<IntExpression>::SetMembership(
    IntExpressionPtr e, const std::vector<IntExpressionPtr> &set,
    const std::vector<std::pair<IntExpressionPtr, IntExpressionPtr>>
        &ranges)
    : Proposition(e->getType().first, e->getType().second,
                  e->getMaxTime()),
      _e(e), _set(set), _ranges(ranges) {

  for (const auto &c : _set) {
    _conditions.push_back(
        makeGenericExpression<IntEq>(copy(_e), copy(c)));
  }
  for (const auto &r : _ranges) {
    PropositionPtr p1 =
        makeGenericExpression<IntGreaterEq>(copy(_e), copy(r.first));
    PropositionPtr p2 =
        makeGenericExpression<IntLessEq>(copy(_e), copy(r.second));
    _conditions.push_back(
        makeGenericExpression<PropositionAnd>(p1, p2));
  }

  initEvaluate();
}

template <>
SetMembership<LogicExpression>::SetMembership(
    LogicExpressionPtr e, const std::vector<LogicExpressionPtr> &set,
    const std::vector<
        std::pair<LogicExpressionPtr, LogicExpressionPtr>> &ranges)
    : Proposition(e->getType().first, e->getType().second,
                  e->getMaxTime()),
      _e(e), _set(set), _ranges(ranges) {

  for (const auto &c : _set) {
    _conditions.push_back(
        makeGenericExpression<LogicEq>(copy(_e), copy(c)));
  }
  for (const auto &r : _ranges) {
    PropositionPtr p1 = makeGenericExpression<LogicGreaterEq>(
        copy(_e), copy(r.first));
    PropositionPtr p2 =
        makeGenericExpression<LogicLessEq>(copy(_e), copy(r.second));
    _conditions.push_back(
        makeGenericExpression<PropositionAnd>(p1, p2));
  }

  initEvaluate();
}

template <>
SetMembership<FloatExpression>::SetMembership(
    FloatExpressionPtr e, const std::vector<FloatExpressionPtr> &set,
    const std::vector<
        std::pair<FloatExpressionPtr, FloatExpressionPtr>> &ranges)
    : Proposition(e->getType().first, e->getType().second,
                  e->getMaxTime()),
      _e(e), _set(set), _ranges(ranges) {

  for (const auto &c : _set) {
    _conditions.push_back(
        makeGenericExpression<FloatEq>(copy(_e), copy(c)));
  }
  for (const auto &r : _ranges) {
    PropositionPtr p1 = makeGenericExpression<FloatGreaterEq>(
        copy(_e), copy(r.first));
    PropositionPtr p2 =
        makeGenericExpression<FloatLessEq>(copy(_e), copy(r.second));
    _conditions.push_back(
        makeGenericExpression<PropositionAnd>(p1, p2));
  }

  initEvaluate();
}

} // namespace expression
