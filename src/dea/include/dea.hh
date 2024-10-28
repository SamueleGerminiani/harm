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
