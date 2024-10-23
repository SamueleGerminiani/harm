#pragma once
#include <string>

#include "DTLimits.hh"
#include "TemplateImplication.hh"

namespace harm {
class TemplateImplication;
class Trace;
} // namespace harm
namespace expression {
class TemporalExpression;
using TemporalExpressionPtr = std::shared_ptr<TemporalExpression>;
} // namespace expression

namespace hparser {

harm::TemplateImplicationPtr parseTemplateImplication(
    std::string formula, const harm::TracePtr &trace,
    const harm::DTLimits &limits = harm::DTLimits(),
    bool useCache = true);

expression::TemporalExpressionPtr
parseTemporalExpression(std::string formula,
                        const harm::TracePtr &trace);

} // namespace hparser
