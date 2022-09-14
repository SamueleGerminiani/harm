#include "varEstimator.hh"
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
std::string ftPath = "";
std::string vars = "";
size_t ve_nStatements = 0;
size_t ve_cluster = 1;
// number of assertions processed each time
size_t ve_chunkSize = 100000;
} // namespace clc

using namespace harm;
using namespace expression;

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
std::unordered_map<std::string, std::vector<Template *>>
discardAssertionsGroupBy(std::vector<Template *> &assertions, int groupBy) {

  size_t ignoredAssertions = 0;
  // ass to <antVars,conVars>
  std::unordered_map<Template *,
                     std::pair<std::set<std::string>, std::set<std::string>>>
      aToVars;
#if enPB_ve
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Discarding assertions...", assertions.size(), 70);
#endif

  for (auto &ass : assertions) {
    // props in the con
    std::vector<std::pair<Proposition *, size_t>> conProps;
    // props in the ant
    std::vector<std::pair<Proposition *, size_t>> antProps;

    // gather the variables: ass -> (1)props -> (2)vars

    // gather the propositions (1)
    // con props
    auto lp = ass->getLoadedPropositionsWithDepthCon();
    conProps.insert(conProps.end(), lp.begin(), lp.end());
    // ant props
    lp = ass->getLoadedPropositionsWithDepthAnt();
    antProps.insert(antProps.end(), lp.begin(), lp.end());
    // gather unique variables (2)
    std::set<std::string> conVars;
    std::set<std::string> antVars;
    for (auto pd : conProps) {
      auto lv = getVars(*pd.first, true);
      for (auto v : lv) {
        conVars.insert(v.first);
      }
    }
    for (auto pd : antProps) {
      auto lv = getVars(*pd.first, true);
      for (auto &v : lv) {
        antVars.insert(v.first);
      }
    }

    // gropByant
    if (groupBy == 0) {
      // only consider assertions where the antecedents's variables do not
      // appear in the consequent
      for (auto &v : antVars) {
        if (conVars.count(v)) {
          // ignore assertion
          ignoredAssertions++;
          delete ass;
          ass = nullptr;
          goto dontAdd;
        }
      }
      // save assertion
      aToVars[ass] = std::make_pair(antVars, conVars);

    } else if (groupBy == 1) {
      // only consider assertions where the consequent's variables do not appear
      // in the antecedent
      for (auto &v : conVars) {
        if (antVars.count(v)) {
          // ignore assertion
          ignoredAssertions++;
          delete ass;
          ass = nullptr;
          goto dontAdd;
        }
      }
      // save assertion
      aToVars[ass] = std::make_pair(antVars, conVars);
    } else {
      messageError("Not supported");
      // consider all assertions
      aToVars[ass] = std::make_pair(antVars, conVars);
    }
  dontAdd:;
#if enPB_ve
    pb.increment(0);
    pb.display();
#endif
  }
#if enPB_ve
  pb.done(0);
#endif

  std::cout << "Ignored assertions:" << ignoredAssertions << "\n";

  std::unordered_map<std::string, std::vector<Template *>> varToAss;
  std::unordered_set<std::string> allACVars;
  if (groupBy == 0) {
    // get all vars in the antecedents
    for (auto &ac : aToVars) {
      allACVars.insert(ac.second.first.begin(), ac.second.first.end());
    }
  } else if (groupBy == 1) {
    // get all vars in the consequents
    for (auto &ac : aToVars) {
      allACVars.insert(ac.second.second.begin(), ac.second.second.end());
    }
  } else {
    messageError("Not supported");
    // get all vars
    for (auto &ac : aToVars) {
      allACVars.insert(ac.second.second.begin(), ac.second.second.end());
    }
    for (auto &ac : aToVars) {
      allACVars.insert(ac.second.first.begin(), ac.second.first.end());
    }
  }

  // groupBy var name
  for (auto &var1 : allACVars) {
    for (auto &[ass, vars] : aToVars) {
      if (groupBy == 0) {
        for (auto &antVar2 : vars.first) {
          if (var1 == antVar2) {
            varToAss[var1].push_back(ass);
            break;
          }
        }
      } else if (groupBy == 1) {
        for (auto &conVar2 : vars.second) {
          if (var1 == conVar2) {
            varToAss[var1].push_back(ass);
            break;
          }
        }
      } else {
        messageError("Not supported");
        for (auto &antVar2 : vars.first) {
          if (var1 == antVar2) {
            varToAss[var1].push_back(ass);
            break;
          }
        }
        for (auto &conVar2 : vars.second) {
          if (var1 == conVar2) {
            varToAss[var1].push_back(ass);
            break;
          }
        }
      }
    }
  }

  // remove ignored assertions
  assertions.erase(std::remove(assertions.begin(), assertions.end(), nullptr),
                   assertions.end());

  // return the assertions grouped by the con vars
  return varToAss;
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
//void getDiffFT(
//    std::unordered_map<std::string, Diff> &varToDiff,
//    std::unordered_map<std::string, size_t> &varToSize,
//    std::unordered_map<std::string, std::vector<Template *>> &varToAss,
//    Trace *trace) {
//
//  //  std::unordered_map<std::string, size_t> varToSize;
//  //  // get the size of all variables
//  //  for (auto &vaa : varToAss) {
//  //    varToSize[vaa.first] = trace->getVarSize(vaa.first);
//  //  }
//
//  progresscpp::ParallelProgressBar pb;
//#if enPB_ve
//  pb.addInstance(1, std::string("Evaluating assertions... "), varToAss.size(),
//                 70);
//#endif
//  clc::isilent = 1;
//
//  for (auto &[v, assertions] : varToAss) {
//    // parse the ft
//    for (size_t i = 0; i < varToSize.at(v); i++) {
//      std::string varName = v + "[" + std::to_string(i) + "]";
//      std::string fn = clc::ftPath + "/" + varName + ".vcd";
//      pb.changeMessage(1, fn);
//      if (!std::filesystem::exists(fn)) {
//        messageWarning("Can not find '" + fn + "'");
//        continue;
//      }
//      TraceReader *tr = new harm::VCDtraceReader(fn, clc::clk);
//      Trace *ft = tr->readTrace();
//      delete tr;
//      size_t nThreads = 16;
//      Semaphore sem(nThreads);
//      size_t served = 0;
//      std::mutex cs;
//      std::mutex ss;
//      while (served < assertions.size()) {
//        sem.wait();
//        auto a = assertions[served];
//        served++;
//
//        std::thread([&ss, &cs, &sem, &a, &ft, &varToDiff, &varName] {
//
//          size_t ct[3][3] = {{0}};
//          a->setCacheAntFalse();
//          a->setCacheConFalse();
//          a->setL1Threads(2);
//          a->fillContingency(ct, 0);
//
//          ss.lock();
//          Template *fAss = hparser::parseTemplate(a->getAssertion(), ft);
//          ss.unlock();
//
//          fAss->setCacheAntFalse();
//          fAss->setCacheConFalse();
//          fAss->setL1Threads(2);
//
//          size_t ctWS[3][3] = {{0}};
//          fAss->fillContingency(ctWS, 0);
//
//          cs.lock();
//          // save the diffs
//          varToDiff[varName]._atct += std::abs((int)(ct[0][0] - ctWS[0][0]));
//          varToDiff[varName]._atcf += std::abs((int)(ct[0][1] - ctWS[0][1]));
//          varToDiff[varName]._nAssertions+= (std::abs((int)(ct[0][1] - ctWS[0][1]))>0?1:0);
//          cs.unlock();
//          delete fAss;
//          sem.notify();
//        }).detach();
//      }
//      for (size_t i = 0; i < nThreads; i++) {
//        sem.wait();
//      }
//
//      delete ft;
//    }
//    pb.increment(1);
//  }
//  pb.done(1);
//  clc::isilent = 0;
//}
void getDiffFT_LP(
    std::unordered_map<std::string, Diff> &stmToDiff,
    std::unordered_map<std::string, std::vector<Template *>> &stmToAss) {

  progresscpp::ParallelProgressBar pb;
  clc::isilent = 1;
  pb.addInstance(1, std::string("Evaluating assertions... "), stmToAss.size(),
                 70);

  for (auto &[s, assertions] : stmToAss) {
    // parse the ft
    std::string fn = clc::ftPath + "/" + s + ".vcd";
    pb.changeMessage(1, fn);
    if (!std::filesystem::exists(fn)) {
      messageWarning("Can not find '" + fn + "'");
      continue;
    }
    TraceReader *tr = new harm::VCDtraceReader(fn, clc::clk);
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
      stmToDiff[s]._atcf += atcf;

      delete fAss;
    }

    delete ft;
    pb.increment(1);
  }
  pb.done(1);
  clc::isilent = 0;
}

void getDiffFT(
    std::unordered_map<std::string, Diff> &varToDiff,
    std::unordered_map<std::string, size_t> &varToSize,
    std::unordered_map<std::string, std::vector<Template *>> &varToAss,
    Trace *trace) {

  //  std::unordered_map<std::string, size_t> varToSize;
  //  // get the size of all variables
  //  for (auto &vaa : varToAss) {
  //    varToSize[vaa.first] = trace->getVarSize(vaa.first);
  //  }

  progresscpp::ParallelProgressBar pb;
#if enPB_ve
  pb.addInstance(1, std::string("Evaluating assertions... "), varToAss.size(),
                 70);
#endif
  clc::isilent = 1;

  for (auto &[v, assertions] : varToAss) {
    // parse the ft
    for (size_t i = 0; i < varToSize.at(v); i++) {
      std::string varName = v + "[" + std::to_string(i) + "]";
      std::string fn = clc::ftPath + "/" + varName + ".vcd";
      pb.changeMessage(1, fn);
      if (!std::filesystem::exists(fn)) {
        messageWarning("Can not find '" + fn + "'");
        continue;
      }
      TraceReader *tr = new harm::VCDtraceReader(fn, clc::clk);
      Trace *ft = tr->readTrace();
      delete tr;

      for (auto &a : assertions) {

        Template *fAss = hparser::parseTemplate(a->getAssertion(), ft);
        //fAss->setL1Threads(4);

        // size_t ct[3][3] = {{0}};
        // fAss->fillContingency(ct, 0);

        // // save the diffs
        // varToDiff[varName]._atcf += ct[0][1];
        // varToDiff[varName]._nAssertions += ((int)(ct[0][1]) > 0 ? 1 : 0);
        //varToDiff[varName]._weight+=(double)ct[0][1]/(double)ct[0][0];
        size_t atcf = 0;
        std::unordered_map<size_t, size_t> &cov = varToDiff[varName]._coverage;

        for (size_t i = 0; i < fAss->_max_length; i++) {
          if (fAss->evaluate(i) == Trinary::F) {
            atcf++;
            cov[i]++;
          }
        }
        varToDiff[varName]._atcf += atcf;

        delete fAss;
      }

      delete ft;
    }
    pb.increment(1);
  }
  pb.done(1);
  clc::isilent = 0;
}

void getDiff(std::unordered_map<std::string, Diff> &varToDiff,
             std::unordered_map<std::string, std::vector<Template *>> &varToAss,
             Trace *trace, int where) {

  std::unordered_map<std::string, size_t> varToSize;
  // get the size of all variables
  for (auto &vaa : varToAss) {
    varToSize[vaa.first] = trace->getLogicVariable(vaa.first)->getType().second;
  }

  // utility vars
  std::unordered_map<Template *,
                     std::vector<std::pair<Proposition *, std::string>>>
      aToProps;
  std::unordered_map<Proposition *,
                     std::unordered_map<std::string, std::vector<size_t>>>
      pToVarsToPositions;

  // gather all assertions
  std::unordered_set<Template *> uniqueAss;
  for (auto &[var, assertions] : varToAss) {
    for (auto &ass : assertions) {
      uniqueAss.insert(ass);
    }
  }
  // ass to props + prop to positions
  for (auto &ass : uniqueAss) {
    if (where == 0) {
      for (auto &[p, d] : ass->getLoadedPropositionsWithDepthAnt()) {
        fillUtilityVars(pToVarsToPositions, aToProps, p, ass);
      }
    } else if (where == 1) {
      for (auto &[p, d] : ass->getLoadedPropositionsWithDepthCon()) {
        fillUtilityVars(pToVarsToPositions, aToProps, p, ass);
      }
    } else {
      messageError("Not supported");
      for (auto &[p, d] : ass->getLoadedPropositionsWithDepthAnt()) {
        fillUtilityVars(pToVarsToPositions, aToProps, p, ass);
      }
      for (auto &[p, d] : ass->getLoadedPropositionsWithDepthCon()) {
        fillUtilityVars(pToVarsToPositions, aToProps, p, ass);
      }
    }
  }

  // calculate the amount of work (for progress bar)
  size_t nEvals = 0;
  for (auto &vaa : varToAss) {
    nEvals += vaa.second.size() * varToSize.at(vaa.first);
  }

  // double the ammount if x is considered
  if (clc::ve_sa == 2) {
    nEvals *= 2;
  }

  progresscpp::ParallelProgressBar pb;
#if enPB_ve
  pb.addInstance(1,
                 std::string("Evaluating assertions... ") + "Stuck at " +
                     (clc::ve_sa != 2 ? std::to_string(clc::ve_sa) : "X"),
                 nEvals, 70);
#endif
  // to protect the shared memory
  std::mutex atcfM;

  for (auto &vaa : varToAss) {
    // retreive the size
    size_t varSize = varToSize.at(vaa.first);
    // for all bits of the considered variable
    for (size_t saIndex = 0; saIndex < varSize; saIndex++) {
      // stuck at 0,1 or X
      for (size_t stuckAt = 0; stuckAt <= 1; stuckAt++) {
        // execute only for the required stuck at
        if (!(clc::ve_sa == 2 || (clc::ve_sa == stuckAt)))
          continue;

        // size_t feasThreads = 1;
        size_t feasThreads = std::thread::hardware_concurrency();
        std::thread threadArray[feasThreads];
        for (size_t nThread = 0; nThread < feasThreads; ++nThread) {
          threadArray[nThread] =
              std::thread([nThread, feasThreads, &pb, &vaa, saIndex, &trace,
                           &varToDiff, &atcfM, &varSize, stuckAt, &aToProps,
                           &pToVarsToPositions, where]() {
                // assertions related to the current variable
                auto &assertions = vaa.second;
                size_t pad = assertions.size() / feasThreads;
                // sp is exacly the first ass
                size_t sp = nThread * pad;
                // ep is 1 unit after the last ass
                size_t ep = (nThread == (feasThreads - 1)) ? assertions.size()
                                                           : (sp + pad);

                for (size_t i = sp; i < ep; i++) {
                  size_t ct[3][3] = {{0}};
                  size_t ctWS[3][3] = {{0}};
                  // current assertion
                  Template *ass = assertions[i];

                  if (where == 0) {
                    ass->setCacheAntFalse();
                  } else if (where == 1) {
                    ass->setCacheConFalse();
                  } else {
                    messageError("Not supported");
                    ass->setCacheAntFalse();
                    ass->setCacheConFalse();
                  }
                  ass->fillContingency(ct, 0);

                  std::vector<std::pair<Proposition *, std::string>> props =
                      aToProps.at(ass);
                  std::vector<std::pair<Proposition *, Proposition *>> subs;
                  // sub in all props
                  for (auto &[p, s] : props) {
                    if (prop2String(*p) == "true" ||
                        !pToVarsToPositions.at(p).count(vaa.first))
                      continue;

                    std::string originalStrCopy = s;
                    std::string substitute = "";
                    // debug
                    // std::cout << vaa.first << "\n";
                    // std::cout << originalStrCopy << "\n";
                    // copy the original as it is read by multiple threads
                    // in parallel
                    // bool var
                    if (varSize == 1) {
                      substitute = stuckAt == 1 ? "(" + vaa.first + " || 1)"
                                                : "(" + vaa.first + " && 0)";
                    } else if (stuckAt == 1) {
                      // get a 'stuck at 1' version of the proposition
                      if (clc::ve_consecutive) {
                        substitute =
                            "(" + vaa.first + " | " +
                            (std::to_string((1ULL << (saIndex + 1)) - 1)) + ")";

                      } else {
                        substitute = "(" + vaa.first + " | " +
                                     (std::to_string(1ULL << saIndex)) + ")";
                      }
                    } else if (stuckAt == 0) {
                      // get a 'stuck at 0' version of the proposition
                      if (clc::ve_consecutive) {
                        substitute =
                            "(" + vaa.first + " & " +
                            (std::to_string(
                                 (~((1ULL << (saIndex + 1)) - 1) << 1) >> 1) +
                             ")");
                      } else {
                        substitute =
                            "(" + vaa.first + " & " +
                            (std::to_string(
                                 (~((uint64_t)(1ULL << saIndex)) << 1) >> 1) +
                             ")");
                      }
                    } else {
                      messageError("Unknown stuck at option!");
                    }

                    subVarInPropStr(pToVarsToPositions, substitute, p,
                                    vaa.first, saIndex, originalStrCopy);
                    // debug
                    // std::cout << originalStrCopy << "\n";
                    // retrieve the prop with the stuck at
                    Proposition *withSA =
                        hparser::parseProposition(originalStrCopy, trace);
                    // save the substitutions
                    subs.emplace_back(p, withSA);
                    // debug
                    // std::cout << ass->getColoredAssertion() << "\n";
                    // std::cout << prop2String(*p) << " -> "
                    //          << prop2String(*withSA) << "\n";

                    // sub the original prop with the modified one
                    ass->subPropInAssertion(p, withSA);
                    // debug
                    // std::cout << ass->getColoredAssertion() << "\n";
                    // free con cache (we have changed the expression)
                  }

                  if (where == 0) {
                    ass->setCacheAntFalse();
                  } else if (where == 1) {
                    ass->setCacheConFalse();
                  } else {
                    messageError("Not supported");
                    ass->setCacheAntFalse();
                    ass->setCacheConFalse();
                  }
                  ass->fillContingency(ctWS, 0);

                  std::string varName = "";
                  if (clc::ve_consecutive) {
                    varName = vaa.first + " bits [" + std::to_string(saIndex) +
                              ", 0]";
                  } else {
                    varName = vaa.first + " bit " + std::to_string(saIndex);
                  }
                  //             join
                  //             varName = vaa.first;
                  atcfM.lock();
                  // save the diffs
                  varToDiff[varName]._atct +=
                      std::abs((int)(ct[0][0] - ctWS[0][0]));
                  varToDiff[varName]._atcf +=
                      std::abs((int)(ct[0][1] - ctWS[0][1]));
                  varToDiff[varName]._nAssertions++;
                  atcfM.unlock();

                  // remove stuck from assertion
                  for (auto &[o, wsa] : subs) {
                    ass->subPropInAssertion(wsa, o);
                    delete wsa;
                  }
              // update progress bar
#if enPB_ve
                  pb.increment(1);
                  pb.display();
#endif
                }
              });
        } // nThreads

        for (size_t j = 0; j < feasThreads; ++j)
          threadArray[j].join();
      }
    }
  }
#if enPB_ve
  pb.done(1);
#endif
}

std::vector<std::pair<std::string, double>>
converToScores(std::unordered_map<std::string, Diff> &tokenToDiff,
               bool normalize) {

  std::vector<std::pair<std::string, double>> scores;

  if (normalize) {
    for (auto &[var, diff] : varToDiff) {
      double score = 0.f;
      for (auto &[id, v] : diff._coverage) {
        //use a log function to normalize
        score += 1.f + log(v);
      }
      scores.emplace_back(var, score);
    }
  } else {
    for (auto &[var, diff] : varToDiff) {
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
//void dumpScore(std::unordered_map<std::string, Diff> &varToDiff, size_t stuckAt,
//               size_t cluster, bool normalize, bool consecutive, bool inAnt) {
//  auto scores = converToScores(varToDiff, normalize, inAnt);
//
//  std::ofstream out(std::string("rank_out_sa") + (inAnt ? "Ant" : "Con") +
//                    std::to_string(stuckAt) + (consecutive ? "Consec" : "") +
//                    (normalize ? "Nor" : "") + ".txt");
//
//  std::vector<double> elements;
//  for (auto &v_s : scores) {
//    elements.push_back(v_s.second);
//  }
//
//  auto ranges = clc::ve_cluster != 1
//                    ? kmeansElbow(elements, clc::ve_cluster, 0.000001, 1)
//                    : kmeansElbow(elements, 100, 0.01, 1);
//  std::map<size_t, std::vector<std::pair<std::string, double>>> buckets;
//  for (auto &v_s : scores) {
//    auto it =
//        std::find_if(ranges.begin(), ranges.end(),
//                     [&v_s](const std::pair<double, double> &e) {
//                       return v_s.second <= e.second && v_s.second >= e.first;
//                     });
//    messageErrorIf(it == ranges.end(), "Could not find range");
//    buckets[std::distance(ranges.begin(), it)].emplace_back(v_s.first,
//                                                            v_s.second);
//  }
//  for (auto &b : buckets) {
//    if (!normalize) {
//      //std::cout << "===================[" << b.first << "]====================" << "\n";
//    }
//    //out << "===================[" << b.first << "]====================" << "\n";
//    for (auto &v_s : b.second) {
//      if (!normalize) {
//        std::cout << v_s.first << "; " << (int)v_s.second << "\n";
//        out << v_s.first << "; " << (int)v_s.second << "\n";
//      } else {
//        out << v_s.first << "; " << std::fixed << std::setprecision(4)
//            << (double)v_s.second << "\n";
//      }
//    }
//  }
//
//  out.close();
//}
void dumpScore(std::unordered_map<std::string, Diff> &tokenToDiff,
               bool normalize) {

  auto scores = converToScores(tokenToDiff, normalize);

  std::ofstream out(std::string("rank_") + clc::ve_technique +
                    (normalize ? "_nor" : "") + ".csv");

  //prep for clustering
  std::vector<double> elements;
  for (auto &v_s : scores) {
    elements.push_back(v_s.second);
  }

  std::map<size_t, std::vector<std::pair<std::string, double>>> clusters_score;

  auto clusters_range =
      clc::ve_cluster != 1 ? kmeansElbow(elements, clc::ve_cluster, 0.000001, 1)
                           : kmeansElbow(elements, 100, 0.01, 1);

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
  for (auto &[id, scores] : clusters_score) {
    for (auto &[token, score] : scores) {
      if (!normalize) {
        out << token << "; " << (int)score << ";" << id << "\n";
      } else {
        out << token << "; " << std::fixed << std::setprecision(4)
            << (double)score << ";" << id "\n";
      }
    }
  }

  out.close();
}
