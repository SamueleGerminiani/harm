#pragma once

#include "classes/atom/Atom.hh"
#include "colors.hh"
#include "expUtils/expUtils.hh"

namespace expression {

enum class FunctionType;

template <typename OT, typename ET>
Function<OT, ET>::Function(VarType type, size_t size, size_t max_time,
                           bool isTemporal)
    : _type(type), _size(size), _max_time(max_time), _isTemporal(isTemporal) {}

template <typename OT, typename ET> size_t Function<OT, ET>::getMaxTime() {
  return _max_time;
}

template <typename OT, typename ET>
void Function<OT, ET>::setType(VarType type, size_t size) {
  _type = type;
  _size = size;
}

template <typename OT, typename ET>
std::pair<VarType, size_t> Function<OT, ET>::getType() {
  return std::make_pair(_type, _size);
}

//Stable------------------------------------------

template <typename OT, typename ET>
Stable<OT, ET>::Stable(OT **op, std::string ph, VarType type, size_t size,
                       size_t max_time)
    : Function<OT, ET>(type, size, max_time, true), _op(op), _ph(ph) {}
template <typename OT, typename ET>
Stable<OT, ET>::Stable(OT *op, VarType type, size_t size, size_t max_time)
    : Function<OT, ET>(type, size, max_time, false) {
  _op = new Stable<OT, ET> *(op);
}

template <typename OT, typename ET> bool Stable<OT, ET>::evaluate(size_t time) {
  return time == 0 ? false
                   : (**_op).evaluate(time) == (**_op).evaluate(time - 1);
}

template <typename OT, typename ET>
void Stable<OT, ET>::acceptVisitor(ExpVisitor &vis) {
  (**_op).acceptVisitor(vis);
}

inline bool checkSub(bool sub, bool _isTemporal, std::string _ph) {
  if (sub && _isTemporal && _ph.front() == 'P')
    return true;
  else
    return false;
}
template <typename OT, typename ET>
std::string Stable<OT, ET>::toString(bool sub) {
  if constexpr (std::is_same<OT, Proposition>::value)
    return "$stable(" +
           (checkSub(sub, _isTemporal, _ph) ? _ph : prop2String(**_op)) + ")";
  else if constexpr (std::is_same<OT, LogicExpression>::value)
    return "$stable(" +
           (checkSub(sub, _isTemporal, _ph) ? _ph : logic2String(**_op)) + ")";
  else if constexpr (std::is_same<OT, NumericExpression>::value)
    return "$stable(" +
           (checkSub(sub, _isTemporal, _ph) ? _ph : num2String(**_op)) + ")";
  else
    return "";
}
template <typename OT, typename ET>
std::string Stable<OT, ET>::toColoredString(bool sub) {
  if constexpr (std::is_same<OT, Proposition>::value)
    return FUN("$stable(") +
           (checkSub(sub, _isTemporal, _ph) ? VAR(_ph)
                                            : prop2ColoredString(**_op)) +
           FUN(")");
  else if constexpr (std::is_same<OT, LogicExpression>::value)
    return FUN("$stable(") +
           (checkSub(sub, _isTemporal, _ph) ? VAR(_ph)
                                            : logic2ColoredString(**_op)) +
           FUN(")");
  else if constexpr (std::is_same<OT, NumericExpression>::value)
    return FUN("$stable(") +
           (checkSub(sub, _isTemporal, _ph) ? VAR(_ph)
                                            : num2ColoredString(**_op)) +
           FUN(")");
  else
    return "";
}

template <typename OT, typename ET> Stable<OT, ET>::~Stable() {
  if (!_isTemporal) {
    delete *_op;
    delete _op;
  }
}
template <typename OT, typename ET>
Stable<OT, ET>::Stable(const Stable &other) {
  OT *tmp = copy(**_op);
  _op = new OT *(tmp);
  _ph = other._ph;
  _type = other._type;
  _size = other._size;
  _max_time = other._max_time;
  _isTemporal = other._isTemporal;
}
template <typename OT, typename ET>
Function<OT, ET> *Stable<OT, ET>::cloneBare() {
  Stable<OT, ET> *ret = new Stable<OT, ET>(*this);
  ret->_ph = _ph;
  ret->_type = _type;
  ret->_size = _size;
  ret->_max_time = _max_time;
  ret->_isTemporal = _isTemporal;
  return ret;
}
template <typename OT, typename ET> Function<OT, ET> *Stable<OT, ET>::clone() {
  return new Stable<OT, ET>(*this);
}
template <typename OT, typename ET>
std::string Stable<OT, ET>::getPlaceholder() {
    messageErrorIf(!_isTemporal, "Function is not temporal");
    return _ph;
}
template <typename OT, typename ET>
  void Stable<OT, ET>::setPlaceholderPointer(OT** pp) {
      _op=pp;
  
  }
//------------------------------------------------

} // namespace expression
