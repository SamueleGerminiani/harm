// H18, acceptance tests A4 (hand cases) and A5 (Z3 against enumeration), D-034: operators bind and
// convert as in C and SystemVerilog (IEEE 1800-2017 Table 11-2, 11.4.4, 11.4.7, 11.8.1; C11 6.5).
// Expected values: worked out by hand in the comments, then recomputed by a script that spells out each
// grouping (the comments of some rows are abbreviated); a numeric '!' is 2-valued (the user's choice).
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <map>
#include <string>
#include <vector>

#include "Logic.hh"
#include "PointerUtils.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "expUtils/smtEquivalence.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

// one row of values: ints x, y, k; bools a, b, c; logic [3:0] q, v (v may hold x)
struct Vals {
  long x, y, k;
  bool a, b, c;
  std::string q, v;
};

TracePtr makeTrace(const std::vector<Vals> &rows) {
  std::vector<VarDeclaration> decls = {
      {"x", ExpType::SInt, 32}, {"y", ExpType::SInt, 32}, {"k", ExpType::SInt, 32},
      {"a", ExpType::Bool, 1},  {"b", ExpType::Bool, 1},  {"c", ExpType::Bool, 1},
      {"q", ExpType::ULogic, 4}, {"v", ExpType::ULogic, 4}};
  TracePtr tr = generatePtr<Trace>(decls, rows.size());
  for (size_t t = 0; t < rows.size(); t++) {
    tr->getIntVariable("x")->assign(t, rows[t].x);
    tr->getIntVariable("y")->assign(t, rows[t].y);
    tr->getIntVariable("k")->assign(t, rows[t].k);
    tr->getBooleanVariable("a")->assign(t, rows[t].a);
    tr->getBooleanVariable("b")->assign(t, rows[t].b);
    tr->getBooleanVariable("c")->assign(t, rows[t].c);
    tr->getLogicVariable("q")->assign(t, Logic(rows[t].q, 4));
    tr->getLogicVariable("v")->assign(t, Logic(rows[t].v, 4));
  }
  return tr;
}

// the value of exp on each row, as "0"/"1", or "ERROR: ..."
std::string values(const std::string &exp, const TracePtr &tr, size_t n) {
  std::string error;
  PropositionPtr p = hparser::tryParseProposition(exp, tr, error);
  if (p == nullptr) {
    return "ERROR: " + error;
  }
  std::string s;
  for (size_t t = 0; t < n; t++) {
    s += p->evaluate(t) ? '1' : '0';
  }
  return s;
}

std::string printed(const std::string &exp, const TracePtr &tr) {
  std::string error;
  PropositionPtr p = hparser::tryParseProposition(exp, tr, error);
  return p == nullptr ? "ERROR: " + error : prop2String(p);
}

} // namespace

// ---------------------------------------------------------------- A4: precedence, hand values
TEST(OperatorPrecedenceTest, handValues) {
  // rows:            x  y  k  a  b  c  q       v
  std::vector<Vals> rows = {{0, 1, 2, 0, 0, 0, "0001", "0000"},
                            {0, 2, 1, 0, 1, 1, "0101", "00x0"},
                            {2, 0, 2, 1, 0, 1, "1000", "0010"},
                            {2, 2, 0, 1, 1, 0, "1111", "x000"},
                            {1, 3, 1, 1, 0, 0, "0011", "0001"},
                            {5, 2, 1, 0, 1, 0, "0110", "1x00"}};
  TracePtr tr = makeTrace(rows);
  const size_t n = rows.size();
  const std::map<std::string, std::string> expected = {
      // P1 (!x) == y: rows (!0)==1 1; (!0)==2 0; (!2)==0 1; (!2)==2 0; (!1)==3 0; (!5)==2 0
      {"!x == y", "101000"},
      // (!x) < y: 1<1 0; 1<2 1; 0<0 0; 0<2 1; 0<3 1; 0<2 1
      {"!x < y", "010111"},
      // (!x) + y == 2: 2,3,0,2,3,2 -> 1 0 0 1 0 1
      {"!x + y == 2", "100101"},
      // P2 x & (y == y): x & 1 -> 0,0,0,0,1,1
      {"x & y == y", "000011"},
      // (x < y) & k: (0<1)&2=0; (0<2)&1=1; (2<0)&2=0; (2<2)&0=0; (1<3)&1=1; (5<2)&1=0
      {"x < y & k", "010010"},
      // (x == y) | k: (0==1)|2 ->2 1; 0|1 1; 0|2 1; (2==2)|0 1; 0|1 1; 0|1 1
      {"x == y | k", "111111"},
      // P3 (x > 0) == y: 0==1 0; 0==2 0; 1==0 0; 1==2 0; 1==3 0; 1==2 0
      {"(x > 0) == y", "000000"},
      // (x > 0) != y: 1 1 1 1 1 1
      {"(x > 0) != y", "111111"},
      // (x < y) < k: (0<1)<2 1; (0<2)<1 0; (2<0)<2 1; (2<2)<0 0; (1<3)<1 0; (5<2)<1 1
      {"x < y < k", "101001"},
      // (x == y) == k: (0==1)==2 0; 0==1 0; 0==2 0; (2==2)==0 0; 0==1 0; 0==1 0
      {"x == y == k", "000000"},
      // (x < y) + 1 == 2: x<y: 1 1 0 0 1 0
      {"(x < y) + 1 == 2", "110010"},
      // P4 (x >> 1) << k == x: 0<<2=0 ==0 1; 0<<1 ==0 1; 1<<2=4==2 0; 1<<0=1==2 0; 0<<1==1 0; 2<<1=4==5 0
      {"x >> 1 << k == x", "110000"},
      // Boolean != and == on one level: (a != b) == c: (0!=0)==0 1; (0!=1)==1 1; (1!=0)==1 1;
      // (1!=1)==0 1; (1!=0)==0 0; (0!=1)==0 0
      {"a != b == c", "111100"},
      // L1 x-1 == 4 only when x == 5
      {"x-1 == 4", "000001"},
      {"x - 1 == 4", "000001"},
      // L2 unary minus and plus
      {"-x == 0 - x", "111111"},
      {"-x + y == 1", "100000"},
      {"+x == x", "111111"},
      // L3 bools as 1-bit numbers: a + a == 2 when a; a < y: 0<1 1; 0<2 1; 1<0 0; 1<2 1; 1<3 1; 0<2 1
      {"a + a == 2", "001110"},
      {"a < y", "110111"},
      // Q2 a bool compared with a number: a == x: 0==0 1; 0==0 1; 1==2 0; 1==2 0; 1==1 1; 0==5 0
      {"a == x", "110010"},
      // H17's forms, now with C/SV precedence: (!a) ^ b; (a && b) ^ c; (a) ^ b
      {"!a ^ b", "100100"},
      {"(a && b) ^ c", "011100"},
      {"(a) ^ b", "011011"},
      // Q1 (b): a numeric ! is 2-valued: !v true where v has no known 1 (00x0 too)
      {"!v", "110100"},
      {"(!v) == 1'b1", "110100"},
      // a select binds tighter than a prefix operator: !(q[0])
      {"!q[0]", "001001"},
      // unchanged readings
      {"!a && b", "010001"},
      {"!(x == y)", "111011"},
      {"!(a)", "110001"},
      {"c && !(a)", "010000"},
      {"!x", "110000"},
      {"a == b", "100100"},
  };
  for (const auto &[exp, want] : expected) {
    EXPECT_EQ(values(exp, tr, n), want) << exp;
  }
}

// ---------------------------------------------------------------- A3, A4: printing re-parses
TEST(OperatorPrecedenceTest, printingKeepsTheMeaning) {
  // shift amounts stay below 32 (a larger one stops HARM: finding E1, H19)
  std::vector<Vals> rows = {{5, 3, 1, 0, 1, 0, "0101", "0000"}, {2, 9, 1, 1, 1, 1, "1111", "0001"},
                            {7, 1, 2, 1, 0, 1, "0011", "0010"}};
  TracePtr tr = makeTrace(rows);
  const std::map<std::string, std::string> expected = {
      {"x - (y - k) == 3", "x - (y - k) == 3"},
      {"x / (y * k) == 0", "x / (y * k) == 0"},
      {"(x + y)[1:0] == 2'b0", "(x + y)[1:0] == 2'b0"},
      {"(!x) == y", "!x == y"},
      {"!(x == y)", "!(x == y)"},
      {"!(q inside {1, 5})", "!(q inside {1,5})"},
      {"q inside {5, 1}", "q inside {5,1}"},
      {"(x >> y) << k == 0", "x >> y << k == 0"},
      {"x >> (y << k) == 0", "x >> (y << k) == 0"},
      {"(x & y) == y", "(x & y) == y"},
      {"x & (y == y)", "x & y == y"},
      {"(a != b) == c", "a != b == c"},
      {"a != (b == c)", "a != (b == c)"},
  };
  for (const auto &[exp, want] : expected) {
    std::string text = printed(exp, tr);
    EXPECT_EQ(text, want) << exp;
    EXPECT_EQ(values(text, tr, rows.size()), values(exp, tr, rows.size())) << exp << " -> " << text;
    EXPECT_EQ(printed(text, tr), text) << exp;
  }
}

// ---------------------------------------------------------------- A5: Z3 against enumeration
TEST(OperatorPrecedenceTest, z3AgreesWithEnumeration) {
  if (!smt::available()) {
    GTEST_SKIP() << "built without Z3";
  }
  // every assignment of 2-bit p, r and bool a (as 4-bit q, v with the top bits 0 and a few ints)
  std::vector<Vals> rows;
  for (int p = 0; p < 4; p++) {
    for (int r = 0; r < 4; r++) {
      for (int a = 0; a < 2; a++) {
        std::string qs = std::string("00") + char('0' + (p >> 1)) + char('0' + (p & 1));
        std::string vs = std::string("00") + char('0' + (r >> 1)) + char('0' + (r & 1));
        rows.push_back({p - 1, r - 1, p + r, bool(a), bool(p & 1), bool(r & 1), qs, vs});
      }
    }
  }
  TracePtr tr = makeTrace(rows);
  const std::vector<std::pair<std::string, std::string>> pairs = {
      {"!q == v", "q == 4'd0 && v == 4'd1 || q != 4'd0 && v == 4'd0"},
      {"(q > 4'd1) == v", "q > 4'd1 && v == 4'd1 || q <= 4'd1 && v == 4'd0"},
      {"q & v == v", "q[0] == 1'b1"},
      {"a == q", "a && q == 4'd1 || !a && q == 4'd0"},
      {"a + a == q", "a && q == 4'd2 || !a && q == 4'd0"},
      {"q < v < q", "q < v && q > 4'd1 || q >= v && q > 4'd0"},
      {"!q == v", "q == v"},
  };
  for (const auto &[x, y] : pairs) {
    std::string error;
    PropositionPtr px = hparser::tryParseProposition(x, tr, error);
    ASSERT_NE(px, nullptr) << x << ": " << error;
    PropositionPtr py = hparser::tryParseProposition(y, tr, error);
    ASSERT_NE(py, nullptr) << y << ": " << error;
    bool same = true;
    for (size_t t = 0; t < rows.size(); t++) {
      same = same && px->evaluate(t) == py->evaluate(t);
    }
    EXPECT_EQ(smt::checkEquivalence(px, py),
              same ? smt::Equivalence::Equivalent : smt::Equivalence::NotEquivalent)
        << x << " vs " << y;
  }
}
