#include <filesystem>
#include <iostream>
#include <memory>
#include <ostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "CSVtraceReader.hh"
#include "ManualDefinition.hh"
#include "Miner.hh"
#include "Qualifier.hh"
#include "TLMiner.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "VCDtraceReader.hh"
#include "VarDeclaration.hh"
#include "commandLineParser.hh"
#include "cxxopts.hpp"
#include "expUtils/ExpType.hh"
#include "globals.hh"
#include "harmIcon.hh"
#include "message.hh"
#include "misc.hh"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace harm;
using namespace expression;

/// @brief handle all the command line arguments
static void parseCommandLineArguments(int argc, char *args[]);

/// @brief automatically generates a config file only using the input trace
static void genConfigFile(std::string &configFile,
                          const TraceReaderPtr &tr);

int main(int arg, char *argv[]) {

  //enforce deterministic rand
  srand(1);

  //print welcome message
  std::cout << getIcon() << "\n";

  //it holds the employed modules
  Miner::ModulesConfig config;

  parseCommandLineArguments(arg, argv);

  // trace reader
  if (clc::parserType == "vcd") {
    config.traceReader =
        generatePtr<VCDtraceReader>(clc::traceFiles, clc::clk);
  } else if (clc::parserType == "csv") {
    config.traceReader = generatePtr<CSVtraceReader>(clc::traceFiles);
  }

  // automatic generation of the configuration file
  if (clc::genConfig) {
    genConfigFile(clc::configFile, config.traceReader);
    messageInfo("Configuration file generated at " + clc::configFile);
    return 0;
  }

  if (clc::dumpTraceAsCSV != "") {
    const TracePtr &trace = config.traceReader->readTrace();
    dumpTraceAsCSV(trace, clc::dumpTraceAsCSV);

    return 0;
  }

  //setting the modules
  config.contextMiner =
      generatePtr<ManualDefinition>(clc::configFile);
  config.propertyMiner = generatePtr<TLMiner>();
  config.propertyQualifier = generatePtr<Qualifier>();

  Miner miner(config);
  miner.run();
  return 0;
}

void parseCommandLineArguments(int argc, char *args[]) {
  //parse the cmd using an external library
  auto result = parseHARM(argc, args);

  //check for errors and build the environment
  messageErrorIf(((result.count("vcd") || result.count("vcd-dir")) &&
                  (result.count("csv") || result.count("csv-dir"))),
                 "Mixing vcd with csv traces");

  if (result.count("name")) {
    hs::name = result["name"].as<std::string>();
  }

  //------------------------
  //vcd cases
  //vcd-ss or vcd-ss + vcd-r == 0 : get signals only in selected scope
  //vcd-ss + vcd-r = n with n>0 : get signals in selected scope and recursive with depth n
  //vcd-ss + vcd-unroll = n with n>0 : get signals in selected scope and recursive with depth n and make a context for each scope
  if (result.count("vcd-ss")) {
    clc::selectedScope = result["vcd-ss"].as<std::string>();
    clc::vcdRecursive = 0;
  }
  if (result.count("vcd-r")) {
    clc::vcdRecursive = safeStoull(result["vcd-r"].as<std::string>());
  }

  messageErrorIf(result.count("vcd-unroll") &&
                     (result.count("vcd-r")),
                 "Can not use 'vcd-unroll' with 'vcd-r'");

  messageErrorIf(
      result.count("vcd-unroll") && !result.count("generate-config"),
      "Can not use 'vcd-unroll' without 'generate-config'");

  if (result.count("vcd-unroll")) {
    clc::vcdUnroll =
        safeStoull(result["vcd-unroll"].as<std::string>());
    messageErrorIf(clc::vcdUnroll == 0,
                   "vcd-unroll must be greater than 0");
  }

  if (result.count("clk")) {
    clc::clk = result["clk"].as<std::string>();
  }

  if (result.count("vcd")) {
    clc::parserType = "vcd";
    clc::traceFiles.push_back(result["vcd"].as<std::string>());
    messageErrorIf(!std::filesystem::exists(clc::traceFiles[0]),
                   "Can not find trace file '" + clc::traceFiles[0] +
                       "'");
  } else if (result.count("csv")) {
    clc::parserType = "csv";
    clc::traceFiles.push_back(result["csv"].as<std::string>());
    messageErrorIf(!std::filesystem::exists(clc::traceFiles[0]),
                   "Can not find trace file '" + clc::traceFiles[0] +
                       "'");
  }

  if (result.count("vcd-dir")) {
    clc::parserType = "vcd";
    messageErrorIf(!std::filesystem::is_directory(
                       result["vcd-dir"].as<std::string>()),
                   "Can not find directory '" +
                       result["vcd-dir"].as<std::string>() + "'");
    for (const auto &entry : std::filesystem::directory_iterator(
             result["vcd-dir"].as<std::string>())) {
      if (entry.path().extension() == ".vcd") {
        clc::traceFiles.push_back(entry.path().u8string());
      }
    }
    messageErrorIf(clc::traceFiles.empty(),
                   "No vcd trace found in: " +
                       result["vcd-dir"].as<std::string>());
  } else if (result.count("csv-dir")) {
    messageErrorIf(!std::filesystem::is_directory(
                       result["csv-dir"].as<std::string>()),
                   "Can not find directory '" +
                       result["csv-dir"].as<std::string>() + "'");
    for (const auto &entry : std::filesystem::directory_iterator(
             result["csv-dir"].as<std::string>())) {
      clc::parserType = "csv";
      if (entry.path().extension() == ".csv") {
        clc::traceFiles.push_back(entry.path().u8string());
      }
    }
    messageErrorIf(clc::traceFiles.empty(),
                   "No csv trace found in: " +
                       result["csv_dir"].as<std::string>());
  }

  if (result.count("sva")) {
    messageErrorIf(
        result.count("spotltl") || result.count("psl"),
        "sva and spotltl/psl options are mutually exclusive");
    clc::outputLang = Language::SVA;
  }

  if (result.count("sva-assert")) {
    messageErrorIf(result.count("spotltl") || result.count("psl"),
                   "sva-assert available only with --sva");
    clc::svaAssert = true;
  }

  if (result.count("psl")) {
    messageErrorIf(
        result.count("spotltl") || result.count("sva"),
        "psl and spotltl/sva options are mutually exclusive");
    clc::outputLang = Language::PSL;
  }

  if (result.count("spotltl")) {
    messageErrorIf(
        result.count("psl") || result.count("sva"),
        "spotltl and psl/sva options are mutually exclusive");
    clc::outputLang = Language::SpotLTL;
  }

  clc::genConfig = result.count("generate-config");
  clc::configFile = result["conf"].as<std::string>();
  messageErrorIf(
      !clc::genConfig && !std::filesystem::exists(clc::configFile),
      "Can not find config file '" + clc::configFile + "'");
  if (result.count("max-ass")) {
    clc::maxAss = result["max-ass"].as<size_t>();
  }
  if (result.count("min-frank")) {
    clc::minFrank = result["min-frank"].as<double>();
    messageErrorIf(clc::minFrank > 1.f || clc::minFrank < 0.f,
                   "min-frank must be between 0 and 1");
  }

  if (result.count("sample-by-con")) {
    messageErrorIf(!result.count("max-ass"),
                   "'sample-by-con' must be used with 'max-ass'");
    clc::sampleByCon = 1;
  }

  if (result.count("dump-vac-ass")) {
    clc::dumpVacAss = result["dump-vac-ass"].as<std::string>();
  }

  if (result.count("keep-vac-ass")) {
    clc::keepVacAss = 1;
  }

  if (result.count("dump-trace-as-csv")) {
    clc::dumpTraceAsCSV =
        result["dump-trace-as-csv"].as<std::string>();
  }

  if (result.count("max-threads")) {
    size_t nt = result["max-threads"].as<size_t>();
    messageErrorIf(nt == 0, "max-threads must be > 0 ");
    messageWarningIf(
        nt > std::thread::hardware_concurrency(),
        "This machine should run " +
            std::to_string(std::thread::hardware_concurrency()) +
            " threads at most");

    clc::maxThreads = nt;
    l3Constants::MAX_THREADS = nt;
    l2Constants::MAX_THREADS = nt;
    l1Constants::MAX_THREADS = nt;
  }
  //this is mostly a debug feature
  if (result.count("test-level")) {
    size_t l = result["test-level"].as<size_t>();
    messageErrorIf(l != 1 && l != 2 && l != 3,
                   "Uknown test level '" + std::to_string(l) + "'");
    if (l == 1) {
      l2Constants::MAX_THREADS = 1;
      l3Constants::MAX_THREADS = 1;
    } else if (l == 2) {
      l3Constants::MAX_THREADS = 1;
      l1Constants::MAX_THREADS = 1;
    } else if (l == 3) {
      l1Constants::MAX_THREADS = 1;
      l2Constants::MAX_THREADS = 1;
    }
  }
  if (result.count("fd")) {
    if (clc::parserType == "vcd") {
      for (const auto &entry : std::filesystem::directory_iterator(
               result["fd"].as<std::string>())) {
        if (entry.path().extension() == ".vcd") {
          clc::faultyTraceFiles.push_back(entry.path().u8string());
        }
      }
      //shuffle the faulty traces, to have an immediate potential outlook on the whole fault coverage
      std::random_shuffle(clc::faultyTraceFiles.begin(),
                          clc::faultyTraceFiles.end());

    } else if (clc::parserType == "csv") {
      for (const auto &entry : std::filesystem::directory_iterator(
               result["fd"].as<std::string>())) {
        if (entry.path().extension() == ".csv") {
          clc::faultyTraceFiles.push_back(entry.path().u8string());
        }
      }
    }

    if (result.count("find-min-subset")) {
      clc::findMinSubset = true;
    }
  }

  if (result.count("dont-normalize")) {
    clc::dontNormalize = true;
  }

  messageErrorIf(result.count("ftm") && result.count("fd"),
                 "ftm and fd options are mutually exclusive");

  if (result.count("dont-print-ass")) {
    clc::dontPrintAss = true;
  }

  if (result.count("silent")) {
    clc::silent = true;
    // disable cout
    std::cout.rdbuf(NULL);
  }
  if (result.count("isilent")) {
    clc::isilent = true;
  }
  if (result.count("wsilent")) {
    clc::wsilent = true;
  }
  if (result.count("psilent")) {
    clc::psilent = true;
  }

  if (result.count("dump-stat")) {
    clc::dumpStat = true;
  }

  if (result.count("dump-to")) {
    clc::dumpAssToFile = true;
    clc::dumpPath = result["dump-to"].as<std::string>();
    messageErrorIf(clc::dumpPath.back() == '/' &&
                       !std::filesystem::exists(clc::dumpPath),
                   "Can not find directory path '" + clc::dumpPath +
                       "'");
    clc::dumpAssSplitContexts =
        std::filesystem::is_directory(clc::dumpPath);

    if (!clc::dumpAssSplitContexts &&
        std::filesystem::exists(clc::dumpPath)) {
      std::filesystem::remove(clc::dumpPath);
      std::ofstream fs(clc::dumpPath);
      fs.close();
    }
  }

  if (result.count("include-ass")) {
    clc::includeAss = result["include-ass"].as<std::string>();
    messageErrorIf(!std::filesystem::exists(clc::includeAss),
                   "Can not find file '" + clc::includeAss + "'");
  }
  if (result.count("interactive")) {
    clc::intMode = true;
  }
  if (result.count("split-logic")) {
    clc::splitLogic = true;
  }
  messageErrorIf(clc::splitLogic && !clc::genConfig,
                 "--split-logic must be used with --generate-config");
}
void genConfigFile(std::string &configFile,
                   const TraceReaderPtr &tr) {
  messageInfo("Generating default config file");
  messageErrorIf(tr == nullptr,
                 "Trace reader module has not been set!");
  const TracePtr &trace = tr->readTrace();
  std::ofstream ofs(configFile, std::fstream::in | std::fstream::out |
                                    std::fstream::trunc);
  ofs << "<harm>"
      << "\n";
  if (clc::parserType == "vcd" && clc::vcdUnroll) {
    VCDtraceReaderPtr vcdtr =
        std::dynamic_pointer_cast<VCDtraceReader>(tr);
    auto sfn_to_sfn = vcdtr->getScopeFullName_to_SignalsFullName();

    //debug
    //print sfn_to_sfn
    //    for (auto &[scopeName, sfn] : sfn_to_sfn) {
    //      std::cout << scopeName << "\n";
    //      for (auto &name : sfn) {
    //        std::cout << "\t\t\t" << name << "\n";
    //      }
    //}

    auto mapDec = trace->getDeclarationsAsMap();

    for (auto &[scopeName, sfn] : sfn_to_sfn) {
      ofs << "\t<context name=\"" + scopeName + "\">"
          << "\n\n";

      for (auto &name : sfn) {
        const auto &type = mapDec.at(name).first;
        const auto &size = mapDec.at(name).second;
        if (clc::splitLogic && isInt(type)) {
          for (size_t i = 0; i < size; i++) {
            ofs << "\t\t<prop exp=\"";
            ofs << name + "[" + std::to_string(i) + "]";
            ofs << "\"";
            ofs << " loc=\"c,dt\"/>"
                << "\n";
          }

        } else if (size == 1) {
          // bool var
          ofs << "\t\t<prop exp=\"";
          ofs << name;
          ofs << "\"";
          ofs << " loc=\"c,dt\"/>"
              << "\n";
        } else {
          ofs << "\t\t<numeric "
                 "clustering=\"K,10Max,0.01WCSS,><,==\" exp=\"";
          ofs << name;
          ofs << "\"";
          ofs << " loc=\"c,dt\"/>"
              << "\n";
        }
      }

      ofs << "\t\t<template dtLimits=\"3D,3W,5A,-0.1E,U\" "
             "exp=\"G({..#1&..}|-> P0)\" /> "
          << "\n\n";
      ofs << "	</context>"
          << "\n";
    }

  } else {

    ofs << "\t<context name=\"default\">"
        << "\n\n";

    for (auto &dec : trace->getDeclarations()) {
      const auto &name = dec.getName();
      const auto &size = dec.getSize();
      const auto &type = dec.getType();

      if (clc::splitLogic && isInt(type)) {
        for (size_t i = 0; i < size; i++) {
          ofs << "\t\t<prop exp=\"";
          ofs << name + "[" + std::to_string(i) + "]";
          ofs << "\"";
          ofs << " loc=\"c,dt\"/>"
              << "\n";
        }

      } else if (size == 1) {
        // bool var
        ofs << "\t\t<prop exp=\"";
        ofs << name;
        ofs << "\"";
        ofs << " loc=\"c,dt\"/>"
            << "\n";
      } else {
        ofs << "\t\t<numeric clustering=\"K,10Max,0.01WCSS,><,==\" "
               "exp=\"";
        ofs << name;
        ofs << "\"";
        ofs << " loc=\"c,dt\"/>"
            << "\n";
      }
    }

    ofs << "\n\n"
        << "\n";
    ofs << "\t\t<template dtLimits=\"5D,3W,15A,-0.1E,U\" "
           "exp=\"G({..#1&..}|-> P0)\" /> "
        << "\n";
    ofs << "\n\n"
        << "\n";
    ofs << "\t\t<sort name=\"causality\" "
           "exp=\"1-afct/traceLength\"/>\n";
    ofs << "\t\t<sort name=\"frequency\" "
           "exp=\"atct/traceLength\"/>\n";
    ofs << "	</context>"
        << "\n";
  }

  ofs << "</harm>"
      << "\n";
  ofs << "\n\n"
      << "\n";
  ofs.close();
}
