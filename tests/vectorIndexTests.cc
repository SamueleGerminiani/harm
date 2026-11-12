// H11c, D-028: vector bit and part selects follow SystemVerilog for variables with a declared
// range (from the VCD: [1:10], [10:3], [7:0], [0:0]).
// A3b: the expected values are printed by Verilator from the same trace (tests/input/h11c/gen.sh),
// so they are independent of HARM. A3/A3c: errors and printing, written by hand.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Logic.hh"
#include "Trace.hh"
#include "VCDtraceReader.hh"
#include "expUtils/expUtils.hh"
#include "globals.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

const char *kTrace = "../tests/input/h11c/ranges.vcd";
const char *kExpected = "../tests/input/h11c/expected.txt";

TracePtr readRanges() {
  VCDTraceReaderConfig cfg;
  cfg._clk = "clk";
  cfg._selectedScope = "tb";
  cfg._vcdRecursive = 0;
  static TraceReader *reader = nullptr; // keeps the trace alive for the whole test binary
  static TracePtr trace = nullptr;
  if (trace == nullptr) {
    reader = new VCDtraceReader(kTrace, cfg);
    trace = reader->readTrace();
  }
  return trace;
}

// full-width, MSB-first rendering (Logic::toString drops leading zeros)
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

std::string logicAt(const std::string &exp, const TracePtr &trace, size_t t) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    return bits(hparser::parseLogicExpression(exp, trace)->evaluate(t));
  } catch (const hlog::HarmError &e) {
    return std::string("PARSE ERROR: ") + e.what();
  }
}

bool parses(const std::string &exp, const TracePtr &trace) {
  std::string error;
  return hparser::tryParseProposition(exp, trace, error) != nullptr;
}

// expected.txt: "CYC <n> sel=bits sel=bits ..."
std::vector<std::map<std::string, std::string>> expected() {
  std::vector<std::map<std::string, std::string>> rows;
  std::ifstream in(kExpected);
  std::string line;
  while (std::getline(in, line)) {
    std::istringstream ss(line);
    std::string tag, cyc, item;
    ss >> tag >> cyc;
    std::map<std::string, std::string> row;
    while (ss >> item) {
      size_t eq = item.find('=');
      row[item.substr(0, eq)] = item.substr(eq + 1);
    }
    rows.push_back(row);
  }
  return rows;
}

} // namespace

// A3b: every select, every cycle, as Verilator computes it
TEST(VectorIndexTest, selectsMatchVerilator) {
  TracePtr tr = readRanges();
  auto rows = expected();
  ASSERT_EQ(rows.size(), 41u);
  ASSERT_GE(tr->getLength(), rows.size());
  for (size_t t = 0; t < rows.size(); t++) {
    for (const auto &[sel, value] : rows[t]) {
      EXPECT_EQ(logicAt(sel, tr, t), value) << sel << " at cycle " << t;
    }
  }
}

// A3: outside the declared range, or against its direction, is an error (as in SystemVerilog)
TEST(VectorIndexTest, outOfRangeAndWrongDirectionAreErrors) {
  TracePtr tr = readRanges();
  EXPECT_FALSE(parses("asc[0] == 1'b1", tr));    // [1:10]
  EXPECT_FALSE(parses("asc[11] == 1'b1", tr));
  EXPECT_FALSE(parses("off[2] == 1'b1", tr));    // [10:3]
  EXPECT_FALSE(parses("off[11] == 1'b1", tr));
  EXPECT_FALSE(parses("asc[6:3] == 4'b0", tr));  // ascending vector, descending select
  EXPECT_FALSE(parses("off[3:6] == 4'b0", tr));  // descending vector, ascending select
  EXPECT_FALSE(parses("d[2:5] == 4'b0", tr));    // [7:0]: also SystemVerilog rules
  // in range and in the declared direction
  EXPECT_TRUE(parses("asc[1] == 1'b1", tr));
  EXPECT_TRUE(parses("asc[10] == 1'b1", tr));
  EXPECT_TRUE(parses("off[3] == 1'b1", tr));
  EXPECT_TRUE(parses("off[10:7] == 4'b0", tr));
  EXPECT_TRUE(parses("one[0] == 1'b1", tr));
}

// A3c: the printed proposition keeps the SystemVerilog indices it was written with
TEST(VectorIndexTest, printingKeepsSourceIndices) {
  TracePtr tr = readRanges();
  for (const std::string &sel :
       {"asc[2]", "asc[3:6]", "off[3]", "off[6:3]", "d[5:2]", "one[0]"}) {
    std::string error;
    PropositionPtr p =
        hparser::tryParseProposition(sel + " == 1'b1", tr, error);
    ASSERT_NE(p, nullptr) << sel << ": " << error;
    EXPECT_NE(prop2String(p).find(sel), std::string::npos)
        << sel << " printed as " << prop2String(p);
    EXPECT_EQ(prop2String(copy(p)), prop2String(p)) << sel;
  }
}

// [n:0] vectors: the same bits as before D-028
TEST(VectorIndexTest, usualRangeUnchanged) {
  TracePtr tr = readRanges();
  auto rows = expected();
  for (size_t t = 0; t < rows.size(); t++) {
    std::string d = logicAt("d", tr, t);
    EXPECT_EQ(logicAt("d[7:0]", tr, t), d);
    EXPECT_EQ(logicAt("d[0]", tr, t), d.substr(7, 1));
  }
}
