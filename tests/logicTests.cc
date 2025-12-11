#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <string>
#include <vector>

#include "Logic.hh"
#include "PointerUtils.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "formula/atom/Atom.hh"
#include "propositionParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

TEST(LogicTest, logicTologicConversion) {

  std::string val = "1xz000zx";
  Logic op(val);
  ASSERT_EQ(op.toString(), val);

  val = "011";
  op = Logic(val, 2, 0);
  ASSERT_EQ(op.toString(), val.substr(1, 2));

  std::vector<VarDeclaration> vars;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  std::string val1 = "'b1010xxzz1010xxxz00001010";
  std::string val2 = "'b11001010xxzzzxzz10100000";

  auto op1 =
      hparser::parseLogicExpression(val1 + " | " + val2, trace);
  ASSERT_EQ(op1->evaluate(0).toString(), "11101x1x1x1xxxxx10101010");

  auto op2 =
      hparser::parseLogicExpression(val1 + " & " + val2, trace);
  ASSERT_EQ(op2->evaluate(0).toString(), "1000x0x0x0x0xxxx00000000");

  auto op3 =
      hparser::parseLogicExpression(val1 + " ^ " + val2, trace);
  ASSERT_EQ(op3->evaluate(0).toString(), "110xxxxxxxxxxxx10101010");

  auto op4 = hparser::parseLogicExpression("~" + val2, trace);
  ASSERT_EQ(op4->evaluate(0).toString(), "110101xxxxxxxx01011111");
}

TEST(LogicTest, twoComplementChecks) {

  std::string val = "111";
  Logic opNegative(val, 3, 1);
  ASSERT_EQ(opNegative.getSignedValue(), -1);
  Logic opPositive(val, 4, 1);
  ASSERT_EQ(opPositive.getSignedValue(), 7);

  Logic opNegative2(3, 1, (ULogic)-1, 0, 0);
  ASSERT_EQ(opNegative2.getSignedValue(), -1);

  Logic opPositive2(3, 0, (ULogic)-1, 0, 0);
  ASSERT_EQ(opPositive2.getUnsignedValue(), 7);
}
