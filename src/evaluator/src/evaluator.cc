#include "evaluator.hh"
#include "CSVtraceReader.hh"
#include "DataType.hh"
#include "EdgeProposition.hh"
#include "Kmeans.hh"
#include "Location.hh"
#include "ProgressBar.hpp"
#include "Template.hh"
#include "VCDtraceReader.hh"
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
void getDiffSR(
    std::unordered_map<std::string, Diff> &stmToDiff,
    std::unordered_map<std::string, std::vector<Template *>> &stmToAss,
    std::unordered_map<std::string, std::vector<std::string>>
        &tokenToFailingAssertions) {

  progresscpp::ParallelProgressBar pb;
  clc::isilent = 1;
  pb.addInstance(1, std::string("Evaluating assertions... "), stmToAss.size(),
                 70);

  for (auto &[s, assertions] : stmToAss) {
    // parse the ft
    std::string fn =
        clc::ve_ftPath + "/" + s + (clc::parserType == "vcd" ? ".vcd" : ".csv");
    pb.changeMessage(1, fn);
    if (!std::filesystem::exists(fn)) {
      messageWarning("Can not find '" + fn + "'");
      continue;
    }
    TraceReader *tr = parseTrace(fn);
    Trace *ft = tr->readTrace();
    delete tr;

    for (auto &a : assertions) {

      Template *fAss = hparser::parseTemplate(a->getAssertion(), ft);
      size_t atcf = 0;
      std::unordered_map<size_t, size_t> &cov = stmToDiff[s]._coverage;

      for (size_t i = 0; i < fAss->_max_length; i++) {
        if (fAss->evaluate(i) == Trinary::F) {
          atcf++;
          cov[i]++;
        }
      }
      //debug
      if (atcf > 0) {
        tokenToFailingAssertions[s].push_back(a->getColoredAssertion() +
                                              " --> " + std::to_string(atcf));
      }
      stmToDiff[s]._atcf += atcf;

      delete fAss;
    }

    delete ft;
    pb.increment(1);
  }
  pb.done(1);
  clc::isilent = 0;
}

void getDiffVBR(
    std::unordered_map<std::string, Diff> &varToDiff,
    std::unordered_map<std::string, size_t> &varToSize,
    std::unordered_map<std::string, std::vector<Template *>> &varToAss) {

  progresscpp::ParallelProgressBar pb;
#if enPB_ve
  pb.addInstance(1, std::string("Evaluating assertions... "), varToAss.size(),
                 70);
#endif
  clc::isilent = 1;

  for (auto &[v, assertions] : varToAss) {
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

      for (auto &a : assertions) {

        Template *fAss = hparser::parseTemplate(a->getAssertion(), ft);

        size_t atcf = 0;
        std::string varCSVformat = v + "," + std::to_string(varToSize.at(v))+","+ std::to_string(i);
        std::unordered_map<size_t, size_t> &cov =
            varToDiff[varCSVformat]._coverage;

        for (size_t i = 0; i < fAss->_max_length; i++) {
          if (fAss->evaluate(i) == Trinary::F) {
            atcf++;
            cov[i]++;
          }
        }
        varToDiff[varCSVformat]._atcf += atcf;

        delete fAss;
      }

      delete ft;
    }
    pb.increment(1);
  }
  pb.done(1);
  clc::isilent = 0;
}
void getDiffBR(
    std::unordered_map<std::string, Diff> &idToDiff,
    std::unordered_map<std::string, size_t> &idToSize,
    std::unordered_map<std::string, std::vector<Template *>> &idToAss) {

  progresscpp::ParallelProgressBar pb;
#if enPB_ve
  pb.addInstance(1, std::string("Evaluating assertions... "), idToAss.size(),
                 70);
#endif
  clc::isilent = 1;

  for (auto &[id, assertions] : idToAss) {
    // parse the ft
    for (size_t i = 0; i < idToSize.at(id); i++) {
      std::string fn = clc::ve_ftPath + "/" + id + "_" + std::to_string(i) +
                       (clc::parserType == "vcd" ? ".vcd" : ".csv");
      pb.changeMessage(1, fn);
      if (!std::filesystem::exists(fn)) {
        messageWarning("Can not find '" + fn + "'");
        continue;
      }
      TraceReader *tr = parseTrace(fn);
      Trace *ft = tr->readTrace();
      delete tr;

      for (auto &a : assertions) {

        Template *fAss = hparser::parseTemplate(a->getAssertion(), ft);

        size_t atcf = 0;
        std::string idCSVformat = id + "," +std::to_string(idToSize.at(id))+ "," + std::to_string(i);
        std::unordered_map<size_t, size_t> &cov =
            idToDiff[idCSVformat]._coverage;

        for (size_t i = 0; i < fAss->_max_length; i++) {
          if (fAss->evaluate(i) == Trinary::F) {
            atcf++;
            cov[i]++;
          }
        }
        idToDiff[idCSVformat]._atcf += atcf;

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
    for (auto &[var, diff] : tokenToDiff) {
      double score = 0.f;
      for (auto &[id, v] : diff._coverage) {
        //use a log function to normalize
        score += 1.f + log(v);
      }
      scores.emplace_back(var, score);
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
}
