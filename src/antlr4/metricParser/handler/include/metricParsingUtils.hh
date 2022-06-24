#pragma once
#include "Trace.hh"
#include "Metric.hh"

namespace hparser{
void addTypeToMetric(std::string &formula,
                          std::vector<harm::VarDeclaration> &varDeclarations) ;

harm::Metric* parseMetric(const std::string &name, std::string &formula, harm::Trace *trace) ;
}
