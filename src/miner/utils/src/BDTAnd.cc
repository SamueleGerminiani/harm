
#include "BDTAnd.hh"
#include "BDTUtils.hh"
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
//--BDTAnd---------------------------------------
BDTAnd::BDTAnd(PropositionAnd *p, Template *t, const BDTLimits &limits)
    : _choices(p), _t(t) {
  _limits = limits;
  _limits._maxDepth = -1;
}

BDTAnd::~BDTAnd() {
  removeItems();
  delete _choices;
};
bool BDTAnd::isMultiDimensional() { return 0; }
size_t BDTAnd::getCurrentDepth() { return 0; }
bool BDTAnd::canInsertAtDepth(int depth) {
  return _choices->size() < _limits._maxWidth;
}
bool BDTAnd::isRandomConstructed() { return false; }
size_t BDTAnd::getNChoices() { return _choices->size(); }
bool BDTAnd::isTaken(size_t id, bool second, int depth) {
  if (second) {
    return _leaves.count(id) && _leaves.at(id).second != nullptr;
  } else {
    return _leaves.count(id) && _leaves.at(id).first != nullptr;
  }
}
void BDTAnd::removeLeaf(size_t id, bool second, int depth) {
  if (second) {
    _leaves.at(id).second = nullptr;
  } else {
    _leaves.at(id).first = nullptr;
  }
}
void BDTAnd::addLeaf(Proposition *p, size_t id, bool second, int depth) {
  if (second) {
    _leaves[id].second = p;
  } else {
    _leaves[id].first = p;
  }
}
void BDTAnd::removeItems() { _choices->removeItems(); }
void BDTAnd::addItem(Proposition *p, int depth) { _choices->addItem(p); }
void BDTAnd::popItem(int depth) { _choices->popItem(); }
std::vector<Proposition *> BDTAnd::getItems() { return _choices->getItems(); }

std::vector<Proposition *> BDTAnd::unpack() {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
};
std::vector<Proposition *> BDTAnd::unpack(Proposition *pack) {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
};
std::vector<Proposition *> BDTAnd::unpack(std::vector<Proposition *> &pack) {
  messageError("Can't unpack in unidimensional operator'");
  return std::vector<Proposition *>();
}

void BDTAnd::clearPack(Proposition *pack) {
  messageError("Can't clear pack in unidimensional operator'");
}
bool BDTAnd::isSolutionInconsequential(std::vector<Proposition *> &sol) {
  return 0;
}

const BDTLimits &BDTAnd::getLimits() { return _limits; }

std::vector<Proposition *> BDTAnd::minimize(bool isOffset) {
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

std::pair<std::string, std::string> BDTAnd::prettyPrint(bool offset) {
  auto modTemplate = _t->_templateFormula;
  if (offset) {
    for (int j = modTemplate.size() - 1; j >= 0; j--) {
      if (modTemplate[j]._t == Hstring::Stype::Imp) {
        modTemplate.insert(modTemplate.begin() + j + 1,
                           Hstring("!(", Hstring::Stype::Temp, nullptr));
        modTemplate.insert(modTemplate.end() - 1,
                           Hstring(")", Hstring::Stype::Temp, nullptr));
        break;
      }
    }
  }
  auto ret =
      std::make_pair(modTemplate.toString(1), modTemplate.toColoredString(1));
  return ret;
}
} // namespace harm
