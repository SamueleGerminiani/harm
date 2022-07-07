#include "Trace.hh"
#include <iostream>

#include <cassert>
#include <sstream>

namespace harm {

using namespace expression;

Trace::Trace(std::vector<DataType> &variables, size_t length)
    : _numeriTrace(nullptr), _booleanTrace(nullptr), _logicTrace(nullptr),
      _length(length), _variables(variables) {

  for (DataType &dt : _variables) {
    _name2size[dt.getName()] = dt.getSize();
    _varName2Type[dt.getName()] = dt.getType();
  }

  _allocateTrace(variables);
  _allocatePointers(variables);
}

std::vector<Trace *> Trace::newTracesWithSAFault(const std::string &varName) {

  auto varsCopy = getVariables();
  size_t varSize = _name2size.at(varName);

  std::vector<Trace *> faultyTraces;
  // copy the trace 'varSize' times
  for (size_t i = 0; i < varSize; i++) {
    faultyTraces.push_back(new Trace(varsCopy, getLength()));
    faultyTraces.back()->setCuts(_cuts);
  }

  // retreive the vars
  for (size_t ft_i = 0; ft_i < varSize; ft_i++) {
    srand(ft_i + 1);

    auto ft = faultyTraces[ft_i];
    std::vector<BooleanVariable *> boolVars;
    std::vector<NumericVariable *> numVars;
    std::vector<LogicVariable *> logVars;

    for (auto &var : varsCopy) {
      if (var.getType() == VarType::Bool) {
        boolVars.push_back(ft->getBooleanVariable(var.getName()));
      } else if (var.getType() == VarType::Numeric) {
        numVars.push_back(ft->getNumericVariable(var.getName()));
      } else {
        logVars.push_back(ft->getLogicVariable(var.getName()));
      }
    }

    // copy values
    for (size_t time = 0; time < getLength(); time++) {
      for (auto bv : boolVars) {
        auto currTracebv = getBooleanVariable(bv->getName());
        bv->assign(time, currTracebv->evaluate(time));
        delete currTracebv;
      }
      for (auto nv : numVars) {
        auto currTracenv = getNumericVariable(nv->getName());
        nv->assign(time, currTracenv->evaluate(time));
        delete currTracenv;
      }
      for (auto lv : logVars) {
        auto currTracelv = getLogicVariable(lv->getName());
        lv->assign(time, currTracelv->evaluate(time));
        delete currTracelv;
      }
    }

    size_t nInsertFaults = 1;
    if (_varName2Type.at(varName) == expression::VarType::Bool) {
      // handle the faulty var
      for (size_t i = 0; i < nInsertFaults; i++) {
        size_t randPos = rand() % ((getLength() - 1) - 0 + 1) + 0;
        auto flv = getBooleanVariable(varName);
        auto original = flv->evaluate(randPos);

        flv->assign(randPos, !original);
        delete flv;
      }
    } else if (_varName2Type.at(varName) == expression::VarType::SLogic ||
               _varName2Type.at(varName) == expression::VarType::ULogic) {
      // handle the faulty var
      for (size_t i = 0; i < nInsertFaults; i++) {
        size_t randPos = rand() % ((getLength() - 1) - 0 + 1) + 0;
        auto flv = getLogicVariable(varName);
        auto original = flv->evaluate(randPos);

        // sa 0
        auto withsa = (original & (~((uint64_t)(1ULL << ft_i)) << 1) >> 1);
        if (original != withsa) {
          flv->assign(randPos, withsa);
          delete flv;
          continue;
        }

        // sa 1
        withsa = (original | 1ULL << ft_i);
        flv->assign(randPos, withsa);
        delete flv;
      }
    } else {
      messageError("Unsupported var type for fault insertion");
    }

    for (auto v : boolVars) {
      delete v;
    }
    for (auto v : logVars) {
      delete v;
    }
    for (auto v : numVars) {
      delete v;
    }
  }

  return faultyTraces;
} // namespace harm
Trace::~Trace() {
  delete[] _numeriTrace;
  delete[] _booleanTrace;
  delete[] _logicTrace;
}
std::string Trace::printTrace(size_t start, size_t n) {

  std::stringstream ss;
  for (auto &[vn, t] : _varName2Type) {
    ss << vn << ": ";
    if (t == VarType::Bool) {
      auto v = getBooleanVariable(vn);
      for (size_t i = start; i < start + n && i < _length; i++) {
        ss << v->evaluate(i) << " ";
      }
      ss << "\n";
      delete v;
    } else if (t == VarType::Numeric) {
      auto v = getNumericVariable(vn);
      for (size_t i = start; i < start + n && i < _length; i++) {
        ss << v->evaluate(i) << " ";
      }
      ss << "\n";
      delete v;
    } else if (t == VarType::ULogic) {
      auto v = getLogicVariable(vn);
      for (size_t i = start; i < start + n && i < _length; i++) {
        ss << (uint64_t)v->evaluate(i) << " ";
      }
      ss << "\n";
      delete v;
    } else if (t == VarType::SLogic) {
      auto v = getLogicVariable(vn);
      for (size_t i = start; i < start + n && i < _length; i++) {
        ss << (int64_t)v->evaluate(i) << " ";
      }
      ss << "\n";
      delete v;
    }
  }
  return ss.str();
}

size_t Trace::getLength() const { return _length; }

void Trace::_allocateTrace(std::vector<DataType> &variables) {
  size_t numVarCounter = 0;
  size_t bolVarCounter = 0;
  size_t logVarCounter = 0;

  for (DataType var : variables) {
    switch (var.getType()) {
    case VarType::Numeric: {
      ++numVarCounter;
      break;
    }
    case VarType::Bool: {
      ++bolVarCounter;
      break;
    }
    default: {
      // number of values in a Logic
      size_t _valuesInside = _val4Logic / var.getSize();
      // number of 64 bits integers to represent all
      // the values of this variable
      size_t tmpSize = (_length + _valuesInside - 1) / _valuesInside;
      logVarCounter += tmpSize;
      break;
    }
    }
  }

  _numeriTrace = new double[_length * numVarCounter]{};
  _booleanTrace = new unsigned[((_length + 31) >> 5) * bolVarCounter]{};
  _logicTrace = new uint64_t[logVarCounter]{};
}

void Trace::_allocatePointers(std::vector<DataType> &variables) {
  size_t numVarCounter = 0;
  size_t bolVarCounter = 0;
  size_t logVarAccu = 0;

  for (DataType var : variables) {
    switch (var.getType()) {
    case VarType::Numeric: {
      _varName2varValues[var.getName()] =
          reinterpret_cast<uintptr_t>(&_numeriTrace[_length * numVarCounter]);
      ++numVarCounter;
      break;
    }
    case VarType::Bool: {
      _varName2varValues[var.getName()] = reinterpret_cast<uintptr_t>(
          &_booleanTrace[((_length + 31) >> 5) * bolVarCounter]);
      ++bolVarCounter;
      break;
    }
    default: {
      _varName2varValues[var.getName()] =
          reinterpret_cast<uintptr_t>(&_logicTrace[logVarAccu]);

      // number of values in a Logic
      size_t _valuesInside = _val4Logic / var.getSize();
      // number of 64 bits integers to represent all
      // the values of this variable
      size_t tmpSize = (_length + _valuesInside - 1) / _valuesInside;
      logVarAccu += tmpSize;

      break;
    }
    }
  }
}

expression::BooleanVariable *
Trace::getBooleanVariable(const std::string &name) const {
  messageErrorIf(_varName2varValues.count(name) == 0 ||
                     (_varName2Type.at(name) != expression::VarType::Bool),
                 "Can't find boolean variable with name: " + name);

  size_t size = _name2size.at(name);
  return new expression::BooleanVariable(
      reinterpret_cast<unsigned int *>(_varName2varValues.at(name)), name,
      _length);
}

expression::LogicVariable *
Trace::getLogicVariable(const std::string &name) const {
  messageErrorIf(_varName2varValues.count(name) == 0 ||
                     (_varName2Type.at(name) != expression::VarType::ULogic &&
                      _varName2Type.at(name) != expression::VarType::SLogic),
                 "Can't find logic variable with name: " + name);

  size_t size = _name2size.at(name);
  return new expression::LogicVariable(
      reinterpret_cast<uint64_t *>(_varName2varValues.at(name)), name,
      _varName2Type.at(name), size, _length);
}

expression::NumericVariable *
Trace::getNumericVariable(const std::string &name) const {
  messageErrorIf(_varName2varValues.count(name) == 0 ||
                     (_varName2Type.at(name) != expression::VarType::Numeric),
                 "Can't find numeric variable with name: " + name);

  size_t size = _name2size.at(name);
  return new expression::NumericVariable(
      reinterpret_cast<expression::Numeric *>(_varName2varValues.at(name)),
      name, _varName2Type.at(name), size, _length);
}

std::vector<size_t> &Trace::getCuts() { return _cuts; }
void Trace::setCuts(const std::vector<size_t> &cuts) { _cuts = cuts; }
} // namespace harm
