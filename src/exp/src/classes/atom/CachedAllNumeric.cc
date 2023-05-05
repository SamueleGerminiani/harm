#include "classes/atom/CachedAllNumeric.hh"

namespace expression {

CachedAllNumeric::CachedAllNumeric(
    NumericExpression *nume, double clsEffort,
    const std::unordered_set<harm::ClsOp> &clsOps)
    : _nume(nume), _clsEffort(clsEffort), _clsOps(clsOps) {

  if (nume->getType().second == 32) {
    _cachedf = new float[nume->getMaxTime()];
    for (size_t i = 0; i < nume->getMaxTime(); i++) {
      _cachedf[i] = nume->evaluate(i);
    }
  } else {
    _cachedd = new double[nume->getMaxTime()];
    for (size_t i = 0; i < nume->getMaxTime(); i++) {
      _cachedd[i] = nume->evaluate(i);
    }
  }
  _loge = nullptr;
}
CachedAllNumeric::CachedAllNumeric(
    LogicExpression *loge, double clsEffort,
    const std::unordered_set<harm::ClsOp> &clsOps)
    : _loge(loge), _clsEffort(clsEffort), _clsOps(clsOps) {
  if (loge->getType().first == VarType::ULogic) {
    _cachedul = new ULogic[loge->getMaxTime()];
    for (size_t i = 0; i < loge->getMaxTime(); i++) {
      _cachedul[i] = loge->evaluate(i);
    }
  } else {
    _cachedsl = new SLogic[loge->getMaxTime()];
    for (size_t i = 0; i < loge->getMaxTime(); i++) {
      _cachedsl[i] = (SLogic)loge->evaluate(i);
    }
  }
  _nume = nullptr;
}
CachedAllNumeric::~CachedAllNumeric() {
  if (_nume != nullptr) {
    if (getType().second == 32) {
      delete[] _cachedf;
    } else {
      delete[] _cachedd;
    }
    delete _nume;
  } else {
    if (getType().first == VarType::ULogic) {
      delete[] _cachedul;
    } else {
      delete[] _cachedsl;
    }
    delete _loge;
  }
}

CachedAllNumeric::EvalRet CachedAllNumeric::evaluate(size_t time) {
  EvalRet r;
  if (_nume != nullptr) {
    if (getType().second == 32) {
      //r._f = _nume->evaluate(time);
      r._f = _cachedf[time];
    } else {
      //r._d = _nume->evaluate(time);
      r._d = _cachedd[time];
    }
  } else {
    if (getType().first == VarType::ULogic) {
      //r._u = _loge->evaluate(time);
      r._u = _cachedul[time];
    } else {
      //r._s = (SLogic)_loge->evaluate(time);
      r._s = _cachedsl[time];
    }
  }
  return r;
}

/// @brief Accepts a visitor to visit the current object.
/// @param vis The visitor.
void CachedAllNumeric::acceptVisitor(ExpVisitor &vis) {
  if (_nume != nullptr) {
    _nume->acceptVisitor(vis);
    return;
  } else {
    _loge->acceptVisitor(vis);
    return;
  }
}

/// @brief Returns the largest simulation time that can be provided to
/// the method evaluate.
size_t CachedAllNumeric::getMaxTime() {
  if (_nume != nullptr) {
    return _nume->getMaxTime();
  } else {
    return _loge->getMaxTime();
  }
}

void CachedAllNumeric::setType(VarType type, size_t size) {
  if (_nume != nullptr) {
    return _nume->setType(type, size);
  } else {
    return _loge->setType(type, size);
  }
}

std::pair<VarType, size_t> CachedAllNumeric::getType() {
  if (_nume != nullptr) {
    return _nume->getType();
  } else {
    return _loge->getType();
  }
}
CachedAllNumeric::GetRet CachedAllNumeric::get() {
  GetRet r;
  if (_nume != nullptr) {
    r._ne = _nume;
  } else {
    r._le = _loge;
  }
  return r;
}

} // namespace expression
