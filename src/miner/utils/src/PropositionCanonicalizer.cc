#include "PropositionCanonicalizer.hh"

#include <algorithm>
#include <map>
#include <set>

#include "Assertion.hh"
#include "expUtils/expUtils.hh"
#include "expUtils/smtEquivalence.hh"
#include "formula/temporal/BooleanLayer.hh"
#include "globals.hh"

namespace harm {
using namespace expression;

void PropositionCanonicalizer::build(
    const std::vector<AssertionPtr> &assertions) {
  _tokens.clear();
  _numberOfClasses = 0;
  _solverCalls = 0;

  // the propositions of the boolean-layer instances, grouped by their text
  std::map<std::string, std::vector<const Proposition *>> byText;
  std::map<std::string, PropositionPtr> representative;
  for (const auto &a : assertions) {
    traverse(a->_formula, [&](const TemporalExpressionPtr &current) {
      if (auto inst = std::dynamic_pointer_cast<BooleanLayerInst>(current)) {
        PropositionPtr p = inst->getProposition();
        std::string text = prop2String(p);
        byText[text].push_back(p.get());
        representative.emplace(text, p);
      }
      return false;
    });
  }

  // buckets of texts over the same variables (deterministic order: texts are sorted)
  std::map<std::vector<std::string>, std::vector<std::string>> buckets;
  for (const auto &[text, p] : representative) {
    std::vector<std::string> vars;
    for (const auto &[name, type] : getVars(p)) {
      vars.push_back(name);
    }
    std::sort(vars.begin(), vars.end());
    vars.erase(std::unique(vars.begin(), vars.end()), vars.end());
    buckets[vars].push_back(text);
  }

  // in each bucket, a text joins the first earlier class it is proved equivalent to
  std::map<std::string, size_t> textToClass;
  for (const auto &[vars, texts] : buckets) {
    std::vector<std::pair<size_t, PropositionPtr>> classes;
    for (const auto &text : texts) {
      PropositionPtr p = representative.at(text);
      size_t cls = (size_t)-1;
      for (const auto &[id, rep] : classes) {
        _solverCalls++;
        if (smt::checkEquivalence(rep, p, _timeoutMs) ==
            smt::Equivalence::Equivalent) {
          cls = id;
          break;
        }
      }
      if (cls == (size_t)-1) {
        cls = _numberOfClasses++;
        classes.emplace_back(cls, p);
      }
      textToClass[text] = cls;
    }
  }

  for (const auto &[text, props] : byText) {
    std::string token = "@C" + std::to_string(textToClass.at(text)) + "@";
    for (const auto *p : props) {
      _tokens[p] = token;
    }
  }
}

std::string
PropositionCanonicalizer::canonicalString(const AssertionPtr &a) const {
  return temp2StringSubst(a->_formula, Language::SpotLTL, _tokens);
}

} // namespace harm
