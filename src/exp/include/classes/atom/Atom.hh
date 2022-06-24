#pragma once

#include <cstddef>
#include <cstdint>
#include <cassert>
#include <type_traits>
#include <iostream>

#include "message.hh"
#include "expUtils/VarType.hh"

namespace expression {

// Forwards declaration of base class Visitor
class ExpVisitor;

/// @brief An Atom can represent either a Variable or a Constant.
/// It only provides the base methods evaluate and visit.
template <typename T> class Atom {
public:
  /// @brief Destructor.
  virtual ~Atom() = default;

  /// @brief Returns the value of the atom in the given simulation time
  /// @param time The simulation time
  /// @return The value of the atom
  virtual T evaluate(size_t time) = 0;

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  virtual void acceptVisitor(ExpVisitor &vis) = 0;

  /// @brief Returns the largest simulation time that can be provided to
  /// the method evaluate.
  virtual size_t getMaxTime();

  void setType(VarType type, uint8_t size);

  std::pair<VarType, uint8_t> getType();

protected:
  /// @brief Constructor of an Atom
  /// @param max_time the largest simulation time that can be provided to
  /// the method evaluate.
  Atom(VarType type = VarType::Bool, uint8_t size = 1, size_t max_time = 0);

  VarType _type;
  uint8_t _size;
  size_t _max_time;
};

using Numeric = double;
using Logic = uint64_t;

using NumericExpression = Atom<Numeric>;
using LogicExpression = Atom<Logic>;
using Proposition = Atom<bool>;

class CachedProposition : public Proposition {
public:
  CachedProposition(Proposition *prop) : _prop(prop) {
    _cached = new bool[prop->getMaxTime()];
    for (size_t i = 0; i < prop->getMaxTime(); i++) {
      _cached[i] = prop->evaluate(i);
    }
  }
  ~CachedProposition() {
    delete _prop;
    delete[] _cached;
  }
  virtual bool evaluate(size_t time) { return _cached[time]; }

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  virtual void acceptVisitor(ExpVisitor &vis) { _prop->acceptVisitor(vis); }

  /// @brief Returns the largest simulation time that can be provided to
  /// the method evaluate.
  virtual size_t getMaxTime() { return _prop->getMaxTime(); }
  virtual Proposition* getItem() { return _prop; }

  void setType(VarType type, uint8_t size) { _prop->setType(type, size); }

  std::pair<VarType, uint8_t> getType() { return _prop->getType(); }
  Proposition *get() { return _prop; }

private:
  Proposition *_prop=nullptr;
  bool *_cached=nullptr;
};

class CachedAllNumeric {
  union EvalRet {
    double _d;
    float _f;
    uint64_t _u;
    int64_t _s;
  };
  union GetRet {
    NumericExpression *_ne;
    LogicExpression *_le;
  };

public:
  CachedAllNumeric(NumericExpression *nume,double clsEffort=1.0f) : _nume(nume), _clsEffort(clsEffort) {
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
  CachedAllNumeric(LogicExpression *loge,double clsEffort=1.0f) : _loge(loge), _clsEffort(clsEffort) {
    if (loge->getType().first == VarType::ULogic) {
      _cachedul = new uint64_t[loge->getMaxTime()];
      for (size_t i = 0; i < loge->getMaxTime(); i++) {
        _cachedul[i] = loge->evaluate(i);
      }
    } else {
      _cachedsl = new int64_t[loge->getMaxTime()];
      for (size_t i = 0; i < loge->getMaxTime(); i++) {
        _cachedsl[i] = loge->evaluate(i);
      }
    }
    _nume = nullptr;
  }
  ~CachedAllNumeric() {
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

  EvalRet evaluate(size_t time) {
    EvalRet r;
    if (_nume != nullptr) {
      if (getType().second == 32) {
        r._f = _nume->evaluate(time);
      } else {
        r._d = _nume->evaluate(time);
      }
    } else {
      if (getType().first == VarType::ULogic) {
        r._u = _loge->evaluate(time);
      } else {
        r._s = _loge->evaluate(time);
      }
    }
    return r;
  }

  /// @brief Accepts a visitor to visit the current object.
  /// @param vis The visitor.
  virtual void acceptVisitor(ExpVisitor &vis) {
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
  virtual size_t getMaxTime() {
    if (_nume != nullptr) {
      return _nume->getMaxTime();
    } else {
      return _loge->getMaxTime();
    }
  }

  void setType(VarType type, uint8_t size) {
    if (_nume != nullptr) {
      return _nume->setType(type, size);
    } else {
      return _loge->setType(type, size);
    }
  }

  std::pair<VarType, uint8_t> getType() {
    if (_nume != nullptr) {
      return _nume->getType();
    } else {
      return _loge->getType();
    }
  }
  GetRet get() {
    GetRet r;
    if (_nume != nullptr) {
      r._ne = _nume;
    } else {
      r._le = _loge;
    }
    return r;
  }

private:
  NumericExpression *_nume = nullptr;
  LogicExpression *_loge = nullptr;
  double *_cachedd;
  float *_cachedf;
  uint64_t *_cachedul;
  int64_t *_cachedsl;
public:
  double _clsEffort=0.3f;
};

} // namespace expression

#include "Atom.i.hh"
