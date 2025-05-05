#include <algorithm>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <stddef.h>
#include <string>
#include <vector>

#include "CSVtraceReader.hh"
#include "Float.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "VCDtraceReader.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "globals.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

class TraceTest : public ::testing::Test {
protected:
  void TearDown() override { delete tr; }

public:
  TraceReader *tr = nullptr;
  const TracePtr &trace = nullptr;
};

///test single csv trace
TEST_F(TraceTest, BasicTypesCSV) {
  tr = new CSVtraceReader("../tests/input/BasicTypes.csv");
  const TracePtr &trace = tr->readTrace();
  PropositionPtr v1 = trace->getBooleanVariable("v1");
  IntExpressionPtr v2 = trace->getIntVariable("v2");
  IntExpressionPtr v3 = trace->getIntVariable("v3");
  FloatExpressionPtr v4 = trace->getFloatVariable("v4");

  EXPECT_EQ(trace->getLength(), 5);
  EXPECT_EQ(trace->getCuts().size(), 1);

  //v1
  EXPECT_EQ(v1->evaluate(0), (bool)1);
  EXPECT_EQ(v1->evaluate(1), (bool)0);
  EXPECT_EQ(v1->evaluate(2), (bool)0);
  EXPECT_EQ(v1->evaluate(3), (bool)1);
  EXPECT_EQ(v1->evaluate(4), (bool)1);

  //v2
  EXPECT_EQ(v2->evaluate(0), (unsigned char)0);
  EXPECT_EQ(v2->evaluate(1), (unsigned char)9);
  EXPECT_EQ(v2->evaluate(2), (unsigned char)8);
  EXPECT_EQ(v2->evaluate(3), (unsigned char)7);
  EXPECT_EQ(v2->evaluate(4), (unsigned char)256);

  //v3
  EXPECT_EQ(v3->evaluate(0), (int)1);
  EXPECT_EQ(v3->evaluate(1), (int)-2);
  EXPECT_EQ(v3->evaluate(2), (int)3);
  EXPECT_EQ(v3->evaluate(3), (int)4);
  EXPECT_EQ(v3->evaluate(4), (int)-999);

  //v4
  EXPECT_EQ(v4->evaluate(0), (double)0.5);
  EXPECT_EQ(v4->evaluate(1), (double)1.5);
  EXPECT_EQ(v4->evaluate(2), (double)255.5);
  EXPECT_EQ(v4->evaluate(3), (double)123456.123);
  EXPECT_EQ(v4->evaluate(4), (double)0);
}

///test single vcd trace
TEST_F(TraceTest, BasicTypesVCD) {
  clc::selectedScope = "tb::DUT";
  tr = new VCDtraceReader("../tests/input/BasicTypes.vcd", "clk");
  const TracePtr &trace = tr->readTrace();
  BooleanVariablePtr o1 = trace->getBooleanVariable("o1");
  IntExpressionPtr o2 = trace->getIntVariable("o2");

  EXPECT_EQ(trace->getLength(), 5);
  EXPECT_EQ(trace->getCuts().size(), 1);

  //o1
  EXPECT_EQ(o1->evaluate(0), (int)0);
  EXPECT_EQ(o1->evaluate(1), (int)1);
  EXPECT_EQ(o1->evaluate(2), (int)0);
  EXPECT_EQ(o1->evaluate(3), (int)0);
  EXPECT_EQ(o1->evaluate(4), (int)0);

  //o2
  EXPECT_EQ(o2->evaluate(0), (unsigned char)0);
  EXPECT_EQ(o2->evaluate(1), (unsigned char)139);
  EXPECT_EQ(o2->evaluate(2), (unsigned char)109);
  EXPECT_EQ(o2->evaluate(3), (unsigned char)151);
  EXPECT_EQ(o2->evaluate(4), (unsigned char)28);
}

///test merged csv trace
TEST_F(TraceTest, MergedCSV) {
  std::vector<std::string> traces;
  traces.push_back("../tests/input/BasicTypes.csv");
  traces.push_back("../tests/input/BasicTypes.csv");
  tr = new CSVtraceReader(traces);
  const TracePtr &trace = tr->readTrace();
  PropositionPtr v1 = trace->getBooleanVariable("v1");
  IntExpressionPtr v2 = trace->getIntVariable("v2");
  IntExpressionPtr v3 = trace->getIntVariable("v3");
  FloatExpressionPtr v4 = trace->getFloatVariable("v4");

  EXPECT_EQ(trace->getLength(), 10);
  EXPECT_EQ(trace->getCuts().size(), 2);

  //v1
  EXPECT_EQ(v1->evaluate(0), (bool)1);
  EXPECT_EQ(v1->evaluate(1), (bool)0);
  EXPECT_EQ(v1->evaluate(2), (bool)0);
  EXPECT_EQ(v1->evaluate(3), (bool)1);
  EXPECT_EQ(v1->evaluate(4), (bool)1);
  EXPECT_EQ(v1->evaluate(5), (bool)1);
  EXPECT_EQ(v1->evaluate(6), (bool)0);
  EXPECT_EQ(v1->evaluate(7), (bool)0);
  EXPECT_EQ(v1->evaluate(8), (bool)1);
  EXPECT_EQ(v1->evaluate(9), (bool)1);

  //v2
  EXPECT_EQ(v2->evaluate(0), (unsigned char)0);
  EXPECT_EQ(v2->evaluate(1), (unsigned char)9);
  EXPECT_EQ(v2->evaluate(2), (unsigned char)8);
  EXPECT_EQ(v2->evaluate(3), (unsigned char)7);
  EXPECT_EQ(v2->evaluate(4), (unsigned char)256);
  EXPECT_EQ(v2->evaluate(5), (unsigned char)0);
  EXPECT_EQ(v2->evaluate(6), (unsigned char)9);
  EXPECT_EQ(v2->evaluate(7), (unsigned char)8);
  EXPECT_EQ(v2->evaluate(8), (unsigned char)7);
  EXPECT_EQ(v2->evaluate(9), (unsigned char)256);

  //v3
  EXPECT_EQ(v3->evaluate(0), (int)1);
  EXPECT_EQ(v3->evaluate(1), (int)-2);
  EXPECT_EQ(v3->evaluate(2), (int)3);
  EXPECT_EQ(v3->evaluate(3), (int)4);
  EXPECT_EQ(v3->evaluate(4), (int)-999);
  EXPECT_EQ(v3->evaluate(5), (int)1);
  EXPECT_EQ(v3->evaluate(6), (int)-2);
  EXPECT_EQ(v3->evaluate(7), (int)3);
  EXPECT_EQ(v3->evaluate(8), (int)4);
  EXPECT_EQ(v3->evaluate(9), (int)-999);

  //v4
  EXPECT_EQ(v4->evaluate(0), (double)0.5);
  EXPECT_EQ(v4->evaluate(1), (double)1.5);
  EXPECT_EQ(v4->evaluate(2), (double)255.5);
  EXPECT_EQ(v4->evaluate(3), (double)123456.123);
  EXPECT_EQ(v4->evaluate(4), (double)0);
  EXPECT_EQ(v4->evaluate(5), (double)0.5);
  EXPECT_EQ(v4->evaluate(6), (double)1.5);
  EXPECT_EQ(v4->evaluate(7), (double)255.5);
  EXPECT_EQ(v4->evaluate(8), (double)123456.123);
  EXPECT_EQ(v4->evaluate(9), (double)0);
}

///test merged vcd trace
TEST_F(TraceTest, MergedVCD) {
  std::vector<std::string> traces;
  traces.push_back("../tests/input/BasicTypes.vcd");
  traces.push_back("../tests/input/BasicTypes.vcd");
  clc::selectedScope = "tb::DUT";
  tr = new VCDtraceReader(traces, "clk");
  const TracePtr &trace = tr->readTrace();
  BooleanVariablePtr o1 = trace->getBooleanVariable("o1");
  IntVariablePtr o2 = trace->getIntVariable("o2");

  EXPECT_EQ(trace->getLength(), 10);
  EXPECT_EQ(trace->getCuts().size(), 2);

  //o1
  EXPECT_EQ(o1->evaluate(0), (bool)0);
  EXPECT_EQ(o1->evaluate(1), (bool)1);
  EXPECT_EQ(o1->evaluate(2), (bool)0);
  EXPECT_EQ(o1->evaluate(3), (bool)0);
  EXPECT_EQ(o1->evaluate(4), (bool)0);
  EXPECT_EQ(o1->evaluate(5), (bool)0);
  EXPECT_EQ(o1->evaluate(6), (bool)1);
  EXPECT_EQ(o1->evaluate(7), (bool)0);
  EXPECT_EQ(o1->evaluate(8), (bool)0);
  EXPECT_EQ(o1->evaluate(9), (bool)0);

  //o2
  EXPECT_EQ(o2->evaluate(0), (unsigned char)0);
  EXPECT_EQ(o2->evaluate(1), (unsigned char)139);
  EXPECT_EQ(o2->evaluate(2), (unsigned char)109);
  EXPECT_EQ(o2->evaluate(3), (unsigned char)151);
  EXPECT_EQ(o2->evaluate(4), (unsigned char)28);
  EXPECT_EQ(o2->evaluate(5), (unsigned char)0);
  EXPECT_EQ(o2->evaluate(6), (unsigned char)139);
  EXPECT_EQ(o2->evaluate(7), (unsigned char)109);
  EXPECT_EQ(o2->evaluate(8), (unsigned char)151);
  EXPECT_EQ(o2->evaluate(9), (unsigned char)28);
}

TEST_F(TraceTest, Logic) {
  clc::reset = "";
  std::vector<std::string> traces;
  traces.push_back("../tests/input/LogicTrace.csv");
  TraceReader *tr = new CSVtraceReader(traces);
  const TracePtr &trace = tr->readTrace();

  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  IntVariablePtr v2 = trace->getIntVariable("v2");
  IntVariablePtr v3 = trace->getIntVariable("v3");
  IntVariablePtr v4 = trace->getIntVariable("v4");
  IntVariablePtr v5 = trace->getIntVariable("v5");

  EXPECT_EQ(v1->evaluate(0), 1);
  EXPECT_EQ(v2->evaluate(0), 6);
  EXPECT_EQ(v3->evaluate(0), 1542);
  EXPECT_EQ(v4->evaluate(0), 101058054);
  EXPECT_EQ(v5->evaluate(0), -2);

  EXPECT_EQ(v1->evaluate(1), 0);
  EXPECT_EQ(v2->evaluate(1), 6);
  EXPECT_EQ(v2->evaluate(1), 6);
}

TEST_F(TraceTest, SignedLogic) {
  clc::reset = "";
  std::vector<std::string> traces;
  clc::selectedScope = "SignedTypes::dut";
  tr = new VCDtraceReader("../tests/input/SignedTypes.vcd", "clk");
  const TracePtr &trace = tr->readTrace();

  IntVariablePtr c_0 = trace->getIntVariable("c_0");
  IntVariablePtr a_0 = trace->getIntVariable("a_0");
  IntVariablePtr a_1 = trace->getIntVariable("a_1");

  EXPECT_EQ(c_0->evaluate(1), -1);
  EXPECT_EQ(c_0->evaluate(2), -2);
  EXPECT_EQ(c_0->evaluate(3), -3);

  EXPECT_EQ((int)a_0->evaluate(1), -1);
  EXPECT_EQ((int)a_0->evaluate(2), 0);
  EXPECT_EQ((int)a_0->evaluate(3), -3);

  EXPECT_EQ((int)a_1->evaluate(1), 0);
  EXPECT_EQ((int)a_1->evaluate(2), -2);
  EXPECT_EQ((int)a_1->evaluate(3), 0);
}

