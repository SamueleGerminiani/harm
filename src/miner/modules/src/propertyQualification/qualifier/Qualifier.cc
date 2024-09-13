#include "Qualifier.hh"

#include "Assertion.hh"
#include "CSVtraceReader.hh"
#include "DTLimits.hh"
#include "ProgressBar.hpp"
#include "Template.hh"
#include "VCDtraceReader.hh"
#include "colors.hh"
#include "fort.hpp"
#include "globals.hh"
#include "message.hh"
#include "metricParser.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "templateParsingUtils.hh"
#include <algorithm>
#include <filesystem>
#include <iomanip>
#include <math.h>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "z3++.h"
#include <map>
#include <sstream>

#define enPB 1

using namespace expression;

namespace metrics {
using VarDeclaration = std::tuple<std::string, VarType, size_t>;
std::vector<VarDeclaration> _availableVars;

} // namespace metrics

namespace harm {

using namespace expression;

Qualifier::Qualifier() : PropertyQualifier() {

  //initialize the assertion's feature
  metrics::_availableVars.push_back(
      std::make_tuple("atct", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("afct", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("auct", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("atcf", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("afcf", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("aucf", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("atcu", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("afcu", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("aucu", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("traceLength", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("complexity", VarType::ULogic, 32));
  metrics::_availableVars.push_back(
      std::make_tuple("pRepetitions", VarType::ULogic, 32));

  loadParams();
}
void Qualifier::loadParams() {
  //load the legal parameters for the interactive ranking
  _functionParams[1] = FunctionParameter(2.9937, 95.114);
  _functionParams[2] = FunctionParameter(3.3212, 52.431);
  _functionParams[3] = FunctionParameter(3.4217, 35.841);
  _functionParams[4] = FunctionParameter(3.4191, 26.7);
  _functionParams[5] = FunctionParameter(3.4217, 21.274);
  _functionParams[6] = FunctionParameter(3.4163, 18.119);
  _functionParams[7] = FunctionParameter(3.416, 15.523);
  _functionParams[8] = FunctionParameter(3.4184, 13.609);
  _functionParams[9] = FunctionParameter(3.3554, 11.83);
  _functionParams[0] = FunctionParameter(3.3005, 10.623);
  _functionParams[12] = FunctionParameter(12.713, 96.676);
  _functionParams[13] = FunctionParameter(7.8153, 47.991);
  _functionParams[14] = FunctionParameter(6.7778, 35.081);
  _functionParams[15] = FunctionParameter(6.081, 26.593);
  _functionParams[16] = FunctionParameter(5.1989, 20.435);
  _functionParams[17] = FunctionParameter(4.9008, 17.058);
  _functionParams[18] = FunctionParameter(4.9476, 15.385);
  _functionParams[19] = FunctionParameter(4.7618, 13.595);
  _functionParams[10] = FunctionParameter(4.536, 11.827);
  _functionParams[23] = FunctionParameter(23.661, 102.23);
  _functionParams[24] = FunctionParameter(12.689, 48.285);
  _functionParams[25] = FunctionParameter(10.453, 35.329);
  _functionParams[26] = FunctionParameter(8.538, 26.254);
  _functionParams[27] = FunctionParameter(7.4046, 20.835);
  _functionParams[28] = FunctionParameter(6.9327, 17.772);
  _functionParams[29] = FunctionParameter(6.1655, 14.731);
  _functionParams[20] = FunctionParameter(6.1083, 13.581);
  _functionParams[34] = FunctionParameter(32.492, 98.036);
  _functionParams[35] = FunctionParameter(17.829, 49.125);
  _functionParams[36] = FunctionParameter(12.941, 32.887);
  _functionParams[37] = FunctionParameter(10.718, 25.172);
  _functionParams[38] = FunctionParameter(9.4645, 20.759);
  _functionParams[39] = FunctionParameter(8.3259, 17.132);
  _functionParams[30] = FunctionParameter(7.816, 15.239);
  _functionParams[45] = FunctionParameter(39.517, 91.622);
  _functionParams[46] = FunctionParameter(23.25, 50.304);
  _functionParams[47] = FunctionParameter(16.46, 33.35);
  _functionParams[48] = FunctionParameter(13.713, 26.097);
  _functionParams[49] = FunctionParameter(11.944, 21.547);
  _functionParams[40] = FunctionParameter(10.598, 18.145);
  _functionParams[56] = FunctionParameter(53.453, 100.59);
  _functionParams[57] = FunctionParameter(28.393, 50.449);
  _functionParams[58] = FunctionParameter(19.486, 32.838);
  _functionParams[59] = FunctionParameter(16.462, 26.324);
  _functionParams[50] = FunctionParameter(14.146, 21.588);
  _functionParams[67] = FunctionParameter(61.522, 97.435);
  _functionParams[68] = FunctionParameter(32.798, 49.49);
  _functionParams[69] = FunctionParameter(24.897, 36.015);
  _functionParams[60] = FunctionParameter(18.216, 25.131);
  _functionParams[78] = FunctionParameter(75.827, 103.61);
  _functionParams[79] = FunctionParameter(37.637, 49.357);
  _functionParams[70] = FunctionParameter(26.875, 33.86);
  _functionParams[89] = FunctionParameter(78.201, 94.068);
  _functionParams[80] = FunctionParameter(42.474, 49.253);
  _functionParams[90] = FunctionParameter(92.567, 99.39);

  _maxParamIndex = 90;
}

std::vector<Assertion *>
Qualifier::patchDiscardAssertions(std::vector<Assertion *> &inAssertions,
                                  Trace *trace) {
  messageInfo("Discarding trivial assertions...");
  std::vector<Assertion *> outAssertions;
  //remove x -> x assertions
  for (auto a : inAssertions) {
    if (a->_ct[1][0] == 0) {
      auto assTemp = hparser::parseTemplate(a->_toString.first, trace);
      auto antProps = assTemp->getLoadedPropositionsAnt();
      if (antProps.size() == 1) {
        auto conProps = assTemp->getLoadedPropositionsCon();
        if (conProps.size() == 1) {
          auto antPropStr = prop2String(*antProps.back());
          auto conPropStr = prop2String(*conProps.back());
          if (antPropStr == conPropStr) {
            delete assTemp;
            continue;
          }
        }
        delete assTemp;
      }
    }
    outAssertions.push_back(a);
  }
  return outAssertions;
}

std::vector<Assertion *>
Qualifier::extractUniqueAssertionsFast(std::vector<Assertion *> &inAssertions) {

  std::vector<Assertion *> outAssertions;
  std::unordered_set<Assertion *> assP;
  std::unordered_set<std::string> keys;
  //change data structer to allow constant access with id
  for (Assertion *ass : inAssertions) {
    assP.insert(ass);
  }
#if enPB
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Extracting unique assertions... 0 discarded",
                 inAssertions.size(), 70);
  size_t discarded = 0;
#endif

  //discard assertions deemed 'equivalent'
  for (auto &ass : assP) {
#if enPB
    pb.changeMessage(0, "Extracting unique assertions... " +
                            std::to_string(discarded) + " discarded");
    pb.increment(0);
    pb.display();
#endif

    //compress contingency table
    std::string cont =
        std::to_string(ass->_ct[0][0]) + std::to_string(ass->_ct[0][1]) +
        std::to_string(ass->_ct[0][2]) + std::to_string(ass->_ct[1][0]) +
        std::to_string(ass->_ct[1][1]) + std::to_string(ass->_ct[1][2]) +
        std::to_string(ass->_ct[2][0]) + std::to_string(ass->_ct[2][1]) +
        std::to_string(ass->_ct[2][2]);

    std::string assS = ass->_toString.first;
    assS.erase(remove_if(assS.begin(), assS.end(),
                         [](const char &c) {
                           return c == '\t' || c == '\n' || c == ' ' ||
                                  c == '(' || c == ')' || c == '{' ||
                                  c == '}' || c == '[' || c == ']';
                         }),
               assS.end());
    //combine the string rep of an assertion with its contincency table to generate a key
    std::string key = cont + assS;
    if (!keys.count(key)) {
      //add only if the key is unique
      outAssertions.push_back(ass);
      keys.insert(key);
    } else {
#if enPB
      discarded++;
#endif
    }
  }
#if enPB
  pb.done(0);
#endif
  return outAssertions;
}

std::vector<Assertion *>
Qualifier::extractUniqueAssertions(std::vector<Assertion *> &inAssertions) {

  // remove equivalent solutions, keep shortest
  std::vector<Assertion *> outAssertions;
  std::unordered_set<size_t> taken;
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Extracting unique assertions... 0 discarded",
                 inAssertions.size(), 70);
  size_t discarded = 0;

  for (size_t i = 0; i < inAssertions.size(); i++) {

    pb.changeMessage(0, "Extracting unique assertions... " +
                            std::to_string(discarded) + " discarded");
    pb.increment(0);
    pb.display();

    if (taken.count(i))
      continue;

    taken.insert(i);
    Assertion *a1 = inAssertions[i];
    Assertion *shortest = a1;
    for (size_t j = i + 1; j < inAssertions.size(); j++) {
      if (taken.count(j))
        continue;

      Assertion *a2 = inAssertions[j];
      if (*a1 == *a2) {
        //     debug
        //std::cout << a1->_toString.second << " == " << a2->_toString.second <<  "\n";
        shortest = a1->_toString.second.size() >= a2->_toString.second.size()
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

std::vector<Assertion *> Qualifier::qualify(Context &context, Trace *trace) {

  _traceLength = trace->getLength();
  std::vector<Assertion *> rankedAssertions = rankAssertions(context, trace);
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

double Qualifier::evaluate(Assertion &a, Metric &m) {

  messageErrorIf(m._vars.empty(), "No vars in metric ");
  for (auto &v : m._vars) {
    if (v == "atct") {
      m.assign(v, a._ct[0][0]);
    } else if (v == "atcf") {
      m.assign(v, a._ct[0][1]);
    } else if (v == "atcu") {
      m.assign(v, a._ct[0][2]);
    } else if (v == "afct") {
      m.assign(v, a._ct[1][0]);
    } else if (v == "afcf") {
      m.assign(v, a._ct[1][1]);
    } else if (v == "afcu") {
      m.assign(v, a._ct[1][2]);
    } else if (v == "auct") {
      m.assign(v, a._ct[2][0]);
    } else if (v == "aucf") {
      m.assign(v, a._ct[2][1]);
    } else if (v == "aucu") {
      m.assign(v, a._ct[2][2]);
    } else if (v == "traceLength") {
      m.assign(v, _traceLength);
    } else if (v == "complexity") {
      m.assign(v, a._complexity);
    } else if (v == "pRepetitions") {
      m.assign(v, a._pRepetitions);
    } else {
      messageError("Unknown metric variable name");
    }
  }
  return m.evaluate();
}
double Qualifier::scoreFunction(double x, FunctionParameter &fp) {
  // 1/(1 + e^(5 - 10x))^2
  return 1 / pow(1 + exp(fp._z - fp._k * x), 2);
}

Trace *Qualifier::parseFaultyTrace(const std::string &ftStr) {
  TraceReader *tr;
  if (clc::parserType == "vcd") {
    messageErrorIf(!std::filesystem::exists(ftStr),
                   "Can not find '" + ftStr + "'");
    tr = new VCDtraceReader(ftStr, clc::clk);
    Trace *t = tr->readTrace();
    delete tr;
    return t;
  } else if (clc::parserType == "csv") {
    messageErrorIf(!std::filesystem::exists(ftStr),
                   "Can not find '" + ftStr + "'");
    tr = new CSVtraceReader(ftStr);
    Trace *t = tr->readTrace();
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

  // for each fault f, get the list of assertion-IDs covering f

  // init optimizer
  z3::context c;
  z3::optimize opt(c);
  z3::params p(c);
  opt.set(p);

  // for each assertion i, create a new integer variable x_i having a value in
  // {1, 0}. If x_i is 1, then the assertion i is taken, otherwise it is
  // discarded.
  std::map<int, z3::expr> assertId2var;
  for (auto ass_f : _aToF) {
    // make the x_i variable
    std::stringstream x_name;
    x_name << "x_" << ass_f.first;
    z3::expr var = c.int_const(x_name.str().c_str());
    // add the constraint x_i in {1, 0}
    opt.add(var >= 0 && var <= 1);
    // map the assertion ith to the x_i variable
    assertId2var.insert({ass_f.first, var});
  }

  // for each fault f, add the constraint x_i + x_j + ... + x_z >= 1 to MILP,
  // where the variable x_i, x_j ..., x_z represent the assertions
  // i, j, ..., z covering f.
  for (auto &kv : _fToA) {
    // get the list of assertIDs covering f
    std::vector<size_t> &assertIDs = kv.second;

    // create the expression x_i + x_j + ... + x_z
    z3::expr_vector operands(c);
    for (int assertID : assertIDs)
      operands.push_back(assertId2var.at(assertID));

    // make x_i + x_j + ... + x_z be >= 1, namely at least an assertion
    // must be taken to cover the fault f
    opt.add((z3::sum(operands) >= 1));
  }

  // create the goal formula to be minimized : x_0 + x_1 + ... + x_n
  z3::expr_vector goal(c);
  for (auto &kv : assertId2var)
    goal.push_back(kv.second);

  // perform the minimization
  messageInfo("Running z3...");
  opt.minimize(z3::sum(goal));

  messageErrorIf(z3::sat != opt.check(), "Something went wrong...");

  z3::model model = opt.get_model();

  for (auto &id_var : assertId2var) {
    z3::func_decl dec = id_var.second.decl();
    unsigned int x_i_value = model.get_const_interp(dec).get_numeral_uint();
    if (x_i_value == 1)
      ret.push_back(id_var.first);
  }

  return ret;
}
void Qualifier::sortAssertionsWithMetrics(std::vector<Metric *> &metrics,
                                          std::vector<Assertion *> &assertions,
                                          size_t currParamIndex) {
  if (metrics.empty()) {
    //nothing to do
    return;
  }

  if (!_functionParams.count(currParamIndex)) {
    currParamIndex = _maxParamIndex;
  }

  // gather max value for all metrics (needed to normalize)
  std::unordered_map<std::string, double> mToMaxValue =
      getMaxValuesForSortMetrics(metrics, assertions);

  for (auto &a : assertions) {
    double score = 1;
    for (auto &m : metrics) {
      double r = scoreFunction(evaluate(*a, *m) / mToMaxValue.at(m->_name),
                               _functionParams[currParamIndex]);
      score *= r;
    }
    a->_finalScore = score;
  }

  std::sort(assertions.begin(), assertions.end(),
            [](Assertion *left, Assertion *right) {
              return left->_finalScore > right->_finalScore;
            });
}

void Qualifier::filterAssertionsWithMetrics(
    std::vector<Assertion *> &assertions,
    std::vector<std::pair<Metric *, double>> &metrics) {

  //need this to normalize the values
  std::unordered_map<std::string, double> mToMaxValue =
      getMaxValuesForFilterMetrics(metrics, assertions);

  // apply filtering metrics, mark as 'deleted' (nullptr) all assertions that evaluates under the threshold
  size_t filtered = 0;
  for (auto &a : assertions) {
    for (auto &m : metrics) {
      if (clc::dontNormalize
              ? evaluate(*a, *m.first) < m.second
              : evaluate(*a, *m.first) / mToMaxValue.at(m.first->_name) <
                    m.second) {
        a = nullptr;
        filtered++;
        break;
      }
    }
  }

  //actually remove the assertion from the container
  assertions.erase(remove_if(assertions.begin(), assertions.end(),
                             [](Assertion *a) { return a == nullptr; }),
                   assertions.end());

  messageInfo("Metrics filtered " + std::to_string(filtered) + " assertions");
}

void Qualifier::printAssertions(Context &context,
                                std::vector<Assertion *> &assertions,
                                Trace *trace) {

  size_t currParamIndex = 19;
  while (1) {
    sortAssertionsWithMetrics(context._sort, assertions, currParamIndex);
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
              << std::string("Assertion ") + "(Context : " + context._name + ")"
              << "final";
        for (auto m : context._sort) {
          table << m->_name;
        }
        table << fort::endr;
      }

      //get the assertion being printed
      Assertion *ass = assertions[i];
      std::vector<std::string> line;
      std::string ass_colored = "";
      std::string ass_black = "";
      //print the assertions according to the selected output language
      if (clc::outputLang == "Spot") {
        ass_colored = ass->_toString.second;
        ass_black = ass->_toString.first;
      } else if (clc::outputLang == "SVA") {
        Hstring svaFormula = hparser::spotToSVA(ass->_toString.first, trace);
        ass_black = svaFormula.toString(1);
        ass_colored = svaFormula.toColoredString(1);
      }
      line.push_back(std::to_string(i));
      line.push_back(ass_colored);
      line.push_back(to_string_with_precision(ass->_finalScore, 2));
      for (auto &m : context._sort) {
        line.push_back(to_string_with_precision(
            evaluate(*ass, *m) / mToMaxValue.at(m->_name), 2));
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
    std::cin >> currParamIndex;
    if ((size_t)(-1) == currParamIndex) {
      //exit interactive mode
      break;
    }
  }
}

void Qualifier::fbqUsingFaultyTraces(std::vector<Assertion *> &selected,
                                     Trace *originalTrace) {

  progresscpp::ParallelProgressBar progressBarPS;
  progressBarPS.addInstance(0, "Preparing fault-based qualification...",
                            selected.size(), 70);
  progressBarPS.display();
  std::vector<Template *> noCacheTemplates;
  for (Assertion *a : selected) {
    noCacheTemplates.push_back(hparser::parseTemplate(
        a->_toString.first, originalTrace, "Spot", harm::DTLimits(), 0));
    noCacheTemplates.back()->dontUseCachedProps();
    progressBarPS.increment(0);
    progressBarPS.display();
  }

  progressBarPS.done(0);

  //silence warnings and infos (to silence the traceReader)
  clc::isilent = 1;
  clc::wsilent = 1;
#if enPB
  progresscpp::ParallelProgressBar progressBar;
  progressBar.addInstance(
      0, "Fault coverage 0/" + std::to_string(clc::faultyTraceFiles.size()),
      selected.size() * clc::faultyTraceFiles.size(), 70);
  progressBar.display();
#endif

  for (size_t j = 0; j < clc::faultyTraceFiles.size(); j++) {
#if enPB
    progressBar.changeMessage(
        0, "Fault coverage " +
               (std::to_string(_fToA.size()) + "/" +
                std::to_string(clc::faultyTraceFiles.size())) +
               " (" +
               to_string_with_precision((_fToA.size() / (double)j) * 100.f, 2) +
               "%)" + " (Elaborating " + clc::faultyTraceFiles[j] + " [" +
               std::to_string(j + 1) + "])");
#endif
    auto ft = parseFaultyTrace(clc::faultyTraceFiles[j]);
    for (size_t i = 0; i < noCacheTemplates.size(); i++) {
      auto &a = noCacheTemplates[i];
      //new assertion with faulty trace
      Template *fAss = new Template(*a);
      fAss->changeTrace(ft);
      //exploit l1 parallelism
      //      fAss->setL1Threads((l1Constants::MAX_THREADS + 1) / 2);
      if (!fAss->assHoldsOnTrace(Location::AntCon)) {
        // new fault covered
        _aToF[i].push_back(j);
        _fToA[j].push_back(i);
        if (!clc::findMinSubset) {
          //stop search for this fault if do not want the optimal covering set
#if enPB
          progressBar.increment(0, noCacheTemplates.size() - i);
          progressBar.display();
#endif
          delete fAss;
          break;
        }
      }
      delete fAss;
#if enPB
      progressBar.increment(0);
      progressBar.display();
#endif
    }
    delete ft;
  }

  // print last
#if enPB
  progressBar.changeMessage(
      0, "Fault coverage " +
             (std::to_string(_fToA.size()) + "/" +
              std::to_string(clc::faultyTraceFiles.size())) +
             " (Elaborating " + clc::faultyTraceFiles.back() + " [" +
             std::to_string(clc::faultyTraceFiles.size()) + "])");
#endif

#if enPB
  progressBar.done(0);
#endif
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
  for (Template *t : noCacheTemplates) {
    delete t;
  }
}
std::vector<Assertion *>
sampleAssertionsByConDiversity(std::vector<Assertion *> selected, size_t n) {

  std::vector<Assertion *> sampled;
  //we want to keep the relative order of assertions
  std::map<size_t, std::vector<Assertion *>> conToAss;
  std::unordered_map<std::string, size_t> hashToId;
  size_t id = 0;
  for (auto a : selected) {
    std::string impl = patternExists(a->_toString.first, "->") ? "->" : "=>";
    std::string hash = selectStringAfter(a->_toString.first, impl);
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

void Qualifier::faultBasedQualification(std::vector<Assertion *> selected,
                                        Trace *trace) {

  size_t nFaultsftm = 0;
  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(selected), std::end(selected), rng);

  _aToF.clear();
  _fToA.clear();
  _fToVar.clear();

  fbqUsingFaultyTraces(selected, trace);
  hs::nFaults = clc::faultyTraceFiles.size();
  std::stringstream ss;

  //gather info on the coverage

  ss << "Coverage: "
     << ((double)_fToA.size() / (double)clc::faultyTraceFiles.size()) * 100
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
         << "\t" << selected[a]->_toString.second << "\n";
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
void Qualifier::dumpAssToFile(Context &context, Trace *trace,
                              std::vector<Assertion *> &assertions) {
#if enPB
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Dumping assertions...", assertions.size(), 70);
#endif

  messageErrorIf(!std::filesystem::exists(clc::dumpPath),
                 "Can not find directory '" + clc::dumpPath + "'");
  std::ofstream assFile(clc::dumpPath + "/" + context._name + "_ass.txt");
  for (auto &a : assertions) {

    if (clc::outputLang == "Spot") {
      assFile << a->_toString.first << "\n";
    } else if (clc::outputLang == "SVA") {
      Hstring svaFormula = hparser::spotToSVA(a->_toString.first, trace);
      assFile << svaFormula.toString(1) << "\n";
    }
#if enPB
    pb.increment(0);
    pb.display();
#endif
  }

  //dump fault coverage
  if (!clc::faultyTraceFiles.empty()) {

    std::ofstream fc_assFile(clc::dumpPath + "/" + context._name +
                             "_faultCov.txt");

    for (auto a : _coverageSet) {
      fc_assFile << assertions[a]->_toString.first << "\n";
    }
    fc_assFile.close();
  }

  assFile.close();
#if enPB
  pb.done(0);
#endif
}
std::vector<Assertion *> Qualifier::rankAssertions(Context &context,
                                                   Trace *trace) {
  if (context._assertions.empty()) {
    messageWarning("Could not mine any assertions for context '" +
                   context._name + "'");
    return std::vector<Assertion *>();
  }
  std::vector<Assertion *> assertions;
  messageInfo("Qualifying " + std::to_string(context._assertions.size()) +
              " assertions");

  assertions = context._assertions;

  assertions = patchDiscardAssertions(assertions, trace);

  //remove redundant assertios
  //FIXME: do we still need the slow version?
  //  if (assertions.size() > 10000) {
  //    //less precise but faster
  assertions = extractUniqueAssertionsFast(assertions);
  //  } else {
  //    assertions = extractUniqueAssertions(assertions);
  //  }

  //filter according to filtering metrics
  filterAssertionsWithMetrics(assertions, context._filter);

  //sort according to the final score
  sortAssertionsWithMetrics(context._sort, assertions);

  if (assertions.size() > clc::maxAss) {
    messageInfo("Keeping only the top " + std::to_string(clc::maxAss) +
                " assertions");
    if (clc::sampleByCon) {
      assertions = sampleAssertionsByConDiversity(assertions, clc::maxAss);
    } else {
      assertions.erase(assertions.begin() + clc::maxAss, assertions.end());
    }
  }

  return assertions;
}

std::unordered_map<std::string, double>
Qualifier::getMaxValuesForSortMetrics(std::vector<Metric *> &metrics,
                                      std::vector<Assertion *> &assertions) {

  std::unordered_map<std::string, double> mToMaxValue;
  for (auto &m : metrics) {
    double max = 0;
    for (auto &a : assertions) {
      double eval = evaluate(*a, *m);
      max = eval > max ? eval : max;
    }
    mToMaxValue[m->_name] = max;
  }
  return mToMaxValue;
}
std::unordered_map<std::string, double> Qualifier::getMaxValuesForFilterMetrics(
    std::vector<std::pair<Metric *, double>> &metrics,
    std::vector<Assertion *> &assertions) {

  std::unordered_map<std::string, double> mToMaxValue;
  for (auto &[m, th] : metrics) {
    double max = 0;
    for (auto &a : assertions) {
      double eval = evaluate(*a, *m);
      max = eval > max ? eval : max;
    }
    mToMaxValue[m->_name] = max;
  }
  return mToMaxValue;
}

} // namespace harm
