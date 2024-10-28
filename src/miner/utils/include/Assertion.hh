#pragma once

#include "Language.hh"
#include "formula/temporal/TemporalExpression.hh"
#include <stddef.h>
#include <string>
#include <utility>

enum class Trinary;

namespace harm {
class TemplateImplication;
using TemplateImplicationPtr = std::shared_ptr<TemplateImplication>;

/*! \class Assertion
    \brief Class representing an assertion (it is just a snapshot of an instantiated template)
*/
class Assertion {
  static size_t idCounter;

public:
  Assertion();

  ~Assertion();

  std::string toString(Language lang = Language::Unset) const;
  std::string toColoredString(Language lang = Language::Unset) const;

  expression::TemporalExpressionPtr _formula = nullptr;

  //assertion's features
  ///contingency table
  size_t _ct[3][3] = {{0}};
  ///consequent coverage
  size_t _CT = 0;
  ///number of variables in the assertion
  size_t _complexity = 0;
  ///number of repetitions of propositions
  size_t _pRepetitions = 0;
  ///adjusted total score
  double _finalScore = 0.f;
  ///length of the trace
  size_t _maxLength = 0;
  //when using the faultCoverage metric
  size_t _nfCovered = 0;
  ///id of the assertion
  size_t _id = (size_t)-1;
};
//smart pointer
using AssertionPtr = std::shared_ptr<Assertion>;

/** \brief fill the assertion with all the necessary information
   */
void fillAssertion(const AssertionPtr &ass,
                   const TemplateImplicationPtr &t, bool isOffset);

/** \brief just a heuristic to find equivalence between assertions (not a real semantical comparison)
   */
bool operator==(const Assertion &a1, const Assertion &a2);
} // namespace harm
