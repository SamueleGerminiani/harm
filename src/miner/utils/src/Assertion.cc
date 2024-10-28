#include <algorithm>

#include "Assertion.hh"
#include "DTOperator.hh"
#include "TemplateImplication.hh"
#include "Trinary.hh"

#include "expUtils/expUtils.hh"
#include "globals.hh"

namespace harm {
size_t Assertion::idCounter = 0;

Assertion::Assertion() : _id(idCounter++) {}

Assertion::~Assertion() {}

bool operator==(const Assertion &a1, const Assertion &a2) {
  if (a1.toString() == a2.toString()) {
    return 1;
  }
  if (a1._ct[0][0] != a2._ct[0][0] || a1._ct[0][1] != a2._ct[0][1] ||
      a1._ct[0][2] != a2._ct[0][2] || a1._ct[1][0] != a2._ct[1][0] ||
      a1._ct[1][1] != a2._ct[1][1] || a1._ct[1][2] != a2._ct[1][2] ||
      a1._ct[2][0] != a2._ct[2][0] || a1._ct[2][1] != a2._ct[2][1] ||
      a1._ct[2][2] != a2._ct[2][2]) {
    return 0;
  }

  if (a1._complexity != a2._complexity ||
      a1._pRepetitions != a2._pRepetitions) {
    return 0;
  }

  std::string a1_s = a1.toString();
  std::string a2_s = a2.toString();
  a1_s.erase(remove_if(a1_s.begin(), a1_s.end(),
                       [](const char &c) {
                         return c == '\t' || c == '\n' || c == ' ' ||
                                c == '(' || c == ')' || c == '{' ||
                                c == '}' || c == '[' || c == ']';
                       }),
             a1_s.end());
  a2_s.erase(remove_if(a2_s.begin(), a2_s.end(),
                       [](const char &c) {
                         return c == '\t' || c == '\n' || c == ' ' ||
                                c == '(' || c == ')' || c == '{' ||
                                c == '}' || c == '[' || c == ']';
                       }),
             a2_s.end());

  return a1_s == a2_s;
}

void fillAssertion(const AssertionPtr &ass,
                   const TemplateImplicationPtr &t, bool isOffset) {

  //fill assertion features
  t->fillContingency(ass->_ct, isOffset);
  if (t->containsDT()) {
    ass->_formula = t->getDT()->getReducedFormula(isOffset);
  } else {
    ass->_formula = copy(t->getTemplateFormula(), true);
  }
  auto loadedProps = t->getLoadedPropositions();
  ass->_complexity = getNumVariables(loadedProps);
  ass->_pRepetitions = getRepetitions(loadedProps);
  ass->_CT = t->getCT();
  ass->_maxLength = t->getTraceLength();
}
std::string Assertion::toString(Language lang) const {
  lang = (lang == Language::Unset) ? clc::outputLang : lang;
  return temp2String(_formula, lang, PrintMode::ShowAll);
}

std::string Assertion::toColoredString(Language lang) const {
  lang = (lang == Language::Unset) ? clc::outputLang : lang;
  return temp2ColoredString(_formula, lang, PrintMode::ShowAll);
}

} // namespace harm
