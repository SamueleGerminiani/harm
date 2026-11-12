// H1d: printing fixes F7 and F8 (found in H8). Expected texts are written by hand from the
// semantics:
//  F7  HARM's '->' starts the consequent with the antecedent; SVA's '|->' starts it at the end of
//      the antecedent. A '->' with a multi-cycle antecedent is printed re-anchored at the end
//      ('|->', '|=>', '|-> ##j', or '$past' when the consequent lies inside the antecedent), or as
//      '(s) implies p' when that is not possible (D-021).
//  F8  in Spot's syntax X, F, G, !, U/W and R bind tighter than && and ||, and && tighter than ||:
//      a proposition with a Boolean connective is parenthesized under them (D-021).
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <string>
#include <utility>
#include <vector>

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
TracePtr trace() {
  std::vector<VarDeclaration> vars;
  for (std::string b : {"a", "b", "en", "wrap"}) {
    vars.emplace_back(b, ExpType::Bool, 1);
  }
  return generatePtr<Trace>(vars, 4);
}

std::string print(const std::string &f, Language lang) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    auto te = hparser::parseTemporalExpression(f, trace());
    return temp2String(te, lang, PrintMode::ShowAll);
  } catch (const hlog::HarmError &e) {
    return std::string("ERROR: ") + e.what();
  }
}

void check(const std::vector<std::pair<std::string, std::string>> &cases, Language lang) {
  for (const auto &[f, want] : cases) {
    EXPECT_EQ(print(f, lang), want) << f;
  }
}
} // namespace

// ---------------------------------------------------------------- F7
TEST(PrintingTest, svaArrowWithMultiCycleAntecedent) {
  check(
      {
          // the consequent at the last antecedent cycle (a@0, b@1, wrap@1)
          {"G({a ##1 b} -> X wrap)", "always (a ##1 b |-> wrap)"},
          // one cycle after it
          {"G({a ##1 b} -> X X wrap)", "always (a ##1 b |=> wrap)"},
          {"G({a ##1 b ##1 en} -> X X X wrap)", "always (a ##1 b ##1 en |=> wrap)"},
          // two cycles after it
          {"G({a ##1 b} -> X X X wrap)", "always (a ##1 b |-> ##2 wrap)"},
          // inside the antecedent: wrap@0 with a@0, b@1; wrap@1 with a@0, b@2
          {"G({a ##1 b} -> wrap)", "always (a ##1 b |-> $past(wrap, 1))"},
          {"G({a ##2 b} -> X wrap)", "always (a ##2 b |-> $past(wrap, 1))"},
          // not a fixed-length sequence, or not a Boolean consequent: 'implies' starts both sides
          // together
          {"G({a ##[1:2] b} -> X wrap)", "always ((a ##[1:2] b) implies nexttime wrap)"},
          {"G(a && X b -> X wrap)", "always ((a and nexttime b) implies nexttime wrap)"},
      },
      Language::SVA);
}

TEST(PrintingTest, svaUnchanged) {
  check(
      {
          {"G(a -> b)", "always (a |-> b)"},
          {"G(a -> X b)", "always (a |=> b)"},
          {"G(a -> X X b)", "always (a |-> ##2 b)"},
          {"G({a ##1 b} |-> X wrap)", "always (a ##1 b |=> wrap)"},
          {"G({a ##1 b} |-> wrap)", "always (a ##1 b |-> wrap)"},
          {"G(a -> X(b && en))", "always (a |=> b && en)"},
      },
      Language::SVA);
}

// ---------------------------------------------------------------- F8
TEST(PrintingTest, spotParenthesesUnderTighterOperators) {
  check(
      {
          {"G(a -> X(b && en))", "G(a -> X(b && en))"},
          {"G(a -> X(b || en))", "G(a -> X(b || en))"},
          {"G((a || b) && X en -> wrap)", "G((a || b) && Xen -> wrap)"},
      },
      Language::SpotLTL);
}

TEST(PrintingTest, spotUnchanged) {
  check(
      {
          {"G(a -> X b)", "G(a -> Xb)"},
          {"G(a && b -> X en)", "G(a && b -> Xen)"},
          {"G({a ##1 b} -> X wrap)", "G({a ##1 b} -> Xwrap)"},
      },
      Language::SpotLTL);
}
