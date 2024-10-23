#include "formula/atom/NumericExpression.hh"
#include "../../clustering/include/ClusteringConfig.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class ExpVisitor;
enum class ExpType;

NumericExpression::NumericExpression(const FloatExpressionPtr &floe,
                                     bool useCache)
    : _floe(floe), _useCache(useCache) {

  if (_useCache) {
    _cachedd = new double[floe->getMaxTime()];
    for (size_t i = 0; i < floe->getMaxTime(); i++) {
      _cachedd[i] = floe->evaluate(i);
    }
  }
}
NumericExpression::NumericExpression(const IntExpressionPtr &inte,
                                     bool useCache)
    : _inte(inte), _useCache(useCache) {

  if (_useCache) {
    _cachedi = new UInt[inte->getMaxTime()];
    for (size_t i = 0; i < inte->getMaxTime(); i++) {
      _cachedi[i] = (UInt)inte->evaluate(i);
    }
  }
}

NumericExpression::~NumericExpression() {
  if (_floe != nullptr) {
    if (_useCache) {
      delete[] _cachedd;
    }
  } else if (_inte != nullptr) {
    if (_useCache) {
      delete[] _cachedi;
    }
  } else {
    messageError("NumericExpression::~NumericExpression(): _floe and "
                 "_int are all nullptr");
  }
}

template <> double NumericExpression::evaluate(size_t time) {
  return _useCache ? _cachedd[time] : _floe->evaluate(time);
}
template <> UInt NumericExpression::evaluate(size_t time) {
  return _useCache ? (UInt)_cachedi[time]
                   : (UInt)_inte->evaluate(time);
}
template <> SInt NumericExpression::evaluate(size_t time) {
  return _useCache ? (SInt)_cachedi[time]
                   : (SInt)_inte->evaluate(time);
}

void NumericExpression::acceptVisitor(ExpVisitor &vis) {
  if (_floe != nullptr) {
    _floe->acceptVisitor(vis);
  } else if (_inte != nullptr) {
    _inte->acceptVisitor(vis);
  } else {
    messageError("NumericExpression::acceptVisitor(): _floe and "
                 "_inte are all nullptr");
  }
}

size_t NumericExpression::getMaxTime() {
  if (_floe != nullptr) {
    return _floe->getMaxTime();
  } else if (_inte != nullptr) {
    return _inte->getMaxTime();
  } else {
    messageError("NumericExpression::getMaxTime(): _floe and _inte "
                 "are all nullptr");
  }
  return 0;
}

std::pair<ExpType, size_t> NumericExpression::getType() {
  if (_floe != nullptr) {
    return _floe->getType();
  } else if (_inte != nullptr) {
    return _inte->getType();
  } else {
    messageError("NumericExpression::getType(): _floe and _inte are "
                 "all nullptr");
  }
  return std::pair<ExpType, size_t>();
}

template <> FloatExpressionPtr NumericExpression::get() {
  return _floe;
}
template <> IntExpressionPtr NumericExpression::get() {
  return _inte;
}

} // namespace expression
