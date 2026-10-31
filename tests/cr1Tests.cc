// CR1 (miner-portfolio's correctness review, doc/plan/CR1_PLAN.md there): C7b-1, a `|=>` instance at the last
// cycle of a trace segment (the end of a VCD file, or a reset interval: Trace::getCuts) is pending, not judged on the
// next segment's first cycle; C7b-5, an expanded decision-tree template's contingency table (its AF row, read by the
// causality score) is the one of the same assertion parsed from its text.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <string>
#include <vector>

#include "DTOperator.hh"
#include "PointerUtils.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "Trinary.hh"
#include "VCDtraceReader.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Variable.hh"
#include "globals.hh"
#include "message.hh"
#include "expUtils/traceFiles.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

/// a trace of the bits in `rows` ("ab,ab,..."), cut after the given cycles
TracePtr cutTrace(const std::vector<std::string> &names, const std::string &rows,
                  const std::vector<size_t> &cuts) {
  std::vector<std::string> cycles;
  size_t start = 0, p;
  while ((p = rows.find(',', start)) != std::string::npos) {
    cycles.push_back(rows.substr(start, p - start));
    start = p + 1;
  }
  cycles.push_back(rows.substr(start));
  std::vector<VarDeclaration> decls;
  for (const auto &n : names) {
    decls.emplace_back(n, ExpType::Bool, 1);
  }
  TracePtr tr = generatePtr<Trace>(decls, cycles.size());
  for (size_t t = 0; t < cycles.size(); t++) {
    for (size_t k = 0; k < names.size(); k++) {
      tr->getBooleanVariable(names[k])->assign(t, cycles[t][k] == '1');
    }
  }
  tr->setCuts(cuts);
  return tr;
}

} // namespace

// C7b-1: a on the last cycle of the first segment (t3), b false on the next segment's first cycle (t4)
TEST(CR1Test, nextCycleImplicationDoesNotCrossACut) {
  hlog::ScopedThrowOnError throwOnError;
  TracePtr tr = cutTrace({"a", "b"}, "01,01,01,11,00,01,01,01", {3, 7});
  TemplateImplicationPtr ti = hparser::parseTemplateImplication("G({a} |=> b)", tr, DTLimits(), false);
  ASSERT_EQ(ti->evaluate(3), Trinary::U);  // pending at the segment's end
  ASSERT_TRUE(ti->assHoldsOnTrace(Location::AntCon));
  size_t ct[3][3] = {};
  ti->fillContingency(ct, false);
  // the instance at t3 is unknown: ant T, con U; it is neither a T nor an F instance of the consequent
  ASSERT_EQ(ct[0][1], 0u);
}

TEST(CR1Test, nextCycleImplicationWithoutACutStillFails) {
  hlog::ScopedThrowOnError throwOnError;
  TracePtr tr = cutTrace({"a", "b"}, "01,01,01,11,00,01,01,01", {7});
  TemplateImplicationPtr ti = hparser::parseTemplateImplication("G({a} |=> b)", tr, DTLimits(), false);
  ASSERT_EQ(ti->evaluate(3), Trinary::F);
  ASSERT_FALSE(ti->assHoldsOnTrace(Location::AntCon));
}

TEST(CR1Test, overlappingImplicationAtACutIsUnchanged) {
  hlog::ScopedThrowOnError throwOnError;
  TracePtr tr = cutTrace({"a", "b"}, "01,01,01,10,00,01,01,01", {3, 7});
  TemplateImplicationPtr ti = hparser::parseTemplateImplication("G({a} |-> b)", tr, DTLimits(), false);
  ASSERT_EQ(ti->evaluate(3), Trinary::F);
}

// C7b-5: the DT template expanded to {v2 ##1 v1} |=> con has the contingency table of the same text parsed
TEST(CR1Test, expandedTemplateContingencyMatchesItsText) {
  hlog::ScopedThrowOnError throwOnError;
  // v2 v1 con: an AF instance (antecedent false) whose consequent differs at t+1 and at t+depth+1
  TracePtr tr = cutTrace({"v1", "v2", "con"}, "010,100,001,000,011,100,000,001,010,001", {9});
  DTLimits limits;
  limits._maxDepth = 5;
  limits._maxAll = 5;
  TemplateImplicationPtr dt = hparser::parseTemplateImplication("G({..##1..} |=> con)", tr, limits);
  DTOperatorPtr dto = dt->getDT();
  dto->addItem(tr->getBooleanVariable("v1"), -1);
  dto->addItem(tr->getBooleanVariable("v2"), -1);
  ASSERT_EQ(dt->getAssertionStr(Language::SpotLTL), "G({v2 ##1 v1} |=> con)");
  TemplateImplicationPtr text = hparser::parseTemplateImplication("G({v2 ##1 v1} |=> con)", tr, DTLimits(), false);
  size_t a[3][3] = {}, b[3][3] = {};
  dt->fillContingency(a, false);
  text->fillContingency(b, false);
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      ASSERT_EQ(a[i][j], b[i][j]) << "row " << i << " column " << j;
    }
  }
}

// C7a-7: $past, $stable, $rose and $fell do not read across the start of a concatenated VCD file (each file is its own
// simulation; reset cuts, within a file, are read across as before)
TEST(CR1Test, svaFunctionsDoNotCrossAFileStart) {
  hlog::ScopedThrowOnError throwOnError;
  TracePtr tr = cutTrace({"a", "b"}, "00,10,10,10,10,00", {2, 5});  // file 1: t0..t2, file 2: t3..t5
  expression::traceFileStart = {0, 0, 0, 3, 3, 3};
  PropositionPtr past = hparser::parseProposition("$past(a)", tr);
  PropositionPtr stable = hparser::parseProposition("$stable(a)", tr);
  PropositionPtr rose = hparser::parseProposition("$rose(a)", tr);
  ASSERT_TRUE(past->evaluate(2));    // a@1, the same file
  ASSERT_FALSE(past->evaluate(3));   // t3 starts file 2: no a@2
  ASSERT_TRUE(past->evaluate(4));    // a@3
  ASSERT_FALSE(stable->evaluate(3)); // as at time 0
  ASSERT_FALSE(rose->evaluate(3));
  expression::traceFileStart.clear();
  ASSERT_TRUE(past->evaluate(3));    // without the table, as before
}

// C8b-1 (CR1's second pass): reading a one-file trace leaves no earlier trace's file starts behind
TEST(CR1Test, aOneFileTraceClearsTheFileStarts) {
  expression::traceFileStart = {0, 0, 3, 3};  // as a two-file trace read before would leave it
  VCDTraceReaderConfig cfg;
  cfg._clk = "clk";
  cfg._selectedScope = "tb";
  cfg._vcdRecursive = 0;
  TraceReader *reader = new VCDtraceReader("../tests/input/h38/bit_index.vcd", cfg);
  reader->readTrace();
  delete reader;
  ASSERT_TRUE(expression::traceFileStart.empty());
}
