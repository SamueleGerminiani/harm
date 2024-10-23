#include <algorithm>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits.h>
#include <ostream>
#include <stddef.h>
#include <string>
#include <vector>

#include "CSVtraceReader.hh"
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
#include "formula/temporal/temporal.hh"
#include "globals.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

namespace harm {
class Context;
} // namespace harm

using namespace harm;
using namespace expression;

TEST(TemporalDepthTest, checkDepth) {
  clc::outputLang = Language::SpotLTL;

  TraceReader *tr =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = tr->readTrace();
  TemporalExpressionPtr t1 = hparser::parseTemporalExpression(
      "G{((v1 ##2 v2)[*3] ##1 v3) && (v1[*100])}|->v3", trace);
  auto ant1 = t1->getItems()[0]->getItems()[0];
  ASSERT_EQ(getTemporalDepth(ant1), 99);

  TemporalExpressionPtr t2 = hparser::parseTemporalExpression(
      "G{((v1 ##5 v2)[*30] ##1 v3) && (v1[->] ##1 v1)}|->v3", trace);
  auto ant2 = t2->getItems()[0]->getItems()[0];
  ASSERT_EQ(getTemporalDepth(ant2), -1);
  TemporalExpressionPtr t3 =
      hparser::parseTemporalExpression("G(v2 W v3 -> v1)", trace);
  auto ant3 = t3->getItems()[0]->getItems()[0];
  ASSERT_EQ(getTemporalDepth(ant3), -1);
  TemporalExpressionPtr t4 = hparser::parseTemporalExpression(
      "G(X{v1 : v2[*2:3] ##1 v3}->v3)", trace);
  auto ant4 = t4->getItems()[0]->getItems()[0];
  ASSERT_EQ(getTemporalDepth(ant4), 4);
  TemporalExpressionPtr t5 =
      hparser::parseTemporalExpression("G(v1->v3)", trace);
  auto ant5 = t5->getItems()[0]->getItems()[0];
  ASSERT_EQ(getTemporalDepth(ant5), 0);

  delete tr;
}
