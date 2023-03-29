#pragma once

#include "Assertion.hh"
#include "Template.hh"
#include "Trace.hh"
#include <vector>

namespace clc {
extern std::string ve_assPath;
extern std::string ve_technique;
extern std::string ve_tracePath;
extern std::string ve_ftPath;
extern std::string ve_infoList;
extern std::string ve_dumpTo;
extern size_t ve_nStatements;
extern size_t ve_maxPushTime;
extern size_t ve_minPushTime;
extern int ve_cluster;
extern bool ve_print_failing_ass;
extern bool ve_recover_diff;
extern bool ve_stopExecution;
// number of assertions processed each time
extern size_t ve_chunkSize;
extern size_t max_threads;
extern double ve_nsga2_mi;
extern bool ve_pushp;
extern std::string ve_pushp_design;
extern bool ve_only_sim;
extern std::string ve_cls_type;
extern bool ve_genRand;
extern size_t ve_minTime;
extern bool ve_plotDominance;
} // namespace clc

struct Diff {
  Diff() {}

  size_t _atct = 0;
  size_t _atcf = 0;
  //<time,N>
  std::unordered_map<size_t, size_t> _coverage;

  //set of instantes of the form "assId,time"
  std::unordered_set<std::string> _coveredInstances;
};

std::vector<std::string> readAssertions(std::string assPath);
std::unordered_map<std::string, std::vector<harm::Template *>>
discardAssertionsGroupBy(std::vector<harm::Template *> &assertions,
                         int groupByAnt);
void cluster(std::unordered_map<std::string, Diff> &tokenToDiff,
               bool normalize);


void getDiffSR(std::unordered_map<std::string, Diff> &idToDiff,
               std::vector<std::string> &ids, std::vector<std::pair<harm::Template *,std::vector<size_t>>> &assertions, bool enablePB = true);

void getDiffBR(std::unordered_map<std::string, Diff> &csvIdToDiff,
               std::unordered_map<std::string, size_t> &idToSize,
               std::vector<std::string> &ids,
                std::vector<std::pair<harm::Template *,std::vector<size_t>>> &assertions, bool enablePB = true);

std::vector<harm::Template *> parseAssertions(std::vector<std::string> assStrs,
                                              harm::Trace *trace, size_t start,
                                              size_t n);

