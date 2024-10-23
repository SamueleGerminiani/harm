#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "Context.hh"
#include "ContextMiner.hh"
#include "Miner.hh"
#include "PropertyMiner.hh"
#include "PropertyQualifier.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"

namespace harm {

Miner::ModulesConfig::ModulesConfig()
    : contextMiner(nullptr), propertyMiner(nullptr),
      propertyQualifier(nullptr) {
  // ntd
}

Miner::ModulesConfig::~ModulesConfig() {}

Miner::Miner(ModulesConfig &configuration) : _config(configuration) {
  // ntd
}

void Miner::run() {
  messageErrorIf(_config.traceReader == nullptr,
                 "Trace reader module has not been set");
  messageErrorIf(_config.contextMiner == nullptr,
                 "ContextMiner module has not been set");
  messageErrorIf(_config.propertyMiner == nullptr,
                 "No propertyMiner module has been set");
  messageErrorIf(_config.propertyQualifier == nullptr,
                 "No propertyQualifier module has been set");

  messageInfo("Miner started...");

  std::vector<ContextPtr> contexts;

  //1) Read the simulation traces

  const TracePtr &trace = _config.traceReader->readTrace();

  //save the trace length
  hs::traceLength = trace->getLength();

  //2) Read the contexts from the configuration file, store them in 'contexts'
  _config.contextMiner->mineContexts(trace, contexts);

  messageInfo("Mining " + std::to_string(contexts.size()) +
              " context" + (contexts.size() > 1 ? "s" : ""));

  for (const ContextPtr &context : contexts) {
    messageWarningIf(context->_templates.empty(),
                     "No templates defined in context '" +
                         context->_name + "'");

    //remove "check" templates from the list and store them in toCheck, they will be handled later
    std::vector<TemplateImplicationPtr> toCheck;
    context->_templates.erase(
        std::remove_if(context->_templates.begin(),
                       context->_templates.end(),
                       [&toCheck](const TemplateImplicationPtr &t) {
                         if (t->getCheck()) {
                           toCheck.push_back(t);
                         }
                         return t->getCheck();
                       }),
        context->_templates.end());

    // time to mine
    dirtyTimerMilliseconds("minerTimer", 1);

    //3) Mine assertions
    _config.propertyMiner->mineProperties(context, trace);

    // store the time to mine of this context
    hs::timeToMine_ms += dirtyTimerMilliseconds("minerTimer", 0);

    //4) Qualify the mined temporal assertions (additionally print and dump)
    _config.propertyQualifier->qualify(*context, trace);

    // handle "check" templates
    for (const TemplateImplicationPtr &t : toCheck) {
      t->check();
    }
  }

  handleStatistics();
}

void Miner::handleStatistics() {
  std::cout << "========================================="
            << "\n";
  if (hs::name != "") {
    std::cout << "Name: " << hs::name << "\n";
  }
  std::cout << "Time to mine: " << (double)hs::timeToMine_ms / 1000.f
            << "s"
            << "\n";
  std::cout << "Number of assertions: " << hs::nAssertions << "\n";
  std::cout << "Trace length: " << hs::traceLength << "\n";
  if (!clc::faultyTraceFiles.empty()) {
    std::cout << "Number of faults: " << clc::faultyTraceFiles.size()
              << "\n";
    std::cout << "Faults covered: " << hs::nOfCovFaults << " ("
              << ((double)hs::nOfCovFaults / (double)hs::nFaults) *
                     100.f
              << "%)"
                 "\n";
    std::cout << "Covering subset: " << hs::nFaultCovSubset << "\n";
  }
  std::cout << "========================================="
            << "\n";

  if (clc::dumpStat) {
    std::string filename = "stat_out_" + hs::name + ".csv";
    bool exists = std::filesystem::exists(filename);
    //append if file exists, otherwise create new
    std::ofstream of(filename, exists ? std::ofstream::app
                                      : std::ofstream::trunc);
    if (!exists) {
      of << "Name; Trace length;Time to mine (s);N assertions;N "
            "faults; Fault "
            "coverage (%);Cov. Subset";
      of << "\n";
    }
    of << (hs::name == "" ? "?" : hs::name) << ";" << hs::traceLength
       << ";" << (double)hs::timeToMine_ms / 1000.f << ";"
       << hs::nAssertions << ";" << hs::nFaults << ";"
       << ((double)hs::nOfCovFaults / (double)hs::nFaults) * 100.f
       << ";" << hs::nFaultCovSubset << ";";

    of << "\n";
    of.close();
  }
}

} // namespace harm
