#include "evaluator.hh"
#include "CSVtraceReader.hh"
#include "DTUtils.hh"
#include "DataType.hh"
#include "EdgeProposition.hh"
#include "Hierarchical.hh"
#include "Kmeans.hh"
#include "Location.hh"
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
// number of assertions processed each time
size_t ve_chunkSize = 100000;
bool ve_print_failing_ass = 0;
bool ve_recover_diff = 0;
bool ve_clusterBySim = 0;
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
               std::vector<harm::Template *> &assertions) {

  progresscpp::ParallelProgressBar pb;
  clc::isilent = 1;
  pb.addInstance(1, std::string("Evaluating assertions... "), ids.size(), 70);

  for (auto &s : ids) {
    // parse the ft
    std::string fn =
        clc::ve_ftPath + "/" + s + (clc::parserType == "vcd" ? ".vcd" : ".csv");
    pb.changeMessage(1, fn);
    if (!std::filesystem::exists(fn)) {
      messageWarning("Can not find '" + fn + "'\n\n");
      pb.increment(1);
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
    pb.increment(1);
  }
  pb.done(1);
  clc::isilent = 0;
}

void getDiffVBR(std::unordered_map<std::string, Diff> &csvVarToDiff,
                std::unordered_map<std::string, size_t> &varToSize,
                std::vector<std::string> &vars,
                std::vector<harm::Template *> &assertions) {

  progresscpp::ParallelProgressBar pb;
#if enPB_ve
  pb.addInstance(1, std::string("Evaluating assertions... "), vars.size(), 70);
#endif
  clc::isilent = 1;

  for (auto &v : vars) {
    // parse the ft
    for (size_t i = 0; i < varToSize.at(v); i++) {
      std::string fn = clc::ve_ftPath + "/" + v + "[" + std::to_string(i) +
                       "]" + (clc::parserType == "vcd" ? ".vcd" : ".csv");
      pb.changeMessage(1, fn);
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
    pb.increment(1);
  }
  pb.done(1);
  clc::isilent = 0;
}
void getDiffBR(std::unordered_map<std::string, Diff> &csvIdToDiff,
               std::unordered_map<std::string, size_t> &idToSize,
               std::vector<std::string> &ids,
               std::vector<harm::Template *> &assertions) {

  progresscpp::ParallelProgressBar pb;
#if enPB_ve
  pb.addInstance(1, std::string("Evaluating assertions... "), ids.size(), 70);
#endif
  clc::isilent = 1;

  for (auto &id : ids) {
    //evaluate the assertions on the faulty trace generated with token id

    //retrieve the faulty trace
    for (size_t i = 0; i < idToSize.at(id); i++) {
      std::string fn = clc::ve_ftPath + "/" + id + "_" + std::to_string(i) +
                       (clc::parserType == "vcd" ? ".vcd" : ".csv");
      pb.changeMessage(1, fn);
      if (!std::filesystem::exists(fn)) {
        messageWarning("Can not find '" + fn + "'\n\n");
        pb.increment(1);
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
    pb.increment(1);
  }
  pb.done(1);
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

void generatePareto(
    std::vector<std::vector<EvaluatorClusterElement>> clusters) {
  std::vector<std::vector<size_t>> listOfCombs;

  for (size_t i = 1; i < clusters.size() && i <= 10; i++) {
//    std::cout << "================================[" << i << "]" << "\n";
    comb(clusters.size() > 10 ? 10 : clusters.size(), i, listOfCombs);
    for (auto &comb : listOfCombs) {
      std::stringstream ss;
      size_t nTokens = 0;
      std::vector<std::vector<EvaluatorClusterElement>> selectedClusters;
      ss << '{';
      for (auto &index : comb) {
        ss << index << (index != comb.back() ? " " : "},");
        nTokens += clusters[index].size();
        selectedClusters.push_back(clusters[index]);
      }

      size_t nUniqueElements = getNUniqueElementsEvaluator(selectedClusters);
      ss << nTokens << "," << nUniqueElements;
      std::cout << ss.str() << "\n";
    }

    listOfCombs.clear();
  }
}
void dumpScore(std::unordered_map<std::string, Diff> &tokenToDiff,
               bool normalize) {

  auto scores = converToScores(tokenToDiff, normalize);

  std::ofstream out(clc::ve_dumpTo + "/" + std::string("rank_") +
                    clc::ve_technique + (normalize ? "_nor" : "") + ".csv");

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

  //dump diffs
  std::ofstream outDiff(clc::ve_dumpTo + "/" + std::string("diff_") +
                        clc::ve_technique + ".csv");
  outDiff << "token; atcf; instances\n";
  for (auto &[token, diff] : tokenToDiff) {
    outDiff << token << ";" << diff._atcf << ";";
    for (auto &ci : diff._coveredInstances) {
      outDiff << ci << " ";
    }
    outDiff << "\n";
  }
  outDiff.close();

  if (clc::ve_clusterBySim && !normalize) {

    //HC clustering
    std::unordered_map<std::string, std::unordered_set<std::string>>
        arrangedElements;
    for (auto &[token, diff] : tokenToDiff) {
      arrangedElements[token] = diff._coveredInstances;
    }

    std::cout << "HC clustering... might take a while"
              << "\n";
    std::vector<std::vector<EvaluatorClusterElement>> hcClusters =
        hcElbowEvaluator(arrangedElements);

    std::ofstream out(clc::ve_dumpTo + "/" + std::string("rank_") +
                      clc::ve_technique + "_bySim" + ".csv");

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

    generatePareto(hcClusters);
  }
}
