#pragma once

#include <iosfwd>
#include <memory>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "formula/atom/Atom.hh"
#include "formula/temporal/TemporalExpression.hh"

namespace expression {
class NumericExpression;
using NumericExpressionPtr = std::shared_ptr<NumericExpression>;

template <typename OT, typename ET> class Function;
using FunctionPropositionPtr =
    std::shared_ptr<Function<Proposition, Proposition>>;

} // namespace expression
namespace harm {
enum class ClsOp;
} // namespace harm

namespace expression {
enum class ExpType;
}

namespace harm {
class Automaton;
class EdgeProposition;
class VarDeclaration;

/** \brief To print a ClsOp
   */
std::ostream &operator<<(std::ostream &os, ClsOp op);

/// @brief converts a string variable to a type
std::pair<expression::ExpType, size_t>
variableTypeFromString(const std::string &type, size_t size = 1);

/// @brief converts a type to a string
std::string varTypeToString(const expression::ExpType &type,
                            size_t size);

/// @brief converts a set of numeric values to propositions
std::vector<expression::PropositionPtr>
genPropsThroughClustering(std::vector<size_t> &ivs,
                          const expression::NumericExpressionPtr &cn,
                          bool DTAlgo);
std::string
dumpClusteringValues(std::vector<size_t> &ivs,
                     const expression::NumericExpressionPtr &cn);

size_t getTypeBase(const std::string &type);

/// @brief converts a variable declaration into VarDeclaration
VarDeclaration toVarDeclaration(std::string name, std::string type,
                                size_t size);

///Pack of placeholders
struct PlaceholderPack {
  PlaceholderPack() = default;

  ///dt and permutations placeholders
  std::unordered_map<std::string, expression::PropositionPtrPtr>
      _tokenToPP;
  ///inst placeholders
  std::unordered_map<std::string, expression::PropositionPtr>
      _tokenToInst;
  ///function placeholders
  std::unordered_map<std::string, expression::FunctionPropositionPtr>
      _tokenToFun;
};

PlaceholderPack
extractPlaceholders(const expression::TemporalExpressionPtr &formula);

int getTemporalDepth(const expression::TemporalExpressionPtr &te);
void substitutePlaceholders(
    expression::TemporalExpressionPtr &original,
    const PlaceholderPack &pack);
} // namespace harm
