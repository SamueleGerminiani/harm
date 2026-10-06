#pragma once

#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

#include "formula/atom/Atom.hh"
#include "formula/temporal/TemporalExpression.hh"

namespace harm {
class Trace;
using TracePtr = std::shared_ptr<Trace>;
class TemplateImplication;
using TemplateImplicationPtr = std::shared_ptr<TemplateImplication>;

/// @brief <coi depth="...">: how the filter uses the depths of the cone (D-020, H8)
enum class CoiDepth { Any, Bounded, Exact };

/// @brief a consequent leaf seen from an antecedent proposition: its variables, and how many
/// cycles after the proposition it is evaluated (std::nullopt if not fixed)
struct ConsequentLeaf {
  std::vector<std::string> vars;
  std::optional<int> distance;
};

/// @brief A cone of influence description (coi.json v1, doc/schemas/coi.v1.json, H4)
class CoiInfo {
public:
  struct Source {
    std::vector<int> depths;
    bool saturated = false;
  };

  /// @brief load and check a coi.json file; every name must be a variable of the trace
  static std::shared_ptr<CoiInfo> load(const std::string &file,
                                       const TracePtr &trace);

  /// @brief true if coi.json describes this signal (a target, not in 'unknown')
  bool knows(const std::string &signal) const;

  /// @brief D-017 (= D-014's leaf rule): a proposition with these variables is in the cone of a
  /// consequent with these variables if every variable is a source of some consequent variable;
  /// unknown signals count as in the cone, an unknown consequent signal keeps everything, and a
  /// proposition without variables is kept
  bool inCone(const std::vector<std::string> &propVars,
              const std::vector<std::string> &consequentVars) const;
  /// @brief D-020: a proposition with these variables fits the consequent leaves at their
  /// distances. Any: inCone. Exact: every variable has some consequent leaf and variable with the
  /// distance among its depths (or beyond max_depth, saturated). Bounded: 0 <= distance <= its
  /// largest depth (or saturated). Unknown signals and distances keep the proposition
  bool fits(const std::vector<std::string> &propVars,
            const std::vector<ConsequentLeaf> &consequent, CoiDepth depth) const;
  /// @brief the source entry of 'source' in the cone of 'target', or nullptr
  const Source *source(const std::string &target,
                       const std::string &source) const;

  std::string _file;
  std::string _vcdScope;
  size_t _vcdRecursion = 0;
  std::string _clock;
  int _maxDepth = 0;
  std::map<std::string, std::map<std::string, Source>> _targets;
  std::set<std::string> _unknown;
};
using CoiInfoPtr = std::shared_ptr<CoiInfo>;

/// @brief an atomic proposition of a formula, with the cycle at which it is evaluated relative to
/// the start of the antecedent (std::nullopt if not fixed: until, eventually, repetitions, ...)
struct LeafOffset {
  expression::PropositionPtr prop;
  bool inAntecedent;
  std::optional<int> offset;
};

/// @brief the leaves of G(antecedent -> consequent), in printing order
std::vector<LeafOffset>
leafOffsets(const expression::TemporalExpressionPtr &formula);

/// @brief D-007: for each decision-tree index of t, the distance in cycles from an item at that
/// index to each consequent leaf (in leafOffsets order); std::nullopt where it is not fixed.
/// Empty if t has no decision-tree operator
std::vector<std::vector<std::optional<int>>>
dtIndexDistances(const TemplateImplicationPtr &t);

/// @brief the COI rank metrics of an assertion (D-014)
struct CoiMetrics {
  double frac = 1;
  double depthFit = 1;
  size_t unknown = 0;
};
CoiMetrics computeCoiMetrics(const expression::TemporalExpressionPtr &formula,
                             const CoiInfo &coi);

} // namespace harm
