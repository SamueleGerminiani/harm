#include <algorithm>
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
#include "Location.hh"
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

TEST(mmaTest, DTNextMMA) {

  TraceReader *tr = new CSVtraceReader("../tests/input/MMA_Trace.csv",
                                       clc::forceInt);
  const TracePtr &trace = tr->readTrace();

  auto t1 = hparser::parseTemplateImplication(
      "G({..##1.. ##1 x ##[1:3] y} |-> {z})", trace);
  DTOperatorPtr dtop = t1->getDT();
  PropositionPtr dt1 = hparser::parseProposition("dt1", trace);
  PropositionPtr dt0 = hparser::parseProposition("dt0", trace);
  dtop->addItem(dt1, 0);
  dtop->addItem(dt0, 1);
  t1->setCacheAntFalse();

  //debug
  //for (size_t i = 0; i < t1->getTraceLength(); i++) {
  //  std::cout << t1->evaluate(i) << " ";
  //}
  //std::cout << "\n";

  ASSERT_EQ(t1->evaluate(4), Trinary::F);

  dtop->popItem(1);
  dtop->popItem(0);
  t1->setCacheAntFalse();

  //debug
  //for (size_t i = 0; i < t1->getTraceLength(); i++) {
  //  std::cout << t1->evaluate(i) << " ";
  //}
  //std::cout << "\n";

  ASSERT_EQ(t1->evaluate(6), Trinary::T);

  dtop->addItem(dt1, 0);
  dtop->addItem(dt0, 1);
  dtop->removeItems();
  t1->setCacheAntFalse();

  //debug
  //for (size_t i = 0; i < t1->getTraceLength(); i++) {
  //  std::cout << t1->evaluate(i) << " ";
  //}
  //std::cout << "\n";

  ASSERT_EQ(t1->evaluate(6), Trinary::T);
}

TEST(mmaTest, DTNextAndMMA) {

  TraceReader *tr = new CSVtraceReader("../tests/input/MMA_Trace.csv",
                                       clc::forceInt);
  const TracePtr &trace = tr->readTrace();

  auto t1 = hparser::parseTemplateImplication(
      "G({..#1&.. ##1 x ##[1:3] y} |-> {z})", trace);
  DTOperatorPtr dtop = t1->getDT();
  PropositionPtr dt1 = hparser::parseProposition("dt1", trace);
  PropositionPtr dt0 = hparser::parseProposition("dt0", trace);
  dtop->addItem(dt1, 0);
  dtop->addItem(dt0, 1);
  dtop->addItem(dt1, 1);
  t1->setCacheAntFalse();

  //debug
  //for (size_t i = 0; i < t1->_maxLength; i++) {
  //  std::cout << t1->evaluate(i) << " ";
  //}
  //std::cout << "\n";

  ASSERT_EQ(t1->evaluate(4), Trinary::F);

  dtop->popItem(1);
  dtop->popItem(1);
  dtop->popItem(0);
  t1->setCacheAntFalse();

  //debug
  //for (size_t i = 0; i < t1->_maxLength; i++) {
  //  std::cout << t1->evaluate(i) << " ";
  //}
  //std::cout << "\n";

  ASSERT_EQ(t1->evaluate(6), Trinary::T);

  dtop->addItem(dt1, 0);
  dtop->addItem(dt0, 1);
  dtop->addItem(dt1, 1);
  dtop->removeItems();
  t1->setCacheAntFalse();

  //debug
  //for (size_t i = 0; i < t1->_maxLength; i++) {
  //  std::cout << t1->evaluate(i) << " ";
  //}
  //std::cout << "\n";

  ASSERT_EQ(t1->evaluate(6), Trinary::T);
}

TEST(mmaTest, DTNCRepsMMA) {

  TraceReader *tr = new CSVtraceReader("../tests/input/MMA_Trace.csv",
                                       clc::forceInt);
  const TracePtr &trace = tr->readTrace();

  auto t1 = hparser::parseTemplateImplication(
      "G({..[->1]@;.. ##1 x ##[1:3] y} |-> {z})", trace);
  DTOperatorPtr dtop = t1->getDT();
  PropositionPtr dt1 = hparser::parseProposition("dt1", trace);
  PropositionPtr dt0 = hparser::parseProposition("dt0", trace);
  dtop->addItem(dt1, 0);
  dtop->addItem(dt0, 1);
  t1->setCacheAntFalse();

  //std::cout << t1->getSpotFormula() << "\n";
  //std::cout << t1->getAssertionStr(Language::SpotLTL) << "\n";
  //std::cout << t1->getColoredAssertion() << "\n";
  ////debug
  //for (size_t i = 0; i < t1->_maxLength; i++) {
  //  std::cout << t1->evaluate(i) << " ";
  //}
  //std::cout << "\n";

  ASSERT_EQ(t1->evaluate(4), Trinary::F);

  dtop->popItem(1);
  dtop->popItem(0);
  t1->setCacheAntFalse();

  //debug
  //for (size_t i = 0; i < t1->_maxLength; i++) {
  //  std::cout << t1->evaluate(i) << " ";
  //}
  //std::cout << "\n";

  ASSERT_EQ(t1->evaluate(6), Trinary::T);

  dtop->addItem(dt1, 0);
  dtop->addItem(dt0, 1);
  dtop->removeItems();
  t1->setCacheAntFalse();

  //debug
  //for (size_t i = 0; i < t1->_maxLength; i++) {
  //  std::cout << t1->evaluate(i) << " ";
  //}
  //std::cout << "\n";

  ASSERT_EQ(t1->evaluate(6), Trinary::T);
}
