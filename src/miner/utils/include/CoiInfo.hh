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

/// @brief the COI rank metrics of an assertion (D-014)
struct CoiMetrics {
  double frac = 1;
  double depthFit = 1;
  size_t unknown = 0;
};
CoiMetrics computeCoiMetrics(const expression::TemporalExpressionPtr &formula,
                             const CoiInfo &coi);

} // namespace harm
