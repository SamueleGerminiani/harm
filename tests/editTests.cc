#include <algorithm>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <string>
#include <utility>
#include <vector>

#include "Assertion.hh"
#include "Edit.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "globals.hh"
#include "misc.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

TEST(EditTest, remove1) {

  clc::outputLang = Language::SVA;
  std::vector<VarDeclaration> vars;

  vars.emplace_back("v1", ExpType::Bool, 1);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  EditPtr removeRule =
      generatePtr<Edit>("always(@(P,a) |-> @(P,b))", "a==b");
  std::string assertionStr = "always(v1} |-> v1)";
  ASSERT_EQ(toBeRemoved(assertionStr,
                        std::vector<EditPtr>({removeRule}), trace),
            1);

  removeRule =
      generatePtr<Edit>("always(@(P,a) ##@(N) @(P,t)  |-> @(P,b))",
                        "a==b && (t==\"1\" || t==\"true\")");
  assertionStr = "always(v1 ##1 true |-> v1)";
  ASSERT_EQ(toBeRemoved(assertionStr,
                        std::vector<EditPtr>({removeRule}), trace),
            1);
  assertionStr = "always(v1 ##1 1 |-> v1)";
  ASSERT_EQ(toBeRemoved(assertionStr,
                        std::vector<EditPtr>({removeRule}), trace),
            1);

  removeRule = generatePtr<Edit>(
      "always(@(P,a) ##@(N) true |-> @(P,b))", "a==b");
  assertionStr = "always(v1 ##1 true |-> v1)";
  ASSERT_EQ(toBeRemoved(assertionStr,
                        std::vector<EditPtr>({removeRule}), trace),
            0);
  assertionStr = "always(v1 ##1 1 |-> v1)";
  ASSERT_EQ(toBeRemoved(assertionStr,
                        std::vector<EditPtr>({removeRule}), trace),
            0);
}

TEST(EditTest, rewrite1) {

  clc::outputLang = Language::SVA;
  std::vector<VarDeclaration> vars;

  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  EditPtr rewriteRule =
      generatePtr<Edit>("always(@(P,a) ##@(N,n) @(P,t)  |-> @(P,b))",
                        "always(@(a) |->  ##@(n) @(b))",
                        "(t==\"1\" || t==\"true\") && n==2");

  std::string assertionStr = "always(v1 ##2 true |-> v2)";
  TemplateImplicationPtr t =
      hparser::parseTemplateImplication(assertionStr, trace);
  AssertionPtr ass = generatePtr<Assertion>();
  fillAssertion(ass, t, 0);
  rewriteAssertion(ass, {rewriteRule}, trace);

  ASSERT_EQ(removeSpaces((const std::string)ass->toString()),
            "always(v1|->##2v2)");

  assertionStr = "always(v1 ##1 true |-> v2)";
  t = hparser::parseTemplateImplication(assertionStr, trace);
  ass = generatePtr<Assertion>();
  fillAssertion(ass, t, 0);
  ASSERT_EQ(rewriteAssertion(ass, {rewriteRule}, trace), 0);

  rewriteRule = generatePtr<Edit>(
      "always(@(P,a) ##@(N,n1) @(P,t)  |->  ##@(N,n2) @(P,b))",
      "always(@(a) |->  ##@(n1+n2) @(b))", "t==\"1\" || t==\"true\"");
  assertionStr = "always(v1 ##1 true |-> ##2 v2)";
  t = hparser::parseTemplateImplication(assertionStr, trace);
  ass = generatePtr<Assertion>();
  fillAssertion(ass, t, 0);
  rewriteAssertion(ass, {rewriteRule}, trace);
  ASSERT_EQ(removeSpaces((const std::string)ass->toString()),
            "always(v1|->##3v2)");
}

TEST(EditTest, removeWorkaroundPropLayerSVA) {

  clc::outputLang = Language::SVA;
  std::vector<VarDeclaration> vars;

  vars.emplace_back("vcs1vcs", ExpType::ULogic, 8);
  vars.emplace_back("vcs2vcs", ExpType::ULogic, 8);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);

  EditPtr removeRule = generatePtr<Edit>(
      "always(@(P,a) and @(P,b)|->@(P,c))", "a==c || b==c || a==b");
  std::string assertionStr =
      "always(vcs1vcs == 0 and vcs2vcs == 28 |-> vcs1vcs == 0)";

  ASSERT_EQ(toBeRemoved(assertionStr,
                        std::vector<EditPtr>({removeRule}), trace),
            1);
}
