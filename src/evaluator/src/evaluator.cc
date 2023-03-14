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
std::string ve_technique = "";
std::string ve_tracePath = "";
std::string ve_ftPath = "";
std::string ve_infoList = "";
std::string ve_dumpTo = ".";
size_t ve_nStatements = 0;
int ve_cluster = 1;
bool ve_stopExecution=0;
// number of assertions processed each time
size_t ve_chunkSize = 100000;
bool ve_print_failing_ass = 0;
bool ve_recover_diff = 0;
bool ve_recover_cls = 0;
double ve_nsga2_mi=1.f;
bool ve_pushp=0;
std::string ve_pushp_design = "";
bool ve_only_sim=0;
bool ve_genRand=0;
std::string ve_cls_type = "rand";
size_t ve_maxPushTime=-1;
} // namespace clc

using namespace harm;
using namespace expression;

TraceReader *parseTrace(std::string path) {

  TraceReader *traceReader = nullptr;
  if (clc::parserType == "vcd") {
    traceReader = new VCDtraceReader(path, clc::clk);
  } else if (clc::parserType == "csv") {
    traceReader = new CSVtraceReader(path);
  } else {
    messageError("Unknown parser type");
  }

  return traceReader;
}

std::vector<size_t> findAllOccs(const std::string &str,
                                const std::string &sub) {

  std::vector<size_t>
      positions; // holds all the positions that sub occurs within str

  size_t pos = str.find(sub, 0);
  while (pos != std::string::npos) {
    positions.push_back(pos);
    pos = str.find(sub, pos + 1);
  }

  return positions;
}

// read assertions from file
std::vector<std::string> readAssertions(std::string assPath) {
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
  return ret;
}

inline void subVarInPropStr(
    const std::unordered_map<
        Proposition *, std::unordered_map<std::string, std::vector<size_t>>>
        &pToVarsToPositions,
    const std::string &substitute, Proposition *p, const std::string &varName,
    size_t saIndex, std::string &originalStrCopy) {
  size_t strSizeIncrement = 0;
  for (auto &pos : pToVarsToPositions.at(p).at(varName)) {
    originalStrCopy.replace(pos + strSizeIncrement, varName.size(), substitute);
    strSizeIncrement += substitute.size() - varName.size();
  }
}
inline void fillUtilityVars(
    std::unordered_map<Proposition *,
                       std::unordered_map<std::string, std::vector<size_t>>>
        &pToVarsToPositions,
    std::unordered_map<Template *,
                       std::vector<std::pair<Proposition *, std::string>>>
        &aToProps,
    Proposition *p, Template *ass) {

  auto s = prop2String(*p);
  auto copy = s;
  auto vars = getVars(*p);

  std::sort(vars.begin(), vars.end(),
            [](const std::pair<std::string, size_t> &e1,
               const std::pair<std::string, size_t> &e2) {
              return e1.first.size() > e2.first.size();
            });
  vars.erase(std::unique(vars.begin(), vars.end()), vars.end());
  for (auto &[v, d1] : vars) {
    pToVarsToPositions[p][v] = findAllOccs(copy, v);
    std::string fillStr(v.size(), ' ');
    for (auto &pos : pToVarsToPositions[p][v]) {
      copy.replace(pos, v.size(), fillStr);
    }
  }
  aToProps[ass].emplace_back(p, s);
}
void getDiffSR(std::unordered_map<std::string, Diff> &stmToDiff,
               std::vector<std::string> &ids,
               std::vector<harm::Template *> &assertions, bool enablePB) {

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
      //messageWarning("Can not find '" + fn + "'\n\n");
      if (enablePB) {
        pb.increment(1);
      }
      continue;
    }
    TraceReader *tr = parseTrace(fn);
    Trace *ft = tr->readTrace();
    delete tr;

    std::unordered_map<size_t, size_t> &cov = stmToDiff[s]._coverage;
    size_t &atcf = stmToDiff[s]._atcf;
    std::unordered_set<std::string> &covInstances =
        stmToDiff[s]._coveredInstances;

    for (size_t assId = 0; assId < assertions.size(); assId++) {

      auto &a = assertions[assId];
      Template *fAss = hparser::parseTemplate(a->getAssertion(), ft);

      for (size_t i = 0; i < fAss->_max_length; i++) {
        if (fAss->evaluate(i) == Trinary::F) {
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

void getDiffVBR(std::unordered_map<std::string, Diff> &csvVarToDiff,
                std::unordered_map<std::string, size_t> &varToSize,
                std::vector<std::string> &vars,
                std::vector<harm::Template *> &assertions, bool enablePB) {

  progresscpp::ParallelProgressBar pb;
  if (enablePB) {
    pb.addInstance(1, std::string("Evaluating assertions... "), vars.size(),
                   70);
  }
  clc::isilent = 1;

  for (auto &v : vars) {
    // parse the ft
    for (size_t i = 0; i < varToSize.at(v); i++) {
      std::string fn = clc::ve_ftPath + "/" + v + "[" + std::to_string(i) +
                       "]" + (clc::parserType == "vcd" ? ".vcd" : ".csv");
      if (enablePB) {
        pb.changeMessage(1, fn);
      }
      if (!std::filesystem::exists(fn)) {
        messageWarning("Can not find '" + fn + "'");
        continue;
      }
      TraceReader *tr = parseTrace(fn);
      Trace *ft = tr->readTrace();
      delete tr;

      std::string varCSVformat =
          v + "," + std::to_string(varToSize.at(v)) + "," + std::to_string(i);
      std::unordered_map<size_t, size_t> &cov =
          csvVarToDiff[varCSVformat]._coverage;
      size_t &atcf = csvVarToDiff[varCSVformat]._atcf;
      std::unordered_set<std::string> &covInstances =
          csvVarToDiff[varCSVformat]._coveredInstances;

      for (size_t assId = 0; assId < assertions.size(); assId++) {

        auto &a = assertions[assId];
        Template *fAss = hparser::parseTemplate(a->getAssertion(), ft);

        for (size_t i = 0; i < fAss->_max_length; i++) {
          if (fAss->evaluate(i) == Trinary::F) {
            atcf++;
            cov[i]++;
            covInstances.insert(std::to_string(assId) + "," +
                                std::to_string(i));
          }
        }

        delete fAss;
      }

      delete ft;
    }
    if (enablePB) {
      pb.increment(1);
    }
  }
  if (enablePB) {
    pb.done(1);
  }
  clc::isilent = 0;
}
void getDiffBR(std::unordered_map<std::string, Diff> &csvIdToDiff,
               std::unordered_map<std::string, size_t> &idToSize,
               std::vector<std::string> &ids,
               std::vector<harm::Template *> &assertions, bool enablePB) {

  progresscpp::ParallelProgressBar pb;
  if (enablePB) {
    pb.addInstance(1, std::string("Evaluating assertions... "), ids.size(), 70);
  }
  clc::isilent = 1;

  for (auto &id : ids) {
    //evaluate the assertions on the faulty trace generated with token id

    //retrieve the faulty trace
    for (size_t i = 0; i < idToSize.at(id); i++) {
      std::string fn = clc::ve_ftPath + "/" + id + "_" + std::to_string(i) +
                       (clc::parserType == "vcd" ? ".vcd" : ".csv");
      if (enablePB) {
        pb.changeMessage(1, fn);
      }

      if (!std::filesystem::exists(fn)) {
        messageWarning("Can not find '" + fn + "'\n\n");
        if (enablePB) {
          pb.increment(1);
        }
        continue;
      }

      // parse the faulty trace
      TraceReader *tr = parseTrace(fn);
      Trace *ft = tr->readTrace();
      delete tr;

      //eval assertions
      for (size_t assId = 0; assId < assertions.size(); assId++) {

        auto &a = assertions[assId];

        Template *fAss = hparser::parseTemplate(a->getAssertion(), ft);

        std::string idCSVformat = id + "," + std::to_string(idToSize.at(id)) +
                                  "," + std::to_string(i);
        std::unordered_map<size_t, size_t> &cov =
            csvIdToDiff[idCSVformat]._coverage;

        std::unordered_set<std::string> &covInstances =
            csvIdToDiff[idCSVformat]._coveredInstances;

        size_t &atcf = csvIdToDiff[idCSVformat]._atcf;

        for (size_t i = 0; i < fAss->_max_length; i++) {
          if (fAss->evaluate(i) == Trinary::F) {
            atcf++;
            cov[i]++;
            covInstances.insert(std::to_string(assId) + "," +
                                std::to_string(i));
          }
        }

        delete fAss;
      }

      delete ft;
    }
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

void dumpParetoAllComb(
    std::vector<std::vector<EvaluatorClusterElement>> clusters) {

  std::vector<std::vector<size_t>> listOfCombs;
  size_t maxClusters = 14;
  size_t maxSize = 14;

  std::vector<std::pair<size_t, size_t>> objectives;
  std::vector<std::unordered_set<std::string>> pop;

  for (size_t i = 1; i < clusters.size() && i <= maxSize; i++) {
    std::cout << "================================[" << i << "]"
              << "\n";
    comb(clusters.size() > maxClusters ? maxClusters : clusters.size(), i,
         listOfCombs);
    for (auto &comb : listOfCombs) {
      size_t nTokens = 0;
      std::vector<std::vector<EvaluatorClusterElement>> selectedClusters;
      //get conf label, conf size
      for (auto &index : comb) {
        nTokens += clusters[index].size();
        selectedClusters.push_back(clusters[index]);
      }

      size_t nUniqueElements = getNUniqueElementsEvaluator(selectedClusters);

      std::unordered_set<std::string> individual;
      for (auto &c : selectedClusters) {
        for (auto &[id, f] : c) {
          individual.insert(id);
        }
        pop.push_back(individual);
        objectives.emplace_back(nTokens, nUniqueElements);
      }
    }

    listOfCombs.clear();
  }

  std::cout << "Dumping pareto front..."
            << "\n";
  auto ranks = generateDominanceRank(pop, objectives);
  std::ofstream out(clc::ve_dumpTo + "/" + clc::ve_technique +
                    "_paretoFront.csv");
  out << "nTokens, nUniqueInstances\n";
  for (size_t i = 0; i < objectives.size(); i++) {
    if (ranks[i] == 0) {
      out << objectives[i].first << ";" << objectives[i].second << "\n";
    }
  }

  out.close();
}
std::vector<size_t>
getNRandoms(size_t l, size_t r, size_t n,
            std::unordered_set<std::string> &alreadyPresent) {
  if (n > (r - l) || n == 0) {
    std::cout << n << "," << r << "," << l << "\n";
    throw std::invalid_argument("n must be greater or equal to r-l");
  }
  std::vector<size_t> result;
  result.reserve(n);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<size_t> distrib(l, r);
  std::string key = "";

  while (result.size() < n) {
    size_t num = distrib(gen);
    if (std::find(result.begin(), result.end(), num) == result.end()) {
      result.push_back(num);
    }
  }
  std::sort(begin(result), end(result));

  for (auto &i : result) {
    key += std::to_string(i) + ",";
  }

  if (alreadyPresent.count(key)) {
    return std::vector<size_t>({(size_t)-1});
  }
  alreadyPresent.insert(key);

  return result;
}
void dumpParetoRandom(
    std::vector<std::vector<EvaluatorClusterElement>> clusters) {

  std::vector<std::vector<size_t>> listOfCombs;
  size_t confIndex = 0;
  size_t maxClusters = 22;
  size_t maxSize = 22;
  size_t nRandomCombsPerSize = 3000;

  std::vector<std::pair<size_t, size_t>> objectives;
  std::vector<std::unordered_set<std::string>> pop;

  for (size_t i = 1; i < clusters.size() && i <= maxSize; i++) {
    std::cout << "================================[" << i << "]"
              << "\n";
    std::unordered_set<std::string> alreadyPresent;
    for (size_t j = 0; j < nRandomCombsPerSize; j++) {
      listOfCombs.push_back(
          getNRandoms(0, clusters.size() - 1, i, alreadyPresent));
      if (listOfCombs.back()[0] == -1) {
        listOfCombs.pop_back();
      }
    }
    alreadyPresent.clear();
    std::cout << listOfCombs.size() << "\n";
    auto start = std::chrono::steady_clock::now();

    for (auto &comb : listOfCombs) {

      size_t nTokens = 0;
      std::vector<std::vector<EvaluatorClusterElement>> selectedClusters;
      //get conf label, conf size
      for (auto &index : comb) {
        nTokens += clusters[index].size();
        selectedClusters.push_back(clusters[index]);
      }

      size_t nUniqueElements = getNUniqueElementsEvaluator(selectedClusters);

      std::unordered_set<std::string> individual;
      for (auto &c : selectedClusters) {
        for (auto &[id, f] : c) {
          individual.insert(id);
        }
        pop.push_back(individual);
        objectives.emplace_back(nTokens, nUniqueElements);
      }
    }
    auto stop = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::seconds>(stop - start);

    std::cout << duration.count() << "s\n";

    listOfCombs.clear();
  }

  std::cout << "Dumping pareto front..."
            << "\n";
  auto ranks = generateDominanceRank(pop, objectives);

  std::ofstream out(clc::ve_dumpTo + "/" + clc::ve_technique +
                    "_paretoFront.csv");
  out << "nTokens, nUniqueInstances\n";
  for (size_t i = 0; i < objectives.size(); i++) {
    if (ranks[i] == 0) {
      out << objectives[i].first << ";" << objectives[i].second << "\n";
    }
  }

  out.close();
}

void dumpKmeans(std::unordered_map<std::string, Diff> &tokenToDiff,
                bool normalize) {

  auto scores = converToScores(tokenToDiff, normalize);

  std::ofstream out(clc::ve_dumpTo + "/" + std::string("rank_") +
                    clc::ve_technique + (normalize ? "_nor" : "") +
                    "_kmeans.csv");

  //prep for clustering
  std::vector<double> elements;
  for (auto &v_s : scores) {
    elements.push_back(v_s.second);
  }

  std::map<size_t, std::vector<std::pair<std::string, double>>> clusters_score;

  auto clusters_range =
      clc::ve_cluster == -1
          ? kmeansElbow(elements, 10, 0.1, 1)
          : (clc::ve_cluster > 1
                 ? kmeansElbow(elements, clc::ve_cluster, 0.01, 1)
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

  //dump the scores
  if (clc::ve_technique == "vbr") {
    out << "var,size,bit,cluster,score\n";
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

  } else if (clc::ve_technique == "sr") {
    out << "statement,cluster,score\n";
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
  } else if (clc::ve_technique == "br") {
    out << "token,size,bit,cluster,score\n";
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

  std::cout << "Dumping pareto front..."
            << "\n";

  std::ofstream pout(clc::ve_dumpTo + "/" + clc::ve_technique +
                     "_paretoFront.csv");
  pout << "nTokens, nUniqueInstances\n";
  for (size_t i = 0; i < objectives.size(); i++) {
    pout << objectives[i].first << ";" << objectives[i].second << "\n";
  }

  pout.close();
}

void dumpScore(std::unordered_map<std::string, Diff> &tokenToDiff,
               bool normalize) {

  //arrange elements
  std::unordered_map<std::string, std::unordered_set<std::string>>
      arrangedElements;
  for (auto &[token, diff] : tokenToDiff) {
    arrangedElements[token] = diff._coveredInstances;
  }

  std::vector<std::vector<EvaluatorClusterElement>> hcClusters;

  if (clc::ve_cls_type != "kmeans" && clc::ve_cls_type != "nsga2") {
    if (clc::ve_recover_cls) {
      //recover clusters
      std::string filePath = clc::ve_dumpTo + "/" + std::string("hccls_") +
                             clc::ve_technique + ".csv";
      std::cout << filePath << "\n";
      messageErrorIf(!std::filesystem::exists(filePath),
                     "Could not find: " + filePath);

      std::unordered_map<size_t, std::vector<std::string>> cidToFaults;

      csv::CSVFormat format;
      format.delimiter(',');
      csv::CSVReader reader(filePath, format);
      csv::CSVRow row;

      while (reader.read_row(row)) {
        std::string id = row[0].get() + "," + row[1].get() + "," + row[2].get();
        size_t clusterID = std::stoull(row[3].get());
        cidToFaults[clusterID].push_back(id);
      }

      for (size_t id = 0; id < cidToFaults.size(); id++) {
        auto faults = cidToFaults.at(id);

        std::vector<EvaluatorClusterElement> newCls;
        for (auto &f : faults) {
          EvaluatorClusterElement ce;
          ce.first = f;
          ce.second = arrangedElements.at(f);
          newCls.push_back(ce);
        }
        hcClusters.push_back(newCls);
      }

      //for (auto &c : hcClusters) {
      //    std::cout << "======================" << "\n";
      //  for (auto &[id, faults] : c) {
      //      std::cout << "-------------------------" << "\n";
      //    std::cout << id << " "<<faults.size();
      //    std::cout <<  "\n";
      //  }
      //}
      std::cout << "Recovered clusters:" << hcClusters.size() << "\n";

    } else {
      //hc clustering
      std::cout << "HC clustering... might take a while"
                << "\n";
      hcClusters = hcElbowEvaluator(arrangedElements);

      std::ofstream out(clc::ve_dumpTo + "/" + std::string("hccls_") +
                        clc::ve_technique + ".csv");

      //dump clusters
      //print header
      if (clc::ve_technique == "br") {
        out << "token,size,bit,cluster,score\n";
      } else if (clc::ve_technique == "sr") {
        out << "statement,cluster,score\n";
      } else if (clc::ve_technique == "vbr") {
        out << "var,size,bit,cluster,score\n";
      }

      for (size_t i = 0; i < hcClusters.size(); i++) {
        auto &cls = hcClusters[i];
        size_t clusterScore = getNUniqueElementsEvaluator(cls);
        for (auto inst : cls) {
          out << inst.first << "," << i << "," << clusterScore << "\n";
        }
      }
      out.close();
    }
  }

  if (clc::ve_cls_type == "rand") {
    dumpParetoRandom(hcClusters);
  } else if (clc::ve_cls_type == "comb") {
    dumpParetoAllComb(hcClusters);
  } else if (clc::ve_cls_type == "nsga2" || clc::ve_cls_type == "nsga2pop") {
    //prepare data for nsga2
    std::vector<std::unordered_set<std::string>> initialPop;
    std::vector<std::tuple<size_t, size_t, std::unordered_set<std::string>>>
        ret;

    if (clc::ve_cls_type == "nsga2") {
      //use single elements as starting pop
      for (auto &[id, instaces] : arrangedElements) {
        std::unordered_set<std::string> individual;
        individual.insert(id);
        initialPop.push_back(individual);
      }

    } else {
      //use clusters as starting pop
      for (auto &c : hcClusters) {
        std::unordered_set<std::string> individual;
        for (auto &[id, f] : c) {
          individual.insert(id);
        }
        initialPop.push_back(individual);
      }
    }

    ret = nsga2(arrangedElements, 100000,clc::ve_nsga2_mi, initialPop);

    std::ofstream out(clc::ve_dumpTo + "/" + clc::ve_technique +
                      "_paretoFront.csv");
    out << "nTokens; nUniqueInstances\n";
    for (auto &p : ret) {
      out << std::get<0>(p) << ";" << std::get<1>(p) << "\n";
    }

    out.close();

    out = std::ofstream(clc::ve_dumpTo + "/" + std::string("rank_") +
                        clc::ve_technique + ".csv");
    //dump the scores
    if (clc::ve_technique == "vbr") {
      out << "var,size,bit,cluster,score\n";
    } else if (clc::ve_technique == "sr") {
      out << "statement,cluster,score\n";
    } else if (clc::ve_technique == "br") {
      out << "token,size,bit,cluster,score\n";
    }
    std::sort(
        ret.begin(), ret.end(),
        [](std::tuple<size_t, size_t, std::unordered_set<std::string>> &e1,
           std::tuple<size_t, size_t, std::unordered_set<std::string>> &e2) {
          return std::get<1>(e1) < std::get<1>(e2);
        });
    size_t cIndex = 0;
    for (auto &[f1, f2, tokens] : ret) {
      for (auto &token : tokens) {
        out << token << "," << cIndex << "," << f2 << "\n";
      }
      cIndex++;
    }
    out.close();

  } else if (clc::ve_cls_type == "kmeans") {
    dumpKmeans(tokenToDiff, normalize);
  }
}
