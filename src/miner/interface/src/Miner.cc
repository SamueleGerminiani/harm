#include "Miner.hh"
#include "globals.hh"
#include "message.hh"
#include "harmIcon.hh"
#include <chrono>
#include <filesystem>
#include <type_traits>


namespace harm {

Miner::Config_t::Config_t()
    : contextMiner(nullptr), propertyMiner(nullptr),
      propertyQualifier(nullptr) {
  // ntd
}

Miner::Config_t::~Config_t() {
  delete contextMiner;
  delete traceReader;
  delete propertyMiner;
  delete propertyQualifier;
}

Miner::Miner(Config_t &configuration) : _config(configuration) {
  // ntd
}

void Miner::run() {
  _printWelcomeMessage();

  messageInfo("Miner started...");

  std::vector<Context *> contexts;

  //==== step 1) Read simulation traces
  //======================================
  messageErrorIf(_config.traceReader == nullptr,
                 "Trace reader module has not been set!");

  Trace *trace = _config.traceReader->readTrace();
  hs::traceLength = trace->getLength();

  ////--------------------------------------------------------------------------

  //==== step 2) Define context of influences
  //===================================
  messageErrorIf(_config.contextMiner == nullptr,
                 "ContextMiner module has not been set!");
  _config.contextMiner->mineContexts(trace, contexts);

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

    //==== step 3) Mine temporal assertions
    if (_config.propertyMiner == nullptr)
      messageWarning("No propertyMiner module has been set");
    else
      _config.propertyMiner->mineProperties(*context, trace);

    // store the time to mine this context
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();
    hs::timeToMine_ms +=
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
            .count();

    //----------------------------------------------------------------------

    //==== step 4) Qualify the mined temporal assertions
    if (_config.propertyQualifier == nullptr)
      messageWarning("No propertyQualifier module has been set");
    else
      _config.propertyQualifier->qualify(*context, trace);

    if (!toCheck.empty()) {
      if (clc::dumpAssToFile) {
        // all the checked assertions will be appended to these files
        std::ofstream assFile(clc::dumpPath + "/" + context->_name +
                                  "_checkedAss.txt",
                              std::ios_base::out);
        assFile.close();
        std::ofstream contingencyFile(clc::dumpPath + "/" + context->_name +
                                          "_checkedAss_cont.txt",
                                      std::ios_base::out);
        contingencyFile.close();
        std::ofstream varsStat(clc::dumpPath + "/" + context->_name +
                                   "_checkedAss_vars.txt",
                               std::ios_base::out);
        varsStat.close();
      }
      for (Template *t : toCheck) {
        t->check(clc::dumpPath + "/" + context->_name);
      }
    }
    delete context;
  }
  //----------------------------------------------------------------------

  delete trace;

  printStats();
}

void Miner::printStats() {
  std::cout << "========================================="
            << "\n";
  if (hs::name != "") {
    std::cout << "Name: " << hs::name << "\n";
  }
  std::cout << "Time to mine: " << (double)hs::timeToMine_ms / 1000.f << "s"
            << "\n";
  std::cout << "Number of assertions: " << hs::nAssertions << "\n";
  std::cout << "Trace length: " << hs::traceLength << "\n";
  if (!clc::faultyTraceFiles.empty() || clc::ftmFile != "") {
    std::cout << "Number of faults: " << clc::faultyTraceFiles.size() << "\n";
    std::cout << "Faults covered: " << hs::nOfCovFaults << " ("
              << ((double)hs::nOfCovFaults / (double)hs::nFaults) * 100.f
              << "%)"
                 "\n";
    std::cout << "Covering subset: " << hs::nFaultCovSubset << "\n";
  }
  std::cout << "========================================="
            << "\n";

  if (clc::dumpStat) {
    std::string filename = "stat_out_"+hs::name+".csv";
    bool exists = std::filesystem::exists(filename);
    std::ofstream of(filename,
                     exists ? std::ofstream::app : std::ofstream::trunc);
    if (!exists) {
      of << "Name; Trace length;Time to mine (s);N assertions;N faults; Fault "
            "coverage (%);Cov. Subset;";
      of << "ClsAlg";
      of << "\n";
    }
    of << (hs::name == "" ? "?" : hs::name) << ";" << hs::traceLength << ";"
       << (double)hs::timeToMine_ms / 1000.f << ";" << hs::nAssertions << ";"
       << hs::nFaults << ";"
       << ((double)hs::nOfCovFaults / (double)hs::nFaults) * 100.f << ";"
       << hs::nFaultCovSubset << ";";

    of << clc::clsAlg;
    of << "\n";
    of.close();
  }
}
void Miner::_printWelcomeMessage() {
  std::cout << getIcon() << "\n";
//  std::string shift = "                             ";
//
//  std::cout << shift << "╭╮╱╭┳━━━┳━━━┳━╮╭━╮"
//            << "\n";
//  std::cout << shift << "┃┃╱┃┃╭━╮┃╭━╮┃┃╰╯┃┃"
//            << "\n";
//  std::cout << shift << "┃╰━╯┃┃╱┃┃╰━╯┃╭╮╭╮┃"
//            << "\n";
//  std::cout << shift << "┃╭━╮┃╰━╯┃╭╮╭┫┃┃┃┃┃"
//            << "\n";
//  std::cout << shift << "┃┃╱┃┃╭━╮┃┃┃╰┫┃┃┃┃┃"
//            << "\n";
//  std::cout << shift << "╰╯╱╰┻╯╱╰┻╯╰━┻╯╰╯╰╯"
//            << "\n";

}

} // namespace harm
