// H1c, acceptance tests A1 (hand-derived end-of-trace verdicts) and A2 (dump for the independent
// IEEE 1800 Annex F oracle, tests/oracle/sva_finite_semantics.py). D-016: '--trace-end harm' is
// the weak view (pending holds), '--trace-end sva' the neutral view (pending strong obligations
// fail).
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "PointerUtils.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Variable.hh"
#include "globals.hh"
#include "message.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

const std::vector<std::string> atoms = {"a", "b", "c"};

TracePtr boolTrace(size_t length) {
  std::vector<VarDeclaration> decls;
  for (const auto &n : atoms) {
    decls.emplace_back(n, ExpType::Bool, 1);
  }
  return generatePtr<Trace>(decls, length);
}

/// restores the default semantics after a test
struct TraceEnd {
  explicit TraceEnd(const std::string &mode) { clc::traceEnd = mode; }
  ~TraceEnd() { clc::traceEnd = "harm"; }
};

/// HARM's verdict on a trace given as rows of 'abc' bits, e.g. "100,010"
bool holds(const std::string &formula, const std::string &rows,
           const std::string &mode) {
  TraceEnd te(mode);
  std::vector<std::string> cycles;
  size_t start = 0, p;
  while ((p = rows.find(',', start)) != std::string::npos) {
    cycles.push_back(rows.substr(start, p - start));
    start = p + 1;
  }
  cycles.push_back(rows.substr(start));
  TracePtr tr = boolTrace(cycles.size());
  for (size_t t = 0; t < cycles.size(); t++) {
    for (size_t k = 0; k < atoms.size(); k++) {
      tr->getBooleanVariable(atoms[k])->assign(t, cycles[t][k] == '1');
    }
  }
  hlog::ScopedThrowOnError throwOnError;
  TemplateImplicationPtr ti =
      hparser::parseTemplateImplication(formula, tr, DTLimits(), false);
  return ti->assHoldsOnTrace(Location::AntCon);
}

} // namespace

// ---------------------------------------------------------------- A1
// formula, trace (rows of a b c), holds with --trace-end harm, holds with --trace-end sva.
// Each verdict is derived by hand from the weak view (harm) and the neutral view (sva).
TEST(EndOfTraceTest, handDerivedVerdicts) {
  struct Case {
    std::string formula, rows;
    bool harm, sva;
  };
  std::vector<Case> cases = {
      // s_eventually: strong
      {"G(a -> F b)", "100,000,000", true, false},  // b never after a
      {"G(a -> F b)", "100,010,000", true, true},   // b at t1
      {"G(a -> F b)", "000,000,000", true, true},   // no antecedent
      {"G(a -> F b)", "110", true, true},           // F includes the current cycle
      {"G(a -> F b)", "100,010,100", true, false},  // the second a is still pending
      // nexttime: weak
      {"G(a -> X b)", "100", true, true},           // a on the last cycle
      {"G(a -> X b)", "100,000", false, false},
      {"G(a -> X X b)", "100,000", true, true},     // t2 does not exist
      {"G(a -> X !b)", "100", true, true},
      // not nexttime = s_nexttime not: strong
      {"G(a -> !X b)", "100", true, false},         // no next cycle to show !b
      {"G(a -> !X b)", "100,000", true, true},
      {"G(a -> !X b)", "100,010", false, false},
      {"G(a -> !X !X b)", "100,000", true, true},   // X(!X b)@0 = (!X b)@1 = false: holds
      {"G(a -> !X !X b)", "100", true, false},      // X(...)@0 is weak-true at the end
      // until: weak; not until: strong
      {"G(a -> b W c)", "110,010,010", true, true}, // b to the end, c never: weak
      {"G(a -> !(b W c))", "110,010", true, false}, // needs !b && !c before c: never
      {"G(a -> !(b W c))", "110,000", true, true},  // !b && !c at t1
      {"G(a -> !(b W c))", "100", true, true},      // !b && !c at t0
      {"G(a -> !(b W c))", "111", false, false},    // c at t0: b W c holds, its negation fails
      // nesting
      {"G(a -> X F b)", "100", true, true},         // nexttime is weak at the end
      {"G(a -> X F b)", "100,000", true, false},    // s_eventually b from t1: never
      {"G(a -> F X b)", "100,000", true, true},     // X b at t1 is weak-true
      {"G(a -> F !X b)", "100,000", true, true},    // at t0, X b = b@1 = 0
      {"G(a -> F !X b)", "100,010", true, false},   // t0: b@1; t1: no next cycle
      {"G(a -> (F b) || (X c))", "100", true, true},  // X c weak-true
      {"G(a -> (F b) || (!X c))", "100", true, false}, // both strong, both pending
      {"G(a -> (F b) && (X c))", "100", true, false},
      // the antecedent: a match must end inside the trace; |=> is a weak nexttime
      {"G(a |=> F b)", "100", true, true},           // the consequent starts after the end
      {"G(a |=> F b)", "100,000", true, false},
      {"G({a ##1 b} |-> F c)", "100,010", true, false},
      {"G({a ##1 b} |-> F c)", "100", true, true},   // no match
      {"G({a ##1 b} |-> F c)", "100,011", true, true},
      // decided inside the trace: unchanged
      {"G(a -> b)", "100", false, false},
  };
  for (const auto &c : cases) {
    for (const std::string mode : {"harm", "sva"}) {
      bool expected = mode == "harm" ? c.harm : c.sva;
      try {
        EXPECT_EQ(holds(c.formula, c.rows, mode), expected)
            << c.formula << " on " << c.rows << " with --trace-end " << mode;
      } catch (const hlog::HarmError &e) {
        ADD_FAILURE() << "cannot evaluate '" << c.formula << "': " << e.what();
      }
    }
  }
}

// ---------------------------------------------------------------- SVA precedence (finding)
// Found while writing A2: HARM's SVA printer used HARM's (LTL) precedence, but in SVA 'until'
// binds looser than 'and'/'or' and 's_eventually' looser than everything (IEEE 1800-2017 Table
// 16-3), so e.g. 'G(b -> (b W c) && X X F b)' printed as 'b until c and ...'.
TEST(EndOfTraceTest, svaPrecedence) {
  std::vector<std::pair<std::string, std::string>> cases = {
      {"G(a -> F b)", "always (a |-> s_eventually b)"},
      {"G(a -> (F b) || (X c))", "always (a |-> (s_eventually b) or nexttime c)"},
      {"G(b -> ((b W c)) && (X X F b))",
       "always (b |-> (b until c) and nexttime nexttime (s_eventually b))"},
      {"G(b -> (F (b) || (!c)) && (!X (!a) || (!c)))",
       "always (b |-> ((s_eventually b) or !c) and (not nexttime !a or !c))"},
      {"G({a && !c} |-> ((!a) && (b) W !c))",
       "always (a && !c |-> !a and (b until !c))"},
      {"G({a ##1 a} |-> F (c) && (c))", "always (a ##1 a |-> (s_eventually c) and c)"},
  };
  TracePtr tr = boolTrace(4);
  for (const auto &[f, sva] : cases) {
    hlog::ScopedThrowOnError throwOnError;
    try {
      TemporalExpressionPtr te = hparser::parseTemporalExpression(f, tr);
      EXPECT_EQ(temp2String(te, Language::SVA, PrintMode::ShowAll), sva) << f;
    } catch (const hlog::HarmError &e) {
      ADD_FAILURE() << "cannot parse '" << f << "': " << e.what();
    }
  }
}

// ---------------------------------------------------------------- A2 (dump)
// For every formula of tests/input/h1c/formulas.txt: its SVA text and HARM's verdicts, in both
// modes, on every boolean trace of a, b, c of lengths 1..4 (one character per trace: '1' holds,
// '0' fails; traces enumerated by length, then by code, bit t*3+k = atom k at cycle t). The
// oracle test (sva_finite_semantics.py) recomputes them from IEEE 1800 Annex F.
TEST(EndOfTraceTest, dumpForOracle) {
  std::ifstream in("../tests/input/h1c/formulas.txt");
  ASSERT_TRUE(in.good());
  // the oracle test (h1c_annex_f_oracle) sets its own file, so the two can run in parallel
  const char *dumpFile = std::getenv("H1C_DUMP");
  std::ofstream out(dumpFile != nullptr ? dumpFile : "h1c_oracle_dump.txt");
  ASSERT_TRUE(out.good());
  std::string formula;
  size_t n = 0, unsupported = 0;
  while (std::getline(in, formula)) {
    if (formula.empty() || formula[0] == '#') {
      continue;
    }
    std::string sva, verdicts[2];
    for (size_t L = 1; L <= 4; L++) {
      TracePtr tr = boolTrace(L);
      TemplateImplicationPtr ti;
      {
        hlog::ScopedThrowOnError throwOnError;
        try {
          ti = hparser::parseTemplateImplication(formula, tr, DTLimits(), false);
        } catch (const hlog::HarmError &e) {
          if (std::string(e.what()).find("non-deterministic automaton") ==
              std::string::npos) {
            ADD_FAILURE() << "cannot parse '" << formula << "': " << e.what();
            break;
          }
          // HARM requires a deterministic automaton (AutomataBasedEvaluator)
          std::cout << "UNSUPPORTED " << formula << ": " << e.what() << "\n";
          sva.clear();
          unsupported++;
          break;
        } catch (const std::exception &e) {
          // HARM cannot evaluate it (e.g. Spot's transition-based acceptance for F inside W)
          std::cout << "UNSUPPORTED " << formula << ": " << e.what() << "\n";
          sva.clear();
          unsupported++;
          break;
        }
      }
      if (sva.empty()) {
        sva = temp2String(ti->getTemplateFormula(), Language::SVA,
                          PrintMode::ShowAll);
      }
      for (size_t code = 0; code < ((size_t)1 << (3 * L)); code++) {
        for (size_t t = 0; t < L; t++) {
          for (size_t k = 0; k < 3; k++) {
            tr->getBooleanVariable(atoms[k])->assign(
                t, (bool)((code >> (t * 3 + k)) & 1));
          }
        }
        for (int m = 0; m < 2; m++) {
          TraceEnd te(m == 0 ? "harm" : "sva");
          verdicts[m] += ti->assHoldsOnTrace(Location::AntCon) ? '1' : '0';
        }
      }
    }
    if (sva.empty()) {
      continue;
    }
    out << formula << " ||| " << sva << " ||| " << verdicts[0] << " ||| "
        << verdicts[1] << "\n";
    n++;
  }
  // pre-existing HARM limitations (open finding, H1c): Spot automata that are not
  // deterministic, or have transition-based acceptance (some W nested in W), are rejected
  EXPECT_EQ(n + unsupported, 300u);
  EXPECT_LE(unsupported, 3u);
  std::cout << "[dump] formulas: " << n << ", unsupported by HARM: " << unsupported << "\n";
}
