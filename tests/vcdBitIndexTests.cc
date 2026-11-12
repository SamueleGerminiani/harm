// H38: a 1-bit variable declared with a nonzero index ($var wire 1 # hi [1:1] $end, as Verilator dumps
// `wire [1:1] hi`) is read as a vector of range [k:k]; HARM aborted on it (VCDParser: "!((new_signal->lindex == -1)
// || (new_signal->rindex == -1))"), which stopped every HARM arm of the miner portfolio on AssertLLM2's pci_bridge and
// rtftextcontroller. Values written by hand in tests/input/h38/bit_index.vcd (sampled on clk's rising edges).
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <string>

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

TracePtr readBits() {
  VCDTraceReaderConfig cfg;
  cfg._clk = "clk";
  cfg._selectedScope = "tb";
  cfg._vcdRecursive = 0;
  static TraceReader *reader = nullptr;
  static TracePtr trace = nullptr;
  if (trace == nullptr) {
    reader = new VCDtraceReader("../tests/input/h38/bit_index.vcd", cfg);
    trace = reader->readTrace();
  }
  return trace;
}

std::string at(const std::string &exp, const TracePtr &trace, size_t t) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    Logic l = hparser::parseLogicExpression(exp, trace)->evaluate(t);
    return boost::multiprecision::bit_test(l._int, 0) ? "1" : "0";
  } catch (const hlog::HarmError &e) {
    return std::string("PARSE ERROR: ") + e.what();
  }
}

bool parses(const std::string &exp, const TracePtr &trace) {
  std::string error;
  return hparser::tryParseProposition(exp, trace, error) != nullptr;
}

} // namespace

// the values, by name and by the declared index
TEST(VcdBitIndexTest, readsDeclaredIndex) {
  TracePtr tr = readBits();
  ASSERT_GE(tr->getLength(), 3u);
  const char *hi[] = {"0", "1", "0"}, *mid[] = {"1", "0", "1"}, *one[] = {"1", "1", "0"};
  for (size_t t = 0; t < 3; t++) {
    EXPECT_EQ(at("hi", tr, t), hi[t]) << t;
    EXPECT_EQ(at("hi[1]", tr, t), hi[t]) << t;
    EXPECT_EQ(at("mid[5]", tr, t), mid[t]) << t;
    EXPECT_EQ(at("one", tr, t), one[t]) << t;
  }
}

// outside the declared index is an error, as in SystemVerilog
TEST(VcdBitIndexTest, otherIndexIsAnError) {
  TracePtr tr = readBits();
  EXPECT_FALSE(parses("hi[0] == 1'b1", tr));
  EXPECT_FALSE(parses("mid[4] == 1'b1", tr));
  EXPECT_TRUE(parses("hi[1] == 1'b1", tr));
  EXPECT_TRUE(parses("one[0] == 1'b1", tr));
}
