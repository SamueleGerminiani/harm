#pragma once
#include "PointerUtils.hh"
#include "expUtils/ExpType.hh"
#include "misc.hh"
#include <cstddef>
#include <sstream>
#include <string>
namespace expression {

//Past------------------------------------------

template <typename OT, typename ET>
Past<OT, ET>::Past(const PropositionPtrPtr &phPtr, size_t shift,
                   std::string ph, ExpType type, size_t size,
                   size_t max_time)
    : Function<OT, ET>(type, size, max_time, phPtr, ph),
      _shift(shift) {
  initEvaluate();
  _funName = "$past_" + std::to_string(shift);
}

template <typename OT, typename ET>
Past<OT, ET>::Past(const GenericPtr<OT> &op, size_t shift,
                   ExpType type, size_t size, size_t max_time)
    : Function<OT, ET>(type, size, max_time, op), _shift(shift) {
  initEvaluate();
  _funName = "$past_" + std::to_string(shift);
}

template <typename OT, typename ET>
void Past<OT, ET>::initEvaluate() {
  if constexpr (std::is_same<OT, LogicExpression>::value) {
    directEvaluate = [this](size_t time) {
      if ((int)time - (int)_shift < 0) {
        return Logic(1, 0, 0, 0, 0);
      }
      return _op->evaluate(time - _shift);
    };
  } else if constexpr (std::is_same<OT, Proposition>::value) {
    directEvaluate = [this](size_t time) {
      PropositionPtr &op = _isTemporal ? *_phPtr : _op;
      if ((int)time - (int)_shift < 0) {
        return false;
      }
      return op->evaluate(time - _shift);
    };
  } else {
    directEvaluate = [this](size_t time) {
      if ((int)time - (int)_shift < 0) {
        return (ReturnType)0;
      }
      return _op->evaluate(time - _shift);
    };
  }
  disableCache();
}

template <typename OT, typename ET>
std::string Past<OT, ET>::toString(bool sub) {
  std::stringstream ss;
  ss << "$past(";
  if (_isTemporal) {
    ss << (canSub<OT>(sub, _isTemporal, _ph, _phPtr)
               ? prop2String(*_phPtr)
               : _ph);
  } else {
    ss << exp2String(_op);
  }
  ss << (_shift != 1 ? "," + std::to_string(_shift) : "");
  ss << ")";
  return ss.str();
}

template <typename OT, typename ET>
std::string Past<OT, ET>::toColoredString(bool sub) {
  std::stringstream ss;
  ss << FUN("$past(");
  if (_isTemporal) {
    ss << (canSub<OT>(sub, _isTemporal, _ph, _phPtr)
               ? prop2ColoredString(*_phPtr)
               : VAR(_ph));
  } else {
    ss << exp2ColoredString(_op);
  }
  ss << (_shift != 1 ? "," + std::to_string(_shift) : "");
  ss << FUN(")");
  return ss.str();
}

template <typename OT, typename ET>
Past<OT, ET>::Past(const Past &other) {
  if (!other._isTemporal) {
    _op = copy(other._op);
    _phPtr = nullptr;
  } else {
    _phPtr = generatePtrPtr<Proposition>((Proposition *)nullptr);
    _op = nullptr;
  }
  _ph = other._ph;
  _type = other._type;
  _size = other._size;
  _max_time = other._max_time;
  _isTemporal = other._isTemporal;
  _shift = other._shift;
  initEvaluate();
}
template <typename OT, typename ET>
FunctionPtr<OT, ET> Past<OT, ET>::clone() {
  return generatePtr<Past<OT, ET>>(*this);
}

template <typename OT, typename ET> size_t Past<OT, ET>::getShift() {
  return _shift;
}
//------------------------------------------------

//Stable------------------------------------------

template <typename OT, typename ET>
Stable<OT, ET>::Stable(const PropositionPtrPtr &phPtr, std::string ph,
                       ExpType type, size_t size, size_t max_time)
    : Function<OT, ET>(type, size, max_time, phPtr, ph) {
  initEvaluate();
  _funName = "$stable";
}

template <typename OT, typename ET>
Stable<OT, ET>::Stable(const GenericPtr<OT> &op, ExpType type,
                       size_t size, size_t max_time)
    : Function<OT, ET>(type, size, max_time, op) {

  initEvaluate();
  _funName = "$stable";
}

template <typename OT, typename ET>
void Stable<OT, ET>::initEvaluate() {
  directEvaluate = [this](size_t time) {
    if constexpr (std::is_same<OT, Proposition>::value) {
      PropositionPtr &op = _isTemporal ? *_phPtr : _op;
      return time == 0 ? false
                       : op->evaluate(time) == op->evaluate(time - 1);
    } else {
      return time == 0
                 ? false
                 : _op->evaluate(time) == _op->evaluate(time - 1);
    }
  };
  disableCache();
}

template <typename OT, typename ET>
std::string Stable<OT, ET>::toString(bool sub) {
  std::stringstream ss;
  ss << "$stable(";
  if (_isTemporal) {
    ss << (canSub<OT>(sub, _isTemporal, _ph, _phPtr)
               ? prop2String(*_phPtr)
               : _ph);
  } else {
    ss << exp2String(_op);
  }
  ss << ")";
  return ss.str();
}
template <typename OT, typename ET>
std::string Stable<OT, ET>::toColoredString(bool sub) {
  std::stringstream ss;
  ss << FUN("$stable(");
  if (_isTemporal) {
    ss << (canSub<OT>(sub, _isTemporal, _ph, _phPtr)
               ? prop2ColoredString(*_phPtr)
               : VAR(_ph));
  } else {
    ss << exp2ColoredString(_op);
  }
  ss << FUN(")");
  return ss.str();
}

template <typename OT, typename ET>
Stable<OT, ET>::Stable(const Stable &other) {
  if (!other._isTemporal) {
    _op = copy(other._op);
    _phPtr = nullptr;
  } else {
    _phPtr = generatePtrPtr<Proposition>((Proposition *)nullptr);
    _op = nullptr;
  }
  _ph = other._ph;
  _type = other._type;
  _size = other._size;
  _max_time = other._max_time;
  _isTemporal = other._isTemporal;
  initEvaluate();
}

template <typename OT, typename ET>
FunctionPtr<OT, ET> Stable<OT, ET>::clone() {
  return generatePtr<Stable<OT, ET>>(*this);
}
//------------------------------------------------

//Rose------------------------------------------

template <typename OT, typename ET>
Rose<OT, ET>::Rose(const PropositionPtrPtr &phPtr, std::string ph,
                   ExpType type, size_t size, size_t max_time)
    : Function<OT, ET>(type, size, max_time, phPtr, ph) {

  initEvaluate();
  _funName = "$rose";
}

template <typename OT, typename ET>
Rose<OT, ET>::Rose(const GenericPtr<OT> &op, ExpType type,
                   size_t size, size_t max_time)
    : Function<OT, ET>(type, size, max_time, op) {

  initEvaluate();
  _funName = "$rose";
}

template <typename OT, typename ET>
std::string Rose<OT, ET>::toString(bool sub) {
  std::stringstream ss;
  ss << "$rose(";
  if (_isTemporal) {
    ss << (canSub<OT>(sub, _isTemporal, _ph, _phPtr)
               ? prop2String(*_phPtr)
               : _ph);
  } else {
    ss << exp2String(_op);
  }
  ss << ")";
  return ss.str();
}
template <typename OT, typename ET>
std::string Rose<OT, ET>::toColoredString(bool sub) {
  std::stringstream ss;
  ss << FUN("$rose(");
  if (_isTemporal) {
    ss << (canSub<OT>(sub, _isTemporal, _ph, _phPtr)
               ? prop2ColoredString(*_phPtr)
               : VAR(_ph));
  } else {
    ss << exp2ColoredString(_op);
  }
  ss << FUN(")");
  return ss.str();
}

template <typename OT, typename ET>
Rose<OT, ET>::Rose(const Rose &other) {
  if (!other._isTemporal) {
    _op = copy(other._op);
    _phPtr = nullptr;
  } else {
    _phPtr = generatePtrPtr<Proposition>((Proposition *)nullptr);
    _op = nullptr;
  }
  _ph = other._ph;
  _type = other._type;
  _size = other._size;
  _max_time = other._max_time;
  _isTemporal = other._isTemporal;
  initEvaluate();
}
template <typename OT, typename ET>
FunctionPtr<OT, ET> Rose<OT, ET>::clone() {
  return generatePtr<Rose<OT, ET>>(*this);
}
//------------------------------------------------

//Fell------------------------------------------

template <typename OT, typename ET>
Fell<OT, ET>::Fell(const PropositionPtrPtr &phPtr, std::string ph,
                   ExpType type, size_t size, size_t max_time)
    : Function<OT, ET>(type, size, max_time, phPtr, ph) {

  initEvaluate();
  _funName = "$fell";
}

template <typename OT, typename ET>
Fell<OT, ET>::Fell(const GenericPtr<OT> &op, ExpType type,
                   size_t size, size_t max_time)
    : Function<OT, ET>(type, size, max_time, op) {
  initEvaluate();
  _funName = "$fell";
}

template <typename OT, typename ET>
std::string Fell<OT, ET>::toString(bool sub) {
  std::stringstream ss;
  ss << "$fell(";
  if (_isTemporal) {
    ss << (canSub<OT>(sub, _isTemporal, _ph, _phPtr)
               ? prop2String(*_phPtr)
               : _ph);
  } else {
    ss << exp2String(_op);
  }
  ss << ")";
  return ss.str();
}
template <typename OT, typename ET>
std::string Fell<OT, ET>::toColoredString(bool sub) {
  std::stringstream ss;
  ss << FUN("$fell(");
  if (_isTemporal) {
    ss << (canSub<OT>(sub, _isTemporal, _ph, _phPtr)
               ? prop2ColoredString(*_phPtr)
               : VAR(_ph));
  } else {
    ss << exp2ColoredString(_op);
  }
  ss << FUN(")");
  return ss.str();
}

template <typename OT, typename ET>
Fell<OT, ET>::Fell(const Fell &other) {
  if (!other._isTemporal) {
    _op = copy(other._op);
    _phPtr = nullptr;
  } else {
    _phPtr = generatePtrPtr<Proposition>((Proposition *)nullptr);
    _op = nullptr;
  }
  _ph = other._ph;
  _type = other._type;
  _size = other._size;
  _max_time = other._max_time;
  _isTemporal = other._isTemporal;
  initEvaluate();
}
template <typename OT, typename ET>
FunctionPtr<OT, ET> Fell<OT, ET>::clone() {
  return generatePtr<Fell<OT, ET>>(*this);
}
//------------------------------------------------
} // namespace expression
