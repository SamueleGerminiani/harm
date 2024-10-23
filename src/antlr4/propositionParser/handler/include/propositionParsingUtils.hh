#pragma once
#include <string>
#include <vector>

#include "formula/atom/Atom.hh"

namespace harm {
class Trace;
using TracePtr = std::shared_ptr<Trace>;
class VarDeclaration;
} // namespace harm

namespace hparser {
void addTypeToExp(std::string &formula,
                  std::vector<harm::VarDeclaration> varDeclarations);

expression::PropositionPtr
parseProposition(std::string formula, const harm::TracePtr &trace);
expression::IntExpressionPtr
parseIntExpression(std::string formula, const harm::TracePtr &trace);
expression::FloatExpressionPtr
parseFloatExpression(std::string formula,
                     const harm::TracePtr &trace);
expression::PropositionPtr
parsePropositionAlreadyTyped(std::string formula,
                             const harm::TracePtr &trace);

} // namespace hparser
