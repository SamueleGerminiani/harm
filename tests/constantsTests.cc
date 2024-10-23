#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <string>
#include <vector>

#include "Trace.hh"
#include "VarDeclaration.hh"
#include "exp.hh"
#include "formula/atom/Atom.hh"
#include "propositionParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

TEST(ConstantsTest, gccBinary) {
  std::vector<VarDeclaration> vars;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  std::string val = "0b101";
  IntExpressionPtr ic = hparser::parseIntExpression(val, trace);

  ASSERT_EQ(ic->evaluate(0), 5);
  ASSERT_EQ("5", exp2String(ic));
}

TEST(ConstantsTest, gccHex) {
  std::vector<VarDeclaration> vars;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  std::string val = "0xff";
  IntExpressionPtr ic = hparser::parseIntExpression(val, trace);

  ASSERT_EQ(ic->evaluate(0), 255);
  ASSERT_EQ("255", exp2String(ic));
}

TEST(ConstantsTest, sInteger) {
  std::vector<VarDeclaration> vars;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  std::string val = "-12345";
  IntExpressionPtr ic = hparser::parseIntExpression(val, trace);

  ASSERT_EQ(ic->evaluate(0), -12345);
  ASSERT_EQ("-12345", exp2String(ic));
}

TEST(ConstantsTest, uInteger) {
  std::vector<VarDeclaration> vars;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  std::string val = "12345";
  IntExpressionPtr ic = hparser::parseIntExpression(val, trace);

  ASSERT_EQ(ic->evaluate(0), 12345);
  ASSERT_EQ("12345", exp2String(ic));
}

TEST(ConstantsTest, sfloat) {
  std::vector<VarDeclaration> vars;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  std::string val = "1.609";
  FloatExpressionPtr ic = hparser::parseFloatExpression(val, trace);

  ASSERT_EQ(ic->evaluate(0), 1.609);
  ASSERT_EQ("1.609", exp2String(ic));
}

TEST(ConstantsTest, llLiteral) {
  std::vector<VarDeclaration> vars;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  std::string val = "12345ll";
  IntExpressionPtr ic = hparser::parseIntExpression(val, trace);

  ASSERT_EQ(ic->evaluate(0), 12345);
  ASSERT_EQ("12345", exp2String(ic));
}

TEST(ConstantsTest, ullLiteral) {
  std::vector<VarDeclaration> vars;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  std::string val = "12345ull";
  IntExpressionPtr ic = hparser::parseIntExpression(val, trace);

  ASSERT_EQ(ic->evaluate(0), 12345);
  ASSERT_EQ("12345", exp2String(ic));
}

TEST(ConstantsTest, fLiteral) {
  std::vector<VarDeclaration> vars;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  std::string val = "-1.f";
  FloatExpressionPtr ic = hparser::parseFloatExpression(val, trace);

  ASSERT_EQ(ic->evaluate(0), -1.f);
  ASSERT_EQ("-1", exp2String(ic));
}
