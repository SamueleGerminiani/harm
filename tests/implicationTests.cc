// H3, acceptance tests A1 (hand-labelled pairs) and A2 (bounded-trace oracle in HARM's own
// semantics): Spot-based implication between assertions must never claim an implication that a
// finite boolean trace refutes.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ImplicationReducer.hh"
#include "PointerUtils.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "formula/atom/Variable.hh"
#include "message.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

const std::string h3 = "../tests/input/h3/";

TracePtr traceWith(const std::vector<std::string> &bools, size_t length,
                   bool withCnt) {
  std::vector<VarDeclaration> decls;
  for (const auto &n : bools) {
    decls.emplace_back(n, ExpType::Bool, 1);
  }
  if (withCnt) {
    decls.emplace_back("cnt", ExpType::ULogic, 4);
  }
  return generatePtr<Trace>(decls, length);
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

/// a trace (as one row per instant) on which A holds and B fails, if any, among all boolean
/// traces of the given atoms and lengths 1..maxLength; HARM's evaluator decides "holds"
std::string refutation(const std::string &a, const std::string &b,
                       const std::vector<std::string> &atoms,
                       size_t maxLength) {
  for (size_t L = 1; L <= maxLength; L++) {
    TracePtr tr = traceWith(atoms, L, false);
    TemplateImplicationPtr ta, tb;
    {
      hlog::ScopedThrowOnError throwOnError;
      try {
        ta = hparser::parseTemplateImplication(a, tr, DTLimits(), false);
        tb = hparser::parseTemplateImplication(b, tr, DTLimits(), false);
      } catch (const hlog::HarmError &e) {
        return std::string("cannot evaluate: ") + e.what();
      }
    }
    size_t bits = atoms.size() * L;
    for (size_t code = 0; code < ((size_t)1 << bits); code++) {
      for (size_t t = 0; t < L; t++) {
        for (size_t k = 0; k < atoms.size(); k++) {
          tr->getBooleanVariable(atoms[k])->assign(
              t, (bool)((code >> (t * atoms.size() + k)) & 1));
        }
      }
      if (ta->assHoldsOnTrace(Location::AntCon) &&
          !tb->assHoldsOnTrace(Location::AntCon)) {
        std::string rows;
        for (size_t t = 0; t < L; t++) {
          rows += "t" + std::to_string(t) + ":";
          for (size_t k = 0; k < atoms.size(); k++) {
            rows += " " + atoms[k] + "=" +
                    std::to_string((code >> (t * atoms.size() + k)) & 1);
          }
          rows += ";";
        }
        return rows;
      }
    }
  }
  return "";
}

/// checks every implication claimed between a and b; returns the number of unsound claims
size_t checkClaims(const std::string &a, const std::string &b, Implication rel,
                   const std::vector<std::string> &atoms, size_t maxLength) {
  size_t unsound = 0;
  auto claim = [&](const std::string &x, const std::string &y) {
    std::string r = refutation(x, y, atoms, maxLength);
    if (!r.empty()) {
      unsound++;
      ADD_FAILURE() << "UNSOUND: '" << x << "' implies '" << y
                    << "' is refuted by " << r;
    }
  };
  if (rel == Implication::AImpliesB || rel == Implication::Equivalent) {
    claim(a, b);
  }
  if (rel == Implication::BImpliesA || rel == Implication::Equivalent) {
    claim(b, a);
  }
  return unsound;
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

} // namespace

// ---------------------------------------------------------------- A1 (+ A2 on its claims)
TEST(ImplicationTest, handLabelledPairs) {
  TracePtr tr = traceWith({"a", "b", "c", "d"}, 4, true);
  std::ifstream in(h3 + "pairs.txt");
  ASSERT_TRUE(in.good());
  std::string line;
  size_t n = 0;
  while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }
    auto f = split(line, " | ");
    ASSERT_GE(f.size(), 3u) << line;
    TemporalExpressionPtr a = parse(f[1], tr), b = parse(f[2], tr);
    if (a == nullptr || b == nullptr) {
      continue;
    }
    Implication rel = implicationBetween(a, b);
    EXPECT_EQ(toString(rel), f[0]) << line;
    // the bounded oracle on the claims of pairs over boolean atoms only
    if (f[1].find("cnt") == std::string::npos &&
        f[2].find("cnt") == std::string::npos) {
      checkClaims(f[1], f[2], rel, {"a", "b", "c", "d"}, 4);
    }
    n++;
  }
  EXPECT_EQ(n, 37u);
}

// ---------------------------------------------------------------- A2
TEST(ImplicationTest, generatedPairsAreSoundOnAllShortTraces) {
  TracePtr tr = traceWith({"a", "b", "c"}, 4, false);
  std::ifstream in(h3 + "generated_pairs.txt");
  ASSERT_TRUE(in.good());
  std::string line;
  size_t pairs = 0, claims = 0, skipped = 0, unsound = 0;
  while (std::getline(in, line)) {
    auto f = split(line, " ||| ");
    if (f.size() != 2) {
      continue;
    }
    TemporalExpressionPtr a = parse(f[0], tr), b = parse(f[1], tr);
    if (a == nullptr || b == nullptr) {
      continue;
    }
    pairs++;
    Implication rel = implicationBetween(a, b);
    skipped += rel == Implication::Skipped;
    claims += rel == Implication::AImpliesB || rel == Implication::BImpliesA ||
              rel == Implication::Equivalent;
    // every boolean trace of a, b, c up to length 6 (2^18 traces at length 6)
    unsound += checkClaims(f[0], f[1], rel, {"a", "b", "c"}, 6);
  }
  std::cout << "[generated] pairs: " << pairs << ", implications claimed: "
            << claims << ", skipped (not safety): " << skipped
            << ", UNSOUND: " << unsound << "\n";
  EXPECT_EQ(pairs, 310u);
  EXPECT_GT(claims, 0u);
  EXPECT_EQ(skipped, 10u);
  EXPECT_EQ(unsound, 0u);
}
