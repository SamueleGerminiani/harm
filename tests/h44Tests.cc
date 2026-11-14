// H44-eval-v4, finding: a proposition inside a temporal formula was handed to the proposition
// parser as ANTLR's getText(), which drops the skipped white space. A ternary whose condition ends
// with a based literal ('c == 8'b1 ? 1'b1 : 1'b0') then read as 'c==8'b1?1'b1:1'b0', where the
// lexer takes '8'b1?1' as one literal ('?' is a z digit), and the parse failed. HARM hit it when
// the fault-based qualification parsed the printed assertions again (uart_to_bus, a relation from
// harm-coi --hints).
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>

#include <string>
#include <vector>

#include "Logic.hh"
#include "PointerUtils.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "VarDeclaration.hh"
#include "expUtils/expUtils.hh"
#include "message.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

namespace {

// a: bool; x: 1-bit logic; c: 8-bit logic, with x == (c == 1) on every row
TracePtr makeTrace() {
  std::vector<VarDeclaration> decls = {
      {"a", ExpType::Bool, 1}, {"x", ExpType::ULogic, 1}, {"c", ExpType::ULogic, 8}};
  const std::vector<std::string> cs = {"00000000", "00000001", "00000010", "00000001"};
  TracePtr tr = generatePtr<Trace>(decls, cs.size());
  for (size_t t = 0; t < cs.size(); t++) {
    tr->getBooleanVariable("a")->assign(t, t % 2 == 1);
    tr->getLogicVariable("c")->assign(t, Logic(cs[t], 8));
    tr->getLogicVariable("x")->assign(t, Logic(cs[t] == "00000001" ? "1" : "0", 1));
  }
  return tr;
}

}  // namespace

// the formula as written, with the condition's literal right before '?'
TEST(H44Test, TernaryAfterBasedLiteralInTemplate) {
  hlog::ScopedThrowOnError throwOnError;
  TracePtr tr = makeTrace();
  for (std::string exp : {"x == ((c == 8'b1) ? 1'b1 : 1'b0)", "x == (c == 8'b1 ? 1'b1 : 1'b0)",
                          "x == (c == 8'd1 ? 1'd1 : 1'd0)"}) {
    TemplateImplicationPtr ti;
    ASSERT_NO_THROW(ti = hparser::parseTemplateImplication("G(a -> " + exp + ")", tr, DTLimits(),
                                                           false))
        << exp;
    EXPECT_TRUE(ti->assHoldsOnTrace(Location::AntCon)) << exp;
  }
}

// the printed assertion parses again (what the fault-based qualification does)
TEST(H44Test, PrintedTernaryParsesAgain) {
  hlog::ScopedThrowOnError throwOnError;
  TracePtr tr = makeTrace();
  auto ti = hparser::parseTemplateImplication("G(a -> x == ((c == 8'd1) ? 1'd1 : 1'd0))", tr,
                                              DTLimits(), false);
  std::string printed = temp2String(ti->getTemplateFormula(), Language::SpotLTL, PrintMode::ShowAll);
  TemplateImplicationPtr again;
  ASSERT_NO_THROW(again = hparser::parseTemplateImplication(printed, tr, DTLimits(), false))
      << printed;
  EXPECT_EQ(temp2String(again->getTemplateFormula(), Language::SpotLTL, PrintMode::ShowAll), printed);
}

// a '?' digit inside a based literal keeps working in a template
TEST(H44Test, QuestionDigitInBasedLiteral) {
  hlog::ScopedThrowOnError throwOnError;
  TracePtr tr = makeTrace();
  ASSERT_NO_THROW(hparser::parseTemplateImplication("G(a -> c != 8'b0000001?)", tr, DTLimits(),
                                                    false));
}
