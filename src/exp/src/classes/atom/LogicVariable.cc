#include "classes/atom/Variable.hh"
#include "visitors/ExpVisitor.hh"
#include "message.hh"
#include <iostream>
#include <bitset>

namespace expression {

LogicVariable::LogicVariable(ULogic *v, const std::string &name,
                              VarType type, size_t size, size_t max_time)
    : Atom<ULogic>(type, size, max_time), _v(v), _name(name) {
  messageErrorIf(size > 64, "Not supported size for Logic");

  // Setting the mask to read only _size bits
  _mask = (1ULL << _size) - 1;
  _valuesInside = _val4Logic / _size;
}

ULogic LogicVariable::evaluate(size_t time) {
  if (_size > 32)
    return _v[time];

  size_t tPos = time / _valuesInside;
  size_t shift = _size * (time % _valuesInside);
  ULogic value = _v[tPos] & (_mask << shift);

  ULogic ret = value >> shift;
  if (_type == VarType::SLogic && ((1 << (_size - 1)) & ret))
    return ret | ~_mask;

  return ret;
}

void LogicVariable::assign(size_t time, ULogic value) {
  if (_size > 32) {
    _v[time] = value;
    return;
  }

  size_t tPos = time / _valuesInside;
  ULogic traceValue = _v[tPos];

  size_t shift = _size * (time % _valuesInside);
  value = value << shift;

  // delete value
  traceValue = traceValue & ~(_mask << shift);

  // set new value
  _v[tPos] = traceValue | value;
}

void LogicVariable::acceptVisitor(ExpVisitor &vis) { vis.visit(*this); }

} // namespace expression
