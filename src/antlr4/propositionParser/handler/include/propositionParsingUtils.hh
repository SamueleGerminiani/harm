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
/// @param inTemplate & and | are temporal operators in templates: only ^ and ~ mark a bool
/// variable as a bitwise operand there (D-032)
void addTypeToExp(std::string &formula,
                  std::vector<harm::VarDeclaration> varDeclarations,
                  bool inTemplate = false);

expression::PropositionPtr parseProposition(std::string formula,
                                            const harm::TracePtr &trace);
expression::IntExpressionPtr
parseIntExpression(std::string formula, const harm::TracePtr &trace);
expression::FloatExpressionPtr
parseFloatExpression(std::string formula, const harm::TracePtr &trace);
expression::LogicExpressionPtr
parseLogicExpression(std::string formula, const harm::TracePtr &trace);
expression::StringExpressionPtr
parseStringExpression(std::string formula, const harm::TracePtr &trace);
expression::PropositionPtr
parsePropositionAlreadyTyped(std::string formula,
                             const harm::TracePtr &trace);

/// @brief like parseProposition, but a syntax or type error does not terminate HARM: it returns
/// nullptr and stores the reason in 'error'
expression::PropositionPtr
tryParseProposition(std::string formula, const harm::TracePtr &trace,
                    std::string &error);

} // namespace hparser
