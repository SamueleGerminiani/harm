#include "DTNext.hh"
#include "DTUtils.hh"
#include "ProgressBar.hpp"
#include "Template.hh"
#include "message.hh"
#include "minerUtils.hh"
#include <spot/tl/formula.hh>
#include <spot/twaalgos/postproc.hh>
#include <string>
#include <unordered_set>
#include <utility>
namespace harm {
//--DTNext---------------------------------------

DTNext::DTNext(BooleanConstant *p, size_t shift, Template *t,
               const DTLimits &limits)
    : _t(t), _shift(shift), _tc(p) {

  _limits = limits;
  _limits._maxWidth = -1;
  // The base case automata were already generated in the template
  _tokens.push_back("dtNext0");
  _ant.push_back(_t->_ant);
  // storing depths
  _antDepth.push_back(_t->getDepth(_ant.back()));

  // adjust offset:  we shouldn't have any delaying when we have only one
  // operand
  for (auto &e : t->_templateFormula)
    e._offset = (e._t == Hstring::Stype::DTNext ? 0 : e._offset);

  _formulas.push_back(t->_templateFormula);

  if (_t->_applyDynamicShift) {
    _applyDynamicShift = true;
    messageErrorIf(
        !nothingBefore(
            _tokens.back(),
            spot::parse_infix_psl(_t->_templateFormula.getAnt().toSpotString())
                .f),
        "Can't have events happening before the dtNext operator when using "
        "|->, |=> ");
  } else {
    messageErrorIf(
        !nothingAfter(
            _tokens.back(),
            spot::parse_infix_psl(_t->_templateFormula.getAnt().toSpotString())
                .f),
        "Can't have events happening after the dtNext operator when not using "
        "->, => ");
  }

  //  debug
  //  messageInfo("Building automata...");

  // generate the rest of the automata
  generateFormulas();

  //  debug
    //for (auto &f : _formulas) {
    //  std::cout << f.toSpotString() << "\n";
    //}

  //   Check for parallel depth
  handleParallelDepth();
}

void DTNext::generateFormulas() {
  // retrieve the consequent and the implication of the formula
  auto hcon = _t->_templateFormula.getCon();
  // remove unwanted spaces in the string representation of the implication

  for (size_t i = 1; i < _limits._maxDepth; i++) {
    // we build on the previously generated antecedent
    auto hant = _formulas[i - 1].getAnt();
    Proposition **pp = new Proposition *(nullptr);
    std::string token = "dtNext" + std::to_string(i);
    // the relation between token name and proposition is kept in the template
    _t->_tokenToProp[token] = pp;
    _tokens.push_back(token);

    if (_t->_applyDynamicShift) {
      // dtNextM ##N ... ##N dtNext2 ##N dtNext0
      //find the last operand and append a new one
      auto dth =
          std::find_if(std::begin(hant), std::end(hant),
                       [](Hstring &e) { return e._t == Hstring::Stype::DTNext; }

          );

      messageErrorIf(dth == hant.end(), "Could not find the operand");
      dth->_offset = _shift;
      hant.insert(dth, Hstring(token, Hstring::Stype::DTNext, pp));
    } else {
      // dtNext0 ##N dtNext1 ##N ... ##N dtNextM
      // find the last operand and append a new one
      auto dth =
          std::find_if(std::rbegin(hant), std::rend(hant),
                       [](Hstring &e) { return e._t == Hstring::Stype::DTNext; }

          );

      messageErrorIf(dth == hant.rend(), "Could not find the operand");
      auto newOperand = Hstring(token, Hstring::Stype::DTNext, pp);
      newOperand[0]._offset = _shift;
      hant.insert(++((dth + 1).base()), newOperand);
    }

    Hstring imp = _t->_templateFormula.getImp();
    _formulas.push_back(Hstring("G(", Hstring::Stype::G) + hant + imp + hcon +
                        Hstring(")", Hstring::Stype::G));

    // string to spot formula
    spot::parsed_formula ant = spot::parse_infix_psl(hant.toSpotString());

    // Synthesising the automata
    auto antAutomaton = generateDeterministicSpotAutomaton(ant.f);

    // building storing our custom automata
    _ant.push_back(buildAutomaton(antAutomaton,_t->_tokenToProp));

    // storing depths
    _antDepth.push_back(_t->getDepth(_ant.back()));
  }
}

void DTNext::handleParallelDepth() {
  if (_t->_applyDynamicShift) {
    if (onlyToken("dtNext0", selectFirstEvent(
                                 spot::parse_infix_psl(
                                     _formulas.front().getAnt().toSpotString())
                                     .f))) {
      //no parallel depth
      return;
    }

    int baseDepth = 0;
    for (auto f : _formulas) {
      //extract first temporal element from the left
      auto portionBare =
          selectFirstEvent(spot::parse_infix_psl(f.getAnt().toSpotString()).f);

      //create an automaton of the first event
      std::stringstream ss;
      print_spin_ltl(ss, portionBare, false) << '\n';
      std::string portion = "{" + ss.str() + "}";
      auto portionFormula = spot::parse_infix_psl(portion);
      auto aut = generateDeterministicSpotAutomaton(portionFormula.f);
      Automaton *pAnt = buildAutomaton(aut,_t->_tokenToProp);
      //get the max depth of the automaton from the root
      int depth = _t->getDepth(pAnt);
      //fails if the automaton has cycles
      messageErrorIf(depth == -1, " parallel depth is unknown");
      if (baseDepth == 0) {
        //depth of the original template
        baseDepth = depth;
      } else if (depth > baseDepth) {
        //cannot add any more operands without pushing things
        delete pAnt;
        break;
      }
      //adding an operand did not change the maximum depth of the automaton
      _parallelDepth++;
      delete pAnt;
    }
  }

  if (_parallelDepth != 0) {
    _limits._maxDepth =
        _parallelDepth < _limits._maxDepth ? _parallelDepth : _limits._maxDepth;
    //set the formula of the correct depth, from now on, the template will remain unchanged
    _t->_ant = _ant[_limits._maxDepth - 1];
    _t->_templateFormula = _formulas[_limits._maxDepth - 1];
    _t->_antDepth = _antDepth[_limits._maxDepth - 1];
    //set all operands to the true constant
    removeItems();
  }
}
DTNext::~DTNext() {
  for (size_t i = 0; i < _tokens.size(); i++) {
    delete _ant[i];
  }
  delete _tc;
}

std::vector<Proposition *> DTNext::minimize(bool isOffset) {

  std::vector<std::vector<size_t>> c;
  std::vector<Proposition *> original;
  for (size_t i = 0; i <= _currDepth; i++) {
    original.emplace_back((*_t->_tokenToProp.at(_tokens[i])));
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
        (*_t->_tokenToProp.at(_tokens[i])) = _tc;
      }
      // load the combination
      for (auto &e : comb) {
        (*_t->_tokenToProp.at(_tokens[e])) = original[e];
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
  std::vector<Proposition *> ret;
  for (size_t i = 0; i < original.size(); i++) {
    ret.push_back(*_t->_tokenToProp.at(_tokens[i]));
    (*_t->_tokenToProp.at(_tokens[i])) = original[i];
  }
  return ret;
}
void DTNext::removeItems() {

  if (_parallelDepth) {
    for (size_t i = 0; i < _limits._maxDepth; i++) {
      (*_t->_tokenToProp[_tokens[i]]) = _tc;
    }
  } else {
    _t->_ant = _ant[0];
    _t->_templateFormula = _formulas[0];
    _t->_antDepth = _antDepth[0];
    (*_t->_tokenToProp[_tokens[0]]) = _tc;
  }
  _choices.clear();
  _order.clear();
  _currDepth = 0;
}
void DTNext::popItem(int depth) {
  if (depth == -1) {
    depth = _currDepth;
  }
  assert(_order.back() == depth);
  if (_parallelDepth) {
    (*_t->_tokenToProp[_tokens[depth]]) = _tc;
    _currDepth = (_currDepth > 0 ? _currDepth - 1 : _currDepth);
  } else {
    (*_t->_tokenToProp[_tokens[depth]]) = _tc;
    //we need to adjust the depth of the operator in order to avoid unnecessery gaps, ex. {true ##1 true ##1 var1}->con is reduced to {var1}->con
    if ((size_t)depth == _currDepth) {
      while (_currDepth > 0 &&
             (*_t->_tokenToProp.at(_tokens[_currDepth])) == _tc) {
        _currDepth--;
      }
    }
    //select the correct template for the current depth
    _t->_ant = _ant[_currDepth];
    _t->_templateFormula = _formulas[_currDepth];
    _t->_antDepth = _antDepth[_currDepth];
  }

  //update utility variables
  _choices.erase(depth);
  _order.pop_back();
  assert(_choices.size() == _order.size());
}
void DTNext::addItem(Proposition *p, int depth) {

  if (depth == -1) {
    //insert at the back
    if (!_choices.empty()) {
      _currDepth++;
    }
    if (_parallelDepth) {
      (*_t->_tokenToProp.at(_tokens[_currDepth])) = p;
    } else {
      (*_t->_tokenToProp.at(_tokens[_currDepth])) = p;
      _t->_ant = _ant[_currDepth];
      _t->_templateFormula = _formulas[_currDepth];
      _t->_antDepth = _antDepth[_currDepth];
    }
    _choices[_currDepth] = p;
    _order.push_back(_currDepth);
  } else {
    //insert at depth 'depth'
    _order.push_back(depth);
    if (_parallelDepth) {
      (*_t->_tokenToProp.at(_tokens[depth])) = p;
      _choices[depth] = p;
    } else {
      (*_t->_tokenToProp.at(_tokens[depth])) = p;
      _choices[depth] = p;
      if ((size_t)depth > _currDepth) {
        // fill gap with tc, if we are using an unordered operator, inserting an element can create 'gaps' in the template, ex. insertion at depth 3 {prop1 ##1 ? ##1 ?}|->con, we must replace ? with a true constant
        int tmp = _currDepth + 1;
        while (tmp < depth) {
          (*_t->_tokenToProp.at(_tokens[tmp++])) = _tc;
        }
        _currDepth = depth;
        _t->_ant = _ant[_currDepth];
        _t->_templateFormula = _formulas[_currDepth];
        _t->_antDepth = _antDepth[_currDepth];
      }
    }
  }
  assert(_choices.size() == _order.size());
}
std::vector<Proposition *> DTNext::getItems() {
  std::vector<Proposition *> ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.push_back(*_t->_tokenToProp.at(_tokens[i]));
  }
  return ret;
}
bool DTNext::isMultiDimensional() { return 0; }
bool DTNext::canInsertAtDepth(int depth) {
  if (depth == -1) {
    return (_choices.empty() ? 0 : _currDepth + 1) < _limits._maxDepth;
  } else {
    return (size_t)depth < _limits._maxDepth &&
           (!_choices.count(depth) || _choices.at(depth) == _tc);
  }
}
bool DTNext::isRandomConstructed() { return _limits._isRandomConstructed; }
size_t DTNext::getNChoices() { return _choices.size(); }
bool DTNext::isTaken(size_t id, bool second, int depth) { return false; }
void DTNext::removeLeaf(size_t id, bool second, int depth) {}
void DTNext::addLeaf(Proposition *p, size_t id, bool second, int depth) {}
const DTLimits &DTNext::getLimits() { return _limits; }
size_t DTNext::getCurrentDepth() { return _currDepth; }
std::pair<std::string, std::string> DTNext::prettyPrint(bool offset) {

  std::vector<Hstring> dtOperators =
      _formulas[_currDepth].getAnt().getDTOperands();

  messageErrorIf(dtOperators.empty(), "No operands in dt to pretty print");

  std::vector<Hstring> reducedOperands;
  //the first dto can never change
  reducedOperands.emplace_back(dtOperators.front());

  size_t shift = 0;
  for (size_t i = 1; i < dtOperators.size() - 1; i++) {
    Hstring &dto = dtOperators[i];
    if (dynamic_cast<BooleanConstant *>(*dto._pp) == nullptr) {
      //shifted operand
      dto._offset += shift;
      reducedOperands.emplace_back(dto);
      shift = 0;
    } else {
      //simplify true constant
      shift += dto._offset;
    }
  }
  //handle last dto, unless I've already done that (front, only one element)
  if (dtOperators.size() > 1) {
    auto last = dtOperators.back();
    last._offset += shift;
    reducedOperands.emplace_back(last);
  }

  //prepare the canvas template
  auto reducedTemplateAnt = _formulas[reducedOperands.size() - 1].getAnt();
  auto imp = _formulas[reducedOperands.size() - 1].getImp();
  auto con = _formulas[reducedOperands.size() - 1].getCon();
  size_t rIndex = 0;
  //paint the canvas
  for (auto &e : reducedTemplateAnt) {
    if (Hstring::isDT(e)) {
      e = reducedOperands[rIndex++];
    }
  }

  if (offset) {
    //negate the consequent
    con = Hstring("!(", Hstring::Stype::Temp, nullptr) + con +
          Hstring(")", Hstring::Stype::Temp, nullptr);
  }

  //compose the reduced template
  auto reducedTemplate = Hstring("G(", Hstring::Stype::G) + reducedTemplateAnt +
                         imp + con + Hstring(")", Hstring::Stype::G);

  return std::make_pair(reducedTemplate.toString(1),
                        reducedTemplate.toColoredString(1));
}

std::vector<Proposition *> DTNext::unpack() {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
};
std::vector<Proposition *> DTNext::unpack(Proposition *pack) {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
};
std::vector<Proposition *> DTNext::unpack(std::vector<Proposition *> &pack) {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
}

void DTNext::clearPack(Proposition *pack) {
  messageError("Can't clear pack in unidimensional operator'");
}
bool DTNext::isSolutionInconsequential(std::vector<Proposition *> &sol) {
  if (_applyDynamicShift) {
    return sol.empty() || sol.back() == _tc;
  } else {
    return sol.empty() || sol.front() == _tc;
  }
}
void DTNext::substitute(int depth, int width, Proposition *&sub) {
  if (depth == -1) {
    depth = _currDepth;
  }
  Proposition *tmp = _choices.at(depth);
  _choices.at(depth) = sub;
  (*_t->_tokenToProp.at(_tokens[depth])) = sub;
  sub = tmp;
}
} // namespace harm
