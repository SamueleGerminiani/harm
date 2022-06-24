#include "Context.hh"
#include "Assertion.hh"
#include "Template.hh"

namespace harm {

Context::Context() {}

Context::~Context() {

  for (auto &t : _templates) {
    delete t;
  }
  for (auto &p : _props) {
    delete p.first;
  }
  for (auto &n : _numerics) {
    delete n;
  }
  for (auto &m : _sort) {
    delete m;
  }
  for (auto &m : _filter) {
    delete m.first;
  }
  for (Assertion *a : _assertions) {
    delete a;
  }
}

Context::Context(std::string &name, const std::string &language)
    : _name(name), _language(language) {
  // not todo
}
Context::Context(
    std::string &name,
    std::vector<std::pair<expression::Proposition *, Location>> &props,
    std::vector<Template *> &templates, const std::string &language)
    : _name(name), _props(props), _templates(templates), _language(language) {
  // not todo
}
} // namespace harm
