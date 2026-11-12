// H1, acceptance test A6 and the D-002 printing rules: HARM's SVA output is valid SystemVerilog
// in the form trivergence's adapter used to produce (tests/input/h1/m0_normalize_cases.txt).
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <fstream>
#include <string>
#include <vector>

#include "PointerUtils.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "globals.hh"
#include "message.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

TracePtr m0Trace() {
  std::vector<VarDeclaration> vars;
  for (std::string b : {"req", "ack", "en", "wrap", "a", "b", "clk",
                        "u_core::busy"}) {
    vars.emplace_back(b, ExpType::Bool, 1);
  }
  vars.emplace_back("count", ExpType::ULogic, 8);
  vars.emplace_back("u_core::state", ExpType::ULogic, 2);
  return generatePtr<Trace>(vars, 4);
}

// print an assertion as --sva-assert does, and return the property body
std::string assertBody(const std::string &assertion, const TracePtr &trace) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    auto te = hparser::parseTemporalExpression(assertion, trace);
    clc::clk = "clk";
    clc::svaAssert = true;
    std::string printed = temp2String(te, Language::SVA, PrintMode::ShowAll);
    clc::svaAssert = false;
    const std::string prefix = "assert property (@(posedge clk) (";
    const std::string suffix = "))";
    if (printed.rfind(prefix, 0) != 0 ||
        printed.size() < prefix.size() + suffix.size() ||
        printed.compare(printed.size() - suffix.size(), suffix.size(),
                        suffix) != 0) {
      return "UNEXPECTED WRAPPER: " + printed;
    }
    return printed.substr(prefix.size(),
                          printed.size() - prefix.size() - suffix.size());
  } catch (const hlog::HarmError &e) {
    clc::svaAssert = false;
    return std::string("PARSE ERROR: ") + e.what();
  }
}

std::string sva(const std::string &assertion, const TracePtr &trace) {
  auto te = hparser::parseTemporalExpression(assertion, trace);
  return temp2String(te, Language::SVA, PrintMode::ShowAll);
}

} // namespace

TEST(SvaOutputTest, trivergenceM0Cases) {
  TracePtr trace = m0Trace();
  std::ifstream in("../tests/input/h1/m0_normalize_cases.txt");
  ASSERT_TRUE(in.good());
  std::string line;
  size_t n = 0;
  while (std::getline(in, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }
    size_t sep = line.find(" ==> ");
    ASSERT_NE(sep, std::string::npos) << line;
    std::string input = line.substr(0, sep);
    std::string expected = line.substr(sep + 5);
    EXPECT_EQ(assertBody(input, trace), expected) << "input: " << input;
    n++;
  }
  EXPECT_EQ(n, 12u);
}

TEST(SvaOutputTest, svaKeepsAlwaysAndUsesValidTokens) {
  // D-002: --sva keeps the outer always, but prints 1'b1, |=> and '.'
  TracePtr trace = m0Trace();
  clc::svaAssert = false;
  EXPECT_EQ(sva("always (!req ##1 true |-> nexttime !ack)", trace),
            "always (!req ##1 1'b1 |=> !ack)");
  EXPECT_EQ(sva("always (u_core::state == 2'b10 |-> u_core::busy)", trace),
            "always (u_core.state == 2'b10 |-> u_core.busy)");
  EXPECT_EQ(sva("G(req -> X X ack)", trace), "always (req |-> ##2 ack)");
}
