#include "CSVtraceReader.hh"
#include "ManualDefinition.hh"
#include "Miner.hh"
#include "Qualifier.hh"
#include "TLMiner.hh"
#include "VCDtraceReader.hh"
#include "colors.hh"
#include "commandLineParser.hh"
#include "exp.hh"
#include "globals.hh"
#include "templateParser.hh"

#include <csignal>
#include <filesystem>
#include <string>

using namespace harm;

static void parseCommandLineArguments(int argc, char *args[]);

static void genConfigFile(std::string &configFile, TraceReader *tr);

int main(int arg, char *argv[]) {
  //enforce deterministic rand
  srand(1);

  //it holds the employed modules
  Miner::ModulesConfig config;

  parseCommandLineArguments(arg, argv);

  // trace reader
  if (clc::parserType == "vcd") {
    config.traceReader = new VCDtraceReader(clc::traceFiles, clc::clk);
  } else if (clc::parserType == "csv") {
    config.traceReader = new CSVtraceReader(clc::traceFiles);
  }

  // automatic generation of the configuration file
  if (clc::genTemp) {
    genConfigFile(clc::configFile, config.traceReader);
    messageInfo("Configuration file generated at " + clc::configFile);
    return 0;
  }

  //setting the modules
  config.contextMiner = new ManualDefinition(clc::configFile);
  config.propertyMiner = new TLMiner();
  config.propertyQualifier = new Qualifier();

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
  if (result.count("vcd-ss")) {
    clc::selectedScope = result["vcd-ss"].as<std::string>();
    clc::vcdRecursive = 0;
  }
  if (result.count("vcd-r")) {
    clc::vcdRecursive = true;
  }

  if (result.count("vcd")) {
    clc::parserType = "vcd";
    clc::traceFiles.push_back(result["vcd"].as<std::string>());
    clc::clk = result["clk"].as<std::string>();
    messageErrorIf(!std::filesystem::exists(clc::traceFiles[0]),
                   "Can not find trace file '" + clc::traceFiles[0] + "'");
  } else if (result.count("csv")) {
    clc::parserType = "csv";
    clc::traceFiles.push_back(result["csv"].as<std::string>());
    messageErrorIf(!std::filesystem::exists(clc::traceFiles[0]),
                   "Can not find trace file '" + clc::traceFiles[0] + "'");
  }

  if (result.count("vcd-dir")) {
    clc::parserType = "vcd";
    clc::clk = result["clk"].as<std::string>();
    messageErrorIf(
        !std::filesystem::is_directory(result["vcd-dir"].as<std::string>()),
        "Can not find directory '" + result["vcd-dir"].as<std::string>() + "'");
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
    messageErrorIf(
        !std::filesystem::is_directory(result["csv-dir"].as<std::string>()),
        "Can not find directory '" + result["csv-dir"].as<std::string>() + "'");
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
    clc::outputLang = "SVA";
  }

  clc::genTemp = result.count("generate-config");
  clc::configFile = result["conf"].as<std::string>();
  messageErrorIf(!clc::genTemp && !std::filesystem::exists(clc::configFile),
                 "Can not find config file '" + clc::configFile + "'");
  if (result.count("max-ass")) {
    clc::maxAss = result["max-ass"].as<size_t>();
  }

  if (result.count("max-threads")) {
    size_t nt = result["max-threads"].as<size_t>();
    messageWarningIf(nt > std::thread::hardware_concurrency(),
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

  if (result.count("ftm")) {
    clc::ftmFile = result["ftm"].as<std::string>();
    messageErrorIf(clc::ftmFile != "<all>" &&
                       !std::filesystem::exists(clc::ftmFile),
                   "Can not find '" + clc::ftmFile + "'");
  }

  if (result.count("dont-fill-ass")) {
    clc::dontFillAss = true;
  }
  if (result.count("dont-print-ass")) {
    clc::dontPrintAss = true;
  }

  if (result.count("silent")) {
    clc::silent = true;
    // disable cout
    cout.rdbuf(NULL);
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

  if (result.count("dump")) {
    clc::dumpAssToFile = true;
    clc::dumpPath = ".";
  }
  if (result.count("dump-to")) {
    clc::dumpAssToFile = true;
    clc::dumpPath = result["dump-to"].as<std::string>();
    messageErrorIf(!std::filesystem::is_directory(clc::dumpPath),
                   "Can not find directory '" + clc::dumpPath + "'");
  }
  if (result.count("interactive")) {
    clc::intMode = true;
  }
  if (result.count("splitLogic")) {
    clc::splitLogic = true;
  }
  messageErrorIf(clc::splitLogic && !clc::genTemp,
                 "--split-logic must be used with --generate-config");

  if (result.count("cls-alg")) {
    clc::clsAlg = result["cls-alg"].as<std::string>();
    messageErrorIf(clc::clsAlg != "kmeans" && clc::clsAlg != "kde" &&
                       clc::clsAlg != "hc",
                   "Unknown clustering algorithm '" + clc::clsAlg + "'");
  }
}
///Automatically generates a config file only using the input trace
void genConfigFile(std::string &configFile, TraceReader *tr) {
  messageInfo("Generating default config file");
  messageErrorIf(tr == nullptr, "Trace reader module has not been set!");
  Trace *trace = tr->readTrace();
  std::ofstream ofs(configFile,
                    std::fstream::in | std::fstream::out | std::fstream::trunc);

  ofs << "<harm>"
      << "\n";
  ofs << "\t<context name=\"default\">"
      << "\n\n";

  // a
  for (auto &dec : trace->getDeclarations()) {
    if (clc::splitLogic && (std::get<1>(dec) == VarType::SLogic ||
                            std::get<1>(dec) == VarType::ULogic)) {
      for (size_t i = 0; i < std::get<2>(dec); i++) {
        ofs << "\t\t<prop exp=\"";
        ofs << std::get<0>(dec) + "[" + std::to_string(i) + "]";
        ofs << "\"";
        ofs << " loc=\"a\"/>"
            << "\n";
      }

    } else if (std::get<2>(dec) == 1) {
      // bool var
      ofs << "\t\t<prop exp=\"";
      ofs << std::get<0>(dec);
      ofs << "\"";
      ofs << " loc=\"a\"/>"
          << "\n";
    } else {
      ofs << "\t\t<numeric clsEffort=\"0.3\" exp=\"";
      ofs << std::get<0>(dec);
      ofs << "\"";
      ofs << " loc=\"a\"/>"
          << "\n";
    }
  }

  // dt
  for (auto &dec : trace->getDeclarations()) {
    if (clc::splitLogic && (std::get<1>(dec) == VarType::SLogic ||
                            std::get<1>(dec) == VarType::ULogic)) {
      for (size_t i = 0; i < std::get<2>(dec); i++) {
        ofs << "\t\t<prop exp=\"";
        ofs << std::get<0>(dec) + "[" + std::to_string(i) + "]";
        ofs << "\"";
        ofs << " loc=\"dt\"/>"
            << "\n";
      }

    } else if (std::get<2>(dec) == 1) {
      // bool var
      ofs << "\t\t<prop exp=\"";
      ofs << std::get<0>(dec);
      ofs << "\"";
      ofs << " loc=\"dt\"/>"
          << "\n";
    } else {
      ofs << "\t\t<numeric clsEffort=\"0.3\" exp=\"";
      ofs << std::get<0>(dec);
      ofs << "\"";
      ofs << " loc=\"dt\"/>"
          << "\n";
    }
  }

  // c
  for (auto &dec : trace->getDeclarations()) {
    if (clc::splitLogic && (std::get<1>(dec) == VarType::SLogic ||
                            std::get<1>(dec) == VarType::ULogic)) {
      for (size_t i = 0; i < std::get<2>(dec); i++) {
        ofs << "\t\t<prop exp=\"";
        ofs << std::get<0>(dec) + "[" + std::to_string(i) + "]";
        ofs << "\"";
        ofs << " loc=\"c\"/>"
            << "\n";
      }

    } else if (std::get<2>(dec) == 1) {
      // bool var
      ofs << "\t\t<prop exp=\"";
      ofs << std::get<0>(dec);
      ofs << "\"";
      ofs << " loc=\"c\"/>"
          << "\n";
    } else {
      ofs << "\t\t<numeric clsEffort=\"0.3\" exp=\"";
      ofs << std::get<0>(dec);
      ofs << "\"";
      ofs << " loc=\"c\"/>"
          << "\n";
    }
  }

  ofs << "\n\n"
      << "\n";
  ofs << "\t\t<template dtLimits=\"3A,-0.1E\" exp=\"G({..&&..}|-> "
         "X(P0))\" /> "
      << "\n";
  ofs << "\t\t<template dtLimits=\"3D,3W,3A,-0.1E,R\" "
         "exp=\"G({..#1&..}|-> X(P0))\" /> "
      << "\n";
  ofs << "\t\t<template dtLimits=\"3A,-0.1E,R\" "
         "exp=\"G({..##1..}|-> X(P0))\" /> "
      << "\n";
  ofs << "\t\t<template dtLimits=\"3D,3W,3A,-0.1E,S\" "
         "exp=\"G({..#1&..}|-> X(P0))\" /> "
      << "\n";
  ofs << "\t\t<template dtLimits=\"3A,-0.1E,S\" "
         "exp=\"G({..##1..}|-> X(P0))\" /> "
      << "\n";
  ofs << "\n\n"
      << "\n";

  //  FIXME: do we need this?
  //  ofs << "\t<filter name=\"causality\" exp=\"1-afct/traceLength\" "
  //         "threshold=\"0.5\"/>\n";
  //  ofs << "\t<filter name=\"complexity\" exp=\"complexity\"
  //  threshold=\"3\"/>\n"; ofs << "\t<filter name=\"pRepetitions\"
  //  exp=\"1/(pRepetitions+1)\" "
  //         "threshold=\"0.99\"/>\n";
  ofs << "\t\t<sort name=\"causality\" exp=\"1-afct/traceLength\"/>\n";
  ofs << "\t\t<sort name=\"frequency\" exp=\"atct/traceLength\"/>\n";
  ofs << "	</context>"
      << "\n";
  ofs << "</harm>"
      << "\n";
  ofs << "\n\n"
      << "\n";

  ofs.close();
}
