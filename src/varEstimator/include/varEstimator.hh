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
extern std::string ve_varList;
extern std::string ve_dumpTo;
extern size_t ve_nStatements;
extern size_t ve_cluster;
// number of assertions processed each time
extern size_t ve_chunkSize;
extern size_t max_threads;
} // namespace clc

struct Diff {
  Diff() {}
  Diff(int atct, int atcf, size_t nAssertions)
      : _atct(atct), _atcf(atcf), _nAssertions(nAssertions) {
    // not todo
  }
  int _atct = 0;
  int _atcf = 0;
  size_t _nAssertions = 0;
  double _weight = 0.f;
  std::unordered_map<size_t, size_t> _coverage;

};

std::vector<std::string> readAssertions(std::string assPath);
std::unordered_map<std::string, std::vector<harm::Template *>>
discardAssertionsGroupBy(std::vector<harm::Template *> &assertions,
                         int groupByAnt);
void dumpScore(std::unordered_map<std::string, Diff> &tokenToDiff, bool normalize);


void getDiffVBR(
    std::unordered_map<std::string, Diff> &varToDiff,
    std::unordered_map<std::string, size_t> &varToSize,
    std::unordered_map<std::string, std::vector<harm::Template *>> &varToAss,
    harm::Trace *trace) ;

void getDiffSR(
    std::unordered_map<std::string, Diff> &stmToDiff,
    std::unordered_map<std::string, std::vector<harm::Template *>> &stmToAss) ;

void findFaultCoverageOnTrace(
    std::unordered_map<std::string, std::vector<harm::Template *>> &varToAss,
    harm::Trace *trace, const std::unordered_set<std::string> outVars,
    size_t &nFaults, std::unordered_map<std::string, std::vector<size_t>> &assToFault);
std::vector<harm::Template *> parseAssertions(std::vector<std::string> assStrs,
                                              harm::Trace *trace, size_t start,
                                              size_t n);

