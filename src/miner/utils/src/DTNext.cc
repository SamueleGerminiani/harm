#include <algorithm>
#include <assert.h>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

#include "Automaton.hh"
#include "DTLimits.hh"
#include "DTNext.hh"
#include "DTUtils.hh"
#include "Evaluator.hh"
#include "Location.hh"
#include "TemplateImplication.hh"

#include "formula/temporal/TemporalExpression.hh"
#include "message.hh"
#include "minerUtils.hh"

namespace harm {
//--DTNext---------------------------------------

DTNext::DTNext(TemplateImplication *t)
    : _t(t), _delay(_t->_limits._dto_param._step),
      _tc(generatePtr<BooleanConstant>(true, ExpType::Bool, 1,
                                       _t->getTraceLength())) {
  // generate the rest of the automata
  generateFormulas();

  //  debug
  //for (auto &f : _formulas) {
  //  std::cout << temp2ColoredString(f, Language::SpotLTL, 0) << "\n";
  //}

  //   Check for parallel depth
  handleParallelDepth();

  updateTemplate(0);
}

void DTNext::generateFormulas() {

  // store the base template
  _formulas.push_back(_t->_templateFormula);
  _dtTokens.push_back("_dtNext0");
  // This first dtNext operator
  TemporalExpressionPtr delayOp = getDTPlaceholder(_formulas[0], 0);
  messageErrorIf(delayOp == nullptr,
                 "Could not find the dtNext placeholder");
  //fill the relation between the token name and the placeholder
  _dtTokenToPP["_dtNext0"] =
      std::dynamic_pointer_cast<BooleanLayerDTPlaceholder>(delayOp)
          ->getPlaceholderPointer();
  (*_dtTokenToPP["_dtNext0"]) = _tc;

  {
    //check if the template is well formed when including the DT Operator
    TemporalExpressionPtr fant =
        _t->_templateFormula->getItems()[0]->getItems()[0];

    if (_t->_applyDynamicShift) {
      messageErrorIf(!nothingBefore(_dtTokens.back(), fant),
                     "Can't have events happening before "
                     "the dtNext operator when "
                     "using "
                     "|->, |=> ");
    } else {
      messageErrorIf(!nothingAfter(_dtTokens.back(), fant),
                     "Can't have events happening after the dtNext "
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
    std::string token = "_dtNext" + std::to_string(i);
    _dtTokens.push_back(token);
    //make a new dt placeholder
    BooleanLayerDTPlaceholderPtr blp =
        generatePtr<BooleanLayerDTPlaceholder>(
            harm::DTO_Type::Next,
            generatePtrPtr<Proposition>((Proposition *)nullptr),
            token, (int)i);
    // save the relation between token and the placeholder pointer
    _dtTokenToPP[token] = blp->getPlaceholderPointer();

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
        "Could not find the parent of the dtNext placeholder");
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
}

void DTNext::handleParallelDepth() {
  TemporalExpressionPtr fant =
      _t->_templateFormula->getItems()[0]->getItems()[0];

  if (_t->_applyDynamicShift) {
    if (onlyToken("_dtNext0", selectFirstEvent(fant))) {
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
DTNext::~DTNext() {}

DTSolution DTNext::getSolution() {
  DTSolution ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.emplace_back();
    ret[i].push_back(*_dtTokenToPP.at(_dtTokens[i]));
  }
  return ret;
}

DTSolution DTNext::getMinimizedSolution(bool isOffset) {

  std::vector<std::vector<size_t>> c;
  std::vector<PropositionPtr> original;
  for (size_t i = 0; i <= _currDepth; i++) {
    original.emplace_back((*_dtTokenToPP.at(_dtTokens[i])));
  }

  for (size_t i = 1; i <= original.size(); i++) {
    // clear the current combinations
    c.clear();
    // generate combinations for size i
    comb(original.size(), i, c);
    // find a combination that satisfies the assertion
    for (auto &comb : c) {
      // fill with all true constants
      for (size_t i = 0; i < original.size(); i++) {
        (*_dtTokenToPP.at(_dtTokens[i])) = _tc;
      }
      // load the combination
      for (auto &e : comb) {
        (*_dtTokenToPP.at(_dtTokens[e])) = original[e];
      }
      // check if this combination works
      if (isOffset) {
        if (_t->assHoldsOnTraceOffset(harm::Location::Ant)) {
          // we found a minimal solution
          goto end;
        }
      } else {
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
  }
end:;
  DTSolution ret;
  for (size_t i = 0; i < original.size(); i++) {
    ret.emplace_back();
    ret[i].push_back(*_dtTokenToPP.at(_dtTokens[i]));
    //restore the original pointers
    (*_dtTokenToPP.at(_dtTokens[i])) = original[i];
  }
  return ret;
}

void DTNext::removeItems() {

  if (_parallelDepth) {
    for (size_t i = 0; i < _t->_limits._maxDepth; i++) {
      (*_dtTokenToPP[_dtTokens[i]]) = _tc;
    }
  } else {
    updateTemplate(0);
    (*_dtTokenToPP[_dtTokens[0]]) = _tc;
  }
  _choices.clear();
  _order.clear();
  _currDepth = 0;
}

void DTNext::popItem(int depth) {
  if (depth == -1) {
    depth = _currDepth;
  }
  messageErrorIf(_order.back() != depth, "out-of-order pop");
  if (_parallelDepth) {
    (*_dtTokenToPP[_dtTokens[depth]]) = _tc;
    _currDepth = (_currDepth > 0 ? _currDepth - 1 : _currDepth);
  } else {
    (*_dtTokenToPP[_dtTokens[depth]]) = _tc;
    //we need to adjust the depth of the operator in order to avoid unnecessery gaps, ex. {true ##1 true ##1 var1}->con is reduced to {var1}->con
    if ((size_t)depth == _currDepth) {
      while (_currDepth > 0 &&
             (*_dtTokenToPP.at(_dtTokens[_currDepth])) == _tc) {
        _currDepth--;
      }
    }
    //select the correct template for the current depth
    updateTemplate(_currDepth);
  }

  //update utility variables
  _choices.erase(depth);
  _order.pop_back();
  assert(_choices.size() == _order.size());
}

void DTNext::addItem(const PropositionPtr &p, int depth) {

  if (depth == -1) {
    //insert at the back
    if (!_choices.empty()) {
      _currDepth++;
    }
    if (_parallelDepth) {
      (*_dtTokenToPP.at(_dtTokens[_currDepth])) = p;
    } else {
      (*_dtTokenToPP.at(_dtTokens[_currDepth])) = p;
      updateTemplate(_currDepth);
    }
    _choices[_currDepth] = p;
    _order.push_back(_currDepth);
  } else {
    //insert at depth 'depth'
    _order.push_back(depth);
    if (_parallelDepth) {
      (*_dtTokenToPP.at(_dtTokens[depth])) = p;
      _choices[depth] = p;
    } else {
      (*_dtTokenToPP.at(_dtTokens[depth])) = p;
      _choices[depth] = p;
      if ((size_t)depth > _currDepth) {
        // fill gap with tc, if we are using an unordered operator, inserting an element can create 'gaps' in the template, ex. insertion at depth 3 {prop1 ##1 ? ##1 ?}|->con, we must replace ? with a true constant
        int tmp = _currDepth + 1;
        while (tmp < depth) {
          (*_dtTokenToPP.at(_dtTokens[tmp++])) = _tc;
        }
        _currDepth = depth;
        updateTemplate(_currDepth);
      }
    }
  }
  assert(_choices.size() == _order.size());
}
std::vector<PropositionPtr> DTNext::getItems() {
  std::vector<PropositionPtr> ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.push_back(*_dtTokenToPP.at(_dtTokens[i]));
  }
  return ret;
}

bool DTNext::isMultiDimensional() { return 0; }

bool DTNext::canInsertAtDepth(int depth) {
  if (depth == -1) {
    //insert to back
    return (_choices.empty() ? 0 : _currDepth + 1) <
           _t->_limits._maxDepth;
  } else {
    //insert at depth
    return (size_t)depth < _t->_limits._maxDepth &&
           (!_choices.count(depth) || _choices.at(depth) == _tc);
  }
}

bool DTNext::isUnordered() { return _t->_limits._isUnordered; }

size_t DTNext::getNChoices() { return _choices.size(); }

bool DTNext::isTaken(size_t id, bool negated, int depth) {
  return false;
}

void DTNext::removeLeaf(size_t id, bool negated, int depth) {}

void DTNext::addLeaf(const PropositionPtr &p, size_t id, bool negated,
                     int depth) {}

const DTLimits &DTNext::getLimits() { return _t->_limits; }

size_t DTNext::getCurrentDepth() { return _currDepth; }

TemporalExpressionPtr DTNext::getReducedFormula(bool offset) {
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
    if (_choices.count(i) && _choices.at(i) != _tc) { //found a prop
      if (delayOp->size() == 0 &&
          delayOp->getWindow().first > (int)_delay) {
        //there were leading true constants
        delayOp->setWindow({delayOp->getWindow().first - _delay,
                            delayOp->getWindow().second - _delay});
        delayOp->addItem(generatePtr<BooleanLayerInst>(
            copy(_choices.at(i)), "_dtNext" + std::to_string(i)));
        if (keepGoing(i + increment)) {
          //extend the delay operator if we are not at the last element
          //the delayOp becomes: (##K P) ##_delay P
          delayOp = extendDelay(delayOp);
        }
      } else {
        //add the current choice to the delayOp
        delayOp->addItem(generatePtr<BooleanLayerInst>(
            copy(_choices.at(i)), "_dtNext" + std::to_string(i)));
      }
    } else { //found a gap
      if (keepGoing(i + increment)) {
        //this is not the last element: increment the window
        delayOp->setWindow({delayOp->getWindow().first + _delay,
                            delayOp->getWindow().second + _delay});
      } else {
        //this is the last element, add a dummy true constant to complete the pair
        delayOp->addItem(generatePtr<BooleanLayerInst>(
            _tc, "_dtNext" + std::to_string(_currDepth)));
        break;
      }
    }

    if (delayOp->size() == 2 && keepGoing(i + increment)) {
      //delay operator is full, extend it, but only if we are not at the last element
      delayOp = extendDelay(delayOp);
    }
  }

  TemporalExpressionPtr ret = copy(_formulas[0], 1);
  substituteByToken(ret, delayOp, "_dtNext0_r");

  //return the reduced formula with the placeholders removed
  return handleOffset(ret);
}

bool DTNext::isSolutionInconsequential(const DTSolution &sol) const {
  auto uniSol = sol.getUnidimensionalSolution();
  return uniSol.empty() || uniSol.back() == _tc;
}

void DTNext::substitute(int depth, int width, PropositionPtr &sub) {
  if (depth == -1) {
    depth = _currDepth;
  }
  PropositionPtr tmp = _choices.at(depth);
  _choices.at(depth) = sub;
  (*_dtTokenToPP.at(_dtTokens[depth])) = sub;
  sub = tmp;
}

void DTNext::setL1Threads(size_t n) {
  for (size_t i = 0; i < _dtTokens.size(); i++) {
    _antEvaluators[i]->setL1Threads(n);
    if (_t->_contains_mma) {
      _impEvaluators[i]->setL1Threads(n);
    }
  }
}

} // namespace harm
