#include "Template.hh"
#include "ManualDefinition.hh"
#include "ProgressBar.hpp"
#include "bdtLimitsParser.hh"
#include "classes/atom/Atom.hh"
#include "metricParser.hh"
#include "metricParsingUtils.hh"
#include "minerUtils.hh"
#include "propositionParser.hh"
#include "templateParser.hh"

#include <algorithm>
#include <cassert>
#include <set>
#include <string>

#define enPB 1

namespace harm {

using namespace rapidxml;
ManualDefinition::ManualDefinition(std::string &configFile)
    : ContextMiner(configFile) {}

void ManualDefinition::mineContexts(Trace *trace,
                                    std::vector<Context*> &contexts) {

  std::vector<rapidxml::xml_node<> *> contextsTag;
  getNodesFromName(_configuration, "context", contextsTag);
  messageErrorIf(contextsTag.empty(), "No contexts defined");

  for (auto &contextTag : contextsTag) {
    auto contextName = getAttributeValue(contextTag, "name", "");
    auto language = getAttributeValue(contextTag, "language", "Spot");
    Context *context = new Context(contextName, language);

    // templates
    std::vector<rapidxml::xml_node<> *> templatesTag;
    getNodesFromName(contextTag, "template", templatesTag);
    for (auto &templateTag : templatesTag) {
      auto exp = getAttributeValue(templateTag, "exp", "");
      auto check = getAttributeValue(templateTag, "check", "0");
      auto bdtLimitsStr =
          getAttributeValue(templateTag, "bdtLimits", "3W,3D,3A,!O,N,0.1E,R");
      BDTLimits bdtLimits = hparser::parseLimits(bdtLimitsStr);
      //  debug
      // std::cout << "maxDepth:" << bdtLimits._maxDepth << "\n";
      // std::cout << "maxWidth:" << bdtLimits._maxWidth << "\n";
      // std::cout << "maxAll:" << bdtLimits._maxAll << "\n";
      // std::cout << "bdtRange:" << bdtLimits._bdtRange << "\n";
      // std::cout << "isRandomConstructed:" << bdtLimits._isRandomConstructed
      //          << "\n";
      // std::cout << "saveOffset:" << bdtLimits._saveOffset << "\n";
      // std::cout << "useNegatedProps:" << bdtLimits._useNegatedProps << "\n";
      context->_templates.push_back(
          hparser::parseTemplate(exp, trace, language, bdtLimits));
      messageErrorIf(check != "0" && check != "1",
                     "Unknown value for 'check' field");
      context->_templates.back()->_check = (check == "1" ? 1 : 0);
    }

    // sort
    std::vector<rapidxml::xml_node<> *> sortsTag;
    getNodesFromName(contextTag, "sort", sortsTag);
    for (auto &sortTag : sortsTag) {
      auto exp = getAttributeValue(sortTag, "exp", "0");
      auto name = getAttributeValue(sortTag, "name", "default");
      auto range = getAttributeValue(sortTag, "range", "[0,1]");

      context->_sort.push_back(hparser::parseMetric(name, exp, trace));
    }

    // filter
    std::vector<rapidxml::xml_node<> *> filtersTag;
    getNodesFromName(contextTag, "filter", filtersTag);
    for (auto &filterTag : filtersTag) {
      auto exp = getAttributeValue(filterTag, "exp", "0");
      auto name = getAttributeValue(filterTag, "name", "default");
      auto th = getAttributeValue(filterTag, "threshold", "0");
      context->_filter.emplace_back(hparser::parseMetric(name, exp, trace),
                                   std::stod(th));
    }

    // propositions
    std::vector<rapidxml::xml_node<> *> propsTag;
    getNodesFromName(contextTag, "prop", propsTag);
    for (auto &propTag : propsTag) {
      auto exp = getAttributeValue(propTag, "exp", "");
      auto locStr = getAttributeValue(propTag, "loc", "");
      harm::Location loc;
      if (locStr == "a") {
        loc = harm::Location::Ant;
      } else if (locStr == "c") {
        loc = harm::Location::Con;
      } else if (locStr == "ac") {
        loc = harm::Location::AntCon;
      } else {
        messageError("Unknown location for proposition " + exp);
      }
      context->_props.emplace_back(
          new CachedProposition(hparser::parseProposition(exp, trace)), loc);
    }

    // numerics for bdt
    std::vector<rapidxml::xml_node<> *> numsTag;
    getNodesFromName(contextTag, "numeric", numsTag);

    if (!numsTag.empty()) {
#if enPB
      progresscpp::ParallelProgressBar pb;
      pb.addInstance(0, "Elaborating numerics ("+contextName+")", numsTag.size(), 70);
#endif
      for (auto &numTag : numsTag) {
        auto exp = getAttributeValue(numTag, "exp", "");
        auto loc = getAttributeValue(numTag, "loc", "bdt");
        double clsEffort =
            std::stod(getAttributeValue(numTag, "clsEffort", "0.3"));
        // convert to proposition to avoid having multiple parsers for similar
        // things
        Proposition *np = hparser::parseProposition(exp, trace);
        CachedAllNumeric *nn;
        messageErrorIf(dynamic_cast<LogicToBool *>(np) == nullptr &&
                           dynamic_cast<NumericToBool *>(np) == nullptr,
                       "Exp " + exp + " is not of numeric or logic type");
        if (dynamic_cast<LogicToBool *>(np) != nullptr) {
          nn = new expression::CachedAllNumeric(
              &dynamic_cast<LogicToBool *>(np)->getItem(), clsEffort);
          dynamic_cast<LogicToBool *>(np)->popItem();
        } else if(dynamic_cast<NumericToBool *>(np) != nullptr) {
          nn = new expression::CachedAllNumeric(
              &dynamic_cast<NumericToBool *>(np)->getItem(), clsEffort);
          dynamic_cast<NumericToBool *>(np)->popItem();
        }else{
            messageError("Bad type in CachedAllNumeric");
        }

        if (loc == "c") {
          std::vector<size_t> ivs;
          for (size_t i = 0; i < trace->getLength(); i++) {
            ivs.push_back(i);
          }

          auto props = genPropsThroughClustering(ivs, nn, trace->getLength());
          for (auto p : props) {
            context->_props.emplace_back(p, Location::Con);
          }
          delete nn;
        } else if (loc == "a") {
          std::vector<size_t> ivs;
          for (size_t i = 0; i < trace->getLength(); i++) {
            ivs.push_back(i);
          }

          auto props = genPropsThroughClustering(ivs, nn, trace->getLength());
          for (auto p : props) {
            context->_props.emplace_back(p, Location::Ant);
          }
          delete nn;
        } else if (loc == "ac") {
          std::vector<size_t> ivs;
          for (size_t i = 0; i < trace->getLength(); i++) {
            ivs.push_back(i);
          }

          auto props = genPropsThroughClustering(ivs, nn, trace->getLength());
          for (auto p : props) {
            context->_props.emplace_back(p, Location::AntCon);
          }
          delete nn;
        } else if (loc == "bdt") {
          context->_numerics.push_back(nn);
        } else {
          messageError("Unsopported attribute '" + loc + "'");
        }

        delete np;

#if enPB
        pb.increment(0);
        pb.display();
#endif
      }
#if enPB
      pb.done(0);
#endif
    }
    contexts.push_back(context);
  }
}

} // namespace harm
