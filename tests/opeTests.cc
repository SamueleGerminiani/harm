#include <algorithm>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits.h>
#include <stddef.h>
#include <string>
#include <vector>

#include "CSVtraceReader.hh"
#include "Context.hh"
#include "Float.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "Trinary.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "formula/expression/TypeCast.hh"
#include "formula/temporal/Sere.hh"
#include "globals.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

TEST(OpeTest, bitSelectorInt) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::SInt, 8);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto v1 = trace->getIntVariable("v1");
  v1->assign(0, safeStoull("0000011001", 2));

  auto res1 = hparser::parseIntExpression("v1[3:6]", trace);
  ASSERT_EQ(res1->evaluate(0), 3);

  auto res2 = hparser::parseIntExpression("v1[6:3]", trace);
  ASSERT_EQ(res2->evaluate(0), 3);
}

TEST(OpeTest, isMultipleMatch) {
  TraceReader *tr =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = tr->readTrace();

  auto t1 = hparser::parseTemplateImplication(
      "G({..##1..;P0[*1:2]} |-> {v1 == 1 && v2 == 2})", trace);
  ASSERT_TRUE(isMultipleMatch(t1->getTemplateFormula()));

  auto t2 = hparser::parseTemplateImplication(
      "G({..##1..;P0} |-> {v1 == 1 && v2 == 2})", trace);
  ASSERT_FALSE(isMultipleMatch(t2->getTemplateFormula()));

  auto t3 = hparser::parseTemplateImplication(
      "G({..##1..;first_match(P0[*1:2])} |-> {v1 == 1 && v2 == 2})",
      trace);
  ASSERT_FALSE(isMultipleMatch(t3->getTemplateFormula()));

  auto t4 = hparser::parseTemplateImplication(
      "G({..##1..;first_match(P0[*1]) ##[1:3] P0} |-> {v1 == 1 && v2 "
      "== 2})",
      trace);
  ASSERT_TRUE(isMultipleMatch(t4->getTemplateFormula()));

  auto t5 = hparser::parseTemplateImplication(
      "G({P0 ##[3:3] P1} |-> {v1 == 1 && v2 "
      "== 2})",
      trace);
  ASSERT_FALSE(isMultipleMatch(t5->getTemplateFormula()));

  delete tr;
}
