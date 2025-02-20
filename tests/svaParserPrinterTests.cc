#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

#include "Assertion.hh"
#include "AutomataBasedEvaluator.hh"
#include "CSVtraceReader.hh"
#include "Evaluator.hh"
#include "ProgressBar.hpp"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "globals.hh"
#include "message.hh"
#include "minerUtils.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"
#include <chrono>
#include <filesystem>

using namespace harm;

TEST(svaParserPrinterTests, parse_print1) {
  clc::clk = "clk";
  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < 100; i++) {
    vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
  }
  vars.emplace_back("clk", ExpType::Bool, 1);

  TracePtr trace = generatePtr<Trace>(vars, 5);
  BooleanVariablePtr b_0 = trace->getBooleanVariable("b_0");
  BooleanVariablePtr b_1 = trace->getBooleanVariable("b_1");

  std::string assertionStr_tmp = "always (b_0 |-> b_1 until b_2)";
  auto assertion =
      hparser::parseTemporalExpression(assertionStr_tmp, trace);
  clc::outputLang = Language::SpotLTL;
  ASSERT_EQ(
      temp2String(assertion, Language::SpotLTL, PrintMode::ShowAll),
      "G({b_0} |-> b_1 W b_2)");
  ASSERT_EQ(temp2String(assertion, Language::SVA, PrintMode::ShowAll),
            "always (b_0 |-> b_1 until b_2)");

  assertionStr_tmp = "G(b_0 -> b_1 W b_2)";
  assertion =
      hparser::parseTemporalExpression(assertionStr_tmp, trace);
  clc::outputLang = Language::SpotLTL;
  ASSERT_EQ(
      temp2String(assertion, Language::SpotLTL, PrintMode::ShowAll),
      "G(b_0 -> b_1 W b_2)");
  clc::outputLang = Language::SVA;
  ASSERT_EQ(temp2String(assertion, Language::SVA, PrintMode::ShowAll),
            "always (b_0 |-> b_1 until b_2)");
  clc::svaAssert = 1;
  ASSERT_EQ(
      temp2String(assertion, Language::SVA, PrintMode::ShowAll),
      "assert property (@(posedge clk) (b_0 |-> b_1 until b_2))");
  clc::svaAssert = 0;
  assertion = hparser::parseTemporalExpression(
      "assert property (@(posedge clk) (b_0 |-> b_1 until b_2))",
      trace);
}

TEST(svaParserPrinterTests, parse_print3) {
  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < 100; i++) {
    vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
  }
  vars.emplace_back("clk", ExpType::Bool, 1);

  TracePtr trace = generatePtr<Trace>(vars, 5);
  BooleanVariablePtr b_0 = trace->getBooleanVariable("b_0");
  BooleanVariablePtr b_1 = trace->getBooleanVariable("b_1");

  std::string assertionStr_tmp = "always(b_0 -> Xb_1)";
  auto assertion =
      hparser::parseTemporalExpression(assertionStr_tmp, trace);
  clc::outputLang = Language::SpotLTL;
  ASSERT_EQ(
      temp2String(assertion, Language::SpotLTL, PrintMode::ShowAll),
      "G(b_0 -> Xb_1)");
  clc::outputLang = Language::SVA;
  ASSERT_EQ(temp2String(assertion, Language::SVA, PrintMode::ShowAll),
            "always (b_0 |-> nexttime b_1)");
  clc::svaAssert = 1;
  ASSERT_EQ(
      temp2String(assertion, Language::SVA, PrintMode::ShowAll),
      "assert property (@(posedge clk) (b_0 |-> nexttime b_1))");
  clc::svaAssert = 0;
  assertion = hparser::parseTemporalExpression(
      "assert property (@(posedge clk) (b_0 |-> nexttime b_1))",
      trace);
}

TEST(svaParserPrinterTests, parse_print5) {
  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < 100; i++) {
    vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
  }

  TracePtr trace = generatePtr<Trace>(vars, 5);
  BooleanVariablePtr b_0 = trace->getBooleanVariable("b_0");
  BooleanVariablePtr b_1 = trace->getBooleanVariable("b_1");

  std::string assertionStr_tmp = "always(b_0 -> b_1 R b_2)";
  auto assertion =
      hparser::parseTemporalExpression(assertionStr_tmp, trace);
  clc::outputLang = Language::SpotLTL;
  ASSERT_EQ(
      temp2String(assertion, Language::SpotLTL, PrintMode::ShowAll),
      "G(b_0 -> b_1 R b_2)");
}

TEST(svaParserPrinterTests, parse_print7) {
  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < 100; i++) {
    vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
  }
  vars.emplace_back("clk", ExpType::Bool, 1);

  TracePtr trace = generatePtr<Trace>(vars, 5);
  BooleanVariablePtr b_0 = trace->getBooleanVariable("b_0");
  BooleanVariablePtr b_1 = trace->getBooleanVariable("b_1");

  std::string assertionStr_tmp = "G (b_0 -> Fb_1 W b_2)";
  auto assertion =
      hparser::parseTemporalExpression(assertionStr_tmp, trace);
  clc::outputLang = Language::SpotLTL;
  ASSERT_EQ(
      temp2String(assertion, Language::SpotLTL, PrintMode::ShowAll),
      "G(b_0 -> Fb_1 W b_2)");
  clc::outputLang = Language::SVA;
  ASSERT_EQ(temp2String(assertion, Language::SVA, PrintMode::ShowAll),
            "always (b_0 |-> eventually b_1 until b_2)");
  clc::svaAssert = 1;
  ASSERT_EQ(temp2String(assertion, Language::SVA, PrintMode::ShowAll),
            "assert property (@(posedge clk) (b_0 |-> eventually b_1 "
            "until b_2))");
  clc::svaAssert = 0;
  assertion = hparser::parseTemporalExpression(
      "assert property (@(posedge clk) (b_0 |-> eventually b_1 until "
      "b_2))",
      trace);
}

TEST(svaParserPrinterTests, parse_print8) {
  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < 100; i++) {
    vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
  }
  vars.emplace_back("clk", ExpType::Bool, 1);

  TracePtr trace = generatePtr<Trace>(vars, 5);
  BooleanVariablePtr b_0 = trace->getBooleanVariable("b_0");
  BooleanVariablePtr b_1 = trace->getBooleanVariable("b_1");

  std::string assertionStr_tmp = "always(b_0 |->X[9]b_1)";
  auto assertion =
      hparser::parseTemporalExpression(assertionStr_tmp, trace);
  clc::outputLang = Language::SpotLTL;
  ASSERT_EQ(
      temp2String(assertion, Language::SpotLTL, PrintMode::ShowAll),
      "G({b_0} |-> X[9](b_1))");
  clc::outputLang = Language::SVA;
  ASSERT_EQ(temp2String(assertion, Language::SVA, PrintMode::ShowAll),
            "always (b_0 |-> nexttime[9] b_1)");

  clc::svaAssert = 1;
  ASSERT_EQ(
      temp2String(assertion, Language::SVA, PrintMode::ShowAll),
      "assert property (@(posedge clk) (b_0 |-> nexttime[9] b_1))");
  clc::svaAssert = 0;
  assertion = hparser::parseTemporalExpression(
      "assert property (@(posedge clk) (b_0 |-> nexttime[9] b_1))",
      trace);
}

TEST(svaParserPrinterTests, parse_print9) {
  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < 100; i++) {
    vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
  }

  TracePtr trace = generatePtr<Trace>(vars, 5);
  BooleanVariablePtr b_0 = trace->getBooleanVariable("b_0");
  BooleanVariablePtr b_1 = trace->getBooleanVariable("b_1");

  clc::outputLang = Language::SpotLTL;
  std::string assertionStr_tmp = "G(b_0 -> b_1)";
  auto assertion =
      hparser::parseTemporalExpression(assertionStr_tmp, trace);
  ASSERT_EQ(
      temp2String(assertion, Language::SpotLTL, PrintMode::ShowAll),
      "G(b_0 -> b_1)");
}
