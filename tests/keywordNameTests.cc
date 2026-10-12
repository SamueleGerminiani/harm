// H23, tests R3 and R4 (D-037): variables whose names are HARM keywords. Declaring one is not an
// error; a formula names it with SystemVerilog's escaped identifier ('\W '); a bare keyword keeps
// its meaning. Oracles: a formula prints the same whether or not the trace has keyword-named
// variables, and an escaped name prints like an ordinary one (written by hand, not from HARM).
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <string>
#include <vector>

#include "PointerUtils.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "globals.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

// HARM's keywords that are legal SystemVerilog names, the grammar's one-letter operators, and the
// constants true/false
const std::vector<std::string> keywordNames = {"W", "X", "G", "F", "R", "next", "substr", "true", "false"};

// Bool variables a, b, c and the keyword-named ones; variable i is 1 at time t iff
// (t * 37 + i * 11) % 5 < 2, so that the variables differ from each other
TracePtr makeTrace(bool withKeywords) {
  std::vector<std::string> names = {"a", "b", "c"};
  if (withKeywords) {
    names.insert(names.end(), keywordNames.begin(), keywordNames.end());
  }
  std::vector<VarDeclaration> vars;
  for (const auto &n : names) {
    vars.emplace_back(n, ExpType::Bool, 1);
  }
  TracePtr tr = generatePtr<Trace>(vars, 16);
  for (size_t i = 0; i < names.size(); i++) {
    for (size_t t = 0; t < 16; t++) {
      tr->getBooleanVariable(names[i])->assign(t, (t * 37 + i * 11) % 5 < 2);
    }
  }
  return tr;
}

bool valueOf(const TracePtr &tr, const std::string &name, size_t t) {
  return tr->getBooleanVariable(name)->evaluate(t);
}

// "1", "0" or "PARSE ERROR: ..." (a missing feature fails one expectation, not the binary)
std::string propAt(const std::string &exp, const TracePtr &trace, size_t t) {
  hlog::ScopedThrowOnError throwOnError;
  std::string error;
  PropositionPtr p = hparser::tryParseProposition(exp, trace, error);
  if (p == nullptr) {
    return "PARSE ERROR: " + error;
  }
  return p->evaluate(t) ? "1" : "0";
}

std::string print(const std::string &assertion, const TracePtr &trace, Language lang) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    auto te = hparser::parseTemporalExpression(assertion, trace);
    return temp2String(te, lang, PrintMode::ShowAll);
  } catch (const hlog::HarmError &e) {
    return std::string("PARSE ERROR: ") + e.what();
  }
}

std::string sva(const std::string &assertion, const TracePtr &trace) {
  return print(assertion, trace, Language::SVA);
}

void replaceAll(std::string &s, const std::string &from, const std::string &to) {
  for (size_t p = s.find(from); p != std::string::npos; p = s.find(from, p + to.size())) {
    s.replace(p, from.size(), to);
  }
}

} // namespace

// R3: a trace with keyword-named variables can be parsed against at all
TEST(KeywordNameTest, declaringIsNotAnError) {
  TracePtr tr = makeTrace(true);
  for (size_t t = 0; t < 16; t++) {
    EXPECT_EQ(propAt("a && !b", tr, t), (valueOf(tr, "a", t) && !valueOf(tr, "b", t)) ? "1" : "0");
  }
}

// R3: '\name ' is the variable, in a proposition, for every keyword name
TEST(KeywordNameTest, escapedIsTheVariable) {
  TracePtr tr = makeTrace(true);
  for (const auto &n : keywordNames) {
    for (size_t t = 0; t < 16; t++) {
      EXPECT_EQ(propAt("\\" + n + " ", tr, t), valueOf(tr, n, t) ? "1" : "0") << n << " at " << t;
      EXPECT_EQ(propAt("(\\" + n + " && a)", tr, t), valueOf(tr, n, t) && valueOf(tr, "a", t) ? "1" : "0")
          << n << " at " << t;
    }
  }
}

// R3: a bare keyword keeps its meaning: true and false stay constants
TEST(KeywordNameTest, bareTrueFalseAreConstants) {
  TracePtr tr = makeTrace(true);
  for (size_t t = 0; t < 16; t++) {
    EXPECT_EQ(propAt("true", tr, t), "1");
    EXPECT_EQ(propAt("false", tr, t), "0");
  }
}

// R3: a bare name that is only a variable here (not an operator in a proposition) is an error that
// names the escape
TEST(KeywordNameTest, bareKeywordVariableNamesTheEscape) {
  TracePtr tr = makeTrace(true);
  std::string r = propAt("next && a", tr, 0);
  EXPECT_NE(r.find("PARSE ERROR"), std::string::npos) << r;
  EXPECT_NE(r.find("\\next "), std::string::npos) << r;
}

// R3: the temporal operators read the same with or without variables named after them
TEST(KeywordNameTest, operatorsUnchanged) {
  TracePtr plain = makeTrace(false), kw = makeTrace(true);
  for (const std::string f : {"G(a -> X b)", "G(a -> X X b)", "G(a -> F b)", "G(a -> (b until c))",
                              "G(a -> (b W c))", "G(a -> (b R c))", "G(a -> next b)",
                              "always (a ##1 b |-> nexttime c)"}) {
    std::string expected = sva(f, plain);
    ASSERT_EQ(expected.find("PARSE ERROR"), std::string::npos) << f << ": " << expected;
    EXPECT_EQ(sva(f, kw), expected) << f;
  }
}

// R3 and R4: operators and escaped variables together; SVA prints the plain name
TEST(KeywordNameTest, mixedAndPrintedPlain) {
  TracePtr plain = makeTrace(false), kw = makeTrace(true);
  std::string expected = sva("G(a -> X b)", plain); // b stands for X, the variable
  replaceAll(expected, "b", "X");
  EXPECT_EQ(sva("G(a -> X \\X )", kw), expected);
  expected = sva("G((a && c) -> (b until a))", plain); // c for W, b for next
  replaceAll(expected, "c", "W");
  replaceAll(expected, "b", "next");
  EXPECT_EQ(sva("G((a && \\W ) -> (\\next  until a))", kw), expected);
}

// R4: HARM's own syntax prints the escape, and reading it back gives the same assertion
TEST(KeywordNameTest, roundTrip) {
  TracePtr tr = makeTrace(true);
  for (const std::string f : {"G((a && \\W ) -> X \\X )", "G(\\G  -> F \\F )", "G((\\R  || \\substr ) -> (\\next  until \\true ))"}) {
    std::string own = print(f, tr, Language::SpotLTL);
    ASSERT_EQ(own.find("PARSE ERROR"), std::string::npos) << f << ": " << own;
    EXPECT_EQ(sva(own, tr), sva(f, tr)) << f << " printed as " << own;
  }
}
