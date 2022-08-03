#include "TraceReader.hh"
#include "VCDtraceReader.hh"
#include "commandLineParser.hh"
#include "globals.hh"
#include "varEstimator.hh"
#include "csv.hpp"
#include <filesystem>
#include <random>

using namespace harm;
using namespace expression;

void parseCommandLineArguments(int argc, char *args[]);

int main(int arg, char *argv[]) {
  parseCommandLineArguments(arg, argv);
  l1Constants::MAX_THREADS = 2;

  TraceReader *traceReader = new VCDtraceReader(clc::ve_tracePath, clc::clk);

  // allocate trace
  harm::Trace *trace = traceReader->readTrace();

  auto assStrs = readAssertions(clc::ve_assPath);
  size_t th = 100000000000;
  if (assStrs.size() > th) {
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(assStrs), std::end(assStrs), rng);
    assStrs.erase(assStrs.begin() + th, assStrs.end());
  }
  std::unordered_map<std::string, Diff> varToDiff;

  int evaluated = 0;
  // eval the assertions one chunck at a time (to avoid memory explosion)
  for (size_t i = 0; ((int)assStrs.size() - evaluated) > 0; i++) {
    std::cout << evaluated << "/" << assStrs.size() << " evaluated\n";

    // convert string to Template
    std::vector<Template *> assertions = parseAssertions(
        assStrs, trace, i * clc::ve_chunkSize, clc::ve_chunkSize);

    std::unordered_map<std::string, std::vector<Template *>> varToAss;
    std::unordered_map<std::string, size_t> varToSize;
    if (clc::ve_oo && !clc::faultyTraceFiles.empty()) {
      //auto vars = trace->getVariables();
        csv::CSVReader reader(clc::vars);
        csv::CSVRow row;
        std::vector<std::string> vars;
        while (reader.read_row(row)) {
//        std::cout << row[1].get() <<" "<<row[2].get()<< "\n";
            varToAss[row[1].get()] = assertions;
            varToSize[row[1].get()] = std::stoul(row[2].get());

        }

    } else {
      varToAss = discardAssertionsGroupBy(assertions, clc::ve_inAnt ? 0 : 1);
    }

    if (clc::faultyTraceFiles.empty()) {
      getDiff(varToDiff, varToAss, trace, clc::ve_inAnt ? 0 : 1);
    } else {
      getDiffFT(varToDiff,varToSize, varToAss, trace);
    }

    // delete processed assertions
    for (Template *a : assertions) {
      delete a;
    }
    // update the amount of evaluated assertions
    evaluated += clc::ve_chunkSize;
  }

  // absolute
  dumpScore(varToDiff, clc::ve_sa, clc::ve_cluster, 0, clc::ve_consecutive,
            clc::ve_inAnt);
  // normalized
  dumpScore(varToDiff, clc::ve_sa, clc::ve_cluster, 1, clc::ve_consecutive,
            clc::ve_inAnt);

  delete trace;
  return 0;
}

void parseCommandLineArguments(int argc, char *args[]) {
  auto result = parseVarEstimator(argc, args);

  if (result.count("fd")) {
    clc::ftPath = result["fd"].as<std::string>();
    for (const auto &entry :
         std::filesystem::directory_iterator(result["fd"].as<std::string>())) {
      if (entry.path().extension() == ".vcd") {
        clc::faultyTraceFiles.push_back(entry.path().u8string());
      }
    }
    messageErrorIf(clc::faultyTraceFiles.empty(), "No ft found!");
  }
  if (result.count("vars")) {
    clc::vars = result["vars"].as<std::string>();
  }
  if (result.count("oo")) {
    clc::ve_oo = 1;
  }

  if (result.count("path")) {
    clc::ve_assPath = result["path"].as<std::string>();
    std::cout << "Path: " << clc::ve_assPath << "\n";
  }
  if (result.count("cluster")) {
    clc::ve_cluster = std::stoul(result["cluster"].as<std::string>());
    std::cout << "Clusters: " << clc::ve_cluster << "\n";
    clc::ve_cluster = clc::ve_cluster > 0 ? clc::ve_cluster : 1;
  }
  if (result.count("technique")) {
    clc::ve_technique = result["technique"].as<std::string>();
    std::cout << "Technique: " << clc::ve_technique << "\n";
  }
  if (result.count("ant")) {
    clc::ve_inAnt = 1;
    std::cout << "Place: "
              << "Ant"
              << "\n";
  } else {
    clc::ve_inAnt = 0;
    std::cout << "Place: "
              << "Con"
              << "\n";
  }
  if (result.count("consec")) {
    clc::ve_consecutive = 1;
    std::cout << "Consecutive: "
              << "Yes"
              << "\n";
  } else {
    std::cout << "Consecutive: "
              << "No"
              << "\n";
  }
  if (result.count("sa")) {
    if (result["sa"].as<std::string>() == "0") {
      clc::ve_sa = 0;
    } else if (result["sa"].as<std::string>() == "1") {
      clc::ve_sa = 1;
    } else if (result["sa"].as<std::string>() == "x") {
      clc::ve_sa = 2;
    } else {
      messageError("Unknown stuck at option!");
    }
    std::cout << "Stuck at: " << result["sa"].as<std::string>() << "\n";
  }

  if (result.count("vcd")) {
    clc::ve_tracePath = result["vcd"].as<std::string>();
    std::cout << "Trace path: " << clc::ve_tracePath << "\n";
  }
  if (result.count("cs")) {
    clc::ve_chunkSize = std::stoul(result["cs"].as<std::string>());
    std::cout << "Chunk size: " << clc::ve_chunkSize << "\n";
  }
  if (result.count("clk")) {
    clc::clk = result["clk"].as<std::string>();
    std::cout << "clk: " << clc::clk << "\n";
  }

  if (result.count("max_threads")) {
    size_t nt = result["max_threads"].as<size_t>();
    messageWarningIf(nt > std::thread::hardware_concurrency(),
                     "This machine should run " +
                         std::to_string(std::thread::hardware_concurrency()) +
                         " threads at most");
    clc::maxThreads = nt;
    l3Constants::MAX_THREADS = nt;
    l2Constants::MAX_THREADS = nt;
    l1Constants::MAX_THREADS = nt;
  }
}
