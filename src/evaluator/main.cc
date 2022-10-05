#include "CSVtraceReader.hh"
#include "TraceReader.hh"
#include "VCDtraceReader.hh"
#include "commandLineParser.hh"
#include "csv.hpp"
#include "globals.hh"
#include "evaluator.hh"
#include <filesystem>
#include <random>

using namespace harm;
using namespace expression;

void parseCommandLineArguments(int argc, char *args[]);

int main(int arg, char *argv[]) {
  parseCommandLineArguments(arg, argv);

  TraceReader *traceReader = nullptr;
  if (clc::parserType == "vcd") {
    traceReader = new VCDtraceReader(clc::ve_tracePath, clc::clk);
  } else if (clc::parserType == "csv") {
    traceReader = new CSVtraceReader(clc::ve_tracePath);
  } else {
    messageError("Unknown parser type");
  }

  // allocate trace
  harm::Trace *trace = traceReader->readTrace();

  auto assStrs = readAssertions(clc::ve_assPath);

  std::unordered_map<std::string, Diff> tokenToDiff;

  int evaluated = 0;
  std::unordered_map<std::string, std::vector<std::string>> tokenToFailingAssertions;
  // eval the assertions one chunck at a time (to avoid memory explosion)
  for (size_t i = 0; ((int)assStrs.size() - evaluated) > 0; i++) {
    std::cout << evaluated << "/" << assStrs.size() << " evaluated\n";

    // convert string to Template
    std::vector<Template *> assertions = parseAssertions(
        assStrs, trace, i * clc::ve_chunkSize, clc::ve_chunkSize);

    if (clc::ve_technique == "sr") {
      //Statement reduction
      std::unordered_map<std::string, std::vector<Template *>> stmToAss;
      for (size_t i = 0; i < clc::ve_nStatements; i++) {
        stmToAss["s" + std::to_string(i)] = assertions;
      }
      getDiffSR(tokenToDiff, stmToAss, tokenToFailingAssertions);
    } else if (clc::ve_technique == "vbr") {
      //Variable Bit reduction
      std::unordered_map<std::string, std::vector<Template *>> varToAss;
      std::unordered_map<std::string, size_t> varToSize;
      csv::CSVReader reader(clc::ve_infoList);
      csv::CSVRow row;
      while (reader.read_row(row)) {
        varToAss[row[0].get()] = assertions;
        varToSize[row[0].get()] = std::stoul(row[1].get());
      }

      getDiffVBR(tokenToDiff, varToSize, varToAss);
    } else if (clc::ve_technique == "br") {
      //Bit reduction
      std::unordered_map<std::string, std::vector<Template *>> idToAss;
      std::unordered_map<std::string, size_t> idToSize;
      csv::CSVReader reader(clc::ve_infoList);
      csv::CSVRow row;
      while (reader.read_row(row)) {
        idToAss[row[0].get()] = assertions;
        idToSize[row[0].get()] = std::stoul(row[1].get());
      }

      getDiffBR(tokenToDiff, idToSize, idToAss);
    }

    // delete processed assertions
    for (Template *a : assertions) {
      delete a;
    }
    // update the amount of evaluated assertions
    evaluated += clc::ve_chunkSize;
  }

  //abs
  dumpScore(tokenToDiff, 0);
  //norm
  dumpScore(tokenToDiff, 1);

  if (clc::ve_print_failing_ass) {
    for (auto &[t, ass] : tokenToFailingAssertions) {
      std::cout << t << std::endl;
      for (auto &a : ass) {
        std::cout << "\t\t\t" << a << std::endl;
      }
    }
  }

  delete trace;
  return 0;
}

void parseCommandLineArguments(int argc, char *args[]) {
  auto result = parseVarEstimator(argc, args);

  if (result.count("fd")) {
    if (result.count("vcd")) {
      clc::ve_ftPath = result["fd"].as<std::string>();
      for (const auto &entry : std::filesystem::directory_iterator(
               result["fd"].as<std::string>())) {
        if (entry.path().extension() == ".vcd") {
          clc::faultyTraceFiles.push_back(entry.path().u8string());
        }
      }

    } else if (result.count("csv")) {
      clc::ve_ftPath = result["fd"].as<std::string>();
      for (const auto &entry : std::filesystem::directory_iterator(
               result["fd"].as<std::string>())) {
        if (entry.path().extension() == ".csv") {
          clc::faultyTraceFiles.push_back(entry.path().u8string());
        }
      }
    }
  }
  messageErrorIf(clc::faultyTraceFiles.empty(), "No faulty traces found!");

  if (result.count("info-list")) {
    clc::ve_infoList = result["info-list"].as<std::string>();
  }
  if (result.count("print-failing-ass")) {
    clc::ve_print_failing_ass = 1;
  }


  if (result.count("ass-file")) {
    clc::ve_assPath = result["ass-file"].as<std::string>();
    std::cout << "Path: " << clc::ve_assPath << "\n";
  }
  if (result.count("cluster")) {
    clc::ve_cluster = std::stol(result["cluster"].as<std::string>());
    std::cout << "Clusters: " << clc::ve_cluster << "\n";
  }
  if (result.count("n-stm")) {
    std::cout << "nStatements: " << result["n-stm"].as<size_t>() << "\n";
    clc::ve_nStatements = result["n-stm"].as<size_t>();
  }
  if (result.count("tech")) {
    clc::ve_technique = result["tech"].as<std::string>();
    messageErrorIf(clc::ve_technique != "sr" && clc::ve_technique != "vbr" && clc::ve_technique != "br",
                   "Unknown technique");
    std::cout << "Technique: " << clc::ve_technique << "\n";
  }
  if (result.count("dump-to")) {
    clc::ve_dumpTo = result["dump-to"].as<std::string>();
    std::cout << "Dump to path: " << clc::ve_dumpTo << "\n";
  }

  if (result.count("vcd")) {
    clc::parserType = "vcd";
    clc::ve_tracePath = result["vcd"].as<std::string>();
    std::cout << "Trace path: " << clc::ve_tracePath << "\n";
  }
  if (result.count("csv")) {
    clc::parserType = "csv";
    clc::ve_tracePath = result["csv"].as<std::string>();
    std::cout << "Trace path: " << clc::ve_tracePath << "\n";
  }
  if (result.count("cs")) {
    clc::ve_chunkSize = std::stoul(result["cs"].as<std::string>());
  }
  std::cout << "Chunk size: " << clc::ve_chunkSize << "\n";
  if (result.count("clk")) {
    clc::clk = result["clk"].as<std::string>();
    std::cout << "clk: " << clc::clk << "\n";
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

  messageErrorIf(clc::ve_technique == "vbr" && !result.count("info-list"),
                 "No info-list specified");
  messageErrorIf(clc::ve_technique == "br" && !result.count("info-list"),
                 "No info-list specified");
  messageErrorIf(clc::ve_technique == "sr" && clc::ve_nStatements<=0,
                 "You must specify the number of statements for the sr technique");

}
