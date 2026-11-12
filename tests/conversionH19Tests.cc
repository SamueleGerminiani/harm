// H19, acceptance test A4 (D-035): conversions, CSV types and the cases that used to stop HARM.
// Expected values by hand, from IEEE 1800-2017 (11.4.2, 11.4.10, 11.8.1, Table 6-8) and the user's
// decision Q3 (a): a division by zero is x for logic, 0 for the 2-valued C integer types.
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "CSVtraceReader.hh"
#include "Float.hh"
#include "Logic.hh"
#include "PointerUtils.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Constant.hh"
#include "formula/atom/Variable.hh"
#include "formula/expression/TypeCast.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

/// a trace read from CSV text by HARM's own reader
TracePtr csvTrace(const std::string &text) {
  auto f = std::filesystem::temp_directory_path() / "harm_h19_conversion.csv";
  std::ofstream(f) << text;
  hlog::ScopedThrowOnError throwOnError;
  TraceReader *tr = new CSVtraceReader(f.string());
  TracePtr trace = tr->readTrace();
  delete tr;
  std::filesystem::remove(f);
  return trace;
}

/// the value of exp on each row as "0"/"1", or "ERROR: ..." (an exit or an error message)
std::string values(const std::string &exp, const TracePtr &tr) {
  hlog::ScopedThrowOnError throwOnError;
  try {
    PropositionPtr p = hparser::parseProposition(exp, tr);
    std::string s;
    for (size_t t = 0; t < tr->getLength(); t++) {
      s += p->evaluate(t) ? '1' : '0';
    }
    return s;
  } catch (const hlog::HarmError &e) {
    return std::string("ERROR: ") + e.what();
  }
}

} // namespace

TEST(ConversionH19Test, castsKeepTheSign) {
  // LogicToInt of a negative signed logic is negative; FloatToInt truncates towards zero
  std::vector<VarDeclaration> decls = {{"s", ExpType::SLogic, 8}};
  TracePtr tr = generatePtr<Trace>(decls, 1);
  tr->getLogicVariable("s")->assign(0, Logic("11111101", 8));  // -3
  auto li = generatePtr<LogicToInt>(LogicExpressionPtr(tr->getLogicVariable("s")));
  EXPECT_EQ(li->getType().first, ExpType::SInt);
  EXPECT_EQ((SInt)li->evaluate(0), -3);
  auto fi = generatePtr<FloatToInt>(
      FloatExpressionPtr(generatePtr<FloatConstant>(-2.5, ExpType::Float, 64, 1)));
  EXPECT_EQ((SInt)fi->evaluate(0), -2);
}

TEST(ConversionH19Test, wideSignedLogic) {
  // a 40-bit signed logic variable holding -1
  TracePtr tr = csvTrace("logic signed [39:0] v\n" + std::string(40, '1') + "\n" + std::string(39, '0') + "1\n");
  EXPECT_EQ(values("v < 0", tr), "10");
  EXPECT_EQ(values("v == -1", tr), "10");
}

TEST(ConversionH19Test, csvTypes) {
  // int unsigned is legal SystemVerilog; integer is 4-state 32-bit signed, time 4-state 64-bit
  TracePtr tr = csvTrace("int unsigned u,integer i,time t\n7," + std::string(32, '1') + "," +
                         std::string(63, '0') + "1\n9," + std::string(31, '0') + "x," +
                         std::string(63, '0') + "z\n");
  EXPECT_EQ(values("u == 7", tr), "10");
  EXPECT_EQ(values("u - 8 < 0", tr), "00");  // unsigned
  EXPECT_EQ(values("i < 0", tr), "10");      // -1; x is false
  EXPECT_EQ(values("i === 32'b" + std::string(31, '0') + "x", tr), "01");
  EXPECT_EQ(values("t == 64'd1", tr), "10");
}

TEST(ConversionH19Test, nothingStopsHarm) {
  TracePtr tr = csvTrace("int x,int y,logic [3:0] q,logic [3:0] r,logic [1:0] p\n6,0,0110,0000,01\n-6,2,0110,0010,11\n");
  // Q3 (a): int division by zero is 0; logic division by zero is x (false when compared)
  EXPECT_EQ(values("x / y == 0", tr), "10");
  EXPECT_EQ(values("x / y == -3", tr), "01");
  EXPECT_EQ(values("q / r == 4'd0", tr), "00");
  EXPECT_EQ(values("q / r != 4'd0", tr), "01");
  // shifts by the width or more give 0; a negative amount is a huge unsigned one (11.4.10)
  EXPECT_EQ(values("x >> 100 == 0", tr), "11");
  EXPECT_EQ(values("x << 100 == 0", tr), "11");
  EXPECT_EQ(values("x << -1 == 0", tr), "11");
  EXPECT_EQ(values("q << 4 == 4'd0", tr), "11");
  // the amount is self-determined (E2): a 2-bit p shifted by 4, in a 5-bit context:
  // 00001 << 4 = 10000; 00011 << 4 = 110000, truncated to 10000
  EXPECT_EQ(values("p << 4 == 5'b10000", tr), "11");
  // >> is logical, >>> arithmetic on a signed result (E4, Q2)
  EXPECT_EQ(values("x >> 1 > 0", tr), "11");
  EXPECT_EQ(values("x >>> 1 == -3", tr), "01");
}
