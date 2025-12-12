#ifndef DEBUG
#include <algorithm>
#include <chrono>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits.h>
#include <stddef.h>
#include <string>
#include <vector>

#include "CSVtraceReader.hh"
#include "DTOperator.hh"
#include "Edit.hh"
#include "Float.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "Trinary.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/NumericExpression.hh"
#include "formula/atom/Variable.hh"
#include "formula/expression/SetMembership.hh"
#include "formula/expression/TypeCast.hh"
#include "formula/function/SVAfunction.hh"
#include "globals.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

namespace harm {
class Context;
} // namespace harm

using namespace harm;
using namespace expression;

TEST(perfTest, propCacheTest) {

  TraceReader *tr = new CSVtraceReader(
      "../tests/input/RandomTrace.csv", clc::forceInt);
  const TracePtr &trace = tr->readTrace();
  std::string pStr = "v9 * v10 + v10 / (v9+1.f) && v1";

  auto p = hparser::parseProposition(pStr, trace);
  size_t sum = 0;
  const size_t N = 10000000;
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();
  for (size_t i = 0; i < N; i++) {
    for (size_t i = 0; i < 10; i++) {
      sum += p->evaluate(i);
    }
  }
  std::chrono::steady_clock::time_point end =
      std::chrono::steady_clock::now();
  std::cout << "Time without cache = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   end - begin)
                   .count()
            << "[ms]" << std::endl;

  p->enableCache();

  size_t sum2 = 0;
  std::chrono::steady_clock::time_point begin2 =
      std::chrono::steady_clock::now();
  for (size_t i = 0; i < N; i++) {
    for (size_t i = 0; i < 10; i++) {
      sum2 += p->evaluate(i);
    }
  }
  std::chrono::steady_clock::time_point end2 =
      std::chrono::steady_clock::now();
  std::cout << "Time with cache = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   end2 - begin2)
                   .count()
            << "[ms]" << std::endl;
  ASSERT_EQ(sum, sum2);

  p->disableCache();

  delete tr;
}
#endif
