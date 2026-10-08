
#pragma once

#include <unordered_map>
#include <utility>
#include <vector>

#include "CoiInfo.hh"
#include "formula/atom/Atom.hh"

namespace expression {
class NumericExpression;
using NumericExpressionPtr = std::shared_ptr<NumericExpression>;
} // namespace expression

namespace harm {

class TemplateImplication;
using TemplateImplicationPtr = std::shared_ptr<TemplateImplication>;
class Assertion;
using AssertionPtr = std::shared_ptr<Assertion>;
class Metric;
using MetricPtr = std::shared_ptr<Metric>;
class Edit;
using EditPtr = std::shared_ptr<Edit>;
enum class Location;

/*! \class Context
    \brief Class representing a set of props, numerics, templates, metrics, edits and assertions
*/
class Context {

public:
  Context() = default;
  ~Context();
  //delete all other constructors
  Context(const Context &) = delete;
  Context &operator=(const Context &) = delete;

  Context(const std::string &name);

  std::string _name;

  //domains
  std::unordered_map<int, std::vector<expression::PropositionPtr>>
      _domainIdToProps;
  std::unordered_map<int,
                     std::vector<expression::NumericExpressionPtr>>
      _domainIdToNumerics;

  std::vector<TemplateImplicationPtr> _templates;

  std::vector<expression::NumericExpressionPtr> _numerics;

  //this is filled by the miner
  std::vector<AssertionPtr> _assertions;

  ///sorting metrics
  std::vector<MetricPtr> _sort;
  ///filtering metrics
  std::vector<std::pair<MetricPtr, double>> _filter;

  ///rewrite assertions rules
  std::vector<EditPtr> _rewrite;
  ///remove assertions rules
  std::vector<EditPtr> _remove;

  ///cone of influence (<coi>, H6); nullptr if the context has none
  CoiInfoPtr _coi = nullptr;
  ///<coi mode="...">: "rank" (H6) or "filter" (H7, D-017)
  std::string _coiMode = "rank";
  ///<coi depth="...">, filter mode only (H8, D-020)
  CoiDepth _coiDepth = CoiDepth::Any;
  ///filter mode: the search space before and after pruning (H7), all templates of the context
  struct CoiFilterStats {
    size_t permutationsBefore = 0, permutationsAfter = 0;
    size_t dtCandidatesBefore = 0, dtCandidatesAfter = 0;
    ///depth filter (H8): (decision-tree candidate, index) pairs the tree tried, before and after
    size_t dtPairsBefore = 0, dtPairsAfter = 0;
  } _coiFilterStats;
  ///origin="..." of propositions and numerics, by their text
  std::unordered_map<std::string, std::string> _origin;
  /// --dump-prop-table (H15): every <prop> and every proposition expanded from a <numeric>, in
  /// configuration order, with its domain ids; numeric is the numeric's text ("" for a <prop>)
  struct LoadedProp {
    expression::PropositionPtr prop;
    std::vector<int> domains;
    std::string numeric;
  };
  std::vector<LoadedProp> _loadedProps;
  /// --dump-prop-table (H15): the <numeric>s left to the decision tree ([dt], [n]), not expanded
  std::vector<std::pair<std::string, std::vector<int>>> _unexpandedNumerics;
};
//using shared pointer for the context
using ContextPtr = std::shared_ptr<Context>;

/// @brief --dump-coi-report (H9, D-022): for each consequent proposition of each context with a
/// <coi>, the antecedent propositions and numerics outside its cone (D-017's rule), with origin.
/// Defined in CoiInfo.cc
void writeCoiReport(const std::vector<ContextPtr> &contexts, const std::string &file);
} // namespace harm
