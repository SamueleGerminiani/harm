
#pragma once
#include <stddef.h>
#include <string>
#include <vector>

enum class Language;

namespace l3Constants {
/// The maximum number of threads to use for the third layer of parallelization
extern size_t MAX_THREADS;
} // namespace l3Constants
namespace l2Constants {
/// The maximum number of threads to use for the second layer of parallelization
extern size_t MAX_THREADS;
} // namespace l2Constants

namespace l1Constants {
/// The maximum number of threads to use for the first layer of parallelization
extern size_t MAX_THREADS;
} // namespace l1Constants

// command line config
namespace clc {
///--vcd --csv --vcd-dir --csv-dir
extern std::vector<std::string> traceFiles;
///--fd
extern std::vector<std::string> faultyTraceFiles;
///--include-ass
extern std::string includeAss;
///--conf
extern std::string configFile;
///csv or vcd
extern std::string parserType;
///--clk
extern std::string clk;
///--reset
extern std::string reset;
///FIXME
extern std::string evaluatorType;
///--sva, --psl, --spotltl
extern Language outputLang;
///--sva-assert
extern bool svaAssert;
///--generate-config
extern bool genConfig;
///--dump-trace-as-csv
extern std::string dumpTraceAsCSV;
///--max-threads
extern size_t maxThreads;
///--dump-to
extern bool dumpAssToFile;
///--dump-to
extern std::string dumpPath;
///--dump-to
extern bool dumpAssSplitContexts;
///--keep-vac-ass
extern bool keepVacAss;
///--dump-vac-ass
extern std::string dumpVacAss;
///--max-ass
extern size_t maxAss;
///--min-frank
extern double minFrank;
///--find-min-subset
extern bool findMinSubset;
///--interactive
extern bool intMode;
///--split-logic
extern bool splitLogic;
///--dont-print-ass
extern bool dontPrintAss;
///--vcd-r
extern size_t vcdRecursive;
///--vcd-unroll
extern size_t vcdUnroll;
///--vcd-ss
extern std::string selectedScope;
///--silent
extern bool silent;
///--wilent
extern bool wsilent;
///--isilent
extern bool isilent;
///--psilent
extern bool psilent;
///--dump-stat
extern bool dumpStat;
///--dump-normalize
extern bool dontNormalize;
///--sample-by-con
extern bool sampleByCon;
} // namespace clc

// harm stat
namespace hs {

/// The name of the current "execution", --name
extern std::string name;
extern size_t timeToMine_ms;
/// Number of mined assertions
extern size_t nAssertions;
/// Number of faults covered by the mined assertions
extern size_t nOfCovFaults;
/// Minimum of faults covering the mined assertions
extern size_t nFaultCovSubset;
///Total length of the input trace
extern size_t traceLength;
///Number of input fault
extern size_t nFaults;

} // namespace hs
