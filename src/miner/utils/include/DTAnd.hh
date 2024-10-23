#pragma once
#include <stddef.h>
#include <string>
#include <utility>
#include <vector>

#include "DTOperator.hh"
#include "formula/atom/Atom.hh"
#include "formula/expression/GenericExpression.hh"

namespace harm {
class TemplateImplication;
struct DTLimits;

/*! \class DTAnd
    \brief Decision tree operator class for ..&&.., see base class for the description of the methods
*/
class DTAnd : public DTOperator {
public:
  DTAnd(TemplateImplication *t);

  virtual ~DTAnd();

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
  ///List of operands
  PropositionAndPtr _choices;
  ///Pointer to the Template using this operator
  TemplateImplication *_t;
  ///List of leaves
  DecTreeVariables _leaves;
};
} // namespace harm
