#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream> // IWYU pragma: keep
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Assertion.hh"
#include "CSVtraceReader.hh"
#include "Context.hh"
#include "DTLimits.hh"
#include "Float.hh"
#include "Hierarchical.hh"

#include "Location.hh"
#include "Metric.hh"
#include "ProgressBar.hpp"
#include "Qualifier.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "VCDtraceReader.hh"
#include "expUtils/expUtils.hh"
#include "fort.h"
#include "fort.hpp"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include "set_cover/set_cover_wrapper.hh"
#include "temporalParsingUtils.hh"

using namespace expression;
namespace harm {

static double scoreFunction(double x, Metric::FunctionParameter &fp) {
  // 1/(1 + e^(z - kx))^2
  return 1.f / pow(1.f + exp(fp._z - fp._k * x), 2);
}

Qualifier::Qualifier() : PropertyQualifier() {}

std::vector<AssertionPtr> Qualifier::extractUniqueAssertionsFast(
    const std::vector<AssertionPtr> &inAssertions) {

  std::vector<AssertionPtr> outAssertions;
  std::unordered_set<AssertionPtr> assP;
  std::unordered_set<std::string> keys;
  //change data structer to allow constant access with id
  for (const AssertionPtr &ass : inAssertions) {
    assP.insert(ass);
  }

  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Filtering redundant assertions... 0 discarded",
                 inAssertions.size(), 70);
  size_t discarded = 0;

  //discard assertions deemed 'equivalent'
  for (auto &ass : assP) {

    pb.changeMessage(0, "Filtering redundant assertions... " +
                            std::to_string(discarded) + " discarded");
    pb.increment(0);
    pb.display();

    //compress contingency table
    std::string cont = std::to_string(ass->_ct[0][0]) +
                       std::to_string(ass->_ct[0][1]) +
                       std::to_string(ass->_ct[0][2]) +
                       std::to_string(ass->_ct[1][0]) +
                       std::to_string(ass->_ct[1][1]) +
                       std::to_string(ass->_ct[1][2]) +
                       std::to_string(ass->_ct[2][0]) +
                       std::to_string(ass->_ct[2][1]) +
                       std::to_string(ass->_ct[2][2]);

    std::string assS = ass->toString();
    assS.erase(remove_if(assS.begin(), assS.end(),
                         [](const char &c) {
                           return c == '\t' || c == '\n' ||
                                  c == ' ' || c == '(' || c == ')' ||
                                  c == '{' || c == '}' || c == '[' ||
                                  c == ']';
                         }),
               assS.end());
    //combine the string rep of an assertion with its contincency table to generate a key
    std::string key = cont + assS;
    if (!keys.count(key)) {
      //add only if the key is unique
      outAssertions.push_back(ass);
      keys.insert(key);
    } else {
      discarded++;
    }
  }

  pb.done(0);

  return outAssertions;
}

std::vector<AssertionPtr> Qualifier::extractUniqueAssertions(
    const std::vector<AssertionPtr> &inAssertions) {

  // remove equivalent solutions, keep shortest
  std::vector<AssertionPtr> outAssertions;
  std::unordered_set<size_t> taken;
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Filtering redundant assertions... 0 discarded",
                 inAssertions.size(), 70);
  size_t discarded = 0;

  for (size_t i = 0; i < inAssertions.size(); i++) {

    pb.changeMessage(0, "Filtering redundant assertions... " +
                            std::to_string(discarded) + " discarded");
    pb.increment(0);
    pb.display();

    if (taken.count(i))
      continue;

    taken.insert(i);
    AssertionPtr a1 = inAssertions[i];
    AssertionPtr shortest = a1;
    for (size_t j = i + 1; j < inAssertions.size(); j++) {
      if (taken.count(j))
        continue;

      AssertionPtr a2 = inAssertions[j];
      if (*a1 == *a2) {
        //     debug
        //std::cout << a1->_toString.second << " == " << a2->_toString.second <<  "\n";
        shortest = a1->toString().size() >= a2->toString().size()
                       ? shortest
                       : a2;
        taken.insert(j);
        discarded++;
      }
    }

    outAssertions.push_back(shortest);
  }

  pb.done(0);
  return outAssertions;
}

std::vector<AssertionPtr> Qualifier::qualify(Context &context,
                                             const TracePtr &trace) {

  if (context._assertions.empty()) {
    messageWarning("Could not mine any assertions for context '" +
                   context._name + "'");
    return std::vector<AssertionPtr>();
  }

  std::vector<AssertionPtr> assertions = context._assertions;

  messageInfo("Qualifying " + std::to_string(assertions.size()) +
              " assertions");

  filterRedundantAssertions(assertions);
  filterAssertionsWithMetrics(assertions, context._filter);

  //auto assCls = clusterAssertions(assertions, trace);

  std::vector<AssertionPtr> rankedAssertions =
      rankAssertions(assertions, context._sort);
  filterAssertionsWithFrank(rankedAssertions);

  //std::vector<AssertionPtr> rankedAssertions;
  //for (auto &[cldID, assertions] : assCls) {
  //  //ranking
  //  std::vector<AssertionPtr> tmp_rankedAssertions =
  //      rankAssertions(assertions, context._sort);
  //  filterAssertionsWithFrank(tmp_rankedAssertions);
  //  rankedAssertions.insert(rankedAssertions.end(),
  //                          tmp_rankedAssertions.begin(),
  //                          tmp_rankedAssertions.end());
  //}

  hs::nAssertions += rankedAssertions.size();

  // print
  if (!clc::dontPrintAss && !rankedAssertions.empty()) {
    printAssertions(context, rankedAssertions, trace);
  }

  // fault-based qualification
  if ((!clc::faultyTraceFiles.empty()) && !rankedAssertions.empty()) {
    faultBasedQualification(rankedAssertions, trace);
  }

  // dump to file
  if (clc::dumpAssToFile && !rankedAssertions.empty()) {
    dumpAssToFile(context, trace, rankedAssertions);
  }

  return rankedAssertions;
}
std::vector<std::pair<size_t, std::vector<AssertionPtr>>>
Qualifier::clusterAssertions(
    const std::vector<AssertionPtr> &assertions,
    const TracePtr &trace) {

  std::cout << "Clustering " << assertions.size() << " assertions\n";

  std::unordered_map<size_t, std::set<std::string>> assIdToVars;
  std::unordered_map<size_t, AssertionPtr> assIdToAss;

  for (size_t i = 0; i < assertions.size(); i++) {
    AssertionPtr ass = assertions[i];
    assIdToAss[i] = ass;
    TemplateImplicationPtr t =
        hparser::parseTemplateImplication(ass->toString(), trace);
    auto vars = t->getVars();
    for (auto &v : vars) {
      assIdToVars[i].insert(v.first);
    }
  }

  std::unordered_map<size_t, std::vector<size_t>> clusters;
  std::unordered_set<size_t> used;

  size_t clusterID = 0;
  for (auto &[assId1, vars1] : assIdToVars) {

    if (used.count(assId1))
      continue;

    std::vector<size_t> cls;
    cls.push_back(assId1);
    used.insert(assId1);

    for (auto &[assId2, vars2] : assIdToVars) {
      if (!used.count(assId2) && vars1 == vars2) {
        cls.push_back(assId2);
        used.insert(assId2);
      }
    }

    clusters[clusterID] = cls;
    clusterID++;
  }

  std::cout << "N clusters:" << clusters.size() << "\n";
  std::cout << "AVG size:"
            << (double)assertions.size() / clusters.size() << "\n";

  // std::unordered_map<std::string, std::unordered_set<std::string>>
  //     assIdToVars;
  //for (size_t i = 0; i < assertions.size(); i++) {
  //  AssertionPtr ass = assertions[i];

  //  TemplateImplicationPtr t = hparser::parseTemplateImplication(ass->toString(), trace);

  //  std::vector<PropositionPtr> loadedProps =
  //      t->getLoadedPropositions();

  //  for (PropositionPtr p : loadedProps) {
  //    for (auto &[name, type] : getVars(*p)) {
  //      assIdToVars[std::to_string(i)].insert(name);
  //    }
  //  }

  //
  //}

  //std::vector<std::vector<EvaluatorClusterElement>> clusters =
  //    hcElbowOverlapping(assIdToVars);

  //for (size_t i = 0; i < clusters.size(); i++) {
  //  auto &c = clusters[i];
  //  std::cout << "[" << i << "]"
  //            << "\n";
  //  for (auto &element : c) {
  //    std::cout << "\t\t" << element.first << "\n";
  //    std::cout << "\t\t\t\t";
  //    for (auto &var : assIdToVars.at(element.first)) {
  //      std::cout << var << " ";
  //    }
  //    std::cout << "\n";
  //  }
  //  std::cout << "\n";
  //}
  //std::cout << "N clusters:" << clusters.size() << "\n";
  std::vector<std::pair<size_t, std::vector<AssertionPtr>>> ret;
  for (auto &[clsId, assIDs] : clusters) {
    std::vector<AssertionPtr> assertions;
    for (auto id : assIDs) {
      assertions.push_back(assIdToAss.at(id));
    }
    ret.emplace_back(std::make_pair(clsId, assertions));
  }

  return ret;
}

TracePtr Qualifier::parseFaultyTrace(const std::string &ftStr) {
  TraceReader *tr;
  if (clc::parserType == "vcd") {
    messageErrorIf(!std::filesystem::exists(ftStr),
                   "Can not find '" + ftStr + "'");
    tr = new VCDtraceReader(ftStr, clc::clk);
    TracePtr t = tr->readTrace();
    delete tr;
    return t;
  } else if (clc::parserType == "csv") {
    messageErrorIf(!std::filesystem::exists(ftStr),
                   "Can not find '" + ftStr + "'");
    tr = new CSVtraceReader(ftStr);
    TracePtr t = tr->readTrace();
    delete tr;
    return t;
  }
  messageError("Uknown parser type");
  return nullptr;
}

std::vector<size_t> Qualifier::getCoverageSet() {
  std::vector<size_t> ret;
  if (_aToF.empty()) {
    return ret;
  }

  std::vector<std::vector<int>> set_to_elements;
  std::unordered_map<int, int> setIdToFaultId;
  size_t setId = 0;
  for (auto &[aID, fIDS] : _aToF) {
    std::vector<int> cfSubset;
    for (auto fID : fIDS) {
      cfSubset.push_back(fID);
    }
    set_to_elements.push_back(cfSubset);
    setIdToFaultId[setId] = aID;
    setId++;
  }
  auto selectedSets = findMinSetCover(set_to_elements);
  for (auto setId : selectedSets) {
    ret.push_back(setIdToFaultId[setId]);
  }

  return ret;
}
void Qualifier::sortAssertionsWithMetrics(
    std::vector<MetricPtr> &metrics,
    std::vector<AssertionPtr> &assertions, size_t currParamIndex) {
  if (metrics.empty()) {
    //nothing to do
    return;
  }

  if (!Metric::functionParams.count(currParamIndex)) {
    currParamIndex = _maxParamIndex;
  }

  // gather max value for all metrics (needed to normalize)
  std::unordered_map<std::string, double> mToMaxValue =
      getMaxValuesForSortMetrics(metrics, assertions);

  for (auto &a : assertions) {
    double score = 1;
    for (auto &m : metrics) {
      score *= scoreFunction(Metric::evaluateMetric(*a, *m) /
                                 mToMaxValue.at(m->_name),
                             Metric::functionParams[currParamIndex]);
    }
    a->_finalScore = score;
  }

  std::sort(assertions.begin(), assertions.end(),
            [](const AssertionPtr &left, const AssertionPtr &right) {
              return left->_finalScore > right->_finalScore;
            });
}

void Qualifier::filterAssertionsWithMetrics(
    std::vector<AssertionPtr> &assertions,
    std::vector<std::pair<MetricPtr, double>> &metrics) {

  //need this to normalize the values
  std::unordered_map<std::string, double> mToMaxValue =
      getMaxValuesForFilterMetrics(metrics, assertions);

  // apply filtering metrics, mark as 'deleted' (nullptr) all assertions that evaluates under the threshold
  size_t filtered = 0;
  for (auto &a : assertions) {
    for (auto &m : metrics) {
      if (Metric::evaluateMetric(*a, *m.first) /
              mToMaxValue.at(m.first->_name) <
          m.second) {
        a = nullptr;
        filtered++;
        break;
      }
    }
  }

  //actually remove the assertion from the container
  assertions.erase(
      remove_if(assertions.begin(), assertions.end(),
                [](const AssertionPtr a) { return a == nullptr; }),
      assertions.end());

  messageInfo("Metrics filtered " + std::to_string(filtered) +
              " assertions");
}

void Qualifier::filterAssertionsWithFrank(
    std::vector<AssertionPtr> &assertions) {

  if (clc::minFrank == 0.f) {
    return;
  }

  // apply filtering metrics, mark as 'deleted' (nullptr) all assertions that evaluates under the threshold
  size_t filtered = 0;
  for (auto &a : assertions) {
    if (a->_finalScore < clc::minFrank) {
      a = nullptr;
      filtered++;
    }
  }

  //actually remove the assertion from the container
  assertions.erase(
      remove_if(assertions.begin(), assertions.end(),
                [](const AssertionPtr &a) { return a == nullptr; }),
      assertions.end());

  messageInfo("min-frank filtered " + std::to_string(filtered) +
              " assertions");
}

void Qualifier::printAssertions(Context &context,
                                std::vector<AssertionPtr> &assertions,
                                const TracePtr &trace) {

  size_t currParamIndex = 19;
  while (1) {
    sortAssertionsWithMetrics(context._sort, assertions,
                              currParamIndex);
    fort::utf8_table table;
    table.set_border_style(FT_NICE_STYLE);

    //need this to normalize the values
    std::unordered_map<std::string, double> mToMaxValue =
        getMaxValuesForSortMetrics(context._sort, assertions);
    size_t headerPrintRate = 100;
    for (size_t i = 0; i < assertions.size(); i++) {
      if (i % headerPrintRate == 0) {
        //print the header, this is repeated every '#headerPrintRate' assertions to improve readability
        table << fort::header << "N"
              << std::string("Assertion ") +
                     "(Context : " + context._name + ")"
              << "final";
        for (auto m : context._sort) {
          table << m->_name;
        }
        table << fort::endr;
      }

      //get the assertion being printed
      AssertionPtr ass = assertions[i];
      std::vector<std::string> line;
      std::string ass_colored = "";
      std::string ass_black = "";
      //print the assertions according to the selected output language
      ass_colored = ass->toColoredString();
      ass_black = ass->toString();
      line.push_back(std::to_string(i));
      line.push_back(ass_colored);
      line.push_back(to_string_with_precision(ass->_finalScore, 2));
      for (auto &m : context._sort) {
        line.push_back(to_string_with_precision(

            clc::dontNormalize ? Metric::evaluateMetric(*ass, *m)
                               : Metric::evaluateMetric(*ass, *m) /
                                     mToMaxValue.at(m->_name),
            2)

        );
      }
      //print the assertion with its ranking
      table.range_write_ln(std::begin(line), std::end(line));
    }

    std::cout << table.to_string() << std::endl;

    if (!clc::intMode) {
      break;
    }

    std::string outPar = std::to_string(currParamIndex);
    std::cout << "Current value: " << outPar << "\n";
    std::cout << "Insert new ranking range LR (1 to 90, -1 to exit)"
              << "\n";
    std::string input = "";
    do {
      std::cin >> input;
    } while (!isInteger(input));
    currParamIndex = safeStoull(input);
    if ((int)currParamIndex == -1) {
      //exit interactive mode
      break;
    }
  }
}

void Qualifier::fbqUsingFaultyTraces(
    const std::vector<AssertionPtr> &selected,
    const TracePtr &originalTrace) {

  progresscpp::ParallelProgressBar progressBarPS;
  progressBarPS.addInstance(0,
                            "Preparing fault-based qualification...",
                            selected.size(), 70);
  progressBarPS.display();
  std::vector<TemplateImplicationPtr> noCacheTemplates;
  for (const AssertionPtr &a : selected) {
    noCacheTemplates.push_back(hparser::parseTemplateImplication(
        a->toString(), originalTrace, DTLimits(), 0));

    progressBarPS.increment(0);
    progressBarPS.display();
  }

  progressBarPS.done(0);

  //silence warnings and infos (to silence the traceReader)
  clc::isilent = 1;
  clc::wsilent = 1;

  progresscpp::ParallelProgressBar progressBar;
  progressBar.addInstance(
      0,
      "Fault coverage 0/" +
          std::to_string(clc::faultyTraceFiles.size()),
      selected.size() * clc::faultyTraceFiles.size(), 70);
  progressBar.display();

  for (size_t j = 0; j < clc::faultyTraceFiles.size(); j++) {

    progressBar.changeMessage(
        0, "Fault coverage " +
               (std::to_string(_fToA.size()) + "/" +
                std::to_string(clc::faultyTraceFiles.size())) +
               " (" +
               to_string_with_precision(
                   (_fToA.size() / (double)j) * 100.f, 2) +
               "%)" + " (Elaborating " + clc::faultyTraceFiles[j] +
               " [" + std::to_string(j + 1) + "])");

    auto ft = parseFaultyTrace(clc::faultyTraceFiles[j]);
    for (size_t i = 0; i < noCacheTemplates.size(); i++) {
      auto &a = noCacheTemplates[i];
      //new assertion with faulty trace
      TemplateImplicationPtr fAss =
          generatePtr<TemplateImplication>(*a);
      fAss->changeTrace(ft);
      //exploit l1 parallelism
      if (!fAss->assHoldsOnTrace(Location::AntCon)) {
        // new fault covered
        _aToF[i].push_back(j);
        _fToA[j].push_back(i);
        if (!clc::findMinSubset) {
          //stop search for this fault if do not want the optimal covering set

          progressBar.increment(0, noCacheTemplates.size() - i);
          progressBar.display();

          break;
        }
      }

      progressBar.increment(0);
      progressBar.display();
    }
  }

  // print last

  progressBar.changeMessage(
      0, "Fault coverage " +
             (std::to_string(_fToA.size()) + "/" +
              std::to_string(clc::faultyTraceFiles.size())) +
             " (Elaborating " + clc::faultyTraceFiles.back() + " [" +
             std::to_string(clc::faultyTraceFiles.size()) + "])");

  progressBar.done(0);

  clc::isilent = 0;
  clc::wsilent = 0;

  //  debug
  //  which ass covers which fault?
  //  for (auto aff : _aToF) {
  //    std::cout << aff.first << ") " <<
  //    selected[aff.first]->_toString.second
  //              << "\n";
  //    for (auto f : aff.second) {
  //      std::cout << "\t"
  //                << "   " << f << "\n";
  //    }
  //  }
  //
}
std::vector<AssertionPtr>
sampleAssertionsByConDiversity(std::vector<AssertionPtr> selected,
                               size_t n) {

  std::vector<AssertionPtr> sampled;
  //we want to keep the relative order of assertions
  std::map<size_t, std::vector<AssertionPtr>> conToAss;
  std::unordered_map<std::string, size_t> hashToId;
  size_t id = 0;
  for (auto a : selected) {
    std::string impl =
        patternExists(a->toString(), "->") ? "->" : "=>";
    std::string hash = selectStringAfter(a->toString(), impl);
    if (!hashToId.count(hash)) {
      hashToId[hash] = id++;
    }
    conToAss[hashToId.at(hash)].push_back(a);
  }

  size_t level = 0;
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Sampling by con...", n, 70);
  while (1) {
    for (auto &[con, ass] : conToAss) {
      if (ass.size() > level) {
        sampled.push_back(ass[level]);
        n--;
        pb.increment(0);
        pb.display();
        if (n == 0) {
          goto end;
        }
      }
    }
    level++;
  }
end:;
  pb.done();
  return sampled;
}

void Qualifier::faultBasedQualification(
    std::vector<AssertionPtr> selected, const TracePtr &trace) {

  size_t nFaultsftm = 0;
  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(selected), std::end(selected), rng);

  _aToF.clear();
  _fToA.clear();

  fbqUsingFaultyTraces(selected, trace);
  hs::nFaults = clc::faultyTraceFiles.size();
  std::stringstream ss;

  //gather info on the coverage

  ss << "Coverage: "
     << ((double)_fToA.size() /
         (double)clc::faultyTraceFiles.size()) *
            100
     << "%\n";
  hs::nOfCovFaults = _fToA.size();

  if (!_fToA.empty()) {
    _coverageSet.clear();
    _coverageSet = getCoverageSet();
    hs::nFaultCovSubset = _coverageSet.size();
    ss << "Covering Subset:"
       << "\n\033[0m";
    for (auto a : _coverageSet) {
      ss << a << ")"
         << "\t" << selected[a]->toColoredString() << "\n";
    }
    ss << "\n\e[1m";
  }

  if (_fToA.size() < clc::faultyTraceFiles.size() ||
      _fToA.size() < nFaultsftm) {
    ss << "Uncovered:"
       << "\n"
       << "\033[0m";

    for (size_t j = 0; j < clc::faultyTraceFiles.size(); j++) {
      if (!_fToA.count(j)) {
        ss << "\t" << clc::faultyTraceFiles[j] << "\n";
      }
    }
    ss << "\n\e[1m";
  }

  ss << "\nNAssertions:" << selected.size() << "\n";
  ss << "NFaults:" << hs::nFaults << "\n";
  //print the coverage
  messageInfo(ss.str());
}
void Qualifier::dumpAssToFile(Context &context, const TracePtr &trace,
                              std::vector<AssertionPtr> &assertions) {
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Dumping assertions...", assertions.size(), 70);

  std::ofstream assFile;

  if (clc::dumpAssSplitContexts) {
    assFile = std::ofstream(clc::dumpPath + "/" + context._name +
                            "_ass.txt");
  } else {
    assFile = std::ofstream(clc::dumpPath, std::ofstream::app);
  }

  for (auto &a : assertions) {
    assFile << a->toString() << "\n";
    pb.increment(0);
    pb.display();
  }

  //dump fault coverage
  if (clc::dumpAssSplitContexts && !clc::faultyTraceFiles.empty()) {

    std::ofstream fc_assFile(clc::dumpPath + "/" + context._name +
                             "_faultCov.txt");

    for (auto a : _coverageSet) {
      fc_assFile << assertions[a]->toString() << "\n";
    }
    fc_assFile.close();
  }

  assFile.close();
  pb.done(0);
}
void Qualifier::filterRedundantAssertions(
    std::vector<AssertionPtr> &assertions) {

  //remove redundant assertios
  //FIXME: do we still need the slow version?
  //  if (assertions.size() > 10000) {
  //    //less precise but faster
  assertions = extractUniqueAssertionsFast(assertions);
  //  } else {
  //    assertions = extractUniqueAssertions(assertions);
  //  }
}

std::vector<AssertionPtr> Qualifier::rankAssertions(
    const std::vector<AssertionPtr> &inAssertions,
    std::vector<MetricPtr> &sort) {

  auto assertions = inAssertions;
  //sort according to the final score
  sortAssertionsWithMetrics(sort, assertions);

  if (assertions.size() > clc::maxAss) {
    messageInfo("Keeping only the top " +
                std::to_string(clc::maxAss) + " assertions");
    if (clc::sampleByCon) {
      assertions =
          sampleAssertionsByConDiversity(assertions, clc::maxAss);
    } else {
      assertions.erase(assertions.begin() + clc::maxAss,
                       assertions.end());
    }
  }

  return assertions;
}

std::unordered_map<std::string, double>
Qualifier::getMaxValuesForSortMetrics(
    std::vector<MetricPtr> &metrics,
    std::vector<AssertionPtr> &assertions) {

  std::unordered_map<std::string, double> mToMaxValue;
  for (auto &m : metrics) {
    double max = 0;
    for (auto &a : assertions) {
      double eval = Metric::evaluateMetric(*a, *m);
      messageErrorIf(std::isnan(eval), "NaN result in metric " +
                                           m->_name + " for " +
                                           a->toString());
      max = eval > max ? eval : max;
    }
    mToMaxValue[m->_name] = max;
  }
  return mToMaxValue;
}
std::unordered_map<std::string, double>
Qualifier::getMaxValuesForFilterMetrics(
    std::vector<std::pair<MetricPtr, double>> &metrics,
    std::vector<AssertionPtr> &assertions) {

  std::unordered_map<std::string, double> mToMaxValue;
  for (auto &[m, th] : metrics) {
    double max = 0;
    for (auto &a : assertions) {
      double eval = Metric::evaluateMetric(*a, *m);
      max = eval > max ? eval : max;
    }
    mToMaxValue[m->_name] = max;
  }
  return mToMaxValue;
}

} // namespace harm
