#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <string>
#include <vector>

#include "Assertion.hh"
#include "CSVtraceReader.hh"
#include "ClsOp.hh"
#include "Context.hh"
#include "Edit.hh"
#include "Float.hh"
#include "TLMiner.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "Trinary.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/NumericExpression.hh"
#include "formula/atom/Variable.hh"
#include "formula/expression/SetMembership.hh"
#include "formula/expression/TypeCast.hh"
#include "formula/function/SVAfunction.hh"
#include "globals.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

TEST(DomainTest, expandedDomain) {

  clc::outputLang = Language::SpotLTL;
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto v1 = trace->getBooleanVariable("v1");
  auto v2 = trace->getBooleanVariable("v2");
  Context c;
  c._domainIdToProps[1].push_back(copy(v1));
  c._domainIdToProps[2].push_back(copy(v2));
  TemplateImplicationPtr t =
      hparser::parseTemplateImplication("G(P0(1) -> P1(2))", trace);
  c._templates.push_back(t);
  t->genPermutations(c._domainIdToProps, c._domainIdToNumerics);
  t->loadPerm(0);

  ASSERT_EQ(t->getNumberOfPermutations(), 1);
  ASSERT_EQ(t->getAssertionStr(Language::SpotLTL), "G(v1 -> v2)");
}

TEST(DomainTest, expandedDomainNonEnumerated) {
  clc::outputLang = Language::SpotLTL;

  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  auto v1 = trace->getBooleanVariable("v1");
  auto v2 = trace->getBooleanVariable("v2");
  auto v3 = trace->getBooleanVariable("v3");

  Context c;
  c._domainIdToProps[(int)Location::Ant].push_back(copy(v1));
  c._domainIdToProps[(int)Location::Con].push_back(copy(v2));
  c._domainIdToProps[1].push_back(copy(v3));

  TemplateImplicationPtr t = hparser::parseTemplateImplication(
      "G(P0 -> P1 && P2(1))", trace);
  c._templates.push_back(t);
  t->genPermutations(c._domainIdToProps, c._domainIdToNumerics);
  t->loadPerm(0);

  ASSERT_EQ(t->getNumberOfPermutations(), 1);
  ASSERT_EQ(t->getAssertionStr(Language::SpotLTL),
            "G(v1 -> {v2 && v3})");
}

// H41 (DD1 A7, the user 2026-11-04): a template's ! over a placeholder holding a comparison is printed with
// brackets, so the text re-parses to the mined property by C/SystemVerilog precedence (! binds tighter than
// ==). It printed !x == 3'b100, which is (!x) == 4, never true, where HARM had checked !(x == 4).
TEST(DomainTest, notOverComparisonPrintsBrackets) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("b", ExpType::Bool, 1);
  vars.emplace_back("x", ExpType::ULogic, 3);
  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  Context c;
  c._domainIdToProps[1].push_back(hparser::parseProposition("b", trace));
  c._domainIdToProps[2].push_back(hparser::parseProposition("x == 3'b100", trace));
  for (auto lang : {Language::SpotLTL, Language::SVA}) {
    clc::outputLang = lang;
    TemplateImplicationPtr t = hparser::parseTemplateImplication("G({P0(1)} |=> !P1(2) W P0(1))", trace);
    t->genPermutations(c._domainIdToProps, c._domainIdToNumerics);
    t->loadPerm(0);
    ASSERT_EQ(t->getNumberOfPermutations(), 1);
    std::string want = lang == Language::SVA ? "always (b |=> !(x == 3'b100) until b)" : "G({b} |=> !(x == 3'b100) W b)";
    ASSERT_EQ(t->getAssertionStr(lang), want);
    AssertionPtr ass = generatePtr<Assertion>();  // as the miner writes it (TLMiner, the dump)
    fillAssertion(ass, t, false);
    ASSERT_EQ(ass->toString(lang), want);
  }
  clc::outputLang = Language::SpotLTL;
  TemplateImplicationPtr t = hparser::parseTemplateImplication("G({P0(1)} |=> !P1(1) W P0(1))", trace);
  t->genPermutations(c._domainIdToProps, c._domainIdToNumerics);
  t->loadPerm(0);
  ASSERT_EQ(t->getAssertionStr(Language::SpotLTL), "G({b} |=> !b W b)");  // a bare signal: no brackets
}
