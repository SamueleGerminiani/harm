#include "DTNCReps.hh"
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
//--DTNCReps---------------------------------------

DTNCReps::DTNCReps(BooleanConstant *p, size_t shift, Template *t,
                   const DTLimits &limits)
    : _t(t), _shift(shift), _tc(p) {

  _limits = limits;
  _limits._maxWidth = -1;
  // The base case automata were already generated in the template
  _tokens.push_back("dtNCReps0");
  _ant.push_back(_t->_ant);
  // storing depths
  _antDepth.push_back(_t->getDepth(_ant.back()));

  for (size_t j = 0; j < t->_templateFormula.size(); j++) {
    if (t->_templateFormula[j]._t == Hstring::Stype::DTNCReps) {
      t->_templateFormula[j]._offset = -1 * _shift;
    }
  }
  _formulas.push_back(t->_templateFormula);

  if (_t->_applyDynamicShift) {
    _applyDynamicShift = true;
    messageErrorIf(
        !nothingBefore(
            _tokens.back(),
            spot::parse_infix_psl(_t->_templateFormula.getAnt().toSpotString())
                .f),
        "Can't have events happening before the dt operator when using "
        "|-> ");
  } else {
    messageErrorIf(
        !nothingAfter(
            "dtMock",
            spot::parse_infix_psl(_t->_templateFormula.getAnt().toSpotString())
                .f),
        "Can't have events happening after the dt operator when not using "
        "|-> ");
  }

  //  messageInfo("Building automata...");
  generateFormulas();
  handleParallelDepth();
}

void DTNCReps::generateFormulas() {
  // retrieve the consequent and the implication of the formula
  auto hcon = _t->_templateFormula.getCon();

  for (size_t i = 1; i < _limits._maxDepth; i++) {
    // we build on the previously generated antecedent
    auto hant = _formulas[i - 1].getAnt();
    Proposition **pp = new Proposition *(nullptr);
    std::string token = "dtNCReps" + std::to_string(i);
    // the relation between token name and proposition is kept in the template
    _t->_tokenToProp[token] = pp;
    _tokens.push_back(token);

    if (_t->_applyDynamicShift) {
      // dtNextM ##N ... ##N dtNext2 ##N dtNext0
      //find the last operand and append a new one
      auto dth = std::find_if(
          std::begin(hant), std::end(hant),
          [](Hstring &e) { return e._t == Hstring::Stype::DTNCReps; }

      );

      messageErrorIf(dth == hant.end(), "Could not find the operand");
      dth->_offset = _shift;
      hant.insert(dth, Hstring(token, Hstring::Stype::DTNCReps, pp));
    } else {
      // dtNext0 ##N dtNext1 ##N ... ##N dtNextM
      // find the last operand and append a new one
      auto dth = std::find_if(
          std::rbegin(hant), std::rend(hant),
          [](Hstring &e) { return e._t == Hstring::Stype::DTNCReps; }

      );

      messageErrorIf(dth == hant.rend(), "Could not find the operand");
      auto newOperand = Hstring(token, Hstring::Stype::DTNCReps, pp);
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
    _ant.push_back(buildAutomaton(antAutomaton, _t->_tokenToProp));

    // storing depths
    _antDepth.push_back(_t->getDepth(_ant.back()));
  }
}
void DTNCReps::handleParallelDepth() {
  if (_t->_applyDynamicShift) {
    if (onlyToken(
            "dtNCReps0",
            selectFirstEvent(
                spot::parse_infix_psl(_formulas.front().getAnt().toSpotString())
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
      Automaton *pAnt = buildAutomaton(aut, _t->_tokenToProp);
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
      messageError(" parallel depth is not allowed");
    }
  }
}
DTNCReps::~DTNCReps() {
  for (size_t i = 0; i < _tokens.size(); i++) {
    delete _ant[i];
  }
  delete _tc;
}

std::vector<Proposition *> DTNCReps::minimize(bool isOffset) {

  std::vector<std::vector<size_t>> c;
  std::vector<Proposition *> propList;
  for (size_t i = 0; i <= _currDepth; i++) {
    propList.emplace_back((*_t->_tokenToProp.at(_tokens[i])));
  }
  std::vector<std::pair<Proposition *, size_t>> originalChoices;
  for (auto i : _order) {
    originalChoices.emplace_back(_choices.at(i), i);
  }

  for (size_t i = 1; i <= propList.size(); i++) {
    // clear the current combinations
    c.clear();
    // generate combinations for size i
    comb(propList.size(), i, c);
    // find a combination that satisfies the assertion
    for (auto &comb : c) {
      // load the combination
      std::vector<size_t> reduced = comb;
      std::sort(reduced.begin(), reduced.end());
      removeItems();
      for (size_t j = 0; j < reduced.size(); j++) {
        addItem(propList[reduced[j]], -1);
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
  std::vector<Proposition *> ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.push_back(*_t->_tokenToProp.at(_tokens[i]));
  }
  removeItems();
  for (auto &p_d : originalChoices) {
    addItem(p_d.first, p_d.second);
  }
  return ret;
}
void DTNCReps::removeItems() {

  _t->_ant = _ant[0];
  _t->_templateFormula = _formulas[0];
  _t->_antDepth = _antDepth[0];
  (*_t->_tokenToProp[_tokens[0]]) = _tc;
  _choices.clear();
  _order.clear();
  _currDepth = 0;
}
void DTNCReps::popItem(int depth) {
  if (depth == -1) {
    depth = _currDepth;
  }
  assert(_order.back() == depth);
  (*_t->_tokenToProp[_tokens[depth]]) = _tc;
  if ((size_t)depth == _currDepth) {
    while (_currDepth > 0 &&
           (*_t->_tokenToProp.at(_tokens[_currDepth])) == _tc) {
      _currDepth--;
    }
  }
  _t->_ant = _ant[_currDepth];
  _t->_templateFormula = _formulas[_currDepth];
  _t->_antDepth = _antDepth[_currDepth];

  _choices.erase(depth);
  _order.pop_back();
  assert(_choices.size() == _order.size());
}
void DTNCReps::addItem(Proposition *p, int depth) {

  if (depth == -1) {
    if (!_choices.empty()) {
      _currDepth++;
    }
    (*_t->_tokenToProp.at(_tokens[_currDepth])) = p;
    _t->_ant = _ant[_currDepth];
    _t->_templateFormula = _formulas[_currDepth];
    _t->_antDepth = _antDepth[_currDepth];
    _choices[_currDepth] = p;
    _order.push_back(_currDepth);
  } else {
    _order.push_back(depth);
    if (_parallelDepth) {
      (*_t->_tokenToProp.at(_tokens[depth])) = p;
      _choices[depth] = p;
    } else {
      (*_t->_tokenToProp.at(_tokens[depth])) = p;
      _choices[depth] = p;
      if ((size_t)depth > _currDepth) {
        // fill gap with tc
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
std::vector<Proposition *> DTNCReps::getItems() {
  std::vector<Proposition *> ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.push_back(*_t->_tokenToProp.at(_tokens[i]));
  }
  return ret;
}
bool DTNCReps::isMultiDimensional() { return 0; }
bool DTNCReps::canInsertAtDepth(int depth) {
  if (depth == -1) {
    return (_choices.empty() ? 0 : _currDepth + 1) < _limits._maxDepth;
  } else {
    return (size_t)depth < _limits._maxDepth &&
           (!_choices.count(depth) || _choices.at(depth) == _tc);
  }
}
bool DTNCReps::isRandomConstructed() { return _limits._isRandomConstructed; }
size_t DTNCReps::getNChoices() { return _choices.size(); }
bool DTNCReps::isTaken(size_t id, bool second, int depth) { return false; }
void DTNCReps::removeLeaf(size_t id, bool second, int depth) {}
void DTNCReps::addLeaf(Proposition *p, size_t id, bool second, int depth) {}
const DTLimits &DTNCReps::getLimits() { return _limits; }
size_t DTNCReps::getCurrentDepth() { return _currDepth; }
std::pair<std::string, std::string> DTNCReps::prettyPrint(bool offset) {

  auto ant = _formulas[_currDepth].getAnt();
  auto imp = _formulas[_currDepth].getImp();
  auto con = _formulas[_currDepth].getCon();

  if (offset) {
    //negate the consequent
    con = Hstring("!(", Hstring::Stype::Temp, nullptr) + con +
          Hstring(")", Hstring::Stype::Temp, nullptr);
  }

  //compose the reduced template
  auto reducedTemplate = Hstring("G(", Hstring::Stype::G) + ant + imp + con +
                         Hstring(")", Hstring::Stype::G);
  return std::make_pair(reducedTemplate.toString(1),
                        reducedTemplate.toColoredString(1));
}

std::vector<Proposition *> DTNCReps::unpack() {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
};
std::vector<Proposition *> DTNCReps::unpack(Proposition *pack) {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
};
std::vector<Proposition *> DTNCReps::unpack(std::vector<Proposition *> &pack) {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
}

void DTNCReps::clearPack(Proposition *pack) {
  messageError("Can't clear pack in unidimensional operator'");
}
bool DTNCReps::isSolutionInconsequential(std::vector<Proposition *> &sol) {
  if (_applyDynamicShift) {
    return sol.empty() || sol.back() == _tc;
  } else {
    return sol.empty() || sol.front() == _tc;
  }
}
void DTNCReps::substitute(int depth, int width, Proposition *&sub) {
  if (depth == -1) {
    depth = _currDepth;
  }
  Proposition *tmp = _choices.at(depth);
  _choices.at(depth) = sub;
  (*_t->_tokenToProp.at(_tokens[depth])) = sub;
  sub = tmp;
}
} // namespace harm
