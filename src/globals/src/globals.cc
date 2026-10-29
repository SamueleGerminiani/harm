#include "globals.hh"
#include "Language.hh"

#include <limits>
#include <thread>

namespace l3Constants {
size_t MAX_THREADS = std::thread::hardware_concurrency();
} // namespace l3Constants
namespace l2Constants {
size_t MAX_THREADS = std::thread::hardware_concurrency();
} // namespace l2Constants

namespace l1Constants {
size_t MAX_THREADS = std::thread::hardware_concurrency() / 2;
} // namespace l1Constants

namespace clc {

std::vector<std::string> traceFiles;
std::vector<std::string> faultyTraceFiles;
std::string includeAss = "";
std::string configFile = "";
std::string checkDumpEvalDirectory = "";
std::string parserType = "";
std::string clk = "";
std::string reset = "";
std::string evaluatorType = "AutomataBased";

Language outputLang = Language::SpotLTL;
bool svaAssert = false;
bool legacySvaPrinting = false;
bool genConfig = false;
std::string dumpTraceAsCSV = "";
size_t maxThreads = std::thread::hardware_concurrency();
bool findMinSubset = false;
bool dumpAssToFile = false;
bool dumpAssSplitContexts = false;
bool keepVacAss = false;
bool skipInvalidProps = false;
std::string reduce = "syntactic";
std::string keep = "stronger";
std::string dumpImplications = "";
std::string traceEnd = "harm";
std::string dumpAssertionInfo = "";
std::string dumpPropTable = "";
std::string harmVersion = "";
std::string dumpCoiReport = "";
bool atomPremises = false;
size_t atomPremisesMax = 2000;
size_t impliesMaxPairs = 0;
double deadline = -1;
double mineDeadline = -1;
std::string dumpVacAss = "";
size_t maxAss = std::numeric_limits<size_t>().max();
double minFrank = 0.f;
std::string dumpPath = "";
bool intMode = false;
bool forceInt = false;
bool printLogicAsInt = false;
bool splitLogic = false;
size_t vcdRecursive = true;
size_t vcdUnroll = 0;
std::string selectedScope = "";
bool dontPrintAss = false;
bool silent = false;
bool wsilent = false;
bool isilent = false;
bool psilent = false;
bool dumpStat = false;
bool dontNormalize = false;
bool sampleByCon = false;
bool dumpDebugData = false;
std::string debugDataPath = "";
} // namespace clc

// harm stat
namespace hs {
std::string name = "";
size_t timeToMine_ms = 0;
size_t nAssertions = 0;
size_t nOfCovFaults = 0;
size_t nFaults = 0;
size_t nFaultCovSubset = 0;
size_t traceLength = 0;
std::vector<std::string> checkDumpEvalIndex;
std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
std::atomic<size_t> permutationsDone{0};
std::atomic<size_t> permutationsTotal{0};
std::atomic<size_t> templatesNotStarted{0};
std::atomic<bool> mineCut{false};

double elapsed() {
  return std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
}

bool mineDeadlinePassed() {
  if (clc::mineDeadline < 0 || elapsed() < clc::mineDeadline) {
    return false;
  }
  mineCut = true;
  return true;
}

std::chrono::steady_clock::time_point reduceDeadline() {
  if (clc::deadline < 0) {
    return std::chrono::steady_clock::time_point::max();
  }
  return start + std::chrono::duration_cast<std::chrono::steady_clock::duration>(
                     std::chrono::duration<double>(clc::deadline));
}

} // namespace hs
