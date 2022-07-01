#pragma once
#include "DTLimits.hh"
#include "Hstring.hh"
#include "Trace.hh"

namespace harm {
class Template;
}

namespace hparser {
void addTypeToTemplate(std::string &formula,
                       std::vector<harm::VarDeclaration> varDeclarations);

harm::Template *parseTemplate(std::string formula, harm::Trace *trace,
                              const std::string &language = "Spot",
                              const harm::DTLimits &limits = harm::DTLimits(),
                              bool useCache = true);
Hstring spotToSVA(std::string spotFormula, harm::Trace *trace);
} // namespace hparser
