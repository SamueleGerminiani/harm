#include "TraceReader.hh"
#include "VCDtraceReader.hh"
#include "commandLineParser.hh"
#include "csv.hpp"
#include "globals.hh"
#include "varEstimator.hh"
#include <filesystem>
#include <random>

using namespace harm;
using namespace expression;

void parseCommandLineArguments(int argc, char *args[]);

int main(int arg, char *argv[]) {
  parseCommandLineArguments(arg, argv);

  TraceReader *traceReader = new VCDtraceReader(clc::ve_tracePath, clc::clk);

  // allocate trace
  harm::Trace *trace = traceReader->readTrace();

  auto assStrs = readAssertions(clc::ve_assPath);

  std::unordered_map<std::string, Diff> tokenToDiff;

  int evaluated = 0;
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
        getDiffSR(tokenToDiff, stmToAss);
      } else if(clc::ve_technique == "vbr") {
          //Variable Bit reduction
          std::unordered_map<std::string, std::vector<Template *>> varToAss;
          std::unordered_map<std::string, size_t> varToSize;
        csv::CSVReader reader(clc::ve_varMap);
        csv::CSVRow row;
        varToAss[reader.get_col_names()[1]] = assertions;
        varToSize[reader.get_col_names()[1]] =
            std::stoul(reader.get_col_names()[2]);
        while (reader.read_row(row)) {
          varToAss[row[1].get()] = assertions;
          varToSize[row[1].get()] = std::stoul(row[2].get());
        }

        getDiffVBR(tokenToDiff, varToSize, varToAss, trace);
      }
    

    // delete processed assertions
    for (Template *a : assertions) {
      delete a;
    }
    // update the amount of evaluated assertions
    evaluated += clc::ve_chunkSize;
  }

  //abs
  dumpScore(tokenToDiff,0);
  //norm
  dumpScore(tokenToDiff,1);

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
  }
    messageErrorIf(clc::faultyTraceFiles.empty(), "No faulty traces found!");

  if (result.count("var-map")) {
      clc::ve_varMap = result["var-map"].as<std::string>();
  }

  messageErrorIf(clc::ve_technique=="vbr" && !result.count("var-map") , "No var-map specified");


  if (result.count("ass-path")) {
    clc::ve_assPath = result["path"].as<std::string>();
    std::cout << "Path: " << clc::ve_assPath << "\n";
  }
  if (result.count("cluster")) {
    clc::ve_cluster = std::stoul(result["cluster"].as<std::string>());
    std::cout << "Clusters: " << clc::ve_cluster << "\n";
    clc::ve_cluster = clc::ve_cluster > 0 ? clc::ve_cluster : 1;
  }
  if (result.count("nStatements")) {
    std::cout << "nStatements: " << result["nStatements"].as<size_t>()<< "\n";
    clc::ve_nStatements = result["nStatements"].as<size_t>();
  }
  if (result.count("technique")) {
    clc::ve_technique = result["technique"].as<std::string>();
    messageErrorIf(clc::ve_technique!="sr" && clc::ve_technique!="vbr", "Unknown technique");
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

  if (result.count("vcd")) {
    clc::ve_tracePath = result["vcd"].as<std::string>();
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
