// H1, acceptance tests A1 (literals and operators) and A3 ('.' hierarchy alias and identifier
// boundaries). Expected values are written by hand.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <string>
#include <tuple>
#include <vector>

#include "Logic.hh"
#include "PointerUtils.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

// name, width, value at each time step (MSB first, 4-valued)
using LogicVar = std::tuple<std::string, size_t, std::vector<std::string>>;

TracePtr makeTrace(const std::vector<LogicVar> &vars) {
  std::vector<VarDeclaration> decls;
  size_t length = 1;
  for (const auto &[name, width, values] : vars) {
    decls.emplace_back(name, ExpType::ULogic, width);
    length = std::max(length, values.size());
  }
  TracePtr trace = generatePtr<Trace>(decls, length);
  for (const auto &[name, width, values] : vars) {
    for (size_t t = 0; t < values.size(); t++) {
      trace->getLogicVariable(name)->assign(t, Logic(values[t], width));
    }
  }
  return trace;
}

// full-width, MSB-first 4-valued rendering (Logic::toString drops leading zeros)
std::string bits(const Logic &l) {
  std::string s;
  for (int i = (int)l._size - 1; i >= 0; i--) {
    if (boost::multiprecision::bit_test(l._x, i)) {
      s += 'x';
    } else if (boost::multiprecision::bit_test(l._z, i)) {
      s += 'z';
    } else {
      s += boost::multiprecision::bit_test(l._int, i) ? '1' : '0';
    }
  }
  return s;
}

// value of a logic expression at time t, or "PARSE ERROR: ..." (so that a missing feature fails
// one assertion instead of terminating the test binary)
std::string logicAt(const std::string &exp, const TracePtr &trace,
                    size_t t = 0) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    return bits(hparser::parseLogicExpression(exp, trace)->evaluate(t));
  } catch (const hlog::HarmError &e) {
    return std::string("PARSE ERROR: ") + e.what();
  }
}

// truth value of a proposition at time t: "1", "0" or "PARSE ERROR: ..."
std::string propAt(const std::string &exp, const TracePtr &trace,
                   size_t t = 0) {
  std::string error;
  PropositionPtr p = hparser::tryParseProposition(exp, trace, error);
  if (p == nullptr) {
    return "PARSE ERROR: " + error;
  }
  return p->evaluate(t) ? "1" : "0";
}

const TracePtr emptyTrace() { return makeTrace({}); }

} // namespace

// ---------------------------------------------------------------- A1: based and fill literals
TEST(PropositionLanguageTest, basedLiterals) {
  TracePtr tr = emptyTrace();
  EXPECT_EQ(logicAt("8'd9", tr), "00001001");
  EXPECT_EQ(logicAt("13'd100", tr), "0000001100100");
  EXPECT_EQ(logicAt("4'hA", tr), "1010");
  EXPECT_EQ(logicAt("4'ha", tr), "1010");
  EXPECT_EQ(logicAt("8'h1x", tr), "0001xxxx");
  EXPECT_EQ(logicAt("8'hz", tr), "zzzzzzzz"); // a leading x/z digit extends, as in SV
  EXPECT_EQ(logicAt("6'o7x", tr), "111xxx");
  EXPECT_EQ(logicAt("4'b1?0?", tr), "1z0z");
  EXPECT_EQ(logicAt("8'dx", tr), "xxxxxxxx");
  EXPECT_EQ(logicAt("4'd20", tr), "0100"); // truncated (warning), as in SV
  EXPECT_EQ(logicAt("'hF", tr),
            "00000000000000000000000000001111"); // unsized: 32 bits
  EXPECT_EQ(logicAt("'d3", tr), "00000000000000000000000000000011");
  // existing forms are unchanged
  EXPECT_EQ(logicAt("4'b1010", tr), "1010");
  EXPECT_EQ(logicAt("'b101", tr), "101");
}

TEST(PropositionLanguageTest, fillLiterals) {
  TracePtr tr = makeTrace({{"q4", 4, {"1111", "0000", "1x11", "zzzz"}}});
  EXPECT_EQ(propAt("q4 == '1", tr, 0), "1");
  EXPECT_EQ(propAt("q4 == '1", tr, 1), "0");
  EXPECT_EQ(propAt("q4 == '0", tr, 1), "1");
  EXPECT_EQ(propAt("q4 === 'z", tr, 3), "1");
  EXPECT_EQ(propAt("q4 === 'x", tr, 2), "0");
  EXPECT_EQ(propAt("q4 != '0", tr, 0), "1");
  // a fill literal without a sized context is an error
  EXPECT_EQ(propAt("'1 == '0", tr).rfind("PARSE ERROR", 0), 0u);
}

// ---------------------------------------------------------------- A1: new operators
TEST(PropositionLanguageTest, concatenationAndReplication) {
  TracePtr tr = makeTrace({{"q4", 4, {"10x1"}}, {"p1", 1, {"1"}}});
  EXPECT_EQ(logicAt("{4'b1010, 2'b0x}", tr), "10100x");
  EXPECT_EQ(logicAt("{2{2'b10}}", tr), "1010");
  EXPECT_EQ(logicAt("{1'b1, {2{1'b0}}}", tr), "100");
  EXPECT_EQ(logicAt("{q4, p1}", tr), "10x11");
  EXPECT_EQ(logicAt("{p1, {3{p1}}, q4}", tr), "111110x1");
  EXPECT_EQ(propAt("{q4, p1} === 5'b10x11", tr), "1");
  // inside {...} keeps working next to concatenation
  EXPECT_EQ(propAt("{p1, p1} inside {2'b11, 2'b00}", tr), "1");
}

TEST(PropositionLanguageTest, ternary) {
  TracePtr tr = makeTrace({{"q4", 4, {"0001", "0010"}},
                           {"r8", 8, {"10101010", "10101010"}}});
  EXPECT_EQ(logicAt("(q4 === 4'b0001) ? r8 : 8'hFF", tr, 0), "10101010");
  EXPECT_EQ(logicAt("(q4 === 4'b0001) ? r8 : 8'hFF", tr, 1), "11111111");
  EXPECT_EQ(propAt("(q4 == 4'd1) ? (r8 == 8'hAA) : (r8 == 8'h00)", tr, 0),
            "1");
  EXPECT_EQ(propAt("(q4 == 4'd1) ? (r8 == 8'hAA) : (r8 == 8'h00)", tr, 1),
            "0");
  // lowest precedence: a == b ? c : d means (a == b) ? c : d
  EXPECT_EQ(logicAt("q4 == 4'd2 ? 4'd7 : 4'd8", tr, 1), "0111");
}

TEST(PropositionLanguageTest, caseEquality) {
  TracePtr tr = makeTrace({{"q4", 4, {"1x0z", "1100"}}});
  EXPECT_EQ(propAt("q4 === 4'b1x0z", tr, 0), "1");
  EXPECT_EQ(propAt("q4 === 4'b1x00", tr, 0), "0");
  EXPECT_EQ(propAt("q4 !== 4'b1x0z", tr, 0), "0");
  EXPECT_EQ(propAt("q4 !== 4'b1100", tr, 1), "0");
  EXPECT_EQ(propAt("q4 === 4'b1100", tr, 1), "1");
  // documented HARM semantics (D-011): == with an x/z operand is false
  EXPECT_EQ(propAt("q4 == 4'b1x0z", tr, 0), "0");
}

TEST(PropositionLanguageTest, printParseRoundTrip) {
  TracePtr tr = makeTrace({{"q4", 4, {"1x01", "0110"}},
                           {"r8", 8, {"00001111", "11110000"}}});
  std::vector<std::string> props = {
      "{q4, 4'hF} === 8'b1x011111",
      "{2{q4}} != 8'd0",
      "(q4 === 4'b0110 ? r8 : 8'hAA) == 8'hF0",
      "r8 !== '0",
      "q4 inside {4'd6, [4'd8:4'd9]}",
  };
  for (const auto &s : props) {
    std::string error;
    PropositionPtr p = hparser::tryParseProposition(s, tr, error);
    ASSERT_NE(p, nullptr) << s << ": " << error;
    std::string printed = prop2String(p);
    PropositionPtr q = hparser::tryParseProposition(printed, tr, error);
    ASSERT_NE(q, nullptr) << "re-parsing '" << printed << "': " << error;
    for (size_t t = 0; t < 2; t++) {
      EXPECT_EQ(p->evaluate(t), q->evaluate(t)) << s << " vs " << printed;
    }
  }
}

// ---------------------------------------------------------------- A3: '.' alias, boundaries
TEST(PropositionLanguageTest, dottedHierarchyAlias) {
  TracePtr tr = makeTrace({{"u_core::state", 2, {"10", "01"}},
                           {"u_core::state_next", 2, {"01", "10"}}});
  for (size_t t = 0; t < 2; t++) {
    EXPECT_EQ(propAt("u_core.state == 2'b10", tr, t),
              propAt("u_core::state == 2'b10", tr, t));
    EXPECT_EQ(propAt("u_core.state_next == u_core::state", tr, t),
              propAt("u_core::state_next == u_core::state", tr, t));
  }
  EXPECT_EQ(propAt("u_core.state == 2'b10", tr, 0), "1");
}

TEST(PropositionLanguageTest, substitutionRespectsIdentifierBoundaries) {
  TracePtr tr = makeTrace({{"a", 4, {"1010"}},
                           {"x", 3, {"100"}},
                           {"b1", 8, {"10110001"}},
                           {"h", 1, {"1"}}});
  EXPECT_EQ(propAt("x == 3'b1x0", tr), "0");  // 'x' inside the literal is not the variable
  EXPECT_EQ(propAt("x === 3'b100", tr), "1");
  EXPECT_EQ(propAt("a == 0xa", tr), "1");     // existing hex int constant
  EXPECT_EQ(propAt("a == 4'ha", tr), "1");
  EXPECT_EQ(propAt("b1 == 8'hb1", tr), "1");
  EXPECT_EQ(propAt("h == 1'h1 && a == 4'd10", tr), "1");
}

// F10 (found in H1): copying a bit selection swapped its bounds, so mined assertions printed
// r[4:7] for r[7:4]
TEST(PropositionLanguageTest, bitSelectionSurvivesCopy) {
  TracePtr tr = makeTrace({{"r", 8, {"10110001", "01000001"}}});
  std::string error;
  PropositionPtr p =
      hparser::tryParseProposition("r[7:4] == 4'b1011", tr, error);
  ASSERT_NE(p, nullptr) << error;
  PropositionPtr c = copy(p);
  EXPECT_EQ(prop2String(c), prop2String(p));
  EXPECT_NE(prop2String(c).find("r[7:4]"), std::string::npos)
      << prop2String(c);
  for (size_t t = 0; t < 2; t++) {
    EXPECT_EQ(c->evaluate(t), p->evaluate(t));
  }
}
