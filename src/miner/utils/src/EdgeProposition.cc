#include "EdgeProposition.hh"
#include "expUtils/expUtils.hh"

namespace harm {

EdgeAnd::EdgeAnd(EdgeProposition *p1, EdgeProposition *p2)
    : EdgeProposition() {
  _operands.push_back(p1);
  _operands.push_back(p2);
}
EdgeAnd::EdgeAnd(std::vector<EdgeProposition *> pp)
    : EdgeProposition() {
  for (auto &p : pp) {
    _operands.push_back(p);
  }
}
EdgeAnd::~EdgeAnd() {
  for (auto e : _operands) {
    delete e;
  }
}
bool EdgeAnd::evaluate(size_t time) {
  for (size_t i = 0; i < _operands.size(); i++) {
    if (!_operands[i]->evaluate(time)) {
      return false;
    }
  }
  return true;
}
std::string EdgeAnd::toString() {
  std::string ret = _operands[0]->toString();
  for (size_t i = 1; i < _operands.size(); i++) {
    ret += " && " + _operands[i]->toString();
  }
  return ret;
}
EdgeOr::EdgeOr(EdgeProposition *p1, EdgeProposition *p2)
    : EdgeProposition() {
  _operands.push_back(p1);
  _operands.push_back(p2);
}
EdgeOr::EdgeOr(std::vector<EdgeProposition *> pp)
    : EdgeProposition() {
  for (auto &p : pp) {
    _operands.push_back(p);
  }
}
EdgeOr::~EdgeOr() {
  for (auto e : _operands) {
    delete e;
  }
}
bool EdgeOr::evaluate(size_t time) {
  for (size_t i = 0; i < _operands.size(); i++) {
    if (_operands[i]->evaluate(time)) {
      return true;
    }
  }
  return false;
}
std::string EdgeOr::toString() {
  std::string ret = _operands[0]->toString();
  for (size_t i = 1; i < _operands.size(); i++) {
    ret += " || " + _operands[i]->toString();
  }
  return ret;
}
EdgeNot::EdgeNot(EdgeProposition *p) : EdgeProposition() {
  _operands.push_back(p);
}

EdgeNot::~EdgeNot() { delete _operands[0]; }

bool EdgeNot::evaluate(size_t time) {
  return !_operands[0]->evaluate(time);
}

std::string EdgeNot::toString() {
  return "!(" + _operands[0]->toString() + ")";
}
bool EdgeTrue::evaluate(size_t time) { return true; }

std::string EdgeTrue::toString() { return "true"; }

bool EdgeFalse::evaluate(size_t time) { return false; }

std::string EdgeFalse::toString() { return "false"; }

EdgePlaceholder::EdgePlaceholder(
    const expression::PropositionPtrPtr &toProp,
    const std::string &phName)
    : EdgeProposition(), _toProp(toProp), _phName(phName) {}
bool EdgePlaceholder::evaluate(size_t time) {
  assert(_toProp != nullptr && "placeholder is nullptr");
  assert(*_toProp != nullptr && "prop is nullptr");
  return (*_toProp)->evaluate(time);
}
std::string EdgePlaceholder::toString() {
  if (*_toProp == nullptr) {
    return _phName;
  }
  return prop2String(*_toProp);
}

EdgeInst::EdgeInst(const expression::PropositionPtr &toInst,
                   const std::string &phName)
    : EdgeProposition(), _toInst(toInst), _phName(phName) {}
bool EdgeInst::evaluate(size_t time) {
  return _toInst->evaluate(time);
}
std::string EdgeInst::toString() {
  if (_toInst == nullptr) {
    return _phName;
  }
  return prop2String(_toInst);
}
} // namespace harm
