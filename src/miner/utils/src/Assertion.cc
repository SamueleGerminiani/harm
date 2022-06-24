#include "Assertion.hh"
#include "Template.hh"

namespace harm {

Assertion::Assertion() {}
Assertion::~Assertion() {
  if (_values != nullptr) {
    delete[] _values;
  }
}
Trinary Assertion::evaluate(size_t time) const {
  if (clc::dontFillAss) {
    return Trinary::T;
  }
  return _values[time];
}
void Assertion::fillValues(Template *t) {
  if (clc::dontFillAss) {
    return;
  }
  if (_values == nullptr) {
    _values = new Trinary[t->_max_length];
  }
  for (size_t i = 0; i < t->_max_length; i++) {
    _values[i] = t->evaluate(i);
  }
  _max_length = t->_max_length;
}
void Assertion::fillValuesOffset(Template *t) {
  if (clc::dontFillAss) {
    return;
  }
  if (_values == nullptr) {
    _values = new Trinary[t->_max_length];
  }
  for (size_t i = 0; i < t->_max_length; i++) {
    _values[i] = t->evaluateOffset(i);
  }
  _max_length = t->_max_length;
}
bool Assertion::holdsOnTrace() {
  if (clc::dontFillAss) {
    return 1;
  }
  for (size_t i = 0; i < _max_length; i++) {
    if (evaluate(i) == Trinary::F) {
      return 0;
    }
  }
  return 1;
}

bool operator==(const Assertion &a1, const Assertion &a2) {
  if (a1._toString.second == a2._toString.second) {
    return 1;
  }
  if (a1._ct[0][0] != a2._ct[0][0] || a1._ct[0][1] != a2._ct[0][1] ||
      a1._ct[0][2] != a2._ct[0][2] || a1._ct[1][0] != a2._ct[1][0] ||
      a1._ct[1][1] != a2._ct[1][1] || a1._ct[1][2] != a2._ct[1][2] ||
      a1._ct[2][0] != a2._ct[2][0] || a1._ct[2][1] != a2._ct[2][1] ||
      a1._ct[2][2] != a2._ct[2][2]) {
    return 0;
  }

  if (a1._complexity!=a2._complexity || a1._pRepetitions!=a2._pRepetitions) {
    return 0;
  }

  for (size_t i = 0; i < a1._max_length; i++) {
    if (a1.evaluate(i) != a2.evaluate(i)) {
      return 0;
    }
  }

  std::string a1_s = a1._toString.first;
  std::string a2_s = a2._toString.first;
  a1_s.erase(remove_if(a1_s.begin(), a1_s.end(),
                       [](const char &c) {
                         return c == '\t' || c == '\n' || c == ' ' ||
                                c == '(' || c == ')' || c == '{' || c == '}' ||
                                c == '[' || c == ']';
                       }),
             a1_s.end());
  a2_s.erase(remove_if(a2_s.begin(), a2_s.end(),
                       [](const char &c) {
                         return c == '\t' || c == '\n' || c == ' ' ||
                                c == '(' || c == ')' || c == '{' || c == '}' ||
                                c == '[' || c == ']';
                       }),
             a2_s.end());
  

  return a1_s == a2_s;
}
} // namespace harm
