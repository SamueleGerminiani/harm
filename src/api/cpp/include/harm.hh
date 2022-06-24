#pragma once
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace harm {
class Assertion;
struct Parameters {
  std::vector<std::string> traceFiles;
  std::vector<std::string> faultyTraceFiles;
  std::string configFile;
  std::string parserType;
  std::string clk;
  bool genTemp;
  size_t maxThreads = std::thread::hardware_concurrency();
  bool findMinSubset = false;
  bool dumpAssToFile = false;
  bool noData = false;
  std::string dumpPath = "";
  bool intMode = false;
  bool splitLogic = false;
  bool vcdRecursive = true;
  std::string selectedScope = "";
  bool dontFillAss = false;
  bool dontPrintAss = false;
  bool silent = false;
  bool wsilent = false;
  bool isilent = false;
  bool psilent = false;
};
std::unordered_map<std::string, std::vector<Assertion *>>
mine(const Parameters &p);
} // namespace harm
