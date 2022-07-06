
#pragma once
#include <chrono>
#include <string>
#include <vector>

namespace l3Constants {
extern size_t MAX_THREADS;
} // namespace l3Constants
namespace l2Constants {
extern size_t MAX_THREADS;
} // namespace l2Constants

namespace l1Constants {
extern size_t MAX_THREADS;
} // namespace l1Constants

// command line config
namespace clc {
extern std::vector<std::string> traceFiles;
extern std::vector<std::string> faultyTraceFiles;
extern std::string ftmFile;
extern std::string configFile;
extern std::string parserType;
extern std::string clk;
extern std::string outputLang;
extern bool genTemp;
extern size_t maxThreads;
extern bool dumpAssToFile;
extern size_t maxAss;
extern bool noData;
extern std::string dumpPath;
extern bool findMinSubset;
extern bool intMode;
extern bool splitLogic;
extern bool dontFillAss;
extern bool dontPrintAss;
extern bool vcdRecursive;
extern std::string selectedScope;
extern bool silent;
extern bool wsilent;
extern bool isilent;
extern bool psilent;
extern std::string clsAlg;
extern bool dumpStat;
} // namespace clc

// harm stat
namespace hs {

extern size_t timeToMine_ms;
extern size_t nAssertions;
extern size_t nOfCovFaults;
extern size_t nFaultCovSubset;
extern size_t traceLength;
extern std::string name;
extern size_t nFaults;

} // namespace hs
