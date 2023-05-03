#include "CSVtraceReader.hh"
#include "ProgressBar.hpp"
#include "TraceReader.hh"
#include "VCDtraceReader.hh"
#include "commandLineParser.hh"
#include "csv.hpp"
#include "evaluator.hh"
#include "globals.hh"
#include "utils.hh"
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

  std::string fileName = clc::ve_ftPath + "/" + std::string("diff_") +
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

  std::string fileName = clc::ve_ftPath + "/" + std::string("diff_") +
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

  for (auto &[at, diff] : tokenToDiff) {
    tokens.push_back(at);
  }
  std::cout << "Number of tokens: " << tokens.size() << "\n";

  //gather time units where ant is true on the golden trace
  std::vector<std::pair<harm::Template *, std::vector<size_t>>>
      assertionsWithAntInstances;
  for (auto &ass : assertions) {
    assertionsWithAntInstances.emplace_back(ass, std::vector<size_t>());
    for (size_t i = 0; i < ass->_trace->getLength(); i++) {
      if (ass->evaluateAntNoCache(i) == Trinary::T) {
        assertionsWithAntInstances.back().second.push_back(i);
      }
    }
  }

  progresscpp::ParallelProgressBar pb;
  pb.addInstance(1, std::string("Evaluating assertions... "), tokens.size(),
                 70);
  pb.display();

  size_t elaborated = 0;
  size_t runningProcesses = 0;
  pid_t pids[tokens.size()];

  while (elaborated < tokens.size()) {
    runningProcesses++;
    pids[elaborated] = fork();
    if (pids[elaborated] == 0) {
      std::vector<std::string> selectedTokens;
      selectedTokens.push_back(tokens[elaborated]);

      getDiff(tokenToDiff, selectedTokens, assertionsWithAntInstances,
              elaborated, 0);
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

void stopExecution(int s) {
  clc::ve_stopExecution = 1;
  std::cout << "Halting request received!"
            << "\n";
}

int main(int arg, char *argv[]) {
  srand(1);
  //signal(SIGINT, stopExecution);

  size_t secondsEvaluate = 0;
  parseCommandLineArguments(arg, argv);

  std::unordered_map<std::string, Diff> tokenToDiff;

  dirtyTimerSeconds("startEvaluate", 1);

  if (!clc::ve_recover_diff) {

    //gather at from file
    std::fstream ass(clc::ve_atList);
    std::string line = "";
    while (std::getline(ass, line)) {
      tokenToDiff[line];
    }

    //get diffs

    // allocate trace
    std::string goldenTracePath = clc::ve_ftPath + "/golden" +
                                  (clc::parserType == "vcd" ? ".vcd" : ".csv");
    if (!std::filesystem::exists(goldenTracePath)) {
      //simulate
      messageInfo("Simulating golden design to retrieve the golden trace...");
      systemCustom("bash " + clc::ve_shPath + " golden " + clc::ve_ftPath +
                   (clc::ve_debugScript ? "" : " > /dev/null"));

      messageErrorIf(!std::filesystem::exists(goldenTracePath),
                     "Can not find golden trace after simulating");
    }

    Trace *trace = parseTrace(goldenTracePath);

    auto assStrs = readAssertionsFromFile(clc::ve_assPath);

    int evaluated = 0;
    // eval the assertions one chunk at a time (to avoid memory explosion)
    for (size_t i = 0; ((int)assStrs.size() - evaluated) > 0; i++) {
      std::cout << evaluated << "/" << assStrs.size() << " evaluated\n";
      getDiffParallel(trace, assStrs, tokenToDiff, i, clc::maxThreads);
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

  //dump temporal statistics
  {
    secondsEvaluate = dirtyTimerSeconds("startEvaluate", 0);
    std::ofstream outfile(clc::ve_dumpTo + "/" + clc::ve_technique + "_" +
                          "time.csv");
    outfile << "timeToEvaluate;timeClusterigP1;timeClusterigP2" << std::endl;
    outfile << secondsEvaluate << ";";
    outfile.close();
  }

  //abs
  cluster(tokenToDiff, 0);

  return 0;
}

void parseCommandLineArguments(int argc, char *args[]) {
  auto result = parseDEA(argc, args);

  if (result.count("fd")) {
    clc::ve_ftPath = result["fd"].as<std::string>();
  }

  if (result.count("at-list")) {
    clc::ve_atList = result["at-list"].as<std::string>();
  }

  if (result.count("bash")) {
    clc::ve_shPath = result["bash"].as<std::string>();
    messageErrorIf(!std::filesystem::exists(clc::ve_shPath),
                   "Can not find script '" + clc::ve_shPath + "'");
  }

  if (result.count("recover-diff")) {
    clc::ve_recover_diff = 1;
  }

  if (result.count("plot-dominance")) {
    clc::ve_plotDominance = 1;
  }

  if (result.count("gen-rand")) {
    clc::ve_genRand = 1;
  }

  if (result.count("push")) {
    clc::ve_push = 1;
  }
  if (result.count("only-sim")) {
    clc::ve_only_sim = 1;
  }

  if (result.count("debug-script")) {
    clc::ve_debugScript = 1;
  }

  if (result.count("ass-file")) {
    clc::ve_assPath = result["ass-file"].as<std::string>();
    messageErrorIf(!std::filesystem::exists(clc::ve_assPath),
                   "Can not find assertion file '" + clc::ve_assPath + "'");
  }

  if (result.count("max-clusters")) {
    messageErrorIf(clc::ve_cls_type != "kmeans",
                   "The cluster option must be used with 'kmeans'");
    clc::ve_maxClusters = std::stol(result["cluster"].as<std::string>());
    std::cout << "Clusters: " << clc::ve_maxClusters << "\n";
  }

  if (result.count("max-push-time")) {
    clc::ve_maxPushTime = result["max-push-time"].as<size_t>();
  }
  if (result.count("min-push-time")) {
    clc::ve_minPushTime = result["min-push-time"].as<size_t>();
  }
  if (result.count("min-time")) {
    clc::ve_minTime = result["min-time"].as<size_t>();
  }
  if (result.count("tech")) {
    clc::ve_technique = result["tech"].as<std::string>();
  }
  if (result.count("metric-name")) {
    clc::ve_metricName = result["metric-name"].as<std::string>();
  }
  if (result.count("cls-type")) {
    clc::ve_cls_type = result["cls-type"].as<std::string>();
    messageErrorIf(clc::ve_cls_type != "nsga2" && clc::ve_cls_type != "kmeans",
                   "Unknown clustering technique");
  }
  if (result.count("dump-to")) {
    clc::ve_dumpTo = result["dump-to"].as<std::string>();
    messageErrorIf(!std::filesystem::is_directory(clc::ve_dumpTo),
                   "Could not find directory '" + clc::ve_dumpTo + "'");
  }

  if (result.count("vcd")) {
    clc::parserType = "vcd";
  }
  if (result.count("csv")) {
    clc::parserType = "csv";
  }
  if (result.count("cs")) {
    clc::ve_chunkSize = std::stoul(result["cs"].as<std::string>());
    std::cout << "Chunk size: " << clc::ve_chunkSize << "\n";
  }
  if (result.count("nsga2-mi")) {
    clc::ve_nsga2_mi = std::stod(result["nsga2-mi"].as<std::string>());
  }
  if (result.count("clk")) {
    clc::clk = result["clk"].as<std::string>();
  }

  if (result.count("max-threads")) {
    size_t nt = result["max-threads"].as<size_t>();
    messageWarningIf(nt > std::thread::hardware_concurrency(),
                     "This machine should run " +
                         std::to_string(std::thread::hardware_concurrency()) +
                         " threads at most");
    clc::maxThreads = nt;
  }

  if (result.count("metric-direction")) {
    clc::ve_metricDirection = result["metric-direction"].as<size_t>();
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

  std::cout << "Assertion file: " << clc::ve_assPath << "\n";
  std::cout << "Script: " << clc::ve_shPath << "\n";
  std::cout << "Technique: " << clc::ve_technique << "\n";
  std::cout << "Trace type: " << clc::parserType << "\n";
  std::cout << "Dump to: " << clc::ve_dumpTo << "\n";
  std::cout << "Faulty traces directory: " << clc::ve_ftPath << "\n";
}
