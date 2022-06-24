#pragma once
#include "BDTLimits.hh"
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
                              const harm::BDTLimits &limits = harm::BDTLimits(),
                              bool useCache = true);
Hstring spotToSVA(std::string spotFormula, harm::Trace *trace);
} // namespace hparser
