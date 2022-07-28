#pragma once

#include "Trinary.hh"
#include "globals.hh"

namespace harm {
class Template;

/*! \class Assertion
    \brief Class representing an assertion (it is just a snapshot of an instantiated template)
*/
class Assertion {

public:
  Assertion() = default;

  ~Assertion();

  Trinary evaluate(size_t time) const;
  /** \brief Fill the assertion with the cached values of the input template t
   */
  void fillValues(Template *t);
  /** \brief Fill the assertion with the cached values (offset) of the input template t
   */
  void fillValuesOffset(Template *t);

  bool holdsOnTrace();

  ///string representation of the assertion <automatic, colored>
  std::pair<std::string, std::string> _toString;

  ///truth values on the trace
  Trinary *_values = nullptr;

  //assertion's features
  ///contingency table
  size_t _ct[3][3] = {{0}};
  ///number of variables in the assertion
  size_t _complexity = 0;
  ///number of repetitions of propositions
  size_t _pRepetitions = 0;
  ///adjusted total score
  double _finalScore = .0f;
  ///length of the trace
  size_t _max_length = 0;
};

/** \brief just a heuristic to find equivalence between assertions
   */
bool operator==(const Assertion &a1, const Assertion &a2);
} // namespace harm
