#include "Context.hh"
#include "Assertion.hh"
#include "Metric.hh"
#include "TemplateImplication.hh"
#include "formula/atom/NumericExpression.hh"

namespace harm {
enum class Location;

Context::~Context() {}

Context::Context(const std::string &name) : _name(name) {
  // not todo
}
} // namespace harm
