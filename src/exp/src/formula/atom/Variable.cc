#include <stddef.h>
#include <string>

#include "Logic.hh"
#include "String.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {
enum class ExpType;
}

namespace expression {

//Boolean----------------------------------------------
BooleanVariable::BooleanVariable(unsigned int *v,
                                 const std::string &name,
                                 size_t max_time)
    : Atom<bool>(ExpType::Bool, 1, max_time), _v(v), _name(name) {

  initEvaluate();
}
BooleanVariable::BooleanVariable(const BooleanVariable &other) {
  _v = other._v;
  _name = other._name;
  _size = other._size;
  _max_time = other._max_time;
  _type = other._type;
  initEvaluate();
}

void BooleanVariable::initEvaluate() {
  directEvaluate = [this](size_t time) {
    size_t tPos = time >> 5;
    unsigned int _buffer = _v[tPos];
    return (_buffer & (1 << (time & 31))) != 0;
  };
  disableCache();
}

void BooleanVariable::assign(size_t time, bool value) {
  if (value)
    _v[time >> 5] |= 1 << (time & 31);
  else
    _v[time >> 5] &= ~(1 << (time & 31));
}

void BooleanVariable::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

//Logic----------------------------------------------
LogicVariable::LogicVariable(ULogic *v[3], const std::string &name,
                             ExpType type, size_t size,
                             size_t max_time)
    : Atom<Logic>(type, size, max_time), _name(name) {
  _v[0] = v[0];
  _v[1] = v[1];
  _v[2] = v[2];
  messageErrorIf(size > sizeOfLogic() * 8,
                 "Not supported size for Logic");

  // Setting the mask to read only _size bits
  _mask = ((ULogic)1 << _size) - 1;
  _valuesInside = _val4Logic / _size;

  initEvaluate();
}

LogicVariable::LogicVariable(const LogicVariable &other) {
  _v[0] = other._v[0];
  _v[1] = other._v[1];
  _v[2] = other._v[2];
  _name = other._name;
  _size = other._size;
  _max_time = other._max_time;
  _type = other._type;
  _mask = other._mask;
  _valuesInside = other._valuesInside;
  initEvaluate();
}

void LogicVariable::initEvaluate() {
  directEvaluate = [this](size_t time) {
    if (_size > sizeOfLogic() * 4)
      return Logic(_size, isSigned(this->_type), _v[0][time],
                   _v[1][time], _v[2][time]);

    size_t tPos = time / _valuesInside;
    size_t shift = _size * (time % _valuesInside);

    ULogic val_i = _v[0][tPos] & (_mask << shift);
    ULogic val_x = _v[1][tPos] & (_mask << shift);
    ULogic val_z = _v[2][tPos] & (_mask << shift);

    ULogic ret_i = val_i >> shift;
    ULogic ret_x = val_x >> shift;
    ULogic ret_z = val_z >> shift;

    if (_type == ExpType::SLogic && ((1 << (_size - 1)) & ret_i)) {
      return Logic(_size, isSigned(this->_type), ret_i | ~_mask,
                   ret_x, ret_z);
    }

    return Logic(_size, isSigned(this->_type), ret_i, ret_x, ret_z);
  };
  disableCache();
}

void LogicVariable::assign(size_t time, Logic value) {
  if (_size > sizeOfLogic() * 4) {
    _v[0][time] = value._int;
    _v[1][time] = value._x;
    _v[2][time] = value._z;
    return;
  }

  size_t tPos = time / _valuesInside;
  ULogic traceValue_i = _v[0][tPos];
  ULogic traceValue_x = _v[1][tPos];
  ULogic traceValue_z = _v[2][tPos];

  size_t shift = _size * (time % _valuesInside);
  ULogic val_i = value._int << shift;
  ULogic val_x = value._x << shift;
  ULogic val_z = value._z << shift;

  // delete value
  traceValue_i = traceValue_i & ~(_mask << shift);
  traceValue_x = traceValue_x & ~(_mask << shift);
  traceValue_z = traceValue_z & ~(_mask << shift);

  // set new value
  _v[0][tPos] = traceValue_i | val_i;
  _v[1][tPos] = traceValue_x | val_x;
  _v[2][tPos] = traceValue_z | val_z;
}

void LogicVariable::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

//Int----------------------------------------------

IntVariable::IntVariable(UInt *v, const std::string &name,
                         ExpType type, size_t size, size_t max_time)
    : Atom<UInt>(type, size, max_time), _v(v), _name(name) {
  messageErrorIf(size > 64, "Not supported size for Int");

  // Setting the mask to read only _size bits
  _mask = (1ULL << _size) - 1;
  _valuesInside = _val4Int / _size;

  initEvaluate();
}
IntVariable::IntVariable(const IntVariable &other) {
  _v = other._v;
  _name = other._name;
  _size = other._size;
  _max_time = other._max_time;
  _type = other._type;
  _mask = other._mask;
  _valuesInside = other._valuesInside;
  initEvaluate();
}

void IntVariable::initEvaluate() {
  directEvaluate = [this](size_t time) {
    if (_size > 32)
      return _v[time];

    size_t tPos = time / _valuesInside;
    size_t shift = _size * (time % _valuesInside);
    UInt value = _v[tPos] & (_mask << shift);

    UInt ret = value >> shift;
    if (_type == ExpType::SInt && ((1 << (_size - 1)) & ret))
      return ret | ~_mask;

    return ret;
  };
  disableCache();
}

void IntVariable::assign(size_t time, UInt value) {
  if (_size > 32) {
    _v[time] = value;
    return;
  }

  size_t tPos = time / _valuesInside;
  UInt traceValue = _v[tPos];

  size_t shift = _size * (time % _valuesInside);
  value = value << shift;

  // delete value
  traceValue = traceValue & ~(_mask << shift);

  // set new value
  _v[tPos] = traceValue | value;
}

void IntVariable::acceptVisitor(ExpVisitor &vis) { vis.visit(*this); }

//String----------------------------------------------

StringVariable::StringVariable(String *v, const std::string &name,
                               ExpType type, size_t size,
                               size_t max_time)
    : Atom<String>(type, size, max_time), _v(v), _name(name) {

  initEvaluate();
}

StringVariable::StringVariable(const StringVariable &other) {
  _v = other._v;
  _name = other._name;
  _size = other._size;
  _max_time = other._max_time;
  _type = other._type;
  initEvaluate();
}

void StringVariable::initEvaluate() {
  directEvaluate = [this](size_t time) { return _v[time]; };
  disableCache();
}

void StringVariable::assign(size_t time, String value) {
  _v[time] = value;
}

void StringVariable::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}

//Float----------------------------------------------

FloatVariable::FloatVariable(Float *v, const std::string &name,
                             ExpType type, size_t size,
                             size_t max_time)
    : Atom<Float>(type, size, max_time), _v(v), _name(name) {
  initEvaluate();
}
FloatVariable::FloatVariable(const FloatVariable &other) {
  _v = other._v;
  _name = other._name;
  _size = other._size;
  _max_time = other._max_time;
  _type = other._type;
  initEvaluate();
}

void FloatVariable::initEvaluate() {
  directEvaluate = [this](size_t time) { return _v[time]; };
  disableCache();
}

void FloatVariable::assign(size_t time, Float value) {
  _v[time] = value;
}

void FloatVariable::acceptVisitor(ExpVisitor &vis) {
  vis.visit(*this);
}
} // namespace expression
