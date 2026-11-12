// H7, acceptance A4: the D-017 cone predicate on hand cases. Cones of the H4 fixture 'multipath'
// (validated by simulation in H4): r1 <- a; r2 <- a, r1; rb <- b; y <- a, r1, r2; z <- b, rb;
// a, b: no sources. 'extra' is a trace variable that coi.json does not know.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <string>
#include <tuple>
#include <vector>

#include "CoiInfo.hh"
#include "PointerUtils.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "message.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

TEST(CoiFilterTest, inConeHandCases) {
  std::vector<VarDeclaration> decls;
  for (const std::string n : {"a", "b", "y", "z", "r1", "r2", "rb", "extra"}) {
    decls.emplace_back(n, ExpType::Bool, 1);
  }
  TracePtr tr = generatePtr<Trace>(decls, 4);
  CoiInfoPtr coi;
  {
    hlog::ScopedThrowOnError throwOnError;
    coi = CoiInfo::load("../tests/input/coi/multipath/expected_coi.json", tr);
  }
  ASSERT_NE(coi, nullptr);
  using V = std::vector<std::string>;
  // proposition variables, consequent variables, in the cone
  std::vector<std::tuple<V, V, bool>> cases = {
      {{"a"}, {"y"}, true},
      {{"b"}, {"y"}, false},
      {{"a", "b"}, {"y"}, false},       // every variable must be in the cone
      {{"a", "b"}, {"y", "z"}, true},   // a reaches y, b reaches z: the union of the cones
      {{"r1", "r2"}, {"y"}, true},
      {{}, {"y"}, true},                // a constant
      {{"r2"}, {"r2"}, false},          // not in its own cone
      {{"a"}, {"a"}, false},            // a has no sources
      {{"b"}, {"z"}, true},
      {{"extra"}, {"y"}, true},         // unknown signal: in the cone (D-014, D-017)
      {{"b"}, {"extra"}, true},         // unknown consequent: its cone is unknown
      {{"a", "extra"}, {"z"}, false},   // a is known and outside z's cone
  };
  for (const auto &[prop, con, expected] : cases) {
    std::string label;
    for (const auto &v : prop) {
      label += v + " ";
    }
    label += "-> ";
    for (const auto &v : con) {
      label += v + " ";
    }
    EXPECT_EQ(coi->inCone(prop, con), expected) << label;
  }
}
