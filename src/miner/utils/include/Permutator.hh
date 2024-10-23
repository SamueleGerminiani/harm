#pragma once

#include <algorithm>
#include <cstdarg>
#include <deque>
#include <map>
#include <numeric>
#include <regex>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Location.hh"
#include "formula/atom/Atom.hh"
#include "minerUtils.hh"

class Hstring;
namespace expression {
template <typename OT, typename ET> class Function;
class TemporalExpression;
} // namespace expression

namespace harm {
enum class Location;

//Table of permutations
using Matrix = std::vector<std::vector<size_t>>;
//One permutation as a row of the table
using Row = std::vector<size_t>;

/*! \class Permutator
    \brief Class to generate permutations of proposition for the placeholders
*/
class Permutator {

public:
  Permutator() = default;

  ~Permutator() = default;

  void genPermutations(
      const std::unordered_map<
          std::string, std::vector<expression::PropositionPtr>>
          &_phToDomain,
      const expression::TemporalExpressionPtr &templateFormula);

  std::string printPermutations();

private:
  /* \brief Mul does the product of permutations, Bin does the binomial coefficent of permutations,Com for non reflexive permutations such for Release and Until
   */
  enum class PermOperator { Mul, Bin, NonR, Ph };

  ///\brief PermUnit is a node of the tree of permutations
  ///\param _op is the operator of the node
  struct PermUnit {
    ///\brief Dim is the dimension of the node in terms of rows and columns of the sub-matrix of permutations
    struct Dim {
      size_t _row;
      size_t _col;
    };
    ///Type of the node
    PermOperator _op;
    Dim _dim;
    ///the list of children of the node
    std::vector<PermUnit *> _children;
  };

  ///\brief generatePermUnit generates the tree of permutations for the formula
  Permutator::PermUnit *
  generatePermUnit(const expression::TemporalExpressionPtr &templ,
                   std::unordered_set<std::string> &foundPH);
  ///\brief wrapper for generatePermUnit
  Permutator::PermUnit *
  generatePermUnit(const expression::TemporalExpressionPtr &templ);
  ///\brief visitPermUnit generates the matrix of permutations from the tree of permutations
  Matrix visitPermUnit(Permutator::PermUnit *pu);
  ///\brief cluister equivalent formulas using areEquivalent
  std::vector<std::pair<
      size_t, std::vector<expression::TemporalExpressionPtr>>>
  clusterFormulas(const expression::TemporalExpressionPtr &templ);
  ///\brief checks if the two formulas would produce the same permutations
  bool areEquivalent(const expression::TemporalExpressionPtr &f1,
                     const expression::TemporalExpressionPtr &f2);

  ///\brief prints the tree of permutations to the console
  void printPermUnit(Permutator::PermUnit *pu);
  ///\brief deletes the tree of permutations
  void deletePermUnit(Permutator::PermUnit *pu);

  ///ph token to the number of times it appears in the formula
  std::unordered_map<std::string, size_t> _phToFrequency;
  ///\brief _phToDomainStr is a map from the placeholder to the domain of the placeholder
  std::unordered_map<std::string, std::vector<std::string>>
      _phToDomainStr;

  ///keep track of the original and repeated index of repeated placeholders
  std::unordered_map<std::string, std::pair<size_t, size_t>>
      _repeatedPhTo_originalAndRepeatedIndex;

  //@class Permutation matrix
public:
  class PermMatrix {
  public:
    PermMatrix() = default;
    PermMatrix(size_t nRows, size_t nCols);
    ~PermMatrix();
    void removeDuplicateRows();

  public:
    size_t _nRows = 0;
    size_t _nCols = 0;
    int **_matrix = nullptr;
  };

  std::shared_ptr<PermMatrix> _permMatrix = nullptr;
  ///\brief _phToIndex is a map from the placeholder to the index of the row in the matrix of permutations
  std::unordered_map<std::string, size_t> _phToIndex;
};
} // namespace harm
