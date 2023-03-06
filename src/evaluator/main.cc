#include "CSVtraceReader.hh"
#include "ProgressBar.hpp"
#include "TraceReader.hh"
#include "VCDtraceReader.hh"
#include "commandLineParser.hh"
#include "csv.hpp"
#include "evaluator.hh"
#include "globals.hh"
#include <filesystem>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <random>
#include <string>
#include <vector>

using namespace harm;
using namespace expression;

void tokenizeString(std::string const &str, const char delim,
                    std::vector<std::string> &out) {
  char *token = strtok(const_cast<char *>(str.c_str()), &delim);
  while (token != nullptr) {
    out.push_back(std::string(token));
    token = strtok(nullptr, &delim);
  }
}

void parseCommandLineArguments(int argc, char *args[]);
void dumpDiffs(const std::unordered_map<std::string, Diff> &tokenToDiff,
               size_t id = -1) {

  std::string fileName = clc::ve_dumpTo + "/" + std::string("diff_") +
                         (id == -1 ? "" : std::to_string(id) + "_") +
                         clc::ve_technique + ".csv";

  std::ofstream outDiff(fileName);
  outDiff << "token; atcf; instances\n";
  for (auto &[token, diff] : tokenToDiff) {
    outDiff << token << ";" << diff._atcf << ";";
    for (auto &ci : diff._coveredInstances) {
      outDiff << ci << " ";
    }
    outDiff << "\n";
  }
  outDiff.close();
}

void recoverDiffs(std::unordered_map<std::string, Diff> &tokenToDiff,
                  size_t id = -1) {

  std::string fileName = clc::ve_dumpTo + "/" + std::string("diff_") +
                         (id == -1 ? "" : std::to_string(id) + "_") +
                         clc::ve_technique + ".csv";

  csv::CSVFormat format;
  format.delimiter(';');
  messageErrorIf(!std::filesystem::exists(fileName),
                 "Could not find: " + fileName);

  csv::CSVReader reader(fileName, format);

  csv::CSVRow row;

  while (reader.read_row(row)) {
    tokenToDiff[row[0].get()]._atcf = std::stoull(row[1].get());
    std::vector<std::string> instances;
    tokenizeString(row[2].get(), ' ', instances);
    for (auto &inst : instances) {
      tokenToDiff[row[0].get()]._coveredInstances.insert(inst);
    }
  }

  //debug -- print diffs
  //for (auto &[token, diff] : tokenToDiff) {
  //  std::cout << token << ": ";
  //  for (auto inst : diff._coveredInstances) {
  //    std::cout << inst << " ";
  //  }
  //  std::cout << "\n";
  //}
  if (id != -1) {
    std::filesystem::remove(std::filesystem::path(fileName));
  }
}
void getDiffParallel(Trace *trace, std::vector<std::string> &assStrs,
                     std::unordered_map<std::string, Diff> &tokenToDiff,
                     size_t i, size_t nProcs) {

  // convert string to Template
  std::vector<Template *> assertions =
      parseAssertions(assStrs, trace, i * clc::ve_chunkSize, clc::ve_chunkSize);
  std::unordered_map<std::string, std::vector<Template *>> tokenToAss;
  std::unordered_map<std::string, size_t> tokenToSize;
  std::vector<std::string> tokens;

  if (clc::ve_technique == "sr") {
    //Statement reduction
    for (size_t i = 0; i < clc::ve_nStatements; i++) {
      tokens.push_back("s" + std::to_string(i));
    }
  } else if (clc::ve_technique == "vbr") {
    //Variable Bit reduction
    csv::CSVReader reader(clc::ve_infoList);
    csv::CSVRow row;
    while (reader.read_row(row)) {
      tokens.push_back(row[0].get());
      tokenToSize[row[0].get()] = std::stoul(row[1].get());
    }
  } else if (clc::ve_technique == "br") {
    //Bit reduction
    csv::CSVReader reader(clc::ve_infoList);
    csv::CSVRow row;
    while (reader.read_row(row)) {
      tokens.push_back(row[0].get());
      tokenToSize[row[0].get()] = std::stoul(row[1].get());
    }
  }

  size_t elaborated = 0;
  size_t runningProcesses = 0;
  pid_t pids[tokens.size()];
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(1, std::string("Evaluating assertions... "), tokens.size(),
                 70);
  pb.display();

  while (elaborated < tokens.size()) {
    runningProcesses++;
    pids[elaborated] = fork();
    if (pids[elaborated] == 0) {
      std::vector<std::string> selectedTokens;
      selectedTokens.push_back(tokens[elaborated]);

      if (clc::ve_technique == "vbr") {
        getDiffVBR(tokenToDiff, tokenToSize, selectedTokens, assertions, 0);
      } else if (clc::ve_technique == "br") {
        getDiffBR(tokenToDiff, tokenToSize, selectedTokens, assertions, 0);
      } else if (clc::ve_technique == "sr") {
        getDiffSR(tokenToDiff, selectedTokens, assertions, 0);
      }

      dumpDiffs(tokenToDiff, elaborated);
      exit(0);
    }
    while (runningProcesses == nProcs ||
           (elaborated == tokens.size() - 1 && runningProcesses > 0)) {
      int status;
      waitpid(-1, &status, 0);
      messageErrorIf(!WIFEXITED(status) || WEXITSTATUS(status) != 0,
                     "Child failed!");
      runningProcesses--;
      pb.increment(1);
      pb.display();
    }
    elaborated++;
  }
  pb.done(1);

  for (size_t j = 0; j < tokens.size(); j++) {
    recoverDiffs(tokenToDiff, j);
  }

  //debug - print instances
  //for (auto &[token, diff] : tokenToDiff) {
  //  std::cout << "[" << token << "]"
  //            << "\n";
  //  for (auto ci : diff._coveredInstances) {
  //    std::cout << ci << " ";
  //  }
  //  std::cout << "\n";
  //}

  // delete processed assertions
  for (Template *a : assertions) {
    delete a;
  }
}

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

  std::unordered_map<std::string, Diff> tokenToDiff;

  if (!clc::ve_recover_diff) {
    //get diffs

    // allocate trace
    harm::Trace *trace = traceReader->readTrace();

    auto assStrs = readAssertions(clc::ve_assPath);

    int evaluated = 0;
    // eval the assertions one chunk at a time (to avoid memory explosion)
    for (size_t i = 0; ((int)assStrs.size() - evaluated) > 0; i++) {
      std::cout << evaluated << "/" << assStrs.size() << " evaluated\n";
      getDiffParallel(trace, assStrs, tokenToDiff, i, 16);
      // update the amount of evaluated assertions
      evaluated += clc::ve_chunkSize;
    }
    delete trace;
  }

  if (clc::ve_recover_diff) {
    recoverDiffs(tokenToDiff);
  } else {
    dumpDiffs(tokenToDiff);
  }

  //abs
  dumpScore(tokenToDiff, 0);

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

  if (result.count("recover-diff")) {
    clc::ve_recover_diff = 1;
  }

  if (result.count("recover-cls")) {
    clc::ve_recover_cls = 1;
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
    messageErrorIf(clc::ve_technique != "sr" && clc::ve_technique != "vbr" &&
                       clc::ve_technique != "br",
                   "Unknown technique");
    std::cout << "Technique: " << clc::ve_technique << "\n";
  }
  if (result.count("cls-type")) {
    clc::ve_cls_type = result["cls-type"].as<std::string>();
    messageErrorIf(clc::ve_cls_type != "rand" && clc::ve_cls_type != "comb" &&
                       clc::ve_cls_type != "nsga2" &&
                       clc::ve_cls_type != "kmeans" &&
                       clc::ve_cls_type != "nsga2pop",
                   "Unknown clustering technique");
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
  if (result.count("nsga2-mi")) {
    clc::ve_nsga2_mi = std::stod(result["nsga2-mi"].as<std::string>());
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
  messageErrorIf(
      clc::ve_technique == "sr" && clc::ve_nStatements <= 0,
      "You must specify the number of statements for the sr technique");
}
