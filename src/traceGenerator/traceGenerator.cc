#include "CSVtraceReader.hh"
#include "DataType.hh"
#include "EdgeProposition.hh"
#include "commandLineParser.hh"
#include "csv.hpp"
#include "exp.hh"
#include "expUtils/expUtils.hh"
#include "expUtils/VarType.hh"
#include "globals.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "templateParser.hh"
#include "varDeclarationParser.hh"
#include "Template.hh"
#include "z3TestCaseGenerator.hh"
#include <fstream>
#include <spot/tl/parse.hh>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace harm;
using namespace expression;
using Path = std::vector<Automaton::Edge *>;

namespace clc {
std::string formula = "";
std::string dtOperator = "";
std::string dtFormula = "";
std::string varsDecl = "";
std::string outFile = "trace.csv";
bool dynamicShift = false;
bool constShift = false;
size_t length = 100;
size_t maxCore = 10;
} // namespace clc
void parseCommandLineArguments(int argc, char *args[]);
void getTokens(const spot::formula &f, std::vector<std::string> &tokens);
static std::vector<z3::TestCase>
genTraceForPath(const Path &path, size_t pathId, bool free = false);
std::vector<z3::TestCase> genTrace(const std::vector<Path> &paths,
                                   size_t length, bool cut);

std::vector<Path> getPaths(Automaton::Node *node) {

  //  debug
  //  std::cout << "id: " << node->_id << "\n";

  std::vector<Path> paths;
  Automaton::Edge *selfLoop = nullptr;
  for (auto &inEdge : node->_inEdges) {
    if (inEdge->_fromNode->_id == node->_id) {
      if (inEdge->_prop->toString() != "true") {
        selfLoop = inEdge;
      }
      continue;
    }
    std::vector<Path> ret = getPaths(inEdge->_fromNode);
    for (auto &path : ret) {
      path.push_back(inEdge);
      paths.push_back(path);
    }
  }

  if (node->_inEdges.size() - (selfLoop != nullptr ? 1 : 0) == 0) {
    // base case
    paths.emplace_back();
  }

  if (selfLoop != nullptr) {
    std::vector<Path> selfLoopPaths;
    for (auto &path : paths) {
      auto copy = path;
      copy.push_back(selfLoop);
      selfLoopPaths.push_back(copy);
    }
    paths.insert(paths.end(), selfLoopPaths.begin(), selfLoopPaths.end());
  }
  return paths;
}

Proposition *edgePropToProp(EdgeProposition *ep) {
  // And
  if (dynamic_cast<EdgeAnd *>(ep) != nullptr) {
    PropositionAnd *ret = new PropositionAnd();
    for (size_t i = 0; i < ep->getOperands().size(); i++) {
      ret->addItem(edgePropToProp(ep->getOperands()[i]));
    }
    return ret;
  }

  // Or
  if (dynamic_cast<EdgeOr *>(ep) != nullptr) {
    PropositionOr *ret = new PropositionOr();
    for (size_t i = 0; i < ep->getOperands().size(); i++) {
      ret->addItem(edgePropToProp(ep->getOperands()[i]));
    }
    return ret;
  }

  // Not
  if (dynamic_cast<EdgeNot *>(ep) != nullptr) {
    return makeExpression<PropositionNot>(edgePropToProp(ep->getOperands()[0]));
  }

  // Atomic proposition
  if (dynamic_cast<EdgePlaceholder *>(ep) != nullptr) {
    return *dynamic_cast<EdgePlaceholder *>(ep)->_toProp;
  }

  // Constants
  if (dynamic_cast<EdgeTrue *>(ep) != nullptr) {
    return new BooleanConstant(true, VarType::Bool, 1, 0);
  }

  if (dynamic_cast<EdgeNot *>(ep) != nullptr) {
    return new BooleanConstant(false, VarType::Bool, 1, 0);
  }

  messageError("Error in edgePropToProp");
  return nullptr;
}
Template *parseAssertion(
    Trace *trace,
    std::vector<std::tuple<Proposition *, size_t, size_t>> &bdtOperands) {
  size_t impl1Pos = clc::formula.find("|->", 0);
  size_t impl2Pos = clc::formula.find("|=>", 0);
  size_t impl3Pos = clc::formula.find("[]->", 0);
  size_t impl4Pos = clc::formula.find("[]=>", 0);
  if (impl1Pos != std::string::npos || impl2Pos != std::string::npos ||
      impl3Pos != std::string::npos || impl4Pos != std::string::npos) {
    clc::dynamicShift = 1;
  }
  impl2Pos = clc::formula.find("|=>", 0);
  impl4Pos = clc::formula.find("[]=>", 0);
  if (impl2Pos != std::string::npos || impl4Pos != std::string::npos) {
    clc::constShift = 1;
  }

  size_t bdtMaxDepth = 0;
  size_t bdtMaxWidth = 0;
  size_t bdtMaxOperands = 0;
  if (clc::dtOperator != "") {

    std::string operandsStr = clc::dtOperator;

    std::unordered_map<size_t, size_t> depthToWidth;
    // parse dtOperator
    for (size_t i = 0; i < operandsStr.size(); i++) {
      char c = operandsStr[i];
      if (c == '{') {
        i++;
        std::string propStr = "";
        while (i < operandsStr.size() && operandsStr[i] != ';') {
          propStr += operandsStr[i++];
        }

        i++;
        std::string depthStr = "";
        while (i < operandsStr.size() && operandsStr[i] != '}') {
          depthStr += operandsStr[i++];
        }
        bdtOperands.push_back(std::make_tuple(
            hparser::parseProposition(propStr, trace), std::stoul(depthStr),
            depthToWidth[std::stoul(depthStr)]));

        depthToWidth.at(std::stoul(depthStr))++;
        bdtMaxDepth = bdtMaxDepth < std::stoul(depthStr) ? std::stoul(depthStr)
                                                         : bdtMaxDepth;
        bdtMaxWidth = bdtMaxWidth < depthToWidth.at(std::stoul(depthStr))
                          ? depthToWidth.at(std::stoul(depthStr))
                          : bdtMaxWidth;
      }
    }
    messageErrorIf(bdtOperands.empty(), "Malformed dto");
    bdtMaxOperands = bdtOperands.size();
    bdtMaxDepth++;
  }
  BDTLimits limits(bdtMaxDepth, bdtMaxWidth, bdtMaxOperands, 0.1, true, true,
                   true);
  Template *ass =
      hparser::parseTemplate(clc::formula, trace, "Spot", limits);
  //   debug
  //   std::cout <<"maxDepth:" <<ass->getBDT()->getLimits()._maxDepth << "\n";
  //   std::cout <<"maxWidth:" <<ass->getBDT()->getLimits()._maxWidth << "\n";
  //   std::cout <<"maxAll:" <<ass->getBDT()->getLimits()._maxAll << "\n";
  //   std::cout <<"maxDepth:" <<bdtMaxDepth << "\n";
  //   std::cout <<"maxWidth:" <<bdtMaxWidth << "\n";
  //   std::cout <<"maxAll:" <<bdtMaxOperands << "\n";
  BDTOperator *bdt_template = ass->getBDT();
  for (auto &op : bdtOperands) {
    bdt_template->addItem(std::get<0>(op), std::get<1>(op));
  }
  return ass;
}
std::vector<z3::TestCase> getCounterExamples(
    Template *ass,
    std::vector<std::tuple<Proposition *, size_t, size_t>> &bdtOperands,
    bool cut) {

  std::vector<z3::TestCase> ret;
  // offset
  Automaton *autOff = ass->buildDiamondAutomaton(1);
  // debug
  //  std::cout << ass->printAutomaton(aut) << "\n";
  auto paths = getPaths(autOff->_accepting);
  //      debug
        std::cout << "N Counterexamples: " << paths.size() << "\n";
        for (auto p : paths) {
          for (auto e : p) {
            std::cout << e->_prop->toString() << " --> ";
          }
          std::cout << "\n";
        }

  // generate counterexamples

  BDTOperator *bdt_template = ass->getBDT();
  std::vector<std::tuple<Proposition *, size_t, size_t>> trueConstants;
  for (auto &p_d : bdtOperands) {
    trueConstants.emplace_back(new BooleanConstant(true, VarType::Bool, 1, 0),
                               std::get<1>(p_d), std::get<2>(p_d));
  }

  for (auto &p_d : trueConstants) {
    bdt_template->substitute(std::get<1>(p_d), std::get<2>(p_d),
                             std::get<0>(p_d));
  }

  for (size_t i = 1; i < trueConstants.size(); i++) {
    std::vector<std::vector<size_t>> c;
    comb(trueConstants.size(), i, c);
    for (auto &comb : c) {
      for (auto ce : comb) {
        bdt_template->substitute(std::get<1>(trueConstants[ce]),
                                 std::get<2>(trueConstants[ce]),
                                 std::get<0>(trueConstants[ce]));
      }

      //      debug
      //            std::cout << "---------->" << ass->getAssertion() << "\n";

      auto subTrace =
          genTrace(paths, clc::length / 2,
                   dynamic_cast<BDTNCReps *>(ass->getBDT()) != nullptr);
      ret.insert(ret.end(), subTrace.begin(), subTrace.end());
      if (cut) {
        ret.push_back(z3::TestCase({std::make_pair("@cut", z3::TypeValue())}));
      }

      for (auto ce : comb) {
        bdt_template->substitute(std::get<1>(trueConstants[ce]),
                                 std::get<2>(trueConstants[ce]),
                                 std::get<0>(trueConstants[ce]));
      }
    }
  }

  //  debug
  //  for (auto &e : z3trace) {
  //    std::cout << e << "\n";
  //  }

  delete autOff;
  return ret;
}
void dumpTrace(std::vector<z3::TestCase> &z3trace,
               std::map<std::string, std::string> &varToType, size_t fileID) {

  std::ofstream file("_" + std::to_string(fileID) + "_" +
                     clc::outFile);
  csv::DelimWriter<std::ofstream, ';', '"', 0> writer(file);

  // to keep track of the positions of the vars
  std::unordered_map<std::string, size_t> varToIndex;
  size_t index = 0;

  // csv header
  std::vector<std::string> header;
  for (auto &e : varToType) {
    varToIndex[e.first] = index++;
    header.push_back(e.second + " " + e.first);
  }
  writer << header;

  for (auto &tc : z3trace) {
    std::vector<std::string> row(varToType.size());
    // init row
    for (auto &e : row) {
      e = "0";
    }
    // fill with the vars' variables
    for (auto &v : tc) {
      row[varToIndex.at(v.first)] = valueToString(v);
    }
    writer << row;
  }

  file.close();
}

// WARNING: this function has an internal state!
static std::vector<z3::TestCase> genTraceForPath(const Path &path,
                                                 size_t pathId, bool free) {
  static std::map<std::pair<size_t, size_t>, bool> isExhausted;
  static std::map<std::pair<size_t, size_t>, std::vector<z3::TestCase>>
      alreadyGen;

  //debug
  //static std::map<std::pair<size_t, size_t>, size_t> ntests;

  if (free) {
    isExhausted.clear();
    alreadyGen.clear();
    //debug
   // ntests.clear();
    return std::vector<z3::TestCase>();
  }

  z3::Z3TestCaseGenerator tcg;
  std::vector<z3::TestCase> subTrace;

  for (size_t j = 0; j < path.size(); j++) {
    auto &edge = path[j];

    // avoid z3 errors
    if (edge->_prop->toString() == "!(true)" ||
        edge->_prop->toString() == "false")
      continue;

    if (isExhausted.count(std::make_pair(pathId, j)) == 0) {
      isExhausted[std::make_pair(pathId, j)] = false;
    }
    if (!isExhausted.at(std::make_pair(pathId, j)) &&
        alreadyGen[std::make_pair(pathId, j)].size() <
            clc::maxCore) {
      auto tcs = tcg.generateTestCase(*edgePropToProp(edge->_prop), 1,
                                      alreadyGen[std::make_pair(pathId, j)]);
      messageErrorIf(tcs.empty() &&
                         alreadyGen.at(std::make_pair(pathId, j)).empty(),
                     "Error in z3");
      if (!tcs.empty()) {
        subTrace.insert(subTrace.end(), tcs.begin(), tcs.end());
        auto &list = alreadyGen.at(std::make_pair(pathId, j));
        //        debug
        //        ntests[std::make_pair(pathId, j)]++;
        list.insert(list.end(), tcs.begin(), tcs.end());
      } else {
        // first time exhausted --> executed only once
        isExhausted.at(std::make_pair(pathId, j)) = true;
        auto &prev = alreadyGen.at(std::make_pair(pathId, j));
        subTrace.push_back(prev.back());
      }
    } else {
      auto &prev = alreadyGen.at(std::make_pair(pathId, j));

      //      debug
      //      std::cout << edge->_prop->toString() << ": ";
      //      std::cout << ntests.at(std::make_pair(pathId, j)) << "\n";
      size_t randNum = rand() % ((prev.size() - 1) - 0 + 1) + 0;
      subTrace.push_back(prev[randNum]);
    }
  }
  return subTrace;
}
std::vector<z3::TestCase> genTrace(const std::vector<Path> &paths,
                                   size_t length, bool cut) {
  if (paths.empty()) {
    return std::vector<z3::TestCase>();
  }

  size_t traceLength = 0;
  std::vector<z3::TestCase> trace;

  // free function state
  genTraceForPath(paths[0], 0, true);

  // generate the shortest trace
  for (size_t i = 0; i < paths.size(); i++) {
    auto subTrace = genTraceForPath(paths[i], i);
    trace.insert(trace.end(), subTrace.begin(), subTrace.end());
    if (cut) {
      trace.push_back(z3::TestCase({std::make_pair("@cut", z3::TypeValue())}));
    }
    traceLength += subTrace.size();
  }

  // extend the trace
  while (1) {
    for (size_t i = 0; i < paths.size(); i++) {
      if (traceLength >= length) {
        goto finish;
      }
      auto subTrace = genTraceForPath(paths[i], i);
      if (subTrace.empty()) {
        goto finish;
      }
      traceLength += subTrace.size();
      trace.insert(trace.end(), subTrace.begin(), subTrace.end());
      if (cut) {
        trace.push_back(
            z3::TestCase({std::make_pair("@cut", z3::TypeValue())}));
      }
    }
  }
finish:;

  return trace;
}

void parseCommandLineArguments(int argc, char *args[]) {
  auto result = parseTraceGenerator(argc, args);

  if (result.count("f")) {
    clc::formula = result["f"].as<std::string>();
    std::cout << "Formula: " << clc::formula << "\n";
  }
  if (result.count("v")) {
    clc::varsDecl = result["v"].as<std::string>();
    std::cout << "Variables: " << clc::varsDecl << "\n";
  }
  if (result.count("l")) {
    clc::length = result["l"].as<size_t>();
    std::cout << "Trace length: " << clc::length << "\n";
  }
  if (result.count("o")) {
    clc::outFile = result["o"].as<std::string>();
    std::cout << "Outfile: " << clc::outFile << "\n";
  }
  if (result.count("core")) {
    clc::maxCore = result["core"].as<size_t>();
    std::cout << "Core length: " << clc::maxCore << "\n";
  }
  if (result.count("dto")) {
    clc::dtOperator = result["dto"].as<std::string>();
    std::cout << "DTO: " << clc::dtOperator << "\n";
  }
}

int main(int arg, char *argv[]) {
  parseCommandLineArguments(arg, argv);

  // read variables
  std::vector<DataType> vars_dt;
  std::map<std::string, std::string> varToType;
  auto rows = csv::parse(clc::varsDecl);
  for (auto &r : rows.get_col_names()) {
    auto var = parseVariable(r);
    vars_dt.push_back(toDataType(var.first, var.second.first,
                                                 var.second.second));
    varToType[var.first] = var.second.first;
  }

  // allocate trace
  Trace *trace = new Trace(vars_dt, clc::length);

  std::vector<std::tuple<Proposition *, size_t, size_t>> bdtOperands;
  Template *ass = parseAssertion(trace, bdtOperands);

  // debug
  std::cout << ass->getColoredAssertion() << "\n";

  std::vector<z3::TestCase> z3trace;

  // get main trace
  Automaton *autOn = ass->buildDiamondAutomaton();
  auto paths = getPaths(autOn->_accepting);
  std::cout << "N Paths: " << paths.size() << "\n";
  for (auto p : paths) {
    for (auto e : p) {
      std::cout << e->_prop->toString() << " --> ";
    }
    std::cout << "\n";
  }

  z3trace = genTrace(paths, clc::length / 2,
                     dynamic_cast<BDTNCReps *>(ass->getBDT()) != nullptr);

  if (ass->getBDT() != nullptr && ass->getBDT()->getNChoices() > 1) {
    // get the counterexample trace for bdt mining
    auto ce = getCounterExamples(
        ass, bdtOperands, dynamic_cast<BDTNCReps *>(ass->getBDT()) != nullptr);
    // add ce to the main trace->t
    z3trace.insert(z3trace.end(), ce.begin(), ce.end());
  }

  if (dynamic_cast<BDTNCReps *>(ass->getBDT()) == nullptr) {
    z3trace.push_back(z3::TestCase({std::make_pair("@cut", z3::TypeValue())}));
  }

  //  debug
  //  for (auto i : z3trace) {
  //      std::cout << i << "\n";
  //  }
  // write to file
  size_t fileID = 0;
  std::vector<z3::TestCase> ft;
  for (auto &e : z3trace) {
    if (e.size() == 1 && e[0].first == "@cut") {
      if (!ft.empty()) {
        dumpTrace(ft, varToType, fileID++);
      }
      ft.clear();
    } else {
      ft.push_back(e);
    }
  }

  delete autOn;
  delete trace;
  delete ass;
  return 0;
}
