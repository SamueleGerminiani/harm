#pragma once
#include "exp.hh"
#include "Trace.hh"

namespace hparser{
void addTypeToExp(std::string &formula,
                          std::vector<harm::VarDeclaration> varDeclarations) ;

expression::Proposition *parseProposition(std::string formula, harm::Trace *trace);
expression::Proposition *parsePropositionAlreadyTyped(std::string formula, harm::Trace *trace);
}
