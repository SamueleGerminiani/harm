#pragma once

#include <stddef.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "DTOperator.hh"

#include "formula/atom/Atom.hh"
#include "formula/atom/Constant.hh"

namespace harm {
class Automaton;
class TemplateImplication;
struct DTLimits;
class Evaluator;
using EvaluatorPtr = std::shared_ptr<Evaluator>;

/*! \class DTNext
    \brief Decision tree operator class for ..[->N];.., see base class for the description of the methods
*/
class DTNCReps : public DTOperator {
public:
  DTNCReps(TemplateImplication *t);

  ~DTNCReps() override;

  bool isMultiDimensional() override;
  bool canInsertAtDepth(int depth) override;
  bool isUnordered() override;
  bool isTaken(size_t id, bool negated, int depth) override;
  size_t getNChoices() override;
  size_t getCurrentDepth() override;
  const DTLimits &getLimits() override;
  void addItem(const PropositionPtr &p, int depth) override;
  void popItem(int depth) override;
  void removeItems() override;
  std::vector<PropositionPtr> getItems() override;
  DTSolution getMinimizedSolution(bool isOffset) override;
  DTSolution getSolution() override;
  bool
  isSolutionInconsequential(const DTSolution &sol) const override;
  void removeLeaf(size_t id, bool negated, int depth) override;
  void addLeaf(const PropositionPtr &p, size_t id, bool negated,
               int depth) override;
  TemporalExpressionPtr getReducedFormula(bool offset) override;
  void substitute(int depth, int width, PropositionPtr &sub) override;
  virtual void setL1Threads(size_t n) override;

private:
  void generateFormulas();
  void handleParallelDepth();

  ///list of choices <depth of operand -> prop>
  std::map<size_t, PropositionPtr> _choices;

  ///order in which the operands were added (each element is the depth of the operand)
  std::vector<int> _order;

  ///list of tokens each operand
  std::vector<std::string> _dtTokens;

  ///list of formulas: if limits._maxDepth is equal to N, then _formulas contains N elements
  std::vector<TemporalExpressionPtr> _formulas;

  ///map from token to the corresponding placeholder pointer (PP)
  std::map<std::string, expression::PropositionPtrPtr> _dtTokenToPP;

  ///Pointer to the Template using this operator
  TemplateImplication *_t = nullptr;

  ///Contains the reps of ..[->Reps]..
  size_t _nReps = -1;

  ///list of evaluators
  std::vector<EvaluatorPtr> _antEvaluators;
  std::vector<EvaluatorPtr> _impEvaluators;

  ///max temporal depth of parallel operators in the template
  size_t _parallelDepth = 0;

  ///curr depth of the dto with respect to the number of choices
  size_t _currDepth = 0;

  //True constant used to cover holes
  PropositionPtr _tc = nullptr;
};
} // namespace harm
