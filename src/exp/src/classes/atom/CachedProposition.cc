#include "classes/atom/CachedProposition.hh"

namespace expression {
CachedProposition::CachedProposition(Proposition *prop) : _prop(prop) {
  _cached = new bool[prop->getMaxTime()];
  for (size_t i = 0; i < prop->getMaxTime(); i++) {
    _cached[i] = prop->evaluate(i);
  }
}
CachedProposition::~CachedProposition() {
  delete _prop;
  delete[] _cached;
}
bool CachedProposition::evaluate(size_t time) { return _cached[time]; }

/// @brief Accepts a visitor to visit the current object.
/// @param vis The visitor.
void CachedProposition::acceptVisitor(ExpVisitor &vis) {
  _prop->acceptVisitor(vis);
}

/// @brief Returns the largest simulation time that can be provided to
/// the method evaluate.
size_t CachedProposition::getMaxTime() { return _prop->getMaxTime(); }
Proposition *CachedProposition::getItem() { return _prop; }

void CachedProposition::setType(VarType type, size_t size) {
  _prop->setType(type, size);
}

std::pair<VarType, size_t> CachedProposition::getType() {
  return _prop->getType();
}
Proposition *CachedProposition::get() { return _prop; }

} // namespace expression
