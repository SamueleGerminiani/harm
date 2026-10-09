// H17, acceptance tests A1 and A2 (D-032): bitwise operators with bool operands (CSV 'bool').
// The reference semantics are written here, independently of HARM: a bool is a 1-bit unsigned
// value (SystemVerilog), zero-extended against wider operands; the result is true where some bit
// is a known 1 (D-011).
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <functional>
#include <string>
#include <vector>

#include "Logic.hh"
#include "PointerUtils.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "expUtils/smtEquivalence.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

// one row: bools a, b, c; p a 1-bit logic ('0', '1', 'x'); v a 4-bit logic
struct BitRow {
  bool a, b, c;
  char p;
  std::string v;
};

const std::vector<std::string> vValues = {"0000", "0001", "0011", "1000", "00x0", "00x1"};

std::vector<BitRow> allRows() {
  std::vector<BitRow> rows;
  for (int abc = 0; abc < 8; abc++) {
    for (char p : std::string("01x")) {
      for (const auto &v : vValues) {
        rows.push_back({bool(abc & 4), bool(abc & 2), bool(abc & 1), p, v});
      }
    }
  }
  return rows;
}

TracePtr makeTrace(const std::vector<BitRow> &rows) {
  std::vector<VarDeclaration> decls = {{"a", ExpType::Bool, 1},
                                       {"b", ExpType::Bool, 1},
                                       {"c", ExpType::Bool, 1},
                                       {"p", ExpType::ULogic, 1},
                                       {"v", ExpType::ULogic, 4}};
  TracePtr tr = generatePtr<Trace>(decls, rows.size());
  for (size_t t = 0; t < rows.size(); t++) {
    tr->getBooleanVariable("a")->assign(t, rows[t].a);
    tr->getBooleanVariable("b")->assign(t, rows[t].b);
    tr->getBooleanVariable("c")->assign(t, rows[t].c);
    tr->getLogicVariable("p")->assign(t, Logic(std::string(1, rows[t].p), 1));
    tr->getLogicVariable("v")->assign(t, Logic(rows[t].v, 4));
  }
  return tr;
}

// ---- reference: 4-valued bits, most significant first
using Bits = std::string;
Bits bit(bool x) { return x ? "1" : "0"; }
Bits ext(const Bits &x, size_t w) { return std::string(w - x.size(), '0') + x; }
char bxor(char x, char y) { return (x == 'x' || y == 'x') ? 'x' : (x != y ? '1' : '0'); }
char band(char x, char y) {
  if (x == '0' || y == '0') return '0';
  return (x == 'x' || y == 'x') ? 'x' : '1';
}
char bor(char x, char y) {
  if (x == '1' || y == '1') return '1';
  return (x == 'x' || y == 'x') ? 'x' : '0';
}
Bits op(const Bits &x, const Bits &y, char (*f)(char, char)) {
  size_t w = std::max(x.size(), y.size());
  Bits xe = ext(x, w), ye = ext(y, w), r;
  for (size_t i = 0; i < w; i++) r += f(xe[i], ye[i]);
  return r;
}
Bits bnot(const Bits &x) {
  Bits r;
  for (char ch : x) r += ch == 'x' ? 'x' : (ch == '1' ? '0' : '1');
  return r;
}
bool truth(const Bits &x) { return x.find('1') != std::string::npos; }

struct Case {
  std::string exp;
  std::function<bool(const BitRow &)> ref;
};

const std::vector<Case> cases = {
    {"a ^ b", [](const BitRow &r) { return truth(op(bit(r.a), bit(r.b), bxor)); }},
    {"a & b", [](const BitRow &r) { return truth(op(bit(r.a), bit(r.b), band)); }},
    {"a | b", [](const BitRow &r) { return truth(op(bit(r.a), bit(r.b), bor)); }},
    {"~a", [](const BitRow &r) { return truth(bnot(bit(r.a))); }},
    {"~a ^ b", [](const BitRow &r) { return truth(op(bnot(bit(r.a)), bit(r.b), bxor)); }},
    {"a ^ b ^ c", [](const BitRow &r) { return truth(op(op(bit(r.a), bit(r.b), bxor), bit(r.c), bxor)); }},
    // SystemVerilog: & binds tighter than ^, which binds tighter than |
    {"a & b | c", [](const BitRow &r) { return truth(op(op(bit(r.a), bit(r.b), band), bit(r.c), bor)); }},
    {"a | b & c", [](const BitRow &r) { return truth(op(bit(r.a), op(bit(r.b), bit(r.c), band), bor)); }},
    {"a ^ b & c", [](const BitRow &r) { return truth(op(bit(r.a), op(bit(r.b), bit(r.c), band), bxor)); }},
    {"a ^ p", [](const BitRow &r) { return truth(op(bit(r.a), std::string(1, r.p), bxor)); }},
    {"p & a", [](const BitRow &r) { return truth(op(std::string(1, r.p), bit(r.a), band)); }},
    {"a ^ v", [](const BitRow &r) { return truth(op(bit(r.a), r.v, bxor)); }},
    {"a & v", [](const BitRow &r) { return truth(op(bit(r.a), r.v, band)); }},
    {"v | b", [](const BitRow &r) { return truth(op(r.v, bit(r.b), bor)); }},
};

PropositionPtr parse(const std::string &exp, const TracePtr &tr) {
  std::string error;
  PropositionPtr p = hparser::tryParseProposition(exp, tr, error);
  EXPECT_NE(p, nullptr) << exp << ": " << error;
  return p;
}

} // namespace

// ---------------------------------------------------------------- A1: values
TEST(BitwiseBoolTest, valuesEqualTheReference) {
  auto rows = allRows();
  TracePtr tr = makeTrace(rows);
  for (const auto &c : cases) {
    PropositionPtr p = parse(c.exp, tr);
    if (p == nullptr) continue;
    for (size_t t = 0; t < rows.size(); t++) {
      EXPECT_EQ(p->evaluate(t), c.ref(rows[t]))
          << c.exp << " at a=" << rows[t].a << " b=" << rows[t].b << " c=" << rows[t].c
          << " p=" << rows[t].p << " v=" << rows[t].v;
    }
  }
}

// ---------------------------------------------------------------- A2: text
TEST(BitwiseBoolTest, printsAsWrittenAndReparses) {
  auto rows = allRows();
  TracePtr tr = makeTrace(rows);
  for (const auto &c : cases) {
    PropositionPtr p = parse(c.exp, tr);
    if (p == nullptr) continue;
    std::string spot = prop2String(p);
    EXPECT_EQ(spot, c.exp);
    PropositionPtr again = parse(spot, tr);
    if (again == nullptr) continue;
    for (size_t t = 0; t < rows.size(); t++) {
      EXPECT_EQ(again->evaluate(t), p->evaluate(t)) << spot << " at " << t;
    }
  }
}

TEST(BitwiseBoolTest, inTemplatesAndSva) {
  auto rows = allRows();
  TracePtr tr = makeTrace(rows);
  hlog::ScopedThrowOnError throwOnError;
  for (std::string exp : {"a ^ b", "~a ^ b", "a ^ v"}) {
    TemplateImplicationPtr ti;
    ASSERT_NO_THROW(ti = hparser::parseTemplateImplication("G(" + exp + " -> c)", tr,
                                                          DTLimits(), false))
        << exp;
    EXPECT_EQ(temp2String(ti->getTemplateFormula(), Language::SVA, PrintMode::ShowAll),
              "always (" + exp + " |-> c)");
    EXPECT_EQ(temp2String(ti->getTemplateFormula(), Language::SpotLTL, PrintMode::ShowAll),
              "G(" + exp + " -> c)");
    // the verdict, from the reference
    bool holds = true;
    const Case *c = nullptr;
    for (const auto &k : cases) {
      if (k.exp == exp) c = &k;
    }
    for (const auto &r : rows) {
      holds = holds && (!c->ref(r) || r.c);
    }
    EXPECT_EQ(ti->assHoldsOnTrace(Location::AntCon), holds) << exp;
  }
}

TEST(BitwiseBoolTest, notAtomsStillRejected) {
  TracePtr tr = makeTrace(allRows());
  for (std::string exp : {"(a && b) ^ c", "!a ^ b", "(a) ^ b"}) {
    std::string error;
    EXPECT_EQ(hparser::tryParseProposition(exp, tr, error), nullptr) << exp;
    EXPECT_FALSE(error.empty()) << exp;
  }
  // what worked before is unchanged
  for (std::string exp : {"a == b", "a != b", "a && b || c", "!a", "{a, p} == 2'b10"}) {
    std::string error;
    PropositionPtr p = hparser::tryParseProposition(exp, tr, error);
    ASSERT_NE(p, nullptr) << exp << ": " << error;
  }
  EXPECT_EQ(prop2String(parse("{a, p} == 2'b10", tr)), "{(a ? 1'b1 : 1'b0), p} == 2'b10");
}

// ---------------------------------------------------------------- A2: Z3, against brute force
TEST(BitwiseBoolTest, z3AgreesWithEnumeration) {
  if (!smt::available()) {
    GTEST_SKIP() << "built without Z3";
  }
  // all assignments of the bools (p and v fixed to known values: Z3 is 2-valued, D-003)
  std::vector<BitRow> rows;
  for (int abc = 0; abc < 8; abc++) {
    rows.push_back({bool(abc & 4), bool(abc & 2), bool(abc & 1), '0', "0000"});
  }
  TracePtr tr = makeTrace(rows);
  const std::vector<std::pair<std::string, std::string>> pairs = {
      {"a ^ b", "a != b"}, {"a & b", "a && b"}, {"a | b", "a || b"},
      {"~a", "!a"},       {"a ^ b", "a | b"}, {"a & b | c", "a && b || c"},
      {"a ^ b ^ c", "a != (b != c)"}};
  for (const auto &[x, y] : pairs) {
    PropositionPtr px = parse(x, tr), py = parse(y, tr);
    if (px == nullptr || py == nullptr) continue;
    bool same = true;
    for (size_t t = 0; t < rows.size(); t++) {
      same = same && px->evaluate(t) == py->evaluate(t);
    }
    smt::Equivalence e = smt::checkEquivalence(px, py);
    EXPECT_EQ(e, same ? smt::Equivalence::Equivalent : smt::Equivalence::NotEquivalent)
        << x << " vs " << y;
  }
}
