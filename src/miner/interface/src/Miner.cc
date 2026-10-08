#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Context.hh"
#include "Location.hh"
#include "expUtils/expUtils.hh"
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

  if (clc::dumpPropTable != "") {
    writePropTable(contexts, trace, _config.traceReader->getReadFiles());
  }

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
      t->check(context->_name);
    }
  }

  if (clc::checkDumpEvalDirectory != "") {
    // D-030: map every dumped file back to its assertion
    std::ofstream out(clc::checkDumpEvalDirectory + "/index.json");
    out << "{\n  \"version\": \"1\",\n  \"assertions\": [\n";
    for (size_t i = 0; i < hs::checkDumpEvalIndex.size(); i++) {
      out << hs::checkDumpEvalIndex[i]
          << (i + 1 < hs::checkDumpEvalIndex.size() ? ",\n" : "\n");
    }
    out << "  ]\n}\n";
  }

  handleStatistics();
}

namespace {
/// a domain id as written in loc: a, c, ac, dt, or the restricted domain's number
std::string domainName(int id) {
  switch (id) {
  case (int)Location::Ant:
    return "a";
  case (int)Location::Con:
    return "c";
  case (int)Location::AntCon:
    return "ac";
  case (int)Location::DecTree:
    return "dt";
  default:
    return std::to_string(id);
  }
}

std::string domainList(std::vector<int> ids) {
  std::sort(ids.begin(), ids.end()); // a, c, ac, dt, then the numbered domains
  ids.erase(std::unique(ids.begin(), ids.end()), ids.end());
  std::string r = "[";
  for (size_t i = 0; i < ids.size(); i++) {
    r += (i ? ", " : "") + jsonString(domainName(ids[i]));
  }
  return r + "]";
}
} // namespace

void Miner::writePropTable(const std::vector<ContextPtr> &contexts,
                           const TracePtr &trace,
                           const std::vector<std::pair<std::string, size_t>> &files) {
  // H15, D-031: prop-table v1
  std::ofstream out(clc::dumpPropTable);
  messageErrorIf(!out.is_open(), "Could not open file '" +
                                     clc::dumpPropTable +
                                     "' for writing");
  const size_t length = trace->getLength();
  const std::vector<size_t> &cuts = trace->getCuts();

  out << "{\n  \"format\": \"prop-table\", \"version\": \"1\", \"harm\": "
      << jsonString(clc::harmVersion) << ",\n";
  if (clc::parserType == "vcd") {
    out << "  \"sampling\": {\"input\": \"vcd\", \"clock\": "
        << jsonString(clc::clk)
        << ", \"edge\": \"posedge\", \"values\": \"preponed\"},\n";
  } else {
    out << "  \"sampling\": {\"input\": \"csv\"},\n";
  }
  out << "  \"length\": " << length << ",\n";

  // one sub-trace per file read, in merge order
  out << "  \"traces\": [";
  size_t first = 0;
  for (size_t i = 0; i < files.size(); i++) {
    out << (i ? ", " : "") << "{\"file\": " << jsonString(files[i].first)
        << ", \"first\": " << first
        << ", \"last\": " << first + files[i].second - 1 << "}";
    first += files[i].second;
  }
  out << "],\n";
  // the trace's cuts: the end of each sub-trace and, with --reset, of each reset interval
  out << "  \"segments\": [";
  first = 0;
  for (size_t i = 0; i < cuts.size(); i++) {
    out << (i ? ", " : "") << "[" << first << ", " << cuts[i] << "]";
    first = cuts[i] + 1;
  }
  out << "],\n  \"contexts\": [";

  for (size_t ci = 0; ci < contexts.size(); ci++) {
    const Context &ctx = *contexts[ci];
    // one entry per text, in configuration order, with the union of the domains
    std::vector<std::string> texts;
    std::unordered_map<std::string, std::pair<size_t, std::vector<int>>> byText;
    for (size_t i = 0; i < ctx._loadedProps.size(); i++) {
      std::string text = prop2String(ctx._loadedProps[i].prop);
      auto it = byText.find(text);
      if (it == byText.end()) {
        texts.push_back(text);
        byText[text] = {i, ctx._loadedProps[i].domains};
      } else {
        auto &d = it->second.second;
        d.insert(d.end(), ctx._loadedProps[i].domains.begin(),
                 ctx._loadedProps[i].domains.end());
      }
    }
    out << (ci ? ",\n" : "\n") << "    {\"name\": " << jsonString(ctx._name)
        << ",\n     \"propositions\": [";
    for (size_t id = 0; id < texts.size(); id++) {
      const auto &[index, domains] = byText.at(texts[id]);
      const auto &lp = ctx._loadedProps[index];
      auto origin = ctx._origin.find(texts[id]);
      std::string values(length, '0');
      for (size_t t = 0; t < length; t++) {
        if (lp.prop->evaluate(t)) {
          values[t] = '1';
        }
      }
      out << (id ? ",\n" : "\n") << "      {\"id\": " << id
          << ", \"text\": " << jsonString(texts[id])
          << ", \"domains\": " << domainList(domains)
          << ", \"source\": "
          << (lp.numeric.empty() ? "\"prop\"" : "\"numeric\"");
      if (!lp.numeric.empty()) {
        out << ", \"numeric\": " << jsonString(lp.numeric);
      }
      out << ", \"origin\": "
          << (origin == ctx._origin.end() ? "null"
                                          : jsonString(origin->second))
          << ", \"values\": \"" << values << "\"}";
    }
    out << "],\n     \"unexpanded_numerics\": [";
    for (size_t i = 0; i < ctx._unexpandedNumerics.size(); i++) {
      out << (i ? ", " : "") << "{\"text\": "
          << jsonString(ctx._unexpandedNumerics[i].first)
          << ", \"domains\": "
          << domainList(ctx._unexpandedNumerics[i].second) << "}";
    }
    out << "]}";
  }
  out << "\n  ]\n}\n";
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
