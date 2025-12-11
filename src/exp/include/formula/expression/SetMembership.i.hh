#include "Limits.hh"
#include "expUtils/expUtils.hh"
#include "expUtils/ope.hh"
#include "globals.hh"
#include <typeinfo>
#include <unordered_set>
#include <vector>

namespace expression {

template <typename T> SetMembership<T>::~SetMembership() {}

template <typename T>
SetMembership<T>::SetMembership(const SetMembership &other) {

  _e = copy(other._e);

  for (auto c : other._conditions) {
    _conditions.push_back(copy(c));
  }

  for (auto s : other._set) {
    _set.push_back(copy(s));
  }

  for (auto &[left, right] : other._ranges) {
    _ranges.push_back(std::make_pair(copy(left), copy(right)));
  }

  initEvaluate();
}

template <typename T> GenericPtr<T> &SetMembership<T>::getItem() {
  return _e;
}

template <typename T>
std::vector<GenericPtr<T>> SetMembership<T>::getSet() {
  return _set;
}

template <typename T>
std::vector<std::pair<GenericPtr<T>, GenericPtr<T>>>
SetMembership<T>::getRanges() {
  return _ranges;
}

template <typename T> std::string SetMembership<T>::valuesToString() {
  std::string s = "{";
  for (const auto &v : _set) {
    s += exp2String(v) + ",";
  }

  if (_ranges.empty()) {
    s.pop_back();
  } else {

    //print ranges
    for (const auto &r : _ranges) {

      std::string left = "";
      std::string right = "";

      if (isConstant(r.first) && isRangeConstantMin(r.first)) {
        left = "$";
      } else {
        left = exp2String(r.first);
      }

      if (isConstant(r.second) && isRangeConstantMax(r.second)) {
        right = "$";
      } else {
        right = exp2String(r.second);
      }

      s += "[" + left + ":" + right + "],";
      s.pop_back();

    } //for ranges

  } //else print range

  s += "}";
  return s;
}

template <typename T> void SetMembership<T>::initEvaluate() {

  directEvaluate = [this](size_t time) {
    for (auto ci : _conditions) {
      if (ci->evaluate(time)) {
        return true;
      }
    }
    return false;
  };
  disableCache();
}

template <typename T>
bool SetMembership<T>::isRangeConstantMax(
    const GenericPtr<T> &maxConstant) {

  messageErrorIf(!isConstant(maxConstant),
                 "isRangeConstantMax: Not a constant");

  size_t length = _e->getType().second;

  if constexpr (std::is_same_v<T, FloatExpression>) {
    return maxConstant->evaluate(0) == max<Float>(length);
  } else if constexpr (std::is_same_v<T, IntExpression>) {
    return isSigned(maxConstant->getType().first)
               ? (SInt)maxConstant->evaluate(0) == max<SInt>(length)
               : maxConstant->evaluate(0) == max<UInt>(length);
  } else if constexpr (std::is_same_v<T, LogicExpression>) {
    return isSigned(maxConstant->getType().first)
               ? maxConstant->evaluate(0).getSignedValue() ==
                     max<SLogic>(length)
               : maxConstant->evaluate(0).getUnsignedValue() ==
                     max<ULogic>(length);
  } else if constexpr (std::is_same_v<T, Proposition>) {
    return maxConstant->evaluate(0) == max<bool>(length);
  }

  messageError("isRangeConstantMax: Type not supported");
}

template <typename T>
bool SetMembership<T>::isRangeConstantMin(
    const GenericPtr<T> &minConstant) {
  messageErrorIf(!isConstant(minConstant),
                 "isRangeConstantMin: Not a constant");

  size_t length = _e->getType().second;

  if constexpr (std::is_same_v<T, FloatExpression>) {
    return minConstant->evaluate(0) == min<Float>(length);
  } else if constexpr (std::is_same_v<T, IntExpression>) {
    return isSigned(minConstant->getType().first)
               ? (SInt)minConstant->evaluate(0) == min<SInt>(length)
               : minConstant->evaluate(0) == min<UInt>(length);
  } else if constexpr (std::is_same_v<T, LogicExpression>) {
    return isSigned(minConstant->getType().first)
               ? minConstant->evaluate(0).getSignedValue() ==
                     min<SLogic>(length)
               : minConstant->evaluate(0).getUnsignedValue() ==
                     min<ULogic>(length);
  } else if constexpr (std::is_same_v<T, Proposition>) {
    return minConstant->evaluate(0) == min<bool>(length);
  }

  messageError("isRangeConstantMin: Type not supported");
}

} // namespace expression
