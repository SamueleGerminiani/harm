#include "harm.hh"
#include "Assertion.hh"
#include "CSVtraceReader.hh"
#include "ManualDefinition.hh"
#include "Miner.hh"
#include "Qualifier.hh"
#include "TLMiner.hh"
#include "VCDtraceReader.hh"
#include "colors.hh"
#include "exp.hh"
#include "globals.hh"

#include <csignal>
#include <filesystem>
#include <string>
#include <unordered_map>

namespace harm {

static void loadParameters(const Parameters &p) {
  messageErrorIf(!std::filesystem::exists(p.configFile),
                 "Can not find config file '" + p.configFile + "'");
  clc::configFile = p.configFile;

  messageErrorIf(p.parserType != "vcd" && p.parserType != "csv",
                 "Unknown parser type '" + p.parserType +
                     "', expected 'vcd' or 'csv'");
  clc::parserType = p.parserType;

  for (const auto &file : p.traceFiles) {
      messageErrorIf(!std::filesystem::exists(file),
                     "Can not find trace file '" + file + "'");
      clc::traceFiles.push_back(file);
  }

  for (const auto &file : p.faultyTraceFiles) {
      messageErrorIf(!std::filesystem::exists(file),
                     "Can not find faulty trace file '" + file + "'");
      clc::faultyTraceFiles.push_back(file);
  }

  messageErrorIf(p.parserType=="vcd" && p.clk=="", "Undefined sampling clk signal");
  clc::clk = p.clk;


  messageErrorIf(p.maxThreads<=1, "Illegal number of threads '"+std::to_string(p.maxThreads)+"'");
  clc::maxThreads = p.maxThreads;

  clc::findMinSubset = p.findMinSubset;

  clc::dumpAssToFile = p.dumpAssToFile;

  clc::noData = p.noData;

  clc::dumpPath = p.dumpPath;


  clc::vcdRecursive = p.vcdRecursive;

  clc::selectedScope = p.selectedScope;

  clc::dontFillAss = p.dontFillAss;

  clc::dontPrintAss = p.dontPrintAss;

  clc::silent = p.silent;

  clc::wsilent = p.wsilent;

  clc::isilent = p.isilent;

  clc::psilent = p.psilent;
}

static std::unordered_map<std::string, std::vector<Assertion *>>
runMiner(Miner::ModulesConfig &config) {
  std::unordered_map<std::string, std::vector<Assertion *>> contextToAss;

  messageInfo("Miner started...");

  std::vector<Context *> contexts;

  //1) Read the simulation traces
  messageErrorIf(config.traceReader == nullptr,
                 "Trace reader module has not been set!");

  Trace *trace = config.traceReader->readTrace();
  hs::traceLength = trace->getLength();

  //2) Read the contexts
  messageErrorIf(config.contextMiner == nullptr,
                 "ContextMiner module has not been set!");
  config.contextMiner->mineContexts(trace, contexts);

  for (Context *context : contexts) {
    messageErrorIf(context->_templates.empty(),
                   "No templates or assertions defined!");

    // handle "check" templates
    std::vector<Template *> toCheck;
    for (Template *&t : context->_templates) {
      if (t->_check) {
        toCheck.push_back(t);
        t = nullptr;
      }
    }
    // remove "check" templates from the list
    auto &templs = context->_templates;
    templs.erase(std::remove(templs.begin(), templs.end(), nullptr),
                 templs.end());

    // time to mine
    std::chrono::steady_clock::time_point begin =
        std::chrono::steady_clock::now();

    messageErrorIf(config.propertyMiner == nullptr,
                   "No propertyMiner module has been set");

    //3) Mine temporal assertions
    config.propertyMiner->mineProperties(*context, trace);

    // store the time to mine this context
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();
    hs::timeToMine_ms +=
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
            .count();

    messageErrorIf(config.propertyQualifier == nullptr,
                   "No propertyQualifier module has been set");

    //4) Qualify the mined temporal assertions (additionally print and dump)
    contextToAss[context->_name] =
        config.propertyQualifier->qualify(*context, trace);

    for (Template *t : toCheck) {
      t->check();
    }

    if (contextToAss.at(context->_name).size() < context->_assertions.size()) {
      //delete assertions filtered by ranking (if any)
      for (auto *a : context->_assertions) {
        if (std::find(std::begin(contextToAss.at(context->_name)),
                      std::end(contextToAss.at(context->_name)),
                      a) == std::end(contextToAss.at(context->_name))) {
          delete a;
        }
      }
    }

    // avoid deleting the assertions, the responsability lies on the caller
    context->_assertions.clear();
    delete context;
  }
  //----------------------------------------------------------------------

  delete trace;
  return contextToAss;
}

std::unordered_map<std::string, std::vector<Assertion *>> mine(const Parameters &p) {

  std::unordered_map<std::string, std::vector<Assertion *>> contextToAss;

  loadParameters(p);
  Miner::ModulesConfig config;

  // trace reader
  if (clc::parserType == "vcd") {
    config.traceReader = new VCDtraceReader(clc::traceFiles, clc::clk);
  } else if (clc::parserType == "csv") {
    config.traceReader = new CSVtraceReader(clc::traceFiles);
  }

  config.contextMiner = new ManualDefinition(clc::configFile);
  config.propertyMiner = new TLMiner();
  config.propertyQualifier = new Qualifier();

  return runMiner(config);
}

} // namespace harm
