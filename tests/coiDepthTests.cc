// H8, acceptance test A1: the decision-tree index -> cycle offset table (D-007), the depth rule of
// the filter (D-020), and the offsets of '->' with a multi-cycle antecedent (H8 finding F6).
// Expected values are written by hand from the semantics: with '|->'/'|=>' the consequent starts
// at the end of the antecedent; with '->' it starts with the antecedent (checked by mining on a
// trace, H8_PLAN F6). The cones come from the H4 fixtures 'multipath' and 'counter'.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include "CoiInfo.hh"
#include "DTLimits.hh"
#include "DTOperator.hh"
#include "PointerUtils.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "message.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {
using D = std::optional<int>;
const D U = std::nullopt; // offset not fixed

TracePtr boolTrace(const std::vector<std::string> &names) {
  std::vector<VarDeclaration> decls;
  for (const auto &n : names) {
    decls.emplace_back(n, ExpType::Bool, 1);
  }
  return generatePtr<Trace>(decls, 4);
}

std::string show(const std::vector<std::vector<D>> &t) {
  std::string s;
  for (const auto &row : t) {
    s += "[";
    for (size_t i = 0; i < row.size(); i++) {
      s += (i ? "," : "") + (row[i] ? std::to_string(*row[i]) : std::string("?"));
    }
    s += "]";
  }
  return s;
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

// ---------------------------------------------------------------- D-007
TEST(CoiDepthTest, dtIndexDistances) {
  TracePtr tr = boolTrace({"v1", "v2", "v4", "con"});
  // template, max depth (D), expected distance from each index to each consequent leaf
  std::vector<std::tuple<std::string, int, std::vector<std::vector<D>>>> cases = {
      // |->: index 0 is the last antecedent cycle, which the consequent overlaps
      {"G({..##1..} |-> con)", 3, {{0}, {1}, {2}}},
      // |=>: the consequent starts one cycle after the antecedent
      {"G({..##1..} |=> con)", 3, {{1}, {2}, {3}}},
      {"G({..##1..} |-> X con)", 3, {{1}, {2}, {3}}},
      // two consequent leaves
      {"G({..##1..} |-> {con ##1 v4})", 3, {{0, 1}, {1, 2}, {2, 3}}},
      // step 2
      {"G({..##2..} |-> con)", 3, {{0}, {2}, {4}}},
      // ->: the consequent starts with the antecedent, which grows to the right
      {"G({..##1..} -> X con)", 3, {{1}, {0}, {-1}}},
      // ..#1&..: like ..##1.., several propositions per index
      {"G({..#1&..} |-> con)", 3, {{0}, {1}, {2}}},
      // ..&&..: a single index
      {"G({..&&..} |-> X con)", 1, {{1}}},
      {"G({..&&.. && v4} |-> con)", 1, {{0}}},
      // other events around the operator
      {"G({..##1..;v4} |-> con)", 3, {{1}, {2}, {3}}},
      {"G({v4;..##1..} -> X con)", 3, {{0}, {-1}, {-2}}},
      // offsets that are not fixed: cone membership only (D-014, D-020)
      {"G({..##1..} |-> F con)", 3, {{U}, {U}, {U}}},
  };
  for (const auto &[f, depth, want] : cases) {
    hlog::ScopedThrowOnError throwOnError;
    DTLimits limits;
    limits._maxDepth = depth;
    limits._maxAll = 5;
    limits._maxWidth = 5;
    try {
      TemplateImplicationPtr t = hparser::parseTemplateImplication(f, tr, limits);
      EXPECT_EQ(show(dtIndexDistances(t)), show(want)) << f;
    } catch (const hlog::HarmError &e) {
      ADD_FAILURE() << f << ": " << e.what();
    }
  }
}

// the index an item takes when inserted with depth -1 (ordered operators)
TEST(CoiDepthTest, insertionIndex) {
  TracePtr tr = boolTrace({"v1", "v2", "v4", "con"});
  DTLimits limits;
  limits._maxDepth = 3;
  limits._maxAll = 5;
  limits._maxWidth = 5;
  auto t = hparser::parseTemplateImplication("G({..##1..} |-> con)", tr, limits);
  DTOperatorPtr dto = t->getDT();
  EXPECT_EQ(dto->insertionIndex(-1), 0u);
  dto->addItem(tr->getBooleanVariable("v1"), -1);
  EXPECT_EQ(dto->insertionIndex(-1), 1u);
  EXPECT_EQ(dto->insertionIndex(2), 2u);
  dto->popItem(-1);
  EXPECT_EQ(dto->insertionIndex(-1), 0u);

  auto a = hparser::parseTemplateImplication("G({..&&..} |-> con)", tr, limits);
  a->getDT()->addItem(tr->getBooleanVariable("v1"), -1);
  EXPECT_EQ(a->getDT()->insertionIndex(-1), 0u);
}

// ---------------------------------------------------------------- D-020
TEST(CoiDepthTest, fits) {
  TracePtr mp = boolTrace({"a", "b", "y", "z", "r1", "r2", "rb"});
  CoiInfoPtr m = loadCoi("multipath", mp);
  ASSERT_NE(m, nullptr);
  // multipath: y <- a at {0, 2}, r1 at {1}, r2 at {0}; z <- b at {1}, rb at {0}; none saturated
  using V = std::vector<std::string>;
  auto con = [](const V &vars, D d) {
    return std::vector<ConsequentLeaf>{{vars, d}};
  };
  struct Case {
    V prop;
    std::vector<ConsequentLeaf> consequent;
    bool any, bounded, exact;
  };
  std::vector<Case> cases = {
      {{"a"}, con({"y"}, 0), true, true, true},
      {{"a"}, con({"y"}, 1), true, true, false},  // 1 is not a depth
      {{"a"}, con({"y"}, 2), true, true, true},
      {{"a"}, con({"y"}, 3), true, false, false}, // deeper than 2, not saturated
      {{"a"}, con({"y"}, -1), true, false, false}, // after the consequent
      {{"a"}, con({"y"}, U), true, true, true},   // offset not fixed: cone membership
      {{"b"}, con({"y"}, 0), false, false, false}, // b is not in y's cone
      {{"a", "r2"}, con({"y"}, 0), true, true, true},
      {{"a", "r2"}, con({"y"}, 2), true, false, false}, // r2 only at depth 0
      // some consequent leaf fits: y at distance 1 does not, y at distance 2 does
      {{"a"}, {{{"y"}, 1}, {{"y"}, 2}}, true, true, true},
      // some consequent variable fits: b is not in y's cone, z <- b at depth 1
      {{"b"}, con({"y", "z"}, 1), true, true, true},
      {{"b"}, con({"y", "z"}, 0), true, true, false},
      {{}, con({"y"}, 7), true, true, true},          // no variables: kept
  };
  for (const auto &c : cases) {
    std::string name = "prop {";
    for (const auto &v : c.prop) {
      name += v + " ";
    }
    name += "} at " + (c.consequent[0].distance
                           ? std::to_string(*c.consequent[0].distance)
                           : std::string("?"));
    EXPECT_EQ(m->fits(c.prop, c.consequent, CoiDepth::Any), c.any) << name;
    EXPECT_EQ(m->fits(c.prop, c.consequent, CoiDepth::Bounded), c.bounded) << name;
    EXPECT_EQ(m->fits(c.prop, c.consequent, CoiDepth::Exact), c.exact) << name;
  }

  // counter: wrap <- rst at {1, 2, 3}, saturated; wrap <- en at {0..3}, saturated
  TracePtr ct = boolTrace({"rst", "en", "cnt", "wrap"});
  CoiInfoPtr k = loadCoi("counter", ct);
  ASSERT_NE(k, nullptr);
  auto w = [](D d) { return std::vector<ConsequentLeaf>{{{"wrap"}, d}}; };
  EXPECT_TRUE(k->fits({"rst"}, w(0), CoiDepth::Bounded));  // below the smallest depth
  EXPECT_FALSE(k->fits({"rst"}, w(0), CoiDepth::Exact));
  EXPECT_TRUE(k->fits({"rst"}, w(5), CoiDepth::Exact));    // saturated, beyond max_depth 3
  EXPECT_TRUE(k->fits({"rst"}, w(5), CoiDepth::Bounded));
  EXPECT_FALSE(k->fits({"rst"}, w(-1), CoiDepth::Bounded)); // after the consequent
  // an unknown variable, and an unknown consequent variable, keep everything
  EXPECT_TRUE(k->fits({"nosuch"}, w(-3), CoiDepth::Exact));
  EXPECT_TRUE(k->fits({"rst"}, {{{"nosuch"}, -3}}, CoiDepth::Exact));
}

// ---------------------------------------------------------------- F6: '->' offsets
TEST(CoiDepthTest, implicationOffsets) {
  TracePtr tr = boolTrace({"a", "b", "c"});
  // "a@0 | b@1 || c@1": the consequent of '->' starts with the antecedent
  std::vector<std::pair<std::string, std::vector<int>>> cases = {
      {"G({a ##1 b} -> X c)", {0, 1, 1}},
      {"G({a ##1 b} -> c)", {0, 1, 0}},
      {"G(a && X b -> X c)", {0, 1, 1}},
      {"G({a ##1 b} |-> X c)", {0, 1, 2}}, // unchanged
  };
  for (const auto &[f, want] : cases) {
    hlog::ScopedThrowOnError throwOnError;
    try {
      auto leaves = leafOffsets(hparser::parseTemporalExpression(f, tr));
      std::vector<int> got;
      for (const auto &l : leaves) {
        got.push_back(l.offset ? *l.offset : -100);
      }
      EXPECT_EQ(got, want) << f;
    } catch (const hlog::HarmError &e) {
      ADD_FAILURE() << f << ": " << e.what();
    }
  }
}
