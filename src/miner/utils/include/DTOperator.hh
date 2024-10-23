#pragma once

#include "DTLimits.hh"
#include "DTUtils.hh"
#include "exp.hh"

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace harm {

class TemplateImplication;
class Automaton;

using namespace expression;
using DecTreeVariables =
    std::map<size_t, std::pair<PropositionPtr, PropositionPtr>>;

/*! \class DTSolution
    \brief Class representing a decision tree solution
*/
struct DTSolution {
  std::vector<std::vector<PropositionPtr>> _solution;
  ///return the list of solutions in a unidimensional format [p1, p2, ...]
  std::vector<PropositionPtr> getUnidimensionalSolution() const {
    std::vector<PropositionPtr> res;
    for (auto &s : _solution) {
      for (auto &p : s) {
        res.push_back(p);
      }
    }
    return res;
  }
  ///return the list of solutions in a multidimensional format [[p1, p2, ...], [p3, p4, ...], ...]
  std::vector<std::vector<PropositionPtr>>
  getMultidimensionalSolution() const {
    return _solution;
  }
  void emplace_back(const std::vector<PropositionPtr> &s = {}) {
    _solution.emplace_back(s);
  }
  std::vector<PropositionPtr> &operator[](size_t i) {
    return _solution[i];
  }
  ///sort the solutions following the width 'dimension' of the solution
  void sortByWidth(bool usingStringRepresentation = false) {
    if (!usingStringRepresentation) {
      for (auto &s : _solution) {
        std::sort(s.begin(), s.end());
      }
    } else {
      for (auto &s : _solution) {
        std::vector<std::pair<std::string, size_t>> originalStr;
        for (size_t i = 0; i < s.size(); i++) {
          originalStr.emplace_back(prop2String(s[i]), i);
        }
        //sort by string representation
        std::sort(originalStr.begin(), originalStr.end(),
                  [](const std::pair<std::string, size_t> &a,
                     const std::pair<std::string, size_t> &b) {
                    return a.first < b.first;
                  });
        std::vector<PropositionPtr> sorted;
        for (auto &p : originalStr) {
          sorted.push_back(s[p.second]);
        }
        s = sorted;
      }
    }
  }

  std::string toString() const {
    std::string res;
    for (size_t i = 0; i < _solution.size(); i++) {
      res += "[" + std::to_string(i) + "] ";
      for (auto &p : _solution[i]) {
        res += prop2String(p) + " ";
      }
      res += "\n";
    }
    return res;
  }
};

/*! \class DTOperator
    \brief Class representing a decision tree operator
*/
class DTOperator {
public:
  virtual ~DTOperator() {}
  /** \brief Add an operand
   * \param Proposition the proposition representing the operand
   * \param depth the temporal depth in the dt operator where to insert the operand
   */
  virtual void addItem(const PropositionPtr &p, int depth) = 0;
  /** \brief Removes an operands at depth 'depth'
   */
  virtual void popItem(int depth) = 0;
  /** \brief Removes all operands
   */
  virtual void removeItems() = 0;

  /** \brief Returns the minimized solution
   */
  virtual DTSolution getMinimizedSolution(bool isOffset) = 0;

  ///Returns the current solution (not minimized)
  virtual DTSolution getSolution() = 0;

  /** \brief Add a leaf of the decision tree
   * \param Proposition the proposition related to the leaf
   * \param id Id of the leaf
   * \param second if true the proposition is negated
   * \param depth depth of the leaf
   */
  virtual void addLeaf(const PropositionPtr &p, size_t id,
                       bool second, int depth) = 0;
  /** \brief Remove a leaf of the decision tree
   * \param id Id of the leaf
   * \param second if true the proposition is negated
   * \param depth depth of the leaf
   */
  virtual void removeLeaf(size_t id, bool second, int depth) = 0;
  /** \brief Returns true if it is possible to insert a new operand at depth 'depth'
   */
  virtual bool canInsertAtDepth(int depth) = 0;
  /** \brief substitute an operand with proposition 'sub'
   */
  virtual void substitute(int depth, int width,
                          PropositionPtr &sub) = 0;
  /** \brief Returns true if there is already a leaf with the given features
   */
  virtual bool isTaken(size_t id, bool second, int depth) = 0;

  virtual void setL1Threads(size_t n) = 0;

  /** \brief Returns true if the operator can be constructed in an unordered fashion
   */
  virtual bool isUnordered() = 0;

  ///Returns true if the operator containts both the width and the temporal depth
  virtual bool isMultiDimensional() = 0;

  ///Returns true if the solution is inconsequential, for example if the first operand is a a true constant
  virtual bool
  isSolutionInconsequential(const DTSolution &sol) const = 0;

  virtual std::vector<PropositionPtr> getItems() = 0;
  /** \brief Returns the current number of choices in the decision tree
   */
  virtual size_t getNChoices() = 0;

  ///Returns the temporal depth of the operator in terms of number of temporal operadsn (not the actual temporal depth of the formula)
  virtual size_t getCurrentDepth() = 0;

  virtual const DTLimits &getLimits() = 0;

  ///Returns an equivalent formula with the temporal depth reduced
  ///@param offset if true then ! is added to the consequent of the formula
  virtual TemporalExpressionPtr getReducedFormula(bool offset) = 0;

protected:
  ///list of dt operands
  std::vector<PropositionPtr> _items;
};

///Pointer to a DTOperator
using DTOperatorPtr = std::shared_ptr<DTOperator>;

///sets the correct template depeding on the input depth
#define updateTemplate(depth)                                        \
  _t->_antEvaluator = _antEvaluators[depth];                         \
  _t->_templateFormula = _formulas[depth];                           \
  if (_t->_contains_mma) {                                           \
    _t->_impEvaluator = _impEvaluators[depth];                       \
  }

} // namespace harm
