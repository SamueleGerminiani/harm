#include "CSVtraceReader.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "VCDtraceReader.hh"
#include "globals.hh"
#include <gtest/gtest.h>

using namespace harm;
using namespace expression;

class TraceTest : public ::testing::Test {
protected:
  TraceTest() {}

  ~TraceTest() override {}

  void SetUp() override {}

  void TearDown() override {
    delete tr;
    delete trace;
  }

public:
  TraceReader *tr = nullptr;
  Trace *trace = nullptr;
};

///test single csv trace
TEST_F(TraceTest, t1) {
  tr = new CSVtraceReader("../tests/input/TraceTest_t1.csv");
  Trace *trace = tr->readTrace();
  Proposition *v1 = trace->getBooleanVariable("v1");
  LogicExpression *v2 = trace->getLogicVariable("v2");
  LogicExpression *v3 = trace->getLogicVariable("v3");
  NumericExpression *v4 = trace->getNumericVariable("v4");

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

  delete v1;
  delete v2;
  delete v3;
  delete v4;
}

///test single vcd trace
TEST_F(TraceTest, t2) {
  clc::selectedScope = "tb::DUT";
  tr = new VCDtraceReader("../tests/input/TraceTest_t2.vcd", "clk");
  Trace *trace = tr->readTrace();
  Proposition *o1 = trace->getBooleanVariable("o1");
  LogicExpression *o2 = trace->getLogicVariable("o2");

  EXPECT_EQ(trace->getLength(), 5);
  EXPECT_EQ(trace->getCuts().size(), 1);

  //o1
  EXPECT_EQ(o1->evaluate(0), (bool)1);
  EXPECT_EQ(o1->evaluate(1), (bool)0);
  EXPECT_EQ(o1->evaluate(2), (bool)0);
  EXPECT_EQ(o1->evaluate(3), (bool)0);
  EXPECT_EQ(o1->evaluate(4), (bool)0);

  //o2
  EXPECT_EQ(o2->evaluate(0), (unsigned char)139);
  EXPECT_EQ(o2->evaluate(1), (unsigned char)109);
  EXPECT_EQ(o2->evaluate(2), (unsigned char)151);
  EXPECT_EQ(o2->evaluate(3), (unsigned char)28);
  EXPECT_EQ(o2->evaluate(4), (unsigned char)23);

  delete o1;
  delete o2;
}

///test merged csv trace
TEST_F(TraceTest, t3) {
  std::vector<std::string> traces;
  traces.push_back("../tests/input/TraceTest_t1.csv");
  traces.push_back("../tests/input/TraceTest_t1.csv");
  tr = new CSVtraceReader(traces);
  Trace *trace = tr->readTrace();
  Proposition *v1 = trace->getBooleanVariable("v1");
  LogicExpression *v2 = trace->getLogicVariable("v2");
  LogicExpression *v3 = trace->getLogicVariable("v3");
  NumericExpression *v4 = trace->getNumericVariable("v4");

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

  delete v1;
  delete v2;
  delete v3;
  delete v4;
}

///test merged vcd trace
TEST_F(TraceTest, t4) {
  std::vector<std::string> traces;
  traces.push_back("../tests/input/TraceTest_t2.vcd");
  traces.push_back("../tests/input/TraceTest_t2.vcd");
  clc::selectedScope = "tb::DUT";
  tr = new VCDtraceReader(traces, "clk");
  Trace *trace = tr->readTrace();
  Proposition *o1 = trace->getBooleanVariable("o1");
  LogicExpression *o2 = trace->getLogicVariable("o2");

  EXPECT_EQ(trace->getLength(), 10);
  EXPECT_EQ(trace->getCuts().size(), 2);

  //o1
  EXPECT_EQ(o1->evaluate(0), (bool)1);
  EXPECT_EQ(o1->evaluate(1), (bool)0);
  EXPECT_EQ(o1->evaluate(2), (bool)0);
  EXPECT_EQ(o1->evaluate(3), (bool)0);
  EXPECT_EQ(o1->evaluate(4), (bool)0);
  EXPECT_EQ(o1->evaluate(5), (bool)1);
  EXPECT_EQ(o1->evaluate(6), (bool)0);
  EXPECT_EQ(o1->evaluate(7), (bool)0);
  EXPECT_EQ(o1->evaluate(8), (bool)0);
  EXPECT_EQ(o1->evaluate(9), (bool)0);

  //o2
  EXPECT_EQ(o2->evaluate(0), (unsigned char)139);
  EXPECT_EQ(o2->evaluate(1), (unsigned char)109);
  EXPECT_EQ(o2->evaluate(2), (unsigned char)151);
  EXPECT_EQ(o2->evaluate(3), (unsigned char)28);
  EXPECT_EQ(o2->evaluate(4), (unsigned char)23);
  EXPECT_EQ(o2->evaluate(5), (unsigned char)139);
  EXPECT_EQ(o2->evaluate(6), (unsigned char)109);
  EXPECT_EQ(o2->evaluate(7), (unsigned char)151);
  EXPECT_EQ(o2->evaluate(8), (unsigned char)28);
  EXPECT_EQ(o2->evaluate(9), (unsigned char)23);

  delete o1;
  delete o2;
}

