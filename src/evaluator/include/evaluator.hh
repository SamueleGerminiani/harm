#pragma once

#include "Assertion.hh"
#include "Template.hh"
#include "Trace.hh"
#include "Assertion.hh"
#include <vector>

namespace clc {
extern std::string ve_assPath;
extern std::string ve_technique;
extern std::string ve_tracePath;
extern std::string ve_ftPath;
extern std::string ve_infoList;
extern std::string ve_dumpTo;
extern size_t ve_nStatements;
extern int ve_cluster;
extern bool ve_print_failing_ass;
extern bool ve_recover_diff;
// number of assertions processed each time
extern size_t ve_chunkSize;
extern size_t max_threads;
extern bool ve_clusterBySim;
extern bool ve_recover_cls;
extern std::string ve_cls_type;
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
void dumpScore(std::unordered_map<std::string, Diff> &tokenToDiff, bool normalize);


void getDiffVBR(
    std::unordered_map<std::string, Diff> &csvVarToDiff,
    std::unordered_map<std::string, size_t> &varToSize,
    std::vector<std::string> &vars,
    std::vector<harm::Template *> &assertions);

void getDiffSR(
    std::unordered_map<std::string, Diff> &idToDiff,
    std::vector<std::string> &ids,
    std::vector<harm::Template *> &assertions
    );

void getDiffBR(
    std::unordered_map<std::string, Diff> &csvIdToDiff,
    std::unordered_map<std::string, size_t> &idToSize,
    std::vector<std::string> &ids,
    std::vector<harm::Template *> &assertions);

void findFaultCoverageOnTrace(
    std::unordered_map<std::string, std::vector<harm::Template *>> &varToAss,
    harm::Trace *trace, const std::unordered_set<std::string> outVars,
    size_t &nFaults, std::unordered_map<std::string, std::vector<size_t>> &assToFault);
std::vector<harm::Template *> parseAssertions(std::vector<std::string> assStrs,
                                              harm::Trace *trace, size_t start,
                                              size_t n);

