#include <algorithm>
#include <fstream>

#include "Trace.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Variable.hh"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"

namespace harm {

using namespace expression;

Trace::Trace(std::vector<VarDeclaration> &variables, size_t length)
    : _length(length), _variables(variables) {

  for (VarDeclaration &dt : _variables) {
    _varName2size[dt.getName()] = dt.getSize();
    _varName2Type[dt.getName()] = dt.getType();
  }

  allocateTrace(variables);
  allocatePointers(variables);
}

Trace::~Trace() {

  //delete sub-trace only if allocated

  if (_floatTrace != nullptr) {
    delete[] _floatTrace;
  }
  if (_booleanTrace != nullptr) {
    delete[] _booleanTrace;
  }
  if (_intTrace != nullptr) {
    delete[] _intTrace;
  }
}

std::string Trace::printTrace(size_t start, size_t n) {

  std::stringstream ss;
  size_t maxNumberOfLeadingCharsVarname = 0;
  for (auto &[vn, t] : _varName2Type) {
    maxNumberOfLeadingCharsVarname =
        std::max(maxNumberOfLeadingCharsVarname, vn.size());
  }

  for (auto &[vn, t] : _varName2Type) {
    ss << std::string(maxNumberOfLeadingCharsVarname - vn.size(), ' ')
       << vn << ": ";
    if (t == ExpType::Bool) {
      auto v = getBooleanVariable(vn);
      for (size_t i = start; i < start + n && i < _length; i++) {
        ss << v->evaluate(i) << " ";
      }
      ss << "\n";
    } else if (t == ExpType::Float) {
      auto v = getFloatVariable(vn);
      for (size_t i = start; i < start + n && i < _length; i++) {
        ss << v->evaluate(i) << " ";
      }
      ss << "\n";
    } else if (t == ExpType::UInt) {
      auto v = getIntVariable(vn);
      for (size_t i = start; i < start + n && i < _length; i++) {
        ss << (UInt)v->evaluate(i) << " ";
      }
      ss << "\n";
    } else if (t == ExpType::SInt) {
      auto v = getIntVariable(vn);
      for (size_t i = start; i < start + n && i < _length; i++) {
        ss << (SInt)v->evaluate(i) << " ";
      }
      ss << "\n";
    }
  }
  return ss.str();
}

size_t Trace::getLength() const { return _length; }

void Trace::allocateTrace(std::vector<VarDeclaration> &variables) {
  size_t floatVarCounter = 0;
  size_t bolVarCounter = 0;
  size_t intVarCounter = 0;

  for (VarDeclaration var : variables) {
    if (var.getType() == ExpType::Float) {
      ++floatVarCounter;
    } else if (var.getType() == ExpType::Bool) {
      ++bolVarCounter;
    } else if (isInt(var.getType())) {
      // number of values in a Int
      size_t valuesInside = _val4Int / var.getSize();
      // number of N bits integers to represent all
      // the values of this variable
      size_t tmpSize = (_length + valuesInside - 1) / valuesInside;
      intVarCounter += tmpSize;
    } else {
      messageError("Unknown var type");
    }
  }

  if (floatVarCounter > 0) {
    _floatTrace = new double[_length * floatVarCounter]{0};
  }
  if (bolVarCounter > 0) {
    _booleanTrace =
        new unsigned[((_length + 31) >> 5) * bolVarCounter]{false};
  }
  if (intVarCounter > 0) {
    _intTrace = new UInt[intVarCounter]{0};
  }
}

void Trace::allocatePointers(std::vector<VarDeclaration> &variables) {
  size_t floatVarCounter = 0;
  size_t bolVarCounter = 0;
  size_t intVarAccur = 0;

  for (VarDeclaration var : variables) {
    ExpType type = var.getType();
    if (type == ExpType::Float) {
      _varName2varValues[var.getName()] = reinterpret_cast<uintptr_t>(
          &_floatTrace[_length * floatVarCounter]);
      ++floatVarCounter;
    } else if (type == ExpType::Bool) {
      _varName2varValues[var.getName()] = reinterpret_cast<uintptr_t>(
          &_booleanTrace[((_length + 31) >> 5) * bolVarCounter]);
      ++bolVarCounter;
    } else if (isInt(var.getType())) {
      _varName2varValues[var.getName()] =
          reinterpret_cast<uintptr_t>(&_intTrace[intVarAccur]);
      // number of values in an Int
      size_t _valuesInside = _val4Int / var.getSize();
      // number of n-bit integers to represent all
      // the values of this variable
      size_t tmpSize = (_length + _valuesInside - 1) / _valuesInside;
      intVarAccur += tmpSize;
    } else {
      messageError("Unknown var type");
    }
  }
}

unsigned int *
Trace::getBooleanVariableValues(const std::string &name) const {
  messageErrorIf(
      _varName2varValues.count(name) == 0 ||
          (_varName2Type.at(name) != expression::ExpType::Bool),
      "Can't find boolean variable with name: " + name);
  return reinterpret_cast<unsigned int *>(
      _varName2varValues.at(name));
}

UInt *Trace::getIntVariableValues(const std::string &name) const {
  messageErrorIf(
      _varName2varValues.count(name) == 0 ||
          (_varName2Type.at(name) != expression::ExpType::UInt &&
           _varName2Type.at(name) != expression::ExpType::SInt),
      "Can't find int variable with name: " + name);

  return reinterpret_cast<UInt *>(_varName2varValues.at(name));
}

Float *Trace::getFloatVariableValues(const std::string &name) const {
  messageErrorIf(
      _varName2varValues.count(name) == 0 ||
          (_varName2Type.at(name) != expression::ExpType::Float),
      "Can't find float variable with name: " + name);

  return reinterpret_cast<Float *>(_varName2varValues.at(name));
}

expression::BooleanVariablePtr
Trace::getBooleanVariable(const std::string &name) const {
  messageErrorIf(
      _varName2varValues.count(name) == 0 ||
          (_varName2Type.at(name) != expression::ExpType::Bool),
      "Can't find boolean variable with name: " + name);

  return generatePtr<expression::BooleanVariable>(
      reinterpret_cast<unsigned int *>(_varName2varValues.at(name)),
      name, _length);
}

expression::IntVariablePtr
Trace::getIntVariable(const std::string &name) const {
  messageErrorIf(
      _varName2varValues.count(name) == 0 ||
          (_varName2Type.at(name) != expression::ExpType::UInt &&
           _varName2Type.at(name) != expression::ExpType::SInt),
      "Can't find int variable with name: " + name);

  size_t size = _varName2size.at(name);
  return generatePtr<expression::IntVariable>(
      reinterpret_cast<UInt *>(_varName2varValues.at(name)), name,
      _varName2Type.at(name), size, _length);
}

expression::FloatVariablePtr
Trace::getFloatVariable(const std::string &name) const {
  messageErrorIf(
      _varName2varValues.count(name) == 0 ||
          (_varName2Type.at(name) != expression::ExpType::Float),
      "Can't find float variable with name: " + name);

  size_t size = _varName2size.at(name);
  return generatePtr<expression::FloatVariable>(
      reinterpret_cast<Float *>(_varName2varValues.at(name)), name,
      _varName2Type.at(name), size, _length);
}

std::vector<size_t> &Trace::getCuts() { return _cuts; }
void Trace::setCuts(const std::vector<size_t> &cuts) { _cuts = cuts; }

std::vector<VarDeclaration> Trace::getDeclarations() {
  std::vector<VarDeclaration> ret;

  for (auto v : _variables) {
    ret.emplace_back(v.getName(), _varName2Type.at(v.getName()),
                     _varName2size.at(v.getName()));
  }
  return ret;
}

std::unordered_map<std::string,
                   std::pair<expression::ExpType, size_t>>
Trace::getDeclarationsAsMap() {
  std::unordered_map<std::string,
                     std::pair<expression::ExpType, size_t>>
      ret;

  for (const auto &v : _variables) {
    ret[v.getName()] = std::make_pair(_varName2Type.at(v.getName()),
                                      _varName2size.at(v.getName()));
  }
  return ret;
}

size_t Trace::getVarSize(std::string varName) {
  messageErrorIf(_varName2size.count(varName) == 0,
                 "Did not find variable '" + varName + "'");
  return _varName2size.at(varName);
}
expression::ExpType Trace::getExpType(const std::string &name) {
  return _varName2Type.at(name);
}

void dumpTraceAsCSV(const TracePtr &trace,
                    const std::string &filename) {

  auto vars = trace->getDeclarations();
  std::ofstream file(filename);
  std::stringstream ss;
  //sort the variables by name, to improve readability
  std::sort(vars.begin(), vars.end(),
            [](const VarDeclaration &a, const VarDeclaration &b) {
              return a.getName() < b.getName();
            }
  );

  for (auto &v : vars) {
    //skip the clock
    if (v.getName() == clc::clk) {
      continue;
    }
    ss << varTypeToString(v.getType(), v.getSize()) << " "
       << v.getName() << ",";
  }
  std::string header = ss.str();
  ss.str(std::string());
  header.pop_back();
  file << header;
  file << "\n";

  for (size_t i = 0; i < trace->getLength(); i++) {
    for (auto &v : vars) {
      //skip the clock
      if (v.getName() == clc::clk) {
        continue;
      }
      auto vn = v.getName();
      auto t = v.getType();

      if (t == ExpType::Bool) {
        auto v = trace->getBooleanVariable(vn);
        ss << v->evaluate(i) << ", ";
      } else if (t == ExpType::Float) {
        auto v = trace->getFloatVariable(vn);
        ss << v->evaluate(i) << ", ";
      } else if (t == ExpType::UInt) {
        auto v = trace->getIntVariable(vn);
        ss << (UInt)v->evaluate(i) << ", ";
      } else if (t == ExpType::SInt) {
        auto v = trace->getIntVariable(vn);
        ss << (SInt)v->evaluate(i) << ", ";
      } else {
        messageError("Unsupported type");
      }
    } //end for vars

    std::string row = ss.str();
    ss.str(std::string());
    //remove last comma
    row = row.substr(0, row.size() - 2);
    file << row;
    file << "\n";
  } //end for i

  file << ss.str();
  file.close();
}

std::vector<VarDeclaration> Trace::getVariables() {
  return _variables;
}
} // namespace harm
