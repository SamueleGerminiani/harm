// H2, acceptance tests A2-A4: proposition equivalence with Z3 under HARM's semantics.
//  A2 hand-labelled pairs (tests/input/h2/pairs.txt)
//  A3 soundness against HARM's own evaluator: exhaustive over all 4-valued assignments of small
//     variables, random assignments for wide ones (tests/input/h2/*_pairs.txt)
//  A4 a solver timeout never yields "equivalent"
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#include "Logic.hh"
#include "PointerUtils.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/smtEquivalence.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "propositionParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;
using smt::Equivalence;

namespace {

const std::string h2 = "../tests/input/h2/";

PropositionPtr parse(const std::string &s, const TracePtr &trace) {
  std::string error;
  PropositionPtr p = hparser::tryParseProposition(s, trace, error);
  EXPECT_NE(p, nullptr) << "cannot parse '" << s << "': " << error;
  return p;
}

std::string str(Equivalence e) {
  return e == Equivalence::Equivalent      ? "Equivalent"
         : e == Equivalence::NotEquivalent ? "NotEquivalent"
                                           : "Unknown";
}

// a trace with the given logic variables and the given number of rows
TracePtr logicTrace(const std::vector<std::pair<std::string, size_t>> &vars,
                    size_t length) {
  std::vector<VarDeclaration> decls;
  for (const auto &[n, w] : vars) {
    decls.emplace_back(n, ExpType::ULogic, w);
  }
  return generatePtr<Trace>(decls, length);
}

std::vector<std::pair<std::string, std::string>>
readPairs(const std::string &file) {
  std::vector<std::pair<std::string, std::string>> pairs;
  std::ifstream in(h2 + file);
  std::string line;
  while (std::getline(in, line)) {
    size_t sep = line.find(" ||| ");
    if (sep != std::string::npos) {
      pairs.emplace_back(line.substr(0, sep), line.substr(sep + 5));
    }
  }
  return pairs;
}

struct Soundness {
  size_t pairs = 0, unsound = 0, provedEquivalent = 0, trulyEquivalent = 0,
         missed = 0, unknown = 0;
};

// Z3 must never say "equivalent" when HARM's evaluator finds a row where the propositions differ
Soundness checkSoundness(const std::vector<std::pair<std::string, std::string>> &pairs,
                         const TracePtr &trace) {
  Soundness s;
  for (const auto &[a, b] : pairs) {
    PropositionPtr p = parse(a, trace), q = parse(b, trace);
    if (p == nullptr || q == nullptr) {
      continue;
    }
    s.pairs++;
    bool same = true;
    for (size_t t = 0; t < trace->getLength() && same; t++) {
      same = p->evaluate(t) == q->evaluate(t);
    }
    Equivalence e = smt::checkEquivalence(p, q);
    s.trulyEquivalent += same;
    s.provedEquivalent += e == Equivalence::Equivalent;
    s.unknown += e == Equivalence::Unknown;
    if (e == Equivalence::Equivalent && !same) {
      s.unsound++;
      if (s.unsound <= 10) {
        std::cout << "UNSOUND: '" << a << "' vs '" << b << "'\n";
      }
    }
    if (e != Equivalence::Equivalent && same) {
      s.missed++;
    }
  }
  return s;
}

void report(const std::string &name, const Soundness &s) {
  std::cout << "[" << name << "] pairs: " << s.pairs
            << ", equivalent by evaluation: " << s.trulyEquivalent
            << ", proved equivalent: " << s.provedEquivalent
            << ", UNSOUND: " << s.unsound
            << ", not proved although equivalent on all rows: " << s.missed
            << ", unknown: " << s.unknown << "\n";
}

} // namespace

TEST(Z3EquivalenceTest, isAvailable) { ASSERT_TRUE(smt::available()); }

// ---------------------------------------------------------------- A2
TEST(Z3EquivalenceTest, handLabelledPairs) {
  std::vector<VarDeclaration> decls;
  decls.emplace_back("a4", ExpType::ULogic, 4);
  decls.emplace_back("b4", ExpType::ULogic, 4);
  decls.emplace_back("c8", ExpType::ULogic, 8);
  decls.emplace_back("e1", ExpType::ULogic, 1);
  decls.emplace_back("k", ExpType::SInt, 64);
  decls.emplace_back("f", ExpType::Float, 64);
  decls.emplace_back("flag", ExpType::Bool, 1);
  decls.emplace_back("s", ExpType::String, 1);
  TracePtr trace = generatePtr<Trace>(decls, 2);

  std::ifstream in(h2 + "pairs.txt");
  ASSERT_TRUE(in.good());
  std::string line;
  size_t n = 0;
  while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }
    std::vector<std::string> f;
    size_t start = 0, sep;
    while ((sep = line.find(" | ", start)) != std::string::npos) {
      f.push_back(line.substr(start, sep - start));
      start = sep + 3;
    }
    f.push_back(line.substr(start));
    ASSERT_GE(f.size(), 3u) << line;
    std::string label = f[0].substr(0, f[0].find(' '));
    PropositionPtr p = parse(f[1], trace), q = parse(f[2], trace);
    if (p == nullptr || q == nullptr) {
      continue;
    }
    Equivalence e = smt::checkEquivalence(p, q);
    if (label == "EQ") {
      EXPECT_EQ(str(e), "Equivalent") << line;
    } else {
      EXPECT_NE(str(e), "Equivalent") << line;
    }
    n++;
  }
  EXPECT_EQ(n, 56u);
}

// ---------------------------------------------------------------- A3
TEST(Z3EquivalenceTest, soundOnAllAssignmentsOfSmallVariables) {
  // every 4-valued assignment of v1 (1 bit), v2 (2 bits), v3 (3 bits): 4^6 = 4096 rows
  std::vector<std::pair<std::string, size_t>> vars = {
      {"v1", 1}, {"v2", 2}, {"v3", 3}};
  TracePtr trace = logicTrace(vars, 4096);
  const char digits[] = {'0', '1', 'x', 'z'};
  for (size_t row = 0; row < 4096; row++) {
    size_t code = row;
    for (const auto &[n, w] : vars) {
      std::string bits;
      for (size_t b = 0; b < w; b++) {
        bits += digits[code % 4];
        code /= 4;
      }
      trace->getLogicVariable(n)->assign(row, Logic(bits, w));
    }
  }
  Soundness s = checkSoundness(readPairs("small_pairs.txt"), trace);
  report("small, exhaustive", s);
  EXPECT_EQ(s.unsound, 0u);
  // completeness: every pair that is equivalent on all assignments should be proved
  EXPECT_EQ(s.missed, 0u);
}

TEST(Z3EquivalenceTest, soundOnRandomAssignmentsOfWideVariables) {
  std::vector<std::pair<std::string, size_t>> vars = {
      {"q4", 4}, {"r8", 8}, {"t13", 13}, {"u32", 32}};
  const size_t rows = 20000;
  TracePtr trace = logicTrace(vars, rows);
  std::mt19937 rng(13);
  for (size_t row = 0; row < rows; row++) {
    // a third of the rows are 2-valued, so that known-value comparisons are exercised too
    bool twoValued = row % 3 == 0;
    for (const auto &[n, w] : vars) {
      std::string bits;
      for (size_t b = 0; b < w; b++) {
        bits += twoValued ? "01"[rng() % 2] : "01xz01"[rng() % 6];
      }
      trace->getLogicVariable(n)->assign(row, Logic(bits, w));
    }
  }
  Soundness s = checkSoundness(readPairs("wide_pairs.txt"), trace);
  report("wide, random", s);
  EXPECT_EQ(s.unsound, 0u);
}

// ---------------------------------------------------------------- A4
TEST(Z3EquivalenceTest, timeoutNeverMeansEquivalent) {
  TracePtr trace = logicTrace({{"u32", 32}, {"w32", 32}}, 2);
  // not equivalent (u32 = 2^31 + 2 also squares to 4), and hard for a solver
  PropositionPtr p = parse("(u32 * w32) == 32'd4 && (w32 == u32)", trace);
  PropositionPtr q = parse("u32 == 32'd2 && w32 == 32'd2", trace);
  ASSERT_NE(p, nullptr);
  ASSERT_NE(q, nullptr);
  EXPECT_NE(str(smt::checkEquivalence(p, q, 1)), "Equivalent");
  EXPECT_NE(str(smt::checkEquivalence(p, q, 1000)), "Equivalent");
}
