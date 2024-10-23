#include <algorithm>
#include <assert.h>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <utility>

#include "Location.hh"
#include "Permutator.hh"

#include "expUtils/expUtils.hh"
#include "expUtils/ope.hh"
#include "formula/atom/Atom.hh"
#include "formula/temporal/temporal.hh"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"

namespace harm {
using namespace expression;
//---utilities----------------------------------------------------------------

Row operator*(const Row &r1, const Row &r2) {
  Row ret = r1;
  for (auto e : r2) {
    ret.push_back(e);
  }
  return ret;
}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
  Matrix ret;
  for (auto &e1 : m1) {
    for (auto &e2 : m2) {
      ret.push_back(e1 * e2);
    }
  }
  return ret;
}

int computeBinomialCoefficient(int n, int k) {
  if (k == 0 || k == n)
    return 1;
  return computeBinomialCoefficient(n - 1, k - 1) +
         computeBinomialCoefficient(n - 1, k);
}

Matrix genBinomialCombinations(int N, int K) {
  Matrix ret;
  std::string bitmask(K, 1); // K leading 1's
  bitmask.resize(N, 0);      // N-K trailing 0's

  do {
    Row tmp;

    for (int i = 0; i < N; ++i) // [0..N-1] integers
    {
      if (bitmask[i])
        tmp.push_back(i);
    }
    ret.push_back(tmp);
  } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
  return ret;
}

Matrix genBinomial(Matrix in, size_t k) {
  Matrix ret;
  Matrix ens = genBinomialCombinations(in.size(), k);
  for (auto &en : ens) {
    Row finalRow;
    for (auto e : en) {
      for (auto f : in[e]) {
        finalRow.push_back(f);
      }
    }
    ret.push_back(finalRow);
  }
  return ret;
}
Matrix genCommutatives(Matrix in, size_t k) {
  Matrix ret;
  for (auto &r1 : in) {
    for (auto &r2 : in) {
      if (!(r1 == r2)) {
        ret.push_back(r1 * r2);
      }
    }
  }
  return ret;
}
bool isNonReflexive(const TemporalExpressionPtr &templ) {
  return isPropertyRelease(templ) || isPropertyUntil(templ);
}
bool isBinomialOp(const TemporalExpressionPtr &templ) {
  return isSereAnd(templ) || isSereOr(templ) ||
         isSereIntersect(templ) || isPropertyAnd(templ) ||
         isPropertyOr(templ);
}
std::vector<TemporalExpressionPtr>
unrollBinomialOperator(const TemporalExpressionPtr &formula,
                       const ope::temporalOpe &opeToUnroll) {
  std::vector<TemporalExpressionPtr> ret;
  std::deque<TemporalExpressionPtr> frontier;
  frontier.push_front(formula);
  while (!frontier.empty()) {
    auto f = frontier.front();
    frontier.pop_front();
    if (f->getOperator() != opeToUnroll) {
      ret.push_back(f);
      continue;
    }
    for (int i = f->size() - 1; i >= 0; i--) {
      frontier.push_front((*f)[i]);
    }
  }

  return ret;
}
//----------------------------------------------------------------

std::vector<std::pair<size_t, std::vector<TemporalExpressionPtr>>>
Permutator::clusterFormulas(const TemporalExpressionPtr &templ) {

  std::vector<std::pair<size_t, std::vector<TemporalExpressionPtr>>>
      equals;
  std::unordered_set<size_t> used;
  std::vector<TemporalExpressionPtr> candidates =
      unrollBinomialOperator(templ, templ->getOperator());
  for (size_t i = 0;
       i < candidates.size() && used.size() != candidates.size();
       i++) {
    if (!used.count(i)) {
      equals.push_back(
          std::make_pair(i, std::vector<TemporalExpressionPtr>()));
      equals.back().second.push_back(candidates[i]);
      used.insert(i);
      for (size_t j = 0; j < candidates.size(); j++) {
        if (i == j) {
          continue;
        }
        if (!used.count(j)) {
          if (areEquivalent(candidates[i], candidates[j])) {
            equals[i].second.push_back(candidates[j]);
            used.insert(j);
          }
        }
      }
    }
  }
  ////print equals
  //for (auto &[id, list] : equals) {
  //  std::cout << "cluster " << id << ": ";
  //  for (const auto &e : list) {
  //    std::cout << temp2String(
  //                     e, Language::SpotLTL,
  //                     PrintMode::ShowOnlyPermuationPlaceholders)
  //              << " ";
  //  }
  //  std::cout << "\n";
  //}
  return equals;
}

std::string Permutator::printPermutations() {
  std::stringstream ss;

  for (size_t i = 0; i < _permMatrix->_nRows; i++) {
    for (size_t j = 0; j < _permMatrix->_nCols; j++) {
      ss << _permMatrix->_matrix[i][j] << " ";
    }
    ss << "\n";
  }

  return ss.str();
}
//----------------------------------------------------------------

Permutator::PermUnit *
Permutator::generatePermUnit(const TemporalExpressionPtr &templ) {
  std::unordered_set<std::string> foundPH;
  return generatePermUnit(templ, foundPH);
}
Permutator::PermUnit *Permutator::generatePermUnit(
    const TemporalExpressionPtr &templ,
    std::unordered_set<std::string> &foundPH) {

  //   debug
  //  std::cout << temp2String(templ, Language::SpotLTL, PrintMode::ShowOnlyPermuationPlaceholders)
  // << "\n";

  PermUnit *ret = new PermUnit();
  ret->_op = PermOperator::Mul;

  if (isBinomialOp(templ)) {
    // retrieve equivalent operands
    std::vector<std::pair<size_t, std::vector<TemporalExpressionPtr>>>
        clusters = clusterFormulas(templ);
    ret->_dim._row = 1;
    ret->_dim._col = 0;
    for (auto &[id, listOfEquals] : clusters) {
      auto representant = listOfEquals[0];
      if (listOfEquals.size() > 1) {
        // cluster of equivalent operands
        auto *repPermUnit = generatePermUnit(representant, foundPH);
        PermUnit *bin = new PermUnit();
        bin->_op = PermOperator::Bin;
        bin->_children.push_back(repPermUnit);

        assert(repPermUnit->_dim._row >= listOfEquals.size());

        bin->_dim._row = computeBinomialCoefficient(
            repPermUnit->_dim._row, listOfEquals.size());
        bin->_dim._col = repPermUnit->_dim._col * listOfEquals.size();
        ret->_children.push_back(bin);
      } else {
        // cluster containing only one formula
        auto *repPermUnit = generatePermUnit(representant, foundPH);
        for (auto &e : repPermUnit->_children) {
          ret->_children.push_back(e);
        }
        delete repPermUnit;
      }
    }

    // adjust the current dimension according to the operands
    for (auto &i : ret->_children) {
      ret->_dim._row *= i->_dim._row;
      ret->_dim._col += i->_dim._col;
    }

  } else if (isNonReflexive(templ) &&
             areEquivalent((*templ)[0], (*templ)[1])) {
    ret->_dim._row = 1;
    ret->_dim._col = 0;
    ret->_op = PermOperator::Mul;
    auto representant = (*templ)[0];
    auto *repPermUnit = generatePermUnit(representant, foundPH);
    PermUnit *com = new PermUnit();
    com->_op = PermOperator::NonR;
    com->_children.push_back(repPermUnit);
    com->_dim._row =
        (repPermUnit->_dim._row * (repPermUnit->_dim._row - 1));
    com->_dim._col = repPermUnit->_dim._col * 2;

    ret->_children.push_back(com);
    for (auto &i : ret->_children) {
      ret->_dim._row *= i->_dim._row;
      ret->_dim._col += i->_dim._col;
    }

  } else if (isPermutationPlaceholder(templ)) {
    //placeholder
    std::string phName =
        isPermutationPlaceholder(templ)
            ? std::dynamic_pointer_cast<
                  BooleanLayerPermutationPlaceholder>(templ)
                  ->getToken()
            : "";

    messageErrorIf(phName == "", "Unknown placeholder ");

    PermUnit *ph = new PermUnit();
    ph->_op = PermOperator::Ph;
    if (foundPH.count(phName)) {
      // this is a repeated placeholder, will contain the same permutation of the first found
      ph->_dim._row = 1;
      ph->_dim._col = 1;
    } else {
      foundPH.insert(phName);
      //set the correct domain size
      ph->_dim._row = _phToDomainStr.at(phName).size();
      ph->_dim._col = 1;
    }
    ret->_children.push_back(ph);
    ret->_dim._row = ph->_dim._row;
    ret->_dim._col = ph->_dim._col;

  } else if (!isInst(templ) && !isDTPlaceholder(templ)) {
    //every other operator
    ret->_op = PermOperator::Mul;
    ret->_dim._row = 1;
    for (size_t i = 0; i < templ->size(); i++) {
      auto *childPermUnit = generatePermUnit((*templ)[i], foundPH);
      for (auto &e : childPermUnit->_children) {
        ret->_children.push_back(e);
      }
      delete childPermUnit;
    }
    for (auto &i : ret->_children) {
      ret->_dim._row *= i->_dim._row;
      ret->_dim._col += i->_dim._col;
    }
  }

  //debug
  //std::cout << temp2String(templ, Language::SpotLTL,
  //                         PrintMode::ShowOnlyPermuationPlaceholders)
  //          << ": " << ret->_dim._row << "x" << ret->_dim._col
  //          << "\n";
  return ret;
}
void Permutator::deletePermUnit(Permutator::PermUnit *pu) {
  for (auto &i : pu->_children) {
    deletePermUnit(i);
  }
  delete pu;
}

void Permutator::printPermUnit(Permutator::PermUnit *pu) {
  static std::string level = "";
  if (pu->_op == PermOperator::Ph) {
    std::cout << level << ">Ph"
              << "\n";
  } else if (pu->_op == PermOperator::NonR) {
    std::cout << level << ">NonR"
              << "\n";
  } else if (pu->_op == PermOperator::Bin) {
    std::cout << level << ">Bin"
              << "\n";
  } else if (pu->_op == PermOperator::Mul) {
    std::cout << level << ">Mul"
              << "\n";
  } else {
    messageError("");
  }
  level += "  ";

  for (auto i : pu->_children) {
    if (i->_op == PermOperator::Ph) {
      std::cout << level << "ph"
                << "\n";

    } else if (i->_op == PermOperator::NonR) {
      std::cout << level << "nr"
                << "\n";
      level += "  ";
      for (auto c : i->_children) {
        printPermUnit(c);
      }
      level.pop_back();
      level.pop_back();
    } else if (i->_op == PermOperator::Bin) {
      std::cout << level << "bin"
                << "\n";
      level += "  ";
      for (auto c : i->_children) {
        printPermUnit(c);
      }
      level.pop_back();
      level.pop_back();
    } else if (i->_op == PermOperator::Mul) {
      std::cout << level << "m"
                << "\n";
      level += "  ";
      for (auto c : i->_children) {
        printPermUnit(c);
      }
      level.pop_back();
      level.pop_back();
    } else {
      messageError("unexpected case");
    }
  }
  level.pop_back();
  level.pop_back();
}
bool Permutator::areEquivalent(const TemporalExpressionPtr &f1,
                               const TemporalExpressionPtr &f2) {

  //check formula type
  if (f1->getOperator() != f2->getOperator()) {
    return false;
  }

  //check number of children
  if (f1->size() != f2->size()) {
    return false;
  }

  //if the formula is a boolean layer check the type
  if (isBooleanLayer(f1) && isBooleanLayer(f2) &&
      !isSameBooleanLayerType(f1, f2)) {
    return false;
  }

  //---repeated placeholders disable the optimization-----
  if ((isPermutationPlaceholder(f1) &&
       (_phToFrequency.at(std::dynamic_pointer_cast<
                              BooleanLayerPermutationPlaceholder>(f1)
                              ->getToken()) > 1))) {
    return false;
  }

  if (isPermutationPlaceholder(f2) &&
      (_phToFrequency.at(std::dynamic_pointer_cast<
                             BooleanLayerPermutationPlaceholder>(f2)
                             ->getToken()) > 1)) {
    return false;
  }

  //------------------------------------------------------

  //check placeholders domains
  if ((isPermutationPlaceholder(f1)) &&
      (isPermutationPlaceholder(f2))) {
    std::string ph1 =
        isPermutationPlaceholder(f1)
            ? std::dynamic_pointer_cast<
                  BooleanLayerPermutationPlaceholder>(f1)
                  ->getToken()
            : "";

    std::string ph2 =
        isPermutationPlaceholder(f2)
            ? std::dynamic_pointer_cast<
                  BooleanLayerPermutationPlaceholder>(f2)
                  ->getToken()
            : "";

    if (_phToDomainStr.at(ph1) != _phToDomainStr.at(ph2)) {
      return false;
    }
  }

  //check if the children are equivalent
  for (size_t i = 0; i < f1->size(); i++) {
    if (!areEquivalent((*f1)[i], (*f2)[i])) {
      return false;
    }
  }

  return true;
}
void Permutator::genPermutations(
    const std::unordered_map<std::string,
                             std::vector<expression::PropositionPtr>>
        &phToDomain,
    const TemporalExpressionPtr &templateFormula) {

  //convert the propositional domains to string to allow quick comparisons
  for (auto &[ph, domain] : phToDomain) {
    for (auto p : domain) {
      _phToDomainStr[ph].push_back(prop2String(p));
    }
  }

  //sort to optimize the comparisons
  for (auto &[ph, domain] : _phToDomainStr) {
    std::sort(domain.begin(), domain.end());
  }

  // assign an index to each placeholders
  size_t phIndex = 0;
  traverse(templateFormula, [&](const TemporalExpressionPtr &templ) {
    if (isPermutationPlaceholder(templ)) {
      //extract the placeholder name
      std::string phName =
          isPermutationPlaceholder(templ)
              ? std::dynamic_pointer_cast<
                    BooleanLayerPermutationPlaceholder>(templ)
                    ->getToken()
              : "";
      messageErrorIf(
          phName == "",
          "Unknown placeholder in " +
              temp2String(templ, Language::SpotLTL,
                          PrintMode::ShowOnlyPermuationPlaceholders));
      if (!_phToIndex.count(phName)) {
        //store the index of the placeholder: this will be the column index in the permutation matrix
        _phToIndex[phName] = phIndex;
      } else {
        // repeated placeholders are stored elsewhere
        _repeatedPhTo_originalAndRepeatedIndex[phName] =
            std::make_pair(_phToIndex.at(phName), phIndex);
      }
      // count placeholders occurrences
      _phToFrequency[phName]++;
      phIndex++;
    }
    //dont skip the children of this node
    return false;
  });

  if (_phToFrequency.empty()) {
    //no placeholders, no permutations
    _permMatrix = std::make_shared<PermMatrix>(1, 0);
    _permMatrix->_nRows = 1;
    _permMatrix->_nCols = 0;
    return;
  }

  // find the dimensions and structure of the permutations
  PermUnit *pu = generatePermUnit(templateFormula);

  //    debug
  //printPermUnit(pu);

  // set the dimensions
  _permMatrix =
      std::make_shared<PermMatrix>(pu->_dim._row, pu->_dim._col);

  // generate the permutations
  auto perms = visitPermUnit(pu);

  messageErrorIf(pu->_dim._row != perms.size() ||
                     pu->_dim._col != perms[0].size(),
                 "Permutation dimensions does not match");

  // delete the dimensions and structure of the permutation
  deletePermUnit(pu);

  //// copy the permutations from vector to raw matrix
  for (size_t i = 0; i < _permMatrix->_nRows; i++) {
    std::copy(perms[i].begin(), perms[i].end(),
              _permMatrix->_matrix[i]);
  }

  // replace the permutations of repeated placeholders
  for (auto &[ph, originalAndRepeatedIndex] :
       _repeatedPhTo_originalAndRepeatedIndex) {
    size_t originalIndex = originalAndRepeatedIndex.first;
    size_t repeatedIndex = originalAndRepeatedIndex.second;
    for (size_t i = 0; i < _permMatrix->_nRows; i++) {
      _permMatrix->_matrix[i][repeatedIndex] =
          _permMatrix->_matrix[i][originalIndex];
    }
  }

  //remove the repeated permutations
  _permMatrix->removeDuplicateRows();

  //  debug
  //std::cout << "_phToIndex:"
  //          << "\n";
  //for (auto &e : _phToIndex) {
  //  std::cout << e.first << ":" << e.second << "\n";
  //}
  //if (!_repeatedPhTo_originalAndRepeatedIndex.empty()) {
  //  std::cout << "_repeatedPhTo_originalAndRepeatedIndex:"
  //            << "\n";
  //}
  //for (auto &[repeatedPh, originalAndRepeatedIndex] :
  //     _repeatedPhTo_originalAndRepeatedIndex) {
  //  std::cout << repeatedPh << ":" << originalAndRepeatedIndex.first
  //            << "-->" << originalAndRepeatedIndex.second << "\n";
  //}
  //std::cout << "n perms: " << _permMatrix->_nRows << "\n";
  ////std::cout << printPermutations() << "\n";
}

Matrix Permutator::visitPermUnit(Permutator::PermUnit *pu) {
  std::vector<Matrix> operands;

  if (pu->_op == PermOperator::Ph) {
    // create a Nx1 matrix
    Matrix op;
    for (size_t i = 0; i < pu->_dim._row; i++) {
      Row l;
      l.push_back(i);
      op.push_back(l);
    }
    operands.push_back(op);
  } else if (pu->_op == PermOperator::NonR) {
    auto perms = visitPermUnit(pu->_children[0]);
    operands.push_back(
        genCommutatives(perms, pu->_dim._col / perms[0].size()));
  } else if (pu->_op == PermOperator::Bin) {
    auto perms = visitPermUnit(pu->_children[0]);
    operands.push_back(
        genBinomial(perms, pu->_dim._col / perms[0].size()));
  } else if (pu->_op == PermOperator::Mul) {
    for (auto c : pu->_children) {
      operands.push_back(visitPermUnit(c));
    }
  } else {
    messageError("");
  }

  Matrix ret = operands[0];
  // multiply
  for (size_t i = 1; i < operands.size(); i++) {
    ret = ret * operands[i];
  }

  return ret;
}

//PermMatrix================================================

Permutator::PermMatrix::PermMatrix(size_t nRows, size_t nCols)
    : _nRows(nRows), _nCols(nCols) {
  _matrix = new int *[_nRows];
  for (size_t i = 0; i < _nRows; ++i) {
    _matrix[i] = new int[_nCols];
  }
}

Permutator::PermMatrix::~PermMatrix() {
  if (_matrix) {
    for (size_t i = 0; i < _nRows; ++i) {
      delete[] _matrix[i];
    }
    delete[] _matrix;
    _matrix = nullptr;
  }
}

void Permutator::PermMatrix::removeDuplicateRows() {
  auto hashFunc = [&](const std::vector<int> &vec) -> size_t {
    std::hash<int> hash;
    size_t result = 0;
    for (const int &val : vec) {
      result = result * 31 + hash(val);
    }
    return result;
  };

  auto equalFunc = [&](const std::vector<int> &a,
                       const std::vector<int> &b) -> bool {
    return a == b;
  };

  std::unordered_set<std::vector<int>, decltype(hashFunc),
                     decltype(equalFunc)>
      uniqueRows(0, hashFunc, equalFunc);
  std::vector<int *> newMatrix;

  for (size_t i = 0; i < _nRows; ++i) {
    std::vector<int> row(_matrix[i], _matrix[i] + _nCols);
    if (uniqueRows.find(row) == uniqueRows.end()) {
      uniqueRows.insert(row);
      newMatrix.push_back(_matrix[i]);
    } else {
      delete[] _matrix[i];
    }
  }

  _nRows = newMatrix.size();
  delete[] _matrix;
  _matrix = new int *[_nRows];
  for (size_t i = 0; i < _nRows; ++i) {
    _matrix[i] = newMatrix[i];
  }
}

} // namespace harm
