#pragma once

#include "Hstring.hh"
#include "Location.hh"
#include "minerUtils.hh"

// spot
#include "spot/tl/parse.hh"
#include "spot/twaalgos/hoa.hh"
#include "spot/twaalgos/translate.hh"

#include <cstdarg>
#include <deque>
#include <numeric>
#include <regex>
#include <spot/tl/print.hh>
#include <spot/twa/bddprint.hh>
#include <string>
#include <unordered_map>

namespace harm {

using Matrix = std::vector<std::vector<size_t>>;
using Row = std::vector<size_t>;
/*! \class PermGenerator
    \brief Class to generate permutations of proposition for the placeholders
*/
class PermGenerator {

public:
  PermGenerator() = default;

  ~PermGenerator();

  void genPermutations(size_t antP, size_t conP, size_t antConP,
                       Hstring &templateFormula);

private:
  enum class PermOperator { Mul, Bin, Com, Ph };
  struct PermUnit {
    PermOperator _op;
    std::pair<size_t, size_t> _dim;
    std::vector<PermUnit *> _children;
  };

  bool compare(spot::formula f1, spot::formula f2);
  Matrix visitPermUnit(PermGenerator::PermUnit *pu);
  PermGenerator::PermUnit *
  generatePermUnit(spot::formula &templ,
                   std::unordered_set<std::string> &foundPH);
  PermGenerator::PermUnit *generatePermUnit(spot::formula &templ);
  void printPermUnit(PermGenerator::PermUnit *pu);
  void deletePermUnit(PermGenerator::PermUnit *pu);

  size_t _cProps;
  size_t _acProps;
  size_t _aProps;
  std::unordered_map<std::string, size_t> _mPhs;
  std::unordered_map<std::string, size_t> _rphToIndex;

public:
  int **_perms = nullptr;
  std::pair<size_t, size_t> _size;
  std::unordered_map<std::string, size_t> _phToIndex;
  std::unordered_map<std::string, harm::Location> _phToLoc;
};
} // namespace harm
