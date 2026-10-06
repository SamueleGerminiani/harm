// H3b, acceptance tests A1-A3 (D-025) and the soundness oracle on traces with x/z values.
//  A1  H3's hand-labelled pairs with atom premises: only the pair that needs a fact between atoms
//      (cnt > 9 / cnt > 8) changes, to B_IMPLIES_A
//  A2  tests/input/h3b/pairs.txt, labelled by hand from the semantics (with HARM's x/z rule, D-011)
//  A3  facts between atoms (smt::checkImplication), labelled by hand
//  Oracle: every implication claimed with premises is checked on random traces in which cnt and st
//      take x/z bits, with HARM's own evaluator (not the reduction code): wherever A holds, B holds.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <fstream>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#include "ImplicationReducer.hh"
#include "Logic.hh"
#include "PointerUtils.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "expUtils/smtEquivalence.hh"
#include "formula/atom/Variable.hh"
#include "formula/temporal/temporal.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {
TracePtr traceOf(size_t length) {
  std::vector<VarDeclaration> decls;
  for (std::string b : {"a", "b", "c", "d"}) {
    decls.emplace_back(b, ExpType::Bool, 1);
  }
  decls.emplace_back("cnt", ExpType::ULogic, 4);
  decls.emplace_back("st", ExpType::ULogic, 2);
  decls.emplace_back("i", ExpType::SInt, 32);
  decls.emplace_back("w64", ExpType::ULogic, 64);
  decls.emplace_back("v64", ExpType::ULogic, 64);
  return generatePtr<Trace>(decls, length);
}

std::vector<std::string> split(const std::string &line, const std::string &sep) {
  std::vector<std::string> f;
  size_t start = 0, p;
  while ((p = line.find(sep, start)) != std::string::npos) {
    f.push_back(line.substr(start, p - start));
    start = p + sep.size();
  }
  f.push_back(line.substr(start));
  return f;
}

TemporalExpressionPtr parse(const std::string &f, const TracePtr &tr) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    return hparser::parseTemporalExpression(f, tr);
  } catch (const hlog::HarmError &e) {
    ADD_FAILURE() << "cannot parse '" << f << "': " << e.what();
    return nullptr;
  }
}

std::string randomLogic(std::mt19937 &rng, size_t width) {
  const char bits[] = "01xz";
  std::string s;
  for (size_t i = 0; i < width; i++) {
    // mostly known bits, so that comparisons are often decided
    s += bits[rng() % 10 < 8 ? rng() % 2 : 2 + rng() % 2];
  }
  return s;
}

/// a random trace on which x holds and y fails, if any, among n random traces (lengths 1..6)
std::string refutation(const std::string &x, const std::string &y, size_t n, unsigned seed) {
  std::mt19937 rng(seed);
  for (size_t k = 0; k < n; k++) {
    size_t L = 1 + rng() % 6;
    TracePtr tr = traceOf(L);
    for (size_t t = 0; t < L; t++) {
      for (std::string b : {"a", "b", "c", "d"}) {
        tr->getBooleanVariable(b)->assign(t, (bool)(rng() % 2));
      }
      tr->getLogicVariable("cnt")->assign(t, Logic(randomLogic(rng, 4), 4));
      tr->getLogicVariable("st")->assign(t, Logic(randomLogic(rng, 2), 2));
    }
    TemplateImplicationPtr tx, ty;
    {
      hlog::ScopedThrowOnError throwOnError;
      try {
        tx = hparser::parseTemplateImplication(x, tr, DTLimits(), false);
        ty = hparser::parseTemplateImplication(y, tr, DTLimits(), false);
      } catch (const hlog::HarmError &e) {
        return std::string("cannot evaluate: ") + e.what();
      }
    }
    if (tx->assHoldsOnTrace(Location::AntCon) && !ty->assHoldsOnTrace(Location::AntCon)) {
      std::string rows;
      for (size_t t = 0; t < L; t++) {
        rows += "t" + std::to_string(t) + ": cnt=" +
                tr->getLogicVariable("cnt")->evaluate(t).toString() + " st=" +
                tr->getLogicVariable("st")->evaluate(t).toString() + "; ";
      }
      return rows;
    }
  }
  return "";
}

/// the soundness oracle on the claims of one pair
void checkClaims(const std::string &a, const std::string &b, Implication rel) {
  auto claim = [&](const std::string &x, const std::string &y) {
    std::string r = refutation(x, y, 2000, 7);
    EXPECT_TRUE(r.empty()) << "UNSOUND: '" << x << "' implies '" << y << "', refuted by " << r;
  };
  if (rel == Implication::AImpliesB || rel == Implication::Equivalent) {
    claim(a, b);
  }
  if (rel == Implication::BImpliesA || rel == Implication::Equivalent) {
    claim(b, a);
  }
}

AtomPremises on() {
  AtomPremises p;
  p.enabled = true;
  return p;
}
} // namespace

// ---------------------------------------------------------------- A1
TEST(AtomPremiseTest, h3PairsOnlyTheAtomPairChanges) {
  TracePtr tr = traceOf(4);
  std::ifstream in("../tests/input/h3/pairs.txt");
  ASSERT_TRUE(in.good());
  std::string line;
  size_t n = 0;
  while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }
    auto f = split(line, " | ");
    auto a = parse(f[1], tr), b = parse(f[2], tr);
    if (a == nullptr || b == nullptr) {
      continue;
    }
    std::string want = f[0];
    if (f[1] == "G(cnt > 4'd9 -> b)" && f[2] == "G(cnt > 4'd8 -> b)") {
      want = "B_IMPLIES_A"; // the one pair H3 labelled "needs H3b"
    }
    EXPECT_EQ(toString(implicationBetween(a, b, 1000, on())), want) << line;
    n++;
  }
  EXPECT_EQ(n, 37u);
}

// ---------------------------------------------------------------- A2 (+ the oracle on its claims)
TEST(AtomPremiseTest, handLabelledPairsWithPremises) {
  TracePtr tr = traceOf(4);
  std::ifstream in("../tests/input/h3b/pairs.txt");
  ASSERT_TRUE(in.good());
  std::string line;
  size_t n = 0, needPremises = 0;
  while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }
    auto f = split(line, " | ");
    ASSERT_GE(f.size(), 3u) << line;
    auto a = parse(f[1], tr), b = parse(f[2], tr);
    if (a == nullptr || b == nullptr) {
      continue;
    }
    Implication rel = implicationBetween(a, b, 1000, on());
    EXPECT_EQ(toString(rel), f[0]) << line;
    needPremises += toString(implicationBetween(a, b)) != f[0];
    checkClaims(f[1], f[2], rel);
    n++;
  }
  EXPECT_EQ(n, 20u);
  std::cout << n << " pairs; " << needPremises << " are labelled differently without premises\n";
  EXPECT_EQ(needPremises, 14u); // the 6 others: one H2 equivalence and five NONE
}

// ---------------------------------------------------------------- A3
TEST(AtomPremiseTest, factsBetweenAtoms) {
  TracePtr tr = traceOf(4);
  using smt::Entails;
  struct Case {
    std::string p, q;
    Entails want;
  };
  std::vector<Case> cases = {
      {"cnt > 4'd9", "cnt > 4'd8", Entails::Yes},
      {"cnt > 4'd8", "cnt > 4'd9", Entails::No},
      {"cnt == 4'd9", "cnt > 4'd8", Entails::Yes},
      {"cnt == 4'd9", "cnt[3]", Entails::Yes},       // 9 = 4'b1001
      {"cnt == 4'd9", "cnt[1]", Entails::No},
      {"cnt != 4'd1", "!(cnt == 4'd1)", Entails::Yes}, // with x: cnt != 1 is false
      {"!(cnt == 4'd1)", "cnt != 4'd1", Entails::No},  // with x: !(cnt == 1) is true
      {"st == 2'd1", "!(st == 2'd2)", Entails::Yes},   // exclusion
      {"!(st == 2'd2)", "st == 2'd1", Entails::No},
      {"i < -1", "i < 0", Entails::Yes},               // signed
      {"i < 0", "i < -1", Entails::No},
      {"a && cnt > 4'd3", "a", Entails::Yes},
  };
  for (const auto &c : cases) {
    hlog::ScopedThrowOnError throwOnError;
    auto p = hparser::parseProposition(c.p, tr);
    auto q = hparser::parseProposition(c.q, tr);
    EXPECT_EQ((int)smt::checkImplication(p, q, 2000), (int)c.want) << c.p << "  =>  " << c.q;
  }
  // a query that cannot be decided in 1 ms (64-bit factoring) gives no fact
  hlog::ScopedThrowOnError throwOnError;
  auto p = hparser::parseProposition("w64 * v64 == 64'd12658759574012456147", tr);
  auto q = hparser::parseProposition("w64 != 64'd1", tr);
  EXPECT_EQ((int)smt::checkImplication(p, q, 1), (int)Entails::Unknown);
}

// ---------------------------------------------------------------- A5 (the cap, at API level)
TEST(AtomPremiseTest, capGivesASubsetOfTheClaims) {
  TracePtr tr = traceOf(4);
  std::ifstream in("../tests/input/h3b/pairs.txt");
  std::string line;
  AtomPremises capped = on();
  capped.maxQueries = 0;
  while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }
    auto f = split(line, " | ");
    auto a = parse(f[1], tr), b = parse(f[2], tr);
    // with no query allowed, every claim is H3's own
    EXPECT_EQ(toString(implicationBetween(a, b, 1000, capped)), toString(implicationBetween(a, b)))
        << line;
  }
}
