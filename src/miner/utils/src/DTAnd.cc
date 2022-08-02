
#include "DTAnd.hh"
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
//--DTAnd---------------------------------------
DTAnd::DTAnd(PropositionAnd *p, Template *t, const DTLimits &limits)
    : _choices(p), _t(t) {
  _limits = limits;
  _limits._maxDepth = -1;
}

DTAnd::~DTAnd() {
  removeItems();
  delete _choices;
};
bool DTAnd::isMultiDimensional() { return 0; }
size_t DTAnd::getCurrentDepth() { return 0; }
bool DTAnd::canInsertAtDepth(int depth) {
  return _choices->size() < _limits._maxWidth;
}
bool DTAnd::isRandomConstructed() { return false; }
size_t DTAnd::getNChoices() { return _choices->size(); }
bool DTAnd::isTaken(size_t id, bool second, int depth) {
  if (second) {
    return _leaves.count(id) && _leaves.at(id).second != nullptr;
  } else {
    return _leaves.count(id) && _leaves.at(id).first != nullptr;
  }
}
void DTAnd::removeLeaf(size_t id, bool second, int depth) {
  if (second) {
    _leaves.at(id).second = nullptr;
  } else {
    _leaves.at(id).first = nullptr;
  }
}
void DTAnd::addLeaf(Proposition *p, size_t id, bool second, int depth) {
  if (second) {
    _leaves[id].second = p;
  } else {
    _leaves[id].first = p;
  }
}
void DTAnd::removeItems() { _choices->removeItems(); }
void DTAnd::addItem(Proposition *p, int depth) { _choices->addItem(p); }
void DTAnd::popItem(int depth) { _choices->popItem(); }
std::vector<Proposition *> DTAnd::getItems() { return _choices->getItems(); }

std::vector<Proposition *> DTAnd::unpack() {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
};
std::vector<Proposition *> DTAnd::unpack(Proposition *pack) {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
};
std::vector<Proposition *> DTAnd::unpack(std::vector<Proposition *> &pack) {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
}

void DTAnd::clearPack(Proposition *pack) {
  messageError("Can't clear pack in unidimensional operator'");
}
bool DTAnd::isSolutionInconsequential(std::vector<Proposition *> &sol) {
  return 0;
}

void DTAnd::substitute(int depth, int width, Proposition *&sub) {
  if (width == -1) {
    width = _choices->getItems().size() - 1;
  }
  Proposition *tmp = _choices->getItems()[width];
  _choices->getItems()[width] = sub;
  sub = tmp;
}

const DTLimits &DTAnd::getLimits() { return _limits; }

std::vector<Proposition *> DTAnd::minimize(bool isOffset) {
  std::vector<std::vector<size_t>> c;
  std::vector<Proposition *> original = _choices->getItems();
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
  std::vector<Proposition *> ret;
  for (auto p : _choices->getItems()) {
    ret.push_back(p);
  }
  _choices->removeItems();
  for (auto p : original) {
    _choices->addItem(p);
  }

  sortPropositions(ret);
  return ret;
}

std::pair<std::string, std::string> DTAnd::prettyPrint(bool offset) {

  auto ant = _t->_templateFormula.getAnt();
  auto imp = _t->_templateFormula.getImp();
  auto con = _t->_templateFormula.getCon();

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
} // namespace harm
