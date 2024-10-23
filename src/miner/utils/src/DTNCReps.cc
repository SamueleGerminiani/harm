#include <algorithm>
#include <assert.h>
#include <iterator>
#include <ostream>
#include <string>
#include <utility>

#include "Automaton.hh"
#include "DTLimits.hh"
#include "DTNCReps.hh"
#include "DTUtils.hh"
#include "Location.hh"
#include "TemplateImplication.hh"
#include "message.hh"
#include "minerUtils.hh"
#include "misc.hh"

namespace harm {
//--DTNCReps---------------------------------------
DTNCReps::DTNCReps(TemplateImplication *t)
    : _t(t), _nReps(_t->_limits._dto_param._step),
      _tc(generatePtr<BooleanConstant>(true, ExpType::Bool, 1,
                                       _t->getTraceLength())) {
  //print limits

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

void DTNCReps::generateFormulas() {

  // store the base template
  _formulas.push_back(_t->_templateFormula);
  _dtTokens.push_back("_dtNCReps0");
  // This first dtNCReps operator
  TemporalExpressionPtr concatOp = getDTPlaceholder(_formulas[0], 0);
  messageErrorIf(concatOp == nullptr,
                 "Could not find the dtNCReps placeholder");
  //fill the relation between the token name and the placeholder
  _dtTokenToPP["_dtNCReps0"] =
      std::dynamic_pointer_cast<BooleanLayerDTPlaceholder>(concatOp)
          ->getPlaceholderPointer();
  (*_dtTokenToPP["_dtNCReps0"]) = _tc;

  {
    //check if the template is well formed when including the DT Operator
    TemporalExpressionPtr fant =
        _t->_templateFormula->getItems()[0]->getItems()[0];

    if (_t->_applyDynamicShift) {
      messageErrorIf(!nothingBefore(_dtTokens.back(), fant),
                     "Can't have events happening before "
                     "the dtNCReps operator when "
                     "using "
                     "|->, |=> ");
    } else {
      messageErrorIf(!nothingAfter(_dtTokens.back(), fant),
                     "Can't have events happening after the dtNCReps "
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
    SereConcatPtr concatOp_new = generatePtr<SereConcat>();
    concatOp_new->setOverlapping(_t->_limits._dto_param._separator ==
                                 ":");
    // we build on the previously generated antecedent
    std::string token = "_dtNCReps" + std::to_string(i);
    _dtTokens.push_back(token);
    //make a new dt placeholder
    BooleanLayerDTPlaceholderPtr blp =
        generatePtr<BooleanLayerDTPlaceholder>(
            _t->_limits._dto_param._type,
            generatePtrPtr<Proposition>((Proposition *)nullptr),
            token, (int)i);
    // save the relation between token and the placeholder pointer
    _dtTokenToPP[token] = blp->getPlaceholderPointer();

    TemporalExpressionPtr toAdd = copy(concatOp);
    TemporalExpressionPtr toSub = getDTPlaceholder(toAdd, i - 1);
    if (_t->_limits._dto_param._type == DTO_Type::GoTo) {
      toSub = generatePtr<SereGoto>(toSub,
                                    std::make_pair(_nReps, _nReps));
    } else if (_t->_limits._dto_param._type == DTO_Type::NCReps) {
      toSub = generatePtr<SereNonConsecutiveRep>(
          toSub, std::make_pair(_nReps, _nReps));
    } else {
      messageError("Unknown DTO_Type");
    }
    substituteByToken(toAdd, toSub,
                      "_dtNCReps" + std::to_string(i - 1));

    if (_t->_applyDynamicShift) {
      // dtNCRepsM ##N ... ##N dtNCReps1 ##N dtNCReps0
      concatOp_new->addItem(blp);
      concatOp_new->addItem(toAdd);
    } else {
      // dtNCReps0 ##N dtNCReps1 ##N ... ##N dtNCRepsM
      concatOp_new->addItem(toAdd);
      concatOp_new->addItem(blp);
    }
    //prepare the concat operator for the next iteration
    concatOp = concatOp_new;

    //add the new concat operator to the base formula
    TemporalExpressionPtr formula_new = copy(_formulas[0]);
    TemporalExpressionPtr sdt_parent =
        getDTPlaceholderParent(formula_new, 0);
    messageErrorIf(
        sdt_parent == nullptr,
        "Could not find the parent of the dtNCReps placeholder");
    //this cover two cases: the second one is when the delat operator is the only element in the antecedent
    //Remember: The order of the elements changes when using a mm implication
    if (_t->_applyDynamicShift ||
        std::dynamic_pointer_cast<PropertyImplication>(sdt_parent) !=
            nullptr) {
      sdt_parent->getItems().front() = concatOp;
    } else {
      sdt_parent->getItems().back() = concatOp;
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

void DTNCReps::handleParallelDepth() {
  TemporalExpressionPtr fant =
      _t->_templateFormula->getItems()[0]->getItems()[0];

  if (_t->_applyDynamicShift) {
    if (onlyToken("_dtNCReps0", selectFirstEvent(fant))) {
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

  messageErrorIf(_parallelDepth != 0,
                 "Parallel depth is not allowed when using DTNCReps");
}

DTNCReps::~DTNCReps() {}

DTSolution DTNCReps::getMinimizedSolution(bool isOffset) {

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

void DTNCReps::removeItems() {
  updateTemplate(0);
  (*_dtTokenToPP[_dtTokens[0]]) = _tc;
  _choices.clear();
  _order.clear();
  _currDepth = 0;
}

void DTNCReps::popItem(int depth) {
  if (depth == -1) {
    depth = _currDepth;
  }
  assert(_order.back() == depth);
  (*_dtTokenToPP[_dtTokens[depth]]) = _tc;
  if ((size_t)depth == _currDepth) {
    while (_currDepth > 0 &&
           (*_dtTokenToPP.at(_dtTokens[_currDepth])) == _tc) {
      _currDepth--;
    }
  }
  updateTemplate(_currDepth);

  _choices.erase(depth);
  _order.pop_back();
  assert(_choices.size() == _order.size());
}

void DTNCReps::addItem(const PropositionPtr &p, int depth) {

  if (depth == -1) {
    if (!_choices.empty()) {
      _currDepth++;
    }
    (*_dtTokenToPP.at(_dtTokens[_currDepth])) = p;
    updateTemplate(_currDepth);
    _choices[_currDepth] = p;
    _order.push_back(_currDepth);
  } else {
    _order.push_back(depth);
    if (_parallelDepth) {
      (*_dtTokenToPP.at(_dtTokens[depth])) = p;
      _choices[depth] = p;
    } else {
      (*_dtTokenToPP.at(_dtTokens[depth])) = p;
      _choices[depth] = p;
      if ((size_t)depth > _currDepth) {
        // fill gap with tc
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

std::vector<PropositionPtr> DTNCReps::getItems() {
  std::vector<PropositionPtr> ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.push_back(*_dtTokenToPP.at(_dtTokens[i]));
  }
  return ret;
}
bool DTNCReps::isMultiDimensional() { return 0; }
bool DTNCReps::canInsertAtDepth(int depth) {
  if (depth == -1) {
    return (_choices.empty() ? 0 : _currDepth + 1) <
           _t->_limits._maxDepth;
  } else {
    return (size_t)depth < _t->_limits._maxDepth &&
           (!_choices.count(depth) || _choices.at(depth) == _tc);
  }
}

bool DTNCReps::isUnordered() { return _t->_limits._isUnordered; }
size_t DTNCReps::getNChoices() { return _choices.size(); }
bool DTNCReps::isTaken(size_t id, bool negated, int depth) {
  return false;
}
void DTNCReps::removeLeaf(size_t id, bool negated, int depth) {}
void DTNCReps::addLeaf(const PropositionPtr &p, size_t id,
                       bool negated, int depth) {}
const DTLimits &DTNCReps::getLimits() { return _t->_limits; }
size_t DTNCReps::getCurrentDepth() { return _currDepth; }

TemporalExpressionPtr DTNCReps::getReducedFormula(bool offset) {
  TemporalExpressionPtr formula = copy(_t->_templateFormula, 1);
  if (offset) {
    TemporalExpressionPtr fimpl = formula->getItems()[0];
    TemporalExpressionPtr fcon = getConsequent(fimpl);
    fimpl->popItem();
    fimpl->addItem(generatePtr<PropertyNot>(fcon));
  }
  return formula;
}

bool DTNCReps::isSolutionInconsequential(
    const DTSolution &sol) const {
  auto uniSol = sol.getUnidimensionalSolution();
  return uniSol.empty() || uniSol.back() == _tc;
}

void DTNCReps::substitute(int depth, int width, PropositionPtr &sub) {
  if (depth == -1) {
    depth = _currDepth;
  }
  PropositionPtr tmp = _choices.at(depth);
  _choices.at(depth) = sub;
  (*_dtTokenToPP.at(_dtTokens[depth])) = sub;
  sub = tmp;
}

void DTNCReps::setL1Threads(size_t n) {
  for (size_t i = 0; i < _dtTokens.size(); i++) {
    _antEvaluators[i]->setL1Threads(n);
    if (_t->_contains_mma) {
      _impEvaluators[i]->setL1Threads(n);
    }
  }
}

DTSolution DTNCReps::getSolution() {
  DTSolution ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.emplace_back();
    ret[i].push_back(*_dtTokenToPP.at(_dtTokens[i]));
  }
  return ret;
}
} // namespace harm
