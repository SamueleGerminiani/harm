
#include <algorithm>
#include <string>
#include <utility>

#include "DTAnd.hh"
#include "DTLimits.hh"
#include "DTUtils.hh"

#include "Location.hh"
#include "TemplateImplication.hh"
#include "expUtils/expUtils.hh"
#include "message.hh"

namespace harm {
//--DTAnd---------------------------------------
DTAnd::DTAnd(TemplateImplication *t) : _t(t) {
  _choices =
      makeGenericExpression<PropositionAnd>(_t->getTraceLength());
  TemporalExpressionPtr delayOp =
      getDTPlaceholder(_t->_templateFormula, 0);
  messageErrorIf(delayOp == nullptr,
                 "Could not find the dtAnd placeholder");
  //fill the relation between the token name and the placeholder
  (*std::dynamic_pointer_cast<BooleanLayerDTPlaceholder>(delayOp)
        ->getPlaceholderPointer()) = _choices;

  //generate the evaluators
  const PropertyImplicationPtr fimpl =
      std::dynamic_pointer_cast<PropertyImplication>(
          _t->_templateFormula->getItems()[0]);
  const TemporalExpressionPtr fant = getAntecedent(fimpl);
  t->_antEvaluator = generateEvaluator(fant, _t->_trace);
  if (t->_contains_mma) {
    t->_impEvaluator = generateEvaluator(fimpl, _t->_trace);
  }
}

DTAnd::~DTAnd() { removeItems(); };

bool DTAnd::isMultiDimensional() { return 0; }
size_t DTAnd::getCurrentDepth() { return 0; }
bool DTAnd::canInsertAtDepth(int depth) {
  return _choices->size() < _t->_limits._maxWidth;
}
bool DTAnd::isUnordered() { return false; }
size_t DTAnd::getNChoices() { return _choices->size(); }
bool DTAnd::isTaken(size_t id, bool negated, int depth) {
  if (negated) {
    return _leaves.count(id) && _leaves.at(id).second != nullptr;
  } else {
    return _leaves.count(id) && _leaves.at(id).first != nullptr;
  }
}
void DTAnd::removeLeaf(size_t id, bool negated, int depth) {
  if (negated) {
    _leaves.at(id).second = nullptr;
  } else {
    _leaves.at(id).first = nullptr;
  }
}
void DTAnd::addLeaf(const PropositionPtr &p, size_t id, bool negated,
                    int depth) {
  if (negated) {
    _leaves[id].second = p;
  } else {
    _leaves[id].first = p;
  }
}
void DTAnd::removeItems() { _choices->removeItems(); }
void DTAnd::addItem(const PropositionPtr &p, int depth) {
  _choices->addItem(p);
}
void DTAnd::popItem(int depth) { _choices->popItem(); }

std::vector<PropositionPtr> DTAnd::getItems() {
  return _choices->getItems();
}

bool DTAnd::isSolutionInconsequential(const DTSolution &sol) const {
  return 0;
}

void DTAnd::substitute(int depth, int width, PropositionPtr &sub) {
  if (width == -1) {
    width = _choices->getItems().size() - 1;
  }
  PropositionPtr tmp = _choices->getItems()[width];
  _choices->getItems()[width] = sub;
  sub = tmp;
}

const DTLimits &DTAnd::getLimits() { return _t->_limits; }

DTSolution DTAnd::getMinimizedSolution(bool isOffset) {
  std::vector<std::vector<size_t>> c;
  std::vector<PropositionPtr> original = _choices->getItems();
  for (size_t i = 1; i <= original.size(); i++) {
    c.clear();
    comb(original.size(), i, c);
    for (auto &comb : c) {
      _choices->removeItems();
      for (auto &e : comb) {
        _choices->addItem(original[e]);
      }
      // check if this combination works
      if (isOffset) {
        if (_t->assHoldsOnTraceOffset(harm::Location::Ant)) {
          // we found a minimal solution
          goto end;
        }
      } else {
        if (_t->assHoldsOnTrace(harm::Location::Ant)) {
          goto end;
        }
      }
    }
  }
end:;
  DTSolution ret;
  ret.emplace_back();
  for (auto p : _choices->getItems()) {
    ret[0].push_back(p);
  }

  _choices->getItems() = original;

  return ret;
}

TemporalExpressionPtr DTAnd::getReducedFormula(bool offset) {
  TemporalExpressionPtr formula = copy(_t->_templateFormula, 1);
  if (offset) {
    TemporalExpressionPtr fimpl = formula->getItems()[0];
    TemporalExpressionPtr fcon = getConsequent(fimpl);
    fimpl->popItem();
    fimpl->addItem(generatePtr<PropertyNot>(fcon));
  }
  return formula;
}

DTSolution DTAnd::getSolution() {
  DTSolution ret;
  ret.emplace_back(_choices->getItems());
  return ret;
}

void DTAnd::setL1Threads(size_t n) {
  //not to be implemented
}

} // namespace harm
