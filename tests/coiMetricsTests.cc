// H6, acceptance tests A1 (leaf offsets) and A2 (COI rank metrics, D-014). Expected values are
// computed by hand; the cones come from the H4 fixtures 'multipath' and 'counter', whose cones were
// validated by simulation.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include "CoiInfo.hh"
#include "PointerUtils.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "message.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

TracePtr boolTrace(const std::vector<std::string> &names) {
  std::vector<VarDeclaration> decls;
  for (const auto &n : names) {
    decls.emplace_back(n, ExpType::Bool, 1);
  }
  return generatePtr<Trace>(decls, 4);
}

TemporalExpressionPtr parse(const std::string &f, const TracePtr &trace) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    return hparser::parseTemporalExpression(f, trace);
  } catch (const hlog::HarmError &e) {
    ADD_FAILURE() << "cannot parse '" << f << "': " << e.what();
    return nullptr;
  }
}

// "a@0 | b@1 || c@?": antecedent leaves, then consequent leaves ('?' = unknown offset)
std::string render(const std::vector<LeafOffset> &leaves) {
  std::string ant, con;
  for (const auto &l : leaves) {
    std::string s = prop2String(l.prop) + "@" +
                    (l.offset ? std::to_string(*l.offset) : std::string("?"));
    std::string &side = l.inAntecedent ? ant : con;
    side += (side.empty() ? "" : " | ") + s;
  }
  return ant + " || " + con;
}

CoiInfoPtr loadCoi(const std::string &fixture, const TracePtr &trace) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    return CoiInfo::load("../tests/input/coi/" + fixture + "/expected_coi.json",
                         trace);
  } catch (const hlog::HarmError &e) {
    ADD_FAILURE() << "cannot load coi.json of " << fixture << ": " << e.what();
    return nullptr;
  }
}

} // namespace

// ---------------------------------------------------------------- A1
TEST(CoiMetricsTest, leafOffsets) {
  TracePtr tr = boolTrace({"a", "b", "c", "d"});
  std::vector<std::pair<std::string, std::string>> cases = {
      {"G(a -> b)", "a@0 || b@0"},
      {"G(a -> X b)", "a@0 || b@1"},
      {"G(a -> X X b)", "a@0 || b@2"},
      {"G({a ##1 b} |-> c)", "a@0 | b@1 || c@1"},
      {"G({a ##1 b} |=> c)", "a@0 | b@1 || c@2"},
      {"G({a ##2 b} |-> c)", "a@0 | b@2 || c@2"},
      {"G({a ; b} |-> c)", "a@0 | b@1 || c@1"},
      {"G({a : b} |-> c)", "a@0 | b@0 || c@0"},
      {"G(a |-> ##3 b)", "a@0 || b@3"},
      {"G({a && b ##1 c} |-> X d)", "a && b@0 | c@1 || d@2"},
      {"G({a ##1 b ##1 c} |-> d)", "a@0 | b@1 | c@2 || d@2"},
      {"G(a -> b W c)", "a@0 || b@? | c@?"},
      {"G(a -> F b)", "a@0 || b@?"},
      {"G({a[*2]} |-> b)", "a@? || b@?"},
      {"G({a ##[1:2] b} |-> c)", "a@0 | b@? || c@?"},
      {"G(a)", "true@0 || a@0"},
  };
  for (const auto &[f, expected] : cases) {
    TemporalExpressionPtr te = parse(f, tr);
    if (te != nullptr) {
      EXPECT_EQ(render(leafOffsets(te)), expected) << f;
    }
  }
}

// ---------------------------------------------------------------- A2
// multipath cones: r1 <- a@1; r2 <- a@2, r1@1; rb <- b@1; y <- a@{0,2}, r1@1, r2@0;
// z <- b@1, rb@0; a, b: none. 'extra' is a trace variable unknown to coi.json.
TEST(CoiMetricsTest, metricsOnMultipath) {
  TracePtr tr = boolTrace({"a", "b", "y", "z", "r1", "r2", "rb", "extra"});
  CoiInfoPtr coi = loadCoi("multipath", tr);
  ASSERT_NE(coi, nullptr);
  // formula, coiFrac, coiDepthFit, coiUnknown
  std::vector<std::tuple<std::string, double, double, size_t>> cases = {
      {"G(a -> y)", 1, 1, 0},           // a reaches y at depth 0
      {"G(a -> X y)", 1, 0, 0},         // ... but not at depth 1
      {"G(a -> X X y)", 1, 1, 0},       // ... and at depth 2
      {"G(b -> y)", 0, 0, 0},           // b never reaches y
      {"G(b -> X z)", 1, 1, 0},         // b reaches z at depth 1
      {"G(b -> z)", 1, 0, 0},           // ... not at depth 0
      {"G({a ##1 b} |-> z)", 0.5, 0, 0},   // a out; b in, at 0 instead of 1
      {"G({b ##1 a} |-> z)", 0.5, 0.5, 0}, // b in at depth 1; a out
      {"G(r2 -> y)", 1, 1, 0},
      {"G(r1 -> X y)", 1, 1, 0},
      {"G(r1 -> y)", 1, 0, 0},
      {"G(a && b -> y)", 0, 0, 0},      // all variables of a leaf must be in the cone
      {"G(a -> y W z)", 1, 1, 0},       // unknown offsets: membership is enough
      {"G(b -> F y)", 0, 0, 0},
      {"G(y)", 1, 1, 0},                // no antecedent leaves with variables
      {"G(extra -> y)", 1, 1, 1},       // unknown signal: in the cone, counted
      {"G({a ##2 true} |-> y)", 1, 1, 0}, // y at offset 2, a at 0: depth 2
      {"G(r2 -> X r2)", 0, 0, 0},       // r2 is not in its own cone
      {"G({a ##1 a} |-> X y)", 1, 0.5, 0}, // depths 2 (fits) and 1 (does not)
  };
  for (const auto &[f, frac, fit, unknown] : cases) {
    TemporalExpressionPtr te = parse(f, tr);
    if (te == nullptr) {
      continue;
    }
    CoiMetrics m = computeCoiMetrics(te, *coi);
    EXPECT_DOUBLE_EQ(m.frac, frac) << f;
    EXPECT_DOUBLE_EQ(m.depthFit, fit) << f;
    EXPECT_EQ(m.unknown, unknown) << f;
  }
}

// counter cones (max_depth 3, all saturated): wrap <- cnt@{0..3}, en@{0..3}, rst@{1..3}
TEST(CoiMetricsTest, saturatedDepths) {
  std::vector<VarDeclaration> decls;
  decls.emplace_back("rst", ExpType::Bool, 1);
  decls.emplace_back("en", ExpType::Bool, 1);
  decls.emplace_back("wrap", ExpType::Bool, 1);
  decls.emplace_back("cnt", ExpType::ULogic, 4);
  TracePtr tr = generatePtr<Trace>(decls, 4);
  CoiInfoPtr coi = loadCoi("counter", tr);
  ASSERT_NE(coi, nullptr);
  std::vector<std::tuple<std::string, double, double>> cases = {
      {"G(rst -> wrap)", 1, 0},               // rst reaches wrap from depth 1 only
      {"G(rst -> X wrap)", 1, 1},
      {"G(rst -> X X X X wrap)", 1, 1},       // depth 4 > max_depth, saturated
      {"G(en -> X X X X X wrap)", 1, 1},
      {"G(cnt == 4'd9 -> wrap)", 1, 1},
  };
  for (const auto &[f, frac, fit] : cases) {
    TemporalExpressionPtr te = parse(f, tr);
    if (te == nullptr) {
      continue;
    }
    CoiMetrics m = computeCoiMetrics(te, *coi);
    EXPECT_DOUBLE_EQ(m.frac, frac) << f;
    EXPECT_DOUBLE_EQ(m.depthFit, fit) << f;
  }
}

// A3 (part): a name in coi.json that is not a trace variable is an error
TEST(CoiMetricsTest, namesMustBeTraceVariables) {
  TracePtr tr = boolTrace({"a", "b", "y", "z", "r1", "r2"}); // no 'rb'
  hlog::ScopedThrowOnError throwOnError;
  try {
    CoiInfo::load("../tests/input/coi/multipath/expected_coi.json", tr);
    FAIL() << "loading should fail";
  } catch (const hlog::HarmError &e) {
    EXPECT_NE(std::string(e.what()).find("rb"), std::string::npos) << e.what();
  }
}
