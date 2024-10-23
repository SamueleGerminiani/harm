#include <algorithm>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits.h>
#include <ostream>
#include <stddef.h>
#include <string>
#include <vector>

#include "CSVtraceReader.hh"
#include "Float.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "Trinary.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"

#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "formula/expression/TypeCast.hh"
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

TEST(TemporalExpressionTest, checkVisitors) {
  clc::outputLang = Language::SpotLTL;

  TraceReader *tr =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = tr->readTrace();
  TraceReader *tr2 =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace_new = tr2->readTrace();
  std::ifstream in("../tests/input/fuzzedTemporalFormulas.txt");
#if 0
   size_t index = 0;
#endif
  std::string line;
  for (std::string line; getline(in, line);) {
#if 0
    std::cout << "================================="
              << "\n";

    std::cout << "--------" << ++index << "-------\n";
    std::cout << line << "\n";
    std::cout << "--------------------------------"
              << "\n";
#endif

    auto te = hparser::parseTemporalExpression(line, trace);
#if 0
    std::cout << "Before copying"
              << "\n";
    std::cout << temp2String(*te, Language::SpotLTL, 0) << std::endl;
    std::cout << "-----------------------------"
              << "\n";
#endif
    auto vars = getVars(te);
    auto te_copy = copy(te);
    changeTrace(te_copy, trace_new);
    auto vars_copy = getVars(te_copy);
    for (size_t i = 0; i < vars.size(); i++) {
      ASSERT_EQ(vars[i].first, vars_copy[i].first);
      ASSERT_EQ(vars[i].second, vars_copy[i].second);
    }

    std::string ass =
        temp2String(te_copy, Language::SpotLTL,
                    PrintMode::ShowOnlyPermuationPlaceholders);

#if 0
    std::cout << "After copying"
              << "\n";
    std::cout << ass << std::endl;
    std::cout << "-----------------------------"
              << "\n";
#endif

    removeSpacesInPlace(ass);
    removeBracketsInPlace(ass);
    removeSpacesInPlace(line);
    removeBracketsInPlace(line);

    ASSERT_EQ(line, ass);

#if 0
    //std::cin << "SVA: " << temp2ColoredString(*te, Language::SVA, 1) << "\n";
    //std::cin << "PSL: " << temp2ColoredString(*te, Language::PSL, 1) << "\n";
    //std::cout << "=================================" << "\n";
#endif
  }

  delete tr;
  delete tr2;
  in.close();
}
