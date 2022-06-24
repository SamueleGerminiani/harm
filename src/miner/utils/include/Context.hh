
#pragma once

#include "exp.hh"
#include "Location.hh"
#include "Metric.hh"
#include "globals.hh"

#include <unordered_map>

namespace harm {
class Template;
class Assertion;

class Context {

public:
  Context();
  ~Context();

  Context(std::string &name, const std::string &language = "Spot");
  Context(std::string &name,
          std::vector<std::pair<expression::Proposition *, Location>> &props,
          std::vector<Template *> &templates,
          const std::string &language = "Spot");

  std::string _name;
  std::string _language;
  std::vector<std::pair<expression::Proposition *, Location>> _props;
  std::vector<expression::CachedAllNumeric *> _numerics;
  std::vector<Template *> _templates;
  std::vector<Assertion *> _assertions;
  std::vector<Metric *> _sort;
  std::vector<std::pair<Metric *, double>> _filter;
};
} // namespace harm
