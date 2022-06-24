#pragma once

#include "globals.hh"
#include "Trinary.hh"

namespace harm {
class Template;

class Assertion {

public:
  Assertion();
  ~Assertion();
  Trinary evaluate(size_t time) const;
  void fillValues(Template *t);
  void fillValuesOffset(Template *t);
  bool holdsOnTrace();

  std::pair<std::string, std::string> _toString;
  size_t _ct[3][3] = {{0}};
  size_t _complexity = 0;
  size_t _pRepetitions = 0;
  double _finalScore = .0f;
  size_t _max_length = 0;
  Trinary *_values = nullptr;
};

bool operator==(const Assertion &a1, const Assertion &a2);
} // namespace harm
