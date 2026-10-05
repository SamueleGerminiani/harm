#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "formula/atom/Atom.hh"

namespace harm {
class Assertion;
using AssertionPtr = std::shared_ptr<Assertion>;

/// @brief Groups the propositions of a set of assertions into classes of equivalent propositions
/// (H2, `--reduce equiv`) and gives each class a token.
///
/// Propositions with the same text are in the same class without a solver call; propositions
/// with different text are compared with Z3 (expression::smt::checkEquivalence) only within
/// buckets of propositions over the same variables. Only a proved equivalence merges two
/// classes: a timeout or an unknown result keeps them apart.
class PropositionCanonicalizer {
public:
  /// @param tokenPrefix, tokenSuffix the token of class k is prefix + k + suffix
  explicit PropositionCanonicalizer(unsigned timeoutMs = 1000,
                                    std::string tokenPrefix = "@C",
                                    std::string tokenSuffix = "@")
      : _timeoutMs(timeoutMs), _tokenPrefix(std::move(tokenPrefix)),
        _tokenSuffix(std::move(tokenSuffix)) {}

  /// @brief compute the classes of the propositions of these assertions (their boolean-layer
  /// instances)
  void build(const std::vector<AssertionPtr> &assertions);

  /// @brief compute the classes of these propositions
  void build(const std::vector<expression::PropositionPtr> &props);

  /// @brief the token of the class of every proposition object seen by build()
  const std::unordered_map<const expression::Proposition *, std::string> &
  tokens() const {
    return _tokens;
  }

  /// @brief the assertion printed with each proposition replaced by its class token
  std::string canonicalString(const AssertionPtr &a) const;

  size_t numberOfClasses() const { return _numberOfClasses; }
  size_t solverCalls() const { return _solverCalls; }

private:
  unsigned _timeoutMs;
  std::string _tokenPrefix, _tokenSuffix;
  std::unordered_map<const expression::Proposition *, std::string> _tokens;
  size_t _numberOfClasses = 0;
  size_t _solverCalls = 0;
};

} // namespace harm
