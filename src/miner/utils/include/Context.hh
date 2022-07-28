
#pragma once

#include "Location.hh"
#include "exp.hh"

#include <unordered_map>
#include <vector>


namespace harm {

class Template;
class Assertion;
class Metric;

/*! \class Context
    \brief Class representing a set of props, numerics, templates, metrics and assertions
*/
class Context {

public:
  Context();
  ~Context();

  Context(std::string &name, const std::string &language = "Spot");
  Context(std::string &name, std::vector<std::pair<expression::Proposition *, Location>> &props, std::vector<Template *> &templates, const std::string &language = "Spot");

  std::string _name;
  std::vector<std::pair<expression::Proposition *, Location>> _props;
  std::vector<Template *> _templates;
  ///language of the templates and assertions (Spot, PSL, SVA)
  std::string _language;

  std::vector<expression::CachedAllNumeric *> _numerics;
  std::vector<Assertion *> _assertions;

  ///sorting metrics
  std::vector<Metric *> _sort;
  ///filtering metrics
  std::vector<std::pair<Metric *, double>> _filter;
};
} // namespace harm
