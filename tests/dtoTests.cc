#include <algorithm>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits.h>
#include <stddef.h>
#include <string>
#include <vector>

#include "CSVtraceReader.hh"
#include "DTOperator.hh"
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

TEST(DTOTest, dtAndPrintEval) {
  clc::outputLang = Language::SpotLTL;
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  v2->assign(0, 1);
  v2->assign(1, 1);
  v2->assign(2, 0);
  v1->assign(0, 1);
  v1->assign(1, 1);
  v1->assign(2, 0);
  v4->assign(2, 1);
  DTLimits limits;
  limits._maxDepth = -1;
  limits._maxAll = 5;
  limits._maxWidth = 5;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..&&..;v4} |-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->addItem(v1, -1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1;v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->addItem(v2, -1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({(v1 && v2);v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->popItem(-1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1;v4} |-> con)");

  dto->popItem(-1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");

  dto->removeItems();
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");

  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);
}

TEST(DTOTest, dtAndReductionNoChange) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  DTLimits limits;
  limits._maxDepth = 7;
  limits._maxAll = 7;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..&&..}|-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  dto->addItem(v1, 1);
  dto->addItem(v2, 2);
  TemporalExpressionPtr rf = dto->getReducedFormula(1);
  ASSERT_EQ(temp2String(rf, Language::SpotLTL, PrintMode::ShowAll),
            "G({(v1 && v2)} |-> !con)");
}

TEST(DTOTest, dtAndMinimize) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr con = trace->getBooleanVariable("con");
  v2->assign(0, 1);
  v1->assign(0, 1);
  con->assign(0, 1);

  DTLimits limits;
  limits._maxDepth = 0;
  limits._maxAll = 3;
  limits._maxAll = 3;

  TemplateImplicationPtr t = hparser::parseTemplateImplication(
      "G({..&&..}|-> con)", trace, limits);
  DTOperatorPtr dto = t->getDT();
  dto->addItem(v1, 0);
  dto->addItem(v1, 0);
  dto->addItem(v2, 1);

  DTSolution dtSol = dto->getMinimizedSolution(false);
  ASSERT_EQ("G({(v1 && v1 && v2)} |-> con)", t->getAssertionStr());
  dto->removeItems();

  for (auto prop : dtSol.getUnidimensionalSolution()) {
    t->getDT()->addItem(prop, -1);
  }

  ASSERT_EQ("G({v1} |-> con)",
            temp2String(dto->getReducedFormula(0), Language::SpotLTL,
                        PrintMode::ShowAll));
}

TEST(DTOTest, dtNextPrintEval) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  v2->assign(0, 1);
  v1->assign(1, 1);
  v4->assign(2, 1);
  DTLimits limits;
  limits._maxDepth = 5;
  limits._maxAll = 5;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..##1..;v4} |-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->addItem(v1, -1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1;v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->addItem(v2, -1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v2 ##1 v1;v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->popItem(-1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1;v4} |-> con)");

  dto->popItem(-1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");

  dto->addItem(v1, 2);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1 ##1 true ##1 true;v4} |-> con)");

  dto->removeItems();
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");

  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);
  //-------------------------------------------------------

  TemplateImplicationPtr imp2 = hparser::parseTemplateImplication(
      "G({v4;..##1..} -> con)", trace, limits);
  DTOperatorPtr dto2 = imp2->getDT();
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");

  dto2->addItem(v1, -1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1} -> con)");

  dto2->addItem(v2, -1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1 ##1 v2} -> con)");

  dto2->popItem(-1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1} -> con)");

  dto2->popItem(-1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");

  dto2->addItem(v1, 2);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true ##1 true ##1 v1} -> con)");

  dto2->removeItems();
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");
}

TEST(DTOTest, dtNextReductionMM) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  DTLimits limits;
  limits._maxDepth = 7;
  limits._maxAll = 7;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..##2..;v4}|-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  dto->addItem(v1, 1);
  dto->addItem(v2, 3);
  dto->addItem(v4, 6);
  //std::cout << imp->getColoredAssertion() << "\n";
  TemporalExpressionPtr rf = dto->getReducedFormula(1);
  //std::cout << temp2ColoredString(rf, Language::SpotLTL, 1) << "\n";
  ASSERT_EQ(temp2String(rf, Language::SpotLTL, PrintMode::ShowAll),
            "G({v4 ##6 v2 ##4 v1 ##2 true;v4} |-> !con)");
  dto->removeItems();

  dto->addItem(v1, 2);
  ASSERT_EQ(temp2String(dto->getReducedFormula(0), Language::SpotLTL,
                        PrintMode::ShowAll),
            "G({v1 ##4 true;v4} |-> con)");
}

TEST(DTOTest, dtNextReduction) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  DTLimits limits;
  limits._maxDepth = 7;
  limits._maxAll = 7;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..##1..}-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  dto->addItem(v4, 3);
  dto->addItem(v1, 5);
  //std::cout << imp->getColoredAssertion() << "\n";
  TemporalExpressionPtr rf = dto->getReducedFormula(1);
  //  std::cout << "=====================" << "\n";
  //std::cout << temp2ColoredString(rf, Language::SpotLTL, 1) << "\n";
  ASSERT_EQ(temp2String(rf, Language::SpotLTL, PrintMode::ShowAll),
            "G({##3 v4 ##2 v1} -> !con)");
}

TEST(DTOTest, dtNextReductionNoChange) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  DTLimits limits;
  limits._maxDepth = 7;
  limits._maxAll = 7;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..##1..}|-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  dto->addItem(v1, 1);
  dto->addItem(v2, 2);
  TemporalExpressionPtr rf = dto->getReducedFormula(0);
  //std::cout << temp2ColoredString(rf, Language::SpotLTL, 1) << "\n";
  ASSERT_EQ(temp2String(rf, Language::SpotLTL, PrintMode::ShowAll),
            "G({v2 ##1 v1 ##1 true} |-> con)");

  dto->removeItems();
  dto->addItem(v1, 0);
  ASSERT_EQ("G({v1} |-> con)",
            temp2String(dto->getReducedFormula(0), Language::SpotLTL,
                        PrintMode::ShowAll));
}

TEST(DTOTest, dtNextMinimize) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr con = trace->getBooleanVariable("con");
  v2->assign(0, 1);
  v2->assign(1, 0);
  v1->assign(0, 0);
  v1->assign(1, 1);
  con->assign(0, 0);
  con->assign(1, 1);

  v1->assign(8, 1);
  con->assign(8, 0);

  DTLimits limits;
  limits._maxDepth = 7;
  limits._maxAll = 7;

  TemplateImplicationPtr t = hparser::parseTemplateImplication(
      "G({..##1..}|-> con)", trace, limits);
  DTOperatorPtr dto = t->getDT();
  dto->addItem(v1, 0);
  dto->addItem(v2, 1);

  DTSolution dtSol = dto->getMinimizedSolution(false);
  ASSERT_EQ("G({v2 ##1 v1} |-> con)", t->getAssertionStr());
  dto->removeItems();

  auto multiSol = dtSol.getUnidimensionalSolution();
  for (auto prop : multiSol) {
    t->getDT()->addItem(prop, -1);
  }

  ASSERT_EQ("G({v2 ##1 true} |-> con)",
            temp2String(dto->getReducedFormula(0), Language::SpotLTL,
                        PrintMode::ShowAll));
}

//DTNextAnd----------------------------------------------

TEST(DTOTest, dtNextAndPrintEval) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v3 = trace->getBooleanVariable("v3");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  v2->assign(0, 1);
  v1->assign(1, 1);
  v4->assign(2, 1);
  DTLimits limits;
  limits._maxDepth = 5;
  limits._maxWidth = 5;
  limits._maxAll = 5;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..#1&..;v4} |-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->addItem(v1, 0);
  dto->addItem(v1, 0);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({(v1 && v1);v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->addItem(v2, 1);
  dto->addItem(v2, 1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({(v2 && v2) ##1 (v1 && v1);v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->popItem(1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v2 ##1 (v1 && v1);v4} |-> con)");

  dto->popItem(1);
  dto->popItem(0);
  dto->popItem(0);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");

  dto->addItem(v1, 2);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1 ##1 true ##1 true;v4} |-> con)");

  dto->removeItems();
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");

  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);
  //-------------------------------------------------------

  TemplateImplicationPtr imp2 = hparser::parseTemplateImplication(
      "G({v4;..#1&..} -> con)", trace, limits);
  DTOperatorPtr dto2 = imp2->getDT();
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");

  dto2->addItem(v1, 0);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1} -> con)");

  dto2->addItem(v2, 1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1 ##1 v2} -> con)");

  dto2->popItem(1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1} -> con)");

  dto2->popItem(0);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");

  dto2->addItem(v1, 2);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true ##1 true ##1 v1} -> con)");

  dto2->removeItems();
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");
}

TEST(DTOTest, dtNextAndReductionMM) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  DTLimits limits;
  limits._maxDepth = 7;
  limits._maxAll = 7;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..#2&..;v4}|-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  dto->addItem(v1, 1);
  dto->addItem(v1, 1);
  dto->addItem(v2, 3);
  dto->addItem(v2, 3);
  dto->addItem(v4, 6);
  dto->addItem(v4, 6);
  //std::cout << imp->getColoredAssertion() << "\n";
  TemporalExpressionPtr rf = dto->getReducedFormula(1);
  //std::cout << temp2ColoredString(rf, Language::SpotLTL, 1) << "\n";
  ASSERT_EQ(temp2String(rf, Language::SpotLTL, PrintMode::ShowAll),
            "G({(v4 && v4) ##6 (v2 && v2) ##4 (v1 && v1) ##2 "
            "true;v4} |-> !con)");

  dto->removeItems();
  dto->addItem(v1, 2);
  ASSERT_EQ(temp2String(dto->getReducedFormula(0), Language::SpotLTL,
                        PrintMode::ShowAll),
            "G({v1 ##4 true;v4} |-> con)");
}

TEST(DTOTest, dtNextAndReduction) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  DTLimits limits;
  limits._maxDepth = 7;
  limits._maxAll = 7;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..#1&..}-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  dto->addItem(v4, 3);
  dto->addItem(v4, 3);
  dto->addItem(v1, 5);
  dto->addItem(v1, 5);
  //std::cout << imp->getColoredAssertion() << "\n";
  TemporalExpressionPtr rf = dto->getReducedFormula(1);
  //  std::cout << "=====================" << "\n";
  //std::cout << temp2ColoredString(rf, Language::SpotLTL, 1) << "\n";
  ASSERT_EQ(temp2String(rf, Language::SpotLTL, PrintMode::ShowAll),
            "G({##3 (v4 && v4) ##2 (v1 && v1)} -> !con)");
}

TEST(DTOTest, dtNextAndReductionNoChange) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  DTLimits limits;
  limits._maxDepth = 7;
  limits._maxAll = 7;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..#1&..}|-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  dto->addItem(v1, 1);
  dto->addItem(v1, 1);
  dto->addItem(v2, 2);
  dto->addItem(v2, 2);
  TemporalExpressionPtr rf = dto->getReducedFormula(0);
  //std::cout << temp2ColoredString(rf, Language::SpotLTL, 1) << "\n";
  ASSERT_EQ(temp2String(rf, Language::SpotLTL, PrintMode::ShowAll),
            "G({(v2 && v2) ##1 (v1 && v1) ##1 true} |-> con)");

  dto->removeItems();
  dto->addItem(v1, 0);
  ASSERT_EQ("G({v1} |-> con)",
            temp2String(dto->getReducedFormula(0), Language::SpotLTL,
                        PrintMode::ShowAll));
}

TEST(DTOTest, dtNextAndMinimize) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr con = trace->getBooleanVariable("con");
  v2->assign(0, 1);
  v2->assign(1, 0);
  v1->assign(0, 0);
  v1->assign(1, 1);
  con->assign(0, 0);
  con->assign(1, 1);

  v2->assign(5, 1);
  con->assign(5, 0);

  v1->assign(8, 1);
  con->assign(8, 0);

  DTLimits limits;
  limits._maxDepth = 7;
  limits._maxAll = 7;

  TemplateImplicationPtr t = hparser::parseTemplateImplication(
      "G({..#1&..}|-> con)", trace, limits);
  DTOperatorPtr dto = t->getDT();
  dto->addItem(v1, 0);
  dto->addItem(v1, 0);
  dto->addItem(v2, 1);
  dto->addItem(v2, 1);

  DTSolution dtSol = dto->getMinimizedSolution(false);
  ASSERT_EQ("G({(v2 && v2) ##1 (v1 && v1)} |-> con)",
            t->getAssertionStr());
  dto->removeItems();

  auto multiSol = dtSol.getMultidimensionalSolution();
  for (size_t i = 0; i < multiSol.size(); i++) {
    for (auto prop : multiSol[i]) {
      t->getDT()->addItem(prop, i);
    }
  }

  ASSERT_EQ("G({v2 ##1 v1} |-> con)",
            temp2String(dto->getReducedFormula(0), Language::SpotLTL,
                        PrintMode::ShowAll));

  dto->removeItems();
  dto->addItem(v1, 0);
  ASSERT_EQ("G({v1} |-> con)",
            temp2String(dto->getReducedFormula(0), Language::SpotLTL,
                        PrintMode::ShowAll));
}

TEST(DTOTest, dtGotToPrintEval) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v3 = trace->getBooleanVariable("v3");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  v2->assign(0, 1);
  v1->assign(1, 1);
  v4->assign(2, 1);
  DTLimits limits;
  limits._maxDepth = 5;
  limits._maxAll = 5;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..[->1]@;..;v4} |-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->addItem(v1, -1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1;v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->addItem(v2, -1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v2;v1[->1];v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->popItem(-1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1;v4} |-> con)");

  dto->popItem(-1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");

  dto->addItem(v1, 2);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1;true[->1];true[->1];v4} |-> con)");

  dto->removeItems();
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");

  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);
  //-------------------------------------------------------

  TemplateImplicationPtr imp2 = hparser::parseTemplateImplication(
      "G({v4;..[->1]@;..} -> con)", trace, limits);
  DTOperatorPtr dto2 = imp2->getDT();
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");

  dto2->addItem(v1, -1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1} -> con)");

  dto2->addItem(v2, -1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1[->1];v2} -> con)");

  dto2->addItem(v3, -1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1[->1];v2[->1];v3} -> con)");

  dto2->popItem(-1);
  dto2->popItem(-1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1} -> con)");

  dto2->popItem(-1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");

  dto2->addItem(v1, 2);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true[->1];true[->1];v1} -> con)");

  dto2->removeItems();
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");
}

TEST(DTOTest, dtNCRepsPrintEval) {
  std::vector<VarDeclaration> vars;
  vars.emplace_back("v1", ExpType::Bool, 1);
  vars.emplace_back("v2", ExpType::Bool, 1);
  vars.emplace_back("v3", ExpType::Bool, 1);
  vars.emplace_back("v4", ExpType::Bool, 1);
  vars.emplace_back("con", ExpType::Bool, 1);
  const TracePtr &trace = generatePtr<Trace>(vars, 10);
  BooleanVariablePtr v1 = trace->getBooleanVariable("v1");
  BooleanVariablePtr v2 = trace->getBooleanVariable("v2");
  BooleanVariablePtr v3 = trace->getBooleanVariable("v3");
  BooleanVariablePtr v4 = trace->getBooleanVariable("v4");
  v2->assign(0, 1);
  v1->assign(1, 1);
  v4->assign(2, 1);
  DTLimits limits;
  limits._maxDepth = 5;
  limits._maxAll = 5;

  TemplateImplicationPtr imp = hparser::parseTemplateImplication(
      "G({..[=1]@;..;v4} |-> con)", trace, limits);
  DTOperatorPtr dto = imp->getDT();
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->addItem(v1, -1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1;v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->addItem(v2, -1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v2;v1[=1];v4} |-> con)");
  ASSERT_EQ(imp->evaluate_ant(0), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);

  dto->popItem(-1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1;v4} |-> con)");

  dto->popItem(-1);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");

  dto->addItem(v1, 2);
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({v1;true[=1];true[=1];v4} |-> con)");

  dto->removeItems();
  ASSERT_EQ(imp->getAssertionStr(Language::SpotLTL),
            "G({true;v4} |-> con)");

  ASSERT_EQ(imp->evaluate_ant(0), Trinary::F);
  ASSERT_EQ(imp->evaluate_ant(1), Trinary::T);
  ASSERT_EQ(imp->evaluate_ant(2), Trinary::F);
  //-------------------------------------------------------

  TemplateImplicationPtr imp2 = hparser::parseTemplateImplication(
      "G({v4;..[=1]@;..} -> con)", trace, limits);
  DTOperatorPtr dto2 = imp2->getDT();
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");

  dto2->addItem(v1, -1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1} -> con)");

  dto2->addItem(v2, -1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1[=1];v2} -> con)");

  dto2->addItem(v3, -1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1[=1];v2[=1];v3} -> con)");

  dto2->popItem(-1);
  dto2->popItem(-1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;v1} -> con)");

  dto2->popItem(-1);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");

  dto2->addItem(v1, 2);
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true[=1];true[=1];v1} -> con)");

  dto2->removeItems();
  ASSERT_EQ(imp2->getAssertionStr(Language::SpotLTL),
            "G({v4;true} -> con)");
}
