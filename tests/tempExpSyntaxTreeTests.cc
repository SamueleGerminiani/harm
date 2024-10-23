#include <algorithm>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits.h>
#include <ostream>
#include <stddef.h>
#include <string>
#include <vector>

#include "Trace.hh"
#include "expUtils/expUtils.hh"
#include "formula/temporal/temporal.hh"
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

TEST(ASTTests, terminalPrint) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("a", ExpType::Bool, 1);
  vars.emplace_back("b", ExpType::Bool, 1);
  vars.emplace_back("c", ExpType::Bool, 1);
  vars.emplace_back("d", ExpType::Bool, 1);
  vars.emplace_back("e", ExpType::Bool, 1);
  vars.emplace_back("f", ExpType::Bool, 1);
  vars.emplace_back("g", ExpType::Bool, 1);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto a = trace->getBooleanVariable("a");
  auto b = trace->getBooleanVariable("b");
  auto c = trace->getBooleanVariable("c");
  auto d = trace->getBooleanVariable("d");
  auto e = trace->getBooleanVariable("e");
  auto f = trace->getBooleanVariable("f");
  auto g = trace->getBooleanVariable("g");

  auto te = hparser::parseTemporalExpression(
      "G({a;b;c} && {d;e}|-> f W g)", trace);

  std::cout << printAST_terminal(te, Language::SpotLTL,
                                 PrintMode::ShowAll)
            << std::endl;
}
