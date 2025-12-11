#include <algorithm>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits.h>
#include <stddef.h>
#include <string>
#include <vector>

#include "CSVtraceReader.hh"
#include "Context.hh"
#include "Edit.hh"
#include "Float.hh"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "Trinary.hh"
#include "VarDeclaration.hh"
#include "expUtils/ExpType.hh"
#include "formula/atom/Atom.hh"
#include "formula/atom/Variable.hh"
#include "formula/expression/SetMembership.hh"
#include "formula/expression/TypeCast.hh"
#include "formula/function/SVAfunction.hh"
#include "formula/temporal/Sere.hh"
#include "globals.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "gtest/gtest_pred_impl.h"

using namespace harm;
using namespace expression;

TEST(OpeTest, bitSelectorLogic) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::SLogic, 8);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto v1 = trace->getLogicVariable("v1");
  v1->assign(0, Logic("000xz01001", 8, 0));

  auto res1 = hparser::parseLogicExpression("v1[3:6]", trace);
  ASSERT_EQ(res1->evaluate(0).toString(), "xz01");

  auto res2 = hparser::parseLogicExpression("v1[6:3]", trace);
  ASSERT_EQ(res2->evaluate(0).toString(), "xz01");
}

TEST(OpeTest, bitSelectorInt) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::SInt, 8);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto v1 = trace->getIntVariable("v1");
  v1->assign(0, safeStoull("0000011001", 2));

  auto res1 = hparser::parseIntExpression("v1[3:6]", trace);
  ASSERT_EQ(res1->evaluate(0), 3);

  auto res2 = hparser::parseIntExpression("v1[6:3]", trace);
  ASSERT_EQ(res2->evaluate(0), 3);
}

TEST(OpeTest, stringConcat) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::String, 0);
  vars.emplace_back("v2", ExpType::String, 0);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto v1 = trace->getStringVariable("v1");
  auto v2 = trace->getStringVariable("v2");
  v1->assign(0, "hello ");
  v2->assign(0, "world");

  auto ress = hparser::parseStringExpression("v1 + v2", trace);
  ASSERT_EQ(ress->evaluate(0), std::string("hello world"));
}

TEST(OpeTest, stringComparison) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::String, 0);
  vars.emplace_back("v2", ExpType::String, 0);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto v1 = trace->getStringVariable("v1");
  auto v2 = trace->getStringVariable("v2");
  v1->assign(0, "hello ");
  v2->assign(0, "world");

  PropositionPtr resp =
      hparser::parseProposition("v1 == \"hello \"", trace);
  ASSERT_EQ(resp->evaluate(0), true);

  resp = hparser::parseProposition("v1 != v2", trace);
  ASSERT_EQ(resp->evaluate(0),
            std::string("hello ") != std::string("world"));

  resp = hparser::parseProposition("v1 > v2", trace);
  ASSERT_EQ(resp->evaluate(0),
            std::string("hello ") > std::string("world"));

  resp = hparser::parseProposition("v1 >= v2", trace);
  ASSERT_EQ(resp->evaluate(0),
            std::string("hello ") >= std::string("world"));

  resp = hparser::parseProposition("v2 < v1", trace);
  ASSERT_EQ(resp->evaluate(0),
            std::string("world") < std::string("hello "));

  resp = hparser::parseProposition("v2 <= v1", trace);
  ASSERT_EQ(resp->evaluate(0),
            std::string("world") <= std::string("hello "));
}

TEST(OpeTest, substring) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::String, 0);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto v1 = trace->getStringVariable("v1");
  v1->assign(0, "hello ");

  StringExpressionPtr resp =
      hparser::parseStringExpression("v1.substr(2,3)", trace);
  ASSERT_EQ(resp->evaluate(0), "llo");

  resp = hparser::parseStringExpression("v1.substr(1)", trace);
  ASSERT_EQ(resp->evaluate(0), "ello ");

  resp = hparser::parseStringExpression("v1.substr()", trace);
  ASSERT_EQ(resp->evaluate(0), "hello ");
}

TEST(OpeTest, setMembershipVsRange) {
  TraceReader *tr =
      new CSVtraceReader("../tests/input/RandomTraceSparse.csv");
  const TracePtr &trace = tr->readTrace();

  auto t1 = hparser::parseTemplateImplication(
      "G({1} |-> {v2 inside {[1:10], [-10:-1], 100, 88}})", trace);
  auto t2 = hparser::parseTemplateImplication(
      "G({1} |-> (v2 <= 10 && v2 >=1) || (v2 <= "
      "-10 && v2 >=-1) || v2==100 || v2==88)",
      trace);
  for (size_t i = 0; i < t1->getTraceLength(); i++) {
    ASSERT_EQ(t1->evaluate(i), t2->evaluate(i));
  }
}

TEST(OpeTest, setMembershipNonConstant) {
  std::vector<VarDeclaration> vars;

  vars.emplace_back("v1", ExpType::UInt, 8);
  vars.emplace_back("v2", ExpType::UInt, 8);
  vars.emplace_back("v3", ExpType::UInt, 8);
  vars.emplace_back("v4", ExpType::UInt, 8);
  vars.emplace_back("v5", ExpType::UInt, 8);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  auto v1 = trace->getIntVariable("v1");
  auto v2 = trace->getIntVariable("v2");
  auto v3 = trace->getIntVariable("v3");
  auto v4 = trace->getIntVariable("v4");
  auto v5 = trace->getIntVariable("v5");

  v1->assign(0, 10);
  v1->assign(1, 10);
  v2->assign(0, 1);
  v3->assign(0, 2);
  v4->assign(0, 9);
  v5->assign(0, 10);

  IntSetMembershipPtr sm =
      std::dynamic_pointer_cast<IntSetMembership>(
          hparser::parseProposition("v1 inside {v2+v3,[v4:v5]}",
                                    trace));

  auto range = sm->getRanges();
  ASSERT_EQ(range[0].first->evaluate(0), (UInt)9);
  ASSERT_EQ(range[0].second->evaluate(0), (UInt)10);

  auto set = sm->getSet();
  ASSERT_EQ((*set.begin())->evaluate(0), (UInt)3);

  ASSERT_EQ(sm->evaluate(0), true);
  ASSERT_EQ(sm->evaluate(1), false);
}

TEST(OpeTest, setMembershipMaxMin) {
  std::vector<VarDeclaration> vars;

  vars.emplace_back("v1", ExpType::SLogic, 8);
  vars.emplace_back("v2", ExpType::ULogic, 8);
  vars.emplace_back("v3", ExpType::SInt, 8);
  vars.emplace_back("v4", ExpType::UInt, 8);

  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  auto v1 = trace->getLogicVariable("v1");
  auto v2 = trace->getLogicVariable("v2");
  auto v3 = trace->getIntVariable("v3");
  auto v4 = trace->getIntVariable("v4");

  LogicSetMembershipPtr smSignedLogicChar =
      std::dynamic_pointer_cast<LogicSetMembership>(
          hparser::parseProposition("v1 inside {[$:$]}", trace));

  LogicSetMembershipPtr smUnsignedLogicChar =
      std::dynamic_pointer_cast<LogicSetMembership>(
          hparser::parseProposition("v2 inside {[$:$]}", trace));

  IntSetMembershipPtr smSignedIntChar =
      std::dynamic_pointer_cast<IntSetMembership>(
          hparser::parseProposition("v3 inside {[$:$]}", trace));

  IntSetMembershipPtr smUnsignedIntChar =
      std::dynamic_pointer_cast<IntSetMembership>(
          hparser::parseProposition("v4 inside {[$:$]}", trace));

  //Logic
  auto rangeSignedLogic = smSignedLogicChar->getRanges();
  ASSERT_EQ(rangeSignedLogic[0].first->evaluate(0).getSignedValue(),
            (SLogic)-128);
  ASSERT_EQ(rangeSignedLogic[0].second->evaluate(0).getSignedValue(),
            (SLogic)127);

  auto rangeUnsignedLogic = smUnsignedLogicChar->getRanges();
  ASSERT_EQ(
      rangeUnsignedLogic[0].first->evaluate(0).getUnsignedValue(),
      (ULogic)0);
  ASSERT_EQ(
      rangeUnsignedLogic[0].second->evaluate(0).getUnsignedValue(),
      (ULogic)255);

  //Integer
  auto rangeSignedInt = smSignedIntChar->getRanges();
  ASSERT_EQ(rangeSignedInt[0].first->evaluate(0), (SInt)-128);
  ASSERT_EQ(rangeSignedInt[0].second->evaluate(0), (SInt)127);

  auto rangeUnsignedInt = smUnsignedIntChar->getRanges();
  ASSERT_EQ(rangeUnsignedInt[0].first->evaluate(0), (UInt)0);
  ASSERT_EQ(rangeUnsignedInt[0].second->evaluate(0), (UInt)255);
}

TEST(OpeTest, pastParsePrint) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::SLogic, 8);
  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto p = hparser::parseLogicExpression("$past(v1)", trace);
  ASSERT_EQ(exp2String(p), "$past(v1)");
}

TEST(OpeTest, pastSemantics) {
  TraceReader *tr =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = tr->readTrace();

  auto t1 = hparser::parseTemplateImplication(
      "G({1} |-> {##1 v2 == $past(v2)})", trace);
  auto t2 = hparser::parseTemplateImplication(
      "G({1} |-> {##1 $stable(v2)})", trace);

  for (size_t i = 0; i < t1->getTraceLength(); i++) {
    ASSERT_EQ(t1->evaluate(i), t2->evaluate(i));
  }

  t1 = hparser::parseTemplateImplication(
      "G({1} |-> {##2 $past(v2,1) == $past(v2,2)})", trace);
  t2 = hparser::parseTemplateImplication(
      "G({1} |-> {{##1 $stable(v2) ##1 true} || {##2 false}})",
      trace);

  for (size_t i = 0; i < t1->getTraceLength(); i++) {
    ASSERT_EQ(t1->evaluate(i), t2->evaluate(i));
  }

  delete tr;
}

TEST(OpeTest, pastPropVsTemporal) {

  clc::psilent = 1;

  TraceReader *traceReader =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = traceReader->readTrace();

  std::vector<ContextPtr> contexts;
  TemplateImplicationPtr t = hparser::parseTemplateImplication(
      "G({1} |-> {$past(P1)})", trace);

  std::unordered_map<int, std::vector<expression::PropositionPtr>>
      domainIdToProps;
  std::unordered_map<int,
                     std::vector<expression::NumericExpressionPtr>>
      domainIdToNumerics;

  domainIdToProps[(int)Location::Con].push_back(
      hparser::parseProposition("v2", trace));

  t->genPermutations(domainIdToProps, domainIdToNumerics);
  t->nextPerm();

  TemplateImplicationPtr fi = hparser::parseTemplateImplication(
      "G({1} |-> {$past(v2)})", trace);

  for (size_t i = 0; i < fi->getTraceLength(); i++) {
    ASSERT_EQ(t->evaluate(i), fi->evaluate(i));
  }

  t = hparser::parseTemplateImplication("G({1} |-> {$past(P1,4)})",
                                        trace);

  t->genPermutations(domainIdToProps, domainIdToNumerics);
  t->nextPerm();

  fi = hparser::parseTemplateImplication("G({1} |-> {$past(v2,4)})",
                                         trace);

  for (size_t i = 0; i < fi->getTraceLength(); i++) {
    ASSERT_EQ(t->evaluate(i), fi->evaluate(i));
  }

  delete traceReader;
}

TEST(OpeTest, pastNonBool) {

  clc::psilent = 1;

  TraceReader *traceReader =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = traceReader->readTrace();

  std::vector<ContextPtr> contexts;
  PropositionPtr p1 = hparser::parseProposition("$past(v6)", trace);
  PropositionPtr p2 = hparser::parseProposition("$past(v9)", trace);
  PropositionPtr p3 = hparser::parseProposition("$past(v8)", trace);
  ASSERT_NE(std::dynamic_pointer_cast<expression::IntPast>(
                std::dynamic_pointer_cast<expression::IntToBool>(p1)
                    ->getItem()),
            nullptr);
  ASSERT_NE(std::dynamic_pointer_cast<expression::FloatPast>(
                std::dynamic_pointer_cast<expression::FloatToBool>(p2)
                    ->getItem()),
            nullptr);
  ASSERT_NE(std::dynamic_pointer_cast<expression::LogicPast>(
                std::dynamic_pointer_cast<expression::LogicToBool>(p3)
                    ->getItem()),
            nullptr);
}

TEST(OpeTest, stableParsePrint) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::SLogic, 8);
  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto p = hparser::parseProposition("$stable(v1)", trace);
  ASSERT_EQ(exp2String(p), "$stable(v1)");
}

TEST(OpeTest, stableSemantics) {
  TraceReader *tr =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = tr->readTrace();

  auto t1 = hparser::parseTemplateImplication(
      "G({1} |-> {##1 $stable(v2)})", trace);
  auto t2 = hparser::parseTemplateImplication(
      "G({1} |-> {(v2 ##1 v2) | (!v2 ##1 !v2)})", trace);

  for (size_t i = 0; i < t1->getTraceLength(); i++) {
    ASSERT_EQ(t1->evaluate(i), t2->evaluate(i));
  }

  delete tr;
}

TEST(OpeTest, stablePropsVsTemporal) {

  clc::psilent = 1;

  TraceReader *traceReader =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = traceReader->readTrace();

  std::vector<ContextPtr> contexts;
  TemplateImplicationPtr t = hparser::parseTemplateImplication(
      "G({1} |-> {$stable(P1)})", trace);

  std::unordered_map<int, std::vector<expression::PropositionPtr>>
      domainIdToProps;
  std::unordered_map<int,
                     std::vector<expression::NumericExpressionPtr>>
      domainIdToNumerics;

  domainIdToProps[(int)Location::Con].push_back(
      hparser::parseProposition("v2", trace));

  t->genPermutations(domainIdToProps, domainIdToNumerics);
  t->nextPerm();

  TemplateImplicationPtr fi = hparser::parseTemplateImplication(
      "G({1} |-> {$stable(v2)})", trace);

  for (size_t i = 0; i < fi->getTraceLength(); i++) {
    ASSERT_EQ(t->evaluate(i), fi->evaluate(i));
  }

  delete traceReader;
}

TEST(OpeTest, stableNonBool) {

  clc::psilent = 1;

  TraceReader *traceReader =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = traceReader->readTrace();

  std::vector<ContextPtr> contexts;
  PropositionPtr p1 = hparser::parseProposition("$stable(v6)", trace);
  PropositionPtr p2 = hparser::parseProposition("$stable(v9)", trace);
  PropositionPtr p3 = hparser::parseProposition("$stable(v8)", trace);

  ASSERT_NE(std::dynamic_pointer_cast<expression::IntStable>(p1),
            nullptr);
  ASSERT_NE(std::dynamic_pointer_cast<expression::FloatStable>(p2),
            nullptr);
  ASSERT_NE(std::dynamic_pointer_cast<expression::LogicStable>(p3),
            nullptr);

  delete traceReader;
}

TEST(OpeTest, roseParsePrint) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::SLogic, 8);
  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto p = hparser::parseProposition("$rose(v1)", trace);
  ASSERT_EQ(exp2String(p), "$rose(v1)");
}

TEST(OpeTest, roseSemantics) {
  TraceReader *tr =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = tr->readTrace();

  auto t1 = hparser::parseTemplateImplication(
      "G({1} |-> {##1 $rose(v2)})", trace);
  auto t2 = hparser::parseTemplateImplication(
      "G({1} |-> {!v2 ##1 v2})", trace);

  for (size_t i = 0; i < t1->getTraceLength(); i++) {
    ASSERT_EQ((t1->evaluate(i) == t2->evaluate(i)) ||
                  t1->evaluate(i) == Trinary::U,
              true);
  }

  delete tr;
}

TEST(OpeTest, rosePropsVsTemporal) {

  clc::psilent = 1;

  TraceReader *traceReader =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = traceReader->readTrace();

  std::vector<ContextPtr> contexts;
  TemplateImplicationPtr t = hparser::parseTemplateImplication(
      "G({1} |-> {$rose(P1)})", trace);

  std::unordered_map<int, std::vector<expression::PropositionPtr>>
      domainIdToProps;
  std::unordered_map<int,
                     std::vector<expression::NumericExpressionPtr>>
      domainIdToNumerics;

  domainIdToProps[(int)Location::Con].push_back(
      hparser::parseProposition("v2", trace));

  t->genPermutations(domainIdToProps, domainIdToNumerics);
  t->nextPerm();

  TemplateImplicationPtr fi = hparser::parseTemplateImplication(
      "G({1} |-> {$rose(v2)})", trace);

  for (size_t i = 0; i < fi->getTraceLength(); i++) {
    ASSERT_EQ(t->evaluate(i), fi->evaluate(i));
  }

  delete traceReader;
}

TEST(OpeTest, roseNonBool) {

  clc::psilent = 1;

  TraceReader *traceReader =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = traceReader->readTrace();

  std::vector<ContextPtr> contexts;
  PropositionPtr p1 = hparser::parseProposition("$rose(v6)", trace);
  PropositionPtr p2 = hparser::parseProposition("$rose(v8)", trace);
  ASSERT_NE(std::dynamic_pointer_cast<expression::IntRose>(p1),
            nullptr);
  ASSERT_NE(std::dynamic_pointer_cast<expression::LogicRose>(p2),
            nullptr);

  delete traceReader;
}

TEST(OpeTest, fellParsePrint) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::SLogic, 8);
  const TracePtr &trace = generatePtr<Trace>(vars, 1);
  auto p = hparser::parseProposition("$fell(v1)", trace);
  ASSERT_EQ(exp2String(p), "$fell(v1)");
}

TEST(OpeTest, fellSemantics) {
  TraceReader *tr =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = tr->readTrace();

  auto t1 = hparser::parseTemplateImplication(
      "G({1} |-> {##1 $fell(v2)})", trace);
  auto t2 = hparser::parseTemplateImplication(
      "G({1} |-> {v2 ##1 !v2})", trace);

  for (size_t i = 0; i < t1->getTraceLength(); i++) {
    ASSERT_EQ((t1->evaluate(i) == t2->evaluate(i)) ||
                  t1->evaluate(i) == Trinary::U,
              true);
  }

  delete tr;
}

TEST(OpeTest, fellPropsVsTemporal) {

  clc::psilent = 1;

  TraceReader *traceReader =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = traceReader->readTrace();

  std::vector<ContextPtr> contexts;
  TemplateImplicationPtr t = hparser::parseTemplateImplication(
      "G({1} |-> {$fell(P1)})", trace);

  std::unordered_map<int, std::vector<expression::PropositionPtr>>
      domainIdToProps;
  std::unordered_map<int,
                     std::vector<expression::NumericExpressionPtr>>
      domainIdToNumerics;

  domainIdToProps[(int)Location::Con].push_back(
      hparser::parseProposition("v2", trace));

  t->genPermutations(domainIdToProps, domainIdToNumerics);
  t->nextPerm();

  TemplateImplicationPtr fi = hparser::parseTemplateImplication(
      "G({1} |-> {$fell(v2)})", trace);

  for (size_t i = 0; i < fi->getTraceLength(); i++) {
    ASSERT_EQ(t->evaluate(i), fi->evaluate(i));
  }

  delete traceReader;
}

TEST(OpeTest, fellNonBool) {

  clc::psilent = 1;

  TraceReader *traceReader =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = traceReader->readTrace();

  PropositionPtr p1 = hparser::parseProposition("$fell(v6)", trace);
  PropositionPtr p2 = hparser::parseProposition("$fell(v8)", trace);
  ASSERT_NE(std::dynamic_pointer_cast<expression::IntFell>(p1),
            nullptr);
  ASSERT_NE(std::dynamic_pointer_cast<expression::LogicFell>(p2),
            nullptr);

  delete traceReader;
}

TEST(OpeTest, isFunction) {
  TraceReader *tr =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = tr->readTrace();

  auto v1 = trace->getBooleanVariable("v1");

  PropositionPtr f = generatePtr<PropositionStable>(
      v1, ExpType::Bool, 1, trace->getLength());

  ASSERT_TRUE(isFunction(f));

  delete tr;
}

TEST(OpeTest, isMultipleMatch) {
  TraceReader *tr =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = tr->readTrace();

  auto t1 = hparser::parseTemplateImplication(
      "G({..##1..;P0[*1:2]} |-> {v1 == 1 && v2 == 2})", trace);
  ASSERT_TRUE(isMultipleMatch(t1->getTemplateFormula()));

  auto t2 = hparser::parseTemplateImplication(
      "G({..##1..;P0} |-> {v1 == 1 && v2 == 2})", trace);
  ASSERT_FALSE(isMultipleMatch(t2->getTemplateFormula()));

  auto t3 = hparser::parseTemplateImplication(
      "G({..##1..;first_match(P0[*1:2])} |-> {v1 == 1 && v2 == 2})",
      trace);
  ASSERT_FALSE(isMultipleMatch(t3->getTemplateFormula()));

  auto t4 = hparser::parseTemplateImplication(
      "G({..##1..;first_match(P0[*1]) ##[1:3] P0} |-> {v1 == 1 && v2 "
      "== 2})",
      trace);
  ASSERT_TRUE(isMultipleMatch(t4->getTemplateFormula()));

  auto t5 = hparser::parseTemplateImplication(
      "G({P0 ##[3:3] P1} |-> {v1 == 1 && v2 "
      "== 2})",
      trace);
  ASSERT_FALSE(isMultipleMatch(t5->getTemplateFormula()));

  delete tr;
}

TEST(OpeTest, convertedLogicSum) {

  clc::psilent = 1;

  TraceReader *traceReader =
      new CSVtraceReader("../tests/input/RandomTrace.csv");
  const TracePtr &trace = traceReader->readTrace();

  LogicExpressionPtr p1 =
      hparser::parseLogicExpression("v7 + 1", trace);

  delete traceReader;
}
