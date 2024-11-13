#include <algorithm>
#include <ctype.h>
#include <istream>
#include <iterator>
#include <stddef.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Assertion.hh"
#include "ClsOp.hh"
#include "ClusteringConfig.hh"
#include "Context.hh"
#include "DTLimits.hh"
#include "Location.hh"
#include "ManualDefinition.hh"
#include "Metric.hh"
#include "ProgressBar.hpp"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/NumericExpression.hh"
#include "formula/expression/TypeCast.hh"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "rapidxml.hh"
#include "temporalParsingUtils.hh"
#include "xmlUtils.hh"

namespace harm {

using namespace rapidxml;
using namespace expression;

ManualDefinition::ManualDefinition(std::string &configFile)
    : ContextMiner(configFile) {}

void addAssertionsFromFile(std::string assPath, const TracePtr &trace,
                           ContextPtr c) {

  std::fstream ass(assPath);
  std::string line = "";
  std::vector<std::string> assStrs;
  while (std::getline(ass, line)) {
    assStrs.push_back(line);
  }

  messageInfo("Number of external assertions: " +
              std::to_string(assStrs.size()) + "\n");

  std::vector<TemplateImplicationPtr> templs;
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Parsing assertions from file...", assStrs.size(),
                 70);

  //lower the number of threads to avoid wasting memory
  size_t prevl1Val = l1Constants::MAX_THREADS;
  l1Constants::MAX_THREADS = 1;

  for (size_t i = 0; i < assStrs.size(); i++) {
    pb.changeMessage(0, "Parsing assertions from file... " +
                            std::to_string(i + 1) + "/" +
                            std::to_string(assStrs.size()));
    TemplateImplicationPtr ti =
        hparser::parseTemplateImplication(assStrs[i], trace);
    if (!ti->assHoldsOnTrace(harm::Location::None)) {
      messageWarning("External assertion does not hold: '" +
                     ti->getAssertionStr(Language::SpotLTL) +
                     "', discarding it");
      continue;
    }

    //create an assertion by making a snapshot of a template
    AssertionPtr ass = generatePtr<Assertion>();
    fillAssertion(ass, ti, false);
    c->_assertions.push_back(ass);

    pb.increment(0);
    pb.display();
  }
  pb.done(0);

  //restore the previous number of threads
  l1Constants::MAX_THREADS = prevl1Val;
}

ClusteringConfig parseClusteringConfig(std::string config) {
  removeSpacesInPlace(config);
  ClusteringConfig res;
  auto options = parseCSV(config);
  std::unordered_set<std::string> seen;
  for (auto &option : options) {
    if (option == "K") {
      res._clusteringType.insert(ClsType::Kmeans);
      seen.insert("K");
    } else if (option == "K+") {
      res._clusteringType.insert(ClsType::Kmeans_UseAllIVsInDT);
      seen.insert("K+");
    } else if (option.size() > 3 &&
               option.substr(option.size() - 3) == "Max") {
      res._maxClusters =
          safeStoull(option.substr(0, option.size() - 3));
    } else if (option.size() > 4 &&
               option.substr(option.size() - 4) == "WCSS") {
      res._minWCSS = safeStod(option.substr(0, option.size() - 4));
    } else if (option == "><") {
      res._clsOps.insert(ClsOp::Range);
    } else if (option == ">=") {
      res._clsOps.insert(ClsOp::GE);
    } else if (option == "<=") {
      res._clsOps.insert(ClsOp::LE);
    } else if (option == "==") {
      res._clsOps.insert(ClsOp::E);
    } else if (option.size() > 1 && option.back() == 'E') {
      std::string constantStr = option.substr(0, option.size() - 1);
      //this is to handle the different formats of the constants
      if (isFloat(constantStr)) {
        res._excluded.insert(constantStr);
      } else if (isInteger(constantStr)) {
        res._excluded.insert(constantStr);
      } else {
        messageError("Invalid constant type '" + constantStr +
                     "' in clustering config option " + option);
      }
    } else {
      messageError("Unknown clustering option: " + option);
    }
  }

  messageErrorIf(seen.count("K") && seen.count("K+"),
                 "Cannot use both K and K+ in " + config);
  return res;
}

///used to parse the 'loc' attribute in a prop or numeric tag
struct ParsedDomain {
  ParsedDomain() = default;
  ParsedDomain(int id, bool dontExpand)
      : _id(id), _dontExpand(dontExpand) {}
  int _id;
  bool _dontExpand;
};

template <bool isNumericDomain>
std::vector<ParsedDomain> parseDomain(std::string loc) {
  std::vector<ParsedDomain> ret;
  removeSpacesInPlace(loc);

  auto options = parseCSV(loc);

  for (auto option : options) {
    if (option == "a") {
      ret.emplace_back((int)Location::Ant, false);
      continue;
    } else if (option == "c") {
      ret.emplace_back((int)Location::Con, false);
      continue;
    } else if (option == "ac") {
      ret.emplace_back((int)Location::AntCon, false);
      continue;
    } else if (option == "dt") {
      ret.emplace_back((int)Location::DecTree, false);
      continue;
    }
    if constexpr (isNumericDomain) {
      if (option.size() > 2 && option.front() == '[' &&
          option.back() == ']' &&
          isPositiveInteger(option.substr(1, option.size() - 2))) {
        //to be expanded ID
        uint64_t id = safeStoull(option.substr(1, option.size() - 2));
        messageErrorIf(id > INT_MAX, "Domain id too big, max is " +
                                         std::to_string(INT_MAX));
        ret.emplace_back((int)id, true);
        continue;
      } else if (option == "[dt]") {
        ret.emplace_back((int)Location::DecTree, true);
        continue;
      }
    }

    messageError(
        "Unknown option '" + option + "' in  loc '" + loc +
        "', available option are 'a' (antecedent), 'c' "
        "(consequent), "
        "'ac' "
        "both antecedent and consequent, 'dt' (decision tree) , "
        "'[dt]' (decision tree not expanded, only for numerics)");
  }
  return ret;
}

DTLimits parseLimits(std::string dtLimits) {
  removeSpacesInPlace(dtLimits);

  auto options = parseCSV(dtLimits);
  DTLimits limits;

  std::unordered_set<std::string> seen;

  for (auto option : options) {
    if (option == "S") {
      limits._isUnordered = false;
      seen.insert(option);
    } else if (option == "U") {
      limits._isUnordered = true;
      seen.insert(option);
    } else if (option == "!N") {
      limits._useNegatedProps = false;
      seen.insert("!N");
    } else if (option == "PF") {
      limits._requirePerfectFitness = true;
      seen.insert("PF");
    } else if (option == "O") {
      limits._saveOffset = true;
      seen.insert(option);
    } else if (option == "COV") {
      limits._heuristic = DTHeuristic::COVERAGE;
      seen.insert(option);
    } else if (option == "ENT") {
      limits._heuristic = DTHeuristic::ENTROPY;
      seen.insert(option);
    } else if (option == "DRP") {
      limits._dontReuseProp = true;
    } else if (option == "DRN") {
      limits._dontReuseNumeric = true;
    } else if (option == "DR") {
      limits._dontReuseProp = true;
      limits._dontReuseNumeric = true;
    } else if (option.size() > 1 &&
               option.substr(option.size() - 1) == "E") {
      limits._effort = safeStod(option.substr(0, option.size() - 1));
      seen.insert("E");
    } else if (option.size() > 1 &&
               option.substr(option.size() - 1) == "A") {
      messageErrorIf(
          !isPositiveInteger(option.substr(0, option.size() - 1)),
          "A option is not an unsigned positive number in " +
              dtLimits);
      limits._maxAll =
          safeStoull(option.substr(0, option.size() - 1));
      seen.insert("A");
    } else if (option.size() > 1 &&
               option.substr(option.size() - 1) == "D") {
      messageErrorIf(
          !isPositiveInteger(option.substr(0, option.size() - 1)),
          "D option is not an unsigned positive number in " +
              dtLimits);
      limits._maxDepth =
          safeStoull(option.substr(0, option.size() - 1));
      seen.insert("D");
    } else if (option.size() > 1 &&
               option.substr(option.size() - 1) == "W") {
      messageErrorIf(
          !isPositiveInteger(option.substr(0, option.size() - 1)),
          "W option is not an unsigned positive number in " +
              dtLimits);
      limits._maxWidth =
          safeStoull(option.substr(0, option.size() - 1));
      seen.insert("W");
    } else {
      messageError("Unknown dt limits option: " + option);
    }
  }

  if ((seen.count("W") xor seen.count("D")) && !seen.count("A")) {
    if (seen.count("D")) {
      limits._maxAll = limits._maxDepth;
      limits._maxWidth = limits._maxDepth;
    } else if (seen.count("W")) {
      limits._maxAll = limits._maxWidth;
      limits._maxDepth = limits._maxWidth;
    }
  }
  if ((!seen.count("W") && !seen.count("D")) && seen.count("A")) {
    limits._maxDepth = limits._maxAll;
    limits._maxWidth = limits._maxAll;
  }

  messageErrorIf(seen.count("COV") && seen.count("ENT"),
                 "Cannot use both COV and ENT in " + dtLimits);
  messageErrorIf(seen.count("U") && seen.count("S"),
                 "Cannot use both U and S in " + dtLimits);

  return limits;
}
void ManualDefinition::mineContexts(
    const TracePtr &trace, std::vector<ContextPtr> &contexts) {

  std::vector<rapidxml::xml_node<> *> contextsTag;
  getNodesFromName(_configuration, "context", contextsTag);
  messageErrorIf(contextsTag.empty(), "No contexts defined");

  for (auto &contextTag : contextsTag) {

    auto contextName = getAttributeValue(contextTag, "name", "");
    messageErrorIf(
        std::find_if(begin(contexts), end(contexts),
                     [&contextName](const ContextPtr &c) {
                       return c->_name == contextName;
                     }) != end(contexts),
        "Multiple contexts with the same name are not allowed");

    ContextPtr context = generatePtr<Context>(contextName);

    // templates
    std::vector<rapidxml::xml_node<> *> templatesTag;
    getNodesFromName(contextTag, "template", templatesTag);
    for (auto &templateTag : templatesTag) {
      auto exp = getAttributeValue(templateTag, "exp", "");
      auto check = getAttributeValue(templateTag, "check", "0");
      messageErrorIf(check != "0" && check != "1",
                     "Unknown value '" + check +
                         "' for 'check' field");

      auto dtLimitsStr = getAttributeValue(templateTag, "dtLimits",
                                           "3W,3D,3A,-0.1E,U");

      DTLimits dtLimits = parseLimits(dtLimitsStr);
      //  debug
      // std::cout << "maxDepth:" << dtLimits._maxDepth << "\n";
      // std::cout << "maxWidth:" << dtLimits._maxWidth << "\n";
      // std::cout << "maxAll:" << dtLimits._maxAll << "\n";
      // std::cout << "dtRange:" << dtLimits._dtRange << "\n";
      // std::cout << "isUnordered:" << dtLimits._isUnordered
      //          << "\n";
      // std::cout << "saveOffset:" << dtLimits._saveOffset << "\n";
      // std::cout << "useNegatedProps:" << dtLimits._useNegatedProps << "\n";
      //std::cout << "DTHeuristic:" << dtLimits._heuristic << "\n";
      TemplateImplicationPtr newTemplate =
          hparser::parseTemplateImplication(exp, trace, dtLimits);
      newTemplate->setCheck(check == "1" ? 1 : 0);

      if (newTemplate->isFullyInstantiated() &&
          !newTemplate->getCheck() &&
          newTemplate->assHoldsOnTrace(Location::AntCon)) {
        //assertioon
        AssertionPtr ass = generatePtr<Assertion>();
        fillAssertion(ass, newTemplate, 0);
        context->_assertions.push_back(ass);
      } else {
        context->_templates.push_back(newTemplate);
      }
    }

    // get sort metrics
    std::vector<rapidxml::xml_node<> *> sortsTag;
    getNodesFromName(contextTag, "sort", sortsTag);
    for (auto &sortTag : sortsTag) {
      auto exp = getAttributeValue(sortTag, "exp", "0");
      auto name = getAttributeValue(sortTag, "name", "default");
      auto range = getAttributeValue(sortTag, "range", "[0,1]");

      context->_sort.push_back(Metric::parseMetric(name, exp));
    }

    // get filter metrics
    std::vector<rapidxml::xml_node<> *> filtersTag;
    getNodesFromName(contextTag, "filter", filtersTag);
    for (auto &filterTag : filtersTag) {
      auto exp = getAttributeValue(filterTag, "exp", "0");
      auto name = getAttributeValue(filterTag, "name", "default");
      auto th = getAttributeValue(filterTag, "threshold", "0");
      context->_filter.emplace_back(Metric::parseMetric(name, exp),
                                    safeStod(th));
    }

    // get propositions
    std::vector<rapidxml::xml_node<> *> propsTag;
    getNodesFromName(contextTag, "prop", propsTag);
    for (auto &propTag : propsTag) {
      auto exp = getAttributeValue(propTag, "exp", "");
      messageErrorIf(exp == "", "exp attribute is empty");

      auto locStr = getAttributeValue(propTag, "loc", "");
      if (locStr == "") {
        messageWarning("loc is empty in exp '" + exp +
                       "', using 'a, c, ac, dt'");
        locStr = "a, c, ac, dt";
      }
      auto domains = parseDomain<0>(locStr);

      PropositionPtr p = hparser::parseProposition(exp, trace);
      p->enableCache();
      for (auto &[id, dontExpand] : domains) {
        //dontExpand is not used for non-numerics
        context->_domainIdToProps[id].push_back(p);
      }
    }

    // get numerics
    std::vector<rapidxml::xml_node<> *> numsTag;
    getNodesFromName(contextTag, "numeric", numsTag);

    if (!numsTag.empty()) {

      progresscpp::ParallelProgressBar pb;
      pb.addInstance(0, "Elaborating numerics (" + contextName + ")",
                     numsTag.size(), 70);
      std::unordered_map<std::string, std::vector<PropositionPtr>>
          expandedNumericStrToProps;
      for (auto &numTag : numsTag) {
        NumericExpressionPtr nn = nullptr;
        auto exp = getAttributeValue(numTag, "exp", "");
        messageErrorIf(exp == "",
                       "exp attribute is empty in numeric exp");
        auto idStr = getAttributeValue(numTag, "id", "::");
        messageErrorIf(idStr != "::" && !isPositiveInteger(idStr),
                       "id is not an unsigned number in "
                       "numeric '" +
                           exp + "'");
        auto locStr = getAttributeValue(numTag, "loc", "");
        if (locStr == "") {
          messageWarning("loc is empty in numeric exp '" + exp +
                         "', using 'a, c, ac, dt'\n\n");
          locStr = "a, c, ac, dt";
        }

        auto domains = parseDomain<1>(locStr);

        // use the proposition parser to parse the numeric expression, because we do not know the actual type of the numeric expression
        PropositionPtr np = hparser::parseProposition(exp, trace);

        messageErrorIf(
            std::dynamic_pointer_cast<IntToBool>(np) == nullptr &&
                std::dynamic_pointer_cast<FloatToBool>(np) == nullptr,
            "Exp '" + exp + "' is not of numeric type");

        // retrieve the numeric expression
        if (std::dynamic_pointer_cast<IntToBool>(np) != nullptr) {
          nn = generatePtr<expression::NumericExpression>(
              std::dynamic_pointer_cast<IntToBool>(np)->getItem());
        } else if (std::dynamic_pointer_cast<FloatToBool>(np) !=
                   nullptr) {
          nn = generatePtr<expression::NumericExpression>(
              std::dynamic_pointer_cast<FloatToBool>(np)->getItem());
        }

        ClusteringConfig cf = parseClusteringConfig(getAttributeValue(
            numTag, "clustering", "K,10Max,0.01WCSS,><,<=,>=,=="));
        nn->_clsConfig = cf;

        std::string nnStr = num2String(nn);

        //get the domains
        std::vector<int> expandedDomains;
        for (auto &[id, dontExpand] : domains) {
          if (dontExpand) {
            context->_domainIdToNumerics[id].push_back(nn);
          } else {
            expandedDomains.push_back(id);
          }
        }

        //non-expanded domains

        if (!expandedDomains.empty()) {
          //generate props though clustering using the whole trace
          std::vector<size_t> ivs;
          for (size_t i = 0; i < trace->getLength(); i++) {
            ivs.push_back(i);
          }
          auto props = genPropsThroughClustering(ivs, nn, false);

          //add the props to the context
          for (auto id : expandedDomains) {
            context->_domainIdToProps[id].insert(
                context->_domainIdToProps[id].end(), props.begin(),
                props.end());
          }
        }

        pb.increment(0);
        pb.display();
      }
      pb.done(0);
    }

    contexts.push_back(context);
  }

  //add external assertions to the 'external' context
  if (clc::includeAss != "") {
    auto pc = std::find_if(
        begin(contexts), end(contexts),
        [](const ContextPtr &c) { return c->_name == "external"; });
    ContextPtr external_context;
    if (pc == end(contexts)) {
      external_context = generatePtr<Context>("external");
      contexts.push_back(external_context);
    } else {
      messageInfo("Inserting external assertions into the 'external' "
                  "context");
      external_context = *pc;
    }
    addAssertionsFromFile(clc::includeAss, trace, external_context);
  }
}

} // namespace harm
