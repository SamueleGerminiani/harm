#pragma once

#include "Assertion.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include <vector>

namespace clc {
extern std::string ve_metricName;
extern bool ve_debugScript;
extern std::string ve_assPath;
extern std::string ve_shPath;
extern std::string ve_technique;
extern std::string ve_ftPath;
extern std::string ve_atList;
extern std::string ve_dumpTo;
extern size_t ve_maxPushTime;
extern size_t ve_minPushTime;
extern int ve_maxClusters;
extern bool ve_recover_diff;
extern bool ve_stopExecution;
// number of assertions processed each time
extern size_t ve_chunkSize;
extern size_t max_threads;
extern double ve_nsga2_mi;
extern size_t ve_nsga2_nt;
extern bool ve_push;
extern bool ve_metricDirection;
extern bool ve_only_sim;
extern std::string ve_cls_type;
extern bool ve_genRand;
extern size_t ve_minTime;
extern bool ve_plotDominance;
extern std::pair<double, double> ve_metricInterval;
extern size_t ve_plotRate;
extern bool ve_dump_dmg_vs_metric;
extern bool ve_dont_plot;
extern bool ve_log;
} // namespace clc

namespace dea {

struct Diff {
  Diff() {}

  size_t _atct = 0;
  size_t _atcf = 0;
  //<time,N>
  std::unordered_map<size_t, size_t> _coverage;

  //set of instantes of the form "assId,time"
  std::unordered_set<std::string> _coveredInstances;
};

inline bool isEqual(const Diff &lhs, const Diff &rhs) {
  return lhs._atct == rhs._atct && lhs._atcf == rhs._atcf &&
         lhs._coverage == rhs._coverage &&
         lhs._coveredInstances == rhs._coveredInstances;
}
inline bool isEqualDebug(const Diff &lhs, const Diff &rhs) {
  if (lhs._atct != rhs._atct) {
    std::cout << "lhs._atct: " << lhs._atct
              << " rhs._atct: " << rhs._atct << std::endl;
    return false;
  }
  if (lhs._atcf != rhs._atcf) {
    std::cout << "lhs._atcf: " << lhs._atcf
              << " rhs._atcf: " << rhs._atcf << std::endl;
    return false;
  }
  if (lhs._coverage != rhs._coverage) {
    std::cout << "lhs._coverage: " << lhs._coverage.size()
              << " rhs._coverage: " << rhs._coverage.size()
              << std::endl;
    return false;
  }
  if (lhs._coveredInstances != rhs._coveredInstances) {
    std::cout << "lhs._coveredInstances: "
              << lhs._coveredInstances.size()
              << " rhs._coveredInstances: "
              << rhs._coveredInstances.size() << std::endl;
    return false;
  }
  return true;
}

std::vector<std::string> readAssertionsFromFile(std::string assPath);
std::unordered_map<std::string,
                   std::vector<harm::TemplateImplicationPtr>>
discardAssertionsGroupBy(
    std::vector<harm::TemplateImplicationPtr> &assertions,
    int groupByAnt);
void cluster(std::unordered_map<std::string, Diff> &tokenToDiff,
             bool normalize);

void getDiff(std::unordered_map<std::string, Diff> &idToDiff,
             std::vector<std::string> &ids,
             std::vector<std::pair<harm::TemplateImplicationPtr,
                                   std::vector<size_t>>> &assertions,
             size_t threadID = 0, bool enablePB = true);

harm::TracePtr parseTrace(std::string path);

std::vector<harm::TemplateImplicationPtr>
parseAssertions(std::vector<std::string> assStrs,
                const harm::TracePtr &trace, size_t start, size_t n);

} // namespace dea
