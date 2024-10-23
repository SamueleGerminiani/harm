#include "gtest/gtest_pred_impl.h"
#include <algorithm>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "ClsOp.hh"
#include "Float.hh"
#include "PointerUtils.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "colors.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "propositionParsingUtils.hh"

using namespace harm;
using namespace expression;

#define customASSERT_EQ_Prop(a, b, line, op)                         \
  if (a != b) {                                                      \
    std::cout << "Line " << line << ": " << (int)a                   \
              << " != " << (int)b << " with op " << op << std::endl; \
    FAIL();                                                          \
  }

#define customASSERT_EQ_Int(a, b, line, op)                          \
  if ((uint64_t)(a) != (uint64_t)(b)) {                              \
    std::cout << "Line " << line << ": " << (uint64_t)a              \
              << " != " << (uint64_t)b << " with op " << op          \
              << std::endl;                                          \
    FAIL();                                                          \
  }

#define customASSERT_EQ_Float(a, b, line)                            \
  if (a != b) {                                                      \
    std::cout << std::fixed << std::setprecision(40) << "Line "      \
              << line << ": \n"                                      \
              << a << "\n != \n"                                     \
              << b << std::endl;                                     \
    FAIL();                                                          \
  }
#define customASSERT_EQ_Logic(l, r, line, op)                        \
  if ((l) != (r)) {                                                  \
    std::cout << GLOB("Line ") << line << ": " << l << " != " << r   \
              << " with op " << op << std::endl;                     \
    FAIL();                                                          \
  }

template <typename R1, typename R2, ExpType T1, ExpType T2, int line>
void checkBinaryOpInt(R1 a, R2 b) {
  //  static_assert(
  //      !((std::numeric_limits<R1>::is_signed && T1 == ExpType::UInt) ||
  //        (!std::numeric_limits<R1>::is_signed &&
  //         T1 == ExpType::SInt)) &&
  //      "Real and Simulated types do not match");
  //  static_assert(
  //      !((std::numeric_limits<R2>::is_signed && T2 == ExpType::UInt) ||
  //        (!std::numeric_limits<R2>::is_signed &&
  //         T2 == ExpType::SInt)) &&
  //      "Real and Simulated types do not match");

  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", T1, sizeof(R1) * 8);
  vars.emplace_back("v2", T2, sizeof(R2) * 8);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto v1 = trace->getIntVariable("v1");
  auto v2 = trace->getIntVariable("v2");
  v1->assign(0, a);
  v2->assign(0, b);

  auto res = hparser::parseIntExpression("v1 + v2", trace);
  customASSERT_EQ_Int(res->evaluate(0), a + b, line, '+');

  res = hparser::parseIntExpression("v1 - v2", trace);
  customASSERT_EQ_Int(res->evaluate(0), a - b, line, '-');

  res = hparser::parseIntExpression("v1 * v2", trace);
  customASSERT_EQ_Int(res->evaluate(0), a * b, line, '*');

  res = hparser::parseIntExpression("v1 / v2", trace);
  customASSERT_EQ_Int(res->evaluate(0), a / b, line, '/');

  auto pres = hparser::parseProposition("v1 == v2", trace);
  customASSERT_EQ_Prop(pres->evaluate(0), (a == b), line, "==");

  pres = hparser::parseProposition("v1 != v2", trace);
  customASSERT_EQ_Prop(pres->evaluate(0), (a != b), line, "!=");

  pres = hparser::parseProposition("v1 > v2", trace);
  customASSERT_EQ_Prop(pres->evaluate(0), (a > b), line, '>');

  pres = hparser::parseProposition("v1 >= v2", trace);
  customASSERT_EQ_Prop(pres->evaluate(0), (a >= b), line, ">=");

  pres = hparser::parseProposition("v1 < v2", trace);
  customASSERT_EQ_Prop(pres->evaluate(0), (a < b), line, "<");

  pres = hparser::parseProposition("v1 <= v2", trace);
  customASSERT_EQ_Prop(pres->evaluate(0), (a <= b), line, "<=");

  res = hparser::parseIntExpression("v1 | v2", trace);
  customASSERT_EQ_Int(res->evaluate(0), (a | b), line, '|');

  res = hparser::parseIntExpression("v1 & v2", trace);
  customASSERT_EQ_Int(res->evaluate(0), (a & b), line, '&');

  res = hparser::parseIntExpression("v1 ^ v2", trace);
  customASSERT_EQ_Int(res->evaluate(0), (a ^ b), line, '^');

  res = hparser::parseIntExpression("~v1", trace);
  customASSERT_EQ_Int(res->evaluate(0), ~a, line, '~');

  if (a >= 0) {
    b = 5;
    v2->assign(0, b);
    res = hparser::parseIntExpression("v1 << v2", trace);
    customASSERT_EQ_Int(res->evaluate(0), (a << b), line, "<<");

    res = hparser::parseIntExpression("v1 >> v2", trace);
    customASSERT_EQ_Int(res->evaluate(0), (a >> b), line, ">>");
  }
}

TEST(ConvTest, integerToIntegerConversion) {

  //integer promotion
  checkBinaryOpInt<char, int, ExpType::SInt, ExpType::SInt, __LINE__>(
      std::numeric_limits<char>::max(), 2);

  checkBinaryOpInt<char, int, ExpType::SInt, ExpType::SInt, __LINE__>(
      std::numeric_limits<char>::min(), -2);

  // Balancing (same type different size)
  checkBinaryOpInt<uint32_t, int64_t, ExpType::UInt, ExpType::SInt,
                   __LINE__>(std::numeric_limits<uint32_t>::max(), 2);
  checkBinaryOpInt<uint32_t, int64_t, ExpType::UInt, ExpType::SInt,
                   __LINE__>(std::numeric_limits<uint32_t>::min(),
                             -2);

  //signed vs unsigned with different size

  //unsigned
  checkBinaryOpInt<uint32_t, uint64_t, ExpType::UInt, ExpType::UInt,
                   __LINE__>(std::numeric_limits<uint32_t>::max(), 2);
  checkBinaryOpInt<uint32_t, uint64_t, ExpType::UInt, ExpType::UInt,
                   __LINE__>(std::numeric_limits<uint32_t>::min(),
                             -2);

  //signed
  checkBinaryOpInt<int32_t, uint64_t, ExpType::SInt, ExpType::UInt,
                   __LINE__>(std::numeric_limits<int32_t>::max(), 2);

  checkBinaryOpInt<int32_t, uint64_t, ExpType::SInt, ExpType::UInt,
                   __LINE__>(std::numeric_limits<int32_t>::min(), -2);

  //signed to unsigned (higher size)
  checkBinaryOpInt<uint64_t, int32_t, ExpType::UInt, ExpType::SInt,
                   __LINE__>(std::numeric_limits<uint64_t>::max(),
                             -2);
  checkBinaryOpInt<uint64_t, int32_t, ExpType::UInt, ExpType::SInt,
                   __LINE__>(0, -2);

  //overflow & underflow
  checkBinaryOpInt<int64_t, int64_t, ExpType::SInt, ExpType::SInt,
                   __LINE__>(std::numeric_limits<int64_t>::min(), -2);
  checkBinaryOpInt<int, int, ExpType::SInt, ExpType::SInt, __LINE__>(
      std::numeric_limits<int>::min(), -2);
  checkBinaryOpInt<int64_t, int64_t, ExpType::SInt, ExpType::SInt,
                   __LINE__>(std::numeric_limits<int64_t>::max(), 2);
  checkBinaryOpInt<int, int, ExpType::SInt, ExpType::SInt, __LINE__>(
      std::numeric_limits<int>::max(), 2);

  checkBinaryOpInt<uint64_t, uint64_t, ExpType::UInt, ExpType::UInt,
                   __LINE__>(std::numeric_limits<uint64_t>::max(), 2);
  checkBinaryOpInt<unsigned int, unsigned int, ExpType::UInt,
                   ExpType::UInt, __LINE__>(
      std::numeric_limits<unsigned int>::max(), 2);
  checkBinaryOpInt<uint64_t, int64_t, ExpType::UInt, ExpType::SInt,
                   __LINE__>(std::numeric_limits<uint64_t>::min(),
                             -2);
  checkBinaryOpInt<unsigned int, int, ExpType::UInt, ExpType::SInt,
                   __LINE__>(std::numeric_limits<unsigned int>::min(),
                             -2);

  checkBinaryOpInt<uint64_t, uint64_t, ExpType::UInt, ExpType::UInt,
                   __LINE__>(std::numeric_limits<uint64_t>::max(), 2);
  checkBinaryOpInt<unsigned int, unsigned int, ExpType::UInt,
                   ExpType::UInt, __LINE__>(
      std::numeric_limits<unsigned int>::max(), 2);
  checkBinaryOpInt<uint64_t, int64_t, ExpType::UInt, ExpType::SInt,
                   __LINE__>(std::numeric_limits<uint64_t>::min(),
                             -2);
  checkBinaryOpInt<unsigned int, int, ExpType::UInt, ExpType::SInt,
                   __LINE__>(std::numeric_limits<unsigned int>::min(),
                             -2);

  size_t length = 300;
  //random s v s
  for (size_t i = 0; i < length; i++) {
    int64_t a = (rand() + 1) * (rand() % 2 ? 1 : -1);
    int64_t b = (rand() + 1) * (rand() % 2 ? 1 : -1);
    checkBinaryOpInt<int64_t, int64_t, ExpType::SInt, ExpType::SInt,
                     __LINE__>(a, b);
  }

  //random u vs u
  for (size_t i = 0; i < length; i++) {
    uint64_t a = (rand() + 1);
    uint64_t b = (rand() + 1);
    checkBinaryOpInt<uint64_t, uint64_t, ExpType::UInt, ExpType::UInt,
                     __LINE__>(a, b);
  }

  //random s vs u
  for (size_t i = 0; i < length; i++) {
    int64_t a = (rand() + 1) * (rand() % 2 ? 1 : -1);
    uint64_t b = (rand() + 1);
    checkBinaryOpInt<int64_t, uint64_t, ExpType::SInt, ExpType::UInt,
                     __LINE__>(a, b);
  }
}

template <typename T1, ExpType V1, typename R, int line>
void checkFloatConversion(T1 val) {

  //static_assert(std::numeric_limits<R>::is_iec559 &&
  //              "To type must be a float");

  std::vector<VarDeclaration> vars;

  vars.emplace_back("v1", V1, 64);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto v1 = trace->getIntVariable("v1");

  v1->assign(0, val);
  auto res = hparser::parseFloatExpression("v1", trace);

  customASSERT_EQ_Float(res->evaluate(0), (R)val, line);
}

template <typename T1, ExpType V1, typename R, ExpType V2, int line>
void checkFloatConversionBinary(T1 val1, R val2) {

  std::vector<VarDeclaration> vars;

  vars.emplace_back("v1", V1, sizeof(T1) * 8);

  vars.emplace_back("v2", V2, sizeof(R) * 8);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto v1 = trace->getIntVariable("v1");
  auto v2 = trace->getFloatVariable("v2");

  v1->assign(0, val1);
  v2->assign(0, val2);
  auto res = hparser::parseFloatExpression("v1+v2", trace);

  customASSERT_EQ_Float(res->evaluate(0), (Float)(val1 + val2), line);
}

TEST(ConvTest, floatConversion) {

  checkFloatConversion<uint64_t, ExpType::UInt, double, __LINE__>(
      std::numeric_limits<uint64_t>::max());
  checkFloatConversion<uint64_t, ExpType::UInt, double, __LINE__>(
      std::numeric_limits<uint64_t>::max());
  checkFloatConversion<uint64_t, ExpType::UInt, double, __LINE__>(
      std::numeric_limits<uint64_t>::min());
  checkFloatConversion<uint64_t, ExpType::UInt, double, __LINE__>(
      std::numeric_limits<uint64_t>::min());

  checkFloatConversion<int64_t, ExpType::SInt, double, __LINE__>(
      std::numeric_limits<int64_t>::max());
  checkFloatConversion<int64_t, ExpType::SInt, double, __LINE__>(
      std::numeric_limits<int64_t>::max());
  checkFloatConversion<int64_t, ExpType::SInt, double, __LINE__>(
      std::numeric_limits<int64_t>::min());
  checkFloatConversion<int64_t, ExpType::SInt, double, __LINE__>(
      std::numeric_limits<int64_t>::min());

  checkFloatConversion<int, ExpType::SInt, double, __LINE__>(
      std::numeric_limits<int>::max());
  checkFloatConversion<int, ExpType::SInt, double, __LINE__>(
      std::numeric_limits<int>::max());
  checkFloatConversion<int, ExpType::SInt, double, __LINE__>(
      std::numeric_limits<int>::min());
  checkFloatConversion<int, ExpType::SInt, double, __LINE__>(
      std::numeric_limits<int>::min());

  size_t length = 300;
  for (size_t i = 0; i < length; i++) {
    int64_t val = (rand() + 1) * (rand() % 2 ? 1 : -1);
    checkFloatConversion<int64_t, ExpType::SInt, double, __LINE__>(
        val);
  }

  checkFloatConversionBinary<int, ExpType::SInt, double,
                             ExpType::Float, __LINE__>(
      std::numeric_limits<int>::max(), 300.f);
  checkFloatConversionBinary<int, ExpType::SInt, double,
                             ExpType::Float, __LINE__>(
      std::numeric_limits<int>::min(), -300.f);
  checkFloatConversionBinary<uint64_t, ExpType::UInt, double,
                             ExpType::Float, __LINE__>(
      std::numeric_limits<int>::max(), 300.f);
  checkFloatConversionBinary<uint64_t, ExpType::UInt, double,
                             ExpType::Float, __LINE__>(
      std::numeric_limits<int>::min(), -300.f);
  checkFloatConversionBinary<int64_t, ExpType::SInt, double,
                             ExpType::Float, __LINE__>(
      std::numeric_limits<int>::max(), 300.f);
  checkFloatConversionBinary<int64_t, ExpType::SInt, double,
                             ExpType::Float, __LINE__>(
      std::numeric_limits<int>::min(), -300.f);

  for (size_t i = 0; i < length; i++) {
    int64_t a = (rand() + 1) * (rand() % 2 ? 1 : -1);
    double b = (rand() + 1) *
               ((rand() % 2 ? 1 : -1) + (double)rand() / 1000.f);
    checkFloatConversionBinary<int64_t, ExpType::SInt, double,
                               ExpType::Float, __LINE__>(a, b);
  }
}

