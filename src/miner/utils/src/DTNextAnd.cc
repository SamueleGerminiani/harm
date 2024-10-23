#include <algorithm>
#include <assert.h>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <ostream>
#include <string>
#include <utility>

#include "Automaton.hh"
#include "DTLimits.hh"
#include "DTNextAnd.hh"
#include "DTUtils.hh"
#include "Location.hh"
#include "TemplateImplication.hh"
#include "expUtils/ExpType.hh"
#include "expUtils/expUtils.hh"
#include "message.hh"
#include "minerUtils.hh"

namespace harm {
//--DTNextAnd---------------------------------------

DTNextAnd::DTNextAnd(TemplateImplication *t)
    : _t(t), _delay(_t->_limits._dto_param._step),
      _tc(generatePtr<BooleanConstant>(true, ExpType::Bool, 1,
                                       _t->getTraceLength())) {
  // generate the rest of the automata
  generateFormulas();

  //  debug
  //for (auto &f : _formulas) {
  //  std::cout << temp2ColoredString(f, Language::SpotLTL,
  //                                  PrintMode::Hide)
  //            << "\n";
  //}

  //   Check for parallel depth
  handleParallelDepth();

  updateTemplate(0);
}

void DTNextAnd::generateFormulas() {

  // store the base template
  _formulas.push_back(_t->_templateFormula);
  // This first dtNext operator
  TemporalExpressionPtr delayOp = getDTPlaceholder(_formulas[0], 0);
  messageErrorIf(delayOp == nullptr,
                 "Could not find the dtNext placeholder");

  (*std::dynamic_pointer_cast<BooleanLayerDTPlaceholder>(delayOp)
        ->getPlaceholderPointer()) =
      makeGenericExpression<PropositionAnd>(_t->getTraceLength());

  //fill the relation between the token name and the operand
  _choices[0] = std::dynamic_pointer_cast<PropositionAnd>(
      *std::dynamic_pointer_cast<BooleanLayerDTPlaceholder>(delayOp)
           ->getPlaceholderPointer());

  {
    //check if the template is well formed when including the DT Operator
    TemporalExpressionPtr fant =
        _t->_templateFormula->getItems()[0]->getItems()[0];

    if (_t->_applyDynamicShift) {
      messageErrorIf(!nothingBefore("_dtNextAnd0", fant),
                     "Can't have events happening before "
                     "the dtNextAnd operator when "
                     "using "
                     "|->, |=> ");
    } else {
      messageErrorIf(
          !nothingAfter("_dtNextAnd0", fant),
          "Can't have events happening after the dtNextAnd "
          "operator when "
          "not using "
          "->, => ");
    }
  }

  //base antecedent
  _antEvaluators.push_back(generateEvaluator(
      _formulas[0]->getItems()[0]->getItems()[0], _t->_trace));

  if (_t->_contains_mma) {
    //base implication
    _impEvaluators.push_back(
        generateEvaluator(_formulas[0]->getItems()[0], _t->_trace));
  }

  //build the rest of the formulas
  for (size_t i = 1; i < _t->_limits._maxDepth; i++) {
    SereDelayPtr delayOp_new = generatePtr<SereDelay>();
    delayOp_new->setWindow({_delay, _delay});
    // we build on the previously generated antecedent
    std::string token = "_dtNextAnd" + std::to_string(i);
    //make a new dt placeholder
    BooleanLayerDTPlaceholderPtr blp =
        generatePtr<BooleanLayerDTPlaceholder>(
            harm::DTO_Type::NextAnd,
            generatePtr<PropositionPtr>(
                makeGenericExpression<PropositionAnd>(
                    _t->getTraceLength())),
            token, (int)i);

    // populate the choices at depth i
    _choices[i] = std::dynamic_pointer_cast<PropositionAnd>(
        *blp->getPlaceholderPointer());

    if (_t->_applyDynamicShift) {
      // dtNextM ##N ... ##N dtNext1 ##N dtNext0
      delayOp_new->addItem(blp);
      delayOp_new->addItem(copy(delayOp));
    } else {
      // dtNext0 ##N dtNext1 ##N ... ##N dtNextM
      delayOp_new->addItem(copy(delayOp));
      delayOp_new->addItem(blp);
    }
    //prepare the delay operator for the next iteration
    delayOp = delayOp_new;

    //add the new delay operator to the base formula
    TemporalExpressionPtr formula_new = copy(_formulas[0]);
    TemporalExpressionPtr sdt_parent =
        getDTPlaceholderParent(formula_new, 0);
    messageErrorIf(
        sdt_parent == nullptr,
        "Could not find the parent of the dtNextAnd placeholder");
    //this cover two cases: the second one is when the delat operator is the only element in the antecedent
    //Remember: The order of the elements changes when using a mm implication
    if (_t->_applyDynamicShift ||
        std::dynamic_pointer_cast<PropertyImplication>(sdt_parent) !=
            nullptr) {
      sdt_parent->getItems().front() = delayOp;
    } else {
      sdt_parent->getItems().back() = delayOp;
    }

    //init all the placeholders with the pointers of the previouse formula: all _formulas must use the same pointers
    auto pack = extractPlaceholders(_formulas[i - 1]);
    substitutePlaceholders(formula_new, pack);

    //store the new formula and the corresponding evaluators
    _formulas.push_back(formula_new);
    _antEvaluators.push_back(generateEvaluator(
        formula_new->getItems()[0]->getItems()[0], _t->_trace));
    if (_t->_contains_mma) {
      _impEvaluators.push_back(
          generateEvaluator(formula_new->getItems()[0], _t->_trace));
    }
  }

  for (size_t i = 0; i < _t->_limits._maxDepth; i++) {
    _leaves.emplace_back();
  }
}

void DTNextAnd::handleParallelDepth() {
  TemporalExpressionPtr fant =
      _t->_templateFormula->getItems()[0]->getItems()[0];

  if (_t->_applyDynamicShift) {
    if (onlyToken("_dtNextAnd0", selectFirstEvent(fant))) {
      //no parallel depth
      return;
    }
    int baseDepth = 0;
    for (const auto &f : _formulas) {
      TemporalExpressionPtr fant = f->getItems()[0]->getItems()[0];
      //extract first temporal element from the left
      auto portionBare = selectFirstEvent(fant);

      //get the max depth
      int depth = getTemporalDepth(fant);
      //fails if the depth cant be quantified
      messageErrorIf(depth == -1, " parallel depth is unknown");
      if (baseDepth == 0) {
        //depth of the original template
        baseDepth = depth;
      } else if (depth > baseDepth) {
        //cannot add any more operands without pushing things
        break;
      }
      //adding an operand did not change the maximum depth of the formula
      _parallelDepth++;
    }
  }

  if (_parallelDepth != 0) {
    //adapt the limits to the found parallel depth
    _t->_limits._maxDepth = _parallelDepth < _t->_limits._maxDepth
                                ? _parallelDepth
                                : _t->_limits._maxDepth;
    //set the formula of the correct depth, from now on, the template will remain unchanged
    updateTemplate(_t->_limits._maxDepth - 1);
    //set all operands to the true constant
    removeItems();
  }
}

DTNextAnd::~DTNextAnd() {}

DTSolution DTNextAnd::getMinimizedSolution(bool isOffset) {

  std::vector<std::pair<PropositionPtr, size_t>> propList;

  // keep track of the original choices
  DTSolution originalChoices = getSolution();
  std::vector<int> _originalOrder = _order;
  size_t originalDepth = _currDepth;

  for (size_t i = 0; i <= _currDepth; i++) {
    for (auto &p : _choices.at(i)->getItems()) {
      propList.emplace_back(p, i);
    }
  }

  std::vector<std::vector<size_t>> c;
  for (size_t i = 1; i <= propList.size(); i++) {
    // clear the current combinations
    c.clear();
    // generate combinations for size i
    comb(propList.size(), i, c);
    // find a combination that satisfies the assertion
    for (auto &comb : c) {
      // fill with all true constants
      for (size_t j = 0; j <= _currDepth; j++) {
        _choices.at(j)->removeItems();
      }

      // load the combination
      for (auto &e : comb) {
        _choices.at(propList[e].second)->addItem(propList[e].first);
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
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.emplace_back();
    for (auto &e : _choices.at(i)->getItems()) {
      ret[i].push_back(e);
    }
  }

  // restore the original solution
  removeItems();
  auto multiSol = originalChoices.getMultidimensionalSolution();
  for (size_t i = 0; i < multiSol.size(); i++) {
    _choices.at(i)->getItems() = multiSol[i];
  }
  _order = _originalOrder;
  _currDepth = originalDepth;
  updateTemplate(_currDepth);
  return ret;
}

void DTNextAnd::removeItems() {
  if (_parallelDepth) {
    for (size_t i = 0; i <= _currDepth; i++) {
      _choices.at(i)->removeItems();
    }
  } else {
    for (size_t i = 0; i <= _currDepth; i++) {
      _choices.at(i)->removeItems();
    }
    updateTemplate(0);
  }
  _order.clear();
  _currDepth = 0;
}

void DTNextAnd::popItem(int depth) {
  messageErrorIf(depth == -1,
                 "You must always specify the depth when popping "
                 "from a multidimensional operator");
  assert(!_choices.at(depth)->empty());
  messageErrorIf(_order.back() != depth,
                 "out-of-order pop, expecting: " +
                     std::to_string(_order.back()) +
                     " recieved: " + std::to_string(depth));

  _choices.at(depth)->popItem();

  if (!_parallelDepth) {
    if ((size_t)depth == _currDepth) {
      while (_currDepth > 0 && _choices.at(_currDepth)->empty()) {
        _currDepth--;
      }
    }
    updateTemplate(_currDepth);
  }

  _order.pop_back();
  assert(std::accumulate(_choices.begin(), _choices.end(), 0ul,
                         [](size_t &a, const auto &e) {
                           return a + e.second->size();
                         }) == _order.size());
}
void DTNextAnd::addItem(const PropositionPtr &p, int depth) {

  messageErrorIf(depth == -1,
                 "You must always specify the depth when "
                 "inserting in a multidimensional operator");
  _order.push_back(depth);
  if (_parallelDepth) {
    _choices.at(depth)->addItem(p);
  } else {
    _choices.at(depth)->addItem(p);
    if ((size_t)depth > _currDepth) {
      _currDepth = depth;
      updateTemplate(_currDepth);
    }
  }

  assert(std::accumulate(_choices.begin(), _choices.end(), 0ul,
                         [](size_t &a, const auto &e) {
                           return a + e.second->size();
                         }) == _order.size());
}

std::vector<PropositionPtr> DTNextAnd::getItems() {
  std::vector<PropositionPtr> ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    if (!_choices.at(i)->empty()) {
      ret.push_back(_choices.at(i));
    } else {
      ret.push_back(_tc);
    }
  }
  return ret;
}

bool DTNextAnd::isMultiDimensional() { return 1; }

bool DTNextAnd::canInsertAtDepth(int depth) {
  messageErrorIf(depth == -1,
                 "You must always specify the depth when dealing "
                 "with a multidimensional operator");
  return (size_t)depth < _t->_limits._maxDepth &&
         (_choices.at(depth)->size() < _t->_limits._maxWidth);
}

bool DTNextAnd::isUnordered() { return _t->_limits._isUnordered; }

size_t DTNextAnd::getNChoices() { return _order.size(); }

bool DTNextAnd::isTaken(size_t id, bool negated, int depth) {
  messageErrorIf(depth == -1,
                 "You must always specify the depth when dealing "
                 "with a multidimensional operator");
  if (negated) {
    return _leaves[depth].count(id) &&
           _leaves[depth].at(id).second != nullptr;
  } else {
    return _leaves[depth].count(id) &&
           _leaves[depth].at(id).first != nullptr;
  }
}

void DTNextAnd::removeLeaf(size_t id, bool negated, int depth) {
  messageErrorIf(depth == -1,
                 "You must always specify the depth when dealing "
                 "with a multidimensional operator");
  if (negated) {
    _leaves[depth].at(id).second = nullptr;
  } else {
    _leaves[depth].at(id).first = nullptr;
  }
}

void DTNextAnd::addLeaf(const PropositionPtr &p, size_t id,
                        bool negated, int depth) {
  messageErrorIf(depth == -1,
                 "You must always specify the depth when dealing "
                 "with a multidimensional operator");
  if (negated) {
    _leaves[depth][id].second = p;
  } else {
    _leaves[depth][id].first = p;
  }
}

const DTLimits &DTNextAnd::getLimits() { return _t->_limits; }

size_t DTNextAnd::getCurrentDepth() { return _currDepth; }

void DTNextAnd::substitute(int depth, int width,
                           PropositionPtr &sub) {
  if (depth == -1) {
    depth = _currDepth;
  }
  if (width == -1) {
    width = _choices.at(depth)->size() - 1;
  }
  PropositionPtr tmp = _choices.at(depth)->getItems()[width];
  _choices.at(depth)->getItems()[width] = sub;
  sub = tmp;
}

bool DTNextAnd::isSolutionInconsequential(
    const DTSolution &sol) const {
  auto multiSol = sol.getMultidimensionalSolution();
  return multiSol.empty() || multiSol.back().empty();
}

DTSolution DTNextAnd::getSolution() {
  DTSolution ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.emplace_back(_choices.at(i)->getItems());
  }
  return ret;
}

void DTNextAnd::setL1Threads(size_t n) {
  for (size_t i = 0; i < _choices.size(); i++) {
    _antEvaluators[i]->setL1Threads(n);
    if (_t->_contains_mma) {
      _impEvaluators[i]->setL1Threads(n);
    }
  }
}

TemporalExpressionPtr DTNextAnd::getReducedFormula(bool offset) {
  auto handleOffset = [&](TemporalExpressionPtr &f) {
    if (offset) {
      TemporalExpressionPtr fimpl = f->getItems()[0];
      TemporalExpressionPtr fcon = fimpl->getItems()[1];
      fimpl->popItem();
      fimpl->addItem(generatePtr<PropertyNot>(fcon));
    }
    return f;
  };

  if (_currDepth == 0) {
    //no need to reduce the formula
    //fill the empy spaces with the true constant
    for (size_t i = 0; i <= _currDepth; i++) {
      if (_choices.at(i)->empty()) {
        _choices.at(i)->addItem(_tc);
      }
    }
    TemporalExpressionPtr ret = copy(_formulas[_currDepth], 1);
    return handleOffset(ret);
  }

  int start = _t->_applyDynamicShift ? _currDepth : 0;
  int increment = _t->_applyDynamicShift ? -1 : 1;

  //termination condition
  auto keepGoing = [&](int i) {
    return _t->_applyDynamicShift ? i >= 0 : i <= (int)_currDepth;
  };

  auto extendDelay = [&](const SereDelayPtr &delayOp) {
    SereDelayPtr delayOp_new = generatePtr<SereDelay>();
    delayOp_new->setWindow({_delay, _delay});
    delayOp_new->addItem(delayOp);
    return delayOp_new;
  };

  SereDelayPtr delayOp = generatePtr<SereDelay>();
  delayOp->setWindow({_delay, _delay});
  for (int i = start; keepGoing(i); i += increment) {
    if (!_choices.at(i)->empty()) { //found a prop
      if (delayOp->size() == 0 &&
          delayOp->getWindow().first > (int)_delay) {
        //there were leading true constants
        delayOp->setWindow({delayOp->getWindow().first - _delay,
                            delayOp->getWindow().second - _delay});
        delayOp->addItem(generatePtr<BooleanLayerInst>(
            copy(_choices.at(i)), "_dtNextAnd" + std::to_string(i)));
        if (keepGoing(i + increment)) {
          //extend the delay operator if we are not at the last element
          //the delayOp becomes: (##K P) ##_delay P
          delayOp = extendDelay(delayOp);
        }
      } else {
        //add the current choice to the delayOp
        delayOp->addItem(generatePtr<BooleanLayerInst>(
            copy(_choices.at(i)), "_dtNextAnd" + std::to_string(i)));
      }
    } else { //found a gap
      if (keepGoing(i + increment)) {
        //this is not the last element: increment the window
        delayOp->setWindow({delayOp->getWindow().first + _delay,
                            delayOp->getWindow().second + _delay});
      } else {
        //this is the last element, add a dummy true constant to complete the pair
        delayOp->addItem(generatePtr<BooleanLayerInst>(
            _tc, "_dtNextAnd" + std::to_string(_currDepth)));
        break;
      }
    }

    if (delayOp->size() == 2 && keepGoing(i + increment)) {
      //delay operator is full, extend it, but only if we are not at the last element
      delayOp = extendDelay(delayOp);
    }
  }

  TemporalExpressionPtr ret = copy(_formulas[0], 1);
  substituteByToken(ret, delayOp, "_dtNextAnd0_r");

  //return the reduced formula with the placeholders removed
  return handleOffset(ret);
}

} // namespace harm
