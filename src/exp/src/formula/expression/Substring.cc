#include <stddef.h>
#include <string>

#include "String.hh"
#include "colors.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "formula/expression/Substring.hh"
#include "visitors/ExpVisitor.hh"

namespace expression {

void Substring::acceptVisitor(ExpVisitor &vis) { vis.visit(*this); }

void Substring::initEvaluate() {
  directEvaluate = [this](int time) {
    String e = _e->evaluate(time);
    if (_nChars == (size_t)-1) {
      return e.substr(_start);
    } else {
      return e.substr(_start, _nChars);
    }
  };
  disableCache();
}

Substring::Substring(StringExpressionPtr e, size_t start,
                     size_t nChars)
    : StringExpression(ExpType::String, 0, e->getMaxTime()), _e(e),
      _start(start), _nChars(nChars) {
  initEvaluate();
}

Substring::~Substring() {}

StringExpressionPtr &Substring::getItem() { return _e; }

size_t Substring::getStartIndex() { return _start; }

size_t Substring::getNChars() { return _nChars; }

String Substring::toString() {
  return ".subtr(" + str2String(_e) + ", " + std::to_string(_start) +
         ", " + std::to_string(_nChars) + ")";
}

String Substring::toColoredString() {
  return FUN(".subtr(") + str2ColoredString(_e) + FUN(", ") +
         VAR(std::to_string(_start)) + VAR(std::to_string(_nChars)) +
         FUN(")");
}

} // namespace expression
