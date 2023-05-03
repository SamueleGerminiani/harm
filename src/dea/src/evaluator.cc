#include "evaluator.hh"
#include "CSVtraceReader.hh"
#include "DTUtils.hh"
#include "DataType.hh"
#include "EdgeProposition.hh"
#include "Hierarchical.hh"
#include "Kmeans.hh"
#include "Location.hh"
#include "NSGA2.hh"
#include "ProgressBar.hpp"
#include "Template.hh"
#include "VCDtraceReader.hh"
#include "csv.hpp"
#include "exp.hh"
#include "expUtils/VarType.hh"
#include "expUtils/expUtils.hh"
#include "globals.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "templateParsingUtils.hh"
#include "utils.hh"
#include "varDeclarationParser.hh"
#include <cmath>
#include <filesystem>

#include <algorithm>
#include <fstream>
#include <mutex>
#include <spot/tl/parse.hh>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#define enPB_ve 1

namespace clc {
std::string ve_assPath = "";
std::string ve_metricName = "Metric";
bool ve_debugScript = 0;
std::string ve_shPath = "";
std::string ve_technique = "";
std::string ve_ftPath = "";
std::string ve_atList = "";
std::string ve_dumpTo = ".";
int ve_maxClusters = 10;
bool ve_stopExecution = 0;
// number of assertions processed each time
size_t ve_chunkSize = 100000;
bool ve_recover_diff = 0;
double ve_nsga2_mi = 1.f;
bool ve_push = 0;
bool ve_only_sim = 0;
bool ve_genRand = 0;
bool ve_plotDominance = 0;
bool ve_metricDirection = 0;
std::string ve_cls_type = "nsga2";
size_t ve_maxPushTime = -1;
size_t ve_minPushTime = 0;
size_t ve_minTime = 0;
} // namespace clc

using namespace harm;
using namespace expression;

Trace *parseTrace(std::string path) {

  TraceReader *traceReader = nullptr;
  if (clc::parserType == "vcd") {
    traceReader = new VCDtraceReader(path, clc::clk);
  } else if (clc::parserType == "csv") {
    traceReader = new CSVtraceReader(path);
  } else {
    messageError("Unknown parser type");
  }

  Trace *trace = traceReader->readTrace();
  delete traceReader;
  return trace;
}

// read assertions from file
std::vector<std::string> readAssertionsFromFile(std::string assPath) {
  std::fstream ass(assPath);
  std::string line = "";
  std::vector<std::string> assStrs;
  while (std::getline(ass, line)) {
    assStrs.push_back(line);
  }
  std::cout << "N assertions: " << assStrs.size() << "\n";
  return assStrs;
}

// parse only the assertions in the range [start,start+n]
std::vector<Template *> parseAssertions(std::vector<std::string> assStrs,
                                        Trace *trace, size_t start, size_t n) {
  std::vector<Template *> ret;
#if enPB_ve
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Parsing assertions...",
                 (start + n <= assStrs.size() ? n : assStrs.size() - start),
                 70);
#endif
  for (size_t i = start; i < start + n && i < assStrs.size(); i++) {
    Template *ass =
        hparser::parseTemplate(assStrs[i], trace, "Spot", DTLimits(), 0);
    messageErrorIf(!ass->assHoldsOnTraceNoCache(),
                   "Assertion fails on golden trace");
    // parallelize eval function with 2 threads
    ass->setL1Threads(2);
    // save
    ret.push_back(ass);

#if enPB_ve
    pb.increment(0);
    pb.display();
#endif
  }
#if enPB_ve
  pb.done(0);
#endif
  //debug
  //size_t atct = 0;
  //for (auto ass : ret) {
  //  size_t ct[3][3] = {{0}};
  //  ass->fillContingency(ct, 0);
  //  atct += ct[0][0];
  //}
  //std::cout << "------------->"<<atct<<"/"<<(ret.size()*1002.f) << "\n";
  return ret;
}

void getDiff(
    std::unordered_map<std::string, Diff> &idToDiff,
    std::vector<std::string> &ids,
    std::vector<std::pair<harm::Template *, std::vector<size_t>>> &assertions,
    size_t threadID, bool enablePB) {

  progresscpp::ParallelProgressBar pb;
  clc::isilent = 1;
  if (enablePB) {
    pb.addInstance(1, std::string("Evaluating assertions... "), ids.size(), 70);
  }

  for (auto &s : ids) {
    // parse the ft
    std::string fn =
        clc::ve_ftPath + "/" + s + (clc::parserType == "vcd" ? ".vcd" : ".csv");

    if (enablePB) {
      pb.changeMessage(1, fn);
    }

    if (!std::filesystem::exists(fn)) {
      //simulate
      systemCustom("bash " + clc::ve_shPath + " " + s + " " + clc::ve_ftPath +
                   " 0 " + std::to_string(threadID) +
                   (clc::ve_debugScript ? "" : " > /dev/null"));
      //      systemCustom("bash " + clc::ve_shPath + " " + s + " 1000 " + clc::ve_ftPath + " 0 " + std::to_string(threadID));

      if (enablePB) {
        pb.increment(1);
      }
      if (!std::filesystem::exists(fn)) {
        messageWarning("Can not find '" + fn + "' after simulating!\n\n");
        continue;
      }
    }

    Trace *ft = parseTrace(fn);

    std::unordered_map<size_t, size_t> &cov = idToDiff[s]._coverage;
    size_t &atcf = idToDiff[s]._atcf;
    std::unordered_set<std::string> &covInstances =
        idToDiff[s]._coveredInstances;

    for (size_t assId = 0; assId < assertions.size(); assId++) {

      auto &a = assertions[assId].first;
      auto &antInstances = assertions[assId].second;
      Template *fAss = new Template(*a);
      fAss->changeTrace(ft);

      for (auto i : antInstances) {
        if (fAss->evaluateNoCache(i) == Trinary::F) {
          atcf++;
          cov[i]++;
          covInstances.insert(std::to_string(assId) + "," + std::to_string(i));
        }
      }

      delete fAss;
    }

    delete ft;
    if (enablePB) {
      pb.increment(1);
    }
  }
  if (enablePB) {
    pb.done(1);
  }
  clc::isilent = 0;
}

std::vector<std::pair<std::string, double>>
converToScores(std::unordered_map<std::string, Diff> &tokenToDiff,
               bool normalize) {

  std::vector<std::pair<std::string, double>> scores;

  if (normalize) {
    for (auto &[token, diff] : tokenToDiff) {
      double score = 0.f;
      for (auto &[id, v] : diff._coverage) {
        //use a log function to normalize
        score += 1.f + log(v);
      }
      scores.emplace_back(token, score);
    }
  } else {
    for (auto &[var, diff] : tokenToDiff) {
      scores.emplace_back(var, (double)(diff._atcf));
    }
  }

  //sort the scores
  std::sort(scores.begin(), scores.end(),
            [](const std::pair<std::string, double> &e1,
               const std::pair<std::string, double> &e2) {
              if (e1.second == e2.second) {
                return e1.first < e2.first;
              } else {
                return e1.second < e2.second;
              }
            });
  return scores;
}

void cluster_with_nsga2(std::unordered_map<std::string, Diff> &tokenToDiff) {

  //prepare data for nsga2
  std::vector<std::unordered_set<std::string>> initialPop;
  //return is a vector of clusters <size,error/damage,tokens>
  std::vector<std::tuple<size_t, double, std::unordered_set<std::string>>> ret;

  //group up all the genes <approximation tokens AT>
  std::unordered_map<std::string, std::unordered_set<std::string>> allGenes;
  for (auto &[id, diff] : tokenToDiff) {
    allGenes[id] = diff._coveredInstances;
  }

  //use single elements as starting pop
  for (auto &[gene, instances] : allGenes) {
    initialPop.push_back(std::unordered_set<std::string>({gene}));
  }

  NSGA2 nsga2;
  ret = nsga2.run(allGenes, 100000, clc::ve_nsga2_mi, initialPop);

  std::ofstream out(clc::ve_dumpTo + "/" + clc::ve_technique +
                    std::string("_nsga2") + ".csv");
  //dump the scores

  out << "tokenID,clusterID,clusterSize," +
             (clc::ve_push ? clc::ve_metricName : "Damage") + "\n";

  std::sort(
      ret.begin(), ret.end(),
      [](std::tuple<size_t, double, std::unordered_set<std::string>> &e1,
         std::tuple<size_t, double, std::unordered_set<std::string>> &e2) {
        return std::get<0>(e1) < std::get<0>(e2);
      });
  size_t cIndex = 0;
  for (auto &[f1, f2, tokens] : ret) {
    for (auto &token : tokens) {
      out << token << "," << cIndex << "," << f1 << "," << f2 << "\n";
    }
    cIndex++;
  }
  out.close();
}

void cluster_with_kmeans(std::unordered_map<std::string, Diff> &tokenToDiff,
                         bool normalize) {

  auto scores = converToScores(tokenToDiff, normalize);

  std::ofstream out(clc::ve_dumpTo + "/" + clc::ve_technique +
                    (normalize ? "_nor" : "") + "_kmeans.csv");

  //prep for clustering
  std::vector<double> elements;
  for (auto &v_s : scores) {
    elements.push_back(v_s.second);
  }

  std::map<size_t, std::vector<std::pair<std::string, double>>> clusters_score;

  auto clusters_range =
      clc::ve_maxClusters == -1
          ? kmeansElbow(elements, 10, 0.1, 1)
          : (clc::ve_maxClusters > 1
                 ? kmeansElbow(elements, clc::ve_maxClusters, 0.01, 1)
                 : kmeansElbow(elements, 1, 0.01, 1));

  //fill the clusters with scores
  for (auto &v_s : scores) {
    auto it =
        std::find_if(clusters_range.begin(), clusters_range.end(),
                     [&v_s](const std::pair<double, double> &e) {
                       return v_s.second <= e.second && v_s.second >= e.first;
                     });
    messageErrorIf(it == clusters_range.end(), "Could not find range");
    clusters_score[std::distance(clusters_range.begin(), it)].emplace_back(
        v_s.first, v_s.second);
  }

  out << "tokenID,clusterID,score\n";

  for (auto &[id, scores] : clusters_score) {
    for (auto &[token, score] : scores) {
      if (!normalize) {
        out << token << "," << id << "," << (int)score << "\n";
      } else {
        out << token << "," << std::fixed << std::setprecision(4) << id << ","
            << (double)score << "\n";
      }
    }
  }
  out.close();

  //pareto front
  std::vector<std::unordered_set<std::string>> pop;

  for (auto &[id, cluster] : clusters_score) {
    std::unordered_set<std::string> individual;
    for (auto &[id, score] : cluster) {
      individual.insert(id);
    }
    pop.push_back(individual);
  }

  std::vector<std::pair<size_t, size_t>> objectives;
  for (auto &individual : pop) {
    std::vector<EvaluatorClusterElement> c;
    for (auto &token : individual) {
      EvaluatorClusterElement ce;
      ce.first = token;
      ce.second = tokenToDiff.at(token)._coveredInstances;
      c.push_back(ce);
    }
    size_t nUniqueElements = getNUniqueElementsEvaluator(c);
    objectives.emplace_back(individual.size(), nUniqueElements);
  }
}

void cluster(std::unordered_map<std::string, Diff> &tokenToDiff,
             bool normalize) {

  if (clc::ve_cls_type == "nsga2") {
    cluster_with_nsga2(tokenToDiff);
  } else if (clc::ve_cls_type == "kmeans") {
    cluster_with_kmeans(tokenToDiff, normalize);
  }
}
