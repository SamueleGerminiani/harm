#include "DTNextAnd.hh"
#include "DTUtils.hh"
#include "Template.hh"
#include "message.hh"
#include "minerUtils.hh"
#include <spot/tl/formula.hh>
#include <spot/twaalgos/postproc.hh>
#include <string>
#include <unordered_set>
#include <utility>

namespace harm {
//--DTNextAnd---------------------------------------

DTNextAnd::DTNextAnd(size_t shift, Template *t, const DTLimits &limits)
    : _t(t), _shift(shift) {

  _limits = limits;
  _tc = new BooleanConstant(true, VarType::Bool, 1, t->_max_length);
  // The base case automata were already generated in the template
  _tokens.push_back("dtNextAnd0");
  _leaves.emplace_back();
  _op.push_back(
      dynamic_cast<PropositionAnd *>(*_t->_tokenToProp.at("dtNextAnd0")));
  _ant.push_back(_t->_ant);
  // storing depths
  _antDepth.push_back(_t->getDepth(_ant.back()));

  // adjust offset:  we shouldn't have any delaying when we have only one
  // operand
  for (auto &e : t->_templateFormula)
    e._offset = (e._t == Hstring::Stype::DTNextAnd ? 0 : e._offset);

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

  // generate the rest of the automata
  generateFormulas();

  //  debug
  //  for (auto &e : _formulas) {
  //    std::cout << e.toSpotString() << "\n";
  //  }

  //   Check for parallel depth
  handleParallelDepth();
}

void DTNextAnd::generateFormulas() {
  // retrieve the consequent and the implication of the formula
  // remove unwanted spaces in the string representation of the implication
  auto hcon = _t->_templateFormula.getCon();

  // generate the rest of the automata
  for (size_t i = 1; i < _limits._maxDepth; i++) {
    // we build on the previous automa
    auto hant = _formulas[i - 1].getAnt();
    Proposition **pp = new Proposition *(makeExpression<PropositionAnd>());
    std::string token = "dtNextAnd" + std::to_string(i);
    _t->_tokenToProp[token] = pp;
    _tokens.push_back(token);
    _leaves.emplace_back();
    _op.push_back(dynamic_cast<PropositionAnd *>(*pp));

    if (_t->_applyDynamicShift) {
      // dtNextM ##N dtNextM-1 ##N ... ##N dtNext0
      // last insertion point
      auto dth = std::find_if(
          std::begin(hant), std::end(hant),
          [](Hstring &e) { return e._t == Hstring::Stype::DTNextAnd; }

      );

      messageErrorIf(dth == hant.end(), "Could not find the operand");
      dth->_offset = _shift;
      hant.insert(dth, Hstring(token, Hstring::Stype::DTNextAnd, pp));
    } else {
      // dtNext1 ##N dtNext2 ##N ... ##N dtNextM
      // find the last operand and append a new one
      auto dth = std::find_if(
          std::rbegin(hant), std::rend(hant),
          [](Hstring &e) { return e._t == Hstring::Stype::DTNextAnd; }

      );

      messageErrorIf(dth == hant.rend(), "Could not find the operand");
      auto newOperand = Hstring(token, Hstring::Stype::DTNextAnd, pp);
      newOperand._offset = _shift;
      hant.insert(++((dth + 1).base()), newOperand);
    }

    Hstring imp = _t->_templateFormula.getImp();
    _formulas.push_back(Hstring("G(", Hstring::Stype::G) + hant + imp + hcon +
                        Hstring(")", Hstring::Stype::G));

    // string to spot formula
    spot::parsed_formula ant = spot::parse_infix_psl(hant.toSpotString());

    auto antAutomaton = _t->generateDeterministicSpotAutomaton(ant.f);

    // building storing our custom automata
    _ant.push_back(_t->buildAutomaton(antAutomaton));

    // storing depths
    _antDepth.push_back(_t->getDepth(_ant.back()));

    //    std::cout << _formulas.back().toSpotString() << "\n";
  }
}
void DTNextAnd::handleParallelDepth() {

  if (_t->_applyDynamicShift) {
    if (onlyToken(
            "dtNextAnd0",
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
      auto aut = _t->generateDeterministicSpotAutomaton(portionFormula.f);
      Automaton *pAnt = _t->buildAutomaton(aut);
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
DTNextAnd::~DTNextAnd() {
  for (size_t i = 0; i < _tokens.size(); i++) {
    delete _ant[i];
  }
  for (size_t i = 0; i < _tokens.size(); i++) {
    _op[i]->removeItems();
    delete _op[i];
  }
  delete _tc;
}
std::vector<Proposition *> DTNextAnd::minimize(bool isOffset) {
  std::vector<std::pair<Proposition *, size_t>> propList;

  for (size_t i = 0; i <= _currDepth; i++) {
    for (auto &p : _op[i]->getItems()) {
      propList.emplace_back(p, i);
    }
  }

  // keep track of the original choices
  std::vector<std::pair<Proposition *, size_t>> originalChoices;
  std::unordered_map<size_t, size_t> orderToShift;
  for (auto o : _order) {
    originalChoices.emplace_back(_choices.at(o)[orderToShift[o]++], o);
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
        _op[j]->removeItems();
      }

      // load the combination
      for (auto &e : comb) {
        _op[propList[e].second]->addItem(propList[e].first);
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
    PropositionAnd *andP = _op[i];
    std::vector<Proposition *> tmp;
    for (auto &e : andP->getItems()) {
      tmp.push_back(e);
    }
    sortPropositions(tmp);
    PropositionAnd *tmp1 = makeExpression<PropositionAnd>();
    for (auto &e : tmp) {
      tmp1->addItem(e);
    }
    ret.push_back(tmp1);
  }

  // restore
  removeItems();
  for (auto p_d : originalChoices) {
    addItem(p_d.first, p_d.second);
  }

  return ret;
}
void DTNextAnd::removeItems() {

  if (_parallelDepth) {
    for (size_t i = 0; i <= _currDepth; i++) {
      _op[i]->removeItems();
    }
  } else {
    for (size_t i = 0; i <= _currDepth; i++) {
      _op[i]->removeItems();
    }
    _t->_ant = _ant[0];
    _t->_templateFormula = _formulas[0];
    _t->_antDepth = _antDepth[0];
  }
  _choices.clear();
  _order.clear();
  _currDepth = 0;
}
void DTNextAnd::popItem(int depth) {
    messageErrorIf(depth==-1, "You must always specify the depth when popping from a multidimensional operator");
  if (_parallelDepth) {
    _op[depth]->popItem();
  } else {
    _op[depth]->popItem();
    if ((size_t)depth == _currDepth) {
      while (_currDepth > 0 && _op[_currDepth]->empty()) {
        _currDepth--;
      }
    }
    _t->_ant = _ant[_currDepth];
    _t->_templateFormula = _formulas[_currDepth];
    _t->_antDepth = _antDepth[_currDepth];
  }

  assert(!_choices.at(depth).empty());
  _choices.at(depth).pop_back();
  _order.pop_back();
  assert(std::accumulate(_choices.begin(), _choices.end(), 0ul,
                         [](size_t &a, auto &e) {
                           return a + e.second.size();
                         }) == _order.size());
}
void DTNextAnd::addItem(Proposition *p, int depth) {

    messageErrorIf(depth==-1, "You must always specify the depth when inserting in a multidimensional operator");
  _order.push_back(depth);
  if (_parallelDepth) {
    _op[depth]->addItem(p);
    _choices[depth].push_back(p);
  } else {
    _op[depth]->addItem(p);
    _choices[depth].push_back(p);
    if ((size_t)depth > _currDepth) {
      _currDepth = depth;
      _t->_ant = _ant[_currDepth];
      _t->_templateFormula = _formulas[_currDepth];
      _t->_antDepth = _antDepth[_currDepth];
    }
  }
  assert(std::accumulate(_choices.begin(), _choices.end(), 0ul,
                         [](size_t &a, auto &e) {
                           return a + e.second.size();
                         }) == _order.size());
}
std::vector<Proposition *> DTNextAnd::getItems() {
  std::vector<Proposition *> ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.push_back(_op[i]);
  }
  return ret;
}
bool DTNextAnd::isMultiDimensional() { return 1; }
bool DTNextAnd::canInsertAtDepth(int depth) {
    messageErrorIf(depth==-1, "You must always specify the depth when dealing with a multidimensional operator");
  return (_choices[depth].size() < _limits._maxWidth &&
          (size_t)depth < _limits._maxDepth);
}
bool DTNextAnd::isRandomConstructed() { return _limits._isRandomConstructed; }
size_t DTNextAnd::getNChoices() { return _order.size(); }
bool DTNextAnd::isTaken(size_t id, bool second, int depth) {
    messageErrorIf(depth==-1, "You must always specify the depth when dealing with a multidimensional operator");
  if (second) {
    return _leaves[depth].count(id) && _leaves[depth].at(id).second != nullptr;
  } else {
    return _leaves[depth].count(id) && _leaves[depth].at(id).first != nullptr;
  }
}
void DTNextAnd::removeLeaf(size_t id, bool second, int depth) {
    messageErrorIf(depth==-1, "You must always specify the depth when dealing with a multidimensional operator");
  if (second) {
    _leaves[depth].at(id).second = nullptr;
  } else {
    _leaves[depth].at(id).first = nullptr;
  }
}
void DTNextAnd::addLeaf(Proposition *p, size_t id, bool second, int depth) {
    messageErrorIf(depth==-1, "You must always specify the depth when dealing with a multidimensional operator");
  if (second) {
    _leaves[depth][id].second = p;
  } else {
    _leaves[depth][id].first = p;
  }
}
const DTLimits &DTNextAnd::getLimits() { return _limits; }
size_t DTNextAnd::getCurrentDepth() { return _currDepth; }

void DTNextAnd::clearPack(Proposition *pack) {
  dynamic_cast<PropositionAnd *>(pack)->removeItems();
}
std::vector<Proposition *> DTNextAnd::unpack() {
  std::vector<Proposition *> ret;
  for (auto &pack : getItems()) {
    std::vector<Proposition *> sorted = unpack(pack);
    ret.insert(end(ret), begin(sorted), end(sorted));
  }
  return ret;
}
std::vector<Proposition *> DTNextAnd::unpack(Proposition *pack) {
  std::vector<Proposition *> ret;
  if (dynamic_cast<PropositionAnd *>(pack)->empty()) {
    ret.push_back(_tc);
  } else {
    for (auto &item : dynamic_cast<PropositionAnd *>(pack)->getItems()) {
      ret.push_back(item);
    }
  }
  sortPropositions(ret);

  return ret;
}
std::vector<Proposition *> DTNextAnd::unpack(std::vector<Proposition *> &pack) {
  std::vector<Proposition *> ret;
  for (auto &p : pack) {
    std::vector<Proposition *> sorted = unpack(p);
    ret.insert(end(ret), begin(sorted), end(sorted));
  }
  return ret;
}

std::pair<std::string, std::string> DTNextAnd::prettyPrint(bool offset) {

  std::vector<Hstring> dtOperators =
      _formulas[_currDepth].getAnt().getDTOperands();

  messageErrorIf(dtOperators.empty(), "No operands in dt to pretty print");

  std::vector<Hstring> reducedOperands;
  //the first dto can never change
  reducedOperands.emplace_back(dtOperators.front());

  size_t shift = 0;
  for (size_t i = 1; i < dtOperators.size() - 1; i++) {
    Hstring &dto = dtOperators[i];
    if (dynamic_cast<PropositionAnd *>(*dto._pp)->empty()) {
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
void DTNextAnd::substitute(int depth, int width, Proposition *&sub) {
  if (depth == -1) {
    depth = _currDepth;
  }
  if (width == -1) {
    width = _choices.at(depth).size() - 1;
  }
  Proposition *tmp = _choices.at(depth)[width];
  _choices.at(depth)[width] = sub;
  _op[depth]->getItems()[width] = sub;
  sub = tmp;
}

} // namespace harm
