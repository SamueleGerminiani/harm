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

public:
  Assertion() = default;

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

  ///mining id: (t<id>,p<id>) (template id, proposition id)
  std::string _mining_id;
};
//smart pointer
using AssertionPtr = std::shared_ptr<Assertion>;

/** \brief fill the assertion with all the necessary information
   */
void fillAssertion(const AssertionPtr &ass, const TemplateImplicationPtr &t,
                   bool isOffset, const std::string &mining_id);

/** \brief make mining id
   */
std::string makeMiningId(size_t template_id, size_t perm_id);

/** \brief just a heuristic to find equivalence between assertions (not a real semantical comparison)
   */
bool operator==(const Assertion &a1, const Assertion &a2);
} // namespace harm
