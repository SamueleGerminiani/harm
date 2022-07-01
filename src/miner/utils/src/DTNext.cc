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
        "|-> ");
  } else {
    messageErrorIf(
        !nothingAfter(
            _tokens.back(),
            spot::parse_infix_psl(_t->_templateFormula.getAnt().toSpotString())
                .f),
        "Can't have events happening after the dtNext operator when not using "
        "|-> ");
  }

  //  debug
  //  messageInfo("Building automata...");

  // retrieve the consequent and the implication of the formula
  std::string imp = t->_templateFormula.getImp()._s;
  auto hcon = t->_templateFormula.getCon();
  // remove unwanted spaces in the string representation of the implication
  imp.erase(remove_if(imp.begin(), imp.end(), isspace), imp.end());

  // generate the rest of the automata
  for (size_t i = 1; i < _limits._maxDepth; i++) {
    // we build on the previous antecedent
    auto hant = _formulas[i - 1].getAnt();

    if (_t->_applyDynamicShift) {
      // dtNextM ##N dtNextM-1 ##N ... ##N dtNext0
      // last insertion point
      size_t lastIP = -1;
      // find the last operand and append a new one
      for (size_t j = 0; j < hant.size(); j++) {
        if (hant[j]._t == Hstring::Stype::DTNext) {
          Proposition **pp = new Proposition *(nullptr);
          std::string token = "dtNext" + std::to_string(i);
          hant.insert(hant.begin() + j,
                      Hstring(token, Hstring::Stype::DTNext, pp));
          hant[j]._offset = _shift;
          // the relation between token name and proposition is kept in the
          // template
          _t->_tokenToProp[token] = pp;
          _tokens.push_back(token);
          lastIP = j;
          break;
        }
      }
      // adjust offset: only the last operand should have delay equal to 0
      hant[lastIP]._offset = 0;
      for (size_t j = lastIP + 1; j < hant.size(); j++) {
        if (hant[j]._t == Hstring::Stype::DTNext) {
          hant[j]._offset = _shift;
        }
      }
    } else {

      // dtNext1 ##N dtNext2 ##N ... ##N dtNextM
      // find the last operand and append a new one
      for (int j = hant.size() - 1; j >= 0; j--) {
        if (hant[j]._t == Hstring::Stype::DTNext) {
          Proposition **pp = new Proposition *(nullptr);
          std::string token = "dtNext" + std::to_string(i);
          hant.insert(hant.begin() + j + 1,
                      Hstring(token, Hstring::Stype::DTNext, pp));
          hant[j]._offset = _shift;
          // the relation between token name and proposition is kept in the
          // template
          _t->_tokenToProp[token] = pp;
          _tokens.push_back(token);
          break;
        }
      }
      // adjust offset: only the first operand should have delay equal to 0
      size_t firstDT = 0;
      for (size_t j = 0; j < hant.size(); j++) {
        if (hant[j]._t == Hstring::Stype::DTNext) {
          firstDT = j;
          break;
        }
      }
      hant[firstDT]._offset = 0;
      for (size_t j = firstDT + 1; j < hant.size(); j++) {
        if (hant[j]._t == Hstring::Stype::DTNext) {
          hant[j]._offset = _shift;
        }
      }
    }

    _formulas.push_back(Hstring("G(", Hstring::Stype::G) + hant +
                        Hstring(" " + imp + " ", Hstring::Stype::Imp) + hcon +
                        Hstring(")", Hstring::Stype::G));

    // string to spot formula
    spot::parsed_formula ant = spot::parse_infix_psl(hant.toSpotString());

    // Synthesising the automata
    auto antAutomaton = t->generateDeterministicSpotAutomaton(ant.f);

    // building storing our custom automata
    _ant.push_back(_t->buildAutomaton(antAutomaton));

    // storing depths
    _antDepth.push_back(_t->getDepth(_ant.back()));
  }
  //  for (auto &f : _formulas) {
  //    std::cout << f.toSpotString() << "\n";
  //  }

  //   Check for parallel depth
  if (_t->_applyDynamicShift) {
    int baseDepth = -1;
    for (auto f : _formulas) {
      auto portionBare =
          selectFirstEvent(spot::parse_infix_psl(f.getAnt().toSpotString()).f);
      std::stringstream ss;
      print_spin_ltl(ss, portionBare, false) << '\n';
      std::string portion = "{" + ss.str() + "}";
      auto portionFormula = spot::parse_infix_psl(portion);
      //      debug
      //      print_spin_ltl(std::cout, portionFormula.f, false) << '\n';
      auto antAutomaton =
          t->generateDeterministicSpotAutomaton(portionFormula.f);
      Automaton *pAnt = _t->buildAutomaton(antAutomaton);
      int depth = _t->getDepth(pAnt);

      messageErrorIf(depth == -1, " parallel depth is unknown");
      baseDepth = (baseDepth == -1 ? depth : baseDepth);
      if (depth == 0) {
        if (!onlyToken("dtNext0", portionFormula.f)) {
          _parallelDepth++;
        }
        delete pAnt;
        break;
      } else if (baseDepth == depth) {
        _parallelDepth++;
      }
      delete pAnt;
    }
  }
  if (_parallelDepth != 0) {
    _limits._maxDepth =
        _parallelDepth < _limits._maxDepth ? _parallelDepth : _limits._maxDepth;
    _t->_ant = _ant[_limits._maxDepth - 1];
    _t->_templateFormula = _formulas[_limits._maxDepth - 1];
    _t->_antDepth = _antDepth[_limits._maxDepth - 1];
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
    if (depth == _currDepth) {
      while (_currDepth > 0 &&
             (*_t->_tokenToProp.at(_tokens[_currDepth])) == _tc) {
        _currDepth--;
      }
    }
    _t->_ant = _ant[_currDepth];
    _t->_templateFormula = _formulas[_currDepth];
    _t->_antDepth = _antDepth[_currDepth];
  }

  _choices.erase(depth);
  _order.pop_back();
  assert(_choices.size() == _order.size());
}
void DTNext::addItem(Proposition *p, int depth) {

  if (depth == -1) {
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
    _order.push_back(depth);
    if (_parallelDepth) {
      (*_t->_tokenToProp.at(_tokens[depth])) = p;
      _choices[depth] = p;
    } else {
      (*_t->_tokenToProp.at(_tokens[depth])) = p;
      _choices[depth] = p;
      if (depth > _currDepth) {
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
    return depth < _limits._maxDepth &&
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

  std::vector<Proposition *> original;
  for (size_t i = 0; i <= _currDepth; i++) {
    original.emplace_back(*_t->_tokenToProp.at(_tokens[i]));
  }
  auto solTemplate = _formulas[_currDepth];

  size_t dtIndex = _t->_applyDynamicShift ? 0 : _currDepth;
  size_t comulativeShift = 0;
  size_t lastCandidate = 0;
  std::unordered_set<size_t> toDelete;
  std::map<size_t, std::pair<Proposition *, size_t>> toUpdate;

  // slide bw
  for (int j = solTemplate.size() - 1; j >= 0; j--) {
    if (solTemplate[j]._t == Hstring::Stype::DTNext) {
      Proposition *p = *_t->_tokenToProp.at(_tokens[dtIndex]);
      // base case
      if (_t->_applyDynamicShift ? (dtIndex == 0) : (dtIndex == _currDepth)) {
        toUpdate.insert(
            {{dtIndex, std::pair(p, _currDepth == 0 ? 0 : _shift)}});
        lastCandidate = dtIndex;
        dtIndex = _t->_applyDynamicShift ? dtIndex + 1 : dtIndex - 1;
        continue;
      }
      if ((dtIndex <= _currDepth) &&
          dynamic_cast<BooleanConstant *>(p) != nullptr) {
        comulativeShift += _shift;
        toDelete.insert(dtIndex);
        //                          std::cout << "toD:" << prop2String(*p) <<
        //                          "\n";
      } else {
        toUpdate.at(lastCandidate).second += comulativeShift;
        //                   std::cout << "toU:" <<
        //                   prop2String(*toUpdate.at(lastCandidate).first) <<
        //                   "," << toUpdate.at(lastCandidate).second << "\n";
        lastCandidate = dtIndex;
        toUpdate.insert({{dtIndex, std::pair(p, solTemplate[j]._offset)}});
        comulativeShift = 0;
      }
      dtIndex = _t->_applyDynamicShift ? dtIndex + 1 : dtIndex - 1;
    }
  }
  if (toDelete.count(_t->_applyDynamicShift ? dtIndex - 1 : dtIndex + 1)) {
    toUpdate.at(lastCandidate).second += (comulativeShift - _shift);
  }

  //       std::cout << "-------toU:" <<
  //       prop2String(*toUpdate.at(lastCandidate).first) << "," <<
  //       toUpdate.at(lastCandidate).second << "\n";

  auto reducedTemplate = _formulas[_currDepth - toDelete.size()];

  for (int j = reducedTemplate.size() - 1; j >= 0; j--) {
    if (reducedTemplate[j]._t == Hstring::Stype::DTNext) {
      size_t adjustedIndex = _t->_applyDynamicShift ? toUpdate.begin()->first
                                                    : toUpdate.rbegin()->first;
      reducedTemplate[j]._offset = toUpdate.at(adjustedIndex).second;
      (*reducedTemplate[j]._pp) = toUpdate.at(adjustedIndex).first;
      toUpdate.erase(adjustedIndex);
    }
  }

  if (offset) {
    for (int j = reducedTemplate.size() - 1; j >= 0; j--) {
      if (reducedTemplate[j]._t == Hstring::Stype::Imp) {
        reducedTemplate.insert(reducedTemplate.begin() + j + 1,
                               Hstring("!(", Hstring::Stype::Temp, nullptr));
        reducedTemplate.insert(reducedTemplate.end() - 1,
                               Hstring(")", Hstring::Stype::Temp, nullptr));
        break;
      }
    }
  }
  auto ret = std::make_pair(reducedTemplate.toString(1),
                            reducedTemplate.toColoredString(1));

  for (size_t i = 0; i < original.size(); i++) {
    (*_t->_tokenToProp.at(_tokens[i])) = original[i];
  }
  return ret;
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
